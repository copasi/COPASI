#ifndef COPASI_CGlobals
#define COPASI_CGlobals

#include <string>

#include "CMetab.h"
#include "CFunctionDB.h"
#include "CVersion.h"

class CGlobals
{
// Attributes
public:
    /**
     *
     */
    CVersion ProgramVersion;
    
    /**
     *
     */
    CFunctionDB FunctionDB;

    /**
     *  This is a hack at the moment to be able to read old configuration files
     */
    CMetabolitesOld OldMetabolites;
    
    /**
     *
     */
    C_FLOAT64 DefaultConc;

// Operations
public:
    /**
     *
     */
    CGlobals();

    /**
     *
     */
    ~CGlobals();
};

extern CGlobals Copasi;

#endif // COPASI_CGlobals

