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
#include <sstream>

#define COPASI_MAIN
#define COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "COptionParser.h"
#include "COptions.h"

C_INT32 TestOptimization(void);

C_INT main(C_INT argc, char *argv[])
{
  char PrgName[512];

#ifdef WIN32
  GetModuleFileName(NULL, PrgName, 512);
#else
  strcpy(PrgName, argv[0]);
#endif
  std::cout << "Starting main program: " << PrgName << std::endl;
  Copasi = new CGlobals;

  try
    {
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