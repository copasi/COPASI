// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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
  mpData(src.mpData != NULL ? new CCopasiParameterGroup(*src.mpData) : NULL)
{}

// virtual
CScanItemData::~CScanItemData()
{}

const CScanProblem::Type & CScanItemData::getType() const
{
  return mType;
}
