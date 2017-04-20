// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CStatistics.h"
#include "copasi/model/CModelValue.h"

CStatistics::CStatistics(const std::string & name,
                         const CDataContainer * pParent,
                         const std::string & type,
                         const unsigned C_INT32 & flag,
                         C_FLOAT64 statValue):
  CDataContainer(name, pParent, type, flag | CDataObject::ValueDbl),
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

CDataObject * CStatistics::getStatValueReference() const
{return mpStatValueReference;}
