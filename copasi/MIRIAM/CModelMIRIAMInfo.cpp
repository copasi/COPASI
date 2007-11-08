// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/11/08 22:26:35 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "report/CKeyFactory.h"

#include "CModelMIRIAMInfo.h"

CModelMIRIAMInfo::CModelMIRIAMInfo()
{
  mAuthors.add(CAuthor("KAMAL", NULL, "Aejaaz"));
}

CModelMIRIAMInfo::~CModelMIRIAMInfo()
{}

CCopasiVector <CAuthor> & CModelMIRIAMInfo::getAuthors()
{return mAuthors;}

CAuthor* CModelMIRIAMInfo::createAuthor(const std::string name)
{
  CAuthor * pAuthor = new CAuthor(name);

  if (!mAuthors.add(pAuthor, true))
    {
      delete pAuthor;
      return NULL;
    }

  return pAuthor;
}

bool CModelMIRIAMInfo::removeAuthor(const std::string & key)
{
  CAuthor * pAuthor =
    dynamic_cast< CAuthor * >(GlobalKeys.get(key));

  if (!pAuthor)
    return false;

  //Check if Author exists
  unsigned C_INT32 index =
    mAuthors.getIndex(pAuthor);

  if (index == C_INVALID_INDEX)
    return false;

  mAuthors.CCopasiVector< CAuthor >::remove(index);
  return true;
}
