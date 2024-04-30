// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef ODEPACK_dgbsl
#define ODEPACK_dgbsl

/**
 * This maps the linpack routine dgbsl to the lapack routine dgbtrs.
 */

#define dgbsl_(__ab, __lda, __n, __ml, __mu, __ipvt, __b, __job) \
  {\
    char __T = (*__job != (C_INT) 0) ? 'T': 'N'; \
    C_INT __info; \
    C_INT __one = 1; \
    dgbtrs_(&__T, __n, __ml, __mu, &__one, __ab, __lda, __ipvt, __b, __n, &__info); \
  }

#ifdef XXXX
C_INT dgbsl_(double * abd,
             C_INT * lda,
             C_INT * n,
             C_INT * ml,
             C_INT * mu,
             C_INT * ipvt,
             double * b,
             C_INT * job);

int dgbtrs_(char *trans,
            integer *n,
            integer *kl,
            integer * ku,
            integer *nrhs,
            doublereal *ab,
            integer *ldab,
            integer *ipiv,
            doublereal *b,
            integer *ldb,
            integer *info);
#endif // XXXX

#endif // ODEPACK_dgbsl
