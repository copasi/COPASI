// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_CNormalItemPower_H__
#define COPASI_CNormalItemPower_H__

#include <string>

#include "copasi/compareExpressions/CNormalItem.h"
#include "copasi/compareExpressions/CNormalBase.h"

/**
 * The class for powers of items with real positive exponent used in CNormal
 */
class CNormalItemPower : public CNormalBase
{
public:
  enum ItemType
  {
    ITEM,
    FUNCTION,
    POWER,
    CHOICE,
    CALL,
    LOGICAL,
    INVALID
  };

protected:

  /**
   * Enumeration of members.
   */
  CNormalBase* mpItem;
  C_FLOAT64 mExp;  // mExp is > 0

  ItemType mItemType;

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
   * Destructor
   */
  virtual ~CNormalItemPower();

  /**
   * Assignment operator Constructor
   */
  CNormalItemPower& operator=(const CNormalItemPower& src);

  CNormalBase * copy() const override;

  /**
   * Data constructor
   */
  CNormalItemPower(const CNormalBase& item, const C_FLOAT64& exp);

  /**
   * Set the base of this itempower.
   * @return true.
   */
  bool setItem(const CNormalBase& item);

  /**
   * Set the exponent of this power
   * @return true
   */
  bool setExp(const C_FLOAT64& number);

  /**
   * Retrieve the base of this power
   * @return mItem
   */
  CNormalBase& getItem();

  /**
   * Retrieve the base of this power
   * @return mItem
   */
  const CNormalBase& getItem() const;

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

  std::string toString() const override;

  bool simplify() override;

  ItemType getItemType() const;

  friend std::ostream & operator<< (std::ostream &os,
                                    const CNormalItemPower & d);
};

#endif // COPASI_CNormalItemPower_H__
