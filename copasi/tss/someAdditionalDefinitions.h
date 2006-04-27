/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/someAdditionalDefinitions.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:32:27 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef DBL_MAX
#define DBL_MAX  1e+308
#endif

#ifndef PI
#define PI           3.14159265358979323846
#endif

#ifndef EXPONENTIALE
#define EXPONENTIALE          2.7182818284590452354   /* e */
#endif

#ifndef INFINITY
#define INFINITY              (2 * 1e+308)
#endif

#ifndef TRUE
#define TRUE                 1
#endif

#ifndef FALSE
#define FALSE                0
#endif

#ifdef SOME_C_FUNCTIONS //These are not part of ANSI C and Visual C++ 6.0 misses them.

double asinh(double value)
{return log(value + sqrt(value * value + 1.0));}

double acosh(double value)
{return log(value + sqrt(value * value - 1.0));}

double atanh(double value)
{return (.5 * log((1.0 + value) / (1.0 - value)));}

#endif // SOME_C_FUNCTIONS

#ifdef  SOME_COPASI_FUNCTIONS

double sec(double value)
{return 1.0 / cos(value);}

double csc(double value)
{return 1.0 / sin(value);}

double cot(double value)
{return 1.0 / tan(value);}

double sech(double value)
{return 1.0 / cosh(value);}

double csch(double value)
{return 1.0 / sinh(value);}

double coth(double value)
{return 1.0 / tanh(value);}

double arcsec(double value)
{return acos(1.0 / value);}

double arccsc(double value)
{return asin(1.0 / value);}

double arccot(double value)
{return atan(1.0 / value);}

double asech(double value)
{return acosh(1.0 / value);}

double acsch(double value)
{return asinh(1.0 / value);}

double acoth(double value)
{return atanh(1.0 / value);}

double factorial(double value)
{
  if (value < 0.0 ||
      value != ceil(value))
    return tan(PI / 2); // this should signal overflow;

  if (value > 170)
    return DBL_MAX * 2;

  if (value == 0.0)
    return 0.0;

  double Value = 1.0;
  double Result = 1.0;

  while (Value < value) Result *= Value++;

  return Result;
}

double minus(double value)
{return - value;}

double plus(double value)
{return value;}

double copasiNot(double value)
{
  if (value != 0.0) return 0.0;
  else return 1.0;
}

#endif  // SOME_COPASI_FUNCTIONS
