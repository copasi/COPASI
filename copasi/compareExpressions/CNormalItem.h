// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalItem.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/12/12 09:11:50 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalItem_H__
#define COPASI_CNormalItem_H__

#include <string>
#include "copasi/compareExpressions/CNormalBase.h"

/**
 * The class for items used in CNormal
 */
class CNormalItem : public CNormalBase
  {
  public:
    /**
     * Enumeration of possible item types.
     */
    enum Type
    {
      CONSTANT,
      VARIABLE
    };

    std::string mName;
    Type mType;

    /**
     * Default constructor
     */
    CNormalItem();

    /**
     * Data constructor
     */
    CNormalItem(const std::string& name, const Type& type);

    virtual CNormalBase * copy() const;

    /**
     * Copy contructor
     */
    CNormalItem(const CNormalItem& src);

    /**
     * Assignment operator
     */
    CNormalItem& operator=(const CNormalItem& src);

    /**
     * Set the name of this item
     * @return true.
     */
    bool setName(const std::string& name);

    /**
     * Set the type of this item.
     * @return true.
     */
    bool setType(const Type& type);

    /**
     * Retrieve the name of this item.
     * @return mName
     */
    const std::string getName() const;

    /**
     * Retrieve the type of this item.
     * @return mType
     */
    const Type& getType() const;

    /**
     * Examine equality of two items.
     * @return bool.
     */
    bool operator==(const CNormalItem & rhs) const;

    /**
     * Examine inequality of two item.
     * @return bool.
     */
    bool operator<(const CNormalItem & rhs) const;

    virtual std::string toString() const;

    virtual bool simplify(){return true;};

    friend std::ostream & operator<< (std::ostream &os,
                                      const CNormalItem & d);
  };

#endif // COPASI_CNormalItem_H__
