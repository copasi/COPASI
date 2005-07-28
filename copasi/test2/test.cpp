/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/test.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/28 13:46:32 $
   End CVS Header */

// Main
//
// (C) Stefan Hoops 2002
//

#include <stdlib.h>
#include "CNormalItem.h"
#include "CNormalProduct.h"
#include "CNormalSum.h"
#include "CNormalLcm.h"
#include "CNormalFraction.h"

int main()
{
  std::cout << "CNormal test program" << std::endl;

  CNormalItem* item0 = new CNormalItem();
  item0->mName = "a";
  CNormalItem* item1 = new CNormalItem();
  item1->mName = "b";

  /**CNormalProduct* product0 = new CNormalProduct();
  product0->add(*item0);
  product0->add(*item1);
  product0->multiply(2.0);
  std::cout << "product0: " << *product0 << std::endl;
  CNormalProduct* product1 = new CNormalProduct(*product0);
  product1->multiply(3.0);
  std::cout << "product1: " << *product1 << std::endl;
  CNormalSum* sum = new CNormalSum();
  sum->add(*product0);
  sum->add(*product1);
  std::cout << "sum: " << *sum << std::endl;
  */

  CNormalItem* item2 = new CNormalItem();
  item2->mName = "c";
  CNormalProduct* product0 = new CNormalProduct();
  product0->multiply(2.0);
  product0->multiply(*item0);
  product0->multiply(*item0);
  CNormalSum* sum = new CNormalSum();
  CNormalProduct* product1 = new CNormalProduct();
  product1->multiply(0.5);
  product1->multiply(*item1);
  CNormalProduct* product2 = new CNormalProduct();
  product2->multiply(3.0);
  product2->multiply(*item2);
  sum->add(*product1);
  sum->add(*product2);
  CNormalSum* newsum = product0->multiply(*sum);
  CNormalFraction* fraction0 = new CNormalFraction();
  fraction0->setNumerator(*sum);
  fraction0->setDenominator(*newsum);
  CNormalFraction* fraction01 = new CNormalFraction();
  CNormalSum* num01 = new CNormalSum();
  num01->add(*product1);
  CNormalSum* denom01 = new CNormalSum();
  denom01->add(*product0);
  fraction01->setNumerator(*num01);
  fraction01->setDenominator(*denom01);
  CNormalFraction* fraction02 = new CNormalFraction();
  CNormalSum* num02 = new CNormalSum();
  num02->add(*product2);
  CNormalSum* denom02 = new CNormalSum();
  product1->multiply(*item0);
  denom02->add(*product1);
  fraction02->setNumerator(*num02);
  fraction02->setDenominator(*denom02);
  CNormalSum* numerator = new CNormalSum();
  numerator->add(*fraction0);
  numerator->add(*product0);
  numerator->add(*fraction01);
  CNormalSum* denominator = new CNormalSum();
  denominator->add(*sum);
  denominator->add(*fraction02);
  CNormalFraction* fraction1 = new CNormalFraction();
  fraction1->setNumerator(*numerator);
  fraction1->setDenominator(*denominator);
  std::cout << "fraction1: " << *fraction1 << std::endl;
  fraction1->simplifyFraction();
  std::cout << "simplified fraction: " << *fraction1 << std::endl;
  return 0;
}
