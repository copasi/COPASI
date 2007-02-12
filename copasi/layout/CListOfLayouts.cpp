// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CListOfLayouts.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/12 00:03:12 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CListOfLayouts.h"
#include "report/CKeyFactory.h"

CListOfLayouts::CListOfLayouts(const std::string & name,
                               const CCopasiContainer * pParent):
    CCopasiVector<CLayout>(name, pParent),
    mKey(GlobalKeys.add("Layout", this))
{}

CListOfLayouts::~CListOfLayouts()
{
  GlobalKeys.remove(mKey);
}

const std::string& CListOfLayouts::getKey()
{
  return mKey;
}
