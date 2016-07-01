// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CMathUpdateSequence.h"
#include "CMathContainer.h"

CMathUpdateSequence::CMathUpdateSequence(CMathContainer * pContainer):
  std::vector< CObjectInterface * >(),
  mpContainer(NULL)
{
  setMathContainer(pContainer);
}

CMathUpdateSequence::CMathUpdateSequence(const CMathUpdateSequence & src, CMathContainer * pContainer):
  std::vector< CObjectInterface * >(src),
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
  std::vector< CObjectInterface * >::operator = (rhs);
  setMathContainer(rhs.mpContainer);

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

void CMathUpdateSequence::sanitize(const CVectorCore< CMathObject > & oldObjects,
                                   const CVectorCore< CMathObject > & newObjects)
{
  if (oldObjects.array() == newObjects.array())
    {
      return;
    }

  const CMathObject * pBegin = oldObjects.array();
  const CMathObject * pEnd = pBegin + oldObjects.size();

  std::vector< CObjectInterface * > Dirty(*this);
  std::vector< CObjectInterface * >::iterator it = Dirty.begin();
  std::vector< CObjectInterface * >::iterator End = Dirty.end();
  clear();

  for (; it != End; ++it)
    if (*it < pBegin || pEnd <= *it)
      {
        push_back(*it);
      }
}
