// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/CODEExporter.cpp,v $
//   $Revision: 1.8.4.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/03/07 19:40:04 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <locale>
#include <math.h>
#include <iostream>
#include <fstream>
#include <ctype.h>

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"

#include "CODEExporter.h"

#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CMetabNameInterface.h"
#include "utilities/CCopasiVector.h"
#include "model/CReaction.h"
#include "model/CMoiety.h"
#include "model/CChemEqElement.h"
#include "function/CFunction.h"
#include "function/CExpression.h"
#include "function/CFunctionDB.h"
#include "report/CKeyFactory.h"
#include "function/CEvaluationTree.h"
#include "function/CEvaluationNode.h"
#include "function/CEvaluationNodeObject.h"
#include "function/CEvaluationNodeOperator.h"
#include "function/CEvaluationNodeFunction.h"
#include "utilities/CCopasiTree.h"
#include "utilities/CCopasiMessage.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"

/**
 ** Constructor for the exporter.
 */
CODEExporter::CODEExporter()
{}

/**
 ** Destructor for the exporter.
 */
CODEExporter::~CODEExporter()
{}

/**
 **
 */
bool CODEExporter::exportMathModel(const CModel * copasiModel, std::string mmasciiFilename,
                                   std::string /* Filter */, bool overwriteFile)
{
  /* check if the file already exisits.
          If yes, write if overwrite is true,
          else create an appropriate  CCopasiMessage. */

  std::ifstream testInfile(utf8ToLocale(mmasciiFilename).c_str(), std::ios::in);
  if (testInfile && !overwriteFile)
    {
      // create a CCopasiMessage with the appropriate error
      CCopasiMessage(CCopasiMessage::ERROR, MCDirEntry + 1, mmasciiFilename.c_str());
      return false;
    }

  std::ofstream outFile(utf8ToLocale(mmasciiFilename).c_str(), std::ios::out);

  /* translate Copasi data names in exporter syntax */

  if (!preprocess(copasiModel)) return false;

  /* export Copasi data */

  if (!exportTitleData(copasiModel, outFile)) return false;

  if (!exportMetabolites(copasiModel)) return false;

  if (!exportCompartments(copasiModel)) return false;

  if (!exportModelValues(copasiModel)) return false;

  if (!exportReacParamsAndFuncs(copasiModel)) return false;

  if (!exportKineticFunctionGroup (copasiModel)) return false;

  if (!exportODEs(copasiModel)) return false;

  //  if (!exportModelValuesExpressions(copasiModel)) return false;

  exportObjectNodesFromModel(copasiModel);

  if (!exportMetabolitesConcentrations(copasiModel)) return false;

  outFile << std::endl << exportTitleString(INITIAL) << std::endl << initial.str() << exportClosingString(INITIAL);
  outFile << std::endl << exportTitleString(FIXED) << std::endl << fixed.str() << exportClosingString(FIXED);
  outFile << std::endl << exportTitleString(ASSIGNMENT) << std::endl << assignment.str() << exportClosingString(ASSIGNMENT);
  outFile << std::endl << exportTitleString(HEADERS) << std::endl << headers.str() << exportClosingString(HEADERS);
  outFile << std::endl << exportTitleString(FUNCTIONS) << std::endl << functions.str() << exportClosingString(FUNCTIONS);
  outFile << std::endl << exportTitleString(ODEs) << std::endl << ode.str() << exportClosingString(ODEs);

  if (!exportClosingData(copasiModel, outFile)) return false;

  return true;
}

void CODEExporter::exportObjectNodesFromModel(const CModel * model)
{

  unsigned int i, imax;

  imax = model->getListOfSimulatedRefreshes().size();
  for (i = 0; i < imax; ++i)
    {
      CCopasiObject * tmp = CCopasiContainer::Root;

      CCopasiObject * obj = findObjectFromRefresh(tmp, model->getListOfSimulatedRefreshes()[i]);
      if (obj) exportSimulatedObject(obj);
      else
        std::cout << "Object for Refresh method is not found!" << std::endl;
    }
}

CCopasiObject* CODEExporter::findObjectFromRefresh(CCopasiObject * tmp, const Refresh* ref)
{

  CCopasiObject* obj = NULL;

  if (tmp->isContainer())
    {

      CCopasiContainer* container;
      container = (CCopasiContainer*)tmp;

      CCopasiContainer::objectMap::const_iterator it = container->getObjects().begin();

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

void CODEExporter::exportSimulatedObject(CCopasiObject * obj)
{

  if (obj->isReference())
    {
      CCopasiObject* parent = obj->getObjectParent();
      assert(parent);
      std::string typeString = parent->getObjectType();
      std::string name = obj->getObjectName();

      if (typeString == "Metabolite" || typeString == "ModelValue" || typeString == "Compartment")
        if (name == "Concentration" || name == "Value" || name == "Volume" || name == "Rate")
          if (!exportModelEntityExpression(obj)) return;
          else return;

      //TODO warning for initial assignments
    }
  return;
}

bool CODEExporter::exportModelEntityExpression(CCopasiObject * obj)
{
  if (obj->isReference())
    {
      CCopasiObject* parent = obj->getObjectParent();
      assert(parent);

      std::string typeString = parent->getObjectType();

      CModelEntity* tmp;
      tmp = dynamic_cast< CModelEntity * >(parent);

      std::ostringstream comments;
      std::ostringstream expression;

      std::string str1;
      std::string str2;

      comments << "model entity \'" << tmp->getObjectName() << "\':" << CModelEntity::StatusName[tmp->getStatus()];

      if (tmp->getStatus() == CModelEntity::ODE)
        {
          const CExpression* pExpression = tmp->getExpressionPtr();
          assert(pExpression);

          std::string result;
          result = isModelEntityExpressionODEExporterCompatible(tmp, pExpression);
          if ((isEmptyString(result)))
            {
              expression << exportExpression(pExpression);
            }
          equations[tmp->getKey()] = expression.str();
        }

      switch (tmp->getStatus())
        {
        case CModelEntity::FIXED:
          break;
        case CModelEntity::ASSIGNMENT:
          {

            const CExpression* pExpression = tmp->getExpressionPtr();
            assert(pExpression);

            std::string result;
            result = isModelEntityExpressionODEExporterCompatible(tmp, pExpression);
            if (!(isEmptyString(result)))
              comments << result;
            else
              {
                expression << exportExpression(pExpression);
              }

            str1 = expression.str();
            str2 = comments.str();

            CMetab* metab;
            metab = dynamic_cast< CMetab * >(tmp);
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
        case CModelEntity::ODE:
          {

            const CExpression* pExpression = tmp->getExpressionPtr();
            assert(pExpression);

            std::string result;
            result = isModelEntityExpressionODEExporterCompatible(tmp, pExpression);
            if (!(isEmptyString(result)))
              comments << result;

            str1 = equations[tmp->getKey()];
            str2 = comments.str();

            CMetab* metab;
            metab = dynamic_cast< CMetab * >(tmp);
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

std::string CODEExporter::isModelEntityExpressionODEExporterCompatible(CModelEntity * tmp, const CExpression* pExpression)
{

  std::ostringstream result;
  const std::vector<CEvaluationNode*>& objectNodes = pExpression->getNodeList();
  unsigned j, jMax = objectNodes.size();
  for (j = 0;j < jMax;++j)
    {
      if (CEvaluationNode::type(objectNodes[j]->getType()) == CEvaluationNode::OBJECT)
        {
          const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(objectNodes[j]);
          assert(pObjectNode);
          std::vector<CCopasiContainer*> containers;
          containers.push_back(CCopasiDataModel::Global->getModel());
          const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(containers, pObjectNode->getObjectCN());
          assert(pObject);

          if (pObject->isReference())
            {
              CCopasiObject* pObjectParent = pObject->getObjectParent();
              assert(pObjectParent);
              std::string typeString = pObjectParent->getObjectType();

              if (typeString == "Compartment")
                {
                  if (pObject->getObjectName() != "Volume"
                      && pObject->getObjectName() != "InitialVolume"
                      && pObject->getObjectName() != "Rate")
                    {
                      result << std::endl << "WARNING : reference to property other than transient volume for compartment \"" << pObjectParent->getObjectName() << "\" in expression  for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }
                }
              else if (typeString == "Metabolite")
                {

                  if (pObject->getObjectName() != "Concentration"
                      && pObject->getObjectName() != "InitialConcentration"
                      && pObject->getObjectName() != "Rate")
                    {

                      result << std::endl << "WARNING : reference to property other than transient concentration, initial concentration or concentrations rate for metabolite \"" << pObjectParent->getObjectName() << "\" in expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }

                  CMetab* metab;
                  metab = dynamic_cast< CMetab * >(pObjectParent);

                  if ((metab->getStatus() == CModelEntity::REACTIONS && metab->isDependent()) && pObject->getObjectName() == "Rate")
                    {

                      result << std::endl << "WARNING : reference to rate of dependent (defined from moiety)  metabolite \"" << pObjectParent->getObjectName() << "\" in expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }
                }
              else if (typeString == "ModelValue")
                {
                  if (pObject->getObjectName() != "Value"
                      && pObject->getObjectName() != "InitialValue"
                      && pObject->getObjectName() != "Rate")
                    {

                      result << std::endl << "WARNING : reference to property other than transient value, initial value or rate for \"" << typeString << "\" \"" << pObjectParent->getObjectName() << "\" in expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }
                }
              else if (typeString == "Model")
                {

                  if (pObject->getObjectName() != "Time" && pObject->getObjectName() != "Initial Time")
                    {

                      result << std::endl << "WARNING : reference to property other than initial time or transient time for model \"" << pObjectParent->getObjectName() << "\" in expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }
                }
              else if (typeString == "Parameter")
                {

                  if (pObject->getObjectName() != "Value")
                    {

                      result << std::endl << "WARNING : reference to property other than initial time or transient time for model \"" << pObjectParent->getObjectName() << "\" in expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\".";
                    }
                }

              else
                {
                  result << std::endl << "WARNING : expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\" contains reference to a value in object \"" << pObjectParent->getObjectName() << "\" of type \"" << typeString << "\" which is not supported in this ODE exporter Version.";
                }
            }
          else
            {
              result << std::endl << "WARNING : expression for \"" << tmp->getObjectType() << "\" \"" << tmp->getObjectName() << "\" contains reference to a object named \"" << pObject->getObjectName() << "\" of type \"" << pObject->getObjectType() << "\" which is not supported in this ODE exporter Version.";
            }
        }
    }
  return result.str();
}

std::string CODEExporter::exportExpression(const CExpression* pExpression)
{

  std::string result;

  CExpression* tmpExpression;
  tmpExpression = new CExpression(*pExpression);

  const std::vector<CEvaluationNode*>& objectNodes = tmpExpression->getNodeList();
  unsigned j, jMax = objectNodes.size();
  for (j = 0;j < jMax;++j)
    {
      if (CEvaluationNode::type(objectNodes[j]->getType()) == CEvaluationNode::OBJECT)
        {
          CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(objectNodes[j]);
          assert(pObjectNode);
          CCopasiObjectName cn = pObjectNode->getObjectCN();

          CCopasiObject* pObject = CCopasiContainer::ObjectFromName(cn);
          assert(pObject);
          std::string objectName = pObject->getObjectName();

          if (pObject->isReference()) pObject = pObject->getObjectParent();
          std::string objectType = pObject->getObjectType();

          if (objectType == "Model")
            {
              if (objectName == "Time")
                objectNodes[j]->setData(NameMap[timeKey]);

              if (objectName == "Initial Time")
                {
                  CTrajectoryTask * pTrajectory =
                    dynamic_cast<CTrajectoryTask *>((*CCopasiDataModel::Global->getTaskList())["Time-Course"]);

                  CTrajectoryProblem * pTrajectoryProblem =
                    dynamic_cast<CTrajectoryProblem *>(pTrajectory->getProblem());

                  std::ostringstream value;
                  value << pTrajectoryProblem->getOutputStartTime();
                  objectNodes[j]->setData(value.str());
                }
            }
          else
            if (objectType == "ModelValue")
              {
                if (objectName == "Value") objectNodes[j]->setData(NameMap[pObject->getKey()]);
                if (objectName == "InitialValue")
                  {
                    CModelValue* modval;
                    modval = dynamic_cast< CModelValue * >(pObject);
                    std::ostringstream value;
                    value << modval->getInitialValue();
                    objectNodes[j]->setData(value.str());
                  }
                if (objectName == "Rate")
                  {
                    CModelValue* modval;
                    modval = dynamic_cast< CModelValue * >(pObject);

                    if (modval->getStatus() == CModelEntity::ODE)
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
            else
              if (objectType == "Metabolite")
                {
                  if (objectName == "Concentration")
                    objectNodes[j]->setData(NameMap[pObject->getKey()]);
                  if (objectName == "InitialConcentration")
                    {
                      CMetab* metab;
                      metab = dynamic_cast< CMetab * >(pObject);
                      std::ostringstream value;
                      value << metab->getInitialConcentration();
                      objectNodes[j]->setData(value.str());
                    }
                  if (objectName == "Rate")
                    {
                      CMetab* metab;
                      metab = dynamic_cast< CMetab * >(pObject);

                      if ((metab->getStatus() == CModelEntity::REACTIONS && !metab->isDependent()) || metab->getStatus() == CModelEntity::ODE)
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
              else
                if (objectType == "Compartment")
                  {
                    if (objectName == "Volume")
                      objectNodes[j]->setData(NameMap[pObject->getKey()]);

                    if (objectName == "InitialVolume")
                      {
                        CCompartment* comp;
                        comp = dynamic_cast< CCompartment * >(pObject);
                        std::ostringstream value;
                        value << comp-> getInitialValue();
                        objectNodes[j]->setData(value.str());
                      }
                    if (objectName == "Rate")
                      {

                        CCompartment* comp;
                        comp = dynamic_cast< CCompartment * >(pObject);

                        if (comp->getStatus() == CModelEntity::ODE)
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
                else
                  if (objectType == "Parameter")
                    {
                      if (objectName == "Value")
                        objectNodes[j]->setData(NameMap[pObject->getKey()]);
                    }
        }
    }

  result = getDisplayExpressionString(tmpExpression);

  return result;
}

bool CODEExporter::preprocess(const CModel* copasiModel)
{
  unsigned C_INT32 i, j;

  setReservedNames();

  timeKey = "time";

  NameMap[timeKey] = translateTimeVariableName();

  const CCopasiVector< CMetab > & metabs = copasiModel->getMetabolitesX();
  unsigned C_INT32 metabs_size = metabs.size();

  for (i = 0; i < metabs_size; i++)
    {
      CMetab * metab = metabs[i];

      //if (metab->isUsed()) //changed
      {

        std::string name = translateObjectName(metab->getObjectName());

        std::ostringstream smKey;
        smKey << "sm_" << metab->getKey();

        NameMap[smKey.str()] = name; // mass fraction

        NameMap[metab->getKey()] = setConcentrationName(name); //concentration

        if (metab->getStatus() == CModelEntity::REACTIONS && !metab->isDependent() || metab->getStatus() == CModelEntity::ODE)
          {
            std::ostringstream odeKey;
            odeKey << "ode_" << metab->getKey();
            NameMap[odeKey.str()] = setODEName(name);
          }
      }
    }

  unsigned C_INT32 comps_size = copasiModel->getCompartments().size();
  const CCopasiVector< CCompartment > & comps = copasiModel->getCompartments();

  for (i = 0; i < comps_size; i++)
    {
      CCompartment* comp = comps[i];
      std::string name = translateObjectName(comp->getObjectName());
      NameMap[comp->getKey()] = name;

      if (comp->getStatus() == CModelEntity::ODE)
        {
          std::ostringstream odeKey;
          odeKey << "ode_" << comp->getKey();
          NameMap[odeKey.str()] = setODEName(name);
        }
    }

  unsigned C_INT32 modvals_size = copasiModel->getModelValues().size();
  const CCopasiVector< CModelValue > & modvals = copasiModel->getModelValues();

  for (i = 0; i < modvals_size; i++)
    {
      CModelValue* modval = modvals[i];
      std::string name = translateObjectName(modval->getObjectName());
      NameMap[modval->getKey()] = name;

      if (modval->getStatus() == CModelEntity::ODE)
        {
          std::ostringstream odeKey;
          odeKey << "ode_" << modval->getKey();
          NameMap[odeKey.str()] = setODEName(name);
        }
    }

  unsigned C_INT32 reacs_size = copasiModel->getReactions().size();

  const CCopasiVector< CReaction > & reacs = copasiModel->getReactions();

  for (i = 0; i < reacs_size; ++i)
    {
      unsigned C_INT32 params_size;

      params_size = reacs[i]->getParameters().size();

      for (j = 0; j < params_size; ++j)
        NameMap[reacs[i]->getParameters().getParameter(j)->getKey()] =
          translateObjectName(reacs[i]->getParameters().getParameter(j)->getObjectName());
    }

  return true;
}

bool CODEExporter::exportTitleData(const CModel* /* copasiModel */,
                                   std::ofstream & /* outFile */)
{return true;}

/* export metabolites */
bool CODEExporter::exportMetabolites(const CModel* copasiModel)
{

  const CCopasiVector< CMetab > & metabs = copasiModel->getMetabolitesX();
  const CModel::CLinkMatrixView & L = copasiModel->getL();

  unsigned C_INT32 metabs_size = metabs.size();
  unsigned C_INT32 indep_size = copasiModel->getNumIndependentMetabs();
  unsigned C_INT32 ode_size = copasiModel->getNumODEMetabs();

  unsigned C_INT32 i, j;
  C_FLOAT64 value;

  for (i = 0; i < metabs_size; i++)
    {
      const CMetab * metab;
      metab = metabs[i];

      //if (!metab->isUsed()) continue;

      std::ostringstream expression;
      std::ostringstream comments;

      std::string str1;
      std::string str2;

      comments << "metabolite \'" << CMetabNameInterface::getDisplayName(copasiModel, *metab)
      << "\': " << CModelEntity::StatusName[metab->getStatus()];

      switch (metab->getStatus())
        {
        case CModelEntity::FIXED:
          {
            const CCompartment * comp;
            comp = metab->getCompartment();
            C_FLOAT64 volume = comp->getInitialValue();

            value = metab->getInitialConcentration() * volume;

            expression << value;

            break;
          }
        case CModelEntity::ASSIGNMENT:

          break;

        case CModelEntity::ODE:
          {

            const CCompartment * comp;
            comp = metab->getCompartment();
            C_FLOAT64 volume = comp->getInitialValue();

            value = metab->getInitialConcentration() * volume;

            expression << value;

            break;
          }
        case CModelEntity::REACTIONS:
          {
            const CCompartment * comp;
            comp = metab->getCompartment();
            C_FLOAT64 volume = comp->getInitialValue();

            std::ostringstream tmp;
            std::ostringstream more;
            value = metab->getInitialConcentration() * volume;

            if (metab->isDependent())
              {
                for (j = 0; j < indep_size; j++)
                  {

                    if (L(i - ode_size, j) != 0.0)
                      {

                        if (L(i - ode_size, j) < 0.0)
                          {
                            tmp << "-";
                          }
                        else
                          {
                            tmp << "+";
                          }
                        if (fabs(L(i - ode_size, j)) != 1.0)
                          tmp << fabs(L(i - ode_size, j)) << "*";

                        std::ostringstream jsmKey;
                        jsmKey << "sm_" << metabs[ode_size + j]->getKey();

                        tmp << NameMap[jsmKey.str()];
                        const CCompartment * compj = metabs[ode_size + j]->getCompartment();

                        value -= L(i - ode_size, j) * metabs[ode_size + j]->getInitialConcentration() * compj->getInitialValue();
                      }

                    // comments << "  dependent ";
                  }
              }
            more.precision(16);
            more << value;

            expression << more.str() << tmp.str();

            break;
          }
        default:

          return false;

          break;
        }

      str1 = expression.str();
      str2 = comments.str();

      if (metab->getStatus() != CModelEntity::ASSIGNMENT)
        if (!exportSingleMetabolite(metab, str1, str2)) return false;
    }
  return true;
}

/* export metabolites concentrations */
bool CODEExporter::exportMetabolitesConcentrations(const CModel* copasiModel)
{

  const CCopasiVector< CMetab > & metabs = copasiModel->getMetabolitesX();

  unsigned C_INT32 metabs_size = metabs.size();

  unsigned C_INT32 i;

  for (i = 0; i < metabs_size; i++)
    {
      const CMetab * metab;
      metab = metabs[i];

      //if (!metab->isUsed()) continue;

      std::string str1;
      std::string str2;

      std::ostringstream expression;
      std::ostringstream comments;

      comments << "concentration of metabolite \'" << CMetabNameInterface::getDisplayName(copasiModel, *metab)
      << "\': " << CModelEntity::StatusName[metab->getStatus()];

      std::ostringstream smKey;
      smKey << "sm_" << metab->getKey();

      expression << NameMap[smKey.str()] << "/" << NameMap[metabs[i]->getCompartment()->getKey()];

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
  const CCopasiVector< CCompartment > & comps = copasiModel->getCompartments();

  unsigned C_INT32 comps_size = comps.size();
  unsigned C_INT32 i;

  for (i = 0; i < comps_size; i++)
    {
      CCompartment* comp;
      comp = comps[i];

      std::ostringstream comments;
      std::ostringstream expression;

      std::string str1;
      std::string str2;

      comments << "compartment \'" << comp->getObjectName() << "\':" << CModelEntity::StatusName[comp->getStatus()];

      switch (comp->getStatus())
        {
        case CModelEntity::FIXED:
          {
            expression << comp->getValue();

            break;
          }
        case CModelEntity::ASSIGNMENT:

          break;

        case CModelEntity::ODE:
          {

            expression << comp->getInitialValue();

            break;
          }
        default:
          return false;
          break;
        }

      str1 = expression.str();
      str2 = comments.str();

      if (comp->getStatus() != CModelEntity::ASSIGNMENT)
        if (!exportSingleCompartment(comp, str1, str2)) return false;
    }
  return true;
}

/* export model values */

bool CODEExporter::exportModelValues(const CModel* copasiModel)
{
  const CCopasiVector< CModelValue > & modvals = copasiModel->getModelValues();

  unsigned C_INT32 modvals_size = modvals.size();
  unsigned C_INT32 i;

  for (i = 0; i < modvals_size; i++)
    {
      CModelValue* modval;
      modval = modvals[i];

      std::ostringstream comments;
      std::ostringstream expression;

      std::string str1;
      std::string str2;

      comments << "global quantity \'" << modval->getObjectName() << "\':" << CModelEntity::StatusName[modval->getStatus()];

      switch (modval->getStatus())
        {
        case CModelEntity::FIXED:
          {
            expression << modval->getValue();

            break;
          }
        case CModelEntity::ASSIGNMENT:
          break;
        case CModelEntity::ODE:
          {
            expression << modval->getInitialValue();

            break;
          }
        default:
          return false;
          break;
        }

      str1 = expression.str();
      str2 = comments.str();

      if (modval->getStatus() != CModelEntity::ASSIGNMENT)
        if (!exportSingleModVal(modval, str1, str2)) return false;
    }

  return true;
}

/* export reaction parameters and kinetic functions */

bool CODEExporter::exportReacParamsAndFuncs(const CModel* copasiModel)
{

  const CCopasiVector< CMetab > & metabs = copasiModel->getMetabolitesX();
  const CCopasiVector< CReaction > & reacs = copasiModel->getReactions();

  unsigned C_INT32 reacs_size = reacs.size();
  unsigned C_INT32 indep_size = copasiModel->getNumIndependentMetabs();
  unsigned C_INT32 ode_size = copasiModel->getNumODEMetabs();

  const CMatrix< C_FLOAT64 > & redStoi = copasiModel->getRedStoi();

  unsigned C_INT32 i, j;

  for (i = 0; i < reacs_size; ++i)
    {
      CReaction* reac;
      reac = reacs[i];

      std::string name = reac->getObjectName();

      unsigned C_INT32 params_size = reac->getParameters().size();

      for (j = 0; j < params_size; ++j)
        {
          std::ostringstream comments;
          std::ostringstream expression;

          CCopasiParameter* param;

          param = reac->getParameters().getParameter(j);
          expression << *param->getValue().pDOUBLE;

          comments << "reaction \'" << name << "\': " <<
          " kinetic parameter \'" << param->getObjectName() << "\'";

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
                  std::string str1 = equations[metabs[ode_size + j]->getKey()];
                  if (!(isEmptyString(str1)))
                    jequation << "+";
                }

              if (fabs(redStoi[j][i]) != 1.0)
                jequation << fabs(redStoi[j][i]) << "*";

              jequation << KineticFunction2ODEmember(reac);

              //std::cout << "reaction  " <<  reac->getObjectName() << " compartment number "  << reac->getCompartmentNumber() << std::endl;

              if (reac->getCompartmentNumber() == 1) jequation << "*" << NameMap[metabs[ode_size + j]->getCompartment()->getKey()];

              //std::cout << " member:    " <<  jequation.str() << std::endl;

              equations[metabs[ode_size + j]->getKey()] += jequation.str();
            }
        }
    }

  return true;
}

/* export ODEs  */
bool CODEExporter::exportODEs(const CModel* copasiModel)
{
  const CCopasiVector< CMetab > & metabs = copasiModel->getMetabolitesX();
  unsigned C_INT32 indep_size = copasiModel->getNumIndependentMetabs();
  unsigned C_INT32 ode_size = copasiModel->getNumODEMetabs();

  unsigned C_INT32 i;

  for (i = 0; i < indep_size; ++i)
    {

      std::string str1 = equations[metabs[ode_size + i]->getKey()];
      std::string str2 = " ";

      if ((metabs[ode_size + i]->getStatus() == CModelEntity::REACTIONS && !(metabs[ode_size + i]->isDependent())))
        if (!exportSingleODE(metabs[ode_size + i], str1, str2)) return false;
    }

  return true;
}

bool CODEExporter::exportClosingData(const CModel* /* copasiModel */,
                                     std::ofstream & /* outFile */)
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
                                      std::string & /* name */,
                                      std::string & /* expression */,
                                      std::string & /* comments */)
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

bool CODEExporter::exportKineticFunction (CReaction* reac)
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
      tmpfunc = new CFunction(*func);

      const std::vector<std::vector<std::string> > & keyMap = reac->getParameterMappings();
      CCopasiTree< CEvaluationNode>::iterator treeIt = tmpfunc->getRoot();

      modifyTreeForMassAction(tmpfunc);

      while (treeIt != NULL)
        {
          if (CEvaluationNode::type(treeIt->getType()) == CEvaluationNode::VARIABLE)
            {

              unsigned C_INT32 index;
              CFunctionParameter::Role role;
              std::string tmpname;
              std::string name;

              name = tmpfunc->getVariables()[treeIt->getData()]->getObjectName();
              index = tmpfunc->getVariableIndex(name);
              role = tmpfunc->getVariables()[index]->getUsage();

              CCopasiObject * obj = GlobalKeys.get(keyMap[index][0]);

              if ((role == CFunctionParameter::SUBSTRATE)
                  || (role == CFunctionParameter::PRODUCT)
                  || (role == CFunctionParameter::MODIFIER))
                {
                  CMetab* metab;
                  metab = dynamic_cast< CMetab * >(obj);
                  tmpname = NameMap[metab->getKey()];
                }

              if (role == CFunctionParameter::PARAMETER)
                if (!(reac->isLocalParameter(index)))
                  {
                    CModelValue* modval;
                    modval = dynamic_cast< CModelValue * >(obj);
                    tmpname = NameMap[modval ->getKey()];
                  }
                else
                  {
                    CCopasiParameter* param;
                    param = dynamic_cast< CCopasiParameter * >(obj);
                    tmpname = NameMap[param->getKey()];
                  }

              if (role == CFunctionParameter::VOLUME)
                {
                  CCompartment* comp;
                  comp = dynamic_cast< CCompartment * >(obj);
                  tmpname = NameMap[comp->getKey()];
                }

              if (role == CFunctionParameter::TIME)
                tmpname = NameMap[timeKey];

              treeIt->setData(tmpname);
            }

          ++treeIt;
        }

      unsigned C_INT32 index = 0;

      if (!exportSingleFunction (tmpfunc->getRoot(), reac, index)) return false;

      expression << getDisplayFunctionString(tmpfunc);
    }
  else
    {

      const CCopasiVector<CChemEqElement> & substrs = reac->getChemEq().getSubstrates();
      const CCopasiVector<CChemEqElement> & prods = reac->getChemEq().getProducts();
      const std::vector<std::vector<std::string> > & keyMap = reac->getParameterMappings();
      CCopasiObject * obj;

      unsigned C_INT32 substrs_size = substrs.size(), prods_size = prods.size();
      unsigned C_INT32 k, m, mult;

      CChemEqElement* substr;
      CChemEqElement* prod;

      const CMassAction cMassAction = *static_cast<const CMassAction*>(reac->getFunction());

      obj = GlobalKeys.get(keyMap[0][0]);

      if (!(reac->isLocalParameter(0)))
        {
          CModelValue* modval;
          modval = dynamic_cast< CModelValue * >(obj);
          expression << NameMap[modval ->getKey()];
        }
      else
        {
          CCopasiParameter * param;
          param = dynamic_cast< CCopasiParameter * >(obj);
          expression << NameMap[param->getKey()];
        }

      for (k = 0; k < substrs_size; ++k)
        {
          substr = substrs[k];
          mult = (unsigned C_INT32) substr->getMultiplicity();

          expression << "*" << NameMap[substr->getMetaboliteKey()];

          if (mult > 1)
            for (m = 1; m < mult; ++m)
              expression << "*" << NameMap[substr->getMetaboliteKey()];
        }

      if (cMassAction.isReversible() == TriTrue)
        {
          expression << "-";

          obj = GlobalKeys.get(keyMap[2][0]);

          if (!(reac->isLocalParameter(2)))
            {
              CModelValue * modval;
              modval = dynamic_cast< CModelValue * >(obj);
              expression << NameMap[modval ->getKey()];
            }
          else
            {
              CCopasiParameter * param;
              param = dynamic_cast< CCopasiParameter * >(obj);
              expression << NameMap[param->getKey()];
            }

          for (k = 0; k < prods_size; ++k)
            {
              prod = prods[k];
              mult = (unsigned C_INT32) prod->getMultiplicity();

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

bool CODEExporter::exportSingleFunction(CEvaluationNode* pNode, const CReaction *reac, unsigned C_INT32 &index)
{
  if (pNode)
    {
      CFunctionDB* pFunctionDB = CCopasiDataModel::Global->getFunctionList();
      CCopasiTree<CEvaluationNode>::iterator treeIt = pNode;

      while (treeIt != NULL)
        {
          if (CEvaluationNode::type(treeIt->getType()) == CEvaluationNode::CALL)
            {
              const CFunction* func;
              func = static_cast<CFunction*> (pFunctionDB->findFunction((*treeIt).getData()));

              CFunction* tmpfunc = NULL;
              tmpfunc = new CFunction(*func);

              std::ostringstream localKey;

              if (index)
                localKey << reac->getKey() << "_func_" << index;
              else
                localKey << reac->getKey() << "_root_func";
              index++;

              std::string name = translateObjectName(func->getObjectName());
              NameMap[localKey.str()] = name;

              treeIt->setData(name);

              CODEExporter::modifyTreeForMassAction(tmpfunc);

              unsigned C_INT32 i, vindex;
              CEvaluationNode* tmproot = tmpfunc->getRoot();
              CCopasiTree<CEvaluationNode>::iterator iIt, newIt = tmproot;

              if (CEvaluationNode::type(newIt->getType()) == CEvaluationNode::VARIABLE)
                {
                  CEvaluationNode* child = dynamic_cast<CEvaluationNode*>(treeIt->getChild());
                  tmproot = child->copyBranch();
                }
              else while (newIt != NULL)
                  {
                    if (CEvaluationNode::type(newIt->getType()) == CEvaluationNode::VARIABLE)
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

              if (!exportSingleFunction (tmproot, reac, index)) return false;

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

std::string CODEExporter::exportTitleString(const unsigned C_INT32 /* tmp */)
{return " ";}

std::string CODEExporter::exportClosingString(const unsigned C_INT32 /* tmp */)
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
  CFunctionDB* pFunctionDB = CCopasiDataModel::Global->getFunctionList();

  CCopasiTree< CEvaluationNode>::iterator treeIt = tmpfunc->getRoot();

  while (treeIt != NULL)
    {
      if (CEvaluationNode::type(treeIt->getType()) == CEvaluationNode::CALL)
        {
          const CFunction* callfunc;
          callfunc = static_cast<CFunction*> (pFunctionDB->findFunction((*treeIt).getData()));

          if (callfunc->getType() == CEvaluationTree::MassAction)
            {
              CEvaluationNode* parent = dynamic_cast<CEvaluationNode*>(treeIt->getParent());
              CEvaluationNode* child1 = dynamic_cast<CEvaluationNode*>(treeIt->getChild());
              CEvaluationNode* child2 = dynamic_cast<CEvaluationNode*>((treeIt->getChild())->getSibling());

              CEvaluationNode* newNode;
              CEvaluationNode* newNode1 = CEvaluationNode::create((CEvaluationNode::Type)(CEvaluationNode::OPERATOR
                                          | CEvaluationNodeOperator::MULTIPLY), "*");

              CODEExporter::assembleSubTreeForMassAction(newNode1, child1, child2);

              if (callfunc->getObjectName() == "Mass action (irreversible)") newNode = newNode1;

              if (callfunc->getObjectName() == "Mass action (reversible)")
                {
                  newNode = CEvaluationNode::create((CEvaluationNode::Type)(CEvaluationNode::OPERATOR
                                                    | CEvaluationNodeOperator::MINUS), "-");
                  newNode->addChild(newNode1, NULL);

                  CEvaluationNode* newNode2 = CEvaluationNode::create((CEvaluationNode::Type)(CEvaluationNode::OPERATOR
                                              | CEvaluationNodeOperator::MULTIPLY), "*");
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

  if (CEvaluationNode::type(child2->getType()) == CEvaluationNode::VARIABLE)
    {
      newchild2 = CEvaluationNode::create((CEvaluationNode::Type)(CEvaluationNode::OPERATOR
                                          | CEvaluationNodeOperator::MULTIPLY), "*");
      newparent->addChild(newchild2, newchild1);
      newparent = newchild2;
      newchild1 = child2->copyBranch();
      newparent->addChild(newchild1, NULL);
      newchild2 = child2->copyBranch();
      newparent->addChild(newchild2, newchild1);
    }

  if (0) // *************** TODO: the current Copasi version does not support the case bellow, the following part is not tested
    if (CEvaluationNode::type(child2->getType()) == CEvaluationNode::VECTOR)
      {
        const std::vector<CEvaluationNode *> & vector = dynamic_cast< CEvaluationNodeVector *> (child2) ->getVector();
        std::vector<CEvaluationNode *>::const_iterator it = vector.begin();
        std::vector<CEvaluationNode *>::const_iterator end = vector.end();

        unsigned C_INT32 i = 0;

        while (it != end)
          {
            newchild2 = CEvaluationNode::create((CEvaluationNode::Type)(CEvaluationNode::OPERATOR
                                                | CEvaluationNodeOperator::MULTIPLY), "*");
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
