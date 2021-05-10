// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "CMathDelay.h"
#include "CMathExpression.h"
#include "CMathContainer.h"

CMathDelay::CMathDelay():
  mpContainer(NULL),
  mpLagObject(NULL),
  mValueObjects(),
  mValueSequence()
{}

CMathDelay::~CMathDelay()
{}

void CMathDelay::create(CMath::DelayData::iterator & itDelayData,
                        const size_t & delayValueCount,
                        CMathContainer & container,
                        CMathObject * pLagObject)
{
  mpContainer = & container;
  mpLagObject = pLagObject;

  // Resize the value objects
  mValueObjects.resize(delayValueCount);
  mValueObjects = NULL;

  // Assign the expression to the lag object.
  mpLagObject->setExpression(itDelayData->first, false, container);
}

void CMathDelay::addValueObject(CMath::DelayValueData::iterator & itValueData,
                                const size_t & index,
                                CMathObject * pValueObject)
{
  assert(index < mValueObjects.size());

  mValueObjects[index] = pValueObject;
  pValueObject->setExpression(itValueData->first, false, *mpContainer);
}

void CMathDelay::modifyMathObject(CMath::DelayValueData::iterator & itValueData,
                                  const size_t & index)
{
  const CMathExpression * pExpression = itValueData->second.second->getExpressionPtr();

  std::string Infix = pExpression->getInfix();
  const std::string Search = itValueData->second.first;
  std::string Replace = "delay(" + pointerToString(mValueObjects[index]->getValuePointer()) + ", " + pointerToString(mpLagObject->getValuePointer()) + ")";

  size_t pos = 0;

  while ((pos = Infix.find(Search, pos)) != std::string::npos)
    {
      Infix.replace(pos, Search.length(), Replace);
    }

  itValueData->second.second->setExpression(Infix, pExpression->isBoolean(), *mpContainer);
}

void CMathDelay::copy(const CMathDelay & src, CMathContainer & container)
{
  assert(&src != this);
  *this = src;
}

void CMathDelay::relocate(const CMathContainer * pContainer,
                          const std::vector< CMath::sRelocate > & relocations)
{
  pContainer->relocateObject(mpLagObject, relocations);

  CMathObject **ppObject = mValueObjects.array();
  CMathObject **ppObjectEnd = ppObject + mValueObjects.size();

  for (; ppObject != ppObjectEnd; ++ppObject)
    {
      pContainer->relocateObject(*ppObject, relocations);
    }
}

void CMathDelay::createUpdateSequences()
{
  // The requested objects are all delay values
  CObjectInterface::ObjectSet Requested;

  CMathObject **pObject = mValueObjects.array();
  CMathObject **pObjectEnd = pObject + mValueObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    if (*pObject != NULL)
      {
        Requested.insert(*pObject);
      }

  mpContainer->getTransientDependencies().getUpdateSequence(mValueSequence, CCore::SimulationContext::DelayValues,
      mpContainer->getStateObjects(false), Requested);
  mpContainer->getTransientDependencies().getUpdateSequence(mValueSequenceReduced, CCore::SimulationContextFlag(CCore::SimulationContext::UseMoieties) | CCore::SimulationContext::DelayValues,
      mpContainer->getStateObjects(true), Requested);
}

void CMathDelay::calculateDelayValues(const bool & useMoieties)
{
  if (useMoieties)
    {
      mpContainer->applyUpdateSequence(mValueSequenceReduced);
    }
  else
    {
      mpContainer->applyUpdateSequence(mValueSequence);
    }
}
