#ifndef COPASI_utilities
#define COPASI_utilities

#include <string>
#include <stdio.h>
#include <stdarg.h>

#include "copasi.h"

#define INITIALTEXTSIZE 1024

/*
 *
 */
string StringPrint( char * format, ...);


    void lsoda_dgefa(C_FLOAT64 ** a, 
                     C_INT32 n, 
                     C_INT32 * ipvt, 
                     C_INT32 * info);

    C_INT32 lsoda_idamax(C_INT32 n,
                         C_FLOAT64 * dx,
                         C_INT32 incx);
			 
    void lsoda_dgesl(C_FLOAT64 ** a,
                     C_INT32 n,
                     C_INT32 * ipvt, 
                     C_FLOAT64 * b, 
                     C_INT32 job);

    void lsoda_daxpy(C_INT32 n,
                     C_FLOAT64 da, 
                     C_FLOAT64 * dx,
                     C_INT32 incx, 
                     C_FLOAT64 * dy,
                     C_INT32 incy);

    void lsoda_dscal(C_INT32 n,
                     C_FLOAT64 da,
                     C_FLOAT64 * dx,
                     C_INT32 incx);

    C_FLOAT64 lsoda_ddot(C_INT32 n, 
                         C_FLOAT64 * dx,
                         C_INT32 incx, 
                         C_FLOAT64 * dy,
                         C_INT32 incy);


#endif COPASI_utilities

