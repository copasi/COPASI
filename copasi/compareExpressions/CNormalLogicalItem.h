// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalLogicalItem.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/07 16:49:49 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CNormalLogicalItem_H__
#define CNormalLogicalItem_H__

#include <iostream>
#include <string>

#include "test3/CNormalBase.h"

class CNormalFraction;

class CNormalLogicalItem : public CNormalBase
  {
  public:
    enum Type
    {
      TRUE,
      FALSE,
      EQ,
      NE,
      LT,
      GT,
      GE,
      LE,
      INVALID
    };

  protected:
    Type mType;
    CNormalFraction* mpLeft;
    CNormalFraction* mpRight;

  public:
    CNormalLogicalItem();
    CNormalLogicalItem(const CNormalLogicalItem& src);
    virtual ~CNormalLogicalItem();
    CNormalLogicalItem& operator=(const CNormalLogicalItem& src);
    bool operator<(const CNormalLogicalItem& rhs) const;
    bool operator==(const CNormalLogicalItem& rhs) const;
    virtual CNormalLogicalItem* copy() const;
    virtual std::string toString() const;
    virtual bool simplify();

    CNormalFraction* getLeft();
    const CNormalFraction* getLeft() const;
    CNormalFraction* getRight();
    const CNormalFraction* getRight() const;

    bool setLeft(const CNormalFraction& left);
    bool setRight(const CNormalFraction& right);

    Type getType() const;
    void setType(Type type);
    void negate();
  };

std::ostream& operator<<(std::ostream& os, const CNormalLogicalItem& item);

#endif /* CNormalItemLogical_H__ */
