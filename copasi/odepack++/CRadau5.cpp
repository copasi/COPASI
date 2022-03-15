// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

/* radau5.f -- translated by f2c (version 20181026).
 You must link the resulting object file with libf2c:
 on Microsoft Windows system, link with libf2c.lib;
 on Linux or Unix systems, link with .../path/to/libf2c.a -lm
 or, if you install libf2c.a in a standard place, with -lf2c -lm
 -- in that order, at the end of the command line, as in
 cc *.o -lf2c -lm
 Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

 http://www.netlib.org/f2c/libf2c.zip
 */
#include <cmath>

#include "copasi/copasi.h"

#include "CRadau5.h"
#include "Cxerrwd.h"
#include "CInternalSolver.h"
#include "common.h"

//#define pow_dd(__x, __y) pow(*__x, *__y)
double d_sign(double * a, double * b);
static double pow_dd(double *ap, double *bp);
static double pow_di(double *ap, C_INT *bp);

/* Common Block Declarations */

struct
{
  C_INT nn, nn2, nn3, nn4;
  double xsol, hsol, c2m1, c1m1;
} conra5_;

#define conra5_1 conra5_

struct
{
  C_INT mle, mue, mbjac, mbb, mdiag, mdiff, mbdiag;
} linal_;

#define linal_1 linal_

/* Table of constant values */

static C_INT c__9 = 9;
static C_INT c__1 = 1;
static C_INT c__5 = 5;
static C_INT c__3 = 3;
static double c_b54 = .5;
static double c_b91 = 81.;
static double c_b92 = .33333333333333331;
static double c_b93 = 9.;
static double c_b103 = 1.;
static double c_b113 = .8;
static double c_b115 = .25;

CRadau5::CRadau5(): CInternalSolver()
{
}

CRadau5::~CRadau5()
{
}

/* Subroutine */
C_INT CRadau5::operator()(C_INT *n, CRadau5::evalF fcn, double *x, double *
                          y, double *xend, double *h__, double *rtol, double *
                          atol, C_INT *itol, CRadau5::evalJ jac, C_INT *ijac, C_INT *mljac, C_INT
                          *mujac, CRadau5::evalM mas, C_INT *imas, C_INT *mlmas, C_INT *mumas, CRadau5::evalO
                          solout, C_INT *iout, double *work, C_INT *lwork, C_INT *
                          iwork, C_INT *liwork, double *rpar, C_INT *ipar, C_INT *
                          idid)
{
  /* System generated locals */
  C_INT i__1;
  double d__1, d__2, d__3, d__4;

  /* Local variables */
  static C_INT i__, m1, m2, nm1, nit, iee1, ief1, lde1, ief2, ief3, iey0,
         iez1, iez2, iez3;
  static double facl;
  static C_INT ndec, njac;
  static double facr, safe;
  static C_INT ijob, nfcn;
  static C_LOGICAL pred;
  static double hmax;
  static C_INT nmax;
  static double thet, expm;
  static C_INT nsol;
  static double quot;
  static C_INT iee2i, iee2r, ieip1, ieip2, nind1, nind2, nind3;
  static double quot1, quot2;
  static C_INT iejac, ldjac;
  static C_LOGICAL jband;
  static C_INT iecon, iemas, ldmas, ieiph;
  static C_LOGICAL arret;
  static double fnewt;
  static C_INT nstep;
  static double tolst;
  static C_INT ldmas2, iescal, naccpt;
  extern /* Subroutine */ int radcor_(C_INT *, CRadau5::evalF, double *,
                                      double *, double *, double *, double *,
                                      double *, double *, C_INT *, CRadau5::evalJ, C_INT *, C_INT *,
                                      C_INT *, CRadau5::evalM, C_INT *, C_INT *, CRadau5::evalO, C_INT *, C_INT *
                                      , C_INT *, double *, double *, double *, double
                                      *, double *, double *, C_INT *, C_INT *, C_LOGICAL *,
                                      C_INT *, C_INT *, C_INT *, C_LOGICAL *, double *,
                                      double *, C_INT *, C_INT *, C_INT *, C_LOGICAL *, C_LOGICAL
                                      *, C_INT *, C_INT *, C_INT *, double *, double *,
                                      double *, double *, double *, double *,
                                      double *, double *, double *, double *,
                                      double *, double *, double *, C_INT *, C_INT *,
                                      C_INT *, double *, C_INT *, C_INT *, C_INT *, C_INT
                                      *, C_INT *, C_INT *, C_INT *, double *, C_INT *);
  static C_INT nrejct;
  static C_LOGICAL implct;
  static C_INT istore;
  static C_LOGICAL startn;
  static double uround;

  /* Fortran I/O blocks */
  static cilist io___10 = {0, 6, 0, 0, 0 };
  static cilist io___12 = {0, 6, 0, 0, 0 };
  static cilist io___15 = {0, 6, 0, 0, 0 };
  static cilist io___17 = {0, 6, 0, 0, 0 };
  static cilist io___19 = {0, 6, 0, 0, 0 };
  static cilist io___24 = {0, 6, 0, 0, 0 };
  static cilist io___29 = {0, 6, 0, 0, 0 };
  static cilist io___31 = {0, 6, 0, 0, 0 };
  static cilist io___33 = {0, 6, 0, 0, 0 };
  static cilist io___36 = {0, 6, 0, 0, 0 };
  static cilist io___39 = {0, 6, 0, 0, 0 };
  static cilist io___43 = {0, 6, 0, 0, 0 };
  static cilist io___50 = {0, 6, 0, 0, 0 };
  static cilist io___52 = {0, 6, 0, 0, 0 };
  static cilist io___68 = {0, 6, 0, 0, 0 };
  static cilist io___72 = {0, 6, 0, 0, 0 };

  /* ---------------------------------------------------------- */
  /*     NUMERICAL SOLUTION OF A STIFF (OR DIFFERENTIAL ALGEBRAIC) */
  /*     SYSTEM OF FIRST 0RDER ORDINARY DIFFERENTIAL EQUATIONS */
  /*                     M*Y'=F(X,Y). */
  /*     THE SYSTEM CAN BE (LINEARLY) IMPLICIT (MASS-MATRIX M .NE. I) */
  /*     OR EXPLICIT (M=I). */
  /*     THE METHOD USED IS AN IMPLICIT RUNGE-KUTTA METHOD (RADAU IIA) */
  /*     OF ORDER 5 WITH STEP SIZE CONTROL AND CONTINUOUS OUTPUT. */
  /*     CF. SECTION IV.8 */

  /*     AUTHORS: E. HAIRER AND G. WANNER */
  /*              UNIVERSITE DE GENEVE, DEPT. DE MATHEMATIQUES */
  /*              CH-1211 GENEVE 24, SWITZERLAND */
  /*              E-MAIL:  Ernst.Hairer@math.unige.ch */
  /*                       Gerhard.Wanner@math.unige.ch */

  /*     THIS CODE IS PART OF THE BOOK: */
  /*         E. HAIRER AND G. WANNER, SOLVING ORDINARY DIFFERENTIAL */
  /*         EQUATIONS II. STIFF AND DIFFERENTIAL-ALGEBRAIC PROBLEMS. */
  /*         SPRINGER SERIES IN COMPUTATIONAL MATHEMATICS 14, */
  /*         SPRINGER-VERLAG 1991, SECOND EDITION 1996. */

  /*     VERSION OF JULY 9, 1996 */
  /*     (latest small correction: January 18, 2002) */

  /*     INPUT PARAMETERS */
  /*     ---------------- */
  /*     N           DIMENSION OF THE SYSTEM */

  /*     FCN         NAME (EXTERNAL) OF SUBROUTINE COMPUTING THE */
  /*                 VALUE OF F(X,Y): */
  /*                    SUBROUTINE FCN(N,X,Y,F,RPAR,IPAR) */
  /*                    double PRECISION X,Y(N),F(N) */
  /*                    F(1)=...   ETC. */
  /*                 RPAR, IPAR (SEE BELOW) */

  /*     X           INITIAL X-VALUE */

  /*     Y(N)        INITIAL VALUES FOR Y */

  /*     XEND        FINAL X-VALUE (XEND-X MAY BE POSITIVE OR NEGATIVE) */

  /*     H           INITIAL STEP SIZE GUESS; */
  /*                 FOR STIFF EQUATIONS WITH INITIAL TRANSIENT, */
  /*                 H=1.D0/(NORM OF F'), USUALLY 1.D-3 OR 1.D-5, IS GOOD. */
  /*                 THIS CHOICE IS NOT VERY IMPORTANT, THE STEP SIZE IS */
  /*                 QUICKLY ADAPTED. (IF H=0.D0, THE CODE PUTS H=1.D-6). */

  /*     RTOL,ATOL   RELATIVE AND ABSOLUTE ERROR TOLERANCES. THEY */
  /*                 CAN BE BOTH SCALARS OR ELSE BOTH VECTORS OF LENGTH N. */

  /*     ITOL        SWITCH FOR RTOL AND ATOL: */
  /*                   ITOL=0: BOTH RTOL AND ATOL ARE SCALARS. */
  /*                     THE CODE KEEPS, ROUGHLY, THE LOCAL ERROR OF */
  /*                     Y(I) BELOW RTOL*ABS(Y(I))+ATOL */
  /*                   ITOL=1: BOTH RTOL AND ATOL ARE VECTORS. */
  /*                     THE CODE KEEPS THE LOCAL ERROR OF Y(I) BELOW */
  /*                     RTOL(I)*ABS(Y(I))+ATOL(I). */

  /*     JAC         NAME (EXTERNAL) OF THE SUBROUTINE WHICH COMPUTES */
  /*                 THE PARTIAL DERIVATIVES OF F(X,Y) WITH RESPECT TO Y */
  /*                 (THIS ROUTINE IS ONLY CALLED IF IJAC=1; SUPPLY */
  /*                 A DUMMY SUBROUTINE IN THE CASE IJAC=0). */
  /*                 FOR IJAC=1, THIS SUBROUTINE MUST HAVE THE FORM */
  /*                    SUBROUTINE JAC(N,X,Y,DFY,LDFY,RPAR,IPAR) */
  /*                    double PRECISION X,Y(N),DFY(LDFY,N) */
  /*                    DFY(1,1)= ... */
  /*                 LDFY, THE COLUMN-LENGTH OF THE ARRAY, IS */
  /*                 FURNISHED BY THE CALLING PROGRAM. */
  /*                 IF (MLJAC.EQ.N) THE JACOBIAN IS SUPPOSED TO */
  /*                    BE FULL AND THE PARTIAL DERIVATIVES ARE */
  /*                    STORED IN DFY AS */
  /*                       DFY(I,J) = PARTIAL F(I) / PARTIAL Y(J) */
  /*                 ELSE, THE JACOBIAN IS TAKEN AS BANDED AND */
  /*                    THE PARTIAL DERIVATIVES ARE STORED */
  /*                    DIAGONAL-WISE AS */
  /*                       DFY(I-J+MUJAC+1,J) = PARTIAL F(I) / PARTIAL Y(J). */

  /*     IJAC        SWITCH FOR THE COMPUTATION OF THE JACOBIAN: */
  /*                    IJAC=0: JACOBIAN IS COMPUTED INTERNALLY BY FINITE */
  /*                       DIFFERENCES, SUBROUTINE "JAC" IS NEVER CALLED. */
  /*                    IJAC=1: JACOBIAN IS SUPPLIED BY SUBROUTINE JAC. */

  /*     MLJAC       SWITCH FOR THE BANDED STRUCTURE OF THE JACOBIAN: */
  /*                    MLJAC=N: JACOBIAN IS A FULL MATRIX. THE LINEAR */
  /*                       ALGEBRA IS DONE BY FULL-MATRIX GAUSS-ELIMINATION. */
  /*                    0<=MLJAC<N: MLJAC IS THE LOWER BANDWITH OF JACOBIAN */
  /*                       MATRIX (>= NUMBER OF NON-ZERO DIAGONALS BELOW */
  /*                       THE MAIN DIAGONAL). */

  /*     MUJAC       UPPER BANDWITH OF JACOBIAN  MATRIX (>= NUMBER OF NON- */
  /*                 ZERO DIAGONALS ABOVE THE MAIN DIAGONAL). */
  /*                 NEED NOT BE DEFINED IF MLJAC=N. */

  /*     ----   MAS,IMAS,MLMAS, AND MUMAS HAVE ANALOG MEANINGS      ----- */
  /*     ----   FOR THE "MASS MATRIX" (THE MATRIX "M" OF SECTION IV.8): - */

  /*     MAS         NAME (EXTERNAL) OF SUBROUTINE COMPUTING THE MASS- */
  /*                 MATRIX M. */
  /*                 IF IMAS=0, THIS MATRIX IS ASSUMED TO BE THE IDENTITY */
  /*                 MATRIX AND NEEDS NOT TO BE DEFINED; */
  /*                 SUPPLY A DUMMY SUBROUTINE IN THIS CASE. */
  /*                 IF IMAS=1, THE SUBROUTINE MAS IS OF THE FORM */
  /*                    SUBROUTINE MAS(N,AM,LMAS,RPAR,IPAR) */
  /*                    double PRECISION AM(LMAS,N) */
  /*                    AM(1,1)= .... */
  /*                    IF (MLMAS.EQ.N) THE MASS-MATRIX IS STORED */
  /*                    AS FULL MATRIX LIKE */
  /*                         AM(I,J) = M(I,J) */
  /*                    ELSE, THE MATRIX IS TAKEN AS BANDED AND STORED */
  /*                    DIAGONAL-WISE AS */
  /*                         AM(I-J+MUMAS+1,J) = M(I,J). */

  /*     IMAS       GIVES INFORMATION ON THE MASS-MATRIX: */
  /*                    IMAS=0: M IS SUPPOSED TO BE THE IDENTITY */
  /*                       MATRIX, MAS IS NEVER CALLED. */
  /*                    IMAS=1: MASS-MATRIX  IS SUPPLIED. */

  /*     MLMAS       SWITCH FOR THE BANDED STRUCTURE OF THE MASS-MATRIX: */
  /*                    MLMAS=N: THE FULL MATRIX CASE. THE LINEAR */
  /*                       ALGEBRA IS DONE BY FULL-MATRIX GAUSS-ELIMINATION. */
  /*                    0<=MLMAS<N: MLMAS IS THE LOWER BANDWITH OF THE */
  /*                       MATRIX (>= NUMBER OF NON-ZERO DIAGONALS BELOW */
  /*                       THE MAIN DIAGONAL). */
  /*                 MLMAS IS SUPPOSED TO BE .LE. MLJAC. */

  /*     MUMAS       UPPER BANDWITH OF MASS-MATRIX (>= NUMBER OF NON- */
  /*                 ZERO DIAGONALS ABOVE THE MAIN DIAGONAL). */
  /*                 NEED NOT BE DEFINED IF MLMAS=N. */
  /*                 MUMAS IS SUPPOSED TO BE .LE. MUJAC. */

  /*     SOLOUT      NAME (EXTERNAL) OF SUBROUTINE PROVIDING THE */
  /*                 NUMERICAL SOLUTION DURING INTEGRATION. */
  /*                 IF IOUT=1, IT IS CALLED AFTER EVERY SUCCESSFUL STEP. */
  /*                 SUPPLY A DUMMY SUBROUTINE IF IOUT=0. */
  /*                 IT MUST HAVE THE FORM */
  /*                    SUBROUTINE SOLOUT (NR,XOLD,X,Y,CONT,LRC,N, */
  /*                                       RPAR,IPAR,IRTRN) */
  /*                    double PRECISION X,Y(N),CONT(LRC) */
  /*                    .... */
  /*                 SOLOUT FURNISHES THE SOLUTION "Y" AT THE NR-TH */
  /*                    GRID-POINT "X" (THEREBY THE INITIAL VALUE IS */
  /*                    THE FIRST GRID-POINT). */
  /*                 "XOLD" IS THE PRECEEDING GRID-POINT. */
  /*                 "IRTRN" SERVES TO INTERRUPT THE INTEGRATION. IF IRTRN */
  /*                    IS SET <0, RADAU5 RETURNS TO THE CALLING PROGRAM. */

  /*          -----  CONTINUOUS OUTPUT: ----- */
  /*                 DURING CALLS TO "SOLOUT", A CONTINUOUS SOLUTION */
  /*                 FOR THE INTERVAL [XOLD,X] IS AVAILABLE THROUGH */
  /*                 THE FUNCTION */
  /*                        >>>   CONTR5(I,S,CONT,LRC)   <<< */
  /*                 WHICH PROVIDES AN APPROXIMATION TO THE I-TH */
  /*                 COMPONENT OF THE SOLUTION AT THE POINT S. THE VALUE */
  /*                 S SHOULD LIE IN THE INTERVAL [XOLD,X]. */
  /*                 DO NOT CHANGE THE ENTRIES OF CONT(LRC), IF THE */
  /*                 DENSE OUTPUT FUNCTION IS USED. */

  /*     IOUT        SWITCH FOR CALLING THE SUBROUTINE SOLOUT: */
  /*                    IOUT=0: SUBROUTINE IS NEVER CALLED */
  /*                    IOUT=1: SUBROUTINE IS AVAILABLE FOR OUTPUT. */

  /*     WORK        ARRAY OF WORKING SPACE OF LENGTH "LWORK". */
  /*                 WORK(1), WORK(2),.., WORK(20) SERVE AS PARAMETERS */
  /*                 FOR THE CODE. FOR STANDARD USE OF THE CODE */
  /*                 WORK(1),..,WORK(20) MUST BE SET TO ZERO BEFORE */
  /*                 CALLING. SEE BELOW FOR A MORE SOPHISTICATED USE. */
  /*                 WORK(21),..,WORK(LWORK) SERVE AS WORKING SPACE */
  /*                 FOR ALL VECTORS AND MATRICES. */
  /*                 "LWORK" MUST BE AT LEAST */
  /*                             N*(LJAC+LMAS+3*LE+12)+20 */
  /*                 WHERE */
  /*                    LJAC=N              IF MLJAC=N (FULL JACOBIAN) */
  /*                    LJAC=MLJAC+MUJAC+1  IF MLJAC<N (BANDED JAC.) */
  /*                 AND */
  /*                    LMAS=0              IF IMAS=0 */
  /*                    LMAS=N              IF IMAS=1 AND MLMAS=N (FULL) */
  /*                    LMAS=MLMAS+MUMAS+1  IF MLMAS<N (BANDED MASS-M.) */
  /*                 AND */
  /*                    LE=N               IF MLJAC=N (FULL JACOBIAN) */
  /*                    LE=2*MLJAC+MUJAC+1 IF MLJAC<N (BANDED JAC.) */

  /*                 IN THE USUAL CASE WHERE THE JACOBIAN IS FULL AND THE */
  /*                 MASS-MATRIX IS THE INDENTITY (IMAS=0), THE MINIMUM */
  /*                 STORAGE REQUIREMENT IS */
  /*                             LWORK = 4*N*N+12*N+20. */
  /*                 IF IWORK(9)=M1>0 THEN "LWORK" MUST BE AT LEAST */
  /*                          N*(LJAC+12)+(N-M1)*(LMAS+3*LE)+20 */
  /*                 WHERE IN THE DEFINITIONS OF LJAC, LMAS AND LE THE */
  /*                 NUMBER N CAN BE REPLACED BY N-M1. */

  /*     LWORK       DECLARED LENGTH OF ARRAY "WORK". */

  /*     IWORK       C_INT WORKING SPACE OF LENGTH "LIWORK". */
  /*                 IWORK(1),IWORK(2),...,IWORK(20) SERVE AS PARAMETERS */
  /*                 FOR THE CODE. FOR STANDARD USE, SET IWORK(1),.., */
  /*                 IWORK(20) TO ZERO BEFORE CALLING. */
  /*                 IWORK(21),...,IWORK(LIWORK) SERVE AS WORKING AREA. */
  /*                 "LIWORK" MUST BE AT LEAST 3*N+20. */

  /*     LIWORK      DECLARED LENGTH OF ARRAY "IWORK". */

  /*     RPAR, IPAR  REAL AND C_INT PARAMETERS (OR PARAMETER ARRAYS) WHICH */
  /*                 CAN BE USED FOR COMMUNICATION BETWEEN YOUR CALLING */
  /*                 PROGRAM AND THE FCN, JAC, MAS, SOLOUT SUBROUTINES. */

  /* ---------------------------------------------------------------------- */

  /*     SOPHISTICATED SETTING OF PARAMETERS */
  /*     ----------------------------------- */
  /*              SEVERAL PARAMETERS OF THE CODE ARE TUNED TO MAKE IT WORK */
  /*              WELL. THEY MAY BE DEFINED BY SETTING WORK(1),... */
  /*              AS WELL AS IWORK(1),... DIFFERENT FROM ZERO. */
  /*              FOR ZERO INPUT, THE CODE CHOOSES DEFAULT VALUES: */

  /*    IWORK(1)  IF IWORK(1).NE.0, THE CODE TRANSFORMS THE JACOBIAN */
  /*              MATRIX TO HESSENBERG FORM. THIS IS PARTICULARLY */
  /*              ADVANTAGEOUS FOR LARGE SYSTEMS WITH FULL JACOBIAN. */
  /*              IT DOES NOT WORK FOR BANDED JACOBIAN (MLJAC<N) */
  /*              AND NOT FOR IMPLICIT SYSTEMS (IMAS=1). */

  /*    IWORK(2)  THIS IS THE MAXIMAL NUMBER OF ALLOWED STEPS. */
  /*              THE DEFAULT VALUE (FOR IWORK(2)=0) IS 100000. */

  /*    IWORK(3)  THE MAXIMUM NUMBER OF NEWTON ITERATIONS FOR THE */
  /*              SOLUTION OF THE IMPLICIT SYSTEM IN EACH STEP. */
  /*              THE DEFAULT VALUE (FOR IWORK(3)=0) IS 7. */

  /*    IWORK(4)  IF IWORK(4).EQ.0 THE EXTRAPOLATED COLLOCATION SOLUTION */
  /*              IS TAKEN AS STARTING VALUE FOR NEWTON'S METHOD. */
  /*              IF IWORK(4).NE.0 ZERO STARTING VALUES ARE USED. */
  /*              THE LATTER IS RECOMMENDED IF NEWTON'S METHOD HAS */
  /*              DIFFICULTIES WITH CONVERGENCE (THIS IS THE CASE WHEN */
  /*              NSTEP IS LARGER THAN NACCPT + NREJCT; SEE OUTPUT PARAM.). */
  /*              DEFAULT IS IWORK(4)=0. */

  /*       THE FOLLOWING 3 PARAMETERS ARE IMPORTANT FOR */
  /*       DIFFERENTIAL-ALGEBRAIC SYSTEMS OF INDEX > 1. */
  /*       THE FUNCTION-SUBROUTINE SHOULD BE WRITTEN SUCH THAT */
  /*       THE INDEX 1,2,3 VARIABLES APPEAR IN THIS ORDER. */
  /*       IN ESTIMATING THE ERROR THE INDEX 2 VARIABLES ARE */
  /*       MULTIPLIED BY H, THE INDEX 3 VARIABLES BY H**2. */

  /*    IWORK(5)  DIMENSION OF THE INDEX 1 VARIABLES (MUST BE > 0). FOR */
  /*              ODE'S THIS EQUALS THE DIMENSION OF THE SYSTEM. */
  /*              DEFAULT IWORK(5)=N. */

  /*    IWORK(6)  DIMENSION OF THE INDEX 2 VARIABLES. DEFAULT IWORK(6)=0. */

  /*    IWORK(7)  DIMENSION OF THE INDEX 3 VARIABLES. DEFAULT IWORK(7)=0. */

  /*    IWORK(8)  SWITCH FOR STEP SIZE STRATEGY */
  /*              IF IWORK(8).EQ.1  MOD. PREDICTIVE CONTROLLER (GUSTAFSSON) */
  /*              IF IWORK(8).EQ.2  CLASSICAL STEP SIZE CONTROL */
  /*              THE DEFAULT VALUE (FOR IWORK(8)=0) IS IWORK(8)=1. */
  /*              THE CHOICE IWORK(8).EQ.1 SEEMS TO PRODUCE SAFER RESULTS; */
  /*              FOR SIMPLE PROBLEMS, THE CHOICE IWORK(8).EQ.2 PRODUCES */
  /*              OFTEN SLIGHTLY FASTER RUNS */

  /*       IF THE DIFFERENTIAL SYSTEM HAS THE SPECIAL STRUCTURE THAT */
  /*            Y(I)' = Y(I+M2)   FOR  I=1,...,M1, */
  /*       WITH M1 A MULTIPLE OF M2, A SUBSTANTIAL GAIN IN COMPUTERTIME */
  /*       CAN BE ACHIEVED BY SETTING THE PARAMETERS IWORK(9) AND IWORK(10). */
  /*       E.G., FOR SECOND ORDER SYSTEMS P'=V, V'=G(P,V), WHERE P AND V ARE */
  /*       VECTORS OF DIMENSION N/2, ONE HAS TO PUT M1=M2=N/2. */
  /*       FOR M1>0 SOME OF THE INPUT PARAMETERS HAVE DIFFERENT MEANINGS: */
  /*       - JAC: ONLY THE ELEMENTS OF THE NON-TRIVIAL PART OF THE */
  /*              JACOBIAN HAVE TO BE STORED */
  /*              IF (MLJAC.EQ.N-M1) THE JACOBIAN IS SUPPOSED TO BE FULL */
  /*                 DFY(I,J) = PARTIAL F(I+M1) / PARTIAL Y(J) */
  /*                FOR I=1,N-M1 AND J=1,N. */
  /*              ELSE, THE JACOBIAN IS BANDED (M1 = M2 * MM ) */
  /*                 DFY(I-J+MUJAC+1,J+K*M2) = PARTIAL F(I+M1) / PARTIAL Y(J+K*M2) */
  /*                FOR I=1,MLJAC+MUJAC+1 AND J=1,M2 AND K=0,MM. */
  /*       - MLJAC: MLJAC=N-M1: IF THE NON-TRIVIAL PART OF THE JACOBIAN IS FULL */
  /*                0<=MLJAC<N-M1: IF THE (MM+1) SUBMATRICES (FOR K=0,MM) */
  /*                     PARTIAL F(I+M1) / PARTIAL Y(J+K*M2),  I,J=1,M2 */
  /*                    ARE BANDED, MLJAC IS THE MAXIMAL LOWER BANDWIDTH */
  /*                    OF THESE MM+1 SUBMATRICES */
  /*       - MUJAC: MAXIMAL UPPER BANDWIDTH OF THESE MM+1 SUBMATRICES */
  /*                NEED NOT BE DEFINED IF MLJAC=N-M1 */
  /*       - MAS: IF IMAS=0 THIS MATRIX IS ASSUMED TO BE THE IDENTITY AND */
  /*              NEED NOT BE DEFINED. SUPPLY A DUMMY SUBROUTINE IN THIS CASE. */
  /*              IT IS ASSUMED THAT ONLY THE ELEMENTS OF RIGHT LOWER BLOCK OF */
  /*              DIMENSION N-M1 DIFFER FROM THAT OF THE IDENTITY MATRIX. */
  /*              IF (MLMAS.EQ.N-M1) THIS SUBMATRIX IS SUPPOSED TO BE FULL */
  /*                 AM(I,J) = M(I+M1,J+M1)     FOR I=1,N-M1 AND J=1,N-M1. */
  /*              ELSE, THE MASS MATRIX IS BANDED */
  /*                 AM(I-J+MUMAS+1,J) = M(I+M1,J+M1) */
  /*       - MLMAS: MLMAS=N-M1: IF THE NON-TRIVIAL PART OF M IS FULL */
  /*                0<=MLMAS<N-M1: LOWER BANDWIDTH OF THE MASS MATRIX */
  /*       - MUMAS: UPPER BANDWIDTH OF THE MASS MATRIX */
  /*                NEED NOT BE DEFINED IF MLMAS=N-M1 */

  /*    IWORK(9)  THE VALUE OF M1.  DEFAULT M1=0. */

  /*    IWORK(10) THE VALUE OF M2.  DEFAULT M2=M1. */

  /* ---------- */

  /*    WORK(1)   UROUND, THE ROUNDING UNIT, DEFAULT 1.D-16. */

  /*    WORK(2)   THE SAFETY FACTOR IN STEP SIZE PREDICTION, */
  /*              DEFAULT 0.9D0. */

  /*    WORK(3)   DECIDES WHETHER THE JACOBIAN SHOULD BE RECOMPUTED; */
  /*              INCREASE WORK(3), TO 0.1 SAY, WHEN JACOBIAN EVALUATIONS */
  /*              ARE COSTLY. FOR SMALL SYSTEMS WORK(3) SHOULD BE SMALLER */
  /*              (0.001D0, SAY). NEGATIV WORK(3) FORCES THE CODE TO */
  /*              COMPUTE THE JACOBIAN AFTER EVERY ACCEPTED STEP. */
  /*              DEFAULT 0.001D0. */

  /*    WORK(4)   STOPPING CRITERION FOR NEWTON'S METHOD, USUALLY CHOSEN <1. */
  /*              SMALLER VALUES OF WORK(4) MAKE THE CODE SLOWER, BUT SAFER. */
  /*              DEFAULT MIN(0.03D0,RTOL(1)**0.5D0) */

  /*    WORK(5) AND WORK(6) : IF WORK(5) < HNEW/HOLD < WORK(6), THEN THE */
  /*              STEP SIZE IS NOT CHANGED. THIS SAVES, TOGETHER WITH A */
  /*              LARGE WORK(3), LU-DECOMPOSITIONS AND COMPUTING TIME FOR */
  /*              LARGE SYSTEMS. FOR SMALL SYSTEMS ONE MAY HAVE */
  /*              WORK(5)=1.D0, WORK(6)=1.2D0, FOR LARGE FULL SYSTEMS */
  /*              WORK(5)=0.99D0, WORK(6)=2.D0 MIGHT BE GOOD. */
  /*              DEFAULTS WORK(5)=1.D0, WORK(6)=1.2D0 . */

  /*    WORK(7)   MAXIMAL STEP SIZE, DEFAULT XEND-X. */

  /*    WORK(8), WORK(9)   PARAMETERS FOR STEP SIZE SELECTION */
  /*              THE NEW STEP SIZE IS CHOSEN SUBJECT TO THE RESTRICTION */
  /*                 WORK(8) <= HNEW/HOLD <= WORK(9) */
  /*              DEFAULT VALUES: WORK(8)=0.2D0, WORK(9)=8.D0 */

  /* ----------------------------------------------------------------------- */

  /*     OUTPUT PARAMETERS */
  /*     ----------------- */
  /*     X           X-VALUE FOR WHICH THE SOLUTION HAS BEEN COMPUTED */
  /*                 (AFTER SUCCESSFUL RETURN X=XEND). */

  /*     Y(N)        NUMERICAL SOLUTION AT X */

  /*     H           PREDICTED STEP SIZE OF THE LAST ACCEPTED STEP */

  /*     IDID        REPORTS ON SUCCESSFULNESS UPON RETURN: */
  /*                   IDID= 1  COMPUTATION SUCCESSFUL, */
  /*                   IDID= 2  COMPUT. SUCCESSFUL (INTERRUPTED BY SOLOUT) */
  /*                   IDID=-1  INPUT IS NOT CONSISTENT, */
  /*                   IDID=-2  LARGER NMAX IS NEEDED, */
  /*                   IDID=-3  STEP SIZE BECOMES TOO SMALL, */
  /*                   IDID=-4  MATRIX IS REPEATEDLY SINGULAR. */

  /*   IWORK(14)  NFCN    NUMBER OF FUNCTION EVALUATIONS (THOSE FOR NUMERICAL */
  /*                      EVALUATION OF THE JACOBIAN ARE NOT COUNTED) */
  /*   IWORK(15)  NJAC    NUMBER OF JACOBIAN EVALUATIONS (EITHER ANALYTICALLY */
  /*                      OR NUMERICALLY) */
  /*   IWORK(16)  NSTEP   NUMBER OF COMPUTED STEPS */
  /*   IWORK(17)  NACCPT  NUMBER OF ACCEPTED STEPS */
  /*   IWORK(18)  NREJCT  NUMBER OF REJECTED STEPS (DUE TO ERROR TEST), */
  /*                      (STEP REJECTIONS IN THE FIRST STEP ARE NOT COUNTED) */
  /*   IWORK(19)  NDEC    NUMBER OF LU-DECOMPOSITIONS OF BOTH MATRICES */
  /*   IWORK(20)  NSOL    NUMBER OF FORWARD-BACKWARD SUBSTITUTIONS, OF BOTH */
  /*                      SYSTEMS; THE NSTEP FORWARD-BACKWARD SUBSTITUTIONS, */
  /*                      NEEDED FOR STEP SIZE SELECTION, ARE NOT COUNTED */
  /* ----------------------------------------------------------------------- */
  /* *** *** *** *** *** *** *** *** *** *** *** *** *** */
  /*          DECLARATIONS */
  /* *** *** *** *** *** *** *** *** *** *** *** *** *** */
  /* *** *** *** *** *** *** *** */
  /*        SETTING THE PARAMETERS */
  /* *** *** *** *** *** *** *** */
  /* Parameter adjustments */
  --y;
  --rtol;
  --atol;
  --work;
  --iwork;
  --rpar;
  --ipar;

  /* Function Body */
  nfcn = 0;
  njac = 0;
  nstep = 0;
  naccpt = 0;
  nrejct = 0;
  ndec = 0;
  nsol = 0;
  arret = FALSE_;

  /* -------- UROUND   SMALLEST NUMBER SATISFYING 1.0D0+UROUND>1.0D0 */
  if (work[1] == 0.)
    {
      uround = 1e-16;
    }
  else
    {
      uround = work[1];

      if (uround <= 1e-19 || uround >= 1.)
        {
//            s_wsle(&io___10);
//            do_lio(&c__9, &c__1, " COEFFICIENTS HAVE 20 DIGITS, UROUND=", (
//                                                                           ftnlen)37);
//            do_lio(&c__5, &c__1, (char *)&work[1], (ftnlen)sizeof(double))
//;
//            e_wsle();
          arret = TRUE_;
        }
    }

  /* -------- CHECK AND CHANGE THE TOLERANCES */
  expm = .66666666666666663;

  if (*itol == 0)
    {
      if (atol[1] <= 0. || rtol[1] <= uround * 10.)
        {
//            s_wsle(&io___12);
//            do_lio(&c__9, &c__1, " TOLERANCES ARE TOO SMALL", (ftnlen)25);
//            e_wsle();
          arret = TRUE_;
        }
      else
        {
          quot = atol[1] / rtol[1];
          rtol[1] = pow_dd(&rtol[1], &expm) * .1;
          atol[1] = rtol[1] * quot;
        }
    }
  else
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          if (atol[i__] <= 0. || rtol[i__] <= uround * 10.)
            {
//                s_wsle(&io___15);
//                do_lio(&c__9, &c__1, " TOLERANCES(", (ftnlen)12);
//                do_lio(&c__3, &c__1, (char *)&i__, (ftnlen)sizeof(C_INT));
//                do_lio(&c__9, &c__1, ") ARE TOO SMALL", (ftnlen)15);
//                e_wsle();
              arret = TRUE_;
            }
          else
            {
              quot = atol[i__] / rtol[i__];
              rtol[i__] = pow_dd(&rtol[i__], &expm) * .1;
              atol[i__] = rtol[i__] * quot;
            }
        }
    }

  /* -------- NMAX , THE MAXIMAL NUMBER OF STEPS ----- */
  if (iwork[2] == 0)
    {
      nmax = 100000;
    }
  else
    {
      nmax = iwork[2];

      if (nmax <= 0)
        {
//            s_wsle(&io___17);
//            do_lio(&c__9, &c__1, " WRONG INPUT IWORK(2)=", (ftnlen)22);
//            do_lio(&c__3, &c__1, (char *)&iwork[2], (ftnlen)sizeof(C_INT));
//            e_wsle();
          arret = TRUE_;
        }
    }

  /* -------- NIT    MAXIMAL NUMBER OF NEWTON ITERATIONS */
  if (iwork[3] == 0)
    {
      nit = 7;
    }
  else
    {
      nit = iwork[3];

      if (nit <= 0)
        {
//            s_wsle(&io___19);
//            do_lio(&c__9, &c__1, " CURIOUS INPUT IWORK(3)=", (ftnlen)24);
//            do_lio(&c__3, &c__1, (char *)&iwork[3], (ftnlen)sizeof(C_INT));
//            e_wsle();
          arret = TRUE_;
        }
    }

  /* -------- STARTN  SWITCH FOR STARTING VALUES OF NEWTON ITERATIONS */
  if (iwork[4] == 0)
    {
      startn = FALSE_;
    }
  else
    {
      startn = TRUE_;
    }

  /* -------- PARAMETER FOR DIFFERENTIAL-ALGEBRAIC COMPONENTS */
  nind1 = iwork[5];
  nind2 = iwork[6];
  nind3 = iwork[7];

  if (nind1 == 0)
    {
      nind1 = *n;
    }

  if (nind1 + nind2 + nind3 != *n)
    {
//        s_wsle(&io___24);
//        do_lio(&c__9, &c__1, " CURIOUS INPUT FOR IWORK(5,6,7)=", (ftnlen)32);
//        do_lio(&c__3, &c__1, (char *)&nind1, (ftnlen)sizeof(C_INT));
//        do_lio(&c__3, &c__1, (char *)&nind2, (ftnlen)sizeof(C_INT));
//        do_lio(&c__3, &c__1, (char *)&nind3, (ftnlen)sizeof(C_INT));
//        e_wsle();
      arret = TRUE_;
    }

  /* -------- PRED   STEP SIZE CONTROL */
  if (iwork[8] <= 1)
    {
      pred = TRUE_;
    }
  else
    {
      pred = FALSE_;
    }

  /* -------- PARAMETER FOR SECOND ORDER EQUATIONS */
  m1 = iwork[9];
  m2 = iwork[10];
  nm1 = *n - m1;

  if (m1 == 0)
    {
      m2 = *n;
    }

  if (m2 == 0)
    {
      m2 = m1;
    }

  if (m1 < 0 || m2 < 0 || m1 + m2 > *n)
    {
//        s_wsle(&io___29);
//        do_lio(&c__9, &c__1, " CURIOUS INPUT FOR IWORK(9,10)=", (ftnlen)31);
//        do_lio(&c__3, &c__1, (char *)&m1, (ftnlen)sizeof(C_INT));
//        do_lio(&c__3, &c__1, (char *)&m2, (ftnlen)sizeof(C_INT));
//        e_wsle();
      arret = TRUE_;
    }

  /* --------- SAFE     SAFETY FACTOR IN STEP SIZE PREDICTION */
  if (work[2] == 0.)
    {
      safe = .9;
    }
  else
    {
      safe = work[2];

      if (safe <= .001 || safe >= 1.)
        {
//            s_wsle(&io___31);
//            do_lio(&c__9, &c__1, " CURIOUS INPUT FOR WORK(2)=", (ftnlen)27);
//            do_lio(&c__5, &c__1, (char *)&work[2], (ftnlen)sizeof(double))
//;
//            e_wsle();
          arret = TRUE_;
        }
    }

  /* ------ THET     DECIDES WHETHER THE JACOBIAN SHOULD BE RECOMPUTED; */
  if (work[3] == 0.)
    {
      thet = .001;
    }
  else
    {
      thet = work[3];

      if (thet >= 1.)
        {
//            s_wsle(&io___33);
//            do_lio(&c__9, &c__1, " CURIOUS INPUT FOR WORK(3)=", (ftnlen)27);
//            do_lio(&c__5, &c__1, (char *)&work[3], (ftnlen)sizeof(double))
//;
//            e_wsle();
          arret = TRUE_;
        }
    }

  /* --- FNEWT   STOPPING CRITERION FOR NEWTON'S METHOD, USUALLY CHOSEN <1. */
  tolst = rtol[1];

  if (work[4] == 0.)
    {
      /* Computing MAX */
      /* Computing MIN */
      d__3 = .03, d__4 = pow_dd(&tolst, &c_b54);
      d__1 = uround * 10 / tolst, d__2 = min(d__3, d__4);
      fnewt = max(d__1, d__2);
    }
  else
    {
      fnewt = work[4];

      if (fnewt <= uround / tolst)
        {
//            s_wsle(&io___36);
//            do_lio(&c__9, &c__1, " CURIOUS INPUT FOR WORK(4)=", (ftnlen)27);
//            do_lio(&c__5, &c__1, (char *)&work[4], (ftnlen)sizeof(double))
//;
//            e_wsle();
          arret = TRUE_;
        }
    }

  /* --- QUOT1 AND QUOT2: IF QUOT1 < HNEW/HOLD < QUOT2, STEP SIZE = CONST. */
  if (work[5] == 0.)
    {
      quot1 = 1.;
    }
  else
    {
      quot1 = work[5];
    }

  if (work[6] == 0.)
    {
      quot2 = 1.2;
    }
  else
    {
      quot2 = work[6];
    }

  if (quot1 > 1. || quot2 < 1.)
    {
//        s_wsle(&io___39);
//        do_lio(&c__9, &c__1, " CURIOUS INPUT FOR WORK(5,6)=", (ftnlen)29);
//        do_lio(&c__5, &c__1, (char *)&quot1, (ftnlen)sizeof(double));
//        do_lio(&c__5, &c__1, (char *)&quot2, (ftnlen)sizeof(double));
//        e_wsle();
      arret = TRUE_;
    }

  /* -------- MAXIMAL STEP SIZE */
  if (work[7] == 0.)
    {
      hmax = *xend - *x;
    }
  else
    {
      hmax = work[7];
    }

  /* -------  FACL,FACR     PARAMETERS FOR STEP SIZE SELECTION */
  if (work[8] == 0.)
    {
      facl = 5.;
    }
  else
    {
      facl = 1. / work[8];
    }

  if (work[9] == 0.)
    {
      facr = .125;
    }
  else
    {
      facr = 1. / work[9];
    }

  if (facl < 1. || facr > 1.)
    {
//        s_wsle(&io___43);
//        do_lio(&c__9, &c__1, " CURIOUS INPUT WORK(8,9)=", (ftnlen)25);
//        do_lio(&c__5, &c__1, (char *)&work[8], (ftnlen)sizeof(double));
//        do_lio(&c__5, &c__1, (char *)&work[9], (ftnlen)sizeof(double));
//        e_wsle();
      arret = TRUE_;
    }

  /* *** *** *** *** *** *** *** *** *** *** *** *** *** */
  /*         COMPUTATION OF ARRAY ENTRIES */
  /* *** *** *** *** *** *** *** *** *** *** *** *** *** */
  /* ---- IMPLICIT, BANDED OR NOT ? */
  implct = *imas != 0;
  jband = *mljac < nm1;

  /* -------- COMPUTATION OF THE ROW-DIMENSIONS OF THE 2-ARRAYS --- */
  /* -- JACOBIAN  AND  MATRICES E1, E2 */
  if (jband)
    {
      ldjac = *mljac + *mujac + 1;
      lde1 = *mljac + ldjac;
    }
  else
    {
      *mljac = nm1;
      *mujac = nm1;
      ldjac = nm1;
      lde1 = nm1;
    }

  /* -- MASS MATRIX */
  if (implct)
    {
      if (*mlmas != nm1)
        {
          ldmas = *mlmas + *mumas + 1;

          if (jband)
            {
              ijob = 4;
            }
          else
            {
              ijob = 3;
            }
        }
      else
        {
          *mumas = nm1;
          ldmas = nm1;
          ijob = 5;
        }

      /* ------ BANDWITH OF "MAS" NOT SMALLER THAN BANDWITH OF "JAC" */
      if (*mlmas > *mljac || *mumas > *mujac)
        {
//            s_wsle(&io___50);
//            do_lio(&c__9, &c__1, "BANDWITH OF \"MAS\" NOT SMALLER THAN BANDW"
//                   "ITH OF \"JAC\"", (ftnlen)52);
//            e_wsle();
          arret = TRUE_;
        }
    }
  else
    {
      ldmas = 0;

      if (jband)
        {
          ijob = 2;
        }
      else
        {
          ijob = 1;

          if (*n > 2 && iwork[1] != 0)
            {
              ijob = 7;
            }
        }
    }

  ldmas2 = max(1, ldmas);

  /* ------ HESSENBERG OPTION ONLY FOR EXPLICIT EQU. WITH FULL JACOBIAN */
  if ((implct || jband) && ijob == 7)
    {
//        s_wsle(&io___52);
//        do_lio(&c__9, &c__1, " HESSENBERG OPTION ONLY FOR EXPLICIT EQUATIONS"
//               " WITH FULL JACOBIAN", (ftnlen)65);
//        e_wsle();
      arret = TRUE_;
    }

  /* ------- PREPARE THE ENTRY-POINTS FOR THE ARRAYS IN WORK ----- */
  iez1 = 21;
  iez2 = iez1 + *n;
  iez3 = iez2 + *n;
  iey0 = iez3 + *n;
  iescal = iey0 + *n;
  ief1 = iescal + *n;
  ief2 = ief1 + *n;
  ief3 = ief2 + *n;
  iecon = ief3 + *n;
  iejac = iecon + (*n << 2);
  iemas = iejac + *n * ldjac;
  iee1 = iemas + nm1 * ldmas;
  iee2r = iee1 + nm1 * lde1;
  iee2i = iee2r + nm1 * lde1;
  /* ------ TOTAL STORAGE REQUIREMENT ----------- */
  istore = iee2i + nm1 * lde1 - 1;

  if (istore > *lwork)
    {
//        s_wsle(&io___68);
//        do_lio(&c__9, &c__1, " INSUFFICIENT STORAGE FOR WORK, MIN. LWORK=", (
//                                                                             ftnlen)43);
//        do_lio(&c__3, &c__1, (char *)&istore, (ftnlen)sizeof(C_INT));
//        e_wsle();
      arret = TRUE_;
    }

  /* ------- ENTRY POINTS FOR C_INT WORKSPACE ----- */
  ieip1 = 21;
  ieip2 = ieip1 + nm1;
  ieiph = ieip2 + nm1;
  /* --------- TOTAL REQUIREMENT --------------- */
  istore = ieiph + nm1 - 1;

  if (istore > *liwork)
    {
//        s_wsle(&io___72);
//        do_lio(&c__9, &c__1, " INSUFF. STORAGE FOR IWORK, MIN. LIWORK=", (
//                                                                          ftnlen)40);
//        do_lio(&c__3, &c__1, (char *)&istore, (ftnlen)sizeof(C_INT));
//        e_wsle();
      arret = TRUE_;
    }

  /* ------ WHEN A FAIL HAS OCCURED, WE RETURN WITH IDID=-1 */
  if (arret)
    {
      *idid = -1;
      return 0;
    }

  /* -------- CALL TO CORE INTEGRATOR ------------ */
  radcor_(n, fcn, x, &y[1], xend, &hmax, h__, &rtol[1], &atol[1],
          itol, jac, ijac, mljac, mujac, mas, mlmas, mumas, solout, iout, idid, &nmax, &uround, &safe, &thet, &fnewt, &quot1, &quot2, &nit, &ijob, &startn, &nind1, &nind2, &nind3, &
          pred, &facl, &facr, &m1, &m2, &nm1, &implct, &jband, &ldjac, &
          lde1, &ldmas2, &work[iez1], &work[iez2], &work[iez3], &work[iey0],
          &work[iescal], &work[ief1], &work[ief2], &work[ief3], &work[iejac], &work[iee1], &work[iee2r], &work[iee2i], &work[iemas], &iwork[ieip1], &iwork[ieip2], &iwork[ieiph], &work[iecon], &nfcn, &
          njac, &nstep, &naccpt, &nrejct, &ndec, &nsol, &rpar[1], &ipar[1]);
  iwork[14] = nfcn;
  iwork[15] = njac;
  iwork[16] = nstep;
  iwork[17] = naccpt;
  iwork[18] = nrejct;
  iwork[19] = ndec;
  iwork[20] = nsol;
  /* -------- RESTORE TOLERANCES */
  expm = 1. / expm;

  if (*itol == 0)
    {
      quot = atol[1] / rtol[1];
      d__1 = rtol[1] * 10.;
      rtol[1] = pow_dd(&d__1, &expm);
      atol[1] = rtol[1] * quot;
    }
  else
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          quot = atol[i__] / rtol[i__];
          d__1 = rtol[i__] * 10.;
          rtol[i__] = pow_dd(&d__1, &expm);
          atol[i__] = rtol[i__] * quot;
        }
    }

  /* ----------- RETURN ----------- */
  return 0;
} /* radau5_ */

/*     END OF SUBROUTINE RADAU5 */

/* *********************************************************** */

/* Subroutine */ int radcor_(C_INT *n, CRadau5::evalF fcn, double *x, double *
                             y, double *xend, double *hmax, double *h__, double *
                             rtol, double *atol, C_INT *itol, CRadau5::evalJ jac, C_INT *ijac,
                             C_INT *mljac, C_INT *mujac, CRadau5::evalM mas, C_INT *mlmas, C_INT *
                             mumas, CRadau5::evalO solout, C_INT *iout, C_INT *idid, C_INT *nmax,
                             double *uround, double *safe, double *thet, double *
                             fnewt, double *quot1, double *quot2, C_INT *nit, C_INT *
                             ijob, C_LOGICAL *startn, C_INT *nind1, C_INT *nind2, C_INT *nind3,
                             C_LOGICAL *pred, double *facl, double *facr, C_INT *m1,
                             C_INT *m2, C_INT *nm1, C_LOGICAL *implct, C_LOGICAL *banded, C_INT *
                             ldjac, C_INT *lde1, C_INT *ldmas, double *z1, double *z2,
                             double *z3, double *y0, double *scal, double *f1,
                             double *f2, double *f3, double *fjac, double *e1,
                             double *e2r, double *e2i, double *fmas, C_INT *ip1,
                             C_INT *ip2, C_INT *iphes, double *cont, C_INT *nfcn,
                             C_INT *njac, C_INT *nstep, C_INT *naccpt, C_INT *nrejct,
                             C_INT *ndec, C_INT *nsol, double *rpar, C_INT *ipar)
{
  /* Format strings */
  static char fmt_979[] = "(\002 EXIT OF RADAU5 AT X=\002,e18.4)";

  /* System generated locals */
  C_INT fjac_dim1, fjac_offset, fmas_dim1, fmas_offset, e1_dim1,
        e1_offset, e2r_dim1, e2r_offset, e2i_dim1, e2i_offset, i__1, i__2,
        i__3, i__4;
  double d__1, d__2, d__3, d__4;

  /* Local variables */
  static C_INT i__, j, k, l;
  static double a1, a2, c1, c2, a3;
  static C_INT j1, n2, n3;
  static double u1, ak;
  static C_INT md;
  static double t11, t12, t13, t21, t22, t23, t31;
  static C_INT mm;
  static double qt, dd1, dd2, dd3, ak1, ak2, ak3, f1i, f2i, f3i, c1q,
         c2q, c3q, z1i, z2i, z3i, sq6, fac, ti11, cno;
  static C_INT lrc;
  static double ti12, ti13, ti21, ti22, ti23, ti31, ti32, ti33;
  static C_INT ier;
  static double xph, thq, err, fac1, cfac, hacc, c1mc2, beta;
  static C_INT lbeg;
  static double alph, hold;
  static C_INT lend;
  static double delt, hnew;
  static C_LOGICAL last;
  static double hopt, xold;
  static C_INT newt;
  static double dyno, dyth, quot, hhfac, betan, alphn, denom, theta,
         ysafe, hmaxn;
  static C_INT nsing;
  static C_LOGICAL first;
  static C_INT irtrn, nrsol, nsolu;
  static double qnewt, xosol, acont3;
  static C_LOGICAL index1, index2, index3, caljac;
  static double faccon;
  extern /* Subroutine */ int decomc_(C_INT *, double *, C_INT *,
                                      double *, C_INT *, C_INT *, C_INT *, C_INT *, C_INT
                                      *, C_INT *, double *, double *, double *,
                                      double *, C_INT *, C_INT *, C_INT *, C_INT *);
  static C_LOGICAL calhes;
  static double erracc;
  static C_INT mujacj;
  extern /* Subroutine */ int decomr_(C_INT *, double *, C_INT *,
                                      double *, C_INT *, C_INT *, C_INT *, C_INT *, C_INT
                                      *, C_INT *, double *, double *, C_INT *, C_INT *,
                                      C_INT *, C_INT *, C_LOGICAL *, C_INT *);
  static C_LOGICAL reject;
  static double facgus;
  static C_INT mujacp;
  extern /* Subroutine */ int estrad_(C_INT *, double *, C_INT *,
                                      C_INT *, C_INT *, double *, C_INT *, C_INT *, C_INT
                                      *, double *, double *, double *, double *, CRadau5::evalF,
                                      C_INT *, double *, double *, C_INT *, double *,
                                      C_INT *, C_INT *, C_INT *, double *, C_INT *,
                                      double *, double *, double *, double *,
                                      double *, double *, C_INT *, C_INT *, double *,
                                      double *, C_LOGICAL *, C_LOGICAL *, double *, double *,
                                      C_INT *);
  static double dynold, posneg;
  extern /* Subroutine */ int slvrad_(C_INT *, double *, C_INT *,
                                      C_INT *, C_INT *, double *, C_INT *, C_INT *, C_INT
                                      *, C_INT *, C_INT *, C_INT *, double *, double *,
                                      double *, double *, double *, double *, C_INT *,
                                      double *, double *, double *, double *,
                                      double *, double *, double *, C_INT *, C_INT *,
                                      C_INT *, C_INT *, C_INT *);
  static double thqold;

  /* Fortran I/O blocks */
  static cilist io___176 = {0, 6, 0, fmt_979, 0 };
  static cilist io___177 = {0, 6, 0, 0, 0 };
  static cilist io___178 = {0, 6, 0, fmt_979, 0 };
  static cilist io___179 = {0, 6, 0, 0, 0 };
  static cilist io___180 = {0, 6, 0, fmt_979, 0 };
  static cilist io___181 = {0, 6, 0, 0, 0 };
  static cilist io___182 = {0, 6, 0, fmt_979, 0 };

  /* ---------------------------------------------------------- */
  /*     CORE INTEGRATOR FOR RADAU5 */
  /*     PARAMETERS SAME AS IN RADAU5 WITH WORKSPACE ADDED */
  /* ---------------------------------------------------------- */
  /*         DECLARATIONS */
  /* ---------------------------------------------------------- */
  /* *** *** *** *** *** *** *** */
  /*  INITIALISATIONS */
  /* *** *** *** *** *** *** *** */
  /* --------- DUPLIFY N FOR COMMON BLOCK CONT ----- */
  /* Parameter adjustments */
  --cont;
  --f3;
  --f2;
  --f1;
  --scal;
  --y0;
  --z3;
  --z2;
  --z1;
  --y;
  --rtol;
  --atol;
  --iphes;
  --ip2;
  --ip1;
  fjac_dim1 = *ldjac;
  fjac_offset = 1 + fjac_dim1;
  fjac -= fjac_offset;
  e2i_dim1 = *lde1;
  e2i_offset = 1 + e2i_dim1;
  e2i -= e2i_offset;
  e2r_dim1 = *lde1;
  e2r_offset = 1 + e2r_dim1;
  e2r -= e2r_offset;
  e1_dim1 = *lde1;
  e1_offset = 1 + e1_dim1;
  e1 -= e1_offset;
  fmas_dim1 = *ldmas;
  fmas_offset = 1 + fmas_dim1;
  fmas -= fmas_offset;
  --rpar;
  --ipar;

  /* Function Body */
  conra5_1.nn = *n;
  conra5_1.nn2 = *n << 1;
  conra5_1.nn3 = *n * 3;
  lrc = *n << 2;
  /* -------- CHECK THE INDEX OF THE PROBLEM ----- */
  index1 = *nind1 != 0;
  index2 = *nind2 != 0;
  index3 = *nind3 != 0;

  /* ------- COMPUTE MASS MATRIX FOR IMPLICIT CASE ---------- */
  if (*implct)
    {
      (*mas)(nm1, &fmas[fmas_offset], ldmas, &rpar[1], &ipar[1]);
    }

  /* ---------- CONSTANTS --------- */
  sq6 = sqrt(6.);
  c1 = (4. - sq6) / 10.;
  c2 = (sq6 + 4.) / 10.;
  conra5_1.c1m1 = c1 - 1.;
  conra5_1.c2m1 = c2 - 1.;
  c1mc2 = c1 - c2;
  dd1 = -(sq6 * 7. + 13.) / 3.;
  dd2 = (sq6 * 7. - 13.) / 3.;
  dd3 = -.33333333333333331;
  u1 = (pow_dd(&c_b91, &c_b92) + 6. - pow_dd(&c_b93, &c_b92)) / 30.;
  alph = (12. - pow_dd(&c_b91, &c_b92) + pow_dd(&c_b93, &c_b92)) / 60.;
  beta = (pow_dd(&c_b91, &c_b92) + pow_dd(&c_b93, &c_b92)) * sqrt(3.) / 60.;
  /* Computing 2nd power */
  d__1 = alph;
  /* Computing 2nd power */
  d__2 = beta;
  cno = d__1 * d__1 + d__2 * d__2;
  u1 = 1. / u1;
  alph /= cno;
  beta /= cno;
  t11 = .091232394870892942792;
  t12 = -.14125529502095420843;
  t13 = -.030029194105147424492;
  t21 = .24171793270710701896;
  t22 = .20412935229379993199;
  t23 = .38294211275726193779;
  t31 = .96604818261509293619;
  ti11 = 4.325579890063155351;
  ti12 = .33919925181580986954;
  ti13 = .54177053993587487119;
  ti21 = -4.1787185915519047273;
  ti22 = -.32768282076106238708;
  ti23 = .47662355450055045196;
  ti31 = -.50287263494578687595;
  ti32 = 2.5719269498556054292;
  ti33 = -.59603920482822492497;

  if (*m1 > 0)
    {
      *ijob += 10;
    }

  d__1 = *xend - *x;
  posneg = d_sign(&c_b103, &d__1);
  /* Computing MIN */
  d__2 = abs(*hmax), d__3 = (d__1 = *xend - *x, abs(d__1));
  hmaxn = min(d__2, d__3);

  if (abs(*h__) <= *uround * 10.)
    {
      *h__ = 1e-6;
    }

  /* Computing MIN */
  d__1 = abs(*h__);
  *h__ = min(d__1, hmaxn);
  *h__ = d_sign(h__, &posneg);
  hold = *h__;
  reject = FALSE_;
  first = TRUE_;
  last = FALSE_;

  if ((*x + *h__ * 1.0001 - *xend) * posneg >= 0.)
    {
      *h__ = *xend - *x;
      last = TRUE_;
    }

  hopt = *h__;
  faccon = 1.;
  cfac = *safe * ((*nit << 1) + 1);
  nsing = 0;
  xold = *x;

  if (*iout != 0)
    {
      irtrn = 1;
      nrsol = 1;
      xosol = xold;
      conra5_1.xsol = *x;
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          cont[i__] = y[i__];
        }

      nsolu = *n;
      conra5_1.hsol = hold;
      (*solout)(&nrsol, &xosol, &conra5_1.xsol, &y[1], &cont[1], &lrc, &nsolu, &rpar[1], n, &irtrn);

      if (irtrn < 0)
        {
          goto L179;
        }
    }

  linal_1.mle = *mljac;
  linal_1.mue = *mujac;
  linal_1.mbjac = *mljac + *mujac + 1;
  linal_1.mbb = *mlmas + *mumas + 1;
  linal_1.mdiag = linal_1.mle + linal_1.mue + 1;
  linal_1.mdiff = linal_1.mle + linal_1.mue - *mumas;
  linal_1.mbdiag = *mumas + 1;
  n2 = *n << 1;
  n3 = *n * 3;

  if (*itol == 0)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          scal[i__] = atol[1] + rtol[1] * (d__1 = y[i__], abs(d__1));
        }
    }
  else
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          scal[i__] = atol[i__] + rtol[i__] * (d__1 = y[i__], abs(d__1));
        }
    }

  hhfac = *h__;
  (*fcn)(n, x, &y[1], &y0[1], &rpar[1], &ipar[1]);
  ++(*nfcn);
  /* --- BASIC INTEGRATION STEP */
L10:
  /* *** *** *** *** *** *** *** */
  /*  COMPUTATION OF THE JACOBIAN */
  /* *** *** *** *** *** *** *** */
  ++(*njac);

  if (*ijac == 0)
    {
      /* --- COMPUTE JACOBIAN MATRIX NUMERICALLY */
      if (*banded)
        {
          /* --- JACOBIAN IS BANDED */
          mujacp = *mujac + 1;
          md = min(linal_1.mbjac, *m2);
          i__1 = *m1 / *m2 + 1;

          for (mm = 1; mm <= i__1; ++mm)
            {
              i__2 = md;

              for (k = 1; k <= i__2; ++k)
                {
                  j = k + (mm - 1) * *m2;
L12:
                  f1[j] = y[j];
                  /* Computing MAX */
                  d__2 = 1e-5, d__3 = (d__1 = y[j], abs(d__1));
                  f2[j] = sqrt(*uround * max(d__2, d__3));
                  y[j] += f2[j];
                  j += md;

                  if (j <= mm * *m2)
                    {
                      goto L12;
                    }

                  (*fcn)(n, x, &y[1], &cont[1], &rpar[1], &ipar[1]);
                  j = k + (mm - 1) * *m2;
                  j1 = k;
                  /* Computing MAX */
                  i__3 = 1, i__4 = j1 - *mujac;
                  lbeg = max(i__3, i__4) + *m1;
L14:
                  /* Computing MIN */
                  i__3 = *m2, i__4 = j1 + *mljac;
                  lend = min(i__3, i__4) + *m1;
                  y[j] = f1[j];
                  mujacj = mujacp - j1 - *m1;
                  i__3 = lend;

                  for (l = lbeg; l <= i__3; ++l)
                    {
                      fjac[l + mujacj + j * fjac_dim1] = (cont[l] - y0[l]) /
                                                         f2[j];
                    }

                  j += md;
                  j1 += md;
                  lbeg = lend + 1;

                  if (j <= mm * *m2)
                    {
                      goto L14;
                    }
                }
            }
        }
      else
        {
          /* --- JACOBIAN IS FULL */
          i__1 = *n;

          for (i__ = 1; i__ <= i__1; ++i__)
            {
              ysafe = y[i__];
              /* Computing MAX */
              d__1 = 1e-5, d__2 = abs(ysafe);
              delt = sqrt(*uround * max(d__1, d__2));
              y[i__] = ysafe + delt;
              (*fcn)(n, x, &y[1], &cont[1], &rpar[1], &ipar[1]);
              i__2 = *n;

              for (j = *m1 + 1; j <= i__2; ++j)
                {
                  fjac[j - *m1 + i__ * fjac_dim1] = (cont[j] - y0[j]) /
                                                    delt;
                }

              y[i__] = ysafe;
            }
        }
    }
  else
    {
      /* --- COMPUTE JACOBIAN MATRIX ANALYTICALLY */
      (*jac)(n, x, &y[1], &fjac[fjac_offset], ldjac, &rpar[1], &ipar[1]);
    }

  caljac = TRUE_;
  calhes = TRUE_;
L20:
  /* --- COMPUTE THE MATRICES E1 AND E2 AND THEIR DECOMPOSITIONS */
  fac1 = u1 / *h__;
  alphn = alph / *h__;
  betan = beta / *h__;
  decomr_(n, &fjac[fjac_offset], ldjac, &fmas[fmas_offset], ldmas, mlmas,
          mumas, m1, m2, nm1, &fac1, &e1[e1_offset], lde1, &ip1[1], &ier,
          ijob, &calhes, &iphes[1]);

  if (ier != 0)
    {
      goto L78;
    }

  decomc_(n, &fjac[fjac_offset], ldjac, &fmas[fmas_offset], ldmas, mlmas,
          mumas, m1, m2, nm1, &alphn, &betan, &e2r[e2r_offset], &e2i[e2i_offset], lde1, &ip2[1], &ier, ijob);

  if (ier != 0)
    {
      goto L78;
    }

  ++(*ndec);
L30:
  ++(*nstep);

  if (*nstep > *nmax)
    {
      goto L178;
    }

  if (abs(*h__) * .1 <= abs(*x) * *uround)
    {
      goto L177;
    }

  if (index2)
    {
      i__1 = *nind1 + *nind2;

      for (i__ = *nind1 + 1; i__ <= i__1; ++i__)
        {
          scal[i__] /= hhfac;
        }
    }

  if (index3)
    {
      i__1 = *nind1 + *nind2 + *nind3;

      for (i__ = *nind1 + *nind2 + 1; i__ <= i__1; ++i__)
        {
          scal[i__] /= hhfac * hhfac;
        }
    }

  xph = *x + *h__;

  /* *** *** *** *** *** *** *** */
  /*  STARTING VALUES FOR NEWTON ITERATION */
  /* *** *** *** *** *** *** *** */
  if (first || *startn)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          z1[i__] = 0.;
          z2[i__] = 0.;
          z3[i__] = 0.;
          f1[i__] = 0.;
          f2[i__] = 0.;
          f3[i__] = 0.;
        }
    }
  else
    {
      c3q = *h__ / hold;
      c1q = c1 * c3q;
      c2q = c2 * c3q;
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          ak1 = cont[i__ + *n];
          ak2 = cont[i__ + n2];
          ak3 = cont[i__ + n3];
          z1i = c1q * (ak1 + (c1q - conra5_1.c2m1) * (ak2 + (c1q -
                       conra5_1.c1m1) * ak3));
          z2i = c2q * (ak1 + (c2q - conra5_1.c2m1) * (ak2 + (c2q -
                       conra5_1.c1m1) * ak3));
          z3i = c3q * (ak1 + (c3q - conra5_1.c2m1) * (ak2 + (c3q -
                       conra5_1.c1m1) * ak3));
          z1[i__] = z1i;
          z2[i__] = z2i;
          z3[i__] = z3i;
          f1[i__] = ti11 * z1i + ti12 * z2i + ti13 * z3i;
          f2[i__] = ti21 * z1i + ti22 * z2i + ti23 * z3i;
          f3[i__] = ti31 * z1i + ti32 * z2i + ti33 * z3i;
        }
    }

  /* *** *** *** *** *** *** *** */
  /*  LOOP FOR THE SIMPLIFIED NEWTON ITERATION */
  /* *** *** *** *** *** *** *** */
  newt = 0;
  d__1 = max(faccon, *uround);
  faccon = pow_dd(&d__1, &c_b113);
  theta = abs(*thet);
L40:

  if (newt >= *nit)
    {
      goto L78;
    }

  /* ---     COMPUTE THE RIGHT-HAND SIDE */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      cont[i__] = y[i__] + z1[i__];
    }

  d__1 = *x + c1 * *h__;
  (*fcn)(n, &d__1, &cont[1], &z1[1], &rpar[1], &ipar[1]);
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      cont[i__] = y[i__] + z2[i__];
    }

  d__1 = *x + c2 * *h__;
  (*fcn)(n, &d__1, &cont[1], &z2[1], &rpar[1], &ipar[1]);
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      cont[i__] = y[i__] + z3[i__];
    }

  (*fcn)(n, &xph, &cont[1], &z3[1], &rpar[1], &ipar[1]);
  *nfcn += 3;
  /* ---     SOLVE THE LINEAR SYSTEMS */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      a1 = z1[i__];
      a2 = z2[i__];
      a3 = z3[i__];
      z1[i__] = ti11 * a1 + ti12 * a2 + ti13 * a3;
      z2[i__] = ti21 * a1 + ti22 * a2 + ti23 * a3;
      z3[i__] = ti31 * a1 + ti32 * a2 + ti33 * a3;
    }

  slvrad_(n, &fjac[fjac_offset], ldjac, mljac, mujac, &fmas[fmas_offset],
          ldmas, mlmas, mumas, m1, m2, nm1, &fac1, &alphn, &betan, &e1[e1_offset], &e2r[e2r_offset], &e2i[e2i_offset], lde1, &z1[1], &z2[1], &z3[1], &f1[1], &f2[1], &f3[1], &cont[1], &ip1[1], &ip2[1], &iphes[1], &ier, ijob);
  ++(*nsol);
  ++newt;
  dyno = 0.;
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      denom = scal[i__];
      /* Computing 2nd power */
      d__1 = z1[i__] / denom;
      /* Computing 2nd power */
      d__2 = z2[i__] / denom;
      /* Computing 2nd power */
      d__3 = z3[i__] / denom;
      dyno = dyno + d__1 * d__1 + d__2 * d__2 + d__3 * d__3;
    }

  dyno = sqrt(dyno / n3);

  /* ---     BAD CONVERGENCE OR NUMBER OF ITERATIONS TO LARGE */
  if (newt > 1 && newt < *nit)
    {
      thq = dyno / dynold;

      if (newt == 2)
        {
          theta = thq;
        }
      else
        {
          theta = sqrt(thq * thqold);
        }

      thqold = thq;

      if (theta < .99)
        {
          faccon = theta / (1. - theta);
          i__1 = *nit - 1 - newt;
          dyth = faccon * dyno * pow_di(&theta, &i__1) / *fnewt;

          if (dyth >= 1.)
            {
              /* Computing MAX */
              d__1 = 1e-4, d__2 = min(20., dyth);
              qnewt = max(d__1, d__2);
              d__1 = -1. / (*nit + 4. - 1 - newt);
              hhfac = pow_dd(&qnewt, &d__1) * .8;
              *h__ = hhfac * *h__;
              reject = TRUE_;
              last = FALSE_;

              if (caljac)
                {
                  goto L20;
                }

              goto L10;
            }
        }
      else
        {
          goto L78;
        }
    }

  dynold = max(dyno, *uround);
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f1i = f1[i__] + z1[i__];
      f2i = f2[i__] + z2[i__];
      f3i = f3[i__] + z3[i__];
      f1[i__] = f1i;
      f2[i__] = f2i;
      f3[i__] = f3i;
      z1[i__] = t11 * f1i + t12 * f2i + t13 * f3i;
      z2[i__] = t21 * f1i + t22 * f2i + t23 * f3i;
      z3[i__] = t31 * f1i + f2i;
    }

  if (faccon * dyno > *fnewt)
    {
      goto L40;
    }

  /* --- ERROR ESTIMATION */
  estrad_(n, &fjac[fjac_offset], ldjac, mljac, mujac, &fmas[fmas_offset], ldmas, mlmas, mumas,
          h__, &dd1, &dd2, &dd3, fcn, nfcn, &y0[1], &y[1], ijob, x, m1, m2, nm1, &e1[e1_offset],
          lde1, &z1[1], &z2[1], &z3[1], &cont[1], &f1[1], &f2[1], &ip1[1], &iphes[1], &scal[1], &err,
          &first, &reject, &fac1, &rpar[1], &ipar[1]);
  /* --- COMPUTATION OF HNEW */
  /* --- WE REQUIRE .2<=HNEW/H<=8. */
  /* Computing MIN */
  d__1 = *safe, d__2 = cfac / (newt + (*nit << 1));
  fac = min(d__1, d__2);
  /* Computing MAX */
  /* Computing MIN */
  d__3 = *facl, d__4 = pow_dd(&err, &c_b115) / fac;
  d__1 = *facr, d__2 = min(d__3, d__4);
  quot = max(d__1, d__2);
  hnew = *h__ / quot;

  /* *** *** *** *** *** *** *** */
  /*  IS THE ERROR SMALL ENOUGH ? */
  /* *** *** *** *** *** *** *** */
  if (err < 1.)
    {
      /* --- STEP IS ACCEPTED */
      first = FALSE_;
      ++(*naccpt);

      if (*pred)
        {
          /*       --- PREDICTIVE CONTROLLER OF GUSTAFSSON */
          if (*naccpt > 1)
            {
              /* Computing 2nd power */
              d__2 = err;
              d__1 = d__2 * d__2 / erracc;
              facgus = hacc / *h__ * pow_dd(&d__1, &c_b115) / *safe;
              /* Computing MAX */
              d__1 = *facr, d__2 = min(*facl, facgus);
              facgus = max(d__1, d__2);
              quot = max(quot, facgus);
              hnew = *h__ / quot;
            }

          hacc = *h__;
          erracc = max(.01, err);
        }

      xold = *x;
      hold = *h__;
      *x = xph;
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          y[i__] += z3[i__];
          z2i = z2[i__];
          z1i = z1[i__];
          cont[i__ + *n] = (z2i - z3[i__]) / conra5_1.c2m1;
          ak = (z1i - z2i) / c1mc2;
          acont3 = z1i / c1;
          acont3 = (ak - acont3) / c2;
          cont[i__ + n2] = (ak - cont[i__ + *n]) / conra5_1.c1m1;
          cont[i__ + n3] = cont[i__ + n2] - acont3;
        }

      if (*itol == 0)
        {
          i__1 = *n;

          for (i__ = 1; i__ <= i__1; ++i__)
            {
              scal[i__] = atol[1] + rtol[1] * (d__1 = y[i__], abs(d__1));
            }
        }
      else
        {
          i__1 = *n;

          for (i__ = 1; i__ <= i__1; ++i__)
            {
              scal[i__] = atol[i__] + rtol[i__] * (d__1 = y[i__], abs(d__1))
                          ;
            }
        }

      if (*iout != 0)
        {
          nrsol = *naccpt + 1;
          conra5_1.xsol = *x;
          xosol = xold;
          i__1 = *n;

          for (i__ = 1; i__ <= i__1; ++i__)
            {
              cont[i__] = y[i__];
            }

          nsolu = *n;
          conra5_1.hsol = hold;
          (*solout)(&nrsol, &xosol, &conra5_1.xsol, &y[1], &cont[1], &lrc, &nsolu, &rpar[1], n, &irtrn);

          if (irtrn < 0)
            {
              goto L179;
            }
        }

      caljac = FALSE_;

      if (last)
        {
          *h__ = hopt;
          *idid = 1;
          return 0;
        }

      (*fcn)(n, x, &y[1], &y0[1], &rpar[1], &ipar[1]);
      ++(*nfcn);
      /* Computing MIN */
      d__1 = abs(hnew);
      hnew = posneg * min(d__1, hmaxn);
      hopt = hnew;
      hopt = min(*h__, hnew);

      if (reject)
        {
          /* Computing MIN */
          d__1 = abs(hnew), d__2 = abs(*h__);
          hnew = posneg * min(d__1, d__2);
        }

      reject = FALSE_;

      if ((*x + hnew / *quot1 - *xend) * posneg >= 0.)
        {
          *h__ = *xend - *x;
          last = TRUE_;
        }
      else
        {
          qt = hnew / *h__;
          hhfac = *h__;

          if (theta <= *thet && qt >= *quot1 && qt <= *quot2)
            {
              goto L30;
            }

          *h__ = hnew;
        }

      hhfac = *h__;

      if (theta <= *thet)
        {
          goto L20;
        }

      goto L10;
    }
  else
    {
      /* --- STEP IS REJECTED */
      reject = TRUE_;
      last = FALSE_;

      if (first)
        {
          *h__ *= .1;
          hhfac = .1;
        }
      else
        {
          hhfac = hnew / *h__;
          *h__ = hnew;
        }

      if (*naccpt >= 1)
        {
          ++(*nrejct);
        }

      if (caljac)
        {
          goto L20;
        }

      goto L10;
    }

  /* --- UNEXPECTED STEP-REJECTION */
L78:

  if (ier != 0)
    {
      ++nsing;

      if (nsing >= 5)
        {
          goto L176;
        }
    }

  *h__ *= .5;
  hhfac = .5;
  reject = TRUE_;
  last = FALSE_;

  if (caljac)
    {
      goto L20;
    }

  goto L10;
  /* --- FAIL EXIT */
L176:
//    s_wsfe(&io___176);
//    do_fio(&c__1, (char *)&(*x), (ftnlen)sizeof(double));
//    e_wsfe();
//    s_wsle(&io___177);
//    do_lio(&c__9, &c__1, " MATRIX IS REPEATEDLY SINGULAR, IER=", (ftnlen)36);
//    do_lio(&c__3, &c__1, (char *)&ier, (ftnlen)sizeof(C_INT));
//    e_wsle();
  *idid = -4;
  return 0;
L177:
//    s_wsfe(&io___178);
//    do_fio(&c__1, (char *)&(*x), (ftnlen)sizeof(double));
//    e_wsfe();
//    s_wsle(&io___179);
//    do_lio(&c__9, &c__1, " STEP SIZE T0O SMALL, H=", (ftnlen)24);
//    do_lio(&c__5, &c__1, (char *)&(*h__), (ftnlen)sizeof(double));
//    e_wsle();
  *idid = -3;
  return 0;
L178:
//    s_wsfe(&io___180);
//    do_fio(&c__1, (char *)&(*x), (ftnlen)sizeof(double));
//    e_wsfe();
//    s_wsle(&io___181);
//    do_lio(&c__9, &c__1, " MORE THAN NMAX =", (ftnlen)17);
//    do_lio(&c__3, &c__1, (char *)&(*nmax), (ftnlen)sizeof(C_INT));
//    do_lio(&c__9, &c__1, "STEPS ARE NEEDED", (ftnlen)16);
//    e_wsle();
  *idid = -2;
  return 0;
  /* --- EXIT CAUSED BY SOLOUT */
L179:
//    s_wsfe(&io___182);
//    do_fio(&c__1, (char *)&(*x), (ftnlen)sizeof(double));
//    e_wsfe();
  *idid = 2;
  return 0;
} /* radcor_ */

/*     END OF SUBROUTINE RADCOR */

/* *********************************************************** */

double contr5_(C_INT *i__, double *x, double *cont, C_INT *lrc)
{
  /* System generated locals */
  double ret_val;

  /* Local variables */
  static double s;

  /* ---------------------------------------------------------- */
  /*     THIS FUNCTION CAN BE USED FOR CONINUOUS OUTPUT. IT PROVIDES AN */
  /*     APPROXIMATION TO THE I-TH COMPONENT OF THE SOLUTION AT X. */
  /*     IT GIVES THE VALUE OF THE COLLOCATION POLYNOMIAL, DEFINED FOR */
  /*     THE LAST SUCCESSFULLY COMPUTED STEP (BY RADAU5). */
  /* ---------------------------------------------------------- */
  /* Parameter adjustments */
  --cont;

  /* Function Body */
  s = (*x - conra5_1.xsol) / conra5_1.hsol;
  ret_val = cont[*i__] + s * (cont[*i__ + conra5_1.nn] + (s - conra5_1.c2m1)
                              * (cont[*i__ + conra5_1.nn2] + (s - conra5_1.c1m1) * cont[*i__ +
                                  conra5_1.nn3]));
  return ret_val;
} /* contr5_ */

double d_sign(double *a, double *b)
{
  double x;
  x = (*a >= 0 ? *a : - *a);
  return (*b >= 0 ? x : -x);
}

static double pow_dd(double *ap, double *bp)
{
  return (pow(*ap, *bp));
}

double pow_di(double *ap, C_INT *bp)
{
  double pow, x;
  C_INT n;
  unsigned long u;

  pow = 1;
  x = *ap;
  n = *bp;

  if (n != 0)
    {
      if (n < 0)
        {
          n = -n;
          x = 1 / x;
        }

      for (u = n; ;)
        {
          if (u & 01)
            pow *= x;

          if (u >>= 1)
            x *= x;
          else
            break;
        }
    }

  return (pow);
}
