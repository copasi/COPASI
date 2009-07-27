// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelMerging.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2009/07/27 12:08:22 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CModelMerging.h"

#include "CModel.h"
#include "function/CExpression.h"
#include "report/CCopasiObject.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CEvent.h"
#include "model/CChemEqElement.h"

CModelMerging::CModelMerging(CModel* pModel, CModel* mModel)
    : mpModel(pModel), mmModel(mModel)
{
}

void CModelMerging::setModel(CModel* pModel, CModel* mModel)
{
  mpModel = pModel;
  mmModel = mModel;
}

void CModelMerging::simpleCall()
{
  if (!mpModel) return;

  if (!mmModel) return;

  keyMap[mmModel->getKey()] = mpModel->getKey();
  std::string name = "model_2";

  if (!addCompartments(name)) return; // TODO error message

  if (!addMetabolites(name)) return; // TODO error message

  if (!addModelValues(name)) return; // TODO error message

  if (!addCompartmentsExpressions()) return; // TODO error message

  if (!addMetabolitesExpressions()) return; // TODO error message

  if (!addModelValuesExpressions()) return; // TODO error message

  if (!addReactions(name)) return; // TODO error message

  if (!addEvents(name)) return; // TODO error message

  /* currently : dummy choice of metabolites  to merge */
  unsigned C_INT32 i, imax = mpModel->getMetabolites().size();
  unsigned C_INT32 j, jmax = imax;

  for (i = 0; i < imax; ++i)
    {
      const CMetab* metab = mpModel->getMetabolites()[i];

      std::string metabName = metab->getObjectName();

      for (j = i + 1; j < jmax; ++j)
        {
          CMetab*  metab1 = mpModel->getMetabolites()[j];

          if (metab1->getObjectName() == metabName)
            {

              std::string toKey = metab->getKey();
              std::string key = metab1->getKey();

              if (!mergeMetabolites(toKey, key)) return;

              /* currently,  before we do not delete metabolites from the model */
              metab1->setStatus(CModelEntity::FIXED);
              metab1->setInitialConcentration(0);

              //  else
              //   pdelete(metab1);
            }
        }
    }

  mpModel->compileIfNecessary(NULL);
}
bool CModelMerging::mergeMetabolites(std::string toKey, std::string  key)
{

  bool info;

  if (!mpModel) return info;

  //merge in  the relevant reactions

  unsigned C_INT32 i, imax = mpModel->getReactions().size();
  unsigned C_INT32 j, jmax;

  for (i = 0; i < imax; ++i)
    {
      CReaction * reac = mpModel->getReactions()[i];

      jmax = reac->getChemEq().getSubstrates().size();

      for (j = 0; j < jmax; ++j)
        {
          CChemEqElement * subst = reac->getChemEq().getSubstrates()[j];

          if (subst->getMetabolite()->getKey() == key)
            subst->setMetabolite(toKey);
        }

      jmax = reac->getChemEq().getProducts().size();

      for (j = 0; j < jmax; ++j)
        {
          CChemEqElement * prod = reac->getChemEq().getProducts()[j];

          if (prod->getMetabolite()->getKey() == key)
            prod->setMetabolite(toKey);
        }

      jmax = reac->getChemEq().getModifiers().size();

      for (j = 0; j < jmax; ++j)
        {
          CChemEqElement * modif = reac->getChemEq().getModifiers()[j];

          if (modif->getMetabolite()->getKey() == key)
            modif->setMetabolite(toKey);
        }

      //change parameters of  the kinetic function

      for (j = 0; j < reac->getFunctionParameters().size(); ++j)
        {
          switch (reac->getFunctionParameters()[j]->getUsage())
            {
              case CFunctionParameter::SUBSTRATE:
              case CFunctionParameter::PRODUCT:
              case CFunctionParameter::MODIFIER:
                //translate the metab keys
              {

                //we assume that only SUBSTRATE, PRODUCT, MODIFIER can be vectors

                unsigned C_INT32 k, kmax = reac->getParameterMappings()[j].size();

                for (k = 0; k < kmax; ++k)
                  if (reac->getParameterMappings()[j][k] == key)
                    reac->getParameterMappings()[j][k] = toKey;
              }
              break;

              case CFunctionParameter::TIME:
                break;

              case CFunctionParameter::VOLUME:
                // TODO : have to ask
                break;

              case CFunctionParameter::PARAMETER:
                break;

              default:
                //TODO: error handling
                break;
            }
        }
    }

  imax = mpModel->getEvents().size();

  for (i = 0; i < imax; ++i)
    {
      CEvent* event = mpModel->getEvents()[i];

      if (!event) return info;

      /* merge in  trigger expressions */
      CExpression* pExpression = event->getTriggerExpressionPtr();

      if (pExpression)
        {
          if (!mergeInExpression(toKey, key, pExpression))
            return info;
        }
      else
        {
          fatalError();
        }

      pExpression = event->getDelayExpressionPtr();

      if (pExpression)
        if (!mergeInExpression(toKey, key, pExpression))
          return info;

      jmax = event->getAssignments().size();

      for (j = 0; j < jmax; ++j)
        {
          CEventAssignment* assignment = event->getAssignments()[j];

          if (!assignment) return info;

          std::string assignmentKey = assignment->getTargetKey();

          if (assignmentKey == key) assignment->setTargetKey(toKey);

          pExpression = assignment->getExpressionPtr();

          if (pExpression)
            {
              if (!mergeInExpression(toKey, key, pExpression))

                return info;
            }
          else
            {
              fatalError();
            }
        }
    }

  imax = mpModel->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      CMetab* metab = mpModel->getMetabolites()[i];

      if (!metab) return info;

      switch (metab->getStatus())
        {
          case CModelEntity::FIXED:
          case CModelEntity::REACTIONS:

            break;
          case CModelEntity::ASSIGNMENT:

            if (!mergeInExpression(toKey, key, metab->getExpressionPtr())) return info;

            break;

          case CModelEntity::ODE:

            if (!mergeInExpression(toKey, key, metab->getExpressionPtr())) return info;

            if (metab->getInitialExpression() != "")
              if (!mergeInExpression(toKey, key, metab->getInitialExpressionPtr())) return info;

            break;

          default:

            return info;

            break;
        }
    }

  imax = mpModel->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      CCompartment* comp = mpModel->getCompartments()[i];

      if (!comp) return info;

      switch (comp ->getStatus())
        {
          case CModelEntity::FIXED:

            break;
          case CModelEntity::ASSIGNMENT:

            if (!mergeInExpression(toKey, key, comp->getExpressionPtr())) return info;

            break;

          case CModelEntity::ODE:

            if (!mergeInExpression(toKey, key, comp->getExpressionPtr())) return info;

            if (comp->getInitialExpression() != "")
              if (!mergeInExpression(toKey, key, comp->getInitialExpressionPtr())) return info;

            break;

          default:

            return info;

            break;
        }
    }

  imax = mpModel->getModelValues().size();

  for (i = 0; i < imax; ++i)
    {
      CModelValue* modval = mpModel->getModelValues()[i];

      if (!modval) return info;

      switch (modval ->getStatus())
        {
          case CModelEntity::FIXED:

            break;
          case CModelEntity::ASSIGNMENT:

            if (!mergeInExpression(toKey, key, modval->getExpressionPtr())) return info;

            break;

          case CModelEntity::ODE:

            if (!mergeInExpression(toKey, key, modval->getExpressionPtr())) return info;

            if (modval->getInitialExpression() != "")
              if (!mergeInExpression(toKey, key, modval->getInitialExpressionPtr())) return info;

            break;

          default:

            return info;

            break;
        }
    }

  return true;
}

bool CModelMerging::mergeInExpression(std::string toKey, std::string key, CExpression *pExpression)
{

  bool info;

  assert(pExpression);

  //std::cout << pExpression->getRoot()->getDisplayString(pExpression).c_str() << std::endl;

  const std::vector<CEvaluationNode*>& objectNodes = pExpression->getNodeList();
  unsigned j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (CEvaluationNode::type(objectNodes[j]->getType()) == CEvaluationNode::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);
          assert(pObjectNode);
          CCopasiObjectName cn = pObjectNode->getObjectCN();

          //std::cout << cn << std::endl;

          const CCopasiObject* mObject = mpModel->getObjectDataModel()->getObject(cn);
          assert(mObject);
          std::string host = "";

          if (mObject->isReference())
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
              //std::cout << host << std::endl;
            }

          assert(mObject);

          CCopasiObject* pObject;

          std::string ikey = (dynamic_cast<const CModelEntity * >(mObject))->getKey();

          if (ikey == key)
            {
              pObject = (CCopasiRootContainer::getKeyFactory()->get(toKey));

              cn = pObject->getCN() + host;

              //std::cout << cn << std::endl;

              pObjectNode->setData("<" + cn + ">");
            }
        }
    }

  pExpression->updateTree();

  //std::cout << pExpression->getRoot()->getDisplayString(pExpression).c_str() << std::endl;
  //std::cout <<  std::endl;

  return true;
}

bool CModelMerging::addEvents(std::string name)
{

  bool info;

  if (!mpModel) return info;

  if (!mmModel) return info;

  unsigned C_INT32 i, imax = mmModel->getEvents().size();

  for (i = 0; i < imax; ++i)
    {
      const CEvent* sourceEvent = mmModel->getEvents()[i];

      if (!sourceEvent) return info;

      //create new event

      std::string eventName;

      eventName = sourceEvent->getObjectName();

      std::string appendix = "";
#if 0
      unsigned int counter = 2;
      std::ostringstream numberStream;

      while (mpModel->getEvents().getIndex(eventName + appendix) != C_INVALID_INDEX)
        {
          numberStream.str("");
          numberStream << "_" << counter;
          counter++;
          appendix = numberStream.str();
        }

#else
      appendix = "_" + name;
#endif

      CEvent* newEvent = mpModel->createEvent(eventName + appendix);
      assert(newEvent != NULL);

      /* copy trigger expression */

      if (sourceEvent->getTriggerExpressionPtr() != NULL)
        {
          if (!copyTriggerExpression(sourceEvent, newEvent))
            return info;
        }
      else
        {
          fatalError();
        }

      /* set whether the calculation or the assignment shall be delayed */

      newEvent->setDelayAssignment(sourceEvent->getDelayAssignment());

      /* copy the delay expression */

      if (sourceEvent->getDelayExpressionPtr() != NULL)
        if (!copyDelayExpression(sourceEvent, newEvent)) return info;

      /* copy the assignments */

      unsigned C_INT32 j, jmax = sourceEvent->getAssignments().size();

      for (j = 0; j < jmax; ++j)
        {
          const CEventAssignment* sourceAssignment = sourceEvent->getAssignments()[j];

          if (!sourceAssignment) return info;

          std::string key = sourceAssignment->getTargetKey();

          CEventAssignment* newAssignment = new CEventAssignment;

          newEvent->getAssignments().add(newAssignment);

          newAssignment->setTargetKey(keyMap[key]);

          if (sourceAssignment->getExpressionPtr() != NULL)
            {
              if (!copyEventAssignmentExpression(sourceAssignment, newAssignment))
                return info;
            }
          else
            {
              fatalError();
            }
        }
    }

  return true;
}
bool CModelMerging::copyEventAssignmentExpression(const CEventAssignment * sourceAssignment, CEventAssignment * newAssignment)
{

  bool info;

  const CExpression* pExpression = sourceAssignment->getExpressionPtr();
  assert(pExpression);

  CExpression* tmp;
  tmp = new CExpression(*pExpression, mmModel);

  //std::cout << tmp->getRoot()->getDisplayString(tmp).c_str() << std::endl;

  const std::vector<CEvaluationNode*>& objectNodes = tmp->getNodeList();
  unsigned j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (CEvaluationNode::type(objectNodes[j]->getType()) == CEvaluationNode::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);
          assert(pObjectNode);
          CCopasiObjectName cn = pObjectNode->getObjectCN();

          //std::cout << cn << std::endl;

          const CCopasiObject* mObject = mmModel->getObjectDataModel()->getObject(cn);
          assert(mObject);
          std::string host = "";

          if (mObject->isReference())
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          assert(mObject);

          std::string key = keyMap[(dynamic_cast<const CModelEntity * >(mObject))->getKey()];
          CCopasiObject*  pObject = (CCopasiRootContainer::getKeyFactory()->get(key));

          cn = pObject->getCN() + host;

          //std::cout << cn << std::endl;

          pObjectNode->setData("<" + cn + ">");
        }
    }

  tmp->updateTree();

  //std::cout << tmp->getRoot()->getDisplayString(tmp).c_str() << std::endl;
  //std::cout <<  std::endl;

  newAssignment->setExpression(tmp->getInfix().c_str());

  return true;
}

bool CModelMerging::copyDelayExpression(const CEvent * sourceEvent, CEvent * newEvent)
{

  bool info;

  const CExpression* pExpression = sourceEvent->getDelayExpressionPtr();
  assert(pExpression);

  CExpression* tmp;
  tmp = new CExpression(*pExpression, mmModel);

  //std::cout << tmp->getRoot()->getDisplayString(tmp).c_str() << std::endl;

  const std::vector<CEvaluationNode*>& objectNodes = tmp->getNodeList();
  unsigned j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (CEvaluationNode::type(objectNodes[j]->getType()) == CEvaluationNode::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);
          assert(pObjectNode);
          CCopasiObjectName cn = pObjectNode->getObjectCN();

          //std::cout << cn << std::endl;

          const CCopasiObject* mObject = mmModel->getObjectDataModel()->getObject(cn);
          assert(mObject);
          std::string host = "";

          if (mObject->isReference())
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          assert(mObject);

          std::string key = keyMap[(dynamic_cast<const CModelEntity * >(mObject))->getKey()];
          CCopasiObject*  pObject = (CCopasiRootContainer::getKeyFactory()->get(key));

          cn = pObject->getCN() + host;

          //std::cout << cn << std::endl;

          pObjectNode->setData("<" + cn + ">");
        }
    }

  tmp->updateTree();

  //std::cout << tmp->getRoot()->getDisplayString(tmp).c_str() << std::endl;
  //std::cout <<  std::endl;

  newEvent->setDelayExpression(tmp->getInfix().c_str());

  return true;
}

bool CModelMerging::copyTriggerExpression(const CEvent * sourceEvent, CEvent * newEvent)
{

  bool info;

  const CExpression* pExpression = sourceEvent->getTriggerExpressionPtr();
  assert(pExpression);

  CExpression* tmp;
  tmp = new CExpression(*pExpression, mmModel);

  //std::cout << tmp->getRoot()->getDisplayString(tmp).c_str() << std::endl;

  const std::vector<CEvaluationNode*>& objectNodes = tmp->getNodeList();
  unsigned j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (CEvaluationNode::type(objectNodes[j]->getType()) == CEvaluationNode::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);
          assert(pObjectNode);
          CCopasiObjectName cn = pObjectNode->getObjectCN();

          //std::cout << cn << std::endl;

          const CCopasiObject* mObject = mmModel->getObjectDataModel()->getObject(cn);
          assert(mObject);
          std::string host = "";

          if (mObject->isReference())
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          assert(mObject);

          std::string key = keyMap[(dynamic_cast<const CModelEntity * >(mObject))->getKey()];
          CCopasiObject*  pObject = (CCopasiRootContainer::getKeyFactory()->get(key));

          cn = pObject->getCN() + host;

          //std::cout << cn << std::endl;

          pObjectNode->setData("<" + cn + ">");
        }
    }

  tmp->updateTree();

  //std::cout << tmp->getRoot()->getDisplayString(tmp).c_str() << std::endl;
  //std::cout <<  std::endl;

  newEvent->setTriggerExpression(tmp->getInfix().c_str());

  return true;
}

bool CModelMerging::copyExpression(const CModelEntity * sourceEntity, CModelEntity * newEntity)
{

  bool info;

  const CExpression* pExpression = sourceEntity->getExpressionPtr();
  assert(pExpression);

  CExpression* tmp;
  tmp = new CExpression(*pExpression, mmModel);

  //std::cout << tmp->getRoot()->getDisplayString(tmp).c_str() << std::endl;

  const std::vector<CEvaluationNode*>& objectNodes = tmp->getNodeList();
  unsigned j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (CEvaluationNode::type(objectNodes[j]->getType()) == CEvaluationNode::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);
          assert(pObjectNode);
          CCopasiObjectName cn = pObjectNode->getObjectCN();

          //std::cout << cn << std::endl;

          const CCopasiObject* mObject = mmModel->getObjectDataModel()->getObject(cn);
          assert(mObject);
          std::string host = "";

          if (mObject->isReference())
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          assert(mObject);

          std::string key = keyMap[(dynamic_cast<const CModelEntity * >(mObject))->getKey()];
          CCopasiObject*  pObject = (CCopasiRootContainer::getKeyFactory()->get(key));

          cn = pObject->getCN() + host;

          //std::cout << cn << std::endl;

          pObjectNode->setData("<" + cn + ">");
        }
    }

  tmp->updateTree();

  //std::cout << tmp->getRoot()->getDisplayString(tmp).c_str() << std::endl;
  //std::cout <<  std::endl;

  newEntity->setExpression(tmp->getInfix().c_str());

  return true;
}

bool CModelMerging::copyInitialExpression(const CModelEntity * sourceEntity, CModelEntity * newEntity)
{

  bool info;

  const CExpression* pExpression = sourceEntity->getInitialExpressionPtr();
  assert(pExpression);

  CExpression* tmp;
  tmp = new CExpression(*pExpression, mmModel);

  //std::cout << tmp->getRoot()->getDisplayString(tmp).c_str() << std::endl;

  const std::vector<CEvaluationNode*>& objectNodes = tmp->getNodeList();
  unsigned j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (CEvaluationNode::type(objectNodes[j]->getType()) == CEvaluationNode::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);
          assert(pObjectNode);
          CCopasiObjectName cn = pObjectNode->getObjectCN();

          //std::cout << cn << std::endl;

          const CCopasiObject* mObject = mmModel->getObjectDataModel()->getObject(cn);
          assert(mObject);
          std::string host = "";

          if (mObject->isReference())
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          assert(mObject);

          std::string key = keyMap[(dynamic_cast<const CModelEntity * >(mObject))->getKey()];
          CCopasiObject*  pObject = (CCopasiRootContainer::getKeyFactory()->get(key));

          cn = pObject->getCN() + host;

          //std::cout << cn << std::endl;

          pObjectNode->setData("<" + cn + ">");
        }
    }

  tmp->updateTree();

  //std::cout << tmp->getRoot()->getDisplayString(tmp).c_str() << std::endl;
  //std::cout <<  std::endl;

  newEntity->setInitialExpression(tmp->getInfix().c_str());

  return true;
}

bool CModelMerging::addCompartments(std::string name)
{
  bool info;

  if (!mpModel) return info;

  if (!mmModel) return info;

  if (!mmModel->getCompartments().size()) return info;

  unsigned C_INT32 i, imax = mmModel->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      const CCompartment* sourceComp = mmModel->getCompartments()[i];

      if (!sourceComp) return info;

      //create new compartment

      std::string newName = sourceComp->getObjectName() + "_" + name;

      CCompartment* newComp = mpModel->createCompartment(newName, sourceComp->getInitialValue());

      if (!newComp) return info;

      newComp->setStatus(sourceComp->getStatus());

      newComp->setDimensionality(sourceComp->getDimensionality());

      keyMap[sourceComp->getKey()] = newComp->getKey();
      nameMap[sourceComp->getObjectName()] = newName;
    }

  return true;
}

bool CModelMerging::addCompartmentsExpressions()
{
  bool info;

  if (!mpModel) return info;

  if (!mmModel) return info;

  if (!mmModel->getCompartments().size()) return info;

  unsigned C_INT32 i, imax = mmModel->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      const CCompartment* sourceComp = mmModel->getCompartments()[i];

      if (!sourceComp) return info;

      std::string newKey = keyMap[sourceComp->getKey()];

      CCopasiObject*  pObject = (CCopasiRootContainer::getKeyFactory()->get(newKey));

      CCompartment*  newComp = dynamic_cast< CCompartment * >(pObject);

      if (!newComp)
        //std::cout << "compartment was  not found ";
        return info;

      switch (newComp ->getStatus())
        {
          case CModelEntity::FIXED:

            break;
          case CModelEntity::ASSIGNMENT:

            if (!copyExpression(sourceComp, newComp)) return info;

            break;

          case CModelEntity::ODE:

            if (!copyExpression(sourceComp, newComp)) return info;

            if (sourceComp->getInitialExpression() != "")
              if (!copyInitialExpression(sourceComp, newComp)) return info;

            break;

          default:

            return info;

            break;
        }
    }

  return true;
}

bool CModelMerging::addMetabolites(std::string name)
{
  bool info;

  if (!mpModel) return info;

  if (!mmModel) return info;

  if (!mmModel->getMetabolites().size()) return info;

  unsigned C_INT32 i, imax = mmModel->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      const CMetab* sourceMetab = mmModel->getMetabolites()[i];
      const CCompartment* sourceComp =  sourceMetab->getCompartment();

      if (!sourceMetab) return info;

      if (!sourceComp) return info;

      //create new metabolite

      std::string newName = sourceMetab->getObjectName() + "_" + name;

      CMetab* newMetab = mpModel->createMetabolite(sourceMetab->getObjectName(), nameMap[sourceComp->getObjectName()], sourceMetab->getInitialConcentration());

      if (!newMetab) return info;

      newMetab->setStatus(sourceMetab->getStatus());

      keyMap[sourceMetab->getKey()] = newMetab->getKey();
      nameMap[sourceMetab->getObjectName()] = newName;
    }

  return true;
}

bool CModelMerging::addMetabolitesExpressions()
{
  bool info;

  if (!mpModel) return info;

  if (!mmModel) return info;

  if (!mmModel->getMetabolites().size()) return info;

  unsigned C_INT32 i, imax = mmModel->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      const CMetab* sourceMetab = mmModel->getMetabolites()[i];

      if (!sourceMetab) return info;

      std::string newKey = keyMap[sourceMetab->getKey()];

      CCopasiObject*  pObject = (CCopasiRootContainer::getKeyFactory()->get(newKey));

      CMetab*  newMetab = dynamic_cast< CMetab * >(pObject);

      if (!newMetab)
        //std::cout << "metabolite was  not found ";
        return info;

      switch (newMetab ->getStatus())
        {
          case CModelEntity::FIXED:

            break;
          case CModelEntity::ASSIGNMENT:

            if (!copyExpression(sourceMetab, newMetab)) return info;

            break;

          case CModelEntity::ODE:

            if (!copyExpression(sourceMetab, newMetab)) return info;

            if (sourceMetab->getInitialExpression() != "")
              if (!copyInitialExpression(sourceMetab, newMetab)) return info;

            break;

          case CModelEntity::REACTIONS:

            break;
          default:

            return info;

            break;
        }
    }

  return true;
}

bool CModelMerging::addModelValues(std::string name)
{
  bool info;

  if (!mpModel) return info;

  if (!mmModel) return info;

  unsigned C_INT32 i, imax = mmModel->getModelValues().size();

  for (i = 0; i < imax; ++i)
    {
      const CModelValue* sourceModVal = mmModel->getModelValues()[i];

      if (!sourceModVal) return info;

      //create new model value

      std::string newName = sourceModVal->getObjectName() + "_" + name;

      CModelValue* newModVal = mpModel->createModelValue(newName, sourceModVal->getInitialValue());

      if (!newModVal) return info;

      newModVal->setStatus(sourceModVal->getStatus());

      keyMap[sourceModVal->getKey()] = newModVal->getKey();
      nameMap[sourceModVal->getObjectName()] = newName;
    }

  return true;
}

bool CModelMerging::addModelValuesExpressions()
{
  bool info;

  if (!mpModel) return info;

  if (!mmModel) return info;

  unsigned C_INT32 i, imax = mmModel->getModelValues().size();

  for (i = 0; i < imax; ++i)
    {
      const CModelValue* sourceModVal = mmModel->getModelValues()[i];

      if (!sourceModVal) return info;

      std::string newKey = keyMap[sourceModVal->getKey()];

      CCopasiObject*  pObject = (CCopasiRootContainer::getKeyFactory()->get(newKey));

      CModelValue*  newModVal = dynamic_cast<CModelValue * >(pObject);

      if (!newModVal)
        //std::cout << "model value was  not found ";
        return info;

      switch (newModVal ->getStatus())
        {
          case CModelEntity::FIXED:

            break;
          case CModelEntity::ASSIGNMENT:

            if (!copyExpression(sourceModVal, newModVal)) return info;

            break;

          case CModelEntity::ODE:

            if (!copyExpression(sourceModVal, newModVal)) return info;

            if (sourceModVal->getInitialExpression() != "")
              if (!copyInitialExpression(sourceModVal, newModVal)) return info;

            break;

          default:

            return info;

            break;
        }
    }

  return true;
}

bool CModelMerging::addReactions(std::string name)
{

  bool info;

  if (!mpModel) return info;

  if (!mmModel) return info;

  //create copies of the relevant reactions

  unsigned C_INT32 i, imax = mmModel->getReactions().size();

  if (!mmModel->getCompartments().size()) return info;

  unsigned C_INT32 ic, icmax = mmModel->getCompartments().size();

  for (ic = 0; ic < icmax; ++ic)
    {
      const CCompartment* sourceComp = mmModel->getCompartments()[ic];

      if (!sourceComp) return info;

      for (i = 0; i < imax; ++i)
        {
          CReaction * sourceReac = mmModel->getReactions()[i];

          if (reactionInvolvesCompartment(sourceReac, sourceComp))
            {

              std::string newName = sourceReac->getObjectName() + "_" + name;

              CReaction* newReac = mpModel->createReaction(newName);

              if (!newReac)
                continue; //should not happen TODO: error handling

              //copy the chemical equation. If the involved metabs are among those that
              //were copied with the compartment, replace them. Otherwise keep the original metab
              newReac->setReversible(sourceReac->isReversible());
              std::map<std::string, std::string>::const_iterator mapIt;
              std::string targetKey;
              unsigned C_INT32 j, jmax = sourceReac->getChemEq().getSubstrates().size();

              for (j = 0; j < jmax; ++j)
                {
                  const CChemEqElement * sourceElement = sourceReac->getChemEq().getSubstrates()[j];
                  //check if the metab is in the map. If yes, translate it, otherwise not.
                  mapIt = keyMap.find(sourceElement->getMetaboliteKey());

                  if (mapIt == keyMap.end())
                    {
                      targetKey = sourceElement->getMetaboliteKey();
                    }
                  else
                    targetKey = mapIt->second;

                  newReac->addSubstrate(targetKey, sourceElement->getMultiplicity());
                }

              jmax = sourceReac->getChemEq().getProducts().size();

              for (j = 0; j < jmax; ++j)
                {
                  const CChemEqElement * sourceElement = sourceReac->getChemEq().getProducts()[j];
                  //check if the metab is in the map. If yes, translate it, otherwise not.
                  mapIt = keyMap.find(sourceElement->getMetaboliteKey());

                  if (mapIt == keyMap.end())
                    {
                      targetKey = sourceElement->getMetaboliteKey();
                    }
                  else
                    targetKey = mapIt->second;

                  newReac->addProduct(targetKey, sourceElement->getMultiplicity());
                }

              jmax = sourceReac->getChemEq().getModifiers().size();

              for (j = 0; j < jmax; ++j)
                {
                  const CChemEqElement * sourceElement = sourceReac->getChemEq().getModifiers()[j];
                  //check if the metab is in the map. If yes, translate it, otherwise not.

                  mapIt = keyMap.find(sourceElement->getMetaboliteKey());

                  if (mapIt == keyMap.end())
                    {
                      targetKey = sourceElement->getMetaboliteKey();
                    }
                  else
                    targetKey = mapIt->second;

                  newReac->addModifier(targetKey);
                }

              //set the kinetic function
              newReac->setFunction(const_cast<CFunction*>(sourceReac->getFunction()));

              //mapping and local parameters
              for (j = 0; j < newReac->getFunctionParameters().size(); ++j)
                {
                  switch (newReac->getFunctionParameters()[j]->getUsage())
                    {
                      case CFunctionParameter::SUBSTRATE:
                      case CFunctionParameter::PRODUCT:
                      case CFunctionParameter::MODIFIER:
                        //translate the metab keys
                      {
                        bool isVector = (newReac->getFunctionParameters()[j]->getType() == CFunctionParameter::VFLOAT64);

                        //we assume that only SUBSTRATE, PRODUCT, MODIFIER can be vectors
                        if (isVector)
                          newReac->clearParameterMapping(j);

                        unsigned C_INT32 k;

                        for (k = 0; k < sourceReac->getParameterMappings()[j].size(); ++k)
                          {
                            mapIt = keyMap.find(sourceReac->getParameterMappings()[j][k]);

                            if (mapIt == keyMap.end())
                              {
                                targetKey = sourceReac->getParameterMappings()[j][k];
                              }
                            else
                              targetKey = mapIt->second;

                            if (isVector)
                              newReac->addParameterMapping(j, targetKey);
                            else
                              newReac->setParameterMapping(j, targetKey);
                          }
                      }
                      break;

                      case CFunctionParameter::TIME:
                        //just copy the key
                        newReac->setParameterMapping(j, sourceReac->getParameterMappings()[j][0]);
                        break;

                      case CFunctionParameter::VOLUME:

                        //translate the compartment key if necessary
                        if (sourceReac->getParameterMappings()[j][0] == sourceComp->getKey())
                          newReac->setParameterMapping(j, keyMap[sourceComp->getKey()]);
                        else
                          newReac->setParameterMapping(j, sourceReac->getParameterMappings()[j][0]);

                        //TODO: this needs to be adapted when sets of compartments will be copied
                        break;

                      case CFunctionParameter::PARAMETER:

                        if (sourceReac->isLocalParameter(j))
                          newReac->setParameterValue(newReac->getFunctionParameters()[j]->getObjectName(),
                                                     sourceReac->getParameterValue(newReac->getFunctionParameters()[j]->getObjectName()));
                        else
                          newReac->setParameterMapping(j, sourceReac->getParameterMappings()[j][0]);

                        break;

                      default:
                        //TODO: error handling
                        break;
                    }
                }
            }
        }
    }

  return true;
}

//static
bool CModelMerging::reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp)
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
