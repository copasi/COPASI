// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CValidatedUnit.h
 *
 *  Created on: Aug 1, 2016
 *      Author: shoops
 */

#ifndef COPASI_CValidatedUnit
#define COPASI_CValidatedUnit

#include "copasi/utilities/CUnit.h"

class CValidatedUnit : public CUnit
{
public:
  friend std::ostream &operator<<(std::ostream &os, const CValidatedUnit & o);

  static CValidatedUnit merge(const CValidatedUnit & a, const CValidatedUnit & b);

  /**
   * Default Constructor
   */
  CValidatedUnit();

  /**
   * Specific constructor
   * @param const CUnit & unit
   * @param const bool & conflict
   */
  CValidatedUnit(const CUnit & unit, const bool & conflict);

  /**
   * Destructor
   */
  ~CValidatedUnit();

  /**
   * Return the unit to the power exponent
   * @param const double & exponent
   * @return CValidatedUnit exponentiated
   */
  CValidatedUnit exponentiate(const double & exponent) const;

  /**
   * Multiply two units and return the result
   * @param const CValidatedUnit & rightSide
   * @return CValidatedUnit product
   */
  CValidatedUnit operator*(const CValidatedUnit & rightSide) const;

  /**
   * Set whether the validated unit represents a conflict;
   * @param const bool & conflict
   */
  void setConflict(const bool & conflict);

  /**
   * Check  whether the validated unit represents a conflict
   * @return const bool & conflict
   */
  const bool & conflict() const;

  /**
   * Comparison operator
   * @param const CUnit & rightSide
   * @return lessThan
   */
  bool operator<(const CValidatedUnit & rightSide) const;

private:
  // Set to true when combining units where the individual ones
  // ought to be compatible (e.g. addition and subtraction in
  // function expressions)
  bool mConflict;
};

#endif /* COPASI_UTILITIES_CVALIDATEDUNIT_H_ */
