/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalProduct.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/28 13:46:06 $
   End CVS Header */

#ifndef COPASI_CNormalProduct
#define COPASI_CNormalProduct

#include <vector>
#include "copasi.h"

//#include "CNormalItem.h"
//#include "CNormalSum.h"
//#include "CNormalLcm.h"
class CNormalItem;
class CNormalItemPower;
class CNormalSum;
class CNormalLcm;

/**
 * The class for products used in CNormal
 */
class CNormalProduct
  {
  private:
    /**
     * Enumeration of members
     */
    C_FLOAT64 mFactor;
    std::vector<CNormalItemPower*> mItemPowers;
    //std::vector<CNormalItem* item,C_FLOAT64 exp> mItems;

  public:

    /**
     * Default constructor
     */
    CNormalProduct();

    /**
     * Copy contructor
     */
    CNormalProduct(const CNormalProduct& src);

    /**
     * Set the factor for this product.
     * @return true.
     */
    bool setFactor(const C_FLOAT64& number);

    /**
     * Multiply this product with a number.
     * @return true.
     */
    bool multiply(const C_FLOAT64& number);

    /**
     * Multiply an item to this product.
     * @return true.
     */
    bool multiply(const CNormalItem& item);

    /**
     * Multiply an itempower to this product.
     * @return true.
     */
    bool multiply(const CNormalItemPower& power);

    /**
     * Multiply a list of powers of items to this product.
     * @return true.
     */
    bool multiply(const std::vector<CNormalItemPower*>& itemPowers);

    /**
     * Remove an itempower from this product, provided it is a factor of it.
     * @return true.
     */
    bool remove(const CNormalItemPower& itemPower);

    /**
     * Multiply this product with another product.
     * @return true
     */
    bool multiply(const CNormalProduct& product);

    /**
     * Multiply this product with a sum not containing fractions.
     * @return sum.
     */
    CNormalSum* multiply(const CNormalSum& sum);

    /**
     * Multiply this product with a lcm.
     * @return true
     */
    const CNormalSum* multiply(const CNormalLcm& lcm);

    /**
     * Retrieve the factor of this product.
     * @return mFactor.
     */
    const C_FLOAT64 & getFactor() const;

    /**
     * Retrieve the vector of itempowers of this product.
     * @return mItems.
     */
    const std::vector<CNormalItemPower*>& getItemPowers() const;

    bool operator==(const CNormalProduct & rhs) const;

    friend std::ostream & operator<<(std::ostream &os,
                                     const CNormalProduct & d);
  };

#endif // COPASI_CNormalProduct
