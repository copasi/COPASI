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

#ifndef COPASI_CNormalLcm
#define COPASI_CNormalLcm

#include <vector>
#include <set>
#include "copasi/copasi.h"

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
  std::set <CNormalItemPower*, compareItemPowers> mItemPowers;
  //std::set <CNormalPower*, comparePowers> mPowers;
  std::vector<CNormalSum*> mSums; //mSums do not contain fractions!!

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

  /*
   * Add a power to this lcm,
   * ie. lcm := LeastCommonMultiple(lcm,power)
   * @return true.
   *
  bool add(const CNormalPower& power);*/

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
  const std::set <CNormalItemPower*, compareItemPowers>& getItemPowers() const;

  /**
   * Retrieve the vector of sums of this lcm.
   * @return mSums.
   */
  const std::vector<CNormalSum*>& getSums() const;

  friend std::ostream & operator<<(std::ostream &os,
                                   const CNormalLcm & d);
};

#endif // COPASI_CNormalLcm
