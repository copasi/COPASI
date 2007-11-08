// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/Attic/CAuthor.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/11/08 22:26:35 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "report/CKeyFactory.h"

#include "CAuthor.h"

CAuthor::CAuthor(const std::string & familyName,
                 const CCopasiContainer * pParent, const std::string & givenName) :
    CCopasiContainer(familyName, pParent, "Author"),
    mKey(GlobalKeys.add("Author", this)),
    mFamilyName(familyName),
    mGivenName (givenName),
    mEmail(""), mURL("")
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CAuthor::CAuthor(const CAuthor & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Author", this)),
    mFamilyName(src.mFamilyName),
    mGivenName(src.mGivenName),
    mEmail(src.mEmail), mURL(src.mURL)

{
  CONSTRUCTOR_TRACE;
  initObjects();
}

void CAuthor::initObjects()
{}

CAuthor::~CAuthor()
{
  GlobalKeys.remove(mKey);
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

const std::string & CAuthor::getKey() const {return mKey;} //By G
