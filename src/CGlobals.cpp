#include "CGlobals.h"
#include "utilities.h"

CGlobals::CGlobals()
{
    ProgramVersion.SetVersion(4,0,101);
    FunctionDB.SetFilename("FunctionDB.gps");
    FunctionDB.Init();

    DefaultConc = 0.0;
}

CGlobals::~CGlobals()
{
    FunctionDB.Delete();
}

CGlobals Copasi;
