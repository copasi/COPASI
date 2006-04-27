/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/dgbfa.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:29:35 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef ODEPACK_dgbfa
#define ODEPACK_dgbfa

/**
 * This maps the linpack routine dgbfa to the lapack routine dgbtrf.
 */

#define dgbfa_(__ab, __lda, __n, __ml, __mu, __ipvt, __info) \
 dgbtrf_(__lda, __n, __ml, __mu, __ab, __lda, __ipvt, __info)

#ifdef XXXX
C_INT dgbfa_(double * ABD,
             C_INT * LDA,
             C_INT * N,
             C_INT * ML,
             C_INT * MU,
             C_INT * ipvt,
             C_INT * info);

int dgbtrf_(integer *m,
            integer *n,
            integer *kl,
            integer *ku,
            doublereal *ab,
            integer *ldab,
            integer *ipiv,
            integer *info);
#endif // XXXX
#endif // ODEPACK_dgbfa
