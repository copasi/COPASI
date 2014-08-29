// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "report/CCopasiRootContainer.h"
#include "function/CExpression.h"
#include "MIRIAM/CRDFUtilities.h"

// The default constructor is intentionally not implemented.
// CEventAssignment::CEventAssignment() {}

CEventAssignment::CEventAssignment(const std::string & targetKey,
                                   const CCopasiContainer * pParent) :
  CCopasiContainer(targetKey, pParent, "EventAssignment"),
  mKey(CCopasiRootContainer::getKeyFactory()->add("EventAssignment", this)),
  mpModel(static_cast<CModel *>(getObjectAncestor("Model"))),
  mpTarget(NULL),
  mpExpression(NULL)
{
  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }
}

CEventAssignment::CEventAssignment(const CEventAssignment & src,
                                   const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  mKey(CCopasiRootContainer::getKeyFactory()->add("EventAssignment", this)),
  mpModel(static_cast<CModel *>(getObjectAncestor("Model"))),
  mpTarget(src.mpTarget),
  mpExpression(NULL)
{
  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  setExpression(src.getExpression());
}

CEventAssignment::~CEventAssignment()
{
  pdelete(mpExpression);

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }
}

bool CEventAssignment::setObjectParent(const CCopasiContainer * pParent)
{
  if (pParent != getObjectParent() &&
      mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  bool success = CCopasiContainer::setObjectParent(pParent);
  mpModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  return success;
}

bool CEventAssignment::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  clearDirectDependencies();

  bool success = true;

  mpTarget = NULL;

  CModelEntity * pEntity =
    dynamic_cast< CModelEntity * >(CCopasiRootContainer::getKeyFactory()->get(getObjectName()));

  // The entity type must not be an ASSIGNMENT
  if (pEntity != NULL &&
      pEntity->getStatus() != CModelEntity::ASSIGNMENT)
    {
      // We need use the virtual method getValueObject to retrieve the
      // target value from the model entity
      mpTarget = pEntity->getValueObject();
    }
  else if (pEntity != NULL &&
           pEntity->getStatus() == CModelEntity::ASSIGNMENT)
    {
      CCopasiMessage(CCopasiMessage::WARNING, "Invalid EventAssignment for '%s': an Assignment Rule already exists", pEntity->getObjectName().c_str());
    }
  else if (pEntity == NULL)
    {
      CCopasiMessage(CCopasiMessage::WARNING, "Invalid EventAssignment for '%s': object does not exist.", getObjectName().c_str());
    }

  if (mpTarget == NULL)
    {
      success = false;
    }

  if (mpExpression != NULL)
    {
      success &= mpExpression->compile(listOfContainer);
      setDirectDependencies(mpExpression->getDirectDependencies());
    }
  else
    {
      success = false;
    }

  return success;
}

const std::string & CEventAssignment::getKey() const
{
  return mKey;
}

const CCopasiObject * CEventAssignment::getTargetObject() const
{
  return mpTarget;
}

bool CEventAssignment::setTargetKey(const std::string & targetKey)
{
  if (targetKey != getTargetKey() &&
      mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  return setObjectName(targetKey);
}

const std::string & CEventAssignment::getTargetKey() const
{
  return getObjectName();
}

bool CEventAssignment::setExpression(const std::string & expression)
{
  if (mpExpression == NULL)
    mpExpression = new CExpression("Expression", this);

  if (mpExpression->getInfix() != expression &&
      mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  return mpExpression->setInfix(expression);
}

bool CEventAssignment::setExpressionPtr(CExpression * pExpression)
{
  if (pExpression == mpExpression) return true;

  if (pExpression == mpExpression) return true;

  if (pExpression == NULL) return false;

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  CExpression * pOld = mpExpression;
  mpExpression = pExpression;

  mpExpression->setObjectName("Expression");
  add(mpExpression, true);
  std::vector< CCopasiContainer * > listOfContainer;
  listOfContainer.push_back(mpModel);

  if (mpExpression->compile(listOfContainer))
    {
      pdelete(pOld);
      return true;
    }

  // If compile fails we do not take ownership
  // and we remove the object from the container
  remove(mpExpression);
  mpExpression->setObjectParent(NULL);
  mpExpression = pOld;
  return false;
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

//****************************************************************

CEvent::CEvent(const std::string & name,
               const CCopasiContainer * pParent):
  CCopasiContainer(name, pParent, "Event"),
  CAnnotation(),
  mpModel(static_cast<CModel *>(getObjectAncestor("Model"))),
  mAssignments("ListOfAssignments", this),
  mDelayAssignment(true),
  mFireAtInitialTime(false),
  mPersistentTrigger(false),
  mpTriggerExpression(NULL),
  mpDelayExpression(NULL),
  mpPriorityExpression(NULL),
  mType(Assignment)
{
  mKey = (CCopasiRootContainer::getKeyFactory()->add(getObjectType(), this));

  initObjects();
}

CEvent::CEvent(const CEvent & src,
               const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  CAnnotation(src),
  mpModel(static_cast<CModel *>(getObjectAncestor("Model"))),
  mAssignments(src.mAssignments, this),
  mDelayAssignment(src.mDelayAssignment),
  mFireAtInitialTime(src.mFireAtInitialTime),
  mPersistentTrigger(src.mPersistentTrigger),
  mpTriggerExpression(src.mpTriggerExpression != NULL ? new CExpression(*src.mpTriggerExpression, this) : NULL),
  mpDelayExpression(src.mpDelayExpression != NULL ? new CExpression(*src.mpDelayExpression, this) : NULL),
  mpPriorityExpression(src.mpPriorityExpression != NULL ? new CExpression(*src.mpPriorityExpression, this) : NULL),
  mType(src.mType)
{
  mKey = (CCopasiRootContainer::getKeyFactory()->add(getObjectType(), this));

  initObjects();

  setMiriamAnnotation(src.getMiriamAnnotation(), mKey, src.mKey);
}

CEvent::~CEvent()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
  pdelete(mpTriggerExpression);
  pdelete(mpDelayExpression);
  pdelete(mpPriorityExpression);
}

// virtual
const std::string & CEvent::getKey() const
{
  return CAnnotation::getKey();
}

// virtual
bool CEvent::mustBeDeleted(const CCopasiObject::DataObjectSet & deletedObjects) const
{
  bool MustBeDeleted = false;

  CCopasiObject::DataObjectSet ChildObjects;

  if (mpTriggerExpression != NULL)
    {
      ChildObjects.insert(mpTriggerExpression);
    }

  if (mpDelayExpression != NULL)
    {
      ChildObjects.insert(mpDelayExpression);
    }

  if (mpPriorityExpression != NULL)
    {
      ChildObjects.insert(mpPriorityExpression);
    }

  // We need to add all assignment targets and expressions
  CCopasiVector< CEventAssignment >::const_iterator itAssignment = mAssignments.begin();
  CCopasiVector< CEventAssignment >::const_iterator endAssignment = mAssignments.end();

  for (; itAssignment != endAssignment; ++itAssignment)
    {
      if ((*itAssignment)->getTargetObject() != NULL)
        {
          ChildObjects.insert((*itAssignment)->getTargetObject());
        }

      if ((*itAssignment)->getExpressionPtr() != NULL)
        {
          ChildObjects.insert((*itAssignment)->getExpressionPtr());
        }
    }

  DataObjectSet::const_iterator it = ChildObjects.begin();
  DataObjectSet::const_iterator end = ChildObjects.end();

  for (; it != end; ++it)
    {
      if ((*it)->mustBeDeleted(deletedObjects))
        {
          MustBeDeleted = true;
          break;
        }
    }

  return MustBeDeleted;
}

bool CEvent::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;

  // Clear the old direct dependencies.
  clearDirectDependencies();

  // Compile the trigger expression
  if (mpTriggerExpression != NULL)
    {
      success &= mpTriggerExpression->compile(listOfContainer);
      addDirectDependency(mpTriggerExpression);
    }

  // Compile the delay expression
  if (mpDelayExpression != NULL)
    {
      success &= mpDelayExpression->compile(listOfContainer);
      addDirectDependency(mpDelayExpression);
    }

  // Compile the assignments
  CCopasiVectorN< CEventAssignment >::iterator itAssignment = mAssignments.begin();
  CCopasiVectorN< CEventAssignment >::iterator endAssignment = mAssignments.end();

  for (; itAssignment != endAssignment; ++itAssignment)
    {
      success &= (*itAssignment)->compile(listOfContainer);
      addDirectDependency(*itAssignment);
    }

  return success;
}

void CEvent::initObjects()
{
  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }
}

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

void CEvent::setDelayAssignment(const bool & delayAssignment)
{
  if (mDelayAssignment != delayAssignment &&
      mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  mDelayAssignment = delayAssignment;
}

const bool & CEvent::getDelayAssignment() const
{
  return mDelayAssignment;
}

void CEvent::setFireAtInitialTime(const bool & fireAtInitialTime)
{
  if (mFireAtInitialTime != fireAtInitialTime)
    {
      mFireAtInitialTime = fireAtInitialTime;

      if (mpModel != NULL)
        {
          mpModel->setCompileFlag(true);
        }
    }
}

const bool & CEvent::getFireAtInitialTime() const
{
  return mFireAtInitialTime;
}

void CEvent::setPersistentTrigger(const bool & persistentTrigger)
{
  if (mPersistentTrigger != persistentTrigger)
    {
      mPersistentTrigger = persistentTrigger;

      if (mpModel != NULL)
        {
          mpModel->setCompileFlag(true);
        }
    }
}

const bool & CEvent::getPersistentTrigger() const
{
  return mPersistentTrigger;
}

bool CEvent::setObjectParent(const CCopasiContainer * pParent)
{
  if (pParent != getObjectParent() &&
      mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  bool success = CCopasiContainer::setObjectParent(pParent);

  mpModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  return success;
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
    {
      mpTriggerExpression = new CExpression("TriggerExpression", this);
      mpTriggerExpression->setIsBoolean(true);
    }

  if (mpTriggerExpression->getInfix() != expression &&
      mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  return mpTriggerExpression->setInfix(expression);
}

bool CEvent::setTriggerExpressionPtr(CExpression * pExpression)
{
  if (pExpression == mpTriggerExpression) return true;

  if (pExpression == NULL) return false;

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  CExpression * pOld = mpTriggerExpression;
  mpTriggerExpression = pExpression;

  mpTriggerExpression->setObjectName("TriggerExpression");
  add(mpTriggerExpression, true);
  std::vector< CCopasiContainer * > listOfContainer;
  listOfContainer.push_back(mpModel);

  if (mpTriggerExpression->compile(listOfContainer))
    {
      pdelete(pOld);
      return true;
    }

  // If compile fails we do not take ownership
  // and we remove the object from the container
  remove(mpTriggerExpression);
  mpTriggerExpression->setObjectParent(NULL);
  mpTriggerExpression = pOld;
  return false;
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
    mpDelayExpression = new CExpression("DelayExpression", this);

  if (mpDelayExpression->getInfix() != expression &&
      mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  return mpDelayExpression->setInfix(expression);
}

bool CEvent::setDelayExpressionPtr(CExpression * pExpression)
{
  if (pExpression == mpDelayExpression) return true;

  if (pExpression == NULL) return false;

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  CExpression * pOld = mpDelayExpression;
  mpDelayExpression = pExpression;

  mpDelayExpression->setObjectName("DelayExpression");
  add(mpDelayExpression, true);
  std::vector< CCopasiContainer * > listOfContainer;
  listOfContainer.push_back(mpModel);

  if (mpDelayExpression->compile(listOfContainer))
    {
      pdelete(pOld);
      return true;
    }

  // If compile fails we do not take ownership
  // and we remove the object from the container
  remove(mpDelayExpression);
  mpDelayExpression->setObjectParent(NULL);
  mpDelayExpression = pOld;
  return false;
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

bool CEvent::setPriorityExpression(const std::string & expression)
{
  if (mpPriorityExpression == NULL)
    mpPriorityExpression = new CExpression("PriorityExpression", this);

  if (mpPriorityExpression->getInfix() != expression &&
      mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  return mpPriorityExpression->setInfix(expression);
}

bool CEvent::setPriorityExpressionPtr(CExpression* pExpression)
{
  if (pExpression == mpPriorityExpression) return true;

  if (pExpression == NULL) return false;

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  CExpression * pOld = mpPriorityExpression;
  mpPriorityExpression = pExpression;

  mpPriorityExpression->setObjectName("PriorityExpression");
  add(mpPriorityExpression, true);
  std::vector< CCopasiContainer * > listOfContainer;
  listOfContainer.push_back(mpModel);

  if (mpPriorityExpression->compile(listOfContainer))
    {
      pdelete(pOld);
      return true;
    }

  // If compile fails we do not take ownership
  // and we remove the object from the container
  remove(mpPriorityExpression);
  mpPriorityExpression->setObjectParent(NULL);
  mpPriorityExpression = pOld;
  return false;
}

std::string CEvent::getPriorityExpression() const
{
  if (mpPriorityExpression == NULL)
    return "";

  mpPriorityExpression->updateInfix();

  return mpPriorityExpression->getInfix();
}

CExpression* CEvent::getPriorityExpressionPtr()
{
  return mpPriorityExpression;
}

const CExpression* CEvent::getPriorityExpressionPtr() const
{
  return mpPriorityExpression;
}

const CCopasiVectorN< CEventAssignment > & CEvent::getAssignments() const
{
  return mAssignments;
}

CCopasiVectorN< CEventAssignment > & CEvent::getAssignments()
{
  return mAssignments;
}

void CEvent::deleteAssignment(const std::string & key)
{
  CEventAssignment * pAssignment =
    dynamic_cast<CEventAssignment *>(CCopasiRootContainer::getKeyFactory()->get(key));

  if (pAssignment != NULL)
    {
      mAssignments.CCopasiVector< CEventAssignment >::remove(pAssignment);
    }
}

const CEvent::Type & CEvent::getType() const
{
  return mType;
}

void CEvent::setType(const CEvent::Type & type)
{
  mType = type;
}
