/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSlider.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/19 02:02:10 $
   End CVS Header */

#include "copasi.h"

#include "CSlider.h"
#include "report/CKeyFactory.h"

const char * CSlider::TypeName[] =
  {"float", "unsignedFloat", "integer", "unsignedInteger", NULL};

CSlider::CSlider(const std::string & name,
                 const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Slider"),
    mKey(GlobalKeys.add("Slider", this)),
    mAssociatedEntityKey(),
    mpSliderObject(NULL),
    mSliderType(),
    mSliderValue(),
    mMinValue(),
    mMaxValue(),
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
    mSliderValue(src.mSliderValue),
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
  return true;
}

bool CSlider::setSliderObject(const CCopasiObjectName & objectCN)
{return setObjectName(objectCN);}

CCopasiObject * CSlider::getSliderObject()
{return mpSliderObject;}

const std::string & CSlider::getSliderObjectCN() const
  {return getObjectName();}

bool CSlider::setSliderType(const CSlider::Type & type)
{
  mSliderType = type;
  return true;
}

const CSlider::Type & CSlider::getSliderType() const
  {return mSliderType;}

bool CSlider::setSliderValue(const C_FLOAT64 & value)
{
  mSliderValue = value;
  return true;
}

const C_FLOAT64 & CSlider::getSliderValue() const
  {return mSliderValue;}

bool CSlider::setMinValue(const C_FLOAT64 & minValue)
{
  mMinValue = minValue;
  return true;
}

const C_FLOAT64 & CSlider::getMinValue() const
  {return mMinValue;}

bool CSlider::setMaxValue(const C_FLOAT64 & maxValue)
{
  mMaxValue = maxValue;
  return true;
}

const C_FLOAT64 & CSlider::getMaxValue() const
  {return mMaxValue;}

bool CSlider::setTickNumber(const unsigned C_INT32 & tickNumber)
{
  mTickNumber = tickNumber;
  return true;
}

const unsigned C_INT32 & CSlider::getTickNumber() const
  {return mTickNumber;}

bool CSlider::setTickFactor(const unsigned C_INT32 & tickFactor)
{
  mTickFactor = tickFactor;
  return true;
}

const unsigned C_INT32 & CSlider::getTickFactor() const
  {return mTickFactor;}
