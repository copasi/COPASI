#include "CGlobals.h"
#include "utilities.h"

CGlobals::CGlobals()
{
  ProgramVersion.setVersion(4,0,101);
  FunctionDB.setFilename("FunctionDB.gps");
  FunctionDB.initialize();

  DefaultConc = 0.0;
}

CGlobals::~CGlobals()
{
  FunctionDB.cleanup();
}

CGlobals Copasi;
