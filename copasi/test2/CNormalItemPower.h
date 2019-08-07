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

#ifndef COPASI_CNormalItemPower
#define COPASI_CNormalItemPower

#include "copasi/copasi.h"

#include "CNormalItem.h"

/**
 * The class for powers of items with real positive exponent used in CNormal
 */
class CNormalItemPower
{
private:
  /**
   * Enumeration of members.
   */
  CNormalItem mItem;
  C_FLOAT64 mExp;  // mExp is > 0

public:
  /**
   * Default constructor
   */
  CNormalItemPower();

  /**
   * Copy Constructor
   */
  CNormalItemPower(const CNormalItemPower& src);

  /**
   * Data constructor
   */
  CNormalItemPower(const CNormalItem& item, const C_FLOAT64& exp);

  /**
   * Create an item power from an evaluation node.
   * Node MUST BE a POWER operator with second child (exponent) of type NUMBER !!
   * @return CNormalItemPower*, pointer to newly created item power.
   */
  static CNormalItemPower * createItemPower(const CEvaluationNode* node);

  /**
   * Set the base of this itempower.
   * @return true.
   */
  bool setItem(const CNormalItem& item);

  /**
   * Set the exponent of this power
   * @return true
   */
  bool setExp(const C_FLOAT64& number);

  /**
   * Retrieve the base of this power
   * @return mItem
   */
  const CNormalItem& getItem() const;

  /**
   * Retrieve the exponent of this power
   * @return mExp
   */
  const C_FLOAT64& getExp() const;

  /**
   * Examine equality of two item powers.
   * @return bool.
   */
  bool operator==(const CNormalItemPower & rhs) const;

  /**
   * Examine inequality of two item powers.
   * @return bool.
   */
  bool operator<(const CNormalItemPower & rhs) const;

  friend std::ostream & operator<<(std::ostream &os,
                                   const CNormalItemPower & d);
};

/*
 * The class for powers with general product exponent used in CNormal
 *
class CNormalPower
{
  private:
  **
   * Enumeration of members.
   *
  CNormalSum mBase;
  CNormalProduct mExp;  //factor of mExp is in (0,1], otherwise could expand (base : sum)^int !!


  public:
  **
   * Default constructor
   *
  CNormalPower();


  **
   * Copy Constructor
   *
  CNormalPower(const CNormalPower& src);


  **
   * Data constructor
   *
  CNormalPower(const CNormalSum& sum, const CNormalProduct& product);


  **
   * Set the base of this power.
   * @return true.
   *
  bool setBase(const CNormalSum& sum);


  **
   * Set the exponent of this power
   * @return true
   *
  bool setExp(const CNormalProduct& product);


  **
   * Set the factor of the exponent of this power
   * @return true.
   *
  bool setExpFactor(const C_FLOAT64 & factor);


  **
   * Multiply this power with another power.
   * Only execute if powers have the same base and the same power list in the exponent.
   * @return true
   *
  bool multiply(const CNormalPower& power);


  **
   * Retrieve the base of this power
   * @return mBase
   *
  const CNormalSum& getBase() const;


  **
   * Retrieve the exponent of this power
   * @return mExp
   *
  const CNormalProduct& getExp() const;


  **
   * Examine equality of two powers.
   * @return bool.
   *
  bool operator==(const CNormalPower & rhs) const;


  **
   * Examine inequality of two powers.
   * @return bool.
   *
  bool operator<(const CNormalPower & rhs) const;


  friend std::ostream & operator<<(std::ostream &os,
                                     const CNormalPower & d);
};
 */

#endif // COPASI_CNormalItemPower
