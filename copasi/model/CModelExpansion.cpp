// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelExpansion.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2009/12/17 10:55:17 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CModelExpansion.h"

#include "CModel.h"
#include "function/CExpression.h"
#include "report/CCopasiObject.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"

CModelExpansion::CModelExpansion(CModel* pModel)
    : mpModel(pModel)
{
}

void CModelExpansion::setModel(CModel* pModel)
{
  mpModel = pModel;
}

void CModelExpansion::simpleCall(const CCompartment * source  , int  mult)
{

  if (!mpModel) return;

  if (!mpModel->getCompartments().size()) return;

  ci.keyMap[mpModel->getKey()] = "";

  unsigned C_INT32 i, imax;

  imax = mpModel->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      const CCompartment* sourceComp = mpModel->getCompartments()[i];

      ci.keyMap[sourceComp->getKey()] = "";
      nameInSet(sourceComp->getObjectName());
    }

  imax = mpModel->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      const CMetab* sourceMetab = mpModel->getMetabolites()[i];

      ci.keyMap[sourceMetab->getKey()] = "";
    }

  imax = mpModel->getReactions().size();

  for (i = 0; i < imax; ++i)
    {
      CReaction * sourceReac = mpModel->getReactions()[i];

      nameInSet(sourceReac->getObjectName());
    }

  imax = mpModel->getModelValues().size();

  for (i = 0; i < imax; ++i)
    {
      const CModelValue* sourceModVal = mpModel->getModelValues()[i];

      ci.keyMap[sourceModVal->getKey()] = "";
      nameInSet(sourceModVal->getObjectName());
    }

  imax = mpModel->getEvents().size();

  for (i = 0; i < imax; ++i)
    {
      const CEvent* sourceEvent = mpModel->getEvents()[i];

      nameInSet(sourceEvent->getObjectName());
    }

  bool progress;

  C_INT m;

  for (m = 0; m < mult; ++m)
    {
      std::ostringstream newname;
      newname <<  source->getObjectName() << "_" << m;
      name = newname.str();

      ci = copyCompartment(source, m);

      progress  =     copyCompartmentsExpressions(source)
                      &&  copyMetabolitesExpressions(source)
                      &&  copyModelValuesExpressions(m)
                      &&  copyEvents(m);
    }

  if (!progress)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCModelExpansion + 1);
      return;
    }

  mpModel->compileIfNecessary(NULL);
}

/**
 **      This method tests whether the given C name already assigned,
 **      put the new name (in cappital letters:
 **      all names can be upper or lower case)
 **      in the set of assigned names
 **      or  modify the name
 **/

std::string CModelExpansion::testName(const std::string & mname)
{
  std::locale C("C");
  char ch;

  std::ostringstream newname, tmp;

  unsigned C_INT32 name_size = mname.size();
  unsigned C_INT32 i;

  for (i = 0; i < name_size; i++)
    {
      ch = mname[i];

      if (std::isalpha(ch, C) && std::islower(ch, C))
        tmp << (char) toupper(ch);
      else
        tmp << ch;
    }

  if (NameSet.find(tmp.str()) == NameSet.end())
    {
      NameSet.insert(tmp.str());

      return mname;
    }
  else
    {
      newname << mname << "_";

      return testName(newname.str());
    }
}

void CModelExpansion::nameInSet(const std::string & mname)
{
  std::locale C("C");
  char ch;

  std::ostringstream newname, tmp;

  unsigned C_INT32 name_size = mname.size();
  unsigned C_INT32 i;

  for (i = 0; i < name_size; i++)
    {
      ch = mname[i];

      if (std::isalpha(ch, C) && std::islower(ch, C))
        tmp << (char) toupper(ch);
      else
        tmp << ch;
    }

  NameSet.insert(tmp.str());

  return;
}

CModelExpansion::CompartmentInfo CModelExpansion::copyCompartment(const CCompartment* source, C_INT32 & count)
{
  CompartmentInfo ret;

  if (!mpModel) return ret;

  if (!source) return ret;

  //create new compartment
  CCompartment* newComp = mpModel->createCompartment(testName(name), source->getInitialValue());

  if (!newComp) return ret;

  ret.key = newComp->getKey();

  newComp->setDimensionality(source->getDimensionality());

  ret.keyMap[source->getKey()] = newComp->getKey();

  //create copies of the metabs
  unsigned C_INT32 i, imax = source->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      CMetab* pSourceMetab = source->getMetabolites()[i];
      CMetab* pNewMetab = mpModel->createMetabolite(pSourceMetab->getObjectName(), newComp->getObjectName(), pSourceMetab->getInitialConcentration());

      if (!pNewMetab)
        continue; //TODO error handling, should not happen

      pNewMetab->setStatus(pSourceMetab->getStatus());

      ret.keyMap[pSourceMetab->getKey()] = pNewMetab->getKey();
    }

  newComp->setStatus(source->getStatus());

  //create copies of the relevant reactions
  imax = mpModel->getReactions().size();

  for (i = 0; i < imax; ++i)
    {
      CReaction * pReac = mpModel->getReactions()[i];

      if (reactionInvolvesCompartment(pReac, source))
        {

          std::ostringstream newname;
          newname << pReac->getObjectName() <<  "_" << count;

          CReaction* pNewReac = mpModel->createReaction(testName(newname.str()));

          if (!pNewReac)
            continue; //should not happen TODO: error handling

          //copy the chemical equation. If the involved metabs are among those that
          //were copied with the compartment, replace them. Otherwise keep the original metab
          pNewReac->setReversible(pReac->isReversible());
          std::map<std::string, std::string>::const_iterator mapIt;
          std::string targetKey;
          unsigned C_INT32 j, jmax = pReac->getChemEq().getSubstrates().size();

          for (j = 0; j < jmax; ++j)
            {
              const CChemEqElement * sourceElement = pReac->getChemEq().getSubstrates()[j];
              //check if the metab is in the map. If yes, translate it, otherwise not.
              mapIt = ret.keyMap.find(sourceElement->getMetaboliteKey());

              if (mapIt == ret.keyMap.end())
                targetKey = sourceElement->getMetaboliteKey();
              else
                targetKey = mapIt->second;

              pNewReac->addSubstrate(targetKey, sourceElement->getMultiplicity());
            }

          jmax = pReac->getChemEq().getProducts().size();

          for (j = 0; j < jmax; ++j)
            {
              const CChemEqElement * sourceElement = pReac->getChemEq().getProducts()[j];
              //check if the metab is in the map. If yes, translate it, otherwise not.
              mapIt = ret.keyMap.find(sourceElement->getMetaboliteKey());

              if (mapIt == ret.keyMap.end())
                targetKey = sourceElement->getMetaboliteKey();
              else
                targetKey = mapIt->second;

              pNewReac->addProduct(targetKey, sourceElement->getMultiplicity());
            }

          jmax = pReac->getChemEq().getModifiers().size();

          for (j = 0; j < jmax; ++j)
            {
              const CChemEqElement * sourceElement = pReac->getChemEq().getModifiers()[j];
              //check if the metab is in the map. If yes, translate it, otherwise not.
              mapIt = ret.keyMap.find(sourceElement->getMetaboliteKey());

              if (mapIt == ret.keyMap.end())
                targetKey = sourceElement->getMetaboliteKey();
              else
                targetKey = mapIt->second;

              pNewReac->addModifier(targetKey);
            }

          //set the kinetic function
          pNewReac->setFunction(const_cast<CFunction*>(pReac->getFunction()));

          //mapping and local parameters
          for (j = 0; j < pNewReac->getFunctionParameters().size(); ++j)
            {
              switch (pNewReac->getFunctionParameters()[j]->getUsage())
                {
                  case CFunctionParameter::SUBSTRATE:
                  case CFunctionParameter::PRODUCT:
                  case CFunctionParameter::MODIFIER:
                    //translate the metab keys
                  {
                    bool isVector = (pNewReac->getFunctionParameters()[j]->getType() == CFunctionParameter::VFLOAT64);

                    //we assume that only SUBSTRATE, PRODUCT, MODIFIER can be vectors
                    if (isVector)
                      pNewReac->clearParameterMapping(j);

                    unsigned C_INT32 k;

                    for (k = 0; k < pReac->getParameterMappings()[j].size(); ++k)
                      {
                        mapIt = ret.keyMap.find(pReac->getParameterMappings()[j][k]);

                        if (mapIt == ret.keyMap.end())
                          targetKey = pReac->getParameterMappings()[j][k];
                        else
                          targetKey = mapIt->second;

                        if (isVector)
                          pNewReac->addParameterMapping(j, targetKey);
                        else
                          pNewReac->setParameterMapping(j, targetKey);
                      }
                  }
                  break;

                  case CFunctionParameter::TIME:
                    //just copy the key
                    pNewReac->setParameterMapping(j, pReac->getParameterMappings()[j][0]);
                    break;

                  case CFunctionParameter::VOLUME:

                    //translate the compartment key if necessary
                    if (pReac->getParameterMappings()[j][0] == source->getKey())
                      pNewReac->setParameterMapping(j, newComp->getKey());
                    else
                      pNewReac->setParameterMapping(j, pReac->getParameterMappings()[j][0]);

                    //TODO: this needs to be adapted when sets of compartments will be copied
                    break;

                  case CFunctionParameter::PARAMETER:

                    if (pReac->isLocalParameter(j))
                      pNewReac->setParameterValue(pNewReac->getFunctionParameters()[j]->getObjectName(),
                                                  pReac->getParameterValue(pNewReac->getFunctionParameters()[j]->getObjectName()));
                    else
                      pNewReac->setParameterMapping(j, pReac->getParameterMappings()[j][0]);

                    break;

                  default:
                    //TODO: error handling
                    break;
                }
            }
        }
    }

  return ret;
}

//static
bool CModelExpansion::reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp)
{
  if (!reac) return false;

  if (!comp) return false;

  unsigned C_INT32 i, imax = reac->getChemEq().getSubstrates().size();

  for (i = 0; i < imax; ++i)
    if (reac->getChemEq().getSubstrates()[i]->getMetabolite()->getCompartment() == comp)
      return true;

  imax = reac->getChemEq().getProducts().size();

  for (i = 0; i < imax; ++i)
    if (reac->getChemEq().getProducts()[i]->getMetabolite()->getCompartment() == comp)
      return true;

  imax = reac->getChemEq().getModifiers().size();

  for (i = 0; i < imax; ++i)
    if (reac->getChemEq().getModifiers()[i]->getMetabolite()->getCompartment() == comp)
      return true;

  return false;
}

bool CModelExpansion::copyModelValuesExpressions(C_INT32 & count)
{
  bool info = false;

  unsigned C_INT32 i, imax = mpModel->getModelValues().size();

  for (i = 0; i < imax; ++i)
    {
      CModelValue* source = mpModel->getModelValues()[i];

      if (!source) return info;

      std::string infix = "";
      std::string newInfix = "";

      const CExpression* pExpression = source->getExpressionPtr();
      CModelValue* newModVal;

      if (pExpression != NULL)
        {
          infix = pExpression->getInfix().c_str();
          newInfix = copyExpression(pExpression);

          if (infix != newInfix)
            {
              std::ostringstream newname;
              newname << source->getObjectName() << "_" << count;

              newModVal = mpModel->createModelValue(testName(newname.str()), source->getInitialValue());
              newModVal->setStatus(source->getStatus());
              newModVal->setExpression(newInfix);

              ci.keyMap[source->getKey()] = newModVal->getKey();
            }
        }

      if (source->getInitialExpression() != "")
        {
          pExpression = source->getInitialExpressionPtr();

          infix = pExpression->getInfix().c_str();
          newInfix = copyExpression(pExpression);

          if (infix != newInfix)
            if (ci.keyMap[source->getKey()] == "")
              {
                std::ostringstream newname;
                newname << source->getObjectName() << "_" << count;

                newModVal = mpModel->createModelValue(testName(newname.str()), source->getInitialValue());
                newModVal->setStatus(source->getStatus());

                const CExpression* tmpExpression = source->getExpressionPtr();

                if (tmpExpression != NULL)
                  newModVal->setExpression(tmpExpression->getInfix().c_str());

                newModVal->setInitialExpression(newInfix);

                ci.keyMap[source->getKey()] = newModVal->getKey();
              }
            else
              newModVal->setInitialExpression(newInfix);
        }
    }

  return true;
}

bool CModelExpansion::copyMetabolitesExpressions(const CCompartment* source)
{
  bool info = false;

  unsigned C_INT32 i, imax = source->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      CMetab* pSourceMetab = source->getMetabolites()[i];

      if (!pSourceMetab) return info;

      std::string newKey = ci.keyMap[pSourceMetab->getKey()];

      CCopasiObject*  pObject = (CCopasiRootContainer::getKeyFactory()->get(newKey));

      CMetab*  newMetab = dynamic_cast< CMetab * >(pObject);

      if (!newMetab) return info;

      std::string infix = "";

      const CExpression* pExpression = pSourceMetab->getExpressionPtr();

      if (pExpression != NULL)
        {
          infix = copyExpression(pExpression);
          newMetab->setExpression(infix);
        }

      if (pSourceMetab->getInitialExpression() != "")
        {
          infix = copyExpression(pSourceMetab->getInitialExpressionPtr());
          newMetab->setInitialExpression(infix);
        }
    }

  return true;
}

bool CModelExpansion::copyCompartmentsExpressions(const CCompartment* source)
{

  bool info = false;

  std::string newKey = ci.keyMap[source->getKey()];

  CCopasiObject*  pObject = (CCopasiRootContainer::getKeyFactory()->get(newKey));

  CCompartment*  newComp = dynamic_cast< CCompartment * >(pObject);

  if (!newComp) return info;

  std::string infix = "";

  const CExpression* pExpression = source->getExpressionPtr();

  if (pExpression != NULL)
    {
      infix = copyExpression(pExpression);
      newComp->setExpression(infix);
    }

  if (source->getInitialExpression() != "")
    {
      infix = copyExpression(source->getInitialExpressionPtr());
      newComp->setInitialExpression(infix);
    }

  return true;
}

std::string CModelExpansion::copyExpression(const CExpression * pExpression)
{

  CExpression* tmp;
  tmp = new CExpression(*pExpression, mpModel);

  const std::vector<CEvaluationNode*>& objectNodes = tmp->getNodeList();
  unsigned j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (CEvaluationNode::type(objectNodes[j]->getType()) == CEvaluationNode::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);

          assert(pObjectNode != NULL);

          CCopasiObjectName cn = pObjectNode->getObjectCN();

          const CCopasiObject* mObject = mpModel->getObjectDataModel()->getObject(cn);

          assert(mObject != NULL);

          std::string host = "";

          if (mObject->isReference())
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          assert(mObject != NULL);

          std::string key;

          key = ci.keyMap[(dynamic_cast<const CModelEntity * >(mObject))->getKey()];

          if (key == "") key = (dynamic_cast<const CModelEntity * >(mObject))->getKey();

          CCopasiObject*  pObject = (CCopasiRootContainer::getKeyFactory()->get(key));

          cn = pObject->getCN() + host;

          pObjectNode->setData("<" + cn + ">");
        }
    }

  tmp->updateTree();

  return tmp->getInfix().c_str();
}

bool CModelExpansion::copyEvents(C_INT32 & count)
{

  bool info = false;

  unsigned C_INT32 i, imax = mpModel->getEvents().size();

  for (i = 0; i < imax; ++i)
    {
      const CEvent* sourceEvent = mpModel->getEvents()[i];
      CEvent* newEvent;

      std::string infix = "";
      std::string trigger = "";
      std::string  delay = "";
      std::string assignment = "";

      if (!sourceEvent) return info;

      /* handle trigger expression */

      const CExpression* pExpression;

      pExpression = sourceEvent->getTriggerExpressionPtr();

      if (pExpression != NULL)
        {
          trigger = pExpression->getInfix().c_str();
          infix = copyExpression(pExpression);

          if (trigger != infix)
            {
              trigger = infix;

              std::ostringstream newname;
              newname << sourceEvent->getObjectName() << "_" << count;

              newEvent = mpModel->createEvent(testName(newname.str()));
              newEvent->setTriggerExpression(trigger);
            }
        }

      /* handle  delay expression */

      pExpression = sourceEvent->getDelayExpressionPtr();

      if (sourceEvent->getDelayAssignment() &&  pExpression != NULL)
        {
          delay = pExpression->getInfix().c_str();
          infix = copyExpression(pExpression);

          if (delay != infix)
            {
              delay = infix;

              if (newEvent == NULL)
                {
                  std::ostringstream newname;
                  newname << sourceEvent->getObjectName() << "_" << count;

                  newEvent = mpModel->createEvent(testName(newname.str()));
                  newEvent->setTriggerExpression(trigger);
                }
            }

          if (newEvent != NULL)
            {
              newEvent->setDelayAssignment(sourceEvent->getDelayAssignment());
              newEvent->setDelayExpression(delay);
            }
        }

      /* handle event  assignments */

      CEvent * tmpEvent;

      tmpEvent = mpModel->createEvent(sourceEvent->getObjectName() + "tmp");

      bool identic = true;

      unsigned C_INT32 j, jmax = sourceEvent->getAssignments().size();

      for (j = 0; j < jmax; ++j)
        {
          const CEventAssignment* sourceAssignment = sourceEvent->getAssignments()[j];

          std::string key = sourceAssignment->getTargetKey();

          CEventAssignment* tmpAssignment = new CEventAssignment;

          tmpEvent->getAssignments().add(tmpAssignment);

          if (ci.keyMap[key] == "")  tmpAssignment->setTargetKey(key);
          else
            {
              tmpAssignment->setTargetKey(ci.keyMap[key]);
              identic = false;
            }

          pExpression = sourceAssignment->getExpressionPtr();

          if (pExpression != NULL)
            {
              assignment = pExpression->getInfix().c_str();
              infix = copyExpression(pExpression);

              if (assignment != infix)
                {
                  tmpAssignment->setExpression(infix);
                  identic = false;
                }
              else
                tmpAssignment->setExpression(assignment);
            }
        }

      if (newEvent == NULL && !identic)
        {
          std::ostringstream newname;
          newname << sourceEvent->getObjectName() << "_" << count;
          newEvent = mpModel->createEvent(testName(newname.str()));
          newEvent->setTriggerExpression(trigger);
          newEvent->setDelayExpression(delay);
          newEvent->setDelayAssignment(sourceEvent->getDelayAssignment());
        }

      if (newEvent != NULL)

        for (j = 0; j < jmax; ++j)
          {
            const CEventAssignment* tmpAssignment = tmpEvent->getAssignments()[j];

            CEventAssignment* newAssignment = new CEventAssignment;

            newEvent->getAssignments().add(newAssignment, true);

            newAssignment->setTargetKey(tmpAssignment->getTargetKey());

            pExpression = tmpAssignment->getExpressionPtr();

            if (pExpression != NULL)
              newAssignment->setExpression(pExpression->getInfix().c_str());
          }

      mpModel->removeEvent(tmpEvent, true);
    }

  return true;
}
