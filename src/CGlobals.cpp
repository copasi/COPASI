#include "CGlobals.h"
#include "utilities.h"

CGlobals::CGlobals()
{
    VersionMajor = 4;
    VersionMinor = 0;
    VersionDevel = 1;
    
    Version = StringPrint("%d.%d.%d", VersionMajor, 
                          VersionMinor, VersionDevel);
    
//    FunctionDB = "FunctionDB.gps";
    DefaultConc = 0.0;
}

CGlobals Copasi;
