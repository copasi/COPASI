// copasi.h
// 
// This file contains compatability issues
// (C) Stefan Hoops 2001
//

#ifndef COPASI_copasi
#define COPASI_copasi

#include <string>
#include <assert.h>

using namespace std ;

#ifdef WIN32 
#define vsnprintf _vsnprintf // they just have a different name for this guy
#define snprintf  _snprintf  // they just have a different name for this guy
#endif  // WIN32

#ifdef TRUE
#undef TRUE
#endif
#define TRUE 1

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

// protected free
#define pfree(p) {if (p) {free(p); p = NULL;}}
    
#include "CCopasiMessage.h"
#include "CCopasiException.h"

#endif // COPASI_copasi
