// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/Attic/CAuthor.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/11/01 05:31:29 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CAuthor.h"

CAuthor::CAuthor(const std::string & familyName, const std::string & givenName) :
    mEmail(""), mURL("")
{
  mFamilyName = familyName;
  mGivenName = givenName;
}

const std::string & CAuthor::getFamilyName() const
  {return mFamilyName;}

const std::string & CAuthor::getGivenName() const
  {return mGivenName;}

const std::string & CAuthor::getEmail() const
  {return mEmail;}

const std::string & CAuthor::getURL() const
  {return mURL;}

std::string CAuthor::getFullName() const
  {return mGivenName + " " + mFamilyName;}

void CAuthor::setFamilyName(const std::string familyName)
{mFamilyName = familyName;}

void CAuthor::setGivenName(const std::string givenName)
{mGivenName = givenName;}

void CAuthor::setEmail(const std::string Email)
{mEmail = Email;}

void CAuthor::setURL(const std::string URL)
{mURL = URL;}
