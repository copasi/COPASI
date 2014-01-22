// Copyright (C) 2013 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * SEDMLImporter.cpp
 * $Rev:               $:  Revision of last commit
 * $Author:            $:  Author of last commit
 * $Date:              $:  Date of last commit
 * $HeadURL:       $
 * $Id:        $
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <limits>
#include <cmath>
#include <algorithm>

#include <sedml/SedTypes.h>
#include <sbml/math/FormulaFormatter.h>

#include "copasi.h"

#include "report/CKeyFactory.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "model/CModelValue.h"
#include "model/CEvent.h"
#include "function/CNodeK.h"
#include "function/CFunctionDB.h"
#include "function/CEvaluationTree.h"
#include "function/CExpression.h"
#include "function/CFunctionParameters.h"
#include "report/CCopasiObjectReference.h"
#include "utilities/CCopasiTree.h"
#include "utilities/CNodeIterator.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "MIRIAM/CRDFGraphConverter.h"
#include "compareExpressions/CEvaluationNodeNormalizer.h"
#include "commandline/CLocaleString.h"
#include "commandline/COptions.h"

#include "utilities/CProcessReport.h"
#include "copasi/commandline/CConfigurationFile.h"

#include "utilities/CCopasiMessage.h"

//TODO SEDML
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "sbml/SBMLImporter.h"
#include "utilities/CDirEntry.h"
#include "utilities/CCopasiException.h"
#include "utilities/CCopasiTask.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"

#include <steadystate/CSteadyStateTask.h>
#include <scan/CScanTask.h>

#include "SEDMLImporter.h"
#include "SEDMLUtils.h"

// static
C_FLOAT64 SEDMLImporter::round(const C_FLOAT64 & x)
{
  return
    x < 0.0 ? -floor(-x + 0.5) : floor(x + 0.5);
}

void SEDMLImporter::setImportHandler(CProcessReport* pHandler)
{mpImportHandler = pHandler;}

CProcessReport* SEDMLImporter::getImportHandlerAddr()
{return mpImportHandler;}

const std::string SEDMLImporter::getArchiveFileName()
{return mArchiveFileName;}

/**
 * Creates and returns a COPASI CTrajectoryTask from the SEDML simulation
 * given as argument.
 */
void SEDMLImporter::updateCopasiTaskForSimulation(SedSimulation* sedmlsim,
    std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap)
{

  switch (sedmlsim->getTypeCode())
    {
      case SEDML_SIMULATION_UNIFORMTIMECOURSE:
      {

        CTrajectoryTask *tTask = static_cast<CTrajectoryTask*>((*mpDataModel->getTaskList())["Time-Course"]);

        CTrajectoryProblem* tProblem = static_cast<CTrajectoryProblem*>(tTask->getProblem());
        SedUniformTimeCourse* tc = static_cast<SedUniformTimeCourse*>(sedmlsim);
        tProblem->setOutputStartTime(tc->getOutputStartTime());
        tProblem->setDuration(tc->getOutputEndTime() - tc->getOutputStartTime());
        tProblem->setStepNumber(tc->getNumberOfPoints());

        // TODO read kisao terms
        if (tc->isSetAlgorithm())
          {
            const SedAlgorithm* alg = tc->getAlgorithm();

            if (alg->isSetKisaoID())
              {
                if (alg->getKisaoID() == SEDML_KISAO_STOCHASTIC)
                  {
                    tTask->setMethodType(CCopasiMethod::stochastic);
                  }
              }
          }

        break;
      }

      case SEDML_SIMULATION_ONESTEP:
      {

        CTrajectoryTask *tTask = static_cast<CTrajectoryTask*>((*mpDataModel->getTaskList())["Time-Course"]);

        CTrajectoryProblem* tProblem = static_cast<CTrajectoryProblem*>(tTask->getProblem());
        SedOneStep* step = static_cast<SedOneStep*>(sedmlsim);
        tProblem->setOutputStartTime(0);
        tProblem->setDuration(step->getStep());
        tProblem->setStepNumber(1);

        // TODO read kisao terms

        break;
      }

      case SEDML_SIMULATION_STEADYSTATE:
      {
        // nothing to be done for this one
        CSteadyStateTask *tTask = static_cast<CSteadyStateTask*>((*mpDataModel->getTaskList())["Steady-State"]);

        // TODO read kisao terms
        //CCopasiProblem* tProblem = static_cast<CCopasiProblem*>(tTask->getProblem());
        //SedSteadyState* tc = static_cast<SedSteadyState*>(sedmlsim);

        break;
      }

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, "SEDMLImporter Error: encountered unknown simulation.");
        break;
    }
}

void SEDMLImporter::readListOfPlotsFromSedMLOutput(
  COutputDefinitionVector *pLotList, CModel* pModel,
  SedDocument *pSEDMLDocument,
  std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap)
{
  size_t i, numOutput = pSEDMLDocument->getNumOutputs();

  std::map<CCopasiObject*, SBase*>& copasiMap = pModel->getObjectDataModel()->getCopasi2SBMLMap();

  for (i = 0; i < numOutput; ++i)
    {
      SedOutput* current = pSEDMLDocument->getOutput(i);

      switch (current->getTypeCode())
        {
          case SEDML_OUTPUT_PLOT2D: //get the curves data
          {
            SedPlot2D* p = static_cast<SedPlot2D*>(current);
            std::string name = current->isSetName() ? current->getName() :
                               current->getId();
            CPlotSpecification* pPl = pLotList->createPlotSpec(
                                        name, CPlotItem::plot2d);

            int count = 0;

            while (pPl == NULL)
              {
                // creation fails on duplicated name!
                pPl = pLotList->createPlotSpec(
                        SEDMLUtils::getNextId(name + " ", ++count), CPlotItem::plot2d);
              }

            bool logX = false;
            bool logY = false;

            for (unsigned int ic = 0; ic < p->getNumCurves(); ++ic)
              {
                SedCurve *curve = p->getCurve(ic);

                std::string xDataReference = curve->getXDataReference();
                std::string yDataReference = curve->getYDataReference();

                const SedDataGenerator* xGenerator = pSEDMLDocument->getDataGenerator(xDataReference);
                const SedDataGenerator* yGenerator = pSEDMLDocument->getDataGenerator(yDataReference);

                const SedDataGenerator* xGenerator = pSEDMLDocument->getDataGenerator(xDataReference);
                const SedDataGenerator* yGenerator = pSEDMLDocument->getDataGenerator(yDataReference);

                //create the curves
                const CCopasiObject * tmpX = SEDMLUtils::resolveDatagenerator(pModel, xGenerator);
                const CCopasiObject * tmpY = SEDMLUtils::resolveDatagenerator(pModel, yGenerator);

                if (tmpX != NULL && tmpY != NULL)
                  {
                    std::string  itemTitle;

                    if (curve->isSetName())
                      itemTitle = curve->getName();
                    else if (yGenerator != NULL && yGenerator->isSetName())
                      itemTitle = yGenerator->getName();
                    else
                      itemTitle = tmpY->getObjectDisplayName();

                    CPlotItem * plItem = pPl->createItem(itemTitle, CPlotItem::curve2d);
                    plItem->setValue("Line width", 2.0);
                    plItem->addChannel(tmpX->getCN());
                    plItem->addChannel(tmpY->getCN());
                  }

                logX = logX || (curve->isSetLogX() && curve->getLogX());
                logY = logY || (curve->isSetLogY() && curve->getLogY());
              }

            pPl->setLogX(logX);
            pPl->setLogY(logY);
            break;
          }

          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, "SEDMLImporter Error: No support for this plot: typecode = %d", current->getTypeCode());
            break;
        }
    }
}

/**
 * Function reads an SEDML file with libsedml and converts it to a Copasi CModel
 */
CModel* SEDMLImporter::readSEDML(std::string filename,
                                 CProcessReport* pImportHandler,
                                 SBMLDocument *& pSBMLDocument,
                                 SedDocument*& pSedDocument,
                                 std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap,
                                 std::map<CCopasiObject*, SBase*>& copasi2sbmlmap,
                                 CListOfLayouts *& prLol,
                                 COutputDefinitionVector * &plotList,
                                 CCopasiDataModel* pDataModel)
{
  // convert filename to the locale encoding
  std::ifstream file(CLocaleString::fromUtf8(filename).c_str());

  if (!file)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSEDML + 5, filename.c_str());
    }

  std::ostringstream stringStream;
  char c;

  while (file.get(c))
    {
      stringStream << c;
    }

  file.clear();
  file.close();

  //using libzip to read SEDML file
  /*  SEDMLUtils utils;
  std::string SEDMLFileName, fileContent("");
  SEDMLFileName = "sedml.xml";

  int success = utils.processArchive(filename, SEDMLFileName, fileContent);*/

  pDataModel->setSEDMLFileName(filename);

  return this->parseSEDML(stringStream.str(), pImportHandler,
                          pSBMLDocument, pSedDocument, copasi2sedmlmap, copasi2sbmlmap, prLol,  plotList, pDataModel);
}
/**
 * Function parses an SEDML document with libsedml and converts it to a COPASI CModel
 * object which is returned. Deletion of the returned pointer is up to the
 * caller.
 */
CModel*
SEDMLImporter::parseSEDML(const std::string& sedmlDocumentText,
                          CProcessReport* pImportHandler,
                          SBMLDocument *& pSBMLDocument,
                          SedDocument *& pSEDMLDocument,
                          std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap,
                          std::map<CCopasiObject*, SBase*>& copasi2sbmlmap,
                          CListOfLayouts *& prLol,
                          COutputDefinitionVector * & pPlotList,
                          CCopasiDataModel* pDataModel)
{

  this->mUsedSEDMLIdsPopulated = false;

  mpDataModel = pDataModel;
  assert(mpDataModel != NULL);

  this->mpCopasiModel = NULL;

  SedReader reader;

  mImportStep = 0;

  if (mpImportHandler)
    {
      mpImportHandler->setName("Importing SED-ML file...");
      mTotalSteps = 11;
      mhImportStep = mpImportHandler->addItem("Step", mImportStep,
                                              &mTotalSteps);
    }

  unsigned C_INT32 step = 0, totalSteps = 0;
  size_t hStep = C_INVALID_INDEX;

  if (this->mpImportHandler != 0)
    {
      step = 0;
      totalSteps = 1;
      hStep = mpImportHandler->addItem("Reading SED-ML file...", step,
                                       &totalSteps);
    }

  mpSEDMLDocument = reader.readSedMLFromString(sedmlDocumentText);

  assert(mpSEDMLDocument != NULL);

  if (mpImportHandler)
    mpImportHandler->finishItem(hStep);

  if (this->mpImportHandler != 0)
    {
      step = 0;
      totalSteps = 1;
      hStep = mpImportHandler->addItem("Checking consistency...", step,
                                       &totalSteps);
    }

  if (mpImportHandler)
    mpImportHandler->finishItem(hStep);

  int fatal = -1;
  unsigned int i, iMax = mpSEDMLDocument->getNumErrors();

  for (i = 0; (i < iMax) && (fatal == -1); ++i)
    {
      const SedError* pSEDMLError = mpSEDMLDocument->getError(i);

      CCopasiMessage::Type messageType = CCopasiMessage::RAW;

      switch (pSEDMLError->getSeverity())
        {

          case LIBSEDML_SEV_WARNING:

            // if issued as warning, this message is to be disregarded,
            // it was a bug in earlier versions of libSEDML
            if (pSEDMLError->getErrorId() == SedInvalidNamespaceOnSed)
              continue;

            if (mIgnoredSEDMLMessages.find(pSEDMLError->getErrorId())
                != mIgnoredSEDMLMessages.end())
              {
                messageType = CCopasiMessage::WARNING_FILTERED;
              }
            else
              {
                messageType = CCopasiMessage::WARNING;
              }

            CCopasiMessage(messageType, MCSEDML + 6, "WARNING",
                           pSEDMLError->getErrorId(), pSEDMLError->getLine(),
                           pSEDMLError->getColumn(),
                           pSEDMLError->getMessage().c_str());
            break;

          case LIBSEDML_SEV_ERROR:

            if (mIgnoredSEDMLMessages.find(pSEDMLError->getErrorId())
                != mIgnoredSEDMLMessages.end())
              {
                messageType = CCopasiMessage::ERROR_FILTERED;
              }

            CCopasiMessage(messageType, MCSEDML + 6, "ERROR",
                           pSEDMLError->getErrorId(), pSEDMLError->getLine(),
                           pSEDMLError->getColumn(),
                           pSEDMLError->getMessage().c_str());
            break;

          case LIBSEDML_SEV_FATAL:

            // treat unknown as fatal
          default:

            if (pSEDMLError->getErrorId() == 10804)
              {
                // this error indicates a problem with a notes element
                // although libsedml flags this as fatal, we would still
                // like to read the model
                CCopasiMessage(messageType, MCSEDML + 6, "ERROR",
                               pSEDMLError->getErrorId(), pSEDMLError->getLine(),
                               pSEDMLError->getColumn(),
                               pSEDMLError->getMessage().c_str());
              }
            else
              {
                fatal = i;
              }

            break;
        }
    }

  if (fatal != -1)
    {
      const XMLError* pSEDMLError = mpSEDMLDocument->getError(fatal);
      CCopasiMessage Message(CCopasiMessage::EXCEPTION, MCXML + 2,
                             pSEDMLError->getLine(), pSEDMLError->getColumn(),
                             pSEDMLError->getMessage().c_str());

      if (mpImportHandler)
        mpImportHandler->finishItem(mhImportStep);

      return NULL;
    }

  if (mpSEDMLDocument->getListOfModels() == NULL)
    {
      CCopasiMessage Message(CCopasiMessage::ERROR, MCSEDML + 2);

      if (mpImportHandler)
        mpImportHandler->finishItem(mhImportStep);

      return NULL;
    }

  //delete reader;
  pSEDMLDocument = mpSEDMLDocument;
  this->mLevel = pSEDMLDocument->getLevel();

  this->mOriginalLevel = this->mLevel;
  this->mVersion = pSEDMLDocument->getVersion();

  importFirstSBMLModel(pImportHandler, pSBMLDocument, copasi2sbmlmap, prLol, pDataModel);

  pPlotList = new COutputDefinitionVector("OutputDefinitions", mpDataModel);
  readListOfPlotsFromSedMLOutput(pPlotList, mpCopasiModel, pSEDMLDocument, copasi2sedmlmap);

  importTasks(copasi2sedmlmap);

  if (mpImportHandler)
    mpImportHandler->finishItem(mhImportStep);

  return mpCopasiModel;

  return NULL;
}

void
SEDMLImporter::importTasks(std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap)
{

  for (unsigned int i = 0; i < mpSEDMLDocument->getNumTasks(); ++i)
    {
      SedTask * current = mpSEDMLDocument->getTask(i);

      // skip taks for models we did not import
      if (current->isSetModelReference() && current->getModelReference() != this->mImportedModel)
        continue;

      switch (current->getTypeCode())
        {
          case SEDML_TASK:
          {
            SedSimulation* sedmlsim =
              mpSEDMLDocument->getSimulation(current->getSimulationReference());
            updateCopasiTaskForSimulation(sedmlsim, copasi2sedmlmap);
            break;
          }

          case SEDML_TASK_REPEATEDTASK:
          {
            SedRepeatedTask *repeat = static_cast<SedRepeatedTask*>(current);
            SedRange* range = repeat->getRange(repeat->getRangeId());

            if (range == NULL || range->getTypeCode() != SEDML_RANGE_UNIFORMRANGE)
              {
                CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI only supports uniform ranges.");
                continue;
              }

            SedUniformRange* urange = static_cast<SedUniformRange*>(range);
            CScanTask *tTask = static_cast<CScanTask*>((*mpDataModel->getTaskList())["Scan"]);
            CScanProblem *pProblem = static_cast<CScanProblem*>(tTask->getProblem());

            if (urange != NULL && repeat->getNumTaskChanges() == 0)
              {
                pProblem->addScanItem(CScanProblem::SCAN_REPEAT, urange->getNumberOfPoints());
              }
            else
              {
                for (unsigned int j = 0; j < repeat->getNumTaskChanges(); ++j)
                  {
                    SedSetValue* sv = repeat->getTaskChange(j);

                    if (SBML_formulaToString(sv->getMath()) != sv->getRange())
                      {
                        CCopasiMessage(CCopasiMessage::WARNING,
                                       "This version of COPASI only supports setValue elements that apply range values.");
                      }

                    std::string target = sv->getTarget();
                    const CCopasiObject * obj = SEDMLUtils::resolveXPath(mpCopasiModel, target, true);

                    if (obj == NULL)
                      {
                        CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI only supports modifications of initial values.");
                        continue;
                      }

                    CCopasiParameterGroup*group = pProblem->addScanItem(CScanProblem::SCAN_LINEAR, urange->getNumberOfPoints(), obj);
                    *group->getParameter("Minimum")->getValue().pDOUBLE = urange->getStart();
                    *group->getParameter("Maximum")->getValue().pDOUBLE = urange->getEnd();
                    *group->getParameter("log")->getValue().pBOOL =
                      (!urange->isSetType() || urange->getType().empty() ||  urange->getType() == "linear") ? false
                      : true;
                  }
              }

            if (repeat->getNumSubTasks() != 1)
              {
                CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI only supports repeatedTasks with one subtask.");
                continue;
              }

            pProblem->setContinueFromCurrentState(!repeat->getResetModel());

            SedSubTask* subTask = repeat->getSubTask(0);

            if (!subTask->isSetTask())
              {
                CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI only supports repeatedTasks with one subtask that has a valid task reference.");
                continue;
              }

            SedTask* actualSubTask = mpSEDMLDocument->getTask(subTask->getTask());

            if (actualSubTask == NULL || !actualSubTask->isSetSimulationReference())
              {
                CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI only supports repeatedTasks with one subtask that itself is a task with simulation reference.");
                continue;
              }

            int code = mpSEDMLDocument->getSimulation(actualSubTask->getSimulationReference())->getTypeCode();

            if (code == SEDML_SIMULATION_STEADYSTATE)
              {
                pProblem->setSubtask(CCopasiTask::steadyState);
                pProblem->setOutputInSubtask(false);
              }
            else if (code == SEDML_SIMULATION_ONESTEP || code == SEDML_SIMULATION_UNIFORMTIMECOURSE)
              {
                pProblem->setSubtask(CCopasiTask::timeCourse);
              }

            break;
          }

          default:
          {
            const char* name = SedTypeCode_toString(current->getTypeCode());
            CCopasiMessage(CCopasiMessage::WARNING,
                           "Encountered unsupported Task type '%s'. This task cannot be imported in COPASI",
                           name != NULL ? name : "unknown");
          }
        }
    }
}

CModel* SEDMLImporter::importFirstSBMLModel(CProcessReport* pImportHandler,
    SBMLDocument *& pSBMLDocument,
    std::map<CCopasiObject*, SBase*>& copasi2sbmlmap,
    CListOfLayouts *& prLol,
    CCopasiDataModel* pDataModel)
{
  std::string SBMLFileName, fileContent;

  unsigned int ii, iiMax = mpSEDMLDocument->getListOfModels()->size();

  if (iiMax < 1)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSEDML + 2);
    }

  if (iiMax > 1)
    {
      CCopasiMessage(CCopasiMessage::WARNING, "COAPSI currently only supports the import of SED-ML models, that involve one model only. Only the simulations for the first model will be imported");
    }

  std::string modelSource = ""; //must be taken from SEDML document.
  std::string modelId = ""; // to ensure only one model is imported since only one model in SEDML file is supported

  for (ii = 0; ii < iiMax; ++ii)
    {
      SedModel* sedmlModel = mpSEDMLDocument->getModel(ii);

      // need to also allow for the specific urns like
      // urn:sedml:language:sbml.level-3.version-1
      if (sedmlModel->getLanguage().find("urn:sedml:language:sbml") == std::string::npos)
        CCopasiMessage(CCopasiMessage::EXCEPTION,
                       "Sorry currently, only SBML models are supported.");

      if (sedmlModel->getSource() != modelId)
        {
          modelId = sedmlModel->getId();

          if ((sedmlModel->getListOfChanges()->size()) > 0)
            CCopasiMessage(CCopasiMessage::WARNING, "Currently no support for"
                           " changing model entities. Changes will not be made to the imported model.");

          modelSource = sedmlModel->getSource();
        }
    }

  assert(modelSource != "");

  //process the archive file and get the SBML model file
  //SEDMLUtils utils;
  //int success = utils.processArchive(pDataModel->getSEDMLFileName(), SBMLFileName, fileContent);

  std::string FileName;

  if (CDirEntry::exist(modelSource))
    FileName = modelSource;
  else
    FileName = CDirEntry::dirName(pDataModel->getSEDMLFileName())
               + CDirEntry::Separator + modelSource;

  std::ifstream file(CLocaleString::fromUtf8(FileName).c_str());

  if (!file)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSEDML + 4,
                     FileName.c_str());
    }

  //set the SBML file name for later use
  pDataModel->setSBMLFileName(FileName);
  std::ostringstream sbmlStringStream;
  char c;

  while (file.get(c))
    {
      sbmlStringStream << c;
    }

  file.clear();
  file.close();

  std::ifstream File(CLocaleString::fromUtf8(FileName).c_str());

  SBMLImporter importer;
  // Right now we always import the COPASI MIRIAM annotation if it is there.
  // Later this will be settable by the user in the preferences dialog
  importer.setImportCOPASIMIRIAM(true);
  importer.setImportHandler(pImportHandler);

  mpCopasiModel = NULL;

  std::map<CCopasiObject*, SBase*> Copasi2SBMLMap;

  try
    {
      mpCopasiModel = importer.parseSBML(sbmlStringStream.str(),
                                         CCopasiRootContainer::getFunctionList(), pSBMLDocument,
                                         Copasi2SBMLMap, prLol, mpDataModel);
    }

  catch (CCopasiException & except)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      //    popData();

      throw except;
    }

  if (mpCopasiModel == NULL)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      //   popData();
      return NULL;
    }

  mImportedModel = modelId;

  return mpCopasiModel;
}

/**
 * Constructor that initializes speciesMap and the FunctionDB object
 */
SEDMLImporter::SEDMLImporter():
  mIgnoredSEDMLMessages(),
  mIncompleteModel(false),
  mLevel(0),
  mOriginalLevel(0),
  mVersion(0),
  mpDataModel(NULL),
  mpCopasiModel(NULL),
  mpSEDMLDocument(NULL),
  mpImportHandler(NULL),
  mImportStep(0),
  mhImportStep(C_INVALID_INDEX),
  mTotalSteps(0),
  mUsedSEDMLIds(),
  mUsedSEDMLIdsPopulated(false),
  mImportedModel()
{

  this->mIgnoredSEDMLMessages.insert(10501);
}

void SEDMLImporter::restoreFunctionDB()
{
}

/**
 * Destructor that does nothing.
 */
SEDMLImporter::~SEDMLImporter()
{
}

void SEDMLImporter::deleteCopasiModel()
{
  if (this->mpCopasiModel != NULL)
    {
      delete this->mpCopasiModel;
      this->mpCopasiModel = NULL;
    }
}
