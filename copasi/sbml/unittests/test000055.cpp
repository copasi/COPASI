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

#include "test000055.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/function/CExpression.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000055::pCOPASIDATAMODEL = NULL;

void test000055::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000055::tearDown()
{
  CRootContainer::destroy();
}

void test000055::test_bug1004()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000055::MODEL_STRING));
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  // check the order of the rules
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumInitialAssignments() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 5);
  const Parameter* pParameter1 = pSBMLModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  CPPUNIT_ASSERT(pParameter1->getConstant() == false);
  const Parameter* pParameter2 = pSBMLModel->getParameter(1);
  CPPUNIT_ASSERT(pParameter2 != NULL);
  CPPUNIT_ASSERT(pParameter2->getConstant() == false);
  const Parameter* pParameter3 = pSBMLModel->getParameter(2);
  CPPUNIT_ASSERT(pParameter3 != NULL);
  CPPUNIT_ASSERT(pParameter3->getConstant() == false);
  const Parameter* pParameter4 = pSBMLModel->getParameter(3);
  CPPUNIT_ASSERT(pParameter4 != NULL);
  CPPUNIT_ASSERT(pParameter4->getConstant() == false);
  const Parameter* pParameter5 = pSBMLModel->getParameter(4);
  CPPUNIT_ASSERT(pParameter5 != NULL);
  CPPUNIT_ASSERT(pParameter5->getConstant() == false);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 5);

  const Rule* pRule = pSBMLModel->getRule(0);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  const AssignmentRule* pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter1->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  const ASTNode* pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_TIMES);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  const ASTNode* pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild1->getReal() - 3.0) / 3.0) < 1e-15);
  const ASTNode* pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild2->getReal() - 4.0) / 4.0) < 1e-15);

  pRule = pSBMLModel->getRule(1);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter2->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_PLUS);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild1->getReal() - 2.0) / 2.0) < 1e-15);
  pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild2->getReal() - 9.0) / 9.0) < 1e-15);

  pRule = pSBMLModel->getRule(2);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter3->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_MINUS);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild1->getReal() - 8.0) / 8.0) < 1e-15);
  pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild2->getReal() - 4.0) / 4.0) < 1e-15);

  pRule = pSBMLModel->getRule(3);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter4->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_DIVIDE);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild1->getReal() - 9.0) / 9.0) < 1e-15);
  pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild2->getReal() - 3.0) / 3.0) < 1e-15);

  pRule = pSBMLModel->getRule(4);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter5->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_PLUS);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild1->getReal() - 6.0) / 6.0) < 1e-15);
  pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild2->getReal() - 1.0) / 1.0) < 1e-15);
  // modify the assignment rules
  // make rule for parameter1 depend on parameter3
  // make rule for parameter3 depend on parameter2
  // make rule for parameter4 depend on parameter5
  // make rule for parameter2 depend on parameter4
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 5);
  // find model value that corresponds to parameter1
  CModelValue *pMV1 = NULL, *pMV2 = NULL, *pMV3 = NULL, *pMV4 = NULL, *pMV5 = NULL;
  unsigned int i, iMax = pModel->getModelValues().size();

  for (i = 0; i < iMax; ++i)
    {
      CModelValue* pTmpMV = pModel->getModelValues()[i];

      if (pTmpMV->getSBMLId() == pParameter1->getId())
        {
          pMV1 = pTmpMV;
        }
      else if (pTmpMV->getSBMLId() == pParameter2->getId())
        {
          pMV2 = pTmpMV;
        }
      else if (pTmpMV->getSBMLId() == pParameter3->getId())
        {
          pMV3 = pTmpMV;
        }
      else if (pTmpMV->getSBMLId() == pParameter4->getId())
        {
          pMV4 = pTmpMV;
        }
      else if (pTmpMV->getSBMLId() == pParameter5->getId())
        {
          pMV5 = pTmpMV;
        }
    }

  CPPUNIT_ASSERT(pMV1 != NULL);
  CPPUNIT_ASSERT(pMV2 != NULL);
  CPPUNIT_ASSERT(pMV3 != NULL);
  CPPUNIT_ASSERT(pMV4 != NULL);
  CPPUNIT_ASSERT(pMV5 != NULL);
  CEvaluationNodeObject* pObjectNode = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pMV3->getCN() + ",Reference=Value>");
  CExpression* pExpr = new CExpression;
  pExpr->setRoot(pObjectNode);
  pMV1->setExpressionPtr(pExpr);
  pObjectNode = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pMV2->getCN() + ",Reference=Value>");
  pExpr = new CExpression;
  pExpr->setRoot(pObjectNode);
  pMV3->setExpressionPtr(pExpr);
  pObjectNode = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pMV5->getCN() + ",Reference=Value>");
  pExpr = new CExpression;
  pExpr->setRoot(pObjectNode);
  pMV4->setExpressionPtr(pExpr);
  pObjectNode = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pMV4->getCN() + ",Reference=Value>");
  pExpr = new CExpression;
  pExpr->setRoot(pObjectNode);
  pMV2->setExpressionPtr(pExpr);
  // reexport to SBML L2V1
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumInitialAssignments() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 5);
  pParameter1 = pSBMLModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  CPPUNIT_ASSERT(pParameter1->getConstant() == false);
  pParameter2 = pSBMLModel->getParameter(1);
  CPPUNIT_ASSERT(pParameter2 != NULL);
  CPPUNIT_ASSERT(pParameter2->getConstant() == false);
  pParameter3 = pSBMLModel->getParameter(2);
  CPPUNIT_ASSERT(pParameter3 != NULL);
  CPPUNIT_ASSERT(pParameter3->getConstant() == false);
  pParameter4 = pSBMLModel->getParameter(3);
  CPPUNIT_ASSERT(pParameter4 != NULL);
  CPPUNIT_ASSERT(pParameter4->getConstant() == false);
  pParameter5 = pSBMLModel->getParameter(4);
  CPPUNIT_ASSERT(pParameter5 != NULL);
  CPPUNIT_ASSERT(pParameter5->getConstant() == false);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 5);

  pRule = pSBMLModel->getRule(0);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter5->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_PLUS);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild1->getReal() - 6.0) / 6.0) < 1e-15);
  pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild2->getReal() - 1.0) / 1.0) < 1e-15);

  pRule = pSBMLModel->getRule(1);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter4->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter5->getId());
  CPPUNIT_ASSERT(pMath->getNumChildren() == 0);

  pRule = pSBMLModel->getRule(2);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter2->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter4->getId());
  CPPUNIT_ASSERT(pMath->getNumChildren() == 0);

  pRule = pSBMLModel->getRule(3);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter3->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter2->getId());
  CPPUNIT_ASSERT(pMath->getNumChildren() == 0);

  pRule = pSBMLModel->getRule(4);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter1->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter3->getId());
  CPPUNIT_ASSERT(pMath->getNumChildren() == 0);
}

const char* test000055::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
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
  "    <listOfParameters>\n"
  "      <parameter id=\"parameter_1\" name=\"A\" value=\"12\" constant=\"false\"/>\n"
  "      <parameter id=\"parameter_2\" name=\"B\" value=\"11\" constant=\"false\"/>\n"
  "      <parameter id=\"parameter_3\" name=\"C\" value=\"4\" constant=\"false\"/>\n"
  "      <parameter id=\"parameter_4\" name=\"D\" value=\"3\" constant=\"false\"/>\n"
  "      <parameter id=\"parameter_5\" name=\"E\" value=\"7\" constant=\"false\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"parameter_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <times/>\n"
  "            <cn> 3 </cn>\n"
  "            <cn> 4 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "      <assignmentRule variable=\"parameter_2\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <plus/>\n"
  "            <cn> 2 </cn>\n"
  "            <cn> 9 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "      <assignmentRule variable=\"parameter_3\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <minus/>\n"
  "            <cn> 8 </cn>\n"
  "            <cn> 4 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "      <assignmentRule variable=\"parameter_4\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <divide/>\n"
  "            <cn> 9 </cn>\n"
  "            <cn> 3 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "      <assignmentRule variable=\"parameter_5\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <plus/>\n"
  "            <cn> 6 </cn>\n"
  "            <cn> 1 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
  ;
