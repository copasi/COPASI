// copasi.h
// 
// This file contains compatability issues
// (C) Stefan Hoops 2001
//

#ifndef COPASI_copasi
#define COPASI_copasi

using namespace std ;

#ifdef WIN32 
#define COPASI__msbug (enum)
#define vsnprintf _vsnprintf
#else 
#define COPASI__msbug
#endif  // WIN32

// protected free
#define pfree(p) {if (p) {free(p); p = NULL;}}
    
#include "CCopasiMessage.h"
#include "CCopasiException.h"

#endif // COPASI_copasi
