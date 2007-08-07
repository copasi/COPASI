// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalChoice.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/07 16:49:49 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CNormalChoice_H__
#define CNormalChoice_H__

#include "test3/CNormalBase.h"
#include <string>
#include <iostream>

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

    virtual CNormalChoice* copy() const;

    CNormalChoice& operator=(const CNormalChoice& src);

    bool setCondition(const CNormalLogical& cond);
    bool setTrueExpression(const CNormalFraction& branch);
    bool setFalseExpression(const CNormalFraction& branch);

    const CNormalLogical* getCondition() const;
    CNormalLogical* getCondition();

    const CNormalFraction* getTrueExpression() const;
    CNormalFraction* getTrueExpression();

    const CNormalFraction* getFalseExpression() const;
    CNormalFraction* getFalseExpression();

    static bool checkConditionTree(const CNormalBase* branch);
    static bool checkExpressionTree(const CNormalBase* branch);

    virtual std::string toString() const;
    virtual bool simplify();

    friend std::ostream& operator<<(std::ostream& os, const CNormalChoice& choice);
  };

#endif /* CNormalChoice_H__ */
