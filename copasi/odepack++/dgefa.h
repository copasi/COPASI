/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/dgefa.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:29:35 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef ODEPACK_dgefa
#define ODEPACK_dgefa

/**
 * This maps the linpack routine dgefa to the lapack routine dgetrf.
 */

#define dgefa_(__a, __lda, __n, __ipvt, __info) \
 dgetrf_(__lda, __n, __a, __lda, __ipvt, __info)

#ifdef XXXX
C_INT dgefa_(double * a,
             C_INT * lda,
             C_INT * n,
             C_INT * ipvt,
             C_INT * info);

int dgetrf_(integer *m,
            integer *n,
            doublereal *a,
            integer * lda,
            integer *ipiv,
            integer *info);
#endif // XXXX

#endif // ODEPACK_dgefa
