// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalChoiceLogical.cpp,v $
//   $Revision: 1.4 $
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

#include "CNormalChoiceLogical.h"
#include "CNormalLogical.h"
#include "CNormalItem.h"
#include "CNormalFraction.h"

CNormalChoiceLogical::CNormalChoiceLogical(): CNormalBase(), mpCondition(NULL), mpTrue(NULL), mpFalse(NULL)
{}

CNormalChoiceLogical::CNormalChoiceLogical(const CNormalChoiceLogical& src):
    CNormalBase(src),
    mpCondition(NULL),
    mpTrue(NULL),
    mpFalse(NULL)
{*this = src;}

CNormalChoiceLogical::~CNormalChoiceLogical()
{
  pdelete(mpCondition);
  pdelete(mpTrue);
  pdelete(mpFalse);
}

CNormalChoiceLogical& CNormalChoiceLogical::operator=(const CNormalChoiceLogical& src)
{
  pdelete(mpCondition);
  pdelete(mpTrue);
  pdelete(mpFalse);

  if (src.mpCondition != NULL)
    mpCondition = new CNormalLogical(*src.mpCondition);
  if (src.mpTrue != NULL)
    mpTrue = new CNormalLogical(*src.mpTrue);
  if (src.mpFalse != NULL)
    mpFalse = new CNormalLogical(*src.mpFalse);

  return *this;
}

bool CNormalChoiceLogical::setCondition(const CNormalLogical& cond)
{
  bool result = true;
  pdelete(mpCondition);

  // check the cond if it is OK
  result = checkConditionTree(cond);
  if (result == true)
    mpCondition = new CNormalLogical(cond);
  return result;
}

bool CNormalChoiceLogical::setTrueExpression(const CNormalLogical& branch)
{
  bool result = true;
  pdelete(mpTrue);

  // check the branch if it is OK
  result = checkConditionTree(branch);
  mpTrue = new CNormalLogical(branch);
  return result;
}

bool CNormalChoiceLogical::setFalseExpression(const CNormalLogical& branch)
{
  bool result = true;
  pdelete(mpFalse);

  // check the branch if it is OK
  result = checkConditionTree(branch);
  mpFalse = new CNormalLogical(branch);
  return result;
}

const CNormalLogical& CNormalChoiceLogical::getCondition() const
  {
    return *mpCondition;
  }

CNormalLogical& CNormalChoiceLogical::getCondition()
{
  return *mpCondition;
}

const CNormalLogical& CNormalChoiceLogical::getTrueExpression() const
  {
    return *mpTrue;
  }

CNormalLogical& CNormalChoiceLogical::getTrueExpression()
{
  return *mpTrue;
}

const CNormalLogical& CNormalChoiceLogical::getFalseExpression() const
  {
    return *mpFalse;
  }

CNormalLogical& CNormalChoiceLogical::getFalseExpression()
{
  return *mpFalse;
}

CNormalBase * CNormalChoiceLogical::copy() const
  {
    return new CNormalChoiceLogical(*this);
  }

bool CNormalChoiceLogical::checkConditionTree(const CNormalBase& branch)
{
  bool result = true;
  const CNormalChoiceLogical* pChoice = dynamic_cast<const CNormalChoiceLogical*>(&branch);
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

std::string CNormalChoiceLogical::toString() const
  {
    std::ostringstream os;
    os << "if(" << this->mpCondition->toString() << ") then (" << this->mpTrue->toString() << ") else (" << this->mpFalse->toString() << ")";
    return os.str();
  }

std::ostream& operator<<(std::ostream& os, const CNormalChoiceLogical& choice)
{
  os << choice.toString();
  return os;
}

bool CNormalChoiceLogical::simplify()
{
  bool result = true;
  if (this->mpCondition != NULL) result &= this->mpCondition->simplify();
  if (this->mpTrue != NULL) result &= this->mpTrue->simplify();
  if (this->mpFalse != NULL) result &= this->mpFalse->simplify();
  return result;
}

void CNormalChoiceLogical::negate()
{
  CNormalLogical* pTmp = this->mpTrue;
  this->mpTrue = this->mpFalse;
  this->mpFalse = pTmp;
}

bool CNormalChoiceLogical::operator==(const CNormalChoiceLogical& rhs) const
  {
    return ((*this->mpCondition) == (*rhs.mpCondition) && (*this->mpTrue == *rhs.mpTrue) && (*this->mpFalse == *rhs.mpFalse));
  }

bool CNormalChoiceLogical::operator<(const CNormalChoiceLogical& rhs) const
  {
    bool result = true;
    if ((*rhs.mpCondition) < (*this->mpCondition))
      {
        result = false;
      }
    else if ((*this->mpCondition) == (*rhs.mpCondition))
      {
        if ((*rhs.mpTrue) < (*this->mpTrue))
          {
            result = false;
          }
        else if ((*rhs.mpTrue) == (*this->mpTrue))
          {
            if (!((*this->mpFalse) < (*rhs.mpFalse)))
              {
                result = false;
              }
          }
      }
    return result;
  }
