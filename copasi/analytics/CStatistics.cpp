// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CStatistics.h"
#include "copasi/model/CModelValue.h"

CStatistics::CStatistics(const std::string & name,
                         const CCopasiContainer * pParent,
                         const std::string & type,
                         const unsigned C_INT32 & flag,
                         C_FLOAT64 statValue):
  CCopasiContainer(name, pParent, type, flag | CCopasiObject::ValueDbl),
  mStatValue(statValue)
{
  initObjects();
}

CStatistics::~CStatistics()
{
  pdelete(mpStatValueReference);
  DESTRUCTOR_TRACE;
}

void CStatistics::initObjects()
{

  pdelete(mpStatValueReference);
  mpStatValueReference = this->addObjectReference(getObjectName(), mStatValue);
}

const C_FLOAT64 & CStatistics::getStatValue() const
{return mStatValue;}

CCopasiObject * CStatistics::getStatValueReference() const
{return mpStatValueReference;}
