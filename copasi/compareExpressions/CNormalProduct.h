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

#ifndef COPASI_CNormalProduct_H__
#define COPASI_CNormalProduct_H__

#include <set>
#include <string>

#include "copasi/compareExpressions/CNormalBase.h"

class CNormalItem;
class CNormalItemPower;
class CNormalSum;
class CNormalLcm;
class CNormalFunction;
class CNormalGeneralPower;
class CNormalChoice;

class compareItemPowers
{
public:
  bool operator()(const CNormalItemPower* itemPower1, const CNormalItemPower* itemPower2) const;
};

/**
 * The class for products used in CNormal
 */
class CNormalProduct : public CNormalBase
{
private:
  /**
   * Enumeration of members
   */
  C_FLOAT64 mFactor;
  std::set<CNormalItemPower*, compareItemPowers > mItemPowers;

public:

  /**
   * Default constructor
   */
  CNormalProduct();

  /**
   * Copy contructor
   */
  CNormalProduct(const CNormalProduct& src);

  virtual CNormalBase * copy() const;

  /**
   * Assignment operator
   */
  CNormalProduct & operator=(const CNormalProduct& src);

  /**
   * Smaller operator
   */
  bool operator<(const CNormalProduct& rhs) const;

  /**
   * Destructor
   */
  virtual ~CNormalProduct();

  /**
   * Set the factor for this product.
   * @return true.
   */
  bool setFactor(const C_FLOAT64& number);

  /**
   * Multiply this product with a number.
   * @return true.
   */
  bool multiply(const C_FLOAT64& number);

  /**
   * Multiply an item to this product.
   * @return true.
   */
  bool multiply(const CNormalItem& item);

  /**
   * Multiply a function to this product.
   * @return true.
   */
  bool multiply(const CNormalFunction& fun);

  /**
   * Multiply a function to this product.
   * @return true.
   */
  bool multiply(const CNormalChoice& choice);

  /**
   * Multiply a general power to this product.
   * @return true.
   */
  bool multiply(const CNormalGeneralPower& pow);

  /**
   * Multiply an itempower to this product.
   * @return true.
   */
  bool multiply(const CNormalItemPower& itemPower);

  /**
   * Multiply a list of itempowers to this product.
   * @return true.
   */
  bool multiply(const std::set <CNormalItemPower*, compareItemPowers >& itemPowers);

  /**
   * Remove an itempower from this product, provided it is a factor of it.
   * @return true.
   */
  bool remove(std::set<CNormalItemPower*, compareItemPowers >::iterator it);

  /**
   * Remove an itempower from this product, provided it is a factor of it.
   * -used in multiplication with lcm-
   * @return true.
   */
  bool remove(const CNormalItemPower& itemPower);

  /**
   * Multiply this product with another product.
   * @return true
   */
  bool multiply(const CNormalProduct& product);

  /**
   * Multiply this product with a sum NOT CONTAINING FRACTIONS!.
   * @return sum.
   */
  CNormalSum* multiply(const CNormalSum& sum);

  /**
   * Multiply this product with a lcm.
   * @return true
   */
  const CNormalSum* multiply(const CNormalLcm& lcm);

  /**
   * Retrieve the factor of this product.
   * @return mFactor.
   */
  const C_FLOAT64 & getFactor() const;

  /**
   * Retrieve the set of itempowers of this product.
   * @return mItemPowers.
   */
  const std::set <CNormalItemPower*, compareItemPowers >& getItemPowers() const;

  /**
   * Sets the item powers of this product.
   */
  void setItemPowers(const std::set<CNormalItemPower*, compareItemPowers>& set);

  bool checkSamePowerList(const CNormalProduct & rhs) const;

  bool operator==(const CNormalProduct & rhs) const;

  virtual std::string toString() const;

  virtual bool simplify();

  CNormalGeneralPower* getDenominator() const;

  void setDenominatorsOne();

  /**
   * Returns a product that is 1.
   * In this case it only creates a new product instance with new.
   */
  static CNormalProduct* createUnitProduct();

  friend std::ostream & operator<< (std::ostream &os,
                                    const CNormalProduct & d);
};

#endif // COPASI_CNormalProduct_H__
