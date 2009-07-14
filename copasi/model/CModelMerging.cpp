// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelMerging.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2009/07/14 14:20:57 $
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

  if (!addReactions(name)) return; // TODO error message

  if (!addEvents(name)) return; // TODO error message

  mpModel->compileIfNecessary(NULL);
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

      switch (sourceComp ->getStatus())
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

      newComp->setDimensionality(sourceComp->getDimensionality());

      keyMap[sourceComp->getKey()] = newComp->getKey();
      nameMap[sourceComp->getObjectName()] = newName;
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

      switch (sourceMetab ->getStatus())
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

      keyMap[sourceMetab->getKey()] = newMetab->getKey();
      nameMap[sourceMetab->getObjectName()] = newName;
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

      switch (sourceModVal ->getStatus())
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

      keyMap[sourceModVal->getKey()] = newModVal->getKey();
      nameMap[sourceModVal->getObjectName()] = newName;
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
