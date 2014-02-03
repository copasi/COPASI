// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define COPASI_MAIN

#include <iostream>
#include <stdlib.h>

#include "copasi/copasi.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/model/CMetab.h"
#include "copasi/report/CCopasiObjectName.h"
#include "copasi/utilities/CCopasiVector.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/commandline/COptionParser.h"
#include "copasi/commandline/COptions.h"

#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/scan/CScanTask.h"
#include "copasi/scan/CScanProblem.h"

int main(int argc, char *argv[])
{
  // Parse the commandline options
  // first argument is the SBML filename
  // second argument is the endtime
  // third argument is the step number
  // fourth argument is the filename where the results are to be written
  // fifth argument is the tmp directory (this is not needed)
  // the rest of the arguments are species names for the result
  try
    {
      // Create the root container.
      CCopasiRootContainer::init(0, NULL, false);
    }

  catch (copasi::autoexcept &e)
    {}

  catch (copasi::option_error &e)
    {}

  if (argc < 5)
    {
      std::cout << "Usage: stochastic-testsuite METHOD SBMLFILENAME ENDTIME STEPNUMBER REPEATS OUTFILENAME SPECIESID1 SPECIESID2 ..." << std::endl;
      exit(1);
    }

  const char* pMethodType = argv[1];

  const char* pSBMLFilename = argv[2];

  const char* pEndTime = argv[3];

  const char* pStepNumber = argv[4];

  const char* pRepeats = argv[5];

  const char* pOutputFilename = argv[6];

  unsigned int NUMARGS = 7;

  /*
  std::cout << "Input : " << pSBMLFilename << std::endl;
  std::cout << "Endtime : " << pEndTime << std::endl;
  std::cout << "Stepnumber: " << pStepNumber << std::endl;
  std::cout << "Repeats : " << pRepeats << std::endl;
  std::cout << "Output file: " << pOutputFilename << std::endl;
  */

  char** pSBMLSpeciesIds = new char * [argc - NUMARGS];

  unsigned int i, iMax = argc;

  CTrajectoryTask* pTrajectoryTask = NULL;

  CScanTask* pScanTask = NULL;

  std::string CWD = COptions::getPWD();

  double endTime = strToDouble(pEndTime, &pEndTime);

  double stepNumber = strToDouble(pStepNumber, &pStepNumber);

  char** pTmpP = (char**)(&pRepeats);

  long int repeats = strtol(pRepeats, pTmpP , 10);

  CCopasiMethod::SubType MethodType;

  if (!strcmp(pMethodType, "stochastic"))
    {
      MethodType = CCopasiMethod::stochastic;
    }
  else if (!strcmp(pMethodType, "directMethod"))
    {
      MethodType = CCopasiMethod::directMethod;
    }
  else if (!strcmp(pMethodType, "tauLeap"))
    {
      MethodType = CCopasiMethod::tauLeap;
    }
  else if (!strcmp(pMethodType, "adaptiveSA"))
    {
      MethodType = CCopasiMethod::adaptiveSA;
    }
  else if (!strcmp(pMethodType, "LSODA"))
    {
      MethodType = CCopasiMethod::deterministic;
    }
  else if (!strcmp(pMethodType, "HybridODE45"))
    {
      MethodType = CCopasiMethod::hybridODE45;
    }
  else
    {
      std::cerr << "Invalid method type. Valid options are:" << std::endl;
      std::cerr << "    stochastic" << std::endl;
      std::cerr << "    directMethod" << std::endl;
      std::cerr << "    tauLeap" << std::endl;
    }

  if (endTime == 0.0)
    {
      std::cerr << "Invalid endtime " << pEndTime << std::endl;
      exit(1);
    }

  if (stepNumber == 0.0)
    {
      std::cerr << "Invalid step number " << pStepNumber << std::endl;
      exit(1);
    }

  for (i = NUMARGS; i < iMax; ++i)
    {
      pSBMLSpeciesIds[i - NUMARGS] = argv[i];
      //std::cout << "Copying pointer to " <<  argv[i]  << "." << std::endl;
    }

  try
    {
      // Create the global data model.
      CCopasiDataModel* pDataModel = CCopasiRootContainer::addDatamodel();

      // Import the SBML File
      pDataModel->importSBML(pSBMLFilename);

      //pDataModel->getModel()->forceCompile();

      // create a report with the correct filename and all the species against
      // time.
      CReportDefinitionVector* pReports = pDataModel->getReportDefinitionList();
      CReportDefinition* pReport = pReports->createReportDefinition("Report", "Output for stochastic testsuite run");
      pReport->setTaskType(CCopasiTask::timeCourse);
      pReport->setIsTable(false);

      CCopasiReportSeparator Separator(std::string(","));
      pReport->setSeparator(Separator);

      std::vector<CRegisteredObjectName> * pHeader = pReport->getHeaderAddr();
      std::vector<CRegisteredObjectName> * pBody = pReport->getBodyAddr();

      // Add time column
      pHeader->push_back(CCopasiStaticString("time").getCN());
      pBody->push_back(CCopasiObjectName(pDataModel->getModel()->getCN() + ",Reference=Time"));

      iMax = iMax - NUMARGS;
      const CCopasiVector<CMetab>& metabolites = pDataModel->getModel()->getMetabolites();

      for (i = 0; i < iMax; ++i)
        {
          pHeader->push_back(Separator.getCN());
          pBody->push_back(Separator.getCN());

          unsigned int j, jMax = metabolites.size();

          std::string SBMLId = unQuote(pSBMLSpeciesIds[i]);

          for (j = 0; j < jMax; ++j)
            {
              if (metabolites[j]->getSBMLId() == SBMLId)
                {
                  break;
                }
            }

          if (j == jMax)
            {
              std::cerr << "Could not find a metabolite for the SBML id \"" << pSBMLSpeciesIds[i] << "\"" << std::endl;
              exit(1);
            }

          pHeader->push_back(CCopasiStaticString(SBMLId).getCN());
          pBody->push_back(metabolites[j]->getObject(CCopasiObjectName("Reference=ParticleNumber"))->getCN());
        }

      // create a trajectory task
      pTrajectoryTask = new CTrajectoryTask();
      pTrajectoryTask->setMethodType(MethodType);
      pTrajectoryTask->getProblem()->setModel(pDataModel->getModel());
      pTrajectoryTask->setScheduled(false);

      //pTrajectoryTask->getReport().setReportDefinition(pReport);
      //pTrajectoryTask->getReport().setTarget(CWD + "/" + pOutputFilename);
      //pTrajectoryTask->getReport().setAppend(false);

      CTrajectoryProblem* pProblem = dynamic_cast<CTrajectoryProblem*>(pTrajectoryTask->getProblem());

      pProblem->setStepNumber((const unsigned C_INT32)stepNumber);
      pProblem->setDuration((const C_FLOAT64)endTime);
      pProblem->setTimeSeriesRequested(true);
      pProblem->setTimeSeriesRequested(false);

      //pProblem->setInitialState(pDataModel->getModel()->getInitialState());

      CCopasiVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();

      TaskList.remove("Time-Course");
      TaskList.add(pTrajectoryTask, true);

      // create a scan task

      pScanTask = new CScanTask(pDataModel);
      CScanProblem* pScanProblem = dynamic_cast<CScanProblem*>(pScanTask->getProblem());
      pScanProblem->setModel(pDataModel->getModel());

      pScanTask->setScheduled(true);

      pScanTask->getReport().setReportDefinition(pReport);
      pScanTask->getReport().setTarget(pOutputFilename);
      pScanTask->getReport().setAppend(false);

      pScanProblem->setSubtask(CCopasiTask::timeCourse);
      //pScanProblem->createScanItem(CScanProblem::SCAN_REPEAT, repeats);
      pScanProblem->addScanItem(CScanProblem::SCAN_REPEAT, repeats);
      pScanProblem->setOutputInSubtask(true);
      pScanProblem->setContinueFromCurrentState(false);

      TaskList.remove("Scan");
      TaskList.add(pScanTask, true);

      // save the file for control purposes
      std::string saveFilename = pSBMLFilename;
      saveFilename = saveFilename.substr(0, saveFilename.length() - 4) + ".cps";
      pDataModel->saveModel(saveFilename, NULL, true);

      // Run the trajectory task

      pScanTask->initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL);
      pScanTask->process(true);
      pScanTask->restore();

      // create another report that will write to the directory where the input file came from
      // this can be used for debugging
      // create a trajectory task
      // pScanTask->getReport().setTarget(pOutputFilename);

      // pScanTask->initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL);
      // pScanTask->process(true);
      // pScanTask->restore();
    }
  catch (CCopasiException Exception)
    {
      std::cerr << Exception.getMessage().getText() << std::endl;
    }

  CCopasiRootContainer::destroy();

  return 0;
}
