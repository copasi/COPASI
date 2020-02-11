// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include <cmath>

#include "CRootFinder.h"
#include "copasi/math/CMathEnum.h"

CRootFinder::CRootFinder():
  mRelativeTolerance(1e-6),
  mTimeLeft(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mTimeRight(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mTimeCurrent(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mRootsLeft(),
  mRootsRight(),
  mRootsCurrent(),
  mToggledRootsLeft(),
  mToggledRootsCurrent(),
  mToggledRootsLeftValid(false),
  mRootMask(),
  mRootMasking(CRootFinder::NONE),
  mRootError(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mpBrentRootValueCalculator(NULL),
  mpRootValueCalculator(NULL)
{
  mpBrentRootValueCalculator = new CBrent::EvalTemplate< CRootFinder >(this, & CRootFinder::brentRootValue);
}

CRootFinder::CRootFinder(const CRootFinder & src)
  :
  mRelativeTolerance(src.mRelativeTolerance),
  mTimeLeft(src.mTimeLeft),
  mTimeRight(src.mTimeRight),
  mTimeCurrent(src.mTimeCurrent),
  mRootsLeft(src.mRootsLeft),
  mRootsRight(src.mRootsRight),
  mRootsCurrent(src.mRootsCurrent),
  mToggledRootsLeft(src.mToggledRootsLeft),
  mToggledRootsCurrent(src.mToggledRootsCurrent),
  mToggledRootsLeftValid(src.mToggledRootsLeftValid),
  mRootMask(),
  mRootMasking(src.mRootMasking),
  mRootError(src.mRootError),
  mpBrentRootValueCalculator(NULL),
  mpRootValueCalculator(src.mpRootValueCalculator)
{
  mRootMask.initialize(src.mRootMask);
  mpBrentRootValueCalculator = new CBrent::EvalTemplate< CRootFinder >(this, & CRootFinder::brentRootValue);
}

// virtual
CRootFinder::~CRootFinder()
{
  pdelete(mpBrentRootValueCalculator);
}

void CRootFinder::initialize(CRootFinder::Eval * pRootValueCalculator,
                             const C_FLOAT64 & relativeTolerance,
                             const CVectorCore< C_INT > & rootMask)
{
  size_t numRoots = rootMask.size();

  mRootMask.initialize(rootMask);
  mRootMasking = NONE;

  mpRootValueCalculator = pRootValueCalculator;
  mRelativeTolerance = relativeTolerance;

  mRootsLeft.resize(numRoots);
  mRootsRight.resize(numRoots);
  mRootsCurrent.resize(numRoots);

  mToggledRootsLeft.resize(numRoots);
  mToggledRootsLeft = static_cast< C_INT >(CMath::RootToggleType::NoToggle);

  mToggledRootsCurrent.resize(numRoots);
  mToggledRootsCurrent = static_cast< C_INT >(CMath::RootToggleType::NoToggle);

  mToggledRootsLeftValid = false;
  mRootError = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

  restart();
}

CRootFinder::ReturnStatus CRootFinder::checkRoots(const C_FLOAT64 & timeLeft,
    const C_FLOAT64 & timeRight,
    const CRootFinder::RootMasking & rootMasking)
{
  // Default return values
  ReturnStatus Status = NotFound;
  mRootMasking = rootMasking;

  // Sanity check
  if (timeLeft >= timeRight)
    {
      return InvalidInterval;
    }

  // Check whether we are restarting
  if (std::isnan(mTimeLeft) &&
      std::isnan(mTimeRight) &&
      timeLeft == mTimeCurrent)
    {
      mTimeCurrent = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      calculateCurrentRoots(timeLeft);

      // If the newly calculated roots differ only in the sign for the previously toggled roots we
      // can resume
      C_FLOAT64 * pLeftRoot = mRootsLeft.begin();
      C_FLOAT64 * pLeftRootEnd = mRootsLeft.end();
      C_FLOAT64 * pRoot = mRootsCurrent.begin();
      C_INT * pRootFound = mToggledRootsCurrent.begin();
      bool Reset = false;

      for (; pLeftRoot != pLeftRootEnd; ++pLeftRoot, ++pRoot, ++pRootFound)
        if (*pRootFound != static_cast< C_INT >(CMath::RootToggleType::NoToggle) &&
            *pRoot == -1.0 * *pLeftRoot)
          {
            *pLeftRoot = -1.0 * *pRoot;
          }
        else if (*pRoot != *pLeftRoot)
          {
            *pLeftRoot = *pRoot;
            Reset = true;
          }

      mTimeLeft = mTimeCurrent;

      if (Reset)
        {
          // We have a clean restart and reset
          mToggledRootsLeft = static_cast< C_INT >(CMath::RootToggleType::NoToggle);
        }
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
  const C_INT * pMask = mRootMask.begin();

  // std::cout.precision(16);
  // std::cout << "timeLeft = " << timeLeft << ", timeRight = " << timeRight << std::endl;
  // std::cout << "mTimeLeft = " << mTimeLeft << ", mTimeRight = " << mTimeRight << std::endl;
  // std::cout << "mRootsLeft = " << mRootsLeft << ", mRootsRight = " << mRootsRight << std::endl;

  for (; pLeftRoot != pLeftRootEnd; ++pLeftRoot, ++pRightRoot, ++pMask)
    if (!(*pMask & mRootMasking) &&
        (*pLeftRoot **pRightRoot < 0 || *pRightRoot == 0)) break;

  if (pLeftRoot != pLeftRootEnd)
    {
      // std::cout.precision(16);
      // std::cout << "timeLeft = " << timeLeft << ", timeRight = " << timeRight << std::endl;
      // std::cout << "mTimeLeft = " << mTimeLeft << ", mTimeRight = " << mTimeRight << ", mTimeCurrent = " << mTimeCurrent << std::endl;

      C_FLOAT64 RootTime = mTimeLeft;
      C_FLOAT64 RootValue;

      // Find the "exact" location of the left most root.
      if (!CBrent::findRoot(mTimeLeft, mTimeRight, mpBrentRootValueCalculator, &RootTime, &RootValue, mRelativeTolerance))
        {
          mToggledRootsCurrent = static_cast< C_INT >(CMath::RootToggleType::NoToggle);
          mToggledRootsLeft = static_cast< C_INT >(CMath::RootToggleType::NoToggle);
          return NotFound;
        }

      // We have found the left most root in the interval [mTimeLeft, mTimeRight]
      calculateCurrentRoots(RootTime);

      C_FLOAT64 * pRoot = mRootsCurrent.begin();
      C_INT * pRootFound = mToggledRootsCurrent.begin();
      C_INT * pRootFoundLeft = mToggledRootsLeft.begin();
      C_FLOAT64 * pLeftRoot = mRootsLeft.begin();
      C_FLOAT64 * pLeftRootEnd = mRootsLeft.end();
      C_FLOAT64 * pRightRoot = mRootsRight.begin();
      pMask = mRootMask.begin();
      bool Advanced = false;

      for (; pLeftRoot != pLeftRootEnd; ++pLeftRoot, ++pRightRoot, ++pRoot, ++pRootFound, ++pRootFoundLeft, ++pMask)
        {
          *pRootFound = static_cast< C_INT >(CMath::RootToggleType::NoToggle);

          if (*pMask & mRootMasking)
            continue;

          // We are only looking for roots which change sign in [pLeftRoots, pRightRoots]
          if (*pLeftRoot **pRightRoot < 0 || *pRightRoot == 0)
            {
              if (*pLeftRoot **pRoot < 0)
                {
                  *pRootFound = static_cast< C_INT >(CMath::RootToggleType::ToggleBoth);
                  Status = RootFound;

                  if (mToggledRootsLeftValid &&
                      *pRootFoundLeft == static_cast< C_INT >(CMath::RootToggleType::NoToggle))
                    Advanced = true;
                }
              else if (fabs(*pRoot) <= (1.0 + std::numeric_limits< C_FLOAT64 >::epsilon()) * fabs(RootValue))
                {
                  *pRoot *= -1; // Change sign to avoid finding it again
                  *pRootFound = static_cast< C_INT >(CMath::RootToggleType::ToggleBoth);
                  Status = RootFound;

                  if (mToggledRootsLeftValid &&
                      *pRootFoundLeft == static_cast< C_INT >(CMath::RootToggleType::NoToggle))
                    Advanced = true;
                }
            }
        }

      if (Status == RootFound)
        {
          // Check whether we advanced in time
          if (!Advanced &&
              fabs(RootTime - mTimeLeft) <= RootTime * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              return NotAdvanced;
            }

          // Prepare for continuation from the current position i.e., start with the current root values and time.
          mTimeLeft = RootTime;
          mRootsLeft = mRootsCurrent;
          mToggledRootsLeft = mToggledRootsCurrent;
          mRootError = RootValue;

          // std::cout.precision(16);
          // std::cout << "RootTime:             " << RootTime << std::endl;
          // std::cout << "mRootsLeft:           " << mRootsLeft << std::endl;
          // std::cout << "mRootsCurrent:        " << mRootsCurrent << std::endl;
          // std::cout << "mRootsRight:          " << mRootsRight << std::endl;
          // std::cout << "mToggledRootsLeft:    " << mToggledRootsLeft << std::endl;
          // std::cout << "mToggledRootsCurrent: " << mToggledRootsCurrent << std::endl;
          // std::cout << "mRootMask:            " << mRootMask << std::endl;
        }
    }

  mToggledRootsLeftValid = true;

  return Status;
}

void CRootFinder::restart()
{
  // std::cout << "<-- restart root finder -->" << std::endl;

  mTimeLeft = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mTimeRight = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
}

C_FLOAT64 CRootFinder::brentRootValue(const C_FLOAT64 & time)
{
  calculateCurrentRoots(time);

  const C_FLOAT64 * pRoot = mRootsCurrent.begin();
  const C_FLOAT64 * pRootEnd = mRootsCurrent.end();

  const C_FLOAT64 * pRootLeft = mRootsLeft.begin();
  const C_FLOAT64 * pRootRight = mRootsRight.begin();
  const C_INT *pMask = mRootMask.begin();

  C_FLOAT64 MaxRootValue = - std::numeric_limits< C_FLOAT64 >::infinity();
  C_FLOAT64 RootValue;

  for (; pRoot != pRootEnd; ++pRoot, ++pRootLeft, ++pRootRight, ++pMask)
    {
      // We are only looking for roots which change sign in [pOld, pNew]
      if (!(*pMask & mRootMasking) &&
          (*pRootLeft **pRootRight < 0 || *pRootRight == 0))
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
  return mToggledRootsCurrent;
}

const C_FLOAT64 & CRootFinder::getRootTime() const
{
  return mTimeCurrent;
}

const CVectorCore< C_FLOAT64 > & CRootFinder::getRootValues() const
{
  return mRootsCurrent;
}

const C_FLOAT64 & CRootFinder::getRootError() const
{
  return mRootError;
}

void CRootFinder::calculateCurrentRoots(const C_FLOAT64 & time)
{
  if (time != mTimeCurrent)
    {
      mTimeCurrent = time;
      (*mpRootValueCalculator)(mTimeCurrent, mRootsCurrent);
    }

  // std::cout.precision(16);
  // std::cout << "mTimeCurrent:  " << mTimeCurrent << std::endl;
  // std::cout << "mRootsCurrent: " << mRootsCurrent << std::endl;
}
