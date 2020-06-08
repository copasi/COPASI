// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// This includes code automatically translated with F2C
// It uses fmin fmax (from <cmath>) for floating point numbers
// min and max is used for integers. Please don't change this!

#include <cfloat>
#include <climits>
#include <cmath>
#include "copasi/copasi.h"
#include "CNL2SOL.h"

/* Table of constant values */
static integer c__1 = 1;
static integer c__9 = 9;
static integer c__3 = 3;
static integer c__2 = 2;
static doublereal c_b78 = 0.;
static integer c_n1 = -1;
static doublereal c_b152 = -1.;
static doublereal c_b173 = 1.;
static integer c__6 = 6;
static logical c_true = TRUE_;
static integer c__5 = 5;
static integer c__4 = 4;
static integer c__0 = 0;
static logical c_false = FALSE_;
static doublereal c_b767 = .33333333333333331;

int s_copy(char *a, char *b, ftnlen la, ftnlen lb);
doublereal pow_dd(doublereal *ap, doublereal *bp);

CNL2SOL::CNL2SOL()
{
}

CNL2SOL::~CNL2SOL()
{
}

int CNL2SOL::dn2fb_(integer *n, integer *p, doublereal *x, doublereal *b,
                    FNL2SOL *calcr, integer *iv, integer *liv, integer *lv, doublereal *v,
                    integer *ui, doublereal *ur, U_fp uf)
{
  /* Initialized data */

  static doublereal hlim = .1;
  static doublereal negpt5 = -.5;
  static doublereal one = 1.;
  static doublereal zero = 0.;

  /* System generated locals */
  integer i__1, i__2;
  doublereal d__1, d__2;

  /* Local variables */
  static doublereal h__;
  static integer i__, k;
  static doublereal t;
  static integer d1;
  static doublereal h0;
  static integer n1, n2, r1;
  extern int drn2gb_(doublereal *, doublereal *,
                     doublereal *, integer *, integer *, integer *, integer *, integer
                     *, integer *, integer *, integer *, doublereal *, doublereal *,
                     doublereal *, doublereal *), dv7scp_(integer *, doublereal *,
                         doublereal *);
  static integer dk, nf, ng, rn;
  static doublereal xk;
  extern int divset_(integer *, integer *, integer *,
                     integer *, doublereal *);
  static integer j1k, dr1, rd1, iv1;
  static doublereal xk1;

  /*  ***  MINIMIZE A NONLINEAR SUM OF SQUARES USING RESIDUAL VALUES ONLY.. */
  /*  ***  THIS AMOUNTS TO   DN2G WITHOUT THE SUBROUTINE PARAMETER CALCJ. */

  /*  ***  PARAMETERS  *** */

  /* /6 */
  /*     INTEGER IV(LIV), UI(1) */
  /*     DOUBLE PRECISION X(P), B(2,P), V(LV), UR(1) */
  /* /7 */
  /* / */

  /* -----------------------------  DISCUSSION  ---------------------------- */

  /*        THIS AMOUNTS TO SUBROUTINE NL2SNO (REF. 1) MODIFIED TO HANDLE */
  /*     SIMPLE BOUNDS ON THE VARIABLES... */
  /*           B(1,I) .LE. X(I) .LE. B(2,I), I = 1(1)P. */
  /*        THE PARAMETERS FOR  DN2FB ARE THE SAME AS THOSE FOR  DN2GB */
  /*     (WHICH SEE), EXCEPT THAT CALCJ IS OMITTED.  INSTEAD OF CALLING */
  /*     CALCJ TO OBTAIN THE JACOBIAN MATRIX OF R AT X,  DN2FB COMPUTES */
  /*     AN APPROXIMATION TO IT BY FINITE (FORWARD) DIFFERENCES -- SEE */
  /*     V(DLTFDJ) BELOW.   DN2FB DOES NOT COMPUTE A COVARIANCE MATRIX. */
  /*        THE NUMBER OF EXTRA CALLS ON CALCR USED IN COMPUTING THE JACO- */
  /*     BIAN APPROXIMATION ARE NOT INCLUDED IN THE FUNCTION EVALUATION */
  /*     COUNT IV(NFCALL), BUT ARE RECORDED IN IV(NGCALL) INSTEAD. */

  /* V(DLTFDJ)... V(43) HELPS CHOOSE THE STEP SIZE USED WHEN COMPUTING THE */
  /*             FINITE-DIFFERENCE JACOBIAN MATRIX.  FOR DIFFERENCES IN- */
  /*             VOLVING X(I), THE STEP SIZE FIRST TRIED IS */
  /*                       V(DLTFDJ) * fmax(ABS(X(I)), 1/D(I)), */
  /*             WHERE D IS THE CURRENT SCALE VECTOR (SEE REF. 1).  (IF */
  /*             THIS STEP IS TOO BIG, I.E., IF CALCR SETS NF TO 0, THEN */
  /*             SMALLER STEPS ARE TRIED UNTIL THE STEP SIZE IS SHRUNK BE- */
  /*             LOW 1000 * MACHEP, WHERE MACHEP IS THE UNIT ROUNDOFF. */
  /*             DEFAULT = MACHEP**0.5. */

  /*  ***  REFERENCE  *** */

  /* 1.  DENNIS, J.E., GAY, D.M., AND WELSCH, R.E. (1981), AN ADAPTIVE */
  /*             NONLINEAR LEAST-SQUARES ALGORITHM, ACM TRANS. MATH. */
  /*             SOFTWARE, VOL. 7, NO. 3. */

  /*  ***  GENERAL  *** */

  /*     CODED BY DAVID M. GAY. */

  /* +++++++++++++++++++++++++++  DECLARATIONS  +++++++++++++++++++++++++++ */

  /*  ***  EXTERNAL SUBROUTINES  *** */

  /* DIVSET.... PROVIDES DEFAULT IV AND V INPUT COMPONENTS. */
  /* DRN2GB... CARRIES OUT OPTIMIZATION ITERATIONS. */
  /* DN2RDP... PRINTS REGRESSION DIAGNOSTICS. */
  /* DV7SCP... SETS ALL ELEMENTS OF A VECTOR TO A SCALAR. */

  /*  ***  LOCAL VARIABLES  *** */

  /*  ***  IV AND V COMPONENTS  *** */

  /* /6 */
  /*     DATA COVREQ/15/, D/27/, DINIT/38/, DLTFDJ/43/, J/70/, MODE/35/, */
  /*    1     NEXTV/47/, NFCALL/6/, NFGCAL/7/, NGCALL/30/, NGCOV/53/, */
  /*    2     R/61/, REGD0/82/, TOOBIG/2/, VNEED/4/ */
  /* /7 */
  /* / */
  /* Parameter adjustments */
  b -= 3;
  --x;
  --iv;
  --v;
  --ui;
  --ur;

  /* Function Body */

  /* ---------------------------------  BODY  ------------------------------ */
  if (iv[1] == 0)
    {
      divset_(&c__1, &iv[1], liv, lv, &v[1]);
    }

  iv[15] = 0;
  iv1 = iv[1];

  if (iv1 == 14)
    {
      goto L10;
    }

  if (iv1 > 2 && iv1 < 12)
    {
      goto L10;
    }

  if (iv1 == 12)
    {
      iv[1] = 13;
    }

  if (iv[1] == 13)
    {
      iv[4] = iv[4] + *p + *n * (*p + 2);
    }

  drn2gb_(&b[3], &x[1], &v[1], &iv[1], liv, lv, n, n, &n1, &n2, p, &v[1], &
          v[1], &v[1], &x[1]);

  if (iv[1] != 14)
    {
      goto L999;
    }

  /*  ***  STORAGE ALLOCATION  *** */

  iv[27] = iv[47];
  iv[61] = iv[27] + *p;
  iv[82] = iv[61] + *n;
  iv[70] = iv[82] + *n;
  iv[47] = iv[70] + *n * *p;

  if (iv1 == 13)
    {
      goto L999;
    }

L10:
  d1 = iv[27];
  dr1 = iv[70];
  r1 = iv[61];
  rn = r1 + *n - 1;
  rd1 = iv[82];

L20:
  drn2gb_(&b[3], &v[d1], &v[dr1], &iv[1], liv, lv, n, n, &n1, &n2, p, &v[r1]
          , &v[rd1], &v[1], &x[1]);

  if ((i__1 = iv[1] - 2) < 0)
    {
      goto L30;
    }
  else if (i__1 == 0)
    {
      goto L50;
    }
  else
    {
      goto L999;
    }

  /*  ***  NEW FUNCTION VALUE (R VALUE) NEEDED  *** */

L30:
  nf = iv[6];
  (*calcr)(n, p, &x[1], &nf, &v[r1], &ui[1], &ur[1], (U_fp)uf);

  if (nf > 0)
    {
      goto L40;
    }

  iv[2] = 1;
  goto L20;
L40:

  if (iv[1] > 0)
    {
      goto L20;
    }

  /*  ***  COMPUTE FINITE-DIFFERENCE APPROXIMATION TO DR = GRAD. OF R  *** */

  /*     *** INITIALIZE D IF NECESSARY *** */

L50:

  if (iv[35] < 0 && v[38] == zero)
    {
      dv7scp_(p, &v[d1], &one);
    }

  j1k = dr1;
  dk = d1;
  ng = iv[30] - 1;

  if (iv[1] == -1)
    {
      --iv[53];
    }

  i__1 = *p;

  for (k = 1; k <= i__1; ++k)
    {
      if (b[(k << 1) + 1] >= b[(k << 1) + 2])
        {
          goto L110;
        }

      xk = x[k];
      /* Computing MAX */
      d__1 = fabs(xk), d__2 = one / v[dk];
      h__ = v[43] * fmax(d__1, d__2);
      h0 = h__;
      ++dk;
      t = negpt5;
      xk1 = xk + h__;

      if (xk - h__ >= b[(k << 1) + 1])
        {
          goto L60;
        }

      t = -t;

      if (xk1 > b[(k << 1) + 2])
        {
          goto L80;
        }

L60:

      if (xk1 <= b[(k << 1) + 2])
        {
          goto L70;
        }

      t = -t;
      h__ = -h__;
      xk1 = xk + h__;

      if (xk1 < b[(k << 1) + 1])
        {
          goto L80;
        }

L70:
      x[k] = xk1;
      nf = iv[7];
      (*calcr)(n, p, &x[1], &nf, &v[j1k], &ui[1], &ur[1], (U_fp)uf);
      ++ng;

      if (nf > 0)
        {
          goto L90;
        }

      h__ = t * h__;
      xk1 = xk + h__;

      if ((d__1 = h__ / h0, fabs(d__1)) >= hlim)
        {
          goto L70;
        }

L80:
      iv[2] = 1;
      iv[30] = ng;
      goto L20;
L90:
      x[k] = xk;
      iv[30] = ng;
      i__2 = rn;

      for (i__ = r1; i__ <= i__2; ++i__)
        {
          v[j1k] = (v[j1k] - v[i__]) / h__;
          ++j1k;
          /* L100: */
        }

      goto L120;
      /*        *** SUPPLY A ZERO DERIVATIVE FOR CONSTANT COMPONENTS... */
L110:
      dv7scp_(n, &v[j1k], &zero);
      j1k += *n;
L120:
      ;
    }

  goto L20;

L999:
  return 0;

  /*  ***  LAST CARD OF  DN2FB FOLLOWS  *** */
} /* dn2fb_ */

doublereal d1mach_(integer *i)
{
  /*  DOUBLE-PRECISION MACHINE CONSTANTS */
  /*  D1MACH(1) = B**(EMIN-1), THE SMALLEST POSITIVE MAGNITUDE. */
  /*  D1MACH(2) = B**EMAX*(1 - B**(-T)), THE LARGEST MAGNITUDE. */
  /*  D1MACH(3) = B**(-T), THE SMALLEST RELATIVE SPACING. */
  /*  D1MACH(4) = B**(1-T), THE LARGEST RELATIVE SPACING. */
  /*  D1MACH(5) = LOG10(B) */

  switch (*i)
    {
      case 1: return DBL_MIN;

      case 2: return DBL_MAX;

      case 3: return DBL_EPSILON / FLT_RADIX;

      case 4: return DBL_EPSILON;

      case 5: return log10(FLT_RADIX);
    }

  fprintf(stderr, "invalid argument: d1mach(%ld)\n", *i);
  exit(1);
  return 0; /* for compilers that complain of missing return values */
} /* d1mach_ */

int da7sst_(integer *iv, integer *liv, integer *lv,
            doublereal *v)
{
  /* System generated locals */
  doublereal d__1, d__2;

  /* Local variables */
  static doublereal emax, xmax, rfac1;
  static integer i__;
  static doublereal emaxs;
  static logical goodx;
  static integer nfc;
  static doublereal gts;

  /*  ***  ASSESS CANDIDATE STEP (***SOL VERSION 2.3)  *** */

  /*  ***  PURPOSE  *** */

  /*        THIS SUBROUTINE IS CALLED BY AN UNCONSTRAINED MINIMIZATION */
  /*     ROUTINE TO ASSESS THE NEXT CANDIDATE STEP.  IT MAY RECOMMEND ONE */
  /*     OF SEVERAL COURSES OF ACTION, SUCH AS ACCEPTING THE STEP, RECOM- */
  /*     PUTING IT USING THE SAME OR A NEW QUADRATIC MODEL, OR HALTING DUE */
  /*     TO CONVERGENCE OR FALSE CONVERGENCE.  SEE THE RETURN CODE LISTING */
  /*     BELOW. */

  /* --------------------------  PARAMETER USAGE  -------------------------- */

  /*  IV (I/O) INTEGER PARAMETER AND SCRATCH VECTOR -- SEE DESCRIPTION */
  /*             BELOW OF IV VALUES REFERENCED. */
  /* LIV (IN)  LENGTH OF IV ARRAY. */
  /*  LV (IN)  LENGTH OF V ARRAY. */
  /*   V (I/O) REAL PARAMETER AND SCRATCH VECTOR -- SEE DESCRIPTION */
  /*             BELOW OF V VALUES REFERENCED. */

  /*  ***  IV VALUES REFERENCED  *** */

  /*    IV(IRC) (I/O) ON INPUT FOR THE FIRST STEP TRIED IN A NEW ITERATION, */
  /*             IV(IRC) SHOULD BE SET TO 3 OR 4 (THE VALUE TO WHICH IT IS */
  /*             SET WHEN STEP IS DEFINITELY TO BE ACCEPTED).  ON INPUT */
  /*             AFTER STEP HAS BEEN RECOMPUTED, IV(IRC) SHOULD BE */
  /*             UNCHANGED SINCE THE PREVIOUS RETURN OF DA7SST. */
  /*                ON OUTPUT, IV(IRC) IS A RETURN CODE HAVING ONE OF THE */
  /*             FOLLOWING VALUES... */
  /*                  1 = SWITCH MODELS OR TRY SMALLER STEP. */
  /*                  2 = SWITCH MODELS OR ACCEPT STEP. */
  /*                  3 = ACCEPT STEP AND DETERMINE V(RADFAC) BY GRADIENT */
  /*                       TESTS. */
  /*                  4 = ACCEPT STEP, V(RADFAC) HAS BEEN DETERMINED. */
  /*                  5 = RECOMPUTE STEP (USING THE SAME MODEL). */
  /*                  6 = RECOMPUTE STEP WITH RADIUS = V(LMAXS) BUT DO NOT */
  /*                       EVALUATE THE OBJECTIVE FUNCTION. */
  /*                  7 = X-CONVERGENCE (SEE V(XCTOL)). */
  /*                  8 = RELATIVE FUNCTION CONVERGENCE (SEE V(RFCTOL)). */
  /*                  9 = BOTH X- AND RELATIVE FUNCTION CONVERGENCE. */
  /*                 10 = ABSOLUTE FUNCTION CONVERGENCE (SEE V(AFCTOL)). */
  /*                 11 = SINGULAR CONVERGENCE (SEE V(LMAXS)). */
  /*                 12 = FALSE CONVERGENCE (SEE V(XFTOL)). */
  /*                 13 = IV(IRC) WAS OUT OF RANGE ON INPUT. */
  /*             RETURN CODE I HAS PRECEDENCE OVER I+1 FOR I = 9, 10, 11. */
  /* IV(MLSTGD) (I/O) SAVED VALUE OF IV(MODEL). */
  /*  IV(MODEL) (I/O) ON INPUT, IV(MODEL) SHOULD BE AN INTEGER IDENTIFYING */
  /*             THE CURRENT QUADRATIC MODEL OF THE OBJECTIVE FUNCTION. */
  /*             IF A PREVIOUS STEP YIELDED A BETTER FUNCTION REDUCTION, */
  /*             THEN IV(MODEL) WILL BE SET TO IV(MLSTGD) ON OUTPUT. */
  /* IV(NFCALL) (IN)  INVOCATION COUNT FOR THE OBJECTIVE FUNCTION. */
  /* IV(NFGCAL) (I/O) VALUE OF IV(NFCALL) AT STEP THAT GAVE THE BIGGEST */
  /*             FUNCTION REDUCTION THIS ITERATION.  IV(NFGCAL) REMAINS */
  /*             UNCHANGED UNTIL A FUNCTION REDUCTION IS OBTAINED. */
  /* IV(RADINC) (I/O) THE NUMBER OF RADIUS INCREASES (OR MINUS THE NUMBER */
  /*             OF DECREASES) SO FAR THIS ITERATION. */
  /* IV(RESTOR) (OUT) SET TO 1 IF V(F) HAS BEEN RESTORED AND X SHOULD BE */
  /*             RESTORED TO ITS INITIAL VALUE, TO 2 IF X SHOULD BE SAVED, */
  /*             TO 3 IF X SHOULD BE RESTORED FROM THE SAVED VALUE, AND TO */
  /*             0 OTHERWISE. */
  /*  IV(STAGE) (I/O) COUNT OF THE NUMBER OF MODELS TRIED SO FAR IN THE */
  /*             CURRENT ITERATION. */
  /* IV(STGLIM) (IN)  MAXIMUM NUMBER OF MODELS TO CONSIDER. */
  /* IV(SWITCH) (OUT) SET TO 0 UNLESS A NEW MODEL IS BEING TRIED AND IT */
  /*             GIVES A SMALLER FUNCTION VALUE THAN THE PREVIOUS MODEL, */
  /*             IN WHICH CASE DA7SST SETS IV(SWITCH) = 1. */
  /* IV(TOOBIG) (I/O)  IS NONZERO ON INPUT IF STEP WAS TOO BIG (E.G., IF */
  /*             IT WOULD CAUSE OVERFLOW).  IT IS SET TO 0 ON RETURN. */
  /*   IV(XIRC) (I/O) VALUE THAT IV(IRC) WOULD HAVE IN THE ABSENCE OF */
  /*             CONVERGENCE, FALSE CONVERGENCE, AND OVERSIZED STEPS. */

  /*  ***  V VALUES REFERENCED  *** */

  /* V(AFCTOL) (IN)  ABSOLUTE FUNCTION CONVERGENCE TOLERANCE.  IF THE */
  /*             ABSOLUTE VALUE OF THE CURRENT FUNCTION VALUE V(F) IS LESS */
  /*             THAN V(AFCTOL) AND DA7SST DOES NOT RETURN WITH */
  /*             IV(IRC) = 11, THEN DA7SST RETURNS WITH IV(IRC) = 10. */
  /* V(DECFAC) (IN)  FACTOR BY WHICH TO DECREASE RADIUS WHEN IV(TOOBIG) IS */
  /*             NONZERO. */
  /* V(DSTNRM) (IN)  THE 2-NORM OF D*STEP. */
  /* V(DSTSAV) (I/O) VALUE OF V(DSTNRM) ON SAVED STEP. */
  /*   V(DST0) (IN)  THE 2-NORM OF D TIMES THE NEWTON STEP (WHEN DEFINED, */
  /*             I.E., FOR V(NREDUC) .GE. 0). */
  /*      V(F) (I/O) ON BOTH INPUT AND OUTPUT, V(F) IS THE OBJECTIVE FUNC- */
  /*             TION VALUE AT X.  IF X IS RESTORED TO A PREVIOUS VALUE, */
  /*             THEN V(F) IS RESTORED TO THE CORRESPONDING VALUE. */
  /*   V(FDIF) (OUT) THE FUNCTION REDUCTION V(F0) - V(F) (FOR THE OUTPUT */
  /*             VALUE OF V(F) IF AN EARLIER STEP GAVE A BIGGER FUNCTION */
  /*             DECREASE, AND FOR THE INPUT VALUE OF V(F) OTHERWISE). */
  /* V(FLSTGD) (I/O) SAVED VALUE OF V(F). */
  /*     V(F0) (IN)  OBJECTIVE FUNCTION VALUE AT START OF ITERATION. */
  /* V(GTSLST) (I/O) VALUE OF V(GTSTEP) ON SAVED STEP. */
  /* V(GTSTEP) (IN)  INNER PRODUCT BETWEEN STEP AND GRADIENT. */
  /* V(INCFAC) (IN)  MINIMUM FACTOR BY WHICH TO INCREASE RADIUS. */
  /*  V(LMAXS) (IN)  MAXIMUM REASONABLE STEP SIZE (AND INITIAL STEP BOUND). */
  /*             IF THE ACTUAL FUNCTION DECREASE IS NO MORE THAN TWICE */
  /*             WHAT WAS PREDICTED, IF A RETURN WITH IV(IRC) = 7, 8, OR 9 */
  /*             DOES NOT OCCUR, IF V(DSTNRM) .GT. V(LMAXS) OR THE CURRENT */
  /*             STEP IS A NEWTON STEP, AND IF */
  /*             V(PREDUC) .LE. V(SCTOL) * ABS(V(F0)), THEN DA7SST RETURNS */
  /*             WITH IV(IRC) = 11.  IF SO DOING APPEARS WORTHWHILE, THEN */
  /*            DA7SST REPEATS THIS TEST (DISALLOWING A FULL NEWTON STEP) */
  /*             WITH V(PREDUC) COMPUTED FOR A STEP OF LENGTH V(LMAXS) */
  /*             (BY A RETURN WITH IV(IRC) = 6). */
  /* V(NREDUC) (I/O)  FUNCTION REDUCTION PREDICTED BY QUADRATIC MODEL FOR */
  /*             NEWTON STEP.  IF DA7SST IS CALLED WITH IV(IRC) = 6, I.E., */
  /*             IF V(PREDUC) HAS BEEN COMPUTED WITH RADIUS = V(LMAXS) FOR */
  /*             USE IN THE SINGULAR CONVERGENCE TEST, THEN V(NREDUC) IS */
  /*             SET TO -V(PREDUC) BEFORE THE LATTER IS RESTORED. */
  /* V(PLSTGD) (I/O) VALUE OF V(PREDUC) ON SAVED STEP. */
  /* V(PREDUC) (I/O) FUNCTION REDUCTION PREDICTED BY QUADRATIC MODEL FOR */
  /*             CURRENT STEP. */
  /* V(RADFAC) (OUT) FACTOR TO BE USED IN DETERMINING THE NEW RADIUS, */
  /*             WHICH SHOULD BE V(RADFAC)*DST, WHERE  DST  IS EITHER THE */
  /*             OUTPUT VALUE OF V(DSTNRM) OR THE 2-NORM OF */
  /*             DIAG(NEWD)*STEP  FOR THE OUTPUT VALUE OF STEP AND THE */
  /*             UPDATED VERSION, NEWD, OF THE SCALE VECTOR D.  FOR */
  /*             IV(IRC) = 3, V(RADFAC) = 1.0 IS RETURNED. */
  /* V(RDFCMN) (IN)  MINIMUM VALUE FOR V(RADFAC) IN TERMS OF THE INPUT */
  /*             VALUE OF V(DSTNRM) -- SUGGESTED VALUE = 0.1. */
  /* V(RDFCMX) (IN)  MAXIMUM VALUE FOR V(RADFAC) -- SUGGESTED VALUE = 4.0. */
  /*  V(RELDX) (IN) SCALED RELATIVE CHANGE IN X CAUSED BY STEP, COMPUTED */
  /*             (E.G.) BY FUNCTION  DRLDST  AS */
  /*                 MAX (D(I)*ABS(X(I)-X0(I)), 1 .LE. I .LE. P) / */
  /*                    MAX (D(I)*(ABS(X(I))+ABS(X0(I))), 1 .LE. I .LE. P). */
  /* V(RFCTOL) (IN)  RELATIVE FUNCTION CONVERGENCE TOLERANCE.  IF THE */
  /*             ACTUAL FUNCTION REDUCTION IS AT MOST TWICE WHAT WAS PRE- */
  /*             DICTED AND  V(NREDUC) .LE. V(RFCTOL)*ABS(V(F0)),  THEN */
  /*            DA7SST RETURNS WITH IV(IRC) = 8 OR 9. */
  /*  V(SCTOL) (IN)  SINGULAR CONVERGENCE TOLERANCE -- SEE V(LMAXS). */
  /* V(STPPAR) (IN)  MARQUARDT PARAMETER -- 0 MEANS FULL NEWTON STEP. */
  /* V(TUNER1) (IN)  TUNING CONSTANT USED TO DECIDE IF THE FUNCTION */
  /*             REDUCTION WAS MUCH LESS THAN EXPECTED.  SUGGESTED */
  /*             VALUE = 0.1. */
  /* V(TUNER2) (IN)  TUNING CONSTANT USED TO DECIDE IF THE FUNCTION */
  /*             REDUCTION WAS LARGE ENOUGH TO ACCEPT STEP.  SUGGESTED */
  /*             VALUE = 10**-4. */
  /* V(TUNER3) (IN)  TUNING CONSTANT USED TO DECIDE IF THE RADIUS */
  /*             SHOULD BE INCREASED.  SUGGESTED VALUE = 0.75. */
  /*  V(XCTOL) (IN)  X-CONVERGENCE CRITERION.  IF STEP IS A NEWTON STEP */
  /*             (V(STPPAR) = 0) HAVING V(RELDX) .LE. V(XCTOL) AND GIVING */
  /*             AT MOST TWICE THE PREDICTED FUNCTION DECREASE, THEN */
  /*            DA7SST RETURNS IV(IRC) = 7 OR 9. */
  /*  V(XFTOL) (IN)  FALSE CONVERGENCE TOLERANCE.  IF STEP GAVE NO OR ONLY */
  /*             A SMALL FUNCTION DECREASE AND V(RELDX) .LE. V(XFTOL), */
  /* 000000 / */
  /*             THEN DA7SST RETURNS WITH IV(IRC) = 12. */

  /* -------------------------------  NOTES  ------------------------------- */

  /*  ***  APPLICATION AND USAGE RESTRICTIONS  *** */

  /*        THIS ROUTINE IS CALLED AS PART OF THE NL2SOL (NONLINEAR */
  /*     LEAST-SQUARES) PACKAGE.  IT MAY BE USED IN ANY UNCONSTRAINED */
  /*     MINIMIZATION SOLVER THAT USES DOGLEG, GOLDFELD-QUANDT-TROTTER, */
  /*     OR LEVENBERG-MARQUARDT STEPS. */

  /*  ***  ALGORITHM NOTES  *** */

  /*        SEE (1) FOR FURTHER DISCUSSION OF THE ASSESSING AND MODEL */
  /*     SWITCHING STRATEGIES.  WHILE NL2SOL CONSIDERS ONLY TWO MODELS, */
  /*    DA7SST IS DESIGNED TO HANDLE ANY NUMBER OF MODELS. */

  /*  ***  USAGE NOTES  *** */

  /*        ON THE FIRST CALL OF AN ITERATION, ONLY THE I/O VARIABLES */
  /*     STEP, X, IV(IRC), IV(MODEL), V(F), V(DSTNRM), V(GTSTEP), AND */
  /*     V(PREDUC) NEED HAVE BEEN INITIALIZED.  BETWEEN CALLS, NO I/O */
  /*     VALUES EXCEPT STEP, X, IV(MODEL), V(F) AND THE STOPPING TOLER- */
  /*     ANCES SHOULD BE CHANGED. */
  /*        AFTER A RETURN FOR CONVERGENCE OR FALSE CONVERGENCE, ONE CAN */
  /*     CHANGE THE STOPPING TOLERANCES AND CALL DA7SST AGAIN, IN WHICH */
  /*     CASE THE STOPPING TESTS WILL BE REPEATED. */

  /*  ***  REFERENCES  *** */

  /*     (1) DENNIS, J.E., JR., GAY, D.M., AND WELSCH, R.E. (1981), */
  /*        AN ADAPTIVE NONLINEAR LEAST-SQUARES ALGORITHM, */
  /*        ACM TRANS. MATH. SOFTWARE, VOL. 7, NO. 3. */

  /*     (2) POWELL, M.J.D. (1970)  A FORTRAN SUBROUTINE FOR SOLVING */
  /*        SYSTEMS OF NONLINEAR ALGEBRAIC EQUATIONS, IN NUMERICAL */
  /*        METHODS FOR NONLINEAR ALGEBRAIC EQUATIONS, EDITED BY */
  /*        P. RABINOWITZ, GORDON AND BREACH, LONDON. */

  /*  ***  HISTORY  *** */

  /*        JOHN DENNIS DESIGNED MUCH OF THIS ROUTINE, STARTING WITH */
  /*     IDEAS IN (2). ROY WELSCH SUGGESTED THE MODEL SWITCHING STRATEGY. */
  /*        DAVID GAY AND STEPHEN PETERS CAST THIS SUBROUTINE INTO A MORE */
  /*     PORTABLE FORM (WINTER 1977), AND DAVID GAY CAST IT INTO ITS */
  /*     PRESENT FORM (FALL 1978), WITH MINOR CHANGES TO THE SINGULAR */
  /*     CONVERGENCE TEST IN MAY, 1984 (TO DEAL WITH FULL NEWTON STEPS). */

  /*  ***  GENERAL  *** */

  /*     THIS SUBROUTINE WAS WRITTEN IN CONNECTION WITH RESEARCH */
  /*     SUPPORTED BY THE NATIONAL SCIENCE FOUNDATION UNDER GRANTS */
  /*     MCS-7600324, DCR75-10143, 76-14311DSS, MCS76-11989, AND */
  /*     MCS-7906671. */

  /* ------------------------  EXTERNAL QUANTITIES  ------------------------ */

  /*  ***  NO EXTERNAL FUNCTIONS AND SUBROUTINES  *** */

  /* --------------------------  LOCAL VARIABLES  -------------------------- */

  /*  ***  SUBSCRIPTS FOR IV AND V  *** */

  /*  ***  DATA INITIALIZATIONS  *** */

  /* /6 */
  /*     DATA HALF/0.5D+0/, ONE/1.D+0/, ONEP2/1.2D+0/, TWO/2.D+0/, */
  /*    1     ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /* /6 */
  /*     DATA IRC/29/, MLSTGD/32/, MODEL/5/, NFCALL/6/, NFGCAL/7/, */
  /*    1     RADINC/8/, RESTOR/9/, STAGE/10/, STGLIM/11/, SWITCH/12/, */
  /*    2     TOOBIG/2/, XIRC/13/ */
  /* /7 */
  /* / */
  /* /6 */
  /*     DATA AFCTOL/31/, DECFAC/22/, DSTNRM/2/, DST0/3/, DSTSAV/18/, */
  /*    1     F/10/, FDIF/11/, FLSTGD/12/, F0/13/, GTSLST/14/, GTSTEP/4/, */
  /*    2     INCFAC/23/, LMAXS/36/, NREDUC/6/, PLSTGD/15/, PREDUC/7/, */
  /*    3     RADFAC/16/, RDFCMN/24/, RDFCMX/25/, RELDX/17/, RFCTOL/32/, */
  /*    4     SCTOL/37/, STPPAR/5/, TUNER1/26/, TUNER2/27/, TUNER3/28/, */
  /*    5     XCTOL/33/, XFTOL/34/ */
  /* /7 */
  /* / */

  /* +++++++++++++++++++++++++++++++  BODY  ++++++++++++++++++++++++++++++++ */

  /* Parameter adjustments */
  --iv;
  --v;

  /* Function Body */
  nfc = iv[6];
  iv[12] = 0;
  iv[9] = 0;
  rfac1 = 1.;
  goodx = TRUE_;
  i__ = iv[29];

  if (i__ >= 1 && i__ <= 12)
    {
      switch (i__)
        {
          case 1:  goto L20;

          case 2:  goto L30;

          case 3:  goto L10;

          case 4:  goto L10;

          case 5:  goto L40;

          case 6:  goto L280;

          case 7:  goto L220;

          case 8:  goto L220;

          case 9:  goto L220;

          case 10:  goto L220;

          case 11:  goto L220;

          case 12:  goto L170;
        }
    }

  iv[29] = 13;
  goto L999;

  /*  ***  INITIALIZE FOR NEW ITERATION  *** */

L10:
  iv[10] = 1;
  iv[8] = 0;
  v[12] = v[13];

  if (iv[2] == 0)
    {
      goto L110;
    }

  iv[10] = -1;
  iv[13] = i__;
  goto L60;

  /*  ***  STEP WAS RECOMPUTED WITH NEW MODEL OR SMALLER RADIUS  *** */
  /*  ***  FIRST DECIDE WHICH  *** */

L20:

  if (iv[5] != iv[32])
    {
      goto L30;
    }

  /*        ***  OLD MODEL RETAINED, SMALLER RADIUS TRIED  *** */
  /*        ***  DO NOT CONSIDER ANY MORE NEW MODELS THIS ITERATION  *** */
  iv[10] = iv[11];
  iv[8] = -1;
  goto L110;

  /*  ***  A NEW MODEL IS BEING TRIED.  DECIDE WHETHER TO KEEP IT.  *** */

L30:
  ++iv[10];

  /*     ***  NOW WE ADD THE POSSIBILITY THAT STEP WAS RECOMPUTED WITH  *** */
  /*     ***  THE SAME MODEL, PERHAPS BECAUSE OF AN OVERSIZED STEP.     *** */

L40:

  if (iv[10] > 0)
    {
      goto L50;
    }

  /*        ***  STEP WAS RECOMPUTED BECAUSE IT WAS TOO BIG.  *** */

  if (iv[2] != 0)
    {
      goto L60;
    }

  /*        ***  RESTORE IV(STAGE) AND PICK UP WHERE WE LEFT OFF.  *** */

  iv[10] = -iv[10];
  i__ = iv[13];

  switch (i__)
    {
      case 1:  goto L20;

      case 2:  goto L30;

      case 3:  goto L110;

      case 4:  goto L110;

      case 5:  goto L70;
    }

L50:

  if (iv[2] == 0)
    {
      goto L70;
    }

  /*  ***  HANDLE OVERSIZE STEP  *** */

  iv[2] = 0;

  if (iv[8] > 0)
    {
      goto L80;
    }

  iv[10] = -iv[10];
  iv[13] = iv[29];

L60:
  iv[2] = 0;
  v[16] = v[22];
  --iv[8];
  iv[29] = 5;
  iv[9] = 1;
  v[10] = v[12];
  goto L999;

L70:

  if (v[10] < v[12])
    {
      goto L110;
    }

  /*     *** THE NEW STEP IS A LOSER.  RESTORE OLD MODEL.  *** */

  if (iv[5] == iv[32])
    {
      goto L80;
    }

  iv[5] = iv[32];
  iv[12] = 1;

  /*     ***  RESTORE STEP, ETC. ONLY IF A PREVIOUS STEP DECREASED V(F). */

L80:

  if (v[12] >= v[13])
    {
      goto L110;
    }

  if (iv[10] < iv[11])
    {
      goodx = FALSE_;
    }
  else if (nfc < iv[7] + iv[11] + 2)
    {
      goodx = FALSE_;
    }
  else if (iv[12] != 0)
    {
      goodx = FALSE_;
    }

  iv[9] = 3;
  v[10] = v[12];
  v[7] = v[15];
  v[4] = v[14];

  if (iv[12] == 0)
    {
      rfac1 = v[2] / v[18];
    }

  v[2] = v[18];

  if (goodx)
    {

      /*     ***  ACCEPT PREVIOUS SLIGHTLY REDUCING STEP *** */

      v[11] = v[13] - v[10];
      iv[29] = 4;
      v[16] = rfac1;
      goto L999;
    }

  nfc = iv[7];

L110:
  v[11] = v[13] - v[10];

  if (v[11] > v[27] * v[7])
    {
      goto L140;
    }

  if (iv[8] > 0)
    {
      goto L140;
    }

  /*        ***  NO (OR ONLY A TRIVIAL) FUNCTION DECREASE */
  /*        ***  -- SO TRY NEW MODEL OR SMALLER RADIUS */

  if (v[10] < v[13])
    {
      goto L120;
    }

  iv[32] = iv[5];
  v[12] = v[10];
  v[10] = v[13];
  iv[9] = 1;
  goto L130;
L120:
  iv[7] = nfc;
L130:
  iv[29] = 1;

  if (iv[10] < iv[11])
    {
      goto L160;
    }

  iv[29] = 5;
  --iv[8];
  goto L160;

  /*  ***  NONTRIVIAL FUNCTION DECREASE ACHIEVED  *** */

L140:
  iv[7] = nfc;
  rfac1 = 1.;
  v[18] = v[2];

  if (v[11] > v[7] * v[26])
    {
      goto L190;
    }

  /*  ***  DECREASE WAS MUCH LESS THAN PREDICTED -- EITHER CHANGE MODELS */
  /*  ***  OR ACCEPT STEP WITH DECREASED RADIUS. */

  if (iv[10] >= iv[11])
    {
      goto L150;
    }

  /*        ***  CONSIDER SWITCHING MODELS  *** */
  iv[29] = 2;
  goto L160;

  /*     ***  ACCEPT STEP WITH DECREASED RADIUS  *** */

L150:
  iv[29] = 4;

  /*  ***  SET V(RADFAC) TO FLETCHER*S DECREASE FACTOR  *** */

L160:
  iv[13] = iv[29];
  emax = v[4] + v[11];
  v[16] = rfac1 * .5;

  if (emax < v[4])
    {
      /* Computing MAX */
      d__1 = v[24], d__2 = v[4] * .5 / emax;
      v[16] = rfac1 * fmax(d__1, d__2);
    }

  /*  ***  DO FALSE CONVERGENCE TEST  *** */

L170:

  if (v[17] <= v[34])
    {
      goto L180;
    }

  iv[29] = iv[13];

  if (v[10] < v[13])
    {
      goto L200;
    }

  goto L230;

L180:
  iv[29] = 12;
  goto L240;

  /*  ***  HANDLE GOOD FUNCTION DECREASE  *** */

L190:

  if (v[11] < -v[28] * v[4])
    {
      goto L210;
    }

  /*     ***  INCREASING RADIUS LOOKS WORTHWHILE.  SEE IF WE JUST */
  /*     ***  RECOMPUTED STEP WITH A DECREASED RADIUS OR RESTORED STEP */
  /*     ***  AFTER RECOMPUTING IT WITH A LARGER RADIUS. */

  if (iv[8] < 0)
    {
      goto L210;
    }

  if (iv[9] == 1)
    {
      goto L210;
    }

  if (iv[9] == 3)
    {
      goto L210;
    }

  /*        ***  WE DID NOT.  TRY A LONGER STEP UNLESS THIS WAS A NEWTON */
  /*        ***  STEP. */

  v[16] = v[25];
  gts = v[4];

  if (v[11] < (.5 / v[16] - 1.) * gts)
    {
      /* Computing MAX */
      d__1 = v[23], d__2 = gts * .5 / (gts + v[11]);
      v[16] = fmax(d__1, d__2);
    }

  iv[29] = 4;

  if (v[5] == 0.)
    {
      goto L230;
    }

  if (v[3] >= 0. && (v[3] < v[2] * 2. || v[6] < v[11] * 1.2))
    {
      goto L230;
    }

  /*             ***  STEP WAS NOT A NEWTON STEP.  RECOMPUTE IT WITH */
  /*             ***  A LARGER RADIUS. */
  iv[29] = 5;
  ++iv[8];

  /*  ***  SAVE VALUES CORRESPONDING TO GOOD STEP  *** */

L200:
  v[12] = v[10];
  iv[32] = iv[5];

  if (iv[9] == 0)
    {
      iv[9] = 2;
    }

  v[18] = v[2];
  iv[7] = nfc;
  v[15] = v[7];
  v[14] = v[4];
  goto L230;

  /*  ***  ACCEPT STEP WITH RADIUS UNCHANGED  *** */

L210:
  v[16] = 1.;
  iv[29] = 3;
  goto L230;

  /*  ***  COME HERE FOR A RESTART AFTER CONVERGENCE  *** */

L220:
  iv[29] = iv[13];

  if (v[18] >= 0.)
    {
      goto L240;
    }

  iv[29] = 12;
  goto L240;

  /*  ***  PERFORM CONVERGENCE TESTS  *** */

L230:
  iv[13] = iv[29];
L240:

  if (iv[9] == 1 && v[12] < v[13])
    {
      iv[9] = 3;
    }

  if (fabs(v[10]) < v[31])
    {
      iv[29] = 10;
    }

  if (v[11] * .5 > v[7])
    {
      goto L999;
    }

  emax = v[32] * fabs(v[13]);
  emaxs = v[37] * fabs(v[13]);

  if (v[7] <= emaxs && (v[2] > v[36] || v[5] == 0.))
    {
      iv[29] = 11;
    }

  if (v[3] < 0.)
    {
      goto L250;
    }

  i__ = 0;

  if (v[6] > 0. && v[6] <= emax || v[6] == 0. && v[7] == 0.)
    {
      i__ = 2;
    }

  if (v[5] == 0. && v[17] <= v[33] && goodx)
    {
      ++i__;
    }

  if (i__ > 0)
    {
      iv[29] = i__ + 6;
    }

  /*  ***  CONSIDER RECOMPUTING STEP OF LENGTH V(LMAXS) FOR SINGULAR */
  /*  ***  CONVERGENCE TEST. */

L250:

  if (iv[29] > 5 && iv[29] != 12)
    {
      goto L999;
    }

  if (v[5] == 0.)
    {
      goto L999;
    }

  if (v[2] > v[36])
    {
      goto L260;
    }

  if (v[7] >= emaxs)
    {
      goto L999;
    }

  if (v[3] <= 0.)
    {
      goto L270;
    }

  if (v[3] * .5 <= v[36])
    {
      goto L999;
    }

  goto L270;
L260:

  if (v[2] * .5 <= v[36])
    {
      goto L999;
    }

  xmax = v[36] / v[2];

  if (xmax * (2. - xmax) * v[7] >= emaxs)
    {
      goto L999;
    }

L270:

  if (v[6] < 0.)
    {
      goto L290;
    }

  /*  ***  RECOMPUTE V(PREDUC) FOR USE IN SINGULAR CONVERGENCE TEST  *** */

  v[14] = v[4];
  v[18] = v[2];

  if (iv[29] == 12)
    {
      v[18] = -v[18];
    }

  v[15] = v[7];
  i__ = iv[9];
  iv[9] = 2;

  if (i__ == 3)
    {
      iv[9] = 0;
    }

  iv[29] = 6;
  goto L999;

  /*  ***  PERFORM SINGULAR CONVERGENCE TEST WITH RECOMPUTED V(PREDUC)  *** */

L280:
  v[4] = v[14];
  v[2] = fabs(v[18]);
  iv[29] = iv[13];

  if (v[18] <= 0.)
    {
      iv[29] = 12;
    }

  v[6] = -v[7];
  v[7] = v[15];
  iv[9] = 3;
L290:

  if (-v[6] <= v[37] * fabs(v[13]))
    {
      iv[29] = 11;
    }

L999:
  return 0;

  /*  ***  LAST LINE OF DA7SST FOLLOWS  *** */
} /* da7sst_ */

int dd7mlp_(integer *n, doublereal *x, doublereal *y,
            doublereal *z__, integer *k)
{
  /* Initialized data */

  static doublereal one = 1.;

  /* System generated locals */
  integer i__1, i__2;

  /* Local variables */
  static integer i__, j, l;
  static doublereal t;

  /* ***  SET X = DIAG(Y)**K * Z */
  /* ***  FOR X, Z = LOWER TRIANG. MATRICES STORED COMPACTLY BY ROW */
  /* ***  K = 1 OR -1. */

  /* /6 */
  /*     DOUBLE PRECISION X(1), Y(N), Z(1) */
  /* /7 */
  /* / */
  /* Parameter adjustments */
  --y;
  --x;
  --z__;

  /* Function Body */

  l = 1;

  if (*k >= 0)
    {
      goto L30;
    }

  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      t = one / y[i__];
      i__2 = i__;

      for (j = 1; j <= i__2; ++j)
        {
          x[l] = t * z__[l];
          ++l;
          /* L10: */
        }

      /* L20: */
    }

  goto L999;

L30:
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      t = y[i__];
      i__2 = i__;

      for (j = 1; j <= i__2; ++j)
        {
          x[l] = t * z__[l];
          ++l;
          /* L40: */
        }

      /* L50: */
    }

L999:
  return 0;
  /*  ***  LAST CARD OF DD7MLP FOLLOWS  *** */
} /* dd7mlp_ */

doublereal dd7tpr_(integer *p, doublereal *x, doublereal *y)
{
  /* Initialized data */

  static doublereal sqteta = 0.;

  /* System generated locals */
  integer i__1;
  doublereal ret_val, d__1, d__2, d__3, d__4;

  /* Local variables */
  static integer i__;
  static doublereal t;
  extern doublereal dr7mdc_(integer *);

  /*  ***  RETURN THE INNER PRODUCT OF THE P-VECTORS X AND Y.  *** */

  /*  ***  DR7MDC(2) RETURNS A MACHINE-DEPENDENT CONSTANT, SQTETA, WHICH */
  /*  ***  IS SLIGHTLY LARGER THAN THE SMALLEST POSITIVE NUMBER THAT */
  /*  ***  CAN BE SQUARED WITHOUT UNDERFLOWING. */

  /* /6 */
  /*     DATA ONE/1.D+0/, SQTETA/0.D+0/, ZERO/0.D+0/ */
  /* /7 */
  /* Parameter adjustments */
  --y;
  --x;

  /* Function Body */
  /* / */

  ret_val = 0.;

  if (*p <= 0)
    {
      goto L999;
    }

  if (sqteta == 0.)
    {
      sqteta = dr7mdc_(&c__2);
    }

  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* Computing MAX */
      d__3 = (d__1 = x[i__], fabs(d__1)), d__4 = (d__2 = y[i__], fabs(d__2));
      t = fmax(d__3, d__4);

      if (t > 1.)
        {
          goto L10;
        }

      if (t < sqteta)
        {
          goto L20;
        }

      t = x[i__] / sqteta * y[i__];

      if (fabs(t) < sqteta)
        {
          goto L20;
        }

L10:
      ret_val += x[i__] * y[i__];
L20:
      ;
    }

L999:
  return ret_val;
  /*  ***  LAST LINE OF DD7TPR FOLLOWS  *** */
} /* dd7tpr_ */

int dd7upd_(doublereal *d__, doublereal *dr, integer *iv,
            integer *liv, integer *lv, integer *n, integer *nd, integer *nn,
            integer *n2, integer *p, doublereal *v)
{
  /* System generated locals */
  integer dr_dim1, dr_offset, i__1, i__2;
  doublereal d__1, d__2, d__3;

  /* Local variables */
  static integer jcni, jtol0, i__, k;
  static doublereal vdfac, t;
  static integer jtoli, d0;
  extern int dv7scp_(integer *, doublereal *, doublereal *)
  ;
  static integer sii, jcn0, jcn1;

  /*  ***  UPDATE SCALE VECTOR D FOR NL2IT  *** */

  /*  ***  PARAMETER DECLARATIONS  *** */

  /*     DIMENSION V(*) */

  /*  ***  LOCAL VARIABLES  *** */

  /*     ***  CONSTANTS  *** */

  /*  ***  INTRINSIC FUNCTIONS  *** */
  /* /+ */
  /* / */
  /*  ***  EXTERNAL SUBROUTINE  *** */

  /* DV7SCP... SETS ALL COMPONENTS OF A VECTOR TO A SCALAR. */

  /*  ***  SUBSCRIPTS FOR IV AND V  *** */

  /* /6 */
  /*     DATA DFAC/41/, DTYPE/16/, JCN/66/, JTOL/59/, NITER/31/, S/62/ */
  /* /7 */
  /* / */

  /* /6 */
  /*     DATA ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /* -------------------------------  BODY  -------------------------------- */

  /* Parameter adjustments */
  --iv;
  --v;
  dr_dim1 = *nd;
  dr_offset = dr_dim1 + 1;
  dr -= dr_offset;
  --d__;

  /* Function Body */
  if (iv[16] != 1 && iv[31] > 0)
    {
      goto L999;
    }

  jcn1 = iv[66];
  jcn0 = abs(jcn1) - 1;

  if (jcn1 < 0)
    {
      goto L10;
    }

  iv[66] = -jcn1;
  dv7scp_(p, &v[jcn1], &c_b78);
L10:
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      jcni = jcn0 + i__;
      t = v[jcni];
      i__2 = *nn;

      for (k = 1; k <= i__2; ++k)
        {
          /* L20: */
          /* Computing MAX */
          d__2 = t, d__3 = (d__1 = dr[k + i__ * dr_dim1], fabs(d__1));
          t = fmax(d__2, d__3);
        }

      v[jcni] = t;
      /* L30: */
    }

  if (*n2 < *n)
    {
      goto L999;
    }

  vdfac = v[41];
  jtol0 = iv[59] - 1;
  d0 = jtol0 + *p;
  sii = iv[62] - 1;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sii += i__;
      jcni = jcn0 + i__;
      t = v[jcni];

      if (v[sii] > 0.)
        {
          /* Computing MAX */
          d__1 = sqrt(v[sii]);
          t = fmax(d__1, t);
        }

      jtoli = jtol0 + i__;
      ++d0;

      if (t < v[jtoli])
        {
          /* Computing MAX */
          d__1 = v[d0], d__2 = v[jtoli];
          t = fmax(d__1, d__2);
        }

      /* Computing MAX */
      d__1 = vdfac * d__[i__];
      d__[i__] = fmax(d__1, t);
      /* L50: */
    }

L999:
  return 0;
  /*  ***  LAST CARD OF DD7UPD FOLLOWS  *** */
} /* dd7upd_ */

int df7dhb_(doublereal *b, doublereal *d__, doublereal *g,
            integer *irt, integer *iv, integer *liv, integer *lv, integer *p,
            doublereal *v, doublereal *x)
{
  /* System generated locals */
  integer i__1;
  doublereal d__1, d__2, d__3;

  /* Local variables */
  static integer kind, mm1o2, pp1o2, stpi, stpm, newm1, i__, k, l, m;
  static doublereal t;
  static integer gsave1;
  extern int dv7scp_(integer *, doublereal *, doublereal *),
         dv7cpy_(integer *, doublereal *, doublereal *);
  static doublereal xm;
  static logical offsid;
  static integer mm1;
  static doublereal xm1, del;
  static integer hmi, hes, hpi, hpm;
  static doublereal del0;
  static integer stp0;

  /*  ***  COMPUTE FINITE-DIFFERENCE HESSIAN, STORE IT IN V STARTING */
  /*  ***  AT V(IV(FDH)) = V(-IV(H)).  HONOR SIMPLE BOUNDS IN B. */

  /*  ***  IF IV(COVREQ) .GE. 0 THEN DF7DHB USES GRADIENT DIFFERENCES, */
  /*  ***  OTHERWISE FUNCTION DIFFERENCES.  STORAGE IN V IS AS IN DG7LIT. */

  /* IRT VALUES... */
  /*     1 = COMPUTE FUNCTION VALUE, I.E., V(F). */
  /*     2 = COMPUTE G. */
  /*     3 = DONE. */

  /*  ***  PARAMETER DECLARATIONS  *** */

  /*  ***  LOCAL VARIABLES  *** */

  /*  ***  EXTERNAL SUBROUTINES  *** */

  /* DV7CPY.... COPY ONE VECTOR TO ANOTHER. */
  /* DV7SCP... COPY SCALAR TO ALL COMPONENTS OF A VECTOR. */

  /*  ***  SUBSCRIPTS FOR IV AND V  *** */

  /* /6 */
  /*     DATA HALF/0.5D+0/, HLIM/0.1D+0/, ONE/1.D+0/, TWO/2.D+0/, */
  /*    1     ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /* /6 */
  /*     DATA COVREQ/15/, DELTA/52/, DELTA0/44/, DLTFDC/42/, F/10/, */
  /*    1     FDH/74/, FX/53/, H/56/, KAGQT/33/, MODE/35/, NFGCAL/7/, */
  /*    2     SAVEI/63/, SWITCH/12/, TOOBIG/2/, W/65/, XMSAVE/51/ */
  /* /7 */
  /* / */

  /* +++++++++++++++++++++++++++++++  BODY  ++++++++++++++++++++++++++++++++ */

  /* Parameter adjustments */
  --iv;
  --v;
  --x;
  --g;
  --d__;
  b -= 3;

  /* Function Body */
  *irt = 4;
  kind = iv[15];
  m = iv[35];

  if (m > 0)
    {
      goto L10;
    }

  hes = abs(iv[56]);
  iv[56] = -hes;
  iv[74] = 0;
  iv[33] = -1;
  v[53] = v[10];
  /*        *** SUPPLY ZEROS IN CASE B(1,I) = B(2,I) FOR SOME I *** */
  i__1 = *p * (*p + 1) / 2;
  dv7scp_(&i__1, &v[hes], &c_b78);
L10:

  if (m > *p)
    {
      goto L999;
    }

  if (kind < 0)
    {
      goto L120;
    }

  /*  ***  COMPUTE FINITE-DIFFERENCE HESSIAN USING BOTH FUNCTION AND */
  /*  ***  GRADIENT VALUES. */

  gsave1 = iv[65] + *p;

  if (m > 0)
    {
      goto L20;
    }

  /*        ***  FIRST CALL ON DF7DHB.  SET GSAVE = G, TAKE FIRST STEP  *** */
  dv7cpy_(p, &v[gsave1], &g[1]);
  iv[12] = iv[7];
  goto L80;

L20:
  del = v[52];
  x[m] = v[51];

  if (iv[2] == 0)
    {
      goto L30;
    }

  /*     ***  HANDLE OVERSIZE V(DELTA)  *** */

  /* Computing MAX */
  d__2 = 1. / d__[m], d__3 = (d__1 = x[m], fabs(d__1));
  del0 = v[44] * fmax(d__2, d__3);
  del *= .5;

  if ((d__1 = del / del0, fabs(d__1)) <= .1)
    {
      goto L140;
    }

L30:
  hes = -iv[56];

  /*  ***  SET  G = (G - GSAVE)/DEL  *** */

  del = 1. / del;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      g[i__] = del * (g[i__] - v[gsave1]);
      ++gsave1;
      /* L40: */
    }

  /*  ***  ADD G AS NEW COL. TO FINITE-DIFF. HESSIAN MATRIX  *** */

  k = hes + m * (m - 1) / 2;
  l = k + m - 2;

  if (m == 1)
    {
      goto L60;
    }

  /*  ***  SET  H(I,M) = 0.5 * (H(I,M) + G(I))  FOR I = 1 TO M-1  *** */

  mm1 = m - 1;
  i__1 = mm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      if (b[(i__ << 1) + 1] < b[(i__ << 1) + 2])
        {
          v[k] = (v[k] + g[i__]) * .5;
        }

      ++k;
      /* L50: */
    }

  /*  ***  ADD  H(I,M) = G(I)  FOR I = M TO P  *** */

L60:
  ++l;
  i__1 = *p;

  for (i__ = m; i__ <= i__1; ++i__)
    {
      if (b[(i__ << 1) + 1] < b[(i__ << 1) + 2])
        {
          v[l] = g[i__];
        }

      l += i__;
      /* L70: */
    }

L80:
  ++m;
  iv[35] = m;

  if (m > *p)
    {
      goto L340;
    }

  if (b[(m << 1) + 1] >= b[(m << 1) + 2])
    {
      goto L80;
    }

  /*  ***  CHOOSE NEXT FINITE-DIFFERENCE STEP, RETURN TO GET G THERE  *** */

  /* Computing MAX */
  d__2 = 1. / d__[m], d__3 = (d__1 = x[m], fabs(d__1));
  del = v[44] * fmax(d__2, d__3);
  xm = x[m];

  if (xm < 0.)
    {
      goto L90;
    }

  xm1 = xm + del;

  if (xm1 <= b[(m << 1) + 2])
    {
      goto L110;
    }

  xm1 = xm - del;

  if (xm1 >= b[(m << 1) + 1])
    {
      goto L100;
    }

  goto L280;
L90:
  xm1 = xm - del;

  if (xm1 >= b[(m << 1) + 1])
    {
      goto L100;
    }

  xm1 = xm + del;

  if (xm1 <= b[(m << 1) + 2])
    {
      goto L110;
    }

  goto L280;

L100:
  del = -del;
L110:
  v[51] = xm;
  x[m] = xm1;
  v[52] = del;
  *irt = 2;
  goto L999;

  /*  ***  COMPUTE FINITE-DIFFERENCE HESSIAN USING FUNCTION VALUES ONLY. */

L120:
  stp0 = iv[65] + *p - 1;
  mm1 = m - 1;
  mm1o2 = m * mm1 / 2;
  hes = -iv[56];

  if (m > 0)
    {
      goto L130;
    }

  /*        ***  FIRST CALL ON DF7DHB.  *** */
  iv[63] = 0;
  goto L240;

L130:

  if (iv[2] == 0)
    {
      goto L150;
    }

  /*        ***  PUNT IN THE EVENT OF AN OVERSIZE STEP  *** */
L140:
  iv[74] = -2;
  goto L350;
L150:
  i__ = iv[63];

  if (i__ > 0)
    {
      goto L190;
    }

  /*  ***  SAVE F(X + STP(M)*E(M)) IN H(P,M)  *** */

  pp1o2 = *p * (*p - 1) / 2;
  hpm = hes + pp1o2 + mm1;
  v[hpm] = v[10];

  /*  ***  START COMPUTING ROW M OF THE FINITE-DIFFERENCE HESSIAN H.  *** */

  newm1 = 1;
  goto L260;
L160:
  hmi = hes + mm1o2;

  if (mm1 == 0)
    {
      goto L180;
    }

  hpi = hes + pp1o2;
  i__1 = mm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      t = 0.;

      if (b[(i__ << 1) + 1] < b[(i__ << 1) + 2])
        {
          t = v[53] - (v[10] + v[hpi]);
        }

      v[hmi] = t;
      ++hmi;
      ++hpi;
      /* L170: */
    }

L180:
  v[hmi] = v[10] - v[53] * 2.;

  if (offsid)
    {
      v[hmi] = v[53] - v[10] * 2.;
    }

  /*  ***  COMPUTE FUNCTION VALUES NEEDED TO COMPLETE ROW M OF H.  *** */

  i__ = 0;
  goto L200;

L190:
  x[i__] = v[52];

  /*  ***  FINISH COMPUTING H(M,I)  *** */

  stpi = stp0 + i__;
  hmi = hes + mm1o2 + i__ - 1;
  stpm = stp0 + m;
  v[hmi] = (v[hmi] + v[10]) / (v[stpi] * v[stpm]);
L200:
  ++i__;

  if (i__ > m)
    {
      goto L230;
    }

  if (b[(i__ << 1) + 1] < b[(i__ << 1) + 2])
    {
      goto L210;
    }

  goto L200;

L210:
  iv[63] = i__;
  stpi = stp0 + i__;
  v[52] = x[i__];
  x[i__] += v[stpi];
  *irt = 1;

  if (i__ < m)
    {
      goto L999;
    }

  newm1 = 2;
  goto L260;
L220:
  x[m] = v[51] - del;

  if (offsid)
    {
      x[m] = v[51] + del * 2.;
    }

  goto L999;

L230:
  iv[63] = 0;
  x[m] = v[51];

L240:
  ++m;
  iv[35] = m;

  if (m > *p)
    {
      goto L330;
    }

  if (b[(m << 1) + 1] < b[(m << 1) + 2])
    {
      goto L250;
    }

  goto L240;

  /*  ***  PREPARE TO COMPUTE ROW M OF THE FINITE-DIFFERENCE HESSIAN H. */
  /*  ***  COMPUTE M-TH STEP SIZE STP(M), THEN RETURN TO OBTAIN */
  /*  ***  F(X + STP(M)*E(M)), WHERE E(M) = M-TH STD. UNIT VECTOR. */

L250:
  v[51] = x[m];
  newm1 = 3;
L260:
  xm = v[51];
  /* Computing MAX */
  d__1 = 1. / d__[m], d__2 = fabs(xm);
  del = v[42] * fmax(d__1, d__2);
  xm1 = xm + del;
  offsid = FALSE_;

  if (xm1 <= b[(m << 1) + 2])
    {
      goto L270;
    }

  offsid = TRUE_;
  xm1 = xm - del;

  if (xm - del * 2. >= b[(m << 1) + 1])
    {
      goto L300;
    }

  goto L280;
L270:

  if (xm - del >= b[(m << 1) + 1])
    {
      goto L290;
    }

  offsid = TRUE_;

  if (xm + del * 2. <= b[(m << 1) + 2])
    {
      goto L310;
    }

L280:
  iv[74] = -2;
  goto L350;

L290:

  if (xm >= 0.)
    {
      goto L310;
    }

  xm1 = xm - del;
L300:
  del = -del;
L310:

  switch (newm1)
    {
      case 1:  goto L160;

      case 2:  goto L220;

      case 3:  goto L320;
    }

L320:
  x[m] = xm1;
  stpm = stp0 + m;
  v[stpm] = del;
  *irt = 1;
  goto L999;

  /*  ***  HANDLE SPECIAL CASE OF B(1,P) = B(2,P) -- CLEAR SCRATCH VALUES */
  /*  ***  FROM LAST ROW OF FDH... */

L330:

  if (b[(*p << 1) + 1] < b[(*p << 1) + 2])
    {
      goto L340;
    }

  i__ = hes + *p * (*p - 1) / 2;
  dv7scp_(p, &v[i__], &c_b78);

  /*  ***  RESTORE V(F), ETC.  *** */

L340:
  iv[74] = hes;
L350:
  v[10] = v[53];
  *irt = 3;

  if (kind < 0)
    {
      goto L999;
    }

  iv[7] = iv[12];
  gsave1 = iv[65] + *p;
  dv7cpy_(p, &g[1], &v[gsave1]);
  goto L999;

L999:
  return 0;
  /*  ***  LAST LINE OF DF7DHB FOLLOWS  *** */
} /* df7dhb_ */

int dg7itb_(doublereal *b, doublereal *d__, doublereal *g,
            integer *iv, integer *liv, integer *lv, integer *p, integer *ps,
            doublereal *v, doublereal *x, doublereal *y)
{
  /* System generated locals */
  integer i__1, i__2;
  doublereal d__1;

  /* Local variables */
  static integer pp1o2, lmat1, p1len, rmat1, temp1, ipiv0, ipiv1, ipiv2,
         temp2, step1;
  static doublereal e;
  static integer i__, j, k, l;
  static doublereal t;
  static logical havrm;
  static integer h1, i1, dummy;
  extern int df7dhb_(doublereal *, doublereal *,
                     doublereal *, integer *, integer *, integer *, integer *, integer
                     *, doublereal *, doublereal *);
  static integer p1, s1;
  static doublereal t1;
  static integer w1;
  extern logical stopx_(integer *);
  extern int dg7qsb_(doublereal *, doublereal *,
                     doublereal *, doublereal *, integer *, integer *, integer *,
                     integer *, doublereal *, integer *, integer *, integer *, integer
                     *, doublereal *, doublereal *, doublereal *, doublereal *,
                     doublereal *, doublereal *, doublereal *), dl7msb_(doublereal *,
                         doublereal *, doublereal *, integer *, integer *, integer *,
                         integer *, integer *, doublereal *, integer *, integer *, integer
                         *, integer *, doublereal *, doublereal *, doublereal *,
                         doublereal *, doublereal *, doublereal *, doublereal *,
                         doublereal *, doublereal *, doublereal *), ds7dmp_(integer *,
                             doublereal *, doublereal *, doublereal *, integer *);
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *);
  extern int da7sst_(integer *, integer *, integer *,
                     doublereal *), i7shft_(integer *, integer *, integer *), dl7vml_(
                       integer *, doublereal *, doublereal *, doublereal *);
  static integer g01;
  extern doublereal dv2nrm_(integer *, doublereal *);
  extern int i7copy_(integer *, integer *, integer *),
         dq7rsh_(integer *, integer *, logical *, doublereal *, doublereal
                 *, doublereal *), dl7sqr_(integer *, doublereal *, doublereal *),
         dl7tvm_(integer *, doublereal *, doublereal *, doublereal *),
         ds7ipr_(integer *, integer *, doublereal *), ds7lup_(doublereal *,
             doublereal *, integer *, doublereal *, doublereal *, doublereal *
             , doublereal *, doublereal *, doublereal *, doublereal *);
  static doublereal gi;
  extern int ds7lvm_(integer *, doublereal *, doublereal *,
                     doublereal *), dv2axy_(integer *, doublereal *, doublereal *,
                         doublereal *, doublereal *), dv7cpy_(integer *, doublereal *,
                             doublereal *), dv7ipr_(integer *, integer *, doublereal *),
                                        i7pnvr_(integer *, integer *, integer *), dv7scp_(integer *,
                                            doublereal *, doublereal *), dv7vmp_(integer *, doublereal *,
                                                doublereal *, doublereal *, integer *);
  static integer x01;
  static doublereal xi;
  extern int dparck_(integer *, doublereal *, integer *,
                     integer *, integer *, integer *, doublereal *);
  static integer hc1;
  extern doublereal drldst_(integer *, doublereal *, doublereal *,
                            doublereal *);
  static logical havqtr;
  static integer stpmod;
  static integer td1, tg1, lstgst, pp1, rstrst;
  static doublereal sttsst;
  static integer ipi, ipn, dig1, wlm1, qtr1;

  /*  ***  CARRY OUT NL2SOL-LIKE ITERATIONS FOR GENERALIZED LINEAR   *** */
  /*  ***  REGRESSION PROBLEMS (AND OTHERS OF SIMILAR STRUCTURE)     *** */
  /*  ***  HAVING SIMPLE BOUNDS ON THE PARAMETERS BEING ESTIMATED.   *** */

  /*  ***  PARAMETER DECLARATIONS  *** */

  /* --------------------------  PARAMETER USAGE  -------------------------- */

  /* B.... VECTOR OF LOWER AND UPPER BOUNDS ON X. */
  /* D.... SCALE VECTOR. */
  /* IV... INTEGER VALUE ARRAY. */
  /* LIV.. LENGTH OF IV.  MUST BE AT LEAST 80. */
  /* LH... LENGTH OF H = P*(P+1)/2. */
  /* LV... LENGTH OF V.  MUST BE AT LEAST P*(3*P + 19)/2 + 7. */
  /* G.... GRADIENT AT X (WHEN IV(1) = 2). */
  /* HC... GAUSS-NEWTON HESSIAN AT X (WHEN IV(1) = 2). */
  /* P.... NUMBER OF PARAMETERS (COMPONENTS IN X). */
  /* PS... NUMBER OF NONZERO ROWS AND COLUMNS IN S. */
  /* V.... FLOATING-POINT VALUE ARRAY. */
  /* X.... PARAMETER VECTOR. */
  /* Y.... PART OF YIELD VECTOR (WHEN IV(1)= 2, SCRATCH OTHERWISE). */

  /*  ***  DISCUSSION  *** */

  /*        DG7ITB IS SIMILAR TO DG7LIT, EXCEPT FOR THE EXTRA PARAMETER B */
  /*     -- DG7ITB ENFORCES THE BOUNDS  B(1,I) .LE. X(I) .LE. B(2,I), */
  /*     I = 1(1)P. */
  /*        DG7ITB PERFORMS NL2SOL-LIKE ITERATIONS FOR A VARIETY OF */
  /*     REGRESSION PROBLEMS THAT ARE SIMILAR TO NONLINEAR LEAST-SQUARES */
  /*     IN THAT THE HESSIAN IS THE SUM OF TWO TERMS, A READILY-COMPUTED */
  /*     FIRST-ORDER TERM AND A SECOND-ORDER TERM.  THE CALLER SUPPLIES */
  /*     THE FIRST-ORDER TERM OF THE HESSIAN IN HC (LOWER TRIANGLE, STORED */
  /*     COMPACTLY BY ROWS), AND DG7ITB BUILDS AN APPROXIMATION, S, TO THE */
  /*     SECOND-ORDER TERM.  THE CALLER ALSO PROVIDES THE FUNCTION VALUE, */
  /*     GRADIENT, AND PART OF THE YIELD VECTOR USED IN UPDATING S. */
  /*     DG7ITB DECIDES DYNAMICALLY WHETHER OR NOT TO USE S WHEN CHOOSING */
  /*     THE NEXT STEP TO TRY...  THE HESSIAN APPROXIMATION USED IS EITHER */
  /*     HC ALONE (GAUSS-NEWTON MODEL) OR HC + S (AUGMENTED MODEL). */
  /*     IF PS .LT. P, THEN ROWS AND COLUMNS PS+1...P OF S ARE KEPT */
  /*     CONSTANT.  THEY WILL BE ZERO UNLESS THE CALLER SETS IV(INITS) TO */
  /*     1 OR 2 AND SUPPLIES NONZERO VALUES FOR THEM, OR THE CALLER SETS */
  /*     IV(INITS) TO 3 OR 4 AND THE FINITE-DIFFERENCE INITIAL S THEN */
  /*     COMPUTED HAS NONZERO VALUES IN THESE ROWS. */

  /*        IF IV(INITS) IS 3 OR 4, THEN THE INITIAL S IS COMPUTED BY */
  /*     FINITE DIFFERENCES.  3 MEANS USE FUNCTION DIFFERENCES, 4 MEANS */
  /*     USE GRADIENT DIFFERENCES.  FINITE DIFFERENCING IS DONE THE SAME */
  /*     WAY AS IN COMPUTING A COVARIANCE MATRIX (WITH IV(COVREQ) = -1, -2, */
  /*     1, OR 2). */

  /*        FOR UPDATING S, DG7ITB ASSUMES THAT THE GRADIENT HAS THE FORM */
  /*     OF A SUM OVER I OF RHO(I,X)*GRAD(R(I,X)), WHERE GRAD DENOTES THE */
  /*     GRADIENT WITH RESPECT TO X.  THE TRUE SECOND-ORDER TERM THEN IS */
  /*     THE SUM OVER I OF RHO(I,X)*HESSIAN(R(I,X)).  IF X = X0 + STEP, */
  /*     THEN WE WISH TO UPDATE S SO THAT S*STEP IS THE SUM OVER I OF */
  /*     RHO(I,X)*(GRAD(R(I,X)) - GRAD(R(I,X0))).  THE CALLER MUST SUPPLY */
  /*     PART OF THIS IN Y, NAMELY THE SUM OVER I OF */
  /*     RHO(I,X)*GRAD(R(I,X0)), WHEN CALLING DG7ITB WITH IV(1) = 2 AND */
  /*     IV(MODE) = 0 (WHERE MODE = 38).  G THEN CONTANS THE OTHER PART, */
  /*     SO THAT THE DESIRED YIELD VECTOR IS G - Y.  IF PS .LT. P, THEN */
  /*     THE ABOVE DISCUSSION APPLIES ONLY TO THE FIRST PS COMPONENTS OF */
  /*     GRAD(R(I,X)), STEP, AND Y. */

  /*        PARAMETERS IV, P, V, AND X ARE THE SAME AS THE CORRESPONDING */
  /*     ONES TO  DN2GB (AND NL2SOL), EXCEPT THAT V CAN BE SHORTER */
  /*     (SINCE THE PART OF V THAT  DN2GB USES FOR STORING D, J, AND R IS */
  /*     NOT NEEDED).  MOREOVER, COMPARED WITH  DN2GB (AND NL2SOL), IV(1) */
  /*     MAY HAVE THE TWO ADDITIONAL OUTPUT VALUES 1 AND 2, WHICH ARE */
  /*     EXPLAINED BELOW, AS IS THE USE OF IV(TOOBIG) AND IV(NFGCAL). */
  /*     THE VALUES IV(D), IV(J), AND IV(R), WHICH ARE OUTPUT VALUES FROM */
  /*      DN2GB (AND  DN2FB), ARE NOT REFERENCED BY DG7ITB OR THE */
  /*     SUBROUTINES IT CALLS. */

  /*        WHEN DG7ITB IS FIRST CALLED, I.E., WHEN DG7ITB IS CALLED WITH */
  /*     IV(1) = 0 OR 12, V(F), G, AND HC NEED NOT BE INITIALIZED.  TO */
  /*     OBTAIN THESE STARTING VALUES, DG7ITB RETURNS FIRST WITH IV(1) = 1, */
  /*     THEN WITH IV(1) = 2, WITH IV(MODE) = -1 IN BOTH CASES.  ON */
  /*     SUBSEQUENT RETURNS WITH IV(1) = 2, IV(MODE) = 0 IMPLIES THAT */
  /*     Y MUST ALSO BE SUPPLIED.  (NOTE THAT Y IS USED FOR SCRATCH -- ITS */
  /*     INPUT CONTENTS ARE LOST.  BY CONTRAST, HC IS NEVER CHANGED.) */
  /*     ONCE CONVERGENCE HAS BEEN OBTAINED, IV(RDREQ) AND IV(COVREQ) MAY */
  /*     IMPLY THAT A FINITE-DIFFERENCE HESSIAN SHOULD BE COMPUTED FOR USE */
  /*     IN COMPUTING A COVARIANCE MATRIX.  IN THIS CASE DG7ITB WILL MAKE */
  /*     A NUMBER OF RETURNS WITH IV(1) = 1 OR 2 AND IV(MODE) POSITIVE. */
  /*     WHEN IV(MODE) IS POSITIVE, Y SHOULD NOT BE CHANGED. */

  /* IV(1) = 1 MEANS THE CALLER SHOULD SET V(F) (I.E., V(10)) TO F(X), THE */
  /*             FUNCTION VALUE AT X, AND CALL DG7ITB AGAIN, HAVING CHANGED */
  /*             NONE OF THE OTHER PARAMETERS.  AN EXCEPTION OCCURS IF F(X) */
  /*             CANNOT BE EVALUATED (E.G. IF OVERFLOW WOULD OCCUR), WHICH */
  /*             MAY HAPPEN BECAUSE OF AN OVERSIZED STEP.  IN THIS CASE */
  /*             THE CALLER SHOULD SET IV(TOOBIG) = IV(2) TO 1, WHICH WILL */
  /*             CAUSE DG7ITB TO IGNORE V(F) AND TRY A SMALLER STEP.  NOTE */
  /*             THAT THE CURRENT FUNCTION EVALUATION COUNT IS AVAILABLE */
  /*             IN IV(NFCALL) = IV(6).  THIS MAY BE USED TO IDENTIFY */
  /*             WHICH COPY OF SAVED INFORMATION SHOULD BE USED IN COM- */
  /*             PUTING G, HC, AND Y THE NEXT TIME DG7ITB RETURNS WITH */
  /*             IV(1) = 2.  SEE MLPIT FOR AN EXAMPLE OF THIS. */
  /* IV(1) = 2 MEANS THE CALLER SHOULD SET G TO G(X), THE GRADIENT OF F AT */
  /*             X.  THE CALLER SHOULD ALSO SET HC TO THE GAUSS-NEWTON */
  /*             HESSIAN AT X.  IF IV(MODE) = 0, THEN THE CALLER SHOULD */
  /*             ALSO COMPUTE THE PART OF THE YIELD VECTOR DESCRIBED ABOVE. */
  /*             THE CALLER SHOULD THEN CALL DG7ITB AGAIN (WITH IV(1) = 2). */
  /*             THE CALLER MAY ALSO CHANGE D AT THIS TIME, BUT SHOULD NOT */
  /*             CHANGE X.  NOTE THAT IV(NFGCAL) = IV(7) CONTAINS THE */
  /*             VALUE THAT IV(NFCALL) HAD DURING THE RETURN WITH */
  /*             IV(1) = 1 IN WHICH X HAD THE SAME VALUE AS IT NOW HAS. */
  /*             IV(NFGCAL) IS EITHER IV(NFCALL) OR IV(NFCALL) - 1.  MLPIT */
  /*             IS AN EXAMPLE WHERE THIS INFORMATION IS USED.  IF G OR HC */
  /*             CANNOT BE EVALUATED AT X, THEN THE CALLER MAY SET */
  /*             IV(NFGCAL) TO 0, IN WHICH CASE DG7ITB WILL RETURN WITH */
  /*             IV(1) = 15. */

  /*  ***  GENERAL  *** */

  /*     CODED BY DAVID M. GAY. */

  /*        (SEE NL2SOL FOR REFERENCES.) */

  /* +++++++++++++++++++++++++++  DECLARATIONS  ++++++++++++++++++++++++++++ */

  /*  ***  LOCAL VARIABLES  *** */

  /*     ***  CONSTANTS  *** */

  /*  ***  EXTERNAL FUNCTIONS AND SUBROUTINES  *** */

  /* DA7SST.... ASSESSES CANDIDATE STEP. */
  /* DD7TPR... RETURNS INNER PRODUCT OF TWO VECTORS. */
  /* DF7DHB... COMPUTE FINITE-DIFFERENCE HESSIAN (FOR INIT. S MATRIX). */
  /* DG7QSB... COMPUTES GOLDFELD-QUANDT-TROTTER STEP (AUGMENTED MODEL). */
  /* I7COPY.... COPIES ONE INTEGER VECTOR TO ANOTHER. */
  /* I7PNVR... INVERTS PERMUTATION ARRAY. */
  /* I7SHFT... SHIFTS AN INTEGER VECTOR. */
  /* DITSUM.... PRINTS ITERATION SUMMARY AND INFO ON INITIAL AND FINAL X. */
  /* DL7MSB... COMPUTES LEVENBERG-MARQUARDT STEP (GAUSS-NEWTON MODEL). */
  /* DL7SQR... COMPUTES L * L**T FROM LOWER TRIANGULAR MATRIX L. */
  /* DL7TVM... COMPUTES L**T * V, V = VECTOR, L = LOWER TRIANGULAR MATRIX. */
  /* DL7VML.... COMPUTES L * V, V = VECTOR, L = LOWER TRIANGULAR MATRIX. */
  /* DPARCK.... CHECK VALIDITY OF IV AND V INPUT COMPONENTS. */
  /* DQ7RSH... SHIFTS A QR FACTORIZATION. */
  /* DRLDST... COMPUTES V(RELDX) = RELATIVE STEP SIZE. */
  /* DS7DMP... MULTIPLIES A SYM. MATRIX FORE AND AFT BY A DIAG. MATRIX. */
  /* DS7IPR... APPLIES PERMUTATION TO (LOWER TRIANG. OF) SYM. MATRIX. */
  /* DS7LUP... PERFORMS QUASI-NEWTON UPDATE ON COMPACTLY STORED LOWER TRI- */
  /*             ANGLE OF A SYMMETRIC MATRIX. */
  /* DS7LVM... MULTIPLIES COMPACTLY STORED SYM. MATRIX TIMES VECTOR. */
  /* STOPX.... RETURNS .TRUE. IF THE BREAK KEY HAS BEEN PRESSED. */
  /* DV2NRM... RETURNS THE 2-NORM OF A VECTOR. */
  /* DV2AXY.... COMPUTES SCALAR TIMES ONE VECTOR PLUS ANOTHER. */
  /* DV7CPY.... COPIES ONE VECTOR TO ANOTHER. */
  /* DV7IPR... APPLIES A PERMUTATION TO A VECTOR. */
  /* DV7SCP... SETS ALL ELEMENTS OF A VECTOR TO A SCALAR. */
  /* DV7VMP... MULTIPLIES (DIVIDES) VECTORS COMPONENTWISE. */

  /*  ***  SUBSCRIPTS FOR IV AND V  *** */

  /*  ***  IV SUBSCRIPT VALUES  *** */

  /*  ***  (NOTE THAT P0 AND PC ARE STORED IN IV(G0) AND IV(STLSTG) RESP.) */

  /* /6 */
  /*     DATA CNVCOD/55/, COVMAT/26/, COVREQ/15/, DIG/37/, FDH/74/, H/56/,
   */
  /*    1     HC/71/, IERR/75/, INITS/25/, IPIVOT/76/, IRC/29/, IVNEED/3/,
   */
  /*    2     KAGQT/33/, KALM/34/, LMAT/42/, MODE/35/, MODEL/5/, */
  /*    3     MXFCAL/17/, MXITER/18/, NEXTIV/46/, NEXTV/47/, NFCALL/6/, */
  /*    4     NFGCAL/7/, NFCOV/52/, NGCOV/53/, NGCALL/30/, NITER/31/, */
  /*    5     P0/48/, PC/41/, PERM/58/, QTR/77/, RADINC/8/, RDREQ/57/, */
  /*    6     REGD/67/, RESTOR/9/, RMAT/78/, S/62/, STEP/40/, STGLIM/11/, */
  /*    7     SUSED/64/, SWITCH/12/, TOOBIG/2/, VNEED/4/, VSAVE/60/, W/65/, */
  /*    8     XIRC/13/, X0/43/ */
  /* /7 */
  /* / */

  /*  ***  V SUBSCRIPT VALUES  *** */

  /* /6 */
  /*     DATA COSMIN/47/, DGNORM/1/, DSTNRM/2/, F/10/, FDIF/11/, FUZZ/45/, */
  /*    1     F0/13/, GTSTEP/4/, INCFAC/23/, LMAX0/35/, LMAXS/36/, */
  /*    2     NVSAVE/9/, PHMXFC/21/, PREDUC/7/, RADFAC/16/, RADIUS/8/, */
  /*    3     RAD0/9/, RELDX/17/, SIZE/55/, STPPAR/5/, TUNER4/29/, */
  /*    4     TUNER5/30/, WSCALE/56/ */
  /* /7 */
  /* / */

  /* /6 */
  /*     DATA HALF/0.5D+0/, NEGONE/-1.D+0/, ONE/1.D+0/, ONEP2/1.2D+0/, */
  /*    1     ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /* +++++++++++++++++++++++++++++++  BODY  ++++++++++++++++++++++++++++++++ */

  /* Parameter adjustments */
  --iv;
  --v;
  --y;
  --x;
  --g;
  --d__;
  b -= 3;

  /* Function Body */
  i__ = iv[1];

  if (i__ == 1)
    {
      goto L50;
    }

  if (i__ == 2)
    {
      goto L60;
    }

  if (i__ < 12)
    {
      goto L10;
    }

  if (i__ > 13)
    {
      goto L10;
    }

  iv[4] = iv[4] + *p * (*p * 3 + 25) / 2 + 7;
  iv[3] += *p << 2;
L10:
  dparck_(&c__1, &d__[1], &iv[1], liv, lv, p, &v[1]);
  i__ = iv[1] - 2;

  if (i__ > 12)
    {
      goto L999;
    }

  switch (i__)
    {
      case 1:  goto L360;

      case 2:  goto L360;

      case 3:  goto L360;

      case 4:  goto L360;

      case 5:  goto L360;

      case 6:  goto L360;

      case 7:  goto L240;

      case 8:  goto L190;

      case 9:  goto L240;

      case 10:  goto L20;

      case 11:  goto L20;

      case 12:  goto L30;
    }

  /*  ***  STORAGE ALLOCATION  *** */

L20:
  pp1o2 = *p * (*p + 1) / 2;
  iv[62] = iv[42] + pp1o2;
  iv[43] = iv[62] + pp1o2;
  iv[40] = iv[43] + (*p << 1);
  iv[37] = iv[40] + *p * 3;
  iv[65] = iv[37] + (*p << 1);
  iv[56] = iv[65] + (*p << 2) + 7;
  iv[47] = iv[56] + pp1o2;
  iv[76] = iv[58] + *p * 3;
  iv[46] = iv[76] + *p;

  if (iv[1] != 13)
    {
      goto L30;
    }

  iv[1] = 14;
  goto L999;

  /*  ***  INITIALIZATION  *** */

L30:
  iv[31] = 0;
  iv[6] = 1;
  iv[30] = 1;
  iv[7] = 1;
  iv[35] = -1;
  iv[11] = 2;
  iv[2] = 0;
  iv[55] = 0;
  iv[26] = 0;
  iv[52] = 0;
  iv[53] = 0;
  iv[8] = 0;
  iv[41] = *p;
  v[9] = 0.;
  v[5] = 0.;
  v[8] = v[35] / (v[21] + 1.);

  /*  ***  CHECK CONSISTENCY OF B AND INITIALIZE IP ARRAY  *** */

  ipi = iv[76];
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      iv[ipi] = i__;
      ++ipi;

      if (b[(i__ << 1) + 1] > b[(i__ << 1) + 2])
        {
          goto L680;
        }

      /* L40: */
    }

  /*  ***  SET INITIAL MODEL AND S MATRIX  *** */

  iv[5] = 1;
  iv[1] = 1;

  if (iv[62] < 0)
    {
      goto L710;
    }

  if (iv[25] > 1)
    {
      iv[5] = 2;
    }

  s1 = iv[62];

  if (iv[25] == 0 || iv[25] > 2)
    {
      i__1 = *p * (*p + 1) / 2;
      dv7scp_(&i__1, &v[s1], &c_b78);
    }

  goto L710;

  /*  ***  NEW FUNCTION VALUE  *** */

L50:

  if (iv[35] == 0)
    {
      goto L360;
    }

  if (iv[35] > 0)
    {
      goto L590;
    }

  if (iv[2] == 0)
    {
      goto L690;
    }

  iv[1] = 63;
  goto L999;

  /*  ***  MAKE SURE GRADIENT COULD BE COMPUTED  *** */

L60:

  if (iv[2] == 0)
    {
      goto L70;
    }

  iv[1] = 65;
  goto L999;

  /*  ***  NEW GRADIENT  *** */

L70:
  iv[34] = -1;
  iv[33] = -1;
  iv[74] = 0;

  if (iv[35] > 0)
    {
      goto L590;
    }

  if (iv[71] <= 0 && iv[78] <= 0)
    {
      goto L670;
    }

  /*  ***  CHOOSE INITIAL PERMUTATION  *** */

  ipi = iv[76];
  ipn = ipi + *p - 1;
  ipiv2 = iv[58] - 1;
  k = iv[41];
  p1 = *p;
  pp1 = *p + 1;
  rmat1 = iv[78];
  havrm = rmat1 > 0;
  qtr1 = iv[77];
  havqtr = qtr1 > 0;
  /*     *** MAKE SURE V(QTR1) IS LEGAL (EVEN WHEN NOT REFERENCED) *** */
  w1 = iv[65];

  if (! havqtr)
    {
      qtr1 = w1 + *p;
    }

  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      i1 = iv[ipn];
      --ipn;

      if (b[(i1 << 1) + 1] >= b[(i1 << 1) + 2])
        {
          goto L80;
        }

      xi = x[i1];
      gi = g[i1];

      if (xi <= b[(i1 << 1) + 1] && gi > 0.)
        {
          goto L80;
        }

      if (xi >= b[(i1 << 1) + 2] && gi < 0.)
        {
          goto L80;
        }

      /*           *** DISALLOW CONVERGENCE IF X(I1) HAS JUST BEEN FREED *** */
      j = ipiv2 + i1;

      if (iv[j] > k)
        {
          iv[55] = 0;
        }

      goto L100;
L80:

      if (i1 >= p1)
        {
          goto L90;
        }

      i1 = pp1 - i__;
      i7shft_(&p1, &i1, &iv[ipi]);

      if (havrm)
        {
          dq7rsh_(&i1, &p1, &havqtr, &v[qtr1], &v[rmat1], &v[w1]);
        }

L90:
      --p1;
L100:
      ;
    }

  iv[41] = p1;

  /*  ***  COMPUTE V(DGNORM) (AN OUTPUT VALUE IF WE STOP NOW)  *** */

  v[1] = 0.;

  if (p1 <= 0)
    {
      goto L110;
    }

  dig1 = iv[37];
  dv7vmp_(p, &v[dig1], &g[1], &d__[1], &c_n1);
  dv7ipr_(p, &iv[ipi], &v[dig1]);
  v[1] = dv2nrm_(&p1, &v[dig1]);
L110:

  if (iv[55] != 0)
    {
      goto L580;
    }

  if (iv[35] == 0)
    {
      goto L510;
    }

  iv[35] = 0;
  v[13] = v[10];

  if (iv[25] <= 2)
    {
      goto L170;
    }

  /*  ***  ARRANGE FOR FINITE-DIFFERENCE INITIAL S  *** */

  iv[13] = iv[15];
  iv[15] = -1;

  if (iv[25] > 3)
    {
      iv[15] = 1;
    }

  iv[55] = 70;
  goto L600;

  /*  ***  COME TO NEXT STMT AFTER COMPUTING F.D. HESSIAN FOR INIT. S  *** */

L120:
  h1 = iv[74];

  if (h1 <= 0)
    {
      goto L660;
    }

  iv[55] = 0;
  iv[35] = 0;
  iv[52] = 0;
  iv[53] = 0;
  iv[15] = iv[13];
  s1 = iv[62];
  pp1o2 = *ps * (*ps + 1) / 2;
  hc1 = iv[71];

  if (hc1 <= 0)
    {
      goto L130;
    }

  dv2axy_(&pp1o2, &v[s1], &c_b152, &v[hc1], &v[h1]);
  goto L140;
L130:
  rmat1 = iv[78];
  lmat1 = iv[42];
  dl7sqr_(p, &v[lmat1], &v[rmat1]);
  ipi = iv[76];
  ipiv1 = iv[58] + *p;
  i7pnvr_(p, &iv[ipiv1], &iv[ipi]);
  ds7ipr_(p, &iv[ipiv1], &v[lmat1]);
  dv2axy_(&pp1o2, &v[s1], &c_b152, &v[lmat1], &v[h1]);

  /*     *** ZERO PORTION OF S CORRESPONDING TO FIXED X COMPONENTS *** */

L140:
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      if (b[(i__ << 1) + 1] < b[(i__ << 1) + 2])
        {
          goto L160;
        }

      k = s1 + i__ * (i__ - 1) / 2;
      dv7scp_(&i__, &v[k], &c_b78);

      if (i__ >= *p)
        {
          goto L170;
        }

      k = k + (i__ << 1) - 1;
      i1 = i__ + 1;
      i__2 = *p;

      for (j = i1; j <= i__2; ++j)
        {
          v[k] = 0.;
          k += j;
          /* L150: */
        }

L160:
      ;
    }

L170:
  iv[1] = 2;

  /* -----------------------------  MAIN LOOP  ----------------------------- */

  /*  ***  PRINT ITERATION SUMMARY, CHECK ITERATION LIMIT  *** */

L190:
  k = iv[31];

  if (k < iv[18])
    {
      goto L200;
    }

  iv[1] = 10;
  goto L999;
L200:
  iv[31] = k + 1;

  /*  ***  UPDATE RADIUS  *** */

  if (k == 0)
    {
      goto L220;
    }

  step1 = iv[40];
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      v[step1] = d__[i__] * v[step1];
      ++step1;
      /* L210: */
    }

  step1 = iv[40];
  t = v[16] * dv2nrm_(p, &v[step1]);

  if (v[16] < 1. || t > v[8])
    {
      v[8] = t;
    }

  /*  ***  INITIALIZE FOR START OF NEXT ITERATION  *** */

L220:
  x01 = iv[43];
  v[13] = v[10];
  iv[29] = 4;
  iv[56] = -abs(iv[56]);
  iv[64] = iv[5];

  /*     ***  COPY X TO X0  *** */

  dv7cpy_(p, &v[x01], &x[1]);

  /*  ***  CHECK STOPX AND FUNCTION EVALUATION LIMIT  *** */

L230:

  if (! stopx_(&dummy))
    {
      goto L250;
    }

  iv[1] = 11;
  goto L260;

  /*     ***  COME HERE WHEN RESTARTING AFTER FUNC. EVAL. LIMIT OR STOPX. */

L240:

  if (v[10] >= v[13])
    {
      goto L250;
    }

  v[16] = 1.;
  k = iv[31];
  goto L200;

L250:

  if (iv[6] < iv[17] + iv[52])
    {
      goto L270;
    }

  iv[1] = 9;
L260:

  if (v[10] >= v[13])
    {
      goto L999;
    }

  /*        ***  IN CASE OF STOPX OR FUNCTION EVALUATION LIMIT WITH */
  /*        ***  IMPROVED V(F), EVALUATE THE GRADIENT AT X. */

  iv[55] = iv[1];
  goto L500;

  /* . . . . . . . . . . . . .  COMPUTE CANDIDATE STEP  . . . . . . . . . . */

L270:
  step1 = iv[40];
  tg1 = iv[37];
  td1 = tg1 + *p;
  x01 = iv[43];
  w1 = iv[65];
  h1 = iv[56];
  p1 = iv[41];
  ipi = iv[58];
  ipiv1 = ipi + *p;
  ipiv2 = ipiv1 + *p;
  ipiv0 = iv[76];

  if (iv[5] == 2)
    {
      goto L280;
    }

  /*        ***  COMPUTE LEVENBERG-MARQUARDT STEP IF POSSIBLE... */

  rmat1 = iv[78];

  if (rmat1 <= 0)
    {
      goto L280;
    }

  qtr1 = iv[77];

  if (qtr1 <= 0)
    {
      goto L280;
    }

  lmat1 = iv[42];
  wlm1 = w1 + *p;
  dl7msb_(&b[3], &d__[1], &g[1], &iv[75], &iv[ipiv0], &iv[ipiv1], &iv[ipiv2]
          , &iv[34], &v[lmat1], lv, p, &iv[48], &iv[41], &v[qtr1], &v[rmat1]
          , &v[step1], &v[td1], &v[tg1], &v[1], &v[w1], &v[wlm1], &x[1],
          &v[x01]);
  /*        *** H IS STORED IN THE END OF W AND HAS JUST BEEN OVERWRITTEN, */
  /*        *** SO WE MARK IT INVALID... */
  iv[56] = -abs(h1);
  /*        *** EVEN IF H WERE STORED ELSEWHERE, IT WOULD BE NECESSARY TO */
  /*        *** MARK INVALID THE INFORMATION DG7QTS MAY HAVE STORED IN V... */
  iv[33] = -1;
  goto L330;

L280:

  if (h1 > 0)
    {
      goto L320;
    }

  /*     ***  SET H TO  D**-1 * (HC + T1*S) * D**-1.  *** */

  p1len = p1 * (p1 + 1) / 2;
  h1 = -h1;
  iv[56] = h1;
  iv[74] = 0;

  if (p1 <= 0)
    {
      goto L320;
    }

  /*        *** MAKE TEMPORARY PERMUTATION ARRAY *** */
  i7copy_(p, &iv[ipi], &iv[ipiv0]);
  j = iv[71];

  if (j > 0)
    {
      goto L290;
    }

  j = h1;
  rmat1 = iv[78];
  dl7sqr_(&p1, &v[h1], &v[rmat1]);
  goto L300;

L290:
  i__1 = *p * (*p + 1) / 2;
  dv7cpy_(&i__1, &v[h1], &v[j]);
  ds7ipr_(p, &iv[ipi], &v[h1]);

L300:

  if (iv[5] == 1)
    {
      goto L310;
    }

  lmat1 = iv[42];
  s1 = iv[62];
  i__1 = *p * (*p + 1) / 2;
  dv7cpy_(&i__1, &v[lmat1], &v[s1]);
  ds7ipr_(p, &iv[ipi], &v[lmat1]);
  dv2axy_(&p1len, &v[h1], &c_b173, &v[lmat1], &v[h1]);

L310:
  dv7cpy_(p, &v[td1], &d__[1]);
  dv7ipr_(p, &iv[ipi], &v[td1]);
  ds7dmp_(&p1, &v[h1], &v[h1], &v[td1], &c_n1);
  iv[33] = -1;

  /*  ***  COMPUTE ACTUAL GOLDFELD-QUANDT-TROTTER STEP  *** */

L320:
  lmat1 = iv[42];
  dg7qsb_(&b[3], &d__[1], &v[h1], &g[1], &iv[ipi], &iv[ipiv1], &iv[ipiv2], &
          iv[33], &v[lmat1], lv, p, &iv[48], &p1, &v[step1], &v[td1],
          &v[tg1], &v[1], &v[w1], &x[1], &v[x01]);

  if (iv[34] > 0)
    {
      iv[34] = 0;
    }

L330:

  if (iv[29] != 6)
    {
      goto L340;
    }

  if (iv[9] != 2)
    {
      goto L360;
    }

  rstrst = 2;
  goto L370;

  /*  ***  CHECK WHETHER EVALUATING F(X0 + STEP) LOOKS WORTHWHILE  *** */

L340:
  iv[2] = 0;

  if (v[2] <= 0.)
    {
      goto L360;
    }

  if (iv[29] != 5)
    {
      goto L350;
    }

  if (v[16] <= 1.)
    {
      goto L350;
    }

  if (v[7] > v[11] * 1.2)
    {
      goto L350;
    }

  if (iv[9] != 2)
    {
      goto L360;
    }

  rstrst = 0;
  goto L370;

  /*  ***  COMPUTE F(X0 + STEP)  *** */

L350:
  x01 = iv[43];
  step1 = iv[40];
  dv2axy_(p, &x[1], &c_b173, &v[step1], &v[x01]);
  ++iv[6];
  iv[1] = 1;
  goto L710;

  /* . . . . . . . . . . . . .  ASSESS CANDIDATE STEP  . . . . . . . . . . . */

L360:
  rstrst = 3;

L370:
  x01 = iv[43];
  v[17] = drldst_(p, &d__[1], &x[1], &v[x01]);
  da7sst_(&iv[1], liv, lv, &v[1]);
  step1 = iv[40];
  lstgst = x01 + *p;
  i__ = iv[9] + 1;

  switch (i__)
    {
      case 1:  goto L410;

      case 2:  goto L380;

      case 3:  goto L390;

      case 4:  goto L400;
    }

L380:
  dv7cpy_(p, &x[1], &v[x01]);
  goto L410;

L390:
  dv7cpy_(p, &v[lstgst], &v[step1]);
  goto L410;

L400:
  dv7cpy_(p, &v[step1], &v[lstgst]);
  dv2axy_(p, &x[1], &c_b173, &v[step1], &v[x01]);
  v[17] = drldst_(p, &d__[1], &x[1], &v[x01]);

  /*  ***  IF NECESSARY, SWITCH MODELS  *** */

L410:

  if (iv[12] == 0)
    {
      goto L420;
    }

  iv[56] = -abs(iv[56]);
  iv[64] += 2;
  l = iv[60];
  dv7cpy_(&c__9, &v[1], &v[l]);
L420:
  dv2axy_(p, &v[step1], &c_b152, &v[x01], &x[1]);
  l = iv[29] - 4;
  stpmod = iv[5];

  if (l > 0)
    {
      switch (l)
        {
          case 1:  goto L440;

          case 2:  goto L450;

          case 3:  goto L460;

          case 4:  goto L460;

          case 5:  goto L460;

          case 6:  goto L460;

          case 7:  goto L460;

          case 8:  goto L460;

          case 9:  goto L570;

          case 10:  goto L510;
        }
    }

  /*  ***  DECIDE WHETHER TO CHANGE MODELS  *** */

  e = v[7] - v[11];
  s1 = iv[62];
  ds7lvm_(ps, &y[1], &v[s1], &v[step1]);
  sttsst = dd7tpr_(ps, &v[step1], &y[1]) * .5;

  if (iv[5] == 1)
    {
      sttsst = -sttsst;
    }

  if ((d__1 = e + sttsst, fabs(d__1)) * v[45] >= fabs(e))
    {
      goto L430;
    }

  /*     ***  SWITCH MODELS  *** */

  iv[5] = 3 - iv[5];

  if (-2 < l)
    {
      goto L470;
    }

  iv[56] = -abs(iv[56]);
  iv[64] += 2;
  l = iv[60];
  dv7cpy_(&c__9, &v[l], &v[1]);
  goto L230;

L430:

  if (-3 < l)
    {
      goto L470;
    }

  /*     ***  RECOMPUTE STEP WITH DIFFERENT RADIUS  *** */

L440:
  v[8] = v[16] * v[2];
  goto L230;

  /*  ***  COMPUTE STEP OF LENGTH V(LMAXS) FOR SINGULAR CONVERGENCE TEST */

L450:
  v[8] = v[36];
  goto L270;

  /*  ***  CONVERGENCE OR FALSE CONVERGENCE  *** */

L460:
  iv[55] = l;

  if (v[10] >= v[13])
    {
      goto L580;
    }

  if (iv[13] == 14)
    {
      goto L580;
    }

  iv[13] = 14;

  /* . . . . . . . . . . . .  PROCESS ACCEPTABLE STEP  . . . . . . . . . . . */

L470:
  iv[26] = 0;
  iv[67] = 0;

  /*  ***  SEE WHETHER TO SET V(RADFAC) BY GRADIENT TESTS  *** */

  if (iv[29] != 3)
    {
      goto L500;
    }

  step1 = iv[40];
  temp1 = step1 + *p;
  temp2 = iv[43];

  /*     ***  SET  TEMP1 = HESSIAN * STEP  FOR USE IN GRADIENT TESTS  *** */

  hc1 = iv[71];

  if (hc1 <= 0)
    {
      goto L480;
    }

  ds7lvm_(p, &v[temp1], &v[hc1], &v[step1]);
  goto L490;

L480:
  rmat1 = iv[78];
  ipiv0 = iv[76];
  dv7cpy_(p, &v[temp1], &v[step1]);
  dv7ipr_(p, &iv[ipiv0], &v[temp1]);
  dl7tvm_(p, &v[temp1], &v[rmat1], &v[temp1]);
  dl7vml_(p, &v[temp1], &v[rmat1], &v[temp1]);
  ipiv1 = iv[58] + *p;
  i7pnvr_(p, &iv[ipiv1], &iv[ipiv0]);
  dv7ipr_(p, &iv[ipiv1], &v[temp1]);

L490:

  if (stpmod == 1)
    {
      goto L500;
    }

  s1 = iv[62];
  ds7lvm_(ps, &v[temp2], &v[s1], &v[step1]);
  dv2axy_(ps, &v[temp1], &c_b173, &v[temp2], &v[temp1]);

  /*  ***  SAVE OLD GRADIENT AND COMPUTE NEW ONE  *** */

L500:
  ++iv[30];
  g01 = iv[65];
  dv7cpy_(p, &v[g01], &g[1]);
  goto L690;

  /*  ***  INITIALIZATIONS -- G0 = G - G0, ETC.  *** */

L510:
  g01 = iv[65];
  dv2axy_(p, &v[g01], &c_b152, &v[g01], &g[1]);
  step1 = iv[40];
  temp1 = step1 + *p;
  temp2 = iv[43];

  if (iv[29] != 3)
    {
      goto L540;
    }

  /*  ***  SET V(RADFAC) BY GRADIENT TESTS  *** */

  /*     ***  SET  TEMP1 = D**-1 * (HESSIAN * STEP  +  (G(X0) - G(X)))  *** */

  k = temp1;
  l = g01;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      v[k] = (v[k] - v[l]) / d__[i__];
      ++k;
      ++l;
      /* L520: */
    }

  /*        ***  DO GRADIENT TESTS  *** */

  if (dv2nrm_(p, &v[temp1]) <= v[1] * v[29])
    {
      goto L530;
    }

  if (dd7tpr_(p, &g[1], &v[step1]) >= v[4] * v[30])
    {
      goto L540;
    }

L530:
  v[16] = v[23];

  /*  ***  COMPUTE Y VECTOR NEEDED FOR UPDATING S  *** */

L540:
  dv2axy_(ps, &y[1], &c_b152, &y[1], &g[1]);

  /*  ***  DETERMINE SIZING FACTOR V(SIZE)  *** */

  /*     ***  SET TEMP1 = S * STEP  *** */
  s1 = iv[62];
  ds7lvm_(ps, &v[temp1], &v[s1], &v[step1]);

  t1 = (d__1 = dd7tpr_(ps, &v[step1], &v[temp1]), fabs(d__1));
  t = (d__1 = dd7tpr_(ps, &v[step1], &y[1]), fabs(d__1));
  v[55] = 1.;

  if (t < t1)
    {
      v[55] = t / t1;
    }

  /*  ***  SET G0 TO WCHMTD CHOICE OF FLETCHER AND AL-BAALI  *** */

  hc1 = iv[71];

  if (hc1 <= 0)
    {
      goto L550;
    }

  ds7lvm_(ps, &v[g01], &v[hc1], &v[step1]);
  goto L560;

L550:
  rmat1 = iv[78];
  ipiv0 = iv[76];
  dv7cpy_(p, &v[g01], &v[step1]);
  i__ = g01 + *ps;

  if (*ps < *p)
    {
      i__1 = *p - *ps;
      dv7scp_(&i__1, &v[i__], &c_b78);
    }

  dv7ipr_(p, &iv[ipiv0], &v[g01]);
  dl7tvm_(p, &v[g01], &v[rmat1], &v[g01]);
  dl7vml_(p, &v[g01], &v[rmat1], &v[g01]);
  ipiv1 = iv[58] + *p;
  i7pnvr_(p, &iv[ipiv1], &iv[ipiv0]);
  dv7ipr_(p, &iv[ipiv1], &v[g01]);

L560:
  dv2axy_(ps, &v[g01], &c_b173, &y[1], &v[g01]);

  /*  ***  UPDATE S  *** */

  ds7lup_(&v[s1], &v[47], ps, &v[55], &v[step1], &v[temp1], &v[temp2],
          &v[g01], &v[56], &y[1]);
  iv[1] = 2;
  goto L190;

  /* . . . . . . . . . . . . . .  MISC. DETAILS  . . . . . . . . . . . . . . */

  /*  ***  BAD PARAMETERS TO ASSESS  *** */

L570:
  iv[1] = 64;
  goto L999;

  /*  ***  CONVERGENCE OBTAINED -- SEE WHETHER TO COMPUTE COVARIANCE  *** */

L580:

  if (iv[57] == 0)
    {
      goto L660;
    }

  if (iv[74] != 0)
    {
      goto L660;
    }

  if (iv[55] >= 7)
    {
      goto L660;
    }

  if (iv[67] > 0)
    {
      goto L660;
    }

  if (iv[26] > 0)
    {
      goto L660;
    }

  if (abs(iv[15]) >= 3)
    {
      goto L640;
    }

  if (iv[9] == 0)
    {
      iv[9] = 2;
    }

  goto L600;

  /*  ***  COMPUTE FINITE-DIFFERENCE HESSIAN FOR COMPUTING COVARIANCE  *** */

L590:
  iv[9] = 0;

L600:
  df7dhb_(&b[3], &d__[1], &g[1], &i__, &iv[1], liv, lv, p, &v[1], &x[1]);

  switch (i__)
    {
      case 1:  goto L610;

      case 2:  goto L620;

      case 3:  goto L630;
    }

L610:
  ++iv[52];
  ++iv[6];
  iv[1] = 1;
  goto L710;

L620:
  ++iv[53];
  ++iv[30];
  iv[7] = iv[6] + iv[53];
  goto L690;

L630:

  if (iv[55] == 70)
    {
      goto L120;
    }

  goto L660;

L640:
  h1 = abs(iv[56]);
  iv[74] = h1;
  iv[56] = -h1;
  hc1 = iv[71];

  if (hc1 <= 0)
    {
      goto L650;
    }

  i__1 = *p * (*p + 1) / 2;
  dv7cpy_(&i__1, &v[h1], &v[hc1]);
  goto L660;

L650:
  rmat1 = iv[78];
  dl7sqr_(p, &v[h1], &v[rmat1]);

L660:
  iv[35] = 0;
  iv[1] = iv[55];
  iv[55] = 0;
  goto L999;

  /*  ***  SPECIAL RETURN FOR MISSING HESSIAN INFORMATION -- BOTH */
  /*  ***  IV(HC) .LE. 0 AND IV(RMAT) .LE. 0 */

L670:
  iv[1] = 1400;
  goto L999;

  /*  ***  INCONSISTENT B  *** */

L680:
  iv[1] = 82;
  goto L999;

  /*  *** SAVE, THEN INITIALIZE IPIVOT ARRAY BEFORE COMPUTING G *** */

L690:
  iv[1] = 2;
  j = iv[76];
  ipi = iv[58];
  i7pnvr_(p, &iv[ipi], &iv[j]);
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      iv[j] = i__;
      ++j;
      /* L700: */
    }

  /*  ***  PROJECT X INTO FEASIBLE REGION (PRIOR TO COMPUTING F OR G)  *** */

L710:
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      if (x[i__] < b[(i__ << 1) + 1])
        {
          x[i__] = b[(i__ << 1) + 1];
        }

      if (x[i__] > b[(i__ << 1) + 2])
        {
          x[i__] = b[(i__ << 1) + 2];
        }

      /* L720: */
    }

  iv[2] = 0;

L999:
  return 0;

  /*  ***  LAST LINE OF DG7ITB FOLLOWS  *** */
} /* dg7itb_ */

int dg7qsb_(doublereal *b, doublereal *d__, doublereal *
            dihdi, doublereal *g, integer *ipiv, integer *ipiv1, integer *ipiv2,
            integer *ka, doublereal *l, integer *lv, integer *p, integer *p0,
            integer *pc, doublereal *step, doublereal *td, doublereal *tg,
            doublereal *v, doublereal *w, doublereal *x, doublereal *x0)
{
  /* Initialized data */

  static doublereal zero = 0.;

  /* System generated locals */
  integer step_dim1, step_offset;

  /* Local variables */
  static doublereal nred, pred;
  static integer k, kinit, p1;
  extern int ds7bqn_(doublereal *, doublereal *,
                     doublereal *, integer *, integer *, integer *, integer *,
                     doublereal *, integer *, integer *, integer *, integer *,
                     doublereal *, doublereal *, doublereal *, doublereal *,
                     doublereal *, doublereal *, doublereal *);
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *);
  extern int dv7scp_(integer *, doublereal *, doublereal *),
         ds7ipr_(integer *, integer *, doublereal *), dg7qts_(doublereal *,
             doublereal *, doublereal *, integer *, doublereal *,
             integer *, doublereal *, doublereal *, doublereal *),
         dv7ipr_(integer *, integer *, doublereal *),
         dv7cpy_(integer *, doublereal *, doublereal *),
         dv7vmp_(integer *, doublereal *, doublereal *,
                 doublereal *, integer *);
  static integer kb, p10;
  static integer ns;
  static doublereal ds0, rad;

  /*  ***  COMPUTE HEURISTIC BOUNDED NEWTON STEP  *** */

  /*     DIMENSION DIHDI(P*(P+1)/2), L(P*(P+1)/2) */

  /*  ***  LOCAL VARIABLES  *** */

  /*  ***  V SUBSCRIPTS  *** */

  /* /6 */
  /*     DATA DST0/3/, DSTNRM/2/, GTSTEP/4/, NREDUC/6/, PREDUC/7/, */
  /*    1     RADIUS/8/ */
  /* /7 */
  /* / */
  /* Parameter adjustments */
  --dihdi;
  --l;
  --v;
  --x0;
  --x;
  --w;
  --tg;
  --td;
  step_dim1 = *p;
  step_offset = step_dim1 + 1;
  step -= step_offset;
  --ipiv2;
  --ipiv1;
  --ipiv;
  --g;
  --d__;
  b -= 3;

  /* Function Body */

  /* +++++++++++++++++++++++++++++++  BODY  ++++++++++++++++++++++++++++++++ */

  p1 = *pc;

  if (*ka < 0)
    {
      goto L10;
    }

  nred = v[6];
  ds0 = v[3];
  goto L20;

L10:
  *p0 = 0;
  *ka = -1;

L20:
  kinit = -1;

  if (*p0 == p1)
    {
      kinit = *ka;
    }

  dv7cpy_(p, &x[1], &x0[1]);
  pred = zero;
  rad = v[8];
  kb = -1;
  v[2] = zero;

  if (p1 > 0)
    {
      goto L30;
    }

  nred = zero;
  ds0 = zero;
  dv7scp_(p, &step[step_offset], &zero);
  goto L60;

L30:
  dv7cpy_(p, &td[1], &d__[1]);
  dv7ipr_(p, &ipiv[1], &td[1]);
  dv7vmp_(p, &tg[1], &g[1], &d__[1], &c_n1);
  dv7ipr_(p, &ipiv[1], &tg[1]);

L40:
  k = kinit;
  kinit = -1;
  v[8] = rad - v[2];
  dg7qts_(&td[1], &tg[1], &dihdi[1], &k, &l[1], &p1, &step[step_offset],
          &v[1], &w[1]);
  *p0 = p1;

  if (*ka >= 0)
    {
      goto L50;
    }

  nred = v[6];
  ds0 = v[3];

L50:
  *ka = k;
  v[8] = rad;
  p10 = p1;
  ds7bqn_(&b[3], &d__[1], &step[(step_dim1 << 1) + 1], &ipiv[1], &ipiv1[1],
          &ipiv2[1], &kb, &l[1], lv, &ns, p, &p1, &step[step_offset], &td[1],
          &tg[1], &v[1], &w[1], &x[1], &x0[1]);

  if (ns > 0)
    {
      ds7ipr_(&p10, &ipiv1[1], &dihdi[1]);
    }

  pred += v[7];

  if (ns != 0)
    {
      *p0 = 0;
    }

  if (kb <= 0)
    {
      goto L40;
    }

L60:
  v[3] = ds0;
  v[6] = nred;
  v[7] = pred;
  v[4] = dd7tpr_(p, &g[1], &step[step_offset]);

  /* L999: */
  return 0;
  /*  ***  LAST LINE OF DG7QSB FOLLOWS  *** */
} /* dg7qsb_ */

int dg7qts_(doublereal *d__, doublereal *dig, doublereal *
            dihdi, integer *ka, doublereal *l, integer *p, doublereal *step,
            doublereal *v, doublereal *w)
{
  /* Initialized data */

  static doublereal big = 0.;
  static doublereal dgxfac = 0.;

  /* System generated locals */
  integer i__1, i__2;
  doublereal d__1, d__2, d__3;

  /* Local variables */
  static integer diag, emin, emax;
  static doublereal root;
  static integer diag0, i__, j, k, q;
  static doublereal t;
  static integer x;
  static doublereal delta;
  static integer kalim, kamin;
  static doublereal radsq, gtsta;
  static integer k1, q0;
  static doublereal t1, t2;
  extern doublereal dr7mdc_(integer *);
  extern int dl7ivm_(integer *, doublereal *, doublereal *,
                     doublereal *);
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *),
         dv2nrm_(integer *, doublereal *);
  extern int dl7itv_(integer *, doublereal *, doublereal *, doublereal *);
  extern doublereal dl7svn_(integer *, doublereal *, doublereal *,
                            doublereal *);
  extern int dl7srt_(integer *, integer *, doublereal *,
                     doublereal *, integer *);
  static doublereal lk, si, sk, alphak, uk, wi, psifac;
  static integer dggdmx;
  static doublereal sw, oldphi, phimin, phimax;
  static integer phipin, dstsav, im1, lk0, uk0;
  static logical restrt;
  static doublereal twopsi, aki, akk, rad;
  static integer inc, irc;
  static doublereal phi, eps, dst;

  /*  *** COMPUTE GOLDFELD-QUANDT-TROTTER STEP BY MORE-HEBDEN TECHNIQUE *** */
  /*  ***  (NL2SOL VERSION 2.2), MODIFIED A LA MORE AND SORENSEN  *** */

  /*  ***  PARAMETER DECLARATIONS  *** */

  /*     DIMENSION DIHDI(P*(P+1)/2), L(P*(P+1)/2), W(4*P+7) */

  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

  /*  ***  PURPOSE  *** */

  /*        GIVEN THE (COMPACTLY STORED) LOWER TRIANGLE OF A SCALED */
  /*     HESSIAN (APPROXIMATION) AND A NONZERO SCALED GRADIENT VECTOR, */
  /*     THIS SUBROUTINE COMPUTES A GOLDFELD-QUANDT-TROTTER STEP OF */
  /*     APPROXIMATE LENGTH V(RADIUS) BY THE MORE-HEBDEN TECHNIQUE.  IN */
  /*     OTHER WORDS, STEP IS COMPUTED TO (APPROXIMATELY) MINIMIZE */
  /*     PSI(STEP) = (G**T)*STEP + 0.5*(STEP**T)*H*STEP  SUCH THAT THE */
  /*     2-NORM OF D*STEP IS AT MOST (APPROXIMATELY) V(RADIUS), WHERE */
  /*     G  IS THE GRADIENT,  H  IS THE HESSIAN, AND  D  IS A DIAGONAL */
  /*     SCALE MATRIX WHOSE DIAGONAL IS STORED IN THE PARAMETER D. */
  /*     (DG7QTS ASSUMES  DIG = D**-1 * G  AND  DIHDI = D**-1 * H * D**-1.) */

  /*  ***  PARAMETER DESCRIPTION  *** */

  /*     D (IN)  = THE SCALE VECTOR, I.E. THE DIAGONAL OF THE SCALE */
  /*              MATRIX  D  MENTIONED ABOVE UNDER PURPOSE. */
  /*   DIG (IN)  = THE SCALED GRADIENT VECTOR, D**-1 * G.  IF G = 0, THEN */
  /*              STEP = 0  AND  V(STPPAR) = 0  ARE RETURNED. */
  /* DIHDI (IN)  = LOWER TRIANGLE OF THE SCALED HESSIAN (APPROXIMATION), */
  /*              I.E., D**-1 * H * D**-1, STORED COMPACTLY BY ROWS., I.E., */
  /*              IN THE ORDER (1,1), (2,1), (2,2), (3,1), (3,2), ETC. */
  /*    KA (I/O) = THE NUMBER OF HEBDEN ITERATIONS (SO FAR) TAKEN TO DETER- */
  /*              MINE STEP.  KA .LT. 0 ON INPUT MEANS THIS IS THE FIRST */
  /*              ATTEMPT TO DETERMINE STEP (FOR THE PRESENT DIG AND DIHDI) */
  /*              -- KA IS INITIALIZED TO 0 IN THIS CASE.  OUTPUT WITH */
  /*              KA = 0  (OR V(STPPAR) = 0)  MEANS  STEP = -(H**-1)*G. */
  /*     L (I/O) = WORKSPACE OF LENGTH P*(P+1)/2 FOR CHOLESKY FACTORS. */
  /*     P (IN)  = NUMBER OF PARAMETERS -- THE HESSIAN IS A  P X P  MATRIX. */
  /*  STEP (I/O) = THE STEP COMPUTED. */
  /*     V (I/O) CONTAINS VARIOUS CONSTANTS AND VARIABLES DESCRIBED BELOW. */
  /*     W (I/O) = WORKSPACE OF LENGTH 4*P + 6. */

  /*  ***  ENTRIES IN V  *** */

  /* V(DGNORM) (I/O) = 2-NORM OF (D**-1)*G. */
  /* V(DSTNRM) (OUTPUT) = 2-NORM OF D*STEP. */
  /* V(DST0)   (I/O) = 2-NORM OF D*(H**-1)*G (FOR POS. DEF. H ONLY), OR */
  /*             OVERESTIMATE OF SMALLEST EIGENVALUE OF (D**-1)*H*(D**-1). */
  /* V(EPSLON) (IN)  = MAX. REL. ERROR ALLOWED FOR PSI(STEP).  FOR THE */
  /*             STEP RETURNED, PSI(STEP) WILL EXCEED ITS OPTIMAL VALUE */
  /*             BY LESS THAN -V(EPSLON)*PSI(STEP).  SUGGESTED VALUE = 0.1. */
  /* V(GTSTEP) (OUT) = INNER PRODUCT BETWEEN G AND STEP. */
  /* V(NREDUC) (OUT) = PSI(-(H**-1)*G) = PSI(NEWTON STEP)  (FOR POS. DEF. */
  /*             H ONLY -- V(NREDUC) IS SET TO ZERO OTHERWISE). */
  /* V(PHMNFC) (IN)  = TOL. (TOGETHER WITH V(PHMXFC)) FOR ACCEPTING STEP */
  /*             (MORE*S SIGMA).  THE ERROR V(DSTNRM) - V(RADIUS) MUST LIE */
  /*             BETWEEN V(PHMNFC)*V(RADIUS) AND V(PHMXFC)*V(RADIUS). */
  /* V(PHMXFC) (IN)  (SEE V(PHMNFC).) */
  /*             SUGGESTED VALUES -- V(PHMNFC) = -0.25, V(PHMXFC) = 0.5. */
  /* V(PREDUC) (OUT) = PSI(STEP) = PREDICTED OBJ. FUNC. REDUCTION FOR STEP. */
  /* V(RADIUS) (IN)  = RADIUS OF CURRENT (SCALED) TRUST REGION. */
  /* V(RAD0)   (I/O) = VALUE OF V(RADIUS) FROM PREVIOUS CALL. */
  /* V(STPPAR) (I/O) IS NORMALLY THE MARQUARDT PARAMETER, I.E. THE ALPHA */
  /*             DESCRIBED BELOW UNDER ALGORITHM NOTES.  IF H + ALPHA*D**2 */
  /*             (SEE ALGORITHM NOTES) IS (NEARLY) SINGULAR, HOWEVER, */
  /*             THEN V(STPPAR) = -ALPHA. */

  /*  ***  USAGE NOTES  *** */

  /*     IF IT IS DESIRED TO RECOMPUTE STEP USING A DIFFERENT VALUE OF */
  /*     V(RADIUS), THEN THIS ROUTINE MAY BE RESTARTED BY CALLING IT */
  /*     WITH ALL PARAMETERS UNCHANGED EXCEPT V(RADIUS).  (THIS EXPLAINS */
  /*     WHY STEP AND W ARE LISTED AS I/O).  ON AN INITIAL CALL (ONE WITH */
  /*     KA .LT. 0), STEP AND W NEED NOT BE INITIALIZED AND ONLY COMPO- */
  /*     NENTS V(EPSLON), V(STPPAR), V(PHMNFC), V(PHMXFC), V(RADIUS), AND */
  /*     V(RAD0) OF V MUST BE INITIALIZED. */

  /*  ***  ALGORITHM NOTES  *** */

  /*        THE DESIRED G-Q-T STEP (REF. 2, 3, 4, 6) SATISFIES */
  /*     (H + ALPHA*D**2)*STEP = -G  FOR SOME NONNEGATIVE ALPHA SUCH THAT */
  /*     H + ALPHA*D**2 IS POSITIVE SEMIDEFINITE.  ALPHA AND STEP ARE */
  /*     COMPUTED BY A SCHEME ANALOGOUS TO THE ONE DESCRIBED IN REF. 5. */
  /*     ESTIMATES OF THE SMALLEST AND LARGEST EIGENVALUES OF THE HESSIAN */
  /*     ARE OBTAINED FROM THE GERSCHGORIN CIRCLE THEOREM ENHANCED BY A */
  /*     SIMPLE FORM OF THE SCALING DESCRIBED IN REF. 7.  CASES IN WHICH */
  /*     H + ALPHA*D**2 IS NEARLY (OR EXACTLY) SINGULAR ARE HANDLED BY */
  /*     THE TECHNIQUE DISCUSSED IN REF. 2.  IN THESE CASES, A STEP OF */
  /*     (EXACT) LENGTH V(RADIUS) IS RETURNED FOR WHICH PSI(STEP) EXCEEDS */
  /*     ITS OPTIMAL VALUE BY LESS THAN -V(EPSLON)*PSI(STEP).  THE TEST */
  /*     SUGGESTED IN REF. 6 FOR DETECTING THE SPECIAL CASE IS PERFORMED */
  /*     ONCE TWO MATRIX FACTORIZATIONS HAVE BEEN DONE -- DOING SO SOONER */
  /*     SEEMS TO DEGRADE THE PERFORMANCE OF OPTIMIZATION ROUTINES THAT */
  /*     CALL THIS ROUTINE. */

  /*  ***  FUNCTIONS AND SUBROUTINES CALLED  *** */

  /* DD7TPR - RETURNS INNER PRODUCT OF TWO VECTORS. */
  /* DL7ITV - APPLIES INVERSE-TRANSPOSE OF COMPACT LOWER TRIANG. MATRIX. */
  /* DL7IVM - APPLIES INVERSE OF COMPACT LOWER TRIANG. MATRIX. */
  /* DL7SRT  - FINDS CHOLESKY FACTOR (OF COMPACTLY STORED LOWER TRIANG.). */
  /* DL7SVN - RETURNS APPROX. TO MIN. SING. VALUE OF LOWER TRIANG. MATRIX. */
  /* DR7MDC - RETURNS MACHINE-DEPENDENT CONSTANTS. */
  /* DV2NRM - RETURNS 2-NORM OF A VECTOR. */

  /*  ***  REFERENCES  *** */

  /* 1.  DENNIS, J.E., GAY, D.M., AND WELSCH, R.E. (1981), AN ADAPTIVE */
  /*             NONLINEAR LEAST-SQUARES ALGORITHM, ACM TRANS. MATH. */
  /*             SOFTWARE, VOL. 7, NO. 3. */
  /* 2.  GAY, D.M. (1981), COMPUTING OPTIMAL LOCALLY CONSTRAINED STEPS, */
  /*             SIAM J. SCI. STATIST. COMPUTING, VOL. 2, NO. 2, PP. */
  /*             186-197. */
  /* 3.  GOLDFELD, S.M., QUANDT, R.E., AND TROTTER, H.F. (1966), */
  /*             MAXIMIZATION BY QUADRATIC HILL-CLIMBING, ECONOMETRICA 34, */
  /*             PP. 541-551. */
  /* 4.  HEBDEN, M.D. (1973), AN ALGORITHM FOR MINIMIZATION USING EXACT */
  /*             SECOND DERIVATIVES, REPORT T.P. 515, THEORETICAL PHYSICS */
  /*             DIV., A.E.R.E. HARWELL, OXON., ENGLAND. */
  /* 5.  MORE, J.J. (1978), THE LEVENBERG-MARQUARDT ALGORITHM, IMPLEMEN- */
  /*             TATION AND THEORY, PP.105-116 OF SPRINGER LECTURE NOTES */
  /*             IN MATHEMATICS NO. 630, EDITED BY G.A. WATSON, SPRINGER- */
  /*             VERLAG, BERLIN AND NEW YORK. */
  /* 6.  MORE, J.J., AND SORENSEN, D.C. (1981), COMPUTING A TRUST REGION */
  /*             STEP, TECHNICAL REPORT ANL-81-83, ARGONNE NATIONAL LAB. */
  /* 7.  VARGA, R.S. (1965), MINIMAL GERSCHGORIN SETS, PACIFIC J. MATH. 15, */
  /*             PP. 719-729. */

  /*  ***  GENERAL  *** */

  /*     CODED BY DAVID M. GAY. */
  /*     THIS SUBROUTINE WAS WRITTEN IN CONNECTION WITH RESEARCH */
  /*     SUPPORTED BY THE NATIONAL SCIENCE FOUNDATION UNDER GRANTS */
  /*     MCS-7600324, DCR75-10143, 76-14311DSS, MCS76-11989, AND */
  /*     MCS-7906671. */

  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

  /*  ***  LOCAL VARIABLES  *** */

  /*     ***  CONSTANTS  *** */

  /*  ***  INTRINSIC FUNCTIONS  *** */
  /* /+ */
  /* / */
  /*  ***  EXTERNAL FUNCTIONS AND SUBROUTINES  *** */

  /*  ***  SUBSCRIPTS FOR V  *** */

  /* /6 */
  /*     DATA DGNORM/1/, DSTNRM/2/, DST0/3/, EPSLON/19/, GTSTEP/4/, */
  /*    1     NREDUC/6/, PHMNFC/20/, PHMXFC/21/, PREDUC/7/, RADIUS/8/, */
  /*    2     RAD0/9/, STPPAR/5/ */
  /* /7 */
  /* / */

  /* /6 */
  /*     DATA EPSFAC/50.0D+0/, FOUR/4.0D+0/, HALF/0.5D+0/, */
  /*    1     KAPPA/2.0D+0/, NEGONE/-1.0D+0/, ONE/1.0D+0/, P001/1.0D-3/, */
  /*    2     SIX/6.0D+0/, THREE/3.0D+0/, TWO/2.0D+0/, ZERO/0.0D+0/ */
  /* /7 */
  /* / */
  /* Parameter adjustments */
  --dihdi;
  --l;
  --step;
  --dig;
  --d__;
  --v;
  --w;

  /* Function Body */

  /*  ***  BODY  *** */

  if (big <= 0.)
    {
      big = dr7mdc_(&c__6);
    }

  /*     ***  STORE LARGEST ABS. ENTRY IN (D**-1)*H*(D**-1) AT W(DGGDMX). */
  dggdmx = *p + 1;
  /*     ***  STORE GERSCHGORIN OVER- AND UNDERESTIMATES OF THE LARGEST */
  /*     ***  AND SMALLEST EIGENVALUES OF (D**-1)*H*(D**-1) AT W(EMAX) */
  /*     ***  AND W(EMIN) RESPECTIVELY. */
  emax = dggdmx + 1;
  emin = emax + 1;
  /*     ***  FOR USE IN RECOMPUTING STEP, THE FINAL VALUES OF LK, UK, DST, */
  /*     ***  AND THE INVERSE DERIVATIVE OF MORE*S PHI AT 0 (FOR POS. DEF. */
  /*     ***  H) ARE STORED IN W(LK0), W(UK0), W(DSTSAV), AND W(PHIPIN) */
  /*     ***  RESPECTIVELY. */
  lk0 = emin + 1;
  phipin = lk0 + 1;
  uk0 = phipin + 1;
  dstsav = uk0 + 1;
  /*     ***  STORE DIAG OF (D**-1)*H*(D**-1) IN W(DIAG),...,W(DIAG0+P). */
  diag0 = dstsav;
  diag = diag0 + 1;
  /*     ***  STORE -D*STEP IN W(Q),...,W(Q0+P). */
  q0 = diag0 + *p;
  q = q0 + 1;
  /*     ***  ALLOCATE STORAGE FOR SCRATCH VECTOR X  *** */
  x = q + *p;
  rad = v[8];
  /* Computing 2nd power */
  d__1 = rad;
  radsq = d__1 * d__1;
  /*     ***  PHITOL = MAX. ERROR ALLOWED IN DST = V(DSTNRM) = 2-NORM OF */
  /*     ***  D*STEP. */
  phimax = v[21] * rad;
  phimin = v[20] * rad;
  psifac = big;
  t1 = v[19] * 2. / (((v[20] + 1.) * 4. * 3. + 2. + 2.) * 3. * rad);

  if (t1 < big * fmin(rad, 1.))
    {
      psifac = t1 / rad;
    }

  /*     ***  OLDPHI IS USED TO DETECT LIMITS OF NUMERICAL ACCURACY.  IF */
  /*     ***  WE RECOMPUTE STEP AND IT DOES NOT CHANGE, THEN WE ACCEPT IT. */
  oldphi = 0.;
  eps = v[19];
  irc = 0;
  restrt = FALSE_;
  kalim = *ka + 50;

  /*  ***  START OR RESTART, DEPENDING ON KA  *** */

  if (*ka >= 0)
    {
      goto L290;
    }

  /*  ***  FRESH START  *** */

  k = 0;
  uk = -1.;
  *ka = 0;
  kalim = 50;
  v[1] = dv2nrm_(p, &dig[1]);
  v[6] = 0.;
  v[3] = 0.;
  kamin = 3;

  if (v[1] == 0.)
    {
      kamin = 0;
    }

  /*     ***  STORE DIAG(DIHDI) IN W(DIAG0+1),...,W(DIAG0+P)  *** */

  j = 0;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j += i__;
      k1 = diag0 + i__;
      w[k1] = dihdi[j];
      /* L10: */
    }

  /*     ***  DETERMINE W(DGGDMX), THE LARGEST ELEMENT OF DIHDI  *** */

  t1 = 0.;
  j = *p * (*p + 1) / 2;
  i__1 = j;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      t = (d__1 = dihdi[i__], fabs(d__1));

      if (t1 < t)
        {
          t1 = t;
        }

      /* L20: */
    }

  w[dggdmx] = t1;

  /*  ***  TRY ALPHA = 0  *** */

L30:
  dl7srt_(&c__1, p, &l[1], &dihdi[1], &irc);

  if (irc == 0)
    {
      goto L50;
    }

  /*        ***  INDEF. H -- UNDERESTIMATE SMALLEST EIGENVALUE, USE THIS */
  /*        ***  ESTIMATE TO INITIALIZE LOWER BOUND LK ON ALPHA. */
  j = irc * (irc + 1) / 2;
  t = l[j];
  l[j] = 1.;
  i__1 = irc;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L40: */
      w[i__] = 0.;
    }

  w[irc] = 1.;
  dl7itv_(&irc, &w[1], &l[1], &w[1]);
  t1 = dv2nrm_(&irc, &w[1]);
  lk = -t / t1 / t1;
  v[3] = -lk;

  if (restrt)
    {
      goto L210;
    }

  goto L70;

  /*     ***  POSITIVE DEFINITE H -- COMPUTE UNMODIFIED NEWTON STEP.  *** */
L50:
  lk = 0.;
  t = dl7svn_(p, &l[1], &w[q], &w[q]);

  if (t >= 1.)
    {
      goto L60;
    }

  if (v[1] >= t * t * big)
    {
      goto L70;
    }

L60:
  dl7ivm_(p, &w[q], &l[1], &dig[1]);
  gtsta = dd7tpr_(p, &w[q], &w[q]);
  v[6] = gtsta * .5;
  dl7itv_(p, &w[q], &l[1], &w[q]);
  dst = dv2nrm_(p, &w[q]);
  v[3] = dst;
  phi = dst - rad;

  if (phi <= phimax)
    {
      goto L260;
    }

  if (restrt)
    {
      goto L210;
    }

  /*  ***  PREPARE TO COMPUTE GERSCHGORIN ESTIMATES OF LARGEST (AND */
  /*  ***  SMALLEST) EIGENVALUES.  *** */

L70:
  k = 0;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      wi = 0.;

      if (i__ == 1)
        {
          goto L90;
        }

      im1 = i__ - 1;
      i__2 = im1;

      for (j = 1; j <= i__2; ++j)
        {
          ++k;
          t = (d__1 = dihdi[k], fabs(d__1));
          wi += t;
          w[j] += t;
          /* L80: */
        }

L90:
      w[i__] = wi;
      ++k;
      /* L100: */
    }

  /*  ***  (UNDER-)ESTIMATE SMALLEST EIGENVALUE OF (D**-1)*H*(D**-1)  *** */

  k = 1;
  t1 = w[diag] - w[1];

  if (*p <= 1)
    {
      goto L120;
    }

  i__1 = *p;

  for (i__ = 2; i__ <= i__1; ++i__)
    {
      j = diag0 + i__;
      t = w[j] - w[i__];

      if (t >= t1)
        {
          goto L110;
        }

      t1 = t;
      k = i__;
L110:
      ;
    }

L120:
  sk = w[k];
  j = diag0 + k;
  akk = w[j];
  k1 = k * (k - 1) / 2 + 1;
  inc = 1;
  t = 0.;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      if (i__ == k)
        {
          goto L130;
        }

      aki = (d__1 = dihdi[k1], fabs(d__1));
      si = w[i__];
      j = diag0 + i__;
      t1 = (akk - w[j] + si - aki) * .5;
      t1 += sqrt(t1 * t1 + sk * aki);

      if (t < t1)
        {
          t = t1;
        }

      if (i__ < k)
        {
          goto L140;
        }

L130:
      inc = i__;

L140:
      k1 += inc;
      /* L150: */
    }

  w[emin] = akk - t;
  uk = v[1] / rad - w[emin];

  if (v[1] == 0.)
    {
      uk = uk + .001 + uk * .001;
    }

  if (uk <= 0.)
    {
      uk = .001;
    }

  /*  ***  COMPUTE GERSCHGORIN (OVER-)ESTIMATE OF LARGEST EIGENVALUE  *** */

  k = 1;
  t1 = w[diag] + w[1];

  if (*p <= 1)
    {
      goto L170;
    }

  i__1 = *p;

  for (i__ = 2; i__ <= i__1; ++i__)
    {
      j = diag0 + i__;
      t = w[j] + w[i__];

      if (t <= t1)
        {
          goto L160;
        }

      t1 = t;
      k = i__;
L160:
      ;
    }

L170:
  sk = w[k];
  j = diag0 + k;
  akk = w[j];
  k1 = k * (k - 1) / 2 + 1;
  inc = 1;
  t = 0.;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      if (i__ == k)
        {
          goto L180;
        }

      aki = (d__1 = dihdi[k1], fabs(d__1));
      si = w[i__];
      j = diag0 + i__;
      t1 = (w[j] + si - aki - akk) * .5;
      t1 += sqrt(t1 * t1 + sk * aki);

      if (t < t1)
        {
          t = t1;
        }

      if (i__ < k)
        {
          goto L190;
        }

L180:
      inc = i__;

L190:
      k1 += inc;
      /* L200: */
    }

  w[emax] = akk + t;
  /* Computing MAX */
  d__1 = lk, d__2 = v[1] / rad - w[emax];
  lk = fmax(d__1, d__2);

  /*     ***  ALPHAK = CURRENT VALUE OF ALPHA (SEE ALG. NOTES ABOVE).  WE */
  /*     ***  USE MORE*S SCHEME FOR INITIALIZING IT. */
  alphak = fabs(v[5]) * v[9] / rad;
  /* Computing MIN */
  d__1 = uk, d__2 = fmax(alphak, lk);
  alphak = fmin(d__1, d__2);

  if (irc != 0)
    {
      goto L210;
    }

  /*  ***  COMPUTE L0 FOR POSITIVE DEFINITE H  *** */

  dl7ivm_(p, &w[1], &l[1], &w[q]);
  t = dv2nrm_(p, &w[1]);
  w[phipin] = rad / t / t;
  /* Computing MAX */
  d__1 = lk, d__2 = phi * w[phipin];
  lk = fmax(d__1, d__2);

  /*  ***  SAFEGUARD ALPHAK AND ADD ALPHAK*I TO (D**-1)*H*(D**-1)  *** */

L210:
  ++(*ka);

  if (-v[3] >= alphak || alphak < lk || alphak >= uk)
    {
      /* Computing MAX */
      d__1 = .001, d__2 = sqrt(lk / uk);
      alphak = uk * fmax(d__1, d__2);
    }

  if (alphak <= 0.)
    {
      alphak = uk * .5;
    }

  if (alphak <= 0.)
    {
      alphak = uk;
    }

  k = 0;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      k += i__;
      j = diag0 + i__;
      dihdi[k] = w[j] + alphak;
      /* L220: */
    }

  /*  ***  TRY COMPUTING CHOLESKY DECOMPOSITION  *** */

  dl7srt_(&c__1, p, &l[1], &dihdi[1], &irc);

  if (irc == 0)
    {
      goto L240;
    }

  /*  ***  (D**-1)*H*(D**-1) + ALPHAK*I  IS INDEFINITE -- OVERESTIMATE */
  /*  ***  SMALLEST EIGENVALUE FOR USE IN UPDATING LK  *** */

  j = irc * (irc + 1) / 2;
  t = l[j];
  l[j] = 1.;
  i__1 = irc;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L230: */
      w[i__] = 0.;
    }

  w[irc] = 1.;
  dl7itv_(&irc, &w[1], &l[1], &w[1]);
  t1 = dv2nrm_(&irc, &w[1]);
  lk = alphak - t / t1 / t1;
  v[3] = -lk;

  if (uk < lk)
    {
      uk = lk;
    }

  if (alphak < lk)
    {
      goto L210;
    }

  /*  ***  NASTY CASE -- EXACT GERSCHGORIN BOUNDS.  FUDGE LK, UK... */

  t = alphak * .001;

  if (t <= 0.)
    {
      t = .001;
    }

  lk = alphak + t;

  if (uk <= lk)
    {
      uk = lk + t;
    }

  goto L210;

  /*  ***  ALPHAK MAKES (D**-1)*H*(D**-1) POSITIVE DEFINITE. */
  /*  ***  COMPUTE Q = -D*STEP, CHECK FOR CONVERGENCE.  *** */

L240:
  dl7ivm_(p, &w[q], &l[1], &dig[1]);
  gtsta = dd7tpr_(p, &w[q], &w[q]);
  dl7itv_(p, &w[q], &l[1], &w[q]);
  dst = dv2nrm_(p, &w[q]);
  phi = dst - rad;

  if (phi <= phimax && phi >= phimin)
    {
      goto L270;
    }

  if (phi == oldphi)
    {
      goto L270;
    }

  oldphi = phi;

  if (phi < 0.)
    {
      goto L330;
    }

  /*  ***  UNACCEPTABLE ALPHAK -- UPDATE LK, UK, ALPHAK  *** */

L250:

  if (*ka >= kalim)
    {
      goto L270;
    }

  /*     ***  THE FOLLOWING DMIN1 IS NECESSARY BECAUSE OF RESTARTS  *** */
  if (phi < 0.)
    {
      uk = fmin(uk, alphak);
    }

  /*     *** KAMIN = 0 ONLY IFF THE GRADIENT VANISHES  *** */
  if (kamin == 0)
    {
      goto L210;
    }

  dl7ivm_(p, &w[1], &l[1], &w[q]);
  /*     *** THE FOLLOWING, COMMENTED CALCULATION OF ALPHAK IS SOMETIMES */
  /*     *** SAFER BUT WORSE IN PERFORMANCE... */
  /*     T1 = DST / DV2NRM(P, W) */
  /*     ALPHAK = ALPHAK  +  T1 * (PHI/RAD) * T1 */
  t1 = dv2nrm_(p, &w[1]);
  alphak += phi / t1 * (dst / t1) * (dst / rad);
  lk = fmax(lk, alphak);
  alphak = lk;
  goto L210;

  /*  ***  ACCEPTABLE STEP ON FIRST TRY  *** */

L260:
  alphak = 0.;

  /*  ***  SUCCESSFUL STEP IN GENERAL.  COMPUTE STEP = -(D**-1)*Q  *** */

L270:
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j = q0 + i__;
      step[i__] = -w[j] / d__[i__];
      /* L280: */
    }

  v[4] = -gtsta;
  v[7] = (fabs(alphak) * dst * dst + gtsta) * .5;
  goto L410;

  /*  ***  RESTART WITH NEW RADIUS  *** */

L290:

  if (v[3] <= 0. || v[3] - rad > phimax)
    {
      goto L310;
    }

  /*     ***  PREPARE TO RETURN NEWTON STEP  *** */

  restrt = TRUE_;
  ++(*ka);
  k = 0;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      k += i__;
      j = diag0 + i__;
      dihdi[k] = w[j];
      /* L300: */
    }

  uk = -1.;
  goto L30;

L310:
  kamin = *ka + 3;

  if (v[1] == 0.)
    {
      kamin = 0;
    }

  if (*ka == 0)
    {
      goto L50;
    }

  dst = w[dstsav];
  alphak = fabs(v[5]);
  phi = dst - rad;
  t = v[1] / rad;
  uk = t - w[emin];

  if (v[1] == 0.)
    {
      uk = uk + .001 + uk * .001;
    }

  if (uk <= 0.)
    {
      uk = .001;
    }

  if (rad > v[9])
    {
      goto L320;
    }

  /*        ***  SMALLER RADIUS  *** */
  lk = 0.;

  if (alphak > 0.)
    {
      lk = w[lk0];
    }

  /* Computing MAX */
  d__1 = lk, d__2 = t - w[emax];
  lk = fmax(d__1, d__2);

  if (v[3] > 0.)
    {
      /* Computing MAX */
      d__1 = lk, d__2 = (v[3] - rad) * w[phipin];
      lk = fmax(d__1, d__2);
    }

  goto L250;

  /*     ***  BIGGER RADIUS  *** */
L320:

  if (alphak > 0.)
    {
      /* Computing MIN */
      d__1 = uk, d__2 = w[uk0];
      uk = fmin(d__1, d__2);
    }

  /* Computing MAX */
  d__1 = 0., d__2 = -v[3], d__1 = fmax(d__1, d__2), d__2 = t - w[emax];
  lk = fmax(d__1, d__2);

  if (v[3] > 0.)
    {
      /* Computing MAX */
      d__1 = lk, d__2 = (v[3] - rad) * w[phipin];
      lk = fmax(d__1, d__2);
    }

  goto L250;

  /*  ***  DECIDE WHETHER TO CHECK FOR SPECIAL CASE... IN PRACTICE (FROM */
  /*  ***  THE STANDPOINT OF THE CALLING OPTIMIZATION CODE) IT SEEMS BEST */
  /*  ***  NOT TO CHECK UNTIL A FEW ITERATIONS HAVE FAILED -- HENCE THE */
  /*  ***  TEST ON KAMIN BELOW. */

L330:
  delta = alphak + fmin(0., v[3]);
  twopsi = alphak * dst * dst + gtsta;

  if (*ka >= kamin)
    {
      goto L340;
    }

  /*     *** IF THE TEST IN REF. 2 IS SATISFIED, FALL THROUGH TO HANDLE */
  /*     *** THE SPECIAL CASE (AS SOON AS THE MORE-SORENSEN TEST DETECTS */
  /*     *** IT). */
  if (psifac >= big)
    {
      goto L340;
    }

  if (delta >= psifac * twopsi)
    {
      goto L370;
    }

  /*  ***  CHECK FOR THE SPECIAL CASE OF  H + ALPHA*D**2  (NEARLY) */
  /*  ***  SINGULAR.  USE ONE STEP OF INVERSE POWER METHOD WITH START */
  /*  ***  FROM DL7SVN TO OBTAIN APPROXIMATE EIGENVECTOR CORRESPONDING */
  /*  ***  TO SMALLEST EIGENVALUE OF (D**-1)*H*(D**-1).  DL7SVN RETURNS */
  /*  ***  X AND W WITH  L*W = X. */

L340:
  t = dl7svn_(p, &l[1], &w[x], &w[1]);

  /*     ***  NORMALIZE W  *** */
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L350: */
      w[i__] = t * w[i__];
    }

  /*     ***  COMPLETE CURRENT INV. POWER ITER. -- REPLACE W BY (L**-T)*W. */
  dl7itv_(p, &w[1], &l[1], &w[1]);
  t2 = 1. / dv2nrm_(p, &w[1]);
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L360: */
      w[i__] = t2 * w[i__];
    }

  t = t2 * t;

  /*  ***  NOW W IS THE DESIRED APPROXIMATE (UNIT) EIGENVECTOR AND */
  /*  ***  T*X = ((D**-1)*H*(D**-1) + ALPHAK*I)*W. */

  sw = dd7tpr_(p, &w[q], &w[1]);
  t1 = (rad + dst) * (rad - dst);
  root = sqrt(sw * sw + t1);

  if (sw < 0.)
    {
      root = -root;
    }

  si = t1 / (sw + root);

  /*  ***  THE ACTUAL TEST FOR THE SPECIAL CASE... */

  /* Computing 2nd power */
  d__1 = t2 * si;
  /* Computing 2nd power */
  d__2 = dst;

  if (d__1 * d__1 <= eps * (d__2 * d__2 + alphak * radsq))
    {
      goto L380;
    }

  /*  ***  UPDATE UPPER BOUND ON SMALLEST EIGENVALUE (WHEN NOT POSITIVE) */
  /*  ***  (AS RECOMMENDED BY MORE AND SORENSEN) AND CONTINUE... */

  if (v[3] <= 0.)
    {
      /* Computing MIN */
      /* Computing 2nd power */
      d__3 = t2;
      d__1 = v[3], d__2 = d__3 * d__3 - alphak;
      v[3] = fmin(d__1, d__2);
    }

  /* Computing MAX */
  d__1 = lk, d__2 = -v[3];
  lk = fmax(d__1, d__2);

  /*  ***  CHECK WHETHER WE CAN HOPE TO DETECT THE SPECIAL CASE IN */
  /*  ***  THE AVAILABLE ARITHMETIC.  ACCEPT STEP AS IT IS IF NOT. */

  /*     ***  IF NOT YET AVAILABLE, OBTAIN MACHINE DEPENDENT VALUE DGXFAC. */
L370:

  if (dgxfac == 0.)
    {
      dgxfac = dr7mdc_(&c__3) * 50.;
    }

  if (delta > dgxfac * w[dggdmx])
    {
      goto L250;
    }

  goto L270;

  /*  ***  SPECIAL CASE DETECTED... NEGATE ALPHAK TO INDICATE SPECIAL CASE */

L380:
  alphak = -alphak;
  v[7] = twopsi * .5;

  /*  ***  ACCEPT CURRENT STEP IF ADDING SI*W WOULD LEAD TO A */
  /*  ***  FURTHER RELATIVE REDUCTION IN PSI OF LESS THAN V(EPSLON)/3. */

  t1 = 0.;
  t = si * (alphak * sw - si * .5 * (alphak + t * dd7tpr_(p, &w[x], &w[1])))
      ;

  if (t < eps * twopsi / 6.)
    {
      goto L390;
    }

  v[7] += t;
  dst = rad;
  t1 = -si;
L390:
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j = q0 + i__;
      w[j] = t1 * w[i__] - w[j];
      step[i__] = w[j] / d__[i__];
      /* L400: */
    }

  v[4] = dd7tpr_(p, &dig[1], &w[q]);

  /*  ***  SAVE VALUES FOR USE IN A POSSIBLE RESTART  *** */

L410:
  v[2] = dst;
  v[5] = alphak;
  w[lk0] = lk;
  w[uk0] = uk;
  v[9] = rad;
  w[dstsav] = dst;

  /*     ***  RESTORE DIAGONAL OF DIHDI  *** */

  j = 0;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j += i__;
      k = diag0 + i__;
      dihdi[j] = w[k];
      /* L420: */
    }

  /* L999: */
  return 0;

  /*  ***  LAST CARD OF DG7QTS FOLLOWS  *** */
} /* dg7qts_ */

int dh2rfa_(integer *n, doublereal *a, doublereal *b,
            doublereal *x, doublereal *y, doublereal *z__)
{
  /* System generated locals */
  integer i__1;

  /* Local variables */
  static integer i__;
  static doublereal t;

  /*  ***  APPLY 2X2 HOUSEHOLDER REFLECTION DETERMINED BY X, Y, Z TO */
  /*  ***  N-VECTORS A, B  *** */

  /* Parameter adjustments */
  --b;
  --a;

  /* Function Body */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      t = a[i__] * *x + b[i__] * *y;
      a[i__] += t;
      b[i__] += t * *z__;
      /* L10: */
    }

  /* L999: */
  return 0;
  /*  ***  LAST LINE OF DH2RFA FOLLOWS  *** */
} /* dh2rfa_ */

doublereal dh2rfg_(doublereal *a, doublereal *b, doublereal *x, doublereal *y,
                   doublereal *z__)
{
  /* Initialized data */

  static doublereal zero = 0.;

  /* System generated locals */
  doublereal ret_val, d__1, d__2;

  /* Local variables */
  static doublereal c__, t, a1, b1;

  /*  ***  DETERMINE X, Y, Z SO  I + (1,Z)**T * (X,Y)  IS A 2X2 */
  /*  ***  HOUSEHOLDER REFLECTION SENDING (A,B)**T INTO (C,0)**T, */
  /*  ***  WHERE  C = -SIGN(A)*SQRT(A**2 + B**2)  IS THE VALUE DH2RFG */
  /*  ***  RETURNS. */

  /* /+ */
  /* / */

  /*  ***  BODY  *** */

  if (*b != zero)
    {
      goto L10;
    }

  *x = zero;
  *y = zero;
  *z__ = zero;
  ret_val = *a;
  goto L999;

L10:
  t = fabs(*a) + fabs(*b);
  a1 = *a / t;
  b1 = *b / t;
  /* Computing 2nd power */
  d__1 = a1;
  /* Computing 2nd power */
  d__2 = b1;
  c__ = sqrt(d__1 * d__1 + d__2 * d__2);

  if (a1 > zero)
    {
      c__ = -c__;
    }

  a1 -= c__;
  *z__ = b1 / a1;
  *x = a1 / c__;
  *y = b1 / c__;
  ret_val = t * c__;

L999:
  return ret_val;
  /*  ***  LAST LINE OF DH2RFG FOLLOWS  *** */
} /* dh2rfg_ */

int divset_(integer *alg, integer *iv, integer *liv, integer
            *lv, doublereal *v);

int CNL2SOL::divset_N(integer *alg, integer *iv, integer *liv,
                      integer *lv, doublereal *v)
{
  return divset_(alg, iv, liv, lv, v);
}

int divset_(integer *alg, integer *iv, integer *liv,
            integer *lv, doublereal *v)
{
  /* Initialized data */

  static integer miniv[4] = {82, 59, 103, 103 };
  static integer minv[4] = {98, 71, 101, 85 };

  extern integer i7mdcn_(integer *);
  extern int dv7dfl_(integer *, integer *, doublereal *);
  static integer mv, miv, alg1;

  /*  ***  SUPPLY ***SOL (VERSION 2.3) DEFAULT VALUES TO IV AND V  *** */

  /*  ***  ALG = 1 MEANS REGRESSION CONSTANTS. */
  /*  ***  ALG = 2 MEANS GENERAL UNCONSTRAINED OPTIMIZATION CONSTANTS. */

  /* I7MDCN... RETURNS MACHINE-DEPENDENT INTEGER CONSTANTS. */
  /* DV7DFL.... PROVIDES DEFAULT VALUES TO V. */

  /*  ***  SUBSCRIPTS FOR IV  *** */

  /*  ***  IV SUBSCRIPT VALUES  *** */

  /* /6 */
  /*     DATA ALGSAV/51/, COVPRT/14/, COVREQ/15/, DRADPR/101/, DTYPE/16/, */
  /*    1     HC/71/, IERR/75/, INITH/25/, INITS/25/, IPIVOT/76/, */
  /*    2     IVNEED/3/, LASTIV/44/, LASTV/45/, LMAT/42/, MXFCAL/17/, */
  /*    3     MXITER/18/, NFCOV/52/, NGCOV/53/, NVDFLT/50/, NVSAVE/9/, */
  /*    4     OUTLEV/19/, PARPRT/20/, PARSAV/49/, PERM/58/, PRUNIT/21/, */
  /*    5     QRTYP/80/, RDREQ/57/, RMAT/78/, SOLPRT/22/, STATPR/23/, */
  /*    6     VNEED/4/, VSAVE/60/, X0PRT/24/ */
  /* /7 */
  /* / */
  /* Parameter adjustments */
  --iv;
  --v;

  /* Function Body */

  /* -------------------------------  BODY  -------------------------------- */

  if (21 <= *liv)
    {
      iv[21] = i7mdcn_(&c__1);
    }

  if (51 <= *liv)
    {
      iv[51] = *alg;
    }

  if (*alg < 1 || *alg > 4)
    {
      goto L40;
    }

  miv = miniv[*alg - 1];

  if (*liv < miv)
    {
      goto L20;
    }

  mv = minv[*alg - 1];

  if (*lv < mv)
    {
      goto L30;
    }

  alg1 = (*alg - 1) % 2 + 1;
  dv7dfl_(&alg1, lv, &v[1]);
  iv[1] = 12;

  if (*alg > 2)
    {
      iv[101] = 1;
    }

  iv[3] = 0;
  iv[44] = miv;
  iv[45] = mv;
  iv[42] = mv + 1;
  iv[17] = 200;
  iv[18] = 150;
  iv[19] = 1;
  iv[20] = 1;
  iv[58] = miv + 1;
  iv[22] = 1;
  iv[23] = 1;
  iv[4] = 0;
  iv[24] = 1;

  if (alg1 >= 2)
    {
      goto L10;
    }

  /*  ***  REGRESSION  VALUES */

  iv[14] = 3;
  iv[15] = 1;
  iv[16] = 1;
  iv[71] = 0;
  iv[75] = 0;
  iv[25] = 0;
  iv[76] = 0;
  iv[50] = 32;
  iv[60] = 58;

  if (*alg > 2)
    {
      iv[60] += 3;
    }

  iv[49] = iv[60] + 9;
  iv[80] = 1;
  iv[57] = 3;
  iv[78] = 0;
  goto L999;

  /*  ***  GENERAL OPTIMIZATION VALUES */

L10:
  iv[16] = 0;
  iv[25] = 1;
  iv[52] = 0;
  iv[53] = 0;
  iv[50] = 25;
  iv[49] = 47;

  if (*alg > 2)
    {
      iv[49] = 61;
    }

  goto L999;

L20:
  iv[1] = 15;
  goto L999;

L30:
  iv[1] = 16;
  goto L999;

L40:
  iv[1] = 67;

L999:
  return 0;
  /*  ***  LAST CARD OF DIVSET FOLLOWS  *** */
} /* divset_ */

int dl7itv_(integer *n, doublereal *x, doublereal *l,
            doublereal *y)
{
  /* System generated locals */
  integer i__1, i__2;

  /* Local variables */
  static integer i__, j, i0, ii, ij;
  static doublereal xi;
  static integer im1, np1;

  /*  ***  SOLVE  (L**T)*X = Y,  WHERE  L  IS AN  N X N  LOWER TRIANGULAR */
  /*  ***  MATRIX STORED COMPACTLY BY ROWS.  X AND Y MAY OCCUPY THE SAME */
  /*  ***  STORAGE.  *** */

  /* /6 */
  /*     DATA ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /* Parameter adjustments */
  --y;
  --x;
  --l;

  /* Function Body */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L10: */
      x[i__] = y[i__];
    }

  np1 = *n + 1;
  i0 = *n * (*n + 1) / 2;
  i__1 = *n;

  for (ii = 1; ii <= i__1; ++ii)
    {
      i__ = np1 - ii;
      xi = x[i__] / l[i0];
      x[i__] = xi;

      if (i__ <= 1)
        {
          goto L999;
        }

      i0 -= i__;

      if (xi == 0.)
        {
          goto L30;
        }

      im1 = i__ - 1;
      i__2 = im1;

      for (j = 1; j <= i__2; ++j)
        {
          ij = i0 + j;
          x[j] -= xi * l[ij];
          /* L20: */
        }

L30:
      ;
    }

L999:
  return 0;
  /*  ***  LAST CARD OF DL7ITV FOLLOWS  *** */
} /* dl7itv_ */

int dl7ivm_(integer *n, doublereal *x, doublereal *l,
            doublereal *y)
{
  /* System generated locals */
  integer i__1, i__2;

  /* Local variables */
  static integer i__, j, k;
  static doublereal t;
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *);

  /*  ***  SOLVE  L*X = Y, WHERE  L  IS AN  N X N  LOWER TRIANGULAR */
  /*  ***  MATRIX STORED COMPACTLY BY ROWS.  X AND Y MAY OCCUPY THE SAME */
  /*  ***  STORAGE.  *** */

  /* /6 */
  /*     DATA ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /* Parameter adjustments */
  --y;
  --x;
  --l;

  /* Function Body */
  i__1 = *n;

  for (k = 1; k <= i__1; ++k)
    {
      if (y[k] != 0.)
        {
          goto L20;
        }

      x[k] = 0.;
      /* L10: */
    }

  goto L999;

L20:
  j = k * (k + 1) / 2;
  x[k] = y[k] / l[j];

  if (k >= *n)
    {
      goto L999;
    }

  ++k;
  i__1 = *n;

  for (i__ = k; i__ <= i__1; ++i__)
    {
      i__2 = i__ - 1;
      t = dd7tpr_(&i__2, &l[j + 1], &x[1]);
      j += i__;
      x[i__] = (y[i__] - t) / l[j];
      /* L30: */
    }

L999:
  return 0;
  /*  ***  LAST CARD OF DL7IVM FOLLOWS  *** */
} /* dl7ivm_ */

int dl7msb_(doublereal *b, doublereal *d__, doublereal *g,
            integer *ierr, integer *ipiv, integer *ipiv1, integer *ipiv2, integer
            *ka, doublereal *lmat, integer *lv, integer *p, integer *p0, integer *
            pc, doublereal *qtr, doublereal *rmat, doublereal *step, doublereal *
            td, doublereal *tg, doublereal *v, doublereal *w, doublereal *wlm,
            doublereal *x, doublereal *x0)
{
  /* Initialized data */

  static doublereal one = 1.;
  static doublereal zero = 0.;

  /* System generated locals */
  integer step_dim1, step_offset, i__1;

  /* Local variables */
  static doublereal nred, pred;
  static integer i__, j, k, l, kinit, k0, p1;
  extern int dd7mlp_(integer *, doublereal *, doublereal *,
                     doublereal *, integer *),
                                ds7bqn_(doublereal *, doublereal *, doublereal *, integer *,
                                        integer *, integer *, integer *, doublereal *,
                                        integer *, integer *, integer *, integer *,
                                        doublereal *, doublereal *, doublereal *, doublereal *,
                                        doublereal *, doublereal *, doublereal *);
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *);
  extern int dv7scp_(integer *, doublereal *, doublereal *),
         dq7rsh_(integer *, integer *, logical *, doublereal *,
                 doublereal *, doublereal *), dl7mst_(doublereal *, doublereal *,
                     integer *, integer *, integer *, integer *, doublereal *,
                     doublereal *, doublereal *, doublereal *, doublereal *),
         dv7ipr_(integer *, integer *, doublereal *),
         dl7tvm_(integer *, doublereal *, doublereal *, doublereal *),
         dv2axy_(integer *, doublereal *, doublereal *, doublereal *, doublereal *),
         dv7cpy_(integer *, doublereal *, doublereal *),
         dv7vmp_(integer *, doublereal *, doublereal *, doublereal *, integer *);
  static integer kb, p10, p11;
  static integer ns;
  static doublereal ds0, rad;

  /*  ***  COMPUTE HEURISTIC BOUNDED NEWTON STEP  *** */

  /*     DIMENSION LMAT(P*(P+1)/2), RMAT(P*(P+1)/2), WLM(P*(P+5)/2 + 4) */

  /*  ***  LOCAL VARIABLES  *** */

  /*  ***  V SUBSCRIPTS  *** */

  /* /6 */
  /*     DATA DST0/3/, DSTNRM/2/, GTSTEP/4/, NREDUC/6/, PREDUC/7/, */
  /*    1     RADIUS/8/ */
  /* /7 */
  /* / */
  /* Parameter adjustments */
  --lmat;
  --v;
  --x0;
  --x;
  --w;
  --tg;
  --td;
  step_dim1 = *p;
  step_offset = step_dim1 + 1;
  step -= step_offset;
  --qtr;
  --ipiv2;
  --ipiv1;
  --ipiv;
  --g;
  --d__;
  b -= 3;
  --rmat;
  --wlm;

  /* Function Body */

  /* +++++++++++++++++++++++++++++++  BODY  ++++++++++++++++++++++++++++++++ */

  p1 = *pc;

  if (*ka < 0)
    {
      goto L10;
    }

  nred = v[6];
  ds0 = v[3];
  goto L20;
L10:
  *p0 = 0;
  *ka = -1;

L20:
  kinit = -1;

  if (*p0 == p1)
    {
      kinit = *ka;
    }

  dv7cpy_(p, &x[1], &x0[1]);
  dv7cpy_(p, &td[1], &d__[1]);
  /*     *** USE STEP(1,3) AS TEMP. COPY OF QTR *** */
  dv7cpy_(p, &step[step_dim1 * 3 + 1], &qtr[1]);
  dv7ipr_(p, &ipiv[1], &td[1]);
  pred = zero;
  rad = v[8];
  kb = -1;
  v[2] = zero;

  if (p1 > 0)
    {
      goto L30;
    }

  nred = zero;
  ds0 = zero;
  dv7scp_(p, &step[step_offset], &zero);
  goto L90;

L30:
  dv7vmp_(p, &tg[1], &g[1], &d__[1], &c_n1);
  dv7ipr_(p, &ipiv[1], &tg[1]);
  p10 = p1;

L40:
  k = kinit;
  kinit = -1;
  v[8] = rad - v[2];
  dv7vmp_(&p1, &tg[1], &tg[1], &td[1], &c__1);
  i__1 = p1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L50: */
      ipiv1[i__] = i__;
    }

  k0 = std::max((integer) 0, k);
  dl7mst_(&td[1], &tg[1], ierr, &ipiv1[1], &k, &p1, &step[step_dim1 * 3 + 1]
          , &rmat[1], &step[step_offset], &v[1], &wlm[1]);
  dv7vmp_(&p1, &tg[1], &tg[1], &td[1], &c_n1);
  *p0 = p1;

  if (*ka >= 0)
    {
      goto L60;
    }

  nred = v[6];
  ds0 = v[3];

L60:
  *ka = k;
  v[8] = rad;
  l = p1 + 5;

  if (k <= k0)
    {
      dd7mlp_(&p1, &lmat[1], &td[1], &rmat[1], &c_n1);
    }

  if (k > k0)
    {
      dd7mlp_(&p1, &lmat[1], &td[1], &wlm[l], &c_n1);
    }

  ds7bqn_(&b[3], &d__[1], &step[(step_dim1 << 1) + 1], &ipiv[1], &ipiv1[1],
          &ipiv2[1], &kb, &lmat[1], lv, &ns, p, &p1, &step[step_offset],
          &td[1], &tg[1], &v[1], &w[1], &x[1], &x0[1]);
  pred += v[7];

  if (ns == 0)
    {
      goto L80;
    }

  *p0 = 0;

  /*  ***  UPDATE RMAT AND QTR  *** */

  p11 = p1 + 1;
  l = p10 + p11;
  i__1 = p10;

  for (k = p11; k <= i__1; ++k)
    {
      j = l - k;
      i__ = ipiv2[j];

      if (i__ < j)
        {
          dq7rsh_(&i__, &j, &c_true, &qtr[1], &rmat[1], &w[1]);
        }

      /* L70: */
    }

L80:

  if (kb > 0)
    {
      goto L90;
    }

  /*  ***  UPDATE LOCAL COPY OF QTR  *** */

  dv7vmp_(&p10, &w[1], &step[(step_dim1 << 1) + 1], &td[1], &c_n1);
  dl7tvm_(&p10, &w[1], &lmat[1], &w[1]);
  dv2axy_(&p10, &step[step_dim1 * 3 + 1], &one, &w[1], &qtr[1]);
  goto L40;

L90:
  v[3] = ds0;
  v[6] = nred;
  v[7] = pred;
  v[4] = dd7tpr_(p, &g[1], &step[step_offset]);

  /* L999: */
  return 0;
  /*  ***  LAST LINE OF DL7MSB FOLLOWS  *** */
} /* dl7msb_ */

int dl7mst_(doublereal *d__, doublereal *g, integer *ierr,
            integer *ipivot, integer *ka, integer *p, doublereal *qtr,
            doublereal *r__, doublereal *step, doublereal *v, doublereal *w)
{
  /* Initialized data */

  static doublereal big = 0.;

  /* System generated locals */
  integer i__1, i__2, i__3;
  doublereal d__1, d__2;

  /* Local variables */
  static integer pp1o2, rmat;
  static doublereal dtol;
  static integer rmat0;
  static doublereal a, b;
  static integer i__, k, l;
  static doublereal t;
  static integer kalim;
  static doublereal d1, d2;
  static integer i1, j1;
  extern doublereal dr7mdc_(integer *);
  extern int dl7ivm_(integer *, doublereal *, doublereal *, doublereal *);
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *),
         dv2nrm_(integer *, doublereal *);
  extern int dl7itv_(integer *, doublereal *, doublereal *, doublereal *);
  extern doublereal dl7svn_(integer *, doublereal *, doublereal *,
                            doublereal *);
  extern int dv7cpy_(integer *, doublereal *, doublereal *)
  ;
  static doublereal lk, si, sj, alphak, dfacsq, uk, wl, psifac, oldphi,
         phimin, phimax;
  static integer phipin, dstsav;
  static doublereal sqrtak;
  static integer lk0, ip1, uk0;
  static doublereal twopsi, adi, rad, phi;
  static integer res;
  static doublereal dst;
  static integer res0;

  /*  ***  PURPOSE  *** */

  /*        GIVEN THE R MATRIX FROM THE QR DECOMPOSITION OF A JACOBIAN */
  /*     MATRIX, J, AS WELL AS Q-TRANSPOSE TIMES THE CORRESPONDING */
  /*     RESIDUAL VECTOR, RESID, THIS SUBROUTINE COMPUTES A LEVENBERG- */
  /*     MARQUARDT STEP OF APPROXIMATE LENGTH V(RADIUS) BY THE MORE- */
  /*     TECHNIQUE. */

  /*  ***  PARAMETER DESCRIPTION  *** */

  /*      D (IN)  = THE SCALE VECTOR. */
  /*      G (IN)  = THE GRADIENT VECTOR (J**T)*R. */
  /*   IERR (I/O) = RETURN CODE FROM QRFACT OR DQ7RGS -- 0 MEANS R HAS */
  /*             FULL RANK. */
  /* IPIVOT (I/O) = PERMUTATION ARRAY FROM QRFACT OR DQ7RGS, WHICH COMPUTE */
  /*             QR DECOMPOSITIONS WITH COLUMN PIVOTING. */
  /*     KA (I/O).  KA .LT. 0 ON INPUT MEANS THIS IS THE FIRST CALL ON */
  /*             DL7MST FOR THE CURRENT R AND QTR.  ON OUTPUT KA CON- */
  /*             TAINS THE NUMBER OF HEBDEN ITERATIONS NEEDED TO DETERMINE */
  /*             STEP.  KA = 0 MEANS A GAUSS-NEWTON STEP. */
  /*      P (IN)  = NUMBER OF PARAMETERS. */
  /*    QTR (IN)  = (Q**T)*RESID = Q-TRANSPOSE TIMES THE RESIDUAL VECTOR. */
  /*      R (IN)  = THE R MATRIX, STORED COMPACTLY BY COLUMNS. */
  /*   STEP (OUT) = THE LEVENBERG-MARQUARDT STEP COMPUTED. */
  /*      V (I/O) CONTAINS VARIOUS CONSTANTS AND VARIABLES DESCRIBED BELOW. */
  /*      W (I/O) = WORKSPACE OF LENGTH P*(P+5)/2 + 4. */

  /*  ***  ENTRIES IN V  *** */

  /* V(DGNORM) (I/O) = 2-NORM OF (D**-1)*G. */
  /* V(DSTNRM) (I/O) = 2-NORM OF D*STEP. */
  /* V(DST0)   (I/O) = 2-NORM OF GAUSS-NEWTON STEP (FOR NONSING. J). */
  /* V(EPSLON) (IN) = MAX. REL. ERROR ALLOWED IN TWONORM(R)**2 MINUS */
  /*             TWONORM(R - J*STEP)**2.  (SEE ALGORITHM NOTES BELOW.) */
  /* V(GTSTEP) (OUT) = INNER PRODUCT BETWEEN G AND STEP. */
  /* V(NREDUC) (OUT) = HALF THE REDUCTION IN THE SUM OF SQUARES PREDICTED */
  /*             FOR A GAUSS-NEWTON STEP. */
  /* V(PHMNFC) (IN)  = TOL. (TOGETHER WITH V(PHMXFC)) FOR ACCEPTING STEP */
  /*             (MORE*S SIGMA).  THE ERROR V(DSTNRM) - V(RADIUS) MUST LIE */
  /*             BETWEEN V(PHMNFC)*V(RADIUS) AND V(PHMXFC)*V(RADIUS). */
  /* V(PHMXFC) (IN)  (SEE V(PHMNFC).) */
  /* V(PREDUC) (OUT) = HALF THE REDUCTION IN THE SUM OF SQUARES PREDICTED */
  /*             BY THE STEP RETURNED. */
  /* V(RADIUS) (IN)  = RADIUS OF CURRENT (SCALED) TRUST REGION. */
  /* V(RAD0)   (I/O) = VALUE OF V(RADIUS) FROM PREVIOUS CALL. */
  /* V(STPPAR) (I/O) = MARQUARDT PARAMETER (OR ITS NEGATIVE IF THE SPECIAL */
  /*             CASE MENTIONED BELOW IN THE ALGORITHM NOTES OCCURS). */

  /* NOTE -- SEE DATA STATEMENT BELOW FOR VALUES OF ABOVE SUBSCRIPTS. */

  /*  ***  USAGE NOTES  *** */

  /*     IF IT IS DESIRED TO RECOMPUTE STEP USING A DIFFERENT VALUE OF */
  /*     V(RADIUS), THEN THIS ROUTINE MAY BE RESTARTED BY CALLING IT */
  /*     WITH ALL PARAMETERS UNCHANGED EXCEPT V(RADIUS).  (THIS EXPLAINS */
  /*     WHY MANY PARAMETERS ARE LISTED AS I/O).  ON AN INTIIAL CALL (ONE */
  /*     WITH KA = -1), THE CALLER NEED ONLY HAVE INITIALIZED D, G, KA, P, */
  /*     QTR, R, V(EPSLON), V(PHMNFC), V(PHMXFC), V(RADIUS), AND V(RAD0). */

  /*  ***  APPLICATION AND USAGE RESTRICTIONS  *** */

  /*     THIS ROUTINE IS CALLED AS PART OF THE NL2SOL (NONLINEAR LEAST- */
  /*     SQUARES) PACKAGE (REF. 1). */

  /*  ***  ALGORITHM NOTES  *** */

  /*     THIS CODE IMPLEMENTS THE STEP COMPUTATION SCHEME DESCRIBED IN */
  /*     REFS. 2 AND 4.  FAST GIVENS TRANSFORMATIONS (SEE REF. 3, PP. 60- */
  /*     62) ARE USED TO COMPUTE STEP WITH A NONZERO MARQUARDT PARAMETER. */
  /*        A SPECIAL CASE OCCURS IF J IS (NEARLY) SINGULAR AND V(RADIUS) */
  /*     IS SUFFICIENTLY LARGE.  IN THIS CASE THE STEP RETURNED IS SUCH */
  /*     THAT  TWONORM(R)**2 - TWONORM(R - J*STEP)**2  DIFFERS FROM ITS */
  /*     OPTIMAL VALUE BY LESS THAN V(EPSLON) TIMES THIS OPTIMAL VALUE, */
  /*     WHERE J AND R DENOTE THE ORIGINAL JACOBIAN AND RESIDUAL.  (SEE */
  /*     REF. 2 FOR MORE DETAILS.) */

  /*  ***  FUNCTIONS AND SUBROUTINES CALLED  *** */

  /* DD7TPR - RETURNS INNER PRODUCT OF TWO VECTORS. */
  /* DL7ITV - APPLY INVERSE-TRANSPOSE OF COMPACT LOWER TRIANG. MATRIX. */
  /* DL7IVM - APPLY INVERSE OF COMPACT LOWER TRIANG. MATRIX. */
  /* DV7CPY  - COPIES ONE VECTOR TO ANOTHER. */
  /* DV2NRM - RETURNS 2-NORM OF A VECTOR. */

  /*  ***  REFERENCES  *** */

  /* 1.  DENNIS, J.E., GAY, D.M., AND WELSCH, R.E. (1981), AN ADAPTIVE */
  /*             NONLINEAR LEAST-SQUARES ALGORITHM, ACM TRANS. MATH. */
  /*             SOFTWARE, VOL. 7, NO. 3. */
  /* 2.  GAY, D.M. (1981), COMPUTING OPTIMAL LOCALLY CONSTRAINED STEPS, */
  /*             SIAM J. SCI. STATIST. COMPUTING, VOL. 2, NO. 2, PP. */
  /*             186-197. */
  /* 3.  LAWSON, C.L., AND HANSON, R.J. (1974), SOLVING LEAST SQUARES */
  /*             PROBLEMS, PRENTICE-HALL, ENGLEWOOD CLIFFS, N.J. */
  /* 4.  MORE, J.J. (1978), THE LEVENBERG-MARQUARDT ALGORITHM, IMPLEMEN- */
  /*             TATION AND THEORY, PP.105-116 OF SPRINGER LECTURE NOTES */
  /*             IN MATHEMATICS NO. 630, EDITED BY G.A. WATSON, SPRINGER- */
  /*             VERLAG, BERLIN AND NEW YORK. */

  /*  ***  GENERAL  *** */

  /*     CODED BY DAVID M. GAY. */
  /*     THIS SUBROUTINE WAS WRITTEN IN CONNECTION WITH RESEARCH */
  /*     SUPPORTED BY THE NATIONAL SCIENCE FOUNDATION UNDER GRANTS */
  /*     MCS-7600324, DCR75-10143, 76-14311DSS, MCS76-11989, AND */
  /*     MCS-7906671. */

  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

  /*  ***  LOCAL VARIABLES  *** */

  /*     ***  CONSTANTS  *** */

  /*  ***  INTRINSIC FUNCTIONS  *** */
  /* /+ */
  /* / */
  /*  ***  EXTERNAL FUNCTIONS AND SUBROUTINES  *** */

  /*  ***  SUBSCRIPTS FOR V  *** */

  /* /6 */
  /*     DATA DGNORM/1/, DSTNRM/2/, DST0/3/, EPSLON/19/, GTSTEP/4/, */
  /*    1     NREDUC/6/, PHMNFC/20/, PHMXFC/21/, PREDUC/7/, RADIUS/8/, */
  /*    2     RAD0/9/, STPPAR/5/ */
  /* /7 */
  /* / */

  /* /6 */
  /*     DATA DFAC/256.D+0/, EIGHT/8.D+0/, HALF/0.5D+0/, NEGONE/-1.D+0/, */
  /*    1     ONE/1.D+0/, P001/1.D-3/, THREE/3.D+0/, TTOL/2.5D+0/, */
  /*    2     ZERO/0.D+0/ */
  /* /7 */
  /* / */
  /* Parameter adjustments */
  --step;
  --qtr;
  --ipivot;
  --g;
  --d__;
  --r__;
  --v;
  --w;

  /* Function Body */

  /*  ***  BODY  *** */

  /*     ***  FOR USE IN RECOMPUTING STEP, THE FINAL VALUES OF LK AND UK, */
  /*     ***  THE INVERSE DERIVATIVE OF MORE*S PHI AT 0 (FOR NONSING. J) */
  /*     ***  AND THE VALUE RETURNED AS V(DSTNRM) ARE STORED AT W(LK0), */
  /*     ***  W(UK0), W(PHIPIN), AND W(DSTSAV) RESPECTIVELY. */
  lk0 = *p + 1;
  phipin = lk0 + 1;
  uk0 = phipin + 1;
  dstsav = uk0 + 1;
  rmat0 = dstsav;
  /*     ***  A COPY OF THE R-MATRIX FROM THE QR DECOMPOSITION OF J IS */
  /*     ***  STORED IN W STARTING AT W(RMAT), AND A COPY OF THE RESIDUAL */
  /*     ***  VECTOR IS STORED IN W STARTING AT W(RES).  THE LOOPS BELOW */
  /*     ***  THAT UPDATE THE QR DECOMP. FOR A NONZERO MARQUARDT PARAMETER */
  /*     ***  WORK ON THESE COPIES. */
  rmat = rmat0 + 1;
  pp1o2 = *p * (*p + 1) / 2;
  res0 = pp1o2 + rmat0;
  res = res0 + 1;
  rad = v[8];

  if (rad > 0.)
    {
      /* Computing 2nd power */
      d__1 = rad;
      psifac = v[19] / (((v[20] + 1.) * 8. + 3.) * (d__1 * d__1));
    }

  if (big <= 0.)
    {
      big = dr7mdc_(&c__6);
    }

  phimax = v[21] * rad;
  phimin = v[20] * rad;
  /*     ***  DTOL, DFAC, AND DFACSQ ARE USED IN RESCALING THE FAST GIVENS */
  /*     ***  REPRESENTATION OF THE UPDATED QR DECOMPOSITION. */
  dtol = .00390625;
  dfacsq = 65536.;
  /*     ***  OLDPHI IS USED TO DETECT LIMITS OF NUMERICAL ACCURACY.  IF */
  /*     ***  WE RECOMPUTE STEP AND IT DOES NOT CHANGE, THEN WE ACCEPT IT. */
  oldphi = 0.;
  lk = 0.;
  uk = 0.;
  kalim = *ka + 12;

  /*  ***  START OR RESTART, DEPENDING ON KA  *** */

  if (*ka < 0)
    {
      goto L10;
    }
  else if (*ka == 0)
    {
      goto L20;
    }
  else
    {
      goto L370;
    }

  /*  ***  FRESH START -- COMPUTE V(NREDUC)  *** */

L10:
  *ka = 0;
  kalim = 12;
  k = *p;

  if (*ierr != 0)
    {
      k = abs(*ierr) - 1;
    }

  v[6] = dd7tpr_(&k, &qtr[1], &qtr[1]) * .5;

  /*  ***  SET UP TO TRY INITIAL GAUSS-NEWTON STEP  *** */

L20:
  v[3] = -1.;

  if (*ierr != 0)
    {
      goto L90;
    }

  t = dl7svn_(p, &r__[1], &step[1], &w[res]);

  if (t >= 1.)
    {
      goto L30;
    }

  if (dv2nrm_(p, &qtr[1]) >= big * t)
    {
      goto L90;
    }

  /*  ***  COMPUTE GAUSS-NEWTON STEP  *** */

  /*     ***  NOTE -- THE R-MATRIX IS STORED COMPACTLY BY COLUMNS IN */
  /*     ***  R(1), R(2), R(3), ...  IT IS THE TRANSPOSE OF A */
  /*     ***  LOWER TRIANGULAR MATRIX STORED COMPACTLY BY ROWS, AND WE */
  /*     ***  TREAT IT AS SUCH WHEN USING DL7ITV AND DL7IVM. */
L30:
  dl7itv_(p, &w[1], &r__[1], &qtr[1]);
  /*     ***  TEMPORARILY STORE PERMUTED -D*STEP IN STEP. */
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j1 = ipivot[i__];
      step[i__] = d__[j1] * w[i__];
      /* L60: */
    }

  dst = dv2nrm_(p, &step[1]);
  v[3] = dst;
  phi = dst - rad;

  if (phi <= phimax)
    {
      goto L410;
    }

  /*     ***  IF THIS IS A RESTART, GO TO 110  *** */
  if (*ka > 0)
    {
      goto L110;
    }

  /*  ***  GAUSS-NEWTON STEP WAS UNACCEPTABLE.  COMPUTE L0  *** */

  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j1 = ipivot[i__];
      step[i__] = d__[j1] * (step[i__] / dst);
      /* L70: */
    }

  dl7ivm_(p, &step[1], &r__[1], &step[1]);
  t = 1. / dv2nrm_(p, &step[1]);
  w[phipin] = t / rad * t;
  lk = phi * w[phipin];

  /*  ***  COMPUTE U0  *** */

L90:
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L100: */
      w[i__] = g[i__] / d__[i__];
    }

  v[1] = dv2nrm_(p, &w[1]);
  uk = v[1] / rad;

  if (uk <= 0.)
    {
      goto L390;
    }

  /*     ***  ALPHAK WILL BE USED AS THE CURRENT MARQUARDT PARAMETER.  WE */
  /*     ***  USE MORE*S SCHEME FOR INITIALIZING IT. */

  alphak = fabs(v[5]) * v[9] / rad;
  /* Computing MIN */
  d__1 = uk, d__2 = fmax(alphak, lk);
  alphak = fmin(d__1, d__2);

  /*  ***  TOP OF LOOP -- INCREMENT KA, COPY R TO RMAT, QTR TO RES  *** */

L110:
  ++(*ka);
  dv7cpy_(&pp1o2, &w[rmat], &r__[1]);
  dv7cpy_(p, &w[res], &qtr[1]);

  /*  ***  SAFEGUARD ALPHAK AND INITIALIZE FAST GIVENS SCALE VECTOR.  *** */

  if (alphak <= 0. || alphak < lk || alphak >= uk)
    {
      /* Computing MAX */
      d__1 = .001, d__2 = sqrt(lk / uk);
      alphak = uk * fmax(d__1, d__2);
    }

  if (alphak <= 0.)
    {
      alphak = uk * .5;
    }

  sqrtak = sqrt(alphak);
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L120: */
      w[i__] = 1.;
    }

  /*  ***  ADD ALPHAK*D AND UPDATE QR DECOMP. USING FAST GIVENS TRANS.  *** */

  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /*        ***  GENERATE, APPLY 1ST GIVENS TRANS. FOR ROW I OF ALPHAK*D. */
      /*        ***  (USE STEP TO STORE TEMPORARY ROW)  *** */
      l = i__ * (i__ + 1) / 2 + rmat0;
      wl = w[l];
      d2 = 1.;
      d1 = w[i__];
      j1 = ipivot[i__];
      adi = sqrtak * d__[j1];

      if (adi >= fabs(wl))
        {
          goto L150;
        }

L130:
      a = adi / wl;
      b = d2 * a / d1;
      t = a * b + 1.;

      if (t > 2.5)
        {
          goto L150;
        }

      w[i__] = d1 / t;
      d2 /= t;
      w[l] = t * wl;
      a = -a;
      i__2 = *p;

      for (j1 = i__; j1 <= i__2; ++j1)
        {
          l += j1;
          step[j1] = a * w[l];
          /* L140: */
        }

      goto L170;

L150:
      b = wl / adi;
      a = d1 * b / d2;
      t = a * b + 1.;

      if (t > 2.5)
        {
          goto L130;
        }

      w[i__] = d2 / t;
      d2 = d1 / t;
      w[l] = t * adi;
      i__2 = *p;

      for (j1 = i__; j1 <= i__2; ++j1)
        {
          l += j1;
          wl = w[l];
          step[j1] = -wl;
          w[l] = a * wl;
          /* L160: */
        }

L170:

      if (i__ == *p)
        {
          goto L280;
        }

      /*        ***  NOW USE GIVENS TRANS. TO ZERO ELEMENTS OF TEMP. ROW  *** */

      ip1 = i__ + 1;
      i__2 = *p;

      for (i1 = ip1; i1 <= i__2; ++i1)
        {
          si = step[i1 - 1];

          if (si == 0.)
            {
              goto L260;
            }

          l = i1 * (i1 + 1) / 2 + rmat0;
          wl = w[l];
          d1 = w[i1];

          /*             ***  RESCALE ROW I1 IF NECESSARY  *** */

          if (d1 >= dtol)
            {
              goto L190;
            }

          d1 *= dfacsq;
          wl /= 256.;
          k = l;
          i__3 = *p;

          for (j1 = i1; j1 <= i__3; ++j1)
            {
              k += j1;
              w[k] /= 256.;
              /* L180: */
            }

          /*             ***  USE GIVENS TRANS. TO ZERO NEXT ELEMENT OF TEMP. ROW */

L190:

          if (fabs(si) > fabs(wl))
            {
              goto L220;
            }

L200:
          a = si / wl;
          b = d2 * a / d1;
          t = a * b + 1.;

          if (t > 2.5)
            {
              goto L220;
            }

          w[l] = t * wl;
          w[i1] = d1 / t;
          d2 /= t;
          i__3 = *p;

          for (j1 = i1; j1 <= i__3; ++j1)
            {
              l += j1;
              wl = w[l];
              sj = step[j1];
              w[l] = wl + b * sj;
              step[j1] = sj - a * wl;
              /* L210: */
            }

          goto L240;

L220:
          b = wl / si;
          a = d1 * b / d2;
          t = a * b + 1.;

          if (t > 2.5)
            {
              goto L200;
            }

          w[i1] = d2 / t;
          d2 = d1 / t;
          w[l] = t * si;
          i__3 = *p;

          for (j1 = i1; j1 <= i__3; ++j1)
            {
              l += j1;
              wl = w[l];
              sj = step[j1];
              w[l] = a * wl + sj;
              step[j1] = b * sj - wl;
              /* L230: */
            }

          /*             ***  RESCALE TEMP. ROW IF NECESSARY  *** */

L240:

          if (d2 >= dtol)
            {
              goto L260;
            }

          d2 *= dfacsq;
          i__3 = *p;

          for (k = i1; k <= i__3; ++k)
            {
              /* L250: */
              step[k] /= 256.;
            }

L260:
          ;
        }

      /* L270: */
    }

  /*  ***  COMPUTE STEP  *** */

L280:
  dl7itv_(p, &w[res], &w[rmat], &w[res]);
  /*     ***  RECOVER STEP AND STORE PERMUTED -D*STEP AT W(RES)  *** */
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j1 = ipivot[i__];
      k = res0 + i__;
      t = w[k];
      step[j1] = -t;
      w[k] = t * d__[j1];
      /* L290: */
    }

  dst = dv2nrm_(p, &w[res]);
  phi = dst - rad;

  if (phi <= phimax && phi >= phimin)
    {
      goto L430;
    }

  if (oldphi == phi)
    {
      goto L430;
    }

  oldphi = phi;

  /*  ***  CHECK FOR (AND HANDLE) SPECIAL CASE  *** */

  if (phi > 0.)
    {
      goto L310;
    }

  if (*ka >= kalim)
    {
      goto L430;
    }

  twopsi = alphak * dst * dst - dd7tpr_(p, &step[1], &g[1]);

  if (alphak >= twopsi * psifac)
    {
      goto L310;
    }

  v[5] = -alphak;
  goto L440;

  /*  ***  UNACCEPTABLE STEP -- UPDATE LK, UK, ALPHAK, AND TRY AGAIN  *** */

L300:

  if (phi < 0.)
    {
      uk = fmin(uk, alphak);
    }

  goto L320;

L310:

  if (phi < 0.)
    {
      uk = alphak;
    }

L320:
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j1 = ipivot[i__];
      k = res0 + i__;
      step[i__] = d__[j1] * (w[k] / dst);
      /* L330: */
    }

  dl7ivm_(p, &step[1], &w[rmat], &step[1]);
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L340: */
      step[i__] /= sqrt(w[i__]);
    }

  t = 1. / dv2nrm_(p, &step[1]);
  alphak += t * phi * t / rad;
  lk = fmax(lk, alphak);
  alphak = lk;
  goto L110;

  /*  ***  RESTART  *** */

L370:
  lk = w[lk0];
  uk = w[uk0];

  if (v[3] > 0. && v[3] - rad <= phimax)
    {
      goto L20;
    }

  alphak = fabs(v[5]);
  dst = w[dstsav];
  phi = dst - rad;
  t = v[1] / rad;

  if (rad > v[9])
    {
      goto L380;
    }

  /*        ***  SMALLER RADIUS  *** */
  uk = t;

  if (alphak <= 0.)
    {
      lk = 0.;
    }

  if (v[3] > 0.)
    {
      /* Computing MAX */
      d__1 = lk, d__2 = (v[3] - rad) * w[phipin];
      lk = fmax(d__1, d__2);
    }

  goto L300;

  /*     ***  BIGGER RADIUS  *** */
L380:

  if (alphak <= 0. || uk > t)
    {
      uk = t;
    }

  lk = 0.;

  if (v[3] > 0.)
    {
      /* Computing MAX */
      d__1 = lk, d__2 = (v[3] - rad) * w[phipin];
      lk = fmax(d__1, d__2);
    }

  goto L300;

  /*  ***  SPECIAL CASE -- RAD .LE. 0 OR (G = 0 AND J IS SINGULAR)  *** */

L390:
  v[5] = 0.;
  dst = 0.;
  lk = 0.;
  uk = 0.;
  v[4] = 0.;
  v[7] = 0.;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L400: */
      step[i__] = 0.;
    }

  goto L450;

  /*  ***  ACCEPTABLE GAUSS-NEWTON STEP -- RECOVER STEP FROM W  *** */

L410:
  alphak = 0.;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j1 = ipivot[i__];
      step[j1] = -w[i__];
      /* L420: */
    }

  /*  ***  SAVE VALUES FOR USE IN A POSSIBLE RESTART  *** */

L430:
  v[5] = alphak;

L440:
  /* Computing MIN */
  d__1 = dd7tpr_(p, &step[1], &g[1]);
  v[4] = fmin(d__1, 0.);
  v[7] = (alphak * dst * dst - v[4]) * .5;

L450:
  v[2] = dst;
  w[dstsav] = dst;
  w[lk0] = lk;
  w[uk0] = uk;
  v[9] = rad;

  /* L999: */
  return 0;

  /*  ***  LAST CARD OF DL7MST FOLLOWS  *** */
} /* dl7mst_ */

int dl7sqr_(integer *n, doublereal *a, doublereal *l)
{
  /* System generated locals */
  integer i__1, i__2, i__3;

  /* Local variables */
  static integer i__, j, k;
  static doublereal t;
  static integer i0, j0, ii, ij, ik, jj, jk, ip1, np1;

  /*  ***  COMPUTE  A = LOWER TRIANGLE OF  L*(L**T),  WITH BOTH */
  /*  ***  L  AND  A  STORED COMPACTLY BY ROWS.  (BOTH MAY OCCUPY THE */
  /*  ***  SAME STORAGE. */

  /*  ***  PARAMETERS  *** */

  /*     DIMENSION A(N*(N+1)/2), L(N*(N+1)/2) */

  /*  ***  LOCAL VARIABLES  *** */

  /* Parameter adjustments */
  --l;
  --a;

  /* Function Body */
  np1 = *n + 1;
  i0 = *n * (*n + 1) / 2;
  i__1 = *n;

  for (ii = 1; ii <= i__1; ++ii)
    {
      i__ = np1 - ii;
      ip1 = i__ + 1;
      i0 -= i__;
      j0 = i__ * (i__ + 1) / 2;
      i__2 = i__;

      for (jj = 1; jj <= i__2; ++jj)
        {
          j = ip1 - jj;
          j0 -= j;
          t = 0.;
          i__3 = j;

          for (k = 1; k <= i__3; ++k)
            {
              ik = i0 + k;
              jk = j0 + k;
              t += l[ik] * l[jk];
              /* L10: */
            }

          ij = i0 + j;
          a[ij] = t;
          /* L20: */
        }

      /* L30: */
    }

  /* L999: */
  return 0;
} /* dl7sqr_ */

int dl7srt_(integer *n1, integer *n, doublereal *l,
            doublereal *a, integer *irc)
{
  /* System generated locals */
  integer i__1, i__2, i__3;

  /* Local variables */
  static integer i__, j, k;
  static doublereal t;
  static integer i0, j0, ij, ik, jk;
  static doublereal td;
  static integer im1, jm1;

  /*  ***  COMPUTE ROWS N1 THROUGH N OF THE CHOLESKY FACTOR  L  OF */
  /*  ***  A = L*(L**T),  WHERE  L  AND THE LOWER TRIANGLE OF  A  ARE BOTH */
  /*  ***  STORED COMPACTLY BY ROWS (AND MAY OCCUPY THE SAME STORAGE). */
  /*  ***  IRC = 0 MEANS ALL WENT WELL.  IRC = J MEANS THE LEADING */
  /*  ***  PRINCIPAL  J X J  SUBMATRIX OF  A  IS NOT POSITIVE DEFINITE -- */
  /*  ***  AND  L(J*(J+1)/2)  CONTAINS THE (NONPOS.) REDUCED J-TH DIAGONAL. */

  /*  ***  PARAMETERS  *** */

  /*     DIMENSION L(N*(N+1)/2), A(N*(N+1)/2) */

  /*  ***  LOCAL VARIABLES  *** */

  /*  ***  INTRINSIC FUNCTIONS  *** */
  /* /+ */
  /* / */
  /* /6 */
  /*     DATA ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /*  ***  BODY  *** */

  /* Parameter adjustments */
  --a;
  --l;

  /* Function Body */
  i0 = *n1 * (*n1 - 1) / 2;
  i__1 = *n;

  for (i__ = *n1; i__ <= i__1; ++i__)
    {
      td = 0.;

      if (i__ == 1)
        {
          goto L40;
        }

      j0 = 0;
      im1 = i__ - 1;
      i__2 = im1;

      for (j = 1; j <= i__2; ++j)
        {
          t = 0.;

          if (j == 1)
            {
              goto L20;
            }

          jm1 = j - 1;
          i__3 = jm1;

          for (k = 1; k <= i__3; ++k)
            {
              ik = i0 + k;
              jk = j0 + k;
              t += l[ik] * l[jk];
              /* L10: */
            }

L20:
          ij = i0 + j;
          j0 += j;
          t = (a[ij] - t) / l[j0];
          l[ij] = t;
          td += t * t;
          /* L30: */
        }

L40:
      i0 += i__;
      t = a[i0] - td;

      if (t <= 0.)
        {
          goto L60;
        }

      l[i0] = sqrt(t);
      /* L50: */
    }

  *irc = 0;
  goto L999;

L60:
  l[i0] = t;
  *irc = i__;

L999:
  return 0;

  /*  ***  LAST CARD OF DL7SRT  *** */
} /* dl7srt_ */

doublereal dl7svn_(integer *p, doublereal *l, doublereal *x, doublereal *y)
{
  /* System generated locals */
  integer i__1, i__2;
  doublereal ret_val, d__1;

  /* Local variables */
  static doublereal b;
  static integer i__, j;
  static doublereal t;
  static integer j0;
  static doublereal splus, xplus;
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *),
         dv2nrm_(integer *, doublereal *);
  extern int dv2axy_(integer *, doublereal *, doublereal *,
                     doublereal *, doublereal *);
  static integer ii, ji, jj, ix, jm1, pm1;
  static doublereal sminus, xminus;
  static integer jjj;

  /*  ***  ESTIMATE SMALLEST SING. VALUE OF PACKED LOWER TRIANG. MATRIX L */

  /*  ***  PARAMETER DECLARATIONS  *** */

  /*     DIMENSION L(P*(P+1)/2) */

  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

  /*  ***  PURPOSE  *** */

  /*     THIS FUNCTION RETURNS A GOOD OVER-ESTIMATE OF THE SMALLEST */
  /*     SINGULAR VALUE OF THE PACKED LOWER TRIANGULAR MATRIX L. */

  /*  ***  PARAMETER DESCRIPTION  *** */

  /*  P (IN)  = THE ORDER OF L.  L IS A  P X P  LOWER TRIANGULAR MATRIX. */
  /*  L (IN)  = ARRAY HOLDING THE ELEMENTS OF  L  IN ROW ORDER, I.E. */
  /*             L(1,1), L(2,1), L(2,2), L(3,1), L(3,2), L(3,3), ETC. */
  /*  X (OUT) IF DL7SVN RETURNS A POSITIVE VALUE, THEN X IS A NORMALIZED */
  /*             APPROXIMATE LEFT SINGULAR VECTOR CORRESPONDING TO THE */
  /*             SMALLEST SINGULAR VALUE.  THIS APPROXIMATION MAY BE VERY */
  /*             CRUDE.  IF DL7SVN RETURNS ZERO, THEN SOME COMPONENTS OF X */
  /*             ARE ZERO AND THE REST RETAIN THEIR INPUT VALUES. */
  /*  Y (OUT) IF DL7SVN RETURNS A POSITIVE VALUE, THEN Y = (L**-1)*X IS AN */
  /*             UNNORMALIZED APPROXIMATE RIGHT SINGULAR VECTOR CORRESPOND- */
  /*             ING TO THE SMALLEST SINGULAR VALUE.  THIS APPROXIMATION */
  /*             MAY BE CRUDE.  IF DL7SVN RETURNS ZERO, THEN Y RETAINS ITS */
  /*             INPUT VALUE.  THE CALLER MAY PASS THE SAME VECTOR FOR X */
  /*             AND Y (NONSTANDARD FORTRAN USAGE), IN WHICH CASE Y OVER- */
  /*             WRITES X (FOR NONZERO DL7SVN RETURNS). */

  /*  ***  ALGORITHM NOTES  *** */

  /*     THE ALGORITHM IS BASED ON (1), WITH THE ADDITIONAL PROVISION THAT */
  /*     DL7SVN = 0 IS RETURNED IF THE SMALLEST DIAGONAL ELEMENT OF L */
  /*     (IN MAGNITUDE) IS NOT MORE THAN THE UNIT ROUNDOFF TIMES THE */
  /*     LARGEST.  THE ALGORITHM USES A RANDOM NUMBER GENERATOR PROPOSED */
  /*     IN (4), WHICH PASSES THE SPECTRAL TEST WITH FLYING COLORS -- SEE */
  /*     (2) AND (3). */

  /*  ***  SUBROUTINES AND FUNCTIONS CALLED  *** */

  /*        DV2NRM - FUNCTION, RETURNS THE 2-NORM OF A VECTOR. */

  /*  ***  REFERENCES  *** */

  /*     (1) CLINE, A., MOLER, C., STEWART, G., AND WILKINSON, J.H.(1977), */
  /*         AN ESTIMATE FOR THE CONDITION NUMBER OF A MATRIX, REPORT */
  /*         TM-310, APPLIED MATH. DIV., ARGONNE NATIONAL LABORATORY. */

  /*     (2) HOAGLIN, D.C. (1976), THEORETICAL PROPERTIES OF CONGRUENTIAL */
  /*         RANDOM-NUMBER GENERATORS --  AN EMPIRICAL VIEW, */
  /*         MEMORANDUM NS-340, DEPT. OF STATISTICS, HARVARD UNIV. */

  /*     (3) KNUTH, D.E. (1969), THE ART OF COMPUTER PROGRAMMING, VOL. 2 */
  /*         (SEMINUMERICAL ALGORITHMS), ADDISON-WESLEY, READING, MASS. */

  /*     (4) SMITH, C.S. (1971), MULTIPLICATIVE PSEUDO-RANDOM NUMBER */
  /*         GENERATORS WITH PRIME MODULUS, J. ASSOC. COMPUT. MACH. 18, */
  /*         PP. 586-593. */

  /*  ***  HISTORY  *** */

  /*     DESIGNED AND CODED BY DAVID M. GAY (WINTER 1977/SUMMER 1978). */

  /*  ***  GENERAL  *** */

  /*     THIS SUBROUTINE WAS WRITTEN IN CONNECTION WITH RESEARCH */
  /*     SUPPORTED BY THE NATIONAL SCIENCE FOUNDATION UNDER GRANTS */
  /*     MCS-7600324, DCR75-10143, 76-14311DSS, AND MCS76-11989. */

  /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

  /*  ***  LOCAL VARIABLES  *** */

  /*  ***  CONSTANTS  *** */

  /*  ***  EXTERNAL FUNCTIONS AND SUBROUTINES  *** */

  /* /6 */
  /*     DATA HALF/0.5D+0/, ONE/1.D+0/, R9973/9973.D+0/, ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /*  ***  BODY  *** */

  /* Parameter adjustments */
  --y;
  --x;
  --l;

  /* Function Body */
  ix = 2;
  pm1 = *p - 1;

  /*  ***  FIRST CHECK WHETHER TO RETURN DL7SVN = 0 AND INITIALIZE X  *** */

  ii = 0;
  j0 = *p * pm1 / 2;
  jj = j0 + *p;

  if (l[jj] == 0.)
    {
      goto L110;
    }

  ix = ix * 3432 % 9973;
  b = ((real) ix / 9973. + 1.) * .5;
  xplus = b / l[jj];
  x[*p] = xplus;

  if (*p <= 1)
    {
      goto L60;
    }

  i__1 = pm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      ii += i__;

      if (l[ii] == 0.)
        {
          goto L110;
        }

      ji = j0 + i__;
      x[i__] = xplus * l[ji];
      /* L10: */
    }

  /*  ***  SOLVE (L**T)*X = B, WHERE THE COMPONENTS OF B HAVE RANDOMLY */
  /*  ***  CHOSEN MAGNITUDES IN (.5,1) WITH SIGNS CHOSEN TO MAKE X LARGE. */

  /*     DO J = P-1 TO 1 BY -1... */
  i__1 = pm1;

  for (jjj = 1; jjj <= i__1; ++jjj)
    {
      j = *p - jjj;
      /*       ***  DETERMINE X(J) IN THIS ITERATION. NOTE FOR I = 1,2,...,J */
      /*       ***  THAT X(I) HOLDS THE CURRENT PARTIAL SUM FOR ROW I. */
      ix = ix * 3432 % 9973;
      b = ((real) ix / 9973. + 1.) * .5;
      xplus = b - x[j];
      xminus = -b - x[j];
      splus = fabs(xplus);
      sminus = fabs(xminus);
      jm1 = j - 1;
      j0 = j * jm1 / 2;
      jj = j0 + j;
      xplus /= l[jj];
      xminus /= l[jj];

      if (jm1 == 0)
        {
          goto L30;
        }

      i__2 = jm1;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          ji = j0 + i__;
          splus += (d__1 = x[i__] + l[ji] * xplus, fabs(d__1));
          sminus += (d__1 = x[i__] + l[ji] * xminus, fabs(d__1));
          /* L20: */
        }

L30:

      if (sminus > splus)
        {
          xplus = xminus;
        }

      x[j] = xplus;

      /*       ***  UPDATE PARTIAL SUMS  *** */
      if (jm1 > 0)
        {
          dv2axy_(&jm1, &x[1], &xplus, &l[j0 + 1], &x[1]);
        }

      /* L50: */
    }

  /*  ***  NORMALIZE X  *** */

L60:
  t = 1. / dv2nrm_(p, &x[1]);
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L70: */
      x[i__] = t * x[i__];
    }

  /*  ***  SOLVE L*Y = X AND RETURN DL7SVN = 1/TWONORM(Y)  *** */

  i__1 = *p;

  for (j = 1; j <= i__1; ++j)
    {
      jm1 = j - 1;
      j0 = j * jm1 / 2;
      jj = j0 + j;
      t = 0.;

      if (jm1 > 0)
        {
          t = dd7tpr_(&jm1, &l[j0 + 1], &y[1]);
        }

      y[j] = (x[j] - t) / l[jj];
      /* L100: */
    }

  ret_val = 1. / dv2nrm_(p, &y[1]);
  goto L999;

L110:
  ret_val = 0.;

L999:
  return ret_val;
  /*  ***  LAST CARD OF DL7SVN FOLLOWS  *** */
} /* dl7svn_ */

int dl7tvm_(integer *n, doublereal *x, doublereal *l,
            doublereal *y)
{
  /* System generated locals */
  integer i__1, i__2;

  /* Local variables */
  static integer i__, j, i0, ij;
  static doublereal yi;

  /*  ***  COMPUTE  X = (L**T)*Y, WHERE  L  IS AN  N X N  LOWER */
  /*  ***  TRIANGULAR MATRIX STORED COMPACTLY BY ROWS.  X AND Y MAY */
  /*  ***  OCCUPY THE SAME STORAGE.  *** */

  /*     DIMENSION L(N*(N+1)/2) */
  /* /6 */
  /*     DATA ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /* Parameter adjustments */
  --y;
  --x;
  --l;

  /* Function Body */
  i0 = 0;
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      yi = y[i__];
      x[i__] = 0.;
      i__2 = i__;

      for (j = 1; j <= i__2; ++j)
        {
          ij = i0 + j;
          x[j] += yi * l[ij];
          /* L10: */
        }

      i0 += i__;
      /* L20: */
    }

  /* L999: */
  return 0;
  /*  ***  LAST CARD OF DL7TVM FOLLOWS  *** */
} /* dl7tvm_ */

int dl7vml_(integer *n, doublereal *x, doublereal *l, doublereal *y)
{
  /* System generated locals */
  integer i__1, i__2;

  /* Local variables */
  static integer i__, j;
  static doublereal t;
  static integer i0, ii, ij, np1;

  /*  ***  COMPUTE  X = L*Y, WHERE  L  IS AN  N X N  LOWER TRIANGULAR */
  /*  ***  MATRIX STORED COMPACTLY BY ROWS.  X AND Y MAY OCCUPY THE SAME */
  /*  ***  STORAGE.  *** */

  /*     DIMENSION L(N*(N+1)/2) */
  /* /6 */
  /*     DATA ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /* Parameter adjustments */
  --y;
  --x;
  --l;

  /* Function Body */
  np1 = *n + 1;
  i0 = *n * (*n + 1) / 2;
  i__1 = *n;

  for (ii = 1; ii <= i__1; ++ii)
    {
      i__ = np1 - ii;
      i0 -= i__;
      t = 0.;
      i__2 = i__;

      for (j = 1; j <= i__2; ++j)
        {
          ij = i0 + j;
          t += l[ij] * y[j];
          /* L10: */
        }

      x[i__] = t;
      /* L20: */
    }

  /* L999: */
  return 0;
  /*  ***  LAST CARD OF DL7VML FOLLOWS  *** */
} /* dl7vml_ */

int dparck_(integer *alg, doublereal *d__, integer *iv,
            integer *liv, integer *lv, integer *n, doublereal *v)
{
  /* Initialized data */

  static doublereal big = 0.;
  static doublereal machep = -1.;
  static doublereal tiny = 1.;
  static doublereal zero = 0.;
  static char vn[4 * 2 * 34] = "";

  static doublereal vm[34] = {.001, -.99, .001, .01, 1.2, .01, 1.2, 0., 0., .001,
                              -1., 0.0, 0., 0.0, 0., 0., 0.0, 0.0, 0., -10., 0., 0., 0., 0.0, 0.0, 0.0, 1.01,
                              1e10, 0.0, 0., 0., 0., 0.0, 0.
                             };
  static doublereal vx[34] = {.9, -.001, 10., .8, 100., .8, 100., .5, .5, 1., 1., 0.0,
                              0.0, .1, 1., 1., 0.0, 0.0, 1., 0.0, 0.0, 0.0, 1., 1., 1., 1., 1e10, 0.0, 1., 0.0,
                              1., 1., 1., 1.
                             };

  /*static char varnm[1*2] = "P" "P";
  static char sh[1*2] = "S" "H";
  static char cngd[4*3] = "---C" "HANG" "ED V";
  static char dflt[4*3] = "NOND" "EFAU" "LT V";*/

  static char varnm[1 * 2] = "";
  static char sh[1 * 2] = "";
  static char cngd[4 * 3] = "";
  static char dflt[4 * 3] = "";

  static integer ijmp = 33;
  static integer jlim[4] = {0, 24, 0, 24 };
  static integer ndflt[4] = {32, 25, 32, 25 };
  static integer miniv[4] = {82, 59, 103, 103 };

  /* System generated locals */
  integer i__1, i__2;

  /* Local variables */
  static integer i__, j, k, l, m;
  static char which[4 * 3];
  extern doublereal dr7mdc_(integer *);
  extern int dv7dfl_(integer *, integer *, doublereal *),
         dv7cpy_(integer *, doublereal *, doublereal *);
  static integer parsv1, ii;
  static doublereal vk;
  static integer pu, ndfalt;
  extern int divset_(integer *, integer *, integer *,
                     integer *, doublereal *);
  static integer iv1, alg1, miv1, miv2;

  /*  ***  CHECK ***SOL (VERSION 2.3) PARAMETERS, PRINT CHANGED VALUES  *** */
  /*  ***  ALG = 1 FOR REGRESSION, ALG = 2 FOR GENERAL UNCONSTRAINED OPT. */

  /* DIVSET  -- SUPPLIES DEFAULT VALUES TO BOTH IV AND V. */
  /* DR7MDC -- RETURNS MACHINE-DEPENDENT CONSTANTS. */
  /* DV7CPY  -- COPIES ONE VECTOR TO ANOTHER. */
  /* DV7DFL  -- SUPPLIES DEFAULT PARAMETER VALUES TO V ALONE. */

  /*  ***  LOCAL VARIABLES  *** */

  /* /6S */
  /*     INTEGER VARNM(2), SH(2) */
  /*     REAL CNGD(3), DFLT(3), VN(2,34), WHICH(3) */
  /* /7S */
  /* / */

  /*  ***  IV AND V SUBSCRIPTS  *** */

  /* /6 */
  /*     DATA ALGSAV/51/, DINIT/38/, DTYPE/16/, DTYPE0/54/, EPSLON/19/, */
  /*    1     INITS/25/, IVNEED/3/, LASTIV/44/, LASTV/45/, LMAT/42/, */
  /*    2     NEXTIV/46/, NEXTV/47/, NVDFLT/50/, OLDN/38/, PARPRT/20/, */
  /*    3     PARSAV/49/, PERM/58/, PRUNIT/21/, VNEED/4/ */
  /* /7 */
  /* / */

  /* Parameter adjustments */
  --iv;
  --v;
  --d__;

  /* Function Body */
  /* /6S */
  /*     DATA VN(1,1),VN(2,1)/4HEPSL,4HON../ */
  /*     DATA VN(1,2),VN(2,2)/4HPHMN,4HFC../ */
  /*     DATA VN(1,3),VN(2,3)/4HPHMX,4HFC../ */
  /*     DATA VN(1,4),VN(2,4)/4HDECF,4HAC../ */
  /*     DATA VN(1,5),VN(2,5)/4HINCF,4HAC../ */
  /*     DATA VN(1,6),VN(2,6)/4HRDFC,4HMN../ */
  /*     DATA VN(1,7),VN(2,7)/4HRDFC,4HMX../ */
  /*     DATA VN(1,8),VN(2,8)/4HTUNE,4HR1../ */
  /*     DATA VN(1,9),VN(2,9)/4HTUNE,4HR2../ */
  /*     DATA VN(1,10),VN(2,10)/4HTUNE,4HR3../ */
  /*     DATA VN(1,11),VN(2,11)/4HTUNE,4HR4../ */
  /*     DATA VN(1,12),VN(2,12)/4HTUNE,4HR5../ */
  /*     DATA VN(1,13),VN(2,13)/4HAFCT,4HOL../ */
  /*     DATA VN(1,14),VN(2,14)/4HRFCT,4HOL../ */
  /*     DATA VN(1,15),VN(2,15)/4HXCTO,4HL.../ */
  /*     DATA VN(1,16),VN(2,16)/4HXFTO,4HL.../ */
  /*     DATA VN(1,17),VN(2,17)/4HLMAX,4H0.../ */
  /*     DATA VN(1,18),VN(2,18)/4HLMAX,4HS.../ */
  /*     DATA VN(1,19),VN(2,19)/4HSCTO,4HL.../ */
  /*     DATA VN(1,20),VN(2,20)/4HDINI,4HT.../ */
  /*     DATA VN(1,21),VN(2,21)/4HDTIN,4HIT../ */
  /*     DATA VN(1,22),VN(2,22)/4HD0IN,4HIT../ */
  /*     DATA VN(1,23),VN(2,23)/4HDFAC,4H..../ */
  /*     DATA VN(1,24),VN(2,24)/4HDLTF,4HDC../ */
  /*     DATA VN(1,25),VN(2,25)/4HDLTF,4HDJ../ */
  /*     DATA VN(1,26),VN(2,26)/4HDELT,4HA0../ */
  /*     DATA VN(1,27),VN(2,27)/4HFUZZ,4H..../ */
  /*     DATA VN(1,28),VN(2,28)/4HRLIM,4HIT../ */
  /*     DATA VN(1,29),VN(2,29)/4HCOSM,4HIN../ */
  /*     DATA VN(1,30),VN(2,30)/4HHUBE,4HRC../ */
  /*     DATA VN(1,31),VN(2,31)/4HRSPT,4HOL../ */
  /*     DATA VN(1,32),VN(2,32)/4HSIGM,4HIN../ */
  /*     DATA VN(1,33),VN(2,33)/4HETA0,4H..../ */
  /*     DATA VN(1,34),VN(2,34)/4HBIAS,4H..../ */
  /* /7S */
  /* / */

  /* /6S */
  /*     DATA VARNM(1)/1HP/, VARNM(2)/1HP/, SH(1)/1HS/, SH(2)/1HH/ */
  /*     DATA CNGD(1),CNGD(2),CNGD(3)/4H---C,4HHANG,4HED V/, */
  /*    1     DFLT(1),DFLT(2),DFLT(3)/4HNOND,4HEFAU,4HLT V/ */
  /* /7S */
  /* / */

  /* ...............................  BODY  ................................
   */

  pu = 0;

  if (21 <= *liv)
    {
      pu = iv[21];
    }

  if (51 > *liv)
    {
      goto L20;
    }

  if (*alg == iv[51])
    {
      goto L20;
    }

  iv[1] = 67;
  goto L999;

L20:

  if (*alg < 1 || *alg > 4)
    {
      goto L340;
    }

  miv1 = miniv[*alg - 1];

  if (iv[1] == 15)
    {
      goto L360;
    }

  alg1 = (*alg - 1) % 2 + 1;

  if (iv[1] == 0)
    {
      divset_(alg, &iv[1], liv, lv, &v[1]);
    }

  iv1 = iv[1];

  if (iv1 != 13 && iv1 != 12)
    {
      goto L30;
    }

  if (58 <= *liv)
    {
      /* Computing MAX */
      i__1 = miv1, i__2 = iv[58] - 1;
      miv1 = std::max(i__1, i__2);
    }

  if (3 <= *liv)
    {
      miv2 = miv1 + std::max(iv[3], (integer) 0);
    }

  if (44 <= *liv)
    {
      iv[44] = miv2;
    }

  if (*liv < miv1)
    {
      goto L300;
    }

  iv[3] = 0;
  iv[45] = std::max(iv[4], (integer) 0) + iv[42] - 1;
  iv[4] = 0;

  if (*liv < miv2)
    {
      goto L300;
    }

  if (*lv < iv[45])
    {
      goto L320;
    }

L30:

  if (iv1 < 12 || iv1 > 14)
    {
      goto L60;
    }

  if (*n >= 1)
    {
      goto L50;
    }

  iv[1] = 81;

  goto L999;

L50:

  if (iv1 != 14)
    {
      iv[46] = iv[58];
    }

  if (iv1 != 14)
    {
      iv[47] = iv[42];
    }

  if (iv1 == 13)
    {
      goto L999;
    }

  k = iv[49] - 19;
  i__1 = *lv - k;
  dv7dfl_(&alg1, &i__1, &v[k + 1]);
  iv[54] = 2 - alg1;
  iv[38] = *n;
  s_copy(which, dflt, (ftnlen)4, (ftnlen)4);
  s_copy(which + 4, dflt + 4, (ftnlen)4, (ftnlen)4);
  s_copy(which + 8, dflt + 8, (ftnlen)4, (ftnlen)4);
  goto L110;

L60:

  if (*n == iv[38])
    {
      goto L80;
    }

  iv[1] = 17;

  goto L999;

L80:

  if (iv1 <= 11 && iv1 >= 1)
    {
      goto L100;
    }

  iv[1] = 80;

  goto L999;

L100:
  s_copy(which, cngd, (ftnlen)4, (ftnlen)4);
  s_copy(which + 4, cngd + 4, (ftnlen)4, (ftnlen)4);
  s_copy(which + 8, cngd + 8, (ftnlen)4, (ftnlen)4);

L110:

  if (iv1 == 14)
    {
      iv1 = 12;
    }

  if (big > tiny)
    {
      goto L120;
    }

  tiny = dr7mdc_(&c__1);
  machep = dr7mdc_(&c__3);
  big = dr7mdc_(&c__6);
  vm[11] = machep;
  vx[11] = big;
  vx[12] = big;
  vm[13] = machep;
  vm[16] = tiny;
  vx[16] = big;
  vm[17] = tiny;
  vx[17] = big;
  vx[19] = big;
  vx[20] = big;
  vx[21] = big;
  vm[23] = machep;
  vm[24] = machep;
  vm[25] = machep;
  vx[27] = dr7mdc_(&c__5);
  vm[28] = machep;
  vx[29] = big;
  vm[32] = machep;

L120:
  m = 0;
  i__ = 1;
  j = jlim[alg1 - 1];
  k = 19;
  ndfalt = ndflt[alg1 - 1];
  i__1 = ndfalt;

  for (l = 1; l <= i__1; ++l)
    {
      vk = v[k];

      if (vk >= vm[i__ - 1] && vk <= vx[i__ - 1])
        {
          goto L140;
        }

      m = k;

L140:
      ++k;
      ++i__;

      if (i__ == j)
        {
          i__ = ijmp;
        }

      /* L150: */
    }

  if (iv[50] == ndfalt)
    {
      goto L170;
    }

  iv[1] = 51;

  goto L999;

L170:

  if ((iv[16] > 0 || v[38] > zero) && iv1 == 12)
    {
      goto L200;
    }

  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      if (d__[i__] > zero)
        {
          goto L190;
        }

      m = 18;

L190:
      ;
    }

L200:

  if (m == 0)
    {
      goto L210;
    }

  iv[1] = m;
  goto L999;

L210:

  if (pu == 0 || iv[20] == 0)
    {
      goto L999;
    }

  if (iv1 != 12 || iv[25] == alg1 - 1)
    {
      goto L230;
    }

  m = 1;
L230:

  if (iv[16] == iv[54])
    {
      goto L250;
    }

  m = 1;
L250:
  i__ = 1;
  j = jlim[alg1 - 1];
  k = 19;
  l = iv[49];
  ndfalt = ndflt[alg1 - 1];
  i__1 = ndfalt;

  for (ii = 1; ii <= i__1; ++ii)
    {
      if (v[k] == v[l])
        {
          goto L280;
        }

      m = 1;

L280:
      ++k;
      ++l;
      ++i__;

      if (i__ == j)
        {
          i__ = ijmp;
        }

      /* L290: */
    }

  iv[54] = iv[16];
  parsv1 = iv[49];
  dv7cpy_(&iv[50], &v[parsv1], &v[19]);
  goto L999;

L300:
  iv[1] = 15;

  if (pu == 0)
    {
      goto L999;
    }

  if (*liv < miv1)
    {
      goto L999;
    }

  if (*lv < iv[45])
    {
      goto L320;
    }

  goto L999;

L320:
  iv[1] = 16;

  goto L999;

L340:
  iv[1] = 67;

  goto L999;

L360:

  if (44 <= *liv)
    {
      iv[44] = miv1;
    }

  if (45 <= *liv)
    {
      iv[45] = 0;
    }

L999:
  return 0;
  /*  ***  LAST LINE OF DPARCK FOLLOWS  *** */
} /* dparck_ */

int dq7apl_(integer *nn, integer *n, integer *p, doublereal * j,
            doublereal *r__, integer *ierr)
{
  /* System generated locals */
  integer j_dim1, j_offset, i__1;
  doublereal d__1;

  /* Local variables */
  static integer k, l;
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *);
  extern int dv2axy_(integer *, doublereal *, doublereal *,
                     doublereal *, doublereal *);
  static integer nl1;

  /*     *****PARAMETERS. */

  /*     .................................................................. */
  /*     .................................................................. */

  /*     *****PURPOSE. */
  /*     THIS SUBROUTINE APPLIES TO R THE ORTHOGONAL TRANSFORMATIONS */
  /*     STORED IN J BY QRFACT */

  /*     *****PARAMETER DESCRIPTION. */
  /*     ON INPUT. */

  /*        NN IS THE ROW DIMENSION OF THE MATRIX J AS DECLARED IN */
  /*             THE CALLING PROGRAM DIMENSION STATEMENT */

  /*        N IS THE NUMBER OF ROWS OF J AND THE SIZE OF THE VECTOR R */

  /*        P IS THE NUMBER OF COLUMNS OF J AND THE SIZE OF SIGMA */

  /*        J CONTAINS ON AND BELOW ITS DIAGONAL THE COLUMN VECTORS */
  /*             U WHICH DETERMINE THE HOUSEHOLDER TRANSFORMATIONS */
  /*             IDENT - U*U.TRANSPOSE */

  /*        R IS THE RIGHT HAND SIDE VECTOR TO WHICH THE ORTHOGONAL */
  /*             TRANSFORMATIONS WILL BE APPLIED */

  /*        IERR IF NON-ZERO INDICATES THAT NOT ALL THE TRANSFORMATIONS */
  /*             WERE SUCCESSFULLY DETERMINED AND ONLY THE FIRST */
  /*             ABS(IERR) - 1 TRANSFORMATIONS WILL BE USED */

  /*     ON OUTPUT. */

  /*        R HAS BEEN OVERWRITTEN BY ITS TRANSFORMED IMAGE */

  /*     *****APPLICATION AND USAGE RESTRICTIONS. */
  /*     NONE */

  /*     *****ALGORITHM NOTES. */
  /*     THE VECTORS U WHICH DETERMINE THE HOUSEHOLDER TRANSFORMATIONS */
  /*     ARE NORMALIZED SO THAT THEIR 2-NORM SQUARED IS 2.  THE USE OF */
  /*     THESE TRANSFORMATIONS HERE IS IN THE SPIRIT OF (1). */

  /*     *****SUBROUTINES AND FUNCTIONS CALLED. */

  /*     DD7TPR - FUNCTION, RETURNS THE INNER PRODUCT OF VECTORS */

  /*     *****REFERENCES. */
  /*     (1) BUSINGER, P. A., AND GOLUB, G. H. (1965), LINEAR LEAST SQUARES
   */
  /*        SOLUTIONS BY HOUSEHOLDER TRANSFORMATIONS, NUMER. MATH. 7, */
  /*        PP. 269-276. */

  /*     *****HISTORY. */
  /*     DESIGNED BY DAVID M. GAY, CODED BY STEPHEN C. PETERS (WINTER 1977)
   */
  /*     CALL ON DV2AXY SUBSTITUTED FOR DO LOOP, FALL 1983. */

  /*     *****GENERAL. */

  /*     THIS SUBROUTINE WAS WRITTEN IN CONNECTION WITH RESEARCH */
  /*     SUPPORTED BY THE NATIONAL SCIENCE FOUNDATION UNDER GRANTS */
  /*     MCS-7600324, DCR75-10143, 76-14311DSS, AND MCS76-11989. */

  /*     .................................................................. */
  /*     .................................................................. */

  /*     *****LOCAL VARIABLES. */
  /*     *****FUNCTIONS. */

  /*  ***  BODY  *** */

  /* Parameter adjustments */
  --r__;
  j_dim1 = *nn;
  j_offset = j_dim1 + 1;
  j -= j_offset;

  /* Function Body */
  k = *p;

  if (*ierr != 0)
    {
      k = abs(*ierr) - 1;
    }

  if (k == 0)
    {
      goto L999;
    }

  i__1 = k;

  for (l = 1; l <= i__1; ++l)
    {
      nl1 = *n - l + 1;
      d__1 = -dd7tpr_(&nl1, &j[l + l * j_dim1], &r__[l]);
      dv2axy_(&nl1, &r__[l], &d__1, &j[l + l * j_dim1], &r__[l]);
      /* L20: */
    }

L999:
  return 0;
  /*  ***  LAST LINE OF DQ7APL FOLLOWS  *** */
} /* dq7apl_ */

int dq7rad_(integer *n, integer *nn, integer *p, doublereal *qtr,
            logical *qtrset, doublereal *rmat, doublereal *w, doublereal *y)
{
  /* Initialized data */

  static doublereal big = -1.;
  static doublereal bigrt = -1.;
  static doublereal one = 1.;
  static doublereal tiny = 0.;
  static doublereal tinyrt = 0.;
  static doublereal zero = 0.;

  /* System generated locals */
  integer w_dim1, w_offset, i__1, i__2;
  doublereal d__1;

  /* Local variables */
  static integer i__, j, k;
  static doublereal s, t;
  extern doublereal dr7mdc_(integer *);
  extern int dv7scl_(integer *, doublereal *, doublereal *,
                     doublereal *);
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *),
         dv2nrm_(integer *, doublereal *);
  extern int dv2axy_(integer *, doublereal *, doublereal *,
                     doublereal *, doublereal *);
  static integer ii, ij, nk;
  static doublereal ri, wi;
  static integer ip1;
  static doublereal ari, qri;

  /*  ***  ADD ROWS W TO QR FACTORIZATION WITH R MATRIX RMAT AND */
  /*  ***  Q**T * RESIDUAL = QTR.  Y = NEW COMPONENTS OF RESIDUAL */
  /*  ***  CORRESPONDING TO W.  QTR, Y REFERENCED ONLY IF QTRSET = .TRUE. */

  /*     DIMENSION RMAT(P*(P+1)/2) */
  /* /+ */
  /* / */

  /*  ***  LOCAL VARIABLES  *** */

  /* /7 */
  /* / */
  /* Parameter adjustments */
  --y;
  w_dim1 = *nn;
  w_offset = w_dim1 + 1;
  w -= w_offset;
  --qtr;
  --rmat;

  /* Function Body */

  /* ------------------------------ BODY ----------------------------------- */

  if (tiny > zero)
    {
      goto L10;
    }

  tiny = dr7mdc_(&c__1);
  big = dr7mdc_(&c__6);

  if (tiny * big < one)
    {
      tiny = one / big;
    }

L10:
  k = 1;
  nk = *n;
  ii = 0;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      ii += i__;
      ip1 = i__ + 1;
      ij = ii + i__;

      if (nk <= 1)
        {
          t = (d__1 = w[k + i__ * w_dim1], fabs(d__1));
        }

      if (nk > 1)
        {
          t = dv2nrm_(&nk, &w[k + i__ * w_dim1]);
        }

      if (t < tiny)
        {
          goto L180;
        }

      ri = rmat[ii];

      if (ri != zero)
        {
          goto L100;
        }

      if (nk > 1)
        {
          goto L30;
        }

      ij = ii;
      i__2 = *p;

      for (j = i__; j <= i__2; ++j)
        {
          rmat[ij] = w[k + j * w_dim1];
          ij += j;
          /* L20: */
        }

      if (*qtrset)
        {
          qtr[i__] = y[k];
        }

      w[k + i__ * w_dim1] = zero;
      goto L999;

L30:
      wi = w[k + i__ * w_dim1];

      if (bigrt > zero)
        {
          goto L40;
        }

      bigrt = dr7mdc_(&c__5);
      tinyrt = dr7mdc_(&c__2);

L40:

      if (t <= tinyrt)
        {
          goto L50;
        }

      if (t >= bigrt)
        {
          goto L50;
        }

      if (wi < zero)
        {
          t = -t;
        }

      wi += t;
      s = sqrt(t * wi);
      goto L70;

L50:
      s = sqrt(t);

      if (wi < zero)
        {
          goto L60;
        }

      wi += t;
      s *= sqrt(wi);
      goto L70;

L60:
      t = -t;
      wi += t;
      s *= sqrt(-wi);

L70:
      w[k + i__ * w_dim1] = wi;
      d__1 = one / s;
      dv7scl_(&nk, &w[k + i__ * w_dim1], &d__1, &w[k + i__ * w_dim1]);
      rmat[ii] = -t;

      if (!(*qtrset))
        {
          goto L80;
        }

      d__1 = -dd7tpr_(&nk, &y[k], &w[k + i__ * w_dim1]);
      dv2axy_(&nk, &y[k], &d__1, &w[k + i__ * w_dim1], &y[k]);
      qtr[i__] = y[k];

L80:

      if (ip1 > *p)
        {
          goto L999;
        }

      i__2 = *p;

      for (j = ip1; j <= i__2; ++j)
        {
          d__1 = -dd7tpr_(&nk, &w[k + j * w_dim1], &w[k + i__ * w_dim1]);
          dv2axy_(&nk, &w[k + j * w_dim1], &d__1, &w[k + i__ * w_dim1], &w[
                    k + j * w_dim1]);
          rmat[ij] = w[k + j * w_dim1];
          ij += j;
          /* L90: */
        }

      if (nk <= 1)
        {
          goto L999;
        }

      ++k;
      --nk;
      goto L180;

L100:
      ari = fabs(ri);

      if (ari > t)
        {
          goto L110;
        }

      /* Computing 2nd power */
      d__1 = ari / t;
      t *= sqrt(one + d__1 * d__1);
      goto L120;

L110:
      /* Computing 2nd power */
      d__1 = t / ari;
      t = ari * sqrt(one + d__1 * d__1);

L120:

      if (ri < zero)
        {
          t = -t;
        }

      ri += t;
      rmat[ii] = -t;
      s = -ri / t;

      if (nk <= 1)
        {
          goto L150;
        }

      d__1 = one / ri;
      dv7scl_(&nk, &w[k + i__ * w_dim1], &d__1, &w[k + i__ * w_dim1]);

      if (!(*qtrset))
        {
          goto L130;
        }

      qri = qtr[i__];
      t = s * (qri + dd7tpr_(&nk, &y[k], &w[k + i__ * w_dim1]));
      qtr[i__] = qri + t;

L130:

      if (ip1 > *p)
        {
          goto L999;
        }

      if (*qtrset)
        {
          dv2axy_(&nk, &y[k], &t, &w[k + i__ * w_dim1], &y[k]);
        }

      i__2 = *p;

      for (j = ip1; j <= i__2; ++j)
        {
          ri = rmat[ij];
          t = s * (ri + dd7tpr_(&nk, &w[k + j * w_dim1], &w[k + i__ *
                                w_dim1]));
          dv2axy_(&nk, &w[k + j * w_dim1], &t, &w[k + i__ * w_dim1], &w[k +
                  j * w_dim1]);
          rmat[ij] = ri + t;
          ij += j;
          /* L140: */
        }

      goto L180;

L150:
      wi = w[k + i__ * w_dim1] / ri;
      w[k + i__ * w_dim1] = wi;

      if (!(*qtrset))
        {
          goto L160;
        }

      qri = qtr[i__];
      t = s * (qri + y[k] * wi);
      qtr[i__] = qri + t;

L160:

      if (ip1 > *p)
        {
          goto L999;
        }

      if (*qtrset)
        {
          y[k] = t * wi + y[k];
        }

      i__2 = *p;

      for (j = ip1; j <= i__2; ++j)
        {
          ri = rmat[ij];
          t = s * (ri + w[k + j * w_dim1] * wi);
          w[k + j * w_dim1] += t * wi;
          rmat[ij] = ri + t;
          ij += j;
          /* L170: */
        }

L180:
      ;
    }

L999:
  return 0;
  /*  ***  LAST LINE OF DQ7RAD FOLLOWS  *** */
} /* dq7rad_ */

int dq7rsh_(integer *k, integer *p, logical *havqtr,
            doublereal *qtr, doublereal *r__, doublereal *w)
{
  /* Initialized data */

  static doublereal zero = 0.;

  /* System generated locals */
  integer i__1, i__2;

  /* Local variables */
  static doublereal a, b;
  static integer i__, j;
  static doublereal t, x, y, z__;
  static integer i1, j1, k1;
  extern int dh2rfa_(integer *, doublereal *, doublereal *,
                     doublereal *, doublereal *, doublereal *);
  extern doublereal dh2rfg_(doublereal *, doublereal *, doublereal *,
                            doublereal *, doublereal *);
  extern int dv7cpy_(integer *, doublereal *, doublereal *)
  ;
  static doublereal wj;
  static integer jm1, km1, jp1, pm1;

  /*  ***  PERMUTE COLUMN K OF R TO COLUMN P, MODIFY QTR ACCORDINGLY  *** */

  /*     DIMSNSION R(P*(P+1)/2) */

  /*  ***  LOCAL VARIABLES  *** */

  /* Parameter adjustments */
  --w;
  --qtr;
  --r__;

  /* Function Body */

  /* +++++++++++++++++++++++++++++++  BODY  ++++++++++++++++++++++++++++++++ */

  if (*k >= *p)
    {
      goto L999;
    }

  km1 = *k - 1;
  k1 = *k * km1 / 2;
  dv7cpy_(k, &w[1], &r__[k1 + 1]);
  wj = w[*k];
  pm1 = *p - 1;
  j1 = k1 + km1;
  i__1 = pm1;

  for (j = *k; j <= i__1; ++j)
    {
      jm1 = j - 1;
      jp1 = j + 1;

      if (jm1 > 0)
        {
          dv7cpy_(&jm1, &r__[k1 + 1], &r__[j1 + 2]);
        }

      j1 += jp1;
      k1 += j;
      a = r__[j1];
      b = r__[j1 + 1];

      if (b != zero)
        {
          goto L10;
        }

      r__[k1] = a;
      x = zero;
      z__ = zero;
      goto L40;

L10:
      r__[k1] = dh2rfg_(&a, &b, &x, &y, &z__);

      if (j == pm1)
        {
          goto L30;
        }

      i1 = j1;
      i__2 = pm1;

      for (i__ = jp1; i__ <= i__2; ++i__)
        {
          i1 += i__;
          dh2rfa_(&c__1, &r__[i1], &r__[i1 + 1], &x, &y, &z__);
          /* L20: */
        }

L30:

      if (*havqtr)
        {
          dh2rfa_(&c__1, &qtr[j], &qtr[jp1], &x, &y, &z__);
        }

L40:
      t = x * wj;
      w[j] = wj + t;
      wj = t * z__;
      /* L50: */
    }

  w[*p] = wj;
  dv7cpy_(p, &r__[k1 + 1], &w[1]);
L999:
  return 0;
} /* dq7rsh_ */

doublereal dr7mdc_(integer *k)
{
  /* Initialized data */

  static doublereal big = 0.;
  static doublereal eta = 0.;
  static doublereal machep = 0.;
  static doublereal zero = 0.;

  /* System generated locals */
  doublereal ret_val;

  /* Local variables */
  extern doublereal d1mach_(integer *);

  /*  ***  RETURN MACHINE DEPENDENT CONSTANTS USED BY NL2SOL  *** */

  /*  ***  THE CONSTANT RETURNED DEPENDS ON K... */

  /*  ***        K = 1... SMALLEST POS. ETA SUCH THAT -ETA EXISTS. */
  /*  ***        K = 2... SQUARE ROOT OF ETA. */
  /*  ***        K = 3... UNIT ROUNDOFF = SMALLEST POS. NO. MACHEP SUCH */
  /*  ***                 THAT 1 + MACHEP .GT. 1 .AND. 1 - MACHEP .LT. 1. */
  /*  ***        K = 4... SQUARE ROOT OF MACHEP. */
  /*  ***        K = 5... SQUARE ROOT OF BIG (SEE K = 6). */
  /*  ***        K = 6... LARGEST MACHINE NO. BIG SUCH THAT -BIG EXISTS. */

  /* /+ */
  /* / */

  if (big > zero)
    {
      goto L1;
    }

  big = d1mach_(&c__2);
  eta = d1mach_(&c__1);
  machep = d1mach_(&c__4);

L1:
  /* -------------------------------  BODY  -------------------------------- */

  switch (*k)
    {
      case 1:  goto L10;

      case 2:  goto L20;

      case 3:  goto L30;

      case 4:  goto L40;

      case 5:  goto L50;

      case 6:  goto L60;
    }

L10:
  ret_val = eta;
  goto L999;

L20:
  ret_val = sqrt(eta * 256.) / 16.;
  goto L999;

L30:
  ret_val = machep;
  goto L999;

L40:
  ret_val = sqrt(machep);
  goto L999;

L50:
  ret_val = sqrt(big / 256.) * 16.;
  goto L999;

L60:
  ret_val = big;

L999:
  return ret_val;
  /*  ***  LAST CARD OF DR7MDC FOLLOWS  *** */
} /* dr7mdc_ */

int dr7tvm_(integer *n, integer *p, doublereal *y,
            doublereal *d__, doublereal *u, doublereal *x)
{
  /* System generated locals */
  integer u_dim1, u_offset, i__1, i__2;

  /* Local variables */
  static integer i__;
  static doublereal t;
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *);
  static integer ii, pl, pp1;

  /*  ***  SET Y TO R*X, WHERE R IS THE UPPER TRIANGULAR MATRIX WHOSE */
  /*  ***  DIAGONAL IS IN D AND WHOSE STRICT UPPER TRIANGLE IS IN U. */

  /*  ***  X AND Y MAY SHARE STORAGE. */

  /*  ***  LOCAL VARIABLES  *** */

  /*  ***  BODY  *** */

  /* Parameter adjustments */
  --x;
  u_dim1 = *n;
  u_offset = u_dim1 + 1;
  u -= u_offset;
  --d__;
  --y;

  /* Function Body */
  /* Computing MIN */
  pl = std::min(*n, *p);
  pp1 = pl + 1;
  i__1 = pl;

  for (ii = 1; ii <= i__1; ++ii)
    {
      i__ = pp1 - ii;
      t = x[i__] * d__[i__];

      if (i__ > 1)
        {
          i__2 = i__ - 1;
          t += dd7tpr_(&i__2, &u[i__ * u_dim1 + 1], &x[1]);
        }

      y[i__] = t;
      /* L10: */
    }

  /* L999: */
  return 0;
  /*  ***  LAST LINE OF DR7TVM FOLLOWS  *** */
} /* dr7tvm_ */

doublereal drldst_(integer *p, doublereal *d__, doublereal *x, doublereal *x0)
{
  /* System generated locals */
  integer i__1;
  doublereal ret_val, d__1, d__2;

  /* Local variables */
  static doublereal emax, xmax;
  static integer i__;
  static doublereal t;

  /*  ***  COMPUTE AND RETURN RELATIVE DIFFERENCE BETWEEN X AND X0  *** */
  /*  ***  NL2SOL VERSION 2.2  *** */

  /* /6 */
  /*     DATA ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /*  ***  BODY  *** */

  /* Parameter adjustments */
  --x0;
  --x;
  --d__;

  /* Function Body */
  emax = 0.;
  xmax = 0.;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      t = (d__1 = d__[i__] * (x[i__] - x0[i__]), fabs(d__1));

      if (emax < t)
        {
          emax = t;
        }

      t = d__[i__] * ((d__1 = x[i__], fabs(d__1)) + (d__2 = x0[i__], fabs(
                        d__2)));

      if (xmax < t)
        {
          xmax = t;
        }

      /* L10: */
    }

  ret_val = 0.;

  if (xmax > 0.)
    {
      ret_val = emax / xmax;
    }

  /* L999: */
  return ret_val;
  /*  ***  LAST CARD OF DRLDST FOLLOWS  *** */
} /* drldst_ */

int drn2gb_(doublereal *b, doublereal *d__, doublereal *dr,
            integer *iv, integer *liv, integer *lv, integer *n, integer *nd,
            integer *n1, integer *n2, integer *p, doublereal *r__, doublereal *rd,
            doublereal *v, doublereal *x)
{
  /* System generated locals */
  integer dr_dim1, dr_offset, i__1;
  doublereal d__1;

  /* Local variables */
  static integer rmat1, jtol1, i__, l;
  static doublereal t;
  static integer g1, y1;
  extern int dg7itb_(doublereal *, doublereal *,
                     doublereal *, integer *, integer *, integer *, integer *, integer
                     *, doublereal *, doublereal *, doublereal *),
                     dq7rad_(integer *, integer *, integer *, doublereal *, logical *,
                             doublereal *, doublereal *, doublereal *),
                     dd7upd_(doublereal *, doublereal *, integer *, integer *, integer *,
                             integer *, integer *, integer *, integer *, integer *, doublereal *),
                     dq7apl_(integer *, integer *, integer *, doublereal *, doublereal *, integer *);
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *);
  extern int dl7vml_(integer *, doublereal *, doublereal *, doublereal *),
         dv7scp_(integer *, doublereal *, doublereal *);
  extern doublereal dv2nrm_(integer *, doublereal *);
  extern int dv7cpy_(integer *, doublereal *, doublereal *)
  ;
  static integer gi;
  extern int dr7tvm_(integer *, integer *, doublereal *,
                     doublereal *, doublereal *, doublereal *);
  static integer lh, nn, yi, ivmode;
  extern int divset_(integer *, integer *, integer *,
                     integer *, doublereal *);
  static integer rd1, iv1, qtr1;

  /*  ***  REVISED ITERATION DRIVER FOR NL2SOL WITH SIMPLE BOUNDS  *** */

  /* --------------------------  PARAMETER USAGE  -------------------------- */

  /* B........ BOUNDS ON X. */
  /* D........ SCALE VECTOR. */
  /* DR....... DERIVATIVES OF R AT X. */
  /* IV....... INTEGER VALUES ARRAY. */
  /* LIV...... LENGTH OF IV... LIV MUST BE AT LEAST 4*P + 82. */
  /* LV....... LENGTH OF V...  LV  MUST BE AT LEAST 105 + P*(2*P+20). */
  /* N........ TOTAL NUMBER OF RESIDUALS. */
  /* ND....... MAX. NO. OF RESIDUALS PASSED ON ONE CALL. */
  /* N1....... LOWEST  ROW INDEX FOR RESIDUALS SUPPLIED THIS TIME. */
  /* N2....... HIGHEST ROW INDEX FOR RESIDUALS SUPPLIED THIS TIME. */
  /* P........ NUMBER OF PARAMETERS (COMPONENTS OF X) BEING ESTIMATED. */
  /* R........ RESIDUALS. */
  /* V........ FLOATING-POINT VALUES ARRAY. */
  /* X........ PARAMETER VECTOR BEING ESTIMATED (INPUT = INITIAL GUESS, */
  /*             OUTPUT = BEST VALUE FOUND). */

  /*  ***  DISCUSSION  *** */

  /*     THIS ROUTINE CARRIES OUT ITERATIONS FOR SOLVING NONLINEAR */
  /*  LEAST SQUARES PROBLEMS.  IT IS SIMILAR TO  DRN2G, EXCEPT THAT */
  /*  THIS ROUTINE ENFORCES THE BOUNDS  B(1,I) .LE. X(I) .LE. B(2,I), */
  /*  I = 1(1)P. */

  /*  ***  GENERAL  *** */

  /*     CODED BY DAVID M. GAY. */

  /* +++++++++++++++++++++++++++++  DECLARATIONS  ++++++++++++++++++++++++++ */

  /*  ***  EXTERNAL FUNCTIONS AND SUBROUTINES  *** */

  /* DIVSET.... PROVIDES DEFAULT IV AND V INPUT COMPONENTS. */
  /* DD7TPR... COMPUTES INNER PRODUCT OF TWO VECTORS. */
  /* DD7UPD...  UPDATES SCALE VECTOR D. */
  /* DG7ITB... PERFORMS BASIC MINIMIZATION ALGORITHM. */
  /* DITSUM.... PRINTS ITERATION SUMMARY, INFO ABOUT INITIAL AND FINAL X. */
  /* DL7VML.... COMPUTES L * V, V = VECTOR, L = LOWER TRIANGULAR MATRIX. */
  /* DQ7APL... APPLIES QR TRANSFORMATIONS STORED BY DQ7RAD. */
  /* DQ7RAD.... ADDS A NEW BLOCK OF ROWS TO QR DECOMPOSITION. */
  /* DR7TVM... MULT. VECTOR BY TRANS. OF UPPER TRIANG. MATRIX FROM QR FACT. */
  /* DV7CPY.... COPIES ONE VECTOR TO ANOTHER. */
  /* DV7SCP... SETS ALL ELEMENTS OF A VECTOR TO A SCALAR. */
  /* DV2NRM... RETURNS THE 2-NORM OF A VECTOR. */

  /*  ***  LOCAL VARIABLES  *** */

  /*  ***  SUBSCRIPTS FOR IV AND V  *** */

  /*  ***  IV SUBSCRIPT VALUES  *** */

  /* /6 */
  /*     DATA DTYPE/16/, G/28/, JCN/66/, JTOL/59/, MODE/35/, NEXTV/47/, */
  /*    1     NF0/68/, NF00/81/, NF1/69/, NFCALL/6/, NFCOV/52/, NFGCAL/7/, */
  /*    2     QTR/77/, RDREQ/57/, RESTOR/9/, REGD/67/, RMAT/78/, TOOBIG/2/, */
  /*    3     VNEED/4/ */
  /* /7 */
  /* / */

  /*  ***  V SUBSCRIPT VALUES  *** */

  /* /6 */
  /*     DATA DINIT/38/, DTINIT/39/, D0INIT/40/, F/10/, RLIMIT/46/ */
  /* /7 */
  /* / */
  /* /6 */
  /*     DATA HALF/0.5D+0/, ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /* +++++++++++++++++++++++++++++++  BODY  ++++++++++++++++++++++++++++++++ */

  /* Parameter adjustments */
  --iv;
  --v;
  --rd;
  --r__;
  --x;
  dr_dim1 = *nd;
  dr_offset = dr_dim1 + 1;
  dr -= dr_offset;
  --d__;
  b -= 3;

  /* Function Body */
  lh = *p * (*p + 1) / 2;

  if (iv[1] == 0)
    {
      divset_(&c__1, &iv[1], liv, lv, &v[1]);
    }

  iv1 = iv[1];

  if (iv1 > 2)
    {
      goto L10;
    }

  nn = *n2 - *n1 + 1;
  iv[9] = 0;
  i__ = iv1 + 4;

  if (iv[2] == 0)
    {
      switch (i__)
        {
          case 1:  goto L150;

          case 2:  goto L130;

          case 3:  goto L150;

          case 4:  goto L120;

          case 5:  goto L120;

          case 6:  goto L150;
        }
    }

  if (i__ != 5)
    {
      iv[1] = 2;
    }

  goto L40;

  /*  ***  FRESH START OR RESTART -- CHECK INPUT INTEGERS  *** */

L10:

  if (*nd <= 0)
    {
      goto L220;
    }

  if (*p <= 0)
    {
      goto L220;
    }

  if (*n <= 0)
    {
      goto L220;
    }

  if (iv1 == 14)
    {
      goto L30;
    }

  if (iv1 > 16)
    {
      goto L999;
    }

  if (iv1 < 12)
    {
      goto L40;
    }

  if (iv1 == 12)
    {
      iv[1] = 13;
    }

  if (iv[1] != 13)
    {
      goto L20;
    }

  iv[4] += *p * (*p + 15) / 2;

L20:
  dg7itb_(&b[3], &d__[1], &x[1], &iv[1], liv, lv, p, p, &v[1], &x[1], &x[1]);

  if (iv[1] != 14)
    {
      goto L999;
    }

  /*  ***  STORAGE ALLOCATION  *** */

  iv[28] = iv[47];
  iv[66] = iv[28] + (*p << 1);
  iv[78] = iv[66] + *p;
  iv[77] = iv[78] + lh;
  iv[59] = iv[77] + (*p << 1);
  iv[47] = iv[59] + (*p << 1);
  /*  ***  TURN OFF COVARIANCE COMPUTATION  *** */
  iv[57] = 0;

  if (iv1 == 13)
    {
      goto L999;
    }

L30:
  jtol1 = iv[59];

  if (v[38] >= 0.)
    {
      dv7scp_(p, &d__[1], &v[38]);
    }

  if (v[39] > 0.)
    {
      dv7scp_(p, &v[jtol1], &v[39]);
    }

  i__ = jtol1 + *p;

  if (v[40] > 0.)
    {
      dv7scp_(p, &v[i__], &v[40]);
    }

  iv[68] = 0;
  iv[69] = 0;

  if (*nd >= *n)
    {
      goto L40;
    }

  /*  ***  SPECIAL CASE HANDLING OF FIRST FUNCTION AND GRADIENT EVALUATION */
  /*  ***  -- ASK FOR BOTH RESIDUAL AND JACOBIAN AT ONCE */

  g1 = iv[28];
  y1 = g1 + *p;
  dg7itb_(&b[3], &d__[1], &v[g1], &iv[1], liv, lv, p, p, &v[1], &x[1], &v[y1]);

  if (iv[1] != 1)
    {
      goto L260;
    }

  v[10] = 0.;
  dv7scp_(p, &v[g1], &c_b78);
  iv[1] = -1;
  qtr1 = iv[77];
  dv7scp_(p, &v[qtr1], &c_b78);
  iv[67] = 0;
  rmat1 = iv[78];
  goto L100;

L40:
  g1 = iv[28];
  y1 = g1 + *p;
  dg7itb_(&b[3], &d__[1], &v[g1], &iv[1], liv, lv, p, p, &v[1], &x[1], &v[
            y1]);

  if ((i__1 = iv[1] - 2) < 0)
    {
      goto L50;
    }
  else if (i__1 == 0)
    {
      goto L60;
    }
  else
    {
      goto L260;
    }

L50:
  v[10] = 0.;

  if (iv[69] == 0)
    {
      goto L240;
    }

  if (iv[9] != 2)
    {
      goto L240;
    }

  iv[68] = iv[69];
  dv7cpy_(n, &rd[1], &r__[1]);
  iv[67] = 0;
  goto L240;

L60:
  dv7scp_(p, &v[g1], &c_b78);

  if (iv[35] > 0)
    {
      goto L230;
    }

  rmat1 = iv[78];
  qtr1 = iv[77];
  rd1 = qtr1 + *p;
  dv7scp_(p, &v[qtr1], &c_b78);
  iv[67] = 0;

  if (*nd < *n)
    {
      goto L90;
    }

  if (*n1 != 1)
    {
      goto L90;
    }

  if (iv[35] < 0)
    {
      goto L100;
    }

  if (iv[69] == iv[7])
    {
      goto L70;
    }

  if (iv[68] != iv[7])
    {
      goto L90;
    }

  dv7cpy_(n, &r__[1], &rd[1]);
  goto L80;

L70:
  dv7cpy_(n, &rd[1], &r__[1]);

L80:
  dq7apl_(nd, n, p, &dr[dr_offset], &rd[1], &c__0);
  i__1 = std::min(*n, *p);
  dr7tvm_(nd, &i__1, &v[y1], &v[rd1], &dr[dr_offset], &rd[1]);
  iv[67] = 0;
  goto L110;

L90:
  iv[1] = -2;

  if (iv[35] < 0)
    {
      iv[1] = -3;
    }

L100:
  dv7scp_(p, &v[y1], &c_b78);

L110:
  dv7scp_(&lh, &v[rmat1], &c_b78);
  goto L240;

  /*  ***  COMPUTE F(X)  *** */

L120:
  t = dv2nrm_(&nn, &r__[1]);

  if (t > v[46])
    {
      goto L210;
    }

  /* Computing 2nd power */
  d__1 = t;
  v[10] += d__1 * d__1 * .5;

  if (*n2 < *n)
    {
      goto L250;
    }

  if (*n1 == 1)
    {
      iv[69] = iv[6];
    }

  goto L40;

  /*  ***  COMPUTE Y  *** */

L130:
  y1 = iv[28] + *p;
  yi = y1;
  i__1 = *p;

  for (l = 1; l <= i__1; ++l)
    {
      v[yi] += dd7tpr_(&nn, &dr[l * dr_dim1 + 1], &r__[1]);
      ++yi;
      /* L140: */
    }

  if (*n2 < *n)
    {
      goto L250;
    }

  iv[1] = 2;

  if (*n1 > 1)
    {
      iv[1] = -3;
    }

  goto L240;

  /*  ***  COMPUTE GRADIENT INFORMATION  *** */

L150:
  g1 = iv[28];
  ivmode = iv[35];

  if (ivmode < 0)
    {
      goto L170;
    }

  if (ivmode == 0)
    {
      goto L180;
    }

  iv[1] = 2;

  /*  ***  COMPUTE GRADIENT ONLY (FOR USE IN COVARIANCE COMPUTATION)  *** */

  gi = g1;
  i__1 = *p;

  for (l = 1; l <= i__1; ++l)
    {
      v[gi] += dd7tpr_(&nn, &r__[1], &dr[l * dr_dim1 + 1]);
      ++gi;
      /* L160: */
    }

  goto L200;

  /*  *** COMPUTE INITIAL FUNCTION VALUE WHEN ND .LT. N *** */

L170:

  if (*n <= *nd)
    {
      goto L180;
    }

  t = dv2nrm_(&nn, &r__[1]);

  if (t > v[46])
    {
      goto L210;
    }

  /* Computing 2nd power */
  d__1 = t;
  v[10] += d__1 * d__1 * .5;

  /*  ***  UPDATE D IF DESIRED  *** */

L180:

  if (iv[16] > 0)
    {
      dd7upd_(&d__[1], &dr[dr_offset], &iv[1], liv, lv, n, nd, &nn, n2, p, &
              v[1]);
    }

  /*  ***  COMPUTE RMAT AND QTR  *** */

  qtr1 = iv[77];
  rmat1 = iv[78];
  dq7rad_(&nn, nd, p, &v[qtr1], &c_true, &v[rmat1], &dr[dr_offset], &r__[1])
  ;
  iv[69] = 0;

  if (*n1 > 1)
    {
      goto L200;
    }

  if (*n2 < *n)
    {
      goto L250;
    }

  /*  ***  SAVE DIAGONAL OF R FOR COMPUTING Y LATER  *** */

  rd1 = qtr1 + *p;
  l = rmat1 - 1;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      l += i__;
      v[rd1] = v[l];
      ++rd1;
      /* L190: */
    }

L200:

  if (*n2 < *n)
    {
      goto L250;
    }

  if (ivmode > 0)
    {
      goto L40;
    }

  iv[81] = iv[7];

  /*  ***  COMPUTE G FROM RMAT AND QTR  *** */

  dl7vml_(p, &v[g1], &v[rmat1], &v[qtr1]);
  iv[1] = 2;

  if (ivmode == 0)
    {
      goto L40;
    }

  if (*n <= *nd)
    {
      goto L40;
    }

  /*  ***  FINISH SPECIAL CASE HANDLING OF FIRST FUNCTION AND GRADIENT */

  y1 = g1 + *p;
  iv[1] = 1;
  dg7itb_(&b[3], &d__[1], &v[g1], &iv[1], liv, lv, p, p, &v[1], &x[1], &v[
            y1]);

  if (iv[1] != 2)
    {
      goto L260;
    }

  goto L40;

  /*  ***  MISC. DETAILS  *** */

  /*     ***  X IS OUT OF RANGE (OVERSIZE STEP)  *** */

L210:
  iv[2] = 1;
  goto L40;

  /*     ***  BAD N, ND, OR P  *** */

L220:
  iv[1] = 66;
  goto L999;

  /*  ***  RECORD EXTRA EVALUATIONS FOR FINITE-DIFFERENCE HESSIAN  *** */

L230:
  ++iv[52];
  ++iv[6];
  iv[7] = iv[6];
  iv[1] = -1;

  /*  ***  RETURN FOR MORE FUNCTION OR GRADIENT INFORMATION  *** */

L240:
  *n2 = 0;

L250:
  *n1 = *n2 + 1;
  *n2 += *nd;

  if (*n2 > *n)
    {
      *n2 = *n;
    }

  goto L999;

  /*  ***  PRINT SUMMARY OF FINAL ITERATION AND OTHER REQUESTED ITEMS  *** */

L260:
  g1 = iv[28];

L999:
  return 0;
  /*  ***  LAST CARD OF DRN2GB FOLLOWS  *** */
} /* drn2gb_ */

int ds7bqn_(doublereal *b, doublereal *d__, doublereal *dst,
            integer *ipiv, integer *ipiv1, integer *ipiv2, integer *kb,
            doublereal *l, integer *lv, integer *ns, integer *p, integer *p1,
            doublereal *step, doublereal *td, doublereal *tg, doublereal *v,
            doublereal *w, doublereal *x, doublereal *x0)
{
  /* Initialized data */

  static doublereal fudge = 1.0001;
  static doublereal half = .5;
  static doublereal meps2 = 0.;
  static doublereal one = 1.;
  static doublereal two = 2.;
  static doublereal zero = 0.;

  /* System generated locals */
  integer i__1, i__2;
  doublereal d__1, d__2, d__3, d__4;

  /* Local variables */
  static integer i__, j, k;
  static doublereal t, alpha;
  static integer p0;
  static doublereal t1;
  extern doublereal dr7mdc_(integer *);
  extern int dv7shf_(integer *, integer *, doublereal *),
         dl7ivm_(integer *, doublereal *, doublereal *, doublereal *);
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *);
  extern int i7shft_(integer *, integer *, integer *),
         dv7scp_(integer *, doublereal *, doublereal *);
  extern doublereal dv2nrm_(integer *, doublereal *);
  extern int dl7itv_(integer *, doublereal *, doublereal *, doublereal *),
         dq7rsh_(integer *, integer *, logical *, doublereal *,
                 doublereal *, doublereal *),
         dv7ipr_(integer *, integer *, doublereal *),
         dv7cpy_(integer *, doublereal *, doublereal *),
         dv2axy_(integer *, doublereal *, doublereal *, doublereal *,
                 doublereal *);
  static doublereal dx, ti, xi, dstmin, dstmax;
  static integer p1m1;
  static doublereal gts, dst0, dst1;

  /*  ***  COMPUTE BOUNDED MODIFIED NEWTON STEP  *** */

  /*     DIMENSION L(P*(P+1)/2) */

  /*  ***  LOCAL VARIABLES  *** */

  /*  ***  V SUBSCRIPTS  *** */

  /* /6 */
  /*     DATA DSTNRM/2/, GTSTEP/4/, PHMNFC/20/, PHMXFC/21/, PREDUC/7/, */
  /*    1     RADIUS/8/, STPPAR/5/ */
  /* /7 */
  /* / */

  /* Parameter adjustments */
  --l;
  --v;
  --x0;
  --x;
  --w;
  --tg;
  --td;
  --step;
  --ipiv2;
  --ipiv1;
  --ipiv;
  --dst;
  --d__;
  b -= 3;

  /* Function Body */

  /* +++++++++++++++++++++++++++++++  BODY  ++++++++++++++++++++++++++++++++ */

  dstmax = fudge * (one + v[21]) * v[8];
  dstmin = (one + v[20]) * v[8];
  dst1 = zero;

  if (meps2 <= zero)
    {
      meps2 = two * dr7mdc_(&c__3);
    }

  p0 = *p1;
  *ns = 0;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      ipiv1[i__] = i__;
      ipiv2[i__] = i__;
      /* L10: */
    }

  i__1 = *p1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L20: */
      w[i__] = -step[i__] * td[i__];
    }

  alpha = fabs(v[5]);
  v[7] = zero;
  gts = -v[4];

  if (*kb < 0)
    {
      dv7scp_(p, &dst[1], &zero);
    }

  *kb = 1;

  /*     ***  -W = D TIMES RESTRICTED NEWTON STEP FROM X + DST/D. */

  /*     ***  FIND T SUCH THAT X - T*W IS STILL FEASIBLE. */

L30:
  t = one;
  k = 0;
  i__1 = *p1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j = ipiv[i__];
      dx = w[i__] / d__[j];
      xi = x[j] - dx;

      if (xi < b[(j << 1) + 1])
        {
          goto L40;
        }

      if (xi <= b[(j << 1) + 2])
        {
          goto L60;
        }

      ti = (x[j] - b[(j << 1) + 2]) / dx;
      k = i__;
      goto L50;

L40:
      ti = (x[j] - b[(j << 1) + 1]) / dx;
      k = -i__;

L50:

      if (t <= ti)
        {
          goto L60;
        }

      t = ti;
L60:
      ;
    }

  if (*p > *p1)
    {
      i__1 = *p - *p1;
      dv7cpy_(&i__1, &step[*p1 + 1], &dst[*p1 + 1]);
    }

  d__1 = -t;
  dv2axy_(p1, &step[1], &d__1, &w[1], &dst[1]);
  dst0 = dst1;
  dst1 = dv2nrm_(p, &step[1]);

  /*  ***  CHECK FOR OVERSIZE STEP  *** */

  if (dst1 <= dstmax)
    {
      goto L80;
    }

  if (*p1 >= p0)
    {
      goto L70;
    }

  if (dst0 < dstmin)
    {
      *kb = 0;
    }

  goto L110;

L70:
  k = 0;

  /*  ***  UPDATE DST, TG, AND V(PREDUC)  *** */

L80:
  v[2] = dst1;
  dv7cpy_(p1, &dst[1], &step[1]);
  t1 = one - t;
  i__1 = *p1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L90: */
      tg[i__] = t1 * tg[i__];
    }

  if (alpha > zero)
    {
      d__1 = t * alpha;
      dv2axy_(p1, &tg[1], &d__1, &w[1], &tg[1]);
    }

  v[7] += t * ((one - half * t) * gts + half * alpha * t * dd7tpr_(p1, &w[1]
               , &w[1]));

  if (k == 0)
    {
      goto L110;
    }

  /*     ***  PERMUTE L, ETC. IF NECESSARY  *** */

  p1m1 = *p1 - 1;
  j = abs(k);

  if (j == *p1)
    {
      goto L100;
    }

  ++(*ns);
  ipiv2[*p1] = j;
  dq7rsh_(&j, p1, &c_false, &tg[1], &l[1], &w[1]);
  i7shft_(p1, &j, &ipiv[1]);
  i7shft_(p1, &j, &ipiv1[1]);
  dv7shf_(p1, &j, &tg[1]);
  dv7shf_(p1, &j, &dst[1]);

L100:

  if (k < 0)
    {
      ipiv[*p1] = -ipiv[*p1];
    }

  *p1 = p1m1;

  if (*p1 <= 0)
    {
      goto L110;
    }

  dl7ivm_(p1, &w[1], &l[1], &tg[1]);
  gts = dd7tpr_(p1, &w[1], &w[1]);
  dl7itv_(p1, &w[1], &l[1], &w[1]);
  goto L30;

  /*     ***  UNSCALE STEP  *** */

L110:
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j = (i__2 = ipiv[i__], abs(i__2));
      step[j] = dst[i__] / d__[j];
      /* L120: */
    }

  /*  ***  FUDGE STEP TO ENSURE THAT IT FORCES APPROPRIATE COMPONENTS */
  /*  ***  TO THEIR BOUNDS  *** */

  if (*p1 >= p0)
    {
      goto L150;
    }

  k = *p1 + 1;
  i__1 = p0;

  for (i__ = k; i__ <= i__1; ++i__)
    {
      j = ipiv[i__];
      t = meps2;

      if (j > 0)
        {
          goto L130;
        }

      t = -t;
      j = -j;
      ipiv[i__] = j;

L130:
      /* Computing MAX */
      d__3 = (d__1 = x[j], fabs(d__1)), d__4 = (d__2 = x0[j], fabs(d__2));
      t *= fmax(d__3, d__4);
      step[j] += t;
      /* L140: */
    }

L150:
  dv2axy_(p, &x[1], &one, &step[1], &x0[1]);

  if (*ns > 0)
    {
      dv7ipr_(&p0, &ipiv1[1], &td[1]);
    }

  /* L999: */
  return 0;
  /*  ***  LAST LINE OF DS7BQN FOLLOWS  *** */
} /* ds7bqn_ */

int ds7dmp_(integer *n, doublereal *x, doublereal *y,
            doublereal *z__, integer *k)
{
  /* Initialized data */

  static doublereal one = 1.;

  /* System generated locals */
  integer i__1, i__2;

  /* Local variables */
  static integer i__, j, l;
  static doublereal t;

  /* ***  SET X = DIAG(Z)**K * Y * DIAG(Z)**K */
  /* ***  FOR X, Y = COMPACTLY STORED LOWER TRIANG. MATRICES */
  /* ***  K = 1 OR -1. */

  /* /6S */
  /*     DOUBLE PRECISION X(1), Y(1), Z(N) */
  /* /7S */
  /* / */
  /* Parameter adjustments */
  --z__;
  --x;
  --y;

  /* Function Body */

  l = 1;

  if (*k >= 0)
    {
      goto L30;
    }

  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      t = one / z__[i__];
      i__2 = i__;

      for (j = 1; j <= i__2; ++j)
        {
          x[l] = t * y[l] / z__[j];
          ++l;
          /* L10: */
        }

      /* L20: */
    }

  goto L999;

L30:
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      t = z__[i__];
      i__2 = i__;

      for (j = 1; j <= i__2; ++j)
        {
          x[l] = t * y[l] * z__[j];
          ++l;
          /* L40: */
        }

      /* L50: */
    }

L999:
  return 0;
  /*  ***  LAST CARD OF DS7DMP FOLLOWS  *** */
} /* ds7dmp_ */

int ds7ipr_(integer *p, integer *ip, doublereal *h__)
{
  /* System generated locals */
  integer i__1, i__2;

  /* Local variables */
  static integer i__, j, k, l, m;
  static doublereal t;
  static integer j1, k1, kk, jm, km, kmj;

  /*  APPLY THE PERMUTATION DEFINED BY IP TO THE ROWS AND COLUMNS OF THE */
  /*  P X P SYMMETRIC MATRIX WHOSE LOWER TRIANGLE IS STORED COMPACTLY IN H. */
  /*  THUS H.OUTPUT(I,J) = H.INPUT(IP(I), IP(J)). */

  /* ***  BODY  *** */

  /* Parameter adjustments */
  --ip;
  --h__;

  /* Function Body */
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j = ip[i__];

      if (j == i__)
        {
          goto L90;
        }

      ip[i__] = abs(j);

      if (j < 0)
        {
          goto L90;
        }

      k = i__;

L10:
      j1 = j;
      k1 = k;

      if (j <= k)
        {
          goto L20;
        }

      j1 = k;
      k1 = j;

L20:
      kmj = k1 - j1;
      l = j1 - 1;
      jm = j1 * l / 2;
      km = k1 * (k1 - 1) / 2;

      if (l <= 0)
        {
          goto L40;
        }

      i__2 = l;

      for (m = 1; m <= i__2; ++m)
        {
          ++jm;
          t = h__[jm];
          ++km;
          h__[jm] = h__[km];
          h__[km] = t;
          /* L30: */
        }

L40:
      ++km;
      kk = km + kmj;
      ++jm;
      t = h__[jm];
      h__[jm] = h__[kk];
      h__[kk] = t;
      j1 = l;
      l = kmj - 1;

      if (l <= 0)
        {
          goto L60;
        }

      i__2 = l;

      for (m = 1; m <= i__2; ++m)
        {
          jm = jm + j1 + m;
          t = h__[jm];
          ++km;
          h__[jm] = h__[km];
          h__[km] = t;
          /* L50: */
        }

L60:

      if (k1 >= *p)
        {
          goto L80;
        }

      l = *p - k1;
      --k1;
      km = kk;
      i__2 = l;

      for (m = 1; m <= i__2; ++m)
        {
          km = km + k1 + m;
          jm = km - kmj;
          t = h__[jm];
          h__[jm] = h__[km];
          h__[km] = t;
          /* L70: */
        }

L80:
      k = j;
      j = ip[k];
      ip[k] = -j;

      if (j > i__)
        {
          goto L10;
        }

L90:
      ;
    }

  /* L999: */
  return 0;
  /*  ***  LAST LINE OF DS7IPR FOLLOWS  *** */
} /* ds7ipr_ */

int ds7lup_(doublereal *a, doublereal *cosmin, integer *p,
            doublereal *size, doublereal *step, doublereal *u, doublereal *w,
            doublereal *wchmtd, doublereal *wscale, doublereal *y)
{
  /* System generated locals */
  integer i__1, i__2;
  doublereal d__1, d__2, d__3;

  /* Local variables */
  static integer i__, j, k;
  static doublereal t;
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *),
         dv2nrm_(integer *, doublereal *);
  extern int ds7lvm_(integer *, doublereal *, doublereal *,
                     doublereal *);
  static doublereal ui, wi, denmin, sdotwm;

  /*  ***  UPDATE SYMMETRIC  A  SO THAT  A * STEP = Y  *** */
  /*  ***  (LOWER TRIANGLE OF  A  STORED ROWWISE       *** */

  /*  ***  PARAMETER DECLARATIONS  *** */

  /*     DIMENSION A(P*(P+1)/2) */

  /*  ***  LOCAL VARIABLES  *** */

  /*     ***  CONSTANTS  *** */

  /*  ***  EXTERNAL FUNCTIONS AND SUBROUTINES  *** */

  /* /6 */
  /*     DATA HALF/0.5D+0/, ONE/1.D+0/, ZERO/0.D+0/ */
  /* /7 */
  /* / */

  /* ----------------------------------------------------------------------- */

  /* Parameter adjustments */
  --a;
  --y;
  --wchmtd;
  --w;
  --u;
  --step;

  /* Function Body */
  sdotwm = dd7tpr_(p, &step[1], &wchmtd[1]);
  denmin = *cosmin * dv2nrm_(p, &step[1]) * dv2nrm_(p, &wchmtd[1]);
  *wscale = 1.;

  if (denmin != 0.)
    {
      /* Computing MIN */
      d__2 = 1., d__3 = (d__1 = sdotwm / denmin, fabs(d__1));
      *wscale = fmin(d__2, d__3);
    }

  t = 0.;

  if (sdotwm != 0.)
    {
      t = *wscale / sdotwm;
    }

  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L10: */
      w[i__] = t * wchmtd[i__];
    }

  ds7lvm_(p, &u[1], &a[1], &step[1]);
  t = (*size * dd7tpr_(p, &step[1], &u[1]) - dd7tpr_(p, &step[1], &y[1])) *
      .5;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L20: */
      u[i__] = t * w[i__] + y[i__] - *size * u[i__];
    }

  /*  ***  SET  A = A + U*(W**T) + W*(U**T)  *** */

  k = 1;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      ui = u[i__];
      wi = w[i__];
      i__2 = i__;

      for (j = 1; j <= i__2; ++j)
        {
          a[k] = *size * a[k] + ui * w[j] + wi * u[j];
          ++k;
          /* L30: */
        }

      /* L40: */
    }

  /* L999: */
  return 0;
  /*  ***  LAST CARD OF DS7LUP FOLLOWS  *** */
} /* ds7lup_ */

int ds7lvm_(integer *p, doublereal *y, doublereal *s,
            doublereal *x)
{
  /* System generated locals */
  integer i__1, i__2;

  /* Local variables */
  static integer i__, j, k;
  extern doublereal dd7tpr_(integer *, doublereal *, doublereal *);
  static doublereal xi;
  static integer im1;

  /*  ***  SET  Y = S * X,  S = P X P SYMMETRIC MATRIX.  *** */
  /*  ***  LOWER TRIANGLE OF  S  STORED ROWWISE.         *** */

  /*  ***  PARAMETER DECLARATIONS  *** */

  /*     DIMENSION S(P*(P+1)/2) */

  /*  ***  LOCAL VARIABLES  *** */

  /*  ***  NO INTRINSIC FUNCTIONS  *** */

  /*  ***  EXTERNAL FUNCTION  *** */

  /* ----------------------------------------------------------------------- */

  /* Parameter adjustments */
  --x;
  --y;
  --s;

  /* Function Body */
  j = 1;
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      y[i__] = dd7tpr_(&i__, &s[j], &x[1]);
      j += i__;
      /* L10: */
    }

  if (*p <= 1)
    {
      goto L999;
    }

  j = 1;
  i__1 = *p;

  for (i__ = 2; i__ <= i__1; ++i__)
    {
      xi = x[i__];
      im1 = i__ - 1;
      ++j;
      i__2 = im1;

      for (k = 1; k <= i__2; ++k)
        {
          y[k] += s[j] * xi;
          ++j;
          /* L30: */
        }

      /* L40: */
    }

L999:
  return 0;
  /*  ***  LAST CARD OF DS7LVM FOLLOWS  *** */
} /* ds7lvm_ */

int dv2axy_(integer *p, doublereal *w, doublereal *a,
            doublereal *x, doublereal *y)
{
  /* System generated locals */
  integer i__1;

  /* Local variables */
  static integer i__;

  /*  ***  SET W = A*X + Y  --  W, X, Y = P-VECTORS, A = SCALAR  *** */

  /* Parameter adjustments */
  --y;
  --x;
  --w;

  /* Function Body */
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L10: */
      w[i__] = *a * x[i__] + y[i__];
    }

  return 0;
} /* dv2axy_ */

doublereal dv2nrm_(integer *p, doublereal *x)
{
  /* Initialized data */

  static doublereal sqteta = 0.;

  /* System generated locals */
  integer i__1;
  doublereal ret_val, d__1;

  /* Local variables */
  static integer i__, j;
  static doublereal r__, t, scale;
  extern doublereal dr7mdc_(integer *);
  static doublereal xi;

  /*  ***  RETURN THE 2-NORM OF THE P-VECTOR X, TAKING  *** */
  /*  ***  CARE TO AVOID THE MOST LIKELY UNDERFLOWS.    *** */

  /* /+ */
  /* / */

  /* /6 */
  /*     DATA ONE/1.D+0/, ZERO/0.D+0/ */
  /* /7 */
  /* / */
  /* Parameter adjustments */
  --x;

  /* Function Body */

  if (*p > 0)
    {
      goto L10;
    }

  ret_val = 0.;
  goto L999;

L10:
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      if (x[i__] != 0.)
        {
          goto L30;
        }

      /* L20: */
    }

  ret_val = 0.;
  goto L999;

L30:
  scale = (d__1 = x[i__], fabs(d__1));

  if (i__ < *p)
    {
      goto L40;
    }

  ret_val = scale;
  goto L999;

L40:
  t = 1.;

  if (sqteta == 0.)
    {
      sqteta = dr7mdc_(&c__2);
    }

  /*     ***  SQTETA IS (SLIGHTLY LARGER THAN) THE SQUARE ROOT OF THE */
  /*     ***  SMALLEST POSITIVE FLOATING POINT NUMBER ON THE MACHINE. */
  /*     ***  THE TESTS INVOLVING SQTETA ARE DONE TO PREVENT UNDERFLOWS. */

  j = i__ + 1;
  i__1 = *p;

  for (i__ = j; i__ <= i__1; ++i__)
    {
      xi = (d__1 = x[i__], fabs(d__1));

      if (xi > scale)
        {
          goto L50;
        }

      r__ = xi / scale;

      if (r__ > sqteta)
        {
          t += r__ * r__;
        }

      goto L60;

L50:
      r__ = scale / xi;

      if (r__ <= sqteta)
        {
          r__ = 0.;
        }

      t = t * r__ * r__ + 1.;
      scale = xi;

L60:
      ;
    }

  ret_val = scale * sqrt(t);

L999:
  return ret_val;
  /*  ***  LAST LINE OF DV2NRM FOLLOWS  *** */
} /* dv2nrm_ */

int dv7cpy_(integer *p, doublereal *y, doublereal *x)
{
  /* System generated locals */
  integer i__1;

  /* Local variables */
  static integer i__;

  /*  ***  SET Y = X, WHERE X AND Y ARE P-VECTORS  *** */

  /* Parameter adjustments */
  --x;
  --y;

  /* Function Body */
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L10: */
      y[i__] = x[i__];
    }

  return 0;
} /* dv7cpy_ */

int dv7dfl_(integer *alg, integer *lv, doublereal *v)
{
  /* System generated locals */
  doublereal d__1, d__2, d__3;

  /* Local variables */
  extern doublereal dr7mdc_(integer *);
  static doublereal machep, mepcrt, sqteps;

  /*  ***  SUPPLY ***SOL (VERSION 2.3) DEFAULT VALUES TO V  *** */

  /*  ***  ALG = 1 MEANS REGRESSION CONSTANTS. */
  /*  ***  ALG = 2 MEANS GENERAL UNCONSTRAINED OPTIMIZATION CONSTANTS. */

  /* DR7MDC... RETURNS MACHINE-DEPENDENT CONSTANTS */

  /*  ***  SUBSCRIPTS FOR V  *** */

  /* /6 */
  /*     DATA ONE/1.D+0/, THREE/3.D+0/ */
  /* /7 */
  /* / */

  /*  ***  V SUBSCRIPT VALUES  *** */

  /* /6 */
  /*     DATA AFCTOL/31/, BIAS/43/, COSMIN/47/, DECFAC/22/, DELTA0/44/, */
  /*    1     DFAC/41/, DINIT/38/, DLTFDC/42/, DLTFDJ/43/, DTINIT/39/, */
  /*    2     D0INIT/40/, EPSLON/19/, ETA0/42/, FUZZ/45/, HUBERC/48/, */
  /*    3     INCFAC/23/, LMAX0/35/, LMAXS/36/, PHMNFC/20/, PHMXFC/21/, */
  /*    4     RDFCMN/24/, RDFCMX/25/, RFCTOL/32/, RLIMIT/46/, RSPTOL/49/, */
  /*    5     SCTOL/37/, SIGMIN/50/, TUNER1/26/, TUNER2/27/, TUNER3/28/, */
  /*    6     TUNER4/29/, TUNER5/30/, XCTOL/33/, XFTOL/34/ */
  /* /7 */
  /* / */

  /* -------------------------------  BODY  -------------------------------- */

  /* Parameter adjustments */
  --v;

  /* Function Body */
  machep = dr7mdc_(&c__3);
  v[31] = 1e-20;

  if (machep > 1e-10)
    {
      /* Computing 2nd power */
      d__1 = machep;
      v[31] = d__1 * d__1;
    }

  v[22] = .5;
  sqteps = dr7mdc_(&c__4);
  v[41] = .6;
  v[39] = 1e-6;
  mepcrt = pow_dd(&machep, &c_b767);
  v[40] = 1.;
  v[19] = .1;
  v[23] = 2.;
  v[35] = 1.;
  v[36] = 1.;
  v[20] = -.1;
  v[21] = .1;
  v[24] = .1;
  v[25] = 4.;
  /* Computing MAX */
  /* Computing 2nd power */
  d__3 = mepcrt;
  d__1 = 1e-10, d__2 = d__3 * d__3;
  v[32] = fmax(d__1, d__2);
  v[37] = v[32];
  v[26] = .1;
  v[27] = 1e-4;
  v[28] = .75;
  v[29] = .5;
  v[30] = .75;
  v[33] = sqteps;
  v[34] = machep * 100.;

  if (*alg >= 2)
    {
      goto L10;
    }

  /*  ***  REGRESSION  VALUES */

  /* Computing MAX */
  d__1 = 1e-6, d__2 = machep * 100.;
  v[47] = fmax(d__1, d__2);
  v[38] = 0.;
  v[44] = sqteps;
  v[42] = mepcrt;
  v[43] = sqteps;
  v[45] = 1.5;
  v[48] = .7;
  v[46] = dr7mdc_(&c__5);
  v[49] = .001;
  v[50] = 1e-4;
  goto L999;

  /*  ***  GENERAL OPTIMIZATION VALUES */

L10:
  v[43] = .8;
  v[38] = -1.;
  v[42] = machep * 1e3;

L999:
  return 0;
  /*  ***  LAST CARD OF DV7DFL FOLLOWS  *** */
} /* dv7dfl_ */

int dv7ipr_(integer *n, integer *ip, doublereal *x)
{
  /* System generated locals */
  integer i__1;

  /* Local variables */
  static integer i__, j, k;
  static doublereal t;

  /*     PERMUTE X SO THAT X.OUTPUT(I) = X.INPUT(IP(I)). */
  /*     IP IS UNCHANGED ON OUTPUT. */

  /* Parameter adjustments */
  --x;
  --ip;

  /* Function Body */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j = ip[i__];

      if (j == i__)
        {
          goto L30;
        }

      if (j > 0)
        {
          goto L10;
        }

      ip[i__] = -j;
      goto L30;

L10:
      t = x[i__];
      k = i__;

L20:
      x[k] = x[j];
      k = j;
      j = ip[k];
      ip[k] = -j;

      if (j > i__)
        {
          goto L20;
        }

      x[k] = t;

L30:
      ;
    }

  /* L999: */
  return 0;
  /*  ***  LAST LINE OF DV7IPR FOLLOWS  *** */
} /* dv7ipr_ */

int dv7scl_(integer *n, doublereal *x, doublereal *a,
            doublereal *y)
{
  /* System generated locals */
  integer i__1;

  /* Local variables */
  static integer i__;

  /*  ***  SET X(I) = A*Y(I), I = 1(1)N  *** */

  /* Parameter adjustments */
  --y;
  --x;

  /* Function Body */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L10: */
      x[i__] = *a * y[i__];
    }

  /* L999: */
  return 0;
  /*  ***  LAST LINE OF DV7SCL FOLLOWS  *** */
} /* dv7scl_ */

int dv7scp_(integer *p, doublereal *y, doublereal *s)
{
  /* System generated locals */
  integer i__1;

  /* Local variables */
  static integer i__;

  /*  ***  SET P-VECTOR Y TO SCALAR S  *** */

  /* Parameter adjustments */
  --y;

  /* Function Body */
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L10: */
      y[i__] = *s;
    }

  return 0;
} /* dv7scp_ */

int dv7shf_(integer *n, integer *k, doublereal *x)
{
  /* System generated locals */
  integer i__1;

  /* Local variables */
  static integer i__;
  static doublereal t;
  static integer nm1;

  /*  ***  SHIFT X(K),...,X(N) LEFT CIRCULARLY ONE POSITION  *** */

  /* Parameter adjustments */
  --x;

  /* Function Body */
  if (*k >= *n)
    {
      goto L999;
    }

  nm1 = *n - 1;
  t = x[*k];
  i__1 = nm1;

  for (i__ = *k; i__ <= i__1; ++i__)
    {
      /* L10: */
      x[i__] = x[i__ + 1];
    }

  x[*n] = t;
L999:
  return 0;
} /* dv7shf_ */

int dv7vmp_(integer *n, doublereal *x, doublereal *y,
            doublereal *z__, integer *k)
{
  /* System generated locals */
  integer i__1;

  /* Local variables */
  static integer i__;

  /* ***  SET X(I) = Y(I) * Z(I)**K, 1 .LE. I .LE. N (FOR K = 1 OR -1)  *** */

  /* Parameter adjustments */
  --z__;
  --y;
  --x;

  /* Function Body */
  if (*k >= 0)
    {
      goto L20;
    }

  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L10: */
      x[i__] = y[i__] / z__[i__];
    }

  goto L999;

L20:
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L30: */
      x[i__] = y[i__] * z__[i__];
    }

L999:
  return 0;
  /*  ***  LAST CARD OF DV7VMP FOLLOWS  *** */
} /* dv7vmp_ */

integer i1mach_(integer *i)
{
  switch (*i)
    {
      case 1:  return 5;    /* standard input  unit -- may need changing */

      case 2:  return 6;    /* standard output unit -- may need changing */

      case 3:  return 7;    /* standard punch  unit -- may need changing */

      case 4:  return 0;    /* standard error  unit -- may need changing */

      case 5:  return 32;    /* bits per integer -- may need changing */

      case 6:  return sizeof(int);    /* Fortran 77 value: 1 character */

        /*    per character storage unit */
      case 7:  return 2;    /* base for integers -- may need changing */

      case 8:  return 31;    /* digits of integer base -- may need changing */

      case 9:  return std::numeric_limits< integer >::max();

      case 10: return FLT_RADIX;

      case 11: return FLT_MANT_DIG;

      case 12: return FLT_MIN_EXP;

      case 13: return FLT_MAX_EXP;

      case 14: return DBL_MANT_DIG;

      case 15: return DBL_MIN_EXP;

      case 16: return DBL_MAX_EXP;
    }

  fprintf(stderr, "invalid argument: i1mach(%ld)\n", *i);
  exit(1);
  return 0; /* for compilers that complain of missing return values */
} /* i1mach_ */

int i7copy_(integer *p, integer *y, integer *x)
{
  /* System generated locals */
  integer i__1;

  /* Local variables */
  static integer i__;

  /*  ***  SET Y = X, WHERE X AND Y ARE INTEGER P-VECTORS  *** */

  /* Parameter adjustments */
  --x;
  --y;

  /* Function Body */
  i__1 = *p;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L10: */
      y[i__] = x[i__];
    }

  /* L999: */
  return 0;
} /* i7copy_ */

integer i7mdcn_(integer *k)
{
  /* Initialized data */

  static integer mdperm[3] = {2, 4, 1 };

  /* System generated locals */
  integer ret_val;

  /* Local variables */
  extern integer i1mach_(integer *);

  /*  ***  RETURN INTEGER MACHINE-DEPENDENT CONSTANTS  *** */

  /*     ***  K = 1 MEANS RETURN STANDARD OUTPUT UNIT NUMBER.   *** */
  /*     ***  K = 2 MEANS RETURN ALTERNATE OUTPUT UNIT NUMBER.  *** */
  /*     ***  K = 3 MEANS RETURN  INPUT UNIT NUMBER.            *** */
  /*          (NOTE -- K = 2, 3 ARE USED ONLY BY TEST PROGRAMS.) */

  /*  +++  PORT VERSION FOLLOWS... */
  /* old version
  /* ret_val = i1mach_(&mdperm[*k - 1]); */
  /* new version */
  ret_val = i1mach_(&mdperm[(0 + (0 + (*k - 1 << 2))) / 4]);
  /*  +++  END OF PORT VERSION  +++ */

  /*  +++  NON-PORT VERSION FOLLOWS... */
  /*     INTEGER MDCON(3) */
  /*     DATA MDCON(1)/6/, MDCON(2)/8/, MDCON(3)/5/ */
  /*     I7MDCN = MDCON(K) */
  /*  +++  END OF NON-PORT VERSION  +++ */

  /* L999: */
  return ret_val;
  /*  ***  LAST CARD OF I7MDCN FOLLOWS  *** */
} /* i7mdcn_ */

int i7pnvr_(integer *n, integer *x, integer *y)
{
  /* System generated locals */
  integer i__1;

  /* Local variables */
  static integer i__, j;

  /*  ***  SET PERMUTATION VECTOR X TO INVERSE OF Y  *** */

  /* Parameter adjustments */
  --y;
  --x;

  /* Function Body */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      j = y[i__];
      x[j] = i__;
      /* L10: */
    }

  /* L999: */
  return 0;
  /*  ***  LAST LINE OF I7PNVR FOLLOWS  *** */
} /* i7pnvr_ */

int i7shft_(integer *n, integer *k, integer *x)
{
  /* System generated locals */
  integer i__1;

  /* Local variables */
  static integer i__, t, k1, ii, nm1;

  /*  ***  SHIFT X(K),...,X(N) LEFT CIRCULARLY ONE POSITION IF K .GT. 0. */
  /*  ***  SHIFT X(-K),...,X(N) RIGHT CIRCULARLY ONE POSITION IF K .LT. 0. */

  /* Parameter adjustments */
  --x;

  /* Function Body */
  if (*k < 0)
    {
      goto L20;
    }

  if (*k >= *n)
    {
      goto L999;
    }

  nm1 = *n - 1;
  t = x[*k];
  i__1 = nm1;

  for (i__ = *k; i__ <= i__1; ++i__)
    {
      /* L10: */
      x[i__] = x[i__ + 1];
    }

  x[*n] = t;
  goto L999;

L20:
  k1 = -(*k);

  if (k1 >= *n)
    {
      goto L999;
    }

  t = x[*n];
  nm1 = *n - k1;
  i__1 = nm1;

  for (ii = 1; ii <= i__1; ++ii)
    {
      i__ = *n - ii;
      x[i__ + 1] = x[i__];
      /* L30: */
    }

  x[k1] = t;

L999:
  return 0;
} /* i7shft_ */

logical stopx_(integer *idummy)
{
  /* System generated locals */
  logical ret_val;

  /*     *****PARAMETERS... */

  /*     .................................................................. */

  /*     *****PURPOSE... */
  /*     THIS FUNCTION MAY SERVE AS THE STOPX (ASYNCHRONOUS INTERRUPTION) */
  /*     FUNCTION FOR THE NL2SOL (NONLINEAR LEAST-SQUARES) PACKAGE AT */
  /*     THOSE INSTALLATIONS WHICH DO NOT WISH TO IMPLEMENT A */
  /*     DYNAMIC STOPX. */

  /*     *****ALGORITHM NOTES... */
  /*     AT INSTALLATIONS WHERE THE NL2SOL SYSTEM IS USED */
  /*     INTERACTIVELY, THIS DUMMY STOPX SHOULD BE REPLACED BY A */
  /*     FUNCTION THAT RETURNS .TRUE. IF AND ONLY IF THE INTERRUPT */
  /*     (BREAK) KEY HAS BEEN PRESSED SINCE THE LAST CALL ON STOPX. */

  /*     .................................................................. */

  ret_val = FALSE_;
  return ret_val;
} /* stopx_ */

/**** Translated from flibs ****/

int s_copy(char *a, char *b, ftnlen la, ftnlen lb)
{
  char *aend, *bend;
  aend = a + la;

  if (la <= lb)
    if (a <= b || a >= b + la)
      while (a < aend)
        *a++ = *b++;
    else
      for (b += la; a < aend;)
        *--aend = *--b;

  else
    {
      bend = b + lb;

      if (a <= b || a >= bend)
        while (b < bend)
          *a++ = *b++;
      else
        {
          a += lb;

          while (b < bend)
            *--a = *--bend;

          a += lb;
        }

      while (a < aend)
        *a++ = ' ';
    }

  return 1;
}
