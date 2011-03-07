// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelValue.cpp,v $
//   $Revision: 1.76 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:30:50 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "CModel.h"
#include "CModelValue.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "function/CExpression.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "utilities/utility.h"
#include "copasi/report/CCopasiRootContainer.h"

//static
const std::string CModelEntity::StatusName[] =
{
  "fixed",
  "assignment",
  "reactions",
  "ode",
  "time",
  ""
};

//static
const char * CModelEntity::XMLStatus[] =
{
  "fixed",
  "assignment",
  "reactions",
  "ode",
  "time",
  NULL
};

// the "variable" keyword is used for compatibility reasons. It actually means "this metab is part
// of the reaction network, copasi needs to figure out if it is independent, dependent (moieties) or unused."

CModelEntity::CModelEntity(const std::string & name,
                           const CCopasiContainer * pParent,
                           const std::string & type,
                           const unsigned C_INT32 & flag):
    CCopasiContainer(name, pParent, type, (flag | CCopasiObject::Container | CCopasiObject::ValueDbl | CCopasiObject::ModelEntity)),
    CAnnotation(),
    mKey(""),
    mpValue(NULL),
    mpIValue(NULL),
    mRate(0.0),
    mpExpression(NULL),
    mpInitialExpression(NULL),
    mStatus(FIXED),
    mUsed(false),
    mpModel(NULL)
{
  initObjects();

  *mpIValue = 1.0;
  *mpValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  CONSTRUCTOR_TRACE;
}

CModelEntity::CModelEntity(const CModelEntity & src,
                           const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    CAnnotation(src),
    mKey(""),
    mpValue(NULL),
    mpIValue(NULL),
    mRate(src.mRate),
    mpExpression(src.mpExpression ? new CExpression(*src.mpExpression, this) : NULL),
    mpInitialExpression(src.mpInitialExpression ? new CExpression(*src.mpInitialExpression, this) : NULL),
    mStatus(FIXED),
    mUsed(false),
    mpModel(NULL)
{
  initObjects();

  setStatus(src.mStatus);

  *mpValue = *src.mpValue;
  *mpIValue = *src.mpIValue;

  setMiriamAnnotation(src.getMiriamAnnotation(), mKey, src.mKey);
}

CModelEntity::~CModelEntity()
{
  if (mpModel)
    mpModel->getStateTemplate().remove(this);

  // After the above call we definitely own the data and
  // therefore must destroy them.

  pdelete(mpValue);
  pdelete(mpIValue);
  // since the expressions now have the model entity as parent, they should
  // automatically be destroyed be the destructor of CCopasiContainer
  //pdelete(mpExpression);
  //pdelete(mpInitialExpression);

  DESTRUCTOR_TRACE;
}

const std::string & CModelEntity::getKey() const {return mKey;}

const C_FLOAT64 & CModelEntity::getValue() const {return *mpValue;}

const C_FLOAT64 & CModelEntity::getInitialValue() const
{return *mpIValue;}

const CModelEntity::Status & CModelEntity::getStatus() const {return mStatus;}

bool CModelEntity::compile()
{
  bool success = true;

  std::set< const CCopasiObject * > NoDependencies;
  std::vector< CCopasiContainer * > listOfContainer;
  listOfContainer.push_back(mpModel);
  CCopasiDataModel* pDataModel = NULL;

  switch (mStatus)
    {
      case ASSIGNMENT:
        success &= mpExpression->compile(listOfContainer);
        mpValueReference->setDirectDependencies(mpExpression->getDirectDependencies());

        pdelete(mpInitialExpression);
        pDataModel = getObjectDataModel();
        assert(pDataModel != NULL);
        mpInitialExpression = CExpression::createInitialExpression(*mpExpression, pDataModel);
        mpInitialExpression->setObjectName("InitialExpression");
        add(mpInitialExpression, true);
        break;

      case ODE:
        mpValueReference->addDirectDependency(this);

        success &= mpExpression->compile(listOfContainer);
        mpRateReference->setDirectDependencies(mpExpression->getDirectDependencies());

      default:
        break;
    }

  // Here we handle initial expressions for all types.
  if (mpInitialExpression != NULL &&
      mpInitialExpression->getInfix() != "")
    {
      success &= mpInitialExpression->compile(listOfContainer);
      mpIValueReference->setDirectDependencies(mpInitialExpression->getDirectDependencies());

      // If we have constant initial expression, we update the initial value.
      if (mpInitialExpression->isUsable() &&
          mpIValueReference->getDirectDependencies().size() == 0)
        *mpIValue = mpInitialExpression->calcValue();
    }
  else
    {
      mpIValueReference->setDirectDependencies(NoDependencies);
    }

  return success;
}

void CModelEntity::calculate()
{
  switch (mStatus)
    {
      case ASSIGNMENT:
        *mpValue = mpExpression->calcValue();
        break;

      case ODE:
        mRate = mpExpression->calcValue();
        break;

      default:
        break;
    }
}

void CModelEntity::refreshInitialValue()
{
  if (mpInitialExpression != NULL &&
      mpInitialExpression->getInfix() != "")
    *mpIValue = mpInitialExpression->calcValue();
}

bool CModelEntity::setExpression(const std::string & expression)
{
  if (isFixed()) return false;

  if (mpExpression == NULL)
    mpExpression = new CExpression("Expression", this);

  if (mpModel)
    mpModel->setCompileFlag(true);

  if (!mpExpression->setInfix(expression)) return false;

  return compile();
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
  return mpExpression;
}

const CExpression* CModelEntity::getExpressionPtr() const
{
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
  return mpInitialExpression;
}

const CExpression* CModelEntity::getInitialExpressionPtr() const
{
  return mpInitialExpression;
}

bool CModelEntity::setInitialExpressionPtr(CExpression* pExpression)
{
  if (mStatus == ASSIGNMENT) return false;

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

bool CModelEntity::setInitialExpression(const std::string & expression)
{
  if (mStatus == ASSIGNMENT) return false;

  if (mpModel)
    mpModel->setCompileFlag(true);

  if (mpInitialExpression == NULL)
    {
      mpInitialExpression = new CExpression("InitialExpression", this);
    }

  if (!mpInitialExpression->setInfix(expression)) return false;

  return compile();
}

std::string CModelEntity::getInitialExpression() const
{
  if (mStatus == ASSIGNMENT || mpInitialExpression == NULL)
    return "";

  mpInitialExpression->updateInfix();
  return mpInitialExpression->getInfix();
}

/**
 * Return rate of production of this entity
 */
const C_FLOAT64 & CModelEntity::getRate() const
{
  return mRate;
}

CCopasiObject * CModelEntity::getInitialValueReference() const
{return mpIValueReference;}

CCopasiObject * CModelEntity::getValueReference() const
{return mpValueReference;}

CCopasiObject * CModelEntity::getRateReference() const
{return mpRateReference;}

//***********

void CModelEntity::setValue(const C_FLOAT64 & value)
{
  if (mStatus == FIXED) return;

  *mpValue = value;
}

void CModelEntity::setInitialValue(const C_FLOAT64 & initialValue)
{
  *mpIValue = initialValue;
}

void CModelEntity::setRate(const C_FLOAT64 & rate)
{
  mRate = rate;
}

//  ******************

void CModelEntity::setStatus(const CModelEntity::Status & status)
{
  if (mStatus != status)
    {
      if (mpModel != NULL)
        mpModel->setCompileFlag(true);

      // An assignment may not have an initial expression.
      // However, internally we always create one, which need
      // to be deleted.
      if (mStatus == ASSIGNMENT)
        pdelete(mpInitialExpression);

      mStatus = status;
      this->setValuePtr(mpValue);

      if (mpModel != NULL)
        mpModel->setCompileFlag(true);

      std::set< const CCopasiObject * > NoDependencies;

      setDirectDependencies(NoDependencies);
      clearRefresh();

      mpIValueReference->setDirectDependencies(NoDependencies);

      mpValueReference->setDirectDependencies(NoDependencies);
      mpValueReference->clearRefresh();

      mpRateReference->setDirectDependencies(NoDependencies);
      mpRateReference->clearRefresh();
      CCopasiDataModel* pDataModel = NULL;

      switch (mStatus)
        {
          case ASSIGNMENT:

            if (mpExpression == NULL)
              mpExpression = new CExpression("Expression", this);

            pdelete(mpInitialExpression);
            pDataModel = getObjectDataModel();
            mpInitialExpression = CExpression::createInitialExpression(*mpExpression, pDataModel);
            mpInitialExpression->setObjectName("InitialExpression");
            add(mpInitialExpression, true);

            mpValueReference->setDirectDependencies(mpExpression->getDirectDependencies());
            mpValueReference->setRefresh(this, &CModelEntity::calculate);

            mRate = std::numeric_limits<C_FLOAT64>::quiet_NaN();

            mUsed = true;
            break;

          case ODE:

            if (mpExpression == NULL)
              mpExpression = new CExpression("Expression", this);

            mpRateReference->setDirectDependencies(mpExpression->getDirectDependencies());
            mpRateReference->setRefresh(this, &CModelEntity::calculate);

            mUsed = true;
            break;

          case REACTIONS:
            pdelete(mpExpression);

            mUsed = true;
            break;

          case TIME:
            pdelete(mpExpression);

            mUsed = true;
            break;

          case FIXED:
            pdelete(mpExpression);

            mRate = 0.0;

            mUsed = false;
            break;
        }
    }
}

// virtual
const CCopasiObject * CModelEntity::getValueObject() const
{
  return mpValueReference;
}

// virtual
void * CModelEntity::getValuePointer() const
{
  return const_cast<C_FLOAT64 *>(mpValue);
}

void CModelEntity::initObjects()
{
  C_FLOAT64 Dummy;

  mpValueReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("Value",
        Dummy,
        CCopasiObject::ValueDbl));
  mpValueReference->setUpdateMethod(this, &CModelEntity::setValue);

  mpIValueReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("InitialValue",
        Dummy,
        CCopasiObject::ValueDbl));
  mpIValueReference->setUpdateMethod(this, &CModelEntity::setInitialValue);
  mpIValueReference->setRefresh(this, &CModelEntity::refreshInitialValue);

  mpRateReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("Rate", mRate, CCopasiObject::ValueDbl));

  addObjectReference("SBMLId", mSBMLId, CCopasiObject::ValueString);

  mpModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel)
    {
      mpModel->getStateTemplate().add(this);
    }
  else
    {
      // This creates the needed values.
      setInitialValuePtr(NULL);
      setValuePtr(NULL);
    }
}

void CModelEntity::setInitialValuePtr(C_FLOAT64 * pInitialValue)
{
  mpIValue = pInitialValue;

  if (!mpIValue) mpIValue = new C_FLOAT64;

  mpIValueReference->setReference(*mpIValue);
}

void CModelEntity::setValuePtr(C_FLOAT64 * pValue)
{
  mpValue = pValue;

  if (!mpValue) mpValue = new C_FLOAT64;

  mpValueReference->setReference(*mpValue);
}

bool CModelEntity::setObjectParent(const CCopasiContainer * pParent)
{
  CCopasiContainer::setObjectParent(pParent);
  CModel * pNewModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel == pNewModel) return true;

  C_FLOAT64 InitialValue = *mpIValue;
  C_FLOAT64 Value = *mpValue;

  if (mpModel)
    {
      // This allocates new objects for mpIValue and mpValueData
      mpModel->getStateTemplate().remove(this);
    }

  // We can safely remove the currently allocated objects as they
  // are not part of an CStateTemplate
  pdelete(mpIValue);
  pdelete(mpValue);

  if (pNewModel)
    {
      pNewModel->getStateTemplate().add(this);
    }
  else
    {
      mpValue = new C_FLOAT64;
      mpIValue = new C_FLOAT64;
    }

  mpModel = pNewModel;
  *mpIValue = InitialValue;
  *mpValue = Value;

  return true;
}

std::set< const CCopasiObject * > CModelEntity::getDeletedObjects() const
{
  std::set< const CCopasiObject * > Deleted;

  Deleted.insert(this);
  Deleted.insert(mpIValueReference);
  Deleted.insert(mpValueReference);
  Deleted.insert(mpRateReference);

  return Deleted;
}

void CModelEntity::setSBMLId(const std::string& id)
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

CModelValue::CModelValue(const std::string & name,
                         const CCopasiContainer * pParent):
    CModelEntity(name, pParent, "ModelValue")
{
  mKey = CCopasiRootContainer::getKeyFactory()->add("ModelValue", this);
  initObjects();

  CONSTRUCTOR_TRACE;
}

CModelValue::CModelValue(const CModelValue & src,
                         const CCopasiContainer * pParent):
    CModelEntity(src, pParent)
{
  mKey = CCopasiRootContainer::getKeyFactory()->add("ModelValue", this);
  initObjects();
  CONSTRUCTOR_TRACE;
}

CModelValue::~CModelValue()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);

  DESTRUCTOR_TRACE;
}

void CModelValue::initObjects()
{}

std::ostream & operator<<(std::ostream &os, const CModelValue & d)
{
  os << "    ++++CModelValue: " << d.getObjectName() << std::endl;
  os << "        mValue " << *d.mpValue << " mIValue " << *d.mpIValue << std::endl;
  os << "        mRate " << d.mRate << " mStatus " << d.getStatus() << std::endl;
  os << "    ----CModelValue " << std::endl;

  return os;
}
