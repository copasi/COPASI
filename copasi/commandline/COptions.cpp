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

#include <sstream>
#include <errno.h>

#include "utilities/CCopasiMessage.h"
#include "COptionParser.h"
#include "COptions.h"

std::map< std::string, COptions::COptionValue * > COptions::mOptions;

COptions::COptions()
{CONSTRUCTOR_TRACE;}

COptions::~COptions()
{
  std::map< std::string, COptionValue * >::iterator begin;
  std::map< std::string, COptionValue * >::iterator end;

  for (begin = mOptions.begin(), end = mOptions.end();
       begin != end; begin++)
    pdelete(begin->second);

  DESTRUCTOR_TRACE;
}

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
    }

  /* Parse the commandline specified file */
  if (!compareValue("ConfigFile", (std::string) ""))
    {
      getValue("ConfigFile", ConfigFile);
      Parser->parse(ConfigFile.c_str());
    }

  /* Parse the commandline arguments */
  Parser->parse(argc, argv);

  const copasi::options &Options = Parser->get_options();

  /* Create manually for each option except CopasiDir, ConfigFile and Home:
     setValue("OptionId", Options.OptionID); */
}

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

  if (CopasiDir == "")
    {
      std::ostringstream error;
      error << std::endl
      << "  use -c COPASIDIR or --copasidir COPASIDIR" << std::endl
      << "  or set the environment variable COPASIDIR" << std::endl
      << "  to point to the Copasi installation directory" << std::endl;

      throw copasi::option_error(error.str());
    }
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
    {
      Home = getEnvironmentVariable("APPDATA");
      if (Home != "")
        {
          Home += "\\copasi";
          CreateDirectory(Home.c_str(), NULL);
        }
    }
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