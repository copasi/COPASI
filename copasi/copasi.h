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

#if (defined SunOS || defined __CYGWIN__ || defined Darwin)
# define C_INT32 long
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
#else
#ifdef WIN32
# define C_INT32 int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
# define vsnprintf _vsnprintf // they just have a different name for this guy
# define snprintf  _snprintf  // they just have a different name for this guy
# define strcasecmp _stricmp  // they just have a different name for this guy
# define min _cpp_min
# define max _cpp_max
#else
# define C_INT32 long
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
#endif
#endif

#if (defined __GNUC__ && __GNUC__ < 3)
# define ios_base ios
#endif

#ifdef USE_MKL
# define C_INT int
#else
# if (defined USE_CLAPACK || defined Darwin)
#  define C_INT long
# else
#  error Neither USE_CLAPACK or USE_MKL is defined!
# endif
#endif

enum TriLogic
{
  TriUnspecified = -1,
  TriFalse = 0,
  TriTrue = 1
};

/* Define Constructor/Destructor Trace */
#ifdef COPASI_DEBUG
#include <time.h>
#include <sys/timeb.h>
# ifdef COPASI_MAIN
#  ifndef Darwin
struct timeb init_time;
unsigned C_INT32 last_time = 0;
unsigned C_INT32 this_time;
#  endif // !Darwin
std::ofstream DebugFile("trace");
# else
#  include <fstream>
#  ifndef Darwin
extern struct timeb init_time;
extern unsigned C_INT32 last_time;
extern unsigned C_INT32 this_time;
#  endif // !Darwin
extern std::ofstream DebugFile;
# endif // COPASI_MAIN
# ifndef Darwin
#  include <iostream>
#  define TIME_TRACE(f, l) {\
  ftime(&init_time); \
  this_time = init_time.time * 1000 + init_time.millitm; \
  std::cout << f <<"(" << l << "):\t" << this_time - last_time  << std::endl; \
  last_time = this_time;\
}
# endif // !Darwin
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

#ifndef TIME_TRACE
# define TIME_TRACE(f, l)
#endif

// protected free
#define pfree(p) {if (p) {free(p); p = NULL;}}
#define pdelete(p) {if (p) {delete p; p = NULL;}}
#define pcleanup(p) {if (p) {p->cleanup(); delete p; p = NULL;}}

// suppress unused parameter warnings
#define C_UNUSED(p)
#define COPASI_DEPRECATED
#define C_INVALID_INDEX ((unsigned C_INT32) -1)
#endif // COPASI_copasi
