/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalSum.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/28 13:46:06 $
   End CVS Header */

#ifndef COPASI_CNormalSum
#define COPASI_CNormalSum

#include <vector>
#include "copasi.h"

#include "CNormalItem.h" 
//#include "CNormalProduct.h"
//#include "CNormalLcm.h"
//#include "CNormalFraction.h"

class CNormalProduct;
class CNormalLcm;
class CNormalFraction;

/**
 * The class for sums used in CNormal
 */
class CNormalSum
  {
  private:
    /**
     * Enumeration of members
     */
    std::vector<CNormalProduct*> mProducts;
    std::vector<CNormalFraction*> mFractions;

  public:
    /**
     * Default constructor
     */
    CNormalSum();

    /**
     * Copy Constructor
     */
    CNormalSum(const CNormalSum& src);

    /**
     * Retrieve the number of summands of this sum.
     * @return int
     */
    int getSize() const;

    /**
     * Add product to this sum.
     * @return true.
     */
    bool add(const CNormalProduct& product);

    /**
     * Add fraction to this sum.
     * @return true.
     */
    bool add(const CNormalFraction& fraction);

    /**
     * Add a sum to this sum.
     * @return true.
     */
    bool add(const CNormalSum& sum);

    /**
     * Check if this sum contains fractions.
     * @return bool.
     */
    bool checkForFractions() const;

    /**
     * Multiply this sum with a number.
     * @return true.
     */
    bool multiply(const C_FLOAT64& number);

    /**
     * Multiply this sum with a power of an item.
     * @return true.
     */
    bool multiply(const CNormalItemPower& itemPower);

    /**
     * Multiply this sum with another sum, both do not contain fractions!!
     * @return true.
     */
    bool multiply(const CNormalSum& sum);

    /**
     * Multiply this sum by a lcm.
     * @return true.
     */
    bool multiply(const CNormalLcm& lcm);

    /**
     * Retrieve the vector of products of this sum.
     * @return mProducts
     */
    const std::vector<CNormalProduct*>& getProducts() const;

    /**
     * Retrieve the vector of fractions of this sum.
     * @return mFractions.
     */
    const std::vector<CNormalFraction*>& getFractions() const;

    bool operator==(const CNormalSum & rhs) const;

    friend std::ostream & operator<<(std::ostream &os,
                                     const CNormalSum & d);
  };

#endif // COPASI_CNormalSum
