// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/core/CVector.h"
#include "copasi/utilities/CBrent.h"

class CRootFinder
{
public:
  class Eval
  {
  public:
    virtual ~Eval() {};

    virtual void operator()(const double & /* value */, CVectorCore< C_FLOAT64 > & /* rootValues */) = 0;
  };

  template <class CType> class EvalTemplate : public Eval
  {
  private:
    // pointer to member function
    void(CType::*mMethod)(const double & value, CVectorCore< C_FLOAT64 > & rootValues);
    // pointer to object
    CType * mpType;

  public:

    // constructor - takes pointer to an object and pointer to a member and stores
    // them in two private variables
    EvalTemplate(CType * pType,
                 void(CType::*method)(const double & value, CVectorCore< C_FLOAT64 > & rootValues))
    {
      mpType = pType;
      mMethod = method;
    };

    virtual ~EvalTemplate() {};

    virtual void operator()(const double & value, CVectorCore< C_FLOAT64 > & rootValues)
    {
      (*mpType.*mMethod)(value, rootValues);
    }
  };

public:
  enum RootMasking
  {
    NONE = 0,
    DISCRETE = 1,
    CONTINUOUS = 2,
    ALL = 3
  };

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
   * @param CRootFinder::Eval * pRootValueCalculator
   * @param const C_FLOAT64 & relativeTolerance
   * @param const CVectorCore< bool > & rootMask
   */
  void initialize(Eval * pRootValueCalculator,
                  const C_FLOAT64 & relativeTolerance,
                  const CVectorCore< C_INT > & rootMask);

  /**
   * Restart the root finder in case the systems state has changed
   */
  void restart();

  /**
   * Check for roots in the interval [timeLeft, timeRight]. If a root is found true is returned
   * and the time is returned in timeRoot, otherwise timeRoot is set to timeRight
   * @param const C_FLOAT64 & timeLeft
   * @param const C_FLOAT64 & timeRight
   * @param const RootMasking & rootMasking
   * @return bool ReturnStatus
   */
  ReturnStatus checkRoots(const C_FLOAT64 & timeLeft, const C_FLOAT64 & timeRight, const RootMasking & rootMasking);

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

  /**
   * Retrieve the error of the last successful root calculation
   */
  const C_FLOAT64 & getRootError() const;

private:
  void calculateCurrentRoots(const C_FLOAT64 & time);

  bool findToggledRoots(C_FLOAT64 & rootTime);

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

  CVectorCore< C_INT > mRootMask;
  RootMasking mRootMasking;
  C_FLOAT64 mRootError;

  /**
   * Pointer to method used for function evaluations for the Brent root finding method.
   */
  CBrent::Eval * mpBrentRootValueCalculator;

  Eval * mpRootValueCalculator;
};

#endif // COPASI_CRootFinder
