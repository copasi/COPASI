/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/website/license/Attic/license.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/21 18:28:55 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>
#include <fstream>
#include <time.h>

#include "COptions.h"
#include "../../copasi/commercial/GenericDecode.h"

license::options Options;
std::ostream * pOutput = NULL;

const char config[] =
  "SUPPLIERID:VTIP%E:1%N:1%H:1%COMBO:en%SDLGTH:13%CONSTLGTH:1%CONSTVAL:T%SEQL:3%"
  "ALTTEXT:Contact support@copasi.org to obtain your registration code.%"
  "SCRMBL:U7,,S0,,U0,,U8,,S2,,U3,,U12,,U1,,U11,,D3,,C0,,U5,,D2,,D0,,S1,,D1,,U4,,U10,,U2,,U6,,U9,,%"
  "ASCDIG:2%MATH:23S,,5A,,R,,37S,,1A,,R,,7A,,13S,,R,,29S,,17S,,R,,8A,,R,,4A,,7S,,R,,R,,3A,,11S,,19S,,%"
  "BASE:52%BASEMAP:dAK0QyEfTD2UkGM3aehxYRi48uz19Wb7qgFJCtXNH65ncrwmpPLj%"
  "REGFRMT:COPASI-####-####-#^####-####-####-####[-#G3Q]";

bool init(int argc, char *argv[]);
int create();
int check();

int main(int argc, char *argv[])
{
  int retcode = 0;

  if (!init(argc, argv)) return 1;

  // Determine the apropriate output target
  if (Options.Output != "")
    {
      pOutput = new std::ofstream(Options.Output.c_str());
    }
  else
    {
      pOutput = &std::cout;
    }

  if (Options.Create)
    retcode = create();
  else
    retcode = check();

  // Close the ouput if needed
  if (Options.Output != "" && pOutput != NULL)
    delete pOutput;

  return retcode;
}

bool init(int argc, char *argv[])
{
  license::COptions Parser;

  try
    {
      Parser.parse(argc, argv, false);

      if (Parser.get_options().Input != "")
        Parser.parse(Parser.get_options().Input.c_str(), false);

      Parser.finalize();

      Options = Parser.get_options();
    }

  catch (license::autoexcept &e)
    {
      switch (e.get_autothrow_id())
        {
        case license::autothrow_help:
          std::cout << "Usage: " << argv[0] << " [options]\n";
          std::cout << e.what();
        }

      return false;
    }

  catch (license::option_error &e)
    {
      std::cerr << argv[0] << ": " << e.what() << "\n";
      std::cerr << e.get_help_comment() << std::endl;

      return false;
    }
  return true;
}

int create()
{
  return 1;
}

int check()
{
  time_t ExpirationDate = 0;

  // Check whether the registration code is correct.
  if (!decodeGenericRegCode(config, Options.RegistrationCode.c_str()))
    {
      unsigned int Date = strtoul(getDate(), NULL, 10);

      // day and year license created
      unsigned int Day = Date / 10 - 1;   // 0 - 365
      unsigned int Year = Date % 10;  // 0 - 9

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

      if (!strcmp("T", getConstant()))
        {
          // License creation day + 31
          pLocalTime->tm_year = Year;
          pLocalTime->tm_mday += Day + 31 - pLocalTime->tm_yday;
        }
      else
        {
          // License creation year + 1
          pLocalTime->tm_year = Year + 1;
          pLocalTime->tm_mday += Day - pLocalTime->tm_yday;
        }

      ExpirationDate = mktime(pLocalTime);
    }
  else
    {
      ExpirationDate = 0;

      *pOutput << "Invalid registration code: \"" << Options.RegistrationCode << "\"." << std::endl;
      return 1;
    }

  // Check whether Email and User are correct.
  setUserEmail(Options.RegisteredEmail.c_str());
  setUserName(Options.RegisteredUser.c_str());
  createUserSeed();

  if (strcmp(getUserSeed(), getCreatedUserSeed()))
    {
      *pOutput << "The user and/or email information does not match the registration code." << std::endl;
      return 1;
    }

  // Check whether the license is expired.

  time_t CurrentTime = time(NULL);

  if (CurrentTime > ExpirationDate)
    {
      std::string ExpirationStr = ctime(&ExpirationDate);
      // Remove the line break character '\n'
      ExpirationStr.erase(ExpirationStr.length() - 1);

      *pOutput << "The license expired at: \"" << ExpirationStr << "\"." << std::endl;
      return 1;
    }

  return 0;
}
