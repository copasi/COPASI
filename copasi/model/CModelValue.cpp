/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelValue.cpp,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:29:21 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "copasi.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/utility.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "CModel.h"
#include "CModelValue.h"

//static
const std::string CModelEntity::StatusName[] =
  {"fixed", "independent variable modified by reactions", "determined by moieties", "unused", "ode", "assignment", ""};

//static
const char * CModelEntity::XMLStatus[] =
  {"fixed", "variable", "variable", "variable", "ode", "assignment", NULL};
// the "variable" keyword is used for compatibility reasons. It actually means "this metab is part
// of the reaction network, copasi needs to figure out if it is independent, dependent (moieties) or unused."

CModelEntity::CModelEntity(const std::string & name,
                           const CCopasiContainer * pParent,
                           const std::string & type,
                           const unsigned C_INT32 & flag):
    CCopasiContainer(name, pParent, type, (flag | CCopasiObject::Container | CCopasiObject::ValueDbl)),
    mKey(""),
    mpValueAccess(NULL),
    mpValueData(NULL),
    mpIValue(NULL),
    mRate(0.0),
    mStatus(FIXED),
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
    mpValueAccess(NULL),
    mpValueData(NULL),
    mpIValue(NULL),
    mRate(src.mRate),
    mStatus(),
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

  DESTRUCTOR_TRACE;
}

const std::string & CModelEntity::getKey() const {return mKey;}

const C_FLOAT64 & CModelEntity::getValue() const {return *mpValueAccess;}

const C_FLOAT64 & CModelEntity::getInitialValue() const {return *mpIValue;}

const CModelEntity::Status & CModelEntity::getStatus() const {return mStatus;}

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

  std::set< const CCopasiObject * > Dependencies;
  Dependencies.insert(mpValueReference);
  mpRateReference->setDirectDependencies(Dependencies);

  addObjectReference("SBMLId", mSBMLId, CCopasiObject::ValueString);

  mpModel = static_cast<CModel *>(getObjectAncestor("Model"));

  if (mpModel)
    {
      mpModel->getStateTemplate().add(this);

      mpValueReference->setRefresh(mpModel, &CModel::applyAssignments);
      mpRateReference->setRefresh(mpModel, &CModel::refreshRates);
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
      mpValueReference->clearRefresh();
      mpRateReference->clearRefresh();
    }
  else
    {
      pdelete(mpIValue);
      pdelete(mpValueData);
    }

  if (pNewModel)
    {
      pNewModel->getStateTemplate().add(this);
      mpValueReference->setRefresh(pNewModel, &CModel::applyAssignments);
      mpRateReference->setRefresh(pNewModel, &CModel::refreshRates);
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

void CModelEntity::setSBMLId(const std::string& id)
{
  this->mSBMLId = id;
}

const std::string& CModelEntity::getSBMLId() const
  {
    return this->mSBMLId;
  }
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
