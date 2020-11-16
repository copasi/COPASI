// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *   CHybridNextReactionLSODAMethod
 *
 *   First approach to an hybrid algorithm. Gibson's Next Reaction method is
 *   combined with the LSODA numerical integrator.
 *
 *   File name: CHybridNextReactionLSODAMethod.h
 *   Author:
 *   Email:
 *
 *   Last change: 08, May 2006
 *
 *   (C) European Media Lab 2003.
 */

/* HEADER FILE ***************************************************************/
#include "copasi/copasi.h"
#include "CHybridNextReactionLSODAMethod.h"
#include "copasi/math/CMathContainer.h"

CHybridNextReactionLSODAMethod::CHybridNextReactionLSODAMethod(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  CHybridMethod(pParent, methodType, taskType),
  mLSODA(this)
{
  initializeParameter();
}

CHybridNextReactionLSODAMethod::CHybridNextReactionLSODAMethod(const CHybridNextReactionLSODAMethod & src,
    const CDataContainer * pParent):
  CHybridMethod(src, pParent),
  mLSODA(src.mLSODA, this)
{
  initializeParameter();
}

void CHybridNextReactionLSODAMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("Partitioning Stepsize")) != NULL)
    {
      setValue("Partitioning Interval", pParm->getValue< C_FLOAT64 >());
      removeParameter("Partitioning Stepsize");
    }

  // We need to assure that  all parameter required from the LSODA method exist
  index_iterator it = mLSODA.beginIndex();
  index_iterator end = mLSODA.endIndex();

  for (; it != end; ++it)
    {
      if (getParameter((*it)->getObjectName()) == NULL)
        {
          addParameter(**it);
        }
    }
}

// virtual
void CHybridNextReactionLSODAMethod::start()
{
  CHybridMethod::start();

  CCopasiParameter *pParm;

  // We need to copy all parameter required from the LSODA method
  index_iterator it = mLSODA.beginIndex();
  index_iterator end = mLSODA.endIndex();

  for (; it != end; ++it)
    {
      if ((pParm = getParameter((*it)->getObjectName())) != NULL)
        {
          **it = *pParm;
        }
    }

  mLSODA.setMathContainer(mpContainer);
  mLSODA.start();
}

// virtual
void CHybridNextReactionLSODAMethod::integrateDeterministicPart(C_FLOAT64 ds)
{
  mLSODA.step(ds);
}

// virtual
void CHybridNextReactionLSODAMethod::stateChange(const CMath::StateChange & change)
{
  mLSODA.stateChange(change);
}

void CHybridNextReactionLSODAMethod::evalF(C_FLOAT64 * ydot)
{
  CVectorCore< C_FLOAT64 > Derivative(mNumVariableMetabs, ydot + mFirstMetabIndex);
  calculateDerivative(Derivative);
}

CHybridNextReactionLSODAMethod::LSODA::LSODA(const CHybridNextReactionLSODAMethod * pParent):
  CLsodaMethod(pParent)
{}

CHybridNextReactionLSODAMethod::LSODA::LSODA(const CHybridNextReactionLSODAMethod::LSODA & src, const CHybridNextReactionLSODAMethod * pParent):
  CLsodaMethod(src, pParent)
{}

// virtual
void CHybridNextReactionLSODAMethod::LSODA::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  *mpContainerStateTime = *t;
  static_cast< CHybridNextReactionLSODAMethod * >(getObjectParent())->evalF(ydot);
}
