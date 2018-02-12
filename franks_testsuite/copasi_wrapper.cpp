// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#define COPASI_MAIN

#include <iostream>
#include <stdlib.h>

#include <copasi/CopasiTypes.h>
#include <copasi/CopasiTaskTypes.h>

#include "copasi/commandline/COptionParser.h"
#include "copasi/commandline/COptions.h"
#include "copasi/utilities/CCopasiException.h"


#ifdef WIN32
#include <windows.h>
#include <rtcapi.h>

void terminateHandler() {
  std::cerr << "COPASI crashed." << std::endl;
  exit(-1);
}

int exception_handler(LPEXCEPTION_POINTERS p)
{
  terminateHandler();
}
int runtime_check_handler(int errorType, const char *filename, int linenumber, const char *moduleName, const char *format, ...)
{
  printf("Error type %d at %s line %d in %s", errorType, filename, linenumber, moduleName);
  terminateHandler();
}

#endif

int main(int argc, char *argv[])
{
#ifdef WIN32
  // in case of fatal exceptions under windows we don't
  // want the OS's error handlers to get in the way
  DWORD dwMode = SetErrorMode(SEM_NOGPFAULTERRORBOX);
  SetErrorMode(dwMode | SEM_NOGPFAULTERRORBOX);
  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)&exception_handler);
  _RTC_SetErrorFunc(&runtime_check_handler);
  set_terminate(&terminateHandler);
#endif

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
      CRootContainer::init(0, NULL, false);
    }

  catch (const copasi::autoexcept &)
    {}

  catch (const copasi::option_error &)
    {}

  if (argc < 5)
    {
      std::cout << "Usage: batch_wrapper SBMLFILENAME STARTTIME ENDTIME STEPNUMBER OUTFILENAME" << std::endl;
      exit(1);
    }

  char* pSBMLFilename = argv[1];
  const char * pStartTime = argv[2];
  const char * pEndTime = argv[3];
  const char * pStepNumber = argv[4];
  char* pOutputFilename = argv[5];
  CTrajectoryTask* pTrajectoryTask = NULL;

  std::string CWD = COptions::getPWD();
  double startTime = strToDouble(pStartTime, NULL);
  double endTime = strToDouble(pEndTime, NULL);
  double stepNumber = strToDouble(pStepNumber, NULL);

  if (startTime < 0.0)
    {
      std::cerr << "Invalid endtime " << pEndTime << std::endl;
      exit(1);
    }

  if (endTime <= 0.0)
    {
      std::cerr << "Invalid endtime " << pEndTime << std::endl;
      exit(1);
    }

  if (stepNumber <= 0.0)
    {
      std::cerr << "Invalid step number " << pStepNumber << std::endl;
      exit(1);
    }

  try
    {
      // Create the global data model.
      CDataModel* pDataModel = CRootContainer::addDatamodel();

      // Import the SBML File
      pDataModel->importSBML(pSBMLFilename);

      // create a report with the correct filename and all the species against
      // time.
      CReportDefinitionVector* pReports = pDataModel->getReportDefinitionList();
      CReportDefinition* pReport = pReports->createReportDefinition("Report", "Output for batch run");
      pReport->setTaskType(CTaskEnum::Task::timeCourse);
      pReport->setIsTable(false);
      pReport->setSeparator(", ");

      std::vector<CRegisteredCommonName>* pHeader = pReport->getHeaderAddr();
      std::vector<CRegisteredCommonName>* pBody = pReport->getBodyAddr();
      pBody->push_back(CCommonName(pDataModel->getModel()->getCN() + ",Reference=Time"));
      pBody->push_back(CRegisteredCommonName(pReport->getSeparator().getCN()));
      pHeader->push_back(CDataString("time").getCN());
      pHeader->push_back(pReport->getSeparator().getCN());
      const CDataVectorNS<CCompartment>& compartments = pDataModel->getModel()->getCompartments();
      unsigned int j, jMax = compartments.size();
      /*
      for (j = 0; j < jMax;++j)
      {
        if(compartments[j]->getStatus()!=CModelEntity::Status::FIXED)
        {
          pBody->push_back(compartments[j]->getObject(CCommonName("Reference=Volume"))->getCN());
          pBody->push_back(pReport->getSeparator().getCN());
          pHeader->push_back(CCopasiStaticString(compartments[j]->getSBMLId()).getCN());
          pHeader->push_back(pReport->getSeparator().getCN());
        }
      }
      */
      const CDataVector<CMetab>& metabolites = pDataModel->getModel()->getMetabolites();
      jMax = metabolites.size();

      for (j = 0; j < jMax; ++j)
        {
          if (metabolites[j].getStatus() != CModelEntity::Status::FIXED)
            {
              pBody->push_back(metabolites[j].getObject(CCommonName("Reference=Concentration"))->getCN());
              pBody->push_back(pReport->getSeparator().getCN());
              pHeader->push_back(CDataString(metabolites[j].getSBMLId()).getCN());
              pHeader->push_back(pReport->getSeparator().getCN());
            }
        }

      /*
      const CDataVectorN<CModelValue>& parameters = pDataModel->getModel()->getModelValues();
      jMax = parameters.size();
      for (j = 0; j < jMax;++j)
      {
        if(parameters[j]->getStatus()!=CModelEntity::Status::FIXED)
        {
          pBody->push_back(parameters[j]->getObject(CCommonName("Reference=Value"))->getCN());
          pBody->push_back(pReport->getSeparator().getCN());
          pHeader->push_back(CCopasiStaticString(parameters[j]->getSBMLId()).getCN());
          pHeader->push_back(pReport->getSeparator().getCN());
        }
      }
      const CDataVectorNS<CReaction>& reactions = pDataModel->getModel()->getReactions();
      jMax = reactions.size();
      for (j = 0; j < jMax;++j)
      {
        pBody->push_back(reactions[j]->getObject(CCommonName("Reference=Flux"))->getCN());
        pBody->push_back(pReport->getSeparator().getCN());
        pHeader->push_back(CCopasiStaticString(reactions[j]->getSBMLId()).getCN());
        pHeader->push_back(pReport->getSeparator().getCN());
      }
      */

      // delete the last separator
      if ((*pBody->rbegin()) == pReport->getSeparator().getCN())
        {
          pBody->erase(--pBody->end());
        }

      if ((*pHeader->rbegin()) == pReport->getSeparator().getCN())
        {
          pHeader->erase(--pHeader->end());
        }

      // create a trajectory task
      pTrajectoryTask = new CTrajectoryTask(pDataModel->getTaskList());
      // use LSODAR from now on since we will have events pretty soon
      pTrajectoryTask->setMethodType(CTaskEnum::Method::deterministic);
      pTrajectoryTask->getProblem()->setMathContainer(&pDataModel->getModel()->getMathContainer());

      pTrajectoryTask->setScheduled(true);

      pTrajectoryTask->getReport().setReportDefinition(pReport);
      pTrajectoryTask->getReport().setTarget(CWD + "/" + pOutputFilename);
      pTrajectoryTask->getReport().setAppend(false);

      CTrajectoryProblem* pProblem = dynamic_cast<CTrajectoryProblem*>(pTrajectoryTask->getProblem());

      pProblem->setStepNumber((const unsigned C_INT32)stepNumber);
      pDataModel->getModel()->setInitialTime((const C_FLOAT64)startTime);
      pProblem->setDuration((const C_FLOAT64)endTime - startTime);
      pProblem->setTimeSeriesRequested(true);

      CTrajectoryMethod* pMethod = dynamic_cast<CTrajectoryMethod*>(pTrajectoryTask->getMethod());

      pMethod->getParameter("Absolute Tolerance")->setValue(1.0e-12);

      CDataVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();

      TaskList.remove("Time-Course");
      TaskList.add(pTrajectoryTask, true);

      // save the file for control purposes
      //std::string saveFilename = pSBMLFilename;
      //saveFilename = saveFilename.substr(0, saveFilename.length() - 4) + ".cps";
      //pDataModel->saveModel(saveFilename, NULL, true);

      // Run the trajectory task

      //pTrajectoryTask->initialize(CCopasiTask::OUTPUT_UI, NULL,NULL);
      //pTrajectoryTask->process(true);
      //pTrajectoryTask->restore();

      // create another report that will write to the directory where the input file came from
      // this can be used for debugging
      // create a trajectory task
      pTrajectoryTask->getReport().setTarget(pOutputFilename);

      pTrajectoryTask->initialize(CCopasiTask::OUTPUT_UI, pDataModel, NULL);
      pTrajectoryTask->process(true);
      pTrajectoryTask->restore();
    }
  catch (const CCopasiException& Exception)
    {
      std::cerr << Exception.getMessage().getText() << std::endl;
    }
  catch (...)
  {
    std::cerr << "unexpected exception occurred" << std::endl;
  }

  std::string Text = "";

  while (CCopasiMessage::size() > 0)
    {
      const CCopasiMessage& message = CCopasiMessage::getLastMessage();

      if (message.getType() < CCopasiMessage::RAW_FILTERED)
        {
          if (Text != "") Text += "\n";

          Text += message.getText();
        }
    }

  if (Text != "") std::cerr << Text << std::endl;

  CRootContainer::destroy();

  return 0;
}
