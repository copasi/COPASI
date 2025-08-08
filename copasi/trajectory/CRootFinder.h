// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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
 * CRootFinder.h
 *
 *  Created on: Oct 6, 2016
 *      Author: shoops
 */

#ifndef COPASI_CRootFinder
#define COPASI_CRootFinder

#include "copasi/utilities/CBrent.h"
#include "copasi/trajectory/CRootMask.h"
class CRootFinder
{
public:
  typedef std::function< void(const double &, CVectorCore< C_FLOAT64 > &) > Eval;
  typedef std::function< C_FLOAT64() > PhysicalRoot;

  enum ReturnStatus
  {
    NotFound = 0,
    RootFound = 1,
    NotAdvanced = -1,
    InvalidInterval = -2
  };

  /**
   * Default Constructor
   */
  CRootFinder();

  /**
   * Copy Constructor
   */
  CRootFinder(const CRootFinder & src);

  /**
   * Destructor
   */
  virtual ~CRootFinder();

  /**
   * Set the function used to evaluate all root values for a given time
   * @param CRootFinder::Eval & rootValueCalculator
   * @param const C_FLOAT64 & relativeTolerance
   * @param const CRootMask & rootMask
   */
  void initialize(const C_FLOAT64 & relativeTolerance,
                  const CVectorCore< const RootMask > & rootMask,
                  Eval rootValueCalculator = Eval());

  void addPhysicalRoot(PhysicalRoot & physicalRootCalculator);

  /**
   * Restart the root finder in case the systems state has changed
   */
  void restart();

  /**
   * Check for roots in the interval [timeLeft, timeRight]. If a root is found true is returned
   * and the time is returned in timeRoot, otherwise timeRoot is set to timeRight
   * @param const C_FLOAT64 & timeLeft
   * @param const C_FLOAT64 & timeRight
   * @param const RootMask & rootMask
   * @return bool ReturnStatus
   */
  ReturnStatus checkRoots(const C_FLOAT64 & timeLeft, const C_FLOAT64 & timeRight, const RootMask & rootMasking);

  /**
   * Check for roots in the interval [timeLeft, timeRight]. If a root is found true is returned
   * and the time is returned in timeRoot, otherwise timeRoot is set to timeRight
   * @param const C_FLOAT64 & timeLeft
   * @param const C_FLOAT64 & timeRight
   * @param const RootMask & rootMask
   * @return bool ReturnStatus
   */
  ReturnStatus checkRoots(const CVector< C_FLOAT64 > & rootsLeft, const CVector< C_FLOAT64 > & rootsRight, const RootMask & rootMasking);

  /**
   * Callback function for the one dimensional Brent method
   * @param const C_FLOAT64 & time
   * @return C_FLOAT64 rootValue
   */
  C_FLOAT64 brentRootValue(const C_FLOAT64 & time);

  /**
   * Retrieve the information on which roots have been found
   * @return const CVectorCore< C_INT > & toggledRoots
   */
  const CVectorCore< C_INT > & getToggledRoots() const;
  const C_INT & getToggledPhysicalRoot() const;

  /**
   * Retrieve the time when the root was found
   * @return const C_FLOAT64 & rootTime
   */
  const C_FLOAT64 & getRootTime() const;

  /**
   * Retrieve the values of the roots
   * @return const CVectorCore< C_FLOAT64 > & rootValues
   */
  const CVectorCore< C_FLOAT64 > & getRootValues() const;
  const C_FLOAT64 & getPhysicalRootValue() const;

  /**
   * Retrieve the error of the last successful root calculation
   */
  const C_FLOAT64 & getRootError() const;

private:
  void calculateCurrentRoots(const C_FLOAT64 & time);

  void calculateRoots(const C_FLOAT64 & time, CVectorCore< C_FLOAT64 > & roots, C_FLOAT64 & physicalRoot);

  bool areApproximatelyEqual(const double & x, const double & y) const;

  C_FLOAT64 mRelativeTolerance;

  C_FLOAT64 mTimeLeft;
  C_FLOAT64 mTimeRight;
  C_FLOAT64 mTimeCurrent;

  CVector< C_FLOAT64 > mRootsLeft;
  CVector< C_FLOAT64 > mRootsRight;
  CVector< C_FLOAT64 > mRootsCurrent;

  CVector< C_INT > mToggledRootsLeft;
  CVector< C_INT > mToggledRootsCurrent;
  bool mToggledRootsLeftValid;

  const CVectorCore< const RootMask > * mpRootMask;
  RootMask mRootMasking;
  C_FLOAT64 mRootError;

  /**
   * Pointer to method used for function evaluations for the Brent root finding method.
   */
  CBrent::Eval mBrentRootValueCalculator;

  Eval mRootValueCalculator;

  C_FLOAT64 mPhysicalRootLeft;
  C_FLOAT64 mPhysicalRootRight;
  C_FLOAT64 mPhysicalRootCurrent;

  C_INT mToggledPhysicalRootsCurrent;

  PhysicalRoot mPhysicalRootCalculator;
};

#endif // COPASI_CRootFinder
