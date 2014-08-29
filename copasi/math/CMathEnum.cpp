// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathEnum.h"

CMath::CAllocationStack::CAllocation::CAllocation():
  nDiscontinuous(0),
  nTotalRoots(0),
  nRootsPerDiscontinuity()
{}

CMath::CAllocationStack::CAllocation::CAllocation(const CMath::CAllocationStack::CAllocation & src):
  nDiscontinuous(src.nDiscontinuous),
  nTotalRoots(src.nTotalRoots),
  nRootsPerDiscontinuity(src.nRootsPerDiscontinuity)
{}

CMath::CAllocationStack::CAllocation::~CAllocation()
{}

CMath::CAllocationStack::CAllocation &
CMath::CAllocationStack::CAllocation::operator = (const CMath::CAllocationStack::CAllocation & rhs)
{
  nDiscontinuous = rhs.nDiscontinuous;
  nTotalRoots = rhs.nTotalRoots;
  nRootsPerDiscontinuity = rhs.nRootsPerDiscontinuity;

  return *this;
}

CMath::CAllocationStack::CAllocation &
CMath::CAllocationStack::CAllocation::operator += (const CMath::CAllocationStack::CAllocation & rhs)
{
  nDiscontinuous += rhs.nDiscontinuous;
  nTotalRoots += rhs.nTotalRoots;
  nRootsPerDiscontinuity.insert(nRootsPerDiscontinuity.end(),
                                rhs.nRootsPerDiscontinuity.begin(),
                                rhs.nRootsPerDiscontinuity.end());

  return *this;
}

CMath::CAllocationStack::CAllocationStack():
  mpStack(NULL),
  mContext(Body),
  mVariableLevel(C_INVALID_INDEX),
  mBodyLevel(C_INVALID_INDEX)
{}

CMath::CAllocationStack::CAllocationStack(CMath::CAllocationStack::Buffer & stack):
  mpStack(&stack),
  mContext(Body),
  mVariableLevel(C_INVALID_INDEX),
  mBodyLevel(C_INVALID_INDEX)
{}

CMath::CAllocationStack::CAllocationStack(const CMath::CAllocationStack & src):
  mpStack(src.mpStack),
  mContext(src.mContext),
  mVariableLevel(src.mVariableLevel),
  mBodyLevel(src.mBodyLevel)
{}

CMath::CAllocationStack::~CAllocationStack()
{}

void CMath::CAllocationStack::push(const CMath::CAllocationStack::StackElement & stackElement)
{
  mpStack->push_back(stackElement);
  mBodyLevel++;
}

void CMath::CAllocationStack::pop()
{
  mpStack->pop_back();
  mBodyLevel--;
}

size_t CMath::CAllocationStack::size() const
{
  return mpStack->size();
}

const CMath::CAllocationStack::CAllocation &
CMath::CAllocationStack::operator [](const size_t & index) const
{
  size_t Level = C_INVALID_INDEX;

  switch (mContext)
    {
      case Variable:
        Level = mVariableLevel;
        break;

      case Body:
        Level = mBodyLevel;

        break;
    }

  assert(Level < mpStack->size());
  assert(index < mpStack->at(Level).size());

  return mpStack->at(Level)[index];
}

std::ostream & operator << (std::ostream & os, const CMath::CAllocationStack::CAllocation & s)
{
  os << "Discontinuities: " << s.nDiscontinuous;
  return os;
}
