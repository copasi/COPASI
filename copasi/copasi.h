// copasi.h
//
// This file contains compatability issues
// (C) Stefan Hoops 2001
//

#ifndef COPASI_copasi
#define COPASI_copasi

#ifdef WIN32
# pragma warning (disable: 4786)
#endif  // WIN32

#include <assert.h>
#include <fstream>

//YH: new defined parameters used by more than one classes
#define SS_FOUND 1             //steady state found
#define SS_NOT_FOUND 0         //steady state not found
#define SS_SINGULAR_JACOBIAN 2
#define SS_DAMPING_LIMIT 3
#define SS_ITERATION_LIMIT 4
#define MCA_OK 0
#define MCA_SINGULAR 1

#if (defined sparc || defined __CYGWIN__)
# define C_INT32 long
# define C_INT int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
#endif

#if (defined i386 && !defined __CYGWIN__)
# define C_INT32 int
# define C_INT int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
#endif

#ifdef WIN32
# define C_INT32 int
# define C_INT int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
# define vsnprintf _vsnprintf // they just have a different name for this guy
# define snprintf  _snprintf  // they just have a different name for this guy
# define timeb _timeb         // they just have a different name for this guy
# define ftime _ftime         // they just have a different name for this guy
#endif  // WIN32

/* Define COPASI_DEBUG */
#ifndef NDEBUG              // for gcc
# define COPASI_DEBUG
#else
# ifdef _DEBUG             // for Visual Studio
#  define COPASI_DEBUG
# else
#  undef COPASI_DEBUG
# endif // _DEBUG
#endif // not NDEBUG

/* Define Constructor/Destructor Trace */
#ifdef COPASI_DEBUG
# ifdef COPASI_MAIN

std::ofstream DebugFile("trace");
# else
#  include <fstream>

extern std::ofstream DebugFile;
# endif // COPASI_MAIN
# if (defined COPASI_TRACE_CONSTRUCTION)
#  include <typeinfo>
#  define CONSTRUCTOR_TRACE \
  {DebugFile << "Construct: " << typeid(*this).name() \
    << ", \tAddress: " << (void *) this << std::endl; }
#  define DESTRUCTOR_TRACE \
  {DebugFile << "Destruct: " << typeid(*this).name() \
    << ", \tAddress: " << (void *) this << std::endl; }
# endif // COPASI_TRACE_CONSTRUCTION
#endif // COPASI_DEBUG

#ifndef CONSTRUCTOR_TRACE
# define CONSTRUCTOR_TRACE
#endif

#ifndef DESTRUCTOR_TRACE
# define DESTRUCTOR_TRACE
#endif

#ifdef TRUE
# undef TRUE
#endif
#define TRUE 1

#ifdef FALSE
# undef FALSE
#endif
#define FALSE 0

// protected free
#define pfree(p) {if (p) {free(p); p = NULL; }}
#define pdelete(p) {if (p) {delete p; p = NULL; }}
#define pcleanup(p) {if (p) {p->cleanup(); delete p; p = NULL; }}

#endif // COPASI_copasi
