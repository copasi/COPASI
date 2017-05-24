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
 * This is an example on how to run an parameter fitting task.
 * The example creates a simple model and runs a time course simulation on it.
 * The timecourse data is written to file with some noise added to it.
 * This data is used to fit the original parameters.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cmath>
#include <assert.h>
#include <stdlib.h>

#define COPASI_MAIN

#include "copasi/copasi.h"
#include "copasi/commandline/COptions.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/parameterFitting/CFitTask.h"
#include "copasi/optimization/COptMethod.h"
#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/parameterFitting/CFitItem.h"
#include "copasi/parameterFitting/CExperimentSet.h"
#include "copasi/parameterFitting/CExperiment.h"
#include "copasi/parameterFitting/CExperimentObjectMap.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"

extern const char* MODEL_STRING;

int main()
{
  // initialize the backend library
  CRootContainer::init(0, NULL);
  assert(CRootContainer::getRoot() != NULL);

  // create a new datamodel
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  assert(CRootContainer::getDatamodelList()->size() == 1);

  // first we load a simple model
  try
    {
      // load the model
      pDataModel->importSBMLFromString(MODEL_STRING);
      // we clear the message stack to get rid of all error messages
      // this is important because otherwise the initialization of the
      // fit task will fail
      CCopasiMessage::clearDeque();
    }
  catch (...)
    {
      std::cerr <<  "Error while importing the model." << std::endl;
      exit(1);
    }

  // now we need to run some time course simulation to get data to fit
  // against

  // get the trajectory task object
  CDataVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();

  // get the optimization task
  CTrajectoryTask* pTrajectoryTask = dynamic_cast<CTrajectoryTask*>(&TaskList["Time-Course"]);
  assert(pTrajectoryTask != NULL);

  // if there isn't one
  if (pTrajectoryTask == NULL)
    {
      // remove any existing steadystate task just to be sure since in
      // theory only the cast might have failed above
      TaskList.remove("Time-Course");

      // create a new one
      pTrajectoryTask = new CTrajectoryTask(& TaskList);

      // add the new time course task to the task list
      pDataModel->getTaskList()->add(pTrajectoryTask);
    }

  // run a deterministic time course
  pTrajectoryTask->setMethodType(CTaskEnum::Method::deterministic);

  // activate the task so that it will be run when the model is saved
  // and passed to CopasiSE
  pTrajectoryTask->setScheduled(true);

  // get the problem for the task to set some parameters
  CTrajectoryProblem* pProblem = dynamic_cast<CTrajectoryProblem*>(pTrajectoryTask->getProblem());

  // simulate 4000 steps
  pProblem->setStepNumber(4000);
  // start at time 0
  pDataModel->getModel()->setInitialTime(0.0);
  // simulate a duration of 400 time units
  pProblem->setDuration(400);
  // tell the problem to actually generate time series data
  pProblem->setTimeSeriesRequested(true);

  bool result = true;

  try
    {
      // now we run the actual trajectory
      pTrajectoryTask->initialize(CCopasiTask::OUTPUT_UI, pDataModel, NULL);
      result = pTrajectoryTask->process(true);
    }
  catch (...)
    {
      std::cerr <<  "Error. Running the time course simulation failed." << std::endl;

      // check if there are additional error messages
      if (CCopasiMessage::size() > 0)
        {
          // print the messages in chronological order
          std::cerr << CCopasiMessage::getAllMessageText(true) << std::endl;
        }

      // clean up the library
      CRootContainer::destroy();
      exit(1);
    }

  if (result == false)
    {
      std::cerr <<  "An error occured while running the time course simulation." << std::endl;

      // check if there are additional error messages
      if (CCopasiMessage::size() > 0)
        {
          // print the messages in chronological order
          std::cerr << CCopasiMessage::getAllMessageText(true) << std::endl;
        }

      // clean up the library
      CRootContainer::destroy();
      exit(1);
    }

  // restore the trajectory task state
  pTrajectoryTask->restore();

  // we write the data to a file and add some noise to it
  // This is necessary since COPASI can only read experimental data from
  // file.
  const CTimeSeries* pTimeSeries = &pTrajectoryTask->getTimeSeries();
  // we simulated 4000 steps, including the initial state, this should be
  // 4001 step in the timeseries
  assert(pTimeSeries->getRecordedSteps() == 4001);
  size_t i, iMax = pTimeSeries->getNumVariables();
  // there should be four variables, the three metabolites and time
  assert(iMax == 4);

  size_t lastIndex = pTimeSeries->getRecordedSteps() - 1;
  // open the file
  // we need to remember in which order the variables are written to file
  // since we need to specify this later in the parameter fitting task
  std::set<size_t> indexSet;
  std::vector<CMetab*> metabVector;

  // write the header
  // the first variable in a time series is a always time, for the rest
  // of the variables, we use the SBML id in the header
  double random = 0.0;

  try
    {
      std::ofstream os("fakedata_example6.txt", std::ios_base::out | std::ios_base::trunc);
      os << ("# time ");

      for (i = 1; i < iMax; ++i)
        {
          std::string key = pTimeSeries->getKey(i);
          CDataObject* pObject = CRootContainer::getKeyFactory()->get(key);
          assert(pObject != NULL);

          // only write header data or metabolites
          if (dynamic_cast<const CMetab*>(pObject))
            {
              os << ", ";
              os << pTimeSeries->getSBMLId(i, pDataModel);
              CMetab* pM = dynamic_cast<CMetab*>(pObject);
              indexSet.insert(i);
              metabVector.push_back(pM);
            }
        }

      os << std::endl;
      double data = 0.0;

      for (i = 0; i < lastIndex; ++i)
        {
          size_t j;
          std::ostringstream s;

          for (j = 0; j < iMax; ++j)
            {
              // we only want to  write the data for metabolites
              // the compartment does not interest us here
              if (j == 0 || indexSet.find(j) != indexSet.end())
                {
                  // write the data with some noise (+-5% max)
                  random = ((double)rand()) / (double)RAND_MAX;
                  data = pTimeSeries->getConcentrationData(i, j);

                  // don't add noise to the time
                  if (j != 0)
                    {
                      data += data * (random * 0.1 - 0.05);
                    }

                  s << data;
                  s << ", ";
                }
            }

          // remove the last two characters again
          os << s.str().substr(0, s.str().length() - 2);
          os << std::endl;
        }

      os.close();
    }
  catch (const std::exception& e)
    {
      std::cerr << "Error. Could not write time course data to file." << std::endl;
      std::cout << e.what() << std::endl;
      exit(1);
    }

  // now we change the parameter values to see if the parameter fitting
  // can really find the original values
  random = (double)rand() / (double)RAND_MAX * 10.0;
  CReaction* pReaction = &pDataModel->getModel()->getReactions()[0];
  // we know that it is an irreversible mass action, so there is one
  // parameter
  assert(pReaction->getParameters().size() == 1);
  assert(pReaction->isLocalParameter(0));
  // the parameter of a irreversible mass action is called k1
  pReaction->setParameterValue("k1", random);

  pReaction = &pDataModel->getModel()->getReactions()[1];
  // we know that it is an irreversible mass action, so there is one
  // parameter
  assert(pReaction->getParameters().size() == 1);
  assert(pReaction->isLocalParameter(0));
  pReaction->setParameterValue("k1", random);

  CFitTask* pFitTask = dynamic_cast<CFitTask*>(&TaskList["Parameter Estimation"]);
  assert(pFitTask != NULL);
  // the method in a fit task is an instance of COptMethod or a subclass of
  // it.
  COptMethod* pFitMethod = dynamic_cast<COptMethod*>(pFitTask->getMethod());
  assert(pFitMethod != NULL);
  // the object must be an instance of COptMethod or a subclass thereof
  // (CFitMethod)
  CFitProblem* pFitProblem = dynamic_cast<CFitProblem*>(pFitTask->getProblem());
  assert(pFitProblem != NULL);

  CExperimentSet* pExperimentSet = dynamic_cast<CExperimentSet*>(pFitProblem->getParameter("Experiment Set"));
  assert(pExperimentSet != NULL);

  // first experiment (we only have one here)
  CExperiment* pExperiment = new CExperiment(pDataModel);
  assert(pExperiment != NULL);
  // tell COPASI where to find the data
  // reading data from string is not possible with the current C++ API
  pExperiment->setFileName("fakedata_example6.txt");
  // we have to tell COPASI that the data for the experiment is a komma
  // separated list (the default is TAB separated)
  pExperiment->setSeparator(",");
  // the data start in row 1 and goes to row 4001
  pExperiment->setFirstRow((unsigned C_INT32) 1);
  assert(pExperiment->getFirstRow() == 1);
  pExperiment->setLastRow(4001);
  assert(pExperiment->getLastRow() == 4001);
  pExperiment->setHeaderRow(1);
  assert(pExperiment->getHeaderRow() == 1);
  pExperiment->setExperimentType(CTaskEnum::Task::timeCourse);
  assert(pExperiment->getExperimentType() == CTaskEnum::Task::timeCourse);
  pExperiment->setNumColumns(4);
  assert(pExperiment->getNumColumns() == 4);
  CExperimentObjectMap* pObjectMap = &pExperiment->getObjectMap();
  assert(pObjectMap != NULL);
  result = pObjectMap->setNumCols(4);
  assert(result == true);
  result = pObjectMap->setRole(0, CExperiment::time);
  assert(result == true);
  assert(pObjectMap->getRole(0) == CExperiment::time);

  CModel* pModel = pDataModel->getModel();
  assert(pModel != NULL);
  const CDataObject* pTimeReference = pModel->getValueReference();
  assert(pTimeReference != NULL);
  pObjectMap->setObjectCN(0, pTimeReference->getCN());

  // now we tell COPASI which column contain the concentrations of
  // metabolites and belong to dependent variables
  pObjectMap->setRole(1, CExperiment::dependent);
  CMetab* pMetab = metabVector[0];
  assert(pMetab != NULL);
  const CDataObject* pParticleReference = pMetab->getConcentrationReference();
  assert(pParticleReference != NULL);
  pObjectMap->setObjectCN(1, pParticleReference->getCN());

  pObjectMap->setRole(2, CExperiment::dependent);
  pMetab = metabVector[1];
  assert(pMetab != NULL);
  pParticleReference = pMetab->getConcentrationReference();
  assert(pParticleReference != NULL);
  pObjectMap->setObjectCN(2, pParticleReference->getCN());

  pObjectMap->setRole(3, CExperiment::dependent);
  pMetab = metabVector[2];
  assert(pMetab != NULL);
  pParticleReference = pMetab->getConcentrationReference();
  assert(pParticleReference != NULL);
  pObjectMap->setObjectCN(3, pParticleReference->getCN());

  pExperimentSet->addExperiment(*pExperiment);
  assert(pExperimentSet->getExperimentCount() == 1);
  // addExperiment makes a copy, so we need to get the added experiment
  // again
  delete pExperiment;
  pExperiment = pExperimentSet->getExperiment(0);
  assert(pExperiment != NULL);

  // now we have to define the two fit items for the two local parameters
  // of the two reactions
  pReaction = &pModel->getReactions()[0];
  assert(pReaction != NULL);
  assert(pReaction->isLocalParameter(0) == true);
  CCopasiParameter* pParameter = pReaction->getParameters().getParameter(0);
  assert(pParameter != NULL);

  // get the list where we have to add the fit items
  CCopasiParameterGroup* pOptimizationItemGroup = dynamic_cast<CCopasiParameterGroup*>(pFitProblem->getParameter("OptimizationItemList"));
  assert(pOptimizationItemGroup != NULL);

  // define a CFitItem
  const CDataObject* pParameterReference = pParameter->getValueReference();
  assert(pParameterReference != NULL);
  CFitItem* pFitItem1 = new CFitItem(pDataModel);
  pFitItem1->setObjectCN(pParameterReference->getCN());
  assert(pFitItem1 != NULL);
  pFitItem1->setStartValue(4.0);
  pFitItem1->setLowerBound(CCommonName("0.00001"));
  pFitItem1->setUpperBound(CCommonName("10"));
  // add the fit item
  pOptimizationItemGroup->addParameter(pFitItem1);

  pReaction = &pModel->getReactions()[1];
  assert(pReaction != NULL);
  assert(pReaction->isLocalParameter(0) == true);
  pParameter = pReaction->getParameters().getParameter(0);
  assert(pParameter != NULL);

  // define a CFitItem
  pParameterReference = pParameter->getValueReference();
  assert(pParameterReference != NULL);
  CFitItem* pFitItem2 = new CFitItem(pDataModel);
  pFitItem2->setObjectCN(pParameterReference->getCN());
  assert(pFitItem2 != NULL);
  pFitItem2->setStartValue(4.0);
  pFitItem2->setLowerBound(CCommonName("0.00001"));
  pFitItem2->setUpperBound(CCommonName("10"));
  // add the fit item
  pOptimizationItemGroup->addParameter(pFitItem2);

  result = true;

  try
    {
      // initialize the fit task
      // we want complete output (HEADER, BODY and FOOTER)
      result = pFitTask->initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL);

      if (result == true)
        {
          // running the task for this example will probably take some time
          std::cout << "This can take some time..." << std::endl;
          result = pFitTask->process(true);
        }
    }
  catch (...)
    {
      std::cerr << "Error. Parameter fitting failed." << std::endl;

      // clean up the library
      CRootContainer::destroy();
      exit(1);
    }

  pFitTask->restore();
  assert(result == true);
  // assert that there are two optimization items
  assert(pFitProblem->getOptItemList().size() == 2);
  // the order should be the order in whih we added the items above
  COptItem* pOptItem1 = pFitProblem->getOptItemList()[0];
  COptItem* pOptItem2 = pFitProblem->getOptItemList()[1];
  // the actual results are stored in the fit problem
  assert(pFitProblem->getSolutionVariables().size() == 2);
  std::cout << "value for " << pOptItem1->getObject()->getCN() << ": " << pFitProblem->getSolutionVariables()[0] << std::endl;
  std::cout << "value for " << pOptItem2->getObject()->getCN() << ": " << pFitProblem->getSolutionVariables()[1] << std::endl;
  // depending on the noise, the fit can be quite bad, so we are a litle
  // relaxed here (we should be within 3% of the original values)
  assert((fabs(pFitProblem->getSolutionVariables()[0] - 0.03) / 0.03) < 3e-2);
  assert((fabs(pFitProblem->getSolutionVariables()[1] - 0.004) / 0.004) < 3e-2);

  // clean up the library
  CRootContainer::destroy();
}

const char* MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- Created by COPASI version 4.5.30 (Debug) on 2009-03-30 08:01 with libSBML version 3.3.2. -->\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"litre\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"mole\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"5\"/>\n"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n"
  "      <species id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n"
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
  "            <parameter id=\"k1\" name=\"k1\" value=\"0.03\"/>\n"
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
  "            <parameter id=\"k1\" name=\"k1\" value=\"0.004\"/>\n"
  "          </listOfParameters>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>";
