#include "CGlobals.h"
#include "utilities.h"

CGlobals::CGlobals()
{
  try
    {
      ProgramVersion.setVersion(4,0,101);
      FunctionDB.setFilename("FunctionDB.gps");
      FunctionDB.initialize();
      Model = NULL;
      
      DefaultConc = 0.0;
    }

  catch (CCopasiException Exception)
    {
      cout << Exception.getMessage().getText() << endl;
    }
}

CGlobals::~CGlobals()
{
  FunctionDB.cleanup();
}

void CGlobals::setArguments(C_INT argc, char *argv[])
{
  C_INT i, imax = argc;
  Arguments.resize(imax);

  for (i=0; i<imax; i++)
    Arguments[i] = argv[i];
}

      
// CGlobals Copasi;
