/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelValue.cpp,v $
   $Revision: 1.34 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/05 13:04:16 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

//static
const std::string CModelEntity::StatusName[] =
  {
    "fixed",
    "assignment",
    "determined by reactions",
    "ode",
    ""
  };

//static
const char * CModelEntity::XMLStatus[] =
  {
    "fixed",
    "assignment",
    "reactions",
    "ode",
    NULL
  };

// the "variable" keyword is used for compatibility reasons. It actually means "this metab is part
// of the reaction network, copasi needs to figure out if it is independent, dependent (moieties) or unused."

CModelEntity::CModelEntity(const std::string & name,
                           const CCopasiContainer * pParent,
                           const std::string & type,
                           const unsigned C_INT32 & flag):
    CCopasiContainer(name, pParent, type, (flag | CCopasiObject::Container | CCopasiObject::ValueDbl | CCopasiObject::ModelEntity)),
    mKey(""),
    mpValueData(NULL),
    mpValueAccess(NULL),
    mpIValue(NULL),
    mRate(0.0),
    mpExpression(NULL),
    mpInitialExpression(NULL),
    mStatus(FIXED),
    mUsed(false),
    mUsedOnce(false),
    mpModel(NULL)
{
  initObjects();

  *mpIValue = 1.0;
  *mpValueData = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  CONSTRUCTOR_TRACE;
}

CModelEntity::CModelEntity(const CModelEntity & src,
                           const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(""),
    mpValueData(NULL),
    mpValueAccess(NULL),
    mpIValue(NULL),
    mRate(src.mRate),
    mpExpression(new CExpression(*src.mpExpression)),
    mpInitialExpression(new CExpression(*src.mpInitialExpression)),
    mStatus(FIXED),
    mUsed(false),
    mUsedOnce(false),
    mpModel(NULL)
{
  initObjects();

  setStatus(src.mStatus);

  *mpValueData = *src.mpValueData;
  *mpIValue = *src.mpIValue;

  CONSTRUCTOR_TRACE;
}

CModelEntity::~CModelEntity()
{
  if (mpModel)
    mpModel->getStateTemplate().remove(this);

  // After the above call we definitely own the data and
  // therfore must destroy them.

  pdelete(mpValueData);
  pdelete(mpIValue);
  pdelete(mpExpression);
  pdelete(mpInitialExpression);

  DESTRUCTOR_TRACE;
}

const std::string & CModelEntity::getKey() const {return mKey;}

const C_FLOAT64 & CModelEntity::getValue() const {return *mpValueAccess;}

const C_FLOAT64 & CModelEntity::getInitialValue() const {return *mpIValue;}

const CModelEntity::Status & CModelEntity::getStatus() const {return mStatus;}

bool CModelEntity::compile()
{
  if (isFixed()) return true;

  std::vector< CCopasiContainer * > listOfContainer;
  listOfContainer.push_back(getObjectAncestor("Model"));

  bool success = mpExpression->compile(listOfContainer);

  setDirectDependencies(mpExpression->getDirectDependencies());

  return success;
}

void CModelEntity::calculate()
{
  switch (getStatus())
    {
    case ASSIGNMENT:
      *mpValueData = mpExpression->calcValue();
      break;

    case ODE:
      mRate = mpExpression->calcValue();
      break;

    default:
      break;
    }
}

bool CModelEntity::setExpression(const std::string & expression)
{
  if (isFixed()) return false;

  if (mpExpression == NULL)
    mpExpression = new CExpression;

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

bool CModelEntity::setExpressionPtr(CExpression* pExpression)
{
  if (isFixed()) return false;

  if (mpExpression)
    pdelete(mpExpression);

  mpExpression = pExpression;

  if (mpModel)
    mpModel->setCompileFlag(true);

  return compile();
}

bool CModelEntity::setInitialExpression(const std::string & expression)
{
  if (mStatus == ASSIGNMENT) return false;

  if (mpInitialExpression == NULL)
    mpInitialExpression = new CExpression;

  return mpInitialExpression->setInfix(expression);
}

std::string CModelEntity::getInitialExpression() const
  {
    if (mStatus == ASSIGNMENT || mpInitialExpression == NULL)
      return "";

    return mpInitialExpression->getInfix();
  }

/**
 * Return rate of production of this entity
 */
const C_FLOAT64 & CModelEntity::getRate() const
  {
    return mRate;
  }

//***********

void CModelEntity::setValue(const C_FLOAT64 & value)
{
  if (mStatus == FIXED) return;

  *mpValueData = value;

#ifdef COPASI_DEBUG
  //if (mStatus == FIXED)
  //std::cout << "warning: set the transient concentration on a fixed entity" << std::endl;
#endif
}

void CModelEntity::setInitialValue(const C_FLOAT64 & initialValue)
{
  *mpIValue = initialValue;

  if (mStatus != FIXED) return;
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
      mStatus = status;
      this->setValuePtr(mpValueData);

      if (mpModel != NULL)
        mpModel->setCompileFlag(true);

      std::set< const CCopasiObject * > NoDependencies;
      std::set< const CCopasiObject * > Self;
      Self.insert(this);

      switch (getStatus())
        {
        case ASSIGNMENT:
          if (mpExpression == NULL)
            mpExpression = new CExpression;
          pdelete(mpInitialExpression)
          setDirectDependencies(mpExpression->getDirectDependencies());
          setRefresh(this, &CModelEntity::calculate);
          mpValueReference->setDirectDependencies(Self);
          mpRateReference->setDirectDependencies(NoDependencies);
          mUsed = true;
          mUsedOnce = false;
          break;

        case ODE:
          if (mpExpression == NULL)
            mpExpression = new CExpression;
          if (mpInitialExpression == NULL)
            mpInitialExpression = new CExpression;
          setDirectDependencies(mpExpression->getDirectDependencies());
          setRefresh(this, &CModelEntity::calculate);
          mpValueReference->setDirectDependencies(NoDependencies);
          mpRateReference->setDirectDependencies(Self);
          mUsed = true;
          mUsedOnce = false;
          break;

        case REACTIONS:
          pdelete(mpExpression);
          if (mpInitialExpression == NULL)
            mpInitialExpression = new CExpression;
          setDirectDependencies(NoDependencies);
          clearRefresh();
          mpValueReference->setDirectDependencies(NoDependencies);
          mpRateReference->setDirectDependencies(NoDependencies);
          mUsed = true;
          mUsedOnce = false;
          break;

        case TIME:
          pdelete(mpExpression);
          if (mpInitialExpression == NULL)
            mpInitialExpression = new CExpression;
          setDirectDependencies(NoDependencies);
          clearRefresh();
          mpValueReference->setDirectDependencies(NoDependencies);
          mpRateReference->setDirectDependencies(NoDependencies);
          mUsed = true;
          mUsedOnce = false;
          break;

        case FIXED:
          pdelete(mpExpression);
          if (mpInitialExpression == NULL)
            mpInitialExpression = new CExpression;
          setDirectDependencies(NoDependencies);
          clearRefresh();
          mpValueReference->setDirectDependencies(NoDependencies);
          mpRateReference->setDirectDependencies(NoDependencies);
          mUsed = false;
          mUsedOnce = false;
          break;
        }
    }
}

void * CModelEntity::getValuePointer() const
{return const_cast<C_FLOAT64 *>(mpValueAccess);}

void CModelEntity::initObjects()
{
  C_FLOAT64 Dummy;

  mpValueReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("Value",
        Dummy,
        CCopasiObject::ValueDbl));
  mpIValueReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("InitialValue",
        Dummy,
        CCopasiObject::ValueDbl));

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
  mpValueData = pValue;
  if (!mpValueData) mpValueData = new C_FLOAT64;

  if (mStatus == FIXED)
    mpValueAccess = mpIValue;
  else
    mpValueAccess = mpValueData;

  mpValueReference->setReference(*mpValueAccess);
}

bool CModelEntity::setObjectParent(const CCopasiContainer * pParent)
{
  CCopasiContainer::setObjectParent(pParent);
  CModel * pNewModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel == pNewModel) return true;

  C_FLOAT64 InitialValue = *mpIValue;
  C_FLOAT64 Value = *mpValueData;

  if (mpModel)
    {
      mpModel->getStateTemplate().remove(this);
    }
  else
    {
      pdelete(mpIValue);
      pdelete(mpValueData);
    }

  if (pNewModel)
    {
      pNewModel->getStateTemplate().add(this);
    }
  else
    {
      mpValueData = new C_FLOAT64;
      mpIValue = new C_FLOAT64;
    }

  mpModel = pNewModel;
  *mpIValue = InitialValue;
  *mpValueData = Value;

  return true;
}

std::set< const CCopasiObject * > CModelEntity::getDeletedObjects() const
  {
    std::set< const CCopasiObject * > Deleted;

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

void CModelEntity::setUsedOnce(const bool & usedOnce)
{mUsedOnce = usedOnce;}

const bool & CModelEntity::isUsedOnce() const
  {return mUsedOnce;}

//********************************************************************+

CModelValue::CModelValue(const std::string & name,
                         const CCopasiContainer * pParent):
    CModelEntity(name, pParent, "ModelValue")
{
  mKey = GlobalKeys.add("ModelValue", this);
  initObjects();

  CONSTRUCTOR_TRACE;
}

CModelValue::CModelValue(const CModelValue & src,
                         const CCopasiContainer * pParent):
    CModelEntity(src, pParent)
{
  mKey = GlobalKeys.add("ModelValue", this);
  initObjects();
  CONSTRUCTOR_TRACE;
}

CModelValue::~CModelValue()
{
  GlobalKeys.remove(mKey);

  DESTRUCTOR_TRACE;
}

void CModelValue::initObjects()
{}

std::ostream & operator<<(std::ostream &os, const CModelValue & d)
{
  os << "    ++++CModelValue: " << d.getObjectName() << std::endl;
  os << "        mValue " << *d.mpValueAccess << " mIValue " << *d.mpIValue << std::endl;
  os << "        mRate " << d.mRate << " mStatus " << d.getStatus() << std::endl;
  os << "    ----CModelValue " << std::endl;

  return os;
}
