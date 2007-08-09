// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/test_expression_comparison.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/09 10:53:34 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "test_expression_comparison.hpp"

#include <stdexcept>

#include "function/CEvaluationTree.h"
#include "utilities/CCopasiException.h"
#include "compareExpressions/CNormalTranslation.h"
#include "compareExpressions/CNormalBase.h"
#include "compareExpressions/CNormalFraction.h"

void test_expression_comparison::setUp()
{}

void test_expression_comparison::tearDown()
{}

void test_expression_comparison::test_substrate_activation()
{
  std::string infix1("V*(substrate/Ksa)^2/(1+substrate/Ksc+substrate/Ksa+(substrate/Ksa)^2)");
  std::string infix2("V*substrate^2/(substrate^2+Ksa*(Ksa*Ksc^(-1)+1)*substrate+Ksa^2)");
  CEvaluationTree* firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
  firstTree->setInfix(infix1);
  CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
  CEvaluationTree* secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
  secondTree->setInfix(infix2);
  CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
  CNormalBase * firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
  CPPUNIT_ASSERT(firstBase != NULL);
  CNormalFraction* firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
  CPPUNIT_ASSERT(firstFraction != NULL);
  CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
  CPPUNIT_ASSERT(secondBase != NULL);
  CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
  CPPUNIT_ASSERT(secondFraction != NULL);
  CPPUNIT_ASSERT(*firstFraction == *secondFraction);
  delete secondFraction;
  delete firstFraction;
  delete secondTree;
  delete firstTree;
}

void test_expression_comparison::test_allosteric_inhibition()
{
  try
    {
      std::string infix1("V*substrate*(Ks+substrate)^(n-1)/(L*(Ks*(1+Inhibitor/Ki))^n+(Ks+substrate)^n)");
      std::string infix2("(Ks+substrate)^(-1)*(substrate*V)/(1+L*((Ki^(-1)*Ks*Inhibitor+Ks)/(substrate+Ks))^n)");
      CEvaluationTree* firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
      firstTree->setInfix(infix1);
      CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
      CEvaluationTree* secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
      secondTree->setInfix(infix2);
      CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
      //std::cout << firstTree->getRoot()->getInfix() << std::endl;
      CNormalBase * firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
      CPPUNIT_ASSERT(firstBase != NULL);
      CNormalFraction* firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
      CPPUNIT_ASSERT(firstFraction != NULL);
      CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
      CPPUNIT_ASSERT(secondBase != NULL);
      CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
      CPPUNIT_ASSERT(secondFraction != NULL);
      CPPUNIT_ASSERT(*firstFraction == *secondFraction);
      delete secondFraction;
      delete firstFraction;
      delete secondTree;
      delete firstTree;
    }
  catch (std::exception e)
    {
      std::cout << "An exception." << std::endl;
    }
  catch (CCopasiException cce)
    {
      std::cout << "A COPASI exception." << std::endl;
    }
}

void test_expression_comparison::test_hyperbolic_modifier()
{
  std::string infix1("((Vf*substrate/Kms-Vr*product/Kmp)*(1+b*Modifier/(a*Kd)))/(1+Modifier/Kd+(substrate/Kms+product/Kmp)*(1+Modifier/(a*Kd)))");
  std::string infix2("(Kms^(-1)*Vf*substrate-Kmp^(-1)*Vr*product+((Vf*b*substrate)/(Kms*a)+(b*(-Vr)*product)/(a*Kmp))*Modifier/Kd)/(1+1/Kmp*product+1/Kms*substrate+(1+1/(a*Kms)*substrate+1/(a*Kmp)*product)*Modifier/Kd)");
  CEvaluationTree* firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
  firstTree->setInfix(infix1);
  CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
  CEvaluationTree* secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
  secondTree->setInfix(infix2);
  CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
  CNormalBase * firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
  CPPUNIT_ASSERT(firstBase != NULL);
  CNormalFraction* firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
  CPPUNIT_ASSERT(firstFraction != NULL);
  CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
  CPPUNIT_ASSERT(secondBase != NULL);
  CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
  CPPUNIT_ASSERT(secondFraction != NULL);
  CPPUNIT_ASSERT(*firstFraction == *secondFraction);
  delete secondFraction;
  delete firstFraction;
  delete secondTree;
  delete firstTree;
}

void test_expression_comparison::test_specific_activation_reversible()
{
  std::string infix1("(Vf*substrate/Kms-Vr*product/Kmp)*Activator/(Ka+(1+substrate/Kms+product/Kmp)*Activator)");
  std::string infix2("(Kmp*Vf*substrate-Kms*Vr*product)/(Activator^(-1)*Ka*Kms*Kmp+Kms*Kmp+Kmp*substrate+Kms*product)");
  CEvaluationTree* firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
  firstTree->setInfix(infix1);
  CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
  CEvaluationTree* secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
  secondTree->setInfix(infix2);
  CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
  CNormalBase * firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
  CPPUNIT_ASSERT(firstBase != NULL);
  CNormalFraction* firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
  CPPUNIT_ASSERT(firstFraction != NULL);
  CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
  CPPUNIT_ASSERT(secondBase != NULL);
  CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
  CPPUNIT_ASSERT(secondFraction != NULL);
  CPPUNIT_ASSERT(*firstFraction == *secondFraction);
  delete secondFraction;
  delete firstFraction;
  delete secondTree;
  delete firstTree;
}

void test_expression_comparison::test_ordered_bi_bi()
{
  std::string infix1("Vf*(substratea*substrateb-productp*productq/Keq)/(substratea*substrateb*(1+productp/Kip)+Kma*substrateb+Kmb*(substratea+Kia)+Vf/(Vr*Keq)*(Kmq*productp*(1+substratea/Kia)+productq*(Kmp*(1+Kia*substrateb/(Kma*Kmb))+productp*(1+substrateb/Kib))))");
  std::string infix2("Vf*(productp^(-1)*productq^(-1)-substratea^(-1)*substrateb^(-1)*Keq^(-1))/(productq^(-1)*(productp^(-1)+Kip^(-1))+Kma*substratea^(-1)*productp^(-1)*productq^(-1)+productp^(-1)*productq^(-1)*Kmb*substrateb^(-1)*(1+Kia*substratea^(-1))+Vf/(Vr*Keq)*(Kmq*productq^(-1)*substrateb^(-1)*(substratea^(-1)+1/Kia)+Kmp*productp^(-1)*substratea^(-1)*(substrateb^(-1)+Kia/(Kma*Kmb))+substratea^(-1)*(substrateb^(-1)+1/Kib)))");
  CEvaluationTree* firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
  firstTree->setInfix(infix1);
  CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
  CEvaluationTree* secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
  secondTree->setInfix(infix2);
  CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
  CNormalBase * firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
  CPPUNIT_ASSERT(firstBase != NULL);
  CNormalFraction* firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
  CPPUNIT_ASSERT(firstFraction != NULL);
  CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
  CPPUNIT_ASSERT(secondBase != NULL);
  CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
  CPPUNIT_ASSERT(secondFraction != NULL);
  CPPUNIT_ASSERT(*firstFraction == *secondFraction);
  delete secondFraction;
  delete firstFraction;
  delete secondTree;
  delete firstTree;
}

void test_expression_comparison::test_reversible_hill()
{
  try
    {
      //std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
      //std::cout << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN\"" << std::endl;
      //std::cout << "\"http://www.w3.org/TR/MathML2/dtd/xhtml-math11-f.dtd\" [" << std::endl;
      //std::cout << "<!ENTITY mathml \"http://www.w3.org/1998/Math/MathML\">" << std::endl;
      //std::cout << "]>" << std::endl;
      //std::cout << "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\n<header></header>\n<body>" << std::endl;
      std::string infix1("Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/(1+(substrate/Shalve+product/Phalve)^h)");
      std::string infix2("(substrate*Phalve+product*Shalve)^(h-1)*Vf/Shalve*(substrate-Keq^(-1)*product)/(Phalve^(h-1)*Shalve^(h-1)+(substrate*Phalve+product*Shalve)^h/(Shalve*Phalve))");
      CEvaluationTree* firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
      firstTree->setInfix(infix1);
      CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
      CEvaluationTree* secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
      secondTree->setInfix(infix2);
      CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
      //std::cout << "<p>Normalizing first tree.</p>" << std::endl;
      CNormalBase * firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
      CPPUNIT_ASSERT(firstBase != NULL);
      CNormalFraction* firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
      CPPUNIT_ASSERT(firstFraction != NULL);
      //std::cout << "<p>Normalizing second tree.</p>" << std::endl;
      CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
      CPPUNIT_ASSERT(secondBase != NULL);
      CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
      CPPUNIT_ASSERT(secondFraction != NULL);
      //std::cout << "<p>first: " << std::endl;
      //std::cout << *firstFraction << "</p>" << std::endl;
      //std::cout << "<p>second: " << std::endl;
      //std::cout << *secondFraction << "</p>" << std::endl;
      //std::cout << "</body>\n</html>" << std::endl;
      CPPUNIT_ASSERT(*firstFraction == *secondFraction);
      delete secondFraction;
      delete firstFraction;
      delete secondTree;
      delete firstTree;
    }
  catch (CCopasiException cce)
    {
      std::cout << "CopasiException " << std::endl;
    }
}

void test_expression_comparison::test_reversible_hill_one_modifier()
{
  std::string infix1("Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/((1+(Modifier/Mhalve)^h)/(1+alpha*(Modifier/Mhalve)^h)+(substrate/Shalve+product/Phalve)^h)");
  std::string infix2("(Vf*Shalve^(-1)*(substrate-Keq^(-1)*product)*(Shalve^(-1)*substrate+Phalve^(-1)*product)^(h-1))/((Modifier^h+Mhalve^h)/(alpha*Modifier^h+Mhalve^h)+(Shalve^(-1)*substrate+Phalve^(-1)*product)^h)");
  CEvaluationTree* firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
  firstTree->setInfix(infix1);
  CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
  CEvaluationTree* secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
  secondTree->setInfix(infix2);
  CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
  CNormalBase * firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
  CPPUNIT_ASSERT(firstBase != NULL);
  CNormalFraction* firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
  CPPUNIT_ASSERT(firstFraction != NULL);
  CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
  CPPUNIT_ASSERT(secondBase != NULL);
  CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
  CPPUNIT_ASSERT(secondFraction != NULL);
  CPPUNIT_ASSERT(*firstFraction == *secondFraction);
  delete secondFraction;
  delete firstFraction;
  delete secondTree;
  delete firstTree;
}

void test_expression_comparison::test_reversible_hill_two_modifiers()
{
  std::string infix1("Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/((1+(ModifierA/MAhalve)^h+(ModifierB/MBhalve)^h)/(1+alphaA*(ModifierA/MAhalve)^h+alphaB*(ModifierB/MBhalve)^h+alphaA*alphaB*alphaAB*(ModifierA/MAhalve)^h*(ModifierB/MBhalve)^h)+(substrate/Shalve+product/Phalve)^h)");
  std::string infix2("Shalve^(-1)*Vf*(substrate-Keq^(-1)*product)*(Shalve^(-1)*substrate+Phalve^(-1)*product)^(h-1)/((MAhalve^h*MBhalve^h+ModifierA^h*MBhalve^h+ModifierB^h*MAhalve^h)/(MAhalve^h*MBhalve^h+alphaA*ModifierA^h*MBhalve^h+alphaB*ModifierB^h*MAhalve^h+alphaA*alphaB*alphaAB*ModifierA^h*ModifierB^h)+(Shalve^(-1)*substrate+Phalve^(-1)*product)^h)");
  CEvaluationTree* firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
  firstTree->setInfix(infix1);
  CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
  CEvaluationTree* secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
  secondTree->setInfix(infix2);
  CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
  CNormalBase * firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
  CPPUNIT_ASSERT(firstBase != NULL);
  CNormalFraction* firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
  CPPUNIT_ASSERT(firstFraction != NULL);
  CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
  CPPUNIT_ASSERT(secondBase != NULL);
  CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
  CPPUNIT_ASSERT(secondFraction != NULL);
  CPPUNIT_ASSERT(*firstFraction == *secondFraction);
  delete secondFraction;
  delete firstFraction;
  delete secondTree;
  delete firstTree;
}

bool test_expression_comparison::are_expressions_equal(const std::string& expr1, const std::string& expr2, const std::string& /*filename*/, bool oldStyle)
{
  bool result = false;
  //std::ofstream file(filename.c_str(),std::ios_base::out|std::ios_base::trunc);
  //std::streambuf* sbuf = std::cout.rdbuf();
  //std::cout.rdbuf(file.rdbuf());
  try
    {
      //std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
      //std::cout << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN\"" << std::endl;
      //std::cout << "\"http://www.w3.org/TR/MathML2/dtd/xhtml-math11-f.dtd\" [" << std::endl;
      //std::cout << "<!ENTITY mathml \"http://www.w3.org/1998/Math/MathML\">" << std::endl;
      //std::cout << "]>" << std::endl;
      //std::cout << "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\n<header></header>\n<body>" << std::endl;
      CEvaluationTree* firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
      firstTree->setInfix(expr1);
      CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
      CEvaluationTree* secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
      secondTree->setInfix(expr2);
      CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
      //std::cout << "<p>Normalizing first tree.</p>" << std::endl;
      CNormalBase * firstBase = NULL;
      if (oldStyle == true)
        {
          firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree));
        }
      else
        {
          firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
        }
      CPPUNIT_ASSERT(firstBase != NULL);
      CNormalFraction* firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
      CPPUNIT_ASSERT(firstFraction != NULL);
      //std::cout << "<p>Normalizing second tree.</p>" << std::endl;
      CNormalBase * secondBase = NULL;
      if (oldStyle == true)
        {
          secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree));
        }
      else
        {
          secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
        }
      CPPUNIT_ASSERT(secondBase != NULL);
      CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
      CPPUNIT_ASSERT(secondFraction != NULL);
      //std::cout << "<p>first: " << std::endl;
      //std::cout << *firstFraction << "</p>" << std::endl;
      //std::cout << "<p>second: " << std::endl;
      //std::cout << *secondFraction << "</p>" << std::endl;
      //std::cout << "</body>\n</html>" << std::endl;
      result = (*firstFraction == *secondFraction);
      delete secondFraction;
      delete firstFraction;
      delete secondTree;
      delete firstTree;
    }
  catch (CCopasiException cce)
    {
      std::cout << "CopasiException " << std::endl;
    }
  //file.close();
  //std::cout.rdbuf(sbuf);
  return result;
}

void test_expression_comparison::test_fraction_to_a_power()
{
  std::string expr1("(A/B+C/D)^E");
  std::string expr2("(C/D+A/B)^E");
  bool result = are_expressions_equal(expr1, expr2, "are_expressions_equal.xhtml", false);
  CPPUNIT_ASSERT(result == true);
}
