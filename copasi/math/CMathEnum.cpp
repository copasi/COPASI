// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathEnum.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/24 16:32:31 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathEnum.h"

CMath::CVariableStack::CVariableStack():
    mpStack(NULL),
    mContext(Body),
    mVariableLevel(C_INVALID_INDEX),
    mBodyLevel(C_INVALID_INDEX)
{}

CMath::CVariableStack::CVariableStack(CMath::CVariableStack::Buffer & stack):
    mpStack(&stack),
    mContext(Body),
    mVariableLevel(C_INVALID_INDEX),
    mBodyLevel(C_INVALID_INDEX)
{}

CMath::CVariableStack::CVariableStack(const CMath::CVariableStack & src):
    mpStack(src.mpStack),
    mContext(src.mContext),
    mVariableLevel(src.mVariableLevel),
    mBodyLevel(src.mBodyLevel)
{}

CMath::CVariableStack::~CVariableStack()
{}

void CMath::CVariableStack::push(const CMath::CVariableStack::StackElement & stackElement)
{
  mpStack->push_back(stackElement);
  mBodyLevel++;
}

void CMath::CVariableStack::pop()
{
  mpStack->pop_back();
  mBodyLevel--;
}

size_t CMath::CVariableStack::size() const
{
  return mpStack->size();
}

const CEvaluationNode * CMath::CVariableStack::operator [](const size_t & index) const
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

std::ostream & operator << (std::ostream & os, const CMath::CVariableStack & s)
{
  switch (s.mContext)
    {
      case CMath::CVariableStack::Variable:
        os << "Context: variable ";
        break;

      case CMath::CVariableStack::Body:
        os << "Context: body ";
        break;
    }

  os << "Variable Level: " << s.mVariableLevel << " Body Level: " << s.mBodyLevel;

  return os;
}

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

CMath::CAllocationStack::CAllocation::CAllocation &
CMath::CAllocationStack::CAllocation::operator = (const CMath::CAllocationStack::CAllocation::CAllocation & rhs)
{
  nDiscontinuous = rhs.nDiscontinuous;
  nTotalRoots = rhs.nTotalRoots;
  nRootsPerDiscontinuity = rhs.nRootsPerDiscontinuity;

  return *this;
}

CMath::CAllocationStack::CAllocation::CAllocation &
CMath::CAllocationStack::CAllocation::operator += (const CMath::CAllocationStack::CAllocation::CAllocation & rhs)
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

