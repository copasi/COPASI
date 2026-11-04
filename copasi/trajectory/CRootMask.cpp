// Copyright (C) 2025 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/trajectory/CRootMask.h"
#include "copasi/math/CMathContainer.h"

RootMask operator |(RootMask lhs, RootMask rhs)
{
  return static_cast< RootMask > (static_cast< std::underlying_type< RootMask >::type >(lhs)
                                  | static_cast< std::underlying_type< RootMask >::type >(rhs));
}

RootMask operator &(RootMask lhs, RootMask rhs)
{
  return static_cast< RootMask > (static_cast< std::underlying_type< RootMask >::type >(lhs)
                                  & static_cast< std::underlying_type< RootMask >::type >(rhs));
}

std::ostream &operator<<(std::ostream &os, RootMask & rootMask)
{
  os << static_cast< std::underlying_type< RootMask >::type >(rootMask);
  return os;
}

CRootMask::operator const CVector< const RootMask > & () const
{
  return *reinterpret_cast< const CVector< const RootMask > * >(this);
}

bool CRootMask::operator== (const CRootMask & rhs) const
{
  return mType == rhs.mType
         && CVector< RootMask >::operator==(rhs);
}

void CRootMask::setMathContainer(CMathContainer * pContainer)
{
  if (mpContainer == pContainer)
    return;

  mpContainer = pContainer;

  if (mpContainer != nullptr)
    resize(mpContainer->getRoots().size());
  else
    resize(0);

  if (std::isnan(mAbsoluteTolerance)
      || (mType == RootMask::NONE))
    CVector< RootMask >::operator =(RootMask::NONE);
  else
    create(mType);
}

void CRootMask::setTolerance(const C_FLOAT64 & tolerance)
{
  mAbsoluteTolerance = tolerance;

  if (mpContainer == nullptr)
    return;

  if (std::isnan(mAbsoluteTolerance)
      || (mType == RootMask::NONE))
    CVector< RootMask >::operator =(RootMask::NONE);
  else
    create(mType);
}

void CRootMask::create(RootMask type, const CVectorCore< C_INT > & rootsFound)
{
  if (mpContainer == nullptr)
    return;

  mType = type;

  if (mType == RootMask::NONE)
    {
      CVector< RootMask >::operator =(RootMask::NONE);
    }
  else
    {
      CVector< C_FLOAT64 > RootDerivatives(size());
      const CVectorCore< C_INT > *pRootsFound = &rootsFound;

      if ((RootMask::CONTINUOUS & mType) != RootMask::NONE)
        {
          mpContainer->updateSimulatedValues(false);
          mpContainer->calculateRootDerivatives(RootDerivatives);
        }

      CVector< C_INT > RootsFound;

      if (rootsFound.size() != size())
        {
          RootsFound.resize(size());
          RootsFound = 0;
          pRootsFound = &RootsFound;
        }

      RootMask *pMask = begin();
      RootMask *pMaskEnd = end();
      const C_FLOAT64 & Time = mpContainer->getState(false)[mpContainer->getCountFixedEventTargets()];
      const C_FLOAT64 * pRootValue = mpContainer->getRoots().begin();
      const C_FLOAT64 * pRootDerivative = RootDerivatives.begin();
      const bool * pDiscrete = mpContainer->getRootIsDiscrete().begin();
      const C_INT * pFound = pRootsFound->begin();

      for (; pMask != pMaskEnd; ++pMask, ++pRootValue, ++pRootDerivative, ++pDiscrete, ++pFound)
        {
          if (*pDiscrete
              && (RootMask::DISCRETE & mType) != RootMask::NONE)
            *pMask = RootMask::DISCRETE;
          else if ((RootMask::CONTINUOUS & mType) != RootMask::NONE
                   && (fabs(*pRootValue) < 1e50 * std::numeric_limits< C_FLOAT64 >::min()
                       || ((*pFound > 0)
                           && fabs(*pRootValue) < 1e3 * Time * fabs(*pRootDerivative) * std::numeric_limits< C_FLOAT64 >::epsilon())))
            {
              if (*pRootValue < 0
                  && (RootMask::CONTINUOUS_NEGATIVE & mType) != RootMask::NONE)
                *pMask = RootMask::CONTINUOUS_NEGATIVE;
              else if (*pRootValue >= 0
                       && (RootMask::CONTINUOUS_POSITIVE & mType) != RootMask::NONE)
                *pMask = RootMask::CONTINUOUS_POSITIVE;
              else
                *pMask = RootMask::NONE;
            }
          else
            *pMask = RootMask::NONE;
        }
    }
}

void CRootMask::setType(RootMask type)
{
  RootMask OldType = mType;
  mType = type;

  if (mpContainer == nullptr
      || OldType == mType)
    return;

  if ((OldType | type) == OldType)
    for (RootMask & mask : *this)
      mask = mask & mType;
  else if (std::isnan(mAbsoluteTolerance)
           || (mType == RootMask::NONE))
    CVector< RootMask >::operator =(RootMask::NONE);
  else
    create(mType);
}

void CRootMask::apply(CVectorCore< C_FLOAT64 > & roots) const
{
  const RootMask *pMask = begin();
  const RootMask *pMaskEnd = end();
  C_FLOAT64 * pRoot = roots.begin();

  for (; pMask != pMaskEnd; ++pMask, ++pRoot)
    if ((*pMask & mType & RootMask::DISCRETE) != RootMask::NONE)
      *pRoot = std::numeric_limits< C_FLOAT64 >::infinity();
    else if ((*pMask & mType & RootMask::CONTINUOUS_NEGATIVE) != RootMask::NONE)
      (*pRoot) = -1.0;
    else if ((*pMask & mType & RootMask::CONTINUOUS_POSITIVE) != RootMask::NONE)
      (*pRoot) = 1.0;
}

bool CRootMask::adjust(RootMask & type, const CVectorCore< C_INT > & found)
{
  RootMask TargetType = type;
  bool adjusted = false;

  RootMask *pMask = begin();
  RootMask *pMaskEnd = end();
  const C_FLOAT64 *pRootValue = mpContainer->getRoots().begin();
  const C_INT * pFound = found.begin();

  for (; pMask != pMaskEnd; ++pMask, ++pFound, ++pRootValue)
    if ((*pMask & RootMask::CONTINUOUS) != RootMask::NONE
        && *pFound > 0
        && fabs(*pRootValue) < 1e50 * std::numeric_limits< C_FLOAT64 >::min())
      type = RootMask::CONTINUOUS | TargetType;
    else if (!((*pMask & TargetType) == *pMask))
      {
        *pMask = (*pMask & TargetType);
        adjusted = true;
      }

  mType = type;

  return adjusted;
}

RootMask * CRootMask::begin()
{
  return CVector< RootMask >::begin();
}

RootMask * CRootMask::end()
{
  return CVector< RootMask >::end();
}

const RootMask * CRootMask::begin() const
{
  return CVector< RootMask >::begin();
}

const RootMask * CRootMask::end() const
{
  return CVector< RootMask >::end();
}

size_t CRootMask::size() const
{
  return CVector< RootMask >::size();
}
