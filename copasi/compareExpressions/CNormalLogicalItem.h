// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CNormalLogicalItem_H__
#define CNormalLogicalItem_H__

#include <iostream>
#include <string>

#include "copasi/compareExpressions/CNormalBase.h"
#include "copasi/compareExpressions/CNormalFraction.h"

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
    CNormalFraction mLeft;
    CNormalFraction mRight;

  public:
    CNormalLogicalItem();
    CNormalLogicalItem(const CNormalLogicalItem& src);
    virtual ~CNormalLogicalItem();
    CNormalLogicalItem& operator=(const CNormalLogicalItem& src);
    bool operator<(const CNormalLogicalItem& rhs) const;
    bool operator==(const CNormalLogicalItem& rhs) const;
    CNormalBase * copy() const override;
    std::string toString() const override;
    bool simplify() override;

    CNormalFraction& getLeft();
    const CNormalFraction& getLeft() const;
    CNormalFraction& getRight();
    const CNormalFraction& getRight() const;

    bool setLeft(const CNormalFraction& left);
    bool setRight(const CNormalFraction& right);

    Type getType() const;
    void setType(Type type);
    void negate();
  };

std::ostream& operator<<(std::ostream& os, const CNormalLogicalItem& item);

#endif /* CNormalItemLogical_H__ */
