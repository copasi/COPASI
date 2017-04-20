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

#include "test000051.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000051::pCOPASIDATAMODEL = NULL;

void test000051::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000051::tearDown()
{
  CRootContainer::destroy();
}

void test000051::test_bug988()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000051::MODEL_STRING);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // assert that there is only one compartment and
  // assert the compartment is constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == true);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 0);
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 1);
  const Species* pSpecies = pModel->getSpecies(0);
  std::string idSpeciesA = pSpecies->getId();
  CPPUNIT_ASSERT(pSpecies->getHasOnlySubstanceUnits() == false);
  CPPUNIT_ASSERT(pModel->getNumRules() == 1);
  AssignmentRule* pRule = dynamic_cast<AssignmentRule*>(pModel->getRule(0));
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == idSpeciesA);
  const ASTNode* pMath = pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains a piecewise
  // function definition
  CPPUNIT_ASSERT(pMath->getType() == AST_FUNCTION_PIECEWISE);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 3);
  CPPUNIT_ASSERT(pMath->getChild(0) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_REAL);
  CPPUNIT_ASSERT(pMath->getChild(0)->getReal() < 1e-6);
  CPPUNIT_ASSERT(pMath->getChild(2) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(2)->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pMath->getChild(2)->getReal() - 10.0) / 10.0) < 1e-3);
  pMath = pMath->getChild(1);
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_RELATIONAL_LT);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getChild(0) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME_TIME);
  CPPUNIT_ASSERT(pMath->getChild(1) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pMath->getChild(1)->getReal() - 5.0) / 5.0) < 1e-3);
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
}

const char* test000051::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.3 (Build 25) (http://www.copasi.org) at 2008-03-04 00:11:31 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"25\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        \n"
  "      </body>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"species\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          if(&lt;CN=Root,Model=New Model,Reference=Time&gt; lt 5,0,10)\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 0 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "  <ListOfTasks>\n"
  "    <Task key=\"Task_9\" name=\"Steady-State\" type=\"steadyState\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_6\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"JacobianRequested\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"StabilityAnalysisRequested\" type=\"bool\" value=\"1\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"Enhanced Newton\" type=\"EnhancedNewton\">\n"
  "        <Parameter name=\"Resolution\" type=\"unsignedFloat\" value=\"1e-009\"/>\n"
  "        <Parameter name=\"Derivation Factor\" type=\"unsignedFloat\" value=\"0.001\"/>\n"
  "        <Parameter name=\"Use Newton\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Use Integration\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Use Back Integration\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Accept Negative Concentrations\" type=\"bool\" value=\"0\"/>\n"
  "        <Parameter name=\"Iteration Limit\" type=\"unsignedInteger\" value=\"50\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_8\" name=\"Time-Course\" type=\"timeCourse\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Problem>\n"
  "        <Parameter name=\"StepNumber\" type=\"unsignedInteger\" value=\"100\"/>\n"
  "        <Parameter name=\"StepSize\" type=\"float\" value=\"0.01\"/>\n"
  "        <Parameter name=\"Duration\" type=\"float\" value=\"1\"/>\n"
  "        <Parameter name=\"TimeSeriesRequested\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"OutputStartTime\" type=\"float\" value=\"0\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"Deterministic (LSODA)\" type=\"Deterministic(LSODA)\">\n"
  "        <Parameter name=\"Integrate Reduced Model\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Relative Tolerance\" type=\"unsignedFloat\" value=\"1e-006\"/>\n"
  "        <Parameter name=\"Absolute Tolerance\" type=\"unsignedFloat\" value=\"1e-012\"/>\n"
  "        <Parameter name=\"Adams Max Order\" type=\"unsignedInteger\" value=\"12\"/>\n"
  "        <Parameter name=\"BDF Max Order\" type=\"unsignedInteger\" value=\"5\"/>\n"
  "        <Parameter name=\"Max Internal Steps\" type=\"unsignedInteger\" value=\"10000\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_7\" name=\"Scan\" type=\"scan\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Problem>\n"
  "        <Parameter name=\"Subtask\" type=\"unsignedInteger\" value=\"1\"/>\n"
  "        <ParameterGroup name=\"ScanItems\">\n"
  "        </ParameterGroup>\n"
  "        <Parameter name=\"Output in subtask\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Adjust initial conditions\" type=\"bool\" value=\"0\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"Scan Framework\" type=\"ScanFramework\">\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_6\" name=\"Elementary Flux Modes\" type=\"fluxMode\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_5\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "      </Problem>\n"
  "      <Method name=\"EFM Algorithm\" type=\"EFMAlgorithm\">\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_5\" name=\"Optimization\" type=\"optimization\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_4\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"Steady-State\" type=\"key\" value=\"\"/>\n"
  "        <Parameter name=\"Time-Course\" type=\"key\" value=\"\"/>\n"
  "        <Parameter name=\"ObjectiveFunction\" type=\"key\" value=\"\"/>\n"
  "        <Parameter name=\"Maximize\" type=\"bool\" value=\"0\"/>\n"
  "        <ParameterGroup name=\"OptimizationItemList\">\n"
  "        </ParameterGroup>\n"
  "        <ParameterGroup name=\"OptimizationConstraintList\">\n"
  "        </ParameterGroup>\n"
  "      </Problem>\n"
  "      <Method name=\"Random Search\" type=\"RandomSearch\">\n"
  "        <Parameter name=\"Number of Iterations\" type=\"unsignedInteger\" value=\"100000\"/>\n"
  "        <Parameter name=\"Random Number Generator\" type=\"unsignedInteger\" value=\"1\"/>\n"
  "        <Parameter name=\"Seed\" type=\"unsignedInteger\" value=\"0\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_4\" name=\"Parameter Estimation\" type=\"parameterFitting\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_3\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"Steady-State\" type=\"key\" value=\"Task_9\"/>\n"
  "        <Parameter name=\"Time-Course\" type=\"key\" value=\"Task_8\"/>\n"
  "        <ParameterGroup name=\"OptimizationItemList\">\n"
  "        </ParameterGroup>\n"
  "        <ParameterGroup name=\"OptimizationConstraintList\">\n"
  "        </ParameterGroup>\n"
  "        <ParameterGroup name=\"Experiment Set\">\n"
  "        </ParameterGroup>\n"
  "      </Problem>\n"
  "      <Method name=\"Evolutionary Programming\" type=\"EvolutionaryProgram\">\n"
  "        <Parameter name=\"Number of Generations\" type=\"unsignedInteger\" value=\"200\"/>\n"
  "        <Parameter name=\"Population Size\" type=\"unsignedInteger\" value=\"20\"/>\n"
  "        <Parameter name=\"Random Number Generator\" type=\"unsignedInteger\" value=\"1\"/>\n"
  "        <Parameter name=\"Seed\" type=\"unsignedInteger\" value=\"0\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_3\" name=\"Metabolic Control Analysis\" type=\"metabolicControlAnalysis\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_2\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"Steady-State\" type=\"key\" value=\"Task_9\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"MCA Method (Reder)\" type=\"MCAMethod(Reder)\">\n"
  "        <Parameter name=\"Modulation Factor\" type=\"unsignedFloat\" value=\"1e-009\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_2\" name=\"Lyapunov Exponents\" type=\"lyapunovExponents\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_1\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"ExponentNumber\" type=\"unsignedInteger\" value=\"3\"/>\n"
  "        <Parameter name=\"DivergenceRequested\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"TransientTime\" type=\"float\" value=\"0\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"Wolf Method\" type=\"WolfMethod\">\n"
  "        <Parameter name=\"Orthonormalization Interval\" type=\"unsignedFloat\" value=\"1\"/>\n"
  "        <Parameter name=\"Overall time\" type=\"unsignedFloat\" value=\"1000\"/>\n"
  "        <Parameter name=\"Relative Tolerance\" type=\"unsignedFloat\" value=\"1e-006\"/>\n"
  "        <Parameter name=\"Use Default Absolute Tolerance\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Absolute Tolerance\" type=\"unsignedFloat\" value=\"1e-012\"/>\n"
  "        <Parameter name=\"Adams Max Order\" type=\"unsignedInteger\" value=\"12\"/>\n"
  "        <Parameter name=\"BDF Max Order\" type=\"unsignedInteger\" value=\"5\"/>\n"
  "        <Parameter name=\"Max Internal Steps\" type=\"unsignedInteger\" value=\"10000\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_1\" name=\"Sensitivities\" type=\"sensitivities\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_0\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"SubtaskType\" type=\"unsignedInteger\" value=\"1\"/>\n"
  "        <ParameterGroup name=\"TargetFunctions\">\n"
  "          <Parameter name=\"SingleObject\" type=\"cn\" value=\"\"/>\n"
  "          <Parameter name=\"ObjectListType\" type=\"unsignedInteger\" value=\"7\"/>\n"
  "        </ParameterGroup>\n"
  "        <ParameterGroup name=\"ListOfVariables\">\n"
  "          <ParameterGroup name=\"Variables\">\n"
  "            <Parameter name=\"SingleObject\" type=\"cn\" value=\"\"/>\n"
  "            <Parameter name=\"ObjectListType\" type=\"unsignedInteger\" value=\"41\"/>\n"
  "          </ParameterGroup>\n"
  "        </ParameterGroup>\n"
  "      </Problem>\n"
  "      <Method name=\"Sensitivities Method\" type=\"SensitivitiesMethod\">\n"
  "        <Parameter name=\"Delta factor\" type=\"unsignedFloat\" value=\"1e-006\"/>\n"
  "        <Parameter name=\"Delta minimum\" type=\"unsignedFloat\" value=\"1e-012\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_0\" name=\"Moieties\" type=\"moieties\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Problem>\n"
  "      </Problem>\n"
  "      <Method name=\"Householder Reduction\" type=\"Householder\">\n"
  "      </Method>\n"
  "    </Task>\n"
  "  </ListOfTasks>\n"
  "  <ListOfReports>\n"
  "    <Report key=\"Report_6\" name=\"Steady-State\" taskType=\"steadyState\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Footer>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Steady-State]\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_5\" name=\"Elementary Flux Modes\" taskType=\"fluxMode\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Footer>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_4\" name=\"Optimization\" taskType=\"optimization\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Header>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Optimization],Object=Description\"/>\n"
  "        <Object cn=\"String=\\[Function Evaluations\\]\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"String=\\[Best Value\\]\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"String=\\[Best Parameters\\]\"/>\n"
  "      </Header>\n"
  "      <Body>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Parameters\"/>\n"
  "      </Body>\n"
  "      <Footer>\n"
  "        <Object cn=\"String=&#x0a;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Optimization],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_3\" name=\"Parameter Estimation\" taskType=\"parameterFitting\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Header>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Parameter Estimation],Object=Description\"/>\n"
  "        <Object cn=\"String=\\[Function Evaluations\\]\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"String=\\[Best Value\\]\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"String=\\[Best Parameters\\]\"/>\n"
  "      </Header>\n"
  "      <Body>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Function Evaluations\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Best Value\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Best Parameters\"/>\n"
  "      </Body>\n"
  "      <Footer>\n"
  "        <Object cn=\"String=&#x0a;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Parameter Estimation],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_2\" name=\"Metabolic Control Analysis\" taskType=\"metabolicControlAnalysis\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Header>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Description\"/>\n"
  "      </Header>\n"
  "      <Footer>\n"
  "        <Object cn=\"String=&#x0a;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_1\" name=\"Lyapunov Exponents\" taskType=\"lyapunovExponents\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Header>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Description\"/>\n"
  "      </Header>\n"
  "      <Footer>\n"
  "        <Object cn=\"String=&#x0a;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_0\" name=\"Sensitivities\" taskType=\"sensitivities\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Header>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Sensitivities],Object=Description\"/>\n"
  "      </Header>\n"
  "      <Footer>\n"
  "        <Object cn=\"String=&#x0a;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Sensitivities],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "  </ListOfReports>\n"
  "  <GUI>\n"
  "  </GUI>\n"
  "</COPASI>\n"
  ;
