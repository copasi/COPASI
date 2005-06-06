/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelValue.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/06/06 14:51:33 $
   End CVS Header */

#include <iostream>
#include <string>
#include <vector>

#define  COPASI_TRACE_CONSTRUCTION

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
    CCopasiContainer(name, pParent, type, flag),
    mKey(""),
    mValue(0.0),
    mIValue(0.0),
    mRate(0.0),
    //    mTT(0.0),
    mStatus(FIXED)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CModelEntity::CModelEntity(const CModelEntity & src,
                           const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(""),
    mValue(src.mValue),
    mIValue(src.mIValue),
    mRate(src.mRate),
    //    mTT(src.mTT),
    mStatus(src.mStatus)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CModelEntity::~CModelEntity()
{
  DESTRUCTOR_TRACE;
}

const std::string & CModelEntity::getKey() const {return mKey;}

const C_FLOAT64 & CModelEntity::getValue() const {return mValue;}

const C_FLOAT64 & CModelEntity::getInitialValue() const {return mIValue;}

const CModelEntity::Status & CModelEntity::getStatus() const {return mStatus;}

/**
 * Return rate of production of this entity
 */
const C_FLOAT64 & CModelEntity::getRate() const
  {
    return mRate;
  }

//***********

void CModelEntity::setValue(const C_FLOAT64 v)
{
  mValue = v;

#ifdef COPASI_DEBUG
  //if (mStatus == FIXED)
  //std::cout << "warning: set the transient concentration on a fixed entity" << std::endl;
#endif
}

bool CModelEntity::setInitialValue(const C_FLOAT64 & iV)
{
  //if (mIConc == initialConcentration) return true;

  mIValue = iV;

  if (mStatus == FIXED)
    setValue(iV);

  return true;
}

void CModelEntity::setRate(const C_FLOAT64 & rate)
{
  mRate = rate;
}

//  ******************

void CModelEntity::setStatus(const CModelValue::Status & status)
{
  mStatus = status;
  if (mStatus == FIXED)
    {
      setValue(getInitialValue());
    }
}

void * CModelEntity::getReference() const
  {return const_cast<C_FLOAT64 *>(&mValue);}

void CModelEntity::initObjects()
{
  addObjectReference("Value", mValue, CCopasiObject::ValueDbl);
  addObjectReference("InitialValue", mIValue, CCopasiObject::ValueDbl);
  addObjectReference("Rate", mRate, CCopasiObject::ValueDbl);
}

//********************************************************************+

CModelValue::CModelValue(const std::string & name,
                         const CCopasiContainer * pParent):
    CModelEntity(name, pParent, "ModelValue")
{
  mKey = GlobalKeys.add("ModelValue", this);
  mStatus = FIXED;
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
{
  //CCopasiObject * pObject;

  //addObjectReference("Value", mValue, CCopasiObject::ValueDbl);
  //pObject = addObjectReference("InitialValue", mIValue, CCopasiObject::ValueDbl);
  //pObject->setUpdateMethod(this, &CModelValue::setInitialConcentration);
  //addObjectReference("TransitionTime", mTT, CCopasiObject::ValueDbl);
}

std::ostream & operator<<(std::ostream &os, const CModelValue & d)
{
  os << "    ++++CModelValue: " << d.getObjectName() << std::endl;
  os << "        mValue " << d.mValue << " mIValue " << d.mIValue << std::endl;
  os << "        mRate " << d.mRate << " mStatus " << d.mStatus << std::endl;
  os << "    ----CModelValue " << std::endl;

  return os;
}
