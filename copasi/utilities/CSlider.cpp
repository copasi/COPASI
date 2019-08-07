// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "CSlider.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/math/CMathContainer.h"

const char * CSlider::TypeName[] =
{"float", "unsignedFloat", "integer", "unsignedInteger", "Undefined", NULL};

const char * CSlider::ScaleName[] =
{"linear", "logarithmic", "undefined", NULL};

// static
CSlider * CSlider::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CSlider(data.getProperty(CData::OBJECT_NAME).toString(),
                     NO_PARENT);
}

// virtual
CData CSlider::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CSlider::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CSlider::CSlider(const std::string & name,
                 const CDataContainer * pParent):
  CDataContainer(name, pParent, "Slider"),
  mKey(CRootContainer::getKeyFactory()->add("Slider", this)),
  mAssociatedEntityKey(),
  mpSliderObject(NULL),
  mSliderType(Float),
  mValue(0.0),
  mOriginalValue(0.0),
  mMinValue(0),
  mMaxValue(0),
  mTickNumber(1000),
  mTickFactor(100),
  mSync(true),
  mScaling(CSlider::logarithmic),
  mCN(),
  mInitialRefreshes()
{}

CSlider::CSlider(const CSlider & src,
                 const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mKey(CRootContainer::getKeyFactory()->add("Slider", this)),
  mAssociatedEntityKey(src.mAssociatedEntityKey),
  mpSliderObject(src.mpSliderObject),
  mSliderType(src.mSliderType),
  mValue(src.mValue),
  mOriginalValue(src.mOriginalValue),
  mMinValue(src.mMinValue),
  mMaxValue(src.mMaxValue),
  mTickNumber(src.mTickNumber),
  mTickFactor(src.mTickFactor),
  mSync(src.mSync),
  mScaling(src.mScaling),
  mCN(src.mCN),
  mInitialRefreshes(src.mInitialRefreshes)
{}

CSlider::~CSlider()
{CRootContainer::getKeyFactory()->remove(mKey);}

bool CSlider::compile(const CObjectInterface::ContainerList & listOfContainer)
{
  if (getObjectDataModel() == NULL) return false;

  //setSliderObject(CDataContainer::ObjectFromCN(listOfContainer, getObjectName()));
  setSliderObject(CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(listOfContainer, mCN)));

  if (this->mSync) this->sync();

  return (mpSliderObject != NULL);
}

void CSlider::setSynced(bool synced)
{
  this->mSync = synced;
}

bool CSlider::getSynced() const
{
  return this->mSync;
}

const std::string & CSlider::getKey() const
{return mKey;}

bool CSlider::setAssociatedEntityKey(const std::string & associatedEntityKey)
{
  mAssociatedEntityKey = associatedEntityKey;

  return (CRootContainer::getKeyFactory()->get(associatedEntityKey) != NULL);
}

const std::string & CSlider::getAssociatedEntityKey() const
{return mAssociatedEntityKey;}

bool CSlider::setSliderObject(const CDataObject * pObject)
{
  mpSliderObject = const_cast< CDataObject * >(pObject);

  if (!pObject)
    {
      mInitialRefreshes.clear();
      return false;
    }

  mCN = pObject->getCN();

  std::set< const CDataObject * > ChangedObjects;
  ChangedObjects.insert(pObject);

  CDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);
  mInitialRefreshes = pDataModel->getModel()->buildInitialRefreshSequence(ChangedObjects);

  if (mpSliderObject->hasFlag(CDataObject::ValueInt))
    {
      this->setSliderType(Integer);
    }
  else if (mpSliderObject->hasFlag(CDataObject::ValueDbl))
    {
      this->setSliderType(Float);
    }
  else
    {
      this->setSliderType(Undefined);
    }

  if (this->mSync) this->sync();

  C_FLOAT64 value = this->getSliderValue();
  this->mOriginalValue = value;

  if (mOriginalValue <= 0.0)
    mScaling = CSlider::linear;

  if (this->mMinValue > value)
    {
      this->mMinValue = value;
    }

  if (this->mMaxValue < value)
    {
      this->mMaxValue = value;
    }

  return true;
}

void CSlider::resetValue()
{
  this->setSliderValue(this->mOriginalValue);
}

void CSlider::resetRange()
{
  if (this->mSliderType != Undefined)
    {
      C_FLOAT64 value = this->getSliderValue();
      this->mMinValue = value / 10.0;
      this->mMaxValue = value == 0 ? 1.0 :  value * 10.0;
    }
}

bool CSlider::setSliderObject(const CCommonName & objectCN)
{
  //return setObjectName(objectCN);
  mCN = objectCN;
  return true;
}

const CDataObject * CSlider::getSliderObject() const
{return mpSliderObject;}

const std::string & CSlider::getSliderObjectCN() const
{return mCN; /*getObjectName();*/}

bool CSlider::setSliderType(const CSlider::Type type)
{
  mSliderType = type;
  return true;
}

CSlider::Type CSlider::getSliderType() const
{return mSliderType;}

bool CSlider::setOriginalValue(const C_FLOAT64 value)
{
  if (mSliderType != Undefined)
    {
      mOriginalValue = value;

      if (mOriginalValue < this->mMinValue)
        {
          mOriginalValue = this->mMinValue;
        }

      if (mOriginalValue > this->mMaxValue)
        {
          mOriginalValue = this->mMaxValue;
        }

      return true;
    }
  else
    {
      return false;
    }
}

bool CSlider::setSliderValue(const C_FLOAT64 value,
                             const bool & writeToObject)
{
  if (mSliderType != Undefined)
    {
      mValue = value;

      if (mValue < this->mMinValue)
        {
          mValue = this->mMinValue;
        }

      if (mValue > this->mMaxValue)
        {
          mValue = this->mMaxValue;
        }

      if (this->mSync && writeToObject)
        {
          this->writeToObject();
        }

      return true;
    }
  else
    {
      return false;
    }
}

void CSlider::sync()
{
  if (!this->mpSliderObject) return;

  if (mSliderType == CSlider::Integer || mSliderType == CSlider::UnsignedInteger)
    {
      C_INT32* reference =
        (C_INT32*)(((CDataObjectReference<C_INT32>*)mpSliderObject)->getValuePointer());

      mValue = *reference;
    }
  else if (mSliderType == CSlider::Float || mSliderType == CSlider::UnsignedFloat)
    {
      C_FLOAT64* reference =
        (C_FLOAT64*)(((CDataObjectReference<C_FLOAT64>*)mpSliderObject)->getValuePointer());

      mValue = *reference;
    }
}

void CSlider::writeToObject()
{
  if (!mpSliderObject) return;

  if (mpSliderObject->hasFlag(CDataObject::ValueDbl))
    *(C_FLOAT64*)mpSliderObject->getValuePointer() = mValue;
  else if (mpSliderObject->hasFlag(CDataObject::ValueInt))
    *(C_INT32*)mpSliderObject->getValuePointer() = (C_INT32) floor(mValue + 0.5);
  else if (mpSliderObject->hasFlag(CDataObject::ValueBool))
    *(bool*)mpSliderObject->getValuePointer() = (mValue != 0.0);

  CDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);
  CMathContainer & Container = pDataModel->getModel()->getMathContainer();
  Container.applyUpdateSequence(mInitialRefreshes);
  Container.pushInitialState();

  return;
}

const C_FLOAT64 & CSlider::getOriginalValue() const
{
  return this->mOriginalValue;
}

const C_FLOAT64 & CSlider::getSliderValue() const
{
  return this->mValue;
}

bool CSlider::setMinValue(const C_FLOAT64 minValue)
{
  if (mSliderType != Undefined)
    {
      mMinValue = minValue;

      if (mMaxValue < mMinValue)
        {
          mMaxValue = mMinValue;
        }

      if (mpSliderObject && getSliderValue() < mMinValue)
        {
          this->mValue = this->mMinValue;
          this->writeToObject();
        }

      return true;
    }
  else
    {
      return false;
    }
}

const C_FLOAT64 & CSlider::getMinValue() const
{return mMinValue;}

bool CSlider::setMaxValue(const C_FLOAT64 maxValue)
{
  if (mSliderType != Undefined)
    {
      mMaxValue = maxValue;

      if (mMaxValue < mMinValue)
        {
          mMinValue = mMaxValue;
        }

      if (mpSliderObject && getSliderValue() > mMaxValue)
        {
          this->mValue = this->mMaxValue;
          this->writeToObject();
        }

      return true;
    }
  else
    {
      return false;
    }
}

const C_FLOAT64 & CSlider::getMaxValue() const
{return mMaxValue;}

bool CSlider::setTickNumber(const unsigned C_INT32 tickNumber)
{
  mTickNumber = tickNumber;
  return true;
}

unsigned C_INT32 CSlider::getTickNumber() const
{return mTickNumber;}

bool CSlider::setTickFactor(const unsigned C_INT32 tickFactor)
{
  mTickFactor = tickFactor;
  return true;
}

unsigned C_INT32 CSlider::getTickFactor() const
{return mTickFactor;}

CSlider::Scale CSlider::getScaling() const
{
  return this->mScaling;
}

bool CSlider::setScaling(CSlider::Scale scaling)
{
  this->mScaling = scaling;
  return true;
}

CSlider::Scale CSlider::convertScaleNameToScale(const char* scaleName)
{
  if (!strncmp("linear", scaleName, 7))
    {
      return CSlider::linear;
    }
  else if (!strncmp("logarithmic", scaleName, 12))
    {
      return CSlider::logarithmic;
    }
  else
    {
      return CSlider::undefinedScale;
    }
}

const char* CSlider::convertScaleToScaleName(Scale scale) const
{
  if (scale < 0 || scale > CSlider::undefinedScale) return ScaleName[undefinedScale];

  return ScaleName[scale];
}

/**
 * Checks whether the object the slider points to actually
 * exists.
 * Returns true if it does.
 */
bool CSlider::isValid() const
{
  bool result = false;
  // check which object if any belongs to the CN and if it is the same as
  // the pointer currently stored in the slider

  assert(getObjectDataModel() != NULL);
  const CModel* pModel = getObjectDataModel()->getModel();
  assert(pModel != NULL);

  const CDataObject* pObject = CObjectInterface::DataObject(pModel->getObjectFromCN(this->mCN));
  result = (pObject != NULL && pObject == this->mpSliderObject);
  return result;
}
