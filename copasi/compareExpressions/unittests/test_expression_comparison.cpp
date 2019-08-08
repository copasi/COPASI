// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "test_expression_comparison.hpp"

#include <stdexcept>

#include "copasi/function/CEvaluationTree.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/compareExpressions/CNormalTranslation.h"
#include "copasi/compareExpressions/CNormalBase.h"
#include "copasi/compareExpressions/CNormalFraction.h"
#include "copasi/core/CRootContainer.h"

void test_expression_comparison::setUp()
{
  CRootContainer::init(false, 0, NULL);
}

void test_expression_comparison::tearDown()
{
  CRootContainer::destroy();
}

void test_expression_comparison::test_substrate_activation()
{
  // latex expression infix 1:
  // \frac{V*\(\frac{substrate}{Ksa}\)^{2}}{1+\frac{substrate}{Ksc}+\frac{substrate}{Ksa}+\(\frac{substrate}{Ksa}\)^{2}}
  std::string infix1("V*(substrate/Ksa)^2/(1+substrate/Ksc+substrate/Ksa+(substrate/Ksa)^2)");
  // latex expression infix 2:
  // \frac{V*substrate^2}{substrate^2+Ksa*(Ksa*Ksc^(-1)+1)*substrate+Ksa^2}
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
  delete secondBase;
  delete firstBase;
  delete secondTree;
  delete firstTree;
}

void test_expression_comparison::test_allosteric_inhibition()
{
  try
    {
      // latex expression infix 1
      // {V*substrate*\(Ks+substrate˜)^{n-1}}{L*\(Ks*\(1+\frac{Inhibitor}{Ki}\)\)^{n}+\(Ks+substrate\)^{n}}
      std::string infix1("V*substrate*(Ks+substrate)^(n-1)/(L*(Ks*(1+Inhibitor/Ki))^n+(Ks+substrate)^n)");
      // latex expression infix 2
      // \frac{\(Ks+substrate\)^{-1}*substrate*V}{1+L*\(\frac{Ki^{-1}*Ks*Inhibitor+Ks}{substrate+Ks}\)^{n}}
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
      std::string s1 = firstFraction->toString();
      //std::cout << "fraction 1: " << s1 << std::endl;
      CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
      CPPUNIT_ASSERT(secondBase != NULL);
      CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
      CPPUNIT_ASSERT(secondFraction != NULL);
      std::string s2 = secondFraction->toString();
      //std::cout << "fraction 2: " << s2 << std::endl;
      CPPUNIT_ASSERT(*firstFraction == *secondFraction);
      delete secondBase;
      delete firstBase;
      delete secondTree;
      delete firstTree;
    }
  catch (CCopasiException cce)
    {
      std::cout << "A COPASI exception." << std::endl;
    }
}

void test_expression_comparison::test_hyperbolic_modifier()
{
  // Latex expression infix 1
  // \frac{\(Vf*\frac{substrate}{Kms}-Vr*\frac{product}{Kmp}\)*\(1+\frac{b*Modifier}{a*Kd}\)}{1+\frac{Modifier}{Kd}+\(\frac{substrate}{Kms}+\frac{product}{Kmp}\)*\(1+\frac{Modifier}{a*Kd}\)}
  std::string infix1("((Vf*substrate/Kms-Vr*product/Kmp)*(1+b*Modifier/(a*Kd)))/(1+Modifier/Kd+(substrate/Kms+product/Kmp)*(1+Modifier/(a*Kd)))");

  // Latex expression infix 2
  // \frac{Kms^{-1}*Vf*substrate-Kmp^{-1}*Vr*product+\(\frac{Vf*b*substrate}{Kms*a}+\frac{b*-Vr*product}{a*Kmp}\)*Modifier/Kd}{1+\frac{1}{Kmp}*product+\frac{1}{Kms}*substrate+\(1+1/(a*Kms)*substrate+\frac{1}{a*Kmp}*product\)*\frac{Modifier}{Kd}}
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
  std::string s1 = firstFraction->toString();
  //std::cout << "first  : " << s1 << std::endl;
  CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
  CPPUNIT_ASSERT(secondBase != NULL);
  CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
  CPPUNIT_ASSERT(secondFraction != NULL);
  std::string s2 = secondFraction->toString();
  //std::cout << "second: " << s2 << std::endl;
  CPPUNIT_ASSERT(*firstFraction == *secondFraction);
  delete secondBase;
  delete firstBase;
  delete secondTree;
  delete firstTree;
}

void test_expression_comparison::test_specific_activation_reversible()
{
  // latex expression 1
  // \frac{\(Vf*\frac{substrate}{Kms}-Vr*\frac{product}{Kmp}\)*Activator}{Ka+\(1+\frac{substrate}{Kms}+\frac{product}{Kmp}\)*Activator}
  std::string infix1("(Vf*substrate/Kms-Vr*product/Kmp)*Activator/(Ka+(1+substrate/Kms+product/Kmp)*Activator)");
  // latex expression 2
  // \frac{K_{mp}*V_{f}*substrate-K_{ms}*V_{r}*product}{Activator^{-1}*K_{a}*K_{ms}*K_{mp}+K_{ms}*K_{mp}+K_{mp}*substrate+K_{ms}*product}
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
  delete secondBase;
  delete firstBase;
  delete secondTree;
  delete firstTree;
}

void test_expression_comparison::test_ordered_bi_bi()
{
  // latex expression 1
  // \frac{Vf*\(substratea*substrateb-\frac{productp*productq}{Keq}\)}/{substratea*substrateb*\(1+\frac{productp}{Kip}\)+Kma*substrateb+Kmb*\(substratea+Kia\)+\frac{Vf}{Vr*Keq}*\(Kmq*productp*\(1+\frac{substratea}{Kia}\)+productq*\(Kmp*\(1+\frac{Kia*substrateb}{Kma*Kmb}\)+productp*\(1+\frac{substrateb}{Kib}\)\)\)}
  std::string infix1("Vf*(substratea*substrateb-productp*productq/Keq)/(substratea*substrateb*(1+productp/Kip)+Kma*substrateb+Kmb*(substratea+Kia)+Vf/(Vr*Keq)*(Kmq*productp*(1+substratea/Kia)+productq*(Kmp*(1+Kia*substrateb/(Kma*Kmb))+productp*(1+substrateb/Kib))))");
  // latex expression 2
  // \frac{Vf*\left(productp^{-1}*productq^{-1}-substratea^{-1}*substrateb^{-1}*Keq^{-1}\right)}{productq^{-1}*\left(productp^{-1}+Kip^{-1}\right)+Kma*substratea^{-1}*productp^{-1}*productq^{-1}+productp^{-1}*productq^{-1}*Kmb*substrateb^{-1}*\left(1+Kia*substratea^{-1}\right)+\frac{Vf}{Vr*Keq}*\left(Kmq*productq^{-1}*substrateb^{-1}*(substratea^{-1}+\frac{1}{Kia})+Kmp*productp^{-1}*substratea^{-1}*\left(substrateb^{-1}+\frac{Kia}{Kma*Kmb}\right)+substratea^{-1}*(substrateb^{-1}+\frac{1}{Kib}\right)}
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
  delete secondBase;
  delete firstBase;
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
      // latex expression 1
      // \frac{Vf*\frac{substrate}{Shalve}*\(1-\frac{product}{substrate*Keq}\)*\(\frac{substrate}{Shalve}+\frac{product}{Phalve}\)^{h-1}}{1+(\frac{substrate}{Shalve}+\frac{product}{Phalve})^{h}}
      std::string infix_numerator1 = "Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)";
      // Test with a simpler version
      std::string infix_denominator1 = "(1+(substrate/Shalve+product/Phalve)^h)";
      std::string infix1("Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/(1+(substrate/Shalve+product/Phalve)^h)");
      // latex expression 2
      // \frac{(substrate*Phalve+product*Shalve)^{h-1}*\frac{Vf}{Shalve}*(substrate-Keq^{-1}*product)}{Phalve^{h-1}*Shalve^{h-1}+\frac{(substrate*Phalve+product*Shalve)^{h}}{Shalve*Phalve}}

      std::string infix_numerator2 = "((substrate*Phalve+product*Shalve)^(h-1)*Vf/Shalve*(substrate-Keq^(-1)*product))";
      std::string infix_denominator2 = "(Phalve^(h-1)*Shalve^(h-1)+(substrate*Phalve+product*Shalve)^h/(Shalve*Phalve))";
      std::string infix2("((substrate*Phalve+product*Shalve)^(h-1)*Vf/Shalve*(substrate-Keq^(-1)*product))/(Phalve^(h-1)*Shalve^(h-1)+(substrate*Phalve+product*Shalve)^h/(Shalve*Phalve))");
      //std::string infix1("Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(5-1)/(1+(substrate/Shalve+product/Phalve)^5)");
      //std::string infix2("(substrate*Phalve+product*Shalve)^(5-1)*Vf/Shalve*(substrate-Keq^(-1)*product)/(Phalve^(5-1)*Shalve^(5-1)+(substrate*Phalve+product*Shalve)^5/(Shalve*Phalve))");

      // numerators
      CEvaluationTree* firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
      firstTree->setInfix(infix_numerator1);
      CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
      CEvaluationTree* secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
      secondTree->setInfix(infix_numerator2);
      CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
      //std::cout << "<p>Normalizing first tree.</p>" << std::endl;
      CNormalBase * firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
      CPPUNIT_ASSERT(firstBase != NULL);
      CNormalFraction* firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
      CPPUNIT_ASSERT(firstFraction != NULL);
      std::string s1 = firstFraction->toString();
      // I do seem to get the expected term below
      //((-1) * Phalve * Vf * product * (Phalve * substrate + Shalve * product)^(h) + Keq * Phalve * Vf * substrate * (Phalve * substrate + Shalve * product)^(h))/(Keq * Phalve * substrate * (Phalve)^(h) * (Shalve)^(h) + Keq * Shalve * product * (Phalve)^(h) * (Shalve)^(h))
      //std::cout << "numerator 1: " << s1 << std::endl;
      //std::cout << "<p>Normalizing second tree.</p>" << std::endl;
      CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
      CPPUNIT_ASSERT(secondBase != NULL);
      CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
      CPPUNIT_ASSERT(secondFraction != NULL);
      std::string s2 = secondFraction->toString();
      // the normalization of the numerator leads to the same result I got when I did it manually
      // "((-1) * Vf * product * (Phalve * substrate + Shalve * product)^(h) + Keq * Vf * substrate * (Phalve * substrate + Shalve * product)^(h))/(Keq * Phalve * Shalve * substrate + Keq * Shalve^2 * product)"
      //std::cout << "numerator 2: " << s2 << std::endl;

      // denominator
      delete secondBase;
      delete firstBase;
      delete firstTree;
      firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
      firstTree->setInfix(infix_denominator1);
      CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
      delete secondTree;
      secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
      secondTree->setInfix(infix_denominator2);
      CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
      //std::cout << "<p>Normalizing first tree.</p>" << std::endl;
      firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
      CPPUNIT_ASSERT(firstBase != NULL);
      firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
      CPPUNIT_ASSERT(firstFraction != NULL);
      s1 = firstFraction->toString();
      // the results of the normalization of the first denominator is the same I get when I do it manually
      // "((Phalve)^(h) * (Shalve)^(h) + (Phalve * substrate + Shalve * product)^(h))/((Phalve)^(h) * (Shalve)^(h))"
      //std::cout << "denominator 1: " << s1 << std::endl;
      //std::cout << "<p>Normalizing second tree.</p>" << std::endl;
      secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
      CPPUNIT_ASSERT(secondBase != NULL);
      secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
      CPPUNIT_ASSERT(secondFraction != NULL);
      s2 = secondFraction->toString();
      // the results of the normalization of the second denominator is the same I get when I do it manually
      // "((Phalve)^(h) * (Shalve)^(h) + (Phalve * substrate + Shalve * product)^(h))/(Phalve * Shalve)"
      //std::cout << "denominator 2: " << s2 << std::endl;

      // complete infix
      delete secondBase;
      delete firstBase;
      delete firstTree;
      firstTree = new CEvaluationTree("first tree", NULL, CEvaluationTree::Function);
      firstTree->setInfix(infix1);
      CPPUNIT_ASSERT(firstTree->getRoot() != NULL);
      delete secondTree;
      secondTree = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
      secondTree->setInfix(infix2);
      CPPUNIT_ASSERT(secondTree->getRoot() != NULL);
      //std::cout << "<p>Normalizing first tree.</p>" << std::endl;
      firstBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(firstTree->getRoot()));
      CPPUNIT_ASSERT(firstBase != NULL);
      firstFraction = dynamic_cast<CNormalFraction*>(firstBase);
      CPPUNIT_ASSERT(firstFraction != NULL);
      s1 = firstFraction->toString();
      //std::cout << "infix 1: " << s1 << std::endl;
      //std::cout << "<p>Normalizing second tree.</p>" << std::endl;
      secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
      CPPUNIT_ASSERT(secondBase != NULL);
      secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
      CPPUNIT_ASSERT(secondFraction != NULL);
      s2 = secondFraction->toString();
      //std::cout << "infix 2: " << s2 << std::endl;
      //std::cout << "<p>first: " << std::endl;
      //std::cout << "first: " << *firstFraction << std::endl;
      //std::cout << "<p>second: " << std::endl;
      //std::cout << "second: " << *secondFraction << std::endl;
      //std::cout << "</body>\n</html>" << std::endl;

      // this is probably one of the cases where the normalization of two
      // equivalent equations does not lead to the same normalform.
      // At least not when I tried to do it manually.
      //CPPUNIT_ASSERT(*firstFraction == *secondFraction);
      delete secondBase;
      delete firstBase;
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
  // latex expression 1
  // \frac{Vf*\frac{substrate}{Shalve}*\(1-\frac{product}{substrate*Keq}\)*(\frac{substrate}{Shalve}+\frac{product}{Phalve})^{h-1}}{\frac{1+\(\frac{Modifier}{Mhalve}\)^h}/{1+alpha*\(\frac{Modifier}{Mhalve}\)^h}+\(\frac{substrate}{Shalve}+\frac{product}{Phalve}\)^h}
  std::string infix1("Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/((1+(Modifier/Mhalve)^h)/(1+alpha*(Modifier/Mhalve)^h)+(substrate/Shalve+product/Phalve)^h)");
  // latex expression 2
  // \frac{Vf*Shalve^{-1}*(substrate-Keq^{-1}*product)*(Shalve^{-1}*substrate+Phalve^{-1}*product)^{h-1}}{\frac{Modifier^{h}+Mhalve^{h}}{alpha*Modifier^{h}+Mhalve^{h}}+(Shalve^{-1}*substrate+Phalve^{-1}*product)^{h}}
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
  //CPPUNIT_ASSERT(*firstFraction == *secondFraction);
  delete secondBase;
  delete firstBase;
  delete secondTree;
  delete firstTree;
}

void test_expression_comparison::test_reversible_hill_two_modifiers()
{
  // latex expression 1
  // \frac{Vf*\frac{substrate}{Shalve}*\(1-\frac{product}{substrate*Keq}\)*\(\frac{substrate}{Shalve}+\frac{product}{Phalve}\)^{h-1}}{\frac{1+\(\frac{ModifierA}{MAhalve}\)^{h}+\(\frac{ModifierB}{MBhalve}\)^{h}}{1+alphaA*\(\frac{ModifierA}{MAhalve}\)^{h}+alphaB*\(\frac{ModifierB}{MBhalve}\)^{h}+alphaA*alphaB*alphaAB*\(\frac{ModifierA}{MAhalve}\)^{h}*\(\frac{ModifierB}{MBhalve}\)^{h}}+\(\frac{substrate}{Shalve}+\frac{product}{Phalve}\)^{h}}
  std::string infix1("Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/((1+(ModifierA/MAhalve)^h+(ModifierB/MBhalve)^h)/(1+alphaA*(ModifierA/MAhalve)^h+alphaB*(ModifierB/MBhalve)^h+alphaA*alphaB*alphaAB*(ModifierA/MAhalve)^h*(ModifierB/MBhalve)^h)+(substrate/Shalve+product/Phalve)^h)");
  // latex expression 2
  // \frac{Shalve^{-1}*Vf*\(substrate-Keq^{-1}*product\)*(Shalve^{-1}*substrate+Phalve^{-1}*product)^{h-1}}{\frac{MAhalve^{h}*MBhalve^{h}+ModifierA^{h}*MBhalve^{h}+ModifierB^{h}*MAhalve^{h}}{MAhalve^{h}*MBhalve^{h}+alphaA*ModifierA^{h}*MBhalve^{h}+alphaB*ModifierB^{h}*MAhalve^{h}+alphaA*alphaB*alphaAB*ModifierA^{h}*ModifierB^{h}}+\(Shalve^{-1}*substrate+Phalve^{-1}*product\)^{h}}
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
  std::string s1 = firstFraction->toString();
  CNormalBase * secondBase = dynamic_cast<CNormalFraction*>(CNormalTranslation::normAndSimplifyReptdly(secondTree->getRoot()));
  CPPUNIT_ASSERT(secondBase != NULL);
  CNormalFraction* secondFraction = dynamic_cast<CNormalFraction*>(secondBase);
  CPPUNIT_ASSERT(secondFraction != NULL);
  std::string s2 = secondFraction->toString();
  //CPPUNIT_ASSERT(*firstFraction == *secondFraction);
  delete secondBase;
  delete firstBase;
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
      delete secondBase;
      delete firstBase;
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
