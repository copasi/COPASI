// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

/**
 * This is an example on how to import an sbml model from a string
 * create a report for a time course simulation
 * and run a scan for a stochastic time course simulation
 */

#include <iostream>
#include <string>

#define COPASI_MAIN

#include "copasi/copasi.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/report/CReport.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/scan/CScanTask.h"
#include "copasi/scan/CScanMethod.h"
#include "copasi/scan/CScanProblem.h"

extern const char* MODEL_STRING;

int main()
{
  // initialize the backend library
  CRootContainer::init(0, NULL);
  assert(CRootContainer::getRoot() != NULL);
  // create a new datamodel
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  assert(CRootContainer::getDatamodelList()->size() == 1);

  // the only argument to the main routine should be the name of an SBML file
  try
    {
      // load the model without progress report
      pDataModel->importSBMLFromString(MODEL_STRING, NULL);
    }
  catch (...)
    {
      std::cerr << "Error while importing the model from the given string." << std::endl;
      CRootContainer::destroy();
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
  pReport->setTaskType(CTaskEnum::Task::timeCourse);
  // we don't want a table
  pReport->setIsTable(false);
  // the entries in the output should be seperated by a ", "
  pReport->setSeparator(", ");

  // we need a handle to the header and the body
  // the header will display the ids of the metabolites and "time" for
  // the first column
  // the body will contain the actual timecourse data
  std::vector<CRegisteredCommonName>* pHeader = pReport->getHeaderAddr();
  std::vector<CRegisteredCommonName>* pBody = pReport->getBodyAddr();
  pBody->push_back(CCommonName(pDataModel->getModel()->getCN() + ",Reference=Time"));
  pBody->push_back(CRegisteredCommonName(pReport->getSeparator().getCN()));
  pHeader->push_back(CDataString("time").getCN());
  pHeader->push_back(pReport->getSeparator().getCN());

  size_t i, iMax = pModel->getMetabolites().size();

  for (i = 0; i < iMax; ++i)
    {
      CMetab* pMetab = &pModel->getMetabolites()[i];
      assert(pMetab != NULL);

      // we don't want output for FIXED metabolites right now
      if (pMetab->getStatus() != CModelEntity::Status::FIXED)
        {
          // we want the concentration oin the output
          // alternatively, we could use "Reference=Amount" to get the
          // particle number
          pBody->push_back(pMetab->getObject(CCommonName("Reference=Concentration"))->getCN());
          // after each entry, we need a seperator
          pBody->push_back(pReport->getSeparator().getCN());

          // add the corresponding id to the header
          pHeader->push_back(CDataString(pMetab->getSBMLId()).getCN());
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
  CDataVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();

  // get the trajectory task object
  CTrajectoryTask* pTrajectoryTask = dynamic_cast<CTrajectoryTask*>(&TaskList["Time-Course"]);

  // if there isn't one
  if (pTrajectoryTask == NULL)
    {
      // remove any existing trajectory task just to be sure since in
      // theory only the cast might have failed above
      TaskList.remove("Time-Course");

      // create a new one
      pTrajectoryTask = new CTrajectoryTask(& TaskList);

      // add the new time course task to the task list
      TaskList.add(pTrajectoryTask, true);
    }

  // run a stochastic time course
  pTrajectoryTask->setMethodType(CTaskEnum::Method::stochastic);

  // we don't want the trajectory task to run by itself, but we want to
  // run it from a scan, so we deactivate the standalone trajectory task
  pTrajectoryTask->setScheduled(false);

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

  // now we set up the scan
  CScanTask* pScanTask = dynamic_cast<CScanTask*>(&TaskList["Scan"]);

  if (pScanTask == NULL)
    {
      // just to be on the save side, delete any existing scan task
      TaskList.remove("Scan");

      // create a new scan task
      pScanTask = new CScanTask(& TaskList);

      // add the new scan task
      TaskList.add(pScanTask, true);
    }

  // get the problem
  CScanProblem* pScanProblem = dynamic_cast<CScanProblem*>(pScanTask->getProblem());
  assert(pScanProblem != NULL);

  // Activate the task so that is is run
  // if the model is saved and passed to CopasiSE
  pScanTask->setScheduled(true);

  // set the report for the task
  pScanTask->getReport().setReportDefinition(pReport);

  // set the output file for the report
  pScanTask->getReport().setTarget("example4.txt");
  // don't append to an existing file, but overwrite
  pScanTask->getReport().setAppend(false);

  // tell the scan that we want to make a scan over a trajectory task
  pScanProblem->setSubtask(CTaskEnum::Task::timeCourse);

  // we just want to run the timecourse task a number of times, so we
  // create a repeat item with 100 repeats
  pScanProblem->addScanItem(CScanProblem::SCAN_REPEAT, 100);

  // we want the output from the trajectory task
  pScanProblem->setOutputInSubtask(true);

  // we don't want to set the initial conditions of the model to the end
  // state of the last run
  pScanProblem->setContinueFromCurrentState(false);

  try
    {
      // initialize the trajectory task
      // we want complete output (HEADER, BODY and FOOTER)
      pScanTask->initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL);
      // now we run the actual trajectory
      pScanTask->process(true);
    }
  catch (...)
    {
      std::cerr << "Error. Running the scan failed." << std::endl;

      // check if there are additional error messages
      if (CCopasiMessage::size() > 0)
        {
          // print the messages in chronological order
          std::cerr << CCopasiMessage::getAllMessageText(true);
        }

      CRootContainer::destroy();
      return 1;
    }

  // restore the state of the trajectory
  pScanTask->restore();

  // clean up the library
  CRootContainer::destroy();
}

const char* MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- Created by COPASI version 4.4.29 (Debug) on 2009-03-05 14:41 with libSBML version 3.3.0. -->\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"litre\" scale=\"-6\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"mole\" scale=\"-9\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species metaid=\"COPASI2\" id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1e-10\">\n"
  "      </species>\n"
  "      <species metaid=\"COPASI3\" id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"0\">\n"
  "      </species>\n"
  "      <species metaid=\"COPASI4\" id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"0\">\n"
  "      </species>\n"
  "    </listOfSpecies>\n"
  "    <listOfReactions>\n"
  "      <reaction id=\"reaction_1\" name=\"reaction\" reversible=\"false\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_1\"/>\n"
  "        </listOfReactants>\n"
  "        <listOfProducts>\n"
  "          <speciesReference species=\"species_2\"/>\n"
  "        </listOfProducts>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <ci> compartment_1 </ci>\n"
  "              <ci> k1 </ci>\n"
  "              <ci> species_1 </ci>\n"
  "            </apply>\n"
  "          </math>\n"
  "          <listOfParameters>\n"
  "            <parameter id=\"k1\" value=\"0.1\"/>\n"
  "          </listOfParameters>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "      <reaction id=\"reaction_2\" name=\"reaction_1\" reversible=\"false\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_2\"/>\n"
  "        </listOfReactants>\n"
  "        <listOfProducts>\n"
  "          <speciesReference species=\"species_3\"/>\n"
  "        </listOfProducts>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <ci> compartment_1 </ci>\n"
  "              <ci> k1 </ci>\n"
  "              <ci> species_2 </ci>\n"
  "            </apply>\n"
  "          </math>\n"
  "          <listOfParameters>\n"
  "            <parameter id=\"k1\" value=\"0.1\"/>\n"
  "          </listOfParameters>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n";
