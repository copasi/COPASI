// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/odepack++/_CRadau5.h"

using namespace _dc_decsol;

_CRadau5::_CRadau5()
  : Cxerrwd(true)
  , mCommon()
{}

void _CRadau5::operator()(const integer & n,
                          evalF & fcn,
                          doublereal & x,
                          CVectorCore< doublereal > & y,
                          const doublereal & xend,
                          doublereal & h,
                          CVectorCore< doublereal > & rtol,
                          CVectorCore< doublereal > & atol,
                          const integer & itol,
                          evalJ & jac,
                          const integer & ijac,
                          integer & mljac,
                          integer & mujac,
                          evalM & mas,
                          const integer & imas,
                          const integer & mlmas,
                          integer & mumas,
                          evalO & solout,
                          const integer & iout,
                          CVectorCore< doublereal > & work,
                          const integer & lwork,
                          CVectorCore< integer > & iwork,
                          const integer & liwork,
                          const CVectorCore< doublereal > & rpar,
                          const CVectorCore< integer > & ipar,
                          integer & idid)
{
  integer nfcn = 0;
  integer njac = 0;
  integer nstep = 0;
  integer naccpt = 0;
  integer nrejct = 0;
  integer ndec = 0;
  integer nsol = 0;
  bool arret = false;
  //C -------- UROUND   SMALLEST NUMBER SATISFYING 1.0D0+UROUND>1.0D0
  doublereal uround = 0.0;
  if (work(1) == 0.0e0)
    {
      uround = 1.0e-16;
    }
  else
    {
      uround = work(1);
      if (uround <= 1.0e-19 || uround >= 1.0e0)
        {
          write(" COEFFICIENTS HAVE 20 DIGITS, UROUND=", work(1));
          arret = true;
        }
    }
  //C -------- CHECK AND CHANGE THE TOLERANCES
  doublereal expm = 2.0e0 / 3.0e0;
  doublereal quot = 0.0;
  integer i = 0;
  if (itol == 0)
    {
      if (atol(1) <= 0.e0 || rtol(1) <= 10.e0 * uround)
        {
          write(" TOLERANCES ARE TOO SMALL");
          arret = true;
        }
      else
        {
          quot = atol(1) / rtol(1);
          rtol(1) = 0.1e0 * std::pow(rtol(1), expm);
          atol(1) = rtol(1) * quot;
        }
    }
  else
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          if (atol(i) <= 0.e0 || rtol(i) <= 10.e0 * uround)
            {
              write(" TOLERANCES(", i, ") ARE TOO SMALL");
              arret = true;
            }
          else
            {
              quot = atol(i) / rtol(i);
              rtol(i) = 0.1e0 * std::pow(rtol(i), expm);
              atol(i) = rtol(i) * quot;
            }
        }
    }
  //C -------- NMAX , THE MAXIMAL NUMBER OF STEPS -----
  integer nmax = 0;
  if (iwork(2) == 0)
    {
      nmax = 100000;
    }
  else
    {
      nmax = iwork(2);
      if (nmax <= 0)
        {
          write(" WRONG INPUT IWORK(2)=", iwork(2));
          arret = true;
        }
    }
  //C -------- NIT    MAXIMAL NUMBER OF NEWTON ITERATIONS
  integer nit = 0;
  if (iwork(3) == 0)
    {
      nit = 7;
    }
  else
    {
      nit = iwork(3);
      if (nit <= 0)
        {
          write(" CURIOUS INPUT IWORK(3)=", iwork(3));
          arret = true;
        }
    }
  //C -------- STARTN  SWITCH FOR STARTING VALUES OF NEWTON ITERATIONS
  bool startn = false;
  if (iwork(4) == 0)
    {
      startn = false;
    }
  else
    {
      startn = true;
    }
  //C -------- PARAMETER FOR DIFFERENTIAL-ALGEBRAIC COMPONENTS
  integer nind1 = iwork(5);
  integer nind2 = iwork(6);
  integer nind3 = iwork(7);
  if (nind1 == 0)
    {
      nind1 = n;
    }
  if (nind1 + nind2 + nind3 != n)
    {
      write(" CURIOUS INPUT FOR IWORK(5,6,7)=", nind1, nind2, nind3);
      arret = true;
    }
  //C -------- PRED   STEP SIZE CONTROL
  bool pred = false;
  if (iwork(8) <= 1)
    {
      pred = true;
    }
  else
    {
      pred = false;
    }
  //C -------- PARAMETER FOR SECOND ORDER EQUATIONS
  integer m1 = iwork(9);
  integer m2 = iwork(10);
  integer nm1 = n - m1;
  if (m1 == 0)
    {
      m2 = n;
    }
  if (m2 == 0)
    {
      m2 = m1;
    }
  if (m1 < 0 || m2 < 0 || m1 + m2 > n)
    {
      write(" CURIOUS INPUT FOR IWORK(9,10)=", m1, m2);
      arret = true;
    }
  //C --------- SAFE     SAFETY FACTOR IN STEP SIZE PREDICTION
  doublereal safe = 0.0;
  if (work(2) == 0.0e0)
    {
      safe = 0.9e0;
    }
  else
    {
      safe = work(2);
      if (safe <= 0.001e0 || safe >= 1.0e0)
        {
          write(" CURIOUS INPUT FOR WORK(2)=", work(2));
          arret = true;
        }
    }
  //C ------ THET     DECIDES WHETHER THE JACOBIAN SHOULD BE RECOMPUTED;
  doublereal thet = 0.0;
  if (work(3) == 0.e0)
    {
      thet = 0.001e0;
    }
  else
    {
      thet = work(3);
      if (thet >= 1.0e0)
        {
          write(" CURIOUS INPUT FOR WORK(3)=", work(3));
          arret = true;
        }
    }
  //C --- FNEWT   STOPPING CRITERION FOR NEWTON'S METHOD, USUALLY CHOSEN <1.
  doublereal tolst = rtol(1);
  doublereal fnewt = 0.0;
  if (work(4) == 0.e0)
    {
      fnewt = std::max(10 * uround / tolst, std::min(0.03e0, std::pow(tolst,
                                                                      0.5e0)));
    }
  else
    {
      fnewt = work(4);
      if (fnewt <= uround / tolst)
        {
          write(" CURIOUS INPUT FOR WORK(4)=", work(4));
          arret = true;
        }
    }
  //C --- QUOT1 AND QUOT2: IF QUOT1 < HNEW/HOLD < QUOT2, STEP SIZE = CONST.
  doublereal quot1 = 0.0;
  if (work(5) == 0.e0)
    {
      quot1 = 1.e0;
    }
  else
    {
      quot1 = work(5);
    }
  doublereal quot2 = 0.0;
  if (work(6) == 0.e0)
    {
      quot2 = 1.2e0;
    }
  else
    {
      quot2 = work(6);
    }
  if (quot1 > 1.0e0 || quot2 < 1.0e0)
    {
      write(" CURIOUS INPUT FOR WORK(5,6)=", quot1, quot2);
      arret = true;
    }
  //C -------- MAXIMAL STEP SIZE
  doublereal hmax = 0.0;
  if (work(7) == 0.e0)
    {
      hmax = xend - x;
    }
  else
    {
      hmax = work(7);
    }
  //C -------  FACL,FACR     PARAMETERS FOR STEP SIZE SELECTION
  doublereal facl = 0.0;
  if (work(8) == 0.e0)
    {
      facl = 5.e0;
    }
  else
    {
      facl = 1.e0 / work(8);
    }
  doublereal facr = 0.0;
  if (work(9) == 0.e0)
    {
      facr = 1.e0 / 8.0e0;
    }
  else
    {
      facr = 1.e0 / work(9);
    }
  if (facl < 1.0e0 || facr > 1.0e0)
    {
      write(" CURIOUS INPUT WORK(8,9)=", work(8), work(9));
      arret = true;
    }
  //C *** *** *** *** *** *** *** *** *** *** *** *** ***
  //C         COMPUTATION OF ARRAY ENTRIES
  //C *** *** *** *** *** *** *** *** *** *** *** *** ***
  //C ---- IMPLICIT, BANDED OR NOT ?
  bool implct = imas != 0;
  bool jband = mljac < nm1;
  //C -------- COMPUTATION OF THE ROW-DIMENSIONS OF THE 2-ARRAYS ---
  //C -- JACOBIAN  AND  MATRICES E1, E2
  integer ldjac = 0;
  integer lde1 = 0;
  if (jband)
    {
      ldjac = mljac + mujac + 1;
      lde1 = mljac + ldjac;
    }
  else
    {
      mljac = nm1;
      mujac = nm1;
      ldjac = nm1;
      lde1 = nm1;
    }
  //C -- MASS MATRIX
  integer ldmas = 0;
  integer ijob = 0;
  if (implct)
    {
      if (mlmas != nm1)
        {
          ldmas = mlmas + mumas + 1;
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
          mumas = nm1;
          ldmas = nm1;
          ijob = 5;
        }
      //C ------ BANDWITH OF "MAS" NOT SMALLER THAN BANDWITH OF "JAC"
      if (mlmas > mljac || mumas > mujac)
        {
          write("BANDWITH OF \"MAS\" NOT SMALLER THAN BANDWITH OF \"JAC\"");
          arret = true;
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
          if (n > 2 && iwork(1) != 0)
            {
              ijob = 7;
            }
        }
    }
  integer ldmas2 = std::max(1, ldmas);
  //C ------ HESSENBERG OPTION ONLY FOR EXPLICIT EQU. WITH FULL JACOBIAN
  if ((implct || jband) && ijob == 7)
    {
      write(" HESSENBERG OPTION ONLY FOR EXPLICIT EQUATIONS WITH FULL JACOBIAN");
      arret = true;
    }
  //C ------- PREPARE THE ENTRY-POINTS FOR THE ARRAYS IN WORK -----
  integer iez1 = 21;
  CVectorCore< doublereal > z1(n, &work[iez1]);
  integer iez2 = iez1 + n;
  CVectorCore< doublereal > z2(n, &work[iez2]);
  integer iez3 = iez2 + n;
  CVectorCore< doublereal > z3(n, &work[iez3]);
  integer iey0 = iez3 + n;
  CVectorCore< doublereal > y0(n, &work[iey0]);
  integer iescal = iey0 + n;
  CVectorCore< doublereal > scal(n, &work[iescal]);
  integer ief1 = iescal + n;
  CVectorCore< doublereal > f1(n, &work[ief1]);
  integer ief2 = ief1 + n;
  CVectorCore< doublereal > f2(n, &work[ief2]);
  integer ief3 = ief2 + n;
  CVectorCore< doublereal > f3(n, &work[ief3]);
  integer iecon = ief3 + n;
  CVectorCore< doublereal > cont(4 * n, &work[iecon]);
  integer iejac = iecon + 4 * n;
  CMatrix< doublereal > fjac(n, ldjac, &work[iejac]);
  integer iemas = iejac + n * ldjac;
  CMatrix< doublereal > fmas(nm1, ldmas, &work[iemas]);
  integer iee1 = iemas + nm1 * ldmas;
  CMatrix< doublereal > e1(nm1, lde1, &work[iee1]);
  integer iee2r = iee1 + nm1 * lde1;
  CMatrix< doublereal > e2r(nm1, lde1, &work[iee2r]);
  integer iee2i = iee2r + nm1 * lde1;
  CMatrix< doublereal > e2i(nm1, lde1, &work[iee2i]);

  //C ------ TOTAL STORAGE REQUIREMENT -----------
  integer istore = iee2i + nm1 * lde1 - 1;
  if (istore > lwork)
    {
      write(" INSUFFICIENT STORAGE FOR WORK, MIN. LWORK=", istore);
      arret = true;
    }
  //C ------- ENTRY POINTS FOR INTEGER WORKSPACE -----
  integer ieip1 = 21;
  CVectorCore< integer > ip1(nm1, &iwork[ieip1]);
  integer ieip2 = ieip1 + nm1;
  CVectorCore< integer > ip2(nm1, &iwork[ieip2]);
  integer ieiph = ieip2 + nm1;
  CVectorCore< integer > iph(nm1, &iwork[ieiph]);

  //C --------- TOTAL REQUIREMENT ---------------
  istore = ieiph + nm1 - 1;
  if (istore > liwork)
    {
      write(" INSUFF. STORAGE FOR IWORK, MIN. LIWORK=", istore);
      arret = true;
    }
  //C ------ WHEN A FAIL HAS OCCURED, WE RETURN WITH IDID=-1
  if (arret)
    {
      idid = -1;
      return;
    }
  //C -------- CALL TO CORE INTEGRATOR ------------
  radcor(n, fcn, x, y, xend, hmax, h, rtol, atol, itol,
         jac, ijac, mljac, mujac, mas, mlmas, mumas, solout, iout, idid,
         nmax, uround, safe, thet, fnewt, quot1, quot2, nit, ijob, startn,
         nind1, nind2, nind3, pred, facl, facr, m1, m2, nm1,
         implct, jband, ldjac, lde1, ldmas2, z1, z2,
         z3, y0, scal, f1, f2, f3,
         fjac, e1, e2r, e2i, fmas,
         ip1, ip2, iph, cont, nfcn,
         njac, nstep, naccpt, nrejct, ndec, nsol, rpar, ipar);
  iwork(14) = nfcn;
  iwork(15) = njac;
  iwork(16) = nstep;
  iwork(17) = naccpt;
  iwork(18) = nrejct;
  iwork(19) = ndec;
  iwork(20) = nsol;
  //C -------- RESTORE TOLERANCES
  expm = 1.0e0 / expm;
  if (itol == 0)
    {
      quot = atol(1) / rtol(1);
      rtol(1) = std::pow((10.0e0 * rtol(1)), expm);
      atol(1) = rtol(1) * quot;
    }
  else
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          quot = atol(i) / rtol(i);
          rtol(i) = std::pow((10.0e0 * rtol(i)), expm);
          atol(i) = rtol(i) * quot;
        }
    }
  //C ----------- RETURN -----------
}

//C
//C     END OF SUBROUTINE RADAU5
//C
//C ***********************************************************
//C
void _CRadau5::radcor(const integer & n,
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
                      const CVectorCore< integer > & ipar)
{
  doublereal & xsol = mCommon.xsol;
  doublereal & hsol = mCommon.hsol;
  doublereal & c2m1 = mCommon.c2m1;
  doublereal & c1m1 = mCommon.c1m1;
  integer & mle = mCommon.mle;
  integer & mue = mCommon.mue;
  integer & mbjac = mCommon.mbjac;
  //
  integer lrc = 0;
  bool index1 = false;
  bool index2 = false;
  bool index3 = false;
  doublereal sq6 = 0.0;
  doublereal c1 = 0.0;
  doublereal c2 = 0.0;
  doublereal c1mc2 = 0.0;
  doublereal dd1 = 0.0;
  doublereal dd2 = 0.0;
  doublereal dd3 = 0.0;
  doublereal u1 = 0.0;
  doublereal alph = 0.0;
  doublereal beta = 0.0;
  doublereal cno = 0.0;
  doublereal t11 = 0.0;
  doublereal t12 = 0.0;
  doublereal t13 = 0.0;
  doublereal t21 = 0.0;
  doublereal t22 = 0.0;
  doublereal t23 = 0.0;
  doublereal t31 = 0.0;
  doublereal ti11 = 0.0;
  doublereal ti12 = 0.0;
  doublereal ti13 = 0.0;
  doublereal ti21 = 0.0;
  doublereal ti22 = 0.0;
  doublereal ti23 = 0.0;
  doublereal ti31 = 0.0;
  doublereal ti32 = 0.0;
  doublereal ti33 = 0.0;
  doublereal posneg = 0.0;
  doublereal hmaxn = 0.0;
  doublereal hold = 0.0;
  bool reject = false;
  bool first = false;
  bool last = false;
  doublereal hopt = 0.0;
  doublereal faccon = 0.0;
  doublereal cfac = 0.0;
  integer nsing = 0;
  doublereal xold = 0.0;
  integer irtrn = 0;
  integer nrsol = 0;
  doublereal xosol = 0.0;
  integer i = 0;
  integer nsolu = 0;
  integer n2 = 0;
  integer n3 = 0;
  doublereal hhfac = 0.0;
  integer mujacp = 0;
  integer md = 0;
  integer mm = 0;
  integer k = 0;
  integer j = 0;
  integer j1 = 0;
  integer lbeg = 0;
  integer lend = 0;
  integer mujacj = 0;
  integer l = 0;
  doublereal ysafe = 0.0;
  doublereal delt = 0.0;
  bool caljac = false;
  bool calhes = false;
  doublereal fac1 = 0.0;
  doublereal alphn = 0.0;
  doublereal betan = 0.0;
  integer ier = 0;
  doublereal xph = 0.0;
  doublereal c3q = 0.0;
  doublereal c1q = 0.0;
  doublereal c2q = 0.0;
  doublereal ak1 = 0.0;
  doublereal ak2 = 0.0;
  doublereal ak3 = 0.0;
  doublereal z1i = 0.0;
  doublereal z2i = 0.0;
  doublereal z3i = 0.0;
  integer newt = 0;
  doublereal theta = 0.0;
  doublereal a1 = 0.0;
  doublereal a2 = 0.0;
  doublereal a3 = 0.0;
  doublereal dyno = 0.0;
  doublereal denom = 0.0;
  doublereal dynold = 0.0;
  doublereal thq = 0.0;
  doublereal thqold = 0.0;
  doublereal dyth = 0.0;
  doublereal qnewt = 0.0;
  doublereal f1i = 0.0;
  doublereal f2i = 0.0;
  doublereal f3i = 0.0;
  doublereal err = 0.0;
  doublereal fac = 0.0;
  doublereal quot = 0.0;
  doublereal hnew = 0.0;
  doublereal hacc = 0.0;
  doublereal erracc = 0.0;
  doublereal facgus = 0.0;
  doublereal ak = 0.0;
  doublereal acont3 = 0.0;
  doublereal qt = 0.0;

  //C ----------------------------------------------------------
  //C     CORE INTEGRATOR FOR RADAU5
  //C     PARAMETERS SAME AS IN RADAU5 WITH WORKSPACE ADDED
  //C ----------------------------------------------------------
  //C         DECLARATIONS
  //C ----------------------------------------------------------
  //C *** *** *** *** *** *** ***
  //C  INITIALISATIONS
  //C *** *** *** *** *** *** ***
  //C --------- DUPLIFY N FOR COMMON BLOCK CONT -----
  mCommon.nn = n;
  mCommon.nn2 = 2 * n;
  mCommon.nn3 = 3 * n;
  lrc = 4 * n;
  //C -------- CHECK THE INDEX OF THE PROBLEM -----
  index1 = nind1 != 0;
  index2 = nind2 != 0;
  index3 = nind3 != 0;
  //C ------- COMPUTE MASS MATRIX FOR IMPLICIT CASE ----------
  if (implct)
    {
      mas(nm1, fmas, ldmas, rpar, ipar);
    }
  //C ---------- CONSTANTS ---------
  sq6 = std::sqrt(6.e0);
  c1 = (4.e0 - sq6) / 10.e0;
  c2 = (4.e0 + sq6) / 10.e0;
  c1m1 = c1 - 1.e0;
  c2m1 = c2 - 1.e0;
  c1mc2 = c1 - c2;
  dd1 = -(13.e0 + 7.e0 * sq6) / 3.e0;
  dd2 = (-13.e0 + 7.e0 * sq6) / 3.e0;
  dd3 = -1.e0 / 3.e0;
  u1 = (6.e0 + std::pow(81.e0, (1.e0 / 3.e0)) - std::pow(9.e0, (1.e0 / 3.e0))) / 30.e0;
  alph = (12.e0 - std::pow(81.e0, (1.e0 / 3.e0)) + std::pow(9.e0, (1.e0 / 3.e0))) / 60.e0;
  beta = (std::pow(81.e0, (1.e0 / 3.e0)) + std::pow(9.e0, (1.e0 / 3.e0))) * std::sqrt(3.e0) / 60.e0;
  cno = _dc_decsol::pow2(alph) + _dc_decsol::pow2(beta);
  u1 = 1.0e0 / u1;
  alph = alph / cno;
  beta = beta / cno;
  t11 = 9.1232394870892942792e-02;
  t12 = -0.14125529502095420843e0;
  t13 = -3.0029194105147424492e-02;
  t21 = 0.24171793270710701896e0;
  t22 = 0.20412935229379993199e0;
  t23 = 0.38294211275726193779e0;
  t31 = 0.96604818261509293619e0;
  ti11 = 4.3255798900631553510e0;
  ti12 = 0.33919925181580986954e0;
  ti13 = 0.54177053993587487119e0;
  ti21 = -4.1787185915519047273e0;
  ti22 = -0.32768282076106238708e0;
  ti23 = 0.47662355450055045196e0;
  ti31 = -0.50287263494578687595e0;
  ti32 = 2.5719269498556054292e0;
  ti33 = -0.59603920482822492497e0;
  if (m1 > 0)
    {
      ijob += 10;
    }
  posneg = _dc_decsol::sign(1.e0, xend - x);
  hmaxn = std::min(std::abs(hmax), std::abs(xend - x));
  if (std::abs(h) <= 10.e0 * uround)
    {
      h = 1.0e-6;
    }
  h = std::min(std::abs(h), hmaxn);
  h = _dc_decsol::sign(h, posneg);
  hold = h;
  reject = false;
  first = true;
  last = false;
  if ((x + h * 1.0001e0 - xend) * posneg >= 0.e0)
    {
      h = xend - x;
      last = true;
    }
  hopt = h;
  faccon = 1.e0;
  cfac = safe * (1 + 2 * nit);
  nsing = 0;
  xold = x;
  if (iout != 0)
    {
      irtrn = 1;
      nrsol = 1;
      xosol = xold;
      xsol = x;
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          cont(i) = y(i);
        }
      nsolu = n;
      hsol = hold;
      solout(nrsol, xosol, xsol, y, cont, lrc, nsolu, rpar, ipar, irtrn);
      if (irtrn < 0)
        {
          goto statement_179;
        }
    }
  mle = mljac;
  mue = mujac;
  mbjac = mljac + mujac + 1;
  mCommon.mbb = mlmas + mumas + 1;
  mCommon.mdiag = mle + mue + 1;
  mCommon.mdiff = mle + mue - mumas;
  mCommon.mbdiag = mumas + 1;
  n2 = 2 * n;
  n3 = 3 * n;
  if (itol == 0)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          scal(i) = atol(1) + rtol(1) * std::abs(y(i));
        }
    }
  else
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          scal(i) = atol(i) + rtol(i) * std::abs(y(i));
        }
    }
  hhfac = h;
  fcn(n, x, y, y0, rpar, ipar);
  nfcn++;
//C --- BASIC INTEGRATION STEP
statement_10:
  //C *** *** *** *** *** *** ***
  //C  COMPUTATION OF THE JACOBIAN
  //C *** *** *** *** *** *** ***
  njac++;
  if (ijac == 0)
    {
      //C --- COMPUTE JACOBIAN MATRIX NUMERICALLY
      if (banded)
        {
          //C --- JACOBIAN IS BANDED
          mujacp = mujac + 1;
          md = std::min(mbjac, m2);
          // FEM_DO_SAFE(mm, 1, m1 / m2 + 1)
          for (integer mm = 1; mm <= m1 / m2 + 1; ++mm)
            {
              // FEM_DO_SAFE(k, 1, md)
              for (integer k = 1; k <= md; ++k)
                {
                  j = k + (mm - 1) * m2;
                statement_12:
                  f1(j) = y(j);
                  f2(j) = std::sqrt(uround * std::max(1.e-5, std::abs(y(j))));
                  y(j) += f2(j);
                  j += md;
                  if (j <= mm * m2)
                    {
                      goto statement_12;
                    }
                  fcn(n, x, y, cont, rpar, ipar);
                  j = k + (mm - 1) * m2;
                  j1 = k;
                  lbeg = std::max(1, j1 - mujac) + m1;
                statement_14:
                  lend = std::min(m2, j1 + mljac) + m1;
                  y(j) = f1(j);
                  mujacj = mujacp - j1 - m1;
                  // FEM_DO_SAFE(l, lbeg, lend)
                  for (integer l = lbeg; l <= lend; ++l)
                    {
                      fjac(l + mujacj, j) = (cont(l) - y0(l)) / f2(j);
                    }
                  j += md;
                  j1 += md;
                  lbeg = lend + 1;
                  if (j <= mm * m2)
                    {
                      goto statement_14;
                    }
                }
            }
        }
      else
        {
          //C --- JACOBIAN IS FULL
          // FEM_DO_SAFE(i, 1, n)
          for (integer i = 1; i <= n; ++i)
            {
              ysafe = y(i);
              delt = std::sqrt(uround * std::max(1.e-5, std::abs(ysafe)));
              y(i) = ysafe + delt;
              fcn(n, x, y, cont, rpar, ipar);
              // FEM_DO_SAFE(j, m1 + 1, n)
              for (integer j = m1 + 1; j <= n; ++j)
                {
                  fjac(j - m1, i) = (cont(j) - y0(j)) / delt;
                }
              y(i) = ysafe;
            }
        }
    }
  else
    {
      //C --- COMPUTE JACOBIAN MATRIX ANALYTICALLY
      jac(n, x, y, fjac, ldjac, rpar, ipar);
    }
  caljac = true;
  calhes = true;
statement_20:
  //C --- COMPUTE THE MATRICES E1 AND E2 AND THEIR DECOMPOSITIONS
  fac1 = u1 / h;
  alphn = alph / h;
  betan = beta / h;
  {
    CFortranAccess< CMatrix< doublereal > > __fjac(fjac);
    CFortranAccess< CMatrix< doublereal > > __e1(e1);
    decomr(mCommon, n, __fjac, ldjac, fmas, ldmas, mlmas, mumas, m1, m2, nm1,
           fac1, __e1, lde1, ip1, ier, ijob, calhes, iphes);
  }
  if (ier != 0)
    {
      goto statement_78;
    }
  {
    CFortranAccess< CMatrix< doublereal > > __e2r(e2r);
    CFortranAccess< CMatrix< doublereal > > __e2i(e2i);
    decomc(mCommon, n, fjac, ldjac, fmas, ldmas, mlmas, mumas, m1, m2, nm1,
           alphn, betan, __e2r, __e2i, lde1, ip2, ier, ijob);
  }
  if (ier != 0)
    {
      goto statement_78;
    }
  ndec++;
statement_30:
  nstep++;
  if (nstep > nmax)
    {
      goto statement_178;
    }
  if (0.1e0 * std::abs(h) <= std::abs(x) * uround)
    {
      goto statement_177;
    }
  if (index2)
    {
      // FEM_DO_SAFE(i, nind1 + 1, nind1 + nind2)
      for (integer i = nind1 + 1; i <= nind1 + nind2; ++i)
        {
          scal(i) = scal(i) / hhfac;
        }
    }
  if (index3)
    {
      // FEM_DO_SAFE(i, nind1 + nind2 + 1, nind1 + nind2 + nind3)
      for (integer i = nind1 + nind2 + 1; i <= nind1 + nind2 + nind3; ++i)
        {
          scal(i) = scal(i) / (hhfac * hhfac);
        }
    }
  xph = x + h;
  //C *** *** *** *** *** *** ***
  //C  STARTING VALUES FOR NEWTON ITERATION
  //C *** *** *** *** *** *** ***
  if (first || startn)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          z1(i) = 0.e0;
          z2(i) = 0.e0;
          z3(i) = 0.e0;
          f1(i) = 0.e0;
          f2(i) = 0.e0;
          f3(i) = 0.e0;
        }
    }
  else
    {
      c3q = h / hold;
      c1q = c1 * c3q;
      c2q = c2 * c3q;
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          ak1 = cont(i + n);
          ak2 = cont(i + n2);
          ak3 = cont(i + n3);
          z1i = c1q * (ak1 + (c1q - c2m1) * (ak2 + (c1q - c1m1) * ak3));
          z2i = c2q * (ak1 + (c2q - c2m1) * (ak2 + (c2q - c1m1) * ak3));
          z3i = c3q * (ak1 + (c3q - c2m1) * (ak2 + (c3q - c1m1) * ak3));
          z1(i) = z1i;
          z2(i) = z2i;
          z3(i) = z3i;
          f1(i) = ti11 * z1i + ti12 * z2i + ti13 * z3i;
          f2(i) = ti21 * z1i + ti22 * z2i + ti23 * z3i;
          f3(i) = ti31 * z1i + ti32 * z2i + ti33 * z3i;
        }
    }
  //C *** *** *** *** *** *** ***
  //C  LOOP FOR THE SIMPLIFIED NEWTON ITERATION
  //C *** *** *** *** *** *** ***
  newt = 0;
  faccon = std::pow(std::max(faccon, uround), 0.8e0);
  theta = std::abs(thet);
statement_40:
  if (newt >= nit)
    {
      goto statement_78;
    }
  //C ---     COMPUTE THE RIGHT-HAND SIDE
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      cont(i) = y(i) + z1(i);
    }
  fcn(n, x + c1 * h, cont, z1, rpar, ipar);
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      cont(i) = y(i) + z2(i);
    }
  fcn(n, x + c2 * h, cont, z2, rpar, ipar);
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      cont(i) = y(i) + z3(i);
    }
  fcn(n, xph, cont, z3, rpar, ipar);
  nfcn += 3;
  //C ---     SOLVE THE LINEAR SYSTEMS
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      a1 = z1(i);
      a2 = z2(i);
      a3 = z3(i);
      z1(i) = ti11 * a1 + ti12 * a2 + ti13 * a3;
      z2(i) = ti21 * a1 + ti22 * a2 + ti23 * a3;
      z3(i) = ti31 * a1 + ti32 * a2 + ti33 * a3;
    }
  slvrad(mCommon, n, fjac, ldjac, mljac, mujac, fmas, ldmas, mlmas, mumas, m1,
         m2, nm1, fac1, alphn, betan, e1, e2r, e2i, lde1, z1, z2, z3, f1,
         f2, f3, cont, ip1, ip2, iphes, ier, ijob);
  nsol++;
  newt++;
  dyno = 0.e0;
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      denom = scal(i);
      dyno += _dc_decsol::pow2((z1(i) / denom)) + _dc_decsol::pow2((z2(i) / denom)) + _dc_decsol::pow2((z3(i) / denom));
    }
  dyno = std::sqrt(dyno / n3);
  //C ---     BAD CONVERGENCE OR NUMBER OF ITERATIONS TO LARGE
  if (newt > 1 && newt < nit)
    {
      thq = dyno / dynold;
      if (newt == 2)
        {
          theta = thq;
        }
      else
        {
          theta = std::sqrt(thq * thqold);
        }
      thqold = thq;
      if (theta < 0.99e0)
        {
          faccon = theta / (1.0e0 - theta);
          dyth = faccon * dyno * std::pow(theta, (nit - 1 - newt)) / fnewt;
          if (dyth >= 1.0e0)
            {
              qnewt = std::max(1.0e-4, std::min(20.0e0, dyth));
              hhfac = .8e0 * std::pow(qnewt, (-1.0e0 / (4.0e0 + nit - 1 - newt)));
              h = hhfac * h;
              reject = true;
              last = false;
              if (caljac)
                {
                  goto statement_20;
                }
              goto statement_10;
            }
        }
      else
        {
          goto statement_78;
        }
    }
  dynold = std::max(dyno, uround);
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      f1i = f1(i) + z1(i);
      f2i = f2(i) + z2(i);
      f3i = f3(i) + z3(i);
      f1(i) = f1i;
      f2(i) = f2i;
      f3(i) = f3i;
      z1(i) = t11 * f1i + t12 * f2i + t13 * f3i;
      z2(i) = t21 * f1i + t22 * f2i + t23 * f3i;
      z3(i) = t31 * f1i + f2i;
    }
  if (faccon * dyno > fnewt)
    {
      goto statement_40;
    }
  //C --- ERROR ESTIMATION
  estrad(mCommon, n, fjac, ldjac, mljac, mujac, fmas, ldmas, mlmas, mumas, h,
         dd1, dd2, dd3, fcn, nfcn, y0, y, ijob, x, m1, m2, nm1, e1, lde1,
         z1, z2, z3, cont, f1, f2, ip1, iphes, scal, err, first, reject,
         fac1, rpar, ipar);
  //C --- COMPUTATION OF HNEW
  //C --- WE REQUIRE .2<=HNEW/H<=8.
  fac = std::min(safe, cfac / (newt + 2 * nit));
  quot = std::max(facr, std::min(facl, std::pow(err, .25e0) / fac));
  hnew = h / quot;
  //C *** *** *** *** *** *** ***
  //C  IS THE ERROR SMALL ENOUGH ?
  //C *** *** *** *** *** *** ***
  if (err < 1.e0)
    {
      //C --- STEP IS ACCEPTED
      first = false;
      naccpt++;
      if (pred)
        {
          //C       --- PREDICTIVE CONTROLLER OF GUSTAFSSON
          if (naccpt > 1)
            {
              facgus = (hacc / h) * std::pow((_dc_decsol::pow2(err) / erracc), 0.25e0) / safe;
              facgus = std::max(facr, std::min(facl, facgus));
              quot = std::max(quot, facgus);
              hnew = h / quot;
            }
          hacc = h;
          erracc = std::max(1.0e-2, err);
        }
      xold = x;
      hold = h;
      x = xph;
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          y(i) += z3(i);
          z2i = z2(i);
          z1i = z1(i);
          cont(i + n) = (z2i - z3(i)) / c2m1;
          ak = (z1i - z2i) / c1mc2;
          acont3 = z1i / c1;
          acont3 = (ak - acont3) / c2;
          cont(i + n2) = (ak - cont(i + n)) / c1m1;
          cont(i + n3) = cont(i + n2) - acont3;
        }
      if (itol == 0)
        {
          // FEM_DO_SAFE(i, 1, n)
          for (integer i = 1; i <= n; ++i)
            {
              scal(i) = atol(1) + rtol(1) * std::abs(y(i));
            }
        }
      else
        {
          // FEM_DO_SAFE(i, 1, n)
          for (integer i = 1; i <= n; ++i)
            {
              scal(i) = atol(i) + rtol(i) * std::abs(y(i));
            }
        }
      if (iout != 0)
        {
          nrsol = naccpt + 1;
          xsol = x;
          xosol = xold;
          // FEM_DO_SAFE(i, 1, n)
          for (integer i = 1; i <= n; ++i)
            {
              cont(i) = y(i);
            }
          nsolu = n;
          hsol = hold;
          solout(nrsol, xosol, xsol, y, cont, lrc, nsolu, rpar, ipar, irtrn);
          if (irtrn < 0)
            {
              goto statement_179;
            }
        }
      caljac = false;
      if (last)
        {
          h = hopt;
          idid = 1;
          return;
        }
      fcn(n, x, y, y0, rpar, ipar);
      nfcn++;
      hnew = posneg * std::min(std::abs(hnew), hmaxn);
      hopt = hnew;
      hopt = std::min(h, hnew);
      if (reject)
        {
          hnew = posneg * std::min(std::abs(hnew), std::abs(h));
        }
      reject = false;
      if ((x + hnew / quot1 - xend) * posneg >= 0.e0)
        {
          h = xend - x;
          last = true;
        }
      else
        {
          qt = hnew / h;
          hhfac = h;
          if (theta <= thet && qt >= quot1 && qt <= quot2)
            {
              goto statement_30;
            }
          h = hnew;
        }
      hhfac = h;
      if (theta <= thet)
        {
          goto statement_20;
        }
      goto statement_10;
    }
  else
    {
      //C --- STEP IS REJECTED
      reject = true;
      last = false;
      if (first)
        {
          h = h * 0.1e0;
          hhfac = 0.1e0;
        }
      else
        {
          hhfac = hnew / h;
          h = hnew;
        }
      if (naccpt >= 1)
        {
          nrejct++;
        }
      if (caljac)
        {
          goto statement_20;
        }
      goto statement_10;
    }
//C --- UNEXPECTED STEP-REJECTION
statement_78:
  if (ier != 0)
    {
      nsing++;
      if (nsing >= 5)
        {
          goto statement_176;
        }
    }
  h = h * 0.5e0;
  hhfac = 0.5e0;
  reject = true;
  last = false;
  if (caljac)
    {
      goto statement_20;
    }
  goto statement_10;
//C --- FAIL EXIT
statement_176:
  write("EXIT OF RADAU5 AT X = ", x);
  write(" MATRIX IS REPEATEDLY SINGULAR, IER=", ier);
  idid = -4;
  return;
statement_177:
  write("EXIT OF RADAU5 AT X = ", x);
  write(" STEP SIZE T0O SMALL, H=", h);
  idid = -3;
  return;
statement_178:
  write("EXIT OF RADAU5 AT X = ", x);
  write(" MORE THAN NMAX =", nmax, "STEPS ARE NEEDED");
  idid = -2;
  return;
//C --- EXIT CAUSED BY evalO
statement_179:
  write("EXIT OF RADAU5 AT X = ", x);
  idid = 2;
}

//C
//C     END OF SUBROUTINE RADCOR
//C
//C ***********************************************************
//C
doublereal _CRadau5::contr5(const integer & i,
                            const doublereal & x,
                            const CVectorCore< doublereal > & cont,
                            const integer & /* lrc */)
{
  doublereal return_value = 0.0;
  //C ----------------------------------------------------------
  //C     THIS FUNCTION CAN BE USED FOR CONINUOUS OUTPUT. IT PROVIDES AN
  //C     APPROXIMATION TO THE I-TH COMPONENT OF THE SOLUTION AT X.
  //C     IT GIVES THE VALUE OF THE COLLOCATION POLYNOMIAL, DEFINED FOR
  //C     THE LAST SUCCESSFULLY COMPUTED STEP (BY RADAU5).
  //C ----------------------------------------------------------
  doublereal s = (x - mCommon.xsol) / mCommon.hsol;
  return_value = cont(i) + s * (cont(i + mCommon.nn) + (s - mCommon.c2m1) * (cont(i + mCommon.nn2) + (s - mCommon.c1m1) * cont(i + mCommon.nn3)));
  return return_value;
}
//C
//C     END OF FUNCTION CONTR5
//C
//C ***********************************************************
