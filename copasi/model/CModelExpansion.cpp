// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelExpansion.cpp,v $
//   $Revision: 1.9.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:04:01 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <locale>

#include "CModelExpansion.h"

#include "CModel.h"
#include "function/CExpression.h"
#include "report/CCopasiObject.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"

CModelExpansion::CModelExpansion(CModel* pModel)
    : mpModel(pModel)
{
  this->initializeNameSets();
}

void CModelExpansion::setModel(CModel* pModel)
{
  mpModel = pModel;
  this->initializeNameSets();
}

void CModelExpansion::simpleCall(const CCompartment * source, std::vector< std::string  > listOfMetabolites,  int  mult, bool diff)
{

  if (!mpModel) return;

  if (!mpModel->getCompartments().size()) return;

  ci.keyMap[mpModel->getKey()] = "";

  size_t i, imax;

  imax = mpModel->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      const CCompartment* sourceComp = mpModel->getCompartments()[i];

      ci.keyMap[sourceComp->getKey()] = "";
      //nameInSet(sourceComp->getObjectName());
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

      //nameInSet(sourceReac->getObjectName());
    }

  imax = mpModel->getModelValues().size();

  for (i = 0; i < imax; ++i)
    {
      const CModelValue* sourceModVal = mpModel->getModelValues()[i];

      ci.keyMap[sourceModVal->getKey()] = "";
      //nameInSet(sourceModVal->getObjectName());

    }

  imax = mpModel->getEvents().size();

  for (i = 0; i < imax; ++i)
    {
      const CEvent* sourceEvent = mpModel->getEvents()[i];

      //nameInSet(sourceEvent->getObjectName());
    }

  bool progress;

  C_INT32 m;

  std::vector< std::vector<std::string> > metabMap;

  if (diff)
    {
      imax = listOfMetabolites.size();
      metabMap.resize(imax);

      for (i = 0; i < imax; ++i)
        {
          metabMap[i].resize(mult + 1);
          metabMap[i][0] = listOfMetabolites[i];
        }
    }

  for (m = 0; m < mult; ++m)
    {
      std::ostringstream newname;
      newname << "copy_" << m;
      name = newname.str();

      std::vector<CModelExpansion::CompartmentInfo> v = copyCompartment(source, 1);
      assert(v.size() == 1);
      ci = v[0];

      progress  =     copyCompartmentsExpressions(source)
                      &&  copyMetabolitesExpressions(source)
                      &&  copyModelValuesExpressions(name)
                      &&  copyEvents(name);

      if (diff)
        for (i = 0; i < imax; ++i)
          metabMap[i][m+1] = ci.keyMap[listOfMetabolites[i]];
    }

  if (diff)
    {
      std::ostringstream k;
      k << "k{diffusion}";

      std::string newparam = testName(k.str(), this->mModelValueNameSet);

      CModelValue* modval = mpModel->createModelValue(newparam, 1.);
      modval->setStatus(CModelValue::FIXED);

      for (m = 0; m < mult; ++m)
        {

          for (i = 0; i < imax; ++i)
            {
              std::ostringstream reacname;
              reacname <<  "diffusion" << m << "_" << i;

              CReaction* reac = mpModel->createReaction(testName(reacname.str(), this->mReactionNameSet));

              if (!reac) continue;

              reac->setReversible(true);

              reac->addSubstrate(metabMap[i][m], 1);
              reac->addProduct(metabMap[i][m+1], 1);
              reac->setFunction("Mass action (reversible)");
              reac->addParameterMapping("substrate", metabMap[i][m]);
              reac->addParameterMapping("product", metabMap[i][m+1]);

              reac->setParameterMapping(0, modval->getKey());
              reac->setParameterMapping(2, modval->getKey());

            }
        }
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

std::string CModelExpansion::testName(const std::string & mname, std::set<std::string>& nameSet)
{
  //std::locale C("C");
  //char ch;

  std::ostringstream newname;

  //size_t name_size = mname.size();
  //size_t i;

  /*
  for (i = 0; i < name_size; i++)
    {
      ch = mname[i];

      if (std::isalpha(ch, C) && std::islower(ch, C))
        tmp << (char) toupper(ch);
      else
        tmp << ch;
    }
  */

  newname << mname;
  std::set<std::string>::const_iterator end = nameSet.end();
  unsigned int index = 1;

  while (nameSet.find(newname.str()) != end)
    {
      newname.str(mname);
      newname << "_" << index;
      ++index;
    }

  nameSet.insert(newname.str());
  return newname.str();
}

void CModelExpansion::nameInSet(const std::string & mname, std::set<std::string>& nameSet)
{
  //std::locale C("C");
  //char ch;

  //std::ostringstream newname, tmp;

  //size_t name_size = mname.size();
  //size_t i;

  //for (i = 0; i < name_size; i++)
  //  {
  //    ch = mname[i];
  //
  //    if (std::isalpha(ch, C) && std::islower(ch, C))
  //      tmp << (char) toupper(ch);
  //    else
  //      tmp << ch;
  //  }

  nameSet.insert(mname);

  return;
}

std::vector<CModelExpansion::CompartmentInfo> CModelExpansion::copyCompartment(const CCompartment* source, unsigned int numCopies)
{
  std::vector<CModelExpansion::CompartmentInfo> ret;

  if (!mpModel || !source || numCopies == 0) return ret;

  unsigned int num = 0;
  // we make a set that contains all reactions that involve the given compartment
  std::set<const CReaction*> relevantReactions;
  size_t i = 0, iMax = this->mpModel->getReactions().size();
  const CReaction* pReact = NULL;

  while (i < iMax)
    {
      pReact = this->mpModel->getReactions()[i];

      if (reactionInvolvesCompartment(pReact, source))
        {
          relevantReactions.insert(pReact);
        }

      ++i;
    }

  while (num < numCopies)
    {
      CompartmentInfo info;
      //create new compartment
      CCompartment* newComp = mpModel->createCompartment(testName(name, this->mCompartmentNameSet), source->getInitialValue());

      if (!newComp)
        {
          ret.clear();
          return ret;
        }

      info.key = newComp->getKey();

      newComp->setDimensionality(source->getDimensionality());

      info.keyMap[source->getKey()] = newComp->getKey();

      //create copies of the metabs
      size_t i, imax = source->getMetabolites().size();

      for (i = 0; i < imax; ++i)
        {
          CMetab* pSourceMetab = source->getMetabolites()[i];
          CMetab* pNewMetab = mpModel->createMetabolite(pSourceMetab->getObjectName(), newComp->getObjectName(), pSourceMetab->getInitialConcentration());

          if (!pNewMetab)
            continue; //TODO error handling, should not happen

          pNewMetab->setStatus(pSourceMetab->getStatus());

          info.keyMap[pSourceMetab->getKey()] = pNewMetab->getKey();
        }

      newComp->setStatus(source->getStatus());

      //create copies of the relevant reactions
      std::set<const CReaction*>::const_iterator reactIt = relevantReactions.begin(), reactEndit = relevantReactions.end();
      imax = mpModel->getReactions().size();

      while (reactIt != reactEndit)
        {
          pReact = *reactIt;

          std::ostringstream newname;
          newname << pReact->getObjectName() <<  "{" << newComp->getObjectName()  << "}";

          CReaction* pNewReac = mpModel->createReaction(testName(newname.str(), this->mReactionNameSet));

          if (!pNewReac)
            {
              ret.clear();
              return ret; //should not happen TODO: error handling
            }

          //copy the chemical equation. If the involved metabs are among those that
          //were copied with the compartment, replace them. Otherwise keep the original metab
          pNewReac->setReversible(pReact->isReversible());
          std::map<std::string, std::string>::const_iterator mapIt;
          std::string targetKey;
          size_t j, jmax = pReact->getChemEq().getSubstrates().size();

          for (j = 0; j < jmax; ++j)
            {
              const CChemEqElement * sourceElement = pReact->getChemEq().getSubstrates()[j];
              //check if the metab is in the map. If yes, translate it, otherwise not.
              mapIt = info.keyMap.find(sourceElement->getMetaboliteKey());

              if (mapIt == info.keyMap.end())
                {
                  targetKey = sourceElement->getMetaboliteKey();
                }
              else
                {
                  targetKey = mapIt->second;
                }

              pNewReac->addSubstrate(targetKey, sourceElement->getMultiplicity());
            }

          jmax = pReact->getChemEq().getProducts().size();

          for (j = 0; j < jmax; ++j)
            {
              const CChemEqElement * sourceElement = pReact->getChemEq().getProducts()[j];
              //check if the metab is in the map. If yes, translate it, otherwise not.
              mapIt = info.keyMap.find(sourceElement->getMetaboliteKey());

              if (mapIt == info.keyMap.end())
                {
                  targetKey = sourceElement->getMetaboliteKey();
                }
              else
                {
                  targetKey = mapIt->second;
                }

              pNewReac->addProduct(targetKey, sourceElement->getMultiplicity());
            }

          jmax = pReact->getChemEq().getModifiers().size();

          for (j = 0; j < jmax; ++j)
            {
              const CChemEqElement * sourceElement = pReact->getChemEq().getModifiers()[j];
              //check if the metab is in the map. If yes, translate it, otherwise not.
              mapIt = info.keyMap.find(sourceElement->getMetaboliteKey());

              if (mapIt == info.keyMap.end())
                {
                  targetKey = sourceElement->getMetaboliteKey();
                }
              else
                {
                  targetKey = mapIt->second;
                }

              pNewReac->addModifier(targetKey);
            }

          //set the kinetic function
          pNewReac->setFunction(const_cast<CFunction*>(pReact->getFunction()));

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
                      {
                        pNewReac->clearParameterMapping(j);
                      }

                    size_t k;

                    for (k = 0; k < pReact->getParameterMappings()[j].size(); ++k)
                      {
                        mapIt = info.keyMap.find(pReact->getParameterMappings()[j][k]);

                        if (mapIt == info.keyMap.end())
                          {
                            targetKey = pReact->getParameterMappings()[j][k];
                          }
                        else
                          {
                            targetKey = mapIt->second;
                          }

                        if (isVector)
                          {
                            pNewReac->addParameterMapping(j, targetKey);
                          }
                        else
                          {
                            pNewReac->setParameterMapping(j, targetKey);
                          }
                      }
                  }
                  break;

                  case CFunctionParameter::TIME:
                    //just copy the key
                    pNewReac->setParameterMapping(j, pReact->getParameterMappings()[j][0]);
                    break;

                  case CFunctionParameter::VOLUME:

                    //translate the compartment key if necessary
                    if (pReact->getParameterMappings()[j][0] == source->getKey())
                      {
                        pNewReac->setParameterMapping(j, newComp->getKey());
                      }
                    else
                      {
                        pNewReac->setParameterMapping(j, pReact->getParameterMappings()[j][0]);
                      }

                    //TODO: this needs to be adapted when sets of compartments will be copied
                    break;

                  case CFunctionParameter::PARAMETER:

                    if (pReact->isLocalParameter(j))
                      {
                        pNewReac->setParameterValue(pNewReac->getFunctionParameters()[j]->getObjectName(),
                                                    pReact->getParameterValue(pNewReac->getFunctionParameters()[j]->getObjectName()));
                      }
                    else
                      {
                        pNewReac->setParameterMapping(j, pReact->getParameterMappings()[j][0]);
                      }

                    break;

                  default:
                    //TODO: error handling
                    break;
                }
            }

          ++reactIt;
        }

      ret.push_back(info);
      ++num;
    }

  return ret;
}

//static
bool CModelExpansion::reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp)
{
  if (!reac) return false;

  if (!comp) return false;

  size_t i, imax = reac->getChemEq().getSubstrates().size();

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

bool CModelExpansion::copyModelValuesExpressions(std::string copyname)
{
  bool info = false;

  size_t i, imax = mpModel->getModelValues().size();

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
              newname << source->getObjectName() << "{" << copyname << "}";

              newModVal = mpModel->createModelValue(testName(newname.str(), this->mModelValueNameSet), source->getInitialValue());
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
                newname << source->getObjectName() << "{" << copyname << "}";

                newModVal = mpModel->createModelValue(testName(newname.str(), this->mModelValueNameSet), source->getInitialValue());
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

  size_t i, imax = source->getMetabolites().size();

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
  size_t j, jmax = objectNodes.size();

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

bool CModelExpansion::copyEvents(std::string copyname)
{

  bool info = false;

  size_t i, imax = mpModel->getEvents().size();

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
              newname << sourceEvent->getObjectName() << "{" << copyname << "}";

              newEvent = mpModel->createEvent(testName(newname.str(), this->mEventNameSet));
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
                  newname << sourceEvent->getObjectName() << "{" << copyname << "}";

                  newEvent = mpModel->createEvent(testName(newname.str(), this->mEventNameSet));
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

      size_t j, jmax = sourceEvent->getAssignments().size();

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
          newname << sourceEvent->getObjectName() << "{" << copyname << "}";
          newEvent = mpModel->createEvent(testName(newname.str(), this->mEventNameSet));
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

void CModelExpansion::initializeNameSets()
{
  this->mCompartmentNameSet.clear();
  this->mReactionNameSet.clear();
  this->mModelValueNameSet.clear();
  this->mEventNameSet.clear();

  if (this->mpModel != NULL)
    {
      size_t i, iMax = this->mpModel->getCompartments().size();

      for (i = 0; i < iMax; ++i)
        {
          this->mCompartmentNameSet.insert(this->mpModel->getCompartments()[i]->getObjectName());
        }

      iMax = this->mpModel->getReactions().size();

      for (i = 0; i < iMax; ++i)
        {
          this->mReactionNameSet.insert(this->mpModel->getReactions()[i]->getObjectName());
        }

      iMax = this->mpModel->getModelValues().size();

      for (i = 0; i < iMax; ++i)
        {
          this->mModelValueNameSet.insert(this->mpModel->getModelValues()[i]->getObjectName());
        }

      iMax = this->mpModel->getEvents().size();

      for (i = 0; i < iMax; ++i)
        {
          this->mEventNameSet.insert(this->mpModel->getEvents()[i]->getObjectName());
        }
    }
}

