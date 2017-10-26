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

#include "copasi.h"

#include <stdio.h>

#include "CopasiDataModel/CDataModel.h"
#include "CModel.h"
#include "CEvent.h"

#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiException.h"
#include "utilities/utility.h"
#include "copasi/core/CDataObjectReference.h"
#include "report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"
#include "function/CExpression.h"
#include "MIRIAM/CRDFUtilities.h"

// static
CEventAssignment * CEventAssignment::fromData(const CData & data)
{
  return new CEventAssignment(data.getProperty(CData::OBJECT_NAME).toString(),
                              NO_PARENT);
}

// virtual
CData CEventAssignment::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CEventAssignment::applyData(const CData & data, CUndoData::ChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

// The default constructor is intentionally not implemented.
// CEventAssignment::CEventAssignment() {}
CEventAssignment::CEventAssignment(const std::string & targetKey,
                                   const CDataContainer * pParent) :
  CDataContainer(targetKey, pParent, "EventAssignment"),
  mKey(CRootContainer::getKeyFactory()->add("EventAssignment", this)),
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
                                   const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mKey(CRootContainer::getKeyFactory()->add("EventAssignment", this)),
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

bool CEventAssignment::setObjectParent(const CDataContainer * pParent)
{
  if (pParent != getObjectParent() &&
      mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  bool success = CDataContainer::setObjectParent(pParent);
  mpModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  return success;
}

CIssue CEventAssignment::compile(CObjectInterface::ContainerList listOfContainer)
{
  mPrerequisits.clear();

  mValidity.clear();
  CIssue firstWorstIssue;

  mpTarget = NULL;

  CModelEntity * pEntity =
    dynamic_cast< CModelEntity * >(CRootContainer::getKeyFactory()->get(getObjectName()));

  // The entity type must not be an ASSIGNMENT
  if (pEntity != NULL &&
      pEntity->getStatus() != CModelEntity::Status::ASSIGNMENT)
    {
      mPrerequisits.insert(pEntity);

      // We need use the virtual method getValueObject to retrieve the
      // target value from the model entity
      mpTarget = pEntity->getValueObject();
    }
  else if (pEntity != NULL &&
           pEntity->getStatus() == CModelEntity::Status::ASSIGNMENT)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Invalid EventAssignment for '%s': an Assignment Rule already exists", pEntity->getObjectName().c_str());
      mValidity.add(CIssue(CIssue::eSeverity::Error, CIssue::eKind::EventAlreadyHasAssignment));
      firstWorstIssue &= mValidity.getFirstWorstIssue();
    }
  else if (pEntity == NULL)
    {
      CCopasiMessage(CCopasiMessage::WARNING, "Invalid EventAssignment for '%s': object does not exist.", getObjectName().c_str());
      mValidity.add(CIssue(CIssue::eSeverity::Warning, CIssue::eKind::ObjectNotFound));
      firstWorstIssue &= mValidity.getFirstWorstIssue();
    }

  if (mpExpression != NULL)
    {
      firstWorstIssue &= mpExpression->compile(listOfContainer);
    }
  else
    {
      mValidity.add(CIssue(CIssue::eSeverity::Warning, CIssue::eKind::CExpressionNotFound));
      firstWorstIssue &= mValidity.getFirstWorstIssue();
    }

  return firstWorstIssue;
}

const std::string & CEventAssignment::getKey() const
{
  return mKey;
}

const CDataObject * CEventAssignment::getTargetObject() const
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

  if (pExpression == NULL) return false;

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  CExpression * pOld = mpExpression;
  mpExpression = pExpression;

  mpExpression->setObjectName("Expression");
  add(mpExpression, true);
  CObjectInterface::ContainerList listOfContainer;
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
  if (mpExpression != NULL) mpExpression->updateInfix();

  return mpExpression;
}

CExpression* CEventAssignment::getExpressionPtr()
{
  if (mpExpression != NULL) mpExpression->updateInfix();

  return mpExpression;
}

//****************************************************************
// static
CEvent * CEvent::fromData(const CData & data)
{
  return new CEvent(data.getProperty(CData::OBJECT_NAME).toString(),
                    NO_PARENT);
}

// virtual
CData CEvent::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CEvent::applyData(const CData & data, CUndoData::ChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CEvent::CEvent(const std::string & name,
               const CDataContainer * pParent):
  CDataContainer(name, pParent, "Event"),
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
  mKey = (CRootContainer::getKeyFactory()->add(getObjectType(), this));

  initObjects();
}

CEvent::CEvent(const CEvent & src,
               const CDataContainer * pParent):
  CDataContainer(src, pParent),
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
  mKey = (CRootContainer::getKeyFactory()->add(getObjectType(), this));

  initObjects();

  setMiriamAnnotation(src.getMiriamAnnotation(), mKey, src.mKey);
}

CEvent::~CEvent()
{
  CRootContainer::getKeyFactory()->remove(mKey);
  pdelete(mpTriggerExpression);
  pdelete(mpDelayExpression);
  pdelete(mpPriorityExpression);
}

// virtual
const std::string & CEvent::getKey() const
{
  return CAnnotation::getKey();
}

std::string CEvent::getOriginFor(const DataObjectSet & deletedObjects) const
{
  std::string Origin;
  std::string Separator;

  if (mpTriggerExpression != NULL &&
      mpTriggerExpression->containsCN(deletedObjects))
    {
      Origin += Separator + "Trigger";
      Separator = "\n";
    }

  if (mpPriorityExpression != NULL &&
      mpPriorityExpression->containsCN(deletedObjects))
    {
      Origin += Separator + "Priority";
      Separator = "\n";
    }

  if (mpDelayExpression != NULL &&
      mpDelayExpression->containsCN(deletedObjects))
    {
      Origin += Separator + "Delay";
      Separator = "\n";
    }

  CDataVectorN< CEventAssignment >::const_iterator itAssignment = mAssignments.begin();
  CDataVectorN< CEventAssignment >::const_iterator endAssignment = mAssignments.end();

  for (; itAssignment != endAssignment; ++itAssignment)
    {
      const CEventAssignment& assignment = *itAssignment;

      if (assignment.getExpressionPtr() != NULL &&
          assignment.getExpressionPtr()->containsCN(deletedObjects))
        {
          Origin += Separator + "Assignment (" + (assignment.getTargetObject() != NULL ? assignment.getTargetObject()->getObjectDisplayName() : "not found") + ")";
          Separator = "\n";
        }

      if (assignment.getTargetObject() != NULL)
        {

          auto setIt = deletedObjects.begin();
          auto setEnd = deletedObjects.end();

          for (; setIt != setEnd; ++setIt)
            {
              if (assignment.getTargetObject()->getCN() == (*setIt)->getCN())
                {

                  Origin += Separator + "Target (" + (assignment.getTargetObject() != NULL ? assignment.getTargetObject()->getObjectDisplayName() : "not found") + ")";
                  Separator = "\n";
                }
            }
        }
    }

  return Origin.empty() ? "Unused" : Origin;
}

CIssue CEvent::compile(CObjectInterface::ContainerList listOfContainer)
{
  mValidity.clear();
  CIssue firstWorstIssue;

  // Clear the old direct dependencies.
  mPrerequisits.clear();

  // Compile the trigger expression
  if (mpTriggerExpression != NULL)
    {
      firstWorstIssue &= mpTriggerExpression->compile(listOfContainer);
      mPrerequisits.insert(mpTriggerExpression);
    }
  else
    {
      mValidity.add(CIssue(CIssue::eSeverity::Error, CIssue::eKind::EventMissingTriggerExpression));
      firstWorstIssue &= mValidity.getFirstWorstIssue();
    }

  // Compile the delay expression
  if (mpDelayExpression != NULL)
    {
      firstWorstIssue &= mpDelayExpression->compile(listOfContainer);
      mPrerequisits.insert(mpDelayExpression);
    }

  // Compile the delay expression
  if (mpPriorityExpression != NULL)
    {
      firstWorstIssue &= mpPriorityExpression->compile(listOfContainer);
      mPrerequisits.insert(mpPriorityExpression);
    }

  // Compile the assignments
  CDataVectorN< CEventAssignment >::iterator itAssignment = mAssignments.begin();
  CDataVectorN< CEventAssignment >::iterator endAssignment = mAssignments.end();

  if (mAssignments.empty())
    {
      mValidity.add(CIssue(CIssue::eSeverity::Warning, CIssue::eKind::EventMissingAssignment));
      firstWorstIssue &= mValidity.getFirstWorstIssue();
    }

  for (; itAssignment != endAssignment; ++itAssignment)
    {
      firstWorstIssue &= itAssignment->compile(listOfContainer);
      mPrerequisits.insert(itAssignment);
    }

  return firstWorstIssue;
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

void CEvent::setSBMLId(const std::string& id) const
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

bool CEvent::setObjectParent(const CDataContainer * pParent)
{
  if (pParent != getObjectParent() &&
      mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  bool success = CDataContainer::setObjectParent(pParent);

  mpModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  return success;
}

std::string CEvent::getObjectDisplayName() const
{
  CModel* tmp = dynamic_cast<CModel*>(this->getObjectAncestor("Model"));

  if (tmp)
    return "((" + getObjectName() + "))";

  return CDataObject::getObjectDisplayName();
}

bool CEvent::setTriggerExpression(const std::string & expression)
{
  if (mpTriggerExpression == NULL)
    {
      mpTriggerExpression = new CExpression("TriggerExpression", this);
      mpTriggerExpression->setIsBoolean(true);
    }

  if (mType != Discontinuity &&
      mpModel != NULL &&
      mpTriggerExpression->getInfix() != expression)
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
  CObjectInterface::ContainerList listOfContainer;
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
  if (mpTriggerExpression != NULL) mpTriggerExpression->updateInfix();

  return mpTriggerExpression;
}

CExpression* CEvent::getTriggerExpressionPtr()
{
  if (mpTriggerExpression != NULL) mpTriggerExpression->updateInfix();

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
  CObjectInterface::ContainerList listOfContainer;
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
  if (mpDelayExpression != NULL) mpDelayExpression->updateInfix();

  return mpDelayExpression;
}

CExpression* CEvent::getDelayExpressionPtr()
{
  if (mpDelayExpression != NULL) mpDelayExpression->updateInfix();

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
  CObjectInterface::ContainerList listOfContainer;
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
  if (mpPriorityExpression != NULL) mpPriorityExpression->updateInfix();

  return mpPriorityExpression;
}

const CExpression* CEvent::getPriorityExpressionPtr() const
{
  if (mpPriorityExpression != NULL) mpPriorityExpression->updateInfix();

  return mpPriorityExpression;
}

const CDataVectorN< CEventAssignment > & CEvent::getAssignments() const
{
  return mAssignments;
}

CDataVectorN< CEventAssignment > & CEvent::getAssignments()
{
  return mAssignments;
}

void CEvent::deleteAssignment(const std::string & key)
{
  CEventAssignment * pAssignment =
    dynamic_cast<CEventAssignment *>(CRootContainer::getKeyFactory()->get(key));

  if (pAssignment != NULL)
    {
      mAssignments.CDataVector< CEventAssignment >::remove(pAssignment);
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
