// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#define dgees_(...)  LAPACK_dgees(__VA_ARGS__)
#define dgetrs_(...) LAPACK_dgetrs(__VA_ARGS__)
#define dgbtrs_(...) LAPACK_dgbtrs(__VA_ARGS__)
#define dtrtri_(...) LAPACK_dtrtri(__VA_ARGS__)
#define dlaset_(...) LAPACK_dlaset(__VA_ARGS__)
#define dpotrf_(...) LAPACK_dpotrf(__VA_ARGS__)
#define dpotrs_(...) LAPACK_dpotrs(__VA_ARGS__)
#define dtrexc_(...) LAPACK_dtrexc(__VA_ARGS__)
#define dtrsyl_(...) LAPACK_dtrsyl(__VA_ARGS__)
#define dsyev_(...)  LAPACK_dsyev(__VA_ARGS__)
#define dpotri_(...) LAPACK_dpotri(__VA_ARGS__)

// This is not exposed by lapack.h
integer dlaic1_(integer *job, integer *j, doublereal *x,
                doublereal *sest, doublereal *w, doublereal *gamma,
                doublereal *sestpr, doublereal *s, doublereal *c__);
