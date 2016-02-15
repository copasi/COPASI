// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CStatistics.h"
#include "copasi/model/CModelValue.h"

CStatistics::CStatistics()
{}

CStatistics::CStatistics(const std::string & name,
                         const CCopasiContainer * pParent,
                         const std::string & type,
                         const unsigned C_INT32 & flag,
                         C_FLOAT64 statValue):
  CModelEntity(name, pParent, type, flag),
  mStatValue(statValue)
{
  initObjects();
}

CStatistics::~CStatistics()
{
  DESTRUCTOR_TRACE;
}

void CStatistics::initObjects()
{
  mpStatValueReference =
    static_cast<CCopasiObjectReference <C_FLOAT64> *>(addObjectReference("Statistics (Reference)", mStatValue, CCopasiObject::ValueDbl));
}

const C_FLOAT64 & CStatistics::getStatValue() const
{return mStatValue;}

CCopasiObjectReference <C_FLOAT64> * CStatistics::getStatValueReference() const
{return mpStatValueReference;}
