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
#define C_INT int
#define C_INT16 short
#define C_FLOAT64 double
#define C_FLOAT32 float

//YH: new defined parameters used by more than one classes
#define SS_FOUND 1             //steady state found
#define SS_NOT_FOUND 0         //steady state not found
#define SS_SINGULAR_JACOBIAN 2
#define SS_DAMPING_LIMIT 3
#define SS_ITERATION_LIMIT 4
#define MCA_OK 0
#define MCA_SINGULAR 1





// protected free
#define pfree(p) {if (p) {free(p); p = NULL;}}
    
#endif // COPASI_copasi

