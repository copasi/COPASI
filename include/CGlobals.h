#ifndef COPASI_CGlobals
#define COPASI_CGlobals

#include <string>

#include "CFunctionDB.h"

class CGlobals
{
// Attributes
public:
    long VersionMajor;
    long VersionMinor;
    long VersionDevel;
    string Version;
    
    CFunctionDB FunctionDB;
    double DefaultConc;

// Operations
public:
    CGlobals();
};

extern CGlobals Copasi;

#endif // COPASI_CGlobals
