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

    CNormalBase * copy() const override;
    bool simplify() override;

    std::string toString() const override;

    Type getType() const;
    void setType(Type type);

    CNormalFraction& getFraction();
    const CNormalFraction& getFraction() const;

    void setFraction(const CNormalFraction& frac);
  };

std::ostream& operator<<(std::ostream& os, const CNormalFunction& fun);

#endif /* COPASI_CNormalFunction_H__ */
