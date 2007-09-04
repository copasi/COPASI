// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSlider.cpp,v $
//   $Revision: 1.24 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/09/04 20:28:35 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"
#include "mathematics.h"

#include "CSlider.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiObjectReference.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

const char * CSlider::TypeName[] =
  {"float", "unsignedFloat", "integer", "unsignedInteger", "Undefined", NULL};

const char * CSlider::ScaleName[] =
  {"linear", "logarithmic", "undefined", NULL};

CSlider::CSlider(const std::string & name,
                 const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Slider"),
    mKey(GlobalKeys.add("Slider", this)),
    mAssociatedEntityKey(),
    mpSliderObject(NULL),
    mSliderType(Float),
    mValue(0.0),
    mMinValue(0),
    mMaxValue(0),
    mTickNumber(1000),
    mTickFactor(100),
    mSync(true),
    mScaling(CSlider::linear),
    mCN(),
    mInitialRefreshes()
{}

CSlider::CSlider(const CSlider & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Slider", this)),
    mAssociatedEntityKey(src.mAssociatedEntityKey),
    mpSliderObject(src.mpSliderObject),
    mSliderType(src.mSliderType),
    mValue(src.mValue),
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
{GlobalKeys.remove(mKey);}

bool CSlider::compile(const std::vector< CCopasiContainer * > & listOfContainer)
{
  //setSliderObject(CCopasiContainer::ObjectFromName(listOfContainer, getObjectName()));
  setSliderObject(CCopasiContainer::ObjectFromName(listOfContainer, mCN));
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

  return (GlobalKeys.get(associatedEntityKey) != NULL);
}

const std::string & CSlider::getAssociatedEntityKey() const
  {return mAssociatedEntityKey;}

bool CSlider::setSliderObject(CCopasiObject * pObject)
{
  mpSliderObject = pObject;

  if (!pObject)
    {
      mInitialRefreshes.clear();
      return false;
    }
  mCN = pObject->getCN();

  std::set< const CCopasiObject * > ChangedObjects;
  ChangedObjects.insert(pObject);

  mInitialRefreshes =
    CCopasiDataModel::Global->getModel()->buildInitialRefreshSequence(ChangedObjects);

  if (mpSliderObject->isValueInt())
    {
      this->setSliderType(Integer);
    }
  else if (mpSliderObject->isValueDbl())
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
      this->mMinValue = value / 2.0;
      this->mMaxValue = value * 2.0;
    }
}

bool CSlider::setSliderObject(const CCopasiObjectName & objectCN)
{
  //return setObjectName(objectCN);
  mCN = objectCN;
  return true;
}

CCopasiObject * CSlider::getSliderObject()
{return mpSliderObject;}

const std::string & CSlider::getSliderObjectCN() const
  {return mCN; /*getObjectName();*/}

bool CSlider::setSliderType(const CSlider::Type type)
{
  mSliderType = type;
  return true;
}

const CSlider::Type CSlider::getSliderType() const
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
        (C_INT32*)(((CCopasiObjectReference<C_INT32>*)mpSliderObject)->getValuePointer());

      mValue = *reference;
    }
  else if (mSliderType == CSlider::Float || mSliderType == CSlider::UnsignedFloat)
    {
      C_FLOAT64* reference =
        (C_FLOAT64*)(((CCopasiObjectReference<C_FLOAT64>*)mpSliderObject)->getValuePointer());

      mValue = *reference;
    }
}

void CSlider::writeToObject()
{
  if (!mpSliderObject) return;

  if (mpSliderObject->isValueDbl())
    mpSliderObject->setObjectValue(mValue);
  else if (mpSliderObject->isValueInt())
    mpSliderObject->setObjectValue((C_INT32) floor(mValue + 0.5));
  else if (mpSliderObject->isValueBool())
    mpSliderObject->setObjectValue(mValue != 0.0);

  std::vector< Refresh * >::iterator it = mInitialRefreshes.begin();
  std::vector< Refresh * >::iterator end = mInitialRefreshes.end();

  for (; it != end; ++it)
    (**it)();

  return;
}

const C_FLOAT64 CSlider::getOriginalValue() const
  {
    return this->mOriginalValue;
  }

const C_FLOAT64 CSlider::getSliderValue() const
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

const C_FLOAT64 CSlider::getMinValue() const
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

const C_FLOAT64 CSlider::getMaxValue() const
  {return mMaxValue;}

bool CSlider::setTickNumber(const unsigned C_INT32 tickNumber)
{
  mTickNumber = tickNumber;
  return true;
}

const unsigned C_INT32 CSlider::getTickNumber() const
  {return mTickNumber;}

bool CSlider::setTickFactor(const unsigned C_INT32 tickFactor)
{
  mTickFactor = tickFactor;
  return true;
}

const unsigned C_INT32 CSlider::getTickFactor() const
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

const char* CSlider::convertScaleToScaleName(Scale scale)
{
  if (scale < 0 || scale > CSlider::undefinedScale) return ScaleName[undefinedScale];
  return ScaleName[scale];
}
