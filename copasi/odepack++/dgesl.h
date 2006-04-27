/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/dgesl.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:29:35 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef ODEPACK_debsl
#define ODEPACK_debsl

/**
 * This maps the linpack routine dgesl to the lapack routine dgetrs.
 */

#define dgesl_(__a, __lda, __n, __ipvt, __b, __job) \
 {\
 char __T = (*__job != (C_INT) 0) ? 'T': 'N'; \
 C_INT __info; \
 C_INT __one = 1; \
  dgetrs_(&__T, __n, &__one, __a, __lda, __ipvt, __b, __n, &__info); \
 }

#ifdef XXXX
C_INT dgesl_(double * a,
             C_INT * lda,
             C_INT * n,
             C_INT * ipvt,
             double * b,
             C_INT * job);

int dgetrs_(char *trans,
            integer *n,
            integer *nrhs,
            doublereal *a,
            integer *lda,
            integer *ipiv,
            doublereal *b,
            integer * ldb,
            integer *info);
#endif // XXXX

#endif // ODEPACK_debsl
