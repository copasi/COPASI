// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CMathUpdateSequence.h"
#include "CMathContainer.h"

CMathUpdateSequence::CMathUpdateSequence(CMathContainer * pContainer):
  CVector< CObjectInterface * >(),
  mpContainer(NULL)
{
  setMathContainer(pContainer);
}

CMathUpdateSequence::CMathUpdateSequence(const CMathUpdateSequence & src, CMathContainer * pContainer):
  CVector< CObjectInterface * >(src),
  mpContainer(NULL)
{
  if (pContainer != NULL)
    {
      setMathContainer(pContainer);
    }
  else
    {
      setMathContainer(src.mpContainer);
    }
}

CMathUpdateSequence::~CMathUpdateSequence()
{
  if (mpContainer != NULL)
    {
      mpContainer->deregisterUpdateSequence(this);
    }
}

CMathUpdateSequence & CMathUpdateSequence::operator = (const CMathUpdateSequence & rhs)
{
  CVector< CObjectInterface * >::operator = (rhs);
  setMathContainer(rhs.mpContainer);

  return *this;
}

CMathUpdateSequence & CMathUpdateSequence::operator = (const std::vector< CObjectInterface * > & rhs)
{
  resize(rhs.size(), false);

  iterator itThis = begin();
  iterator endThis = end();

  std::vector< CObjectInterface * >::const_iterator itSrc = rhs.begin();

  for (; itThis != endThis; ++itThis, ++itSrc)
    {
      *itThis = *itSrc;
    }

  return *this;
}

void CMathUpdateSequence::setMathContainer(CMathContainer * pContainer)
{
  if (pContainer == mpContainer) return;

  if (mpContainer != NULL)
    {
      mpContainer->deregisterUpdateSequence(this);
    }

  mpContainer = pContainer;

  if (mpContainer != NULL)
    {
      mpContainer->registerUpdateSequence(this);
    }
}

CMathUpdateSequence::iterator CMathUpdateSequence::begin()
{
  return CVectorCore< CObjectInterface * >::mpBuffer;
}

CMathUpdateSequence::iterator CMathUpdateSequence::end()
{
  return CVectorCore< CObjectInterface * >::mpBuffer + CVectorCore< CObjectInterface * >::mSize;
}

CMathUpdateSequence::const_iterator CMathUpdateSequence::begin() const
{
  return CVectorCore< CObjectInterface * >::mpBuffer;
}

CMathUpdateSequence::const_iterator CMathUpdateSequence::end() const
{
  return CVectorCore< CObjectInterface * >::mpBuffer + CVectorCore< CObjectInterface * >::mSize;
}

const size_t & CMathUpdateSequence::size() const
{
  return CVectorCore< CObjectInterface * >::mSize;
}

bool CMathUpdateSequence::empty() const
{
  return CVectorCore< CObjectInterface * >::mSize == 0;
}

void CMathUpdateSequence::clear()
{
  resize(0);
}
