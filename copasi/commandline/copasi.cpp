// Main
//
// (C) Stefan Hoops 2002
//

#define COPASI_MAIN

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "COptionParser.h"

C_INT32 TestOptimization(void);

C_INT main(C_INT argc, char *argv[])
{
  unsigned C_INT32 i, imax;

  cout << "Starting main program." << endl;
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

      std::cout << "libdir \t'" << options.libdir << "' "
      << locations.libdir << std::endl;
      std::cout << "SystemFunctionDB \t'" << options.SystemFunctionDB << "' "
      << locations.SystemFunctionDB << std::endl;
      std::cout << "UserFunctionDB \t'" << options.UserFunctionDB << "' "
      << locations.UserFunctionDB << std::endl;
      std::cout << "configFile \t'" << options.configFile << "' "
      << locations.configFile << std::endl;
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
    }

  catch (copasi::autoexcept &e)
    {
      switch (e.get_autothrow_id())
        {
        case copasi::autothrow_help:
          std::cout << "Usage: " << argv[0] << " [options]\n";
          std::cout << e.what();
          return 0;
        }
    }

  catch (copasi::option_error &e)
    {
      std::cerr << argv[0] << ": " << e.what() << "\n";
      std::cerr << e.get_help_comment() << std::endl;
      return 1;
    }

  catch (CCopasiException Exception)
    {
      cout << Exception.getMessage().getText() << endl;
    }

  delete Copasi;
  cout << "Leaving main program." << endl;
  return 0;
}