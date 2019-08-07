// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "CModelMerging.h"
#include "CModel.h"
#include "copasi/function/CExpression.h"
#include "copasi/core/CDataObject.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CEvent.h"
#include "copasi/model/CChemEqElement.h"

CModelAdd::CModelAdd(CModel* pModel, CModel* mModel)
  : mpModel(pModel), mmModel(mModel)
{
}

void CModelAdd::setModel(CModel* pModel, CModel* mModel)
{
  mpModel = pModel;
  mmModel = mModel;
}

void CModelAdd::simpleCall()
{
  if (!mpModel)
    {
      fatalError();
    }

  if (!mmModel)
    {
      fatalError();
    }

  keyMap[mmModel->getKey()] = mpModel->getKey();

  std::string name = "model_2"; // temporary we do not take care about naming conflicts.
  // : "model_2" is the appendix for the names  of compartments and reactions,
  // comming form the second model

  bool  progress  =      addCompartments(name)
                         &&  addMetabolites(name)
                         &&  addModelValues(name)
                         &&  addCompartmentsExpressions()
                         &&  addMetabolitesExpressions()
                         &&  addModelValuesExpressions()
                         &&  addReactions(name)
                         &&  addEvents(name);

  if (!progress)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCModelMerging + 1);
      return;
    }

  mpModel->compileIfNecessary(NULL);
}

bool CModelAdd::addEvents(std::string name)
{

  bool info = false;

  size_t i, imax = mmModel->getEvents().size();

  for (i = 0; i < imax; ++i)
    {
      const CEvent* sourceEvent = &mmModel->getEvents()[i];

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

      if (newEvent == NULL) return info;

      /* copy trigger expression */

      if (sourceEvent->getTriggerExpressionPtr() != NULL)
        {
          if (!copyTriggerExpression(sourceEvent, newEvent))
            return info;
        }
      else
        {
          return info;
        }

      /* set whether the calculation or the assignment shall be delayed */

      newEvent->setDelayAssignment(sourceEvent->getDelayAssignment());

      /* copy the delay expression */

      if (sourceEvent->getDelayExpressionPtr() != NULL)
        if (!copyDelayExpression(sourceEvent, newEvent)) return info;

      /* copy the assignments */

      size_t j, jmax = sourceEvent->getAssignments().size();

      for (j = 0; j < jmax; ++j)
        {
          const CEventAssignment* sourceAssignment = &sourceEvent->getAssignments()[j];

          if (!sourceAssignment) return info;

          std::string key = sourceAssignment->getTargetKey();

          CEventAssignment* newAssignment = new CEventAssignment;

          newEvent->getAssignments().add(newAssignment, true);

          newAssignment->setTargetKey(keyMap[key]);

          if (sourceAssignment->getExpressionPtr() != NULL)
            {
              if (!copyEventAssignmentExpression(sourceAssignment, newAssignment))
                return info;
            }
          else
            {
              return info;
            }
        }
    }

  return true;
}
bool CModelAdd::copyEventAssignmentExpression(const CEventAssignment * sourceAssignment, CEventAssignment * newAssignment)
{

  bool info = false;

  const CExpression* pExpression = sourceAssignment->getExpressionPtr();

  if (pExpression == NULL) return info;

  CExpression* tmp;
  tmp = new CExpression(*pExpression, mmModel);

  const std::vector<CEvaluationNode*>& objectNodes = tmp->getNodeList();
  size_t j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (objectNodes[j]->mainType() == CEvaluationNode::MainType::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);

          if (pObjectNode == NULL) return info;

          CCommonName cn = pObjectNode->getObjectCN();

          const CDataObject* mObject =
            static_cast< const CDataObject * >(mmModel->getObjectDataModel()->getObject(cn));

          if (mObject == NULL) return info;

          std::string host = "";

          if (mObject->hasFlag(CDataObject::Reference))
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          if (mObject == NULL) return info;

          std::string key = keyMap[(dynamic_cast<const CModelEntity * >(mObject))->getKey()];
          CDataObject*  pObject = (CRootContainer::getKeyFactory()->get(key));

          cn = pObject->getCN() + host;

          pObjectNode->setData("<" + cn + ">");
        }
    }

  tmp->updateTree();

  newAssignment->setExpression(tmp->getInfix().c_str());

  return true;
}

bool CModelAdd::copyDelayExpression(const CEvent * sourceEvent, CEvent * newEvent)
{

  bool info = false;

  const CExpression* pExpression = sourceEvent->getDelayExpressionPtr();

  if (pExpression == NULL) return info;

  CExpression* tmp;
  tmp = new CExpression(*pExpression, mmModel);

  const std::vector<CEvaluationNode*>& objectNodes = tmp->getNodeList();
  size_t j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (objectNodes[j]->mainType() == CEvaluationNode::MainType::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);

          if (pObjectNode == NULL) return info;

          CCommonName cn = pObjectNode->getObjectCN();

          const CDataObject* mObject =
            static_cast< const CDataObject * >(mmModel->getObjectDataModel()->getObject(cn));

          if (mObject == NULL) return info;

          std::string host = "";

          if (mObject->hasFlag(CDataObject::Reference))
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          if (mObject == NULL) return info;

          std::string key = keyMap[(dynamic_cast<const CModelEntity * >(mObject))->getKey()];
          CDataObject*  pObject = (CRootContainer::getKeyFactory()->get(key));

          cn = pObject->getCN() + host;

          pObjectNode->setData("<" + cn + ">");
        }
    }

  tmp->updateTree();

  newEvent->setDelayExpression(tmp->getInfix().c_str());

  return true;
}

bool CModelAdd::copyTriggerExpression(const CEvent * sourceEvent, CEvent * newEvent)
{

  bool info = false;

  const CExpression* pExpression = sourceEvent->getTriggerExpressionPtr();

  if (pExpression == NULL) return info;

  CExpression* tmp;
  tmp = new CExpression(*pExpression, mmModel);

  const std::vector<CEvaluationNode*>& objectNodes = tmp->getNodeList();
  size_t j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (objectNodes[j]->mainType() == CEvaluationNode::MainType::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);

          if (pObjectNode == NULL) return info;

          CCommonName cn = pObjectNode->getObjectCN();

          const CDataObject* mObject =
            static_cast< const CDataObject * >(mmModel->getObjectDataModel()->getObject(cn));

          if (mObject == NULL) return info;

          std::string host = "";

          if (mObject->hasFlag(CDataObject::Reference))
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          if (mObject == NULL) return info;

          std::string key = keyMap[(dynamic_cast<const CModelEntity * >(mObject))->getKey()];
          CDataObject*  pObject = (CRootContainer::getKeyFactory()->get(key));

          cn = pObject->getCN() + host;

          pObjectNode->setData("<" + cn + ">");
        }
    }

  tmp->updateTree();

  newEvent->setTriggerExpression(tmp->getInfix().c_str());

  return true;
}

bool CModelAdd::copyExpression(const CModelEntity * sourceEntity, CModelEntity * newEntity)
{

  bool info = false;

  const CExpression* pExpression = sourceEntity->getExpressionPtr();

  if (pExpression == NULL) return info;

  CExpression* tmp;
  tmp = new CExpression(*pExpression, mmModel);

  const std::vector<CEvaluationNode*>& objectNodes = tmp->getNodeList();
  size_t j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (objectNodes[j]->mainType() == CEvaluationNode::MainType::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);

          if (pObjectNode == NULL) return info;

          CCommonName cn = pObjectNode->getObjectCN();

          const CDataObject* mObject =
            static_cast< const CDataObject * >(mmModel->getObjectDataModel()->getObject(cn));

          if (mObject == NULL) return info;

          std::string host = "";

          if (mObject->hasFlag(CDataObject::Reference))
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          if (mObject == NULL) return info;

          std::string key = keyMap[(dynamic_cast<const CModelEntity * >(mObject))->getKey()];
          CDataObject*  pObject = (CRootContainer::getKeyFactory()->get(key));

          cn = pObject->getCN() + host;

          pObjectNode->setData("<" + cn + ">");
        }
    }

  tmp->updateTree();

  newEntity->setExpression(tmp->getInfix().c_str());

  return true;
}

bool CModelAdd::copyInitialExpression(const CModelEntity * sourceEntity, CModelEntity * newEntity)
{

  bool info = false;

  const CExpression* pExpression = sourceEntity->getInitialExpressionPtr();

  if (pExpression == NULL) return info;

  CExpression* tmp;
  tmp = new CExpression(*pExpression, mmModel);

  const std::vector<CEvaluationNode*>& objectNodes = tmp->getNodeList();
  size_t j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (objectNodes[j]->mainType() == CEvaluationNode::MainType::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);

          if (pObjectNode == NULL) return info;

          CCommonName cn = pObjectNode->getObjectCN();

          const CDataObject* mObject =
            static_cast< const CDataObject * >(mmModel->getObjectDataModel()->getObject(cn));

          if (mObject == NULL) return info;

          std::string host = "";

          if (mObject->hasFlag(CDataObject::Reference))
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          if (mObject == NULL) return info;

          std::string key = keyMap[(dynamic_cast<const CModelEntity * >(mObject))->getKey()];
          CDataObject*  pObject = (CRootContainer::getKeyFactory()->get(key));

          cn = pObject->getCN() + host;

          pObjectNode->setData("<" + cn + ">");
        }
    }

  tmp->updateTree();

  newEntity->setInitialExpression(tmp->getInfix().c_str());

  return info;
}

bool CModelAdd::addCompartments(std::string name)
{

  size_t i, imax = mmModel->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      const CCompartment* sourceComp = &mmModel->getCompartments()[i];

      if (!sourceComp) return false;

      //create new compartment

      std::string newName = sourceComp->getObjectName() + "_" + name;

      CCompartment* newComp = mpModel->createCompartment(newName, sourceComp->getInitialValue());

      if (!newComp) return false;

      newComp->setStatus(sourceComp->getStatus());

      newComp->setDimensionality(sourceComp->getDimensionality());

      keyMap[sourceComp->getKey()] = newComp->getKey();
      nameMap[sourceComp->getObjectName()] = newName;
    }

  return true;
}

bool CModelAdd::addCompartmentsExpressions()
{

  bool info = false;

  size_t i, imax = mmModel->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      const CCompartment* sourceComp = &mmModel->getCompartments()[i];

      if (!sourceComp) return info;

      std::string newKey = keyMap[sourceComp->getKey()];

      CDataObject*  pObject = (CRootContainer::getKeyFactory()->get(newKey));

      CCompartment*  newComp = dynamic_cast< CCompartment * >(pObject);

      if (!newComp) return info;

      switch (newComp ->getStatus())
        {
          case CModelEntity::Status::FIXED:

            break;

          case CModelEntity::Status::ASSIGNMENT:

            if (!copyExpression(sourceComp, newComp)) return info;

            break;

          case CModelEntity::Status::ODE:

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

bool CModelAdd::addMetabolites(std::string name)
{
  bool info = false;

  size_t i, imax = mmModel->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      const CMetab* sourceMetab = &mmModel->getMetabolites()[i];
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

bool CModelAdd::addMetabolitesExpressions()
{
  bool info = false;

  size_t i, imax = mmModel->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      const CMetab* sourceMetab = &mmModel->getMetabolites()[i];

      if (!sourceMetab) return info;

      std::string newKey = keyMap[sourceMetab->getKey()];

      CDataObject*  pObject = (CRootContainer::getKeyFactory()->get(newKey));

      CMetab*  newMetab = dynamic_cast< CMetab * >(pObject);

      if (!newMetab) return info;

      switch (newMetab ->getStatus())
        {
          case CModelEntity::Status::FIXED:

            break;

          case CModelEntity::Status::ASSIGNMENT:

            if (!copyExpression(sourceMetab, newMetab)) return info;

            break;

          case CModelEntity::Status::ODE:

            if (!copyExpression(sourceMetab, newMetab)) return info;

            if (sourceMetab->getInitialExpression() != "")
              if (!copyInitialExpression(sourceMetab, newMetab)) return info;

            break;

          case CModelEntity::Status::REACTIONS:

            break;

          default:

            return info;

            break;
        }
    }

  return true;
}

bool CModelAdd::addModelValues(std::string name)
{
  bool info = false;

  size_t i, imax = mmModel->getModelValues().size();

  for (i = 0; i < imax; ++i)
    {
      const CModelValue* sourceModVal = &mmModel->getModelValues()[i];

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

bool CModelAdd::addModelValuesExpressions()
{
  bool info = false;

  size_t i, imax = mmModel->getModelValues().size();

  for (i = 0; i < imax; ++i)
    {
      const CModelValue* sourceModVal = &mmModel->getModelValues()[i];

      if (!sourceModVal) return info;

      std::string newKey = keyMap[sourceModVal->getKey()];

      CDataObject*  pObject = (CRootContainer::getKeyFactory()->get(newKey));

      CModelValue*  newModVal = dynamic_cast<CModelValue * >(pObject);

      if (!newModVal) return info;

      switch (newModVal ->getStatus())
        {
          case CModelEntity::Status::FIXED:

            break;

          case CModelEntity::Status::ASSIGNMENT:

            if (!copyExpression(sourceModVal, newModVal)) return info;

            break;

          case CModelEntity::Status::ODE:

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

bool CModelAdd::addReactions(std::string name)
{

  bool info = false;

  //create copies of the relevant reactions

  size_t i, imax = mmModel->getReactions().size();

  size_t ic, icmax = mmModel->getCompartments().size();

  for (ic = 0; ic < icmax; ++ic)
    {
      const CCompartment* sourceComp = &mmModel->getCompartments()[ic];

      if (!sourceComp) return info;

      for (i = 0; i < imax; ++i)
        {
          CReaction * sourceReac = &mmModel->getReactions()[i];

          if (reactionInvolvesCompartment(sourceReac, sourceComp))
            {

              std::string newName = sourceReac->getObjectName() + "_" + name;

              CReaction* newReac = mpModel->createReaction(newName);

              if (!newReac) return info;

              //copy the chemical equation. If the involved metabs are among those that
              //were copied with the compartment, replace them. Otherwise keep the original metab
              newReac->setReversible(sourceReac->isReversible());
              std::map<std::string, std::string>::const_iterator mapIt;
              std::string targetKey;
              size_t j, jmax = sourceReac->getChemEq().getSubstrates().size();

              for (j = 0; j < jmax; ++j)
                {
                  const CChemEqElement * sourceElement = &sourceReac->getChemEq().getSubstrates()[j];
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
                  const CChemEqElement * sourceElement = &sourceReac->getChemEq().getProducts()[j];
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
                  const CChemEqElement * sourceElement = &sourceReac->getChemEq().getModifiers()[j];
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
                      case CFunctionParameter::Role::SUBSTRATE:
                      case CFunctionParameter::Role::PRODUCT:
                      case CFunctionParameter::Role::MODIFIER:
                        //translate the metab keys
                      {
                        bool isVector = (newReac->getFunctionParameters()[j]->getType() == CFunctionParameter::DataType::VFLOAT64);

                        //we assume that only SUBSTRATE, PRODUCT, MODIFIER can be vectors
                        if (isVector)
                          newReac->clearParameterMapping(j);

                        size_t k;

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

                      case CFunctionParameter::Role::TIME:
                        //just copy the key
                      {
                        mapIt = keyMap.find(sourceReac->getParameterMappings()[j][0]);

                        if (mapIt == keyMap.end())
                          {
                            targetKey = sourceReac->getParameterMappings()[j][0];
                          }
                        else
                          targetKey = mapIt->second;

                        newReac->setParameterMapping(j, targetKey);
                      }
                      break;

                      case CFunctionParameter::Role::VOLUME:

                        //translate the compartment key if necessary
                        if (sourceReac->getParameterMappings()[j][0] == sourceComp->getKey())
                          newReac->setParameterMapping(j, keyMap[sourceComp->getKey()]);
                        else
                          {
                            mapIt = keyMap.find(sourceReac->getParameterMappings()[j][0]);

                            if (mapIt == keyMap.end())
                              {
                                targetKey = sourceReac->getParameterMappings()[j][0];
                              }
                            else
                              targetKey = mapIt->second;

                            newReac->setParameterMapping(j, targetKey);
                          }

                        //TODO: this needs to be adapted when sets of compartments will be copied
                        break;

                      case CFunctionParameter::Role::PARAMETER:

                        if (sourceReac->isLocalParameter(j))
                          newReac->setParameterValue(newReac->getFunctionParameters()[j]->getObjectName(),
                                                     sourceReac->getParameterValue(newReac->getFunctionParameters()[j]->getObjectName()));
                        else
                          {
                            mapIt = keyMap.find(sourceReac->getParameterMappings()[j][0]);

                            if (mapIt == keyMap.end())
                              {
                                targetKey = sourceReac->getParameterMappings()[j][0];
                              }
                            else
                              targetKey = mapIt->second;

                            newReac->setParameterMapping(j,  targetKey);
                          }

                        break;

                      default:
                        return info;
                        break;
                    }
                }
            }
        }
    }

  return true;
}

//static
bool CModelAdd::reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp)
{
  if (!reac) return false;

  if (!comp) return false;

  size_t i, imax = reac->getChemEq().getSubstrates().size();

  for (i = 0; i < imax; ++i)
    if (reac->getChemEq().getSubstrates()[i].getMetabolite()->getCompartment() == comp)
      return true;

  imax = reac->getChemEq().getProducts().size();

  for (i = 0; i < imax; ++i)
    if (reac->getChemEq().getProducts()[i].getMetabolite()->getCompartment() == comp)
      return true;

  imax = reac->getChemEq().getModifiers().size();

  for (i = 0; i < imax; ++i)
    if (reac->getChemEq().getModifiers()[i].getMetabolite()->getCompartment() == comp)
      return true;

  return false;
}

const std::string CModelMerging::TypeName[] =
{
  "ignore",
  "merge",
  ""
};

CModelMerging::CModelMerging(CModel* pModel)
  : mpModel(pModel)
{
}

void CModelMerging::setModel(CModel* pModel)
{
  mpModel = pModel;
}

void  CModelMerging::simpleCall(std::vector< std::string > & /* toKey */, std::vector< std::string > & objectKey)
{
  if (!mpModel)
    {
      fatalError();
    }

  size_t i, j, imax = mpModel->getMetabolites().size();

  CMetab * metab;
  CMetab * metab1;
  CMetab* tmp;
  std::string empty = "";

  for (i = 0; i < imax; ++i)
    {
      metab = &mpModel->getMetabolites()[i];

      for (j = 0; j < imax; ++j)
        {
          if (objectKey[i] != "")
            {
              tmp = &mpModel->getMetabolites()[j];

              if (tmp->getKey() == objectKey[i])
                {
                  metab1 = tmp;
                }
            }
        }

      if (! mergeMetabolites(metab->getKey(), objectKey[i]))
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCModelMerging + 2,
                         metab1->getObjectName().c_str(), metab->getObjectName().c_str());
          return;
        }
    }

  for (i = 0; i < imax; ++i)
    {
      if (objectKey[i] != empty) mpModel->removeMetabolite(objectKey[i] , false);
    }

  mpModel->compileIfNecessary(NULL);
}

bool CModelMerging::mergeMetabolites(std::string toKey, std::string  key)
{

  bool info = false;

  //merge in  the relevant reactions

  size_t i, imax = mpModel->getReactions().size();
  size_t j, jmax;

  for (i = 0; i < imax; ++i)
    {
      CReaction * reac = &mpModel->getReactions()[i];

      jmax = reac->getChemEq().getSubstrates().size();

      for (j = 0; j < jmax; ++j)
        {
          CChemEqElement * subst = const_cast< CChemEqElement * >(&reac->getChemEq().getSubstrates()[j]);

          if (subst->getMetabolite()->getKey() == key)
            subst->setMetabolite(toKey);
        }

      jmax = reac->getChemEq().getProducts().size();

      for (j = 0; j < jmax; ++j)
        {
          CChemEqElement * prod = const_cast< CChemEqElement * >(&reac->getChemEq().getProducts()[j]);

          if (prod->getMetabolite()->getKey() == key)
            prod->setMetabolite(toKey);
        }

      jmax = reac->getChemEq().getModifiers().size();

      for (j = 0; j < jmax; ++j)
        {
          CChemEqElement * modif = const_cast< CChemEqElement * >(&reac->getChemEq().getModifiers()[j]);

          if (modif->getMetabolite()->getKey() == key)
            modif->setMetabolite(toKey);
        }

      //change parameters of  the kinetic function

      for (j = 0; j < reac->getFunctionParameters().size(); ++j)
        {
          switch (reac->getFunctionParameters()[j]->getUsage())
            {
              case CFunctionParameter::Role::SUBSTRATE:
              case CFunctionParameter::Role::PRODUCT:
              case CFunctionParameter::Role::MODIFIER:
                //translate the metab keys
              {

                //we assume that only SUBSTRATE, PRODUCT, MODIFIER can be vectors

                size_t k, kmax = reac->getParameterMappings()[j].size();

                for (k = 0; k < kmax; ++k)
                  if (reac->getParameterMappings()[j][k] == key)
                    reac->getParameterMappings()[j][k] = toKey;
              }
              break;

              case CFunctionParameter::Role::TIME:
                break;

              case CFunctionParameter::Role::VOLUME:
                // ??? TODO : have to ask
                break;

              case CFunctionParameter::Role::PARAMETER:
                break;

              default:
                return info;
                break;
            }
        }
    }

  imax = mpModel->getEvents().size();

  for (i = 0; i < imax; ++i)
    {
      CEvent * event = &mpModel->getEvents()[i];

      if (!event) return info;

      /* merge in  trigger expressions */
      CExpression* pExpression = event->getTriggerExpressionPtr();

      if (pExpression == NULL) return info;

      if (!mergeInExpression(toKey, key, pExpression))  return info;

      pExpression = event->getDelayExpressionPtr();

      if (pExpression)
        if (!mergeInExpression(toKey, key, pExpression))
          return info;

      jmax = event->getAssignments().size();

      for (j = 0; j < jmax; ++j)
        {
          CEventAssignment* assignment = &event->getAssignments()[j];

          if (!assignment) return info;

          std::string assignmentKey = assignment->getTargetKey();

          if (assignmentKey == key) assignment->setTargetKey(toKey);

          pExpression = assignment->getExpressionPtr();

          if (pExpression == NULL) return info;

          if (!mergeInExpression(toKey, key, pExpression))    return info;
        }
    }

  imax = mpModel->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      CMetab* metab = &mpModel->getMetabolites()[i];

      if (!metab) return info;

      switch (metab->getStatus())
        {
          case CModelEntity::Status::FIXED:
          case CModelEntity::Status::REACTIONS:

            break;

          case CModelEntity::Status::ASSIGNMENT:

            if (!mergeInExpression(toKey, key, metab->getExpressionPtr())) return info;

            break;

          case CModelEntity::Status::ODE:

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
      CCompartment* comp = &mpModel->getCompartments()[i];

      if (!comp) return info;

      switch (comp ->getStatus())
        {
          case CModelEntity::Status::FIXED:

            break;

          case CModelEntity::Status::ASSIGNMENT:

            if (!mergeInExpression(toKey, key, comp->getExpressionPtr())) return info;

            break;

          case CModelEntity::Status::ODE:

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
      CModelValue* modval = &mpModel->getModelValues()[i];

      if (!modval) return info;

      switch (modval ->getStatus())
        {
          case CModelEntity::Status::FIXED:

            break;

          case CModelEntity::Status::ASSIGNMENT:

            if (!mergeInExpression(toKey, key, modval->getExpressionPtr())) return info;

            break;

          case CModelEntity::Status::ODE:

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

  bool info = false;

  if (pExpression == NULL) return info;

  const std::vector<CEvaluationNode*>& objectNodes = pExpression->getNodeList();
  size_t j, jmax = objectNodes.size();

  for (j = 0; j < jmax; ++j)
    {
      if (objectNodes[j]->mainType() == CEvaluationNode::MainType::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);

          if (pObjectNode == NULL) return info;

          CCommonName cn = pObjectNode->getObjectCN();

          const CDataObject* mObject =
            static_cast< const CDataObject * >(mpModel->getObjectDataModel()->getObject(cn));

          if (mObject == NULL) return info;

          std::string host = "";

          if (mObject->hasFlag(CDataObject::Reference))
            {
              host = ",Reference=" + mObject->getObjectName();
              mObject = mObject->getObjectParent();
            }

          if (mObject == NULL) return info;

          CDataObject* pObject;

          std::string ikey = (dynamic_cast<const CModelEntity * >(mObject))->getKey();

          if (ikey == key)
            {
              pObject = (CRootContainer::getKeyFactory()->get(toKey));

              cn = pObject->getCN() + host;

              pObjectNode->setData("<" + cn + ">");
            }
        }
    }

  pExpression->updateTree();

  return true;
}
