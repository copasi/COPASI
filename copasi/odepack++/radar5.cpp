// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/odepack++/radar5.h"
#include "copasi/odepack++/decsol.h"

using namespace fem::major_types;

radar5::common_constn::common_constn()
  : c1(fem::double0)
  , c2(fem::double0)
  , c1m1(fem::double0)
  , c2m1(fem::double0)
  , c1mc2(fem::double0)
{}

radar5::common_posits::common_posits()
  : x0b(fem::double0)
  , uround(fem::double0)
  , hmax(fem::double0)
  , iact(fem::int0)
  , irtrn(fem::int0)
  , idif(fem::int0)
  , mxst(fem::int0)
  , flags(fem::bool0)
  , flagn(fem::bool0)
{}

radar5::common_bplog::common_bplog()
  : first(fem::bool0)
  , last(fem::bool0)
  , reject(fem::bool0)
  , bpd(fem::bool0)
{}

radar5::common_bpcom::common_bpcom()
  : bpp(fem::double0)
  , ilbp(fem::int0)
  , left(fem::bool0)
{}

radar5::common_linal::common_linal()
  : mle(fem::int0)
  , mue(fem::int0)
  , mbjac(fem::int0)
  , mbb(fem::int0)
  , mdiag(fem::int0)
  , mdiff(fem::int0)
  , mbdiag(fem::int0)
{}

radar5::common::common(integer argc, char const * argv[])
  : fem::common(argc, argv)
  , common_constn()
  , common_posits()
  , common_bplog()
  , common_bpcom()
  , common_linal()
{}

//C********************************************************
//C
doublereal radar5::contr5(common & cmn,
                      integer const & i,
                      integer const & n,
                      doublereal const & x,
                      const CVectorCore< doublereal > & cont,
                      doublereal const & xsol,
                      doublereal const & hsol)
{
  doublereal return_value = fem::double0;
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
void radar5::bpdtct(common & cmn,
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
                    integer const & nrds)
{
  integer lrc = fem::int0;
  doublereal epsilon = fem::double0;
  doublereal compar = fem::double0;
  doublereal xlast = fem::double0;
  doublereal hlast = fem::double0;
  integer il = fem::int0;
  doublereal als = fem::double0;
  integer ic = fem::int0;
  doublereal ald = fem::double0;
  integer l = fem::int0;
  doublereal thlim = fem::double0;
  doublereal thrigh = fem::double0;
  doublereal thleft = fem::double0;
  integer k = fem::int0;
  doublereal thnew = fem::double0;
  doublereal xa = fem::double0;
  doublereal aln = fem::double0;
  doublereal hp = fem::double0;
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
  FEM_THROW_UNHANDLED("executable allocate: allocate(yadv(n))");
  compar = cmn.uround * fem::max(fem::abs(x), fem::abs(x + h));
  xlast = ucont(lrc + 1);
  hlast = ucont(lrc + 2);
  FEM_DO_SAFE(il, 1, nlags)
  {
    als = arglag(il, x, n, y, rpar, ipar, phi, past, ipast, nrds);
    //C -----  DEVIATING ARGUMENT AT X
    //C -----  EXTRAPOLATION OF THE COLLOCATION POLYNOMIAL
    FEM_DO_SAFE(ic, 1, n)
    {
      yadv(ic) = contr5(cmn, ic, n, x + h, ucont, xlast, hlast);
    }
    ald = arglag(il, x + h, n, yadv, rpar, ipar, phi, past, ipast, nrds);
    //C -----  DEVIATING ARGUMENT AT X+H
    if (fem::abs(als - ald) <= compar)
      {
        goto statement_33;
      }
    FEM_DO_SAFE(l, 1, igrid - 1)
    {
      bpp = grid(l);
      if ((als - bpp) * (ald - bpp) < compar)
        {
          bpd = true;
          //C          BREAKING POINT!
          goto statement_33;
        }
    }
    FEM_DOSTEP(l, ibp, 1, -1)
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
        FEM_DO_SAFE(k, 1, kmax)
        {
          thnew = thleft - (als - bpp) * (thrigh - thleft) / (ald - als);
          //C ---       TEST DI CONVERGENZA
          if (fem::abs(thrigh - thnew) <= epsilon || fem::abs(thleft - thnew) <= epsilon)
            {
              goto statement_36;
            }
          xa = x + thnew * h;
          FEM_DO_SAFE(ic, 1, n)
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
            FEM_DO_SAFE(l, 1, igrid - 1)
            {
              bpp = grid(l);
              if (fem::abs(bpp - x - hp) <= compar)
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
  FEM_THROW_UNHANDLED("executable deallocate: deallocate(yadv)");
}

void radar5::bpacc(common & cmn,
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
                   integer const & nrds)
{
  CVector< doublereal > yapp(n);
  CVector< doublereal > ycont(4 * n);
  doublereal epsilon = fem::double0;
  integer i = fem::int0;
  doublereal z3i = fem::double0;
  doublereal yi = fem::double0;
  doublereal z2i = fem::double0;
  doublereal z1i = fem::double0;
  doublereal a1 = fem::double0;
  doublereal ak = fem::double0;
  doublereal acont3 = fem::double0;
  doublereal a2 = fem::double0;
  doublereal xsol = fem::double0;
  doublereal hsol = fem::double0;
  doublereal thleft = fem::double0;
  doublereal thrigh = fem::double0;
  doublereal xl = fem::double0;
  doublereal als = fem::double0;
  doublereal xr = fem::double0;
  doublereal ald = fem::double0;
  integer k = fem::int0;
  doublereal fac = fem::double0;
  doublereal thnew = fem::double0;
  doublereal xap = fem::double0;
  //C ----------------------------------------------------------
  //C     THIS SUBROUTINE CAN BE USED FOR APPROXIMATING BREAKING POINTS
  //C     IN TANDEM WITH THE SIMPLIFIED NEWTON ITERATION..
  //C ----------------------------------------------------------
  //C C     INTEGER, PARAMETER :: DP=kind(1D0)
  //C----   COMMON BLOCKS
  //C ---
  epsilon = cmn.uround * 1.e3;
  //C ---   DYNAMIC UPDATE
  FEM_DO_SAFE(i, 1, n)
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
  FEM_DO_SAFE(i, 1, n)
  {
    yapp(i) = contr5(cmn, i, n, xl, ycont, xsol, hsol);
  }
  als = arglag(ilbp, xl, n, yapp, rpar, ipar, phi, past, ipast, nrds);
  //C ---
  xr = x + thrigh * h;
  ald = arglag(ilbp, xr, n, ycont, rpar, ipar, phi, past, ipast, nrds);
  FEM_DO_SAFE(k, 1, kmax)
  {
    if (fem::abs(ald - als) <= epsilon)
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
    if (fem::abs(thnew - thrigh) <= epsilon)
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
    FEM_DO_SAFE(i, 1, n)
    {
      yapp(i) = contr5(cmn, i, n, xap, ycont, xsol, hsol);
    }
    ald = arglag(ilbp, xap, n, yapp, rpar, ipar, phi, past, ipast, nrds);
    if (fem::abs(ald - als) <= epsilon)
      {
        goto statement_36;
      }
  }
statement_36:
  //C ---   BP FOUND
  h = fem::min(thrigh, thleft) * h;
  bpv(ibp) = x + h;
}

//C
//C     END OF SUBROUTINE RADAR5
//C
//C ***********************************************************
//C
void radar5::radcor(common & cmn,
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
                    integer const & /* lgrid */,
                    integer const & nrds,
                    integer const & nlags,
                    integer const & njacl,
                    integer const & ngrid,
                    integer const & ieflag,
                    doublereal const & work7,
                    doublereal const & tckbp,
                    doublereal const & alpha,
                    integer const & iswjl)
{
  common_write write(cmn);
  doublereal & x0b = cmn.x0b;
  doublereal & uround = cmn.uround;
  doublereal & hmax = cmn.hmax;
  integer & iact = cmn.iact;
  integer & irtrn = cmn.irtrn;
  integer & idif = cmn.idif;
  integer & mxst = cmn.mxst;
  bool & flags = cmn.flags;
  bool & flagn = cmn.flagn;
  doublereal & c1 = cmn.c1;
  doublereal & c2 = cmn.c2;
  doublereal & c1m1 = cmn.c1m1;
  doublereal & c2m1 = cmn.c2m1;
  doublereal & c1mc2 = cmn.c1mc2;
  bool & first = cmn.first;
  bool & last = cmn.last;
  bool & reject = cmn.reject;
  bool & bpd = cmn.bpd;
  doublereal & bpp = cmn.bpp;
  integer & ilbp = cmn.ilbp;
  bool & left = cmn.left;
  integer & mle = cmn.mle;
  integer & mue = cmn.mue;
  integer & mbjac = cmn.mbjac;
  //
  integer lrc = fem::int0;
  bool bpc = fem::bool0;
  bool bpdmem = fem::bool0;
  bool quadr = fem::bool0;
  bool callag = fem::bool0;
  integer ipos = fem::int0;
  integer i = fem::int0;
  integer igrid = fem::int0;
  integer ibp = fem::int0;
  doublereal btol = fem::double0;
  integer kmax = fem::int0;
  integer imant = fem::int0;
  bool flagus = fem::bool0;
  doublereal erracc = fem::double0;
  doublereal rtolm = fem::double0;
  bool index1 = fem::bool0;
  bool index2 = fem::bool0;
  bool index3 = fem::bool0;
  doublereal sq6 = fem::double0;
  doublereal cq1 = fem::double0;
  doublereal cq2 = fem::double0;
  doublereal cq3 = fem::double0;
  doublereal cl1 = fem::double0;
  doublereal cl2 = fem::double0;
  doublereal cl3 = fem::double0;
  doublereal cers = fem::double0;
  doublereal cerc = fem::double0;
  doublereal cerlq = fem::double0;
  doublereal thrs = fem::double0;
  doublereal dd1 = fem::double0;
  doublereal dd2 = fem::double0;
  doublereal dd3 = fem::double0;
  doublereal u1 = fem::double0;
  doublereal alph = fem::double0;
  doublereal beta = fem::double0;
  doublereal cno = fem::double0;
  doublereal t11 = fem::double0;
  doublereal t12 = fem::double0;
  doublereal t13 = fem::double0;
  doublereal t21 = fem::double0;
  doublereal t22 = fem::double0;
  doublereal t23 = fem::double0;
  doublereal t31 = fem::double0;
  doublereal ti11 = fem::double0;
  doublereal ti12 = fem::double0;
  doublereal ti13 = fem::double0;
  doublereal ti21 = fem::double0;
  doublereal ti22 = fem::double0;
  doublereal ti23 = fem::double0;
  doublereal ti31 = fem::double0;
  doublereal ti32 = fem::double0;
  doublereal ti33 = fem::double0;
  doublereal ai11 = fem::double0;
  doublereal ai12 = fem::double0;
  doublereal ai13 = fem::double0;
  doublereal ai21 = fem::double0;
  doublereal ai22 = fem::double0;
  doublereal ai23 = fem::double0;
  doublereal ai31 = fem::double0;
  doublereal ai32 = fem::double0;
  doublereal ai33 = fem::double0;
  doublereal hmaxn = fem::double0;
  doublereal hold = fem::double0;
  integer niter = fem::int0;
  integer ipa = fem::int0;
  integer j = fem::int0;
  integer k = fem::int0;
  doublereal faccon = fem::double0;
  doublereal cfac = fem::double0;
  integer nsing = fem::int0;
  doublereal xold = fem::double0;
  integer nrsol = fem::int0;
  doublereal xosol = fem::double0;
  doublereal xsol = fem::double0;
  integer nsolu = fem::int0;
  doublereal hsol = fem::double0;
  integer n2 = fem::int0;
  integer n3 = fem::int0;
  doublereal hhfac = fem::double0;
  doublereal alopt = fem::double0;
  integer mujacp = fem::int0;
  integer md = fem::int0;
  integer mm = fem::int0;
  integer j1 = fem::int0;
  integer lbeg = fem::int0;
  integer lend = fem::int0;
  integer mujacj = fem::int0;
  integer l = fem::int0;
  doublereal ysafe = fem::double0;
  doublereal delt = fem::double0;
  bool caljac = fem::bool0;
  bool calhes = fem::bool0;
  integer jlflag = fem::int0;
  doublereal a1 = fem::double0;
  doublereal c3q = fem::double0;
  doublereal c1q = fem::double0;
  doublereal c2q = fem::double0;
  doublereal ak1 = fem::double0;
  doublereal ak2 = fem::double0;
  doublereal ak3 = fem::double0;
  doublereal z1i = fem::double0;
  doublereal z2i = fem::double0;
  doublereal z3i = fem::double0;
  bool caljacl = fem::bool0;
  doublereal x1 = fem::double0;
  doublereal x2 = fem::double0;
  doublereal x3 = fem::double0;
  integer il = fem::int0;
  integer ll = fem::int0;
  integer nl = fem::int0;
  integer is = fem::int0;
  doublereal xact = fem::double0;
  doublereal x13 = fem::double0;
  doublereal s1 = fem::double0;
  doublereal s2 = fem::double0;
  doublereal s3 = fem::double0;
  integer ile = fem::int0;
  integer kk = fem::int0;
  integer ik = fem::int0;
  integer jk = fem::int0;
  doublereal fac1 = fem::double0;
  doublereal alphn = fem::double0;
  doublereal betan = fem::double0;
  integer ier = fem::int0;
  doublereal xph = fem::double0;
  integer newt = fem::int0;
  doublereal theta = fem::double0;
  doublereal ak = fem::double0;
  doublereal acont3 = fem::double0;
  doublereal a2 = fem::double0;
  integer inrej = fem::int0;
  doublereal dbp = fem::double0;
  doublereal xx = fem::double0;
  doublereal a3 = fem::double0;
  doublereal dyno = fem::double0;
  doublereal denom = fem::double0;
  doublereal dynold = fem::double0;
  doublereal thq = fem::double0;
  doublereal thqold = fem::double0;
  doublereal dyth = fem::double0;
  doublereal hp = fem::double0;
  doublereal qnewt = fem::double0;
  doublereal f1i = fem::double0;
  doublereal f2i = fem::double0;
  doublereal f3i = fem::double0;
  doublereal hnewt = fem::double0;
  doublereal fij = fem::double0;
  doublereal dl1 = fem::double0;
  doublereal dl2 = fem::double0;
  doublereal dl3 = fem::double0;
  doublereal xl = fem::double0;
  doublereal dcoli1 = fem::double0;
  doublereal dcoli2 = fem::double0;
  doublereal dcoli3 = fem::double0;
  doublereal fjlk = fem::double0;
  integer iki = fem::int0;
  doublereal ai11h = fem::double0;
  doublereal ai12h = fem::double0;
  doublereal ai13h = fem::double0;
  doublereal ai21h = fem::double0;
  doublereal ai22h = fem::double0;
  doublereal ai23h = fem::double0;
  doublereal ai31h = fem::double0;
  doublereal ai32h = fem::double0;
  doublereal ai33h = fem::double0;
  integer i1 = fem::int0;
  doublereal serr = fem::double0;
  doublereal cerr = fem::double0;
  doublereal fac = fem::double0;
  doublereal err = fem::double0;
  doublereal quot = fem::double0;
  doublereal hnew = fem::double0;
  doublereal cerr2 = fem::double0;
  bool repeat = fem::bool0;
  doublereal hacc = fem::double0;
  doublereal facgus = fem::double0;
  doublereal yi = fem::double0;
  doublereal he = fem::double0;
  doublereal xlr = fem::double0;
  bool project = fem::bool0;
  doublereal posneg = fem::double0;
  doublereal xeps = fem::double0;
  doublereal hopt = fem::double0;
  doublereal qt = fem::double0;
  static const char * format_979 = "(' EXIT OF RADAR5 AT X=',e18.4)";
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
  cmn.io.open(8, "radar5.log");
  cmn.io.rewind(8);
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
  FEM_DO_SAFE(i, 1, nlags)
  {
    ipast(i + 2 * n) = 1;
  }
  x0b = x;
  FEM_DO_SAFE(i, 1, ngrid)
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
      FEM_DO_SAFE(i, 2, n)
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
  sq6 = fem::dsqrt(6.e0);
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
  u1 = (6.e0 + fem::pow(81.e0, (1.e0 / 3.e0)) - fem::pow(9.e0, (1.e0 / 3.e0))) / 30.e0;
  alph = (12.e0 - fem::pow(81.e0, (1.e0 / 3.e0)) + fem::pow(9.e0, (1.e0 / 3.e0))) / 60.e0;
  beta = (fem::pow(81.e0, (1.e0 / 3.e0)) + fem::pow(9.e0, (1.e0 / 3.e0))) * fem::dsqrt(3.e0) / 60.e0;
  cno = fem::pow2(alph) + fem::pow2(beta);
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
  hmaxn = fem::min(hmax, xend - x);
  if (h <= 10.e0 * uround)
    {
      h = 1.0e-6;
    }
  h = fem::min(h, hmaxn);
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
  FEM_DO_SAFE(i, 0, mxst - 1)
  {
    past(1 + idif * i) = x;
  }
  ipa = (mxst - 1) * idif + 1;
  FEM_DO_SAFE(j, 1, nrds)
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
      FEM_DO_SAFE(i, 1, n)
      {
        scal(i) = atol(1) + rtol(1) * fem::abs(y(i));
      }
    }
  else
    {
      FEM_DO_SAFE(i, 1, n)
      {
        scal(i) = atol(i) + rtol(i) * fem::abs(y(i));
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
          md = fem::min(mbjac, m2);
          FEM_DO_SAFE(mm, 1, m1 / m2 + 1)
          {
            FEM_DO_SAFE(k, 1, md)
            {
              j = k + (mm - 1) * m2;
            statement_12:
              f1(j) = y(j);
              f2(j) = fem::dsqrt(uround * fem::max(1.e-5, fem::abs(y(j))));
              y(j) += f2(j);
              j += md;
              if (j <= mm * m2)
                {
                  goto statement_12;
                }
              fcn(n, x, y, cont, arglag, phi, rpar, ipar, past, ipast, nrds);
              j = k + (mm - 1) * m2;
              j1 = k;
              lbeg = fem::max(1, j1 - mujac) + m1;
            statement_14:
              lend = fem::min(m2, j1 + mljac) + m1;
              y(j) = f1(j);
              mujacj = mujacp - j1 - m1;
              FEM_DO_SAFE(l, lbeg, lend)
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
          FEM_DO_SAFE(i, 1, n)
          {
            ysafe = y(i);
            delt = fem::dsqrt(uround * fem::max(1.e-5, fem::abs(ysafe)));
            y(i) = ysafe + delt;
            fcn(n, x, y, cont, arglag, phi, rpar, ipar, past, ipast, nrds);
            FEM_DO_SAFE(j, m1 + 1, n)
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
      FEM_DO_SAFE(i, 1, n)
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
      FEM_DO_SAFE(i, 1, n)
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
          FEM_DO_SAFE(i, 1, n)
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
      FEM_DO_SAFE(il, 1, nlags)
      {
        xlag(1, il) = 0.e0;
        xlag(2, il) = 0.e0;
        xlag(3, il) = 0.e0;
        icoun(1, il) = 0;
        icoun(2, il) = 0;
        icoun(3, il) = 0;
      }
      //C ---  LOOP ON LAG TERMS
      FEM_DO_SAFE(il, 1, nlags)
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
              FEM_DO_SAFE(l, 1, nlags)
              {
                nl = 0;
                FEM_DO_SAFE(i, 1, njacl)
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
          FEM_DO_SAFE(il, 1, nlags)
          {
            FEM_DO_SAFE(is, 1, 3)
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
                      write(6, star),
                        " WARNING!: ADVANCED ARGUMENTS ARE USED AT X= ", xact;
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
                alopt = (-1.e0 + s1) * s1 * (-13.e0 - 7.e0 * fem::sqrt(6.e0) + 5.e0 * (2.e0 + 3.e0 * fem::sqrt(6.e0)) * s1);
              }
            if (icoun(2, il) == 1)
              {
                s2 = dim(xlag(2, il), x) / h;
                alopt = alopt - (-1 + s2) * s2 * (13.e0 - 7.e0 * fem::sqrt(6.e0) + 5.e0 * (-2.e0 + 3.e0 * fem::sqrt(6.e0)) * s2);
              }
            if (icoun(3, il) == 1)
              {
                s3 = dim(xlag(3, il), x) / h;
                alopt += s3 * (1.e0 - 8.e0 * s3 + 10.e0 * fem::pow2(s3));
              }
            alopt = alopt / 9.e0;
            //C
            //C         OPTIMAL COEFFICIENT (W.R.T. FROBENIUS NORM)
            //C         JACLAG ~= ALOPT*I
            //C
            //C         ACTIVATES IF ALOPT DIFFERENT FROM ZERO
            if (fem::abs(alopt) >= 1.e-8)
              {
                nl = ils(2 * il - 1);
                ile = ils(2 * il);
                FEM_DO_SAFE(k, 1, nl)
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
  decomr(n, _fjac, ldjac, _fmas, ldmas, mlmas, mumas, m1, m2, nm1,
         fac1, _e1, lde1, ip1, ier, ijob, calhes, iphes);
  if (ier != 0)
    {
      goto statement_78;
    }
  decomc(n, _fjac, ldjac, _fmas, ldmas, mlmas, mumas, m1, m2, nm1,
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
  if (0.1e0 * h <= fem::abs(x) * uround)
    {
      goto statement_177;
    }
  if (index2)
    {
      FEM_DO_SAFE(i, nind1 + 1, nind1 + nind2)
      {
        scal(i) = scal(i) / hhfac;
      }
    }
  if (index3)
    {
      FEM_DO_SAFE(i, nind1 + nind2 + 1, nind1 + nind2 + nind3)
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
  faccon = fem::pow(fem::max(faccon, uround), 0.8e0);
  theta = fem::abs(thet);
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
      FEM_DO_SAFE(j, 1, nrds)
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
  FEM_DO_SAFE(i, 1, n)
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
      FEM_DO_SAFE(i, 1, n)
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
  FEM_DO_SAFE(i, 1, n)
  {
    a1 = z1(i);
    a2 = z2(i);
    a3 = z3(i);
    z1(i) = ti11 * a1 + ti12 * a2 + ti13 * a3;
    z2(i) = ti21 * a1 + ti22 * a2 + ti23 * a3;
    z3(i) = ti31 * a1 + ti32 * a2 + ti33 * a3;
  }
  //C
  slvrad(n, _fjac, ldjac, mljac, mujac, _fmas, ldmas, mlmas, mumas, m1,
         m2, nm1, fac1, alphn, betan, _e1, _e2r, _e2i, lde1, z1, z2, z3, f1,
         f2, f3, cont, ip1, ip2, iphes, ier, ijob);
  nsol++;
  newt++;
  //C ---       NORM OF DY
  dyno = 0.e0;
  FEM_DO_SAFE(i, 1, n)
  {
  }
  FEM_DO_SAFE(i, 1, n)
  {
    denom = scal(i);
    dyno += fem::pow2((z1(i) / denom)) + fem::pow2((z2(i) / denom)) + fem::pow2((z3(i) / denom));
  }
  dyno = fem::dsqrt(dyno / n3);
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
          theta = fem::sqrt(thq * thqold);
        }
      thqold = thq;
      inrej = 0;
      //C --- 1
      if (theta < 0.99e0)
        {
          faccon = theta / (1.0e0 - theta);
          dyth = faccon * dyno * fem::pow(theta, (nit - 1 - newt)) / fnewt;
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
              qnewt = fem::dmax1(1.0e-4, fem::dmin1(20.0e0, dyth));
              hhfac = .8e0 * fem::pow(qnewt, (-1.0e0 / (4.0e0 + nit - 1 - newt)));
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
                  qnewt = fem::dmax1(1.0e-4, fem::dmin1(20.0e0, dyth));
                  hhfac = .8e0 * fem::pow(qnewt, (-1.0e0 / (4.0e0 + nit - 1 - newt)));
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
  dynold = fem::max(dyno, uround);
  FEM_DO_SAFE(i, 1, n)
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
      if (fem::abs(h - hnewt) / hnewt >= fem::max(btol, rtolm * 1.e-2))
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
  FEM_DO_SAFE(i, 1, n)
  {
    FEM_DO_SAFE(j, 1, n)
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
  FEM_DO_SAFE(il, 1, nlags)
  {
    FEM_DO_SAFE(i, 1, 3)
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
          FEM_DO_SAFE(k, 1, nl)
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
      FEM_DO_SAFE(i1, 1, n)
      {
        FEM_DO_SAFE(j1, 1, n)
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
      FEM_DO_SAFE(i1, 1, n)
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
  if (0.1e0 * h <= fem::abs(x) * uround)
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
  faccon = fem::pow(fem::max(faccon, uround), 0.8e0);
  theta = fem::abs(thet);
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
      FEM_DO_SAFE(j, 1, nrds)
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
  FEM_DO_SAFE(i1, 1, n)
  {
    cont(i1) = y(i1) + z1(i1);
  }
  fcn(n, x + c1 * h, cont, f1, arglag, phi, rpar, ipar, past, ipast, nrds);
  FEM_DO_SAFE(i1, 1, n)
  {
    cont(i1) = y(i1) + z2(i1);
  }
  fcn(n, x + c2 * h, cont, f2, arglag, phi, rpar, ipar, past, ipast, nrds);
  FEM_DO_SAFE(i1, 1, n)
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
      FEM_DO_SAFE(i1, 1, n)
      {
        FEM_DO_SAFE(j1, 1, n)
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
      FEM_DO_SAFE(i1, 1, n)
      {
        zl(i1) = ai11h * z1(i1) + ai12h * z2(i1) + ai13h * z3(i1);
        zl(n + i1) = ai21h * z1(i1) + ai22h * z2(i1) + ai23h * z3(i1);
        zl(2 * n + i1) = ai31h * z1(i1) + ai32h * z2(i1) + ai33h * z3(i1);
      }
    }
  //C
  FEM_DO_SAFE(i1, 1, n)
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
  FEM_DO_SAFE(i, 1, n)
  {
    denom = scal(i);
    dyno += fem::pow2((zl(i) / denom)) + fem::pow2((zl(i + n) / denom)) + fem::pow2((zl(i + 2 * n) / denom));
  }
  dyno = fem::dsqrt(dyno / n3);
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
          theta = fem::sqrt(thq * thqold);
        }
      thqold = thq;
      inrej = 0;
      //C --- 1
      if (theta < 0.99e0)
        {
          faccon = theta / (1.0e0 - theta);
          dyth = faccon * dyno * fem::pow(theta, (nit - 1 - newt)) / fnewt;
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
          qnewt = fem::dmax1(1.0e-4, fem::dmin1(20.0e0, dyth));
          hhfac = .8e0 * fem::pow(qnewt, (-1.0e0 / (4.0e0 + nit - 1 - newt)));
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
  dynold = fem::max(dyno, uround);
  //C --        UPDATE OF Z VALUES
  FEM_DO_SAFE(i1, 1, n)
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
  estrad(n, _fjac, ldjac, mljac, mujac, _fmas, ldmas, mlmas, mumas, h,
         u1, dd1, dd2, dd3, cl1, cl3, cq1, cq2, cq3, cerlq, fcn, nfcn, y0,
         y, ijob, x, m1, m2, nm1, _e1, lde1, alpha, z1, z2, z3, cont, f1,
         f2, f3, ip1, iphes, scal, serr, cerr, first, reject, fac1,
         arglag, phi, rpar, ipar, iout, past, ipast, nrds, jlflag, ieflag);
  fac = fem::min(safe, cfac / (newt + 2 * nit));
  //C
  if (first)
    {
      //C ------------------------------------------------------------
      //C ---  AFTER A GRID OR BREAKING POINT
      //C ---------------------------------------------
      err = serr;
      //C ---  WE REQUIRE .2<=HNEW/H<=8.
      quot = fem::max(facr, fem::min(facl, fem::pow(err, 0.25e0) / fac));
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
      quot = fem::max(facr, fem::min(facl, fem::pow(err, .25e0) / fac));
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
                  facgus = (hacc / h) * fem::pow((fem::pow2(err) / erracc), 0.25e0) / safe;
                  facgus = fem::max(facr, fem::min(facl, facgus));
                  quot = fem::max(quot, facgus);
                  hnew = h / quot;
                }
              else
                {
                  flagus = true;
                }
            }
          hacc = h;
        }
      erracc = fem::max(1.0e-2, err);
      //C        ERRACC=ERR
      xold = x;
      hold = h;
      x = xph;
      //C ---    AGGIORNAMENTO DELLA SOLUZIONE
      FEM_DO_SAFE(i, 1, n)
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
      FEM_DO_SAFE(i, 1, lrc)
      {
        ucont(i) = cont(i);
      }
      ucont(lrc + 1) = x;
      ucont(lrc + 2) = h;
      //C ---    FOR POSSIBLE SEARCH OF BREAKING POINTS
      //C ------------------------------------------------------------------
      //C ---    STEP IS ACCEPTED> DENSE OUTPUT IS STORED IN PAST
      //C ---
      FEM_DO_SAFE(j, 1, nrds)
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
              he = fem::dmax1(h / 1.e4, 10.e0 * uround);
              //C --------------------
              left = true;
              //C --------------------
              //C ---
              //C ---       EULER STEP
              fcn(n, x, y, f2, arglag, phi, rpar, ipar, past, ipast, nrds);
              if (neutral)
                {
                  FEM_DO_SAFE(i, 1, n - ndimn)
                  {
                    z2(i) = y(i) + he * f2(i);
                  }
                  FEM_DO_SAFE(i, 1, ndimn)
                  {
                    z2(n - ndimn + i) = f2(ipast(nrds + i)) + he * f2(n - ndimn + i);
                  }
                }
              else
                {
                  FEM_DO_SAFE(i, 1, n)
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
                  FEM_DO_SAFE(i, 1, n - ndimn)
                  {
                    z3(i) = y(i) + he * f3(i);
                  }
                  FEM_DO_SAFE(i, 1, ndimn)
                  {
                    z3(n - ndimn + i) = f3(ipast(nrds + i)) + he * f3(n - ndimn + i);
                  }
                }
              else
                {
                  FEM_DO_SAFE(i, 1, n)
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
                          write(6, star), " WARNING!: SOLUTION DOES NOT EXIST AT X= ", x;
                        }
                      else
                        {
                          write(6, star), " WARNING!: SOLUTION IS  NOT UNIQUE AT X= ", x;
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
                      FEM_DO_SAFE(j, 1, ndimn)
                      {
                        y(n - ndimn + j) = f2(ipast(nrds + j));
                      }
                    }
                  else
                    {
                      FEM_DO_SAFE(j, 1, ndimn)
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
          FEM_DO_SAFE(i, 1, n)
          {
            scal(i) = atol(1) + rtol(1) * fem::abs(y(i));
          }
        }
      else
        {
          FEM_DO_SAFE(i, 1, n)
          {
            scal(i) = atol(i) + rtol(i) * fem::abs(y(i));
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
      xeps = posneg * (fem::abs(x) + 1.0e0) * 100 * uround;
      fcn(n, x + xeps, y, y0, arglag, phi, rpar, ipar, past, ipast, nrds);
      if (first)
        {
          FEM_DO_SAFE(i, 1, ndimn)
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
              if (fem::abs(xend - x) <= (h * 1.e-2))
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
              hnew = fem::min(hnew, h);
            }
        }
      hnew = fem::min(hnew, hmaxn);
      hopt = fem::min(h, hnew);
      if (reject)
        {
          hnew = fem::min(hnew, h);
        }
      reject = false;
      if ((x + hnew / quot1 - xend) >= 0.e0)
        {
          h = xend - x;
          if (h < 0.e0)
            {
              write(6, star), "ERROR!: NEGATIVE STEPSIZE! AT ";
              write(6, star), "X > XEND = ", x, xend;
              FEM_STOP(0);
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
  write(6, format_979), x;
  write(6, star), " MATRIX IS REPEATEDLY SINGULAR, IER=", ier;
  idid = -4;
  goto statement_980;
statement_177:
  write(6, format_979), x;
  write(6, star), " STEP SIZE TOO SMALL, H=", h;
  idid = -3;
  goto statement_980;
statement_178:
  write(6, format_979), x;
  write(6, star), " MORE THAN NMAX =", nmax, "STEPS ARE NEEDED";
  idid = -2;
  goto statement_980;
//C --- EXIT CAUSED BY SOLOUT
statement_179:
  write(6, format_979), x;
  idid = 2;
//C --- RETURN LABEL
statement_980:
  write(6, star), ibp, " COMPUTED BREAKING POINTS: ";
  write(8, star), "BREAKING POINTS: ";
  FEM_DO_SAFE(i, 1, ibp)
  {
    write(8, star), bpv(i);
  }
  write(8, star), " -------------- ";
  cmn.io.close(8);
  //C --- DEALLOCATION OF THE MEMORY
  FEM_THROW_UNHANDLED(
    "executable deallocate: deallocate(z1,z2,z3,y0,scal,f1,f2,f3)");
  FEM_THROW_UNHANDLED("executable deallocate: deallocate(bpv)");
  FEM_THROW_UNHANDLED("executable deallocate: deallocate(fjac,zl)");
  if (implct)
    {
      FEM_THROW_UNHANDLED("executable deallocate: if(implct)deallocate(fmas)");
    }
  FEM_THROW_UNHANDLED("executable deallocate: deallocate(ip1,ip2,iphes)");
  FEM_THROW_UNHANDLED("executable deallocate: deallocate(e1,e2r,e2i)");
  FEM_THROW_UNHANDLED("executable deallocate: deallocate(past)");
  if (nlags > 0)
    {
      FEM_THROW_UNHANDLED("executable deallocate: deallocate(fjacs,fjaclag)");
      FEM_THROW_UNHANDLED(
        "executable deallocate: deallocate(ivl,ive,ivc,ils,icoun)");
      if (iswjl != 1)
        {
          FEM_THROW_UNHANDLED(
            "executable deallocate: if(iswjl.ne.1)deallocate(ipj,fjacl,xlag)");
        }
    }
  FEM_THROW_UNHANDLED("executable deallocate: deallocate(cont,ucont)");
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
void radar5::radar5(common & cmn,
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
                    integer const & nrdens)
{
  common_write write(cmn);
  doublereal & uround = cmn.uround;
  doublereal & hmax = cmn.hmax;
  integer & idif = cmn.idif;
  integer & mxst = cmn.mxst;
  //
  integer nn = fem::int0;
  integer nfcn = fem::int0;
  integer njac = fem::int0;
  integer nstep = fem::int0;
  integer naccpt = fem::int0;
  integer nrejct = fem::int0;
  integer ndec = fem::int0;
  integer nsol = fem::int0;
  bool arret = fem::bool0;
  integer ieflag = fem::int0;
  integer ngrid = fem::int0;
  integer ndimn = fem::int0;
  integer lipast = fem::int0;
  integer nrds = fem::int0;
  integer i = fem::int0;
  integer lrpast = fem::int0;
  integer iswjl = fem::int0;
  doublereal expm = fem::double0;
  doublereal quot = fem::double0;
  integer nmax = fem::int0;
  integer nit = fem::int0;
  bool startn = fem::bool0;
  integer nind1 = fem::int0;
  integer nind2 = fem::int0;
  integer nind3 = fem::int0;
  bool pred = fem::bool0;
  integer m1 = fem::int0;
  integer m2 = fem::int0;
  integer nm1 = fem::int0;
  doublereal safe = fem::double0;
  doublereal thet = fem::double0;
  doublereal tolst = fem::double0;
  doublereal fnewt = fem::double0;
  doublereal quot1 = fem::double0;
  doublereal quot2 = fem::double0;
  doublereal xuro = fem::double0;
  integer igrid = fem::int0;
  doublereal facl = fem::double0;
  doublereal facr = fem::double0;
  doublereal alpha = fem::double0;
  doublereal tckbp = fem::double0;
  bool implct = fem::bool0;
  bool neutral = fem::bool0;
  bool jband = fem::bool0;
  integer ldjac = fem::int0;
  integer lde1 = fem::int0;
  integer ldmas = fem::int0;
  integer ijob = fem::int0;
  integer ldmas2 = fem::int0;
  integer nfull = fem::int0;
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
  cmn.flags = false;
  cmn.flagn = false;
  //C
  if (iout == 1)
    {
      write(6, star), "STARTING INTEGRATION...";
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
      write(6, star), "NUMBER OF PRESCRIBED GRID POINTS: ", ngrid;
    }
  //C ------- NDIMN   NUMBER OF COMPONENTS OF A NEUTRAL PROBLEM
  if (imas == 2)
    {
      if (iwork(16) == 0)
        {
          write(6, star), "NUMBER OF Y COMPONENTS HAS TO BE SPECIFIED";
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
          write(6, star), " CURIOUS INPUT IWORK(15)=", iwork(15);
        }
      arret = true;
    }
  else
    {
      nrds = nrdens;
    }
  if (nrds == n)
    {
      FEM_DO_SAFE(i, 1, nrds)
      {
        ipast(i) = i;
      }
    }
  if (iout == 1)
    {
      write(6, star), "NUMBER OF DELAYED COMPONENTS: ", nrds;
    }
  //C ------- LRPAST   DIMENSION OF VECTOR PAST
  mxst = iwork(12);
  //C ------- CONTROL OF LENGTH OF PAST  -------
  if (mxst < 1)
    {
      if (iout > 0)
        {
          write(6, star), " INSUFFICIENT STORAGE FOR PAST, MIN. LRPAST=", 1;
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
          write(6, star), " COEFFICIENTS HAVE 20 DIGITS, UROUND=", work(1);
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
          write(6, star), " TOLERANCES ARE TOO SMALL";
          arret = true;
        }
      else
        {
          quot = atol(1) / rtol(1);
          rtol(1) = 0.1e0 * fem::pow(rtol(1), expm);
          atol(1) = rtol(1) * quot;
        }
    }
  else
    {
      FEM_DO_SAFE(i, 1, n)
      {
        if (atol(i) <= 0.e0 || rtol(i) <= 10.e0 * uround)
          {
            write(6, star), " TOLERANCES(", i, ") ARE TOO SMALL";
            arret = true;
          }
        else
          {
            quot = atol(i) / rtol(i);
            rtol(i) = 0.1e0 * fem::pow(rtol(i), expm);
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
          write(6, star), " WRONG INPUT IWORK(2)=", iwork(2);
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
          write(6, star), " CURIOUS INPUT IWORK(3)=", iwork(3);
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
      write(6, star), " CURIOUS INPUT FOR IWORK(5,6,7)=", nind1, nind2, nind3;
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
      write(6, star), " CURIOUS INPUT FOR IWORK(9,10)=", m1, m2;
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
          write(6, star), " CURIOUS INPUT FOR WORK(2)=", work(2);
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
          write(6, star), " CURIOUS INPUT FOR WORK(3)=", work(3);
          arret = true;
        }
    }
  //C
  //C ---> FNEWT : STOPPING CRITERION FOR NEWTON'S METHOD, USUALLY CHOSEN <1. <---
  tolst = rtol(1);
  if (work(4) == 0.e0)
    {
      fnewt = fem::max(10 * uround / tolst, fem::min(0.03e0, fem::pow(tolst,
                                                                      0.5e0)));
    }
  else
    {
      fnewt = work(4);
      if (fnewt <= uround / tolst)
        {
          write(6, star), " CURIOUS INPUT FOR WORK(4)=", work(4);
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
      write(6, star), " CURIOUS INPUT FOR WORK(5,6)=", quot1, quot2;
      arret = true;
    }
  //C -------------------------------------------------------
  //C
  //C ---->    GRID WITH DISCONTINUITIES  <----
  xuro = 100 * uround * fem::abs(xend);
  if (ngrid > 0)
    {
      if (grid(ngrid) - xend >= xuro)
        {
          if (iout > 0)
            {
              write(6, star), " GRID(NGRID) HAS TO BE <= XEND";
            }
          arret = true;
        }
      if (fem::abs(grid(ngrid) - xend) >= xuro)
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
      FEM_DO_SAFE(i, 1, ngrid)
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
      write(6, star), " CURIOUS INPUT WORK(8,9)=", work(8), work(9);
      arret = true;
    }
  //C ------->  PARAMETER FOR THE CONTROL OF DENSE OUTPUT <-------
  alpha = work(10);
  if (alpha < 0.e0 || alpha > 1.e0)
    {
      write(6, star), " CURIOUS INPUT WORK(10)=", work(10);
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
          write(6, star),
            "BANDWITH OF \"MAS\" NOT SMALLER THAN BANDWITH OF \"JAC\"";
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
  ldmas2 = fem::max(1, ldmas);
  //C ------ HESSENBERG OPTION ONLY FOR EXPLICIT EQU. WITH FULL JACOBIAN
  if ((implct || jband) && ijob == 7)
    {
      write(6, star),
        " HESSENBERG OPTION ONLY FOR EXPLICIT EQUATIONS WITH FULL JACOBIAN";
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
  write(6, star), "INTEGRATION...";
  //C -------- CALL TO CORE INTEGRATOR ------------
  radcor(cmn, n, x, y, xend, h, fcn, phi, arglag, rtol, atol, itol, jac,
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
      rtol(1) = fem::pow((10.0e0 * rtol(1)), expm);
      atol(1) = rtol(1) * quot;
    }
  else
    {
      FEM_DO_SAFE(i, 1, n)
      {
        quot = atol(i) / rtol(i);
        rtol(i) = fem::pow((10.0e0 * rtol(i)), expm);
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
void radar5::lagr5(common & cmn,
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
                   integer const & nrds)
{
  common_write write(cmn);
  bool & first = cmn.first;
  bool & bpd = cmn.bpd;
  doublereal & bpp = cmn.bpp;
  integer & ilbp = cmn.ilbp;
  bool & left = cmn.left;
  doublereal & x0b = cmn.x0b;
  doublereal & uround = cmn.uround;
  integer & iact = cmn.iact;
  integer & idif = cmn.idif;
  integer & mxst = cmn.mxst;
  //
  doublereal xlag = fem::double0;
  doublereal compar = fem::double0;
  doublereal epsact = fem::double0;
  integer ipa = fem::int0;
  integer inext = fem::int0;
  doublereal xright = fem::double0;
  doublereal h = fem::double0;
  integer iprev = fem::int0;
  integer iposb = fem::int0;
  doublereal epsilon = fem::double0;
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
  compar = uround * fem::max(fem::abs(xlag), fem::abs(x0b));
  epsact = 10.e0 * compar;
  if (iact > 1)
    {
      epsact = fem::dmax1(past(iact - 1) - 2, epsact);
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
          if (fem::abs(xlag - x0b) <= epsact)
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
          else if (fem::abs(xlag - bpp) <= epsact)
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
      write(6, star), " MEMORY FULL, MXST = ", mxst;
      cmn.irtrn = -1;
      FEM_STOP(0);
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
      if (fem::abs(bpp - past(ipos)) <= 10.e0 * uround)
        {
          iposb = ipos;
        }
      else if (fem::abs(bpp - past(inext)) <= 10.e0 * uround)
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
          epsilon = fem::dmin1(past(iposb + idif) - past(iposb), past(
                                                                   iposb)
                                                                   - past(iposb - idif));
        }
      epsilon = fem::dmax1(epsilon * 1.e-2, epsact);
      if (fem::abs(xlag - bpp) > epsilon)
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
doublereal radar5::ylagr5(common & cmn,
                      integer const & ic,
                      doublereal const & theta,
                      integer const & ipos,
                      PHI & phi,
                      float const & rpar,
                      integer const & ipar,
                      CVectorCore< doublereal > & past,
                      CVectorCore< integer > & ipast,
                      integer const & nrds)
{
  doublereal return_value = fem::double0;
  common_write write(cmn);
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
  integer j = fem::int0;
  FEM_DO_SAFE(j, 1, nrds)
  {
    if (ipast(j) == ic)
      {
        i = j;
      }
  }
  if (i == 0)
    {
      write(6, star), " NO DENSE OUTPUT AVAILABLE FOR COMP.", ic;
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
doublereal radar5::dlagr5(common & cmn,
                      integer const & ic,
                      doublereal const & theta,
                      integer const & ipos,
                      PHI & phi,
                      float const & rpar,
                      integer const & ipar,
                      CVectorCore< doublereal > & past,
                      CVectorCore< integer > & ipast,
                      integer const & nrds)
{
  doublereal return_value = fem::double0;
  common_write write(cmn);
  // COMMON constn
  doublereal & c1m1 = cmn.c1m1;
  doublereal & c2m1 = cmn.c2m1;
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
  integer j = fem::int0;
  FEM_DO_SAFE(j, 1, nrds)
  {
    if (ipast(j) == ic)
      {
        i = j;
      }
  }
  if (i == 0)
    {
      write(6, star), " NO DENSE OUTPUT AVAILABLE FOR COMP.", ic;
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
doublereal radar5::dontr5(common & cmn,
                      integer const & i,
                      integer const & n,
                      doublereal const & x,
                      const CVectorCore< doublereal > & cont,
                      doublereal const & xsol,
                      doublereal const & hsol)
{
  doublereal return_value = fem::double0;
  // COMMON constn
  doublereal & c1m1 = cmn.c1m1;
  doublereal & c2m1 = cmn.c2m1;
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

void radar5::decomr(integer const & n,
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
                    const CVectorCore< integer > & iphes)
{}

void radar5::decomc(integer const & n,
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
                    integer const & ijob)
{}

void radar5::slvrad(integer const & n,
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
                    integer const & ijob)
{}

void radar5::estrad(integer const & n,
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
                    integer const & ieflag)
{}

// Matrix Triangularization by Gaussian Elimination
// integer dec_(integer n, doublereal **A, integer *ip);
int radar5::dec(const integer & n,
                 const integer & ldjac,
                 CMatrix< doublereal > & fjacl,
                 CVectorCore< integer > & ipj,
                 integer & ier)
{
  return dec_(&n, &ldjac, fjacl.array(), ipj.array(), &ier);
}

// Solution of linear system A*x = b
// void sol_(integer n, doublereal **A, doublereal *b, integer *ip);
int radar5::sol(const integer & n,
                 const integer & ldjac,
                 const CMatrix< doublereal > & fjacl,
                 CVectorCore< doublereal > & zl,
                 const CVectorCore< integer > & ipj)
{
  return sol_(&n, &ldjac, fjacl.array(), zl.array(), ipj.array());
}
