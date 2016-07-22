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
