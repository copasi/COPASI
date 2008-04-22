// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalFunction.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/04/22 11:06:48 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalFunction_H__
#define COPASI_CNormalFunction_H__

#include <iostream>
#include <string>

#include "copasi/compareExpressions/CNormalBase.h"

class CNormalFraction;

class CNormalFunction: public CNormalBase
  {
  public:
    enum Type
    {
      LOG = 0,
      LOG10,
      EXP,
      SIN,
      COS,
      TAN,
#ifdef SEC
# undef SEC
#endif
      SEC,
      CSC,
      COT,
      SINH,
      COSH,
      TANH,
      SECH,
      CSCH,
      COTH,
      ARCSIN,
      ARCCOS,
      ARCTAN,
      ARCSEC,
      ARCCSC,
      ARCCOT,
      ARCSINH,
      ARCCOSH,
      ARCTANH,
      ARCSECH,
      ARCCSCH,
      ARCCOTH,
      SQRT,
      ABS,
      FLOOR,
      CEIL,
      FACTORIAL,
      INVALID
    };

  protected:
    Type mType;

    CNormalFraction* mpFraction;

  public:
    static const char* NAMES[];

    CNormalFunction();
    CNormalFunction(const CNormalFunction& src);
    virtual ~CNormalFunction();

    CNormalFunction& operator=(const CNormalFunction& src);
    bool operator==(const CNormalFunction& src) const;
    bool operator<(const CNormalFunction& src) const;

    virtual CNormalBase * copy() const;
    virtual bool simplify();

    virtual std::string toString() const;

    Type getType() const;
    void setType(Type type);

    CNormalFraction& getFraction();
    const CNormalFraction& getFraction() const;

    void setFraction(const CNormalFraction& frac);
  };

std::ostream& operator<<(std::ostream& os, const CNormalFunction& fun);

#endif /* COPASI_CNormalFunction_H__ */
