// Main
//
// (C) Stefan Hoops 2002
//

#ifdef WIN32
# include <windows.h>
# include <winbase.h>
# include <direct.h>
# define getcwd _getcwd
# ifdef ERROR
#  undef ERROR
# endif
#else
# include <unistd.h>
#endif

#include <stdlib.h>

#define COPASI_MAIN
#define COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "COptionParser.h"
#include "COptions.h"

C_INT32 TestOptimization(void);

C_INT main(C_INT argc, char *argv[])
{
  unsigned C_INT32 i, imax;
  char PrgName[512];
  char Cwd[512];
  char *HOME;

  getcwd(Cwd, 512);
  HOME = getenv("HOME");

#ifdef WIN32
  GetModuleFileName(NULL, PrgName, 512);
#else
  strcpy(PrgName, argv[0]);
#endif
  std::cout << "Starting main program: " << PrgName << std::endl;
  Copasi = new CGlobals;

  try
    {
      /*
       * create a command line parser class and then tell it to parse your
       * command line.
       */
      copasi::COptionParser parser;
      parser.parse(".copasirc");
      parser.parse(argc, argv);

      /*
       * get the struct of options from the parser class so that you can
       * access the option values.
       */
      const copasi::options &options = parser.get_options();
      const copasi::option_locations &locations = parser.get_locations();
      const std::vector<std::string> &non_options =
        parser.get_non_options();

      std::cout << "CopsiDir \t'" << options.CopasiDir << "' "
      << locations.CopasiDir << std::endl;
      std::cout << "SystemFunctionDB \t'" << options.SystemFunctionDB << "' "
      << locations.SystemFunctionDB << std::endl;
      std::cout << "UserFunctionDB \t'" << options.UserFunctionDB << "' "
      << locations.UserFunctionDB << std::endl;
      std::cout << "ConfigFile \t'" << options.ConfigFile << "' "
      << locations.ConfigFile << std::endl;
      std::cout << "save \t'" << options.save << "' "
      << locations.save << std::endl;
      std::cout << "ImportSBML \t'" << options.ImportSBML << "' "
      << locations.ImportSBML << std::endl;
      std::cout << "ExportSBML \t'" << options.ExportSBML << "' "
      << locations.ExportSBML << std::endl;
      std::cout << std::endl;

      std::cout << "Flag \t'" << options.Flag << "' "
      << locations.Flag << std::endl;
      std::cout << "Bool \t'" << options.Bool << "' "
      << locations.Bool << std::endl;
      std::cout << std::endl;

      std::cout << "Defaults (" << options.Default.size() << "):" << std::endl;

      std::map<std::string, std::string>::const_iterator begin;
      std::map<std::string, std::string>::const_iterator end;
      for (begin = options.Default.begin(), end = options.Default.end();
           begin != end; begin++)
        std::cout << "  '" << begin->first << "'\t '" << begin->second
        << "'" << std::endl;
      std::cout << std::endl;

      for (i = 0, imax = non_options.size(); i < imax; i++)
        std::cout << non_options[i] << std::endl;

      COptions::init(argc, argv);
    }

  catch (copasi::autoexcept &e)
    {
      switch (e.get_autothrow_id())
        {
        case copasi::autothrow_help:
          std::cout << "Usage: " << argv[0] << " [options]\n";
          std::cout << e.what();
        }
    }

  catch (copasi::option_error &e)
    {
      std::cerr << argv[0] << ": " << e.what() << "\n";
      std::cerr << e.get_help_comment() << std::endl;
    }

  catch (CCopasiException Exception)
    {
      std::cout << Exception.getMessage().getText() << std::endl;
    }

  delete Copasi;
  std::cout << "Leaving main program." << std::endl;
  return 0;
}