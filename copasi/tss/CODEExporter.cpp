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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <locale>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctype.h>

#include "copasi/copasi.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

#include "CODEExporter.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CMetabNameInterface.h"
#include "copasi/core/CDataVector.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CMoiety.h"
#include "copasi/model/CChemEqElement.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CExpression.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeObject.h"
#include "copasi/function/CEvaluationNodeOperator.h"
#include "copasi/function/CEvaluationNodeFunction.h"
#include "copasi/utilities/CCopasiTree.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/commandline/CLocaleString.h"

#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryProblem.h"

/**
 ** Constructor for the exporter.
 */
CODEExporter::CODEExporter()
  : mExportedFunctions()
{}

/**
 ** Destructor for the exporter.
 */
CODEExporter::~CODEExporter()
{}

bool  CODEExporter::exportSingleFunction(const CFunction *func)
{
  return exportSingleFunction(func, mExportedFunctions);
}

void CODEExporter::findFunctionsCalls(const CEvaluationNode* pNode)
{
  if (pNode == NULL) return;

  CFunctionDB* pFunctionDB = CRootContainer::getFunctionList();
  CCopasiTree<CEvaluationNode>::const_iterator treeIt = pNode;

  while (treeIt != NULL)
    {
      if (treeIt->mainType() == CEvaluationNode::MainType::CALL)
        {
          const CFunction* ifunc;
          ifunc = static_cast<CFunction*>(pFunctionDB->findFunction((*treeIt).getData()));

          findFunctionsCalls(ifunc->getRoot());

          if (ifunc->getType() != CEvaluationTree::MassAction)
            {
              if (!exportSingleFunction(ifunc)) return;
            }
        }

      ++treeIt;
    }
}

bool CODEExporter::exportModelValuesExpressions(const CModel *copasiModel)
{
  size_t i, size = copasiModel->getNumModelValues();

  for (i = 0; i < size; ++i)
    {
      const CModelEntity* entity = &copasiModel->getModelValues()[i];

      if (entity->getStatus() == CModelEntity::Status::ASSIGNMENT)
        {
          if (entity->getExpressionPtr() == NULL || entity->getExpressionPtr()->getRoot() == NULL)
            continue;

          findFunctionsCalls(entity->getExpressionPtr()->getRoot());
          exportModelEntityExpression(entity, entity->getObjectDataModel());
        }
    }

  size = copasiModel->getNumMetabs();

  for (i = 0; i < size; ++i)
    {
      const CModelEntity* entity = &copasiModel->getMetabolites()[i];

      if (entity->getStatus() == CModelEntity::Status::ASSIGNMENT)
        {
          if (entity->getExpressionPtr() == NULL || entity->getExpressionPtr()->getRoot() == NULL)
            continue;

          findFunctionsCalls(entity->getExpressionPtr()->getRoot());
          exportModelEntityExpression(entity, entity->getObjectDataModel());
        }
    }

  size = copasiModel->getCompartments().size();

  for (i = 0; i < size; ++i)
    {
      const CModelEntity* entity = &copasiModel->getCompartments()[i];

      if (entity->getStatus() == CModelEntity::Status::ASSIGNMENT)
        {
          if (entity->getExpressionPtr() == NULL || entity->getExpressionPtr()->getRoot() == NULL)
            continue;

          findFunctionsCalls(entity->getExpressionPtr()->getRoot());
          exportModelEntityExpression(entity, entity->getObjectDataModel());
        }
    }

  return true;
}

bool CODEExporter::exportSingleFunction(const CFunction *func, std::set<std::string>& isExported)
{
  return true;
}

bool CODEExporter::exportToStream(const CDataModel* pDataModel, std::ostream & os)
{
  mExportedFunctions.clear();

  /* translate COPASI data names in exporter syntax */
  if (!preprocess(pDataModel->getModel())) return false;

  /* export COPASI data */

  if (!exportMetabolites(pDataModel->getModel())) return false;

  if (!exportCompartments(pDataModel->getModel())) return false;

  if (!exportModelValues(pDataModel->getModel())) return false;

  if (!exportReacParamsAndFuncs(pDataModel->getModel())) return false;

  if (!exportKineticFunctionGroup(pDataModel->getModel())) return false;

  if (!exportODEs(pDataModel->getModel())) return false;

  if (!exportModelValuesExpressions(pDataModel->getModel())) return false;

  exportObjectNodesFromModel(pDataModel);

  if (!exportMetabolitesConcentrations(pDataModel->getModel())) return false;

  // export title data, so that a list of additionally created entities can be exported.
  // NOTE: this does not change the order in the file
  if (!exportTitleData(pDataModel->getModel(), os)) return false;

  os << std::endl << exportTitleString(INITIAL) << std::endl << initial.str() << exportClosingString(INITIAL);
  os << std::endl << exportTitleString(FIXED) << std::endl << fixed.str() << exportClosingString(FIXED);
  os << std::endl << exportTitleString(ASSIGNMENT) << std::endl << assignment.str() << exportClosingString(ASSIGNMENT);
  os << std::endl << exportTitleString(HEADERS) << std::endl << headers.str() << exportClosingString(HEADERS);
  os << std::endl << exportTitleString(FUNCTIONS) << std::endl << functions.str() << exportClosingString(FUNCTIONS);
  os << std::endl << exportTitleString(ODEs) << std::endl << ode.str() << exportClosingString(ODEs);

  if (!exportClosingData(pDataModel->getModel(), os)) return false;

  return true;
}

void CODEExporter::exportObjectNodesFromModel(const CDataModel* pDataModel)
{
  const CCore::CUpdateSequence & Objects = pDataModel->getModel()->getMathContainer().getSimulationValuesSequence(false);
  CCore::CUpdateSequence::const_iterator it = Objects.begin();
  CCore::CUpdateSequence::const_iterator end = Objects.end();

  for (; it != end; ++it)
    {
      const CDataObject * obj = (*it)->getDataObject();

      if (obj) exportSimulatedObject(obj, pDataModel);
    }
}

/*
CDataObject* CODEExporter::findObjectFromRefresh(const CDataObject * tmp, const Refresh* ref)
{

  CDataObject* obj = NULL;

  if (tmp->isContainer())
    {

      CDataContainer* container;
      container = (CDataContainer*)tmp;

      CDataContainer::objectMap::const_iterator it = container->getObjects().begin();

      for (; it != container->getObjects().end(); ++it)
        {

          //skip if the contained object is not owned by this container

          if (it->second->getObjectParent() != container) continue;

          if (it->second->getRefresh() == ref)
            {
              obj = it->second;

              return obj;
            }

          //the next line skips name references...

          if (it->second->getObjectName() == "Name") continue;

          if (it->second->getObjectType() == "Function") continue;

          obj = findObjectFromRefresh(it->second, ref);

          if (obj) return obj;
        }

      return NULL;
    }

  return NULL;
}
 */

void CODEExporter::exportSimulatedObject(const CDataObject * obj, const CDataModel* pDataModel)
{
  if (obj == NULL || pDataModel == NULL)
    return;

  if (obj->hasFlag(CDataObject::Reference))
    {
      CDataObject* parent = obj->getObjectParent();
      assert(parent);
      std::string typeString = parent->getObjectType();
      std::string name = obj->getObjectName();

      if (typeString == "Metabolite" || typeString == "ModelValue" || typeString == "Compartment")
        {
          if (name == "Concentration" || name == "Value"
              || name == "Volume" || name == "Rate"
              || name == "ParticleNumberRate")
            {
              if (!exportModelEntityExpression(obj, pDataModel))
                {
                  return;
                }
              else
                {
                  return;
                }
            }
        }

      //TODO warning for initial assignments
    }

  return;
}

bool CODEExporter::exportModelEntityExpression(const CDataObject * obj, const CDataModel* pDataModel)
{
  if (obj == NULL || pDataModel == NULL)
    return false;

  if (obj->hasFlag(CDataObject::Reference))
    {
      CDataObject* parent = obj->getObjectParent();
      return exportModelEntityExpression(parent, pDataModel);
    }
  else
    {
      std::string typeString = obj->getObjectType();

      const CModelEntity * tmp = dynamic_cast< const CModelEntity * >(obj);

      std::ostringstream comments;
      std::ostringstream expression;

      std::string str1;
      std::string str2;

      comments << "model entity \'" << tmp->getObjectName() << "\':" << CModelEntity::StatusName[tmp->getStatus()];

      if (tmp->getStatus() == CModelEntity::Status::ODE)
        {
          const CExpression* pExpression = tmp->getExpressionPtr();
          assert(pExpression);

          findFunctionsCalls(pExpression->getRoot());

          std::string result;
          result = isModelEntityExpressionODEExporterCompatible(tmp, pExpression, pDataModel);

          if ((isEmptyString(result)))
            {
              expression << exportExpression(pExpression, pDataModel);
            }

          equations[tmp->getKey()] = expression.str();
        }

      switch (tmp->getStatus())
        {
          case CModelEntity::Status::FIXED:
            break;

          case CModelEntity::Status::ASSIGNMENT:
          {

            const CExpression* pExpression = tmp->getExpressionPtr();
            assert(pExpression);

            findFunctionsCalls(pExpression->getRoot());

            std::string result;
            result = isModelEntityExpressionODEExporterCompatible(tmp, pExpression, pDataModel);

            if (!(isEmptyString(result)))
              comments << result;
            else
              {
                expression << exportExpression(pExpression, pDataModel);
              }

            str1 = expression.str();
            str2 = comments.str();

            const CMetab * metab = dynamic_cast< const CMetab * >(tmp);

            if (metab)
              {
                std::ostringstream convert;
                const CCompartment * comp = metab->getCompartment();
                convert << " * " << NameMap[comp->getKey()];
                str1 += convert.str();
              }

            if (!exportSingleModelEntity(tmp, str1, str2)) return false;

            break;
          }

          case CModelEntity::Status::ODE:
          {

            const CExpression* pExpression = tmp->getExpressionPtr();
            assert(pExpression);

            findFunctionsCalls(pExpression->getRoot());

            std::string result;
            result = isModelEntityExpressionODEExporterCompatible(tmp, pExpression, pDataModel);

            if (!(isEmptyString(result)))
              comments << result;

            str1 = equations[tmp->getKey()];
            str2 = comments.str();

            const CMetab* metab = dynamic_cast< const CMetab * >(tmp);

            if (metab)
              {
                std::ostringstream convert;
                const CCompartment * comp = metab->getCompartment();
                convert << " * " << NameMap[comp->getKey()];
                str1 += convert.str();
              }

            if (!exportSingleODE(tmp, str1, str2)) return false;

            break;
          }

          default:
            return false;
            break;
        }
    }

  return true;
}

std::string CODEExporter::getSingleLineComment()
{
  return "";
}

std::string CODEExporter::isModelEntityExpressionODEExporterCompatible(const CModelEntity * tmp, const CExpression* pExpression, const CDataModel* pDataModel)
{

  std::ostringstream result;
  const std::vector<CEvaluationNode*>& objectNodes = pExpression->getNodeList();
  size_t j, jMax = objectNodes.size();
  assert(pDataModel != NULL);

  for (j = 0; j < jMax; ++j)
    {
      if (objectNodes[j]->mainType() == CEvaluationNode::MainType::OBJECT)
        {
          const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(objectNodes[j]);
          assert(pObjectNode);
          CObjectInterface::ContainerList containers;
          containers.push_back(const_cast<CDataModel*>(pDataModel)->getModel());
          const CDataObject* pObject = CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(containers, pObjectNode->getObjectCN()));
          assert(pObject);

          if (pObject->hasFlag(CDataObject::Reference))
            {
              CDataObject* pObjectParent = pObject->getObjectParent();
              assert(pObjectParent);
              std::string typeString = pObjectParent->getObjectType();

              if (typeString == "Compartment")
                {
                  if (pObject->getObjectName() != "Volume"
                      && pObject->getObjectName() != "InitialVolume"
                      && pObject->getObjectName() != "Rate")
                    {
                      result << std::endl << getSingleLineComment() << "WARNING : reference to property other than transient volume for compartment \"" << pObjectParent->getObjectName() << "\" in expression  for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }
                }
              else if (typeString == "Metabolite")
                {

                  if (pObject->getObjectName() != "Concentration"
                      && pObject->getObjectName() != "InitialConcentration"
                      && pObject->getObjectName() != "ParticleNumber"
                      && pObject->getObjectName() != "Rate")
                    {

                      result << std::endl << getSingleLineComment() << "WARNING : reference to property other than transient concentration, initial concentration or concentrations rate for metabolite \"" << pObjectParent->getObjectName() << "\" in expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }

                  CMetab* metab;
                  metab = dynamic_cast< CMetab * >(pObjectParent);

                  if ((metab->getStatus() == CModelEntity::Status::REACTIONS &&  metab->isDependent()) && pObject->getObjectName() == "Rate")
                    {

                      result << std::endl << getSingleLineComment() <<  "WARNING : reference to rate of dependent (defined from moiety)  metabolite \"" << pObjectParent->getObjectName() << "\" in expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }
                }
              else if (typeString == "ModelValue")
                {
                  if (pObject->getObjectName() != "Value"
                      && pObject->getObjectName() != "InitialValue"
                      && pObject->getObjectName() != "Rate")
                    {

                      result << std::endl << getSingleLineComment() << "WARNING : reference to property other than transient value, initial value or rate for \"" << typeString << "\" \"" << pObjectParent->getObjectName() << "\" in expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }
                }
              else if (typeString == "Model")
                {

                  if (pObject->getObjectName() != "Time" && pObject->getObjectName() != "Initial Time" && pObject->getObjectName() != "Avogadro Constant")
                    {

                      result << std::endl << getSingleLineComment() << "WARNING : reference to property other than initial time or transient time for model \"" << pObjectParent->getObjectName() << "\" in expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }
                }
              else if (typeString == "Parameter")
                {

                  if (pObject->getObjectName() != "Value")
                    {

                      result << std::endl << getSingleLineComment() << "WARNING : reference to property other than initial time or transient time for model \"" << pObjectParent->getObjectName() << "\" in expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }
                }
              else if (typeString == "Reaction")
                {
                  if (pObject->getObjectName() != "Flux")
                    {
                      result << std::endl << getSingleLineComment() << "WARNING : reference to property other than Flux for Reaction \"" << pObjectParent->getObjectName() << "\" in expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }
                }
              else
                {
                  result << std::endl << getSingleLineComment() << "WARNING : expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\" contains reference to a value in object \"" << pObjectParent->getObjectName() << "\" of type \"" << typeString << "\" which is not supported in this ODE exporter Version.";
                }
            }
          else
            {
              result << std::endl << getSingleLineComment() << "WARNING : expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\" contains reference to a object named \"" << pObject->getObjectName() << "\" of type \"" << pObject->getObjectType() << "\" which is not supported in this ODE exporter Version.";
            }
        }
    }

  return result.str();
}

size_t getReactionIndex(const CDataVector< CReaction > & reacs, const CReaction *react)
{
  return reacs.getIndex(react);
}

std::string getQuantityParameterOrValue(const std::map< std::string, std::string >& map, const CDataModel* pDataModel)
{
  double val = pDataModel->getModel()->getQuantity2NumberFactor();
  const CDataVectorN< CModelValue >& vals = pDataModel->getModel()->getModelValues();
  CDataVectorN< CModelValue >::const_iterator it = vals.begin();

  for (; it != vals.end(); ++it)
    {
      std::map< std::string, std::string >::const_iterator key = map.find(it->getKey());

      if (it->getInitialValue() == val && key != map.end())
        return key->second;
    }

  std::ostringstream str;
  str << val;
  return str.str();
}

std::string CODEExporter::exportExpression(const CExpression* pExpression, const CDataModel* pDataModel)
{

  std::string result;

  CExpression* tmpExpression;
  tmpExpression = new CExpression(*pExpression, pDataModel);
  assert(pDataModel != NULL);

  const std::vector<CEvaluationNode*>& objectNodes = tmpExpression->getNodeList();
  size_t j, jMax = objectNodes.size();

  for (j = 0; j < jMax; ++j)
    {
      if (objectNodes[j]->mainType() == CEvaluationNode::MainType::CALL)
        {
          CEvaluationNodeCall* pObjectNode = dynamic_cast<CEvaluationNodeCall*>(objectNodes[j]);
          assert(pObjectNode);
          objectNodes[j]->setData(NameMap[pObjectNode->getCalledTree()->getKey()]);
        }
      else if (objectNodes[j]->mainType() == CEvaluationNode::MainType::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);
          assert(pObjectNode);
          CCommonName cn = pObjectNode->getObjectCN();

          const CDataObject* pObject = CObjectInterface::DataObject(pDataModel->getObjectFromCN(cn));

          assert(pObject);
          std::string objectName = pObject->getObjectName();

          if (pObject->hasFlag(CDataObject::Reference)) pObject = pObject->getObjectParent();

          std::string objectType = pObject->getObjectType();

          if (objectType == "Model")
            {
              if (objectName == "Time")
                objectNodes[j]->setData(NameMap[timeKey]);

              if (objectName == "Avogadro Constant")
                {
                  std::ostringstream value;
                  value << pDataModel->getModel()->getQuantity2NumberFactor();
                  objectNodes[j]->setData(value.str());
                }

              if (objectName == "Initial Time")
                {
                  const CTrajectoryTask * pTrajectory =
                    dynamic_cast<CTrajectoryTask *>(&const_cast<CDataModel*>(pDataModel)->getTaskList()->operator[]("Time-Course"));

                  const CTrajectoryProblem * pTrajectoryProblem =
                    dynamic_cast<const CTrajectoryProblem *>(pTrajectory->getProblem());

                  std::ostringstream value;
                  value << pTrajectoryProblem->getOutputStartTime();
                  objectNodes[j]->setData(value.str());
                }
            }
          else if (objectType == "ModelValue")
            {
              if (objectName == "Value") objectNodes[j]->setData(NameMap[pObject->getKey()]);

              if (objectName == "InitialValue")
                {
                  const CModelValue* modval;
                  modval = dynamic_cast<const CModelValue * >(pObject);
                  std::ostringstream value;
                  value << exportNumber(modval->getInitialValue());
                  objectNodes[j]->setData(value.str());
                }

              if (objectName == "Rate")
                {
                  const CModelValue* modval;
                  modval = dynamic_cast<const CModelValue * >(pObject);

                  if (modval->getStatus() == CModelEntity::Status::ODE)
                    {

                      if ((isEmptyString(equations[modval->getKey()])))
                        {
                          std::ostringstream odeKey;
                          odeKey << "ode_" << modval->getKey();
                          objectNodes[j]->setData(NameMap[odeKey.str()]);
                        }
                      else
                        {
                          std::ostringstream str1;
                          str1 << "(" << equations[modval->getKey()] << ")";
                          objectNodes[j]->setData(str1.str());
                        }
                    }
                }
            }
          else if (objectType == "Metabolite")
            {
              if (objectName == "Concentration")
                objectNodes[j]->setData(NameMap[pObject->getKey()]);

              if (objectName == "ParticleNumber")
                {
                  std::ostringstream str;
                  str << NameMap["sm_" + pObject->getKey()] << " * "
                      << getQuantityParameterOrValue(NameMap, pDataModel)
                      << " ";
                  objectNodes[j]->setData(str.str());
                }

              if (objectName == "InitialConcentration")
                {
                  const CMetab* metab;
                  metab = dynamic_cast<const CMetab * >(pObject);
                  std::ostringstream value;
                  value << metab->getInitialConcentration();
                  objectNodes[j]->setData(value.str());
                }

              if (objectName == "Rate")
                {
                  const CMetab* metab;
                  metab = dynamic_cast<const CMetab * >(pObject);

                  if ((metab->getStatus() == CModelEntity::Status::REACTIONS && !metab->isDependent()) || metab->getStatus() == CModelEntity::Status::ODE)
                    {
                      if ((isEmptyString(equations[metab->getKey()])))
                        {
                          std::ostringstream odeKey;
                          odeKey << "ode_" << metab->getKey();
                          objectNodes[j]->setData(NameMap[odeKey.str()]);
                        }
                      else
                        {
                          std::ostringstream str1;
                          str1 << "(" << equations[metab->getKey()] << ")";
                          objectNodes[j]->setData(str1.str());
                        }
                    }
                }
            }
          else if (objectType == "Compartment")
            {
              if (objectName == "Volume")
                objectNodes[j]->setData(NameMap[pObject->getKey()]);

              if (objectName == "InitialVolume")
                {
                  const CCompartment* comp;
                  comp = dynamic_cast<const CCompartment * >(pObject);
                  std::ostringstream value;
                  value << exportNumber(comp-> getInitialValue());
                  objectNodes[j]->setData(value.str());
                }

              if (objectName == "Rate")
                {

                  const CCompartment* comp;
                  comp = dynamic_cast<const CCompartment * >(pObject);

                  if (comp->getStatus() == CModelEntity::Status::ODE)
                    {

                      if ((isEmptyString(equations[comp->getKey()])))
                        {
                          std::ostringstream odeKey;
                          odeKey << "ode_" << comp->getKey();
                          objectNodes[j]->setData(NameMap[odeKey.str()]);
                        }
                      else
                        {
                          std::ostringstream str1;
                          str1 << "(" << equations[comp->getKey()] << ")";
                          objectNodes[j]->setData(str1.str());
                        }
                    }
                }
            }
          else if (objectType == "Parameter")
            {
              if (objectName == "Value")
                objectNodes[j]->setData(NameMap[pObject->getKey()]);
            }
          else if (objectType == "Reaction")
            {
              if (objectName == "Flux")
                {
                  const CModel* copasiModel = pDataModel->getModel();
                  const CReaction *react = static_cast<const CReaction*>(pObject);
                  const CDataVector< CReaction > & reacs = copasiModel->getReactions();

                  size_t index = getReactionIndex(reacs, react);

                  if (index == C_INVALID_INDEX)
                    {
                      objectNodes[j]->setData("0");
                      continue;
                    }

                  const CDataVector< CMetab > & metabs = copasiModel->getMetabolitesX();

                  size_t indep_size = copasiModel->getNumIndependentReactionMetabs();

                  size_t ode_size = copasiModel->getNumODEMetabs();

                  const CMatrix< C_FLOAT64 > & redStoi = copasiModel->getRedStoi();

                  std::ostringstream jequation;

                  for (size_t j1 = 0; j1 < indep_size; ++j1)
                    {
                      if (fabs(redStoi[j1][index]) > 0.0)
                        {
                          jequation << equations[metabs[ode_size + j1].getKey()];
                        }
                    }

                  objectNodes[j]->setData(jequation.str());
                }
            }
        }
    }

  result = getDisplayExpressionString(tmpExpression);

  return result;
}

bool CODEExporter::preprocess(const CModel* copasiModel)
{
  size_t i, j;

  setReservedNames();

  timeKey = "time";

  NameMap[timeKey] = translateTimeVariableName();

  const CDataVector< CMetab > & metabs = copasiModel->getMetabolitesX();
  size_t metabs_size = metabs.size();

  for (i = 0; i < metabs_size; i++)
    {
      const CMetab * metab = &metabs[i];

      //if (metab->isUsed()) //changed
      {

        std::string name = translateObjectName(metab->getObjectName());

        std::ostringstream smKey;
        smKey << "sm_" << metab->getKey();

        NameMap[smKey.str()] = name; // mass fraction

        NameMap[metab->getKey()] = setConcentrationName(name); //concentration

        if ((metab->getStatus() == CModelEntity::Status::REACTIONS && !metab->isDependent()) || metab->getStatus() == CModelEntity::Status::ODE)
          {
            std::ostringstream odeKey;
            odeKey << "ode_" << metab->getKey();
            NameMap[odeKey.str()] = setODEName(name);
          }
      }
    }

  size_t comps_size = copasiModel->getCompartments().size();
  const CDataVector< CCompartment > & comps = copasiModel->getCompartments();

  for (i = 0; i < comps_size; i++)
    {
      const CCompartment* comp = &comps[i];
      std::string name = translateObjectName(comp->getObjectName());
      NameMap[comp->getKey()] = name;

      if (comp->getStatus() == CModelEntity::Status::ODE)
        {
          std::ostringstream odeKey;
          odeKey << "ode_" << comp->getKey();
          NameMap[odeKey.str()] = setODEName(name);
        }
    }

  size_t modvals_size = copasiModel->getModelValues().size();
  const CDataVector< CModelValue > & modvals = copasiModel->getModelValues();

  for (i = 0; i < modvals_size; i++)
    {
      const CModelValue* modval = &modvals[i];
      std::string name = translateObjectName(modval->getObjectName());
      NameMap[modval->getKey()] = name;

      if (modval->getStatus() == CModelEntity::Status::ODE)
        {
          std::ostringstream odeKey;
          odeKey << "ode_" << modval->getKey();
          NameMap[odeKey.str()] = setODEName(name);
        }
    }

  size_t reacs_size = copasiModel->getReactions().size();

  const CDataVector< CReaction > & reacs = copasiModel->getReactions();

  for (i = 0; i < reacs_size; ++i)
    {
      size_t params_size;

      params_size = reacs[i].getParameters().size();

      for (j = 0; j < params_size; ++j)
        {
          const CCopasiParameter * current = reacs[i].getParameters().getParameter(j);

          if (reacs[i].isLocalParameter(current->getObjectName()))
            {
              std::string name = translateObjectName(current->getObjectName());
              NameMap[current->getKey()] = name;

            }
        }
    }

  return true;
}

bool CODEExporter::exportTitleData(const CModel* /* copasiModel */,
                                   std::ostream & /* os */)
{return true;}

std::string CODEExporter::exportNumber(double number)
{
  std::stringstream str; str << number;
  return str.str();
}

/* export metabolites */
bool CODEExporter::exportMetabolites(const CModel* copasiModel)
{

  const CDataVector< CMetab > & metabs = copasiModel->getMetabolitesX();
  const CLinkMatrixView & L = copasiModel->getL();

  size_t metabs_size = metabs.size();
  size_t indep_size = copasiModel->getNumIndependentReactionMetabs();
  size_t ode_size = copasiModel->getNumODEMetabs();
  size_t conservedTotals = 0;
  size_t i, j;
  C_FLOAT64 value;

  for (i = 0; i < metabs_size; i++)
    {
      const CMetab * metab = &metabs[i];

      //if (!metab->isUsed()) continue;

      std::ostringstream expression;
      std::ostringstream comments;

      std::string str1;
      std::string str2;

      comments << "metabolite \'" << CMetabNameInterface::getDisplayName(copasiModel, *metab, false)
               << "\': " << CModelEntity::StatusName[metab->getStatus()];

      switch (metab->getStatus())
        {
          case CModelEntity::Status::FIXED:
          {
            const CCompartment * comp;
            comp = metab->getCompartment();
            C_FLOAT64 volume = comp->getInitialValue();

            value = metab->getInitialConcentration() * volume;

            expression << exportNumber(value);

            break;
          }

          case CModelEntity::Status::ASSIGNMENT:

            break;

          case CModelEntity::Status::ODE:
          {

            const CCompartment * comp;
            comp = metab->getCompartment();
            C_FLOAT64 volume = comp->getInitialValue();

            value = metab->getInitialConcentration() * volume;

            expression << exportNumber(value);

            break;
          }

          case CModelEntity::Status::REACTIONS:
          {
            const CCompartment * comp;
            comp = metab->getCompartment();
            C_FLOAT64 volume = comp->getInitialValue();

            std::ostringstream tmp;
            std::ostringstream more;
            value = metab->getInitialConcentration() * volume;
            double eps = std::numeric_limits<double>::epsilon();
            more.precision(std::numeric_limits<double>::digits10 + 2);

            if (metab->isDependent())
              {
                for (j = 0; j < indep_size; j++)
                  {

                    if (fabs(L(i - ode_size, j)) > eps)
                      {

                        if (L(i - ode_size, j) < 0.0)
                          {
                            tmp << "-";
                          }
                        else
                          {
                            tmp << "+";
                          }

                        if (fabs(fabs(L(i - ode_size, j)) - 1.0) > eps)
                          {
                            tmp << fabs(L(i - ode_size, j)) << "*";
                          }

                        std::ostringstream jsmKey;
                        jsmKey << "sm_" << metabs[ode_size + j].getKey();

                        tmp << NameMap[jsmKey.str()];
                        const CCompartment * compj = metabs[ode_size + j].getCompartment();

                        value -= L(i - ode_size, j) * metabs[ode_size + j].getInitialConcentration() * compj->getInitialValue();
                      }

                    // comments << "  dependent ";
                  }

                more << value;
                std::stringstream stream; stream << "ct["  << (conservedTotals++) << "]";
                std::string ctName(stream.str());
                NameMap["CT " + metab->getObjectName()] = ctName;
                stream.clear(); stream << " conserved total for '" << metab->getObjectName() << "'";
                exportSingleObject(fixed, ctName, more.str(), stream.str());
                expression << ctName << tmp.str();
              }
            else
              {
                more << exportNumber(value);
                expression << more.str() << tmp.str();
              }

            break;
          }

          default:

            return false;

            break;
        }

      str1 = expression.str();
      str2 = comments.str();

      if (metab->getStatus() != CModelEntity::Status::ASSIGNMENT)
        if (!exportSingleMetabolite(metab, str1, str2)) return false;
    }

  return true;
}

/* export metabolites concentrations */
bool CODEExporter::exportMetabolitesConcentrations(const CModel* copasiModel)
{

  const CDataVector< CMetab > & metabs = copasiModel->getMetabolitesX();

  size_t metabs_size = metabs.size();

  size_t i;

  for (i = 0; i < metabs_size; i++)
    {
      const CMetab * metab = &metabs[i];

      //if (!metab->isUsed()) continue;

      std::string str1;
      std::string str2;

      std::ostringstream expression;
      std::ostringstream comments;

      comments << "concentration of metabolite \'" << CMetabNameInterface::getDisplayName(copasiModel, *metab, false)
               << "\': " << CModelEntity::StatusName[metab->getStatus()];

      std::ostringstream smKey;
      smKey << "sm_" << metab->getKey();

      expression << NameMap[smKey.str()] << "/" << NameMap[metabs[i].getCompartment()->getKey()];

      str1 = expression.str();
      str2 = comments.str();

      if (!exportSingleObject(assignment, NameMap[metab->getKey()], str1, str2))
        return false;
    }

  return true;
}

/* export compartments */

bool CODEExporter::exportCompartments(const CModel* copasiModel)
{
  const CDataVector< CCompartment > & comps = copasiModel->getCompartments();

  size_t comps_size = comps.size();
  size_t i;

  for (i = 0; i < comps_size; i++)
    {
      const CCompartment* comp = &comps[i];

      std::ostringstream comments;
      std::ostringstream expression;

      std::string str1;
      std::string str2;

      comments << "compartment \'" << comp->getObjectName() << "\':" << CModelEntity::StatusName[comp->getStatus()];

      switch (comp->getStatus())
        {
          case CModelEntity::Status::FIXED:
          {
            expression << exportNumber(comp->getInitialValue());

            break;
          }

          case CModelEntity::Status::ASSIGNMENT:

            break;

          case CModelEntity::Status::ODE:
          {

            expression << exportNumber(comp->getInitialValue());

            break;
          }

          default:
            return false;
            break;
        }

      str1 = expression.str();
      str2 = comments.str();

      if (comp->getStatus() != CModelEntity::Status::ASSIGNMENT)
        if (!exportSingleCompartment(comp, str1, str2)) return false;
    }

  return true;
}

/* export model values */

bool CODEExporter::exportModelValues(const CModel* copasiModel)
{
  const CDataVector< CModelValue > & modvals = copasiModel->getModelValues();

  size_t modvals_size = modvals.size();
  size_t i;

  for (i = 0; i < modvals_size; i++)
    {
      const CModelValue* modval = &modvals[i];

      std::ostringstream comments;
      std::ostringstream expression;

      std::string str1;
      std::string str2;

      comments << "global quantity \'" << modval->getObjectName() << "\':" << CModelEntity::StatusName[modval->getStatus()];

      switch (modval->getStatus())
        {
          case CModelEntity::Status::FIXED:
          {
            expression << exportNumber(modval->getInitialValue());

            break;
          }

          case CModelEntity::Status::ASSIGNMENT:
            //{
            //CExpression *cexpression = new CExpression(*modval->getExpressionPtr());
            //CEvaluationNode *node = cexpression->getRoot();
            //const std::string &key  = modval->getKey();
            //size_t index = 0;
            //if (!exportSingleFunction(node, key, index))
            //  return false;
            //expression << getDisplayExpressionString(cexpression);
            //}
            break;

          case CModelEntity::Status::ODE:
          {
            expression << exportNumber(modval->getInitialValue());

            break;
          }

          default:
            return false;
            break;
        }

      str1 = expression.str();
      str2 = comments.str();

      if (modval->getStatus() != CModelEntity::Status::ASSIGNMENT)
        if (!exportSingleModVal(modval, str1, str2)) return false;
    }

  return true;
}

/* export reaction parameters and kinetic functions */

bool CODEExporter::exportReacParamsAndFuncs(const CModel* copasiModel)
{

  const CDataVector< CMetab > & metabs = copasiModel->getMetabolitesX();
  const CDataVector< CReaction > & reacs = copasiModel->getReactions();

  size_t reacs_size = reacs.size();
  size_t indep_size = copasiModel->getNumIndependentReactionMetabs();
  size_t ode_size = copasiModel->getNumODEMetabs();

  const CMatrix< C_FLOAT64 > & redStoi = copasiModel->getRedStoi();

  size_t i, j;

  for (i = 0; i < reacs_size; ++i)
    {
      const CReaction* reac = &reacs[i];

      std::string name = reac->getObjectName();

      const CCopasiParameterGroup & parameters = reac->getParameters();
      size_t params_size = parameters.size();

      for (j = 0; j < params_size; ++j)
        {
          const CCopasiParameter* param = parameters.getParameter(j);
          const std::string & parameterName = param->getObjectName();

          if (!reac->isLocalParameter(parameterName))
            continue;

          std::ostringstream comments;
          std::ostringstream expression;

          expression << param->getValue< C_FLOAT64 >();

          comments << "reaction \'" << name << "\': " <<
                   " kinetic parameter \'" << parameterName << "\'";

          std::string str1 = expression.str();
          std::string str2 = comments.str();

          if (!exportSingleParameter(param, str1, str2)) return false;
        }

      if (!exportKineticFunction(reac)) return false;

      for (j = 0; j < indep_size; ++j)
        {
          std::ostringstream jequation;

          if (fabs(redStoi[j][i]) > 0.0)
            {
              if (redStoi[j][i] < 0.0)
                jequation << "-";
              else
                {
                  std::string str1 = equations[metabs[ode_size + j].getKey()];

                  if (!(isEmptyString(str1)))
                    jequation << "+";
                }

              if (fabs(redStoi[j][i]) != 1.0)
                jequation << fabs(redStoi[j][i]) << "*";

              jequation << KineticFunction2ODEmember(reac);

              if (reac->getEffectiveKineticLawUnitType() == CReaction::KineticLawUnit::ConcentrationPerTime) jequation << "*" << NameMap[metabs[ode_size + j].getCompartment()->getKey()];

              equations[metabs[ode_size + j].getKey()] += jequation.str();
            }
        }
    }

  return true;
}

/* export ODEs  */
bool CODEExporter::exportODEs(const CModel* copasiModel)
{
  const CDataVector< CMetab > & metabs = copasiModel->getMetabolitesX();
  size_t indep_size = copasiModel->getNumIndependentReactionMetabs();
  size_t ode_size = copasiModel->getNumODEMetabs();
  size_t metabs_size = metabs.size();

  size_t i;

  for (i = 0; i < indep_size && i + ode_size < metabs_size; ++i)
    {
      const CMetab * metab = &metabs[ode_size + i];

      std::string str1 = equations[metab->getKey()];
      std::string str2 = " ";

      if ((metab->getStatus() == CModelEntity::Status::REACTIONS && !(metab->isDependent())))
        if (!exportSingleODE(metab, str1, str2)) return false;
    }

  for (i = indep_size; i + ode_size < metabs_size; ++i)
    {
      const CMetab * metab = &metabs[ode_size + i];

      if (metab->getStatus() == CModelEntity::Status::REACTIONS && !metab->isDependent())
        {
          std::string str1 = "0";
          std::string str2 = " ";

          if (!exportSingleODE(metab, str1, str2)) return false;
        }
    }

  return true;
}

bool CODEExporter::exportClosingData(const CModel* /* copasiModel */,
                                     std::ostream & /* os */)
{return true;}

void CODEExporter::setReservedNames()
{return;}

std::string CODEExporter::translateTimeVariableName()
{return " ";}

std::string CODEExporter::translateObjectName(const std::string & /* realName */)
{return " ";}

std::string CODEExporter::setODEName(const std::string & /* objName */)
{return " ";}

std::string CODEExporter::setConcentrationName(const std::string & /* objName */)
{return " ";}

bool CODEExporter::exportSingleObject(std::ostringstream & /* which */,
                                      const std::string & /* name */,
                                      const std::string & /* expression */,
                                      const std::string & /* comments */)
{return true;}

bool CODEExporter::exportSingleMetabolite(const CMetab * /* metab */,
    std::string & /* expression */,
    std::string & /* comments */)
{return true;}

bool CODEExporter::exportSingleCompartment(const CCompartment * /* comp */,
    std::string & /* expression */,
    std::string & /* comments */)
{return true;}

bool CODEExporter::exportSingleModVal(const CModelValue * /* modval */,
                                      std::string & /* expression */,
                                      std::string & /* comments */)
{return true;}

bool CODEExporter::exportSingleModelEntity(const CModelEntity * /* tmp */,
    std::string & /* expression */,
    std::string & /* comments */)
{return true;}

bool CODEExporter::exportSingleParameter(const CCopasiParameter * /* param */,
    std::string & /* expression */,
    std::string & /* comments */)
{return true;}

bool CODEExporter::exportKineticFunction(const CReaction* reac)
{

  std::ostringstream comments;
  std::ostringstream expression;

  const CFunction* func;

  func = reac->getFunction();

  comments << "reaction \'" << reac->getObjectName() << "\': "
           << "kinetic function \'" << func ->getObjectName() << "\'";

  if (func->getType() != CEvaluationTree::MassAction)
    {
      CFunction* tmpfunc;
      tmpfunc = new CFunction(*func, NO_PARENT);

      const std::vector< std::vector< const CDataObject * > > & ObjectMap = reac->getParameterObjects();
      CCopasiTree< CEvaluationNode>::iterator treeIt = tmpfunc->getRoot();

      modifyTreeForMassAction(tmpfunc);

      while (treeIt != NULL)
        {
          if (treeIt->mainType() == CEvaluationNode::MainType::VARIABLE)
            {

              size_t index;
              CFunctionParameter::Role role;
              std::string tmpname;
              std::string name;

              name = tmpfunc->getVariables()[treeIt->getData()]->getObjectName();
              index = tmpfunc->getVariableIndex(name);
              role = tmpfunc->getVariables()[index]->getUsage();

              const CDataObject * obj = ObjectMap[index][0];

              if ((role == CFunctionParameter::Role::SUBSTRATE)
                  || (role == CFunctionParameter::Role::PRODUCT)
                  || (role == CFunctionParameter::Role::MODIFIER))
                {
                  if (obj)
                    tmpname = NameMap[obj->getKey()];
                  else
                    tmpname = "unknown";
                }

              if (role == CFunctionParameter::Role::PARAMETER)
                {
                  if (!(reac->isLocalParameter(index)))
                    {
                      const CModelValue* modval;
                      modval = dynamic_cast< const CModelValue * >(obj);
                      tmpname = NameMap[modval ->getKey()];
                    }
                  else
                    {
                      const CCopasiParameter* param;
                      param = dynamic_cast< const CCopasiParameter * >(obj);
                      tmpname = NameMap[param->getKey()];
                    }
                }

              if (role == CFunctionParameter::Role::VOLUME)
                {
                  const CCompartment* comp;
                  comp = dynamic_cast< const CCompartment * >(obj);
                  tmpname = NameMap[comp->getKey()];
                }

              if (role == CFunctionParameter::Role::TIME)
                tmpname = NameMap[timeKey];

              treeIt->setData(tmpname);
            }

          ++treeIt;
        }

      size_t index = 0;

      if (!exportSingleFunction(tmpfunc->getRoot(), reac, index)) return false;

      expression << getDisplayFunctionString(tmpfunc);
    }
  else
    {

      const CDataVector<CChemEqElement> & substrs = reac->getChemEq().getSubstrates();
      const CDataVector<CChemEqElement> & prods = reac->getChemEq().getProducts();
      const std::vector< std::vector< const CDataObject * > > & ObjectMap = reac->getParameterObjects();
      const CDataObject * obj;

      size_t substrs_size = substrs.size(), prods_size = prods.size();
      size_t k, m, mult;

      const CChemEqElement* substr;
      const CChemEqElement* prod;

      const CMassAction & cMassAction = *static_cast<const CMassAction*>(reac->getFunction());

      obj = ObjectMap[0][0];

      if (!(reac->isLocalParameter(0)))
        {
          const CModelValue* modval;
          modval = dynamic_cast< const CModelValue * >(obj);
          expression << NameMap[modval ->getKey()];
        }
      else
        {
          const CCopasiParameter * param;
          param = dynamic_cast< const CCopasiParameter * >(obj);
          expression << NameMap[param->getKey()];
        }

      for (k = 0; k < substrs_size; ++k)
        {
          substr = &substrs[k];
          mult = (size_t) substr->getMultiplicity();

          expression << "*" << NameMap[substr->getMetaboliteKey()];

          if (mult > 1)
            for (m = 1; m < mult; ++m)
              expression << "*" << NameMap[substr->getMetaboliteKey()];
        }

      if (cMassAction.isReversible() == TriTrue)
        {
          expression << "-";

          obj = ObjectMap[2][0];

          if (!(reac->isLocalParameter(2)))
            {
              const CModelValue * modval;
              modval = dynamic_cast< const CModelValue * >(obj);
              expression << NameMap[modval ->getKey()];
            }
          else
            {
              const CCopasiParameter * param;
              param = dynamic_cast< const CCopasiParameter * >(obj);
              expression << NameMap[param->getKey()];
            }

          for (k = 0; k < prods_size; ++k)
            {
              prod = &prods[k];
              mult = (size_t) prod->getMultiplicity();

              expression << "*" << NameMap[prod->getMetaboliteKey()];

              if (mult > 1)
                for (m = 1; m < mult; ++m)
                  expression << "*" << NameMap[prod->getMetaboliteKey()];
            }
        }
    }

  std::string name = translateObjectName(reac->getFunction()->getObjectName());
  std::ostringstream localKey;
  localKey << reac->getKey() << "_root_func";
  NameMap[localKey.str()] = name;

  std::string str1 = expression.str();
  std::string str2 = comments.str();

  //functions << std::endl;

  if (!exportSingleObject(functions, name, str1, str2)) return false;

  //functions << std::endl;

  return true;
}

bool CODEExporter::exportSingleFunction(CEvaluationNode* pNode, const CReaction *reac, size_t &index)
{
  return exportSingleFunction(pNode, reac->getKey(), index);
}

bool CODEExporter::exportSingleFunction(CEvaluationNode* pNode, const std::string& key, size_t &index)
{
  if (pNode)
    {
      CFunctionDB* pFunctionDB = CRootContainer::getFunctionList();
      CCopasiTree<CEvaluationNode>::iterator treeIt = pNode;

      while (treeIt != NULL)
        {
          if (treeIt->mainType() == CEvaluationNode::MainType::CALL)
            {
              const CFunction* func;
              func = static_cast<CFunction*>(pFunctionDB->findFunction((*treeIt).getData()));

              CFunction* tmpfunc = NULL;
              tmpfunc = new CFunction(*func, NO_PARENT);

              std::ostringstream localKey;

              if (index)
                localKey << key << "_func_" << index;
              else
                localKey << key << "_root_func";

              index++;

              std::string name = translateObjectName(func->getObjectName());
              NameMap[localKey.str()] = name;

              treeIt->setData(name);

              CODEExporter::modifyTreeForMassAction(tmpfunc);

              size_t i, vindex;
              CEvaluationNode* tmproot = tmpfunc->getRoot();
              CCopasiTree<CEvaluationNode>::iterator iIt, newIt = tmproot;

              if (newIt->mainType() == CEvaluationNode::MainType::VARIABLE)
                {
                  CEvaluationNode* child = dynamic_cast<CEvaluationNode*>(treeIt->getChild());
                  tmproot = child->copyBranch();
                }
              else while (newIt != NULL)
                  {
                    if (newIt->mainType() == CEvaluationNode::MainType::VARIABLE)
                      {
                        vindex = tmpfunc->getVariableIndex((*newIt).getData());

                        CEvaluationNode* child = dynamic_cast<CEvaluationNode*>(treeIt->getChild());

                        for (i = 0; i < vindex ; i++)
                          child = dynamic_cast<CEvaluationNode*>((child)->getSibling());

                        CEvaluationNode* parent = dynamic_cast<CEvaluationNode*>(newIt->getParent());
                        CEvaluationNode* newnode = child->copyBranch();

                        iIt = newIt;

                        ++newIt;

                        if (parent)
                          {
                            parent->addChild(newnode, &(*iIt));
                            parent->removeChild(&(*iIt));
                          }

                        delete &(*iIt);
                      }
                    else
                      ++newIt;
                  }

              if (!exportSingleFunction(tmproot, key, index)) return false;

              std::string expression;
              std::string comments = " ";

              expression = getDisplayFunctionString(tmpfunc);

              //functions << std::endl;

              if (!exportSingleObject(functions, name, expression, comments)) return false;

              //functions << std::endl;
            }

          ++treeIt;
        }
    }

  return true;
}

std::string CODEExporter::getDisplayFunctionString(CFunction * /* func */)
{return " ";}

std::string CODEExporter::getDisplayExpressionString(CExpression * /* tmp */)
{return " ";}

bool CODEExporter::exportSingleODE(const CModelEntity * /* mentity */,
                                   std::string & /* equation */,
                                   std::string & /* comments */)
{return true;}

bool CODEExporter::exportKineticFunctionGroup(const CModel * /* copasiModel */)
{return true;}

std::string CODEExporter::KineticFunction2ODEmember(const CReaction * /* reac */)
{return " ";}

std::string CODEExporter::exportTitleString(const size_t /* tmp */)
{return " ";}

std::string CODEExporter::exportClosingString(const size_t /* tmp */)
{return " ";}

/**
 **       This method tests if a string consists only of whitespace characters
 **/
bool CODEExporter::isEmptyString(std::string & str)
{return (str.find_first_not_of(" \n\t\r") == std::string::npos);}

/**
 **      This method modifies the export tree of the function for internal calls of Mass Action
 **/
void CODEExporter::modifyTreeForMassAction(CFunction* tmpfunc)
{
  CFunctionDB* pFunctionDB = CRootContainer::getFunctionList();

  CCopasiTree< CEvaluationNode>::iterator treeIt = tmpfunc->getRoot();

  while (treeIt != NULL)
    {
      if (treeIt->mainType() == CEvaluationNode::MainType::CALL)
        {
          const CFunction* callfunc;
          callfunc = static_cast<CFunction*>(pFunctionDB->findFunction((*treeIt).getData()));

          if (callfunc->getType() == CEvaluationTree::MassAction)
            {
              CEvaluationNode* parent = dynamic_cast<CEvaluationNode*>(treeIt->getParent());
              CEvaluationNode* child1 = dynamic_cast<CEvaluationNode*>(treeIt->getChild());
              CEvaluationNode* child2 = dynamic_cast<CEvaluationNode*>((treeIt->getChild())->getSibling());

              CEvaluationNode* newNode = NULL;
              CEvaluationNode* newNode1 = CEvaluationNode::create(CEvaluationNode::MainType::OPERATOR, CEvaluationNode::SubType::MULTIPLY, "*");

              CODEExporter::assembleSubTreeForMassAction(newNode1, child1, child2);

              if (callfunc->getObjectName() == "Mass action (irreversible)") newNode = newNode1;

              if (callfunc->getObjectName() == "Mass action (reversible)")
                {
                  newNode = CEvaluationNode::create(CEvaluationNode::MainType::OPERATOR, CEvaluationNode::SubType::MINUS, "-");
                  newNode->addChild(newNode1, NULL);

                  CEvaluationNode* newNode2 = CEvaluationNode::create(CEvaluationNode::MainType::OPERATOR, CEvaluationNode::SubType::MULTIPLY, "*");
                  CEvaluationNode* child3 = dynamic_cast<CEvaluationNode*>((child2)->getSibling());
                  CEvaluationNode* child4 = dynamic_cast<CEvaluationNode*>((child3)->getSibling());

                  CODEExporter::assembleSubTreeForMassAction(newNode2, child3, child4);

                  newNode->addChild(newNode2, newNode1);
                }

              if (parent)
                {
                  parent->addChild(newNode, &(*treeIt));
                  parent->removeChild(&(*treeIt));
                }

              delete &(*treeIt);
              treeIt = newNode;
            }
        }

      ++treeIt;
    }
}

/**
 **         This method assembles an expression sub tree for some internal call of Mass Action.
 **         The sub tree has to be included in the tree of corresponding root kinetic function in order to
 **         export this function  whithout the user defined internall Mass Action calls
 **/
void CODEExporter::assembleSubTreeForMassAction(CEvaluationNode* newNode, CEvaluationNode* child1, CEvaluationNode* child2)
{
  CEvaluationNode* newparent = newNode;
  CEvaluationNode* newchild1 = child1->copyBranch();
  newparent->addChild(newchild1, NULL);
  CEvaluationNode* newchild2;

  if (child2->mainType() == CEvaluationNode::MainType::VARIABLE)
    {
      newchild2 = CEvaluationNode::create(CEvaluationNode::MainType::OPERATOR, CEvaluationNode::SubType::MULTIPLY, "*");
      newparent->addChild(newchild2, newchild1);
      newparent = newchild2;
      newchild1 = child2->copyBranch();
      newparent->addChild(newchild1, NULL);
      newchild2 = child2->copyBranch();
      newparent->addChild(newchild2, newchild1);
    }

  if (0) // *************** TODO: the current Copasi version does not support the case bellow, the following part is not tested
    if (child2->mainType() == CEvaluationNode::MainType::VECTOR)
      {
        const std::vector<CEvaluationNode *> & vector = dynamic_cast< CEvaluationNodeVector *>(child2) ->getNodes();
        std::vector<CEvaluationNode *>::const_iterator it = vector.begin();
        std::vector<CEvaluationNode *>::const_iterator end = vector.end();

        size_t i = 0;

        while (it != end)
          {
            newchild2 = CEvaluationNode::create(CEvaluationNode::MainType::OPERATOR, CEvaluationNode::SubType::MULTIPLY, "*");
            newparent->addChild(newchild2, newchild1);

            newparent = newchild2;
            newchild1 = dynamic_cast<CEvaluationNode*>(vector[i]);
            newparent->addChild(newchild1, NULL);
            it++;
            i++;
          }

        if (it == end)
          {
            newchild2 = dynamic_cast<CEvaluationNode*>(vector[i]);
            newparent->addChild(newchild2, newchild1);
          }
      } // END of this TODO. ****************************************************************************************************
}
