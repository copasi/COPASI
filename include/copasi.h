// copasi.h
// 
// This file contains compatability issues
// (C) Stefan Hoops 2001
//

#ifndef COPASI_copasi
#define COPASI_copasi

#include <assert.h>
#include <iostream>

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

#define C_INT32 long
#define C_INT16 short
#define C_FLOAT64 double
#define C_FLOAT32 float

// protected free
#define pfree(p) {if (p) {free(p); p = NULL;}}
    
#endif // COPASI_copasi
