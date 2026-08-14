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

#ifndef CNormalChoice_H__
#define CNormalChoice_H__

#include <string>
#include <iostream>
#include "copasi/compareExpressions/CNormalBase.h"

class CNormalLogical;
class CNormalFraction;

class CNormalChoice : public CNormalBase
  {
  protected:
    CNormalLogical* mpCondition;
    CNormalFraction* mpTrue;
    CNormalFraction* mpFalse;

  public:
    CNormalChoice();
    CNormalChoice(const CNormalChoice& src);
    virtual ~CNormalChoice();

    CNormalBase * copy() const override;

    CNormalChoice& operator=(const CNormalChoice& src);
    bool operator==(const CNormalChoice& rhs) const;
    bool operator<(const CNormalChoice& rhs) const;

    bool setCondition(const CNormalLogical& cond);
    bool setTrueExpression(const CNormalFraction& branch);
    bool setFalseExpression(const CNormalFraction& branch);

    const CNormalLogical& getCondition() const;
    CNormalLogical& getCondition();

    const CNormalFraction& getTrueExpression() const;
    CNormalFraction& getTrueExpression();

    const CNormalFraction& getFalseExpression() const;
    CNormalFraction& getFalseExpression();

    static bool checkConditionTree(const CNormalBase& branch);
    static bool checkExpressionTree(const CNormalBase& branch);

    std::string toString() const override;
    bool simplify() override;

    friend std::ostream& operator<<(std::ostream& os, const CNormalChoice& choice);
  };

#endif /* CNormalChoice_H__ */
