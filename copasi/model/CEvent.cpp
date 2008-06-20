// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CEvent.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/20 09:51:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
 \file CEvent.h
 \brief Implementation file of class CEvent.
 */

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

CEvent::CEvent(const std::string & name,
               const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Event"),
    mKey(GlobalKeys.add("Event", this)),
    mpTriggerExpression(NULL),
    mpDelayExpression(NULL) /*,
            mpExpressionEA(NULL),
                                        mpModel(NULL)*/
{
  std::cout << "CE::CE" << std::endl;
  CONSTRUCTOR_TRACE;
  initObjects();
}

CEvent::CEvent(const CEvent & src,
               const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Event", this)),
    mpTriggerExpression(NULL),
    mpDelayExpression(NULL) /*,
            mpExpressionEA(NULL)*/
{
  CONSTRUCTOR_TRACE;
  initObjects();
  if (src.mpTriggerExpression != NULL)
    {
      this->mpTriggerExpression = new CExpression(*src.mpTriggerExpression);
      this->mpTriggerExpression->compile();
    }
  if (src.mpDelayExpression != NULL)
    {
      this->mpDelayExpression = new CExpression(*src.mpDelayExpression);
      this->mpDelayExpression->compile();
    }
  /*
    if (src.mpExpressionEA != NULL)
    {
      this->mpExpressionEA = new CExpression(*src.mpExpressionEA);
      this->mpExpressionEA->compile();
    }
  */
  std::vector<std::pair<std::string, CExpression*> >::const_iterator it = src.mAssignsExpression.begin(), endit = src.mAssignsExpression.end();
  CExpression* pTmpExpression = NULL;
  while (it != endit)
    {
      pTmpExpression = new CExpression(*it->second);
      pTmpExpression->compile();
      this->mAssignsExpression.push_back(std::make_pair(it->first, pTmpExpression));
      ++it;
    }
}

CEvent::~CEvent()
{
  GlobalKeys.remove(mKey);
  cleanup();
  DESTRUCTOR_TRACE;
}

void CEvent::cleanup()
{
  if (mpDelayExpression != NULL) delete mpDelayExpression;
  //  if (mpExpressionEA != NULL) delete mpExpressionEA;
  if (mpTriggerExpression != NULL) delete mpTriggerExpression;

  std::vector<std::pair<std::string, CExpression*> >::const_iterator it = this->mAssignsExpression.begin(), endit = this->mAssignsExpression.end();
  while (it != endit)
    {
      delete it->second;
      ++it;
    }
}

const std::string & CEvent::getKey() const {return mKey;}

bool CEvent::compile()    // DOES NOTHING !!!
{
  std::cout << "CE::compile" << std::endl;

  bool success = true;

  return success;
}

void CEvent::initObjects()
{
  std::cout << "CE::initObject" << std::endl;
  mAssignsExpression.resize(0);
  mAssignsExpression.reserve(100);
}

std::set< const CCopasiObject * > CEvent::getDeletedObjects() const
  {
    std::set< const CCopasiObject * > Deleted;

    Deleted.insert(this);

    return Deleted;
  }

std::ostream & operator<<(std::ostream &os, const CEvent & d)
{
  os << "CEvent:  " << d.getObjectName() << std::endl;
  os << "   sbml id:  " << d.mSBMLId << std::endl;

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

bool CEvent::setExpressionTrigger(const std::string &expression)
{
  std::cout << "CE::setExpressionTrigger - expression: " << expression << std::endl;

  if (mpTriggerExpression == NULL)
    mpTriggerExpression = static_cast< CExpression*>(CEvaluationTree::create(CEvaluationTree::Boolean));

  if (!mpTriggerExpression->setInfix(expression)) return false;

  return compile();
}

std::string CEvent::getExpressionTrigger() const
  {
    std::cout << "CE::getExpressionTrigger" << std::endl;

    if (mpTriggerExpression == NULL)
      return "";

    mpTriggerExpression->updateInfix();

    return mpTriggerExpression->getInfix();
  }

bool CEvent::setExpressionDelay(const std::string &expression)
{
  std::cout << "CE::setExpressionDelay - expression: " << expression << std::endl;

  if (mpDelayExpression == NULL)
    mpDelayExpression = new CExpression;

  if (!mpDelayExpression->setInfix(expression)) return false;

  return compile();
}

std::string CEvent::getExpressionDelay() const
  {
    std::cout << "CE::getExpressionDelay" << std::endl;

    if (mpDelayExpression == NULL)
      return "";

    mpDelayExpression->updateInfix();

    return mpDelayExpression->getInfix();
  }

unsigned C_INT32 CEvent::getNumAssignments() const
  {
    return mAssignsExpression.size();
  }

// TODO: would be deleted
/*
void CEvent::setAssignment(std::vector<std::pair<std::string, std::string> > &vector)
{
  std::vector<std::pair<std::string, std::string> >::iterator it = vector.begin();
  for (; it != vector.end(); ++it)
  {
    std::cout << "key = " << it->first << " - expression = " << it->second << std::endl;
    addAssignment(it->first, it->second);
  }
}
 */
bool CEvent::addAssignment(const std::string & key, const std::string & expression)
{
  //  std::cout << "CE::addAssignment(" << key << ", " << expression << ")" << std::endl;

  unsigned C_INT32 Sum;

  Sum = mAssignsExpression.size();

  CExpression* pExpr = new CExpression;

  if (!pExpr->setInfix(expression)) return false;

  CCopasiMessage msg;
  msg = CCopasiMessage::getLastMessage();

  pExpr->compile();
  std::pair<std::string, CExpression*> pair(key, pExpr);

  msg = CCopasiMessage::getLastMessage();

  mAssignsExpression.push_back(pair);

  msg = CCopasiMessage::getLastMessage();

  std::cout << __FILE__ << " L" << __LINE__ << ": mAssigns.size() = " << mAssignsExpression.size() << std::endl;

  msg = CCopasiMessage::getLastMessage();

  if (mAssignsExpression.size() == Sum) // the size is not changed
    return false;

  msg = CCopasiMessage::getLastMessage();

  return true;
}

bool CEvent::updateAssignment(unsigned C_INT32 i, const std::string & key, const std::string & expression)
{
  if (mAssignsExpression[i].first != key)
    mAssignsExpression[i].first = key;

  if (mAssignsExpression[i].second->getInfix() != expression)
    setAssignmentExpression(key, expression);

  return true;
}

bool CEvent::setAssignmentExpression(const std::string & key, const std::string &expression)
{
  std::cout << "CE::setAssignmentExpression - key: " << key << " - expression: " << expression << std::endl;
  /*
    if (mpExpressionEA == NULL)
      mpExpressionEA = new CExpression;

    if (!mpExpressionEA->setInfix(expression)) return false;
  */
  CExpression expr(expression, this);
  if (!expr.setInfix(expression)) return false;

  std::cout << "----------------------------------------------------------" << std::endl;
  std::cout << "current assignment expression: " << std::endl;
  std::cout << "a. expr.getInfix() = " << expr.getInfix() << std::endl;
  std::cout << "b. expr.getDisplayString() = " << expr.getDisplayString() << std::endl;
  std::cout << "c. expr.getDisplay_C_String() = " << expr.getDisplay_C_String() << std::endl;
  std::cout << "d. expr.getDisplay_MMD_String() = " << expr.getDisplay_MMD_String() << std::endl;
  std::cout << "e. expr.getDisplay_XPP_String() = " << expr.getDisplay_XPP_String() << std::endl;

  std::vector<std::pair<std::string, CExpression*> >::iterator it;
  for (it = mAssignsExpression.begin(); it != mAssignsExpression.end(); ++it)
    {
      if (it->first == key)
        it->second = new CExpression(expr);
      it->second->compile();
    }

  return true;
}

unsigned C_INT32 CEvent::getAssignmentIndex(const std::string & key)
{
  std::cout << "CE::getAssignmentExpressionStr - key = " << key << std::endl;

  if (key == "")
    return (unsigned C_INT32) - 1;

  unsigned C_INT32 index = 0;
  std::vector<std::pair<std::string, CExpression*> >::iterator it;
  for (it = mAssignsExpression.begin(); it != mAssignsExpression.end(); ++it, index++)
    {
      if (it->first == key)
        return index;
    }

  return (unsigned C_INT32) - 1;
}

const std::string CEvent::getAssignmentObjectKey(unsigned C_INT32 i) const
  {
    std::cout << "CE::getAssignmentObjectKey - index: " << i << std::endl;
    std::cout << "-> key: " << mAssignsExpression[i].first << std::endl;

    return mAssignsExpression[i].first;
  }

void CEvent::showAssignments()
{
  std::cout << "---------------------------------------------" << std::endl;
  std::cout << "CE::showAssignments - getNumAssignments() = " << getNumAssignments() << std::endl;
  std::cout << "---------------------------------------------" << std::endl;
  unsigned C_INT32 j;
  for (j = 0; j < getNumAssignments(); j++)
    std::cout << "the " << j << "-th assignment : "
    << "name = " << mAssignsExpression[j].first << " - expression = " << mAssignsExpression[j].second->getInfix() << std::endl;
  std::cout << "---------------------------------------------" << std::endl;
}

std::string CEvent::getAssignmentExpressionStr(const std::string & key)
{
  std::cout << "CE::getAssignmentExpressionStr - key = " << key << std::endl;

  std::vector<std::pair<std::string, CExpression*> >::iterator it;
  for (it = mAssignsExpression.begin(); it != mAssignsExpression.end(); ++it)
    {
      if (it->first == key)
        {
          CExpression* pExpression = it->second;
          pExpression->updateInfix();
          std::cout << "expression of key = " << key << " = " << pExpression->getInfix() << std::endl;
          return pExpression->getInfix();
        }
    }

  return "";
}

std::string CEvent::getAssignmentExpressionStr(unsigned C_INT32 i) const
  {
    std::cout << "CE::getAssignmentExpressionStr - index = " << i << std::endl;

    std::cout << "the " << i << "-th assignment expression A = " << mAssignsExpression[i].second->getInfix() << std::endl;

    CExpression* pExpr = mAssignsExpression[i].second;
    std::cout << "the " << i << "-th assignment expression B = " << pExpr->getInfix() << std::endl;

    //  return mAssigns[i].second.getInfix(); // 2*4 * 5
    return pExpr->getInfix();     // 2*4*5
  }

void CEvent::clearAssignment()
{
  std::cout << "CE::clearAssignment ... START ... mAssigns.size() = " << mAssignsExpression.size() << std::endl;
  if (!mAssignsExpression.empty())
    mAssignsExpression.clear();
}

bool CEvent::deleteAssignment(unsigned C_INT32 i)
{
  std::cout << "CE::deleteAssignment - index = " << i << std::endl;

  std::vector<std::pair<std::string, CExpression*> >::iterator itA = mAssignsExpression.begin();
  itA += i;

  std::cout << "(" << itA->first << ", " << itA->second->getInfix() << ") will be deleted from event." << std::endl;
  /*
    std::vector<std::pair<std::string, CExpression *> >::const_iterator it = mAssigns.begin();
    std::vector<std::pair<std::string, CExpression *> >::const_iterator end = mAssigns.end();
    for (; it!=end; ++it)
  */
  /*  std::vector<std::pair<std::string, CExpression> >::iterator it;
    for (it = mAssigns.begin(); it != mAssigns.end(); ++it)
    {
      if (it->first == key)
     it->second = expr;
    }
  */
  mAssignsExpression.erase(itA);

  // update the key of EventAssignment
  return compile();
}

//const std::vector<std::pair<std::string, CExpression> > CEvent::getAssignmentExpressionVector() const
std::vector<std::pair<std::string, CExpression*> > CEvent::getAssignmentExpressionVector()
//std::vector<std::pair<std::string, CExpression> > * CEvent::getAssignmentExpressionVector()
{
  if (!mAssignsExpression.size()) // empty
    {
      std::cout << "CE ERROR on L" << __LINE__ << ": mAssigns is empty" << std::endl;
      return std::vector<std::pair<std::string, CExpression*> > ();
    }
  return mAssignsExpression;
}

// TODO: would be deleted
/*
void CEvent::setAssignmentExpressionVector(std::vector<std::pair<std::string, CExpression> > &vector)
{
  mAssigns = vector;
}
 */
const CExpression* CEvent::getTriggerExpressionPtr() const
  {
    return this->mpTriggerExpression;
  }

CExpression* CEvent::getTriggerExpressionPtr()
{
  return this->mpTriggerExpression;
}

void CEvent::setTriggerExpressionPtr(CExpression* pExpression)
{
  if ((pExpression->getType()) != CEvaluationTree::Boolean) return;
  if (this->mpTriggerExpression != NULL) delete this->mpTriggerExpression;
  this->mpTriggerExpression = pExpression;
  this->mpTriggerExpression->compile();
}

void CEvent::setAssignmentExpressionPtr(const std::string & key, CExpression* pExpression)
{
  pExpression->compile();
  this->mAssignsExpression.push_back(std::make_pair(key, pExpression));
}

const CExpression* CEvent::getAssignmentExpressionPtr(unsigned C_INT32 i) const
  {
    CExpression* pResult = NULL;
    if (i < this->mAssignsExpression.size())
      pResult = this->mAssignsExpression[i].second;

    return pResult;
  }

CExpression* CEvent::getAssignmentExpressionPtr(unsigned C_INT32 i)
{
  CExpression* pResult = NULL;
  if (i < this->mAssignsExpression.size())
    pResult = this->mAssignsExpression[i].second;
  return pResult;
}

CExpression* CEvent::getDelayExpressionPtr()
{
  return this->mpDelayExpression;
}

const CExpression* CEvent::getDelayExpressionPtr() const
  {
    return this->mpDelayExpression;
  }

void CEvent::setDelayExpressionPtr(CExpression* pExpression)
{
  if (this->mpDelayExpression != NULL) delete this->mpDelayExpression;
  this->mpDelayExpression = pExpression;
  this->mpDelayExpression->compile();
}
