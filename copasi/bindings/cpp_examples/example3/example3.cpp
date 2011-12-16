// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/cpp_examples/example3/example3.cpp,v $
//   $Revision: 1.1.6.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/12/16 07:06:51 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/**
 * This is an example on how to import an sbml file
 * create a report for a time course simulation
 * and run a time course simulation
 */

#include <iostream>
#include <string>

#define COPASI_MAIN

#include "copasi/copasi.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/report/CReport.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/trajectory/CTimeSeries.h"
#include "copasi/function/CFunctionDB.h"


int main(int argc, char** argv)
{
  // initialize the backend library
  CCopasiRootContainer::init(argc, argv);
  assert(CCopasiRootContainer::getRoot() != NULL);
  // create a new datamodel
  CCopasiDataModel* pDataModel = CCopasiRootContainer::addDatamodel();
  assert(CCopasiRootContainer::getDatamodelList()->size() == 1);

  // the only argument to the main routine should be the name of an SBML file
  if (argc == 2)
    {
      std::string filename = argv[1];

      try
        {
          // load the model without progress report
          pDataModel->importSBML(filename, NULL);
          //pDataModel->loadModel(filename, NULL);
        }
      catch (...)
        {
          std::cerr << "Error while importing the model from file named \"" << filename << "\"." << std::endl;
          CCopasiRootContainer::destroy();
          return 1;
        }

      CModel* pModel = pDataModel->getModel();
      assert(pModel != NULL);
      // create a report with the correct filename and all the species against
      // time.
      CReportDefinitionVector* pReports = pDataModel->getReportDefinitionList();
      // create a new report definition object
      CReportDefinition* pReport = pReports->createReportDefinition("Report", "Output for timecourse");
      // set the task type for the report definition to timecourse
      pReport->setTaskType(CCopasiTask::timeCourse);
      // we don't want a table
      pReport->setIsTable(false);
      // the entries in the output should be seperated by a ", "
      pReport->setSeparator(CCopasiReportSeparator(", "));

      // we need a handle to the header and the body
      // the header will display the ids of the metabolites and "time" for
      // the first column
      // the body will contain the actual timecourse data
      std::vector<CRegisteredObjectName>* pHeader = pReport->getHeaderAddr();
      std::vector<CRegisteredObjectName>* pBody = pReport->getBodyAddr();
      pBody->push_back(CCopasiObjectName(pDataModel->getModel()->getCN() + ",Reference=Time"));
      pBody->push_back(CRegisteredObjectName(pReport->getSeparator().getCN()));
      pHeader->push_back(CCopasiStaticString("time").getCN());
      pHeader->push_back(pReport->getSeparator().getCN());

      size_t i, iMax = pModel->getMetabolites().size();

      for (i = 0; i < iMax; ++i)
        {
          CMetab* pMetab = pModel->getMetabolites()[i];
          assert(pMetab != NULL);

          // we don't want output for FIXED metabolites right now
          if (pMetab->getStatus() != CModelEntity::FIXED)
            {
              // we want the concentration oin the output
              // alternatively, we could use "Reference=Amount" to get the
              // particle number
              pBody->push_back(pMetab->getObject(CCopasiObjectName("Reference=Concentration"))->getCN());
              // after each entry, we need a seperator
              pBody->push_back(pReport->getSeparator().getCN());

              // add the corresponding id to the header
              pHeader->push_back(CCopasiStaticString(pMetab->getSBMLId()).getCN());
              // and a seperator
              pHeader->push_back(pReport->getSeparator().getCN());
            }
        }

      if (iMax > 0)
        {
          // delete the last separator
          // since we don't need one after the last element on each line
          if ((*pBody->rbegin()) == pReport->getSeparator().getCN())
            {
              pBody->erase(--pBody->end());
            }

          if ((*pHeader->rbegin()) == pReport->getSeparator().getCN())
            {
              pHeader->erase(--pHeader->end());
            }
        }

      // get the task list
      CCopasiVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();

      // get the trajectory task object
      CTrajectoryTask* pTrajectoryTask = dynamic_cast<CTrajectoryTask*>(TaskList["Time-Course"]);

      // if there isn't one
      if (pTrajectoryTask == NULL)
        {
          // create a new one
          pTrajectoryTask = new CTrajectoryTask();
          // remove any existing trajectory task just to be sure since in
          // theory only the cast might have failed above
          TaskList.remove("Time-Course");

          // add the new time course task to the task list
          TaskList.add(pTrajectoryTask, true);
        }

      // run a deterministic time course
      pTrajectoryTask->setMethodType(CCopasiMethod::deterministic);

      // pass a pointer of the model to the problem
      pTrajectoryTask->getProblem()->setModel(pDataModel->getModel());

      // actiavate the task so that it will be run when the model is saved
      // and passed to CopasiSE
      pTrajectoryTask->setScheduled(true);

      // set the report for the task
      pTrajectoryTask->getReport().setReportDefinition(pReport);
      // set the output filename
      pTrajectoryTask->getReport().setTarget("example3.txt");
      // don't append output if the file exists, but overwrite the file
      pTrajectoryTask->getReport().setAppend(false);

      // get the problem for the task to set some parameters
      CTrajectoryProblem* pProblem = dynamic_cast<CTrajectoryProblem*>(pTrajectoryTask->getProblem());

      // simulate 100 steps
      pProblem->setStepNumber(100);
      // start at time 0
      pDataModel->getModel()->setInitialTime(0.0);
      // simulate a duration of 10 time units
      pProblem->setDuration(10);
      // tell the problem to actually generate time series data
      pProblem->setTimeSeriesRequested(true);

      // set some parameters for the LSODA method through the method
      CTrajectoryMethod* pMethod = dynamic_cast<CTrajectoryMethod*>(pTrajectoryTask->getMethod());

      CCopasiParameter* pParameter = pMethod->getParameter("Absolute Tolerance");
      assert(pParameter != NULL);
      pParameter->setValue(1.0e-12);


      try
        {
          // initialize the trajectory task
          // we want complete output (HEADER, BODY and FOOTER)
          //
          // The output has to be set to OUTPUT_UI, otherwise the time series will not be
          // kept in memory and some of the assert further down will fail
          // If it is OK that the output is only written to file, the output type can
          // be set to OUTPUT_SE
          pTrajectoryTask->initialize(CCopasiTask::OUTPUT_UI, pDataModel, NULL);
          // now we run the actual trajectory
          pTrajectoryTask->process(true);
        }
      catch (...)
        {
          std::cerr << "Error. Running the time course simulation failed." << std::endl;

          // check if there are additional error messages
          if (CCopasiMessage::size() > 0)
            {
              // print the messages in chronological order
              std::cerr << CCopasiMessage::getAllMessageText(true);
            }

          CCopasiRootContainer::destroy();
          return 1;
        }

      // restore the state of the trajectory
      pTrajectoryTask->restore();

      // look at the timeseries
      const CTimeSeries* pTimeSeries = &pTrajectoryTask->getTimeSeries();
      // we simulated 100 steps, including the initial state, this should be
      // 101 step in the timeseries
      assert(pTimeSeries->getRecordedSteps() == 101);
      std::cout << "The time series consists of " << pTimeSeries->getRecordedSteps() << "." << std::endl;
      std::cout << "Each step contains " << pTimeSeries->getNumVariables() << " variables." << std::endl;
      std::cout << "The final state is: " << std::endl;
      iMax = pTimeSeries->getNumVariables();
      size_t lastIndex = pTimeSeries->getRecordedSteps() - 1;

      for (i = 0; i < iMax; ++i)
        {
          // here we get the particle number (at least for the species)
          // the unit of the other variables may not be particle numbers
          // the concentration data can be acquired with getConcentrationData
          std::cout << pTimeSeries->getTitle(i) << ": " << pTimeSeries->getData(lastIndex, i) << std::endl;
        }

    }
  else
    {
      std::cerr << "Usage: example3 SBMLFILE" << std::endl;
      CCopasiRootContainer::destroy();
      return 1;
    }

  // clean up the library
  CCopasiRootContainer::destroy();
}
