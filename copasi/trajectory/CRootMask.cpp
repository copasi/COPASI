// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/trajectory/CRootMask.h"
#include "copasi/math/CMathContainer.h"

RootMask operator |(RootMask lhs, RootMask rhs)
{
  return static_cast< RootMask > (static_cast< std::underlying_type< RootMask >::type >(lhs)
                                  | static_cast< std::underlying_type< RootMask >::type >(lhs));
}

RootMask operator &(RootMask lhs, RootMask rhs)
{
  return static_cast< RootMask > (static_cast< std::underlying_type< RootMask >::type >(lhs)
                                  & static_cast< std::underlying_type< RootMask >::type >(lhs));
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

void CRootMask::create(RootMask type)
{
  if (mpContainer == nullptr)
    return;

  mType = type;

  CVector< C_FLOAT64 > RootDerivatives;
  RootDerivatives.resize(size());

  if ((RootMask::CONTINUOUS & mType) != RootMask::NONE)
    {
      mpContainer->updateSimulatedValues(false);
      mpContainer->calculateRootDerivatives(RootDerivatives);
    }

  RootMask *pMask = begin();
  RootMask *pMaskEnd = end();
  const C_FLOAT64 * pRootValue = mpContainer->getRoots().begin();
  const C_FLOAT64 * pRootDerivative = RootDerivatives.begin();
  const bool * pDiscrete = mpContainer->getRootIsDiscrete().begin();

  for (; pMask != pMaskEnd; ++pMask, ++pRootValue, ++pRootDerivative, ++pDiscrete)
    if ((RootMask::DISCRETE & mType) != RootMask::NONE
        && *pDiscrete)
      *pMask = RootMask::DISCRETE;
    else if ((RootMask::CONTINUOUS & mType) != RootMask::NONE
             && fabs(*pRootDerivative) < mAbsoluteTolerance * 1e50 * std::numeric_limits< C_FLOAT64 >::min()
             && fabs(*pRootValue) < 1e50 * std::numeric_limits< C_FLOAT64 >::min())
      *pMask = RootMask::CONTINUOUS;
    else
      *pMask = RootMask::NONE;

  // std::cout << "Root Mask:     " << *this << std::endl;
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
    if (*pMask != RootMask::NONE)
      *pRoot = std::numeric_limits< C_FLOAT64 >::infinity();
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
