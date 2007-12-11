// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalChoice.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/12/11 20:55:55 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <sstream>

#include "CNormalChoice.h"
#include "CNormalLogical.h"
#include "CNormalItem.h"
#include "CNormalFraction.h"

CNormalChoice::CNormalChoice(): CNormalBase(), mpCondition(NULL), mpTrue(NULL), mpFalse(NULL)
{}

CNormalChoice::CNormalChoice(const CNormalChoice& src):
    CNormalBase(src),
    mpCondition(NULL),
    mpTrue(NULL),
    mpFalse(NULL)
{*this = src;}

CNormalChoice::~CNormalChoice()
{
  pdelete(mpCondition);
  pdelete(mpTrue);
  pdelete(mpFalse);
}

CNormalChoice& CNormalChoice::operator=(const CNormalChoice& src)
{
  pdelete(mpCondition);
  pdelete(mpTrue);
  pdelete(mpFalse);

  if (src.mpCondition != NULL)
    mpCondition = new CNormalLogical(*src.mpCondition);
  if (src.mpCondition != NULL)
    mpTrue = new CNormalFraction(*src.mpTrue);
  if (src.mpCondition != NULL)
    mpFalse = new CNormalFraction(*src.mpFalse);

  return *this;
}

bool CNormalChoice::setCondition(const CNormalLogical& cond)
{
  bool result = true;

  pdelete(mpCondition);

  // check the cond if it is OK
  result = checkConditionTree(cond);
  if (result == true)
    mpCondition = new CNormalLogical(cond);

  return result;
}

bool CNormalChoice::setTrueExpression(const CNormalFraction& branch)
{
  bool result = true;

  pdelete(mpTrue);

  // check the branch if it is OK
  result = checkExpressionTree(branch);

  mpTrue = new CNormalFraction(branch);
  return result;
}

bool CNormalChoice::setFalseExpression(const CNormalFraction& branch)
{
  bool result = true;
  pdelete(mpFalse);

  // check the branch if it is OK
  result = checkExpressionTree(branch);
  mpFalse = new CNormalFraction(branch);
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

CNormalBase * CNormalChoice::copy() const
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

bool CNormalChoice::operator==(const CNormalChoice& rhs) const
  {
    bool result = true;
    if (!(((*this->mpCondition) == (*rhs.mpCondition)) && ((*this->mpTrue) == (*rhs.mpTrue)) && ((*this->mpFalse) == (*rhs.mpFalse))))
      {
        result = false;
      }
    return result;
  }

bool CNormalChoice::operator<(const CNormalChoice& rhs) const
  {
    bool result = false;
    if ((*this->mpCondition) < (*rhs.mpCondition))
      {
        result = true;
      }
    else if ((*this->mpCondition) == (*rhs.mpCondition))
      {
        if ((*this->mpTrue) < (*rhs.mpTrue))
          {
            result = true;
          }
        else if ((*this->mpTrue) == (*rhs.mpTrue))
          {
            if ((*this->mpFalse) < (*rhs.mpFalse))
              {
                result = true;
              }
          }
      }
    return result;
  }
