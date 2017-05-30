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

#include "test000087.h"

#include <sstream>
#include <limits>

#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CModelValue.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeObject.h"
#include "copasi/function/CExpression.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/trajectory/CTrajectoryMethod.h"

#include <sbml/SBMLDocument.h>
#include <sbml/Model.h>
#include <sbml/Species.h>
#include <sbml/Reaction.h>
#include <sbml/Rule.h>
#include <sbml/math/ASTNode.h>

CDataModel* test000087::pCOPASIDATAMODEL = NULL;

void test000087::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000087::tearDown()
{
  CRootContainer::destroy();
}

void test000087::test_import_reaction_flux_reference_1()
{
  try
    {
      CPPUNIT_ASSERT(pCOPASIDATAMODEL->importSBMLFromString(test000087::MODEL_STRING1));
    }
  catch (...)
    {
      // there should be an exception (MCSBML + 81)
      unsigned int i, iMax = CCopasiMessage::size();
      CCopasiMessage message;
      bool found81 = false;

      for (i = 0; i < iMax; ++i)
        {
          message = CCopasiMessage::getLastMessage();

          if (message.getNumber() == MCSBML + 81)
            {
              found81 = true;
              break;
            }
        }

      CPPUNIT_ASSERT(found81 == true);
      return;
    }

  // we should never get here
  CPPUNIT_ASSERT(false);
}

void test000087::test_import_reaction_flux_reference_2()
{
  try
    {
      CPPUNIT_ASSERT(pCOPASIDATAMODEL->importSBMLFromString(test000087::MODEL_STRING2));
    }
  catch (...)
    {
      // there should not be an exception
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(pCOPASIDATAMODEL->getModel() != NULL);
  CPPUNIT_ASSERT(pCOPASIDATAMODEL->getModel()->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pCOPASIDATAMODEL->getModel()->getMetabolites().size() == 2);
  CPPUNIT_ASSERT(pCOPASIDATAMODEL->getModel()->getModelValues().size() == 1);
  CPPUNIT_ASSERT(pCOPASIDATAMODEL->getModel()->getReactions().size() == 1);
  const CReaction* pReaction = pCOPASIDATAMODEL->getModel()->getReactions()[0];
  CPPUNIT_ASSERT(pReaction != NULL);
  const CModelValue* pMV = pCOPASIDATAMODEL->getModel()->getModelValues()[0];
  CPPUNIT_ASSERT(pMV != NULL);
  CPPUNIT_ASSERT(pMV->getStatus() == CModelEntity::Status::ASSIGNMENT);
  const CExpression* pExpr = pMV->getExpressionPtr();
  CPPUNIT_ASSERT(pExpr != NULL);
  const CEvaluationNode* pRoot = pExpr->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->mainType() == CEvaluationNode::MainType::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pRoot);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  const CRegisteredCommonName cn = pObjectNode->getObjectCN();
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(pCOPASIDATAMODEL->getModel());
  const CDataObject* pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, cn));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == "Flux");
  CPPUNIT_ASSERT(pObject->getObjectParent() == pReaction);
}

void test000087::test_import_reaction_flux_reference_3()
{
  try
    {
      CPPUNIT_ASSERT(pCOPASIDATAMODEL->importSBMLFromString(test000087::MODEL_STRING3));
    }
  catch (...)
    {
      // there should be an exception (MCSBML + 81)
      unsigned int i, iMax = CCopasiMessage::size();
      CCopasiMessage message;
      bool found80 = false;

      for (i = 0; i < iMax; ++i)
        {
          message = CCopasiMessage::getLastMessage();

          if (message.getNumber() == MCSBML + 80)
            {
              found80 = true;
              break;
            }
        }

      CPPUNIT_ASSERT(found80 == true);
      return;
    }

  // we should never get here
  CPPUNIT_ASSERT(false);
}

void test000087::test_export_reaction_flux_reference_1()
{
  try
    {
      std::istringstream iss(test000087::MODEL_STRING4);
      bool result = load_cps_model_from_stream(iss, *pCOPASIDATAMODEL);
      CPPUNIT_ASSERT(result == true);
      CPPUNIT_ASSERT(pCOPASIDATAMODEL->getModel() != NULL);
    }
  catch (...)
    {
      // there should be no exception
      CPPUNIT_ASSERT(false);
    }

  try
    {
      CPPUNIT_ASSERT(pCOPASIDATAMODEL->exportSBMLToString(NULL, 2, 3).empty() == false);
    }
  catch (...)
    {
      // there should be no exception
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(CCopasiMessage::size() == 0);
  const SBMLDocument* pDocument = pCOPASIDATAMODEL->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  CPPUNIT_ASSERT(pDocument->getLevel() == 2);
  CPPUNIT_ASSERT(pDocument->getVersion() == 3);
  const Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getListOfFunctionDefinitions()->size() == 0);
  CPPUNIT_ASSERT(pModel->getListOfCompartments()->size() == 1);
  CPPUNIT_ASSERT(pModel->getListOfSpecies()->size() == 3);
  CPPUNIT_ASSERT(pModel->getListOfReactions()->size() == 1);
  CPPUNIT_ASSERT(pModel->getListOfRules()->size() == 1);
  const Reaction* pReaction = pModel->getReaction(0);
  CPPUNIT_ASSERT(pReaction != NULL);
  std::string reactionId = pReaction->getId();
  CPPUNIT_ASSERT(reactionId.empty() == false);
  const Rule* pRule = pModel->getRule(0);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  const AssignmentRule* pAssignmentRule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pAssignmentRule != NULL);
  const Species* pSpecies = pModel->getSpecies(pAssignmentRule->getVariable());
  CPPUNIT_ASSERT(pSpecies != NULL);
  CPPUNIT_ASSERT(pSpecies->getName() == "C");
  const ASTNode* pMath = pAssignmentRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == reactionId);
}

void test000087::test_export_reaction_flux_reference_2()
{
  try
    {
      std::istringstream iss(test000087::MODEL_STRING4);
      bool result = load_cps_model_from_stream(iss, *pCOPASIDATAMODEL);
      CPPUNIT_ASSERT(result == true);
      CPPUNIT_ASSERT(pCOPASIDATAMODEL->getModel() != NULL);
    }
  catch (...)
    {
      // there should be no exception
      CPPUNIT_ASSERT(false);
    }

  try
    {
      std::string result = pCOPASIDATAMODEL->exportSBMLToString(NULL, 2, 1);
      CPPUNIT_ASSERT(result.empty());
    }
  catch (...)
    {
      // there should be an exception
      // check if the correct error message has been created
      CPPUNIT_ASSERT(pCOPASIDATAMODEL->getCurrentSBMLDocument() == NULL);
      // last message should be an exception
      CCopasiMessage message = CCopasiMessage::getLastMessage();
      CPPUNIT_ASSERT(message.getType() == CCopasiMessage::EXCEPTION);
      // see if the incompatibility message is there
      bool found = false;

      while (CCopasiMessage::size() > 0)
        {
          message = CCopasiMessage::getLastMessage();

          if (message.getType() == CCopasiMessage::RAW)
            {
              std::string s = message.getText();

              if (s.find(std::string("SBML Incompatibility (10)")) != std::string::npos)
                {
                  found = true;
                  break;
                }
            }
        }

      CPPUNIT_ASSERT_MESSAGE("Error message not found.", found == true);
      return;
    }

  CPPUNIT_ASSERT(false);
}

void test000087::test_simulate_reaction_flux_reference_1()
{
  try
    {
      bool result = pCOPASIDATAMODEL->importSBMLFromString(test000087::MODEL_STRING5);
      CPPUNIT_ASSERT(result = true);
    }
  catch (...)
    {
      // there should be no exception
      CPPUNIT_ASSERT(false);
    }

  CModel* pModel = pCOPASIDATAMODEL->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 2);
  CPPUNIT_ASSERT(pModel->getReactions().size() == 1);
  const CReaction* pReaction = pModel->getReactions()[0];
  CPPUNIT_ASSERT(pReaction != NULL);
  CModelValue* pConstParameter = NULL;
  CModelValue* pNonConstParameter = NULL;
  unsigned int i, iMax = pModel->getModelValues().size();

  for (i = 0; i < iMax; ++i)
    {
      if (pModel->getModelValues()[i]->getStatus() == CModelEntity::Status::FIXED)
        {
          pConstParameter = pModel->getModelValues()[i];
        }

      if (pModel->getModelValues()[i]->getStatus() == CModelEntity::Status::ASSIGNMENT)
        {
          pNonConstParameter = pModel->getModelValues()[i];
        }
    }

  CPPUNIT_ASSERT(pConstParameter != NULL);
  CPPUNIT_ASSERT(pNonConstParameter != NULL);
  // check if the kinetic law is mass action with const global parameter as the kinetic constant
  CPPUNIT_ASSERT(pReaction->getChemEq().getSubstrates().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getProducts().size() == 1);
  CPPUNIT_ASSERT(pReaction->getChemEq().getModifiers().size() == 0);
  CPPUNIT_ASSERT(pReaction->isReversible() == false);
  const CFunction* pKineticLaw = pReaction->getFunction();
  CPPUNIT_ASSERT(pKineticLaw != NULL);
  CPPUNIT_ASSERT(pKineticLaw->getType() == CEvaluationTree::MassAction);
  const std::vector< std::vector<std::string> > & parameterMappings = pReaction->getParameterMappings();
  CPPUNIT_ASSERT(parameterMappings.size() == 2);
  CPPUNIT_ASSERT(parameterMappings[0].size() == 1);
  CPPUNIT_ASSERT(parameterMappings[0][0] == pConstParameter->getKey());
  CPPUNIT_ASSERT(parameterMappings[1].size() == 1);
  std::string substrateKey = parameterMappings[1][0];
  const CDataObject* pTempObject = CRootContainer::getKeyFactory()->get(substrateKey);
  CPPUNIT_ASSERT(pTempObject != NULL);
  const CMetab* pSubstrate = dynamic_cast<const CMetab*>(pTempObject);
  CPPUNIT_ASSERT(pSubstrate != NULL);
  // check that the assignment consists of only one object node that is a reference to the reaction flux
  const CExpression* pExpression = pNonConstParameter->getExpressionPtr();
  CPPUNIT_ASSERT(pExpression != NULL);
  const CEvaluationNode* pRoot = pExpression->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->mainType() == CEvaluationNode::MainType::OBJECT);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pRoot);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  const CRegisteredCommonName cn = pObjectNode->getObjectCN();
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(pCOPASIDATAMODEL->getModel());
  const CDataObject* pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, cn));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == "Flux");
  CPPUNIT_ASSERT(pObject->getObjectParent() == pReaction);
  // Simulate the model (5 steps, stepsize 1 and check that at each step, the value of the variable parameter
  // is the same as the flux through the reaction.
  std::ostringstream result;
  // create a report with the correct filename and all the species against
  // time.
  CReportDefinitionVector* pReports = pCOPASIDATAMODEL->getReportDefinitionList();
  CReportDefinition* pReport = pReports->createReportDefinition("Report", "Output for simulation");
  pReport->setTaskType(CCopasiTask::timeCourse);
  pReport->setIsTable(false);
  pReport->setSeparator(", ");

  std::vector<CRegisteredCommonName>* pHeader = pReport->getHeaderAddr();
  std::vector<CRegisteredCommonName>* pBody = pReport->getBodyAddr();
  pHeader->push_back(CDataString("time").getCN());
  pHeader->push_back(pReport->getSeparator().getCN());
  pHeader->push_back(CDataString("substrate").getCN());
  pHeader->push_back(pReport->getSeparator().getCN());
  pHeader->push_back(CDataString("reaction flux").getCN());
  pHeader->push_back(pReport->getSeparator().getCN());
  pHeader->push_back(CDataString("variable model value").getCN());
  pBody->push_back(CCommonName(pCOPASIDATAMODEL->getModel()->getCN() + ",Reference=Time"));
  pBody->push_back(CRegisteredCommonName(pReport->getSeparator().getCN()));
  pBody->push_back(CCommonName(pSubstrate->getCN() + ",Reference=Concentration"));
  pBody->push_back(CRegisteredCommonName(pReport->getSeparator().getCN()));
  pBody->push_back(CCommonName(pReaction->getCN() + ",Reference=Flux"));
  pBody->push_back(CRegisteredCommonName(pReport->getSeparator().getCN()));
  pBody->push_back(CCommonName(pNonConstParameter->getCN() + ",Reference=Value"));
  //
  // create a trajectory task
  CTrajectoryTask* pTrajectoryTask = new CTrajectoryTask();
  // use LSODAR from now on since we will have events pretty soon
  pTrajectoryTask->setMethodType(CCopasiMethod::LSODAR);
  pTrajectoryTask->getProblem()->setModel(pCOPASIDATAMODEL->getModel());

  pTrajectoryTask->setScheduled(true);
  pTrajectoryTask->getReport().setReportDefinition(pReport);
  // the target needs to be set in order to get output on the stream
  // object passed to the task in the call to initialize below
  pTrajectoryTask->getReport().setTarget("test.tmp");

  CTrajectoryProblem* pProblem = dynamic_cast<CTrajectoryProblem*>(pTrajectoryTask->getProblem());

  pProblem->setStepNumber((const unsigned C_INT32)30);
  pCOPASIDATAMODEL->getModel()->setInitialTime((const C_FLOAT64)0.0);
  pProblem->setDuration((const C_FLOAT64)30);
  pProblem->setTimeSeriesRequested(true);

  CTrajectoryMethod* pMethod = dynamic_cast<CTrajectoryMethod*>(pTrajectoryTask->getMethod());

  pMethod->getParameter("Absolute Tolerance")->setValue(1.0e-12);

  CDataVectorN< CCopasiTask > & TaskList = * pCOPASIDATAMODEL->getTaskList();

  TaskList.remove("Time-Course");
  TaskList.add(pTrajectoryTask, true);

  try
    {
      pTrajectoryTask->initialize(CCopasiTask::OUTPUT_UI, pCOPASIDATAMODEL, &result);
      pTrajectoryTask->process(true);
      pTrajectoryTask->restore();
    }
  catch (...)
    {
      // there should be no exception
      CPPUNIT_ASSERT(false);
    }

  // analyse the result
  CPPUNIT_ASSERT(!result.str().empty());
  std::string result_string = result.str();
  std::string delimiter = "\n";
  std::string delimiter2 = ",";
  std::size_t lastPos = result_string.find_first_not_of(delimiter);
  std::size_t pos;
  std::string line, number_string;
  unsigned int index = 0;
  unsigned int index2;
  std::size_t lastPos2;
  std::size_t pos2;
  double last = std::numeric_limits<double>::max(), current = std::numeric_limits<double>::max();

  while (lastPos != std::string::npos)
    {
      pos = result_string.find_first_of(delimiter, lastPos);
      line = result_string.substr(lastPos, pos - lastPos);
      lastPos = result_string.find_first_not_of(delimiter, pos);
      lastPos2 = line.find_first_not_of(delimiter2);

      // skip the header line
      if (index != 0)
        {
          index2 = 0;

          while (lastPos2 != std::string::npos)
            {
              pos2 = line.find_first_of(delimiter2, lastPos2);
              number_string = line.substr(lastPos2, pos2 - lastPos2);
              lastPos2 = line.find_first_not_of(delimiter2, pos2);

              // skip the time column
              if (index2 != 0)
                {
                  //check that all values in the row (besides the time)
                  // are always the same
                  if (index2 == 1)
                    {
                      last = strToDouble(number_string.c_str(), NULL);

                      if (index == 1)
                        {
                          // just make sure that we don't compare all zeros
                          // The initial value of the substrate hould be higher than 1
                          CPPUNIT_ASSERT(fabs(pSubstrate->getInitialValue()) > 1);
                          // the first rwo should correspond the the initial value of the substrate
                          // We check this to make sure that the whole timeseries does not consist of zeros
                          CPPUNIT_ASSERT(fabs((last - pSubstrate->getInitialConcentration()) / pSubstrate->getInitialConcentration()) < 1e-20);
                        }
                    }
                  else
                    {
                      current = strToDouble(number_string.c_str(), NULL);
                      CPPUNIT_ASSERT(fabs((current - last) / last) < 1e-20);
                      last = current;
                    }
                }

              ++index2;
            }
        }

      ++index;
    }

  // make sure there actually were datapoints
  CPPUNIT_ASSERT(index > 1);
  // the simulation is set to run until all substrate is depleted, so in the end
  // last should be below the absolute tolerance for the simulation
  CPPUNIT_ASSERT(last < *pMethod->getParameter("Absolute Tolerance")->getValue().pDOUBLE);
}

const char* test000087::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"model_1\" name=\"model\">\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species compartment=\"compartment_1\" id=\"species_1\" initialConcentration=\"1\" />\n"
  "      <species compartment=\"compartment_1\" id=\"species_2\" initialConcentration=\"1\" />\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter constant=\"false\" id=\"parameter_1\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"parameter_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <ci> reaction_1 </ci>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "    <listOfReactions>\n"
  "      <reaction id=\"reaction_1\" reversible=\"false\">\n"
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
  "              <cn> 1 </cn>\n"
  "              <ci> species_1 </ci>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n";

const char* test000087::MODEL_STRING2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model id=\"model_1\" name=\"model\">\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species compartment=\"compartment_1\" id=\"species_1\" initialConcentration=\"1\" />\n"
  "      <species compartment=\"compartment_1\" id=\"species_2\" initialConcentration=\"1\" />\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter constant=\"false\" id=\"parameter_1\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"parameter_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <ci> reaction_1 </ci>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "    <listOfReactions>\n"
  "      <reaction id=\"reaction_1\" reversible=\"false\">\n"
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
  "              <cn> 1 </cn>\n"
  "              <ci> species_1 </ci>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n";

const char* test000087::MODEL_STRING3 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model id=\"model_1\" name=\"model\">\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species compartment=\"compartment_1\" id=\"species_1\" initialConcentration=\"1\" />\n"
  "      <species compartment=\"compartment_1\" id=\"species_2\" initialConcentration=\"1\" />\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter constant=\"false\" id=\"parameter_1\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"parameter_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <ci> reaction_1 </ci>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "    <listOfReactions>\n"
  "      <reaction id=\"reaction_1\" reversible=\"false\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_1\"/>\n"
  "        </listOfReactants>\n"
  "        <listOfProducts>\n"
  "          <speciesReference species=\"species_2\"/>\n"
  "        </listOfProducts>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n";

const char* test000087::MODEL_STRING4 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"30\">\n"
  "  <ListOfFunctions>\n"
  "    <Function key=\"Function_13\" name=\"Mass action (irreversible)\" type=\"MassAction\" reversible=\"false\">\n"
  "      <Expression>\n"
  "        k1*PRODUCT&lt;substrate_i&gt;\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_81\" name=\"k1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_79\" name=\"substrate\" order=\"1\" role=\"substrate\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "  </ListOfFunctions>\n"
  "  <Model key=\"Model_1\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\" dimensionality=\"3\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_2\" name=\"C\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Reactions[Reaction 1],Reference=Flux&gt;\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"Reaction 1\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_511\" name=\"k1\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"Parameter_511\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_79\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_2\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 10000.0 0.0 NaN 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n";

const char* test000087::MODEL_STRING5 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model id=\"model_1\" name=\"model\">\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species compartment=\"compartment_1\" id=\"species_1\" initialConcentration=\"5\" />\n"
  "      <species compartment=\"compartment_1\" id=\"species_2\" initialConcentration=\"0\" />\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter constant=\"false\" id=\"parameter_1\"/>\n"
  "      <parameter constant=\"true\" id=\"parameter_2\" value=\"1.0\" />\n"
  "    </listOfParameters>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"parameter_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <ci> reaction_1 </ci>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "    <listOfReactions>\n"
  "      <reaction id=\"reaction_1\" reversible=\"false\">\n"
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
  "              <ci> parameter_2 </ci>\n"
  "              <ci> species_1 </ci>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n";
