// copasi.h
//
// This file contains compatability issues
// (C) Stefan Hoops 2001
//

#ifndef COPASI_copasi
#define COPASI_copasi

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243) 
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
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

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#if (defined sparc || defined __CYGWIN__)
# define C_INT32 long
# define C_INT long
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
#else
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
# define strcasecmp _stricmp  // they just have a different name for this guy
# define min _cpp_min
# define max _cpp_max
#else
# define C_INT32 long
# define C_INT int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
#endif
#endif

enum TriLogic
{
  TriUnspecified = -1,
  TriFalse = 0,
  TriTrue = 1
};

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
    << ", \tAddress: " << (void *) this << std::endl;}
#  define DESTRUCTOR_TRACE \
  {DebugFile << "Destruct: " << typeid(*this).name() \
    << ", \tAddress: " << (void *) this << std::endl;}
# endif // COPASI_TRACE_CONSTRUCTION
#endif // COPASI_DEBUG

#ifndef CONSTRUCTOR_TRACE
# define CONSTRUCTOR_TRACE
#endif

#ifndef DESTRUCTOR_TRACE
# define DESTRUCTOR_TRACE
#endif

// protected free
#define pfree(p) {if (p) {free(p); p = NULL;}}
#define pdelete(p) {if (p) {delete p; p = NULL;}}
#define pcleanup(p) {if (p) {p->cleanup(); delete p; p = NULL;}}

// suppress unused parameter warnings
#define C_UNUSED(p) 
// #define COPASI_DEPRECATED
#define C_INVALID_INDEX ((unsigned C_INT32) -1)
#endif // COPASI_copasi
