// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
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
#include <tuple>

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

CSEDMLExporter::CSEDMLExporter()
  : mpSEDMLDocument(NULL)
  , mSEDMLLevel(1)
  , mSEDMLVersion(4)
  , mpTimecourse(NULL)
  , mpTimecourseTask(NULL)
  , mGeneratedIds()
  , mExportExecutableTasksOnly(false)
  , mExportActivePlotsOnly(true)
  , mExportSpecificPlots(true)
  , mModelId()
  , mpSBMLNamespaces(NULL)
  , mDataGenerators()
  , mpDataModel(NULL)
  , mpCurrentTask(NULL)
  , mpCurrentPlot(NULL)
  , mpCurrentPlot3D(NULL)
  , mpCurrentSpec(NULL)
  , mStyleMap()
{
}

CSEDMLExporter::~CSEDMLExporter()
{
  pdelete(mpSBMLNamespaces);
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

  if (mpSBMLNamespaces)
    {
      mpSEDMLDocument->getSedNamespaces()->addNamespaces(mpSBMLNamespaces);
    }

  setDataModel(&dataModel);

  createModel(modelRef);
  createTasks();

  return mpSEDMLDocument;
}

void CSEDMLExporter::clearMaps()
{
  mGeneratedIds.clear();
  mDataGenerators.clear();
  mStyleMap.clear();

  mpCurrentTime = NULL;
  mpCurrentPlot = NULL;
  mpCurrentTask = NULL;
  mCurrentTaskId = "";
}

bool CSEDMLExporter::exportNthScanItem(CScanProblem * pProblem,
                                       size_t n,
                                       SedRepeatedTask * task)
{
  if (!mpDataModel || !pProblem)
    return false;

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
      const CDataObject * pObject = static_cast< const CDataObject * >(mpDataModel->getObject(cn));

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

void CSEDMLExporter::setSBMLNamespaces(int level, int version, const std::string & prefix)
{
  pdelete(mpSBMLNamespaces);
  mpSBMLNamespaces = new XMLNamespaces();
  mpSBMLNamespaces->add(SBMLNamespaces::getSBMLNamespaceURI(level, version), prefix);
}

/**
 * Creates the simulations for SEDML.
 */
std::string
CSEDMLExporter::createScanTask()
{
  if (!mpDataModel)
    return "";

  // need L1V2 to export repeated tasks
  if (mpSEDMLDocument->getVersion() < 2)
    return "";

  CScanTask* pTask =  dynamic_cast<CScanTask*>(&mpDataModel->getTaskList()->operator[]("Scan"));

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
      subTaskId = createSteadyStateTask();
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
  bool result = exportNthScanItem(pProblem, numItems - 1, task);

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
      exportNthScanItem(pProblem, i, task);

      // update last task id for nesting
      lastTaskId = task->getId();
    }

  return lastTaskId;
}

/**
 * Creates the simulations for SEDML.
 */
std::string
CSEDMLExporter::createTimeCourseTask()
{
  if (!mpDataModel)
    return "";

  CCopasiTask* pTask = &mpDataModel->getTaskList()->operator[]("Time-Course");
  CTrajectoryProblem* tProblem = static_cast<CTrajectoryProblem*>(pTask->getProblem());

  mpTimecourse = mpSEDMLDocument->createUniformTimeCourse();
  SEDML_SET_ID(mpTimecourse, SEDMLUtils::getNextId("sim", mpSEDMLDocument->getNumSimulations()));

  double initialTime = mpDataModel->getModel()->getInitialTime();
  mpTimecourse->setInitialTime(initialTime);
  bool Delayed;

  if (tProblem->getStepSize() > 0.0)
    Delayed = (tProblem->getOutputStartTime() - initialTime) > std::numeric_limits< C_FLOAT64 >::min();
  else
    Delayed = (initialTime - tProblem->getOutputStartTime()) > std::numeric_limits< C_FLOAT64 >::min();

  double outputStartTime = initialTime;

  if (Delayed)
    outputStartTime += tProblem->getOutputStartTime();

  double stepSize = tProblem->getStepSize();
  int stepNumber = (int)tProblem->getStepNumber();
  mpTimecourse->setOutputStartTime(outputStartTime);
  mpTimecourse->setOutputEndTime(initialTime + tProblem->getDuration());

  if ((outputStartTime - initialTime) > 0)
    {
      // adjust number of points, as the definition in COPASI includes the
      // interval (0, timeEnd), while in SED-ML it is (timeStart, timeEnd)
      int initialSteps = (int)floor((outputStartTime - initialTime) / stepSize);
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
          auto value = getParameterValueAsString(pParameter);

          // skip 0 maximum step size since there are tools
          // that interpret that value literally.
          if (entry.first == "KISAO:0000467" && value == "0")
            continue;

          SedAlgorithmParameter * pSedParam = alg->createAlgorithmParameter();
          pSedParam->setKisaoID(entry.first);
          pSedParam->setName(entry.second);
          pSedParam->setValue(value);
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
std::string CSEDMLExporter::createSteadyStateTask()
{
  if (!mpDataModel || !mpSEDMLDocument)
    return "";

  SedSteadyState *steady  = mpSEDMLDocument->createSteadyState();
  SEDML_SET_ID(steady, SEDMLUtils::getNextId("steady", mpSEDMLDocument->getNumSimulations()));
  //presently SEDML only supports time course
  CCopasiTask* pTask = &mpDataModel->getTaskList()->operator[]("Steady-State");
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
CSEDMLExporter::createModel(const std::string & modelRef)
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
void CSEDMLExporter::createTasks()
{
  if (!mpDataModel)
    return;

  // create time course task
  CCopasiTask *pTask = &mpDataModel->getTaskList()->operator[]("Time-Course");
  std::string taskId;

  if (!mExportExecutableTasksOnly || pTask->isScheduled())
    {
      taskId = createTimeCourseTask();
      createDataGenerators(taskId, pTask);
    }

  // export Scan Task
  pTask = &mpDataModel->getTaskList()->operator[]("Scan");

  if (!mExportExecutableTasksOnly || pTask->isScheduled())
    {
      taskId = createScanTask();

      if (!taskId.empty())
        createDataGenerators(taskId, pTask);
    }
}

void CSEDMLExporter::setSBMLNamespaces(const XMLNamespaces & sbmlns)
{
  pdelete(mpSBMLNamespaces);
  mpSBMLNamespaces = new XMLNamespaces(sbmlns);
}

SedDataGenerator *
CSEDMLExporter::createDataGenerator(
  const VariableInfo& info,
  const std::string& taskId,
  size_t i,
  size_t j)
{
  auto key = std::make_pair(taskId, info);
  auto it = mDataGenerators.find(key);

  if (it != mDataGenerators.end())
    return it->second;

  SedDataGenerator *pPDGen = mpSEDMLDocument->createDataGenerator();
  SEDML_SET_ID(pPDGen, info.getSbmlId() << "_" << j + 1 << "_" << taskId);

  pPDGen->setName(info.getName());

  SedVariable * pPVar = info.addToDataGenerator(pPDGen);
  SEDML_SET_ID(pPVar, "p" << i + 1 << "_" << pPDGen->getId());

  pPVar->setTaskReference(taskId);

  pPDGen->setMath(SBML_parseFormula(pPVar->getId().c_str()));

  mDataGenerators[key] = pPDGen;

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
        str << (pParameter->getValue< bool >() ? "true" : "false");
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

void
CSEDMLExporter::exportReport(const CReportDefinition * def)
{
  if (def == NULL || mpDataModel == NULL)
    return;

  SedDataGenerator * pPDGen;
  SedReport * pReport = mpSEDMLDocument->createReport();
  std::string name = def->getObjectName();
  SEDMLUtils::removeCharactersFromString(name, "[]");
  //
  SEDML_SET_ID(pReport, "report"
               << "_" << mCurrentTaskId);
  pReport->setName(name);

  std::vector< CRegisteredCommonName > header = *def->getHeaderAddr();
  std::vector< CRegisteredCommonName > body =
    def->isTable() ? *def->getTableAddr() : *def->getBodyAddr();

  int dsCount = 0;

  for (size_t i = 0; i < body.size(); ++i)
    {
      CRegisteredCommonName & current = body[i];

      if (current == def->getSeparator().getCN())
        continue;

      const CDataObject * object = CObjectInterface::DataObject(mpDataModel->getObjectFromCN(current));

      if (object == NULL)
        continue;

      auto info = VariableInfo(object);

      if (!info.isValid())
        {
          CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export report '%s' variable '%s', as no xpath expression for it could be generated.", name.c_str(), object->getObjectDisplayName().c_str());
        }

      if (object->getCN() == mTimeCN)
        pPDGen = mpCurrentTime;
      else
        pPDGen = createDataGenerator(
                   info,
                   mCurrentTaskId,
                   i,
                   0);

      SedDataSet * pDS = pReport->createDataSet();
      SEDML_SET_ID(pDS, "ds_" << ++dsCount << "_" << mCurrentTaskId);

      if (def->isTable())
        {
          const CDataObject * headerObj = NULL;

          if (header.size() > i)
            headerObj = CObjectInterface::DataObject(mpDataModel->getObjectFromCN(header[i]));
          else
            headerObj = CObjectInterface::DataObject(mpDataModel->getObjectFromCN(body[i]));

          if (headerObj != NULL)
            pDS->setLabel(headerObj->getObjectDisplayName());
          else
            pDS->setLabel(info.getName());
        }
      else
        pDS->setLabel(info.getName());

      pDS->setDataReference(pPDGen->getId());
    }
}

/**
 * Creates the data generators for SEDML.
 */
void
CSEDMLExporter::createDataGenerators(std::string & taskId,
                                     CCopasiTask* task)
{
  if (!mpDataModel || !task)
    return;

  mCurrentTaskId = taskId;
  mpCurrentTask = task;

  const CModel* pModel = mpDataModel->getModel();
  std::vector<std::string> stringsContainer; //split string container

  if (pModel == NULL)
    CCopasiMessage(CCopasiMessage::ERROR, "SED-ML: No model for this SED-ML document. An SBML model must exist for every SED-ML document.");

  size_t i, imax = mpDataModel->getPlotDefinitionList()->size();

  if (imax == 0 && (task == NULL || task->getReport().getTarget().empty()))
    CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: No plot/report definition for this SED-ML document.");

  //create generator for special variable time
  setCurrentTime(taskId);

  // export report if we have one
  if (task != NULL && !task->getReport().getTarget().empty())
    {
      const CReportDefinition* def = task->getReport().getReportDefinition();
      exportReport(def);
    }

  // export plots
  for (i = 0; i < imax; i++)
    {
      const CPlotSpecification* pPlot = &mpDataModel->getPlotDefinitionList()->operator[](i);
      exportNthPlot(pPlot, i);
    }
}

void
CSEDMLExporter::exportNthPlot(const CPlotSpecification * pPlot,
                              size_t i)
{
  if (!pPlot || !mpDataModel)
    return;

  if (mExportActivePlotsOnly && !pPlot->isActive())
    return; // ignore deactivated plots

  if (mExportSpecificPlots && !pPlot->appliesTo(mpCurrentTask))
    return; // ignore plots that don't apply to this task

  mpCurrentSpec = pPlot;
  mpCurrentPlot = mpSEDMLDocument->createPlot2D();
  mpCurrentPlot3D = NULL;

  std::string plotName = pPlot->getObjectName();
  SEDMLUtils::removeCharactersFromString(plotName, "[]");

  SEDML_SET_ID(mpCurrentPlot, "plot_" << mpSEDMLDocument->getNumOutputs()
               << "_" << mCurrentTaskId);
  mpCurrentPlot->setName(plotName);

  size_t j, jmax = pPlot->getItems().size();

  for (j = 0; j < jmax; j++)
    {
      const CPlotItem * pPlotItem = &pPlot->getItems()[j];
      exportPlotItem(pPlotItem, i, j);
    }

  if (mpCurrentPlot3D != NULL && mpCurrentPlot->getNumCurves() == 0)
    {
      // if the plot had only a contour remove the plot without curves
      std::string id = mpCurrentPlot->getId();
      delete mpSEDMLDocument->removeOutput(id);
      mpCurrentPlot3D->setId(id);
    }
}

void CSEDMLExporter::exportPlotItem(const CPlotItem * pPlotItem, size_t i, size_t j)
{
  if (!pPlotItem || !mpCurrentSpec || !mpDataModel)
    return;

  // first resolve all elements needed
  std::vector< std::pair< const CDataObject *, VariableInfo > > resolvedElements;

for (auto & channel : pPlotItem->getChannels())
    {
      const CDataObject * object = CObjectInterface::DataObject(mpDataModel->getObjectFromCN(channel));

      if (!object)
        {
          CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export plotItem '%s' variable '%s', as it cannot be resolved.", pPlotItem->getObjectName().c_str(), channel.c_str());
          return;
        }

      auto info = VariableInfo(object);

      if (!info.isValid())
        {
          CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export plotItem '%s' variable '%s', as no xpath expression for it could be generated.", pPlotItem->getObjectName().c_str(), channel.c_str());
          return;
        }

      resolvedElements.push_back(std::make_pair(object, info));
    }

  if (pPlotItem->getChannels().size() < 2)
    {
      CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export plotItem '%s', as it has no data channels.", pPlotItem->getObjectName().c_str());
      return;
    }

  switch (pPlotItem->getType())
    {
      case CPlotItem::curve2d:
      {
        SedCurve * pCurve = mpCurrentPlot->createCurve();
        SEDML_SET_ID(pCurve, "p" << i + 1 << "_curve_" << j + 1 << "_" << mCurrentTaskId);
        pCurve->setLogX(mpCurrentSpec->isLogX());
        pCurve->setLogY(mpCurrentSpec->isLogY());
        pCurve->setName(pPlotItem->getObjectName());

        SedDataGenerator * pDG = createDataGenerator(
                                   resolvedElements[0].second,
                                   mCurrentTaskId,
                                   i,
                                   j);

        pCurve->setXDataReference(pDG->getId());

        pDG = createDataGenerator(
                resolvedElements[1].second,
                mCurrentTaskId,
                i,
                j);

        pCurve->setYDataReference(pDG->getId());
        pCurve->setStyle(exportStyleForItem(pPlotItem));
      }
      break;

      case CPlotItem::bandedGraph:
      {
        SedShadedArea * pCurve = mpCurrentPlot->createShadedArea();
        SEDML_SET_ID(pCurve, "p" << i + 1 << "_curve_" << j + 1 << "_" << mCurrentTaskId);
        pCurve->setLogX(mpCurrentSpec->isLogX());
        pCurve->setName(pPlotItem->getObjectName());

        SedDataGenerator * pDG = createDataGenerator(
                                   resolvedElements[0].second,
                                   mCurrentTaskId,
                                   i,
                                   j);
        pCurve->setXDataReference(pDG->getId());

        pDG = createDataGenerator(
                resolvedElements[1].second,
                mCurrentTaskId,
                i,
                j);
        pCurve->setYDataReferenceFrom(pDG->getId());

        pDG = createDataGenerator(
                resolvedElements[2].second,
                mCurrentTaskId,
                i,
                j);
        pCurve->setYDataReferenceTo(pDG->getId());
        pCurve->setStyle(exportStyleForItem(pPlotItem));
      }
      break;

      case CPlotItem::spectogram:
      {
        // need 3d plot here
        if (mpCurrentPlot3D == NULL)
          {
            mpCurrentPlot3D = mpSEDMLDocument->createPlot3D();
            mpCurrentPlot3D->setId(mpCurrentPlot->getId() + "_3d");
            mpCurrentPlot3D->setName(mpCurrentPlot->getName());
            mGeneratedIds.insert(mpCurrentPlot->getId() + "_3d");
          }

        SedSurface * pCurve = mpCurrentPlot3D->createSurface();
        pCurve->setType(SEDML_SURFACETYPE_CONTOUR);
        pCurve->setName(pPlotItem->getObjectName());
        pCurve->setLogX(mpCurrentSpec->isLogX());
        pCurve->setLogY(mpCurrentSpec->isLogY());

        SedDataGenerator * pDG = createDataGenerator(
                                   resolvedElements[0].second, mCurrentTaskId, i, j
                                 );
        pCurve->setXDataReference(pDG->getId());

        pDG = createDataGenerator(
                resolvedElements[1].second, mCurrentTaskId, i, j);
        pCurve->setYDataReference(pDG->getId());

        pDG = createDataGenerator(
                resolvedElements[2].second, mCurrentTaskId, i, j);
        pCurve->setZDataReference(pDG->getId());

        pCurve->setStyle(exportStyleForItem(pPlotItem));
      }
      break;

      default :
        CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export plotItem '%s', because it has an unsupported type.", pPlotItem->getObjectName().c_str());
        return;
    }
}

std::string CSEDMLExporter::exportStyleForItem(const CPlotItem * pPlotItem)
{
  if (!pPlotItem || !mpSEDMLDocument || mSEDMLVersion < 4)
    return "";

  if (pPlotItem->getType() == CPlotItem::spectogram) // no styles for contours
    return "";

  auto it = mStyleMap.find(pPlotItem);

  if (it != mStyleMap.end())
    return it->second;

  auto style = mpSEDMLDocument->createStyle();
  SEDML_SET_ID(style, SEDMLUtils::getNextId("style", mpSEDMLDocument->getNumStyles()));

  auto lineWidth = pPlotItem->getValue< C_FLOAT64 >("Line width");
  auto lineType = (CPlotItem::LineType) pPlotItem->getValue< unsigned C_INT32 >("Line type");
  auto symbolType = (CPlotItem::SymbolType) pPlotItem->getValue< unsigned C_INT32 >("Symbol subtype");
  auto lineStyle = (CPlotItem::LineStyle) pPlotItem->getValue< unsigned C_INT32 >("Line subtype");
  auto color = pPlotItem->getValue< std::string >("Color");
  auto rgba = SEDMLUtils::argbToRgba(color, false);
  bool haveColor = !color.empty() && color != "auto";
  bool haveSymbols = lineType == CPlotItem::LineType::LinesAndSymbols || lineType == CPlotItem::LineType::Symbols;

  auto line = style->createLineStyle();

  if (lineType == CPlotItem::LineType::Points)
    {
      line->setType(SEDML_LINETYPE_NONE);
      auto symbol = style->createMarkerStyle();
      symbol->setType(SEDML_MARKERTYPE_CIRCLE);
      symbol->setSize(0.1);

      if (haveColor)
        symbol->setLineColor(rgba);
    }
  else
    {
      line->setType((LineType_t) SEDMLUtils::lineTypeToSed((int) lineStyle));
      line->setThickness(lineWidth);

      if (haveColor)
        line->setColor(rgba);
    }

  auto symbol = style->createMarkerStyle();

  if (haveSymbols)
    {
      symbol->setType((MarkerType_t) SEDMLUtils::symbolToSed((int) symbolType));
      symbol->setSize(8);

      if (haveColor)
        symbol->setLineColor(rgba);
    }
  else
    {
      symbol->setType(SEDML_MARKERTYPE_NONE);
    }

  if (pPlotItem->getType() == CPlotItem::bandedGraph && haveColor)
    {
      auto fill = style->createFillStyle();
      fill->setColor(SEDMLUtils::argbToRgba(color, false));
    }

  mStyleMap[pPlotItem] = style->getId();

  return style->getId();
}

void CSEDMLExporter::setCurrentTime(std::string & taskId)
{
  if (!mpDataModel)
    return;

  const CDataObject * pTime = static_cast< const CDataObject * >(mpDataModel->getModel()->getObject(CCommonName("Reference=Time")));
  mTimeCN = pTime->getCN();
  auto it = mDataGenerators.find(std::make_pair(taskId, VariableInfo(pTime)));

  if (it != mDataGenerators.end())
    mpCurrentTime = it->second;
  else
    {
      mpCurrentTime = this->mpSEDMLDocument->createDataGenerator();
      SEDML_SET_ID(mpCurrentTime, "time_" << taskId);
      mpCurrentTime->setName(pTime->getObjectName());
      SedVariable * pTimeVar = mpCurrentTime->createVariable();
      SEDML_SET_ID(pTimeVar, "var_time_" << taskId);
      pTimeVar->setTaskReference(taskId);
      pTimeVar->setSymbol(SEDML_TIME_URN);
      mpCurrentTime->setMath(SBML_parseFormula(pTimeVar->getId().c_str()));
    }
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

bool CSEDMLExporter::KeyComparer::operator()(const TaskVarKey & lhs, const TaskVarKey & rhs) const
{
  if (lhs.first != rhs.first)
    return lhs.first < rhs.first;

  return lhs.second < rhs.second;
}

CDataModel* CSEDMLExporter::getDataModel()
{
  return mpDataModel;
}

void CSEDMLExporter::setDataModel(CDataModel* pDataModel)
{
  mpDataModel = pDataModel;
}

bool CSEDMLExporter::PlotItemStyleComparer::operator()(const CPlotItem* lhs, const CPlotItem* rhs) const
{
  return
    std::tie(
      lhs->getValue< C_FLOAT64 >("Line width"),
      lhs->getValue< unsigned C_INT32 >("Line type"),
      lhs->getValue< unsigned C_INT32 >("Symbol subtype"),
      lhs->getValue< unsigned C_INT32 >("Line subtype"),
      lhs->getValue< std::string >("Color")
    )

    <

    std::tie
    (
      rhs->getValue< C_FLOAT64 >("Line width"),
      rhs->getValue< unsigned C_INT32 >("Line type"),
      rhs->getValue< unsigned C_INT32 >("Symbol subtype"),
      rhs->getValue< unsigned C_INT32 >("Line subtype"),
      rhs->getValue< std::string >("Color")
    );
}
