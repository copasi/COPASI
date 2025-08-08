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

#include <cmath>

#include "CRootFinder.h"
#include "copasi/math/CMathEnum.h"

// Uncomment this line below to get debug print out.
// #define DEBUG_OUTPUT 1

CRootFinder::CRootFinder()
  : mRelativeTolerance(1e-6)
  , mTimeLeft(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mTimeRight(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mTimeCurrent(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mRootsLeft()
  , mRootsRight()
  , mRootsCurrent()
  , mToggledRootsLeft()
  , mToggledRootsCurrent()
  , mToggledRootsLeftValid(false)
  , mpRootMask(nullptr)
  , mRootMasking(RootMask::NONE)
  , mRootError(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mBrentRootValueCalculator(std::bind(&CRootFinder::brentRootValue, this, std::placeholders::_1))
  , mRootValueCalculator()
  , mPhysicalRootLeft(std::numeric_limits< C_FLOAT64 >::infinity())
  , mPhysicalRootRight(std::numeric_limits< C_FLOAT64 >::infinity())
  , mPhysicalRootCurrent(std::numeric_limits< C_FLOAT64 >::infinity())
  , mToggledPhysicalRootsCurrent(static_cast< C_INT >(CMath::RootToggleType::NoToggle))
  , mPhysicalRootCalculator()
{}

CRootFinder::CRootFinder(const CRootFinder & src)
  : mRelativeTolerance(src.mRelativeTolerance)
  , mTimeLeft(src.mTimeLeft)
  , mTimeRight(src.mTimeRight)
  , mTimeCurrent(src.mTimeCurrent)
  , mRootsLeft(src.mRootsLeft)
  , mRootsRight(src.mRootsRight)
  , mRootsCurrent(src.mRootsCurrent)
  , mToggledRootsLeft(src.mToggledRootsLeft)
  , mToggledRootsCurrent(src.mToggledRootsCurrent)
  , mToggledRootsLeftValid(src.mToggledRootsLeftValid)
  , mpRootMask(nullptr)
  , mRootMasking(src.mRootMasking)
  , mRootError(src.mRootError)
  , mBrentRootValueCalculator(std::bind(&CRootFinder::brentRootValue, this, std::placeholders::_1))
  , mRootValueCalculator(src.mRootValueCalculator)
  , mPhysicalRootLeft(src.mPhysicalRootLeft)
  , mPhysicalRootRight(src.mPhysicalRootRight)
  , mPhysicalRootCurrent(src.mPhysicalRootCurrent)
  , mToggledPhysicalRootsCurrent(src.mToggledPhysicalRootsCurrent)
  , mPhysicalRootCalculator(src.mPhysicalRootCalculator)
{}

// virtual
CRootFinder::~CRootFinder()
{}

void CRootFinder::initialize(const C_FLOAT64 & relativeTolerance,
                             const CVectorCore< const RootMask > & rootMask,
                             CRootFinder::Eval rootValueCalculator)
{
  size_t numRoots = rootMask.size();

  mpRootMask = &rootMask;
  mRootMasking = RootMask::NONE;

  mRootValueCalculator = rootValueCalculator;
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

void CRootFinder::addPhysicalRoot(CRootFinder::PhysicalRoot & physicalRootCalculator)
{
  mPhysicalRootCalculator = physicalRootCalculator;
  mPhysicalRootLeft = mPhysicalRootCurrent = mPhysicalRootRight = std::numeric_limits< C_FLOAT64 >::infinity();
}

CRootFinder::ReturnStatus CRootFinder::checkRoots(const C_FLOAT64 & timeLeft,
    const C_FLOAT64 & timeRight,
    const RootMask & rootMasking)
{
  if (!mRootValueCalculator && !mPhysicalRootCalculator)
    return NotFound;

  // Default return values
  ReturnStatus Status = NotFound;
  mRootMasking = rootMasking;

  // Sanity check
  if (timeLeft >= timeRight)
    return InvalidInterval;

  // Check whether we are restarting
  if (std::isnan(mTimeLeft) &&
      std::isnan(mTimeRight) &&
      timeLeft == mTimeCurrent)
    {
      mTimeCurrent = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      calculateCurrentRoots(timeLeft);

      // If the newly calculated roots do not differ we can resume
      C_FLOAT64 * pLeftRoot = mRootsLeft.begin();
      C_FLOAT64 * pLeftRootEnd = mRootsLeft.end();
      C_FLOAT64 * pRoot = mRootsCurrent.begin();
      C_INT * pRootFound = mToggledRootsCurrent.begin();
      bool Reset = false;

      for (; pLeftRoot != pLeftRootEnd; ++pLeftRoot, ++pRoot, ++pRootFound)
        if (*pRootFound != static_cast< C_INT >(CMath::RootToggleType::NoToggle) &&
            *pRoot != *pLeftRoot)
          Reset = true;

      mTimeLeft = mTimeCurrent;

      if (Reset)
        {
          // We have a clean restart and reset
          mToggledRootsLeft = static_cast< C_INT >(CMath::RootToggleType::NoToggle);
          mToggledRootsLeftValid = false;
        }
    }

  if (mToggledRootsLeftValid)
    mToggledRootsLeft = mToggledRootsCurrent;

  // Check whether we have roots for timeLeft
  if (timeLeft != mTimeLeft)
    {
      if (timeLeft == mTimeRight)
        {
          mTimeLeft = mTimeRight;
          mRootsLeft = mRootsRight;
          mPhysicalRootLeft = mPhysicalRootRight;
        }
      else if (timeLeft == mTimeCurrent)
        {
          mTimeLeft = mTimeCurrent;
          mRootsLeft = mRootsCurrent;
          mPhysicalRootLeft = mPhysicalRootCurrent;
        }
      else
        {
          mTimeLeft = timeLeft;
          calculateRoots(mTimeLeft, mRootsLeft, mPhysicalRootLeft);
        }
    }

  // the right root must always be calculated.
  mTimeRight = timeRight;
  calculateRoots(mTimeRight, mRootsRight, mPhysicalRootRight);

  C_FLOAT64 * pLeftRoot = mRootsLeft.begin();
  C_FLOAT64 * pLeftRootEnd = mRootsLeft.end();
  C_FLOAT64 * pRightRoot = mRootsRight.begin();
  const RootMask * pMask = mpRootMask->begin();

#ifdef DEBUG_OUTPUT
  std::cout.precision(16);
  // std::cout << "timeLeft = " << timeLeft << ", timeRight = " << timeRight << std::endl;
  // std::cout << "mTimeLeft = " << mTimeLeft << ", mTimeRight = " << mTimeRight << std::endl;
  // std::cout << "mRootsLeft = " << mRootsLeft << std::endl;
  // std::cout << "mRootsRight = " << mRootsRight << std::endl;
#endif // DEBUG_OUTPUT

  bool HaveRoots = (mPhysicalRootLeft * mPhysicalRootRight < 0
                    || (mPhysicalRootLeft > 0  && mPhysicalRootRight == 0));

  for (; pLeftRoot != pLeftRootEnd && !HaveRoots; ++pLeftRoot, ++pRightRoot, ++pMask)
    if ((*pMask & mRootMasking) == RootMask::NONE
        && (*pLeftRoot * *pRightRoot < 0
            || (pLeftRoot < 0  && *pRightRoot == 0)))
      HaveRoots = true;

  if (HaveRoots)
    {
#ifdef DEBUG_OUTPUT
      std::cout << "timeLeft = " << timeLeft << ", timeRight = " << timeRight << std::endl;
      std::cout << "mTimeLeft = " << mTimeLeft << ", mTimeRight = " << mTimeRight << ", mTimeCurrent = " << mTimeCurrent << std::endl;
#endif // DEBUG_OUTPUT

      C_FLOAT64 LeftRootTime = mTimeLeft;
      C_FLOAT64 LeftRootValue;
      C_FLOAT64 LeftPhysicalRoot(std::numeric_limits< C_FLOAT64 >::infinity());
      C_FLOAT64 RightRootTime = mTimeRight;
      C_FLOAT64 RightRootValue;

      // Find the "exact" location of the left most root.
      if (!CBrent::findRootInterval(mTimeLeft,
                                    mTimeRight,
                                    mBrentRootValueCalculator,
                                    &LeftRootTime,
                                    &LeftRootValue,
                                    &RightRootTime,
                                    &RightRootValue,
                                    mRelativeTolerance))
        {
          fatalError();
          return InvalidInterval;
        }

      // Handle interval size which are near the numerical resolution indicating a discontinuity
      if (!fabs(RightRootTime - LeftRootTime) <= (fabs(RightRootTime) + fabs(LeftRootTime)) * 50.0 * std::numeric_limits< double >::epsilon())
        CBrent::findRootInterval(LeftRootTime,
                                 RightRootTime,
                                 mBrentRootValueCalculator,
                                 &LeftRootTime,
                                 &LeftRootValue,
                                 &RightRootTime,
                                 &RightRootValue,
                                 mRelativeTolerance * 1e-6);

      CVector< C_FLOAT64 > LeftRoots(mpRootMask->size());
      calculateRoots(LeftRootTime, LeftRoots, LeftPhysicalRoot);
      mTimeCurrent = RightRootTime;
      calculateRoots(mTimeCurrent, mRootsCurrent, mPhysicalRootCurrent);

      bool Advanced = mTimeLeft < mTimeCurrent;

      const RootMask * pMask = mpRootMask->begin();
      const RootMask * pMaskEnd = mpRootMask->end();
      C_INT * pRootToggled = mToggledRootsCurrent.begin();
      C_INT * pRootToggledLeft = mToggledRootsLeft.begin();
      C_FLOAT64 * pLeftRoot = mRootsLeft.begin();
      C_FLOAT64 * pLeftRootCurrent = LeftRoots.begin();
      C_FLOAT64 * pRightRoot = mRootsRight.begin();
      C_FLOAT64 * pRightRootCurrent = mRootsCurrent.begin();

      for (; pMask != pMaskEnd; ++pMask, ++pRootToggled, ++pRootToggledLeft, ++pLeftRoot, ++pLeftRootCurrent, ++pRightRoot, ++pRightRootCurrent)
        {
          *pRootToggled = static_cast< C_INT >(CMath::RootToggleType::NoToggle);

          // We are only looking for roots which change sign in [pLeftRoots, pRightRoots]
          if ((*pMask & mRootMasking) == RootMask::NONE
              && (*pLeftRoot * *pRightRoot < 0
                  || (*pLeftRoot < 0 && *pRightRoot == 0)))
            {
              assert(*pLeftRoot * *pLeftRootCurrent >= 0);

              if (*pLeftRootCurrent * *pRightRootCurrent <= 0)
                {
                  *pRootToggled = static_cast< C_INT >(CMath::RootToggleType::ToggleBoth);
                  Status = RootFound;

                  if (mToggledRootsLeftValid
                      && *pRootToggledLeft == static_cast< C_INT >(CMath::RootToggleType::NoToggle))
                    Advanced = true;
                }
            }
        }

      mRootError = RightRootValue;

      // Check if we have a physical root
      if (mPhysicalRootCalculator
          && (mPhysicalRootLeft * mPhysicalRootRight < 0
              || (mPhysicalRootLeft > 0 && mPhysicalRootRight == 0)))
        {
          assert(mPhysicalRootLeft * LeftPhysicalRoot >= 0);

          if (LeftPhysicalRoot * mPhysicalRootCurrent <= 0)
            {
              if (Status != RootFound)
                {
                  Status = RootFound;
                  mTimeCurrent = LeftRootTime;
                  mPhysicalRootCurrent = LeftPhysicalRoot;
                  mRootError = mPhysicalRootCurrent;
                  Advanced = mTimeLeft < mTimeCurrent;
                }

                mToggledPhysicalRootsCurrent = static_cast< C_INT >(CMath::RootToggleType::ToggleBoth);
            }
        }

      if (Status == RootFound && Advanced == false)
        return NotAdvanced;

      if (Status == RootFound)
        {
          // Prepare for continuation from the current position i.e., start with the current root values and time.
#ifdef DEBUG_OUTPUT
          std::cout << "RootTime:                     " << mTimeCurrent << std::endl;
          std::cout << "mRootsLeft:                   " << mRootsLeft << std::endl;
          std::cout << "mRootsCurrent:                " << mRootsCurrent << std::endl;
          std::cout << "mRootsRight:                  " << mRootsRight << std::endl;
          std::cout << "mToggledRootsLeft:            " << mToggledRootsLeft << std::endl;
          std::cout << "mToggledRootsCurrent:         " << mToggledRootsCurrent << std::endl;
          std::cout << "mPhysicalRootLeft:            " << mPhysicalRootLeft << std::endl;
          std::cout << "mPhysicalRootCurrent:         " << mPhysicalRootCurrent << std::endl;
          std::cout << "mPhysicalRootRight:           " << mPhysicalRootRight << std::endl;
          std::cout << "mToggledPhysicalRootsCurrent: " << mToggledPhysicalRootsCurrent << std::endl;
          std::cout << "mRootMask:                    " << *reinterpret_cast< const CVector< RootMask > * >(mpRootMask) << std::endl;
#endif // DEBUG_OUTPUT

          mTimeLeft = mTimeCurrent;
          mRootsLeft = mRootsCurrent;
          mPhysicalRootLeft = mPhysicalRootCurrent;
          mToggledRootsLeft = mToggledRootsCurrent;
        }
    }
  else
    {
      mToggledRootsLeft = static_cast< C_INT >(CMath::RootToggleType::NoToggle);
      mTimeCurrent = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
    }

  mToggledRootsLeftValid = true;

  return Status;
}

/**
 * Check for roots in the interval [timeLeft, timeRight]. If a root is found true is returned
 * and the time is returned in timeRoot, otherwise timeRoot is set to timeRight
 * @param const C_FLOAT64 & timeLeft
 * @param const C_FLOAT64 & timeRight
 * @param const RootMask & rootMask
 * @return bool ReturnStatus
 */
CRootFinder::ReturnStatus CRootFinder::checkRoots(const CVector< C_FLOAT64 > & rootsLeft, const CVector< C_FLOAT64 > & rootsRight, const RootMask & rootMasking)
{
  // Default return values
  ReturnStatus Status = NotFound;

  const RootMask * pMask = mpRootMask->begin();
  const RootMask * pMaskEnd = mpRootMask->end();
  const C_FLOAT64 * pLeftRoot = rootsLeft.begin();
  const C_FLOAT64 * pRightRoot = rootsRight.begin();
  C_INT * pToggledRoot = mToggledRootsCurrent.begin();

  for (; pMask != pMaskEnd; ++pMask, ++pLeftRoot, ++pRightRoot, ++pToggledRoot)
    if ((*pMask & mRootMasking) == RootMask::NONE
        && (*pLeftRoot * *pRightRoot < 0
            || (pLeftRoot < 0  && *pRightRoot == 0)))
      {
        *pToggledRoot = static_cast< C_INT >(CMath::RootToggleType::NoToggle);
        Status = RootFound;
      }

  return Status;
}

void CRootFinder::restart()
{
#ifdef DEBUG_OUTPUT
  std::cout << "<-- restart root finder -->" << std::endl;
#endif // DEBUG_OUTPUT

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
  const RootMask *pMask = mpRootMask->begin();

  C_FLOAT64 MaxRootValue = - std::numeric_limits< C_FLOAT64 >::infinity();

  // Note, we always have mPhysicalRootLeft >= 0
  if (mPhysicalRootLeft * mPhysicalRootRight < 0
      || (mPhysicalRootLeft > 0 && mPhysicalRootRight == 0))
    {
      // Assure that the RootValue is increasing between old and new.
      MaxRootValue = (mPhysicalRootRight >= mPhysicalRootLeft) ? mPhysicalRootCurrent : -mPhysicalRootCurrent;
    }

  C_FLOAT64 RootValue;

  for (; pRoot != pRootEnd; ++pRoot, ++pRootLeft, ++pRootRight, ++pMask)
    {
      // We are only looking for roots which change sign in [pOld, pNew]
      if ((*pMask & mRootMasking) == RootMask::NONE
          && (*pRootLeft **pRootRight < 0
              || (*pRootLeft < 0 && *pRootRight == 0)))
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

const C_INT & CRootFinder::getToggledPhysicalRoot() const
{
  return mToggledPhysicalRootsCurrent;
}

const C_FLOAT64 & CRootFinder::getRootTime() const
{
  return mTimeCurrent;
}

const CVectorCore< C_FLOAT64 > & CRootFinder::getRootValues() const
{
  return mRootsCurrent;
}

const C_FLOAT64 & CRootFinder::getPhysicalRootValue() const
{
  return mPhysicalRootCurrent;
}

const C_FLOAT64 & CRootFinder::getRootError() const
{
  return mRootError;
}

void CRootFinder::calculateCurrentRoots(const C_FLOAT64 & time)
{
  mTimeCurrent = time;
  calculateRoots(mTimeCurrent, mRootsCurrent, mPhysicalRootCurrent);
}

void CRootFinder::calculateRoots(const C_FLOAT64 & time, CVectorCore< C_FLOAT64 > & roots, C_FLOAT64 & physicalRoot)
{
  mRootValueCalculator(time, roots);

  if (mPhysicalRootCalculator)
    physicalRoot = mPhysicalRootCalculator();

#ifdef DEBUG_OUTPUT
  std::cout << "Time: " << time << ", ";
  std::cout << "Physical Root: " << physicalRoot << ", ";
  std::cout << "mRootsCurrent: " << mRootsCurrent << std::endl;
#endif // DEBUG_OUTPUT
}

bool CRootFinder::areApproximatelyEqual(const double & x, const double & y) const
{
  double Scale =
    (fabs(x) + fabs(y)) * 50.0 * std::numeric_limits< double >::epsilon();

  // Avoid underflow
  if (Scale < 100.0 * std::numeric_limits< C_FLOAT64 >::min())
    return true;

  return 2 * fabs(x - y) < Scale;
}
