// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanItemData.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/12/22 19:51:57 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
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
