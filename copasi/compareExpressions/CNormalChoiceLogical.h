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

#ifndef CNormalChoiceLogical_H__
#define CNormalChoiceLogical_H__

#include <string>
#include <iostream>

#include "copasi/compareExpressions/CNormalBase.h"

class CNormalLogical;

class CNormalChoiceLogical : public CNormalBase
  {
  protected:
    CNormalLogical* mpCondition;
    CNormalLogical* mpTrue;
    CNormalLogical* mpFalse;

  public:
    CNormalChoiceLogical();
    CNormalChoiceLogical(const CNormalChoiceLogical& src);
    virtual ~CNormalChoiceLogical();

    CNormalBase * copy() const override;

    CNormalChoiceLogical& operator=(const CNormalChoiceLogical& src);
    bool operator==(const CNormalChoiceLogical& rhs) const;
    bool operator<(const CNormalChoiceLogical& rhs) const;

    bool setCondition(const CNormalLogical& cond);
    bool setTrueExpression(const CNormalLogical& branch);
    bool setFalseExpression(const CNormalLogical& branch);

    const CNormalLogical& getCondition() const;
    CNormalLogical& getCondition();

    const CNormalLogical& getTrueExpression() const;
    CNormalLogical& getTrueExpression();

    const CNormalLogical& getFalseExpression() const;
    CNormalLogical& getFalseExpression();

    static bool checkConditionTree(const CNormalBase& branch);

    std::string toString() const override;
    bool simplify() override;

    void negate();
  };

std::ostream& operator<<(std::ostream& os, const CNormalChoiceLogical& choice);

#endif /* CNormalChoiceLogical_H__ */
