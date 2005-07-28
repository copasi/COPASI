/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalItem.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/28 13:46:06 $
   End CVS Header */

#ifndef COPASI_CNormalItem
#define COPASI_CNormalItem

#include <vector>
#include "copasi.h"

/**
 * The class for items used in CNormal
 */
class CNormalItem
  {
  public:
    /**
     * Enumeration of possible item types.
     */
    enum Type
    {
      VARIABLE ,
      FUNCTION
    };

    std::string mName;

    /**
     * Default constructor
     */
    CNormalItem();

    /**
     * Copy contructor
     */
    CNormalItem(const CNormalItem& src);

    /**
     * Retrieve the name of this item.
     * @return mName
     */
    const std::string getName() const;

    /**
     * Examine equality of two items.
     * @return bool.
     */
    bool operator==(const CNormalItem & rhs) const;

    friend std::ostream & operator<<(std::ostream &os,
                                     const CNormalItem & d);

    friend bool compareItems(const CNormalItem* item1, const CNormalItem* item2);
  };

/**
 * The class for powers of items used in CNormal
 */
class CNormalItemPower
  {
  private:
    /**
     * Enumeration of members.
     */
    CNormalItem mItem;
    C_FLOAT64 mExp;

  public:
    /**
     * Default constructor
     */
    CNormalItemPower();

    /**
     * Copy Constructor
     */
    CNormalItemPower(const CNormalItemPower& src);

    /**
     * Create a new power of the given item and exponent
     * @return CNormalItemPower, the newly created power.
     */
    CNormalItemPower(const CNormalItem& item, const C_FLOAT64& exp);

    /**
     * Set the base of this itempower.
     * @return true.
     */
    bool setItem(const CNormalItem& item);

    /**
     * Set the exponent of this power
     * @return true
     */
    bool setExp(const C_FLOAT64& number);

    /**
     * Retrieve the base of this power
     * @return mItem
     */
    const CNormalItem& getItem() const;

    /**
     * Retrieve the exponent of this power
     * @return mExp
     */
    const C_FLOAT64& getExp() const;

    /**
     * Examine equality of two item powers.
     * @return bool.
     */
    bool operator==(const CNormalItemPower & rhs) const;

    friend std::ostream & operator<<(std::ostream &os,
                                     const CNormalItemPower & d);

    friend bool compareItemPowers(const CNormalItemPower* itemPower1, const CNormalItemPower* itemPower2);
  };

#endif // COPASI_CNormalItem
