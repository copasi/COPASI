#ifndef COPASI_CGlobals
#define COPASI_CGlobals

#include <string>

#include "CFunctionDB.h"
#include "CVersion.h"

class CGlobals
{
// Attributes
public:
    CVersion ProgramVersion;
    
    CFunctionDB FunctionDB;
    double DefaultConc;

// Operations
public:
    CGlobals();
};

extern CGlobals Copasi;

#endif // COPASI_CGlobals

