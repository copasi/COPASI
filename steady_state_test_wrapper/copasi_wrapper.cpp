// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/steady_state_test_wrapper/copasi_wrapper.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2012/04/23 08:44:44 $
// End CVS Header

// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define COPASI_MAIN

#include <iostream>
#include <fstream>
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
  CSteadyStateTask* pSSTask = NULL;

  std::string CWD = COptions::getPWD();

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

      for (j = 0; j < jMax; ++j)
        {
          if (compartments[j]->getStatus() != CModelEntity::FIXED)
            {
              pFoot->push_back(compartments[j]->getObject(CCopasiObjectName("Reference=Volume"))->getCN());
              pFoot->push_back(pReport->getSeparator().getCN());
              pHeader->push_back(CCopasiStaticString(compartments[j]->getSBMLId()).getCN());
              pHeader->push_back(pReport->getSeparator().getCN());
            }
        }

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

      const CCopasiVectorN<CModelValue>& parameters = pDataModel->getModel()->getModelValues();

      jMax = parameters.size();

      for (j = 0; j < jMax; ++j)
        {
          if (parameters[j]->getStatus() != CModelEntity::FIXED)
            {
              pFoot->push_back(parameters[j]->getObject(CCopasiObjectName("Reference=Value"))->getCN());
              pFoot->push_back(pReport->getSeparator().getCN());
              pHeader->push_back(CCopasiStaticString(parameters[j]->getSBMLId()).getCN());
              pHeader->push_back(pReport->getSeparator().getCN());
            }
        }

      /*
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
      pSSTask->setMethodType(CCopasiMethod::Newton);
      pSSTask->getProblem()->setModel(pDataModel->getModel());

      pSSTask->setScheduled(true);

      pSSTask->getReport().setReportDefinition(pReport);
      pSSTask->getReport().setTarget(CWD + "/" + pOutputFilename + ".res");
      pSSTask->getReport().setAppend(false);

      //**** specify problem ****
      CSteadyStateProblem* pProblem = dynamic_cast<CSteadyStateProblem*>(pSSTask->getProblem());

      //pProblem->setStepNumber((const unsigned C_INT32)stepNumber);
      //pDataModel->getModel()->setInitialTime((const C_FLOAT64)startTime);

      //**** method settings ****
      CSteadyStateMethod* pMethod = dynamic_cast<CSteadyStateMethod*>(pSSTask->getMethod());
      pMethod->getParameter("Maximum duration for forward integration")->setValue(1.0e5);
      pMethod->getParameter("Use Back Integration")->setValue(false);
      pMethod->getParameter("Maximum duration for backward integration")->setValue(1.0e3);

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

      // create another report that will write to the directory where the input file came from
      // this can be used for debugging
      // create a trajectory task

      //pSSTask->getReport().setTarget(pOutputFilename);

      pSSTask->initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL);
      pSSTask->process(true);
      pDataModel->finish();
      pSSTask->restore();
    }
  catch (CCopasiException Exception)
    {
      std::cerr << Exception.getMessage().getText() << std::endl;
    }

  //status output
  CSteadyStateMethod::ReturnCode rc = pSSTask->getResult();

  switch (rc)
    {
      case CSteadyStateMethod::notFound: std::cout << "###0 No steady state found." << std::endl; break;
      case CSteadyStateMethod::found: std::cout << "###1 Steady state found." << std::endl; break;
      case CSteadyStateMethod::foundEquilibrium: std::cout << "###2 Equilibrium found." << std::endl; break;
      case CSteadyStateMethod::foundNegative: std::cout << "###3 Negative steady state found." << std::endl; break;
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



  //write method log to separate file
  std::string methodlog = dynamic_cast<CSteadyStateMethod*>(pSSTask->getMethod())->getMethodLog();
  std::string logname = CWD + "/" + pOutputFilename + ".log";
  std::ofstream ofs(logname.c_str());
  ofs << methodlog;
  ofs.close();




  //finish
  CCopasiRootContainer::destroy();

  return 0;
}
