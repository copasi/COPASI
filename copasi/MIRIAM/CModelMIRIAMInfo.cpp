// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/10/27 01:45:50 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CModelMIRIAMInfo.h"

CModelMIRIAMInfo::CModelMIRIAMInfo()
{
  CAuthor *tmp = new CAuthor ("KAMAL", "Aejaaz");
  mAuthors.push_back(*tmp);
}

std::vector <CAuthor> & CModelMIRIAMInfo::getAuthors()
{return mAuthors;}
