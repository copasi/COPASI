/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commandline/COptions.cpp,v $
   $Revision: 1.30 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/01 14:28:29 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#ifdef WIN32
# include <windows.h>
# include <winbase.h>
# include <direct.h>
# ifdef ERROR
#  undef ERROR
# endif
#else
# include <unistd.h>
#endif

#ifdef Darwin
# include "Carbon.h"
#endif

#include <sstream>
#include <errno.h>

#include "utilities/CCopasiMessage.h"
#include "utilities/CDirEntry.h"
#include "COptionParser.h"
#include "COptions.h"

COptions::optionType COptions::mOptions;
COptions::nonOptionType COptions::mNonOptions;

COptions::COptions()
{CONSTRUCTOR_TRACE;}

COptions::~COptions()
{DESTRUCTOR_TRACE;}

void COptions::init(C_INT argc, char *argv[])
{
  setValue("Self", (std::string) argv[0]);
  setValue("PWD", getPWD());

  {
    copasi::COptionParser * pPreParser = new copasi::COptionParser;
    pPreParser->parse(argc, argv);

    const copasi::options &PreOptions = pPreParser->get_options();

    setValue("CopasiDir", PreOptions.CopasiDir);
    if (compareValue("CopasiDir", (std::string) ""))
      {
        setValue("CopasiDir", getCopasiDir());
      }

    setValue("Home", PreOptions.Home);
    if (compareValue("Home", (std::string) ""))
      setValue("Home", getHome());

    setValue("Tmp", PreOptions.Tmp);
    if (compareValue("Tmp", (std::string) ""))
      setValue("Tmp", getTemp());

    setValue("ConfigDir", PreOptions.ConfigDir);
    if (compareValue("ConfigDir", (std::string) ""))
      setValue("ConfigDir", getConfigDir());

    setValue("ConfigFile", PreOptions.ConfigFile);
    if (compareValue("ConfigFile", (std::string) ""))
      setValue("ConfigFile", getConfigFile());

    delete pPreParser;
  }

  copasi::COptionParser * Parser = new copasi::COptionParser;

  std::string CopasiDir;
  getValue("CopasiDir", CopasiDir);
  std::string Home;
  getValue("Home", Home);

  mNonOptions = Parser->get_non_options();

  const copasi::options &Options = Parser->get_options();

  /* The values for ExampleDir and WizardDir are dependent on CopasiDir
     and on the OS. */

  getValue("CopasiDir", CopasiDir);
#ifdef Darwin
  setValue("ExampleDir", CDirEntry::dirName(CopasiDir) + "/examples");
  setValue("WizardDir", CopasiDir + "/Contents/Resources/doc/html");
#elif WIN32
  setValue("ExampleDir", CopasiDir + "\\share\\copasi\\examples");
  setValue("WizardDir", CopasiDir + "\\share\\copasi\\doc\\html");
#else // All unix flavors have the same installation structure.
  setValue("ExampleDir", CopasiDir + "/share/copasi/examples");
  setValue("WizardDir", CopasiDir + "/share/copasi/doc/html");
#endif

  /* Create manually for each option except for:
     CopasiDir, ConfigFile, Home, and Default
     setValue("OptionId", Options.OptionID); */

  if (Options.Tmp != "") setValue("Tmp", Options.Tmp);
  setValue("Verbose", Options.Verbose);
  setValue("License", Options.License);
  setValue("Save", Options.Save);
  setValue("ImportSBML", Options.ImportSBML);
  setValue("ExportSBML", Options.ExportSBML);

  delete Parser;
}

void COptions::cleanup()
{
  optionType::iterator begin = mOptions.begin();
  optionType::iterator end = mOptions.end();

  for (; begin != end; begin++) pdelete(begin->second);
}

const COptions::nonOptionType & COptions::getNonOptions() {return mNonOptions;}

std::string COptions::getEnvironmentVariable(const std::string & name)
{
  char * value = getenv(name.c_str());

  if (value) return (std::string) value;
  else return "";
}

std::string COptions::getCopasiDir(void)
{
  std::string CopasiDir;

  CopasiDir = getEnvironmentVariable("COPASIDIR");

#ifdef WIN32
  if (CopasiDir == "")
    {
      size_t PrgNameSize = 256;
      size_t Returned;
      char * PrgName = new char[PrgNameSize];

      while (!(Returned = GetModuleFileName(NULL, PrgName, PrgNameSize)) ||
             PrgNameSize == Returned)
        {
          if (GetLastError() != ERROR_ALREADY_EXISTS)
            {
              *PrgName = '\0';
              break;
            }

          delete [] PrgName;
          PrgNameSize *= 2;
          PrgName = new char[PrgNameSize];
        }

      CopasiDir = PrgName;
      delete [] PrgName;

      /* Get rid of the executable */
      CopasiDir = CDirEntry::dirName(CopasiDir);

      /* Get rid of bin or sbin */
      CopasiDir = CDirEntry::dirName(CopasiDir);
    }
#endif // WIN32

#ifdef Darwin
  if (CopasiDir == "")
    {
      CFURLRef pluginRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
      CFStringRef macPath = CFURLCopyFileSystemPath(pluginRef,
                            kCFURLPOSIXPathStyle);
      CopasiDir = CFStringGetCStringPtr(macPath, CFStringGetSystemEncoding());
    }
#endif // Darwin

  if (CopasiDir == "")
    CCopasiMessage Message(CCopasiMessage::RAW, MCConfiguration + 1);

  return CopasiDir;
}

std::string COptions::getPWD(void)
{
  size_t PWDSize = 256;
  char * PWD = NULL;

  while (!(PWD = getcwd(NULL, PWDSize)))
    {
      if (errno != ERANGE) break;
      PWDSize *= 2;
    }

  std::string pwd;
  if (PWD)
    {
      pwd = PWD;
      free(PWD);
    }
  else
    pwd = "";

  return pwd;
}

std::string COptions::getHome(void)
{
  std::string Home;

  Home = getEnvironmentVariable("HOME");

#ifdef WIN32
  if (Home == "")
    Home = getEnvironmentVariable("HOMEDRIVE")
           + getEnvironmentVariable("HOMEPATH");
#endif // WIN32

  if (Home == "")
    {
      std::ostringstream error;
      error << std::endl
      << "  use --home HOME" << std::endl
      << "  or set the environment variable HOME" << std::endl
      << "  to point to your home directory" << std::endl;

      throw copasi::option_error(error.str());
    }

  return Home;
}

std::string COptions::getTemp(void)
{
  std::string Temp, User, CreateCopasiDir, CreateUserDir;

  Temp = getEnvironmentVariable("TEMP");
  if (Temp == "") Temp = getEnvironmentVariable("TMP");

  User = getEnvironmentVariable("USER");
  if (User == "") User = getEnvironmentVariable("USERNAME");
  if (User == "") User = "CopasiUser";

  if (Temp == "") // OS specific fallback.
#ifdef WIN32
    Temp = getEnvironmentVariable("windir") + CDirEntry::Separator + "Temp";
#else
    Temp = "/tmp";
#endif // WIN32

  // Assure that Temp exists and is a directory.
  if (!CDirEntry::isDir(Temp) || !CDirEntry::isWritable(Temp))
    return "";

  CreateCopasiDir = Temp + CDirEntry::Separator + "copasi";
  CreateUserDir = CreateCopasiDir + CDirEntry::Separator + User;

  //Assure that CreateCopasiDir exists and is a writable directory.
  if (!CDirEntry::createDir("copasi", Temp))
    return Temp;

  Temp = CreateCopasiDir;
  //Assure that CreateUserDir exists and is a writable directory.
  if (!CDirEntry::createDir(User, Temp))
    return Temp;

  Temp = CreateUserDir;
  return Temp;
}

std::string COptions::getConfigDir(void)
{
  std::string Home;

  getValue("Home", Home);
  if (!CDirEntry::createDir(".copasi", Home))
    return Home;

  return Home + CDirEntry::Separator + ".copasi";
}

std::string COptions::getConfigFile(void)
{
  std::string ConfigDir;

  getValue("ConfigDir", ConfigDir);

  return ConfigDir + CDirEntry::Separator + "copasi";
}
