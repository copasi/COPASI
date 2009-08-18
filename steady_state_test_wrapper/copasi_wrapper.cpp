// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/steady_state_test_wrapper/copasi_wrapper.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2009/08/18 12:31:12 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CSteadyStateMethod.h"
#include "copasi/steadystate/CSteadyStateProblem.h"

#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/report/CReportDefinition.h"

int main(int argc, char *argv[])
{
  // Parse the commandline options
  // 1. argument is the SBML filename
  // 2. argument is the filename where the results are to be written
  // (the rest of the arguments are species names for the result)
  try
    {
      // Create the root container.
      CCopasiRootContainer::init(0, NULL, false);
    }

  catch (copasi::autoexcept &e)
    {}

  catch (copasi::option_error &e)
    {}

  if (argc < 3)
    {
      std::cout << "Usage: batch_wrapper SBMLFILENAME OUTFILENAME" << std::endl;
      exit(1);
    }

  char* pSBMLFilename = argv[1];
  const char* pOutputFilename = argv[2];
  //CTrajectoryTask* pTrajectoryTask = NULL;
  CSteadyStateTask* pSSTask = NULL;

  std::string CWD = COptions::getPWD();
//  double startTime = strToDouble(pStartTime, &pStartTime);
//  double endTime = strToDouble(pEndTime, &pEndTime);
//  double stepNumber = strToDouble(pStepNumber, &pStepNumber);

  /*  if (startTime < 0.0)
      {
        std::cerr << "Invalid endtime " << pEndTime << std::endl;
        exit(1);
      }*/

  try
    {
      // Create the global data model.
      CCopasiDataModel* pDataModel = CCopasiRootContainer::addDatamodel();

      // Import the SBML File
      pDataModel->importSBML(pSBMLFilename);

      // create a report with the correct filename and all the species against
      // time.
      CReportDefinitionVector* pReports = pDataModel->getReportDefinitionList();
      CReportDefinition* pReport = pReports->createReportDefinition("Report", "Output for batch run");
      pReport->setTaskType(CCopasiTask::steadyState);
      pReport->setIsTable(false);
      pReport->setSeparator(CCopasiReportSeparator(", "));

      std::vector<CRegisteredObjectName>* pHeader = pReport->getHeaderAddr();
      std::vector<CRegisteredObjectName>* pBody = pReport->getBodyAddr();
      std::vector<CRegisteredObjectName>* pFoot = pReport->getFooterAddr();

      //Time is not needed for steady state
      //pBody->push_back(CCopasiObjectName(pDataModel->getModel()->getCN() + ",Reference=Time"));
      //pBody->push_back(CRegisteredObjectName(pReport->getSeparator().getCN()));
      //pHeader->push_back(CCopasiStaticString("time").getCN());
      //pHeader->push_back(pReport->getSeparator().getCN());

      const CCopasiVectorNS<CCompartment>& compartments = pDataModel->getModel()->getCompartments();
      unsigned int j, jMax = compartments.size();
      /*
      for (j = 0; j < jMax;++j)
      {
        if(compartments[j]->getStatus()!=CModelEntity::FIXED)
        {
          pBody->push_back(compartments[j]->getObject(CCopasiObjectName("Reference=Volume"))->getCN());
          pBody->push_back(pReport->getSeparator().getCN());
          pHeader->push_back(CCopasiStaticString(compartments[j]->getSBMLId()).getCN());
          pHeader->push_back(pReport->getSeparator().getCN());
        }
      }
      */

      const CCopasiVector<CMetab>& metabolites = pDataModel->getModel()->getMetabolites();
      jMax = metabolites.size();

      for (j = 0; j < jMax; ++j)
        {
          if (metabolites[j]->getStatus() != CModelEntity::FIXED)
            {
              pFoot->push_back(metabolites[j]->getObject(CCopasiObjectName("Reference=Concentration"))->getCN());
              pFoot->push_back(pReport->getSeparator().getCN());
              pHeader->push_back(CCopasiStaticString(metabolites[j]->getSBMLId()).getCN());
              pHeader->push_back(pReport->getSeparator().getCN());
            }
        }

      /*
      const CCopasiVectorN<CModelValue>& parameters = pDataModel->getModel()->getModelValues();
      jMax = parameters.size();
      for (j = 0; j < jMax;++j)
      {
        if(parameters[j]->getStatus()!=CModelEntity::FIXED)
        {
          pBody->push_back(parameters[j]->getObject(CCopasiObjectName("Reference=Value"))->getCN());
          pBody->push_back(pReport->getSeparator().getCN());
          pHeader->push_back(CCopasiStaticString(parameters[j]->getSBMLId()).getCN());
          pHeader->push_back(pReport->getSeparator().getCN());
        }
      }
      const CCopasiVectorNS<CReaction>& reactions = pDataModel->getModel()->getReactions();
      jMax = reactions.size();
      for (j = 0; j < jMax;++j)
      {
        pBody->push_back(reactions[j]->getObject(CCopasiObjectName("Reference=Flux"))->getCN());
        pBody->push_back(pReport->getSeparator().getCN());
        pHeader->push_back(CCopasiStaticString(reactions[j]->getSBMLId()).getCN());
        pHeader->push_back(pReport->getSeparator().getCN());
      }
      */

      // delete the last separator

      if ((*pFoot->rbegin()) == pReport->getSeparator().getCN())
        {
          pFoot->erase(--pFoot->end());
        }

      if ((*pHeader->rbegin()) == pReport->getSeparator().getCN())
        {
          pHeader->erase(--pHeader->end());
        }

      //**** create a task ****

      pSSTask = new CSteadyStateTask();
      // use LSODAR from now on since we will have events pretty soon
      pSSTask->setMethodType(CCopasiMethod::Newton);
      pSSTask->getProblem()->setModel(pDataModel->getModel());

      pSSTask->setScheduled(true);

      pSSTask->getReport().setReportDefinition(pReport);
      pSSTask->getReport().setTarget(CWD + "/" + pOutputFilename);
      pSSTask->getReport().setAppend(false);

      //**** specify problem ****

      CSteadyStateProblem* pProblem = dynamic_cast<CSteadyStateProblem*>(pSSTask->getProblem());

      //pProblem->setStepNumber((const unsigned C_INT32)stepNumber);
      //pDataModel->getModel()->setInitialTime((const C_FLOAT64)startTime);
      //pProblem->setDuration((const C_FLOAT64)endTime - startTime);
      //pProblem->setTimeSeriesRequested(true);

      //**** method settings ****

      CSteadyStateMethod* pMethod = dynamic_cast<CSteadyStateMethod*>(pSSTask->getMethod());

      //pMethod->getParameter("Absolute Tolerance")->setValue(1.0e-12);

      //***** run the task *********
      CCopasiVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();

      TaskList.remove("Steady-State");
      TaskList.add(pSSTask, true);

      // save the file for control purposes
      std::string saveFilename = pSBMLFilename;
      saveFilename = saveFilename.substr(0, saveFilename.length() - 4) + ".cps";
      pDataModel->saveModel(saveFilename, NULL, true);

      // Run the task

      //pTrajectoryTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL,NULL);
      //pTrajectoryTask->process(true);
      //pTrajectoryTask->restore();

      // create another report that will write to the directory where the input file came from
      // this can be used for debugging
      // create a trajectory task
      pSSTask->getReport().setTarget(pOutputFilename);

      pSSTask->initialize(CCopasiTask::OUTPUT_COMPLETE, pDataModel, NULL);
      pSSTask->process(true);
      pSSTask->restore();
    }
  catch (CCopasiException Exception)
    {
      std::cerr << Exception.getMessage().getText() << std::endl;
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

  CCopasiRootContainer::destroy();

  return 0;
}
