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

      std::cout << options.CopasiLib << " "
      << locations.CopasiLib << std::endl;
      std::cout << options.SystemFunctionDB << " "
      << locations.SystemFunctionDB << std::endl;
      std::cout << options.UserFunctionDB << " "
      << locations.UserFunctionDB << std::endl;
      std::cout << options.rc << " "
      << locations.rc << std::endl;
      std::cout << options.save << " "
      << locations.save << std::endl;

      unsigned C_INT32 i, imax = non_options.size();
      for (i = 0; i < imax; i++)
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