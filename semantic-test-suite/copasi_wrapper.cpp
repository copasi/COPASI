/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/semantic-test-suite/copasi_wrapper.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2006/03/14 16:19:49 $
   End CVS Header */

#define COPASI_MAIN

#include <iostream>
#include <stdlib.h>

#include "copasi.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiContainer.h"
#include "model/CMetab.h"
#include "report/CCopasiObjectName.h"
#include "utilities/CCopasiVector.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryMethod.h"
#include "trajectory/CTrajectoryProblem.h"
#include "report/CReportDefinitionVector.h"
#include "report/CReportDefinition.h"

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
      // Parse the commandline options
      COptions::init(argc, argv);
    }

  catch (copasi::autoexcept &e)
  {}

  catch (copasi::option_error &e)
  {}
  if (argc < 5)
    {
      std::cout << "Usage: semantic-test-suite SBMLFILENAME ENDTIME STEPNUMBER OUTFILENAME TMPDIR SPECIESID1 SPECIESID2 ..." << std::endl;
      exit(1);
    }
  char* pSBMLFilename = argv[1];
  char* pEndTime = argv[2];
  char* pStepNumber = argv[3];
  char* pOutputFilename = argv[4];
  //char* pTmpDirectory=argv[5];
  char** pSBMLSpeciesIds = new char * [argc - 6];
  unsigned int i, iMax = argc;
  CTrajectoryTask* pTrajectoryTask = NULL;

  std::string CWD = COptions::getPWD();
  double endTime = strtod(pEndTime, &pEndTime);
  double stepNumber = strtod(pStepNumber, &pStepNumber);
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

  for (i = 6; i < iMax;++i)
    {
      pSBMLSpeciesIds[i - 6] = argv[i];
      //std::cout << "Copying pointer to " <<  argv[i]  << "." << std::endl;
    }

  try
    {
      // Create the root container.
      CCopasiContainer::init();

      // Create the global data model.
      CCopasiDataModel::Global = new CCopasiDataModel;

      // Import the SBML File
      CCopasiDataModel::Global->importSBML(pSBMLFilename);

      //CCopasiDataModel::Global->getModel()->forceCompile();

      // create a report with the correct filename and all the species against
      // time.
      CReportDefinitionVector* pReports = CCopasiDataModel::Global->getReportDefinitionList();
      CReportDefinition* pReport = pReports->createReportDefinition("Report", "Output for SBML testsuite run");
      pReport->setTaskType(CCopasiTask::timeCourse);
      pReport->setIsTable(true);

      std::vector<CRegisteredObjectName>* pTable = pReport->getTableAddr();
      pTable->push_back(CCopasiObjectName("CN=Root,Model=" + CCopasiDataModel::Global->getModel()->getObjectName() + ",Reference=Time"));
      iMax = iMax - 6;
      const CCopasiVector<CMetab>& metabolites = CCopasiDataModel::Global->getModel()->getMetabolites();
      for (i = 0; i < iMax;++i)
        {
          unsigned int j, jMax = metabolites.size();
          for (j = 0; j < jMax;++j)
            {
              if (metabolites[j]->getSBMLId() == pSBMLSpeciesIds[i])
                {
                  pTable->push_back(metabolites[j]->getObject(CCopasiObjectName("Reference=Concentration"))->getCN());
                  //std::cout << "adding metabolite " << metabolites[j]->getObjectName() << " to report." << std::endl;
                  break;
                }
            }
          if (j == jMax)
            {
              std::cerr << "Could not find a metabolite for the SBML id " << pSBMLSpeciesIds[i] << std::endl;
              exit(1);
            }
        }

      // create a trajectory task
      pTrajectoryTask = new CTrajectoryTask();
      pTrajectoryTask->getProblem()->setModel(CCopasiDataModel::Global->getModel());

      pTrajectoryTask->setScheduled(true);

      pTrajectoryTask->getReport().setReportDefinition(pReport);
      pTrajectoryTask->getReport().setTarget(CWD + "/" + pOutputFilename);
      pTrajectoryTask->getReport().setAppend(false);

      CTrajectoryProblem* pProblem = dynamic_cast<CTrajectoryProblem*>(pTrajectoryTask->getProblem());

      pProblem->setStepNumber((const unsigned C_INT32)stepNumber);
      pProblem->setDuration((const C_FLOAT64)endTime);
      pProblem->setTimeSeriesRequested(true);
      //pProblem->setInitialState(CCopasiDataModel::Global->getModel()->getInitialState());

      CLsodaMethod* pMethod = dynamic_cast<CLsodaMethod*>(pTrajectoryTask->getMethod());

      pMethod->getParameter("Use Default Absolute Tolerance")->setValue(false);
      pMethod->getParameter("LSODA.AbsoluteTolerance")->setValue(1000.0);

      CCopasiVectorN< CCopasiTask > & TaskList = * CCopasiDataModel::Global->getTaskList();

      TaskList.remove("Time-Course");
      TaskList.add(pTrajectoryTask, true);

      // save the file for control purposes
      std::string saveFilename = pSBMLFilename;
      saveFilename = saveFilename.substr(0, saveFilename.length() - 4) + ".cps";
      CCopasiDataModel::Global->saveModel(saveFilename, true);

      // Run the trajectory task

      pTrajectoryTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL);
      pTrajectoryTask->process(true);
      pTrajectoryTask->restore();

      // create another report that will write to the directory where the input file came from
      // this can be used for debugging
      // create a trajectory task
      pTrajectoryTask->getReport().setTarget(pOutputFilename);

      pTrajectoryTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL);
      pTrajectoryTask->process(true);
      pTrajectoryTask->restore();
    }
  catch (CCopasiException Exception)
    {
      std::cerr << Exception.getMessage().getText() << std::endl;
    }

  pdelete(CCopasiDataModel::Global);
  pdelete(CCopasiContainer::Root);

  return 0;
}
