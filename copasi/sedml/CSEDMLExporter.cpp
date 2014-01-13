// Copyright (C) 2013 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "CopasiDataModel/CCopasiDataModel.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CModelValue.h"
#include "commandline/CLocaleString.h"

const std::string CSEDMLExporter::exportModelAndTasksToString(CCopasiDataModel& dataModel,
    std::string &sbmlModelSource,
    unsigned int sedmlLevel,
    unsigned int sedmlVersion)
{
  this->mSEDMLLevel = sedmlLevel;
  this->mSEDMLVersion = sedmlVersion;
  this->createSEDMLDocument(dataModel, sbmlModelSource);

  CSBMLExporter exporter;
  SedWriter* writer = new SedWriter();

  writer->setProgramName("COPASI");
  writer->setProgramVersion(CVersion::VERSION.getVersion().c_str());

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
bool CSEDMLExporter::exportModelAndTasks(CCopasiDataModel& dataModel,
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

void CSEDMLExporter::createSEDMLDocument(CCopasiDataModel& dataModel, std::string modelRef)
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
std::string CSEDMLExporter::createScanTask(CCopasiDataModel& dataModel, const std::string & modelId)
{
  // need L1V2 to export repeated tasks
  if (mpSEDMLDocument->getVersion() != 2) return "";

  CScanTask* pTask =  dynamic_cast<CScanTask*>((*dataModel.getTaskList())["Scan"]);

  if (pTask == NULL) return "";

  CScanProblem* pProblem = dynamic_cast<CScanProblem*>(pTask->getProblem());
  size_t numItems = pProblem->getNumberOfScanItems();

  if (numItems == 0)
    return "";

  if (pProblem->getSubtask() != CCopasiTask::steadyState &&
      pProblem->getSubtask() != CCopasiTask::timeCourse)
    {
      CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI only allows the export of time course or steady state scans.");
      return "";
    }

  std::string subTaskId;

  if (pProblem->getSubtask() == CCopasiTask::steadyState)
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

  // craete ranges / changes
  for (size_t i = 0; i < numItems; ++i)
    {
      CCopasiParameterGroup* current = pProblem->getScanItem(i);
      CScanProblem::Type type = (CScanProblem::Type)(*current->getParameter("Type")->getValue().pUINT);

      // ignore random items
      if (type == CScanProblem::SCAN_RANDOM)
        {
          CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI cannot export random scan items, they will be ignored.");
          continue;
        }

      int numSteps = (*current->getParameter("Number of steps")->getValue().pUINT);

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
          double min = (*current->getParameter("Minimum")->getValue().pDOUBLE);
          double max = (*current->getParameter("Maximum")->getValue().pDOUBLE);
          bool log = (*current->getParameter("log")->getValue().pBOOL);

          SedUniformRange *range = task->createUniformRange();
          range->setId(SEDMLUtils::getNextId("range", task->getNumRanges()));
          range->setStart(min);
          range->setEnd(max);
          range->setNumberOfPoints(numSteps);
          range->setType(log ? "log" : "linear");

          const CRegisteredObjectName& cn = (*current->getParameter("Object")->getValue().pCN);
          std::string xpath = SEDMLUtils::getXPathForObject(*static_cast<const CCopasiObject*>(dataModel.getObject(cn)));

          if (xpath.empty())
            {
              CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI cannot export the selected scan object, it will be ignored.");
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
std::string CSEDMLExporter::createTimeCourseTask(CCopasiDataModel& dataModel, const std::string & modelId)
{
  mpTimecourse = this->mpSEDMLDocument->createUniformTimeCourse();
  mpTimecourse->setId(SEDMLUtils::getNextId("sim", mpSEDMLDocument->getNumSimulations()));
  //presently SEDML only supports time course
  CCopasiTask* pTask = (*dataModel.getTaskList())["Time-Course"];
  CTrajectoryProblem* tProblem = static_cast<CTrajectoryProblem*>(pTask->getProblem());
  mpTimecourse->setInitialTime(0.0);
  mpTimecourse->setOutputStartTime(tProblem->getOutputStartTime());
  mpTimecourse->setOutputEndTime(tProblem->getStepNumber()*tProblem->getStepSize());
  mpTimecourse->setNumberOfPoints(tProblem->getStepNumber());

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
std::string CSEDMLExporter::createSteadyStateTask(CCopasiDataModel& dataModel, const std::string & modelId)
{
  SedSteadyState *steady  = this->mpSEDMLDocument->createSteadyState();
  steady->setId(SEDMLUtils::getNextId("steady", mpSEDMLDocument->getNumSimulations()));
  //presently SEDML only supports time course
  CCopasiTask* pTask = (*dataModel.getTaskList())["Steady-State"];
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
void CSEDMLExporter::createModels(CCopasiDataModel& dataModel, std::string & modelRef)
{
  SedModel *model = this->mpSEDMLDocument->createModel();
  model->setId(modelRef.substr(0, modelRef.length() - 4));
  model->setSource(modelRef);
  model->setLanguage("urn:sedml:language:sbml");
}

/**
 * Creates the Tasks for SEDML. This will always create a task running a time course
 * simulation. If the parameter scan has been specified, it will be exported as well.
 */
void CSEDMLExporter::createTasks(CCopasiDataModel& dataModel, std::string & modelRef)
{
  std::string modelId = modelRef.substr(0, modelRef.length() - 4);
  // create time course task
  std::string taskId = createTimeCourseTask(dataModel, modelId);
  createDataGenerators(dataModel, taskId);

  taskId = createScanTask(dataModel, modelId);

  if (!taskId.empty())
    createDataGenerators(dataModel, taskId);
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
  std::ostringstream idStrStream;
  idStrStream << sbmlId;
  idStrStream << "_";
  idStrStream << j + 1;
  pPDGen->setId(idStrStream.str());

  pPDGen->setName(sbmlId);

  SedVariable * pPVar = pPDGen->createVariable();
  std::ostringstream idVarStrStream;
  idVarStrStream << "p";
  idVarStrStream << i + 1;
  idVarStrStream << "_";
  idVarStrStream << pPDGen->getName();
  pPVar->setId(idVarStrStream.str());
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

std::string getXPathAndName(std::string& yAxis, const std::string &type,
                            const CModel *pModel, const CCopasiDataModel& dataModel,
                            std::vector<std::string>& stringsContainer)
{
  std::string targetXPathString;
  char delim;
  SEDMLUtils utils;

  if (type == "Concentration")
    {
      targetXPathString = "/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id=\'";
      //remove unwanted characters from the plot item object name
      char concChars[] = "[]";

      for (unsigned int ii = 0; ii < strlen(concChars); ++ii)
        {
          yAxis.erase(std::remove(yAxis.begin(), yAxis.end(), concChars[ii]), yAxis.end());
        }

      CCopasiVector<CMetab>::const_iterator it = pModel->getMetabolites().begin(), endit = pModel->getMetabolites().end();
      const std::map<CCopasiObject*, SBase*>& copasi2sbmlmap = const_cast<CCopasiDataModel&>(dataModel).getCopasi2SBMLMap();
      std::map<CCopasiObject*, SBase*>::const_iterator pos;
      const Species* pSBMLSpecies = NULL;

      while (it != endit)
        {
          pos = copasi2sbmlmap.find(*it);

          if (pos != copasi2sbmlmap.end())
            {
              pSBMLSpecies = dynamic_cast<const Species*>(pos->second);
              std::string name = pSBMLSpecies->getName();

              if (name.compare(yAxis) == 0)
                {
                  //    std::cout<<"Name: "<<pSBMLSpecies->getName()<<std::endl;
                  yAxis = pSBMLSpecies->getId();
                }
            }

          ++it;
        }
    }
  else if (type == "Flux")
    {
      targetXPathString = "/sbml:sbml/sbml:model/sbml:listOfReactions/sbml:reaction[@id=\'";
      delim = ')';
      utils.splitStrings(yAxis, delim, stringsContainer);
      yAxis = stringsContainer[0];

      char fluxChars[] = "(";

      for (unsigned int ii = 0; ii < strlen(fluxChars); ++ii)
        {
          yAxis.erase(std::remove(yAxis.begin(), yAxis.end(), fluxChars[ii]), yAxis.end());
        }

      CCopasiVector<CReaction>::const_iterator it = pModel->getReactions().begin(), endit = pModel->getReactions().end();
      const std::map<CCopasiObject*, SBase*>& copasi2sbmlmap = const_cast<CCopasiDataModel&>(dataModel).getCopasi2SBMLMap();
      std::map<CCopasiObject*, SBase*>::const_iterator pos;
      const Reaction* pSBMLReaction = NULL;

      while (it != endit)
        {
          pos = copasi2sbmlmap.find(*it);

          if (pos != copasi2sbmlmap.end())
            {
              pSBMLReaction = dynamic_cast<const Reaction*>(pos->second);
              std::string name = pSBMLReaction->getName();

              if (name.compare(yAxis) == 0)
                {
                  yAxis = pSBMLReaction->getId();
                }
            }

          ++it;
        }
    }
  else if (type == "Value")
    {
      targetXPathString = "/sbml:sbml/sbml:model/sbml:listOfParameters/sbml:parameter[@id=\'";
      delim = '[';
      utils.splitStrings(yAxis, delim, stringsContainer);
      yAxis = stringsContainer[1];

      char valueChars[] = "]";

      for (unsigned int ii = 0; ii < strlen(valueChars); ++ii)
        {
          yAxis.erase(std::remove(yAxis.begin(), yAxis.end(), valueChars[ii]), yAxis.end());
        }

      CCopasiVector<CModelValue>::const_iterator it = pModel->getModelValues().begin(), endit = pModel->getModelValues().end();
      const std::map<CCopasiObject*, SBase*>& copasi2sbmlmap = const_cast<CCopasiDataModel&>(dataModel).getCopasi2SBMLMap();
      std::map<CCopasiObject*, SBase*>::const_iterator pos;
      const Parameter* pSBMLParameter = NULL;

      while (it != endit)
        {
          pos = copasi2sbmlmap.find(*it);

          if (pos != copasi2sbmlmap.end())
            {
              pSBMLParameter =
                dynamic_cast<const Parameter*>(pos->second);
              std::string name = pSBMLParameter->getName();

              if (name.compare(yAxis) == 0)
                {
                  yAxis = pSBMLParameter->getId();
                }
            }

          ++it;
        }
    }
  else if (type == "Time")
    return "urn:sedml:symbol:time";

  return targetXPathString;
}

SedDataGenerator * createDataGenerator(
  SedDocument* mpSEDMLDocument,
  const std::string &yAxis,
  const std::string &targetXPathString,
  const std::string& taskId,
  size_t i,
  size_t j)
{
  SedDataGenerator *pPDGen = mpSEDMLDocument->createDataGenerator();
  std::ostringstream idStrStream;
  idStrStream << yAxis;
  idStrStream << "_";
  idStrStream << j + 1;
  pPDGen->setId(idStrStream.str());

  pPDGen->setName(yAxis);

  SedVariable * pPVar = pPDGen->createVariable();
  std::ostringstream idVarStrStream;
  idVarStrStream << "p";
  idVarStrStream << i + 1;
  idVarStrStream << "_";
  idVarStrStream << pPDGen->getName();
  pPVar->setId(idVarStrStream.str());
  pPVar->setTaskReference(taskId);
  pPVar->setName(pPDGen->getName());

  pPDGen->setMath(SBML_parseFormula(pPVar->getId().c_str()));

  if (targetXPathString == "urn:sedml:symbol:time")
    {
      pPVar->setSymbol(targetXPathString);
    }
  else
    {
      //temporary method to set XPath target
      std::ostringstream targetStrStream;
      targetStrStream << targetXPathString;
      targetStrStream << pPVar->getName();
      targetStrStream << "\']";
      pPVar->setTarget(targetStrStream.str());
    }

  return pPDGen;
}

/**
 * Creates the data generators for SEDML.
 */
void CSEDMLExporter::createDataGenerators(CCopasiDataModel & dataModel, std::string & taskId)
{
  const CModel* pModel = dataModel.getModel();
  std::vector<std::string> stringsContainer; //split string container

  if (pModel == NULL)
    CCopasiMessage(CCopasiMessage::ERROR, "No model for this SEDML document. An SBML model must exist for every SEDML document.");

  SedPlot2D* pPSedPlot;
  SedCurve* pCurve; // = pPSedPlot->createCurve();

  //create generator for special varibale time
  const CCopasiObject* pTime = static_cast<const CCopasiObject *>(dataModel.getModel()->getObject(CCopasiObjectName("Reference=Time")));
  SedDataGenerator *pTimeDGenp = this->mpSEDMLDocument->createDataGenerator();
  pTimeDGenp->setId("time");
  pTimeDGenp->setName(pTime->getObjectName());
  SedVariable *pTimeVar = pTimeDGenp->createVariable();
  pTimeVar->setId("var_time");
  pTimeVar->setTaskReference(taskId);
  pTimeVar->setSymbol(SEDML_TIME_URN);
  pTimeDGenp->setMath(SBML_parseFormula(pTimeVar->getId().c_str()));

  size_t i, imax = dataModel.getPlotDefinitionList()->size();
  SedDataGenerator *pPDGen;

  if (!imax)
    CCopasiMessage(CCopasiMessage::ERROR, "No plot definition for this SEDML document.");

  for (i = 0; i < imax; i++)
    {
      pPSedPlot = this->mpSEDMLDocument->createPlot2D();
      const CPlotSpecification* pPlot = (*dataModel.getPlotDefinitionList())[i];
      std::string plotName = pPlot->getObjectName();

      SEDMLUtils::removeCharactersFromString(plotName, "[]");

      pPSedPlot->setId(SEDMLUtils::getNextId("plot", mpSEDMLDocument->getNumOutputs()));
      pPSedPlot->setName(plotName);

      size_t j, jmax = pPlot->getItems().size();

      for (j = 0; j < jmax; j++)
        {
          const CPlotItem* pPlotItem = pPlot->getItems()[j];

          CCopasiObject *objectX, *objectY;

          if (pPlotItem->getChannels().size() >= 1)
            objectX = dataModel.getDataObject(pPlotItem->getChannels()[0]);

          bool xIsTime = objectX->getCN() == pTime->getCN();

          if (pPlotItem->getChannels().size() >= 2)
            objectY = dataModel.getDataObject(pPlotItem->getChannels()[1]);

          const std::string& type = objectY->getObjectName();
          std::string yAxis = objectY->getObjectDisplayName();
          std::string targetXPathString = SEDMLUtils::getXPathAndName(yAxis, type,
                                          pModel, dataModel);

          if (targetXPathString.empty())
            {
              continue;
            }

          pPDGen = createDataGenerator(
                     this->mpSEDMLDocument,
                     yAxis,
                     targetXPathString,
                     taskId,
                     i,
                     j
                   );

          pCurve = pPSedPlot->createCurve();
          std::ostringstream idCurveStrStream;
          idCurveStrStream << "p";
          idCurveStrStream << i + 1;
          idCurveStrStream << "_curve_";
          idCurveStrStream << j + 1;
          pCurve->setId(idCurveStrStream.str());
          pCurve->setLogX(pPlot->isLogX());
          pCurve->setLogY(pPlot->isLogY());
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
