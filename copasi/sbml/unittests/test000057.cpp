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

#include "test000057.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000057::pCOPASIDATAMODEL = NULL;

void test000057::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000057::tearDown()
{
  CRootContainer::destroy();
}

void test000057::test_bug1006()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000057::MODEL_STRING));
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 5);
  const Parameter* pParameter1 = pSBMLModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  CPPUNIT_ASSERT(pParameter1->getConstant() == true);
  const Parameter* pParameter2 = pSBMLModel->getParameter(1);
  CPPUNIT_ASSERT(pParameter2 != NULL);
  CPPUNIT_ASSERT(pParameter2->getConstant() == true);
  const Parameter* pParameter3 = pSBMLModel->getParameter(2);
  CPPUNIT_ASSERT(pParameter3 != NULL);
  CPPUNIT_ASSERT(pParameter3->getConstant() == true);
  const Parameter* pParameter4 = pSBMLModel->getParameter(3);
  CPPUNIT_ASSERT(pParameter4 != NULL);
  CPPUNIT_ASSERT(pParameter4->getConstant() == true);
  const Parameter* pParameter5 = pSBMLModel->getParameter(4);
  CPPUNIT_ASSERT(pParameter5 != NULL);
  CPPUNIT_ASSERT(pParameter5->getConstant() == true);
  CPPUNIT_ASSERT(pSBMLModel->getNumInitialAssignments() == 5);
  const InitialAssignment* pIA = pSBMLModel->getInitialAssignment(0);
  CPPUNIT_ASSERT(pIA != NULL);
  CPPUNIT_ASSERT(pIA->getSymbol() == pParameter1->getId());
  CPPUNIT_ASSERT(pIA->isSetMath() == true);
  const ASTNode* pMath = pIA->getMath();
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

  pIA = pSBMLModel->getInitialAssignment(1);
  CPPUNIT_ASSERT(pIA != NULL);
  CPPUNIT_ASSERT(pIA->getSymbol() == pParameter2->getId());
  CPPUNIT_ASSERT(pIA->isSetMath() == true);
  pMath = pIA->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_PLUS);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild1->getReal() - 9.0) / 9.0) < 1e-15);
  pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild2->getReal() - 2.0) / 2.0) < 1e-15);

  pIA = pSBMLModel->getInitialAssignment(2);
  CPPUNIT_ASSERT(pIA != NULL);
  CPPUNIT_ASSERT(pIA->getSymbol() == pParameter3->getId());
  CPPUNIT_ASSERT(pIA->isSetMath() == true);
  pMath = pIA->getMath();
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

  pIA = pSBMLModel->getInitialAssignment(3);
  CPPUNIT_ASSERT(pIA != NULL);
  CPPUNIT_ASSERT(pIA->getSymbol() == pParameter4->getId());
  CPPUNIT_ASSERT(pIA->isSetMath() == true);
  pMath = pIA->getMath();
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

  pIA = pSBMLModel->getInitialAssignment(4);
  CPPUNIT_ASSERT(pIA != NULL);
  CPPUNIT_ASSERT(pIA->getSymbol() == pParameter5->getId());
  CPPUNIT_ASSERT(pIA->isSetMath() == true);
  pMath = pIA->getMath();
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
  // delete some initial assignments
  // delete iniaitl assignments for model value1,model value4 and model value5
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 5);
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
  pMV1->setInitialExpression("");
  pMV4->setInitialExpression("");
  pMV5->setInitialExpression("");

  // reexport the model to L2V3
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 5);
  pParameter1 = pSBMLModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  CPPUNIT_ASSERT(pParameter1->getConstant() == true);
  pParameter2 = pSBMLModel->getParameter(1);
  CPPUNIT_ASSERT(pParameter2 != NULL);
  CPPUNIT_ASSERT(pParameter2->getConstant() == true);
  pParameter3 = pSBMLModel->getParameter(2);
  CPPUNIT_ASSERT(pParameter3 != NULL);
  CPPUNIT_ASSERT(pParameter3->getConstant() == true);
  pParameter4 = pSBMLModel->getParameter(3);
  CPPUNIT_ASSERT(pParameter4 != NULL);
  CPPUNIT_ASSERT(pParameter4->getConstant() == true);
  pParameter5 = pSBMLModel->getParameter(4);
  CPPUNIT_ASSERT(pParameter5 != NULL);
  CPPUNIT_ASSERT(pParameter5->getConstant() == true);
  CPPUNIT_ASSERT(pSBMLModel->getNumInitialAssignments() == 2);
  pIA = pSBMLModel->getInitialAssignment(0);
  CPPUNIT_ASSERT(pIA != NULL);
  CPPUNIT_ASSERT(pIA->getSymbol() == pParameter2->getId());
  CPPUNIT_ASSERT(pIA->isSetMath() == true);
  pMath = pIA->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_PLUS);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild1->getReal() - 9.0) / 9.0) < 1e-15);
  pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild2->getReal() - 2.0) / 2.0) < 1e-15);

  pIA = pSBMLModel->getInitialAssignment(1);
  CPPUNIT_ASSERT(pIA != NULL);
  CPPUNIT_ASSERT(pIA->getSymbol() == pParameter3->getId());
  CPPUNIT_ASSERT(pIA->isSetMath() == true);
  pMath = pIA->getMath();
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
}

const char* test000057::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
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
  "      <parameter id=\"parameter_1\" name=\"A\" value=\"12\"/>\n"
  "      <parameter id=\"parameter_2\" name=\"B\" value=\"11\"/>\n"
  "      <parameter id=\"parameter_3\" name=\"C\" value=\"4\"/>\n"
  "      <parameter id=\"parameter_4\" name=\"D\" value=\"3\"/>\n"
  "      <parameter id=\"parameter_5\" name=\"E\" value=\"7\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfInitialAssignments>\n"
  "      <initialAssignment symbol=\"parameter_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <times/>\n"
  "            <cn> 3 </cn>\n"
  "            <cn> 4 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </initialAssignment>\n"
  "      <initialAssignment symbol=\"parameter_2\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <plus/>\n"
  "            <cn> 9 </cn>\n"
  "            <cn> 2 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </initialAssignment>\n"
  "      <initialAssignment symbol=\"parameter_3\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <minus/>\n"
  "            <cn> 8 </cn>\n"
  "            <cn> 4 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </initialAssignment>\n"
  "      <initialAssignment symbol=\"parameter_4\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <divide/>\n"
  "            <cn> 9 </cn>\n"
  "            <cn> 3 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </initialAssignment>\n"
  "      <initialAssignment symbol=\"parameter_5\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <plus/>\n"
  "            <cn> 6 </cn>\n"
  "            <cn> 1 </cn>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </initialAssignment>\n"
  "    </listOfInitialAssignments>\n"
  "  </model>\n"
  "</sbml>\n"
  ;
