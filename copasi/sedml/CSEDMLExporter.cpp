// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CSEDMLExporter.cpp
 *
 *  Created on: 24 Jul 2013
 *      Author: dada
 */

/**
 * Export the model and Task to SEDML.
 * The SEDML document is returned as a string and SBML model is copied to sbmldocument parameter. In case of an error, an
 * empty string is returned.
 */

#include <sbml/math/FormulaParser.h>

#include <sedml/SedTypes.h>
#include <sbml/SBMLTypes.h>

#include "SEDMLUtils.h"

#include "copasi/sbml/CSBMLExporter.h"
#include "CSEDMLExporter.h"

#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/scan/CScanTask.h"
#include "copasi/scan/CScanProblem.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/utilities/CParameterEstimationUtils.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/plot/CPlotSpecification.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModelValue.h"
#include "copasi/commandline/CLocaleString.h"

#include <algorithm>

#define SEDML_SET_ID(element, arguments) \
  {\
    std::ostringstream idStream; idStream << arguments;\
    std::string pVarId = idStream.str();\
    int count = 1;\
    while (mGeneratedIds.find(pVarId) != mGeneratedIds.end())\
      {\
        pVarId = SEDMLUtils::getNextId(idStream.str(), ++count);\
      }\
    mGeneratedIds.insert(pVarId);\
    element->setId(pVarId);\
  }

std::string CSEDMLExporter::exportModelAndTasksToString(CDataModel& dataModel,
    const std::string &modelLocation,
    unsigned int sedmlLevel,
    unsigned int sedmlVersion)
{
  setLevelAndVersion(sedmlLevel, sedmlVersion);

  createSEDMLDocument(dataModel, modelLocation);

  return writeSedMLToString();
}


void CSEDMLExporter::setLevelAndVersion(unsigned int sedmlLevel, unsigned int sedmlVersion)
{
  this->mSEDMLLevel = sedmlLevel;
  this->mSEDMLVersion = sedmlVersion;
}

std::string
createUniqueModelFileName(const std::string& dir,
                          const std::string& baseName,
                          const std::string& extension = ".xml")
{
  int count = 1;
  std::string current = baseName + extension;

  while (CDirEntry::exist(dir + CDirEntry::Separator + current))
    {
      std::stringstream temp;
      temp << baseName << count << extension;
      current = temp.str();
      ++count;
    }

  return current;
}

/**
 * Export the model and Task to SEDML.
 * The SEDML document is written to the file given by SEDMLFilename and
 * reference SBML model is written to SBMLFilename .
 * If the export fails, false is returned.
 */
bool
CSEDMLExporter::exportModelAndTasks(
  CDataModel& dataModel,
  const std::string& filename,
  const std::string& sbmlDocument,
  unsigned int sedmlLevel,
  unsigned int sedmlVersion,
  bool overwrite)
{
  bool success = true;
  /* create a string that represents the SBMLDocument */

  // std::string sedmlModelSource = "model1.xml"; //always name of the SBML model to reference in SEDML document
  // create a unique name for all exported models, rather than to overwrite existing ones!
  std::string sedmlModelSource = createUniqueModelFileName(CDirEntry::dirName(filename), "model", ".xml");

  std::string sbmlFileName;
  sbmlFileName = CDirEntry::dirName(filename) + CDirEntry::Separator + sedmlModelSource;

  std::ifstream sbmlFile(CLocaleString::fromUtf8(sbmlFileName).c_str(), std::ios::in);

  if (sbmlFile && !overwrite)
    {
      // create a CCopasiMessage with the appropriate error
      CCopasiMessage(CCopasiMessage::ERROR, MCDirEntry + 1, sbmlFileName.c_str());
      return false;
    }

  /* write the sbml model document to a file */
  std::ofstream sbmlOutFile(CLocaleString::fromUtf8(sbmlFileName).c_str(), std::ios::out | std::ios::trunc);
  sbmlOutFile << sbmlDocument;
  sbmlOutFile.close();

  std::string str = exportModelAndTasksToString(dataModel, sedmlModelSource, sedmlLevel, sedmlVersion);


  if (!str.empty())
    {
      /* check if the file already exists.
       If yes, write if overwrite is true,
       else create an appropriate  CCopasiMessage. */
      std::ifstream testInfile(CLocaleString::fromUtf8(filename).c_str(), std::ios::in);

      if (testInfile && !overwrite)
        {
          // create a CCopasiMessage with the appropriate error
          CCopasiMessage(CCopasiMessage::ERROR, MCDirEntry + 1, filename.c_str());
          return false;
        }

      /* write the document to a file */
      std::ofstream outfile(CLocaleString::fromUtf8(filename).c_str(), std::ios::out | std::ios::trunc);
      outfile << str;
      outfile.close();
    }
  else
    {
      /* if no SBMLDocument could be created return false */
      success = false;
    }

  return success;
}

LIBSEDML_CPP_NAMESPACE::SedDocument *
CSEDMLExporter::createSEDMLDocument(CDataModel& dataModel, std::string modelRef)
{
  clearMaps();

  mpSEDMLDocument = new SedDocument(mSEDMLLevel, mSEDMLVersion);

  createModel(dataModel, modelRef);
  createTasks(dataModel);

  return mpSEDMLDocument;
}


void CSEDMLExporter::clearMaps()
{
  mGeneratedIds.clear();
}

bool CSEDMLExporter::exportNthScanItem(CScanProblem * pProblem,
                                       size_t n,
                                       SedRepeatedTask * task,
                                       CDataModel & dataModel)
{
  CCopasiParameterGroup * current = pProblem->getScanItem(n);
  CScanProblem::Type type = (CScanProblem::Type)(current->getParameter("Type")->getValue< unsigned C_INT32 >());

  // ignore random items
  if (type == CScanProblem::SCAN_RANDOM)
    {
      CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: This version of COPASI cannot export random scan items, they will be ignored.");
      return false;
    }

  int numSteps = (current->getParameter("Number of steps")->getValue< unsigned C_INT32 >());

  // handle repeats
  if (type == CScanProblem::SCAN_REPEAT)
    {
      SedUniformRange * range = task->createUniformRange();
      SEDML_SET_ID(range, SEDMLUtils::getNextId("range", task->getNumRanges()));
      range->setStart(0);
      range->setEnd(numSteps);
      range->setNumberOfPoints(numSteps);
      range->setType("linear");

      task->setRangeId(range->getId());

      return true;
    }

  // handle scans
  if (type == CScanProblem::SCAN_LINEAR)
    {
      double min = (current->getParameter("Minimum")->getValue< C_FLOAT64 >());
      double max = (current->getParameter("Maximum")->getValue< C_FLOAT64 >());
      bool log = (current->getParameter("log")->getValue< bool >());
      std::string values = current->getParameter("Values") != NULL ? current->getParameter("Values")->getValue< std::string >() : std::string("");

      std::string rangeId = SEDMLUtils::getNextId("range", task->getNumRanges());

      if (current->getParameter("Use Values") != NULL && current->getParameter("Use Values")->getValue< bool >() && !values.empty())
        {
          SedVectorRange * range = task->createVectorRange();
          SEDML_SET_ID(range, rangeId);
          rangeId = range->getId();
          std::vector< std::string > elems;
          ResultParser::split(values, std::string(",; |\n\t\r"), elems);

for (std::string & number : elems)
            {
              range->addValue(ResultParser::saveToDouble(number));
            }
        }
      else
        {
          SedUniformRange * range = task->createUniformRange();
          SEDML_SET_ID(range, rangeId);
          rangeId = range->getId();
          range->setStart(min);
          range->setEnd(max);
          range->setNumberOfPoints(numSteps);
          range->setType(log ? "log" : "linear");
        }

      const CRegisteredCommonName & cn = (current->getParameter("Object")->getValue< CCommonName >());
      const CDataObject * pObject = static_cast< const CDataObject * >(dataModel.getObject(cn));

      if (pObject == NULL)
        {
          CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: This version of COPASI cannot export the selected scan object, it will be ignored.");
          return false;
        }

      std::string xpath = SEDMLUtils::getXPathForObject(*pObject);

      if (xpath.empty())
        {
          CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: This version of COPASI cannot export the selected scan object, it will be ignored.");
          return false;
        }

      SedSetValue * change = task->createTaskChange();
      change->setModelReference(mModelId);

      if (xpath == SEDML_TIME_URN)
        {
          change->setSymbol(xpath);
        }
      else
        {
          change->setTarget(xpath);
        }

      change->setRange(rangeId);
      change->setMath(SBML_parseFormula(rangeId.c_str()));
      task->setRangeId(rangeId);
      return true;
    }

  return false;
}


bool CSEDMLExporter::getExportExecutableTasksOnly() const
{
  return mExportExecutableTasksOnly;
}


void CSEDMLExporter::setExportExecutableTasksOnly(bool val)
{
  mExportExecutableTasksOnly = val;
}


bool CSEDMLExporter::getExportActivePlotsOnly() const
{
  return mExportActivePlotsOnly;
}


void CSEDMLExporter::setExportActivePlotsOnly(bool val)
{
  mExportActivePlotsOnly = val;
}

bool CSEDMLExporter::getExportSpecificPlots() const
{
  return mExportSpecificPlots;
}


void CSEDMLExporter::setExportSpecificPlots(bool val)
{
  mExportSpecificPlots = val;
}


const std::string & CSEDMLExporter::getModelId() const
{
  return mModelId;
}

void CSEDMLExporter::setModelId(const std::string & val)
{
  mModelId = val;
}

void CSEDMLExporter::freeSedMLDocument()
{
  clearMaps();
  pdelete(mpSEDMLDocument);
}

/**
 * Creates the simulations for SEDML.
 */
std::string
CSEDMLExporter::createScanTask(CDataModel& dataModel)
{
  // need L1V2 to export repeated tasks
  if (mpSEDMLDocument->getVersion() < 2)
    return "";

  CScanTask* pTask =  dynamic_cast<CScanTask*>(&dataModel.getTaskList()->operator[]("Scan"));

  if (pTask == NULL)
    return "";

  CScanProblem* pProblem = dynamic_cast<CScanProblem*>(pTask->getProblem());
  int numItems = (int)pProblem->getNumberOfScanItems();

  if (numItems == 0)
    return "";

  if (pProblem->getSubtask() != CTaskEnum::Task::steadyState &&
      pProblem->getSubtask() != CTaskEnum::Task::timeCourse)
    {
      CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: This version of COPASI only allows the export of time course or steady state scans.");
      return "";
    }

  std::string subTaskId;

  if (pProblem->getSubtask() == CTaskEnum::Task::steadyState)
    {
      subTaskId = createSteadyStateTask(dataModel);
    }
  else
    {
      subTaskId = mpTimecourseTask->getId();
    }

  SedRepeatedTask* task = mpSEDMLDocument->createRepeatedTask();
  std::string taskId = SEDMLUtils::getNextId("task", mpSEDMLDocument->getNumTasks());
  SEDML_SET_ID(task, taskId);
  task->setResetModel(!pProblem->getContinueFromCurrentState());

  // create subtask
  SedSubTask * subTask = task->createSubTask();
  subTask->setOrder(1);
  subTask->setTask(subTaskId);

  // create first range
  bool result = exportNthScanItem(pProblem, numItems - 1, task, dataModel);

  std::string lastTaskId = task->getId();

  // create remaining ranges / changes as new repeated task
  for (int i = numItems - 2; i >= 0 ; --i)
    {

      task = mpSEDMLDocument->createRepeatedTask();
      std::string nestedId = SEDMLUtils::getNextId("task", mpSEDMLDocument->getNumTasks());
      SEDML_SET_ID(task, nestedId);
      task->setResetModel(!pProblem->getContinueFromCurrentState());

      // create subtask
      SedSubTask * subTask = task->createSubTask();
      subTask->setOrder(1);
      subTask->setTask(lastTaskId);

      // export range
      exportNthScanItem(pProblem, i, task, dataModel);

      // update last task id for nesting
      lastTaskId = task->getId();
    }

  return taskId;
}

/**
 * Creates the simulations for SEDML.
 */
std::string
CSEDMLExporter::createTimeCourseTask(CDataModel& dataModel)
{
  CCopasiTask* pTask = &dataModel.getTaskList()->operator[]("Time-Course");
  CTrajectoryProblem* tProblem = static_cast<CTrajectoryProblem*>(pTask->getProblem());

  mpTimecourse = mpSEDMLDocument->createUniformTimeCourse();
  SEDML_SET_ID(mpTimecourse, SEDMLUtils::getNextId("sim", mpSEDMLDocument->getNumSimulations()));

  //presently SEDML only supports time course
  mpTimecourse->setInitialTime(dataModel.getModel()->getInitialTime());
  double outputStartTime = tProblem->getOutputStartTime();
  double stepSize = tProblem->getStepSize();
  int stepNumber = (int)tProblem->getStepNumber();
  mpTimecourse->setOutputStartTime(outputStartTime);
  mpTimecourse->setOutputEndTime(tProblem->getDuration());

  if (outputStartTime > 0)
    {
      // adjust number of points, as the definition in COPASI includes the
      // interval (0, timeEnd), while in SED-ML it is (timeStart, timeEnd)
      int initialSteps = (int)floor(outputStartTime / stepSize);
      mpTimecourse->setNumberOfPoints(stepNumber - initialSteps);
    }
  else
    {
      mpTimecourse->setNumberOfPoints(stepNumber);
    }

  // set the correct KISAO Term
  SedAlgorithm * alg = mpTimecourse->createAlgorithm();
  const CCopasiMethod * pMethod = pTask->getMethod();

  exportAlgorithm(alg, pMethod);

  mpTimecourseTask = mpSEDMLDocument->createTask();
  std::string taskId = SEDMLUtils::getNextId("task", mpSEDMLDocument->getNumTasks());
  SEDML_SET_ID(mpTimecourseTask, taskId);
  mpTimecourseTask->setSimulationReference(mpTimecourse->getId());
  mpTimecourseTask->setModelReference(mModelId);

  return taskId;
}


void
CSEDMLExporter::exportAlgorithm(SedAlgorithm * alg,
                                const CCopasiMethod * pMethod)
{
  if (pMethod == NULL)
    return;

  alg->setName(pMethod->getObjectName());

  switch (pMethod->getSubType())
    {
      case CTaskEnum::Method::deterministic:
        alg->setKisaoID("KISAO:0000560");
        break;

      case CTaskEnum::Method::RADAU5:
        alg->setKisaoID("KISAO:0000304");
        break;

      case CTaskEnum::Method::LSODA2:
        alg->setKisaoID("KISAO:0000560");
        break;

      case CTaskEnum::Method::directMethod:
        alg->setKisaoID("KISAO:0000029");
        break;

      case CTaskEnum::Method::stochastic:
        alg->setKisaoID("KISAO:0000027");
        break;

      case CTaskEnum::Method::tauLeap:
        alg->setKisaoID("KISAO:0000039");
        break;

      case CTaskEnum::Method::adaptiveSA:
        alg->setKisaoID("KISAO:0000048");
        break;

      case CTaskEnum::Method::hybrid:
        alg->setKisaoID("KISAO:0000561");
        break;

      case CTaskEnum::Method::hybridLSODA:
        alg->setKisaoID("KISAO:0000562");
        break;

      case CTaskEnum::Method::hybridODE45:
        alg->setKisaoID("KISAO:0000563");
        break;

      case CTaskEnum::Method::stochasticRunkeKuttaRI5:
        alg->setKisaoID("KISAO:0000566");
        break;

      default:
        CCopasiMessage(CCopasiMessage::WARNING, "No KIASO term for the method. %s defaulting to KISAO:0000019", pMethod->getObjectName().c_str());
        alg->setKisaoID("KISAO:0000019");
        break;
    }

for (const auto & entry : SEDMLUtils::PARAMETER_KISAO_MAP)
    {
      const CCopasiParameter * pParameter = pMethod->getParameter(entry.second);

      if (pParameter)
        {
          SedAlgorithmParameter * pSedParam = alg->createAlgorithmParameter();
          pSedParam->setKisaoID(entry.first);
          pSedParam->setName(entry.second);
          pSedParam->setValue(getParameterValueAsString(pParameter));
        }
    }

  /*if (pMethod->getObjectName().find("Stochastic") != std::string::npos)
    alg->setKisaoID("KISAO:0000241");
  else
    alg->setKisaoID("KISAO:0000019");*/
}

/**
 * Creates the simulations for SEDML.
 */
std::string CSEDMLExporter::createSteadyStateTask(CDataModel& dataModel)
{
  SedSteadyState *steady  = mpSEDMLDocument->createSteadyState();
  SEDML_SET_ID(steady, SEDMLUtils::getNextId("steady", mpSEDMLDocument->getNumSimulations()));
  //presently SEDML only supports time course
  CCopasiTask* pTask = &dataModel.getTaskList()->operator[]("Steady-State");
  CTrajectoryProblem* tProblem = static_cast<CTrajectoryProblem*>(pTask->getProblem());

  // set the correct KISAO Term
  SedAlgorithm* alg = steady->createAlgorithm();
  alg->setKisaoID("KISAO:0000282");

  SedTask *task = this->mpSEDMLDocument->createTask();
  std::string taskId = SEDMLUtils::getNextId("task", mpSEDMLDocument->getNumTasks());
  SEDML_SET_ID(task, taskId);
  task->setSimulationReference(steady->getId());
  task->setModelReference(mModelId);

  return taskId;
}

/**
 * Creates the models for SEDML.
 */
std::string
CSEDMLExporter::createModel(CDataModel& dataModel, const std::string & modelRef)
{
  SedModel *model = this->mpSEDMLDocument->createModel();
  SEDML_SET_ID(model, CDirEntry::baseName(modelRef));
  model->setSource(modelRef);
  model->setLanguage("urn:sedml:language:sbml");

  setModelId(model->getId());

  return model->getId();
}

/**
 * Creates the Tasks for SEDML. This will always create a task running a time course
 * simulation. If the parameter scan has been specified, it will be exported as well.
 */
void CSEDMLExporter::createTasks(CDataModel & dataModel)
{
  // create time course task
  CCopasiTask *pTask = &dataModel.getTaskList()->operator[]("Time-Course");
  std::string taskId;

  if (!mExportExecutableTasksOnly || pTask->isScheduled())
    {
      taskId = createTimeCourseTask(dataModel);
      createDataGenerators(dataModel, taskId, pTask);
    }

  // export Scan Task
  pTask = &dataModel.getTaskList()->operator[]("Scan");

  if (!mExportExecutableTasksOnly || pTask->isScheduled())
    {
      taskId = createScanTask(dataModel);

      if (!taskId.empty())
        createDataGenerators(dataModel, taskId, pTask);
    }
}

SedDataGenerator *
CSEDMLExporter::createDataGenerator(
  const std::string &sbmlId,
  const std::string &targetXPathString,
  const std::string& taskId,
  size_t i,
  size_t j)
{
  SedDataGenerator *pPDGen = mpSEDMLDocument->createDataGenerator();
  SEDML_SET_ID(pPDGen, sbmlId << "_" << j + 1 << "_" << taskId);

  pPDGen->setName(sbmlId);

  SedVariable * pPVar = pPDGen->createVariable();
  SEDML_SET_ID(pPVar, "p" << i + 1 << "_" << pPDGen->getName() << "_" << taskId);
  pPVar->setTaskReference(taskId);
  pPVar->setName(pPDGen->getName());

  pPDGen->setMath(SBML_parseFormula(pPVar->getId().c_str()));

  if (targetXPathString == SEDML_TIME_URN)
    {
      pPVar->setSymbol(targetXPathString);
    }
  else
    {
      pPVar->setTarget(targetXPathString);
    }

  return pPDGen;
}


std::string
CSEDMLExporter::getParameterValueAsString(const CCopasiParameter * pParameter)
{
  if (pParameter == NULL)
    return "";

  std::ostringstream str;

  switch (pParameter->getType())
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        str << pParameter->getValue< C_FLOAT64 >();
        break;

      case CCopasiParameter::Type::INT:
        str << pParameter->getValue< C_INT32 >();
        break;

      case CCopasiParameter::Type::UINT:
        str << pParameter->getValue< unsigned C_INT32 >();
        break;

      case CCopasiParameter::Type::BOOL:
        str << pParameter->getValue< bool >() ? "true" : "false";
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::CN:
        str << pParameter->getValue< std::string >();
        break;

      default:
        // ignore for now
        break;
    }

  return str.str();
}

/**
 * Creates the data generators for SEDML.
 */
void
CSEDMLExporter::createDataGenerators(CDataModel & dataModel,
                                     std::string & taskId,
                                     CCopasiTask* task)
{
  const CModel* pModel = dataModel.getModel();
  std::vector<std::string> stringsContainer; //split string container

  if (pModel == NULL)
    CCopasiMessage(CCopasiMessage::ERROR, "SED-ML: No model for this SED-ML document. An SBML model must exist for every SED-ML document.");

  //create generator for special variable time
  const CDataObject* pTime = static_cast<const CDataObject *>(dataModel.getModel()->getObject(CCommonName("Reference=Time")));
  SedDataGenerator *pTimeDGenp = this->mpSEDMLDocument->createDataGenerator();
  SEDML_SET_ID(pTimeDGenp, "time_" << taskId);
  pTimeDGenp->setName(pTime->getObjectName());
  SedVariable *pTimeVar = pTimeDGenp->createVariable();
  SEDML_SET_ID(pTimeVar, "var_time_" << taskId);
  pTimeVar->setTaskReference(taskId);
  pTimeVar->setSymbol(SEDML_TIME_URN);
  pTimeDGenp->setMath(SBML_parseFormula(pTimeVar->getId().c_str()));

  size_t i, imax = dataModel.getPlotDefinitionList()->size();
  SedDataGenerator *pPDGen;

  if (imax == 0 && (task == NULL || task->getReport().getTarget().empty()))
    CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: No plot/report definition for this SED-ML document.");

  // export report
  if (task != NULL && !task->getReport().getTarget().empty())
    {
      const CReportDefinition* def = task->getReport().getReportDefinition();

      if (def != NULL)
        {
          SedReport* pReport = mpSEDMLDocument->createReport();
          std::string name = def->getObjectName();
          SEDMLUtils::removeCharactersFromString(name, "[]");
          //
          SEDML_SET_ID(pReport, "report" << "_" << taskId);
          pReport->setName(name);

          std::vector<CRegisteredCommonName> header = *def->getHeaderAddr();
          std::vector<CRegisteredCommonName> body =
            def->isTable() ? *def->getTableAddr() :
            *def->getBodyAddr();

          int dsCount = 0;

          for (size_t i = 0; i < body.size(); ++i)
            {
              CRegisteredCommonName& current = body[i];

              if (current == def->getSeparator().getCN()) continue;

              const CDataObject *object = CObjectInterface::DataObject(dataModel.getObjectFromCN(current));

              if (object == NULL) continue;

              std::string xAxis = SEDMLUtils::getSbmlId(*object);
              std::string targetXPathStringX;

              if (!xAxis.empty())
                targetXPathStringX = SEDMLUtils::getXPathForObject(*object);

              if (targetXPathStringX.empty())
                {
                  const std::string& typeX = object->getObjectName();
                  xAxis = object->getObjectDisplayName();

                  targetXPathStringX = SEDMLUtils::getXPathAndName(xAxis, typeX,
                                       pModel, dataModel);

                  if (targetXPathStringX.empty())
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export report '%s' variable '%s', as no xpath expression for it could be generated.", name.c_str(), object->getObjectDisplayName().c_str());
                      continue;
                    }
                }

              if (object->getCN() == pTime->getCN())
                pPDGen = pTimeDGenp;
              else
                pPDGen = createDataGenerator(
                           xAxis,
                           targetXPathStringX,
                           taskId,
                           i,
                           0
                         );

              SedDataSet* pDS = pReport->createDataSet();
              SEDML_SET_ID(pDS, "ds_" << ++dsCount << "_" << taskId);

              if (def->isTable())
                {
                  const CDataObject *headerObj = NULL;

                  if (header.size() > i)
                    headerObj = CObjectInterface::DataObject(dataModel.getObjectFromCN(header[i]));
                  else
                    headerObj = CObjectInterface::DataObject(dataModel.getObjectFromCN(body[i]));

                  if (headerObj != NULL)
                    pDS->setLabel(headerObj->getObjectDisplayName());
                  else
                    pDS->setLabel(xAxis);
                }
              else
                pDS->setLabel(xAxis);

              pDS->setDataReference(pPDGen->getId());
            }
        }
    }

  // export plots
  SedPlot2D* pPSedPlot;
  SedCurve* pCurve; // = pPSedPlot->createCurve();

  for (i = 0; i < imax; i++)
    {
      const CPlotSpecification* pPlot = &dataModel.getPlotDefinitionList()->operator[](i);

      if (mExportActivePlotsOnly && !pPlot->isActive())
        continue; // ignore deactivated plots

      if (mExportSpecificPlots && !pPlot->appliesTo(task))
        continue; // ignore plots that don't apply to this task

      pPSedPlot = this->mpSEDMLDocument->createPlot2D();
      std::string plotName = pPlot->getObjectName();

      SEDMLUtils::removeCharactersFromString(plotName, "[]");

      SEDML_SET_ID(pPSedPlot, "plot_" << mpSEDMLDocument->getNumOutputs()
                   << "_" << taskId);
      pPSedPlot->setName(plotName);

      size_t j, jmax = pPlot->getItems().size();

      for (j = 0; j < jmax; j++)
        {
          const CPlotItem* pPlotItem = & pPlot->getItems()[j];

          const CDataObject *objectX, *objectY;

          if (!pPlotItem->getChannels().empty())
            {
              objectX = CObjectInterface::DataObject(dataModel.getObjectFromCN(pPlotItem->getChannels()[0]));
            }
          else
            {
              CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export plotItem '%s', as it has no data channel.", pPlotItem->getObjectName().c_str());
              continue;
            }

          if (objectX == NULL)
            {
              CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export plotItem '%s' variable '%s', as it cannot be resolved.",  pPlotItem->getObjectName().c_str(), pPlotItem->getChannels()[0].c_str());
              continue;
            }

          bool xIsTime = objectX->getCN() == pTime->getCN();

          if (pPlotItem->getChannels().size() >= 2)
            {
              objectY = CObjectInterface::DataObject(dataModel.getObjectFromCN(pPlotItem->getChannels()[1]));
            }
          else
            {
              CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export plotItem '%s', as it has only 1 data channel.", pPlotItem->getObjectName().c_str());
              continue;
            }

          if (objectY == NULL)
            {
              CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export plotItem '%s' variable '%s', as it cannot be resolved.",  pPlotItem->getObjectName().c_str(), pPlotItem->getChannels()[1].c_str());
              continue;
            }

          const std::string& type = objectY->getObjectName();

          std::string yAxis = objectY->getObjectDisplayName();

          std::string sbmlId = SEDMLUtils::getSbmlId(*objectY);
          std::string targetXPathString;

          if (!sbmlId.empty())
            targetXPathString = SEDMLUtils::getXPathForObject(*objectY);

          if (targetXPathString.empty())
            {
              sbmlId = yAxis;

              targetXPathString = SEDMLUtils::getXPathAndName(sbmlId, type,
                                  pModel, dataModel);

              if (targetXPathString.empty())
                {
                  CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export plotItem '%s' variable '%s', as no xpath expression for it could be generated.", pPlotItem->getObjectName().c_str(), pPlotItem->getChannels()[1].c_str());
                  continue;
                }
            }

          pPDGen = createDataGenerator(
                     sbmlId,
                     targetXPathString,
                     taskId,
                     i,
                     j
                   );

          pPDGen->setName(yAxis);

          pCurve = pPSedPlot->createCurve();
          SEDML_SET_ID(pCurve, "p" << i + 1 << "_curve_" << j + 1 << "_" << taskId);
          pCurve->setLogX(pPlot->isLogX());
          pCurve->setLogY(pPlot->isLogY());
          pCurve->setName(yAxis);
          pCurve->setYDataReference(pPDGen->getId());

          if (xIsTime)
            {
              pCurve->setXDataReference(pTimeDGenp->getId());
            }
          else
            {
              const std::string& typeX = objectX->getObjectName();
              std::string xAxis = objectX->getObjectDisplayName();
              std::string targetXPathStringX = SEDMLUtils::getXPathAndName(xAxis, typeX,
                                               pModel, dataModel);

              pPDGen = createDataGenerator(
                         xAxis,
                         targetXPathStringX,
                         taskId,
                         i,
                         j
                       );
              pCurve->setXDataReference(pPDGen->getId());
            }
        }
    }
}

CSEDMLExporter::CSEDMLExporter()
  : mpSEDMLDocument(NULL)
  , mSEDMLLevel(1)
  , mSEDMLVersion(2)
  , mpTimecourse(NULL)
  , mpTimecourseTask(NULL)
  , mGeneratedIds()
  , mExportExecutableTasksOnly(false)
  , mExportActivePlotsOnly(true)
  , mExportSpecificPlots(false)
  , mModelId()
{

}

CSEDMLExporter::~CSEDMLExporter()
{

}

LIBSEDML_CPP_NAMESPACE::SedDocument * CSEDMLExporter::getSEDMLDocument()
{
  return mpSEDMLDocument;
}

std::string CSEDMLExporter::writeSedMLToString() const
{
  SedWriter writer;

  writer.setProgramName("COPASI");
  writer.setProgramVersion(CVersion::VERSION.getVersion());

  return writer.writeSedMLToStdString(mpSEDMLDocument);
}

bool CSEDMLExporter::writeSedMLToFile(const std::string & filename) const
{
  SedWriter writer;

  writer.setProgramName("COPASI");
  writer.setProgramVersion(CVersion::VERSION.getVersion());

  return writer.writeSedMLToFile(mpSEDMLDocument, filename);
}
