#include "CGlobals.h"
#include "utilities.h"

CGlobals::CGlobals()
{
    ProgramVersion.SetVersion(4,0,101);
    FunctionDB.SetFilename("FunctionDB.gps");

    DefaultConc = 0.0;
}

CGlobals Copasi;


