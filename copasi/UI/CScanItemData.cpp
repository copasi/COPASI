// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"
#include "CScanItemData.h"
#include "utilities/CCopasiParameterGroup.h"

CScanItemData::CScanItemData() :
  mType(CScanProblem::SCAN_BREAK),
  mpData(NULL)
{}

CScanItemData::CScanItemData(const CScanProblem::Type & type) :
  mType(type),
  mpData(CScanProblem::createScanItem(type))
{}

CScanItemData::CScanItemData(const CScanItemData & src) :
  mType(src.mType),
  mpData(src.mpData != NULL ? new CCopasiParameterGroup(*src.mpData, NO_PARENT) : NULL)
{}

// virtual
CScanItemData::~CScanItemData()
{}

const CScanProblem::Type & CScanItemData::getType() const
{
  return mType;
}
