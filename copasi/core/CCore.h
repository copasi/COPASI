// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CCore
#define COPASI_CCore

#include <limits>

#include <copasi/config.h>

#define C_INVALID_INDEX (std::numeric_limits< size_t >::max())

#if (defined SunOS || defined __CYGWIN__ || defined Darwin)
# define C_INT64 long long int
# define LLONG_CONST(n) n ## LL
# define C_INT32 int
# define C_UINT32 unsigned int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
# define abs64 abs
#else
#ifdef WIN32
# ifndef _USE_MATH_DEFINES
# define _USE_MATH_DEFINES 1
# endif // _USE_MATH_DEFINES
# define C_INT64 __int64
# define LLONG_CONST(n) n ## i64
# define C_INT32 int
# define C_UINT32 unsigned int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
#if _MSC_VER < 1900
# define vsnprintf _vsnprintf // they just have a different name for this guy
# define snprintf  _snprintf  // they just have a different name for this guy
# define isnan _isnan         // they just have a different name for this guy
#endif
# define strcasecmp _stricmp  // they just have a different name for this guy
# define strdup _strdup       // they just have a different name for this guy
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
# define C_UINT32 unsigned int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
# define abs64 abs
#endif
#endif

// for compatibility with default CLAPACK f2c
#ifdef F2C_INTEGER
# define C_INT F2C_INTEGER
#else
# if ((defined __LP64__) && (!(defined HAVE_CLAPACK_H) || (defined Darwin)))
#  define C_INT int
# else
#  define C_INT long
# endif
#endif

#ifdef F2C_LOGICAL
# define C_LOGICAL F2C_LOGICAL
#else
# define C_LOGICAL C_INT
#endif

#include "copasi/core/CFlags.h"

class CMathUpdateSequence;

class CCore
{
public:
  typedef CMathUpdateSequence CUpdateSequence;

  enum struct SimulationContext
  {
    Default,
    // This is used to indicate deterministic simulation
    // Deterministic = 0x1,
    // This must be set when using the reduced model
    UseMoieties,
    // This updates the total mass of a moiety and must be set
    // at the beginning of the simulation or after events
    UpdateMoieties,
    // This is used to indicate stochastic simulation
    // Stochastic = 0x8,
    // Event handling
    EventHandling,
    // This is used to detect whether a delay value depends on other delay values.
    DelayValues,
    __SIZE
  };

  typedef CFlags< SimulationContext > SimulationContextFlag;

  enum struct Framework
  {
    Concentration = 0,
    ParticleNumbers,
    __SIZE
  };

  /**
   * String representation of the valid model types.
   */
  static const CEnumAnnotation< std::string, Framework > FrameworkNames;
};

#endif // COPASI_CCore
