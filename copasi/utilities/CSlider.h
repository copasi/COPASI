/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSlider.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/20 04:10:05 $
   End CVS Header */

#ifndef COPASI_CSlider
#define COPASI_CSlider

#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"

class CSlider : public CCopasiContainer
  {
  public:
    /**
     *  Enum of valid quantitye units
     */
    enum Type {Float = 0, UnsignedFloat, Integer, UnsignedInteger};

    /**
     * String representation of valid quantity units
     */
    static const char * TypeName[];

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSlider(const std::string & name = "NoName",
            const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CSlider & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSlider(const CSlider & src,
            const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CSlider();

    /**
     * Compile, i.e., find the objects pointed to by the CN.
     * @param const std::vector< CCopasiContainer * > & listOfContainer
     * @return bool success
     */
    bool compile(const std::vector< CCopasiContainer * > & listOfContainer =
                   CCopasiContainer::EmptyList);

    /**
     * Retrieve the key
     * @return const std::string & key
     */
    const std::string & getKey() const;

    /**
     * Set the key of the associated entity
     * @param const std::string & associatedEntityKey
     * @return bool succes
     */
    bool setAssociatedEntityKey(const std::string & associatedEntityKey);

    /**
     * Retrieve the key of the associated entity.
     * @return const std::string & associatedEntityKey
     */
    const std::string & getAssociatedEntityKey() const;

    /**
     * Set the slider object.
     * @param CCopasiObject * pObject
     * @return bool succes
     */
    bool setSliderObject(CCopasiObject * pObject);

    /**
     * Set the slider object.
     * @param const CCopasiObjectName & objectCN
     * @return bool succes
     */
    bool setSliderObject(const CCopasiObjectName & objectCN);

    /**
     * Retrieve the slider object.
     * @return CCopasiObject * pObject
     */
    CCopasiObject * getSliderObject();

    /**
     * Retrieve the slider object CN.
     * @return const std::string & sliderObjectCN
     */
    const std::string & CSlider::getSliderObjectCN() const;

    /**
     * Set the slider type.
     * @param const CSlider::Type  type
     * @return bool succes
     */
    bool setSliderType(const CSlider::Type type);

    /**
     * Retrieve the slider type.
     * @return const CSlider::Type  type
     */
    const CSlider::Type getSliderType() const;

    /**
     * Set the slider value.
     * @param const C_FLOAT64 Value
     * @param const bool & writeToObject (Default: true)
     * @return bool succes
     */
    bool setSliderValue(const C_FLOAT64 value,
                        const bool & writeToObject = true);

    /**
     * Retrieve the slider Value.
     * @return const C_FLOAT64 Value
     */
    const C_FLOAT64 getSliderValue() const;

    /**
     * Set the slider minimum value.
     * @param const C_FLOAT64 minValue
     * @return bool succes
     */
    bool setMinValue(const C_FLOAT64 minValue);

    /**
     * Retrieve the slider minimum value.
     * @return const C_FLOAT64  minValue
     */
    const C_FLOAT64 getMinValue() const;

    /**
     * Set the slider maximum value.
     * @param const C_FLOAT64 maxValue
     * @return bool succes
     */
    bool setMaxValue(const C_FLOAT64 maxValue);

    /**
     * Retrieve the slider maximum value.
     * @return const C_FLOAT64 & maxValue
     */
    const C_FLOAT64 getMaxValue() const;

    /**
     * Set the tick number.
     * @param const unsigned C_INT32 & tickNumber
     * @return bool succes
     */
    bool setTickNumber(const unsigned C_INT32 tickNumber);

    /**
     * Retrieve the tick number.
     * @return const unsigned C_INT32 & tickNumber
     */
    const unsigned C_INT32 getTickNumber() const;

    /**
     * Set the tick factor.
     * @param const unsigned C_INT32 & tickFactor
     * @return bool succes
     */
    bool setTickFactor(const unsigned C_INT32 tickFactor);

    /**
     * Retrieve the tick factor.
     * @return const unsigned C_INT32 & tickFactor
     */
    const unsigned C_INT32 getTickFactor() const;

    /**
     * Reset the minimum and maximum value to defaults. For the minimum this is
     * half the current value. For the maximum this is twice the current value.
     */
    void resetRange();

    /**
     * Sets wether the value is to be kept in sync the the objects value.  
     */
    void setSynced(bool synced);

    /**
     * Returns wether the value is to be kept in sync the the objects value.  
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
     * The slider object pointing to the slider's object afteer compile.
     */
    CCopasiObject * mpSliderObject;

    /**
     * The value type of the slider's object.
     */
    Type mSliderType;

    /**
     * The value of the slider-
     */
    C_FLOAT64 mValue;

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
  };

#endif
