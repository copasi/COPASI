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

#include "test_compare_utilities.h"

#include <sstream>

#include "copasi/sbml/unittests/utilities.hpp"

#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/compareExpressions/compare_utilities.h"
#include "copasi/function/CFunctionDB.h"

CDataModel* test_compare_utilities::pCOPASIDATAMODEL = NULL;

void test_compare_utilities::setUp()
{
  // Create the root container.
  CRootContainer::init(false, 0, NULL);

  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test_compare_utilities::tearDown()
{
  CRootContainer::destroy();
}

void test_compare_utilities::test_copasi_function_expansion()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;;
  std::istringstream iss(test_compare_utilities::MODEL_STRING1);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CFunctionDB* pFunctionDB = CRootContainer::getFunctionList();
  // function_5
  CEvaluationTree* pTree = pFunctionDB->findFunction("function_4");
  CPPUNIT_ASSERT(pTree != NULL);
  // generate a call node
  CFunction* pFunction = dynamic_cast<CFunction*>(pTree);
  CPPUNIT_ASSERT(pFunction != NULL);
  CEvaluationNodeCall* pCallNode = new CEvaluationNodeCall(CEvaluationNode::SubType::FUNCTION, pFunction->getObjectName());
  CPPUNIT_ASSERT(pCallNode != NULL);
  CFunctionParameters* pFunctionParameters = &pFunction->getVariables();
  unsigned int i = 0, iMax = pFunctionParameters->size();

  while (i < iMax)
    {
      CFunctionParameter* pParameter = (*pFunctionParameters)[i];
      CPPUNIT_ASSERT(pParameter != NULL);
      CEvaluationNodeVariable* pVariableNode = new CEvaluationNodeVariable(CEvaluationNode::SubType::DEFAULT, pParameter->getObjectName());
      pCallNode->addChild(pVariableNode);
      ++i;
    }

  CEvaluationNode* pExpanded = expand_function_calls(pCallNode, pFunctionDB);
  delete pCallNode;
  CPPUNIT_ASSERT(pExpanded != NULL);
  CPPUNIT_ASSERT(pExpanded->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pExpanded->subType() == CEvaluationNode::SubType::DIVIDE);
  CEvaluationNode* pChild = dynamic_cast<CEvaluationNode*>(pExpanded->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::PLUS);
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->getData() == std::string("y"));
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->getData() == std::string("x"));
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);
  pChild = dynamic_cast<CEvaluationNode*>(pExpanded->getChild()->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::NUMBER);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT((fabs(pChild->getValue() - 2.0) / 2.0) < 1e-6);
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);
  delete pExpanded;

  // function_5
  pTree = pFunctionDB->findFunction("function_5");
  CPPUNIT_ASSERT(pTree != NULL);
  // generate a call node
  pFunction = dynamic_cast<CFunction*>(pTree);
  CPPUNIT_ASSERT(pFunction != NULL);
  pCallNode = new CEvaluationNodeCall(CEvaluationNode::SubType::FUNCTION, pFunction->getObjectName());
  CPPUNIT_ASSERT(pCallNode != NULL);
  pFunctionParameters = &pFunction->getVariables();
  i = 0, iMax = pFunctionParameters->size();

  while (i < iMax)
    {
      CFunctionParameter* pParameter = (*pFunctionParameters)[i];
      CPPUNIT_ASSERT(pParameter != NULL);
      CEvaluationNodeVariable* pVariableNode = new CEvaluationNodeVariable(CEvaluationNode::SubType::DEFAULT, pParameter->getObjectName());
      pCallNode->addChild(pVariableNode);
      ++i;
    }

  pExpanded = expand_function_calls(pCallNode, pFunctionDB);
  delete pCallNode;
  CPPUNIT_ASSERT(pExpanded != NULL);
  CPPUNIT_ASSERT(pExpanded->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pExpanded->subType() == CEvaluationNode::SubType::PLUS);
  pChild = dynamic_cast<CEvaluationNode*>(pExpanded->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MINUS);
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->getData() == std::string("a"));
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MULTIPLY);
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->getData() == std::string("c"));
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::NUMBER);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT((fabs(pChild->getValue() - 1.3) / 1.3) < 1e-6);
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);

  // (3*b)-5.23
  pChild = dynamic_cast<CEvaluationNode*>(pExpanded->getChild()->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MINUS);
  // 3*b
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MULTIPLY);
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::NUMBER);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT((fabs(pChild->getValue() - 3.0) / 3.0) < 1e-6);
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->getData() == std::string("b"));
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);
  // 5.23
  pChild = dynamic_cast<CEvaluationNode*>(pExpanded->getChild()->getSibling()->getChild()->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::NUMBER);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT((fabs(pChild->getValue() - 5.23) / 5.23) < 1e-6);
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);

  delete pExpanded;

  // function_6
  pTree = pFunctionDB->findFunction("function_6");
  CPPUNIT_ASSERT(pTree != NULL);
  // generate a call node
  pFunction = dynamic_cast<CFunction*>(pTree);
  CPPUNIT_ASSERT(pFunction != NULL);
  pCallNode = new CEvaluationNodeCall(CEvaluationNode::SubType::FUNCTION, pFunction->getObjectName());
  CPPUNIT_ASSERT(pCallNode != NULL);
  pFunctionParameters = &pFunction->getVariables();
  i = 0, iMax = pFunctionParameters->size();

  while (i < iMax)
    {
      CFunctionParameter* pParameter = (*pFunctionParameters)[i];
      CPPUNIT_ASSERT(pParameter != NULL);
      CEvaluationNodeVariable* pVariableNode = new CEvaluationNodeVariable(CEvaluationNode::SubType::DEFAULT, pParameter->getObjectName());
      pCallNode->addChild(pVariableNode);
      ++i;
    }

  pExpanded = expand_function_calls(pCallNode, pFunctionDB);
  delete pCallNode;
  CPPUNIT_ASSERT(pExpanded != NULL);
  // (k1-k3*1.3)+((3*k2)-5.23)
  CPPUNIT_ASSERT(pExpanded->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pExpanded->subType() == CEvaluationNode::SubType::PLUS);
  pChild = dynamic_cast<CEvaluationNode*>(pExpanded->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MINUS);
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->getData() == std::string("k1"));
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MULTIPLY);
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->getData() == std::string("k3"));
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::NUMBER);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT((fabs(pChild->getValue() - 1.3) / 1.3) < 1e-6);
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);

  // (3*b)-5.23
  pChild = dynamic_cast<CEvaluationNode*>(pExpanded->getChild()->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MINUS);
  // 3*b
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::OPERATOR);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::MULTIPLY);
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getChild());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::NUMBER);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT((fabs(pChild->getValue() - 3.0) / 3.0) < 1e-6);
  pChild = dynamic_cast<CEvaluationNode*>(pChild->getSibling());
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::VARIABLE);
  CPPUNIT_ASSERT(pChild->getData() == std::string("k2"));
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);
  // 5.23
  pChild = dynamic_cast<CEvaluationNode*>(pExpanded->getChild()->getSibling()->getChild()->getSibling());
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->mainType() == CEvaluationNode::MainType::NUMBER);
  CPPUNIT_ASSERT(pChild->subType() == CEvaluationNode::SubType::DOUBLE);
  CPPUNIT_ASSERT((fabs(pChild->getValue() - 5.23) / 5.23) < 1e-6);
  CPPUNIT_ASSERT(pChild->getSibling() == NULL);

  delete pExpanded;
}

const char* test_compare_utilities::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.27 (Debug) (http://www.copasi.org) at 2008-08-30 15:28:23 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"27\">\n"
  "  <ListOfFunctions>\n"
  "    <Function key=\"Function_37\" name=\"function_1\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        3*k\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_260\" name=\"k\" order=\"0\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_38\" name=\"function_2\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        B+A\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_258\" name=\"A\" order=\"0\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_243\" name=\"B\" order=\"1\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_39\" name=\"function_3\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        C-k*1.3\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_246\" name=\"k\" order=\"0\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_250\" name=\"C\" order=\"1\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_40\" name=\"function_4\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        function_2(x,y)/2\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_254\" name=\"x\" order=\"0\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_261\" name=\"y\" order=\"1\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_41\" name=\"function_5\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        function_3(c,a)+(function_1(b)-5.23)\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_262\" name=\"a\" order=\"0\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_263\" name=\"b\" order=\"1\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_264\" name=\"c\" order=\"2\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_42\" name=\"function_6\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        function_5(k1,k2,k3)\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_265\" name=\"k1\" order=\"0\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_266\" name=\"k2\" order=\"1\" role=\"variable\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_267\" name=\"k3\" order=\"2\" role=\"variable\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <!--"
  "    <Function key=\"Function_54\" name=\"Function for reaction1\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        3*parameter_1\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_269\" name=\"parameter_1\" order=\"0\" role=\"constant\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_55\" name=\"Function for reaction2\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        parameter_2+parameter_1\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_272\" name=\"parameter_1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_273\" name=\"parameter_2\" order=\"1\" role=\"constant\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_56\" name=\"Function for reaction3\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        species_2-parameter_1*1.3\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_276\" name=\"parameter_1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_277\" name=\"species_2\" order=\"1\" role=\"product\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_57\" name=\"Function for reaction4\" type=\"UserDefined\" reversible=\"true\">\n"
  "      <Expression>\n"
  "        function_2(species_1,species_2)/2\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_280\" name=\"species_1\" order=\"0\" role=\"substrate\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_281\" name=\"species_2\" order=\"1\" role=\"product\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_58\" name=\"Function for reaction5\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        function_3(species_2,parameter_1)+(function_1(parameter_3)-5.23)\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_285\" name=\"parameter_1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_286\" name=\"parameter_3\" order=\"1\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_287\" name=\"species_2\" order=\"2\" role=\"product\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_59\" name=\"Function for reaction6\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        function_5(parameter_1,parameter_2,parameter_3)\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_291\" name=\"parameter_1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_292\" name=\"parameter_2\" order=\"1\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_293\" name=\"parameter_3\" order=\"2\" role=\"constant\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    -->\n"
  "  </ListOfFunctions>\n"
  "  <!--\n"
  "  <Model key=\"Model_1\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"l\" quantityUnit=\"mol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "  <p>Model with function call in kinetics and rules.</p>\n"
  "  <p>This is to check function expansion for export to L1V2</p>\n"
  "</body>\n"
  "\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_2\" name=\"C\" simulationType=\"assignment\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          function_5(&lt;CN=Root,Model=New Model,Vector=Values[K1],Reference=Value&gt;,2.4,3.5)\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_3\" name=\"D\" simulationType=\"ode\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          function_2(&lt;CN=Root,Model=New Model,Vector=Values[K1],Reference=Value&gt;,3.4)\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_4\" name=\"E\" simulationType=\"ode\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          function_4(1.4,&lt;CN=Root,Model=New Model,Vector=Values[K2],Reference=Value&gt;)\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_5\" name=\"F\" simulationType=\"ode\" compartment=\"Compartment_0\">\n"
  "        <Expression>\n"
  "          function_6(&lt;CN=Root,Model=New Model,Vector=Values[K3],Reference=Value&gt;,&lt;CN=Root,Model=New Model,Vector=Values[K1],Reference=Value&gt;,3.4)\n"
  "        </Expression>\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K1\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          function_1(4.5)\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_1\" name=\"K2\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_2\" name=\"K3\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          function_3(2,&lt;CN=Root,Model=New Model,Vector=Values[K1],Reference=Value&gt;)\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction1\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_81\" name=\"parameter_1\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_54\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_269\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_1\" name=\"reaction2\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_80\" name=\"parameter_1\" value=\"1\"/>\n"
  "          <Constant key=\"Parameter_79\" name=\"parameter_2\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_55\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_272\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_273\">\n"
  "              <SourceParameter reference=\"ModelValue_1\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_2\" name=\"reaction3\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_78\" name=\"parameter_1\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_56\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_276\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_277\">\n"
  "              <SourceParameter reference=\"Metabolite_1\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_3\" name=\"reaction4\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <KineticLaw function=\"Function_57\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_280\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_281\">\n"
  "              <SourceParameter reference=\"Metabolite_1\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_4\" name=\"reaction5\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_77\" name=\"parameter_1\" value=\"1\"/>\n"
  "          <Constant key=\"Parameter_76\" name=\"parameter_3\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_58\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_285\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_286\">\n"
  "              <SourceParameter reference=\"ModelValue_2\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_287\">\n"
  "              <SourceParameter reference=\"Metabolite_1\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "      <Reaction key=\"Reaction_5\" name=\"reaction6\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_67\" name=\"parameter_1\" value=\"1\"/>\n"
  "          <Constant key=\"Parameter_68\" name=\"parameter_2\" value=\"1\"/>\n"
  "          <Constant key=\"Parameter_71\" name=\"parameter_3\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_59\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_291\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_292\">\n"
  "              <SourceParameter reference=\"ModelValue_1\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_293\">\n"
  "              <SourceParameter reference=\"ModelValue_2\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_3\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_4\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_5\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_2\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_2\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 6.0221415e+23 6.0221415e+23 6.0221415e+23 6.0221415e+23 6.0221415e+23 6.0221415e+23 1.1 1.3 1.2 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "  -->\n"
  "</COPASI>\n"
  ;
