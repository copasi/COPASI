#define  COPASI_TRACE_CONSTRUCTION

//#include "copasi.h"
#include "CGlobals.h" 
//#include "utilities.h"

#include "utilities/CCopasiException.h"

CGlobals::CGlobals():
    DefaultConc(0.0),
    DefaultVolume(1.0)

{
  try
    {
      ProgramVersion.setVersion(4, 0, 101);
      FunctionDB.setFilename("FunctionDB.gps");
      FunctionDB.initialize();
      Model = NULL;
    }

  catch (CCopasiException Exception)
    {
      std::cout << Exception.getMessage().getText() << std::endl;
    }
}

CGlobals::~CGlobals()
{
  FunctionDB.cleanup();
  OldMetabolites.cleanup();
}

void CGlobals::setArguments(C_INT argc, char *argv[])
{
  C_INT i, imax = argc;
  Arguments.resize(imax);

  for (i = 0; i < imax; i++)
    Arguments[i] = argv[i];
}

// CGlobals Copasi;
