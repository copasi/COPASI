/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/CRegistration.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/12 21:22:08 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CRegistration.h"

CRegistration::CRegistration(const std::string & name,
                             const CCopasiContainer * pParent):
    CCopasiParameterGroup(name, pParent),
    mpRegisteredUser(NULL),
    mpRegistrationCode(NULL),
    mpSignature(NULL)
{initializeParameter();}

CRegistration::CRegistration(const CRegistration & src,
                             const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mpRegisteredUser(NULL),
    mpRegistrationCode(NULL),
    mpSignature(NULL)
{initializeParameter();}

CRegistration::CRegistration(const CCopasiParameterGroup & group,
                             const CCopasiContainer * pParent):
    CCopasiParameterGroup(group, pParent),
    mpRegisteredUser(NULL),
    mpRegistrationCode(NULL),
    mpSignature(NULL)
{initializeParameter();}

CRegistration::~CRegistration() {}

void CRegistration::initializeParameter()
{
  mpRegisteredUser =
    assertParameter("Registered User", CCopasiParameter::STRING, std::string(""))->getValue().pSTRING;
  mpRegistrationCode =
    assertParameter("Registration Code", CCopasiParameter::STRING, std::string(""))->getValue().pSTRING;
  mpSignature =
    assertParameter("Signature", CCopasiParameter::STRING, std::string(""))->getValue().pSTRING;
}

void CRegistration::setRegisteredUser(const std::string & registeredUser)
{*mpRegisteredUser = registeredUser;}

const std::string & CRegistration::getRegisteredUser() const
  {return *mpRegisteredUser;}

void CRegistration::setRegistrationCode(const std::string & registrationCode)
{*mpRegistrationCode = registrationCode;}

const std::string & CRegistration::getRegistrationCode() const
  {return *mpRegistrationCode;}

bool CRegistration::isValid() const
  {
    // :TODO: this needs to be implemented
    return false;
  }
