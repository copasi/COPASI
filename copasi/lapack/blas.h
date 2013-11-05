// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/* Function */
VOID cdotc_(complex *ret_val, integer *n, complex *cx, integer *incx, complex *cy, integer *incy);
/* Function */
VOID cdotu_(complex *ret_val, integer *n, complex *cx, integer *incx, complex *cy, integer *incy);
/* Function */
VOID zdotc_(doublecomplex *ret_val, integer *n, doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);
/* Function */
VOID zdotu_(doublecomplex *ret_val, integer *n, doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);
/* Function */
doublereal dasum_(integer *n, doublereal *dx, integer *incx);
/* Function */
doublereal dcabs1_(doublecomplex *z);
/* Function */
doublereal ddot_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
/* Function */
doublereal dnrm2_(integer *n, doublereal *x, integer *incx);
/* Function */
doublereal dzasum_(integer *n, doublecomplex *zx, integer *incx);
/* Function */
doublereal dznrm2_(integer *n, doublecomplex *x, integer *incx);
/* Function */
doublereal sasum_(integer *n, real *sx, integer *incx);
/* Function */
doublereal scasum_(integer *n, complex *cx, integer *incx);
/* Function */
doublereal scnrm2_(integer *n, complex *x, integer *incx);
/* Function */
doublereal sdot_(integer *n, real *sx, integer *incx, real *sy, integer *incy);
/* Function */
doublereal snrm2_(integer *n, real *x, integer *incx);
/* Function */
integer icamax_(integer *n, complex *cx, integer *incx);
/* Function */
integer idamax_(integer *n, doublereal *dx, integer *incx);
/* Function */
integer isamax_(integer *n, real *sx, integer *incx);
/* Function */
integer izamax_(integer *n, doublecomplex *zx, integer *incx);
/* Function */
logical lsame_(char *ca, char *cb);

/* Subroutine */
int caxpy_(integer *n, complex *ca, complex *cx, integer *incx, complex *cy, integer *incy);
/* Subroutine */
int ccopy_(integer *n, complex *cx, integer *incx, complex *cy, integer *incy);
/* Subroutine */
int cgbmv_(char *trans, integer *m, integer *n, integer *kl, integer *ku, complex *alpha, complex *a, integer *lda, complex *x, integer *incx, complex *beta, complex *y, integer *incy);
/* Subroutine */
int cgemm_(char *transa, char *transb, integer *m, integer *n, integer *k, complex *alpha, complex *a, integer *lda, complex *b, integer *ldb, complex *beta, complex *c, integer *ldc);
/* Subroutine */
int cgemv_(char *trans, integer *m, integer *n, complex *alpha, complex *a, integer *lda, complex *x, integer *incx, complex *beta, complex *y, integer *incy);
/* Subroutine */
int cgerc_(integer *m, integer *n, complex *alpha, complex *x, integer *incx, complex *y, integer *incy, complex *a, integer *lda);
/* Subroutine */
int cgeru_(integer *m, integer *n, complex *alpha, complex *x, integer *incx, complex *y, integer *incy, complex *a, integer *lda);
/* Subroutine */
int chbmv_(char *uplo, integer *n, integer *k, complex *alpha, complex *a, integer *lda, complex *x, integer *incx, complex *beta, complex *y, integer *incy);
/* Subroutine */
int chemm_(char *side, char *uplo, integer *m, integer *n, complex *alpha, complex *a, integer *lda, complex *b, integer *ldb, complex *beta, complex *c, integer *ldc);
/* Subroutine */
int chemv_(char *uplo, integer *n, complex *alpha, complex *a, integer *lda, complex *x, integer *incx, complex *beta, complex *y, integer *incy);
/* Subroutine */
int cher2_(char *uplo, integer *n, complex *alpha, complex *x, integer *incx, complex *y, integer *incy, complex *a, integer *lda);
/* Subroutine */
int cher2k_(char *uplo, char *trans, integer *n, integer *k, complex *alpha, complex *a, integer *lda, complex *b, integer *ldb, real *beta, complex *c, integer *ldc);
/* Subroutine */
int cher_(char *uplo, integer *n, real *alpha, complex *x, integer *incx, complex *a, integer *lda);
/* Subroutine */
int cherk_(char *uplo, char *trans, integer *n, integer *k, real *alpha, complex *a, integer *lda, real *beta, complex *c, integer *ldc);
/* Subroutine */
int chpmv_(char *uplo, integer *n, complex *alpha, complex *ap, complex *x, integer *incx, complex *beta, complex *y, integer *incy);
/* Subroutine */
int chpr2_(char *uplo, integer *n, complex *alpha, complex *x, integer *incx, complex *y, integer *incy, complex *ap);
/* Subroutine */
int chpr_(char *uplo, integer *n, real *alpha, complex *x, integer *incx, complex *ap);
/* Subroutine */
int crotg_(complex *ca, complex *cb, real *c, complex *s);
/* Subroutine */
int cscal_(integer *n, complex *ca, complex *cx, integer *incx);
/* Subroutine */
int csscal_(integer *n, real *sa, complex *cx, integer *incx);
/* Subroutine */
int cswap_(integer *n, complex *cx, integer *incx, complex *cy, integer *incy);
/* Subroutine */
int csymm_(char *side, char *uplo, integer *m, integer *n, complex *alpha, complex *a, integer *lda, complex *b, integer *ldb, complex *beta, complex *c, integer *ldc);
/* Subroutine */
int csyr2k_(char *uplo, char *trans, integer *n, integer *k, complex *alpha, complex *a, integer *lda, complex *b, integer *ldb, complex *beta, complex *c, integer *ldc);
/* Subroutine */
int csyrk_(char *uplo, char *trans, integer *n, integer *k, complex *alpha, complex *a, integer *lda, complex *beta, complex *c, integer *ldc);
/* Subroutine */
int ctbmv_(char *uplo, char *trans, char *diag, integer *n, integer *k, complex *a, integer *lda, complex *x, integer *incx);
/* Subroutine */
int ctbsv_(char *uplo, char *trans, char *diag, integer *n, integer *k, complex *a, integer *lda, complex *x, integer *incx);
/* Subroutine */
int ctpmv_(char *uplo, char *trans, char *diag, integer *n, complex *ap, complex *x, integer *incx);
/* Subroutine */
int ctpsv_(char *uplo, char *trans, char *diag, integer *n, complex *ap, complex *x, integer *incx);
/* Subroutine */
int ctrmm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, complex *alpha, complex *a, integer *lda, complex *b, integer *ldb);
/* Subroutine */
int ctrmv_(char *uplo, char *trans, char *diag, integer *n, complex *a, integer *lda, complex *x, integer *incx);
/* Subroutine */
int ctrsm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, complex *alpha, complex *a, integer *lda, complex *b, integer *ldb);
/* Subroutine */
int ctrsv_(char *uplo, char *trans, char *diag, integer *n, complex *a, integer *lda, complex *x, integer *incx);
/* Subroutine */
int daxpy_(integer *n, doublereal *da, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
/* Subroutine */
int dcopy_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
/* Subroutine */
int dgbmv_(char *trans, integer *m, integer *n, integer *kl, integer *ku, doublereal *alpha, doublereal *a, integer *lda, doublereal *x, integer *incx, doublereal *beta, doublereal *y, integer *incy);
/* Subroutine */
int dgemm_(char *transa, char *transb, integer *m, integer *n, integer *k, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *beta, doublereal *c, integer *ldc);
/* Subroutine */
int dgemv_(char *trans, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *x, integer *incx, doublereal *beta, doublereal *y, integer *incy);
/* Subroutine */
int dger_(integer *m, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *y, integer *incy, doublereal *a, integer *lda);
/* Subroutine */
int drot_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy, doublereal *c, doublereal *s);
/* Subroutine */
int drotg_(doublereal *da, doublereal *db, doublereal *c, doublereal *s);
/* Subroutine */
int dsbmv_(char *uplo, integer *n, integer *k, doublereal *alpha, doublereal *a, integer *lda, doublereal *x, integer *incx, doublereal *beta, doublereal *y, integer *incy);
/* Subroutine */
int dscal_(integer *n, doublereal *da, doublereal *dx, integer *incx);
/* Subroutine */
int dspmv_(char *uplo, integer *n, doublereal *alpha, doublereal *ap, doublereal *x, integer *incx, doublereal *beta, doublereal *y, integer *incy);
/* Subroutine */
int dspr2_(char *uplo, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *y, integer *incy, doublereal *ap);
/* Subroutine */
int dspr_(char *uplo, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *ap);
/* Subroutine */
int dswap_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
/* Subroutine */
int dsymm_(char *side, char *uplo, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *beta, doublereal *c, integer *ldc);
/* Subroutine */
int dsymv_(char *uplo, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *x, integer *incx, doublereal *beta, doublereal *y, integer *incy);
/* Subroutine */
int dsyr2_(char *uplo, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *y, integer *incy, doublereal *a, integer *lda);
/* Subroutine */
int dsyr2k_(char *uplo, char *trans, integer *n, integer *k, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *beta, doublereal *c, integer *ldc);
/* Subroutine */
int dsyr_(char *uplo, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *a, integer *lda);
/* Subroutine */
int dsyrk_(char *uplo, char *trans, integer *n, integer *k, doublereal *alpha, doublereal *a, integer *lda, doublereal *beta, doublereal *c, integer *ldc);
/* Subroutine */
int dtbmv_(char *uplo, char *trans, char *diag, integer *n, integer *k, doublereal *a, integer *lda, doublereal *x, integer *incx);
/* Subroutine */
int dtbsv_(char *uplo, char *trans, char *diag, integer *n, integer *k, doublereal *a, integer *lda, doublereal *x, integer *incx);
/* Subroutine */
int dtpmv_(char *uplo, char *trans, char *diag, integer *n, doublereal *ap, doublereal *x, integer *incx);
/* Subroutine */
int dtpsv_(char *uplo, char *trans, char *diag, integer *n, doublereal *ap, doublereal *x, integer *incx);
/* Subroutine */
int dtrmm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb);
/* Subroutine */
int dtrmv_(char *uplo, char *trans, char *diag, integer *n, doublereal *a, integer *lda, doublereal *x, integer *incx);
/* Subroutine */
int dtrsm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb);
/* Subroutine */
int dtrsv_(char *uplo, char *trans, char *diag, integer *n, doublereal *a, integer *lda, doublereal *x, integer *incx);
/* Subroutine */
int saxpy_(integer *n, real *sa, real *sx, integer *incx, real *sy, integer *incy);
/* Subroutine */
int scopy_(integer *n, real *sx, integer *incx, real *sy, integer *incy);
/* Subroutine */
int sgbmv_(char *trans, integer *m, integer *n, integer *kl, integer *ku, real *alpha, real *a, integer *lda, real *x, integer *incx, real *beta, real *y, integer *incy);
/* Subroutine */
int sgemm_(char *transa, char *transb, integer *m, integer *n, integer *k, real *alpha, real *a, integer *lda, real *b, integer *ldb, real *beta, real *c, integer *ldc);
/* Subroutine */
int sgemv_(char *trans, integer *m, integer *n, real *alpha, real *a, integer *lda, real *x, integer *incx, real *beta, real *y, integer *incy);
/* Subroutine */
int sger_(integer *m, integer *n, real *alpha, real *x, integer *incx, real *y, integer *incy, real *a, integer *lda);
/* Subroutine */
int srot_(integer *n, real *sx, integer *incx, real *sy, integer *incy, real *c, real *s);
/* Subroutine */
int srotg_(real *sa, real *sb, real *c, real *s);
/* Subroutine */
int ssbmv_(char *uplo, integer *n, integer *k, real *alpha, real *a, integer *lda, real *x, integer *incx, real *beta, real *y, integer *incy);
/* Subroutine */
int sscal_(integer *n, real *sa, real *sx, integer *incx);
/* Subroutine */
int sspmv_(char *uplo, integer *n, real *alpha, real *ap, real *x, integer *incx, real *beta, real *y, integer *incy);
/* Subroutine */
int sspr2_(char *uplo, integer *n, real *alpha, real *x, integer *incx, real *y, integer *incy, real *ap);
/* Subroutine */
int sspr_(char *uplo, integer *n, real *alpha, real *x, integer *incx, real *ap);
/* Subroutine */
int sswap_(integer *n, real *sx, integer *incx, real *sy, integer *incy);
/* Subroutine */
int ssymm_(char *side, char *uplo, integer *m, integer *n, real *alpha, real *a, integer *lda, real *b, integer *ldb, real *beta, real *c, integer *ldc);
/* Subroutine */
int ssymv_(char *uplo, integer *n, real *alpha, real *a, integer *lda, real *x, integer *incx, real *beta, real *y, integer *incy);
/* Subroutine */
int ssyr2_(char *uplo, integer *n, real *alpha, real *x, integer *incx, real *y, integer *incy, real *a, integer *lda);
/* Subroutine */
int ssyr2k_(char *uplo, char *trans, integer *n, integer *k, real *alpha, real *a, integer *lda, real *b, integer *ldb, real *beta, real *c, integer *ldc);
/* Subroutine */
int ssyr_(char *uplo, integer *n, real *alpha, real *x, integer *incx, real *a, integer *lda);
/* Subroutine */
int ssyrk_(char *uplo, char *trans, integer *n, integer *k, real *alpha, real *a, integer *lda, real *beta, real *c, integer *ldc);
/* Subroutine */
int stbmv_(char *uplo, char *trans, char *diag, integer *n, integer *k, real *a, integer *lda, real *x, integer *incx);
/* Subroutine */
int stbsv_(char *uplo, char *trans, char *diag, integer *n, integer *k, real *a, integer *lda, real *x, integer *incx);
/* Subroutine */
int stpmv_(char *uplo, char *trans, char *diag, integer *n, real *ap, real *x, integer *incx);
/* Subroutine */
int stpsv_(char *uplo, char *trans, char *diag, integer *n, real *ap, real *x, integer *incx);
/* Subroutine */
int strmm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, real *alpha, real *a, integer *lda, real *b, integer *ldb);
/* Subroutine */
int strmv_(char *uplo, char *trans, char *diag, integer *n, real *a, integer *lda, real *x, integer *incx);
/* Subroutine */
int strsm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, real *alpha, real *a, integer *lda, real *b, integer *ldb);
/* Subroutine */
int strsv_(char *uplo, char *trans, char *diag, integer *n, real *a, integer *lda, real *x, integer *incx);
/* Subroutine */
int xerbla_(char *srname, integer *info);
/* Subroutine */
int zaxpy_(integer *n, doublecomplex *za, doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);
/* Subroutine */
int zcopy_(integer *n, doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);
/* Subroutine */
int zdscal_(integer *n, doublereal *da, doublecomplex *zx, integer *incx);
/* Subroutine */
int zgbmv_(char *trans, integer *m, integer *n, integer *kl, integer *ku, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy);
/* Subroutine */
int zgemm_(char *transa, char *transb, integer *m, integer *n, integer *k, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *beta, doublecomplex *c, integer *ldc);
/* Subroutine */
int zgemv_(char *trans, integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy);
/* Subroutine */
int zgerc_(integer *m, integer *n, doublecomplex *alpha, doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, doublecomplex *a, integer *lda);
/* Subroutine */
int zgeru_(integer *m, integer *n, doublecomplex *alpha, doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, doublecomplex *a, integer *lda);
/* Subroutine */
int zhbmv_(char *uplo, integer *n, integer *k, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy);
/* Subroutine */
int zhemm_(char *side, char *uplo, integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *beta, doublecomplex *c, integer *ldc);
/* Subroutine */
int zhemv_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy);
/* Subroutine */
int zher2_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, doublecomplex *a, integer *lda);
/* Subroutine */
int zher2k_(char *uplo, char *trans, integer *n, integer *k, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublereal *beta, doublecomplex *c, integer *ldc);
/* Subroutine */
int zher_(char *uplo, integer *n, doublereal *alpha, doublecomplex *x, integer *incx, doublecomplex *a, integer *lda);
/* Subroutine */
int zherk_(char *uplo, char *trans, integer *n, integer *k, doublereal *alpha, doublecomplex *a, integer *lda, doublereal *beta, doublecomplex *c, integer *ldc);
/* Subroutine */
int zhpmv_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *ap, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy);
/* Subroutine */
int zhpr2_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, doublecomplex *ap);
/* Subroutine */
int zhpr_(char *uplo, integer *n, doublereal *alpha, doublecomplex *x, integer *incx, doublecomplex *ap);
/* Subroutine */
int zrotg_(doublecomplex *ca, doublecomplex *cb, doublereal *c, doublecomplex *s);
/* Subroutine */
int zscal_(integer *n, doublecomplex *za, doublecomplex *zx, integer *incx);
/* Subroutine */
int zswap_(integer *n, doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);
/* Subroutine */
int zsymm_(char *side, char *uplo, integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *beta, doublecomplex *c, integer *ldc);
/* Subroutine */
int zsyr2k_(char *uplo, char *trans, integer *n, integer *k, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *beta, doublecomplex *c, integer *ldc);
/* Subroutine */
int zsyrk_(char *uplo, char *trans, integer *n, integer *k, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *beta, doublecomplex *c, integer *ldc);
/* Subroutine */
int ztbmv_(char *uplo, char *trans, char *diag, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx);
/* Subroutine */
int ztbsv_(char *uplo, char *trans, char *diag, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx);
/* Subroutine */
int ztpmv_(char *uplo, char *trans, char *diag, integer *n, doublecomplex *ap, doublecomplex *x, integer *incx);
/* Subroutine */
int ztpsv_(char *uplo, char *trans, char *diag, integer *n, doublecomplex *ap, doublecomplex *x, integer *incx);
/* Subroutine */
int ztrmm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb);
/* Subroutine */
int ztrmv_(char *uplo, char *trans, char *diag, integer *n, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx);
/* Subroutine */
int ztrsm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb);
/* Subroutine */
int ztrsv_(char *uplo, char *trans, char *diag, integer *n, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx);
