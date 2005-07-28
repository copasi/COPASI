/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalLcm.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/28 13:46:06 $
   End CVS Header */

#ifndef COPASI_CNormalLcm
#define COPASI_CNormalLcm

#include <vector>
#include "copasi.h"

#include "CNormalItem.h"
#include "CNormalProduct.h"
#include "CNormalSum.h"
#include "CNormalFraction.h"

/**
 * The class for lcms used in CNormal
 */

class CNormalLcm
  {
  private:
    /**
     * Enumeration of members
     */
    std::vector<CNormalItemPower*> mItemPowers;
    std::vector<CNormalSum*> mSums;

  public:
    /**
     * Default constructor
     */
    CNormalLcm();

    /**
     * Copy contructor
     */
    CNormalLcm(const CNormalLcm& src);

    /**
     * Add an itempower to this lcm.
     * @return true.
     */
    bool add(const CNormalItemPower& itemPower);

    /**
     * Add a sum to this lcm.
     * @return true.
     */
    bool add(const CNormalSum& sum);

    /**
     * Remove an itempower from this lcm.
     * @return true.
     */
    bool remove(const CNormalItemPower& itemPower);

    /**
     * Remove a sum from this lcm.
     * @return true.
     */
    bool remove(const CNormalSum& sum);   //sum must not contain fractions!!

    /**
     * Retrieve the vector of itempowers of this lcm.
     * @return mItemPowers.
     */
    const std::vector<CNormalItemPower*>& getItemPowers() const;

    /**
     * Retrieve the vector of sums of this lcm.
     * @return mSums.
     */
    const std::vector<CNormalSum*>& getSums() const;

    friend std::ostream & operator<<(std::ostream &os,
                                     const CNormalLcm & d);
  };

#endif // COPASI_CNormalLcm
