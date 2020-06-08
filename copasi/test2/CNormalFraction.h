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

#ifndef COPASI_CNormalFraction
#define COPASI_CNormalFraction

#include <vector>
#include "copasi/copasi.h"

//#include "CNormalItem.h"
//#include "CNormalProduct.h"
#include "CNormalSum.h"
//#include "CNormalLcm.h"

class CNormalProduct;
//class CNormalSum;
class CNormalLcm;

class CNormalFraction
{
private:
  /**
   * Enumeration of members
   */
  CNormalSum mNumerator;
  CNormalSum mDenominator;

public:
  /**
   * Default constructor
   */
  CNormalFraction();

  /**
   * Copy contructor
   */
  CNormalFraction(const CNormalFraction& src);

  /**
   * Create a fraction from a node. node is necessarily a DIVIDE operator if not the root node of the tree.
   * @return CNormalFraction*, pointer to newly created fraction.
   */
  static CNormalFraction* createFraction(const CEvaluationNode* node);

  /**
   * Set numerator of this fraction
   * @return true.
   */
  bool setNumerator(const CNormalSum& numerator);

  /**
   * Set denominator of this fraction.
   * @return true.
   */
  bool setDenominator(const CNormalSum& denominator);

  /**
   * Check if the denominator of this fraction equals 1.
   * @return bool
   */
  bool checkDenominatorOne() const;

  /**
   * Set the denominator of this fraction equal 1.
   * @return true.
   */
  bool setDenominatorOne();

  /**
   * Retrieve the numerator of this fraction.
   * @return mNumerator.
   */
  const CNormalSum& getNumerator() const;

  /**
   * Retrieve the denominator of this fraction.
   * @return mDenominator.
   */
  const CNormalSum& getDenominator() const;

  /**
   * Check if this fraction contains further fractions.
   * @return bool.
   */
  bool checkForFractions() const;

  /**
   * Expand this fraction by a lcm.
   * @return true.
   */
  bool expand(const CNormalLcm& lcm);

  /**
   * Cancel common items of mNumerator and mDenominator.
   * @return true.
   */
  bool cancel();

  /**
   * Multiply this fraction with a number.
   * @return true.
   */
  bool multiply(const C_FLOAT64& number);

  /**
   * Multiply a fraction with an itempower.
   * @return true.
   */
  bool multiply(const CNormalItemPower& itemPower);

  /**
   * Find lcm of denominators of respective fractions contained in this fraction.
   * @return pointer to lcm.
   */
  const CNormalLcm* findLcm() const;

  /**
   * Multiply this fraction by a lcm.
   * @return CNormalSum*, pointer to result of multiplication ie. a normal sum.
   * This fraction is useless now.
   */
  const CNormalSum* multiply(CNormalLcm lcm);

  /**
   * Check if numerator and denominator contain fractions,
   * find lcm of respective denominators, expand this fraction by lcm and cancel.
   * @return true
   */
  bool simplify();

  bool operator==(const CNormalFraction & rhs) const;

  /*
   * Remove the denominator of this fraction.
   * -applicable if checkDenominatorOne() = true-
   * @return pointer to mNumerator
   *
  CNormalSum* removeDenominator();*/

  /*
   * Multiply this fraction with a sum.
   * @return true.
   *
  bool multiply(const CNormalSum& sum);*/

  /*
   * Multiply this fraction with a fraction.
   * @return true.
   *
  bool multiply(const CNormalFraction& fraction);*/

  /*
   * Divide this fraction by a fraction.
   * @return true.
   *
  bool divide(const CNormalFraction& fraction);*/

  /*
   * Check whether this fraction equals another fraction.
   *  @return bool
   *
  bool checkEqual(const CNormalFraction& fraction) const;*/

  friend std::ostream & operator<<(std::ostream &os,
                                   const CNormalFraction & d);
};

#endif // COPASI_CNormalFraction
