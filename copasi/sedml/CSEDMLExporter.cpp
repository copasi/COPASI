// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "sbml/CSBMLExporter.h"
#include "CSEDMLExporter.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "scan/CScanTask.h"
#include "scan/CScanProblem.h"
#include "utilities/CCopasiException.h"
#include "utilities/CVersion.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CDirEntry.h"
#include "CopasiDataModel/CDataModel.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "report/CReportDefinition.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CModelValue.h"
#include "commandline/CLocaleString.h"

#define SEDML_SET_ID(element, arguments) \
  {\
    std::ostringstream idStream; idStream << arguments;\
    element->setId(idStream.str());\
  }

const std::string CSEDMLExporter::exportModelAndTasksToString(CDataModel& dataModel,
    const std::string &modelLocation,
    unsigned int sedmlLevel,
    unsigned int sedmlVersion)
{
  this->mSEDMLLevel = sedmlLevel;
  this->mSEDMLVersion = sedmlVersion;
  this->createSEDMLDocument(dataModel, modelLocation);

  CSBMLExporter exporter;
  SedWriter* writer = new SedWriter();

  writer->setProgramName("COPASI");
  writer->setProgramVersion(CVersion::VERSION.getVersion());

  char* d = writer->writeToString(this->mpSEDMLDocument);
  std::string returnValue = d;

  if (d) free(d);

  pdelete(writer);

  return returnValue;
}

std::string createUniqueModelFileName(const std::string& dir, const std::string& baseName, const std::string& extension = ".xml")
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
 * The SEDML document is written to the file given by SEDMLFilename and reference SBML model is written to SBMLFilename .
 * If the export fails, false is returned.
 */
bool CSEDMLExporter::exportModelAndTasks(CDataModel& dataModel,
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

  std::string str = this->exportModelAndTasksToString(dataModel, sedmlModelSource, sedmlLevel, sedmlVersion);

  //std::cout<<str<<std::endl; //only for debuging

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

void CSEDMLExporter::createSEDMLDocument(CDataModel& dataModel, std::string modelRef)
{
  const SedDocument* pOldSEDMLDocument = NULL; //dataModel.getCurrentSEDMLDocument();
  const CModel* pModel = dataModel.getModel();
  COutputDefinitionVector *plotDef = dataModel.getPlotDefinitionList();
  assert(plotDef != NULL); //need to emit a message
  assert(pModel != NULL);

  if (pOldSEDMLDocument == NULL)
    {
      this->mpSEDMLDocument = new SedDocument(mSEDMLLevel, mSEDMLVersion);
    }
  else
    {
      this->mpSEDMLDocument = dynamic_cast<SedDocument*>(pOldSEDMLDocument->clone());
    }

  if (this->mpSEDMLDocument == NULL) fatalError();

  createModels(dataModel, modelRef);
  createTasks(dataModel,  modelRef);
}

/**
 * Creates the simulations for SEDML.
 */
std::string
CSEDMLExporter::createScanTask(CDataModel& dataModel, const std::string & modelId)
{
  // need L1V2 to export repeated tasks
  if (mpSEDMLDocument->getVersion() != 2)
    return "";

  CScanTask* pTask =  dynamic_cast<CScanTask*>(&dataModel.getTaskList()->operator[]("Scan"));

  if (pTask == NULL)
    return "";

  CScanProblem* pProblem = dynamic_cast<CScanProblem*>(pTask->getProblem());
  size_t numItems = pProblem->getNumberOfScanItems();

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
      subTaskId = createSteadyStateTask(dataModel, modelId);
    }
  else
    {
      subTaskId = mpTimecourseTask->getId();
    }

  SedRepeatedTask* task = mpSEDMLDocument->createRepeatedTask();
  std::string taskId = SEDMLUtils::getNextId("task", mpSEDMLDocument->getNumTasks());
  task->setId(taskId);
  task->setResetModel(!pProblem->getContinueFromCurrentState());

  // create ranges / changes
  for (size_t i = 0; i < numItems; ++i)
    {
      CCopasiParameterGroup* current = pProblem->getScanItem(i);
      CScanProblem::Type type = (CScanProblem::Type)(current->getParameter("Type")->getValue< unsigned C_INT32 >());

      // ignore random items
      if (type == CScanProblem::SCAN_RANDOM)
        {
          CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: This version of COPASI cannot export random scan items, they will be ignored.");
          continue;
        }

      int numSteps = (current->getParameter("Number of steps")->getValue< unsigned C_INT32 >());

      // handle repeats
      if (type == CScanProblem::SCAN_REPEAT)
        {
          SedUniformRange *range = task->createUniformRange();
          range->setId(SEDMLUtils::getNextId("range", task->getNumRanges()));
          range->setStart(0);
          range->setEnd(numSteps);
          range->setNumberOfPoints(numSteps);
          range->setType("linear");

          if (task->isSetRangeId())
            task->setRangeId(range->getId());

          continue;
        }

      // handle scans
      if (type == CScanProblem::SCAN_LINEAR)
        {
          double min = (current->getParameter("Minimum")->getValue< C_FLOAT64 >());
          double max = (current->getParameter("Maximum")->getValue< C_FLOAT64 >());
          bool log = (current->getParameter("log")->getValue< bool >());

          SedUniformRange *range = task->createUniformRange();
          range->setId(SEDMLUtils::getNextId("range", task->getNumRanges()));
          range->setStart(min);
          range->setEnd(max);
          range->setNumberOfPoints(numSteps);
          range->setType(log ? "log" : "linear");

          const CRegisteredCommonName& cn = (current->getParameter("Object")->getValue< CCommonName >());
          const CDataObject* pObject = static_cast<const CDataObject*>(dataModel.getObject(cn));

          if (pObject == NULL)
            {
              CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: This version of COPASI cannot export the selected scan object, it will be ignored.");
              continue;
            }

          std::string xpath = SEDMLUtils::getXPathForObject(*pObject);

          if (xpath.empty())
            {
              CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: This version of COPASI cannot export the selected scan object, it will be ignored.");
              continue;
            }

          SedSetValue *change = task->createTaskChange();
          change->setModelReference(modelId);

          if (xpath == SEDML_TIME_URN)
            {
              change->setSymbol(xpath);
            }
          else
            {
              change->setTarget(xpath);
            }

          change->setRange(range->getId());
          change->setMath(SBML_parseFormula(range->getId().c_str()));

          continue;
        }
    }

  if (!task->isSetRangeId() && task->getNumRanges() > 0)
    task->setRangeId(task->getRange(0)->getId());

  // create subtask
  SedSubTask* subTask = task->createSubTask();
  subTask->setOrder(1);
  subTask->setTask(subTaskId);

  return taskId;
}

/**
 * Creates the simulations for SEDML.
 */
std::string CSEDMLExporter::createTimeCourseTask(CDataModel& dataModel, const std::string & modelId)
{
  mpTimecourse = this->mpSEDMLDocument->createUniformTimeCourse();
  mpTimecourse->setId(SEDMLUtils::getNextId("sim", mpSEDMLDocument->getNumSimulations()));
  //presently SEDML only supports time course
  CCopasiTask* pTask = &dataModel.getTaskList()->operator[]("Time-Course");
  CTrajectoryProblem* tProblem = static_cast<CTrajectoryProblem*>(pTask->getProblem());
  mpTimecourse->setInitialTime(0.0);
  double outputStartTime = tProblem->getOutputStartTime();
  double stepSize = tProblem->getStepSize();
  int stepNumber = (int)tProblem->getStepNumber();
  mpTimecourse->setOutputStartTime(outputStartTime);
  mpTimecourse->setOutputEndTime(stepNumber * stepSize);

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
  SedAlgorithm* alg = mpTimecourse->createAlgorithm();

  if (pTask->getMethod()->getObjectName().find("Stochastic") != std::string::npos)
    alg->setKisaoID("KISAO:0000241");
  else
    alg->setKisaoID("KISAO:0000019");

  mpTimecourseTask = this->mpSEDMLDocument->createTask();
  std::string taskId = SEDMLUtils::getNextId("task", mpSEDMLDocument->getNumTasks());
  mpTimecourseTask->setId(taskId);
  mpTimecourseTask->setSimulationReference(mpTimecourse->getId());
  mpTimecourseTask->setModelReference(modelId);

  return taskId;
}

/**
 * Creates the simulations for SEDML.
 */
std::string CSEDMLExporter::createSteadyStateTask(CDataModel& dataModel, const std::string & modelId)
{
  SedSteadyState *steady  = this->mpSEDMLDocument->createSteadyState();
  steady->setId(SEDMLUtils::getNextId("steady", mpSEDMLDocument->getNumSimulations()));
  //presently SEDML only supports time course
  CCopasiTask* pTask = &dataModel.getTaskList()->operator[]("Steady-State");
  CTrajectoryProblem* tProblem = static_cast<CTrajectoryProblem*>(pTask->getProblem());

  // set the correct KISAO Term
  SedAlgorithm* alg = steady->createAlgorithm();
  alg->setKisaoID("KISAO:0000282");

  SedTask *task = this->mpSEDMLDocument->createTask();
  std::string taskId = SEDMLUtils::getNextId("task", mpSEDMLDocument->getNumTasks());
  task->setId(taskId);
  task->setSimulationReference(steady->getId());
  task->setModelReference(modelId);

  return taskId;
}

/**
 * Creates the models for SEDML.
 */
void CSEDMLExporter::createModels(CDataModel& dataModel, std::string & modelRef)
{
  SedModel *model = this->mpSEDMLDocument->createModel();
  model->setId(CDirEntry::baseName(modelRef));
  model->setSource(modelRef);
  model->setLanguage("urn:sedml:language:sbml");
}

/**
 * Creates the Tasks for SEDML. This will always create a task running a time course
 * simulation. If the parameter scan has been specified, it will be exported as well.
 */
void CSEDMLExporter::createTasks(CDataModel& dataModel, std::string & modelRef)
{
  std::string modelId = CDirEntry::baseName(modelRef);
  // create time course task
  std::string taskId = createTimeCourseTask(dataModel, modelId);
  createDataGenerators(dataModel, taskId, &dataModel.getTaskList()->operator[]("Time-Course"));

  taskId = createScanTask(dataModel, modelId);

  if (!taskId.empty())
    createDataGenerators(dataModel, taskId, &dataModel.getTaskList()->operator[]("Scan"));
}

SedDataGenerator * createDataGenerator(
  SedDocument* mpSEDMLDocument,
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

/**
 * Creates the data generators for SEDML.
 */
void CSEDMLExporter::createDataGenerators(CDataModel & dataModel,
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
      CReportDefinition* def = task->getReport().getReportDefinition();

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

              const std::string& typeX = object->getObjectName();
              std::string xAxis = object->getObjectDisplayName();

              std::string targetXPathStringX = SEDMLUtils::getXPathAndName(xAxis, typeX,
                                               pModel, dataModel);

              if (object->getCN() == pTime->getCN())
                pPDGen = pTimeDGenp;
              else
                pPDGen = createDataGenerator(
                           this->mpSEDMLDocument,
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
      pPSedPlot = this->mpSEDMLDocument->createPlot2D();
      const CPlotSpecification* pPlot = &dataModel.getPlotDefinitionList()->operator[](i);
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

          std::string sbmlId = yAxis;

          std::string targetXPathString = SEDMLUtils::getXPathAndName(sbmlId, type,
                                          pModel, dataModel);

          if (targetXPathString.empty())
            {
              CCopasiMessage(CCopasiMessage::WARNING, "SED-ML: Can't export plotItem '%s' variable '%s', as no xpath expression for it could be generated.",  pPlotItem->getObjectName().c_str(), pPlotItem->getChannels()[1].c_str());
              continue;
            }

          pPDGen = createDataGenerator(
                     this->mpSEDMLDocument,
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
                         this->mpSEDMLDocument,
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
  , mpTimecourse(NULL)
  , mpTimecourseTask(NULL)
{
  // TODO Auto-generated constructor stub
}

CSEDMLExporter::~CSEDMLExporter()
{
  // TODO Auto-generated destructor stub
}
