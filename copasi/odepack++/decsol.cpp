/* decsol.f -- translated by f2c (version 20160102).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/
#include "decsol.h"

/* Subroutine */ int dec_(integer *n, integer *ndim, doublereal *a, integer *
	ip, integer *ier)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Local variables */
    static integer i__, j, k, m;
    static doublereal t;
    static integer nm1, kp1;

/* VERSION REAL DOUBLE PRECISION */
/* ----------------------------------------------------------------------- */
/*  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION. */
/*  INPUT.. */
/*     N = ORDER OF MATRIX. */
/*     NDIM = DECLARED DIMENSION OF ARRAY  A . */
/*     A = MATRIX TO BE TRIANGULARIZED. */
/*  OUTPUT.. */
/*     A(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U . */
/*     A(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L. */
/*     IP(K), K.LT.N = INDEX OF K-TH PIVOT ROW. */
/*     IP(N) = (-1)**(NUMBER OF INTERCHANGES) OR O . */
/*     IER = 0 IF MATRIX A IS NONSINGULAR, OR K IF FOUND TO BE */
/*           SINGULAR AT STAGE K. */
/*  USE  SOL  TO OBTAIN SOLUTION OF LINEAR SYSTEM. */
/*  DETERM(A) = IP(N)*A(1,1)*A(2,2)*...*A(N,N). */
/*  IF IP(N)=O, A IS SINGULAR, SOL WILL DIVIDE BY ZERO. */

/*  REFERENCE.. */
/*     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER, */
/*     C.A.C.M. 15 (1972), P. 274. */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    a_dim1 = *ndim;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    *ier = 0;
    ip[*n] = 1;
    if (*n == 1) {
	goto L70;
    }
    nm1 = *n - 1;
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	kp1 = k + 1;
	m = k;
	i__2 = *n;
	for (i__ = kp1; i__ <= i__2; ++i__) {
	    if ((d__1 = a[i__ + k * a_dim1], fabs(d__1)) > (d__2 = a[m + k *
		    a_dim1], fabs(d__2))) {
		m = i__;
	    }
/* L10: */
	}
	ip[k] = m;
	t = a[m + k * a_dim1];
	if (m == k) {
	    goto L20;
	}
	ip[*n] = -ip[*n];
	a[m + k * a_dim1] = a[k + k * a_dim1];
	a[k + k * a_dim1] = t;
L20:
	if (t == 0.) {
	    goto L80;
	}
	t = 1. / t;
	i__2 = *n;
	for (i__ = kp1; i__ <= i__2; ++i__) {
/* L30: */
	    a[i__ + k * a_dim1] = -a[i__ + k * a_dim1] * t;
	}
	i__2 = *n;
	for (j = kp1; j <= i__2; ++j) {
	    t = a[m + j * a_dim1];
	    a[m + j * a_dim1] = a[k + j * a_dim1];
	    a[k + j * a_dim1] = t;
	    if (t == 0.) {
		goto L45;
	    }
	    i__3 = *n;
	    for (i__ = kp1; i__ <= i__3; ++i__) {
/* L40: */
		a[i__ + j * a_dim1] += a[i__ + k * a_dim1] * t;
	    }
L45:
/* L50: */
	    ;
	}
/* L60: */
    }
L70:
    k = *n;
    if (a[*n + *n * a_dim1] == 0.) {
	goto L80;
    }
    return 0;
L80:
    *ier = k;
    ip[*n] = 0;
    return 0;
/* ----------------------- END OF SUBROUTINE DEC ------------------------- */
} /* dec_ */



/* Subroutine */ int sol_(integer *n, integer *ndim, doublereal *a,
	doublereal *b, integer *ip)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Local variables */
    static integer i__, k, m;
    static doublereal t;
    static integer kb, km1, nm1, kp1;

/* VERSION REAL DOUBLE PRECISION */
/* ----------------------------------------------------------------------- */
/*  SOLUTION OF LINEAR SYSTEM, A*X = B . */
/*  INPUT.. */
/*    N = ORDER OF MATRIX. */
/*    NDIM = DECLARED DIMENSION OF ARRAY  A . */
/*    A = TRIANGULARIZED MATRIX OBTAINED FROM DEC. */
/*    B = RIGHT HAND SIDE VECTOR. */
/*    IP = PIVOT VECTOR OBTAINED FROM DEC. */
/*  DO NOT USE IF DEC HAS SET IER .NE. 0. */
/*  OUTPUT.. */
/*    B = SOLUTION VECTOR, X . */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    --b;
    a_dim1 = *ndim;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    if (*n == 1) {
	goto L50;
    }
    nm1 = *n - 1;
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	kp1 = k + 1;
	m = ip[k];
	t = b[m];
	b[m] = b[k];
	b[k] = t;
	i__2 = *n;
	for (i__ = kp1; i__ <= i__2; ++i__) {
/* L10: */
	    b[i__] += a[i__ + k * a_dim1] * t;
	}
/* L20: */
    }
    i__1 = nm1;
    for (kb = 1; kb <= i__1; ++kb) {
	km1 = *n - kb;
	k = km1 + 1;
	b[k] /= a[k + k * a_dim1];
	t = -b[k];
	i__2 = km1;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* L30: */
	    b[i__] += a[i__ + k * a_dim1] * t;
	}
/* L40: */
    }
L50:
    b[1] /= a[a_dim1 + 1];
    return 0;
/* ----------------------- END OF SUBROUTINE SOL ------------------------- */
} /* sol_ */



/* Subroutine */ int dech_(integer *n, integer *ndim, doublereal *a, integer *
	lb, integer *ip, integer *ier)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Local variables */
    static integer i__, j, k, m;
    static doublereal t;
    static integer na, nm1, kp1;

/* VERSION REAL DOUBLE PRECISION */
/* ----------------------------------------------------------------------- */
/*  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION OF A HESSENBERG */
/*  MATRIX WITH LOWER BANDWIDTH LB */
/*  INPUT.. */
/*     N = ORDER OF MATRIX A. */
/*     NDIM = DECLARED DIMENSION OF ARRAY  A . */
/*     A = MATRIX TO BE TRIANGULARIZED. */
/*     LB = LOWER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED, LB.GE.1). */
/*  OUTPUT.. */
/*     A(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U . */
/*     A(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L. */
/*     IP(K), K.LT.N = INDEX OF K-TH PIVOT ROW. */
/*     IP(N) = (-1)**(NUMBER OF INTERCHANGES) OR O . */
/*     IER = 0 IF MATRIX A IS NONSINGULAR, OR K IF FOUND TO BE */
/*           SINGULAR AT STAGE K. */
/*  USE  SOLH  TO OBTAIN SOLUTION OF LINEAR SYSTEM. */
/*  DETERM(A) = IP(N)*A(1,1)*A(2,2)*...*A(N,N). */
/*  IF IP(N)=O, A IS SINGULAR, SOL WILL DIVIDE BY ZERO. */

/*  REFERENCE.. */
/*     THIS IS A SLIGHT MODIFICATION OF */
/*     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER, */
/*     C.A.C.M. 15 (1972), P. 274. */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    a_dim1 = *ndim;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    *ier = 0;
    ip[*n] = 1;
    if (*n == 1) {
	goto L70;
    }
    nm1 = *n - 1;
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	kp1 = k + 1;
	m = k;
/* Computing MIN */
	i__2 = *n, i__3 = *lb + k;
	na = min(i__2,i__3);
	i__2 = na;
	for (i__ = kp1; i__ <= i__2; ++i__) {
	    if ((d__1 = a[i__ + k * a_dim1], fabs(d__1)) > (d__2 = a[m + k *
		    a_dim1], fabs(d__2))) {
		m = i__;
	    }
/* L10: */
	}
	ip[k] = m;
	t = a[m + k * a_dim1];
	if (m == k) {
	    goto L20;
	}
	ip[*n] = -ip[*n];
	a[m + k * a_dim1] = a[k + k * a_dim1];
	a[k + k * a_dim1] = t;
L20:
	if (t == 0.) {
	    goto L80;
	}
	t = 1. / t;
	i__2 = na;
	for (i__ = kp1; i__ <= i__2; ++i__) {
/* L30: */
	    a[i__ + k * a_dim1] = -a[i__ + k * a_dim1] * t;
	}
	i__2 = *n;
	for (j = kp1; j <= i__2; ++j) {
	    t = a[m + j * a_dim1];
	    a[m + j * a_dim1] = a[k + j * a_dim1];
	    a[k + j * a_dim1] = t;
	    if (t == 0.) {
		goto L45;
	    }
	    i__3 = na;
	    for (i__ = kp1; i__ <= i__3; ++i__) {
/* L40: */
		a[i__ + j * a_dim1] += a[i__ + k * a_dim1] * t;
	    }
L45:
/* L50: */
	    ;
	}
/* L60: */
    }
L70:
    k = *n;
    if (a[*n + *n * a_dim1] == 0.) {
	goto L80;
    }
    return 0;
L80:
    *ier = k;
    ip[*n] = 0;
    return 0;
/* ----------------------- END OF SUBROUTINE DECH ------------------------ */
} /* dech_ */



/* Subroutine */ int solh_(integer *n, integer *ndim, doublereal *a, integer *
	lb, doublereal *b, integer *ip)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, k, m;
    static doublereal t;
    static integer kb, na, km1, nm1, kp1;

/* VERSION REAL DOUBLE PRECISION */
/* ----------------------------------------------------------------------- */
/*  SOLUTION OF LINEAR SYSTEM, A*X = B . */
/*  INPUT.. */
/*    N = ORDER OF MATRIX A. */
/*    NDIM = DECLARED DIMENSION OF ARRAY  A . */
/*    A = TRIANGULARIZED MATRIX OBTAINED FROM DECH. */
/*    LB = LOWER BANDWIDTH OF A. */
/*    B = RIGHT HAND SIDE VECTOR. */
/*    IP = PIVOT VECTOR OBTAINED FROM DEC. */
/*  DO NOT USE IF DECH HAS SET IER .NE. 0. */
/*  OUTPUT.. */
/*    B = SOLUTION VECTOR, X . */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    --b;
    a_dim1 = *ndim;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    if (*n == 1) {
	goto L50;
    }
    nm1 = *n - 1;
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	kp1 = k + 1;
	m = ip[k];
	t = b[m];
	b[m] = b[k];
	b[k] = t;
/* Computing MIN */
	i__2 = *n, i__3 = *lb + k;
	na = min(i__2,i__3);
	i__2 = na;
	for (i__ = kp1; i__ <= i__2; ++i__) {
/* L10: */
	    b[i__] += a[i__ + k * a_dim1] * t;
	}
/* L20: */
    }
    i__1 = nm1;
    for (kb = 1; kb <= i__1; ++kb) {
	km1 = *n - kb;
	k = km1 + 1;
	b[k] /= a[k + k * a_dim1];
	t = -b[k];
	i__2 = km1;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* L30: */
	    b[i__] += a[i__ + k * a_dim1] * t;
	}
/* L40: */
    }
L50:
    b[1] /= a[a_dim1 + 1];
    return 0;
/* ----------------------- END OF SUBROUTINE SOLH ------------------------ */
} /* solh_ */


/* Subroutine */ int decc_(integer *n, integer *ndim, doublereal *ar, 
	doublereal *ai, integer *ip, integer *ier)
{
    /* System generated locals */
    integer ar_dim1, ar_offset, ai_dim1, ai_offset, i__1, i__2, i__3;
    doublereal d__1, d__2, d__3, d__4;

    /* Local variables */
    static integer i__, j, k, m;
    static doublereal ti, tr;
    static integer nm1, kp1;
    static doublereal den, prodi, prodr;

/* VERSION COMPLEX DOUBLE PRECISION */
/* ----------------------------------------------------------------------- */
/*  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION */
/*  ------ MODIFICATION FOR COMPLEX MATRICES -------- */
/*  INPUT.. */
/*     N = ORDER OF MATRIX. */
/*     NDIM = DECLARED DIMENSION OF ARRAYS  AR AND AI . */
/*     (AR, AI) = MATRIX TO BE TRIANGULARIZED. */
/*  OUTPUT.. */
/*     AR(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U ; REAL PART. */
/*     AI(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U ; IMAGINARY PART. */
/*     AR(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L. */
/*                                                    REAL PART. */
/*     AI(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L. */
/*                                                    IMAGINARY PART. */
/*     IP(K), K.LT.N = INDEX OF K-TH PIVOT ROW. */
/*     IP(N) = (-1)**(NUMBER OF INTERCHANGES) OR O . */
/*     IER = 0 IF MATRIX A IS NONSINGULAR, OR K IF FOUND TO BE */
/*           SINGULAR AT STAGE K. */
/*  USE  SOL  TO OBTAIN SOLUTION OF LINEAR SYSTEM. */
/*  IF IP(N)=O, A IS SINGULAR, SOL WILL DIVIDE BY ZERO. */

/*  REFERENCE.. */
/*     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER, */
/*     C.A.C.M. 15 (1972), P. 274. */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    ai_dim1 = *ndim;
    ai_offset = 1 + ai_dim1;
    ai -= ai_offset;
    ar_dim1 = *ndim;
    ar_offset = 1 + ar_dim1;
    ar -= ar_offset;

    /* Function Body */
    *ier = 0;
    ip[*n] = 1;
    if (*n == 1) {
	goto L70;
    }
    nm1 = *n - 1;
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	kp1 = k + 1;
	m = k;
	i__2 = *n;
	for (i__ = kp1; i__ <= i__2; ++i__) {
	    if ((d__1 = ar[i__ + k * ar_dim1], fabs(d__1)) + (d__2 = ai[i__ +
		    k * ai_dim1], fabs(d__2)) > (d__3 = ar[m + k * ar_dim1],
		    fabs(d__3)) + (d__4 = ai[m + k * ai_dim1], fabs(d__4))) {
		m = i__;
	    }
/* L10: */
	}
	ip[k] = m;
	tr = ar[m + k * ar_dim1];
	ti = ai[m + k * ai_dim1];
	if (m == k) {
	    goto L20;
	}
	ip[*n] = -ip[*n];
	ar[m + k * ar_dim1] = ar[k + k * ar_dim1];
	ai[m + k * ai_dim1] = ai[k + k * ai_dim1];
	ar[k + k * ar_dim1] = tr;
	ai[k + k * ai_dim1] = ti;
L20:
	if (fabs(tr) + fabs(ti) == 0.) {
	    goto L80;
	}
	den = tr * tr + ti * ti;
	tr /= den;
	ti = -ti / den;
	i__2 = *n;
	for (i__ = kp1; i__ <= i__2; ++i__) {
	    prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * ti;
	    prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * ti;
	    ar[i__ + k * ar_dim1] = -prodr;
	    ai[i__ + k * ai_dim1] = -prodi;
/* L30: */
	}
	i__2 = *n;
	for (j = kp1; j <= i__2; ++j) {
	    tr = ar[m + j * ar_dim1];
	    ti = ai[m + j * ai_dim1];
	    ar[m + j * ar_dim1] = ar[k + j * ar_dim1];
	    ai[m + j * ai_dim1] = ai[k + j * ai_dim1];
	    ar[k + j * ar_dim1] = tr;
	    ai[k + j * ai_dim1] = ti;
	    if (fabs(tr) + fabs(ti) == 0.) {
		goto L48;
	    }
	    if (ti == 0.) {
		i__3 = *n;
		for (i__ = kp1; i__ <= i__3; ++i__) {
		    prodr = ar[i__ + k * ar_dim1] * tr;
		    prodi = ai[i__ + k * ai_dim1] * tr;
		    ar[i__ + j * ar_dim1] += prodr;
		    ai[i__ + j * ai_dim1] += prodi;
/* L40: */
		}
		goto L48;
	    }
	    if (tr == 0.) {
		i__3 = *n;
		for (i__ = kp1; i__ <= i__3; ++i__) {
		    prodr = -ai[i__ + k * ai_dim1] * ti;
		    prodi = ar[i__ + k * ar_dim1] * ti;
		    ar[i__ + j * ar_dim1] += prodr;
		    ai[i__ + j * ai_dim1] += prodi;
/* L45: */
		}
		goto L48;
	    }
	    i__3 = *n;
	    for (i__ = kp1; i__ <= i__3; ++i__) {
		prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * 
			ti;
		prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * 
			ti;
		ar[i__ + j * ar_dim1] += prodr;
		ai[i__ + j * ai_dim1] += prodi;
/* L47: */
	    }
L48:
/* L50: */
	    ;
	}
/* L60: */
    }
L70:
    k = *n;
    if ((d__1 = ar[*n + *n * ar_dim1], fabs(d__1)) + (d__2 = ai[*n + *n *
	    ai_dim1], fabs(d__2)) == 0.) {
	goto L80;
    }
    return 0;
L80:
    *ier = k;
    ip[*n] = 0;
    return 0;
/* ----------------------- END OF SUBROUTINE DECC ------------------------ */
} /* decc_ */



/* Subroutine */ int solc_(integer *n, integer *ndim, doublereal *ar, 
	doublereal *ai, doublereal *br, doublereal *bi, integer *ip)
{
    /* System generated locals */
    integer ar_dim1, ar_offset, ai_dim1, ai_offset, i__1, i__2;

    /* Local variables */
    static integer i__, k, m, kb;
    static doublereal ti, tr;
    static integer km1, nm1, kp1;
    static doublereal den, prodi, prodr;

/* VERSION COMPLEX DOUBLE PRECISION */
/* ----------------------------------------------------------------------- */
/*  SOLUTION OF LINEAR SYSTEM, A*X = B . */
/*  INPUT.. */
/*    N = ORDER OF MATRIX. */
/*    NDIM = DECLARED DIMENSION OF ARRAYS  AR AND AI. */
/*    (AR,AI) = TRIANGULARIZED MATRIX OBTAINED FROM DEC. */
/*    (BR,BI) = RIGHT HAND SIDE VECTOR. */
/*    IP = PIVOT VECTOR OBTAINED FROM DEC. */
/*  DO NOT USE IF DEC HAS SET IER .NE. 0. */
/*  OUTPUT.. */
/*    (BR,BI) = SOLUTION VECTOR, X . */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    --bi;
    --br;
    ai_dim1 = *ndim;
    ai_offset = 1 + ai_dim1;
    ai -= ai_offset;
    ar_dim1 = *ndim;
    ar_offset = 1 + ar_dim1;
    ar -= ar_offset;

    /* Function Body */
    if (*n == 1) {
	goto L50;
    }
    nm1 = *n - 1;
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	kp1 = k + 1;
	m = ip[k];
	tr = br[m];
	ti = bi[m];
	br[m] = br[k];
	bi[m] = bi[k];
	br[k] = tr;
	bi[k] = ti;
	i__2 = *n;
	for (i__ = kp1; i__ <= i__2; ++i__) {
	    prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * ti;
	    prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * ti;
	    br[i__] += prodr;
	    bi[i__] += prodi;
/* L10: */
	}
/* L20: */
    }
    i__1 = nm1;
    for (kb = 1; kb <= i__1; ++kb) {
	km1 = *n - kb;
	k = km1 + 1;
	den = ar[k + k * ar_dim1] * ar[k + k * ar_dim1] + ai[k + k * ai_dim1] 
		* ai[k + k * ai_dim1];
	prodr = br[k] * ar[k + k * ar_dim1] + bi[k] * ai[k + k * ai_dim1];
	prodi = bi[k] * ar[k + k * ar_dim1] - br[k] * ai[k + k * ai_dim1];
	br[k] = prodr / den;
	bi[k] = prodi / den;
	tr = -br[k];
	ti = -bi[k];
	i__2 = km1;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * ti;
	    prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * ti;
	    br[i__] += prodr;
	    bi[i__] += prodi;
/* L30: */
	}
/* L40: */
    }
L50:
    den = ar[ar_dim1 + 1] * ar[ar_dim1 + 1] + ai[ai_dim1 + 1] * ai[ai_dim1 + 
	    1];
    prodr = br[1] * ar[ar_dim1 + 1] + bi[1] * ai[ai_dim1 + 1];
    prodi = bi[1] * ar[ar_dim1 + 1] - br[1] * ai[ai_dim1 + 1];
    br[1] = prodr / den;
    bi[1] = prodi / den;
    return 0;
/* ----------------------- END OF SUBROUTINE SOLC ------------------------ */
} /* solc_ */



/* Subroutine */ int dechc_(integer *n, integer *ndim, doublereal *ar, 
	doublereal *ai, integer *lb, integer *ip, integer *ier)
{
    /* System generated locals */
    integer ar_dim1, ar_offset, ai_dim1, ai_offset, i__1, i__2, i__3;
    doublereal d__1, d__2, d__3, d__4;

    /* Local variables */
    static integer i__, j, k, m, na;
    static doublereal ti, tr;
    static integer nm1, kp1;
    static doublereal den, prodi, prodr;

/* VERSION COMPLEX DOUBLE PRECISION */
/* ----------------------------------------------------------------------- */
/*  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION */
/*  ------ MODIFICATION FOR COMPLEX MATRICES -------- */
/*  INPUT.. */
/*     N = ORDER OF MATRIX. */
/*     NDIM = DECLARED DIMENSION OF ARRAYS  AR AND AI . */
/*     (AR, AI) = MATRIX TO BE TRIANGULARIZED. */
/*  OUTPUT.. */
/*     AR(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U ; REAL PART. */
/*     AI(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U ; IMAGINARY PART. */
/*     AR(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L. */
/*                                                    REAL PART. */
/*     AI(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L. */
/*                                                    IMAGINARY PART. */
/*     LB = LOWER BANDWIDTH OF A (DIAGONAL NOT COUNTED), LB.GE.1. */
/*     IP(K), K.LT.N = INDEX OF K-TH PIVOT ROW. */
/*     IP(N) = (-1)**(NUMBER OF INTERCHANGES) OR O . */
/*     IER = 0 IF MATRIX A IS NONSINGULAR, OR K IF FOUND TO BE */
/*           SINGULAR AT STAGE K. */
/*  USE  SOL  TO OBTAIN SOLUTION OF LINEAR SYSTEM. */
/*  IF IP(N)=O, A IS SINGULAR, SOL WILL DIVIDE BY ZERO. */

/*  REFERENCE.. */
/*     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER, */
/*     C.A.C.M. 15 (1972), P. 274. */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    ai_dim1 = *ndim;
    ai_offset = 1 + ai_dim1;
    ai -= ai_offset;
    ar_dim1 = *ndim;
    ar_offset = 1 + ar_dim1;
    ar -= ar_offset;

    /* Function Body */
    *ier = 0;
    ip[*n] = 1;
    if (*lb == 0) {
	goto L70;
    }
    if (*n == 1) {
	goto L70;
    }
    nm1 = *n - 1;
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	kp1 = k + 1;
	m = k;
/* Computing MIN */
	i__2 = *n, i__3 = *lb + k;
	na = min(i__2,i__3);
	i__2 = na;
	for (i__ = kp1; i__ <= i__2; ++i__) {
	    if ((d__1 = ar[i__ + k * ar_dim1], fabs(d__1)) + (d__2 = ai[i__ +
		    k * ai_dim1], fabs(d__2)) > (d__3 = ar[m + k * ar_dim1],
		    fabs(d__3)) + (d__4 = ai[m + k * ai_dim1], fabs(d__4))) {
		m = i__;
	    }
/* L10: */
	}
	ip[k] = m;
	tr = ar[m + k * ar_dim1];
	ti = ai[m + k * ai_dim1];
	if (m == k) {
	    goto L20;
	}
	ip[*n] = -ip[*n];
	ar[m + k * ar_dim1] = ar[k + k * ar_dim1];
	ai[m + k * ai_dim1] = ai[k + k * ai_dim1];
	ar[k + k * ar_dim1] = tr;
	ai[k + k * ai_dim1] = ti;
L20:
	if (fabs(tr) + fabs(ti) == 0.) {
	    goto L80;
	}
	den = tr * tr + ti * ti;
	tr /= den;
	ti = -ti / den;
	i__2 = na;
	for (i__ = kp1; i__ <= i__2; ++i__) {
	    prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * ti;
	    prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * ti;
	    ar[i__ + k * ar_dim1] = -prodr;
	    ai[i__ + k * ai_dim1] = -prodi;
/* L30: */
	}
	i__2 = *n;
	for (j = kp1; j <= i__2; ++j) {
	    tr = ar[m + j * ar_dim1];
	    ti = ai[m + j * ai_dim1];
	    ar[m + j * ar_dim1] = ar[k + j * ar_dim1];
	    ai[m + j * ai_dim1] = ai[k + j * ai_dim1];
	    ar[k + j * ar_dim1] = tr;
	    ai[k + j * ai_dim1] = ti;
	    if (fabs(tr) + fabs(ti) == 0.) {
		goto L48;
	    }
	    if (ti == 0.) {
		i__3 = na;
		for (i__ = kp1; i__ <= i__3; ++i__) {
		    prodr = ar[i__ + k * ar_dim1] * tr;
		    prodi = ai[i__ + k * ai_dim1] * tr;
		    ar[i__ + j * ar_dim1] += prodr;
		    ai[i__ + j * ai_dim1] += prodi;
/* L40: */
		}
		goto L48;
	    }
	    if (tr == 0.) {
		i__3 = na;
		for (i__ = kp1; i__ <= i__3; ++i__) {
		    prodr = -ai[i__ + k * ai_dim1] * ti;
		    prodi = ar[i__ + k * ar_dim1] * ti;
		    ar[i__ + j * ar_dim1] += prodr;
		    ai[i__ + j * ai_dim1] += prodi;
/* L45: */
		}
		goto L48;
	    }
	    i__3 = na;
	    for (i__ = kp1; i__ <= i__3; ++i__) {
		prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * 
			ti;
		prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * 
			ti;
		ar[i__ + j * ar_dim1] += prodr;
		ai[i__ + j * ai_dim1] += prodi;
/* L47: */
	    }
L48:
/* L50: */
	    ;
	}
/* L60: */
    }
L70:
    k = *n;
    if ((d__1 = ar[*n + *n * ar_dim1], fabs(d__1)) + (d__2 = ai[*n + *n *
	    ai_dim1], fabs(d__2)) == 0.) {
	goto L80;
    }
    return 0;
L80:
    *ier = k;
    ip[*n] = 0;
    return 0;
/* ----------------------- END OF SUBROUTINE DECHC ----------------------- */
} /* dechc_ */



/* Subroutine */ int solhc_(integer *n, integer *ndim, doublereal *ar, 
	doublereal *ai, integer *lb, doublereal *br, doublereal *bi, integer *
	ip)
{
    /* System generated locals */
    integer ar_dim1, ar_offset, ai_dim1, ai_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
    static integer i__, k, m, kb;
    static doublereal ti, tr;
    static integer km1, nm1, kp1;
    static doublereal den, prodi, prodr;

/* VERSION COMPLEX DOUBLE PRECISION */
/* ----------------------------------------------------------------------- */
/*  SOLUTION OF LINEAR SYSTEM, A*X = B . */
/*  INPUT.. */
/*    N = ORDER OF MATRIX. */
/*    NDIM = DECLARED DIMENSION OF ARRAYS  AR AND AI. */
/*    (AR,AI) = TRIANGULARIZED MATRIX OBTAINED FROM DEC. */
/*    (BR,BI) = RIGHT HAND SIDE VECTOR. */
/*    LB = LOWER BANDWIDTH OF A. */
/*    IP = PIVOT VECTOR OBTAINED FROM DEC. */
/*  DO NOT USE IF DEC HAS SET IER .NE. 0. */
/*  OUTPUT.. */
/*    (BR,BI) = SOLUTION VECTOR, X . */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    --bi;
    --br;
    ai_dim1 = *ndim;
    ai_offset = 1 + ai_dim1;
    ai -= ai_offset;
    ar_dim1 = *ndim;
    ar_offset = 1 + ar_dim1;
    ar -= ar_offset;

    /* Function Body */
    if (*n == 1) {
	goto L50;
    }
    nm1 = *n - 1;
    if (*lb == 0) {
	goto L25;
    }
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	kp1 = k + 1;
	m = ip[k];
	tr = br[m];
	ti = bi[m];
	br[m] = br[k];
	bi[m] = bi[k];
	br[k] = tr;
	bi[k] = ti;
/* Computing MIN */
	i__3 = *n, i__4 = *lb + k;
	i__2 = min(i__3,i__4);
	for (i__ = kp1; i__ <= i__2; ++i__) {
	    prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * ti;
	    prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * ti;
	    br[i__] += prodr;
	    bi[i__] += prodi;
/* L10: */
	}
/* L20: */
    }
L25:
    i__1 = nm1;
    for (kb = 1; kb <= i__1; ++kb) {
	km1 = *n - kb;
	k = km1 + 1;
	den = ar[k + k * ar_dim1] * ar[k + k * ar_dim1] + ai[k + k * ai_dim1] 
		* ai[k + k * ai_dim1];
	prodr = br[k] * ar[k + k * ar_dim1] + bi[k] * ai[k + k * ai_dim1];
	prodi = bi[k] * ar[k + k * ar_dim1] - br[k] * ai[k + k * ai_dim1];
	br[k] = prodr / den;
	bi[k] = prodi / den;
	tr = -br[k];
	ti = -bi[k];
	i__2 = km1;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * ti;
	    prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * ti;
	    br[i__] += prodr;
	    bi[i__] += prodi;
/* L30: */
	}
/* L40: */
    }
L50:
    den = ar[ar_dim1 + 1] * ar[ar_dim1 + 1] + ai[ai_dim1 + 1] * ai[ai_dim1 + 
	    1];
    prodr = br[1] * ar[ar_dim1 + 1] + bi[1] * ai[ai_dim1 + 1];
    prodi = bi[1] * ar[ar_dim1 + 1] - br[1] * ai[ai_dim1 + 1];
    br[1] = prodr / den;
    bi[1] = prodi / den;
    return 0;
/* ----------------------- END OF SUBROUTINE SOLHC ----------------------- */
} /* solhc_ */


/* Subroutine */ int decb_(integer *n, integer *ndim, doublereal *a, integer *
	ml, integer *mu, integer *ip, integer *ier)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;
    doublereal d__1, d__2;

    /* Local variables */
    static integer i__, j, k, m;
    static doublereal t;
    static integer md, jk, mm, ju, md1, nm1, kp1, mdl, ijk;

/* ----------------------------------------------------------------------- */
/*  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION OF A BANDED */
/*  MATRIX WITH LOWER BANDWIDTH ML AND UPPER BANDWIDTH MU */
/*  INPUT.. */
/*     N       ORDER OF THE ORIGINAL MATRIX A. */
/*     NDIM    DECLARED DIMENSION OF ARRAY  A. */
/*     A       CONTAINS THE MATRIX IN BAND STORAGE.   THE COLUMNS */
/*                OF THE MATRIX ARE STORED IN THE COLUMNS OF  A  AND */
/*                THE DIAGONALS OF THE MATRIX ARE STORED IN ROWS */
/*                ML+1 THROUGH 2*ML+MU+1 OF  A. */
/*     ML      LOWER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED). */
/*     MU      UPPER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED). */
/*  OUTPUT.. */
/*     A       AN UPPER TRIANGULAR MATRIX IN BAND STORAGE AND */
/*                THE MULTIPLIERS WHICH WERE USED TO OBTAIN IT. */
/*     IP      INDEX VECTOR OF PIVOT INDICES. */
/*     IP(N)   (-1)**(NUMBER OF INTERCHANGES) OR O . */
/*     IER     = 0 IF MATRIX A IS NONSINGULAR, OR  = K IF FOUND TO BE */
/*                SINGULAR AT STAGE K. */
/*  USE  SOLB  TO OBTAIN SOLUTION OF LINEAR SYSTEM. */
/*  DETERM(A) = IP(N)*A(MD,1)*A(MD,2)*...*A(MD,N)  WITH MD=ML+MU+1. */
/*  IF IP(N)=O, A IS SINGULAR, SOLB WILL DIVIDE BY ZERO. */

/*  REFERENCE.. */
/*     THIS IS A MODIFICATION OF */
/*     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER, */
/*     C.A.C.M. 15 (1972), P. 274. */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    a_dim1 = *ndim;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    *ier = 0;
    ip[*n] = 1;
    md = *ml + *mu + 1;
    md1 = md + 1;
    ju = 0;
    if (*ml == 0) {
	goto L70;
    }
    if (*n == 1) {
	goto L70;
    }
    if (*n < *mu + 2) {
	goto L7;
    }
    i__1 = *n;
    for (j = *mu + 2; j <= i__1; ++j) {
	i__2 = *ml;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* L5: */
	    a[i__ + j * a_dim1] = 0.;
	}
    }
L7:
    nm1 = *n - 1;
    i__2 = nm1;
    for (k = 1; k <= i__2; ++k) {
	kp1 = k + 1;
	m = md;
/* Computing MIN */
	i__1 = *ml, i__3 = *n - k;
	mdl = min(i__1,i__3) + md;
	i__1 = mdl;
	for (i__ = md1; i__ <= i__1; ++i__) {
	    if ((d__1 = a[i__ + k * a_dim1], fabs(d__1)) > (d__2 = a[m + k *
		    a_dim1], fabs(d__2))) {
		m = i__;
	    }
/* L10: */
	}
	ip[k] = m + k - md;
	t = a[m + k * a_dim1];
	if (m == md) {
	    goto L20;
	}
	ip[*n] = -ip[*n];
	a[m + k * a_dim1] = a[md + k * a_dim1];
	a[md + k * a_dim1] = t;
L20:
	if (t == 0.) {
	    goto L80;
	}
	t = 1. / t;
	i__1 = mdl;
	for (i__ = md1; i__ <= i__1; ++i__) {
/* L30: */
	    a[i__ + k * a_dim1] = -a[i__ + k * a_dim1] * t;
	}
/* Computing MIN */
/* Computing MAX */
	i__3 = ju, i__4 = *mu + ip[k];
	i__1 = max(i__3,i__4);
	ju = min(i__1,*n);
	mm = md;
	if (ju < kp1) {
	    goto L55;
	}
	i__1 = ju;
	for (j = kp1; j <= i__1; ++j) {
	    --m;
	    --mm;
	    t = a[m + j * a_dim1];
	    if (m == mm) {
		goto L35;
	    }
	    a[m + j * a_dim1] = a[mm + j * a_dim1];
	    a[mm + j * a_dim1] = t;
L35:
	    if (t == 0.) {
		goto L45;
	    }
	    jk = j - k;
	    i__3 = mdl;
	    for (i__ = md1; i__ <= i__3; ++i__) {
		ijk = i__ - jk;
/* L40: */
		a[ijk + j * a_dim1] += a[i__ + k * a_dim1] * t;
	    }
L45:
/* L50: */
	    ;
	}
L55:
/* L60: */
	;
    }
L70:
    k = *n;
    if (a[md + *n * a_dim1] == 0.) {
	goto L80;
    }
    return 0;
L80:
    *ier = k;
    ip[*n] = 0;
    return 0;
/* ----------------------- END OF SUBROUTINE DECB ------------------------ */
} /* decb_ */



/* Subroutine */ int solb_(integer *n, integer *ndim, doublereal *a, integer *
	ml, integer *mu, doublereal *b, integer *ip)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, k, m;
    static doublereal t;
    static integer kb, md, lm, md1, nm1, imd, kmd, mdl, mdm;

/* ----------------------------------------------------------------------- */
/*  SOLUTION OF LINEAR SYSTEM, A*X = B . */
/*  INPUT.. */
/*    N      ORDER OF MATRIX A. */
/*    NDIM   DECLARED DIMENSION OF ARRAY  A . */
/*    A      TRIANGULARIZED MATRIX OBTAINED FROM DECB. */
/*    ML     LOWER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED). */
/*    MU     UPPER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED). */
/*    B      RIGHT HAND SIDE VECTOR. */
/*    IP     PIVOT VECTOR OBTAINED FROM DECB. */
/*  DO NOT USE IF DECB HAS SET IER .NE. 0. */
/*  OUTPUT.. */
/*    B      SOLUTION VECTOR, X . */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    --b;
    a_dim1 = *ndim;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    md = *ml + *mu + 1;
    md1 = md + 1;
    mdm = md - 1;
    nm1 = *n - 1;
    if (*ml == 0) {
	goto L25;
    }
    if (*n == 1) {
	goto L50;
    }
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	m = ip[k];
	t = b[m];
	b[m] = b[k];
	b[k] = t;
/* Computing MIN */
	i__2 = *ml, i__3 = *n - k;
	mdl = min(i__2,i__3) + md;
	i__2 = mdl;
	for (i__ = md1; i__ <= i__2; ++i__) {
	    imd = i__ + k - md;
/* L10: */
	    b[imd] += a[i__ + k * a_dim1] * t;
	}
/* L20: */
    }
L25:
    i__1 = nm1;
    for (kb = 1; kb <= i__1; ++kb) {
	k = *n + 1 - kb;
	b[k] /= a[md + k * a_dim1];
	t = -b[k];
	kmd = md - k;
/* Computing MAX */
	i__2 = 1, i__3 = kmd + 1;
	lm = max(i__2,i__3);
	i__2 = mdm;
	for (i__ = lm; i__ <= i__2; ++i__) {
	    imd = i__ - kmd;
/* L30: */
	    b[imd] += a[i__ + k * a_dim1] * t;
	}
/* L40: */
    }
L50:
    b[1] /= a[md + a_dim1];
    return 0;
/* ----------------------- END OF SUBROUTINE SOLB ------------------------ */
} /* solb_ */


/* Subroutine */ int decbc_(integer *n, integer *ndim, doublereal *ar, 
	doublereal *ai, integer *ml, integer *mu, integer *ip, integer *ier)
{
    /* System generated locals */
    integer ar_dim1, ar_offset, ai_dim1, ai_offset, i__1, i__2, i__3, i__4;
    doublereal d__1, d__2, d__3, d__4;

    /* Local variables */
    static integer i__, j, k, m, md, jk, mm;
    static doublereal ti;
    static integer ju;
    static doublereal tr;
    static integer md1, nm1, kp1;
    static doublereal den;
    static integer mdl, ijk;
    static doublereal prodi, prodr;

/* ----------------------------------------------------------------------- */
/*  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION OF A BANDED COMPLEX */
/*  MATRIX WITH LOWER BANDWIDTH ML AND UPPER BANDWIDTH MU */
/*  INPUT.. */
/*     N       ORDER OF THE ORIGINAL MATRIX A. */
/*     NDIM    DECLARED DIMENSION OF ARRAY  A. */
/*     AR, AI     CONTAINS THE MATRIX IN BAND STORAGE.   THE COLUMNS */
/*                OF THE MATRIX ARE STORED IN THE COLUMNS OF  AR (REAL */
/*                PART) AND AI (IMAGINARY PART)  AND */
/*                THE DIAGONALS OF THE MATRIX ARE STORED IN ROWS */
/*                ML+1 THROUGH 2*ML+MU+1 OF  AR AND AI. */
/*     ML      LOWER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED). */
/*     MU      UPPER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED). */
/*  OUTPUT.. */
/*     AR, AI  AN UPPER TRIANGULAR MATRIX IN BAND STORAGE AND */
/*                THE MULTIPLIERS WHICH WERE USED TO OBTAIN IT. */
/*     IP      INDEX VECTOR OF PIVOT INDICES. */
/*     IP(N)   (-1)**(NUMBER OF INTERCHANGES) OR O . */
/*     IER     = 0 IF MATRIX A IS NONSINGULAR, OR  = K IF FOUND TO BE */
/*                SINGULAR AT STAGE K. */
/*  USE  SOLBC  TO OBTAIN SOLUTION OF LINEAR SYSTEM. */
/*  DETERM(A) = IP(N)*A(MD,1)*A(MD,2)*...*A(MD,N)  WITH MD=ML+MU+1. */
/*  IF IP(N)=O, A IS SINGULAR, SOLBC WILL DIVIDE BY ZERO. */

/*  REFERENCE.. */
/*     THIS IS A MODIFICATION OF */
/*     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER, */
/*     C.A.C.M. 15 (1972), P. 274. */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    ai_dim1 = *ndim;
    ai_offset = 1 + ai_dim1;
    ai -= ai_offset;
    ar_dim1 = *ndim;
    ar_offset = 1 + ar_dim1;
    ar -= ar_offset;

    /* Function Body */
    *ier = 0;
    ip[*n] = 1;
    md = *ml + *mu + 1;
    md1 = md + 1;
    ju = 0;
    if (*ml == 0) {
	goto L70;
    }
    if (*n == 1) {
	goto L70;
    }
    if (*n < *mu + 2) {
	goto L7;
    }
    i__1 = *n;
    for (j = *mu + 2; j <= i__1; ++j) {
	i__2 = *ml;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ar[i__ + j * ar_dim1] = 0.;
	    ai[i__ + j * ai_dim1] = 0.;
/* L5: */
	}
    }
L7:
    nm1 = *n - 1;
    i__2 = nm1;
    for (k = 1; k <= i__2; ++k) {
	kp1 = k + 1;
	m = md;
/* Computing MIN */
	i__1 = *ml, i__3 = *n - k;
	mdl = min(i__1,i__3) + md;
	i__1 = mdl;
	for (i__ = md1; i__ <= i__1; ++i__) {
	    if ((d__1 = ar[i__ + k * ar_dim1], fabs(d__1)) + (d__2 = ai[i__ +
		    k * ai_dim1], fabs(d__2)) > (d__3 = ar[m + k * ar_dim1],
		    fabs(d__3)) + (d__4 = ai[m + k * ai_dim1], fabs(d__4))) {
		m = i__;
	    }
/* L10: */
	}
	ip[k] = m + k - md;
	tr = ar[m + k * ar_dim1];
	ti = ai[m + k * ai_dim1];
	if (m == md) {
	    goto L20;
	}
	ip[*n] = -ip[*n];
	ar[m + k * ar_dim1] = ar[md + k * ar_dim1];
	ai[m + k * ai_dim1] = ai[md + k * ai_dim1];
	ar[md + k * ar_dim1] = tr;
	ai[md + k * ai_dim1] = ti;
L20:
	if (fabs(tr) + fabs(ti) == 0.) {
	    goto L80;
	}
	den = tr * tr + ti * ti;
	tr /= den;
	ti = -ti / den;
	i__1 = mdl;
	for (i__ = md1; i__ <= i__1; ++i__) {
	    prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * ti;
	    prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * ti;
	    ar[i__ + k * ar_dim1] = -prodr;
	    ai[i__ + k * ai_dim1] = -prodi;
/* L30: */
	}
/* Computing MIN */
/* Computing MAX */
	i__3 = ju, i__4 = *mu + ip[k];
	i__1 = max(i__3,i__4);
	ju = min(i__1,*n);
	mm = md;
	if (ju < kp1) {
	    goto L55;
	}
	i__1 = ju;
	for (j = kp1; j <= i__1; ++j) {
	    --m;
	    --mm;
	    tr = ar[m + j * ar_dim1];
	    ti = ai[m + j * ai_dim1];
	    if (m == mm) {
		goto L35;
	    }
	    ar[m + j * ar_dim1] = ar[mm + j * ar_dim1];
	    ai[m + j * ai_dim1] = ai[mm + j * ai_dim1];
	    ar[mm + j * ar_dim1] = tr;
	    ai[mm + j * ai_dim1] = ti;
L35:
	    if (fabs(tr) + fabs(ti) == 0.) {
		goto L48;
	    }
	    jk = j - k;
	    if (ti == 0.) {
		i__3 = mdl;
		for (i__ = md1; i__ <= i__3; ++i__) {
		    ijk = i__ - jk;
		    prodr = ar[i__ + k * ar_dim1] * tr;
		    prodi = ai[i__ + k * ai_dim1] * tr;
		    ar[ijk + j * ar_dim1] += prodr;
		    ai[ijk + j * ai_dim1] += prodi;
/* L40: */
		}
		goto L48;
	    }
	    if (tr == 0.) {
		i__3 = mdl;
		for (i__ = md1; i__ <= i__3; ++i__) {
		    ijk = i__ - jk;
		    prodr = -ai[i__ + k * ai_dim1] * ti;
		    prodi = ar[i__ + k * ar_dim1] * ti;
		    ar[ijk + j * ar_dim1] += prodr;
		    ai[ijk + j * ai_dim1] += prodi;
/* L45: */
		}
		goto L48;
	    }
	    i__3 = mdl;
	    for (i__ = md1; i__ <= i__3; ++i__) {
		ijk = i__ - jk;
		prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * 
			ti;
		prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * 
			ti;
		ar[ijk + j * ar_dim1] += prodr;
		ai[ijk + j * ai_dim1] += prodi;
/* L47: */
	    }
L48:
/* L50: */
	    ;
	}
L55:
/* L60: */
	;
    }
L70:
    k = *n;
    if ((d__1 = ar[md + *n * ar_dim1], fabs(d__1)) + (d__2 = ai[md + *n *
	    ai_dim1], fabs(d__2)) == 0.) {
	goto L80;
    }
    return 0;
L80:
    *ier = k;
    ip[*n] = 0;
    return 0;
/* ----------------------- END OF SUBROUTINE DECBC ------------------------ */
} /* decbc_ */



/* Subroutine */ int solbc_(integer *n, integer *ndim, doublereal *ar, 
	doublereal *ai, integer *ml, integer *mu, doublereal *br, doublereal *
	bi, integer *ip)
{
    /* System generated locals */
    integer ar_dim1, ar_offset, ai_dim1, ai_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, k, m, kb, md, lm;
    static doublereal ti, tr;
    static integer md1, nm1;
    static doublereal den;
    static integer imd, kmd, mdl, mdm;
    static doublereal prodi, prodr;

/* ----------------------------------------------------------------------- */
/*  SOLUTION OF LINEAR SYSTEM, A*X = B , */
/*                  VERSION BANDED AND COMPLEX-DOUBLE PRECISION. */
/*  INPUT.. */
/*    N      ORDER OF MATRIX A. */
/*    NDIM   DECLARED DIMENSION OF ARRAY  A . */
/*    AR, AI TRIANGULARIZED MATRIX OBTAINED FROM DECB (REAL AND IMAG. PART). */
/*    ML     LOWER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED). */
/*    MU     UPPER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED). */
/*    BR, BI RIGHT HAND SIDE VECTOR (REAL AND IMAG. PART). */
/*    IP     PIVOT VECTOR OBTAINED FROM DECBC. */
/*  DO NOT USE IF DECB HAS SET IER .NE. 0. */
/*  OUTPUT.. */
/*    BR, BI SOLUTION VECTOR, X (REAL AND IMAG. PART). */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --ip;
    --bi;
    --br;
    ai_dim1 = *ndim;
    ai_offset = 1 + ai_dim1;
    ai -= ai_offset;
    ar_dim1 = *ndim;
    ar_offset = 1 + ar_dim1;
    ar -= ar_offset;

    /* Function Body */
    md = *ml + *mu + 1;
    md1 = md + 1;
    mdm = md - 1;
    nm1 = *n - 1;
    if (*ml == 0) {
	goto L25;
    }
    if (*n == 1) {
	goto L50;
    }
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	m = ip[k];
	tr = br[m];
	ti = bi[m];
	br[m] = br[k];
	bi[m] = bi[k];
	br[k] = tr;
	bi[k] = ti;
/* Computing MIN */
	i__2 = *ml, i__3 = *n - k;
	mdl = min(i__2,i__3) + md;
	i__2 = mdl;
	for (i__ = md1; i__ <= i__2; ++i__) {
	    imd = i__ + k - md;
	    prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * ti;
	    prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * ti;
	    br[imd] += prodr;
	    bi[imd] += prodi;
/* L10: */
	}
/* L20: */
    }
L25:
    i__1 = nm1;
    for (kb = 1; kb <= i__1; ++kb) {
	k = *n + 1 - kb;
	den = ar[md + k * ar_dim1] * ar[md + k * ar_dim1] + ai[md + k * 
		ai_dim1] * ai[md + k * ai_dim1];
	prodr = br[k] * ar[md + k * ar_dim1] + bi[k] * ai[md + k * ai_dim1];
	prodi = bi[k] * ar[md + k * ar_dim1] - br[k] * ai[md + k * ai_dim1];
	br[k] = prodr / den;
	bi[k] = prodi / den;
	tr = -br[k];
	ti = -bi[k];
	kmd = md - k;
/* Computing MAX */
	i__2 = 1, i__3 = kmd + 1;
	lm = max(i__2,i__3);
	i__2 = mdm;
	for (i__ = lm; i__ <= i__2; ++i__) {
	    imd = i__ - kmd;
	    prodr = ar[i__ + k * ar_dim1] * tr - ai[i__ + k * ai_dim1] * ti;
	    prodi = ai[i__ + k * ai_dim1] * tr + ar[i__ + k * ar_dim1] * ti;
	    br[imd] += prodr;
	    bi[imd] += prodi;
/* L30: */
	}
/* L40: */
    }
    den = ar[md + ar_dim1] * ar[md + ar_dim1] + ai[md + ai_dim1] * ai[md + 
	    ai_dim1];
    prodr = br[1] * ar[md + ar_dim1] + bi[1] * ai[md + ai_dim1];
    prodi = bi[1] * ar[md + ar_dim1] - br[1] * ai[md + ai_dim1];
    br[1] = prodr / den;
    bi[1] = prodi / den;
L50:
    return 0;
/* ----------------------- END OF SUBROUTINE SOLBC ------------------------ */
} /* solbc_ */



/* Subroutine */ int elmhes_(integer *nm, integer *n, integer *low, integer *
	igh, doublereal *a, integer *int__)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1;

    /* Local variables */
    static integer i__, j, m;
    static doublereal x, y;
    static integer la, mm1, kp1, mp1;



/*     this subroutine is a translation of the algol procedure elmhes, */
/*     num. math. 12, 349-368(1968) by martin and wilkinson. */
/*     handbook for auto. comp., vol.ii-linear algebra, 339-358(1971). */

/*     given a real general matrix, this subroutine */
/*     reduces a submatrix situated in rows and columns */
/*     low through igh to upper hessenberg form by */
/*     stabilized elementary similarity transformations. */

/*     on input: */

/*      nm must be set to the row dimension of two-dimensional */
/*        array parameters as declared in the calling program */
/*        dimension statement; */

/*      n is the order of the matrix; */

/*      low and igh are integers determined by the balancing */
/*        subroutine  balanc.      if  balanc  has not been used, */
/*        set low=1, igh=n; */

/*      a contains the input matrix. */

/*     on output: */

/*      a contains the hessenberg matrix.  the multipliers */
/*        which were used in the reduction are stored in the */
/*        remaining triangle under the hessenberg matrix; */

/*      int contains information on the rows and columns */
/*        interchanged in the reduction. */
/*        only elements low through igh are used. */

/*     questions and comments should be directed to b. s. garbow, */
/*     applied mathematics division, argonne national laboratory */

/*     ------------------------------------------------------------------ */

    /* Parameter adjustments */
    a_dim1 = *nm;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --int__;

    /* Function Body */
    la = *igh - 1;
    kp1 = *low + 1;
    if (la < kp1) {
	goto L200;
    }

    i__1 = la;
    for (m = kp1; m <= i__1; ++m) {
	mm1 = m - 1;
	x = 0.;
	i__ = m;

	i__2 = *igh;
	for (j = m; j <= i__2; ++j) {
	    if ((d__1 = a[j + mm1 * a_dim1], fabs(d__1)) <= fabs(x)) {
		goto L100;
	    }
	    x = a[j + mm1 * a_dim1];
	    i__ = j;
L100:
	    ;
	}

	int__[m] = i__;
	if (i__ == m) {
	    goto L130;
	}
/*    :::::::::: interchange rows and columns of a :::::::::: */
	i__2 = *n;
	for (j = mm1; j <= i__2; ++j) {
	    y = a[i__ + j * a_dim1];
	    a[i__ + j * a_dim1] = a[m + j * a_dim1];
	    a[m + j * a_dim1] = y;
/* L110: */
	}

	i__2 = *igh;
	for (j = 1; j <= i__2; ++j) {
	    y = a[j + i__ * a_dim1];
	    a[j + i__ * a_dim1] = a[j + m * a_dim1];
	    a[j + m * a_dim1] = y;
/* L120: */
	}
/*    :::::::::: end interchange :::::::::: */
L130:
	if (x == 0.) {
	    goto L180;
	}
	mp1 = m + 1;

	i__2 = *igh;
	for (i__ = mp1; i__ <= i__2; ++i__) {
	    y = a[i__ + mm1 * a_dim1];
	    if (y == 0.) {
		goto L160;
	    }
	    y /= x;
	    a[i__ + mm1 * a_dim1] = y;

	    i__3 = *n;
	    for (j = m; j <= i__3; ++j) {
/* L140: */
		a[i__ + j * a_dim1] -= y * a[m + j * a_dim1];
	    }

	    i__3 = *igh;
	    for (j = 1; j <= i__3; ++j) {
/* L150: */
		a[j + m * a_dim1] += y * a[j + i__ * a_dim1];
	    }

L160:
	    ;
	}

L180:
	;
    }

L200:
    return 0;
/*    :::::::::: last card of elmhes :::::::::: */
} /* elmhes_ */

