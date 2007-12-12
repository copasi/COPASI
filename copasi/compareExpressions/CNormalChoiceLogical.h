// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalChoiceLogical.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/12/12 09:11:50 $
// End CVS Header

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

    virtual CNormalBase * copy() const;

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

    virtual std::string toString() const;
    virtual bool simplify();

    void negate();
  };

std::ostream& operator<<(std::ostream& os, const CNormalChoiceLogical& choice);

#endif /* CNormalChoiceLogical_H__ */
