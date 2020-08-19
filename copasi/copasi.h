// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include <sbml/common/libsbml-namespace.h>
#include <sedml/common/libsedml-namespace.h>

LIBSBML_CPP_NAMESPACE_USE
LIBSEDML_CPP_NAMESPACE_USE

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

#include "copasi/core/CCore.h"

#ifdef min
# undef min
#endif

#ifdef max
# undef max
#endif

#if defined(HAVE_APPLE) || __GNUC__ > 5 || (__GNUC__ == 5 && __GNUC_MINOR__ >= 3)
# include <cmath>
using std::isnan;
#endif

#if (defined __GNUC__ && __GNUC__ < 3)
# define ios_base ios
#endif

enum TriLogic
{
  TriUnspecified = -1,
  TriFalse = 0,
  TriTrue = 1
};

/* This is necessary to link with Intel MKL or LAPACK compiled with Intel under Visual C++ 8 */
#if defined COPASI_MAIN && defined _MSC_VER && _MSC_VER > 1200 && defined _DLL && _MSC_VER < 1900
extern "C"
{
  FILE _iob[3] = {__iob_func()[0], __iob_func()[1], __iob_func()[2]};
  int __argc = 0;
  char ** __argv = NULL;
}

#endif

#ifdef COPASI_MAIN
class CRootContainer;
CRootContainer * pRootContainer = NULL;

class QMutex;
QMutex * pCopasiGuiMutex = NULL;
#endif

/* Define Constructor/Destructor Trace */
#ifdef COPASI_DEBUG_TRACE
# include <time.h>
# if !defined(WIN32)
#   include <sys/time.h>
# endif

# ifdef COPASI_MAIN
#  if !defined(Darwin) && !defined(WIN32)
timeval C_init_time;
unsigned C_INT32 C_last_time = 0;
unsigned C_INT32 C_this_time;
#  endif // !Darwin
std::ofstream DebugFile("trace");
# else // not COPASI_MAIN
#  include <fstream>
#  if !defined(Darwin) && !defined(WIN32)
extern timeval C_init_time;
extern unsigned C_INT32 C_last_time;
extern unsigned C_INT32 C_this_time;
#  endif // !Darwin
extern std::ofstream DebugFile;
# endif // COPASI_MAIN

#  if !defined(Darwin) && !defined(WIN32)
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
#endif // COPASI_copasi
