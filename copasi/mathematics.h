/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/Attic/mathematics.h,v $
   $Revision: 1.7.38.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2011/03/02 20:17:47 $
   End CVS Header */

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_mathematics
#define COPASI_mathematics

#include <math.h>
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif
#ifndef M_E
#define M_E            2.7182818284590452354   /* e */
#endif

#ifdef WIN32 // These are not part of ANSI C and Visual C++ 6.0 misses them.
static inline double asinh(double value)
{return log(value + sqrt(value * value + 1.0));}

static inline double acosh(double value)
{return log(value + sqrt(value * value - 1.0));}

static inline double atanh(double value)
{return (.5 * log((1.0 + value) / (1.0 - value)));}

static inline double round(double value)
{return  value < 0.0 ? -floor(-value + 0.5) : floor(value + 0.5);}

#endif // WIN32

#endif // COPASI_mathematics
