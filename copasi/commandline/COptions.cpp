/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commandline/COptions.cpp,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/17 14:50:35 $
   End CVS Header */

#define COPASI_TRACE_CONSTRUCTION

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
#include "COptionParser.h"
#include "COptions.h"

COptions::optionType COptions::mOptions;
COptions::defaultType COptions::mDefaults;
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
      setValue("CopasiDir", getCopasiDir());

    setValue("Home", PreOptions.Home);
    if (compareValue("Home", (std::string) ""))
      setValue("Home", getHome());

    setValue("Tmp", PreOptions.Tmp);
    if (compareValue("Tmp", (std::string) ""))
      setValue("Tmp", getTemp());

    setValue("ConfigFile", PreOptions.ConfigFile);

    delete pPreParser;
  }

  copasi::COptionParser * Parser = new copasi::COptionParser;

  std::string CopasiDir;
  getValue("CopasiDir", CopasiDir);
  std::string Home;
  getValue("Home", Home);

  /* Parse the system wide configuration file */
  std::string ConfigFile(CopasiDir + "/etc/copasi.conf");
  try
    {
      Parser->parse(ConfigFile.c_str());
    }

  catch (copasi::option_error &e)
    {
      if (errno != ENOENT) throw(e);

#ifdef XXXX
      /* This is currently not needed since a system wide configuration
         is not supported */
      std::ostringstream error;
      error << std::endl
      << "file '" << ConfigFile << "' does not exist." << std::endl
      << "  use -c COPASIDIR or --copasidir COPASIDIR" << std::endl
      << "  or set the environment variable COPASIDIR" << std::endl
      << "  to point to the Copasi installation directory" << std::endl;

      throw copasi::option_error(error.str());
#endif // XXXX
    }

  /* Parse the user's configuration file */
  ConfigFile = Home + "/.copasirc";
  try
    {
      Parser->parse(ConfigFile.c_str());
    }

  catch (copasi::option_error &e)
    {
      if (errno != ENOENT) throw(e);

#ifdef XXXX
      /* Make sure that the user's configuration file exists in the future */
      /* :TODO: we should create a template that will be copied */
      std::ofstream f(ConfigFile.c_str());
#endif // XXXX
    }

  /* Parse the commandline specified file */
  if (!compareValue("ConfigFile", (std::string) ""))
    {
      getValue("ConfigFile", ConfigFile);
      Parser->parse(ConfigFile.c_str());
    }

  /* Parse the commandline arguments */
  Parser->parse(argc, argv);

  mNonOptions = Parser->get_non_options();

  const copasi::options &Options = Parser->get_options();
  mDefaults = Options.Default;

  /* The values for ExampleDir and WizardDir are dependent on CopasiDir
     and on the OS. */

  getValue("CopasiDir", CopasiDir);
#ifdef Darwin
  setValue("ExampleDir", CopasiDir + "/Contents/Resources/examples");
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
  setValue("SystemFunctionDB", Options.SystemFunctionDB);
  setValue("UserFunctionDB", Options.UserFunctionDB);
  setValue("CopasiFile", Options.CopasiFile);
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

std::string COptions::getDefault(const std::string & name)
{
  defaultType::iterator found = mDefaults.find(name);

  if (found == mDefaults.end()) return "<unset>";
  else return found->second;
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
      CopasiDir = CopasiDir.substr(0, CopasiDir.find_last_of('\\'));

      /* Get rid of bin or sbin */
      CopasiDir = CopasiDir.substr(0, CopasiDir.find_last_of('\\'));
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

#if (defined SunOS || defined Linux) // :TODO: use CCopasiMessage
  if (CopasiDir == "")
    {
      std::ostringstream error;
      error << std::endl
      << "  use -c COPASIDIR or --copasidir COPASIDIR" << std::endl
      << "  or set the environment variable COPASIDIR" << std::endl
      << "  to point to the Copasi installation directory" << std::endl;

      throw copasi::option_error(error.str());
    }
#endif // SunOS || Linux

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
  std::string Temp;

  Temp = getEnvironmentVariable("TEMP");

  if (Temp == "")
    Temp = getEnvironmentVariable("TMP");

  if (Temp == "")
#ifdef WIN32
    Temp = getEnvironmentVariable("windir") + "\\Temp";
#else
    Temp = "/tmp";
#endif // WIN32

  return Temp;
}
