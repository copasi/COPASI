/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/utility.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/15 20:21:07 $
   End CVS Header */

#ifndef COPASI_utilities
#define COPASI_utilities

#include <string> 
// #include <stdio.h>
#include <stdarg.h>

#define INITIALTEXTSIZE 1024

struct tm;

/**
 * Returns the time pointed to by pTime in ISO format
 */
std::string ISODateTime(tm * pTime);

/**
 * Returns the current local time in ISO format
 */
std::string LocalTimeStamp();

/**
 * Returns the current time in ISO format
 */
std::string UTCTimeStamp();

/**
 * Check whether the given string represents a number
 * @param const std::string & str
 * @return bool isNumber
 */
bool isNumber(const std::string & str);

/**
 *  sprintf like function for strings
 *  @param "const char *" format sprintf like format string
 *  @param ...
 *  @return "string" 
 */
std::string StringPrint(const char * format, ...);

/**
 *
 */
void dgefa(C_FLOAT64 ** a,
           C_INT32 n,
           C_INT32 * ipvt,
           C_INT32 * info);

/**
 *  Returns index of the componen the maximum of the absolute values of 
 *  the components of the vector dx. The vector dx is incremented (n-1) 
 *  times by the incx.
 *  @param "C_INT32" n number of elements in the vector dx
 *  @param "C_FLOAT64 *" dx (fortran style vector)
 *  @param "C_INT32" incx increment stepsize
 *  @return "C_INT32" index of the component with maximum of absolute values
 */
C_INT32 idamax(C_INT32 n,
               C_FLOAT64 * dx,
               C_INT32 incx);

/**
 *  Returns the maximum of the absolute values of the components of 
 *  the vector dx. The vector dx is incremented (n-1) times by the incx.
 *  @param "C_INT32" n number of elements in the vector dx
 *  @param "C_FLOAT64 *" dx (fortran style vector)
 *  @param "C_INT32" incx increment stepsize
 *  @return "C_FLOAT64" maximum of absolute values
 */
C_FLOAT64 xNorm(C_INT32 n,
                C_FLOAT64 * dx,
                C_INT32 incx);

/**
 *
 */
void dgesl(C_FLOAT64 ** a,
           C_INT32 n,
           C_INT32 * ipvt,
           C_FLOAT64 * b,
           C_INT32 job);

/**
 *
 */
void daxpy(C_INT32 n,
           C_FLOAT64 da,
           C_FLOAT64 * dx,
           C_INT32 incx,
           C_FLOAT64 * dy,
           C_INT32 incy);

#ifdef XXXX 
/**
 *
 */
void lsoda_dscal(C_INT32 n,
                 C_FLOAT64 da,
                 C_FLOAT64 * dx,
                 C_INT32 incx);
#endif // XXXX

/**
 *
 */
C_FLOAT64 ddot(C_INT32 n,
               C_FLOAT64 * dx,
               C_INT32 incx,
               C_FLOAT64 * dy,
               C_INT32 incy);

/*
 * Fixes a string to be a SName element from SBML
 * (this is a destructive function, some changes are irreversible)
 *
 */
void FixSName(const std::string &original, std::string &fixed)
;

/*
 * Fixes a string to a XHTML valid equivalent
 */
void FixXHTML(const std::string &original, std::string &fixed)
;

#endif // COPASI_utilities
