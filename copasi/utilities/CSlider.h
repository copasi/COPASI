/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSlider.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/18 21:59:11 $
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
     * @param const CSlider::Type & type
     * @return bool succes
     */
    bool setSliderType(const CSlider::Type & type);

    /**
     * Retrieve the slider type.
     * @return const CSlider::Type & type
     */
    const CSlider::Type & getSliderType() const;

    /**
     * Set the slider value.
     * @param const C_FLOAT64 Value
     * @return bool succes
     */
    bool setSliderValue(const C_FLOAT64 & value);

    /**
     * Retrieve the slider Value.
     * @return const C_FLOAT64 & Value
     */
    const C_FLOAT64 & getSliderValue() const;

    /**
     * Set the slider minimum value.
     * @param const C_FLOAT64 minValue
     * @return bool succes
     */
    bool setMinValue(const C_FLOAT64 & minValue);

    /**
     * Retrieve the slider minimum value.
     * @return const C_FLOAT64 & minValue
     */
    const C_FLOAT64 & getMinValue() const;

    /**
     * Set the slider maximum value.
     * @param const C_FLOAT64 maxValue
     * @return bool succes
     */
    bool setMaxValue(const C_FLOAT64 & maxValue);

    /**
     * Retrieve the slider maximum value.
     * @return const C_FLOAT64 & maxValue
     */
    const C_FLOAT64 & getMaxValue() const;

    /**
     * Set the tick number.
     * @param const unsigned C_INT32 & tickNumber
     * @return bool succes
     */
    bool setTickNumber(const unsigned C_INT32 & tickNumber);

    /**
     * Retrieve the tick number.
     * @return const unsigned C_INT32 & tickNumber
     */
    const unsigned C_INT32 & getTickNumber() const;

    /**
     * Set the tick factor.
     * @param const unsigned C_INT32 & tickFactor
     * @return bool succes
     */
    bool setTickFactor(const unsigned C_INT32 & tickFactor);

    /**
     * Retrieve the tick factor.
     * @return const unsigned C_INT32 & tickFactor
     */
    const unsigned C_INT32 & getTickFactor() const;

    // Attributes
  private:
    std::string mKey;
    std::string mAssociatedEntityKey;
    CCopasiObject * mpSliderObject;
    Type mSliderType;
    C_FLOAT64 mSliderValue;
    C_FLOAT64 mMinValue;
    C_FLOAT64 mMaxValue;
    unsigned C_INT32 mTickNumber;
    unsigned C_INT32 mTickFactor;
  };

#endif // COPASI_CSlider
