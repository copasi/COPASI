/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSlider.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/01 03:01:16 $
   End CVS Header */

#include "copasi.h"
#include "mathematics.h"

#include "CSlider.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiObjectReference.h"

const char * CSlider::TypeName[] =
  {"float", "unsignedFloat", "integer", "unsignedInteger", NULL};

CSlider::CSlider(const std::string & name,
                 const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Slider"),
    mKey(GlobalKeys.add("Slider", this)),
    mAssociatedEntityKey(),
    mpSliderObject(NULL),
    mSliderType(Float),
    mMinValue(0),
    mMaxValue(0),
    mTickNumber(1000),
    mTickFactor(100)
{}

CSlider::CSlider(const CSlider & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Slider", this)),
    mAssociatedEntityKey(src.mAssociatedEntityKey),
    mpSliderObject(src.mpSliderObject),
    mSliderType(src.mSliderType),
    mMinValue(src.mMinValue),
    mMaxValue(src.mMaxValue),
    mTickNumber(src.mTickNumber),
    mTickFactor(src.mTickFactor)
{}

CSlider::~CSlider()
{GlobalKeys.remove(mKey);}

bool CSlider::compile(const std::vector< CCopasiContainer * > & listOfContainer)
{
  mpSliderObject = CCopasiContainer::ObjectFromName(listOfContainer, getObjectName());
  return (mpSliderObject != NULL);
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

bool CSlider::setSliderValue(const C_FLOAT64 value)
{
  C_FLOAT64 tmpValue = value;
  if (value < this->mMinValue)
    {
      tmpValue = this->mMinValue;
    }
  if (value > this->mMaxValue)
    {
      tmpValue = this->mMaxValue;
    }

  if (mSliderType == CSlider::Integer || mSliderType == CSlider::UnsignedInteger)
    {
      C_INT32* reference = (C_INT32*)(((CCopasiObjectReference<C_INT32>*)mpSliderObject)->getReference());

      *reference = (C_INT32)floor(tmpValue + 0.5);
    }
  else if (mSliderType == CSlider::Float || mSliderType == CSlider::UnsignedFloat)
    {
      C_FLOAT64* reference = (C_FLOAT64*)(((CCopasiObjectReference<C_FLOAT64>*)mpSliderObject)->getReference());

      *reference = tmpValue;
    }

  return true;
}

const C_FLOAT64 CSlider::getSliderValue() const
  {
    C_FLOAT64 value;
    if (mSliderType == CSlider::Integer || mSliderType == CSlider::UnsignedInteger)
      {
        C_INT32* reference = (C_INT32*)(((CCopasiObjectReference<C_INT32>*)mpSliderObject)->getReference());
        value = (C_FLOAT64)(*reference);
      }
    else if (mSliderType == CSlider::Float || mSliderType == CSlider::UnsignedFloat)
      {
        C_FLOAT64* reference = (C_FLOAT64*)(((CCopasiObjectReference<C_FLOAT64>*)mpSliderObject)->getReference());
        value = *reference;
      }

    return value;
  }

bool CSlider::setMinValue(const C_FLOAT64 minValue)
{
  if (minValue > this->mMaxValue) return false;

  mMinValue = minValue;

  if (this->getSliderValue() < this->mMinValue)
    {
      this->setSliderValue(this->mMinValue);
    }
  return true;
}

const C_FLOAT64 CSlider::getMinValue() const
  {return mMinValue;}

bool CSlider::setMaxValue(const C_FLOAT64 maxValue)
{
  if (maxValue < mMinValue) return false;

  mMaxValue = maxValue;

  if (this->getSliderValue() > mMaxValue)
    {
      this->setSliderValue(mMaxValue);
    }
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
