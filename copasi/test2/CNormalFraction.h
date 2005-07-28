/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalFraction.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/28 13:46:06 $
   End CVS Header */

#ifndef COPASI_CNormalFraction
#define COPASI_CNormalFraction

#include <vector>
#include "copasi.h"

//#include "CNormalItem.h"
//#include "CNormalProduct.h"
#include "CNormalSum.h" 
//#include "CNormalLcm.h"

class CNormalProduct;
//class CNormalSum;
class CNormalLcm;

class CNormalFraction
  {
  private:
    /**
     * Enumeration of members
     */
    CNormalSum mNumerator;
    CNormalSum mDenominator;

  public:
    /**
     * Default constructor
     */
    CNormalFraction();

    /**
     * Copy contructor
     */
    CNormalFraction(const CNormalFraction& src);

    /**
     * Set numerator of this fraction
     * @return true.
     */
    bool setNumerator(const CNormalSum& numerator);

    /**
     * Set denominator of this fraction
     * @return true.
     */
    bool setDenominator(const CNormalSum& denominator);

    /**
     * Check if the denominator of this fraction equals 1.
     * @return bool
     */
    bool checkDenominatorOne() const;

    /**
     * Remove the denominator of this fraction.
     * -applicable if checkDenominatorOne() = true-
     * @return pointer to mNumerator
     */
    CNormalSum* removeDenominator();

    /**
     * Retrieve the numerator of this fraction.
     * @return mNumerator.
     */
    const CNormalSum& getNumerator() const;

    /**
     * Retrieve the denominator of this fraction.
     * @return mDenominator.
     */
    const CNormalSum& getDenominator() const;

    /**
     * Check if this fraction contains further fractions.
     * @return bool.
     */
    bool checkForFractions() const;

    /**
     * Expand this fraction by a lcm.
     * @return true.
     */
    bool expand(const CNormalLcm& lcm);

    /**
     * Cancel common items in numerator and denominator of this fraction if possible.
     * @return true
     */
    bool cancel();

    /**
     * Multiply this fraction with a number.
     * @return true.
     */
    bool multiply(const C_FLOAT64& number);

    /**
     * Multiply a fraction with a power of an item.
     * @return true.
     */
    bool multiply(const CNormalItemPower& itemPower);

    /**
     * Find lcm of denominators of respective fractions contained in this fraction.
     * @return pointer to lcm.
     */
    const CNormalLcm* findLcm() const;

    /**
     * Multiply this fraction by a lcm.
     * @return CNormalSum*, pointer to result of multiplication ie. a normal sum.
     */
    const CNormalSum* multiply(CNormalLcm lcm);

    /**
     * Check if numerator and denominator contain fractions,
     * find lcm of respective denominators and expand this fraction by lcm.
     * @return bool. True if it has been simplified, false if no simplification was necessary.
     */
    bool simplifyFraction();

    bool operator==(const CNormalFraction & rhs) const;

    friend std::ostream & operator<<(std::ostream &os,
                                     const CNormalFraction & d);
  };

#endif // COPASI_CNormalFraction
