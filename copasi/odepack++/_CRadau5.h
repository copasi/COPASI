// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include "copasi/odepack++/_dc_decsol.h"
#include "copasi/odepack++/Cxerrwd.h"

class _CRadau5 : public Cxerrwd
{
public:
  // THIS FILE CONTAINS THE SUBROUTINE RADAU5 AND ALL ITS DEPENDENCIES.
  // RADAR5 IS A FORTRAN 77 IMPLEMENTATION OF THE RADAU IIA METHOD OF
  // ORDER 5. IT WAS DEVELOPED BY E. HAIRER AND G. WANNER, UNIVERSITY
  // OF ZURICH, SWITZERLAND. THE ORIGINAL SOURCE CODE CAN BE FOUND AT
  // http://www.unige.ch/~hairer/software.html.

  template < typename T >
  T dim(const T & a, const T & b)
  {
    return (a > b) ? a - b : 0;
  }

  struct conra5
  {
    int nn = 0;
    int nn2 = 0;
    int nn3 = 0;
    int nn4 = 0;
    double xsol = 0.0;
    double hsol = 0.0;
    double c2m1 = 0.0;
    double c1m1 = 0.0;
  };

  struct common : public _dc_decsol::common
    , public conra5
  {};

  //C     evalF          NAME (EXTERNAL) OF SUBROUTINE COMPUTING THE
  //C                    VALUE OF F(X,Y):
  //C                    SUBROUTINE evalF(N,X,Y,F,RPAR,IPAR)
  //C                    DOUBLE PRECISION X,Y(N),F(N)
  typedef _dc_decsol::evalF evalF;

  //C     evalJ          SUBROUTINE evalJ(N,X,Y,DFY,LDFY,RPAR,IPAR)
  //C                    doublereal PRECISION X,Y(N),DFY(LDFY,N)
  //C                    DFY(1,1)= ...
  typedef std::function< void(const integer & n,
                              const doublereal & x,
                              const CVectorCore< doublereal > & y,
                              CMatrix< doublereal > & dfy,
                              const integer & ldfy,
                              const CVectorCore< doublereal > & rpar,
                              const CVectorCore< integer > & ipar) >
    evalJ;

  //C                    SUBROUTINE evalM(N,AM,LMAS,RPAR,IPAR)
  //C                    doublereal PRECISION AM(LMAS,N)
  //C                    AM(1,1)= ....
  typedef std::function< void(const integer & n,
                              CMatrix< doublereal > & am,
                              const integer & lmas,
                              const CVectorCore< doublereal > & rpar,
                              const CVectorCore< integer > & ipar) >
    evalM;

  //C                    SUBROUTINE evalO (NR,XOLD,X,Y,CONT,LRC,N,
  //C                                       RPAR,IPAR,IRTRN)
  //C                    doublereal PRECISION X,Y(N),CONT(LRC)
  typedef std::function< void(const integer & nr,
                              const doublereal & xold,
                              const doublereal & x,
                              const CVectorCore< doublereal > & y,
                              const CVectorCore< doublereal > & cont,
                              const integer & lrc,
                              const integer & n,
                              const CVectorCore< doublereal > & rpar,
                              const CVectorCore< integer > & ipar,
                              const integer & irtrn) >
    evalO;

  _CRadau5();

  //C ----------------------------------------------------------
  //C     NUMERICAL SOLUTION OF A STIFF (OR DIFFERENTIAL ALGEBRAIC)
  //C     SYSTEM OF FIRST 0RDER ORDINARY DIFFERENTIAL EQUATIONS
  //C                     M*Y'=F(X,Y).
  //C     THE SYSTEM CAN BE (LINEARLY) IMPLICIT (MASS-MATRIX M .NE. I)
  //C     OR EXPLICIT (M=I).
  //C     THE METHOD USED IS AN IMPLICIT RUNGE-KUTTA METHOD (RADAU IIA)
  //C     OF ORDER 5 WITH STEP SIZE CONTROL AND CONTINUOUS OUTPUT.
  //C     CF. SECTION IV.8
  //C
  //C     AUTHORS: E. HAIRER AND G. WANNER
  //C              UNIVERSITE DE GENEVE, DEPT. DE MATHEMATIQUES
  //C              CH-1211 GENEVE 24, SWITZERLAND
  //C              E-MAIL:  Ernst.Hairer@math.unige.ch
  //C                       Gerhard.Wanner@math.unige.ch
  //C
  //C     THIS CODE IS PART OF THE BOOK:
  //C         E. HAIRER AND G. WANNER, SOLVING ORDINARY DIFFERENTIAL
  //C         EQUATIONS II. STIFF AND DIFFERENTIAL-ALGEBRAIC PROBLEMS.
  //C         SPRINGER SERIES IN COMPUTATIONAL MATHEMATICS 14,
  //C         SPRINGER-VERLAG 1991, SECOND EDITION 1996.
  //C
  //C     VERSION OF JULY 9, 1996
  //C     (latest small correction: January 18, 2002)
  //C
  //C     INPUT PARAMETERS
  //C     ----------------
  //C     N           DIMENSION OF THE SYSTEM
  //C
  //C     evalF       NAME (EXTERNAL) OF SUBROUTINE COMPUTING THE
  //C                 VALUE OF F(X,Y):
  //C                    SUBROUTINE evalF(N,X,Y,F,RPAR,IPAR)
  //C                    doublereal PRECISION X,Y(N),F(N)
  //C                    F(1)=...   ETC.
  //C                 RPAR, IPAR (SEE BELOW)
  //C
  //C     X           INITIAL X-VALUE
  //C
  //C     Y(N)        INITIAL VALUES FOR Y
  //C
  //C     XEND        FINAL X-VALUE (XEND-X MAY BE POSITIVE OR NEGATIVE)
  //C
  //C     H           INITIAL STEP SIZE GUESS;
  //C                 FOR STIFF EQUATIONS WITH INITIAL TRANSIENT,
  //C                 H=1.D0/(NORM OF F'), USUALLY 1.D-3 OR 1.D-5, IS GOOD.
  //C                 THIS CHOICE IS NOT VERY IMPORTANT, THE STEP SIZE IS
  //C                 QUICKLY ADAPTED. (IF H=0.D0, THE CODE PUTS H=1.D-6).
  //C
  //C     RTOL,ATOL   RELATIVE AND ABSOLUTE ERROR TOLERANCES. THEY
  //C                 CAN BE BOTH SCALARS OR ELSE BOTH VECTORS OF LENGTH N.
  //C
  //C     ITOL        SWITCH FOR RTOL AND ATOL:
  //C                   ITOL=0: BOTH RTOL AND ATOL ARE SCALARS.
  //C                     THE CODE KEEPS, ROUGHLY, THE LOCAL ERROR OF
  //C                     Y(I) BELOW RTOL*ABS(Y(I))+ATOL
  //C                   ITOL=1: BOTH RTOL AND ATOL ARE VECTORS.
  //C                     THE CODE KEEPS THE LOCAL ERROR OF Y(I) BELOW
  //C                     RTOL(I)*ABS(Y(I))+ATOL(I).
  //C
  //C     evalJ       NAME (EXTERNAL) OF THE SUBROUTINE WHICH COMPUTES
  //C                 THE PARTIAL DERIVATIVES OF F(X,Y) WITH RESPECT TO Y
  //C                 (THIS ROUTINE IS ONLY CALLED IF IJAC=1; SUPPLY
  //C                 A DUMMY SUBROUTINE IN THE CASE IJAC=0).
  //C                 FOR IJAC=1, THIS SUBROUTINE MUST HAVE THE FORM
  //C                    SUBROUTINE evalJ(N,X,Y,DFY,LDFY,RPAR,IPAR)
  //C                    doublereal PRECISION X,Y(N),DFY(LDFY,N)
  //C                    DFY(1,1)= ...
  //C                 LDFY, THE COLUMN-LENGTH OF THE ARRAY, IS
  //C                 FURNISHED BY THE CALLING PROGRAM.
  //C                 IF (MLJAC.EQ.N) THE JACOBIAN IS SUPPOSED TO
  //C                    BE FULL AND THE PARTIAL DERIVATIVES ARE
  //C                    STORED IN DFY AS
  //C                       DFY(I,J) = PARTIAL F(I) / PARTIAL Y(J)
  //C                 ELSE, THE JACOBIAN IS TAKEN AS BANDED AND
  //C                    THE PARTIAL DERIVATIVES ARE STORED
  //C                    DIAGONAL-WISE AS
  //C                       DFY(I-J+MUJAC+1,J) = PARTIAL F(I) / PARTIAL Y(J).
  //C
  //C     IJAC        SWITCH FOR THE COMPUTATION OF THE JACOBIAN:
  //C                    IJAC=0: JACOBIAN IS COMPUTED INTERNALLY BY FINITE
  //C                       DIFFERENCES, SUBROUTINE "evalJ" IS NEVER CALLED.
  //C                    IJAC=1: JACOBIAN IS SUPPLIED BY SUBROUTINE evalJ.
  //C
  //C     MLJAC       SWITCH FOR THE BANDED STRUCTURE OF THE JACOBIAN:
  //C                    MLJAC=N: JACOBIAN IS A FULL MATRIX. THE LINEAR
  //C                       ALGEBRA IS DONE BY FULL-MATRIX GAUSS-ELIMINATION.
  //C                    0<=MLJAC<N: MLJAC IS THE LOWER BANDWITH OF JACOBIAN
  //C                       MATRIX (>= NUMBER OF NON-ZERO DIAGONALS BELOW
  //C                       THE MAIN DIAGONAL).
  //C
  //C     MUJAC       UPPER BANDWITH OF JACOBIAN  MATRIX (>= NUMBER OF NON-
  //C                 ZERO DIAGONALS ABOVE THE MAIN DIAGONAL).
  //C                 NEED NOT BE DEFINED IF MLJAC=N.
  //C
  //C     ----   MAS,IMAS,MLMAS, AND MUMAS HAVE ANALOG MEANINGS      -----
  //C     ----   FOR THE "MASS MATRIX" (THE MATRIX "M" OF SECTION IV.8): -
  //C
  //C     evalM       NAME (EXTERNAL) OF SUBROUTINE COMPUTING THE MASS-
  //C                 MATRIX M.
  //C                 IF IMAS=0, THIS MATRIX IS ASSUMED TO BE THE IDENTITY
  //C                 MATRIX AND NEEDS NOT TO BE DEFINED;
  //C                 SUPPLY A DUMMY SUBROUTINE IN THIS CASE.
  //C                 IF IMAS=1, THE SUBROUTINE evalM IS OF THE FORM
  //C                    SUBROUTINE evalM(N,AM,LMAS,RPAR,IPAR)
  //C                    doublereal PRECISION AM(LMAS,N)
  //C                    AM(1,1)= ....
  //C                    IF (MLMAS.EQ.N) THE MASS-MATRIX IS STORED
  //C                    AS FULL MATRIX LIKE
  //C                         AM(I,J) = M(I,J)
  //C                    ELSE, THE MATRIX IS TAKEN AS BANDED AND STORED
  //C                    DIAGONAL-WISE AS
  //C                         AM(I-J+MUMAS+1,J) = M(I,J).
  //C
  //C     IMAS       GIVES INFORMATION ON THE MASS-MATRIX:
  //C                    IMAS=0: M IS SUPPOSED TO BE THE IDENTITY
  //C                       MATRIX, MAS IS NEVER CALLED.
  //C                    IMAS=1: MASS-MATRIX  IS SUPPLIED.
  //C
  //C     MLMAS       SWITCH FOR THE BANDED STRUCTURE OF THE MASS-MATRIX:
  //C                    MLMAS=N: THE FULL MATRIX CASE. THE LINEAR
  //C                       ALGEBRA IS DONE BY FULL-MATRIX GAUSS-ELIMINATION.
  //C                    0<=MLMAS<N: MLMAS IS THE LOWER BANDWITH OF THE
  //C                       MATRIX (>= NUMBER OF NON-ZERO DIAGONALS BELOW
  //C                       THE MAIN DIAGONAL).
  //C                 MLMAS IS SUPPOSED TO BE .LE. MLJAC.
  //C
  //C     MUMAS       UPPER BANDWITH OF MASS-MATRIX (>= NUMBER OF NON-
  //C                 ZERO DIAGONALS ABOVE THE MAIN DIAGONAL).
  //C                 NEED NOT BE DEFINED IF MLMAS=N.
  //C                 MUMAS IS SUPPOSED TO BE .LE. MUJAC.
  //C
  //C     evalO      NAME (EXTERNAL) OF SUBROUTINE PROVIDING THE
  //C                 NUMERICAL SOLUTION DURING INTEGRATION.
  //C                 IF IOUT=1, IT IS CALLED AFTER EVERY SUCCESSFUL STEP.
  //C                 SUPPLY A DUMMY SUBROUTINE IF IOUT=0.
  //C                 IT MUST HAVE THE FORM
  //C                    SUBROUTINE evalO (NR,XOLD,X,Y,CONT,LRC,N,
  //C                                       RPAR,IPAR,IRTRN)
  //C                    doublereal PRECISION X,Y(N),CONT(LRC)
  //C                    ....
  //C                 evalO FURNISHES THE SOLUTION "Y" AT THE NR-TH
  //C                    GRID-POinteger "X" (THEREBY THE INITIAL VALUE IS
  //C                    THE FIRST GRID-POINT).
  //C                 "XOLD" IS THE PRECEEDING GRID-POINT.
  //C                 "IRTRN" SERVES TO INTERRUPT THE INTEGRATION. IF IRTRN
  //C                    IS SET <0, RADAU5 RETURNS TO THE CALLING PROGRAM.
  //C
  //C          -----  CONTINUOUS OUTPUT: -----
  //C                 DURING CALLS TO "evalO", A CONTINUOUS SOLUTION
  //C                 FOR THE INTERVAL [XOLD,X] IS AVAILABLE THROUGH
  //C                 THE FUNCTION
  //C                        >>>   CONTR5(I,S,CONT,LRC)   <<<
  //C                 WHICH PROVIDES AN APPROXIMATION TO THE I-TH
  //C                 COMPONENT OF THE SOLUTION AT THE POinteger S. THE VALUE
  //C                 S SHOULD LIE IN THE INTERVAL [XOLD,X].
  //C                 DO NOT CHANGE THE ENTRIES OF CONT(LRC), IF THE
  //C                 DENSE OUTPUT FUNCTION IS USED.
  //C
  //C     IOUT        SWITCH FOR CALLING THE SUBROUTINE evalO:
  //C                    IOUT=0: SUBROUTINE IS NEVER CALLED
  //C                    IOUT=1: SUBROUTINE IS AVAILABLE FOR OUTPUT.
  //C
  //C     WORK        ARRAY OF WORKING SPACE OF LENGTH "LWORK".
  //C                 WORK(1), WORK(2),.., WORK(20) SERVE AS PARAMETERS
  //C                 FOR THE CODE. FOR STANDARD USE OF THE CODE
  //C                 WORK(1),..,WORK(20) MUST BE SET TO ZERO BEFORE
  //C                 CALLING. SEE BELOW FOR A MORE SOPHISTICATED USE.
  //C                 WORK(21),..,WORK(LWORK) SERVE AS WORKING SPACE
  //C                 FOR ALL VECTORS AND MATRICES.
  //C                 "LWORK" MUST BE AT LEAST
  //C                             N*(LJAC+LMAS+3*LE+12)+20
  //C                 WHERE
  //C                    LJAC=N              IF MLJAC=N (FULL JACOBIAN)
  //C                    LJAC=MLJAC+MUJAC+1  IF MLJAC<N (BANDED JACOBIAN.)
  //C                 AND
  //C                    LMAS=0              IF IMAS=0
  //C                    LMAS=N              IF IMAS=1 AND MLMAS=N (FULL)
  //C                    LMAS=MLMAS+MUMAS+1  IF MLMAS<N (BANDED MASS-M.)
  //C                 AND
  //C                    LE=N               IF MLJAC=N (FULL JACOBIAN)
  //C                    LE=2*MLJAC+MUJAC+1 IF MLJAC<N (BANDED JACOBIAN.)
  //C
  //C                 IN THE USUAL CASE WHERE THE JACOBIAN IS FULL AND THE
  //C                 MASS-MATRIX IS THE INDENTITY (IMAS=0), THE MINIMUM
  //C                 STORAGE REQUIREMENT IS
  //C                             LWORK = 4*N*N+12*N+20.
  //C                 IF IWORK(9)=M1>0 THEN "LWORK" MUST BE AT LEAST
  //C                          N*(LJAC+12)+(N-M1)*(LMAS+3*LE)+20
  //C                 WHERE IN THE DEFINITIONS OF LJAC, LMAS AND LE THE
  //C                 NUMBER N CAN BE REPLACED BY N-M1.
  //C
  //C     LWORK       DECLARED LENGTH OF ARRAY "WORK".
  //C
  //C     IWORK       INTEGER WORKING SPACE OF LENGTH "LIWORK".
  //C                 IWORK(1),IWORK(2),...,IWORK(20) SERVE AS PARAMETERS
  //C                 FOR THE CODE. FOR STANDARD USE, SET IWORK(1),..,
  //C                 IWORK(20) TO ZERO BEFORE CALLING.
  //C                 IWORK(21),...,IWORK(LIWORK) SERVE AS WORKING AREA.
  //C                 "LIWORK" MUST BE AT LEAST 3*N+20.
  //C
  //C     LIWORK      DECLARED LENGTH OF ARRAY "IWORK".
  //C
  //C     RPAR, IPAR  REAL AND INTEGER PARAMETERS (OR PARAMETER ARRAYS) WHICH
  //C                 CAN BE USED FOR COMMUNICATION BETWEEN YOUR CALLING
  //C                 PROGRAM AND THE evalF, evalJ, evalM, evalO SUBROUTINES.
  //C
  //C ----------------------------------------------------------------------
  //C
  //C     SOPHISTICATED SETTING OF PARAMETERS
  //C     -----------------------------------
  //C              SEVERAL PARAMETERS OF THE CODE ARE TUNED TO MAKE IT WORK
  //C              WELL. THEY MAY BE DEFINED BY SETTING WORK(1),...
  //C              AS WELL AS IWORK(1),... DIFFERENT FROM ZERO.
  //C              FOR ZERO INPUT, THE CODE CHOOSES DEFAULT VALUES:
  //C
  //C    IWORK(1)  IF IWORK(1).NE.0, THE CODE TRANSFORMS THE JACOBIAN
  //C              MATRIX TO HESSENBERG FORM. THIS IS PARTICULARLY
  //C              ADVANTAGEOUS FOR LARGE SYSTEMS WITH FULL JACOBIAN.
  //C              IT DOES NOT WORK FOR BANDED JACOBIAN (MLJAC<N)
  //C              AND NOT FOR IMPLICIT SYSTEMS (IMAS=1).
  //C
  //C    IWORK(2)  THIS IS THE MAXIMAL NUMBER OF ALLOWED STEPS.
  //C              THE DEFAULT VALUE (FOR IWORK(2)=0) IS 100000.
  //C
  //C    IWORK(3)  THE MAXIMUM NUMBER OF NEWTON ITERATIONS FOR THE
  //C              SOLUTION OF THE IMPLICIT SYSTEM IN EACH STEP.
  //C              THE DEFAULT VALUE (FOR IWORK(3)=0) IS 7.
  //C
  //C    IWORK(4)  IF IWORK(4).EQ.0 THE EXTRAPOLATED COLLOCATION SOLUTION
  //C              IS TAKEN AS STARTING VALUE FOR NEWTON'S METHOD.
  //C              IF IWORK(4).NE.0 ZERO STARTING VALUES ARE USED.
  //C              THE LATTER IS RECOMMENDED IF NEWTON'S METHOD HAS
  //C              DIFFICULTIES WITH CONVERGENCE (THIS IS THE CASE WHEN
  //C              NSTEP IS LARGER THAN NACCPT + NREJCT; SEE OUTPUT PARAM.).
  //C              DEFAULT IS IWORK(4)=0.
  //C
  //C       THE FOLLOWING 3 PARAMETERS ARE IMPORTANT FOR
  //C       DIFFERENTIAL-ALGEBRAIC SYSTEMS OF INDEX > 1.
  //C       THE FUNCTION-SUBROUTINE SHOULD BE WRITTEN SUCH THAT
  //C       THE INDEX 1,2,3 VARIABLES APPEAR IN THIS ORDER.
  //C       IN ESTIMATING THE ERROR THE INDEX 2 VARIABLES ARE
  //C       MULTIPLIED BY H, THE INDEX 3 VARIABLES BY H**2.
  //C
  //C    IWORK(5)  DIMENSION OF THE INDEX 1 VARIABLES (MUST BE > 0). FOR
  //C              ODE'S THIS EQUALS THE DIMENSION OF THE SYSTEM.
  //C              DEFAULT IWORK(5)=N.
  //C
  //C    IWORK(6)  DIMENSION OF THE INDEX 2 VARIABLES. DEFAULT IWORK(6)=0.
  //C
  //C    IWORK(7)  DIMENSION OF THE INDEX 3 VARIABLES. DEFAULT IWORK(7)=0.
  //C
  //C    IWORK(8)  SWITCH FOR STEP SIZE STRATEGY
  //C              IF IWORK(8).EQ.1  MOD. PREDICTIVE CONTROLLER (GUSTAFSSON)
  //C              IF IWORK(8).EQ.2  CLASSICAL STEP SIZE CONTROL
  //C              THE DEFAULT VALUE (FOR IWORK(8)=0) IS IWORK(8)=1.
  //C              THE CHOICE IWORK(8).EQ.1 SEEMS TO PRODUCE SAFER RESULTS;
  //C              FOR SIMPLE PROBLEMS, THE CHOICE IWORK(8).EQ.2 PRODUCES
  //C              OFTEN SLIGHTLY FASTER RUNS
  //C
  //C       IF THE DIFFERENTIAL SYSTEM HAS THE SPECIAL STRUCTURE THAT
  //C            Y(I)' = Y(I+M2)   FOR  I=1,...,M1,
  //C       WITH M1 A MULTIPLE OF M2, A SUBSTANTIAL GAIN IN COMPUTERTIME
  //C       CAN BE ACHIEVED BY SETTING THE PARAMETERS IWORK(9) AND IWORK(10).
  //C       E.G., FOR SECOND ORDER SYSTEMS P'=V, V'=G(P,V), WHERE P AND V ARE
  //C       VECTORS OF DIMENSION N/2, ONE HAS TO PUT M1=M2=N/2.
  //C       FOR M1>0 SOME OF THE INPUT PARAMETERS HAVE DIFFERENT MEANINGS:
  //C       - JAC: ONLY THE ELEMENTS OF THE NON-TRIVIAL PART OF THE
  //C              JACOBIAN HAVE TO BE STORED
  //C              IF (MLJAC.EQ.N-M1) THE JACOBIAN IS SUPPOSED TO BE FULL
  //C                 DFY(I,J) = PARTIAL F(I+M1) / PARTIAL Y(J)
  //C                FOR I=1,N-M1 AND J=1,N.
  //C              ELSE, THE JACOBIAN IS BANDED (M1 = M2 * MM)
  //C                 DFY(I-J+MUJAC+1,J+K*M2) = PARTIAL F(I+M1) / PARTIAL Y(J+K*M2)
  //C                FOR I=1,MLJAC+MUJAC+1 AND J=1,M2 AND K=0,MM.
  //C       - MLJAC: MLJAC=N-M1: IF THE NON-TRIVIAL PART OF THE JACOBIAN IS FULL
  //C                0<=MLJAC<N-M1: IF THE (MM+1) SUBMATRICES (FOR K=0,MM)
  //C                     PARTIAL F(I+M1) / PARTIAL Y(J+K*M2),  I,J=1,M2
  //C                    ARE BANDED, MLJAC IS THE MAXIMAL LOWER BANDWIDTH
  //C                    OF THESE MM+1 SUBMATRICES
  //C       - MUJAC: MAXIMAL UPPER BANDWIDTH OF THESE MM+1 SUBMATRICES
  //C                NEED NOT BE DEFINED IF MLJAC=N-M1
  //C       - MAS: IF IMAS=0 THIS MATRIX IS ASSUMED TO BE THE IDENTITY AND
  //C              NEED NOT BE DEFINED. SUPPLY A DUMMY SUBROUTINE IN THIS CASE.
  //C              IT IS ASSUMED THAT ONLY THE ELEMENTS OF RIGHT LOWER BLOCK OF
  //C              DIMENSION N-M1 DIFFER FROM THAT OF THE IDENTITY MATRIX.
  //C              IF (MLMAS.EQ.N-M1) THIS SUBMATRIX IS SUPPOSED TO BE FULL
  //C                 AM(I,J) = M(I+M1,J+M1)     FOR I=1,N-M1 AND J=1,N-M1.
  //C              ELSE, THE MASS MATRIX IS BANDED
  //C                 AM(I-J+MUMAS+1,J) = M(I+M1,J+M1)
  //C       - MLMAS: MLMAS=N-M1: IF THE NON-TRIVIAL PART OF M IS FULL
  //C                0<=MLMAS<N-M1: LOWER BANDWIDTH OF THE MASS MATRIX
  //C       - MUMAS: UPPER BANDWIDTH OF THE MASS MATRIX
  //C                NEED NOT BE DEFINED IF MLMAS=N-M1
  //C
  //C    IWORK(9)  THE VALUE OF M1.  DEFAULT M1=0.
  //C
  //C    IWORK(10) THE VALUE OF M2.  DEFAULT M2=M1.
  //C
  //C ----------
  //C
  //C    WORK(1)   UROUND, THE ROUNDING UNIT, DEFAULT 1.D-16.
  //C
  //C    WORK(2)   THE SAFETY FACTOR IN STEP SIZE PREDICTION,
  //C              DEFAULT 0.9D0.
  //C
  //C    WORK(3)   DECIDES WHETHER THE JACOBIAN SHOULD BE RECOMPUTED;
  //C              INCREASE WORK(3), TO 0.1 SAY, WHEN JACOBIAN EVALUATIONS
  //C              ARE COSTLY. FOR SMALL SYSTEMS WORK(3) SHOULD BE SMALLER
  //C              (0.001D0, SAY). NEGATIV WORK(3) FORCES THE CODE TO
  //C              COMPUTE THE JACOBIAN AFTER EVERY ACCEPTED STEP.
  //C              DEFAULT 0.001D0.
  //C
  //C    WORK(4)   STOPPING CRITERION FOR NEWTON'S METHOD, USUALLY CHOSEN <1.
  //C              SMALLER VALUES OF WORK(4) MAKE THE CODE SLOWER, BUT SAFER.
  //C              DEFAULT MIN(0.03D0,RTOL(1)**0.5D0)
  //C
  //C    WORK(5) AND WORK(6) : IF WORK(5) < HNEW/HOLD < WORK(6), THEN THE
  //C              STEP SIZE IS NOT CHANGED. THIS SAVES, TOGETHER WITH A
  //C              LARGE WORK(3), LU-DECOMPOSITIONS AND COMPUTING TIME FOR
  //C              LARGE SYSTEMS. FOR SMALL SYSTEMS ONE MAY HAVE
  //C              WORK(5)=1.D0, WORK(6)=1.2D0, FOR LARGE FULL SYSTEMS
  //C              WORK(5)=0.99D0, WORK(6)=2.D0 MIGHT BE GOOD.
  //C              DEFAULTS WORK(5)=1.D0, WORK(6)=1.2D0 .
  //C
  //C    WORK(7)   MAXIMAL STEP SIZE, DEFAULT XEND-X.
  //C
  //C    WORK(8), WORK(9)   PARAMETERS FOR STEP SIZE SELECTION
  //C              THE NEW STEP SIZE IS CHOSEN SUBJECT TO THE RESTRICTION
  //C                 WORK(8) <= HNEW/HOLD <= WORK(9)
  //C              DEFAULT VALUES: WORK(8)=0.2D0, WORK(9)=8.D0
  //C
  //C-----------------------------------------------------------------------
  //C
  //C     OUTPUT PARAMETERS
  //C     -----------------
  //C     X           X-VALUE FOR WHICH THE SOLUTION HAS BEEN COMPUTED
  //C                 (AFTER SUCCESSFUL RETURN X=XEND).
  //C
  //C     Y(N)        NUMERICAL SOLUTION AT X
  //C
  //C     H           PREDICTED STEP SIZE OF THE LAST ACCEPTED STEP
  //C
  //C     IDID        REPORTS ON SUCCESSFULNESS UPON RETURN:
  //C                   IDID= 1  COMPUTATION SUCCESSFUL,
  //C                   IDID= 2  COMPUT. SUCCESSFUL (INTERRUPTED BY evalO)
  //C                   IDID=-1  INPUT IS NOT CONSISTENT,
  //C                   IDID=-2  LARGER NMAX IS NEEDED,
  //C                   IDID=-3  STEP SIZE BECOMES TOO SMALL,
  //C                   IDID=-4  MATRIX IS REPEATEDLY SINGULAR.
  //C
  //C   IWORK(14)  NFCN    NUMBER OF FUNCTION EVALUATIONS (THOSE FOR NUMERICAL
  //C                      EVALUATION OF THE JACOBIAN ARE NOT COUNTED)
  //C   IWORK(15)  NJAC    NUMBER OF JACOBIAN EVALUATIONS (EITHER ANALYTICALLY
  //C                      OR NUMERICALLY)
  //C   IWORK(16)  NSTEP   NUMBER OF COMPUTED STEPS
  //C   IWORK(17)  NACCPT  NUMBER OF ACCEPTED STEPS
  //C   IWORK(18)  NREJCT  NUMBER OF REJECTED STEPS (DUE TO ERROR TEST),
  //C                      (STEP REJECTIONS IN THE FIRST STEP ARE NOT COUNTED)
  //C   IWORK(19)  NDEC    NUMBER OF LU-DECOMPOSITIONS OF BOTH MATRICES
  //C   IWORK(20)  NSOL    NUMBER OF FORWARD-BACKWARD SUBSTITUTIONS, OF BOTH
  //C                      SYSTEMS; THE NSTEP FORWARD-BACKWARD SUBSTITUTIONS,
  //C                      NEEDED FOR STEP SIZE SELECTION, ARE NOT COUNTED
  //C-----------------------------------------------------------------------
  //C *** *** *** *** *** *** *** *** *** *** *** *** ***
  //C          DECLARATIONS
  //C *** *** *** *** *** *** *** *** *** *** *** *** ***
  //C *** *** *** *** *** *** ***
  //C        SETTING THE PARAMETERS
  //C *** *** *** *** *** *** ***
  void operator()(const integer & n,
                  evalF & fcn,
                  double & x,
                  CVectorCore< double > & y,
                  const doublereal & xend,
                  double & h,
                  CVectorCore< double > & rtol,
                  CVectorCore< double > & atol,
                  const integer & itol,
                  evalJ & jac,
                  const integer & ijac,
                  int & mljac,
                  int & mujac,
                  evalM & mas,
                  const integer & imas,
                  const integer & mlmas,
                  int & mumas,
                  evalO & solout,
                  const integer & iout,
                  CVectorCore< double > & work,
                  const integer & lwork,
                  CVectorCore< int > & iwork,
                  const integer & liwork,
                  const CVectorCore< double > & rpar,
                  const CVectorCore< int > & ipar,
                  int & idid);

private:
  //C********************************************************
  //C
  doublereal contr5(const common & cmn,
                    const integer & i,
                    const integer & n,
                    const doublereal & x,
                    const CVectorCore< doublereal > & cont,
                    const doublereal & xsol,
                    const doublereal & hsol);

  void radcor(const integer & n,
              evalF & fcn,
              doublereal & x,
              CVectorCore< doublereal > & y,
              const doublereal & xend,
              const doublereal & hmax,
              doublereal & h,
              const CVectorCore< doublereal > & rtol,
              const CVectorCore< doublereal > & atol,
              const integer & itol,
              evalJ & jac,
              const integer & ijac,
              const integer & mljac,
              const integer & mujac,
              evalM & mas,
              const integer & mlmas,
              const integer & mumas,
              evalO & solout,
              const integer & iout,
              integer & idid,
              const integer & nmax,
              const doublereal & uround,
              const doublereal & safe,
              const doublereal & thet,
              const doublereal & fnewt,
              const doublereal & quot1,
              const doublereal & quot2,
              const integer & nit,
              integer & ijob,
              bool const & startn,
              const integer & nind1,
              const integer & nind2,
              const integer & nind3,
              bool const & pred,
              const doublereal & facl,
              const doublereal & facr,
              const integer & m1,
              const integer & m2,
              const integer & nm1,
              bool const & implct,
              bool const & banded,
              const integer & ldjac,
              const integer & lde1,
              const integer & ldmas,
              CVectorCore< doublereal > & z1,
              CVectorCore< doublereal > & z2,
              CVectorCore< doublereal > & z3,
              const CVectorCore< doublereal > & y0,
              CVectorCore< doublereal > & scal,
              CVectorCore< doublereal > & f1,
              CVectorCore< doublereal > & f2,
              CVectorCore< doublereal > & f3,
              CMatrix< doublereal > & fjac,
              CMatrix< doublereal > & e1,
              CMatrix< doublereal > & e2r,
              CMatrix< doublereal > & e2i,
              CMatrix< doublereal > & fmas,
              CVectorCore< integer > & ip1,
              CVectorCore< integer > & ip2,
              CVectorCore< integer > & iphes,
              CVectorCore< doublereal > & cont,
              integer & nfcn,
              integer & njac,
              integer & nstep,
              integer & naccpt,
              integer & nrejct,
              integer & ndec,
              integer & nsol,
              const CVectorCore< doublereal > & rpar,
              const CVectorCore< integer > & ipar);

  //C
  //C     END OF SUBROUTINE RADCOR
  //C
  //C ***********************************************************
  //C

  doublereal contr5(const integer & i,
                    const doublereal & x,
                    const CVectorCore< doublereal > & cont,
                    const integer & lrc);

  common mCommon;
};
