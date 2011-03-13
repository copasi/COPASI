// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalSum.h,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/03/13 17:40:50 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalSum_H__
#define COPASI_CNormalSum_H__

#include <string>
#include <set>

#include "copasi/compareExpressions/CNormalBase.h"
#include "copasi/copasi.h"

class CNormalProduct;
class CNormalFraction;
class CNormalItemPower;
class CNormalLcm;

class compareProducts
{
public:
  bool operator()(const CNormalProduct* product1, const CNormalProduct* product2) const;
};

/**
 * The class for sums used in CNormal
 */
class CNormalSum : public CNormalBase
{
private:
  /**
   * Enumeration of members
   */
  std::set<CNormalProduct*, compareProducts > mProducts;
  std::set<CNormalFraction*> mFractions;

public:
  /**
   * Default constructor
   */
  CNormalSum();

  /**
   * Copy Constructor
   */
  CNormalSum(const CNormalSum& src);

  /**
   * Assignment operator
   */
  CNormalSum & operator=(const CNormalSum& src);

  /**
   * Smaller operator
   */
  bool operator<(const CNormalSum& rhs) const;

  /**
   * Destructor
   */
  virtual ~CNormalSum();

  virtual CNormalBase * copy() const;

  /**
   * Retrieve the number of summands of this sum.
   * @return int
   */
  int getSize() const;

  /**
   * Add product to this sum.
   * @return true.
   */
  bool add(const CNormalProduct& product);

  /**
   * Add fraction to this sum.
   * @return true.
   */
  bool add(const CNormalFraction& fraction);

  /**
   * Add a sum to this sum.
   * @return true.
   */
  bool add(const CNormalSum& sum);

  /**
   * Multiply this sum with a number.
   * @return true.
   */
  bool multiply(const C_FLOAT64& number);

  /**
   * Multiply this sum with an itempower.
   * @return true.
   */
  bool multiply(const CNormalItemPower& itemPower);

  /**
   * Multiply this sum with another sum, both do not contain fractions!!
   * @return true.
   */
  bool multiply(const CNormalSum& sum);

  /**
   * Multiply this sum by a lcm
   * Numerator and denominator of mFractions do not contain further fractions!
   * @return true.
   */
  bool multiply(const CNormalLcm& lcm);

  /**
   * Divide this sum by an itempower, provided it is a factor of it
   * -This sum does not contain fractions!
   * @return true.
   */
  bool divide(const CNormalItemPower& itemPower);

  /**
   * Retrieve the set of products of this sum.
   * @return mProducts
   */
  const std::set<CNormalProduct*, compareProducts >& getProducts() const;

  /**
   * Retrieve the set of fractions of this sum.
   * @return mFractions.
   */
  const std::set<CNormalFraction*>& getFractions() const;

  /**
   * Examine equality of two sums.
   * @return bool.
   */
  bool operator==(const CNormalSum & rhs) const;

  /**
   * Sets the products of this product.
   */
  void setProducts(const std::set<CNormalProduct*, compareProducts>& set);

  /**
   * Sets the fractions of this product.
   */
  void setFractions(const std::set<CNormalFraction*>& set);

  /**
   * Check if an itempower is a factor of this sum.
   * @return positive C_FLOAT64, exponent of the largest power of the item contained in this sum.
   *         if == 0, power is not a factor of this sum.
   * This sum does not contain fractions!!
   */
  C_FLOAT64 checkFactor(const CNormalItemPower& itemPower) const;

  virtual std::string toString() const;

  virtual bool simplify();

  bool checkIsOne() const;

  bool checkIsZero() const;

  /**
   * Returns a sum that is 1.
   * In this case it only creates a new sum sum and adds a unit product to
   *the sum.
   */
  static CNormalSum* createUnitSum();

  friend std::ostream & operator<< (std::ostream &os, const CNormalSum & d);

  static void printProducts(const CNormalSum* pSum);
};

#endif // COPASI_CNormalSum_H__
