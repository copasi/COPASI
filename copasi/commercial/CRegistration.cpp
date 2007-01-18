// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/CRegistration.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/01/18 20:51:53 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sstream>

#include "copasi.h"

#include "CRegistration.h"
#include "GenericDecode.h"
#include "Cmd5.h"

#include "commandline/COptions.h"

/*
Seed Combo :en
Seed Length: 13
Minimum Email Length: 1
Minimum Name Length: 1
Minimum HotSync ID Length: 1
Length of Constant: 1
Constant value: T
Sequence Length: 3
Alternate Text: Contact support@copasi.org to obtain your registration code.
Scramble Order: U7,S0,U0,U8,S2,U3,U12,U1,U11,D3,C0,U5,D2,D0,S1,D1,U4,U10,U2,U6,U9,
ASCII Digit(For text to Number Conversion):2
Math Operation(Example:36A(36->Operand,A-Addition)): 23S,5A,R,37S,1A,R,7A,13S,R,29S,17S,R,8A,R,4A,7S,R,R,3A,11S,19S,
New Base: 52
Base Character Set: dAK0QyEfTD2UkGM3aehxYRi48uz19Wb7qgFJCtXNH65ncrwmpPLj
Registration code format(^ is place holder for check digit) : COPASI-####-####-#^####-####-####-####[-#G3Q]
 */

const char config[] =
  "SUPPLIERID:VTIP%E:1%N:1%H:1%COMBO:en%SDLGTH:13%CONSTLGTH:1%CONSTVAL:F%SEQL:3%"
  "ALTTEXT:Contact support@copasi.org to obtain your registration code.%"
  "SCRMBL:U7,,S0,,U0,,U8,,S2,,U3,,U12,,U1,,U11,,D3,,C0,,U5,,D2,,D0,,S1,,D1,,U4,,U10,,U2,,U6,,U9,,%"
  "ASCDIG:2%MATH:23S,,5A,,R,,37S,,1A,,R,,7A,,13S,,R,,29S,,17S,,R,,8A,,R,,4A,,7S,,R,,R,,3A,,11S,,19S,,%"
  "BASE:52%BASEMAP:dAK0QyEfTD2UkGM3aehxYRi48uz19Wb7qgFJCtXNH65ncrwmpPLj%"
  "REGFRMT:COPASI-####-####-#^####-####-####-####[-#G3Q]";

CRegistration::CRegistration(const std::string & name,
                             const CCopasiContainer * pParent):
    CCopasiParameterGroup(name, pParent),
    mpRegisteredEmail(NULL),
    mpRegisteredUser(NULL),
    mpRegistrationCode(NULL),
    mpSignature(NULL),
    mExpirationDate(-1)
{initializeParameter();}

CRegistration::CRegistration(const CRegistration & src,
                             const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mpRegisteredEmail(NULL),
    mpRegisteredUser(NULL),
    mpRegistrationCode(NULL),
    mpSignature(NULL),
    mExpirationDate(src.mExpirationDate)
{initializeParameter();}

CRegistration::CRegistration(const CCopasiParameterGroup & group,
                             const CCopasiContainer * pParent):
    CCopasiParameterGroup(group, pParent),
    mpRegisteredEmail(NULL),
    mpRegisteredUser(NULL),
    mpRegistrationCode(NULL),
    mpSignature(NULL),
    mExpirationDate(-1)
{initializeParameter();}

CRegistration::~CRegistration() {}

void CRegistration::initializeParameter()
{
  mpRegisteredEmail =
    assertParameter("Registered Email", CCopasiParameter::STRING, std::string(""))->getValue().pSTRING;
  mpRegisteredUser =
    assertParameter("Registered User", CCopasiParameter::STRING, std::string(""))->getValue().pSTRING;
  mpRegistrationCode =
    assertParameter("Registration Code", CCopasiParameter::STRING, std::string(""))->getValue().pSTRING;
  mpSignature =
    assertParameter("Signature", CCopasiParameter::STRING, std::string(""))->getValue().pSTRING;
}

void CRegistration::setRegisteredEmail(const std::string & registeredEmail)
{*mpRegisteredEmail = registeredEmail;}

const std::string & CRegistration::getRegisteredEmail() const
  {return *mpRegisteredEmail;}

void CRegistration::setRegisteredUser(const std::string & registeredUser)
{*mpRegisteredUser = registeredUser;}

const std::string & CRegistration::getRegisteredUser() const
  {return *mpRegisteredUser;}

void CRegistration::setRegistrationCode(const std::string & registrationCode)
{*mpRegistrationCode = registrationCode;}

const std::string & CRegistration::getRegistrationCode() const
  {return *mpRegistrationCode;}

bool CRegistration::isValidRegistration() const
  {
    bool Trial = false;

    // Check whether the registration code is correct.
    if (!decodeGenericRegCode(config, mpRegistrationCode->c_str()))
      {
        // We have a valid registration code.
        Trial = !strcmp("T", getConstant());
        if (Trial)
          {
            unsigned C_INT32 Date = strtoul(getDate(), NULL, 10);

            // day and year license created
            unsigned C_INT32 Day = Date / 10 - 1;   // 0 - 365
            unsigned C_INT32 Year = Date % 10;  // 0 - 9

            time_t CurrentTime = time(NULL);
            tm * pLocalTime = localtime(&CurrentTime);

            // License creation year minus 1900
            // Was the license created in the previous decade?
            if (Year != 0 && (pLocalTime->tm_year % 10) == 0)
              Year += pLocalTime->tm_year - 10;
            else
              Year += pLocalTime->tm_year - (pLocalTime->tm_year % 10);

            // End of day
            pLocalTime->tm_sec = 0;
            pLocalTime->tm_min = 0;
            pLocalTime->tm_hour = 24;

            // License creation day + 31
            pLocalTime->tm_year = Year;
            pLocalTime->tm_mday += Day + 31 - pLocalTime->tm_yday;

            mExpirationDate = mktime(pLocalTime);
          }
        else
          {
            mExpirationDate = -1;
          }
      }
    else
      {
        CCopasiMessage(CCopasiMessage::RAW, MCRegistration + 1);
        return false;
      }

    // Check whether Email and User are correct.
    setUserEmail(mpRegisteredEmail->c_str());
    setUserName(mpRegisteredUser->c_str());
    createUserSeed();

    if (strcmp(getUserSeed(), getCreatedUserSeed()))
      {
        CCopasiMessage(CCopasiMessage::RAW, MCRegistration + 2);
        return false;
      }

    // Check whether a trial license is expired.
    if (Trial)
      {
        unsigned C_INT32 CurrentTime = time(NULL);

        if (CurrentTime > mExpirationDate)
          {
            std::string ExpirationStr = ctime(&mExpirationDate);
            // Remove the line break character '\n'
            ExpirationStr.erase(ExpirationStr.length() - 1);

            CCopasiMessage(CCopasiMessage::RAW, MCRegistration + 3, ExpirationStr.c_str());
            return false;
          }
      }

    std::stringstream Message;
    Message << *mpRegistrationCode << * mpRegisteredEmail << *mpRegisteredUser;

    // To prevent copying the configuration file
    std::string ConfigFile;
    COptions::getValue("ConfigFile", ConfigFile);
    Message << ConfigFile;

    *mpSignature = Cmd5::digest(Message);

    return true;
  }

bool CRegistration::isValidSignature() const
  {
    std::stringstream Message;
    Message << *mpRegistrationCode << * mpRegisteredEmail << *mpRegisteredUser;

    // To prevent copying the configuration file
    std::string ConfigFile;
    COptions::getValue("ConfigFile", ConfigFile);
    Message << ConfigFile;

    if (*mpSignature == Cmd5::digest(Message))
      return true;

    // Detected tempering with the registration information
    // therefore we reset it.
    if (isValidRegistration())
      {
        *mpRegistrationCode = "";
        *mpRegisteredEmail = "";
        *mpRegisteredUser = "";
      }

    return false;
  }

std::string CRegistration::getExpirationDate() const
  {
    std::string ExpirationDate;

    if (mExpirationDate != -1)
      {
        ExpirationDate = ctime(&mExpirationDate);
        // Remove the line break character '\n'
        ExpirationDate.erase(ExpirationDate.length() - 1);
      }
    else
      {
        ExpirationDate = "unlimited";
      }

    return ExpirationDate;
  }
