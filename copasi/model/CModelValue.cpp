/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelValue.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/05/27 16:06:54 $
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
  {"fixed", "independent variable modified by reactions", "determined by moieties", "ode", "assignment", "unused", ""};

//static
const char * CModelEntity::XMLStatus[] =
  {"fixed", "variable", "variable", "ode", "assignment", "variable", NULL};
// the "variable" keyword is used for compatibility reasons. It actually means "this metab is part
// of the reaction network, copasi needs to figure out if it is independent, dependent (moieties) or unused."

CModelEntity::CModelEntity(const std::string & name,
                           const CCopasiContainer * pParent,
                           const std::string & type,
                           const unsigned C_INT32 & flag):
    CCopasiContainer(name, pParent, type, flag),
    mValue(0.0),
    mIValue(0.0),
    mRate(0.0),
    //    mTT(0.0),
    mStatus(FIXED)
{
  //initObjects();
  CONSTRUCTOR_TRACE;
}

CModelEntity::CModelEntity(const CModelEntity & src,
                           const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mValue(src.mValue),
    mIValue(src.mIValue),
    mRate(src.mRate),
    //    mTT(src.mTT),
    mStatus(src.mStatus)
{
  //initObjects();
  CONSTRUCTOR_TRACE;
}

CModelEntity::~CModelEntity()
{
  DESTRUCTOR_TRACE;
}

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

//********************************************************************+

CModelValue::CModelValue(const std::string & name,
                         const CCopasiContainer * pParent):
    CModelEntity(name, pParent, "ModelValue"),
    mKey(GlobalKeys.add("ModelValue", this))
    //    mTT(0.0),
{
  mStatus = FIXED;
  initObjects();
  CONSTRUCTOR_TRACE;
}

CModelValue::CModelValue(const CModelValue & src,
                         const CCopasiContainer * pParent):
    CModelEntity(src, pParent),
    mKey(GlobalKeys.add("ModelValue", this))
    //    mTT(src.mTT),
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CModelValue::~CModelValue()
{
  GlobalKeys.remove(mKey);
  DESTRUCTOR_TRACE;
}

void CModelValue::cleanup() {}

/*void CModelValue::initModel()
{
  mpModel = dynamic_cast< CModel * >(getObjectAncestor("Model"));
  if (!mpModel && CCopasiDataModel::Global) mpModel = CCopasiDataModel::Global->getModel();
}*/

const std::string & CModelValue::getKey() const {return mKey;}

//const CModel * CModelValue::getModel() const {return mpModel;}

/*bool CModelValue::setObjectParent(const CCopasiContainer * pParent)
{
  CCopasiObject::setObjectParent(pParent);
 
  initCompartment(NULL);
  initModel();
 
  return true;
}*/

// ***** set quantities ********

void CModelValue::setValue(const C_FLOAT64 v)
{
  mValue = v;

#ifdef COPASI_DEBUG
  //if (mStatus == METAB_FIXED)
  //std::cout << "warning: set the transient concentration on a fixed metab" << std::endl;
#endif
}

bool CModelValue::setInitialValue(const C_FLOAT64 & iV)
{
  //if (mIConc == initialConcentration) return true;

  mIValue = iV;

  if (mStatus == FIXED)
    setValue(iV);

  return true;
}

//  ******************

void CModelValue::setStatus(const CModelValue::Status & status)
{
  mStatus = status;
}

//void CModelValue::setModel(CModel * model) {mpModel = model;}

void CModelValue::initObjects()
{
  CCopasiObject * pObject;

  addObjectReference("Value", mValue, CCopasiObject::ValueDbl);
  pObject = addObjectReference("InitialValue", mIValue, CCopasiObject::ValueDbl);
  //pObject->setUpdateMethod(this, &CModelValue::setInitialConcentration);
  //addObjectReference("TransitionTime", mTT, CCopasiObject::ValueDbl);
}

void CModelValue::setRate(const C_FLOAT64 & rate)
{mRate = rate;}

void * CModelValue::getReference() const
  {return const_cast<C_FLOAT64 *>(&mValue);}

std::ostream & operator<<(std::ostream &os, const CModelValue & d)
{
  os << "    ++++CModelValue: " << d.getObjectName() << std::endl;
  os << "        mValue " << d.mValue << " mIValue " << d.mIValue << std::endl;
  os << "        mRate " << d.mRate << " mStatus " << d.mStatus << std::endl;
  os << "    ----CModelValue " << std::endl;

  return os;
}

/*std::string CModelValue::getObjectDisplayName(bool regular, bool richtext) const
  {
    CModel* tmp = dynamic_cast<CModel*>(this->getObjectAncestor("Model"));
    if (tmp)
      {
        return CModelValueNameInterface::getDisplayName(tmp, *this);
      }
 
    return CCopasiObject::getObjectDisplayName(regular, richtext);
  }*/
