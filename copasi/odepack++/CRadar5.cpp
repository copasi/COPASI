// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <cmath>
#include <algorithm>

#include "copasi/copasi.h"

#include "copasi/odepack++/CRadar5.h"
using namespace dc_sumexpdel;

#include "copasi/utilities/CCopasiMessage.h"

CRadar5::common_constn::common_constn()
  : c1(0.0)
  , c2(0.0)
  , c1m1(0.0)
  , c2m1(0.0)
  , c1mc2(0.0)
{}

CRadar5::common_posits::common_posits()
  : x0b(0.0)
  , uround(0.0)
  , hmax(0.0)
  , iact(0)
  , irtrn(0)
  , idif(0)
  , mxst(0)
  , flags(0)
  , flagn(0)
{}

CRadar5::common_bplog::common_bplog()
  : first(0)
  , last(0)
  , reject(0)
  , bpd(0)
{}

CRadar5::common_bpcom::common_bpcom()
  : bpp(0.0)
  , ilbp(0)
  , left(0)
{}

CRadar5::CRadar5()
  : Cxerrwd(false)
  , mCommon()
{}

//C********************************************************
//C
doublereal CRadar5::contr5(const common & cmn,
                          const integer & i,
                          const integer & n,
                          const doublereal & x,
                          const CVectorCore< doublereal > & cont,
                          const doublereal & xsol,
                          const doublereal & hsol)
{
  doublereal return_value = 0.0;
  //C ----------------------------------------------------------
  //C     THIS FUNCTION CAN BE USED FOR CONINUOUS OUTPUT. IT PROVIDES AN
  //C     APPROXIMATION TO THE I-TH COMPONENT OF THE SOLUTION AT X.
  //C     IT GIVES THE VALUE OF THE COLLOCATION POLYNOMIAL, DEFINED FOR
  //C     THE LAST SUCCESSFULLY COMPUTED STEP (BY RADAR5).
  //C ----------------------------------------------------------
  //C     INTEGER, PARAMETER :: DP=kind(1D0)
  //C --- REQUIRED CONSTANTS
  integer n2 = 2 * n;
  integer n3 = 3 * n;
  doublereal s = (x - xsol) / hsol;
  return_value = cont(i) + s * (cont(i + n) + (s - cmn.c2m1) * (cont(i + n2) + (s - cmn.c1m1) * cont(i + n3)));
  return return_value;
}

//C
//C     END OF FUNCTION DLAGR5
//C
void CRadar5::bpdtct(const common & cmn,
                    const integer & n,
                    const doublereal & x,
                    doublereal & h,
                    CVectorCore< doublereal > & y,
                    ARGLAG & arglag,
                    float const & rpar,
                    const integer & ipar,
                    const CVectorCore< doublereal > & ucont,
                    const CVectorCore< doublereal > & grid,
                    const integer & nlags,
                    logical const & first,
                    logical const & last,
                    const doublereal & xend,
                    const integer & igrid,
                    CVectorCore< doublereal > & bpv,
                    integer & ibp,
                    integer & ilbp,
                    doublereal & bpp,
                    logical & bpd,
                    const integer & kmax,
                    PHI & phi,
                    CVectorCore< doublereal > & past,
                    CVectorCore< integer > & ipast,
                    const integer & nrds)
{
  integer lrc = 0;
  doublereal epsilon = 0.0;
  doublereal compar = 0.0;
  doublereal xlast = 0.0;
  doublereal hlast = 0.0;
  integer il = 0;
  doublereal als = 0.0;
  integer ic = 0;
  doublereal ald = 0.0;
  integer l = 0;
  doublereal thlim = 0.0;
  doublereal thrigh = 0.0;
  doublereal thleft = 0.0;
  integer k = 0;
  doublereal thnew = 0.0;
  doublereal xa = 0.0;
  doublereal aln = 0.0;
  doublereal hp = 0.0;
  CVector< doublereal > yadv(n);

  //C ----------------------------------------------------------
  //C     THIS SUBROUTINE CAN BE USED FOR DETECTING BREAKING POINTS
  //C     WITH THE OUTPUT-SUBROUTINE FOR RADAR5. IT PROVIDES AN
  //C     APPROXIMATION TO THE IC-TH COMPONENT OF THE SOLUTION AT X.
  //C ----------------------------------------------------------
  //C C     INTEGER, PARAMETER :: DP=kind(1D0)
  //C----   COMMON BLOCKS
  //C ---
  if (first)
    {
      return;
    }
  bpd = false;
  lrc = 4 * n;
  epsilon = 1.e-10;
  compar = cmn.uround * std::max(dabs(x), dabs(x + h));
  xlast = ucont(lrc + 1);
  hlast = ucont(lrc + 2);
  for (size_t il = 1; il <= nlags; ++il) // for (size_t il =  1; il <=  nlags; ++il) // FEM_DO_SAFE(il, 1, nlags)
    {
      als = arglag(il, x, n, y, rpar, ipar, phi, past, ipast, nrds);
      //C -----  DEVIATING ARGUMENT AT X
      //C -----  EXTRAPOLATION OF THE COLLOCATION POLYNOMIAL
      for (size_t ic = 1; ic <= n; ++ic) // for (size_t ic =  1; ic <=  n; ++ic) // FEM_DO_SAFE(ic, 1, n)
        {
          yadv(ic) = contr5(cmn, ic, n, x + h, ucont, xlast, hlast);
        }
      ald = arglag(il, x + h, n, yadv, rpar, ipar, phi, past, ipast, nrds);
      //C -----  DEVIATING ARGUMENT AT X+H
      if (dabs(als - ald) <= compar)
        {
          goto statement_33;
        }
      for (size_t l = 1; l <= igrid - 1; ++l) // for (size_t l =  1; l <=  igrid - 1; ++l) // FEM_DO_SAFE(l, 1, igrid - 1)
        {
          bpp = grid(l);
          if ((als - bpp) * (ald - bpp) < compar)
            {
              bpd = true;
              //C          BREAKING POINT!
              goto statement_33;
            }
        }
      for (int l = ibp; l >= 1; --l) // FEM_DOSTEP(l, ibp, 1, -1)
        {
          bpp = bpv(l);
          if ((als - bpp) * (ald - bpp) < compar)
            {
              //C          BREAKING POINT!
              bpd = true;
              goto statement_33;
            }
        }
    statement_33:
      if (bpd)
        {
          //C ---
          thlim = 1.e0;
          thrigh = thlim;
          //C --------------------------------------------------
          thleft = 0.e0;
          //C ---
          for (size_t k = 1; k <= kmax; ++k) // FEM_DO_SAFE(k, 1, kmax)
            {
              thnew = thleft - (als - bpp) * (thrigh - thleft) / (ald - als);
              //C ---       TEST DI CONVERGENZA
              if (dabs(thrigh - thnew) <= epsilon || dabs(thleft - thnew) <= epsilon)
                {
                  goto statement_36;
                }
              xa = x + thnew * h;
              for (size_t ic = 1; ic <= n; ++ic) // FEM_DO_SAFE(ic, 1, n)
                {
                  yadv(ic) = contr5(cmn, ic, n, xa, ucont, xlast, hlast);
                }
              aln = arglag(il, xa, n, yadv, rpar, ipar, phi, past, ipast, nrds);
              if ((als - bpp) * (aln - bpp) <= 0.e0)
                {
                  ald = aln;
                  thrigh = thnew;
                }
              else
                {
                  als = aln;
                  thleft = thnew;
                }
              //C ---
            }
        statement_36:
          //C ---      BP FOUND!
          if ((thnew > compar) && (thnew < thlim))
            {
              hp = thnew * h;
              //C ---
              if (hp <= 1.e2 * compar)
                {
                  bpd = false;
                  goto statement_37;
                }
              //C ---
              for (size_t l = 1; l <= igrid - 1; ++l) // FEM_DO_SAFE(l, 1, igrid - 1)
                {
                  bpp = grid(l);
                  if (dabs(bpp - x - hp) <= compar)
                    {
                      bpd = false;
                      goto statement_37;
                    }
                }
              ibp++;
              bpv(ibp) = x + hp;
              h = hp;
              ilbp = il;
              goto statement_37;
            }
          else
            {
              //C ---       BP ALREADY PRESENT
              bpd = false;
            }
        }
    }
statement_37:
  return;
}

void CRadar5::bpacc(const common & cmn,
                   const integer & n,
                   const doublereal & x,
                   doublereal & h,
                   CVectorCore< doublereal > & y,
                   ARGLAG & arglag,
                   float const & rpar,
                   const integer & ipar,
                   CVectorCore< doublereal > & z1,
                   CVectorCore< doublereal > & z2,
                   CVectorCore< doublereal > & z3,
                   logical const & first,
                   CVectorCore< doublereal > & bpv,
                   const integer & ibp,
                   const integer & ilbp,
                   const doublereal & bpp,
                   const integer & kmax,
                   PHI & phi,
                   CVectorCore< doublereal > & past,
                   CVectorCore< integer > & ipast,
                   const integer & nrds)
{
  CVector< doublereal > yapp(n);
  CVector< doublereal > ycont(4 * n);
  doublereal epsilon = 0.0;
  integer i = 0;
  doublereal z3i = 0.0;
  doublereal yi = 0.0;
  doublereal z2i = 0.0;
  doublereal z1i = 0.0;
  doublereal a1 = 0.0;
  doublereal ak = 0.0;
  doublereal acont3 = 0.0;
  doublereal a2 = 0.0;
  doublereal xsol = 0.0;
  doublereal hsol = 0.0;
  doublereal thleft = 0.0;
  doublereal thrigh = 0.0;
  doublereal xl = 0.0;
  doublereal als = 0.0;
  doublereal xr = 0.0;
  doublereal ald = 0.0;
  integer k = 0;
  doublereal fac = 0.0;
  doublereal thnew = 0.0;
  doublereal xap = 0.0;
  //C ----------------------------------------------------------
  //C     THIS SUBROUTINE CAN BE USED FOR APPROXIMATING BREAKING POINTS
  //C     IN TANDEM WITH THE SIMPLIFIED NEWTON ITERATION..
  //C ----------------------------------------------------------
  //C C     INTEGER, PARAMETER :: DP=kind(1D0)
  //C----   COMMON BLOCKS
  //C ---
  epsilon = cmn.uround * 1.e3;
  //C ---   DYNAMIC UPDATE
  for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      z3i = z3(i);
      yi = y(i) + z3i;
      ycont(i) = yi;
      z2i = z2(i);
      z1i = z1(i);
      a1 = (z2i - z3i) / cmn.c2m1;
      ycont(i + n) = a1;
      ak = (z1i - z2i) / cmn.c1mc2;
      acont3 = z1i / cmn.c1;
      acont3 = (ak - acont3) / cmn.c2;
      a2 = (ak - ycont(i + n)) / cmn.c1m1;
      ycont(i + 2 * n) = a2;
      if (!first)
        {
          ycont(i + 3 * n) = a2 - acont3;
        }
      else
        {
          ycont(i + 3 * n) = 0.e0;
        }
    }
  //C ---   INITIAL VALUES FOR THE COMPUTATION
  xsol = x + h;
  hsol = h;
  thleft = 0.9e0;
  thrigh = 1.0e0;
  xl = x + thleft * h;
  for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      yapp(i) = contr5(cmn, i, n, xl, ycont, xsol, hsol);
    }
  als = arglag(ilbp, xl, n, yapp, rpar, ipar, phi, past, ipast, nrds);
  //C ---
  xr = x + thrigh * h;
  ald = arglag(ilbp, xr, n, ycont, rpar, ipar, phi, past, ipast, nrds);
  for (size_t k = 1; k <= kmax; ++k) // FEM_DO_SAFE(k, 1, kmax)
    {
      if (dabs(ald - als) <= epsilon)
        {
          fac = 0.0e0;
        }
      else
        {
          fac = (ald - bpp) / (ald - als);
        }
      thnew = thrigh - fac * (thrigh - thleft);
      thleft = thrigh;
      //C ---       TEST DI CONVERGENZA
      if (dabs(thnew - thrigh) <= epsilon)
        {
          goto statement_36;
        }
      if ((thnew <= 0.5e0) || (thnew >= 1.5e0))
        {

          return;
        }
      thrigh = thnew;
      xap = x + thrigh * h;
      als = ald;
      for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
        {
          yapp(i) = contr5(cmn, i, n, xap, ycont, xsol, hsol);
        }
      ald = arglag(ilbp, xap, n, yapp, rpar, ipar, phi, past, ipast, nrds);
      if (dabs(ald - als) <= epsilon)
        {
          goto statement_36;
        }
    }
statement_36:
  //C ---   BP FOUND
  h = std::min(thrigh, thleft) * h;
  bpv(ibp) = x + h;
}

//C
//C     END OF SUBROUTINE RADAR5
//C
//C ***********************************************************
//C
void CRadar5::radcor(common & cmn,
                    const integer & n,
                    doublereal & x,
                    CVectorCore< doublereal > & y,
                    doublereal & xend,
                    doublereal & h,
                    FCN & fcn,
                    PHI & phi,
                    ARGLAG & arglag,
                    CVectorCore< doublereal > & rtol,
                    CVectorCore< doublereal > & atol,
                    const integer & itol,
                    JAC & jac,
                    const integer & ijac,
                    const integer & mljac,
                    const integer & mujac,
                    JACLAG & jaclag,
                    MAS & mas,
                    const integer & mlmas,
                    const integer & mumas,
                    SOLOUT & solout,
                    const integer & iout,
                    integer & idid,
                    const integer & nmax,
                    const doublereal & safe,
                    const doublereal & thet,
                    const doublereal & fnewt,
                    const doublereal & quot1,
                    const doublereal & quot2,
                    const integer & nit,
                    integer & ijob,
                    logical const & startn,
                    const integer & nind1,
                    const integer & nind2,
                    const integer & nind3,
                    logical const & pred,
                    const doublereal & facl,
                    const doublereal & facr,
                    const integer & m1,
                    const integer & m2,
                    const integer & nm1,
                    logical const & implct,
                    logical const & neutral,
                    const integer & ndimn,
                    logical const & banded,
                    const integer & ldjac,
                    const integer & lde1,
                    const integer & ldmas,
                    integer & nfcn,
                    integer & njac,
                    integer & nstep,
                    integer & naccpt,
                    integer & nrejct,
                    integer & ndec,
                    integer & nsol,
                    integer & nfull,
                    const doublereal & rpar,
                    const integer & ipar,
                    CVectorCore< integer > & ipast,
                    CVectorCore< doublereal > & grid,
                    const integer & /* lgrid */,
                    const integer & nrds,
                    const integer & nlags,
                    const integer & njacl,
                    const integer & ngrid,
                    const integer & ieflag,
                    const doublereal & work7,
                    const doublereal & tckbp,
                    const doublereal & alpha,
                    const integer & iswjl)
{
  doublereal & x0b = cmn.x0b;
  const doublereal & uround = cmn.uround;
  doublereal & hmax = cmn.hmax;
  integer & iact = cmn.iact;
  integer & irtrn = cmn.irtrn;
  const integer & idif = cmn.idif;
  const integer & mxst = cmn.mxst;
  logical & flags = cmn.flags;
  logical & flagn = cmn.flagn;
  doublereal & c1 = cmn.c1;
  doublereal & c2 = cmn.c2;
  doublereal & c1m1 = cmn.c1m1;
  doublereal & c2m1 = cmn.c2m1;
  doublereal & c1mc2 = cmn.c1mc2;
  logical & first = cmn.first;
  logical & last = cmn.last;
  logical & reject = cmn.reject;
  logical & bpd = cmn.bpd;
  doublereal & bpp = cmn.bpp;
  integer & ilbp = cmn.ilbp;
  logical & left = cmn.left;
  integer & mle = cmn.mle;
  integer & mue = cmn.mue;
  integer & mbjac = cmn.mbjac;
  //
  integer lrc = 0;
  logical bpc = 0;
  logical bpdmem = 0;
  logical quadr = 0;
  logical callag = 0;
  integer ipos = 0;
  integer i = 0;
  integer igrid = 0;
  integer ibp = 0;
  doublereal btol = 0.0;
  integer kmax = 0;
  integer imant = 0;
  logical flagus = 0;
  doublereal erracc = 0.0;
  doublereal rtolm = 0.0;
  logical index1 = 0;
  logical index2 = 0;
  logical index3 = 0;
  doublereal sq6 = 0.0;
  doublereal cq1 = 0.0;
  doublereal cq2 = 0.0;
  doublereal cq3 = 0.0;
  doublereal cl1 = 0.0;
  doublereal cl2 = 0.0;
  doublereal cl3 = 0.0;
  doublereal cers = 0.0;
  doublereal cerc = 0.0;
  doublereal cerlq = 0.0;
  doublereal thrs = 0.0;
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
  doublereal ai11 = 0.0;
  doublereal ai12 = 0.0;
  doublereal ai13 = 0.0;
  doublereal ai21 = 0.0;
  doublereal ai22 = 0.0;
  doublereal ai23 = 0.0;
  doublereal ai31 = 0.0;
  doublereal ai32 = 0.0;
  doublereal ai33 = 0.0;
  doublereal hmaxn = 0.0;
  doublereal hold = 0.0;
  integer niter = 0;
  integer ipa = 0;
  integer j = 0;
  integer k = 0;
  doublereal faccon = 0.0;
  doublereal cfac = 0.0;
  integer nsing = 0;
  doublereal xold = 0.0;
  integer nrsol = 0;
  doublereal xosol = 0.0;
  doublereal xsol = 0.0;
  integer nsolu = 0;
  doublereal hsol = 0.0;
  integer n2 = 0;
  integer n3 = 0;
  doublereal hhfac = 0.0;
  doublereal alopt = 0.0;
  integer mujacp = 0;
  integer md = 0;
  integer mm = 0;
  integer j1 = 0;
  integer lbeg = 0;
  integer lend = 0;
  integer mujacj = 0;
  integer l = 0;
  doublereal ysafe = 0.0;
  doublereal delt = 0.0;
  logical caljac = 0;
  logical calhes = 0;
  integer jlflag = 0;
  doublereal a1 = 0.0;
  doublereal c3q = 0.0;
  doublereal c1q = 0.0;
  doublereal c2q = 0.0;
  doublereal ak1 = 0.0;
  doublereal ak2 = 0.0;
  doublereal ak3 = 0.0;
  doublereal z1i = 0.0;
  doublereal z2i = 0.0;
  doublereal z3i = 0.0;
  logical caljacl = 0;
  doublereal x1 = 0.0;
  doublereal x2 = 0.0;
  doublereal x3 = 0.0;
  integer il = 0;
  integer ll = 0;
  integer nl = 0;
  integer is = 0;
  doublereal xact = 0.0;
  doublereal x13 = 0.0;
  doublereal s1 = 0.0;
  doublereal s2 = 0.0;
  doublereal s3 = 0.0;
  integer ile = 0;
  integer kk = 0;
  integer ik = 0;
  integer jk = 0;
  doublereal fac1 = 0.0;
  doublereal alphn = 0.0;
  doublereal betan = 0.0;
  integer ier = 0;
  doublereal xph = 0.0;
  integer newt = 0;
  doublereal theta = 0.0;
  doublereal ak = 0.0;
  doublereal acont3 = 0.0;
  doublereal a2 = 0.0;
  integer inrej = 0;
  doublereal dbp = 0.0;
  doublereal xx = 0.0;
  doublereal a3 = 0.0;
  doublereal dyno = 0.0;
  doublereal denom = 0.0;
  doublereal dynold = 0.0;
  doublereal thq = 0.0;
  doublereal thqold = 0.0;
  doublereal dyth = 0.0;
  doublereal hp = 0.0;
  doublereal qnewt = 0.0;
  doublereal f1i = 0.0;
  doublereal f2i = 0.0;
  doublereal f3i = 0.0;
  doublereal hnewt = 0.0;
  doublereal fij = 0.0;
  doublereal dl1 = 0.0;
  doublereal dl2 = 0.0;
  doublereal dl3 = 0.0;
  doublereal xl = 0.0;
  doublereal dcoli1 = 0.0;
  doublereal dcoli2 = 0.0;
  doublereal dcoli3 = 0.0;
  doublereal fjlk = 0.0;
  integer iki = 0;
  doublereal ai11h = 0.0;
  doublereal ai12h = 0.0;
  doublereal ai13h = 0.0;
  doublereal ai21h = 0.0;
  doublereal ai22h = 0.0;
  doublereal ai23h = 0.0;
  doublereal ai31h = 0.0;
  doublereal ai32h = 0.0;
  doublereal ai33h = 0.0;
  integer i1 = 0;
  doublereal serr = 0.0;
  doublereal cerr = 0.0;
  doublereal fac = 0.0;
  doublereal err = 0.0;
  doublereal quot = 0.0;
  doublereal hnew = 0.0;
  doublereal cerr2 = 0.0;
  logical repeat = 0;
  doublereal hacc = 0.0;
  doublereal facgus = 0.0;
  doublereal yi = 0.0;
  doublereal he = 0.0;
  doublereal xlr = 0.0;
  logical project = 0;
  doublereal posneg = 0.0;
  doublereal xeps = 0.0;
  doublereal hopt = 0.0;
  doublereal qt = 0.0;
  //C ----------------------------------------------------------
  //C     CORE INTEGRATOR FOR RADAR5
  //C     PARAMETERS SAME AS IN RADAR5 WITH WORKSPACE ADDED
  //C ----------------------------------------------------------
  //C         DECLARATIONS
  //C ----------------------------------------------------------
  //C     use definitions
  //C     INTEGER, PARAMETER :: DP=kind(1D0)
  //C ----> COMMON BLOCKS <----
  //C ----
  //C *** *** *** *** *** *** ***
  //C  INITIALISATIONS
  //C *** *** *** *** *** *** ***
  CVector< doublereal > z1(n);
  CVector< doublereal > z2(n);
  CVector< doublereal > z3(n);
  CVector< doublereal > y0(n);
  CVector< doublereal > scal(n);
  CVector< doublereal > f1(n);
  CVector< doublereal > f2(n);
  CVector< doublereal > f3(n);

  CMatrix< doublereal > _fjac(ldjac, n);
  CFortranAccess< CMatrix< doublereal > > fjac(_fjac);
  CVector< doublereal > zl(3 * n);

  CVector< doublereal > bpv(10000);
  CMatrix< doublereal > _fmas(0, 0);
  CFortranAccess< CMatrix< doublereal > > fmas(_fmas);

  if (implct)
    _fmas.resize(ldmas, nm1);

  CVector< integer > ip1(nm1);
  CVector< integer > ip2(nm1);
  CVector< integer > iphes(nm1);
  CMatrix< doublereal > _e1(lde1, nm1);
  CMatrix< doublereal > _e2r(lde1, nm1);
  CMatrix< doublereal > _e2i(lde1, nm1);
  CVector< doublereal > past(mxst * idif);

  CMatrix< doublereal > _fjacs(0, 0);
  CFortranAccess< CMatrix< doublereal > > fjacs(_fjacs);
  CVector< doublereal > fjaclag(0);
  CVector< integer > ivl(0);
  CVector< integer > ive(0);
  CVector< integer > ivc(0);
  CVector< integer > ils(0);
  CMatrix< integer > _icoun(0, 0);
  CFortranAccess< CMatrix< integer > > icoun(_icoun);
  CMatrix< doublereal > _xlag(0, 0);
  CFortranAccess< CMatrix< doublereal > > xlag(_xlag);
  CVector< integer > ipj(0);
  CMatrix< doublereal > _fjacl(0, 0);
  CFortranAccess< CMatrix< doublereal > > fjacl(_fjacl);

  if (nlags > 0)
    {
      _fjacs.resize(ldjac, n);
      fjaclag.resize(njacl);
      ivl.resize(njacl);
      ive.resize(njacl);
      ivc.resize(njacl);
      ils.resize(2 * nlags + njacl);
      _icoun.resize(3, nlags);

      if (iswjl != 1)
        {
          ipj.resize(3 * n);
          _fjacl.resize(3 * n, 3 * n);
        }

      _xlag.resize(3, nlags);
    }

  //C
  //C     AMPLITUDE OF CONT
  lrc = 4 * n;
  CVector< doublereal > cont(lrc);
  CVector< doublereal > ucont(lrc + 2);

  //C ---
  //C
  //C -------------------------------------------------
  bpc = false;
  bpd = false;
  bpdmem = false;
  quadr = false;
  ilbp = 0;
  //C
  //C --- INITIAL PREPARATIONS
  callag = false;
  iact = 1;
  ipos = 1;
  for (size_t i = 1; i <= nlags; ++i) // FEM_DO_SAFE(i, 1, nlags)
    {
      ipast(i + 2 * n) = 1;
    }
  x0b = x;
  for (size_t i = 1; i <= ngrid; ++i) // FEM_DO_SAFE(i, 1, ngrid)
    {
      if (grid(i) > x0b)
        {
          igrid = i;
          goto statement_2;
        }
    }
statement_2:
  xend = grid(igrid);
  ibp = 1;
  bpv(1) = x0b;
  btol = 1.e1 * uround;
  kmax = 10;
  imant = 0;
  //C
  //C --- GUSTAFFSON TECHNIQUE AFTER BREAKING POINTS IS NOT APPLIED
  flagus = false;
  erracc = 1.e0;
  //C
  irtrn = 2;
  fcn(n, x, y, y0, arglag, phi, rpar, ipar, past, ipast, nrds);
  irtrn = 1;
  //C
  //C     TOLMIN
  if (itol == 0)
    {
      rtolm = rtol(1);
    }
  else
    {
      rtolm = rtol(1);
      for (size_t i = 2; i <= n; ++i) // FEM_DO_SAFE(i, 2, n)
        {
          if (rtol(i) < rtolm)
            {
              rtolm = rtol(i);
            }
        }
    }
  //C
  //C -------- CHECK THE INDEX OF THE PROBLEM -----
  index1 = nind1 != 0;
  index2 = nind2 != 0;
  index3 = nind3 != 0;
  //C ------- COMPUTE MASS MATRIX FOR IMPLICIT CASE ----------
  if (implct)
    {
      mas(nm1, _fmas, ldmas, rpar, ipar);
    }
  //C ---------> REQUIRED CONSTANTS <---------
  sq6 = std::sqrt(6.e0);
  c1 = (4.e0 - sq6) / 10.e0;
  c2 = (4.e0 + sq6) / 10.e0;
  c1m1 = c1 - 1.e0;
  c2m1 = c2 - 1.e0;
  c1mc2 = c1 - c2;
  cq1 = (2.e0 + 3.e0 * sq6) / 6.e0;
  cq2 = (2.e0 - 3.e0 * sq6) / 6.e0;
  cq3 = 1.e0 / 3.e0;
  cl1 = 10.e0 / (6.e0 + sq6);
  cl2 = 0.e0;
  cl3 = (-4.e0 + sq6) / (6.e0 + sq6);
  cers = 5.e-1;
  cerc = 5.e-1;
  cerlq = 1.e-2;
  thrs = 100.e0;
  dd1 = -(13.e0 + 7.e0 * sq6) / 3.e0;
  dd2 = (-13.e0 + 7.e0 * sq6) / 3.e0;
  dd3 = -1.e0 / 3.e0;
  u1 = (6.e0 + pow(81.e0, (1.e0 / 3.e0)) - pow(9.e0, (1.e0 / 3.e0))) / 30.e0;
  alph = (12.e0 - pow(81.e0, (1.e0 / 3.e0)) + pow(9.e0, (1.e0 / 3.e0))) / 60.e0;
  beta = (pow(81.e0, (1.e0 / 3.e0)) + pow(9.e0, (1.e0 / 3.e0))) * std::sqrt(3.e0) / 60.e0;
  cno = pow2(alph) + pow2(beta);
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
  //C
  //C     INVERSE OF A
  if (nlags > 0 && iswjl != 1)
    {
      ai11 = 3.22474487139158904909864e0;
      ai12 = 1.16784008469040549492404e0;
      ai13 = -0.25319726474218082618594e0;
      ai21 = -3.56784008469040549492404e0;
      ai22 = 0.77525512860841095090136e0;
      ai23 = 1.05319726474218082618594e0;
      ai31 = 5.53197264742180826185942e0;
      ai32 = -7.53197264742180826185942e0;
      ai33 = 5.00000000000000000000000e0;
    }
  //C
  if (m1 > 0)
    {
      ijob += 10;
    }
  hmaxn = std::min(hmax, xend - x);
  if (h <= 10.e0 * uround)
    {
      h = 1.0e-6;
    }
  h = std::min(h, hmaxn);
  hold = h;
  reject = false;
  first = true;
  last = false;
  niter = 0;
  if ((x + h * 1.0001e0 - xend) >= 0.e0)
    {
      h = xend - x;
      last = true;
    }
  //C ---  INITIALIZATION FOR THE ARRAY PAST
  for (size_t i = 0; i <= mxst - 1; ++i) // FEM_DO_SAFE(i, 0, mxst - 1)
    {
      past(1 + idif * i) = x;
    }
  ipa = (mxst - 1) * idif + 1;
  for (size_t j = 1; j <= nrds; ++j) // FEM_DO_SAFE(j, 1, nrds)
    {
      k = ipast(j);
      past(j + ipa) = y(k);
      past(j + 1 * nrds + ipa) = 0.e0;
      past(j + 2 * nrds + ipa) = 0.e0;
      past(j + 3 * nrds + ipa) = 0.e0;
    }
  past(ipa + idif - 1) = h;
  //C ---  END OF THE INITIALIZATION
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
      cont = y;
      nsolu = n;
      hsol = hold;
      solout(nrsol, xosol, xsol, hsol, y, cont, lrc, nsolu, rpar, ipar, irtrn);
      if (irtrn < 0)
        {
          goto statement_179;
        }
    }
  mle = mljac;
  mue = mujac;
  mbjac = mljac + mujac + 1;
  cmn.mbb = mlmas + mumas + 1;
  cmn.mdiag = mle + mue + 1;
  cmn.mdiff = mle + mue - mumas;
  cmn.mbdiag = mumas + 1;
  n2 = 2 * n;
  n3 = 3 * n;
  if (itol == 0)
    {
      for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
        {
          scal(i) = atol(1) + rtol(1) * dabs(y(i));
        }
    }
  else
    {
      for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
        {
          scal(i) = atol(i) + rtol(i) * dabs(y(i));
        }
    }
  hhfac = h;
  nfcn++;
  //C
  nfull = 0;
//C --------------------------
//C --- BASIC INTEGRATION STEP
//C --------------------------
statement_10:
  //C *** *** *** *** *** *** ***
  //C  COMPUTATION OF THE JACOBIAN
  //C *** *** *** *** *** *** ***
  //C -----------------------
  flags = false;
  flagn = false;
  //C -----------------------
  alopt = 0.e0;
  njac++;
  if (bpd)
    {
      bpdmem = true;
      bpd = false;
    }
  if (ijac == 0)
    {
      //C --- COMPUTE JACOBIAN MATRIX NUMERICALLY
      if (banded)
        {
          //C --- JACOBIAN IS BANDED
          mujacp = mujac + 1;
          md = std::min(mbjac, m2);
          for (size_t mm = 1; mm <= m1 / m2 + 1; ++mm) // FEM_DO_SAFE(mm, 1, m1 / m2 + 1)
            {
              for (size_t k = 1; k <= md; ++k) // FEM_DO_SAFE(k, 1, md)
                {
                  j = k + (mm - 1) * m2;
                statement_12:
                  f1(j) = y(j);
                  f2(j) = std::sqrt(uround * std::max(1.e-5, dabs(y(j))));
                  y(j) += f2(j);
                  j += md;
                  if (j <= mm * m2)
                    {
                      goto statement_12;
                    }
                  fcn(n, x, y, cont, arglag, phi, rpar, ipar, past, ipast, nrds);
                  j = k + (mm - 1) * m2;
                  j1 = k;
                  lbeg = std::max(1, j1 - mujac) + m1;
                statement_14:
                  lend = std::min(m2, j1 + mljac) + m1;
                  y(j) = f1(j);
                  mujacj = mujacp - j1 - m1;
                  for (size_t l = lbeg; l <= lend; ++l) // FEM_DO_SAFE(l, lbeg, lend)
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
          for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
            {
              ysafe = y(i);
              delt = std::sqrt(uround * std::max(1.e-5, dabs(ysafe)));
              y(i) = ysafe + delt;
              fcn(n, x, y, cont, arglag, phi, rpar, ipar, past, ipast, nrds);
              for (size_t j = m1 + 1; j <= n; ++j) // FEM_DO_SAFE(j, m1 + 1, n)
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
      jac(n, x, y, _fjac, ldjac, arglag, phi, rpar, ipar, past, ipast, nrds);
    }
  if (bpdmem)
    {
      bpdmem = false;
      bpd = true;
    }
  caljac = true;
  calhes = true;
  jlflag = 0;
  //C --- SAVE FJAC
  if (nlags > 0)
    {
      _fjacs = _fjac;
    }
//C
//C ------------------------------------------------
//C --- GLOBAL ITERATION BEGINS HERE
//C ------------------------------------------------
statement_20:
  //C
  //C *** *** *** *** *** *** ***
  //C  STARTING VALUES FOR NEWTON ITERATION
  //C *** *** *** *** *** *** ***
  //C
  if (first || startn)
    {
      for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
        {
          z1(i) = 0.e0;
          z2(i) = 0.e0;
          z3(i) = 0.e0;
          f1(i) = 0.e0;
          f2(i) = 0.e0;
          f3(i) = 0.e0;
          //C
          a1 = y(i);
          zl(i) = a1;
          zl(i + n) = a1;
          zl(i + n2) = a1;
        }
    }
  else
    {
      c3q = h / hold;
      c1q = c1 * c3q;
      c2q = c2 * c3q;
      for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
        {
          a1 = y(i);
          ak1 = cont(i + n);
          ak2 = cont(i + n2);
          ak3 = cont(i + n3);
          z1i = c1q * (ak1 + (c1q - c2m1) * (ak2 + (c1q - c1m1) * ak3));
          z2i = c2q * (ak1 + (c2q - c2m1) * (ak2 + (c2q - c1m1) * ak3));
          z3i = c3q * (ak1 + (c3q - c2m1) * (ak2 + (c3q - c1m1) * ak3));
          z1(i) = z1i;
          z2(i) = z2i;
          z3(i) = z3i;
          //C
          zl(i) = a1 + z1i;
          f1(i) = ti11 * z1i + ti12 * z2i + ti13 * z3i;
          f2(i) = ti21 * z1i + ti22 * z2i + ti23 * z3i;
          f3(i) = ti31 * z1i + ti32 * z2i + ti33 * z3i;
        }
      if (nlags > 0)
        {
          for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
            {
              a1 = y(i);
              zl(i + n) = a1 + z2(i);
              zl(i + n2) = a1 + z3(i);
            }
        }
    }
  //C ---
  if (jlflag == 0)
    {
      if (nlags == 0)
        {
          if (!(reject || last))
            {
              if (imant == 1)
                {
                  goto statement_30;
                }
            }
          goto statement_22;
        }
      //C ---------------------
      //C      INITIALIZATION
      //C
      //C ---  LAGS CYCLE --- C
      //C ---
      caljacl = false;
      x1 = x + c1 * h;
      x2 = x + c2 * h;
      x3 = x + h;
      for (size_t il = 1; il <= nlags; ++il) // FEM_DO_SAFE(il, 1, nlags)
        {
          xlag(1, il) = 0.e0;
          xlag(2, il) = 0.e0;
          xlag(3, il) = 0.e0;
          icoun(1, il) = 0;
          icoun(2, il) = 0;
          icoun(3, il) = 0;
        }
      //C ---  LOOP ON LAG TERMS
      for (size_t il = 1; il <= nlags; ++il) // FEM_DO_SAFE(il, 1, nlags)
        {
          //C ---   DELAYED ARGUMENTS ARE COMPUTED
          xlag(1, il) = arglag(il, x1, n, zl, rpar, ipar, phi, past, ipast, nrds);
          if (xlag(1, il) > x)
            {
              icoun(1, il) = 1;
            }
          xlag(2, il) = arglag(il, x2, n, zl(n + 1), rpar, ipar, phi,
                               past, ipast, nrds);
          if (xlag(2, il) > x)
            {
              icoun(2, il) = 1;
            }
          xlag(3, il) = arglag(il, x3, n, zl(n2 + 1), rpar, ipar, phi,
                               past, ipast, nrds);
          if (xlag(3, il) > x)
            {
              icoun(3, il) = 1;
            }
          if (icoun(1, il) + icoun(2, il) + icoun(3, il) >= 1)
            {
              caljacl = true;
            }
        }
      //C
      if (caljacl)
        {
          jaclag(n, x, y, fjaclag, arglag, phi, ive, ivc, ivl, rpar,
                 ipar, past, ipast, nrds);
          if (!callag)
            {
              callag = true;
              //C --     ORDERING STEP
              ll = 2 * nlags + 1;
              for (size_t l = 1; l <= nlags; ++l) // FEM_DO_SAFE(l, 1, nlags)
                {
                  nl = 0;
                  for (size_t i = 1; i <= njacl; ++i) // FEM_DO_SAFE(i, 1, njacl)
                    {
                      if (ivl(i) == l)
                        {
                          ils(ll) = i;
                          nl++;
                          ll++;
                        }
                    }
                  ils(2 * l - 1) = nl;
                  ils(2 * l) = ll - 1;
                }
            }
          //C
          for (size_t il = 1; il <= nlags; ++il) // FEM_DO_SAFE(il, 1, nlags)
            {
              for (size_t is = 1; is <= 3; ++is) // FEM_DO_SAFE(is, 1, 3)
                {
                  if (is == 1)
                    {
                      xact = x1;
                    }
                  if (is == 2)
                    {
                      xact = x2;
                    }
                  if (is == 3)
                    {
                      xact = x13;
                    }
                  if (xlag(is, il) > xact)
                    {
                      if (iout == 2)
                        {
                          write("WARNING!: ADVANCED ARGUMENTS ARE USED AT X = ", xact);
                        }
                      xlag(is, il) = xact;
                    }
                }
              //C
              //C ------ JACOBIAN MAINTAINS THE TENSOR STRUCTURE
              //C ------ UPDATING CONDITION
              alopt = 0.e0;
              if (icoun(1, il) == 1)
                {
                  s1 = dim(xlag(1, il), x) / h;
                  alopt = (-1.e0 + s1) * s1 * (-13.e0 - 7.e0 * std::sqrt(6.e0) + 5.e0 * (2.e0 + 3.e0 * std::sqrt(6.e0)) * s1);
                }
              if (icoun(2, il) == 1)
                {
                  s2 = dim(xlag(2, il), x) / h;
                  alopt = alopt - (-1 + s2) * s2 * (13.e0 - 7.e0 * std::sqrt(6.e0) + 5.e0 * (-2.e0 + 3.e0 * std::sqrt(6.e0)) * s2);
                }
              if (icoun(3, il) == 1)
                {
                  s3 = dim(xlag(3, il), x) / h;
                  alopt += s3 * (1.e0 - 8.e0 * s3 + 10.e0 * pow2(s3));
                }
              alopt = alopt / 9.e0;
              //C
              //C         OPTIMAL COEFFICIENT (W.R.T. FROBENIUS NORM)
              //C         JACLAG ~= ALOPT*I
              //C
              //C         ACTIVATES IF ALOPT DIFFERENT FROM ZERO
              if (dabs(alopt) >= 1.e-8)
                {
                  nl = ils(2 * il - 1);
                  ile = ils(2 * il);
                  for (size_t k = 1; k <= nl; ++k) // FEM_DO_SAFE(k, 1, nl)
                    {
                      kk = ils(ile - k + 1);
                      ik = ive(kk);
                      jk = ivc(kk);
                      fjac(ik, jk) += alopt * fjaclag(kk);
                    }
                }
              else
                {
                  caljacl = false;
                }
            }
          //C
        }
      else
        {
          //C ---   FACTORIZATION IS CONSERVED
        }
      if (!(reject || last || caljacl))
        {
          if (imant == 1)
            {
              goto statement_30;
            }
        }
      goto statement_22;
      //C ---
    }
  else if (jlflag == 1)
    {
      //C ---  THE FULL ITERATION MAKES USE OF THE SAME STEPSIZE OF THE SIMPLIFIED
      goto statement_23;
      //C ---
    }
//C
//C - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//C - - THE DIFFERENCE IN THE SOLUTION OF THE SYSTEM STARTS HERE
//C ------------------------------- - - - - - - - - - - - - - - -
//C --- SIMPLE NEWTON ITERATION
//C -------------------------------
statement_22:
  //C
  //C --- COMPUTE THE MATRICES E1 AND E2 AND THEIR DECOMPOSITIONS
  fac1 = u1 / h;
  alphn = alph / h;
  betan = beta / h;
  //C --- RK JACOBIAN FACTORIZATION
  decomr(cmn, n, _fjac, ldjac, _fmas, ldmas, mlmas, mumas, m1, m2, nm1,
         fac1, _e1, lde1, ip1, ier, ijob, calhes, iphes);
  if (ier != 0)
    {
      goto statement_78;
    }
  decomc(cmn, n, _fjac, ldjac, _fmas, ldmas, mlmas, mumas, m1, m2, nm1,
         alphn, betan, _e2r, _e2i, lde1, ip2, ier, ijob);
  if (ier != 0)
    {
      goto statement_78;
    }
  ndec++;
//C ---
statement_30:
  //C --- UPDATE NSTEP
  nstep++;
  if (nstep > nmax)
    {
      goto statement_178;
    }
  if (0.1e0 * h <= dabs(x) * uround)
    {
      goto statement_177;
    }
  if (index2)
    {
      for (size_t i = nind1 + 1; i <= nind1 + nind2; ++i) // FEM_DO_SAFE(i, nind1 + 1, nind1 + nind2)
        {
          scal(i) = scal(i) / hhfac;
        }
    }
  if (index3)
    {
      for (size_t i = nind1 + nind2 + 1; i <= nind1 + nind2 + nind3; ++i) // FEM_DO_SAFE(i, nind1 + nind2 + 1, nind1 + nind2 + nind3)
        {
          scal(i) = scal(i) / (hhfac * hhfac);
        }
    }
  xph = x + h;
  //C
  //C *** *** *** *** *** *** ***
  //C  LOOP FOR THE SIMPLE NEWTON ITERATION
  //C *** *** *** *** *** *** ***
  //C              -----------
  newt = 0;
  imant = 0;
  //C -----------------------
  flags = false;
  flagn = false;
  //C -----------------------
  faccon = pow(std::max(faccon, uround), 0.8e0);
  theta = dabs(thet);
//C -------------------------------------------------------
//C           REFERENCE POINT FOR THE SIMPLE AZIONE SIMPLE
//C -------------------------------------------------------
statement_40:
  //C -------------------------
  if (flags)
    {
      flagn = true;
      //C ---        CALLS SUBROUTINE LAGR5
      //C -------------------------------------------------------------
      //C ---------- DYNAMIC UPDATE OF INTERPOLANT (in PAST).
      //C -------------------------------------------------------------
      for (size_t j = 1; j <= nrds; ++j) // FEM_DO_SAFE(j, 1, nrds)
        {
          i = ipast(j);
          past(j + iact) = y(i) + z3(i);
          z2i = z2(i);
          z1i = z1(i);
          a1 = (z2i - z3(i)) / c2m1;
          past(j + 1 * nrds + iact) = a1;
          ak = (z1i - z2i) / c1mc2;
          acont3 = z1i / c1;
          acont3 = (ak - acont3) / c2;
          a2 = (ak - a1) / c1m1;
          past(j + 2 * nrds + iact) = a2;
          past(j + 3 * nrds + iact) = a2 - acont3;
        }
      //C ---        UPDATE DI PAST
      past(iact) = x;
      //C            LEFT ENDPOINT
      past(iact + idif - 1) = h;
      //C            STEPSIZE
    }
  //C ----------------
  if (newt >= nit)
    {
      inrej = 2;
      goto statement_421;
    }
  //C -----------------------------------
  //C ---     COMPUTE THE RIGHT-HAND SIDE
  for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      a1 = y(i);
      zl(i) = a1 + z1(i);
      zl(i + n) = a1 + z2(i);
      zl(i + n2) = a1 + z3(i);
    }
  //C           COMPUTATION OF STAGE VALUES
  fcn(n, x + c1 * h, zl, z1, arglag, phi, rpar, ipar, past, ipast, nrds);
  fcn(n, x + c2 * h, zl(n + 1), z2, arglag, phi, rpar, ipar, past, ipast, nrds);
  if (bpd)
    {
      //C ----------------------------------------------------------------------
      //C ---         A BREAKING POINT HAS BEEN DETECTED
      //C ----------------------------------------------------------------
      left = false;
      dbp = arglag(ilbp, x + c2 * h, n, zl(n + 1), rpar, ipar, phi,
                   past, ipast, nrds);
      if (dbp < bpp)
        {
          left = true;
        }
    }
  else if (last)
    {
      //C ---         DISC. FLAG
      xx = (x + h) * (1.e0 - btol);
      for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
        {
          zl(n2 + i) = (1.e0 - btol) * zl(n2 + i) + btol * zl(n + i);
        }
      fcn(n, xx, zl(n2 + 1), z3, arglag, phi, rpar, ipar, past, ipast, nrds);
      goto statement_42;
    }
  fcn(n, x + h, zl(n2 + 1), z3, arglag, phi, rpar, ipar, past, ipast, nrds);
statement_42:
  //C
  nfcn += 3;
  //C -----------------------------------
  //C ---     SOLVE THE LINEAR SYSTEMS
  for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      a1 = z1(i);
      a2 = z2(i);
      a3 = z3(i);
      z1(i) = ti11 * a1 + ti12 * a2 + ti13 * a3;
      z2(i) = ti21 * a1 + ti22 * a2 + ti23 * a3;
      z3(i) = ti31 * a1 + ti32 * a2 + ti33 * a3;
    }
  //C
  slvrad(cmn, n, _fjac, ldjac, mljac, mujac, _fmas, ldmas, mlmas, mumas, m1,
         m2, nm1, fac1, alphn, betan, _e1, _e2r, _e2i, lde1, z1, z2, z3, f1,
         f2, f3, cont, ip1, ip2, iphes, ier, ijob);
  nsol++;
  newt++;
  //C ---       NORM OF DY
  dyno = 0.e0;
  for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
    }
  for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      denom = scal(i);
      dyno += pow2((z1(i) / denom)) + pow2((z2(i) / denom)) + pow2((z3(i) / denom));
    }
  dyno = std::sqrt(dyno / n3);
  //C --------------------------------------------------------
  //C ---     BAD CONVERGENCE OR NUMBER OF ITERATIONS TO LARGE
  //C --------------------------------------------------------
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
      inrej = 0;
      //C --- 1
      if (theta < 0.99e0)
        {
          faccon = theta / (1.0e0 - theta);
          dyth = faccon * dyno * pow(theta, (nit - 1 - newt)) / fnewt;
          if (dyth >= 1.0e0)
            {
              inrej = 1;
            }
          //C ----------------  SLOW CONVERGENCE ---
        }
      else
        {
          inrej = 2;
          //C ----------------  DIVERGENCE ---
        }
      //C --- 1
    }
  else
    {
      //C ---           NEWT=1
      inrej = 0;
    }
//C ----------------------------------------
//C ------------------ THE STEP IS REPEATED
//C ----------------------------------------
//C ---- 2
statement_421:
  if (inrej > 0)
    {
      //C
      //C ----- 3
      if (!(bpc || first))
        {
          if (bpd)
            {
              //C ---          BP IS WRONG
              ibp = ibp - 1;
              bpd = false;
            }
          hp = h * 0.99e0;
          bpdtct(cmn, n, x, hp, y, arglag, rpar, ipar, ucont, grid,
                 nlags, first, last, xend, igrid, bpv, ibp, ilbp, bpp, bpd,
                 kmax, phi, past, ipast, nrds);
          //C
          bpc = true;
          //C ------ 4
          if (bpd)
            {
              h = hp;
              last = true;
            }
          else if (inrej == 1)
            {
              qnewt = std::max(1.0e-4, std::min(20.0e0, dyth));
              hhfac = .8e0 * pow(qnewt, (-1.0e0 / (4.0e0 + nit - 1 - newt)));
              h = hhfac * h;
              last = false;
              //C
            }
          else if (inrej == 2)
            {
              h = h * 0.55e0;
              hhfac = 0.55e0;
              last = false;
              //C
            }
          //C ------ 4
        }
      else
        {
          //C ----- 3
          if (bpd)
            {
              //C              BP WRONG
              ibp = ibp - 1;
              bpd = false;
              last = false;
            }
          //C -------------------------------------------
          if (!caljacl || iswjl == 1)
            {
              //C ---          THERE ARE NOT SMALL DELAYS
              if (reject && caljac)
                {
                  h = h * 0.12e0;
                  hhfac = 0.12e0;
                }
              else if (inrej == 1)
                {
                  qnewt = std::max(1.0e-4, std::min(20.0e0, dyth));
                  hhfac = .8e0 * pow(qnewt, (-1.0e0 / (4.0e0 + nit - 1 - newt)));
                  h = hhfac * h;
                  last = false;
                }
              else if (inrej == 2)
                {
                  h = h * 0.55e0;
                  hhfac = 0.55e0;
                  last = false;
                }
            }
          else
            {
              //C ---          CALJACL IS TRUE: FULL ITEARATION IS DONE
              //C ---          THE STEPSIZE DOES NOT CHANGET
              jlflag = 1;
            }
        }
      //C ----- 3
      reject = true;
      if (caljac)
        {
          goto statement_20;
        }
      goto statement_10;
    }
  //C ---- 2
  //C --------------------------------------------------------
  dynold = std::max(dyno, uround);
  for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      f1i = f1(i) + z1(i);
      f2i = f2(i) + z2(i);
      f3i = f3(i) + z3(i);
      f1(i) = f1i;
      f2(i) = f2i;
      f3(i) = f3i;
      z1(i) = t11 * f1i + t12 * f2i + t13 * f3i;
      z2(i) = t21 * f1i + t22 * f2i + t23 * f3i;
      z3i = t31 * f1i + f2i;
      z3(i) = z3i;
      //C ---          APPROX DELLA SOLUZIONE
      zl(i + n2) = y(i) + z3i;
    }
  //C -- -- -- -- -- -- -- -- -- -- -- -- -- --
  if (newt == 1 || faccon * dyno > fnewt)
    {
      //C ---        NEWTON PROCEDE
      goto statement_40;
    }
  //C
  //C ----------------------------------------------------------------
  //C ---       ITERATIVE CORRECTION OF THE BREAKING POINT
  //C ----------------------------------------------------------------
  if (bpd)
    {
      hnewt = h;
      niter++;
      if (niter > nit)
        {
          //C              BP WRONG
          ibp = ibp - 1;
          bpd = false;
          last = false;
          h = h * 0.55e0;
          hhfac = 0.55e0;
          reject = true;
          niter = 0;
          if (caljac)
            {
              goto statement_20;
            }
          goto statement_10;
        }
      //C
      bpacc(cmn, n, x, h, y, arglag, rpar, ipar, z1, z2, z3, first,
            bpv, ibp, ilbp, bpp, kmax, phi, past, ipast, nrds);
      if (dabs(h - hnewt) / hnewt >= std::max(btol, rtolm * 1.e-2))
        {
          goto statement_20;
          //C             REF POINT
        }
      else
        {
          h = hnewt;
          niter = 0;
        }
    }
  //C ----------------------------------------------------------------
  //C
  //C *** *** *** *** *** *** *** *** *** *** ***
  //C END LOOP
  //C *** *** *** *** *** *** *** *** *** *** ***
  goto statement_55;
//C *** *** *** *** ***
//C
//C --- FULL NEWTON ITERATION
statement_23:
  nfull++;
  //C ---
  //C
  //C ----------------------------------------------------
  //C --- ALTERNATIVE FULL NEWTON JACOB. INTEGRATION STEP
  //C ----------------------------------------------------
  //C
  for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      for (size_t j = 1; j <= n; ++j) // FEM_DO_SAFE(j, 1, n)
        {
          fjacl(i + n, j) = 0.e0;
          fjacl(i + 2 * n, j) = 0.e0;
          fjacl(i + 2 * n, j + n) = 0.e0;
          fjacl(i, j + n) = 0.e0;
          fjacl(i, j + 2 * n) = 0.e0;
          fjacl(i + n, j + 2 * n) = 0.e0;
          fij = fjacs(i, j);
          fjacl(i, j) = fij;
          fjacl(i + n, j + n) = fij;
          fjacl(i + 2 * n, j + 2 * n) = fij;
        }
    }
  //C
  quadr = first;
  if (!quadr)
    {
      dl1 = c1 * (c1 - c2) * (c1 - 1.e0);
      dl2 = c2 * (c2 - c1) * (c2 - 1.e0);
      dl3 = (1.e0 - c1) * (1.e0 - c2);
    }
  else
    {
      dl1 = (c1 - c2) * (c1 - 1.e0);
      dl2 = (c2 - c1) * (c2 - 1.e0);
      dl3 = (1.e0 - c1) * (1.e0 - c2);
    }
  for (size_t il = 1; il <= nlags; ++il) // FEM_DO_SAFE(il, 1, nlags)
    {
      for (size_t i = 1; i <= 3; ++i) // FEM_DO_SAFE(i, 1, 3)
        {
          xl = xlag(i, il);
          if (xl > x)
            {
              //CCC
              //CCC            DERIVATIVES OF THE COLLOCATION POLYNOMIAL WRT STAGES
              //CCC            d u/d Y_k = L_k(xlag_i)
              //CCC
              if (!quadr)
                {
                  dcoli1 = ((xl - x) / h) * ((xl - x2) / h) * ((xl - x3) / h) / dl1;
                  dcoli2 = ((xl - x) / h) * ((xl - x1) / h) * ((xl - x3) / h) / dl2;
                  dcoli3 = ((xl - x) / h) * ((xl - x1) / h) * ((xl - x2) / h) / dl3;
                }
              else
                {
                  dcoli1 = ((xl - x2) / h) * ((xl - x3) / h) / dl1;
                  dcoli2 = ((xl - x1) / h) * ((xl - x3) / h) / dl2;
                  dcoli3 = ((xl - x1) / h) * ((xl - x2) / h) / dl3;
                }
              //C
              //C -----------> JACOBIAN IS UPDATED
              nl = ils(2 * il - 1);
              ile = ils(2 * il);
              //C
              //C -----------> FULL JACOBIAN MATRIX FJACL
              for (size_t k = 1; k <= nl; ++k) // FEM_DO_SAFE(k, 1, nl)
                {
                  kk = ils(ile - k + 1);
                  ik = ive(kk);
                  jk = ivc(kk);
                  fjlk = fjaclag(kk);
                  iki = ik + (i - 1) * n;
                  //C
                  fjacl(iki, jk) += fjlk * dcoli1;
                  fjacl(iki, jk + n) += fjlk * dcoli2;
                  fjacl(iki, jk + 2 * n) += fjlk * dcoli3;
                }
            }
        }
      //CCC
      //CCC --> NLAGS
    }
  //CCC <--
  //C
  ai11h = -ai11 / h;
  ai12h = -ai12 / h;
  ai13h = -ai13 / h;
  ai21h = -ai21 / h;
  ai22h = -ai22 / h;
  ai23h = -ai23 / h;
  ai31h = -ai31 / h;
  ai32h = -ai32 / h;
  ai33h = -ai33 / h;
  //C
  //C --- FJACL
  if (implct)
    {
      for (size_t i1 = 1; i1 <= n; ++i1) // FEM_DO_SAFE(i1, 1, n)
        {
          for (size_t j1 = 1; j1 <= n; ++j1) // FEM_DO_SAFE(j1, 1, n)
            {
              fjacl(i1, j1) += ai11h * fmas(i1, j1);
              fjacl(i1, j1 + n) += ai12h * fmas(i1, j1);
              fjacl(i1, j1 + 2 * n) += ai13h * fmas(i1, j1);
              //C
              fjacl(i1 + n, j1) += ai21h * fmas(i1, j1);
              fjacl(i1 + n, j1 + n) += ai22h * fmas(i1, j1);
              fjacl(i1 + n, j1 + 2 * n) += ai23h * fmas(i1, j1);
              //C
              fjacl(i1 + 2 * n, j1) += ai31h * fmas(i1, j1);
              fjacl(i1 + 2 * n, j1 + n) += ai32h * fmas(i1, j1);
              fjacl(i1 + 2 * n, j1 + 2 * n) += ai33h * fmas(i1, j1);
            }
        }
    }
  else
    {
      //C ---  EXPLICIT CASE
      for (size_t i1 = 1; i1 <= n; ++i1) // FEM_DO_SAFE(i1, 1, n)
        {
          fjacl(i1, i1) += ai11h;
          fjacl(i1, i1 + n) += ai12h;
          fjacl(i1, i1 + 2 * n) += ai13h;
          //C
          fjacl(i1 + n, i1) += ai21h;
          fjacl(i1 + n, i1 + n) += ai22h;
          fjacl(i1 + n, i1 + 2 * n) += ai23h;
          //C
          fjacl(i1 + 2 * n, i1) += ai31h;
          fjacl(i1 + 2 * n, i1 + n) += ai32h;
          fjacl(i1 + 2 * n, i1 + 2 * n) += ai33h;
        }
    }
  //C ----- FACTORIZATION OF THE FULL JACOBIAN
  dec(3 * n, 3 * ldjac, _fjacl, ipj, ier);
  if (ier != 0)
    {
      goto statement_78;
    }
  //CCC --->
  ndec++;
  //C ---
  //C --- R: EVERY STEP STARTS WITH A SIMPLE ITERATION
  nstep++;
  if (nstep > nmax)
    {
      goto statement_178;
    }
  if (0.1e0 * h <= dabs(x) * uround)
    {
      goto statement_177;
    }
  //C ---
  xph = x + h;
  //C
  //C *** *** *** *** *** *** ***
  //C  LOOP FOR NEWTON ITERATION
  //C *** *** *** *** *** *** ***
  //C              -----------
  newt = 0;
  //C -----------------------
  flags = false;
  flagn = false;
  //C -----------------------
  faccon = pow(std::max(faccon, uround), 0.8e0);
  theta = dabs(thet);
//CCC --- --- --- --- --- --- --- --- --- --- --- --- ---
//CCC         REFERENCE POINT FOR FULL ITERATION
//CCC --- --- --- --- --- --- --- --- --- --- --- --- ---
statement_43:
  //C --- --- --- --- --- --- --- --- --- --- --- ---
  if (flags)
    {
      flagn = true;
      //C *****************
      //CCC ---      DYNAMIC UPDATE OF THE CURRENT INTETPOLANT (in PAST)
      for (size_t j = 1; j <= nrds; ++j) // FEM_DO_SAFE(j, 1, nrds)
        {
          i = ipast(j);
          past(j + iact) = y(i) + z3(i);
          z2i = z2(i);
          z1i = z1(i);
          past(j + 1 * nrds + iact) = (z2i - z3(i)) / c2m1;
          ak = (z1i - z2i) / c1mc2;
          acont3 = z1i / c1;
          acont3 = (ak - acont3) / c2;
          past(j + 2 * nrds + iact) = (ak - past(j + 1 * nrds + iact)) / c1m1;
          past(j + 3 * nrds + iact) = past(j + 2 * nrds + iact) - acont3;
        }
      //CCC          UPDATE
      past(iact) = x;
      //CCC          LEFT ENDPOINT OF CURRENT INTERVAL
      past(iact + idif - 1) = h;
      //CCC          USED STEPSIZE
    }
  //C --- --- --- --- --- --- --- --- --- --- --- ---
  if (newt >= nit)
    {
      inrej = 2;
      goto statement_431;
      //C ---------> UNEXPECTED STEP-REJECTION
    }
  //C ---     COMPUTE THE RIGHT-HAND SIDE
  for (size_t i1 = 1; i1 <= n; ++i1) // FEM_DO_SAFE(i1, 1, n)
    {
      cont(i1) = y(i1) + z1(i1);
    }
  fcn(n, x + c1 * h, cont, f1, arglag, phi, rpar, ipar, past, ipast, nrds);
  for (size_t i1 = 1; i1 <= n; ++i1) // FEM_DO_SAFE(i1, 1, n)
    {
      cont(i1) = y(i1) + z2(i1);
    }
  fcn(n, x + c2 * h, cont, f2, arglag, phi, rpar, ipar, past, ipast, nrds);
  for (size_t i1 = 1; i1 <= n; ++i1) // FEM_DO_SAFE(i1, 1, n)
    {
      cont(i1) = y(i1) + z3(i1);
    }
  fcn(n, xph, cont, f3, arglag, phi, rpar, ipar, past, ipast, nrds);
  nfcn += 3;
  //C
  //C --->    RHS COMPUTATION
  if (implct)
    {
      zl = 0.e0;
      for (size_t i1 = 1; i1 <= n; ++i1) // FEM_DO_SAFE(i1, 1, n)
        {
          for (size_t j1 = 1; j1 <= n; ++j1) // FEM_DO_SAFE(j1, 1, n)
            {
              zl(i1) += ai11h * fmas(i1, j1) * z1(j1);
              zl(i1) += ai12h * fmas(i1, j1) * z2(j1);
              zl(i1) += ai13h * fmas(i1, j1) * z3(j1);
              //C
              zl(i1 + n) += ai21h * fmas(i1, j1) * z1(j1);
              zl(i1 + n) += ai22h * fmas(i1, j1) * z2(j1);
              zl(i1 + n) += ai23h * fmas(i1, j1) * z3(j1);
              //C
              zl(i1 + 2 * n) += ai31h * fmas(i1, j1) * z1(j1);
              zl(i1 + 2 * n) += ai32h * fmas(i1, j1) * z2(j1);
              zl(i1 + 2 * n) += ai33h * fmas(i1, j1) * z3(j1);
            }
        }
    }
  else
    {
      for (size_t i1 = 1; i1 <= n; ++i1) // FEM_DO_SAFE(i1, 1, n)
        {
          zl(i1) = ai11h * z1(i1) + ai12h * z2(i1) + ai13h * z3(i1);
          zl(n + i1) = ai21h * z1(i1) + ai22h * z2(i1) + ai23h * z3(i1);
          zl(2 * n + i1) = ai31h * z1(i1) + ai32h * z2(i1) + ai33h * z3(i1);
        }
    }
  //C
  for (size_t i1 = 1; i1 <= n; ++i1) // FEM_DO_SAFE(i1, 1, n)
    {
      zl(i1) = -zl(i1) - f1(i1);
      zl(n + i1) = -zl(n + i1) - f2(i1);
      zl(2 * n + i1) = -zl(2 * n + i1) - f3(i1);
    }
  //C --------> SOLVE THE LINEAR SYSTEMS
  sol(3 * n, 3 * ldjac, _fjacl, zl, ipj);
  nsol++;
  newt++;
  dyno = 0.e0;
  for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      denom = scal(i);
      dyno += pow2((zl(i) / denom)) + pow2((zl(i + n) / denom)) + pow2((zl(i + 2 * n) / denom));
    }
  dyno = std::sqrt(dyno / n3);
  //C --------------------------------------------------------
  //C ---     BAD CONVERGENCE OR NUMBER OF ITERATIONS TO LARGE
  //C --------------------------------------------------------
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
      inrej = 0;
      //C --- 1
      if (theta < 0.99e0)
        {
          faccon = theta / (1.0e0 - theta);
          dyth = faccon * dyno * pow(theta, (nit - 1 - newt)) / fnewt;
          if (dyth >= 1.0e0)
            {
              inrej = 1;
            }
          //C ----------------  CONVERGENZA LENTA ---
        }
      else
        {
          inrej = 2;
          //C ----------------  DIVERGENZA ---
        }
      //C --- 1
    }
  else
    {
      inrej = 0;
    }
//C ----------------------------------------
//C ------------------ THE STEP IS REPEATED
//C ----------------------------------------
statement_431:
  if (inrej > 0)
    {
      reject = true;
      last = false;
      jlflag = 0;
      //C --------------------------------------------
      //C ---        TURN TO A SIMPLE ITERATION
      if (inrej == 1)
        {
          qnewt = std::max(1.0e-4, std::min(20.0e0, dyth));
          hhfac = .8e0 * pow(qnewt, (-1.0e0 / (4.0e0 + nit - 1 - newt)));
          h = hhfac * h;
        }
      else if (inrej == 2)
        {
          h = h * 0.55e0;
          hhfac = 0.55e0;
        }
      if (caljac)
        {
          goto statement_20;
        }
      goto statement_10;
    }
  //C --------------------------------------------------------
  dynold = std::max(dyno, uround);
  //C --        UPDATE OF Z VALUES
  for (size_t i1 = 1; i1 <= n; ++i1) // FEM_DO_SAFE(i1, 1, n)
    {
      z1(i1) += zl(i1);
      z2(i1) += zl(n + i1);
      z3(i1) += zl(2 * n + i1);
    }
  //C -- -- -- -- -- -- -- -- -- -- -- -- -- --
  if (faccon * dyno > fnewt)
    {
      goto statement_43;
    }
//C - - - - - END FULL NEWTON ITERATION
//C -----------------------------------------------------------------
//C          RK EQUATIONS SUCCESFULLY SOLVED
//C -----------------------------------------------------------------
//C *** *** *** *** *** *** *** *** *** *** ***
//C END LOOP
//C *** *** *** *** *** *** *** *** *** *** ***
//C -----------------------------------------------------------------
statement_55:
  //C ********************
  //C --- ERROR ESTIMATION
  //C ********************
  //C
  //C    ERROR ESTIMATES
  estrad(cmn, n, _fjac, ldjac, mljac, mujac, _fmas, ldmas, mlmas, mumas, h,
         u1, dd1, dd2, dd3, cl1, cl3, cq1, cq2, cq3, cerlq, fcn, nfcn, y0,
         y, ijob, x, m1, m2, nm1, _e1, lde1, alpha, z1, z2, z3, cont, f1,
         f2, f3, ip1, iphes, scal, serr, cerr, first, reject, fac1,
         arglag, phi, rpar, ipar, iout, past, ipast, nrds, jlflag, ieflag);
  fac = std::min(safe, cfac / (newt + 2 * nit));
  //C
  if (first)
    {
      //C ------------------------------------------------------------
      //C ---  AFTER A GRID OR BREAKING POINT
      //C ---------------------------------------------
      err = serr;
      //C ---  WE REQUIRE .2<=HNEW/H<=8.
      quot = std::max(facr, std::min(facl, pow(err, 0.25e0) / fac));
      hnew = h / quot;
    }
  else
    {
      //C   ----------------------------------------------------------
      if (ieflag == -1)
        {
          cerr2 = h * cerr;
          //C ---
          err = cerr2;
        }
      else if (ieflag == 1)
        {
          //C -----
          cerr2 = h * cerr;
          err = cers * serr + cerc * cerr2;
        }
      else if (ieflag == 2)
        {
          //C ----- STANDARD DISCRETE ERROR
          err = serr;
        }
      else if (ieflag == 3)
        {
          //C ----- NOT AVAILABLE AT THE MOMENT
          cerr2 = h * cerr;
          err = cers * serr + cerc * cerr2;
        }
      //C ------------------------------------
      //C ---  COMPUTATION OF HNEW
      //C ---  AS PREVIOUSLY COMPUTED:
      //C ------------------------------------
      //C ---  WE REQUIRE .2<=HNEW/H<=8.
      //C ---  LINEAR COMBINATION OF BOTH ERROR COMPONENTS
      quot = std::max(facr, std::min(facl, pow(err, .25e0) / fac));
      //C
      hnew = h / quot;
    }
  //C *** *** *** *** *** *** ***
  //C  DOES THE ERROR INCREASE MUCH?
  //C *** *** *** *** *** *** ***
  repeat = false;
  if (err >= 1.e0 || ((err / erracc >= tckbp) && (!bpd)))
    {
      //C ---   KIND OF STEPSIZE
      if (bpd)
        {
          //C ---     BP IS WRONG! REPEAT
          ibp = ibp - 1;
          bpd = false;
          repeat = true;
          if (err < 1.e0)
            {
              hnew = h * 0.55e0;
            }
        }
      else
        {
          //C ---     LOOK FOR A BP
          hp = h * 0.99e0;
          bpdtct(cmn, n, x, hp, y, arglag, rpar, ipar, ucont, grid,
                 nlags, first, last, xend, igrid, bpv, ibp, ilbp, bpp, bpd,
                 kmax, phi, past, ipast, nrds);
          if (bpd)
            {
              repeat = true;
            }
        }
    }
  bpc = false;
  //C *** *** *** *** *** *** ***
  //C  IS THE ERROR SMALL ENOUGH ?
  //C *** *** *** *** *** *** ***
  //C     IF (ERR.LT.1.D0) THEN
  if (!repeat && err < 1.e0)
    {
      //C --------------------
      //C --- STEP IS ACCEPTED
      //C --------------------
      flagn = false;
      caljacl = false;
      //C ---    UPDATE NUMBER OF ACCEPTED STEPS
      naccpt++;
      if (pred)
        {
          //C --------> PREDICTIVE CONTROLLER OF GUSTAFSSON
          if (naccpt > 1)
            {
              if (flagus)
                {
                  facgus = (hacc / h) * pow((pow2(err) / erracc), 0.25e0) / safe;
                  facgus = std::max(facr, std::min(facl, facgus));
                  quot = std::max(quot, facgus);
                  hnew = h / quot;
                }
              else
                {
                  flagus = true;
                }
            }
          hacc = h;
        }
      erracc = std::max(1.0e-2, err);
      //C        ERRACC=ERR
      xold = x;
      hold = h;
      x = xph;
      //C ---    AGGIORNAMENTO DELLA SOLUZIONE
      for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
        {
          z3i = z3(i);
          yi = y(i) + z3i;
          y(i) = yi;
          //C -------------------------------------------------------------------------
          //C --------- UPDATE THE STAGES AND SOLUTION
          //C -------------------------------------------------------------------------
          //C ---
          cont(i) = yi;
          z2i = z2(i);
          z1i = z1(i);
          //C -------------------------------------------------------------------
          //C ---         INVERSE DEVIDED DIFFERENCES
          //C -------------------------------------------------------------------
          a1 = (z2i - z3i) / c2m1;
          cont(i + n) = a1;
          ak = (z1i - z2i) / c1mc2;
          acont3 = z1i / c1;
          acont3 = (ak - acont3) / c2;
          a2 = (ak - cont(i + n)) / c1m1;
          cont(i + n2) = a2;
          if (!first)
            {
              cont(i + n3) = a2 - acont3;
            }
          else
            {
              //C ---         QUADRATIC APPROXIMATION
              cont(i + n3) = 0.e0;
              //C ---         INVECE DI:
              //C ---         CONT(I+N3)=CONT(I+N2)-ACONT3
            }
        }
      //C ----------------------------------------
      //C ---    SAVE LAST ACCEPTED STEP INFORMATION
      for (size_t i = 1; i <= lrc; ++i) // FEM_DO_SAFE(i, 1, lrc)
        {
          ucont(i) = cont(i);
        }
      ucont(lrc + 1) = x;
      ucont(lrc + 2) = h;
      //C ---    FOR POSSIBLE SEARCH OF BREAKING POINTS
      //C ------------------------------------------------------------------
      //C ---    STEP IS ACCEPTED> DENSE OUTPUT IS STORED IN PAST
      //C ---
      for (size_t j = 1; j <= nrds; ++j) // FEM_DO_SAFE(j, 1, nrds)
        {
          i = ipast(j);
          past(j + iact) = cont(i);
          past(j + 1 * nrds + iact) = cont(i + n);
          past(j + 2 * nrds + iact) = cont(i + n2);
          if (!first)
            {
              past(j + 3 * nrds + iact) = cont(i + n3);
            }
          else
            {
              //C ---       QUADRATIC APPROXIMATION
              past(j + 3 * nrds + iact) = 0.e0;
            }
        }
      //C ---------> AGGIORNAMENTO DI PAST <---------
      past(iact) = xold;
      //C ---
      iact += idif;
      //C ---    POINTER TO NEXT STEP
      past(iact - 1) = h;
      //C ---
      if (iact + idif - 1 > mxst * idif)
        {
          iact = 1;
        }
      //C ---    CONTROL ON THE MEMORY DIMENSION
      //C -----------------------------------------------------------------
      //C ---    COMPUTATION AT BP FOR NEXT STEP
      if (last)
        {
          //C ---     LAST HAS TO BE RE/DEFINED
          if (bpd)
            {
              igrid = igrid - 1;
            }
          //C ---
          //C EXPLICIT PROBLEM
          if (!implct || neutral)
            {
              he = std::max(h / 1.e4, 10.e0 * uround);
              //C --------------------
              left = true;
              //C --------------------
              //C ---
              //C ---       EULER STEP
              fcn(n, x, y, f2, arglag, phi, rpar, ipar, past, ipast, nrds);
              if (neutral)
                {
                  for (size_t i = 1; i <= n - ndimn; ++i) // FEM_DO_SAFE(i, 1, n - ndimn)
                    {
                      z2(i) = y(i) + he * f2(i);
                    }
                  for (size_t i = 1; i <= ndimn; ++i) // FEM_DO_SAFE(i, 1, ndimn)
                    {
                      z2(n - ndimn + i) = f2(ipast(nrds + i)) + he * f2(n - ndimn + i);
                    }
                }
              else
                {
                  for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
                    {
                      z2(i) = y(i) + he * f2(i);
                    }
                }
              //C --------------------
              left = false;
              //C --------------------
              fcn(n, x, y, f3, arglag, phi, rpar, ipar, past, ipast, nrds);
              if (neutral)
                {
                  for (size_t i = 1; i <= n - ndimn; ++i) // FEM_DO_SAFE(i, 1, n - ndimn)
                    {
                      z3(i) = y(i) + he * f3(i);
                    }
                  for (size_t i = 1; i <= ndimn; ++i) // FEM_DO_SAFE(i, 1, ndimn)
                    {
                      z3(n - ndimn + i) = f3(ipast(nrds + i)) + he * f3(n - ndimn + i);
                    }
                }
              else
                {
                  for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
                    {
                      z3(i) = y(i) + he * f3(i);
                    }
                }
              xl = arglag(ilbp, x + he, n, z2, rpar, ipar, phi, past, ipast, nrds);
              xlr = arglag(ilbp, x + he, n, z3, rpar, ipar, phi, past, ipast, nrds);
              if (xl >= bpp && xlr >= bpp)
                {
                  left = false;
                }
              else if (xl < bpp && xlr < bpp)
                {
                  left = true;
                }
              else
                {
                  if (iout == 1)
                    {
                      if (xl > bpp)
                        {
                          write("WARNING!: SOLUTION DOES NOT EXIST AT X = ", x);
                        }
                      else
                        {
                          write("WARNING!: SOLUTION IS NOT UNIQUE AT X = ", x);
                        }
                      goto statement_980;
                      //C             RETURN
                    }
                }
              //C ---       PROJECTION FOR DERIVATIVE COMPONENTS OF NEUTRAL EXPLICIT PROBLEMS
              project = true;
              if (neutral && project)
                {
                  if (left)
                    {
                      for (size_t j = 1; j <= ndimn; ++j) // FEM_DO_SAFE(j, 1, ndimn)
                        {
                          y(n - ndimn + j) = f2(ipast(nrds + j));
                        }
                    }
                  else
                    {
                      for (size_t j = 1; j <= ndimn; ++j) // FEM_DO_SAFE(j, 1, ndimn)
                        {
                          y(n - ndimn + j) = f3(ipast(nrds + j));
                        }
                    }
                }
              //C GENERAL IMPLICIT
            }
          else
            {
              left = true;
            }
          //C ---
          bpd = false;
        }
      //C -----------------------------------------------------------------
      if (itol == 0)
        {
          for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
            {
              scal(i) = atol(1) + rtol(1) * dabs(y(i));
            }
        }
      else
        {
          for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
            {
              scal(i) = atol(i) + rtol(i) * dabs(y(i));
            }
        }
      if (iout != 0)
        {
          //C ---
          nrsol = naccpt + 1;
          xsol = x;
          xosol = xold;
          nsolu = n;
          hsol = hold;
          //C ---
          solout(nrsol, xosol, xsol, hsol, y, cont, lrc, nsolu, rpar, ipar, irtrn);
          if (irtrn < 0)
            {
              goto statement_179;
            }
        }
      caljac = false;
      //C -----------------------------
      //C ---    FIRST IS RESTORED
      first = false;
      if (last)
        {
          first = true;
        }
      //C ---    COMPUTATION OF Y0
      posneg = 1.0e0;
      if (left)
        {
          posneg = -posneg;
        }
      xeps = posneg * (dabs(x) + 1.0e0) * 100 * uround;
      fcn(n, x + xeps, y, y0, arglag, phi, rpar, ipar, past, ipast, nrds);
      if (first)
        {
          for (size_t i = 1; i <= ndimn; ++i) // FEM_DO_SAFE(i, 1, ndimn)
            {
              y0(n - ndimn + i) = 0.0e0;
            }
        }
      nfcn++;
      first = false;
      //C -----------------------------
      //C ------ FINAL POINT
      if (last)
        {
        statement_45:
          if (igrid >= ngrid)
            {
              h = hopt;
              idid = 1;
              //C ---          END OF COMPUTATION
              goto statement_980;
            }
          else
            {
              igrid++;
              last = false;
              //C              LEFT=.FALSE.
              first = true;
              xend = grid(igrid);
              if (dabs(xend - x) <= (h * 1.e-2))
                {
                  igrid++;
                  goto statement_45;
                }
              flagus = false;
              if (work7 == 0.e0)
                {
                  hmaxn = xend - x;
                  hmax = hmaxn;
                }
              hnew = std::min(hnew, h);
            }
        }
      hnew = std::min(hnew, hmaxn);
      hopt = std::min(h, hnew);
      if (reject)
        {
          hnew = std::min(hnew, h);
        }
      reject = false;
      if ((x + hnew / quot1 - xend) >= 0.e0)
        {
          h = xend - x;
          if (h < 0.e0)
            {
              write("ERROR!: NEGATIVE STEPSIZE! AT X = ", x , " > XEND = ", xend);
              fatalError();
            }
          last = true;
        }
      else
        {
          //C -----------------------------------------------------
          //C --------  IN ORDER TO AVOID VERY SMALL END-STEPSIZES:
          if ((x + 1.8e0 * hnew - xend) > 0.e0)
            {
              h = (xend - x) * 0.55e0;
            }
          else
            {
              qt = hnew / h;
              hhfac = h;
              imant = 0;
              //C ---         STEP IS MAINTAINED
              if (theta <= thet && qt >= quot1 && qt <= quot2)
                {
                  if ((jlflag == 0) && (!first))
                    {
                      imant = 1;
                    }
                }
              else
                {
                  h = hnew;
                }
            }
        }
      hhfac = h;
      //C -------------------------------------------
      //C ---    SIMPLE ITERATION FIRST
      jlflag = 0;
      //C ---
      if ((!first) && (theta <= thet))
        {
          goto statement_20;
        }
      goto statement_10;
      //C --------------------
      //C --- STEP IS ACCEPTED
      //C --------------------
    }
  else
    {
      //C --------------------
      //C --- STEP IS REJECTED
      //C --------------------
      if (bpd)
        {
          if (!first)
            {
              hnew = hp;
              last = true;
            }
        }
      else
        {
          last = false;
        }
      flagn = false;
      //C -------------------------------
      if (irtrn < 0)
        {
          goto statement_179;
        }
      reject = true;
      //C ---
      if (first)
        {
          h = h * 0.12e0;
          hhfac = 0.12e0;
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
      //C --->
      jlflag = 0;
      if (caljac)
        {
          goto statement_20;
        }
      goto statement_10;
      //C --------------------
      //C --- STEP IS REJECTED
      //C --------------------
    }
//C ----------------------------------
//C --- END OF ERROR CONTROL PROCEDURE
//C ----------------------------------
//C --- UNEXPECTED STEP-REJECTION
statement_78:
  reject = true;
  flagn = false;
  //C ---
  last = false;
  //C ---
  if (ier != 0)
    {
      nsing++;
      if (nsing >= 5)
        {
          goto statement_176;
        }
    }
  //C ---
  h = h * 0.55e0;
  hhfac = 0.55e0;
  //C ---
  if (caljac)
    {
      goto statement_20;
    }
  if (irtrn < 0)
    {
      goto statement_175;
    }
  goto statement_10;
//C --- FAIL EXIT
statement_175:
  idid = -5;
  goto statement_980;
statement_176:
  write("exit of radar5 at x = ", x);
  write("MATRIX IS REPEATEDLY SINGULAR, IER = ", ier);
  idid = -4;
  goto statement_980;
statement_177:
  write("exit of radar5 at x = ", x);
  write("STEP SIZE TOO SMALL, H = ", h);
  idid = -3;
  goto statement_980;
statement_178:
  write("exit of radar5 at x = ", x);
  write("MORE THAN NMAX = R1 STEPS ARE NEEDED", nmax);
  idid = -2;
  goto statement_980;
//C --- EXIT CAUSED BY SOLOUT
statement_179:
  write("exit of radar5 at x = ", x);
  idid = 2;
//C --- RETURN LABEL
statement_980:
  write("COMPUTED ", ibp, " BREAKING POINTS :");
  for (size_t i = 1; i <= ibp; ++i) // FEM_DO_SAFE(i, 1, ibp)
    write("  ", bpv(i));
  write("--------------");

  //C --- DEALLOCATION OF THE MEMORY
  return;
}

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
void CRadar5::operator()(const integer & n,
                        FCN & fcn,
                        PHI & phi,
                        ARGLAG arglag,
                        doublereal & x,
                        CVectorCore< doublereal > & y,
                        doublereal & xend,
                        doublereal & h,
                        CVectorCore< doublereal > & rtol,
                        CVectorCore< doublereal > & atol,
                        const integer & itol,
                        JAC & jac,
                        const integer & ijac,
                        integer & mljac,
                        integer & mujac,
                        JACLAG & jaclag,
                        const integer & nlags,
                        const integer & njacl,
                        MAS & mas,
                        const integer & imas,
                        const integer & mlmas,
                        const integer & mumas,
                        SOLOUT & solout,
                        const integer & iout,
                        CVectorCore< doublereal > & work,
                        const integer & lwork,
                        CVectorCore< integer > & iwork,
                        const integer & liwork,
                        const doublereal & rpar,
                        const integer & ipar,
                        integer & idid,
                        CVectorCore< doublereal > & grid,
                        const integer & lgrid,
                        CVectorCore< integer > & ipast,
                        const integer & nrdens)
{
  doublereal & uround = mCommon.uround;
  doublereal & hmax = mCommon.hmax;
  integer & idif = mCommon.idif;
  integer & mxst = mCommon.mxst;
  //
  integer nn = 0;
  integer nfcn = 0;
  integer njac = 0;
  integer nstep = 0;
  integer naccpt = 0;
  integer nrejct = 0;
  integer ndec = 0;
  integer nsol = 0;
  logical arret = 0;
  integer ieflag = 0;
  integer ngrid = 0;
  integer ndimn = 0;
  integer lipast = 0;
  integer nrds = 0;
  integer i = 0;
  integer lrpast = 0;
  integer iswjl = 0;
  doublereal expm = 0.0;
  doublereal quot = 0.0;
  integer nmax = 0;
  integer nit = 0;
  logical startn = 0;
  integer nind1 = 0;
  integer nind2 = 0;
  integer nind3 = 0;
  logical pred = 0;
  integer m1 = 0;
  integer m2 = 0;
  integer nm1 = 0;
  doublereal safe = 0.0;
  doublereal thet = 0.0;
  doublereal tolst = 0.0;
  doublereal fnewt = 0.0;
  doublereal quot1 = 0.0;
  doublereal quot2 = 0.0;
  doublereal xuro = 0.0;
  integer igrid = 0;
  doublereal facl = 0.0;
  doublereal facr = 0.0;
  doublereal alpha = 0.0;
  doublereal tckbp = 0.0;
  logical implct = 0;
  logical neutral = 0;
  logical jband = 0;
  integer ldjac = 0;
  integer lde1 = 0;
  integer ldmas = 0;
  integer ijob = 0;
  integer ldmas2 = 0;
  integer nfull = 0;
  //C ----------------------------------------------------------
  //C     INPUT PARAMETERS
  //C --------------------
  //C     N           DIMENSION OF THE SYSTEM
  //C
  //C     FCN         NAME (EXTERNAL) OF SUBROUTINE COMPUTING THE RIGHT-
  //C                 HAND-SIDE OF THE DELAY EQUATION, E.G.,
  //C                    SUBROUTINE FCN(N,X,Y,F,RPAR,IPAR,...)
  //C                    DOUBLE PRECISION X,Y(N),F(N)
  //C                    EXTERNAL PHI
  //C                    F(1)=G1(X,Y(*),YLAGR5(*,X-TAU(X,Y(*))),PHI,...))
  //C                    F(2)=G2(X,Y(*),YLAGR5(*,X-TAU(X,Y(*))),PHI,...))
  //C                    ETC.
  //C                    (*) MEANS ALL POSSIBLE COMPONENTS
  //C                 FOR AN EXPLICATION OF YLAGR5 SEE BELOW.
  //C                 DO NOT USE YLAGR5(I,X-0.D0,PHI,RPAR,IPAR,...) !
  //C                 Note:
  //C                 THE INITIAL FUNCTION HAS TO BE SUPPLIED BY:
  //C                    FUNCTION PHI(I,X,RPAR,IPAR)
  //C                    DOUBLE PRECISION PHI,X
  //C                 WHERE I IS THE COMPONENT AND X THE ARGUMENT
  //C                 RPAR, IPAR (SEE BELOW)
  //C
  //C     PHI         NAME (EXTERNAL) OF FUNCTION COMPUTING THE INITIAL
  //C                 FUNCTIONS FOR COMONENTS I (WITH RETARDED ARGUMENT),
  //C                    FUNCTION PHI(I,X,RPAR,IPAR)
  //C                    DOUBLE PRECISION PHI,X
  //C
  //C     ARGLAG      NAME (EXTERNAL) OF FUNCTION COMPUTING THE IL-TH LAG TERM,
  //C                    FUNCTION ARGLAG(IL,X,N,Y,RPAR,IPAR,PHI,...)
  //C                    DOUBLE PRECISION PHI,X,Y(N)
  //C     X           INITIAL X-VALUE
  //C
  //C     Y(N)        INITIAL VALUES FOR Y (MAY BE DIFFERENT FROM PHI (I,X),
  //C                 IN THIS CASE IT IS HIGHLY RECOMMENDED TO SET IWORK(13)
  //C                 AND GRID(1),..., (SEE BELOW)
  //C
  //C     XEND        FINAL X-VALUE (XEND-X HAS TO BE POSITIVE)
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
  //C                     Y(I) OVER RTOL*ABS(Y(I))+ATOL
  //C                   ITOL=1: BOTH RTOL AND ATOL ARE VECTORS.
  //C                     THE CODE KEEPS THE LOCAL ERROR OF Y(I) OVER
  //C                     RTOL(I)*ABS(Y(I))+ATOL(I).
  //C
  //C     JAC         NAME (EXTERNAL) OF THE SUBROUTINE WHICH COMPUTES
  //C                 THE PARTIAL DERIVATIVES OF F(X,Y) WITH RESPECT TO Y
  //C                 (THIS ROUTINE IS ONLY CALLED IF IJAC=1;
  //C                 THE USER HAS TO SUPPLY A DUMMY SUBROUTINE
  //C                 IN THE CASE IJAC=0).
  //C                 FOR IJAC=1, THIS SUBROUTINE MUST HAVE THE FORM
  //C                    SUBROUTINE JAC(N,X,Y,DFY,LDFY,RPAR,IPAR,...)
  //C                    DOUBLE PRECISION X,Y(N),DFY(LDFY,N)
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
  //C                       DIFFERENCES, SUBROUTINE "JAC" IS NEVER CALLED.
  //C                    IJAC=1: JACOBIAN IS SUPPLIED BY SUBROUTINE JAC.
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
  //C                 DOES NOT NEED TO BE DEFINED IF MLJAC=N.
  //C
  //C     JACLAG      NAME (EXTERNAL) OF THE SUBROUTINE WHICH COMPUTES
  //C                 THE PARTIAL DERIVATIVES OF F(X,Y,YLAG) WITH RESPECT TO
  //C                 YLAG(*) (YLAG DENOTE THE DELAYED VARIABLES)
  //C
  //C     NLAGS       DENOTES THE NUMBER OF DELAY ARGUMENTS.
  //C                 THIS PARAMETER IS OF INTEREST FOR THE COMPUTATION OF THE
  //C                 JACOBIAN.
  //C                 TO BE SET = 0 IF ONE DOES WANT TO COMPUTE THE TRADITIONAL
  //C                 JACOBIAN;
  //C                 TO BE SET = NUMBER OF DISTINCT DELAY ARGUMENTS
  //C                 IF ONE WANTS TO CORRECT THE STANDARD JACOBIAN (THROUGH
  //C                 THE SUBROUTINE JACLAG) WHEN ADVANCED ARGUMENTS ARE USED.
  //C
  //C     NJACL       NUMBER OF TERMS IN THE JACOBIAN W.R.T.
  //C                 RETARDED COMPONENTS (WHICH IS THOUGHT AS A SPARSE MATRIX).
  //C
  //C     ----   MAS,IMAS,MLMAS, AND MUMAS HAVE ANALOG MEANINGS      -----
  //C     ----   FOR THE "MASS MATRIX" (THE MATRIX "M" OF SECTION IV.8): -
  //C
  //C     MAS         NAME (EXTERNAL) OF SUBROUTINE COMPUTING THE MASS-
  //C                 MATRIX M.
  //C                 IF IMAS=0, THIS MATRIX IS ASSUMED TO BE THE IDENTITY
  //C                 MATRIX AND NEEDS NOT TO BE DEFINED;
  //C                 THE USER HAS TO SUPPLY A DUMMY SUBROUTINE IN THIS CASE.
  //C                 IF IMAS=1, THE SUBROUTINE MAS IS OF THE FORM
  //C                    SUBROUTINE MAS(N,AM,LMAS,RPAR,IPAR)
  //C                    DOUBLE PRECISION AM(LMAS,N)
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
  //C                 MLMAS IS SUPPOSED TO BE <= MLJAC.
  //C
  //C     MUMAS       UPPER BANDWITH OF MASS-MATRIX (>= NUMBER OF NON-
  //C                 ZERO DIAGONALS ABOVE THE MAIN DIAGONAL).
  //C                 DOES NOT NEED TO BE DEFINED IF MLMAS=N.
  //C                 MUMAS IS SUPPOSED TO BE <= MUJAC.
  //C
  //C     SOLOUT      NAME (EXTERNAL) OF SUBROUTINE PROVIDING THE
  //C                 NUMERICAL SOLUTION DURING INTEGRATION.
  //C                 IF IOUT=1, IT IS CALLED AFTER EVERY SUCCESSFUL STEP.
  //C                 THE USER HAS TO SUPPLY A DUMMY SUBROUTINE IF IOUT=0.
  //C                 IT MUST HAVE THE FORM
  //C                    SUBROUTINE SOLOUT (NR,XOLD,X,HSOL,Y,CONT,LRC,N,
  //C                                       RPAR,IPAR,IRTRN)
  //C                    DOUBLE PRECISION X,Y(N),CONT(LRC)
  //C                    ....
  //C                 SOLOUT FURNISHES THE SOLUTION "Y" AT THE NR-TH
  //C                    GRID-POINT "X" (THEREBY THE INITIAL VALUE IS
  //C                    THE FIRST GRID-POINT).
  //C                 "XOLD" IS THE PRECEEDING GRID-POINT.
  //C                 "IRTRN" SERVES TO INTERRUPT THE INTEGRATION. IF IRTRN
  //C                    IS SET <0, RADAR5 RETURNS TO THE CALLING PROGRAM.
  //C
  //C          -----  CONTINUOUS OUTPUT: -----
  //C                 DURING CALLS TO "SOLOUT" AS WELL AS TO "FCN", A
  //C                 CONTINUOUS SOLUTION IS AVAILABLE THROUGH HTHE FUNCTION
  //C                        >>>   YLAGR5(I,S,PHI,RPAR,IPAR,...)   <<<
  //C                 WHICH PROVIDES AN APPROXIMATION TO THE I-TH
  //C                 COMPONENT OF THE SOLUTION AT THE POINT S. THE VALUE S
  //C                 HAS TO LIE IN AN INTERVAL WHERE THE NUMERICAL SOLUTION
  //C                 IS ALREADY COMPUTED. IT DEPENDS ON THE SIZE OF LRPAST
  //C                 (SEE BELOW) HOW FAR BACK THE SOLUTION IS AVAILABLE.
  //C
  //C     IOUT        SWITCH FOR CALLING THE SUBROUTINE SOLOUT:
  //C                    IOUT=0: SUBROUTINE IS NEVER CALLED
  //C                    IOUT=1: SUBROUTINE IS AVAILABLE FOR OUTPUT.
  //C
  //C     WORK        ARRAY OF STATE VARIABLES OF REAL TYPE FOR EXECUTION.
  //C                 WORK(1), WORK(2),.., WORK(20) SERVE AS PARAMETERS
  //C                 FOR THE CODE. FOR STANDARD USE OF THE CODE
  //C                 WORK(1),..,WORK(20) MUST BE SET TO ZERO BEFORE
  //C
  //C     LWORK       DECLARED LENGTH OF ARRAY WORK
  //C
  //C     IWORK       INTEGER WORKING SPACE OF LENGTH "LIWORK".
  //C                 IWORK(1),IWORK(2),...,IWORK(20) SERVE AS PARAMETERS
  //C                 FOR THE CODE. FOR STANDARD USE, SET IWORK(1),..,
  //C                 IWORK(20) TO ZERO BEFORE CALLING.
  //C
  //C     LIWORK       DECLARED LENGTH OF ARRAY IWORK
  //C
  //C     RPAR, IPAR  REAL AND INTEGER PARAMETERS (OR PARAMETER ARRAYS) WHICH
  //C                 CAN BE USED FOR COMMUNICATION BETWEEN YOUR CALLING
  //C                 PROGRAM AND THE FCN, JAC, MAS, SOLOUT SUBROUTINES.
  //C
  //C     GRID        CONTAINS PRESCRIBED GRID POINTS, WHICH THE
  //C                 INTEGRATION METHOD HAS TO TAKE AS GRID-POINTS
  //C                 NORMALLY, IF GRID(1) > X, THEN ONE HAS
  //C                 X < GRID(1) < GRID(2) < ... < GRID(NGRID) <= XEND
  //C                 IN SOME CASES IF THERE ARE DISCONTINUITIES IN THE
  //C                 INITIAL FUNCTIONS THEY ARE ALSO SET IN THE GRID
  //C                 VECTOR; THEN X < GRID(J) < GRID(J+1) ... < XEND
  //C                 WHERE J ADDRESSES THE FIRST ASCISSA IN GRID > X
  //C
  //C     LGRID       DECLARED LENGTH OF GRID VECTOR,
  //C                 GRID(LGRID),
  //C                 WHICH MUST BE DECLARED IN THE CALLING PROGRAM.
  //C                 "LGRID" MUST BE AT LEAST
  //C                              NGRID + 1
  //C
  //C     IPAST       FOR   0 < NRDENS < N   THE COMPONENTS (FOR WHICH DENSE
  //C                 OUTPUT IS REQUIRED) HAVE TO BE SPECIFIED IN
  //C                 IPAST(1),...,IPAST(NRDENS),
  //C                 FOR  NRDENS=N  THIS IS DONE BY THE CODE.
  //C
  //C     NRDENS =    NUMBER OF COMPONENTS, FOR WHICH DENSE OUTPUT
  //C                 IS REQUIRED (EITHER BY "SOLOUT" OR BY "FCN");
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
  //C              DIFFICULTIES WITH CONVERGENCE (THIS IS SEEN IN THE CASE WHEN
  //C              NSTEP IS LARGER THAN NACCPT + NREJCT; SEE OUTPUT PARAM.).
  //C              DEFAULT IS IWORK(4)=0.
  //C
  //C       THE FOLLOWING 3 PARAMETERS ARE IMPORTANT FOR
  //C       DELAY DIFFERENTIAL-ALGEBRAIC SYSTEMS OF INDEX > 1.
  //C       THE FUNCTION-SUBROUTINE SHOULD BE WRITTEN SUCH THAT
  //C       THE INDEX 1,2,3 VARIABLES APPEAR IN THIS ORDER.
  //C       IN ESTIMATING THE ERROR THE INDEX 2 VARIABLES ARE
  //C       MULTIPLIED BY H, THE INDEX 3 VARIABLES BY H**2.
  //C
  //C    IWORK(5)  DIMENSION OF THE INDEX 1 VARIABLES (MUST BE > 0). FOR
  //C              DDE'S THIS EQUALS THE DIMENSION OF THE SYSTEM.
  //C              DEFAULT IWORK(5)=N.
  //C
  //C    IWORK(6)  DIMENSION OF THE INDEX 2 VARIABLES. DEFAULT IWORK(6)=0.
  //C
  //C    IWORK(7)  DIMENSION OF THE INDEX 3 VARIABLES. DEFAULT IWORK(7)=0.
  //C
  //C    IWORK(8)  SWITCH FOR STEP SIZE STRATEGY
  //C              IF IWORK(8).EQ.1  MODIFIED PREDICTIVE CONTROLLER
  //C              (GUSTAFSSON)
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
  //C       - MUJAC: MAXIMAL UPPER BANDWIDTH OF THESE MM+1 SUBMATRICES;
  //C                DOES NOT NEED TO BE DEFINED IF MLJAC=N-M1
  //C       - MAS: IF IMAS=0 THIS MATRIX IS ASSUMED TO BE THE IDENTITY AND
  //C              DOES NOT NEED TO BE DEFINED.
  //C              THE USER HAS TO SUPPLY A DUMMY SUBROUTINE IN THIS CASE.
  //C              IT IS ASSUMED THAT ONLY THE ELEMENTS OF RIGHT LOWER BLOCK OF
  //C              DIMENSION N-M1 DIFFER FROM THAT OF THE IDENTITY MATRIX.
  //C              IF (MLMAS.EQ.N-M1) THIS SUBMATRIX IS SUPPOSED TO BE FULL
  //C                 AM(I,J) = M(I+M1,J+M1)     FOR I=1,N-M1 AND J=1,N-M1.
  //C              ELSE, THE MASS MATRIX IS BANDED
  //C                 AM(I-J+MUMAS+1,J) = M(I+M1,J+M1)
  //C       - MLMAS: MLMAS=N-M1: IF THE NON-TRIVIAL PART OF M IS FULL
  //C                0<=MLMAS<N-M1: LOWER BANDWIDTH OF THE MASS MATRIX
  //C       - MUMAS: UPPER BANDWIDTH OF THE MASS MATRIX
  //C                DOES NOT NEED TO BE DEFINED IF MLMAS=N-M1
  //C
  //C    IWORK(9)  THE VALUE OF M1.  DEFAULT M1=0.
  //C
  //C    IWORK(10) THE VALUE OF M2.  DEFAULT M2=M1.
  //C
  //C    IWORK(11) SELECT THE TYPE OF ERROR CONTROL:
  //C              -1: FOR A PURE CONTROL OF THE DENSE OUTPUT
  //C                  (MAKES USE OF A QUADRATIC AND A LINEAR INTERPOLATING
  //C                   POLYNOMIALS);
  //C               1: FOR A MIXED CONTROL OF DENSE OUTPUT AND DISCRETE OUTPUT
  //C               2: FOR A PURE CONTROL OF THE DISCRETE OUTPUT
  //C                  (ERROR CONTROL PROVIDED BY THE SUBROUTINE ESTRAD).
  //C               3: FOR A SIMPLER MIXED CONTROL OF DENSE OUTPUT AND
  //C                  DISCRETE OUTPUT
  //C               DEFAULT VALUE IWORK(11)=2.
  //C
  //C    IWORK(12) = MXST = (ON INPUT)
  //C              DECLARED NUMBER OF STEPS STORED IN THE ``PAST VECTOR'',
  //C              PAST(LRPAST),
  //C              WHICH MUST BE DECLARED IN THE CALLING PROGRAM.
  //C              "MXST" MUST BE SUFFICIENTLY LARGE. IF THE DENSE
  //C              OUTPUT OF MXST BACK STEPS HAS TO BE STORED,
  //C              THE DIMENSION OF PAST MUST BE
  //C                       LRPAST=MXST*(4*NRDENS+2)
  //C              WHERE NRDENS=IWORK(15) (SEE BELOW).
  //C
  //C    IWORK(13) = NGRID = (ON INPUT)
  //C              NUMBER OF PRESCRIBED POINTS IN THE
  //C              INTEGRATION INTERVAL WHICH HAVE TO BE GRID-POINTS
  //C              IN THE INTEGRATION. USUALLY, AT THESE POINTS THE
  //C              SOLUTION OR ONE OF ITS DERIVATIVE HAS A DISCONTINUITY.
  //C              DEFINE THESE POINTS IN GRID(1),...,GRID(NGRID)
  //C              DEFAULT VALUE:  IWORK(13)=0
  //C
  //C    IWORK(14) = SELECTOR FOR FULL ITERATION (2) OR SIMPLIFIED
  //C              ITERATION (1) (TAKING INTO ACCOUNT POSSIBLE
  //C              ADVANCED ARGUMENTS BUT PRESERVING TENSOR STRUCTURE
  //C              OF THE JACOBIAN.
  //C              DEFAULT VALUE:  IWORK(14)=1
  //C
  //C    IWORK(16) = NDIMN = (ON INPUT)
  //C              OPTION VALID FOR NEUTRAL PROBLEMS
  //C              NUMBER OF DERIVATIVE COMPONENTS (Z) OF THE NEUTRAL PROBLEM
  //C              EXCLUDED TRUE SOLUTION COMPONENTS
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
  //C    WORK(10)  PARAMETER FOR CONTROLLING THE ERROR CONTROL OF DENSE
  //C              OUTPUT (0 <= WORK(10) <= 1). (0: STRONG CONTROL, 1: WEAKER)
  //C              SUGGESTED VALUES:
  //C              FOR PROBLEMS WITH `ALMOST DISCONTINUOUS' SOLUTIONS
  //C              (LIKE SHOCKS):  WORK(10)=0.D0
  //C              FOR PROBLEMS WITH FAIRLY SMOOTH SOLUTION:  WORK(10)=1.D0
  //C              FOR INTERMEDIATE PROBLEMS:  WORK(10)=1.D-M (M=1,2,3,..,)
  //C              DEFAULT VALUE: WORK(10)=0.D0
  //C    WORK(11)  PARAMETER FOR CONTROLLING THE SEARCH OF BREAKING POINTS:
  //C              IF THE ERROR INCREASES OF A FACTOR LARGER THAN WORK(11)
  //C              FROM A STEP TO THE SUBSEQUENT, THE ROUTINE SEARCHING BREAKING
  //C              POINTS ACTIVATES.
  //C              DEFAULT VALUE: WORK(11)=5.D0
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
  //C                   IDID= 2  COMPUT. SUCCESSFUL (INTERRUPTED BY SOLOUT)
  //C                   IDID=-1  INPUT IS NOT CONSISTENT,
  //C                   IDID=-2  LARGER NMAX IS NEEDED,
  //C                   IDID=-3  STEP SIZE BECOMES TOO SMALL,
  //C                   IDID=-4  MATRIX IS REPEATEDLY SINGULAR.
  //C                   IDID=-5  COMPUTATION INTERRUPTED BY YLAGR5.
  //C                   IDID=-6  THE EQUATION USES ADVANCED ARGUMENTS
  //C
  //C   IWORK(13)  NFULL   NUMBER OF FULL NEWTON ITERATIONS
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
  //C     INTEGER, PARAMETER :: DP=kind(1D0)
  //C ----> COMMON BLOCKS <----
  //C *** *** *** *** *** *** ***
  //C        SETTING THE PARAMETERS
  //C *** *** *** *** *** *** ***
  nn = n;
  nfcn = 0;
  njac = 0;
  nstep = 0;
  naccpt = 0;
  nrejct = 0;
  ndec = 0;
  nsol = 0;
  arret = false;
  mCommon.flags = false;
  mCommon.flagn = false;
  //C
  if (iout == 1)
    {
      write("STARTING INTEGRATION ...");
    }
  //C
  //C ------> OPERATIONS RELEVANT TO THE DELAY DEPENDENCE <------
  //C
  //C -------- ERROR CONTROL
  if (iwork(11) == 0)
    {
      ieflag = 2;
    }
  else
    {
      ieflag = iwork(11);
    }
  if (ieflag == 2)
    {
      work(10) = 1.e0;
    }
  //C -------- NGRID   NUMBER OF PRESCRIBED GRID-POINTS
  ngrid = iwork(13);
  if (ngrid < 0)
    {
      ngrid = 0;
    }
  if (iout == 1)
    {
      write("NUMBER OF PRESCRIBED GRID POINTS: ", ngrid);
    }
  //C ------- NDIMN   NUMBER OF COMPONENTS OF A NEUTRAL PROBLEM
  if (imas == 2)
    {
      if (iwork(16) == 0)
        {
          write("NUMBER OF Y COMPONENTS HAS TO BE SPECIFIED");
          arret = true;
        }
      ndimn = iwork(16);
    }
  else
    {
      ndimn = 0;
    }
  //C ------- LIPAST   DIMENSION OF VECTOR IPAST
  lipast = nrdens + 1;
  if (nrdens < 0 || nrdens > n)
    {
      if (iout > 0)
        {
          write("CURIOUS INPUT IWORK(15) = ", iwork(15));
        }
      arret = true;
    }
  else
    {
      nrds = nrdens;
    }
  if (nrds == n)
    {
      for (size_t i = 1; i <= nrds; ++i) // FEM_DO_SAFE(i, 1, nrds)
        {
          ipast(i) = i;
        }
    }
  if (iout == 1)
    {
      write("NUMBER OF DELAYED COMPONENTS: ", nrds);
    }
  //C ------- LRPAST   DIMENSION OF VECTOR PAST
  mxst = iwork(12);
  //C ------- CONTROL OF LENGTH OF PAST  -------
  if (mxst < 1)
    {
      if (iout > 0)
        {
          write("INSUFFICIENT STORAGE FOR PAST, MIN. LRPAST: ", 1);
        }
      arret = true;
    }
  //C ------- DIM. of PAST  --------
  idif = 4 * nrds + 2;
  lrpast = mxst * idif;
  //C -------------------------------------------------
  //C ------- CONTROL OF SIMPLE NEWTON ITERATION  -------
  iswjl = iwork(14);
  if (iswjl == 0)
    {
      iswjl = 1;
    }
  //C
  //C -------- UROUND : SMALLEST NUMBER SATISFYING 1.0D0+UROUND>1.0D0
  if (work(1) == 0.0e0)
    {
      uround = 1.0e-16;
    }
  else
    {
      uround = work(1);
      if (uround <= 1.0e-19 || uround >= 1.0e0)
        {
          write("COEFFICIENTS HAVE 20 DIGITS, UROUND = ", work(1));
          arret = true;
        }
    }
  //C
  //C -------> CHECK AND CHANGE THE TOLERANCES <------
  expm = 2.0e0 / 3.0e0;
  if (itol == 0)
    {
      if (atol(1) <= 0.e0 || rtol(1) <= 10.e0 * uround)
        {
          write("TOLERANCES ARE TOO SMALL");
          arret = true;
        }
      else
        {
          quot = atol(1) / rtol(1);
          rtol(1) = 0.1e0 * pow(rtol(1), expm);
          atol(1) = rtol(1) * quot;
        }
    }
  else
    {
      for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
        {
          if (atol(i) <= 0.e0 || rtol(i) <= 10.e0 * uround)
            {
              write("TOLERANCES(", i, ") ARE TOO SMALL");
              arret = true;
            }
          else
            {
              quot = atol(i) / rtol(i);
              rtol(i) = 0.1e0 * pow(rtol(i), expm);
              atol(i) = rtol(i) * quot;
            }
        }
    }
  //C
  //C -------> NMAX : THE MAXIMAL NUMBER OF STEPS <-------
  if (iwork(2) == 0)
    {
      nmax = 100000;
    }
  else
    {
      nmax = iwork(2);
      if (nmax <= 0)
        {
          write("WRONG INPUT IWORK(2) = ", iwork(2));
          arret = true;
        }
    }
  //C
  //C -------> NIT :  MAXIMAL NUMBER OF NEWTON ITERATIONS <-------
  if (iwork(3) == 0)
    {
      nit = 7;
    }
  else
    {
      nit = iwork(3);
      if (nit <= 0)
        {
          write("CURIOUS INPUT IWORK(3) = ", iwork(3));
          arret = true;
        }
    }
  //C -------- STARTN : SWITCH FOR STARTING VALUES OF NEWTON ITERATIONS
  if (iwork(4) == 0)
    {
      startn = false;
    }
  else
    {
      startn = true;
    }
  //C
  //C -------> PARAMETERS (IF ANY) FOR DIFFERENTIAL-ALGEBRAIC COMPONENTS <-------
  nind1 = iwork(5);
  nind2 = iwork(6);
  nind3 = iwork(7);
  if (nind1 == 0)
    {
      nind1 = n;
    }
  if (nind1 + nind2 + nind3 != n)
    {
      write("CURIOUS INPUT FOR IWORK(5,6,7): ", nind1, ", ", nind2, ", ", nind3);
      arret = true;
    }
  //C
  //C -------> PRED   STEP SIZE CONTROL <-------
  if (iwork(8) <= 1)
    {
      pred = true;
    }
  else
    {
      pred = false;
    }
  //C
  //C -------> PARAMETER FOR SECOND ORDER EQUATIONS <-------
  m1 = iwork(9);
  m2 = iwork(10);
  nm1 = n - m1;
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
      write("CURIOUS INPUT FOR IWORK(9,10): ", m1, ", ", m2);
      arret = true;
    }
  //C
  //C -------> SAFE  :  SAFETY FACTOR IN STEP SIZE PREDICTION <-------
  if (work(2) == 0.0e0)
    {
      safe = 0.9e0;
    }
  else
    {
      safe = work(2);
      if (safe <= 0.001e0 || safe >= 1.0e0)
        {
          write("CURIOUS INPUT FOR WORK(2): ", work(2));
          arret = true;
        }
    }
  //C
  //C ------> THET : DETERMINES WHETHER THE JACOBIAN SHOULD BE RECOMPUTED;
  if (work(3) == 0.e0)
    {
      thet = 0.001e0;
    }
  else
    {
      thet = work(3);
      if (thet >= 1.0e0)
        {
          write("CURIOUS INPUT FOR WORK(3): ", work(3));
          arret = true;
        }
    }
  //C
  //C ---> FNEWT : STOPPING CRITERION FOR NEWTON'S METHOD, USUALLY CHOSEN <1. <---
  tolst = rtol(1);
  if (work(4) == 0.e0)
    {
      fnewt = std::max(10 * uround / tolst, std::min(0.03e0, pow(tolst,
                                                                 0.5e0)));
    }
  else
    {
      fnewt = work(4);
      if (fnewt <= uround / tolst)
        {
          write("CURIOUS INPUT FOR WORK(4): ", work(4));
          arret = true;
        }
    }
  //C
  //C ---> QUOT1 AND QUOT2: IF QUOT1 < HNEW/HOLD < QUOT2, STEP SIZE = CONST. <---
  if (work(5) == 0.e0)
    {
      quot1 = 1.e0;
    }
  else
    {
      quot1 = work(5);
    }
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
      write("CURIOUS INPUT FOR WORK(5,6): ", quot1, ", ", quot2);
      arret = true;
    }
  //C -------------------------------------------------------
  //C
  //C ---->    GRID WITH DISCONTINUITIES  <----
  xuro = 100 * uround * dabs(xend);
  if (ngrid > 0)
    {
      if (grid(ngrid) - xend >= xuro)
        {
          if (iout > 0)
            {
              write("GRID(NGRID) HAS TO BE <= XEND ");
            }
          arret = true;
        }
      if (dabs(grid(ngrid) - xend) >= xuro)
        {
          ngrid++;
        }
    }
  else
    {
      ngrid++;
    }
  grid(ngrid) = xend;
  //C -------------------------------------------------------
  //C
  //C -------> MAXIMAL STEP SIZE <-------
  if (work(7) == 0.e0)
    {
      for (size_t i = 1; i <= ngrid; ++i) // FEM_DO_SAFE(i, 1, ngrid)
        {
          if (grid(i) > x)
            {
              igrid = i;
              goto statement_2;
            }
        }
    statement_2:
      hmax = grid(igrid) - x;
    }
  else
    {
      hmax = work(7);
    }
  //C
  //C ------->  FACL,FACR     PARAMETERS FOR STEP SIZE SELECTION <-------
  if (work(8) == 0.e0)
    {
      facl = 5.e0;
    }
  else
    {
      facl = 1.e0 / work(8);
    }
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
      write("CURIOUS INPUT WORK(8,9): ", work(8), ", ", work(9));
      arret = true;
    }
  //C ------->  PARAMETER FOR THE CONTROL OF DENSE OUTPUT <-------
  alpha = work(10);
  if (alpha < 0.e0 || alpha > 1.e0)
    {
      write("CURIOUS INPUT WORK(10): ", work(10));
      arret = true;
    }
  //C ------->   PARAMETER FOR CONTROLLING THE SEARCH OF BP <-------
  tckbp = work(11);
  if (tckbp <= 0.e0)
    {
      tckbp = 5.e0;
    }
  //C *** *** *** *** *** *** *** *** *** *** *** *** ***
  //C         COMPUTATION OF ARRAY ENTRIES
  //C *** *** *** *** *** *** *** *** *** *** *** *** ***
  //C ---- IMPLICIT, BANDED OR NOT ?
  implct = imas != 0;
  neutral = imas == 2;
  jband = mljac < nm1;
  //C -------- COMPUTATION OF THE ROW-DIMENSIONS OF THE 2-ARRAYS ---
  //C -- JACOBIAN  AND  MATRICES E1, E2
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
  ldmas2 = std::max(1, ldmas);
  //C ------ HESSENBERG OPTION ONLY FOR EXPLICIT EQU. WITH FULL JACOBIAN
  if ((implct || jband) && ijob == 7)
    {
      write("HESSENBERG OPTION ONLY FOR EXPLICIT EQUATIONS WITH FULL JACOBIAN");
      arret = true;
    }
  //C
  //C ------ WHEN A FAIL HAS OCCURED, WE RETURN WITH IDID=-1
  if (arret)
    {
      idid = -1;
      return;
    }
  //C
  //C     NUMERICAL KERNEL
  write("INTEGRATION ...");
  //C -------- CALL TO CORE INTEGRATOR ------------
  radcor(mCommon, n, x, y, xend, h, fcn, phi, arglag, rtol, atol, itol, jac,
         ijac, mljac, mujac, jaclag, mas, mlmas, mumas, solout, iout, idid,
         nmax, safe, thet, fnewt, quot1, quot2, nit, ijob, startn, nind1,
         nind2, nind3, pred, facl, facr, m1, m2, nm1, implct, neutral, ndimn,
         jband, ldjac, lde1, ldmas2, nfcn, njac, nstep, naccpt, nrejct, ndec,
         nsol, nfull, rpar, ipar, ipast, grid, lgrid, nrds, nlags, njacl,
         ngrid, ieflag, work(7), tckbp, alpha, iswjl);
  iwork(13) = nfull;
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
      rtol(1) = pow((10.0e0 * rtol(1)), expm);
      atol(1) = rtol(1) * quot;
    }
  else
    {
      for (size_t i = 1; i <= n; ++i) // FEM_DO_SAFE(i, 1, n)
        {
          quot = atol(i) / rtol(i);
          rtol(i) = pow((10.0e0 * rtol(i)), expm);
          atol(i) = rtol(i) * quot;
        }
    }
  //C ----------- RETURN -----------
}

//C
//C     END OF SUBROUTINE RADCOR
//C
//C ***********************************************************
//C
void CRadar5::lagr5(common & cmn,
                   const integer & il,
                   const doublereal & x,
                   const integer & n,
                   float const & y,
                   ARGLAG & arglag,
                   CVectorCore< doublereal > & past,
                   doublereal & theta,
                   integer & ipos,
                   float const & rpar,
                   const integer & ipar,
                   PHI & phi,
                   CVectorCore< integer > & ipast,
                   const integer & nrds)
{
  const logical & first = cmn.first;
  const logical & bpd = cmn.bpd;
  const doublereal & bpp = cmn.bpp;
  const integer & ilbp = cmn.ilbp;
  const logical & left = cmn.left;
  const doublereal & x0b = cmn.x0b;
  const doublereal & uround = cmn.uround;
  const integer & iact = cmn.iact;
  const integer & idif = cmn.idif;
  const integer & mxst = cmn.mxst;
  //
  doublereal xlag = 0.0;
  doublereal compar = 0.0;
  doublereal epsact = 0.0;
  integer ipa = 0;
  integer inext = 0;
  doublereal xright = 0.0;
  doublereal h = 0.0;
  integer iprev = 0;
  integer iposb = 0;
  doublereal epsilon = 0.0;
  //C ----------------------------------------------------------
  //C     THIS FUNCTION CAN BE USED FOR CONTINUOUS OUTPUT IN CONNECTION
  //C     WITH THE OUTPUT-SUBROUTINE FOR RADAR5. IT PROVIDES THE
  //C     POSITION OF THE DENSE OUTPUT AT THE IL-TH DELAY.
  //C ----------------------------------------------------------
  //C     INTEGER, PARAMETER :: DP=kind(1D0)
  //C --- COMMON BLOCKS
  //C --- COMPUTE DEVIATED ARGUMENT FOR IL-TH DELAY
  xlag = arglag(il, x, n, y, rpar, ipar, phi, past, ipast, nrds);
  //C --- INITIAL PHASE
  theta = xlag;
  ipos = -1;
  //C     EPSILON GIVES THE OVERLAPPING
  //C     MIN VALUE FOR THE SUPER-POSITION NEIGHBOURHOOD OF A BP
  compar = uround * std::max(dabs(xlag), dabs(x0b));
  epsact = 10.e0 * compar;
  if (iact > 1)
    {
      epsact = std::max(past(iact - 1) - 2, epsact);
    }
  if (xlag <= x0b)
    {
      //C ---     DEVIATING ARGUMENT ON THE INITIAL SEGMENT
      if (!((il == ilbp) && (bpd || first)))
        {
          if (xlag - x0b < 0.e0)
            {
              return;
            }
          else
            {
              ipos = 1;
              theta = -1.e0;
            }
        }
      else
        {
          if (dabs(xlag - x0b) <= epsact)
            {
              if (left)
                {
                  ipos = -1;
                  theta = xlag;
                }
              else
                {
                  ipos = 1;
                  theta = (xlag - (past(ipos) + past(ipos + idif - 1))) / past(ipos + idif - 1);
                }
            }
          else if (dabs(xlag - bpp) <= epsact)
            {
              ipos = -1;
              if (left)
                {
                  if (xlag > bpp)
                    {
                      if (bpp > 0.e0)
                        {
                          theta = bpp * (1.e0 - 100 * uround);
                        }
                      else
                        {
                          theta = bpp * (1.e0 + 100 * uround);
                        }
                    }
                }
              else
                {
                  if (xlag < bpp)
                    {
                      if (bpp > 0)
                        {
                          theta = bpp * (1.e0 + 100 * uround);
                        }
                      else
                        {
                          theta = bpp * (1.e0 - 100 * uround);
                        }
                    }
                }
            }
        }
      return;
    }
  //C --- COMPUTE THE POSITION OF XLAG
  ipa = iact + idif;
  if (ipa > (mxst - 1) * idif + 1)
    {
      ipa = 1;
    }
  if (xlag - past(ipa) < 0.e0)
    {
      write("MEMORY FULL, MXST = ", mxst);
      cmn.irtrn = -1;
      fatalError();
      ;
    }
  inext = iact - idif;
  if (inext < 1)
    {
      inext = (mxst - 1) * idif + 1;
    }
  xright = past(inext) + past(inext + idif - 1);
  //C -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
  //C --- INITIALIZE POSITION INSIDE THE MEMORY
  ipos = ipast(il + 2 * n);
  //C --- STEP AND DELAYS
  if (xlag - xright > 0.e0)
    {
      if (!cmn.flagn)
        {
          ipos = iact - idif;
          if (ipos < 1)
            {
              ipos = (mxst - 1) * idif + 1;
            }
        }
      else
        {
          ipos = iact;
        }
      cmn.flags = true;
      //C ------------------------
      //C ----- COMPUTE THETA (>0)
      //C ------------------------
      h = past(ipos + idif - 1);
      theta = (xlag - (past(ipos) + h)) / h;
      //C -----    EXTRAPOLATION USE OF THE COLLOCATION POLYNOMIAL
      //C -----
      return;
    }
  else
    {
    statement_1:
      if (xlag - past(ipos) <= 0.e0)
        {
          ipos = ipos - idif;
          if (ipos < 1)
            {
              ipos = (mxst - 1) * idif + 1;
            }
          goto statement_1;
        }
    statement_2:
      inext = ipos + idif;
      if (inext > (mxst - 1) * idif + 1)
        {
          inext = 1;
        }
      if (xlag > past(inext) && inext != iact)
        {
          ipos = inext;
          goto statement_2;
        }
      if (ipos == 1)
        {
          iprev = (mxst - 1) * idif + 1;
        }
      else
        {
          iprev = ipos - idif;
        }
      //C ---
      //C ---   IN CORRESPONDENCE OF BREAKING POINTS
      //C ---
      if (!((il == ilbp) && (bpd || first)))
        {
          goto statement_10;
        }
      if (bpp == x0b)
        {
          if (left)
            {
              ipos = -1;
              theta = xlag;
              return;
            }
          else
            {
              if (ipos == -1)
                {
                  ipos = 1;
                }
              goto statement_10;
            }
        }
      iposb = 0;
      if (dabs(bpp - past(ipos)) <= 10.e0 * uround)
        {
          iposb = ipos;
        }
      else if (dabs(bpp - past(inext)) <= 10.e0 * uround)
        {
          iposb = inext;
        }
      if (iposb == 0)
        {
          goto statement_10;
        }
      if (iposb == 1)
        {
          epsilon = (past(iposb + idif) - past(iposb));
        }
      else if (iposb == (mxst - 1) * idif + 1)
        {
          epsilon = (past(iposb) - past(iposb - idif));
        }
      else
        {
          epsilon = std::min(past(iposb + idif) - past(iposb), past(iposb) - past(iposb - idif));
        }
      epsilon = std::max(epsilon * 1.e-2, epsact);
      if (dabs(xlag - bpp) > epsilon)
        {
          goto statement_10;
        }
      if (iposb == 1)
        {
          if (left)
            {
              ipos = -1;
              theta = xlag;
              return;
            }
          else
            {
              ipos = 1;
              goto statement_10;
            }
        }
      if (left)
        {
          //C ---     PREVIOUS INTERVAL HAS TO BE SELECTED
          ipos = iposb - idif;
        }
      else
        {
          //C ---     NEXT INTERVAL HAS TO BE SELECTED
          ipos = iposb;
        }
    //C ----- COMPUTE THETA (<0): SITUAZIONE PIU' TIPICA
    statement_10:
      theta = (xlag - (past(ipos) + past(ipos + idif - 1))) / past(ipos + idif - 1);
      //C ----- REM: THETA IS NEGATIVE
    }
  //C --- UPDATE POSITION INSIDE THE MEMORY
  ipast(il + 2 * n) = ipos;
}

//C
//C     END OF FUNCTION LAGR5
//C
//C -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//C
//C ***********************************************************
//C
doublereal CRadar5::ylagr5(const common & cmn,
                          const integer & ic,
                          const doublereal & theta,
                          const integer & ipos,
                          PHI & phi,
                          float const & rpar,
                          const integer & ipar,
                          CVectorCore< doublereal > & past,
                          CVectorCore< integer > & ipast,
                          const integer & nrds)
{
  doublereal return_value = 0.0;
  //C ----------------------------------------------------------
  //C     THIS FUNCTION CAN BE USED FOR CONTINUOUS OUTPUT IN CONNECTION
  //C     WITH THE SUBROUTINE LAGR5. IT PROVIDES AN APPROXIMATION
  //C     TO THE IC-TH COMPONENT OF THE SOLUTION AT XLAG.
  //C ----------------------------------------------------------
  //C     INTEGER, PARAMETER :: DP=kind(1D0)
  //C---- COMMON BLOCKS
  //C
  //C --- INITIAL PHASE
  if (ipos == -1)
    {
      return_value = phi(ic, theta, rpar, ipar);
      //C ---       CALL PHI(IC,THETA,YLAGR5,RPAR,IPAR)
      return return_value;
    }
  //C ---
  //C --- COMPUTE PLACE OF IC-TH COMPONENT
  integer i = 0;
  integer j = 0;
  for (size_t j = 1; j <= nrds; ++j) // FEM_DO_SAFE(j, 1, nrds)
    {
      if (ipast(j) == ic)
        {
          i = j;
        }
    }
  if (i == 0)
    {
      write("NO DENSE OUTPUT AVAILABLE FOR COMP: ", ic);
      return return_value;
    }
  //C ----- COMPUTE DESIRED APPROXIMATION
  i += ipos;
  return_value = past(i) + theta * (past(nrds + i) + (theta - cmn.c2m1) * (past(2 * nrds + i) + (theta - cmn.c1m1) * (past(3 * nrds + i))));
  return return_value;
}

//C
//C     END OF FUNCTION YLAGR5
//C
//C ***********************************************************
//C
doublereal CRadar5::dlagr5(const common & cmn,
                          const integer & ic,
                          const doublereal & theta,
                          const integer & ipos,
                          PHI & phi,
                          float const & rpar,
                          const integer & ipar,
                          CVectorCore< doublereal > & past,
                          CVectorCore< integer > & ipast,
                          const integer & nrds)
{
  doublereal return_value = 0.0;
  // COMMON constn
  const doublereal & c1m1 = cmn.c1m1;
  const doublereal & c2m1 = cmn.c2m1;
  //
  //C ----------------------------------------------------------
  //C     THIS FUNCTION CAN BE USED FOR CONTINUOUS OUTPUT IN CONNECTION
  //C     WITH THE SUBROUTINE LAGR5. IT PROVIDES AN APPROXIMATION
  //C     TO THE IC-TH COMPONENT OF THE SOLUTION DERIVATIVE AT XLAG.
  //C ----------------------------------------------------------
  //C     INTEGER, PARAMETER :: DP=kind(1D0)
  //C---- COMMON BLOCKS
  //C
  //C --- INITIAL PHASE
  if (ipos == -1)
    {
      //C           DLAGR5=DPHI(IC,THETA,RPAR,IPAR)
      return_value = 0.e0;
      return return_value;
    }
  //C ---
  //C --- COMPUTE PLACE OF IC-TH COMPONENT
  integer i = 0;
  integer j = 0;
  for (size_t j = 1; j <= nrds; ++j) // FEM_DO_SAFE(j, 1, nrds)
    {
      if (ipast(j) == ic)
        {
          i = j;
        }
    }
  if (i == 0)
    {
      write("NO DENSE OUTPUT AVAILABLE FOR COMP: ", ic);
      return return_value;
    }
  //C ----- COMPUTE DESIRED APPROXIMATION
  doublereal h = past(ipos + cmn.idif - 1);
  i += ipos;
  return_value = past(nrds + i) + (theta - c2m1) * (past(2 * nrds + i) + (theta - c1m1) * past(3 * nrds + i)) + theta * (past(2 * nrds + i) + (2.e0 * theta - c2m1 - c1m1) * past(3 * nrds + i));
  return_value = return_value / h;
  return return_value;
}

//C
//C     END OF FUNCTION CONTR5
//C
//C ***********************************************************
//C
doublereal CRadar5::dontr5(const common & cmn,
                          const integer & i,
                          const integer & n,
                          const doublereal & x,
                          const CVectorCore< doublereal > & cont,
                          const doublereal & xsol,
                          const doublereal & hsol)
{
  doublereal return_value = 0.0;
  // COMMON constn
  const doublereal & c1m1 = cmn.c1m1;
  const doublereal & c2m1 = cmn.c2m1;
  //
  //C ----------------------------------------------------------
  //C     THIS FUNCTION CAN BE USED FOR CONINUOUS OUTPUT. IT PROVIDES AN
  //C     APPROXIMATION TO THE I-TH COMPONENT OF THE SOLUTION DERIVATIVE AT .
  //C     X. IT GIVES THE VALUE OF THE COLLOCATION POLYNOMIAL, DEFINED FOR
  //C     THE LAST SUCCESSFULLY COMPUTED STEP (BY DELAY5).
  //C ----------------------------------------------------------
  //C     INTEGER, PARAMETER :: DP=kind(1D0)
  //C --- REQUIRED CONSTANTS
  integer n2 = 2 * n;
  integer n3 = 3 * n;
  doublereal s = (x - xsol) / hsol;
  return_value = (cont(i + n) + (s - c2m1) * (cont(i + n2) + cont(i + n3) * (s - c1m1)) + s * (cont(i + n2) + cont(i + n3) * (2.f * s - c1m1 - c2m1))) / hsol;
  return return_value;
}

void CRadar5::estrad(const common & cmn,
                    const integer & n,
                    CMatrix< doublereal > & fjac,
                    const integer & ldjac,
                    const integer & mljac,
                    const integer & mujac,
                    CMatrix< doublereal > & fmas,
                    const integer & ldmas,
                    const integer & mlmas,
                    const integer & mumas,
                    const doublereal & h,
                    const doublereal & g0,
                    const doublereal & dd1,
                    const doublereal & dd2,
                    const doublereal & dd3,
                    const doublereal & cl1,
                    const doublereal & cl3,
                    const doublereal & cq1,
                    const doublereal & cq2,
                    const doublereal & cq3,
                    const doublereal & cerlq,
                    FCN & fcn,
                    integer & nfcn,
                    CVectorCore< doublereal > & y0,
                    CVectorCore< doublereal > & y,
                    const integer & ijob,
                    const doublereal & x,
                    const integer & m1,
                    const integer & m2,
                    const integer & nm1,
                    CMatrix< doublereal > & e1,
                    const integer & lde1,
                    const doublereal & alpha,
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
                    logical const & first,
                    logical const & reject,
                    const doublereal & fac1,
                    ARGLAG & arglag,
                    PHI & phi,
                    const doublereal & rpar,
                    const integer & ipar,
                    const integer & iout,
                    CVectorCore< doublereal > & past,
                    CVectorCore< integer > & ipast,
                    const integer & nrds,
                    const integer & jeflag,
                    const integer & ieflag)
{
  const integer & mbdiag = cmn.mbdiag;
  //
  double hee1 = 0.0;
  double hee2 = 0.0;
  double hee3 = 0.0;
  integer nl = 0;
  integer i = 0;
  double bb = 0.0;
  double errb = 0.0;
  double errlb = 0.0;
  double errl = 0.0;
  double errqb = 0.0;
  double errq = 0.0;
  double cerrb = 0.0;
  double xx = 0.0;
  double serr = 0.0;
  CVector< double > w1(n);
  CVector< double > w2(n);
  CVector< double > q1(n);
  CVector< double > q2(n);
  w1(1) = 1.0e0;
  w2(1) = 1.0e0;
  q1(1) = 1.0e0;
  q2(1) = 1.0e0;
  hee1 = dd1 / h;
  hee2 = dd2 / h;
  hee3 = dd3 / h;
  switch (ijob)
    {
    case 1:
      goto statement_1;
    case 2:
      goto statement_2;
    case 3:
      goto statement_3;
    case 4:
      goto statement_2;
    case 5:
      goto statement_55;
    case 6:
      goto statement_55;
    case 7:
      goto statement_55;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_2;
    case 12:
      goto statement_2;
    case 13:
      goto statement_55;
    case 14:
      goto statement_55;
    case 15:
      goto statement_55;
    default:
      break;
    }
//C
statement_1:
  //C ------  B=IDENTITY, JACOBIAN A FULL MATRIX
  nl = n;
  for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
    {
      f2(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
      cont(i) = f2(i) + y0(i);
      w1(i) = cl1 * z1(i) + cl3 * z3(i);
      q1(i) = cq1 * z1(i) + cq2 * z2(i) + cq3 * z3(i);
    }
  for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
    {
      f3(i) = g0 * h * cont(i);
    }
  if (alpha != 0.e0)
    {
      for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
        {
          w2(i) = w1(i) / (g0 * h);
          q2(i) = q1(i) / (g0 * h);
        }
      sol(nl, lde1, e1, w2, ip1);
      sol(nl, lde1, e1, q2, ip1);
    }
  sol(nl, lde1, e1, cont, ip1);
  goto statement_77;
//C
statement_2:
  //C ------  B IS DIAGONAL, JACOBIAN A BANDED MATRIX
  nl = n - 2;
  bb = 1.0e0;
  for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
    {
      if (ijob == 4)
        {
          bb = fmas(mbdiag, i);
        }
      f2(i) = bb * (hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i));
      cont(i) = f2(i) + y0(i);
      w1(i) = bb * (cl1 * z1(i) + cl3 * z3(i));
      q1(i) = bb * (cq1 * z1(i) + cq2 * z2(i) + cq3 * z3(i));
    }
  for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
    {
      f3(i) = g0 * h * cont(i);
    }
  if (alpha != 0.e0)
    {
      for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
        {
          w2(i) = w1(i) / (g0 * h);
          q2(i) = q1(i) / (g0 * h);
        }
      solexp(n, fjac, ldjac, mujac, nm1, lde1, e1, w2, ip1, fac1, ijob);
      solexp(n, fjac, ldjac, mujac, nm1, lde1, e1, q2, ip1, fac1, ijob);
    }
  solexp(n, fjac, ldjac, mujac, nm1, lde1, e1, cont, ip1, fac1, ijob);
  goto statement_77;
//C
statement_3:
  //C ------  B IS DIAGONAL, JACOBIAN A FULL MATRIX
  nl = n;
  for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
    {
      bb = fmas(mbdiag, i);
      f2(i) = bb * (hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i));
      w1(i) = bb * (cl1 * z1(i) + cl3 * z3(i));
      q1(i) = bb * (cq1 * z1(i) + cq2 * z2(i) + cq3 * z3(i));
      cont(i) = f2(i) + y0(i);
    }
  for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
    {
      f3(i) = g0 * h * cont(i);
    }
  if (alpha != 0.e0)
    {
      for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
        {
          w2(i) = w1(i) / (g0 * h);
          q2(i) = q1(i) / (g0 * h);
        }
      sol(nl, lde1, e1, w2, ip1);
      sol(nl, lde1, e1, q2, ip1);
    }
  sol(nl, lde1, e1, cont, ip1);
  goto statement_77;
//C
//C --------------------------------------
//C
statement_77:
  //C ********************
  //C --- ERROR ESTIMATION
  //C ********************
  errb = 0.e0;
  for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
    {
      errb += pow2((w1(i) / scal(i)));
    }
  errlb = std::max(std::sqrt(errb / nl), 1.e-10);
  if (alpha != 0.e0)
    {
      err = 0.e0;
      for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
        {
          err += pow2((w2(i) / scal(i)));
        }
      errl = std::max(std::sqrt(err / nl), 1.e-10);
    }
  else
    {
      errl = 0.e0;
    }
  errb = 0.e0;
  for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
    {
      errb += pow2((q1(i) / scal(i)));
    }
  errqb = std::max(std::sqrt(errb / nl), 1.e-10);
  if (alpha != 0.e0)
    {
      err = 0.e0;
      for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
        {
          err += pow2((q2(i) / scal(i)));
        }
      errq = std::max(std::sqrt(err / nl), 1.e-10);
    }
  else
    {
      errq = 0.e0;
    }
  cerrb = errqb * (errqb / std::sqrt(errqb * errqb + cerlq * cerlq * pow2(std::min(errlb, errqb / cerlq))));
  if (alpha != 0.e0)
    {
      cerr = errq * (errq / std::sqrt(errq * errq + cerlq * cerlq * pow2(std::min(errl, errq / cerlq))));
    }
  else
    {
      cerr = 0.e0;
    }
  cerr = alpha * cerr + (1.e0 - alpha) * cerrb;
  errb = 0.e0;
  for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
    {
      errb += pow2((f3(i) / scal(i)));
    }
  errb = std::max(std::sqrt(errb / nl), 1.e-10);
  err = 0.e0;
  for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
    {
      err += pow2((cont(i) / scal(i)));
    }
  err = std::max(std::sqrt(err / nl), 1.e-10);
  err = std::min(errb, err);
  if (err < 1.e0 || jeflag > 0)
    {
      return;
    }
  else if (first || reject)
    {
      for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
        {
          cont(i) += y(i);
        }
      //C ---
      xx = x;
      fcn(n, xx, cont, f1, arglag, phi, rpar, ipar, past, ipast, nrds);
      nfcn++;
      for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
        {
          cont(i) = f1(i) + f2(i);
        }
      switch (ijob)
        {
        case 1:
          goto statement_31;
        case 2:
          goto statement_32;
        case 3:
          goto statement_31;
        case 4:
          goto statement_32;
        case 5:
          goto statement_31;
        case 6:
          goto statement_32;
        case 7:
          goto statement_55;
        case 8:
          goto statement_55;
        case 9:
          goto statement_55;
        case 10:
          goto statement_55;
        case 11:
          goto statement_32;
        case 12:
          goto statement_32;
        case 13:
          goto statement_31;
        case 14:
          goto statement_32;
        case 15:
          goto statement_31;
        default:
          break;
        }
    //C ----- FULL MATRIX OPTION
    statement_31:
      sol(nl, lde1, e1, cont, ip1);
      goto statement_88;
    //C ----- BANDED MATRIX OPTION
    statement_32:
      solexp(n, fjac, ldjac, mujac, nm1, lde1, e1, cont, ip1, fac1, ijob);
      goto statement_88;
    //C -----------------------------------
    statement_88:
      serr = err;
      err = 0.e0;
      for (size_t i = 1; i <= nl; ++i) // FEM_DO_SAFE(i, 1, nl)
        {
          err += pow2((cont(i) / scal(i)));
        }
      err = std::max(std::sqrt(err / nl), 1.e-10);
      err = std::min(serr, err);
    }
  return;
//C -----------------------------------------------------------
statement_55:
  return;
}

//C
//C     END OF SUBROUTINE ESTRAD
//C
//C ***********************************************************

// Matrix Triangularization by Gaussian Elimination
// integer dec_(integer n, doublereal **A, integer *ip);
integer CRadar5::dec(const integer & n,
                    const integer & ldjac,
                    CMatrix< doublereal > & fjacl,
                    CVectorCore< integer > & ipj,
                    integer & ier)
{
  return dec_(&n, &ldjac, fjacl.array(), ipj.array(), &ier);
}

// Solution of linear system A*x = b
// void sol_(integer n, doublereal **A, doublereal *b, integer *ip);
integer CRadar5::sol(const integer & n,
                    const integer & ldjac,
                    const CMatrix< doublereal > & fjacl,
                    CVectorCore< doublereal > & zl,
                    const CVectorCore< integer > & ipj)
{
  return sol_(&n, &ldjac, fjacl.array(), zl.array(), ipj.array());
}
