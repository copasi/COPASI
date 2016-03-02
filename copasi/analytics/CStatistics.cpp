// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CStatistics.h"
#include "copasi/model/CModelValue.h"

CStatisticsReference::CStatisticsReference(const std::string & name,
    const CCopasiContainer *pParent,
    C_FLOAT64 & reference):
  CCopasiObjectReference< C_FLOAT64 >(name, pParent, reference)
{}

CStatisticsReference::~CStatisticsReference()
{}

CStatistics::CStatistics(const std::string & name,
                         const CCopasiContainer * pParent,
                         const std::string & type,
                         const unsigned C_INT32 & flag,
                         C_FLOAT64 statValue):
  CCopasiContainer(name, pParent, type, flag | CCopasiObject::ValueDbl),
  mStatValue(statValue)
{
  initObjects(name, statValue);
}

CStatistics::~CStatistics()
{
  DESTRUCTOR_TRACE;
}

void CStatistics::initObjects(const std::string & name, C_FLOAT64 & value)
{

  pdelete(mpStatValueReference);
  mpStatValueReference = new CStatisticsReference(name + "Reference", this, value);
}

const C_FLOAT64 & CStatistics::getStatValue() const
{return mStatValue;}

CStatisticsReference *CStatistics::getStatValueReference() const
{return mpStatValueReference;}
