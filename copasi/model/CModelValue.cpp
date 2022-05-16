// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
    \file CModelValue.cpp
    \brief Implementation file of class CModelEntity and CModelValue
 */

#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "copasi/copasi.h"

#include "CModel.h"
#include "CModelValue.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/function/CExpression.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/utility.h"
#include "copasi/core/CRootContainer.h"

//static
const CEnumAnnotation< std::string, CModelEntity::Status > CModelEntity::StatusName(
{
  "fixed",
  "assignment",
  "reactions",
  "ode",
  "time"
});

//static
const CEnumAnnotation< std::string, CModelEntity::Status > CModelEntity::XMLStatus(
{
  "fixed",
  "assignment",
  "reactions",
  "ode",
  "time"
});

// static
CModelEntity * CModelEntity::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  // It is not possible to create a CModelEntity from data.
  // Only derived classes are allowed!

  return NULL;
}

// virtual
CData CModelEntity::toData() const
{
  CData Data = CDataContainer::toData();

  Data.addProperty(CData::SIMULATION_TYPE, StatusName[mStatus]);
  Data.addProperty(CData::INITIAL_VALUE, mIValue);
  Data.addProperty(CData::INITIAL_EXPRESSION, getInitialExpression());
  Data.addProperty(CData::EXPRESSION, getExpression());
  Data.addProperty(CData::ADD_NOISE, mHasNoise);
  Data.addProperty(CData::NOISE_EXPRESSION, getNoiseExpression());

  Data.appendData(CAnnotation::toData());

  return Data;
}

// virtual
bool CModelEntity::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);
  bool compileModel = false;

  if (data.isSetProperty(CData::SIMULATION_TYPE))
    {
      setStatus(StatusName.toEnum(data.getProperty(CData::SIMULATION_TYPE).toString()));
      compileModel = true;
    }

  if (data.isSetProperty(CData::INITIAL_VALUE))
    {
      mIValue = data.getProperty(CData::INITIAL_VALUE).toDouble();
    }

  if (data.isSetProperty(CData::INITIAL_EXPRESSION))
    {
      success &= setInitialExpression(data.getProperty(CData::INITIAL_EXPRESSION).toString());
      compileModel = true;
    }

  if (data.isSetProperty(CData::EXPRESSION))
    {
      success &= setExpression(data.getProperty(CData::EXPRESSION).toString());
      compileModel = true;
    }

  if (data.isSetProperty(CData::ADD_NOISE))
    {
      setHasNoise(data.getProperty(CData::ADD_NOISE).toBool());
      compileModel = true;
    }

  if (data.isSetProperty(CData::NOISE_EXPRESSION))
    {
      success &= setNoiseExpression(data.getProperty(CData::NOISE_EXPRESSION).toString());
      compileModel = true;
    }

  success &= CAnnotation::applyData(data, changes);

  if (compileModel &&
      mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  return success;
}

// virtual
void CModelEntity::createUndoData(CUndoData & undoData,
                                  const CUndoData::Type & type,
                                  const CData & oldData,
                                  const CCore::Framework & framework) const
{
  CDataContainer::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  undoData.addProperty(CData::SIMULATION_TYPE, oldData.getProperty(CData::SIMULATION_TYPE), StatusName[mStatus]);
  undoData.addProperty(CData::INITIAL_VALUE, oldData.getProperty(CData::INITIAL_VALUE), mIValue);
  undoData.addProperty(CData::INITIAL_EXPRESSION, oldData.getProperty(CData::INITIAL_EXPRESSION), getInitialExpression());
  undoData.addProperty(CData::EXPRESSION, oldData.getProperty(CData::EXPRESSION), getExpression());
  undoData.addProperty(CData::ADD_NOISE, oldData.getProperty(CData::ADD_NOISE), mHasNoise);
  undoData.addProperty(CData::NOISE_EXPRESSION, oldData.getProperty(CData::NOISE_EXPRESSION), getNoiseExpression());

  CAnnotation::createUndoData(undoData, type, oldData, framework);

  return;
}

// the "variable" keyword is used for compatibility reasons. It actually means "this metab is part
// of the reaction network, copasi needs to figure out if it is independent, dependent (moieties) or unused."

CModelEntity::CModelEntity(const std::string & name,
                           const CDataContainer * pParent,
                           const std::string & type,
                           const CFlags< Flag > & flag):
  CDataContainer(name, pParent, type, (flag | CDataObject::Container | CDataObject::ValueDbl | CDataObject::ModelEntity)),
  CAnnotation(),
  mValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
  mIValue(1.0),
  mRate(0.0),
  mNoise(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
  mpExpression(NULL),
  mpInitialExpression(NULL),
  mpNoiseExpression(NULL),
  mHasNoise(false),
  mStatus(Status::FIXED),
  mUsed(false),
  mpModel(NULL),
  mUnitExpression("")
{
  mKey = CRootContainer::getKeyFactory()->add(getObjectType(), this);
  initMiriamAnnotation(mKey);

  initObjects();

  CONSTRUCTOR_TRACE;
}

CModelEntity::CModelEntity(const CModelEntity & src,
                           const CDataContainer * pParent):
  CDataContainer(src, pParent),
  CAnnotation(src),
  mValue(src.mValue),
  mIValue(src.mIValue),
  mRate(src.mRate),
  mNoise(src.mNoise),
  mpExpression(src.mpExpression != NULL ? new CExpression(*src.mpExpression, this) : NULL),
  mpInitialExpression(src.mpInitialExpression != NULL ? new CExpression(*src.mpInitialExpression, this) : NULL),
  mpNoiseExpression(src.mpNoiseExpression != NULL ? new CExpression(*src.mpNoiseExpression, this) : NULL),
  mHasNoise(src.mHasNoise),
  mStatus(Status::FIXED),
  mUsed(false),
  mpModel(NULL),
  mUnitExpression(src.mUnitExpression)
{
  mKey = CRootContainer::getKeyFactory()->add(getObjectType(), this);
  setMiriamAnnotation(src.getMiriamAnnotation(), mKey, src.mKey);

  initObjects();

  setStatus(src.mStatus);
}

CModelEntity::~CModelEntity()
{
  if (mpModel)
    mpModel->removeModelEntity(this);

  // After the above call we definitely own the data and
  // therefore must destroy them.

  // since the expressions now have the model entity as parent, they should
  // automatically be destroyed be the destructor of CDataContainer
  //pdelete(mpExpression);
  //pdelete(mpInitialExpression);

  DESTRUCTOR_TRACE;
}

// virtual
const std::string & CModelEntity::getKey() const
{
  return CAnnotation::getKey();
}

const C_FLOAT64 & CModelEntity::getValue() const {return mValue;}

const C_FLOAT64 & CModelEntity::getInitialValue() const
{return mIValue;}

const CModelEntity::Status & CModelEntity::getStatus() const {return mStatus;}

CIssue CModelEntity::compile()
{
  mPrerequisits.clear();
  mValidity.clear();

  CIssue firstWorstIssue, issue;

  CObjectInterface::ContainerList listOfContainer;
  listOfContainer.push_back(mpModel);
  CDataModel* pDataModel = NULL;

  switch (mStatus)
    {
      case Status::ASSIGNMENT:

        pdelete(mpInitialExpression);

        if (getExpression().empty())
          {
            issue = CIssue(CIssue::eSeverity::Warning, CIssue::eKind::ExpressionEmpty);
            mValidity.add(issue);
            firstWorstIssue &= issue;
          }

        if (mpExpression != NULL)
          {
            issue = mpExpression->compile(listOfContainer);
            mValidity.add(issue);
            firstWorstIssue &= issue;

            pDataModel = getObjectDataModel();
            assert(pDataModel != NULL);
            mpInitialExpression = CExpression::createInitialExpression(*mpExpression, pDataModel);

            if (mpInitialExpression != NULL)
              {
                mpInitialExpression->setObjectName("InitialExpression");
                add(mpInitialExpression, true);
              }
          }

        break;

      case Status::ODE:

        if (getExpression().empty())
          {
            issue = CIssue(CIssue::eSeverity::Warning, CIssue::eKind::ExpressionEmpty);
            mValidity.add(issue);
            firstWorstIssue &= issue;
          }

        if (mpExpression != NULL)
          {
            issue = mpExpression->compile(listOfContainer);
            mValidity.add(issue);
            firstWorstIssue &= issue;
          }

        if (mHasNoise)
          {
            if (getNoiseExpression().empty())
              {
                issue = CIssue(CIssue::eSeverity::Warning, CIssue::eKind::ExpressionEmpty);
                mValidity.add(issue);
                firstWorstIssue &= issue;
              }

            if (mpNoiseExpression != NULL)
              {
                issue = mpNoiseExpression->compile(listOfContainer);
                mValidity.add(issue);
                firstWorstIssue &= issue;
              }
          }

        break;

      default:
        break;
    }

  // Here we handle initial expressions for all types.
  if (mpInitialExpression != NULL &&
      mpInitialExpression->getInfix() != "")
    {
      issue = mpInitialExpression->compile(listOfContainer);
      mValidity.add(issue);
      firstWorstIssue &= issue;

      // If we have a valid initial expression, we update the initial value.
      // In case the expression is constant this suffices other are updated lated again.
      issue = mpInitialExpression->getValidity().getFirstWorstIssue();
      mValidity.add(issue);
      firstWorstIssue &= issue;

      if (issue)
        mIValue = mpInitialExpression->calcValue();
    }

  // We need to add all called functions to the dependencies
  if (mpInitialExpression != NULL)
    {
      mPrerequisits.insert(mpInitialExpression->getPrerequisites().begin(), mpInitialExpression->getPrerequisites().end());
    }

  if (mpExpression != NULL)
    {
      mPrerequisits.insert(mpExpression->getPrerequisites().begin(), mpExpression->getPrerequisites().end());
    }

  if (mpNoiseExpression != NULL)
    {
      mPrerequisits.insert(mpNoiseExpression->getPrerequisites().begin(), mpNoiseExpression->getPrerequisites().end());
    }

  return firstWorstIssue;
}

void CModelEntity::calculate()
{
  switch (mStatus)
    {
      case Status::ASSIGNMENT:
        mValue = mpExpression->calcValue();
        break;

      case Status::ODE:
        mRate = mpExpression->calcValue();
        break;

      default:
        break;
    }
}

CIssue CModelEntity::setExpression(const std::string & expression)
{
  CIssue issue;
  mValidity.remove(CValidity::Severity::All,
                   CValidity::Kind(CIssue::eKind::SettingFixedExpression));

  if (isFixed() && !expression.empty())
    {
      issue = CIssue(CIssue::eSeverity::Error,
                     CIssue::eKind::SettingFixedExpression);
      mValidity.add(issue);
      return issue;
    }

  if ((mpExpression == NULL &&
       expression.empty()) ||
      (mpExpression != NULL &&
       mpExpression->getInfix() == expression)) return issue;

  if (mpExpression == NULL)
    mpExpression = new CExpression("Expression", this);

  if (mpModel != NULL)
    mpModel->setCompileFlag(true);

  issue = mpExpression->setInfix(expression);

  if (!issue) return issue;

  return issue &= compile();
}

std::string CModelEntity::getExpression() const
{
  if (isFixed() || mpExpression == NULL)
    return "";

  mpExpression->updateInfix();
  return mpExpression->getInfix();
}

CExpression* CModelEntity::getExpressionPtr()
{
  if (mpExpression != NULL) mpExpression->updateInfix();

  return mpExpression;
}

const CExpression* CModelEntity::getExpressionPtr() const
{
  if (mpExpression != NULL) mpExpression->updateInfix();

  return mpExpression;
}

bool CModelEntity::setExpressionPtr(CExpression* pExpression)
{
  if (isFixed()) return false;

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

  if (compile())
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

CExpression* CModelEntity::getInitialExpressionPtr()
{
  if (mpInitialExpression != NULL) mpInitialExpression->updateInfix();

  return mpInitialExpression;
}

const CExpression* CModelEntity::getInitialExpressionPtr() const
{
  if (mpInitialExpression != NULL) mpInitialExpression->updateInfix();

  return mpInitialExpression;
}

std::string CModelEntity::getDefaultNoiseExpression() const
{
  return "sqrt(abs(<" + mpRateReference->getCN() + ">))";
}

bool CModelEntity::setNoiseExpression(const std::string & expression)
{
  if (mStatus != Status::ODE) return false;

  if (mpModel)
    mpModel->setCompileFlag(true);

  if (mpNoiseExpression == NULL)
    {
      mpNoiseExpression = new CExpression("NoiseExpression", this);
    }

  if (!mpNoiseExpression->setInfix(expression)) return false;

  return compile();
}

std::string CModelEntity::getNoiseExpression() const
{
  if (mStatus != Status::ODE || mpNoiseExpression == NULL)
    return "";

  mpNoiseExpression->updateInfix();
  return mpNoiseExpression->getInfix();
}

bool CModelEntity::setNoiseExpressionPtr(CExpression* pExpression)
{
  if (mStatus != Status::ODE) return false;

  if (pExpression == mpNoiseExpression) return true;

  if (pExpression == NULL) return false;

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  CExpression * pOld = mpNoiseExpression;
  mpNoiseExpression = pExpression;

  mpNoiseExpression->setObjectName("NoiseExpression");
  add(mpNoiseExpression, true);

  if (compile())
    {
      pdelete(pOld);
      return true;
    }

  // If compile fails we do not take ownership
  // and we remove the object from the container
  remove(mpNoiseExpression);
  mpNoiseExpression->setObjectParent(NULL);
  mpNoiseExpression = pOld;

  return false;
}

CExpression* CModelEntity::getNoiseExpressionPtr()
{
  if (mpNoiseExpression != NULL) mpNoiseExpression->updateInfix();

  return mpNoiseExpression;
}

const CExpression* CModelEntity::getNoiseExpressionPtr() const
{
  if (mpNoiseExpression != NULL) mpNoiseExpression->updateInfix();

  return mpNoiseExpression;
}

void CModelEntity::setHasNoise(const bool & hasNoise)
{
  mHasNoise = hasNoise;

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }
}

/**
 * Check whether noise is added to the ODE
 * @return const bool & hasNoise
 */
const bool & CModelEntity::hasNoise() const
{
  return mHasNoise;
}

bool CModelEntity::setInitialExpressionPtr(CExpression* pExpression)
{
  if (mStatus == Status::ASSIGNMENT) return false;

  if (pExpression == mpInitialExpression) return true;

  if (pExpression == NULL) return false;

  if (mpModel != NULL)
    {
      mpModel->setCompileFlag(true);
    }

  CExpression * pOld = mpInitialExpression;
  mpInitialExpression = pExpression;

  mpInitialExpression->setObjectName("InitialExpression");
  add(mpInitialExpression, true);

  if (compile())
    {
      pdelete(pOld);
      return true;
    }

  // If compile fails we do not take ownership
  // and we remove the object from the container
  remove(mpInitialExpression);
  mpInitialExpression->setObjectParent(NULL);
  mpInitialExpression = pOld;

  return false;
}

CIssue CModelEntity::setInitialExpression(const std::string & expression)
{
  CIssue issue;
  mValidity.remove(CValidity::Severity::All,
                   CValidity::Kind(CIssue::eKind::InitialExpressionWithAssignment));

  if (mStatus == Status::ASSIGNMENT)
    {
      issue = CIssue(CIssue::eSeverity::Error, CIssue::eKind::InitialExpressionWithAssignment);
      mValidity.add(issue);
      return issue;
    }

  if ((mpInitialExpression == NULL &&
       expression.empty()) ||
      (mpInitialExpression != NULL &&
       mpInitialExpression->getInfix() == expression)) return issue;

  if (mpInitialExpression == NULL)
    {
      mpInitialExpression = new CExpression("InitialExpression", this);
    }

  if (mpModel) mpModel->setCompileFlag(true);

  if (!(issue = mpInitialExpression->setInfix(expression))) return issue;

  return compile();
}

std::string CModelEntity::getInitialExpression() const
{
  if (mStatus == Status::ASSIGNMENT || mpInitialExpression == NULL)
    return "";

  mpInitialExpression->updateInfix();
  return mpInitialExpression->getInfix();
}

// virtual
CIssue CModelEntity::setUnitExpression(std::string unitExpression)
{
  CIssue Issue;

  if (mUnitExpression != unitExpression)
    {
      mUnitExpression = unitExpression;
      mValidity.remove(CValidity::Severity::All,
                       CValidity::Kind(CIssue::eKind::UnitUndefined) | CIssue::eKind::UnitConflict | CIssue::eKind::UnitInvalid);

      CUnit Unit;

      if (!(Issue = Unit.setExpression(mUnitExpression)))
        {
          if (mUnitExpression == "" || mUnitExpression == "?")
            {
              Issue = CIssue(CIssue::eSeverity::Warning, CIssue::eKind::UnitUndefined);
            }

          mValidity.add(Issue);
        }
    }

  return Issue;
}

// virtual
const std::string & CModelEntity::getUnitExpression() const
{
  return mUnitExpression;
}

// virtual
std::string CModelEntity::getChildObjectUnits(const CDataObject * pObject) const
{
  if (pObject == mpRateReference)
    {
      std::string ValueUnit = getChildObjectUnits(mpValueReference);
      std::string TimeUnit = (mpModel != NULL) ? mpModel->getTimeUnit() : "?";

      return (ValueUnit.empty() ? "?" : ValueUnit) + "/(" + TimeUnit + ")";
    }

  if (pObject == mpValueReference ||
      pObject == mpIValueReference)
    {
      return getUnits();
    }

  return "?";
}

/**
 * Return rate of production of this entity
 */
const C_FLOAT64 & CModelEntity::getRate() const
{
  return mRate;
}

CDataObject * CModelEntity::getInitialValueReference() const
{return mpIValueReference;}

CDataObject * CModelEntity::getValueReference() const
{return mpValueReference;}

CDataObject * CModelEntity::getRateReference() const
{return mpRateReference;}

CDataObject * CModelEntity::getNoiseReference() const
{return mpNoiseReference;}

CModel * CModelEntity::getModel() const
{
  return mpModel;
}
//***********

void CModelEntity::setValue(const C_FLOAT64 & value)
{
  mValue = value;
}

void CModelEntity::setInitialValue(const C_FLOAT64 & initialValue)
{
  mIValue = initialValue;
}

void CModelEntity::setRate(const C_FLOAT64 & rate)
{
  mRate = rate;
}

//  ******************

bool CModelEntity::setStatus(const CModelEntity::Status & status)
{
  bool success = (status != Status::__SIZE);

  if (success
      && mStatus != status)
    {
      if (mpModel != NULL)
        mpModel->setCompileFlag(true);

      // An assignment may not have an initial expression.
      // However, internally we always create one, which need
      // to be deleted.
      if (mStatus == Status::ASSIGNMENT)
        pdelete(mpInitialExpression);

      if (mpModel != NULL)
        mpModel->setCompileFlag(true);

      CDataModel* pDataModel = NULL;

      switch (status)
        {
          case Status::ASSIGNMENT:
            mStatus = status;

            if (mpExpression == NULL)
              mpExpression = new CExpression("Expression", this);

            pdelete(mpInitialExpression);
            pDataModel = getObjectDataModel();
            mpInitialExpression = CExpression::createInitialExpression(*mpExpression, pDataModel);

            if (mpInitialExpression != NULL)
              {
                mpInitialExpression->setObjectName("InitialExpression");
                add(mpInitialExpression, true);
              }

            mRate = std::numeric_limits<C_FLOAT64>::quiet_NaN();

            mUsed = true;
            break;

          case Status::ODE:
            mStatus = status;

            if (mpExpression == NULL)
              mpExpression = new CExpression("Expression", this);

            mUsed = true;
            break;

          case Status::REACTIONS:
            success = (getObjectType() == "Metabolite");

            if (success)
              {
                mStatus = status;
                pdelete(mpExpression);
              }

            mUsed = true;
            break;

          case Status::TIME:
            success = (getObjectType() == "Model");

            if (success)
              {
                mStatus = status;
                pdelete(mpExpression);
              }

            mUsed = true;
            break;

          case Status::FIXED:
            mStatus = status;
            pdelete(mpExpression);

            mRate = 0.0;

            mUsed = false;
            break;

          case Status::__SIZE:
            success = false;
            break;
        }
    }

  return success;
}

// virtual
const CDataObject * CModelEntity::getValueObject() const
{
  return mpValueReference;
}

// virtual
void * CModelEntity::getValuePointer() const
{
  return const_cast<C_FLOAT64 *>(&mValue);
}

void CModelEntity::initObjects()
{

  mpValueReference =
    static_cast<CDataObjectReference<C_FLOAT64> *>(addObjectReference("Value",
        mValue,
        CDataObject::ValueDbl));

  mpIValueReference =
    static_cast<CDataObjectReference<C_FLOAT64> *>(addObjectReference("InitialValue",
        mIValue,
        CDataObject::ValueDbl));

  mpRateReference =
    static_cast<CDataObjectReference<C_FLOAT64> *>(addObjectReference("Rate", mRate, CDataObject::ValueDbl));

  mpNoiseReference =
    static_cast<CDataObjectReference<C_FLOAT64> *>(addObjectReference("Noise", mNoise, CDataObject::ValueDbl));

  addObjectReference("SBMLId", mSBMLId, CDataObject::ValueString);

  mpModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel)
    {
      mpModel->addModelEntity(this);
    }
}

bool CModelEntity::setObjectParent(const CDataContainer * pParent)
{
  CDataContainer::setObjectParent(pParent);
  CModel * pNewModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel == pNewModel) return true;

  if (mpModel)
    {
      // This allocates new objects for mpIValue and mpValueData
      mpModel->removeModelEntity(this);
    }

  // We can safely remove the currently allocated objects as they
  // are not part of an CStateTemplate
  if (pNewModel)
    {
      pNewModel->addModelEntity(this);
    }

  mpModel = pNewModel;

  return true;
}

void CModelEntity::setSBMLId(const std::string& id) const
{
  this->mSBMLId = id;
}

const std::string& CModelEntity::getSBMLId() const
{
  return this->mSBMLId;
}

void CModelEntity::setUsed(const bool & used)
{mUsed = used;}

const bool & CModelEntity::isUsed() const
{return mUsed;}

//********************************************************************+

// static
CModelValue * CModelValue::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CModelValue(data.getProperty(CData::OBJECT_NAME).toString(),
                         NO_PARENT);
}

// virtual
CData CModelValue::toData() const
{
  CData Data = CModelEntity::toData();

  Data.addProperty(CData::UNIT, mUnitExpression);

  return Data;
}

// virtual
bool CModelValue::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CModelEntity::applyData(data, changes);

  if (data.isSetProperty(CData::UNIT))
    {
      success &= setUnitExpression(data.getProperty(CData::UNIT).toString());
    }

  return success;
}

// virtual
void CModelValue::createUndoData(CUndoData & undoData,
                                 const CUndoData::Type & type,
                                 const CData & oldData,
                                 const CCore::Framework & framework) const
{
  CModelEntity::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  undoData.addProperty(CData::UNIT, oldData.getProperty(CData::UNIT), mUnitExpression);

  return;
}

CModelValue::CModelValue(const std::string & name,
                         const CDataContainer * pParent):
  CModelEntity(name, pParent, "ModelValue")
{
  initObjects();

  CONSTRUCTOR_TRACE;
}

CModelValue::CModelValue(const CModelValue & src,
                         const CDataContainer * pParent):
  CModelEntity(src, pParent)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CModelValue::~CModelValue()
{
  DESTRUCTOR_TRACE;
}

void CModelValue::initObjects()
{}

// virtual
const std::string CModelValue::getUnits() const
{
  return mUnitExpression;
}

std::ostream & operator<<(std::ostream &os, const CModelValue & d)
{
  os << "    ++++CModelValue: " << d.getObjectName() << std::endl;
  os << "        mValue " << d.mValue << " mIValue " << d.mIValue << std::endl;
  os << "        mRate " << d.mRate << " mStatus " << CModelEntity::StatusName[d.getStatus()] << std::endl;
  os << "    ----CModelValue " << std::endl;

  return os;
}
