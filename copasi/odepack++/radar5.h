// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <functional>
#include <fem.hpp> // Fortran EMulation library of fable module

#include "copasi/copasi.h"

#ifdef HAVE_F2C_H
#  include <f2c.h>
#else
#  include "copasi/lapack/f2c.h"
#endif

#ifdef min
#  undef min
#endif // min

#ifdef max
#  undef max
#endif // max

#include "copasi/core/CVector.h"
#include "copasi/core/CMatrix.h"

namespace radar5
{
// THIS FILE CONTAINS THE SUBROUTINE RADAR5 AND ALL ITS DEPENDENCIES.
// RADAR5 IS A FORTRAN 77 IMPLEMENTATION OF THE RADAU IIA METHOD OF
// ORDER 5. IT WAS DEVELOPED BY E. HAIRER AND G. WANNER, UNIVERSITY
// OF ZURICH, SWITZERLAND. THE ORIGINAL SOURCE CODE CAN BE FOUND AT
// http://www.unige.ch/~hairer/software.html.

// PHI              FUNCTION COMPUTING THE INITIAL FUNCTIONS FOR COMPONENTS I (WITH RETARDED ARGUMENT),
//                    FUNCTION PHI(I,X,RPAR,IPAR)
//                    DOUBLE PRECISION PHI,X
//
typedef std::function< double(const integer & i,
                              doublereal const & x,
                              const doublereal & rpar,
                              const integer & ipar) >
  PHI;

// ARGLAG           FUNCTION COMPUTING THE IL-TH LAG TERM
//                    FUNCTION ARGLAG(IL,X,N,Y,RPAR,IPAR,PHI,...)
//                    DOUBLE PRECISION PHI,X,Y(N)
typedef std::function< double(const integer & i,
                              doublereal const & x,
                              integer const & n,
                              const CVectorCore< doublereal > & y,
                              const doublereal & rpar,
                              const integer & ipar,
                              PHI & phi,
                              const CVectorCore< doublereal > & past,
                              const CVectorCore< integer > & ipast,
                              integer const & nrds) >
  ARGLAG;

// FCN           SUBROUTINE COMPUTING THE RIGHT-
//                 HAND-SIDE OF THE DELAY EQUATION, E.G.,
//                    SUBROUTINE FCN(N,X,Y,F,RPAR,IPAR,...)
//                    DOUBLE PRECISION X,Y(N),F(N)
//                    EXTERNAL PHI
//                    F(1)=G1(X,Y(*),YLAGR5(*,X-TAU(X,Y(*))),PHI,...))
//                    F(2)=G2(X,Y(*),YLAGR5(*,X-TAU(X,Y(*))),PHI,...))
//                    ETC.
//                    (*) MEANS ALL POSSIBLE COMPONENTS
//                 FOR AN EXPLICATION OF YLAGR5 SEE BELOW.
//                 DO NOT USE YLAGR5(I,X-0.D0,PHI,RPAR,IPAR,...) !
//                 Note:
//                 THE INITIAL FUNCTION HAS TO BE SUPPLIED BY:
//                    FUNCTION PHI(I,X,RPAR,IPAR)
//                    DOUBLE PRECISION PHI,X
//                 WHERE I IS THE COMPONENT AND X THE ARGUMENT
//                 RPAR, IPAR (SEE BELOW)
typedef std::function< void(integer const & n,
                            const doublereal & x,
                            const CVectorCore< doublereal > & y,
                            const CVectorCore< doublereal > & y0,
                            ARGLAG & arglag,
                            PHI & phi,
                            const doublereal & rpar,
                            const integer & ipar,
                            CVectorCore< doublereal > & past,
                            CVectorCore< integer > & ipast,
                            integer const & nrds) >
  FCN;

// JAC           SUBROUTINE WHICH COMPUTES
//                 THE PARTIAL DERIVATIVES OF F(X,Y) WITH RESPECT TO Y
//                 (THIS ROUTINE IS ONLY CALLED IF IJAC=1;
//                 THE USER HAS TO SUPPLY A DUMMY SUBROUTINE
//                 IN THE CASE IJAC=0).
//                 FOR IJAC=1, THIS SUBROUTINE MUST HAVE THE FORM
//                    SUBROUTINE JAC(N,X,Y,DFY,LDFY,RPAR,IPAR,...)
//                    DOUBLE PRECISION X,Y(N),DFY(LDFY,N)
//                    DFY(1,1)= ...
//                 LDFY, THE COLUMN-LENGTH OF THE ARRAY, IS
//                 FURNISHED BY THE CALLING PROGRAM.
//                 IF (MLJAC.EQ.N) THE JACOBIAN IS SUPPOSED TO
//                    BE FULL AND THE PARTIAL DERIVATIVES ARE
//                    STORED IN DFY AS
//                       DFY(I,J) = PARTIAL F(I) / PARTIAL Y(J)
//                 ELSE, THE JACOBIAN IS TAKEN AS BANDED AND
//                    THE PARTIAL DERIVATIVES ARE STORED
//                    DIAGONAL-WISE AS
//                       DFY(I-J+MUJAC+1,J) = PARTIAL F(I) / PARTIAL Y(J).
typedef std::function< void(integer const & n,
                            const doublereal & x,
                            const CVectorCore< doublereal > & y,
                            CMatrix< doublereal > & dfy,
                            integer const & ldfy,
                            ARGLAG & arglag,
                            PHI & phi,
                            const doublereal & rpar,
                            const integer & ipar,
                            CVectorCore< doublereal > & past,
                            CVectorCore< integer > & ipast,
                            integer const & nrds) >
  JAC;

// JACLAG        SUBROUTINE WHICH COMPUTES
//                 THE PARTIAL DERIVATIVES OF F(X,Y,YLAG) WITH RESPECT TO
//                 YLAG(*) (YLAG DENOTE THE DELAYED VARIABLES)
//
typedef std::function< void(integer const & n,
                            const doublereal & x,
                            const CVectorCore< doublereal > & y,
                            const CVectorCore< doublereal > & ylag,
                            ARGLAG & arglag,
                            PHI & phi,
                            const CVectorCore< integer > & ive,
                            const CVectorCore< integer > & ivc,
                            const CVectorCore< integer > & ivl,
                            const doublereal & rpar,
                            const integer & ipar,
                            CVectorCore< doublereal > & past,
                            CVectorCore< integer > & ipast,
                            integer const & nrds) >
  JACLAG;

// MAS           SUBROUTINE COMPUTING THE MASS-
//                 MATRIX M.
//                 IF IMAS=0, THIS MATRIX IS ASSUMED TO BE THE IDENTITY
//                 MATRIX AND NEEDS NOT TO BE DEFINED;
//                 THE USER HAS TO SUPPLY A DUMMY SUBROUTINE IN THIS CASE.
//                 IF IMAS=1, THE SUBROUTINE MAS IS OF THE FORM
//                    SUBROUTINE MAS(N,AM,LMAS,RPAR,IPAR)
//                    DOUBLE PRECISION AM(LMAS,N)
//                    AM(1,1)= ....
//                    IF (MLMAS.EQ.N) THE MASS-MATRIX IS STORED
//                    AS FULL MATRIX LIKE
//                         AM(I,J) = M(I,J)
//                    ELSE, THE MATRIX IS TAKEN AS BANDED AND STORED
//                    DIAGONAL-WISE AS
//                         AM(I-J+MUMAS+1,J) = M(I,J).
typedef std::function< void(integer const & n,
                            CMatrix< doublereal > & am,
                            integer const & lmas,
                            const doublereal & rpar,
                            const integer & ipar) >
  MAS;

// SOLOUT        SUBROUTINE PROVIDING THE
//                 NUMERICAL SOLUTION DURING INTEGRATION.
//                 IF IOUT=1, IT IS CALLED AFTER EVERY SUCCESSFUL STEP.
//                 THE USER HAS TO SUPPLY A DUMMY SUBROUTINE IF IOUT=0.
//                 IT MUST HAVE THE FORM
//                    SUBROUTINE SOLOUT (NR,XOLD,X,HSOL,Y,CONT,LRC,N,
//                                       RPAR,IPAR,IRTRN)
//                    DOUBLE PRECISION X,Y(N),CONT(LRC)
//                    ....
//                 SOLOUT FURNISHES THE SOLUTION "Y" AT THE NR-TH
//                    GRID-POINT "X" (THEREBY THE INITIAL VALUE IS
//                    THE FIRST GRID-POINT).
//                 "XOLD" IS THE PRECEEDING GRID-POINT.
//                 "IRTRN" SERVES TO INTERRUPT THE INTEGRATION. IF IRTRN
//                    IS SET <0, RADAR5 RETURNS TO THE CALLING PROGRAM.
//
//          -----  CONTINUOUS OUTPUT: -----
//                 DURING CALLS TO "SOLOUT" AS WELL AS TO "FCN", A
//                 CONTINUOUS SOLUTION IS AVAILABLE THROUGH HTHE FUNCTION
//                        >>>   YLAGR5(I,S,PHI,RPAR,IPAR,...)   <<<
//                 WHICH PROVIDES AN APPROXIMATION TO THE I-TH
//                 COMPONENT OF THE SOLUTION AT THE POINT S. THE VALUE S
//                 HAS TO LIE IN AN INTERVAL WHERE THE NUMERICAL SOLUTION
//                 IS ALREADY COMPUTED. IT DEPENDS ON THE SIZE OF LRPAST
//                 (SEE BELOW) HOW FAR BACK THE SOLUTION IS AVAILABLE.
typedef std::function< void(integer const & nr,
                            const doublereal & xold,
                            const doublereal & x,
                            const doublereal & hsol,
                            const CVectorCore< doublereal > & y,
                            const CVectorCore< doublereal > & cont,
                            integer const & lrc,
                            integer const & n,
                            const doublereal & rpar,
                            const integer & ipar,
                            integer & irtrn) >
  SOLOUT;

template < typename T >
T dim(const T & a, const T & b)
{
  return (a > b) ? a - b : 0;
}

struct common_constn
{
  doublereal c1;
  doublereal c2;
  doublereal c1m1;
  doublereal c2m1;
  doublereal c1mc2;

  common_constn();
};

struct common_posits
{
  doublereal x0b;
  doublereal uround;
  doublereal hmax;
  integer iact;
  integer irtrn;
  integer idif;
  integer mxst;
  bool flags;
  bool flagn;

  common_posits();
};

struct common_bplog
{
  bool first;
  bool last;
  bool reject;
  bool bpd;

  common_bplog();
};

struct common_bpcom
{
  doublereal bpp;
  integer ilbp;
  bool left;

  common_bpcom();
};

struct common_linal
{
  integer mle;
  integer mue;
  integer mbjac;
  integer mbb;
  integer mdiag;
  integer mdiff;
  integer mbdiag;

  common_linal();
};

struct common : fem::common
  , common_constn
  , common_posits
  , common_bplog
  , common_bpcom
  , common_linal
{
  common(integer argc, char const * argv[]);
};

//C********************************************************
//C
doublereal contr5(common & cmn,
                  integer const & i,
                  integer const & n,
                  doublereal const & x,
                  const CVectorCore< doublereal > & cont,
                  doublereal const & xsol,
                  doublereal const & hsol);

void bpdtct(common & cmn,
            integer const & n,
            doublereal const & x,
            doublereal & h,
            CVectorCore< doublereal > & y,
            ARGLAG & arglag,
            float const & rpar,
            integer const & ipar,
            const CVectorCore< doublereal > & ucont,
            const CVectorCore< doublereal > & grid,
            integer const & nlags,
            bool const & first,
            bool const & last,
            doublereal const & xend,
            integer const & igrid,
            CVectorCore< doublereal > & bpv,
            integer & ibp,
            integer & ilbp,
            doublereal & bpp,
            bool & bpd,
            integer const & kmax,
            PHI & phi,
            CVectorCore< doublereal > & past,
            CVectorCore< integer > & ipast,
            integer const & nrds);

void bpacc(common & cmn,
           integer const & n,
           doublereal const & x,
           doublereal & h,
           CVectorCore< doublereal > & y,
           ARGLAG & arglag,
           float const & rpar,
           integer const & ipar,
           CVectorCore< doublereal > & z1,
           CVectorCore< doublereal > & z2,
           CVectorCore< doublereal > & z3,
           bool const & first,
           CVectorCore< doublereal > & bpv,
           integer const & ibp,
           integer const & ilbp,
           doublereal const & bpp,
           integer const & kmax,
           PHI & phi,
           CVectorCore< doublereal > & past,
           CVectorCore< integer > & ipast,
           integer const & nrds);

void radcor(common & cmn,
            integer const & n,
            doublereal & x,
            CVectorCore< doublereal > & y,
            doublereal & xend,
            doublereal & h,
            FCN & fcn,
            PHI & phi,
            ARGLAG & arglag,
            CVectorCore< doublereal > & rtol,
            CVectorCore< doublereal > & atol,
            integer const & itol,
            JAC & jac,
            integer const & ijac,
            integer const & mljac,
            integer const & mujac,
            JACLAG & jaclag,
            MAS & mas,
            integer const & mlmas,
            integer const & mumas,
            SOLOUT & solout,
            integer const & iout,
            integer & idid,
            integer const & nmax,
            doublereal const & safe,
            doublereal const & thet,
            doublereal const & fnewt,
            doublereal const & quot1,
            doublereal const & quot2,
            integer const & nit,
            integer & ijob,
            bool const & startn,
            integer const & nind1,
            integer const & nind2,
            integer const & nind3,
            bool const & pred,
            doublereal const & facl,
            doublereal const & facr,
            integer const & m1,
            integer const & m2,
            integer const & nm1,
            bool const & implct,
            bool const & neutral,
            integer const & ndimn,
            bool const & banded,
            integer const & ldjac,
            integer const & lde1,
            integer const & ldmas,
            integer & nfcn,
            integer & njac,
            integer & nstep,
            integer & naccpt,
            integer & nrejct,
            integer & ndec,
            integer & nsol,
            integer & nfull,
            float const & rpar,
            integer const & ipar,
            CVectorCore< integer > & ipast,
            CVectorCore< doublereal > & grid,
            integer const & lgrid,
            integer const & nrds,
            integer const & nlags,
            integer const & njacl,
            integer const & ngrid,
            integer const & ieflag,
            doublereal const & work7,
            doublereal const & tckbp,
            doublereal const & alpha,
            integer const & iswjl);

//C ----------------------------------------------------------
//C     NUMERICAL SOLUTION OF A STIFF DIFFERENTIAL
//C     (OR DIFFERENTIAL ALGEBRAIC) SYSTEM OF FIRST 0RDER
//C     DELAY DIFFERENTIAL EQUATIONS
//C                     M*Y'(X)=F(X,Y(X),Y(X-A),...).
//C     THE SYSTEM CAN BE (LINEARLY) IMPLICIT (MASS-MATRIX M .NE. I)
//C     OR EXPLICIT (M = I).
//C     NOTE: THIS FORM ALSO ALLOWS TO SOLVE NEUTRAL DIFFERENTIAL PROBLEMS
//C
//C     NOTE: THIS VERSION ALLOWS ARBITRARILY LARGE STEP SIZES
//C     (POSSIBLY LARGER THAN THE DELAYS)
//C
//C     THE METHOD USED IS AN IMPLICIT RUNGE-KUTTA METHOD (3 STAGE
//C     RADAU IIA) OF ORDER 5 WITH STEP SIZE CONTROL AND CONTINUOUS
//C     EXTENSION OF ORDER 3  (C.F. SECTION IV.8 OF (HW))
//C
//C     AUTHORS: N. GUGLIELMI(*) AND E. HAIRER($)
//C          (*) DIVISION OF MATHEMATICS, GRAN SASSO SCIENCE INSTITUTE
//C              VIA CRISPI 7, 67100 L'AQUILA, ITALY
//C          ($) UNIVERSITE DE GENEVE, DEPT. DE MATHEMATIQUES
//C              CH-1211 GENEVE 24, SWITZERLAND
//C              E-MAIL ADRESSES:
//C                        nicola.guglielmi@gssi.it
//C                            ernst.hairer@unige.ch
//C
//C     THIS PROGRAM EXTENDS THE CODE RADAU5 (BY E. HAIRER AND G. WANNER)
//C     TO THE CASE OF DELAY DIFFERENTIAL EQUATIONS.
//C     DETAILS ABOUT RADAU5 CAN BE FOUND IN THE BOOK:
//C     (HW)  E. HAIRER AND G. WANNER, SOLVING ORDINARY DIFFERENTIAL
//C           EQUATIONS II. STIFF AND DIFFERENTIAL-ALGEBRAIC PROBLEMS.
//C           SPRINGER SERIES IN COMPUTATIONAL MATHEMATICS 14,
//C           SPRINGER-VERLAG 1991, SECOND EDITION 1996.
//C     DETAILS ABOUT RADAR5 CAN BE FOUND IN THE PAPERS:
//C     (GH1) N. GUGLIELMI AND E. HAIRER, Implementing Radau IIA methods for
//C           stiff delay differential equations , Computing 67, 1-12 (2001).
//C     (GH2) N. GUGLIELMI AND E. HAIRER, Computing breaking points in
//C           implicit delay differential equations,
//C           Adv. Comput. Math. 29 (2008) 229-247
//C
//C ===============================================================================================
//C     VERSION 2.2 OF FEBRUARY 8, 2024
//C     FIXES A FEW BUGS, AND MAKES OTHER LITTLE CHANGES WITH RESPECT TO PREVIOUS VERSION 2.1,
//C     ALL CHANGES HAVE MINIMAL IMPACT, IF ANY, ON BACKWARD COMPATIBILITY WITH VERSION 2.1.
//C     BASIC DIFFERENCES FROM VERSION 2.1: CONCERN THE CALL TO RADAR5, WHICH NOW INCLUDES A FEW
//C     FURTHER PARAMETERS CONCERNING VECTOR DIMENSIONS.
//C     THE SUBROUTINE CONTR5 - WHICH WAS GIVEN AS AN EXTERNAL FILES - IS NOW INCLUDED IN THIS FILE.
//C     THE ALGORITHM IMPLEMENTING THE NUMERICAL INTEGRATOR HAS NOT CHANGED WITH RESPECT TO VERSION
//C     2.1.
//C ===============================================================================================
//C
//C     AN ADDITIONAL SEPARATED ROUTINE (DC_SUMEXPDEL) MIGHT BE USED TO TREAT DISTRIUTED DELAYS BY
//C     A FAST LINEAR SOLVER. IT SHOULD REPLACE THE SUBROUTINE DC_DECDEL
//C     A NEW DRIVER PROGRAM FOR AN EXAMPLE WITH IS AVAILABLE IN THE SAME WEBPAGE OF THE CODE.
//C
//C ----------------------------------------------------------
void radar5(common & cmn,
            integer const & n,
            FCN & fcn,
            PHI & phi,
            ARGLAG arglag,
            doublereal & x,
            CVectorCore< doublereal > & y,
            doublereal & xend,
            doublereal & h,
            CVectorCore< doublereal > & rtol,
            CVectorCore< doublereal > & atol,
            integer const & itol,
            JAC & jac,
            integer const & ijac,
            integer & mljac,
            integer & mujac,
            JACLAG & jaclag,
            integer const & nlags,
            integer const & njacl,
            MAS & mas,
            integer const & imas,
            integer const & mlmas,
            integer const & mumas,
            SOLOUT & solout,
            integer const & iout,
            CVectorCore< doublereal > & work,
            integer const & lwork,
            CVectorCore< integer > & iwork,
            integer const & liwork,
            float const & rpar,
            integer const & ipar,
            integer & idid,
            CVectorCore< doublereal > & grid,
            integer const & lgrid,
            CVectorCore< integer > & ipast,
            integer const & nrdens);

//C
//C     END OF SUBROUTINE RADCOR
//C
//C ***********************************************************
//C
void lagr5(common & cmn,
           integer const & il,
           doublereal const & x,
           integer const & n,
           float const & y,
           ARGLAG & arglag,
           CVectorCore< doublereal > & past,
           doublereal & theta,
           integer & ipos,
           float const & rpar,
           integer const & ipar,
           PHI & phi,
           CVectorCore< integer > & ipast,
           integer const & nrds);

doublereal ylagr5(common & cmn,
                  integer const & ic,
                  doublereal const & theta,
                  integer const & ipos,
                  PHI & phi,
                  float const & rpar,
                  integer const & ipar,
                  CVectorCore< doublereal > & past,
                  CVectorCore< integer > & ipast,
                  integer const & nrds);

doublereal dlagr5(common & cmn,
                  integer const & ic,
                  doublereal const & theta,
                  integer const & ipos,
                  PHI & phi,
                  float const & rpar,
                  integer const & ipar,
                  CVectorCore< doublereal > & past,
                  CVectorCore< integer > & ipast,
                  integer const & nrds);

doublereal dontr5(common & cmn,
                  integer const & i,
                  integer const & n,
                  doublereal const & x,
                  const CVectorCore< doublereal > & cont,
                  doublereal const & xsol,
                  doublereal const & hsol);

void decomr(integer const & n,
            const CMatrix< doublereal > & fjac,
            integer const & ldjac,
            const CMatrix< doublereal > & fmas,
            integer const & ldmas,
            integer const & mlmas,
            integer const & mumas,
            integer const & m1,
            integer const & m2,
            integer const & nm1,
            doublereal const & fac1,
            CMatrix< doublereal > & e1,
            integer const & lde1,
            const CVectorCore< integer > & ip1,
            integer const & ier,
            integer const & ijob,
            bool const & calhes,
            const CVectorCore< integer > & iphes);

void decomc(integer const & n,
            const CMatrix< doublereal > & fjac,
            integer const & ldjac,
            const CMatrix< doublereal > & fmas,
            integer const & ldmas,
            integer const & mlmas,
            integer const & mumas,
            integer const & m1,
            integer const & m2,
            integer const & nm1,
            doublereal const & alphn,
            doublereal const & betan,
            CMatrix< doublereal > & e2r,
            CMatrix< doublereal > & e2i,
            integer const & lde1,
            const CVectorCore< integer > & ip2,
            integer const & ier,
            integer const & ijob);

void slvrad(integer const & n,
            CMatrix< doublereal > & fjac,
            integer const & ldjac,
            integer const & mljac,
            integer const & mujac,
            CMatrix< doublereal > & fmas,
            integer const & ldmas,
            integer const & mlmas,
            integer const & mumas,
            integer const & m1,
            integer const & m2,
            integer const & nm1,
            doublereal const & fac1,
            doublereal const & alphn,
            doublereal const & betan,
            CMatrix< doublereal > & e1,
            CMatrix< doublereal > & e2r,
            CMatrix< doublereal > & e2i,
            integer const & lde1,
            CVectorCore< doublereal > & z1,
            CVectorCore< doublereal > & z2,
            CVectorCore< doublereal > & z3,
            CVectorCore< doublereal > & f1,
            CVectorCore< doublereal > & f2,
            CVectorCore< doublereal > & f3,
            CVectorCore< doublereal > & cont,
            CVectorCore< integer > & ip1,
            CVectorCore< integer > & ip2,
            CVectorCore< integer > & phes,
            integer const & ier,
            integer const & ijob);

void estrad(integer const & n,
            CMatrix< doublereal > & fjac,
            integer const & ldjac,
            integer const & mljac,
            integer const & mujac,
            CMatrix< doublereal > & fmas,
            integer const & ldmas,
            integer const & mlmas,
            integer const & mumas,
            doublereal const & h,
            doublereal const & g0,
            doublereal const & dd1,
            doublereal const & dd2,
            doublereal const & dd3,
            doublereal const & cl1,
            doublereal const & cl3,
            doublereal const & cq1,
            doublereal const & cq2,
            doublereal const & cq3,
            doublereal const & cerlq,
            FCN & fcn,
            integer & nfcn,
            CVectorCore< doublereal > & y0,
            CVectorCore< doublereal > & y,
            integer const & ijob,
            doublereal const & x,
            integer const & m1,
            integer const & m2,
            integer const & nm1,
            CMatrix< doublereal > & e1,
            integer const & lde1,
            doublereal const & alpha,
            CVectorCore< doublereal > & z1,
            CVectorCore< doublereal > & z2,
            CVectorCore< doublereal > & z3,
            CVectorCore< doublereal > & cont,
            CVectorCore< doublereal > & f1,
            CVectorCore< doublereal > & f2,
            CVectorCore< doublereal > & f3,
            CVectorCore< integer > & ip1,
            CVectorCore< integer > & iphes,
            CVectorCore< doublereal > & scal,
            doublereal & err,
            doublereal & cerr,
            bool const & first,
            bool const & reject,
            doublereal const & fac1,
            ARGLAG & arglag,
            PHI & phi,
            CVectorCore< doublereal > rpar,
            CVectorCore< integer > ipar,
            integer const & iout,
            CVectorCore< doublereal > & past,
            CVectorCore< integer > & ipast,
            integer const & nrds,
            integer const & jeflag,
            integer const & ieflag);

// Matrix Triangularization by Gaussian Elimination
int dec(const integer & n,
        const integer & ldjac,
        CMatrix< doublereal > & fjacl,
        CVectorCore< integer > & ipj,
        integer & ier);

// Solution of linear system A*x = b
int sol(const integer & n,
        const integer & ldjac,
        const CMatrix< doublereal > & fjacl,
        CVectorCore< doublereal > & zl,
        const CVectorCore< integer > & ipj);
} // namespace radar5
