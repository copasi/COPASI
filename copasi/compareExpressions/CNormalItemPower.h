// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalItemPower.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/09/18 19:34:00 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalItemPower_H__
#define COPASI_CNormalItemPower_H__

#include "compareExpressions/CNormalItem.h"
#include "compareExpressions/CNormalBase.h"
#include <string>

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

    virtual CNormalBase * copy() const;

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

    virtual std::string toString() const;

    virtual bool simplify();

    ItemType getItemType() const;

    friend std::ostream & operator<< (std::ostream &os,
                                      const CNormalItemPower & d);
  };

#endif // COPASI_CNormalItemPower_H__
