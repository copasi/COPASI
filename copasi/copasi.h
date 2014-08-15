// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// copasi.h
//
// This file contains compatability issues
// (C) Stefan Hoops 2001
//

#ifndef COPASI_copasi
#define COPASI_copasi

/* #define AVOGADRO 6.0221367e23 */
#define AVOGADRO 6.0221415e23

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
# if  _MSC_VER >= 1400
#  define _CRT_SECURE_NO_DEPRECATE

// avoid the following warning:
// The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _strdup. See online help for details.
#  pragma warning(disable : 4996)
# endif
#endif  // WIN32

#include <assert.h>
#include <fstream>
#include <limits>

//YH: new defined parameters used by more than one classes
#define SS_FOUND 1             //steady state found
#define SS_NOT_FOUND 0         //steady state not found
#define SS_SINGULAR_JACOBIAN 2
#define SS_DAMPING_LIMIT 3
#define SS_ITERATION_LIMIT 4
#define MCA_OK 0
#define MCA_SINGULAR 1

#ifdef min
# undef min
#endif

#ifdef max
# undef max
#endif

#if (defined SunOS || defined __CYGWIN__ || defined Darwin)
# define C_INT64 long long int
# define LLONG_CONST(n) n ## LL
# define C_INT32 int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
# define abs64 abs
#else
#ifdef WIN32
# define C_INT64 __int64
# define LLONG_CONST(n) n ## i64
# define C_INT32 int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
# define vsnprintf _vsnprintf // they just have a different name for this guy
# define snprintf  _snprintf  // they just have a different name for this guy
# define strcasecmp _stricmp  // they just have a different name for this guy
# define strdup _strdup       // they just have a different name for this guy
# define isnan _isnan         // they just have a different name for this guy
# define finite _finite       // they just have a different name for this guy
#if _MSC_VER < 1600
# define min _cpp_min         // they just have a different name for this guy
# define max _cpp_max         // they just have a different name for this guy
#endif // _MSC_VER
# define abs64 _abs64
#else
# define C_INT64 long long int
# define LLONG_CONST(n) n ## LL
# define C_INT32 int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
# define abs64 abs
#endif
#endif

#ifdef Darwin
# ifndef isnan
#  define isnan(__x) ((__x == __x) != true)
# endif
#endif

#if (defined __GNUC__ && __GNUC__ < 3)
# define ios_base ios
#endif

// for compatibility with default CLAPACK f2c
#if ((defined __LP64__) && (!(defined HAVE_CLAPACK_H) || (defined Darwin)))
# define C_INT int
#else
# define C_INT long
#endif

enum TriLogic
{
  TriUnspecified = -1,
  TriFalse = 0,
  TriTrue = 1
};

/* This is necessary to link with Intel MKL or LAPACK compiled with Intel under Visual C++ 8 */
#if defined COPASI_MAIN && defined _MSC_VER && _MSC_VER > 1200 && defined _DLL
extern "C"
{
  FILE _iob[3] = {__iob_func()[0], __iob_func()[1], __iob_func()[2]};
  int __argc = 0;
  char ** __argv = NULL;
}

#endif

#ifdef COPASI_MAIN
class CCopasiRootContainer;
CCopasiRootContainer * pRootContainer = NULL;

class QMutex;
QMutex * pCopasiGuiMutex = NULL;
#endif

/* Define Constructor/Destructor Trace */
#ifdef COPASI_DEBUG_TRACE
# include <time.h>
# include <sys/time.h>

# ifdef COPASI_MAIN
#  ifndef Darwin
timeval C_init_time;
unsigned C_INT32 C_last_time = 0;
unsigned C_INT32 C_this_time;
#  endif // !Darwin
std::ofstream DebugFile("trace");
# else // not COPASI_MAIN
#  include <fstream>
#  ifndef Darwin
extern timeval C_init_time;
extern unsigned C_INT32 C_last_time;
extern unsigned C_INT32 C_this_time;
#  endif // !Darwin
extern std::ofstream DebugFile;
# endif // COPASI_MAIN

# ifndef Darwin
#  include <iostream>
#  define TIME_TRACE(f, l) {\
    gettimeofday(&C_init_time, NULL); \
    C_this_time = C_init_time.tv_sec * 1000 + C_init_time.tv_usec; \
    DebugFile << f <<"(" << l << "):\t" << C_this_time - C_last_time  << std::endl; \
    C_last_time = C_this_time;\
  }
# endif // !Darwin

# if (defined COPASI_TRACE_CONSTRUCTION)
#  include <typeinfo>
#  define CONSTRUCTOR_TRACE \
  {DebugFile << "Construct:\t" << typeid(*this).name() \
             << "\tAddress:\t" << (void *) this << std::endl;}
#  define DESTRUCTOR_TRACE \
  {DebugFile << "Destruct:\t" << typeid(*this).name() \
             << "\tAddress:\t" << (void *) this << std::endl;}
# endif // COPASI_TRACE_CONSTRUCTION

# define DEBUG_OUT(s) {DebugFile << (s) << std::endl;}
#else
# if !defined (NDEBUG) && !defined (_DEBUG)
#  define NDEBUG
# endif // !defined (NDEBUG) && !defined (_DEBUG)
# define DEBUG_OUT(s)
#endif // COPASI_DEBUG_TRACE

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
#define pdeletev(p) {if (p) {delete[] p; p = NULL;}}
#define pcleanup(p) {if (p) {p->cleanup(); delete p; p = NULL;}}

// suppress unused parameter warnings
#define C_UNUSED(p)
#define COPASI_DEPRECATED
#define NOMINMAX
#define C_INVALID_INDEX (std::numeric_limits< size_t >::max())
#endif // COPASI_copasi
