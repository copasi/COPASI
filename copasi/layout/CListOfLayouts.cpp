// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CListOfLayouts.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/26 18:11:51 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

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

void CListOfLayouts::addLayout(CLayout * layout, const std::map<std::string, std::string> & m)
{
  if (layout)
    add(layout, true);

  //TODO: store map
}
