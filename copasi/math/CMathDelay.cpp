// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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
  mValueObjects[index] = pValueObject;
  pValueObject->setExpression(itValueData->first, false, *mpContainer);
}

void CMathDelay::modifyMathObject(CMath::DelayValueData::iterator & itValueData,
                                  const size_t & index)
{
  const CMathExpression * pExpression = itValueData->second.second->getExpressionPtr();

  std::string Infix = pExpression->getInfix();
  const std::string Search = itValueData->second.first->buildInfix();
  std::string Replace = "delay(" + pointerToString(mValueObjects[index]) + ", " + pointerToString(mpLagObject) + ")";

  size_t pos = 0;

  if ((pos = Infix.find(Search, pos)) != std::string::npos)
    {
      Infix.replace(pos, Search.length(), Replace);
    }

  itValueData->second.second->setExpression(Infix, pExpression->isBoolean(), *mpContainer);
}

void CMathDelay::copy(const CMathDelay & src, CMathContainer & container, const size_t & valueOffset, const size_t & objectOffset)
{
  mpContainer = &container;
  mpLagObject = (CMathObject *)((size_t) src.mpLagObject + objectOffset);

  mValueObjects.resize(src.mValueObjects.size());

  CMathObject ** pValueObject = mValueObjects.array();
  CMathObject ** pValueObjectEnd = pValueObject + mValueObjects.size();
  CMathObject * const * pValueObjectSrc = src.mValueObjects.array();

  for (; pValueObject != pValueObjectEnd; ++pValueObject, ++pValueObjectSrc)
    {
      *pValueObject = (CMathObject *)((size_t) * pValueObjectSrc + objectOffset);
    }
}

void CMathDelay::createUpdateSequences()
{
  // The requested objects are all delay values
  CObjectInterface::ObjectSet Requested;

  CMathObject **pObject = mValueObjects.array();
  CMathObject **pObjectEnd = pObject + mValueObjects.size();

  for (; pObject != pObjectEnd; ++pObject)
    {
      Requested.insert(*pObject);
    }

  mpContainer->getTransientDependencies().getUpdateSequence(mValueSequence, CMath::DelayValues,
      mpContainer->getStateObjects(false), Requested);
  mpContainer->getTransientDependencies().getUpdateSequence(mValueSequence, CMath::UseMoieties | CMath::DelayValues,
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
