// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include <stdio.h>

#include "copasi/CopasiDataModel/CDataModel.h"
#include "CModel.h"
#include "CEvent.h"

#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/utility.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/function/CExpression.h"
#include "copasi/MIRIAM/CRDFUtilities.h"

// static
CEventAssignment * CEventAssignment::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CEventAssignment(data.getProperty(CData::OBJECT_NAME).toString(),
                              NO_PARENT);
}

// virtual
CData CEventAssignment::toData() const
{
  CData Data(CDataContainer::toData());

  Data.addProperty(CData::EXPRESSION, getExpression());
  Data.addProperty(CData::OBJECT_REFERENCE_CN, getTargetCN());

  return Data;
}

// virtual
bool CEventAssignment::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);
  bool compileModel = false;

  if (data.isSetProperty(CData::EXPRESSION))
    {
      setExpression(data.getProperty(CData::EXPRESSION).toString());
      compileModel = true;
    }

  if (data.isSetProperty(CData::OBJECT_REFERENCE_CN))
    {
      setTargetCN(data.getProperty(CData::OBJECT_REFERENCE_CN).toString());
      compileModel = true;
    }

  if (compileModel)
    {
      CModel * pModel = dynamic_cast< CModel * >(getObjectAncestor("Model"));

      if (pModel != nullptr)
        {
          pModel->setCompileFlag(true);
        }
    }

  return success;
}

// virtual
void CEventAssignment::createUndoData(CUndoData & undoData,
                                      const CUndoData::Type & type,
                                      const CData & oldData,
                                      const CCore::Framework & framework) const
{
  CDataContainer::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  undoData.addProperty(CData::EXPRESSION, oldData.getProperty(CData::EXPRESSION), getExpression());
  undoData.addProperty(CData::OBJECT_REFERENCE_CN, oldData.getProperty(CData::OBJECT_REFERENCE_CN), getTargetCN());
}

// The default constructor is intentionally not implemented.
// CEventAssignment::CEventAssignment() {}

CEventAssignment::CEventAssignment(const std::string & targetCN,
                                   const CDataContainer * pParent) :
  CDataContainer(targetCN, pParent, "EventAssignment"),
  mKey(CRootContainer::getKeyFactory()->add("EventAssignment", this)),
  mpModel(static_cast<CModel *>(getObjectAncestor("Model"))),
  mTargetCN(targetCN),
  mpTarget(nullptr),
  mpExpression(nullptr)
{
  //fall back, in case the constructor is called with a key instead of a CN
  CModelEntity * pObject = dynamic_cast< CModelEntity * >(CRootContainer::getKeyFactory()->get(targetCN));

  if (pObject != nullptr)
    {
      mTargetCN = pObject->getValueObject()->getCN();
      setObjectName(mTargetCN);
    }

  if (mpModel != nullptr)
    {
      mpModel->setCompileFlag(true);
    }
}

CEventAssignment::CEventAssignment(const CEventAssignment & src,
                                   const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mKey(CRootContainer::getKeyFactory()->add("EventAssignment", this)),
  mpModel(static_cast<CModel *>(getObjectAncestor("Model"))),
  mTargetCN(src.mTargetCN),
  mpTarget(src.mpTarget),
  mpExpression(nullptr)
{
  if (mpModel != nullptr)
    {
      mpModel->setCompileFlag(true);
    }

  setExpression(src.getExpression());
}

CEventAssignment::~CEventAssignment()
{
  pdelete(mpExpression);

  if (mpModel != nullptr)
    {
      mpModel->setCompileFlag(true);
    }
}

bool CEventAssignment::operator != (const CEventAssignment & rhs) const
{
  if (getTargetCN() != rhs.getTargetCN())
    {
      return true;
    }

  if (getExpression() != rhs.getExpression())
    {
      return true;
    }

  return false;
}

bool CEventAssignment::setObjectParent(const CDataContainer * pParent)
{
  if (pParent != getObjectParent() &&
      mpModel != nullptr)
    {
      mpModel->setCompileFlag(true);
    }

  bool success = CDataContainer::setObjectParent(pParent);
  mpModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel != nullptr)
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

  mpTarget = nullptr;
  CDataModel * pDataModel = getObjectDataModel();

  if (pDataModel != nullptr)
    mpTarget = CObjectInterface::DataObject(pDataModel->getObject(getTargetCN()));

  const CModelEntity * pEntity = dynamic_cast< const CModelEntity * >(mpTarget);

  if (pEntity != nullptr)
    {
      mpTarget = pEntity->getValueObject();
      setTargetCN(mpTarget->getCN());
    }
  else
    pEntity =  dynamic_cast< const CModelEntity * >(mpTarget->getObjectParent());

  if (pEntity != nullptr &&
      pEntity->getStatus() != CModelEntity::Status::ASSIGNMENT)
    {
      mPrerequisits.insert(pEntity);
    }
  else if (pEntity != nullptr &&
           pEntity->getStatus() == CModelEntity::Status::ASSIGNMENT)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Invalid EventAssignment for '%s': an Assignment Rule already exists", pEntity->getObjectName().c_str());
      mValidity.add(CIssue(CIssue::eSeverity::Error, CIssue::eKind::EventAlreadyHasAssignment));
      firstWorstIssue &= mValidity.getFirstWorstIssue();
    }
  else if (pEntity == nullptr)
    {
      CCopasiMessage(CCopasiMessage::WARNING, "Invalid EventAssignment for '%s': object does not exist.", getObjectName().c_str());
      mValidity.add(CIssue(CIssue::eSeverity::Warning, CIssue::eKind::ObjectNotFound));
      firstWorstIssue &= mValidity.getFirstWorstIssue();
    }

  if (mpExpression != nullptr)
    {
      firstWorstIssue &= mpExpression->compile(listOfContainer);
      mPrerequisits.insert(mpExpression->getPrerequisites().begin(), mpExpression->getPrerequisites().end());
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

bool CEventAssignment::setTargetCN(const std::string & targetCN)
{
  if (targetCN != getTargetCN() &&
      mpModel != nullptr)
    {
      mpModel->setCompileFlag(true);
    }

  mTargetCN = targetCN;
  return setObjectName(targetCN);
}

const std::string & CEventAssignment::getTargetCN() const
{
  //if (mTargetCN != getObjectName())
  //  setObjectName(mTargetCN);
  return mTargetCN;
}

std::string CEventAssignment::getXmlTargetCN() const
{
  CCommonName parentCN;
  std::string objectType;
  std::string objectName;

  mTargetCN.split(parentCN, objectType, objectName);

  if (objectName != "ParticleNumber")
    return parentCN;

  return mTargetCN;
}

bool CEventAssignment::setExpression(const std::string & expression)
{
  if (mpExpression == nullptr)
    mpExpression = new CExpression("Expression", this);

  if (mpExpression->getInfix() != expression &&
      mpModel != nullptr)
    {
      mpModel->setCompileFlag(true);
    }

  return mpExpression->setInfix(expression);
}

bool CEventAssignment::setExpressionPtr(CExpression * pExpression)
{
  if (pExpression == mpExpression) return true;

  if (pExpression == nullptr) return false;

  if (mpModel != nullptr)
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
  mpExpression->setObjectParent(nullptr);
  mpExpression = pOld;
  return false;
}

std::string CEventAssignment::getExpression() const
{
  if (mpExpression == nullptr)
    return "";

  mpExpression->updateInfix();

  return mpExpression->getInfix();
}

const CExpression* CEventAssignment::getExpressionPtr() const
{
  if (mpExpression != nullptr) mpExpression->updateInfix();

  return mpExpression;
}

CExpression* CEventAssignment::getExpressionPtr()
{
  if (mpExpression != nullptr) mpExpression->updateInfix();

  return mpExpression;
}

//****************************************************************
// static
CEvent * CEvent::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CEvent(data.getProperty(CData::OBJECT_NAME).toString(),
                    NO_PARENT);
}

// virtual
CData CEvent::toData() const
{
  CData Data(CDataContainer::toData());

  Data.addProperty(CData::DELAY_ASSIGNMENT, mDelayAssignment);
  Data.addProperty(CData::FIRE_AT_INITIALTIME, mFireAtInitialTime);
  Data.addProperty(CData::PERSISTENT_TRIGGER, mPersistentTrigger);
  Data.addProperty(CData::TRIGGER_EXPRESSION, getTriggerExpression());
  Data.addProperty(CData::DELAY_EXPRESSION, getDelayExpression());
  Data.addProperty(CData::PRIORITY_EXPRESSION, getPriorityExpression());
  Data.addProperty(CData::ASSIGNMENTS, mAssignments.toData().getProperty(CData::VECTOR_CONTENT));

  Data.appendData(CAnnotation::toData());

  return Data;
}

// virtual
bool CEvent::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);
  bool compileModel = false;

  if (data.isSetProperty(CData::DELAY_ASSIGNMENT))
    {
      mDelayAssignment = data.getProperty(CData::DELAY_ASSIGNMENT).toBool();
      compileModel = true;
    }

  if (data.isSetProperty(CData::FIRE_AT_INITIALTIME))
    {
      mFireAtInitialTime = data.getProperty(CData::EXPRESSION).toBool();
      compileModel = true;
    }

  if (data.isSetProperty(CData::PERSISTENT_TRIGGER))
    {
      mPersistentTrigger = data.getProperty(CData::PERSISTENT_TRIGGER).toBool();
      compileModel = true;
    }

  if (data.isSetProperty(CData::TRIGGER_EXPRESSION))
    {
      success &= setTriggerExpression(data.getProperty(CData::TRIGGER_EXPRESSION).toString());
      compileModel = true;
    }

  if (data.isSetProperty(CData::DELAY_EXPRESSION))
    {
      success &= setDelayExpression(data.getProperty(CData::DELAY_EXPRESSION).toString());
    }

  if (data.isSetProperty(CData::PRIORITY_EXPRESSION))
    {
      success &= setPriorityExpression(data.getProperty(CData::PRIORITY_EXPRESSION).toString());
      compileModel = true;
    }

  if (data.isSetProperty(CData::ASSIGNMENTS))
    {
      CData Data;
      Data.addProperty(CData::VECTOR_CONTENT, data.getProperty(CData::ASSIGNMENTS));
      success &= mAssignments.applyData(Data, changes);
      compileModel = true;
    }

  success &= CAnnotation::applyData(data, changes);

  if (compileModel)
    {
      CModel * pModel = dynamic_cast< CModel * >(getObjectAncestor("Model"));

      if (pModel != nullptr)
        {
          pModel->setCompileFlag(true);
        }
    }

  return success;
}

// virtual
void CEvent::createUndoData(CUndoData & undoData,
                            const CUndoData::Type & type,
                            const CData & oldData,
                            const CCore::Framework & framework) const
{
  CDataContainer::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  undoData.addProperty(CData::DELAY_ASSIGNMENT, oldData.getProperty(CData::DELAY_ASSIGNMENT), mDelayAssignment);
  undoData.addProperty(CData::FIRE_AT_INITIALTIME, oldData.getProperty(CData::FIRE_AT_INITIALTIME), mFireAtInitialTime);
  undoData.addProperty(CData::PERSISTENT_TRIGGER, oldData.getProperty(CData::PERSISTENT_TRIGGER), mPersistentTrigger);
  undoData.addProperty(CData::TRIGGER_EXPRESSION, oldData.getProperty(CData::TRIGGER_EXPRESSION), getTriggerExpression());
  undoData.addProperty(CData::DELAY_EXPRESSION, oldData.getProperty(CData::DELAY_EXPRESSION), getDelayExpression());
  undoData.addProperty(CData::PRIORITY_EXPRESSION, oldData.getProperty(CData::PRIORITY_EXPRESSION), getPriorityExpression());

  CData VectorContent;
  VectorContent.addProperty(CData::VECTOR_CONTENT, oldData.getProperty(CData::ASSIGNMENTS));

  CUndoData Assignments;
  mAssignments.createUndoData(Assignments, CUndoData::Type::CHANGE, VectorContent, framework);

  undoData.addPreProcessData(Assignments.getPreProcessData());
  undoData.addPostProcessData(Assignments.getPostProcessData());

  if (Assignments.isChangedProperty(CData::VECTOR_CONTENT))
    {
      undoData.addProperty(CData::ASSIGNMENTS, Assignments.getOldData().getProperty(CData::VECTOR_CONTENT), Assignments.getNewData().getProperty(CData::VECTOR_CONTENT));
    }

  CAnnotation::createUndoData(undoData, type, oldData, framework);

  return;
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
  mpTriggerExpression(nullptr),
  mpDelayExpression(nullptr),
  mpPriorityExpression(nullptr),
  mType(Assignment)
{
  mKey = (CRootContainer::getKeyFactory()->add(getObjectType(), this));
  initMiriamAnnotation(mKey);

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
  mpTriggerExpression(src.mpTriggerExpression != nullptr ? new CExpression(*src.mpTriggerExpression, this) : nullptr),
  mpDelayExpression(src.mpDelayExpression != nullptr ? new CExpression(*src.mpDelayExpression, this) : nullptr),
  mpPriorityExpression(src.mpPriorityExpression != nullptr ? new CExpression(*src.mpPriorityExpression, this) : nullptr),
  mType(src.mType)
{
  mKey = (CRootContainer::getKeyFactory()->add(getObjectType(), this));
  setMiriamAnnotation(src.getMiriamAnnotation(), mKey, src.mKey);

  initObjects();
}

CEvent::~CEvent()
{
  if (mpModel != nullptr)
    {
      mpModel->setCompileFlag(true);
    }

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

  if (mpTriggerExpression != nullptr &&
      mpTriggerExpression->containsCN(deletedObjects))
    {
      Origin += Separator + "Trigger";
      Separator = "\n";
    }

  if (mpPriorityExpression != nullptr &&
      mpPriorityExpression->containsCN(deletedObjects))
    {
      Origin += Separator + "Priority";
      Separator = "\n";
    }

  if (mpDelayExpression != nullptr &&
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

      if (assignment.getExpressionPtr() != nullptr &&
          assignment.getExpressionPtr()->containsCN(deletedObjects))
        {
          Origin += Separator + "Assignment (" + (assignment.getTargetObject() != nullptr ? assignment.getTargetObject()->getObjectDisplayName() : "not found") + ")";
          Separator = "\n";
        }

      if (assignment.getTargetObject() != nullptr)
        {

          auto setIt = deletedObjects.begin();
          auto setEnd = deletedObjects.end();

          for (; setIt != setEnd; ++setIt)
            {
              if (assignment.getTargetObject()->getCN() == (*setIt)->getCN())
                {

                  Origin += Separator + "Target (" + (assignment.getTargetObject() != nullptr ? assignment.getTargetObject()->getObjectDisplayName() : "not found") + ")";
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
  if (mpTriggerExpression != nullptr)
    {
      firstWorstIssue &= mpTriggerExpression->compile(listOfContainer);
      mPrerequisits.insert(mpTriggerExpression->getPrerequisites().begin(), mpTriggerExpression->getPrerequisites().end());
    }
  else
    {
      mValidity.add(CIssue(CIssue::eSeverity::Error, CIssue::eKind::EventMissingTriggerExpression));
      firstWorstIssue &= mValidity.getFirstWorstIssue();
    }

  // Compile the delay expression
  if (mpDelayExpression != nullptr)
    {
      firstWorstIssue &= mpDelayExpression->compile(listOfContainer);
      mPrerequisits.insert(mpDelayExpression->getPrerequisites().begin(), mpDelayExpression->getPrerequisites().end());
    }

  // Compile the delay expression
  if (mpPriorityExpression != nullptr)
    {
      firstWorstIssue &= mpPriorityExpression->compile(listOfContainer);
      mPrerequisits.insert(mpPriorityExpression->getPrerequisites().begin(), mpPriorityExpression->getPrerequisites().end());
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
    }

  return firstWorstIssue;
}

void CEvent::initObjects()
{
  if (mpModel != nullptr)
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
      mpModel != nullptr)
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

      if (mpModel != nullptr)
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

      if (mpModel != nullptr)
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
      mpModel != nullptr)
    {
      mpModel->setCompileFlag(true);
    }

  bool success = CDataContainer::setObjectParent(pParent);

  mpModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel != nullptr)
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
  if (mpTriggerExpression == nullptr)
    {
      mpTriggerExpression = new CExpression("TriggerExpression", this);
      mpTriggerExpression->setIsBoolean(true);
    }

  if (mType != Discontinuity &&
      mpModel != nullptr &&
      mpTriggerExpression->getInfix() != expression)
    {
      mpModel->setCompileFlag(true);
    }

  return mpTriggerExpression->setInfix(expression);
}

bool CEvent::setTriggerExpressionPtr(CExpression * pExpression)
{
  if (pExpression == mpTriggerExpression) return true;

  if (pExpression == nullptr) return false;

  if (mpModel != nullptr)
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
  mpTriggerExpression->setObjectParent(nullptr);
  mpTriggerExpression = pOld;
  return false;
}

std::string CEvent::getTriggerExpression() const
{
  if (mpTriggerExpression == nullptr)
    return "";

  mpTriggerExpression->updateInfix();

  return mpTriggerExpression->getInfix();
}

const CExpression* CEvent::getTriggerExpressionPtr() const
{
  if (mpTriggerExpression != nullptr) mpTriggerExpression->updateInfix();

  return mpTriggerExpression;
}

CExpression* CEvent::getTriggerExpressionPtr()
{
  if (mpTriggerExpression != nullptr) mpTriggerExpression->updateInfix();

  return mpTriggerExpression;
}

bool CEvent::setDelayExpression(const std::string & expression)
{
  if (mpDelayExpression == nullptr)
    mpDelayExpression = new CExpression("DelayExpression", this);

  if (mpDelayExpression->getInfix() != expression &&
      mpModel != nullptr)
    {
      mpModel->setCompileFlag(true);
    }

  return mpDelayExpression->setInfix(expression);
}

bool CEvent::setDelayExpressionPtr(CExpression * pExpression)
{
  if (pExpression == mpDelayExpression) return true;

  if (pExpression == nullptr) return false;

  if (mpModel != nullptr)
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
  mpDelayExpression->setObjectParent(nullptr);
  mpDelayExpression = pOld;
  return false;
}

std::string CEvent::getDelayExpression() const
{
  if (mpDelayExpression == nullptr)
    return "";

  mpDelayExpression->updateInfix();

  return mpDelayExpression->getInfix();
}

const CExpression* CEvent::getDelayExpressionPtr() const
{
  if (mpDelayExpression != nullptr) mpDelayExpression->updateInfix();

  return mpDelayExpression;
}

CExpression* CEvent::getDelayExpressionPtr()
{
  if (mpDelayExpression != nullptr) mpDelayExpression->updateInfix();

  return mpDelayExpression;
}

bool CEvent::setPriorityExpression(const std::string & expression)
{
  if (mpPriorityExpression == nullptr)
    mpPriorityExpression = new CExpression("PriorityExpression", this);

  if (mpPriorityExpression->getInfix() != expression &&
      mpModel != nullptr)
    {
      mpModel->setCompileFlag(true);
    }

  return mpPriorityExpression->setInfix(expression);
}

bool CEvent::setPriorityExpressionPtr(CExpression* pExpression)
{
  if (pExpression == mpPriorityExpression) return true;

  if (pExpression == nullptr) return false;

  if (mpModel != nullptr)
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
  mpPriorityExpression->setObjectParent(nullptr);
  mpPriorityExpression = pOld;
  return false;
}

std::string CEvent::getPriorityExpression() const
{
  if (mpPriorityExpression == nullptr)
    return "";

  mpPriorityExpression->updateInfix();

  return mpPriorityExpression->getInfix();
}

CExpression* CEvent::getPriorityExpressionPtr()
{
  if (mpPriorityExpression != nullptr) mpPriorityExpression->updateInfix();

  return mpPriorityExpression;
}

const CExpression* CEvent::getPriorityExpressionPtr() const
{
  if (mpPriorityExpression != nullptr) mpPriorityExpression->updateInfix();

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

  if (pAssignment != nullptr)
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
