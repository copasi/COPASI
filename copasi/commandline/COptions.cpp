#define COPASI_TRACE_CONSTRUCTION

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

#include "copasi.h"

#include "utilities/CCopasiMessage.h"
#include "COptionParser.h"
#include "COptions.h"

map< std::string, COptions::COptionValue * > COptions::mOptions;

COptions::COptions()
{CONSTRUCTOR_TRACE;}

COptions::~COptions()
{
  std::map< std::string, COptionValue * >::iterator begin;
  std::map< std::string, COptionValue * >::const_iterator end;

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
  Parser->parse(ConfigFile.c_str());

  /* Parse the user's configuration file */
  ConfigFile = Home + ".copasirc";
  Parser->parse(ConfigFile.c_str());

  /* Parse the commandline specified file */
  if (!compareValue("ConfigFile", (std::string) ""))
    {
      getValue("ConfigFile", ConfigFile);
      Parser->parse(ConfigFile.c_str());
    }

  /* Parse the commandline arguments */
  Parser->parse(argc, argv);

  const copasi::options &Options = Parser->get_options();

  /* Create manually for each option except CopasiDir and ConfigFile:
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
#ifdef WIN32
  size_t PrgNameSize = 1024
                       char * PrgName = new char[PrgNameSize];
  if (!GetModuleFileName(NULL, PrgName, PrgNameSize)) fatalError();

  CopasiDir = PrgName;
  delete [] PrgName;

  /* Get rid of the executable */
  CopasiDir = CopasiDir.substr(0, CopasiDir.find_last_of('\\'));

  /* Get rid of bin or sbin */
  CopasiDir = CopasiDir.substr(0, CopasiDir.find_last_of('\\'));

  setValue("CopasiDir", CopasiDir);
#else
  CopasiDir = getEnvironmentVariable("COPASIDIR");
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
  size_t PWDSize = 64;
  char * PWD = NULL;

  while (!(PWD = getcwd(NULL, PWDSize)))
    {
      if (errno != ERANGE) break;
      PWDSize *= 2;
    }

  if (PWD)
    return (std::string) PWD;
  else
    return "";
}

std::string COptions::getHome(void)
{
  std::string Home;
#ifdef WIN32
#else
  Home = getEnvironmentVariable("HOME");
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