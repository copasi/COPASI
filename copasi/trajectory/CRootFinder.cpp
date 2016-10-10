// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <cmath>

#include "CRootFinder.h"
#include "math/CMathEnum.h"

CRootFinder::CRootFinder():
  mRelativeTolerance(1e-6),
  mTimeLeft(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mTimeRight(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mTimeCurrent(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mRootsLeft(),
  mRootsRight(),
  mRootsCurrent(),
  mToggledRoots(),
  mpBrentRootValueCalculator(NULL),
  mpRootValueCalculator(NULL)
{
  mpBrentRootValueCalculator = new CBrent::EvalTemplate< CRootFinder >(this, & CRootFinder::brentRootValue);
}

// virtual
CRootFinder::~CRootFinder()
{
  pdelete(mpBrentRootValueCalculator);
}

void CRootFinder::initialize(CRootFinder::Eval * pRootValueCalculator,
                             const C_FLOAT64 & relativeTolerance,
                             const size_t & numRoots)
{
  mpRootValueCalculator = pRootValueCalculator;
  mRelativeTolerance = relativeTolerance;

  mTimeLeft = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mTimeRight = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mTimeCurrent = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

  mRootsLeft.resize(numRoots);
  mRootsRight.resize(numRoots);
  mRootsCurrent.resize(numRoots);
  mToggledRoots.resize(numRoots);
  mToggledRoots = CMath::NoToggle;
}

bool CRootFinder::checkRoots(const C_FLOAT64 & timeLeft, const C_FLOAT64 & timeRight)
{
  // Default return values
  bool RootFound = false;

  // Sanity check
  if (timeLeft == timeRight)
    {
      return RootFound;
    }

  // Check whether we have roots for timeLeft
  if (timeLeft != mTimeLeft)
    {
      if (timeLeft == mTimeRight)
        {
          mTimeLeft = mTimeRight;
          mRootsLeft = mRootsRight;
        }
      else
        {
          if (timeLeft != mTimeCurrent)
            {
              calculateCurrentRoots(timeLeft);
            }

          mTimeLeft = mTimeCurrent;
          mRootsLeft = mRootsCurrent;
        }
    }

  // Check whether we have roots for timeRight
  if (timeRight != mTimeRight)
    {
      // Note mTimeLeft == timeLeft != timeRight, i.e., we do not need to check whether mTimeLeft == timeRight
      if (timeRight != mTimeCurrent)
        {
          calculateCurrentRoots(timeRight);
        }

      mTimeRight = mTimeCurrent;
      mRootsRight = mRootsCurrent;
    }

  C_FLOAT64 * pLeftRoot = mRootsLeft.begin();
  C_FLOAT64 * pLeftRootEnd = mRootsLeft.end();
  C_FLOAT64 * pRightRoot = mRootsRight.begin();

  for (; pLeftRoot != pLeftRootEnd; ++pLeftRoot, ++pRightRoot)
    if (*pLeftRoot **pRightRoot < 0 || *pRightRoot == 0) break;

  if (pLeftRoot != pLeftRootEnd)
    {
      // We have found at least one root in the current interval.
      C_FLOAT64 RootTime;
      C_FLOAT64 RootValue;

      // Find the "exact" location of the left most root.
      if (!CBrent::findRoot(mTimeLeft, mTimeRight, mpBrentRootValueCalculator, &RootTime, &RootValue, mRelativeTolerance * fabs(mTimeRight)))
        {
          fatalError();
        }

      // We have found the left most root in the interval [mTimeLeft, mTimeRight]
      calculateCurrentRoots(RootTime);

      C_FLOAT64 * pRoot = mRootsCurrent.begin();
      C_INT * pRootFound = mToggledRoots.begin();
      pLeftRoot = mRootsLeft.begin();
      pRightRoot = mRootsRight.begin();

      for (; pLeftRoot != pLeftRootEnd; ++pLeftRoot, ++pRightRoot, ++pRoot, ++pRootFound)
        {
          *pRootFound = CMath::NoToggle;

          // We are only looking for roots which change sign in [pLeftRoots, pRightRoots]
          if (*pLeftRoot **pRightRoot < 0 || *pRightRoot == 0)
            {
              if (*pLeftRoot **pRoot < 0)
                {
                  *pRootFound = CMath::ToggleBoth;
                  RootFound = true;
                }
              else if (fabs(*pRoot) <= (1.0 + std::numeric_limits< C_FLOAT64 >::epsilon()) * fabs(RootValue))
                {
                  *pRoot *= -1;
                  *pRootFound = CMath::ToggleBoth;
                  RootFound = true;
                }
            }
        }
    }

  return RootFound;
}

C_FLOAT64 CRootFinder::brentRootValue(const C_FLOAT64 & time)
{
  calculateCurrentRoots(time);

  const C_FLOAT64 * pRoot = mRootsCurrent.begin();
  const C_FLOAT64 * pRootEnd = mRootsCurrent.end();

  const C_FLOAT64 * pRootLeft = mRootsLeft.begin();
  const C_FLOAT64 * pRootRight = mRootsRight.begin();

  C_FLOAT64 MaxRootValue = - std::numeric_limits< C_FLOAT64 >::infinity();
  C_FLOAT64 RootValue;

  for (; pRoot != pRootEnd; ++pRoot, ++pRootLeft, ++pRootRight)
    {
      // We are only looking for roots which change sign in [pOld, pNew]
      if (*pRootLeft **pRootRight < 0 || *pRootRight == 0)
        {
          // Assure that the RootValue is increasing between old and new for each
          // candidate root.
          RootValue = (*pRootRight >= *pRootLeft) ? *pRoot : -*pRoot;

          if (RootValue > MaxRootValue)
            {
              MaxRootValue = RootValue;
            }
        }
    }

  return MaxRootValue;
}

const CVectorCore< C_INT > & CRootFinder::getToggledRoots() const
{
  return mToggledRoots;
}

const C_FLOAT64 & CRootFinder::getRootTime() const
{
  return mTimeCurrent;
}

const CVectorCore< C_FLOAT64 > & CRootFinder::getRootValues() const
{
  return mRootsCurrent;
}

void CRootFinder::calculateCurrentRoots(const C_FLOAT64 & time)
{
  if (time != mTimeCurrent)
    {
      mTimeCurrent = time;
      (*mpRootValueCalculator)(mTimeCurrent, mRootsCurrent);
    }
}
