// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/11/01 05:31:29 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CModelMIRIAMInfo.h"

CModelMIRIAMInfo::CModelMIRIAMInfo()
{
  CAuthor *tmp = new CAuthor ("KAMAL", "Aejaaz");
  mAuthors.push_back(tmp);
}

CModelMIRIAMInfo::~CModelMIRIAMInfo()
{
  std::vector<CAuthor*>::iterator it = mAuthors.begin();
  std::vector<CAuthor*>::iterator end = mAuthors.end();
  for (; it != end; ++it)
    {
      delete *it;
      *it = NULL;
    }
  mAuthors.clear();
}

std::vector <CAuthor*> & CModelMIRIAMInfo::getAuthors()
{return mAuthors;}

CAuthor* CModelMIRIAMInfo::createAuthor(std::string name)
{
  CAuthor *tmp = new CAuthor ("", name);
  mAuthors.push_back(tmp);
  return tmp;
}
