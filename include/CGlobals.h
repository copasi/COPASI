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
    C_FLOAT64 DefaultConc;

// Operations
public:
    CGlobals();
};

extern CGlobals Copasi;

#endif // COPASI_CGlobals

