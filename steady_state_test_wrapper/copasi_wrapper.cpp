// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#define COPASI_MAIN

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "copasi/copasi.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CMetab.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CDataVector.h"
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

CReportDefinition* createReport(CDataModel* pDataModel, CReportDefinitionVector* pReports)
{
  CReportDefinition* pReport =  pReports->createReportDefinition("Report", "Output for batch run");
  pReport->setTaskType(CTaskEnum::Task::steadyState);
  pReport->setIsTable(false);
  pReport->setSeparator(", ");

  std::vector<CRegisteredCommonName>* pHeader = pReport->getHeaderAddr();
  std::vector<CRegisteredCommonName>* pBody = pReport->getBodyAddr();
  std::vector<CRegisteredCommonName>* pFoot = pReport->getFooterAddr();

  //Time is not needed for steady state
  //pBody->push_back(CCommonName(pDataModel->getModel()->getCN() + ",Reference=Time"));
  //pBody->push_back(CRegisteredCommonName(pReport->getSeparator().getCN()));
  //pHeader->push_back(CCopasiStaticString("time").getCN());
  //pHeader->push_back(pReport->getSeparator().getCN());

  const CDataVectorNS<CCompartment>& compartments = pDataModel->getModel()->getCompartments();
  unsigned int j, jMax = compartments.size();

  for (j = 0; j < jMax; ++j)
    {
      if (compartments[j].getStatus() != CModelEntity::Status::FIXED)
        {
          pFoot->push_back(compartments[j].getObject(CCommonName("Reference=Volume"))->getCN());
          pFoot->push_back(pReport->getSeparator().getCN());
          pHeader->push_back(CDataString(compartments[j].getSBMLId()).getCN());
          pHeader->push_back(pReport->getSeparator().getCN());
        }
    }

  const CDataVector<CMetab>& metabolites = pDataModel->getModel()->getMetabolites();

  jMax = metabolites.size();

  for (j = 0; j < jMax; ++j)
    {
      if (metabolites[j].getStatus() != CModelEntity::Status::FIXED)
        {
          pFoot->push_back(metabolites[j].getObject(CCommonName("Reference=Concentration"))->getCN());
          pFoot->push_back(pReport->getSeparator().getCN());
          pHeader->push_back(CDataString(metabolites[j].getSBMLId()).getCN());
          pHeader->push_back(pReport->getSeparator().getCN());
        }
    }

  const CDataVectorN<CModelValue>& parameters = pDataModel->getModel()->getModelValues();

  jMax = parameters.size();

  for (j = 0; j < jMax; ++j)
    {
      if (parameters[j].getStatus() != CModelEntity::Status::FIXED)
        {
          pFoot->push_back(parameters[j].getObject(CCommonName("Reference=Value"))->getCN());
          pFoot->push_back(pReport->getSeparator().getCN());
          pHeader->push_back(CDataString(parameters[j].getSBMLId()).getCN());
          pHeader->push_back(pReport->getSeparator().getCN());
        }
    }

  /*
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

  if ((*pFoot->rbegin()) == pReport->getSeparator().getCN())
    {
      pFoot->erase(--pFoot->end());
    }

  if ((*pHeader->rbegin()) == pReport->getSeparator().getCN())
    {
      pHeader->erase(--pHeader->end());
    }

  return pReport;
}

int main(int argc, char *argv[])
{
  // Parse the commandline options
  // 1. argument is the SBML filename
  // 2. argument is the filename where the results are to be written
  try
    {
      // Create the root container.
      CRootContainer::init(0, NULL, false);
    }

  catch (copasi::autoexcept &e)
    {}

  catch (copasi::option_error &e)
    {}

  if (argc < 3)
    {
      std::cout << "Usage: steady_state_test_wrapper SBMLFILENAME OUTPUTFILE_PREFIX" << std::endl;
      exit(1);
    }

  char* pSBMLFilename = argv[1];
  const char* pOutputFilename = argv[2];

  std::string CWD = COptions::getPWD();

  try
    {
      // Create the global data model.
      CDataModel* pDataModel = CRootContainer::addDatamodel();

      // Import the SBML File
      pDataModel->importSBML(pSBMLFilename);

      // create a report with the correct filename and all the species against
      // time.
      CReportDefinitionVector* pReports = pDataModel->getReportDefinitionList();
      CReportDefinition* pSteadyState = &(*pReports)["Steady-State"];

      CReportDefinition* pReport = createReport(pDataModel, pReports);

      //**** create a task ****

      CSteadyStateTask* pSSTask = new CSteadyStateTask(pDataModel->getTaskList());
      pSSTask->setMethodType(CTaskEnum::Method::Newton);
      pSSTask->getProblem()->setModel(pDataModel->getModel());

      pSSTask->setScheduled(true);

      pSSTask->getReport().setReportDefinition(pSteadyState);
      pSSTask->getReport().setTarget(pOutputFilename + std::string(".res1"));
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
      CDataVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();

      TaskList.remove("Steady-State");
      TaskList.add(pSSTask, true);

      // save the file for control purposes
      std::string saveFilename = pOutputFilename + std::string("1.cps");
      pDataModel->saveModel(saveFilename, NULL, true);

      pSSTask->getReport().setReportDefinition(pReport);
      pSSTask->getReport().setTarget(pOutputFilename + std::string(".res"));
      pSSTask->getReport().setAppend(false);

      // save the file for control purposes
      saveFilename = pOutputFilename + std::string(".cps");
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

      //status output
      CSteadyStateMethod::ReturnCode rc = pSSTask->getResult();

      std::string resultCode;

      switch (rc)
        {
          case CSteadyStateMethod::notFound: resultCode = "###0 No steady state found."; break;

          case CSteadyStateMethod::found: resultCode = "###1 Steady state found."; break;

          case CSteadyStateMethod::foundEquilibrium: resultCode = "###2 Equilibrium found."; break;

          case CSteadyStateMethod::foundNegative: resultCode = "###3 Negative steady state found."; break;
        }

      std::cout << resultCode << std::endl;

      std::string resultFileName = pOutputFilename + std::string(".txt");
      std::ofstream resultFile(resultFileName.c_str());
      resultFile << resultCode << std::endl;
      resultFile.close();

      //write method log to separate file
      std::string methodlog = dynamic_cast<CSteadyStateMethod*>(pSSTask->getMethod())->getMethodLog();
      std::string logname = pOutputFilename + std::string(".log");
      std::ofstream ofs(logname.c_str());
      ofs << methodlog;
      ofs.close();
    }
  catch (CCopasiException & Exception)
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

  //finish
  CRootContainer::destroy();

  return 0;
}
