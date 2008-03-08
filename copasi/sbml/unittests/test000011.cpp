// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000011.cpp,v $
//   $Revision: 1.1.2.10 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/03/08 19:58:29 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000011.hpp"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

void test000011::setUp()
{
  // Create the root container.
  CCopasiContainer::init();

  // Create the global data model.
  CCopasiDataModel::Global = new CCopasiDataModel;
}

void test000011::tearDown()
{
  delete CCopasiDataModel::Global;
  CCopasiDataModel::Global = NULL;
  delete CCopasiContainer::Root;
  CCopasiContainer::Root = NULL;
}

void test000011::test_references_to_species()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  std::istringstream iss(test000011::MODEL_STRING);
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
  CPPUNIT_ASSERT(pCompartment->getConstant() == false);
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  Species* pSpecies = pModel->getSpecies(1);
  CPPUNIT_ASSERT(pSpecies->getHasOnlySubstanceUnits() == true);
  pSpecies = pModel->getSpecies(0);
  std::string idSpeciesA = pSpecies->getId();
  CPPUNIT_ASSERT(pSpecies->getHasOnlySubstanceUnits() == true);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 2);
  Parameter* pParameter = pModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter != NULL);
  Parameter* pFactor = pModel->getParameter(1);
  CPPUNIT_ASSERT(pFactor != NULL);
  CPPUNIT_ASSERT(pFactor->getConstant() == true);
  CPPUNIT_ASSERT(fabs((pFactor->getValue() - (AVOGADRO / 1000.0)) / (AVOGADRO / 1000.0)) < 1e-3);
  // two rules, the second rule is for the compartment
  CPPUNIT_ASSERT(pModel->getNumRules() == 2);
  AssignmentRule* pRule = dynamic_cast<AssignmentRule*>(pModel->getRule(0));
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == pParameter->getId());
  const ASTNode* pMath = pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // the expression should be the species multiplied by a factor
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getChild(0) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(0)->getName() == pSpecies->getId());
  CPPUNIT_ASSERT(pMath->getChild(1) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(1)->getName() == pFactor->getId());
  CPPUNIT_ASSERT(pModel->getNumReactions() == 2);
  Reaction* pReaction = pModel->getReaction(0);
  // make sure this is reaction A ->
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getNumReactants() == 1);
  CPPUNIT_ASSERT(pReaction->getNumProducts() == 0);
  // check if all references in the kinetic law are unmodified
  // math element must be a multiplication of the mass action term by
  // the compartment volume
  // the mass action term is a multiplication of the parameter node by
  // the species node
  CPPUNIT_ASSERT(pReaction->isSetKineticLaw() == true);
  KineticLaw* pLaw = pReaction->getKineticLaw();
  CPPUNIT_ASSERT(pLaw != NULL);
  CPPUNIT_ASSERT(pLaw->isSetMath() == true);
  pMath = pLaw->getMath();
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getChild(0) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(0)->getName() == std::string("k1"));
  CPPUNIT_ASSERT(pMath->getChild(1) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(1)->getName() == idSpeciesA);

  pReaction = pModel->getReaction(1);
  // make sure this is reaction A -> S
  CPPUNIT_ASSERT(pReaction != NULL);
  CPPUNIT_ASSERT(pReaction->getNumReactants() == 1);
  CPPUNIT_ASSERT(pReaction->getNumProducts() == 1);
  // check if all references in the kinetic law are unmodified
  // math element must be a multiplication of the compartments volume with
  // a function call with three arguments
  // the first argument is the reference to the species
  CPPUNIT_ASSERT(pReaction->isSetKineticLaw() == true);
  pLaw = pReaction->getKineticLaw();
  CPPUNIT_ASSERT(pLaw != NULL);
  CPPUNIT_ASSERT(pLaw->isSetMath() == true);
  pMath = pLaw->getMath();
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(0)->getName() == pCompartment->getId());
  pMath = pMath->getChild(1);
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_FUNCTION);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 3);
  pMath = pMath->getChild(0);
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_DIVIDE);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getChild(0) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(0)->getName() == idSpeciesA);
  CPPUNIT_ASSERT(pMath->getChild(1) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getChild(1)->getName() == pCompartment->getId());
}

const char* test000011::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.3.25 (Debug) (http://www.copasi.org) at 2008-02-15 09:36:52 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"25\">\n"
  "  <ListOfFunctions>\n"
  "    <Function key=\"Function_8\" name=\"Henri-Michaelis-Menten (irreversible)\" type=\"PreDefined\" reversible=\"false\">\n"
  "      <Expression>\n"
  "        V*substrate/(Km+substrate)\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_41\" name=\"substrate\" order=\"0\" role=\"substrate\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_30\" name=\"Km\" order=\"1\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_45\" name=\"V\" order=\"2\" role=\"constant\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
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
  "  <Model key=\"Model_1\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "<p>Model with variable volume compartment,mmol quantity units and a reference to the species transient amount.</p>\n"
  "<p>On export this should create an SBML file with the hasOnlySubstanceUnits flag on the species set.</p>\n"
  "<p>The reference in the rule should by multiplied by a factor (6.023e20) and the references in the reaction should be divided by the volume.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          3+4\n"
  "        </Expression>\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"S\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=ParticleNumber&gt;\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_93\" name=\"k1\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"Parameter_93\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_79\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_1\" name=\"reaction_1\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_92\" name=\"Km\" value=\"0.1\"/>\n"
  "          <Constant key=\"Parameter_91\" name=\"V\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_8\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_41\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_30\">\n"
  "              <SourceParameter reference=\"Parameter_92\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_45\">\n"
  "              <SourceParameter reference=\"Parameter_91\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 4.215499050000001e+21 4.215499050000002e+20 7 4.215499050000001e+21\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "  <ListOfTasks>\n"
  "    <Task key=\"Task_12\" name=\"Steady-State\" type=\"steadyState\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_7\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"JacobianRequested\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"StabilityAnalysisRequested\" type=\"bool\" value=\"1\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"Enhanced Newton\" type=\"EnhancedNewton\">\n"
  "        <Parameter name=\"Resolution\" type=\"unsignedFloat\" value=\"1e-09\"/>\n"
  "        <Parameter name=\"Derivation Factor\" type=\"unsignedFloat\" value=\"0.001\"/>\n"
  "        <Parameter name=\"Use Newton\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Use Integration\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Use Back Integration\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Accept Negative Concentrations\" type=\"bool\" value=\"0\"/>\n"
  "        <Parameter name=\"Iteration Limit\" type=\"unsignedInteger\" value=\"50\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_13\" name=\"Time-Course\" type=\"timeCourse\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Problem>\n"
  "        <Parameter name=\"StepNumber\" type=\"unsignedInteger\" value=\"100\"/>\n"
  "        <Parameter name=\"StepSize\" type=\"float\" value=\"0.01\"/>\n"
  "        <Parameter name=\"Duration\" type=\"float\" value=\"1\"/>\n"
  "        <Parameter name=\"TimeSeriesRequested\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"OutputStartTime\" type=\"float\" value=\"0\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"Deterministic (LSODA)\" type=\"Deterministic(LSODA)\">\n"
  "        <Parameter name=\"Integrate Reduced Model\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Relative Tolerance\" type=\"unsignedFloat\" value=\"1e-06\"/>\n"
  "        <Parameter name=\"Absolute Tolerance\" type=\"unsignedFloat\" value=\"1e-12\"/>\n"
  "        <Parameter name=\"Adams Max Order\" type=\"unsignedInteger\" value=\"12\"/>\n"
  "        <Parameter name=\"BDF Max Order\" type=\"unsignedInteger\" value=\"5\"/>\n"
  "        <Parameter name=\"Max Internal Steps\" type=\"unsignedInteger\" value=\"10000\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_14\" name=\"Scan\" type=\"scan\" scheduled=\"false\" updateModel=\"false\">\n"
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
  "    <Task key=\"Task_15\" name=\"Elementary Flux Modes\" type=\"fluxMode\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_8\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "      </Problem>\n"
  "      <Method name=\"EFM Algorithm\" type=\"EFMAlgorithm\">\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_16\" name=\"Optimization\" type=\"optimization\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_9\" target=\"\" append=\"1\"/>\n"
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
  "    <Task key=\"Task_17\" name=\"Parameter Estimation\" type=\"parameterFitting\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_10\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"Steady-State\" type=\"key\" value=\"Task_12\"/>\n"
  "        <Parameter name=\"Time-Course\" type=\"key\" value=\"Task_13\"/>\n"
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
  "    <Task key=\"Task_18\" name=\"Metabolic Control Analysis\" type=\"metabolicControlAnalysis\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_11\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"Steady-State\" type=\"key\" value=\"Task_12\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"MCA Method (Reder)\" type=\"MCAMethod(Reder)\">\n"
  "        <Parameter name=\"Modulation Factor\" type=\"unsignedFloat\" value=\"1e-09\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_19\" name=\"Lyapunov Exponents\" type=\"lyapunovExponents\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_12\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"ExponentNumber\" type=\"unsignedInteger\" value=\"3\"/>\n"
  "        <Parameter name=\"DivergenceRequested\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"TransientTime\" type=\"float\" value=\"0\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"Wolf Method\" type=\"WolfMethod\">\n"
  "        <Parameter name=\"Orthonormalization Interval\" type=\"unsignedFloat\" value=\"1\"/>\n"
  "        <Parameter name=\"Overall time\" type=\"unsignedFloat\" value=\"1000\"/>\n"
  "        <Parameter name=\"Relative Tolerance\" type=\"unsignedFloat\" value=\"1e-06\"/>\n"
  "        <Parameter name=\"Use Default Absolute Tolerance\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Absolute Tolerance\" type=\"unsignedFloat\" value=\"1e-12\"/>\n"
  "        <Parameter name=\"Adams Max Order\" type=\"unsignedInteger\" value=\"12\"/>\n"
  "        <Parameter name=\"BDF Max Order\" type=\"unsignedInteger\" value=\"5\"/>\n"
  "        <Parameter name=\"Max Internal Steps\" type=\"unsignedInteger\" value=\"10000\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_20\" name=\"Time Scale Separation Analysis\" type=\"timeScaleSeparation\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Problem>\n"
  "        <Parameter name=\"StepNumber\" type=\"unsignedInteger\" value=\"100\"/>\n"
  "        <Parameter name=\"StepSize\" type=\"float\" value=\"0.01\"/>\n"
  "        <Parameter name=\"Duration\" type=\"float\" value=\"1\"/>\n"
  "        <Parameter name=\"TimeSeriesRequested\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"OutputStartTime\" type=\"float\" value=\"0\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"ILDM (LSODA)\" type=\"TimeScaleSeparation(ILDM)\">\n"
  "        <Parameter name=\"Deuflhard Tolerance\" type=\"unsignedFloat\" value=\"1e-06\"/>\n"
  "        <Parameter name=\"Integrate Reduced Model\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Relative Tolerance\" type=\"unsignedFloat\" value=\"1e-06\"/>\n"
  "        <Parameter name=\"Absolute Tolerance\" type=\"unsignedFloat\" value=\"1e-12\"/>\n"
  "        <Parameter name=\"Adams Max Order\" type=\"unsignedInteger\" value=\"12\"/>\n"
  "        <Parameter name=\"BDF Max Order\" type=\"unsignedInteger\" value=\"5\"/>\n"
  "        <Parameter name=\"Max Internal Steps\" type=\"unsignedInteger\" value=\"10000\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_21\" name=\"Time Scale Separation\" type=\"timeScaleSeparationAnalysis\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Problem>\n"
  "      </Problem>\n"
  "      <Method name=\"Time Scale Separation Method\" type=\"TimeScaleSeparationMethod\">\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_22\" name=\"Sensitivities\" type=\"sensitivities\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_13\" target=\"\" append=\"1\"/>\n"
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
  "        <Parameter name=\"Delta factor\" type=\"unsignedFloat\" value=\"1e-06\"/>\n"
  "        <Parameter name=\"Delta minimum\" type=\"unsignedFloat\" value=\"1e-12\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "  </ListOfTasks>\n"
  "  <ListOfReports>\n"
  "    <Report key=\"Report_7\" name=\"Steady-State\" taskType=\"steadyState\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Footer>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Steady-State]\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_8\" name=\"Elementary Flux Modes\" taskType=\"fluxMode\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Footer>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_9\" name=\"Optimization\" taskType=\"optimization\" separator=\"&#x09;\" precision=\"6\">\n"
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
  "    <Report key=\"Report_10\" name=\"Parameter Estimation\" taskType=\"parameterFitting\" separator=\"&#x09;\" precision=\"6\">\n"
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
  "    <Report key=\"Report_11\" name=\"Metabolic Control Analysis\" taskType=\"metabolicControlAnalysis\" separator=\"&#x09;\" precision=\"6\">\n"
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
  "    <Report key=\"Report_12\" name=\"Lyapunov Exponents\" taskType=\"lyapunovExponents\" separator=\"&#x09;\" precision=\"6\">\n"
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
  "    <Report key=\"Report_13\" name=\"Sensitivities\" taskType=\"sensitivities\" separator=\"&#x09;\" precision=\"6\">\n"
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
