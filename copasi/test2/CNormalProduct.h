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

#ifndef COPASI_CNormalProduct
#define COPASI_CNormalProduct

#include <set>
#include "copasi/copasi.h"

//#include "CNormalItem.h"
//#include "CNormalSum.h"
//#include "CNormalLcm.h"
#include "CNormalItemPower.h"
//class CNormalItem;
//class CNormalItemPower;
class CNormalSum;
class CNormalLcm;

class compareItemPowers
{public: bool operator()(const CNormalItemPower* itemPower1, const CNormalItemPower* itemPower2);};

//class comparePowers
//{public: bool operator()(const CNormalPower* power1, const CNormalPower* power2);}

/**
 * The class for products used in CNormal
 */
class CNormalProduct
{
public:

private:
  /**
   * Enumeration of members
   */
  C_FLOAT64 mFactor;
  std::set<CNormalItemPower*, compareItemPowers> mItemPowers;
  //std::set<CNormalPower*, comparePowers> mPowers;

public:

  /**
   * Default constructor
   */
  CNormalProduct();

  /**
   * Copy contructor
   */
  CNormalProduct(const CNormalProduct& src);

  /**
   * Assignment operator
   */
  CNormalProduct & operator=(const CNormalProduct& src);

  /**
   * Destructor
   */
  ~CNormalProduct();

  /**
   * Create a product from an evaluation node that is not necessarily a multiply operator.
   * @return CNormalProduct*, pointer to newly created product.
   */
  static CNormalProduct * createProduct(const CEvaluationNode* node);

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
   * Multiply an itempower to this product.
   * @return true.
   */
  bool multiply(const CNormalItemPower& itemPower);

  /**
   * Multiply a power to this product.
   * @return true.
   *
  bool multiply(const CNormalPower& power);*/

  /**
   * Multiply a list of itempowers to this product.
   * @return true.
   */
  bool multiply(const std::set <CNormalItemPower*, compareItemPowers>& itemPowers);

  /**
   * Multiply a list of powers to this product.
   * @return true.
   *
  bool multiply(const std::set <CNormalPower*, comparePowers>& powers);*/

  /**
   * Remove an itempower from this product, provided it is a factor of it.
   * @return true.
   */
  bool remove(std::set <CNormalItemPower*, compareItemPowers>::iterator it);

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
  const std::set <CNormalItemPower*, compareItemPowers>& getItemPowers() const;

  /**
   * Retrieve the set of powers of this product.
   * @return mPowers.
   *
  const std::set <CNormalPower*, comparePowers>& getPowers() const;*/

  bool checkSamePowerList(const CNormalProduct & rhs) const;

  bool operator==(const CNormalProduct & rhs) const;

  friend std::ostream & operator<<(std::ostream &os,
                                   const CNormalProduct & d);
};

#endif // COPASI_CNormalProduct
