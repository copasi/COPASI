// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalGeneralPower.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/07/07 18:26:49 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalGeneralPower_H__
#define COPASI_CNormalGeneralPower_H__

#include <iostream>
#include <string>

#include "copasi/compareExpressions/CNormalBase.h"

class CNormalFraction;

class CNormalGeneralPower: public CNormalBase
  {
  public:
    enum Type
    {
      POWER = 0,
      MODULO,
      INVALID
    };

  protected:
    Type mType;
    CNormalFraction* mpLeft;
    CNormalFraction* mpRight;

    static const char* SYMBOLS[];

  public:
    CNormalGeneralPower();
    CNormalGeneralPower(const CNormalGeneralPower& src);
    virtual ~CNormalGeneralPower();

    CNormalGeneralPower& operator=(const CNormalGeneralPower& src);

    bool operator==(const CNormalGeneralPower& rhs) const;
    bool operator<(const CNormalGeneralPower& rhs) const;

    virtual CNormalBase * copy() const;
    virtual bool simplify();

    virtual std::string toString() const;

    CNormalFraction& getLeft();
    const CNormalFraction& getLeft() const;
    void setLeft(const CNormalFraction& left);
    CNormalFraction& getRight();
    const CNormalFraction& getRight() const;
    void setRight(const CNormalFraction& right);
    Type getType() const;
    void setType(Type type);
    bool checkIsOne() const;
    void multiply(const CNormalGeneralPower& generalPower);

    /**
     * Returns a general power that is (1/1)^(1/1).
     * It creates a new general power of type power and sets the left and right
     * side to a unit fraction.
     */
    static CNormalGeneralPower* createUnitGeneralPower();
  };

std::ostream& operator<<(std::ostream& os, const CNormalGeneralPower& pow);

#endif /* COPASI_CNormalGeneralPower_H__ */
