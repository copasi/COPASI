// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CEvent.cpp,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/24 19:27:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include <stdio.h>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "CModel.h"
#include "CEvent.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiException.h"
#include "utilities/utility.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "function/CExpression.h"

// The default constructor is intentionally not implemented.
// CEventAssignment::CEventAssignment() {}

CEventAssignment::CEventAssignment(const std::string & targetKey,
                                   const CCopasiContainer * pParent) :
    CCopasiContainer(targetKey, pParent, "EventAssignment"),
    mKey(CCopasiRootContainer::getKeyFactory()->add("EventAssignment", this)),
    mTargetKey(targetKey),
    mpExpression(NULL)
{}

CEventAssignment::CEventAssignment(const CEventAssignment & src,
                                   const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(CCopasiRootContainer::getKeyFactory()->add("EventAssignment", this)),
    mTargetKey(src.mTargetKey),
    mpExpression(NULL)
{
  setExpression(src.getExpression());
}

CEventAssignment::~CEventAssignment()
{
  pdelete(mpExpression);
}

bool CEventAssignment::operator < (const CEventAssignment & rhs) const
{
  return mTargetKey < rhs.mTargetKey;
}

const std::string & CEventAssignment::getKey() const
{
  return mKey;
}

const std::string & CEventAssignment::getTargetKey() const
{
  return mTargetKey;
}

bool CEventAssignment::setExpression(const std::string & expression)
{
  if (mpExpression == NULL)
    mpExpression = new CExpression("Expression", this);

  return mpExpression->setInfix(expression);
}

void CEventAssignment::setExpressionPtr(CExpression * pExpression)
{
  pdelete(mpExpression);

  if (pExpression != NULL)
    {
      mpExpression = pExpression;
      mpExpression->setObjectParent(this);
      mpExpression->setObjectName("Expression");

      mpExpression->compile();
    }
}

std::string CEventAssignment::getExpression() const
{
  if (mpExpression == NULL)
    return "";

  mpExpression->updateInfix();

  return mpExpression->getInfix();
}

const CExpression* CEventAssignment::getExpressionPtr() const
{
  return mpExpression;
}

CExpression* CEventAssignment::getExpressionPtr()
{
  return mpExpression;
}

CEvent::CEvent(const std::string & name,
               const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Event"),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Event", this)),
    mDelayCalculation(true),
    mpTriggerExpression(NULL),
    mpDelayExpression(NULL),
    mAssignments()
{
  initObjects();
}

CEvent::CEvent(const CEvent & src,
               const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Event", this)),
    mDelayCalculation(src.mDelayCalculation),
    mpTriggerExpression(src.mpTriggerExpression == NULL ? NULL : new CExpression(*src.mpTriggerExpression)),
    mpDelayExpression(src.mpDelayExpression == NULL ? NULL : new CExpression(*src.mpDelayExpression)),
    mAssignments(src.mAssignments)
{
  initObjects();
}

CEvent::~CEvent()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
  pdelete(mpTriggerExpression);
  pdelete(mpDelayExpression);
}

const std::string & CEvent::getKey() const
{
  return mKey;
}

bool CEvent::compile()
{
  bool success = true;

  // TODO We need build the list of direct dependencies to assure the events are deleted
  // whenever an object used in an expression or assignment is deleted.

  return success;
}

void CEvent::initObjects()
{}

std::ostream & operator<<(std::ostream &os, const CEvent & d)
{
  os << "CEvent:  " << d.getObjectName() << std::endl;
  os << "   SBML id:  " << d.mSBMLId << std::endl;

  os << "----CEvent" << std::endl;

  return os;
}

void CEvent::setSBMLId(const std::string& id)
{
  this->mSBMLId = id;
}

const std::string& CEvent::getSBMLId() const
{
  return this->mSBMLId;
}

std::string CEvent::getObjectDisplayName(bool regular, bool richtext) const
{
  CModel* tmp = dynamic_cast<CModel*>(this->getObjectAncestor("Model"));

  if (tmp)
    return "((" + getObjectName() + "))";

  return CCopasiObject::getObjectDisplayName(regular, richtext);
}

bool CEvent::setTriggerExpression(const std::string & expression)
{
  if (mpTriggerExpression == NULL)
    mpTriggerExpression = new CExpression("TriggerExpression");

  return mpTriggerExpression->setInfix(expression);
}

void CEvent::setTriggerExpressionPtr(CExpression * pExpression)
{
  pdelete(mpTriggerExpression);

  if (pExpression)
    {
      mpTriggerExpression = pExpression;
      mpTriggerExpression->compile();
    }
}

std::string CEvent::getTriggerExpression() const
{
  if (mpTriggerExpression == NULL)
    return "";

  mpTriggerExpression->updateInfix();

  return mpTriggerExpression->getInfix();
}

const CExpression* CEvent::getTriggerExpressionPtr() const
{
  return mpTriggerExpression;
}

CExpression* CEvent::getTriggerExpressionPtr()
{
  return mpTriggerExpression;
}

bool CEvent::setDelayExpression(const std::string & expression)
{
  if (mpDelayExpression == NULL)
    mpDelayExpression = new CExpression("DelayExpression");

  return mpDelayExpression->setInfix(expression);
}

void CEvent::setDelayExpressionPtr(CExpression * pExpression)
{
  pdelete(mpDelayExpression);

  if (pExpression)
    {
      mpDelayExpression = pExpression;
      mpDelayExpression->compile();
    }
}

std::string CEvent::getDelayExpression() const
{
  if (mpDelayExpression == NULL)
    return "";

  mpDelayExpression->updateInfix();

  return mpDelayExpression->getInfix();
}

const CExpression* CEvent::getDelayExpressionPtr() const
{
  return mpDelayExpression;
}

CExpression* CEvent::getDelayExpressionPtr()
{
  return mpDelayExpression;
}

const std::set< CEventAssignment > & CEvent::getAssignments() const
{
  return mAssignments;
}

std::set< CEventAssignment > & CEvent::getAssignments()
{
  return mAssignments;
}

void CEvent::deleteAssignment(const std::string & key)
{
  const CEventAssignment * pAssignment =
    dynamic_cast<const CEventAssignment *>(CCopasiRootContainer::getKeyFactory()->get(key));

  if (pAssignment != NULL)
    {
      mAssignments.erase(pAssignment->getTargetKey());
    }
}
