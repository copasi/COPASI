// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalChoice.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/10 13:42:20 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CNormalChoice.h"
#include "CNormalLogical.h"
#include "CNormalItem.h"
#include "CNormalFraction.h"
#include <sstream>

CNormalChoice::CNormalChoice(): CNormalBase(), mpCondition(NULL), mpTrue(NULL), mpFalse(NULL)
{}

CNormalChoice::CNormalChoice(const CNormalChoice& src): CNormalBase(src), mpCondition(src.mpCondition->copy()), mpTrue(src.mpTrue->copy()), mpFalse(src.mpFalse->copy())
{}

CNormalChoice::~CNormalChoice()
{
  if (this->mpCondition != NULL) delete this->mpCondition;
  if (this->mpTrue != NULL) delete this->mpTrue;
  if (this->mpFalse != NULL) delete this->mpFalse;
}

CNormalChoice& CNormalChoice::operator=(const CNormalChoice& src)
{
  if (this->mpCondition != NULL) delete this->mpCondition;
  if (this->mpTrue != NULL) delete this->mpTrue;
  if (this->mpFalse != NULL) delete this->mpFalse;
  this->mpCondition = src.mpCondition->copy();
  this->mpTrue = src.mpTrue->copy();
  this->mpFalse = src.mpFalse->copy();
  return *this;
}

bool CNormalChoice::setCondition(const CNormalLogical& cond)
{
  bool result = true;
  if (this->mpCondition != NULL) delete this->mpCondition;
  // check the cond if it is OK
  result = checkConditionTree(cond);
  if (result == true)
    {
      this->mpCondition = cond.copy();
    }
  return result;
}

bool CNormalChoice::setTrueExpression(const CNormalFraction& branch)
{
  bool result = true;
  if (this->mpTrue != NULL) delete this->mpTrue;
  // check the branch if it is OK
  result = checkExpressionTree(branch);
  this->mpTrue = branch.copy();
  return result;
}

bool CNormalChoice::setFalseExpression(const CNormalFraction& branch)
{
  bool result = true;
  if (this->mpFalse != NULL) delete this->mpFalse;
  // check the branch if it is OK
  result = checkExpressionTree(branch);
  this->mpFalse = branch.copy();
  return result;
}

const CNormalLogical& CNormalChoice::getCondition() const
  {
    return *mpCondition;
  }

CNormalLogical& CNormalChoice::getCondition()
{
  return *mpCondition;
}

const CNormalFraction& CNormalChoice::getTrueExpression() const
  {
    return *mpTrue;
  }

CNormalFraction& CNormalChoice::getTrueExpression()
{
  return *mpTrue;
}

const CNormalFraction& CNormalChoice::getFalseExpression() const
  {
    return *mpFalse;
  }

CNormalFraction& CNormalChoice::getFalseExpression()
{
  return *mpFalse;
}

CNormalChoice* CNormalChoice::copy() const
  {
    return new CNormalChoice(*this);
  }

bool CNormalChoice::checkConditionTree(const CNormalBase& branch)
{
  bool result = true;
  const CNormalChoice* pChoice = dynamic_cast<const CNormalChoice*>(&branch);
  if (pChoice != NULL)
    {
      // check the condition and the two branches
      result = checkConditionTree(pChoice->getCondition());
      if (result == true) result = checkConditionTree(pChoice->getTrueExpression());
      if (result == true) result = checkConditionTree(pChoice->getFalseExpression());
    }
  else
    {
      const CNormalLogical* pLogical = dynamic_cast<const CNormalLogical*>(&branch);
      if (pLogical == NULL)
        {
          const CNormalItem* pItem = dynamic_cast<const CNormalItem*>(&branch);
          if (pItem == NULL)
            {
              result = false;
            }
          else
            {
              result = pItem->getType() == CNormalItem::CONSTANT;
              if (result == true)
                {
                  std::string name = pItem->getName();
                  if (name != "true" && name != "TRUE" && name != "false" && name != "FALSE")
                    {
                      result = false;
                    }
                }
            }
        }
    }
  return result;
}

bool CNormalChoice::checkExpressionTree(const CNormalBase& branch)
{
  bool result = true;
  const CNormalChoice* pChoice = dynamic_cast<const CNormalChoice*>(&branch);
  if (pChoice != NULL)
    {
      result = checkConditionTree(pChoice->getCondition());
      if (result == true) result = checkExpressionTree(pChoice->getTrueExpression());
      if (result == true) result = checkExpressionTree(pChoice->getFalseExpression());
    }
  else
    {
      const CNormalFraction* pFraction = dynamic_cast<const CNormalFraction*>(&branch);
      if (pFraction == NULL)
        {
          result = false;
        }
    }
  return result;
}

std::string CNormalChoice::toString() const
  {
    std::ostringstream os;
    os << "if(" << this->mpCondition->toString() << ") then (" << this->mpTrue->toString() << ") else (" << this->mpFalse->toString() << ")";
    return os.str();
  }

std::ostream& operator<<(std::ostream& os, const CNormalChoice& choice)
{
  os << choice.toString();
  return os;
}

bool CNormalChoice::simplify()
{
  bool result = true;
  if (this->mpCondition != NULL) result &= this->mpCondition->simplify();
  if (this->mpTrue != NULL) result &= this->mpTrue->simplify();
  if (this->mpFalse != NULL) result &= this->mpFalse->simplify();
  return result;
}
