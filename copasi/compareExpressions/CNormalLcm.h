// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalLcm.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/03/03 15:57:53 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalLcm_H__
#define COPASI_CNormalLcm_H__

class CNormalItemPower;
class CNormalSum;
class CNormalLcm;

#include <vector>
#include <string>

#include "copasi/compareExpressions/CNormalProduct.h"

/**
 * The class for lcms used in CNormal
 */
class CNormalLcm
  {
  private:
    /**
     * Enumeration of members
     */
    std::set <CNormalItemPower*, compareItemPowers > mItemPowers;
    std::vector<CNormalSum*> mSums; //mSums do not contain fractions!!
#ifdef COPASI_DEBUG
    std::string mInfix;
#endif /* COPASI_DEBUG */

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
     * Assignment operator
     */
    CNormalLcm & operator=(const CNormalLcm& src);

    /**
     * Destructor
     */
    ~CNormalLcm();

    /**
     * Add an itempower to this lcm,
     * ie. lcm := LeastCommonMultiple(lcm,itempower)
     * @return true.
     */
    bool add(const CNormalItemPower& itemPower);

    /**
     * Add a fractionless sum to this lcm,
     * ie. lcm := LeastCommonMultiple(lcm,sum)
     * @return true.
     */
    bool add(const CNormalSum& sum);

    /**
     * Remove an itempower from this lcm, provided it is a factor
     * @return true.
     */
    bool remove(const CNormalItemPower& itemPower);

    /**
     * Remove a fractionless sum from this lcm, provided it is a factor
     * @return true.
     */
    bool remove(const CNormalSum& sum);   //sum must not contain fractions!!

    /**
     * Retrieve the set of itempowers of this lcm.
     * @return mItemPowers.
     */
    const std::set <CNormalItemPower*, compareItemPowers >& getItemPowers() const;

    /**
     * Retrieve the vector of sums of this lcm.
     * @return mSums.
     */
    const std::vector<CNormalSum*>& getSums() const;

    std::string toString() const;

#ifdef COPASI_DEBUG
    void refresh();
#endif /* COPASI_DEBUG */
    friend std::ostream & operator<< (std::ostream &os, const CNormalLcm & d);
  };

#endif // COPASI_CNormalLcm_H__
