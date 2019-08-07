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

#ifndef COPASI_CSlider
#define COPASI_CSlider

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CRegisteredCommonName.h"

#include "copasi/math/CMathUpdateSequence.h"

class CSlider : public CDataContainer
{
public:
  /**
   *  Enum of valid quantity units
   */
  enum Type {Float = 0, UnsignedFloat, Integer, UnsignedInteger, Undefined};

  /**
   *  Enum of valid scales
   */
  enum Scale {linear = 0, logarithmic, undefinedScale};

  /**
   * String representation of valid quantity units
   */
  static const char * TypeName[];

  /**
   * String representation of valid scalings
   */
  static const char * ScaleName[];

  // Operations
public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CSlider * pDataObject
   */
  static CSlider * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CSlider(const std::string & name = "Slider",
          const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CSlider & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CSlider(const CSlider & src,
          const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CSlider();

  /**
   * Compile, i.e., find the objects pointed to by the CN.
   * @param const CObjectInterface::ContainerList & listOfContainer
   *  (default: CDataContainer::EmptyList)
   * @return bool success
   */
  bool compile(const CObjectInterface::ContainerList & listOfContainer);

  /**
   * Retrieve the key
   * @return const std::string & key
   */
  const std::string & getKey() const;

  /**
   * Set the key of the associated entity
   * @param const std::string & associatedEntityKey
   * @return bool success
   */
  bool setAssociatedEntityKey(const std::string & associatedEntityKey);

  /**
   * Retrieve the key of the associated entity.
   * @return const std::string & associatedEntityKey
   */
  const std::string & getAssociatedEntityKey() const;

  /**
   * Set the slider object.
   * @param const CDataObject * pObject
   * @return bool success
   */
  bool setSliderObject(const CDataObject * pObject);

  /**
   * Set the slider object.
   * @param const CCommonName & objectCN
   * @return bool success
   */
  bool setSliderObject(const CCommonName & objectCN);

  /**
   * Retrieve the slider object.
   * @return const CDataObject * pObject
   */
  const CDataObject * getSliderObject() const;

  /**
   * Retrieve the slider object CN.
   * @return const std::string & sliderObjectCN
   */
  const std::string & getSliderObjectCN() const;

  /**
   * Set the slider type.
   * @param const CSlider::Type  type
   * @return bool success
   */
  bool setSliderType(const CSlider::Type type);

  /**
   * Retrieve the slider type.
   * @return const CSlider::Type  type
   */
  CSlider::Type getSliderType() const;

  /**
   * Set the sliders original value.
   * @param const C_FLOAT64 Value
   * @param const bool & writeToObject (Default: true)
   * @return bool success
   */
  bool setOriginalValue(const C_FLOAT64 value);

  /**
   * Retrieve the original slider Value.
   * @return const C_FLOAT64 Value
   */
  const C_FLOAT64 & getOriginalValue() const;

  /**
   * Set the slider value.
   * @param const C_FLOAT64 Value
   * @param const bool & writeToObject (Default: true)
   * @return bool success
   */
  bool setSliderValue(const C_FLOAT64 value,
                      const bool & writeToObject = true);

  /**
   * Sets the value of the slider back to it's original
   * value.
   */
  void resetValue();

  /**
   * Retrieve the slider Value.
   * @return const C_FLOAT64 Value
   */
  const C_FLOAT64 & getSliderValue() const;

  /**
   * Set the slider minimum value.
   * @param const C_FLOAT64 minValue
   * @return bool success
   */
  bool setMinValue(const C_FLOAT64 minValue);

  /**
   * Retrieve the slider minimum value.
   * @return const C_FLOAT64  minValue
   */
  const C_FLOAT64 & getMinValue() const;

  /**
   * Set the slider maximum value.
   * @param const C_FLOAT64 maxValue
   * @return bool success
   */
  bool setMaxValue(const C_FLOAT64 maxValue);

  /**
   * Retrieve the slider maximum value.
   * @return const C_FLOAT64 & maxValue
   */
  const C_FLOAT64 & getMaxValue() const;

  /**
   * Set the tick number.
   * @param const unsigned C_INT32 & tickNumber
   * @return bool success
   */
  bool setTickNumber(const unsigned C_INT32 tickNumber);

  /**
   * Retrieve the tick number.
   * @return const unsigned C_INT32 & tickNumber
   */
  unsigned C_INT32 getTickNumber() const;

  /**
   * Set the tick factor.
   * @param const unsigned C_INT32 & tickFactor
   * @return bool success
   */
  bool setTickFactor(const unsigned C_INT32 tickFactor);

  /**
   * Retrieve the tick factor.
   * @return const unsigned C_INT32 & tickFactor
   */
  unsigned C_INT32 getTickFactor() const;

  /**
   * Set the scaling for the CSlider.
   */
  bool setScaling(Scale scaling);

  /**
   * Retrieve the scaling of the slider.
   * @return Scale scaling
   */
  Scale getScaling() const;

  /**
   * Reset the minimum and maximum value to defaults. For the minimum this is
   * half the current value. For the maximum this is twice the current value.
   */
  void resetRange();

  /**
   * Sets whether the value is to be kept in sync the the objects value.
   */
  void setSynced(bool synced);

  /**
   * Returns whether the value is to be kept in sync the the objects value.
   * @return bool isSynced.
   */
  bool getSynced() const;

  /**
   * Set the CSliders value to the value of the underlying object.
   */
  void sync();

  /**
   * Set the objects value to the value stored in CSlider.
   */
  void writeToObject();

  /**
   * Converts the scaling name to the corresponding enum.
   * @return CSlider::Scale
   */
  Scale convertScaleNameToScale(const char* scaleName);

  /**
   * Converts the scaling name to the corresponding enum.
   * @return const char* scaleName
   */
  const char* convertScaleToScaleName(Scale scale) const;

  /**
   * Checks whether the object the slider points to actually
   * exists.
   * Returns true if it does.
   */
  bool isValid() const;

  // Attributes
private:
  /**
   * The key of the slider.
   */
  std::string mKey;

  /**
   * The key of the associated entity of the slider's object.
   */
  std::string mAssociatedEntityKey;

  /**
   * The slider object pointing to the slider's object after compile.
   */
  CDataObject * mpSliderObject;

  /**
   * The value type of the slider's object.
   */
  Type mSliderType;

  /**
   * The value of the slider-
   */
  C_FLOAT64 mValue;

  /**
   * The original value of the slider-
   */
  C_FLOAT64 mOriginalValue;

  /**
   * The minimun value of the slider
   */
  C_FLOAT64 mMinValue;

  /**
   * The maximum value of the slider
   */
  C_FLOAT64 mMaxValue;

  /**
   * The number of ticks the slider is divided into.
   */
  unsigned C_INT32 mTickNumber;

  /**
   * The factor between minor and major ticks.
   */
  unsigned C_INT32 mTickFactor;

  /**
   * Wether the CSlider's value is always in sync with its object's value.
   */
  bool mSync;

  /**
   * The scaling of the slider.
   */
  Scale mScaling;

  /**
   * The CN of the object that the slider modifies.
   */
  CRegisteredCommonName mCN;

  /**
   * The sequnece of methods to update initial values depending on this sliders
   * object.
   */
  CCore::CUpdateSequence mInitialRefreshes;
};

#endif
