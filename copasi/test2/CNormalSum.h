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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalSum
#define COPASI_CNormalSum

#include <vector>
#include "copasi/copasi.h"

#include "CNormalItemPower.h"
//#include "CNormalProduct.h"
//#include "CNormalLcm.h"
//#include "CNormalFraction.h"

class CNormalProduct;
class CNormalLcm;
class CNormalFraction;

class compareProducts
{public: bool operator()(const CNormalProduct* product1, const CNormalProduct* product2);};

/**
 * The class for sums used in CNormal
 */
class CNormalSum
{
private:
  /**
   * Enumeration of members
   */
  std::set<CNormalProduct*, compareProducts> mProducts;
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
   * Destructor
   */
  ~CNormalSum();

  /**
   * Create a sum from an evaluation node -node does not need to be a PLUS operator!
   * @return CNormalSum*, pointer to newly created sum
   */
  static CNormalSum* CNormalSum::createSum(const CEvaluationNode* node);

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
   * Check if an itempower is a factor of this sum.
   * @return positive C_FLOAT64, exponent of the largest power of the item contained in this sum.
   *         if == 0, power is not a factor of this sum.
   * This sum does not contain fractions!!
   */
  C_FLOAT64 checkFactor(const CNormalItemPower& itemPower) const;

  /**
   * Retrieve the set of products of this sum.
   * @return mProducts
   */
  const std::set<CNormalProduct*, compareProducts>& getProducts() const;

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

  friend std::ostream & operator<<(std::ostream &os,
                                   const CNormalSum & d);
};

#endif // COPASI_CNormalSum
