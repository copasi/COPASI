/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSlider.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/03/23 18:58:37 $
   End CVS Header */

#include "copasi.h"
#include "mathematics.h"

#include "CSlider.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiObjectReference.h"

const char * CSlider::TypeName[] =
  {"float", "unsignedFloat", "integer", "unsignedInteger", NULL};

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
    mScaling(CSlider::linear)
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
    mScaling(src.mScaling)
{}

CSlider::~CSlider()
{GlobalKeys.remove(mKey);}

bool CSlider::compile(const std::vector< CCopasiContainer * > & listOfContainer)
{
  mpSliderObject = CCopasiContainer::ObjectFromName(listOfContainer, getObjectName());
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
  if (!setObjectName(pObject->getCN())) return false;

  mpSliderObject = pObject;
  if (this->mSync) this->sync();
  this->resetRange();
  return true;
}

void CSlider::resetRange()
{
  C_FLOAT64 value = this->getSliderValue();
  this->mMinValue = value / 2.0;
  this->mMaxValue = value * 2.0;
}

bool CSlider::setSliderObject(const CCopasiObjectName & objectCN)
{return setObjectName(objectCN);}

CCopasiObject * CSlider::getSliderObject()
{return mpSliderObject;}

const std::string & CSlider::getSliderObjectCN() const
  {return getObjectName();}

bool CSlider::setSliderType(const CSlider::Type type)
{
  mSliderType = type;
  return true;
}

const CSlider::Type CSlider::getSliderType() const
  {return mSliderType;}

bool CSlider::setSliderValue(const C_FLOAT64 value,
                             const bool & writeToObject)
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

void CSlider::sync()
{
  if (!this->mpSliderObject) return;
  if (mSliderType == CSlider::Integer || mSliderType == CSlider::UnsignedInteger)
    {
      C_INT32* reference = (C_INT32*)(((CCopasiObjectReference<C_INT32>*)mpSliderObject)->getReference());

      mValue = *reference;
    }
  else if (mSliderType == CSlider::Float || mSliderType == CSlider::UnsignedFloat)
    {
      C_FLOAT64* reference = (C_FLOAT64*)(((CCopasiObjectReference<C_FLOAT64>*)mpSliderObject)->getReference());

      mValue = *reference;
    }
}

void CSlider::writeToObject()
{
  if (!this->mpSliderObject) return;

  if (mpSliderObject->setObjectValue(mValue)) return;

  if (mpSliderObject->setObjectValue((C_INT32)floor(mValue + 0.5))) return;

  if (mpSliderObject->setObjectValue(mValue != 0.0)) return;

  return;
}

const C_FLOAT64 CSlider::getSliderValue() const
  {
    return this->mValue;
  }

bool CSlider::setMinValue(const C_FLOAT64 minValue)
{
  if (minValue > mMaxValue) return false;

  mMinValue = minValue;

  if (mpSliderObject && getSliderValue() < mMinValue)
    this->mValue = this->mMinValue;

  return true;
}

const C_FLOAT64 CSlider::getMinValue() const
{return mMinValue;}

bool CSlider::setMaxValue(const C_FLOAT64 maxValue)
{
  if (maxValue < mMinValue) return false;

  mMaxValue = maxValue;

  if (mpSliderObject && getSliderValue() > mMaxValue)
    this->mValue = this->mMaxValue;

  return true;
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
