/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CLsodaMethod.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:03 $
   End CVS Header */

/*
From tam@dragonfly.wri.com Wed Apr 24 01:35:52 1991
Return-Path: <tam>
Date: Wed, 24 Apr 91 03:35:24 CDT
From: tam@dragonfly.wri.com
To: whitbeck@wheeler.wrc.unr.edu
Subject: lsoda.c
Cc: augenbau@sparc0.brc.uconn.edu
 
I'm told by Steve Nichols at Georgia Tech that you are interested in
a stiff integrator.  Here's a translation of the fortran code LSODA.
 
Please note
that there is no comment.  The interface is the same as the FORTRAN
code and I believe the documentation in LSODA will suffice.
As usual, a free software comes with no guarantee.
 
Hon Wah Tam
Wolfram Research, Inc.
tam@wri.com
 */

/*
  I have done some additions to lsoda.c . These were mainly to fill the
  gap of some features that were available in the fortran code and were
  missing in the C version.
 
  Changes are:
  * all messages printed by lsoda routines will start with
  a '\n' (instead of ending with one).
  * xsetf() was added so that user can control printing
  of messages by lsoda. xsetf should be called before
  calling lsoda: xsetf(0) switches printing off
  xsetf(1) swithces printing on (default)
  this implies one new global variable prfl (print flag).
  xsetf(0) will stop *any* printing by lsoda functions.
  Turning printing off means losing valuable information
  but will not scramble your stderr output; -)
  This function is part of the original FORTRAN version.
  * xsetf() and intdy() are now callable from outside the
  library as assumed in the FORTRAN version.
  * created lsoda.h that should be included in blocks
  calling functions in lsoda's library.
  * iwork5 can now have an extra value:
  0 - no extra printing (default)
  1 - print data on each method switch
  ->  2 - print useful information at *each* stoda
  step (one lsoda call has performs many stoda
  calls) and also data on each method switch
  note that a xsetf(0) call will prevent any printing even
  if iwork5 > 0.
  * hu, tn were made available as extern variables.
  * the variable ml has been renamed to _ml
 
  Pedro Mendes
 
  eMail:      INTERNET: prm@aber.ac.uk
  sMail:                Pedro Mendes,
  Dept. of Biological Sciences,
  University of Wales, Aberystwyth
  Dyfed, SY23 3DA,
  United Kingdom.
 */

/*
  Added a call to Sleep function and a global variable to hold
  the time to Sleep.                    Pedro Mendes 15/8/1996
 */

// #define DBL_EPSILON 2.2204460492503131e-16

#ifndef _ZTC
#ifdef Darwin
#include <alloc.h>
#else
#include <malloc.h>
#endif
#define mem_malloc malloc
#define mem_free free
#define mem_realloc realloc
#else
#include <stdlib.h>
#define MEM_DEBUG 1
#include "mem.h"
#endif

#include <stdio.h>
#include "mathematics.h"
#include <float.h>
#include <algorithm>
#include <assert.h>

// #define  COPASI_TRACE_CONSTRUCTION
#include "copasi.h"

#include "CTrajectoryMethod.h"
#include "utilities/utility.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "model/CCompartment.h"

#ifdef WIN32
#define min _cpp_min
#define max _cpp_max
#endif // WIN32

static const C_INT32 mord[3] = {0, 12, 5};

static const C_FLOAT64 sm1[13] =
  {
    0., 0.5, 0.575, 0.55, 0.45, 0.35, 0.25,
    0.2, 0.15, 0.1, 0.075, 0.05, 0.025
  };

/*
  The following are useful statistics.
 
  hu,
  h,
  tn,
  tolsf,
  tsw,
  nst,
  nfe,
  nje,
  nqu,
  nq,
  imxer,
  mused,
  meth
 */

CLsodaMethod::CLsodaMethod(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::deterministic, pParent),
    mpStateX(NULL),
    mY(NULL)
{
  addParameter("LSODA.RelativeTolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-012);
  addParameter("LSODA.AbsoluteTolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-006);
  addParameter("LSODA.AdamsMaxOrder",
               CCopasiParameter::UINT, (unsigned C_INT32) 12);
  addParameter("LSODA.BDFMaxOrder",
               CCopasiParameter::UINT, (unsigned C_INT32) 5);
  addParameter("LSODA.MaxStepsInternal",
               CCopasiParameter::UINT, (unsigned C_INT32) 10000);

#ifdef COPASI_DEBUG // We only want lsoda to output information while debuging.
  prfl = 1;
#else
  prfl = 0;
#endif

  illin = 0;
  init = 0;
  ntrep = 0;
  ixpr = 0;
  mesflg = 1;
  yh = NULL;
  wm = NULL;
  ewt = NULL;
  savf = NULL;
  acor = NULL;
  ipvt = NULL;
}

CLsodaMethod::CLsodaMethod(const CLsodaMethod & src,
                           const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent),
    mpStateX(NULL),
    mY(NULL)
{
#ifdef COPASI_DEBUG // We only want lsoda to output information while debuging.
  prfl = 1;
#else
  prfl = 0;
#endif

  illin = 0;
  init = 0;
  ntrep = 0;
  ixpr = 0;
  mesflg = 1;
  yh = NULL;
  wm = NULL;
  ewt = NULL;
  savf = NULL;
  acor = NULL;
  ipvt = NULL;
}

CLsodaMethod::~CLsodaMethod()
{
  pdelete(mpStateX);
  lsoda_freevectors();
}

const double CLsodaMethod::step(const double & deltaT)
{
  lsoda(mDim,                                   // number of variables
        mY - 1,                                 // the array of current concentrations
        // fortran style vector !!!
        &mTime,                                 // the current time
        mTime + deltaT,                         // the final time
        1,                                      // scalar error control
        (&mRtol) - 1,                           // relative tolerance array
        // fortran style vector !!!
        (&mAtol) - 1,                           // absolute tolerance array
        // fortran style vector !!!
        1,                                      // output by overshoot & interpolatation
        &mLsodaStatus,                          // the state control variable
        1,                                      // optional inputs are being used
        2,                                      // jacobian calculated internally
        0, 0, 0,                                // options left at default values
        mMaxSteps,                              // max iterations for each lsoda call
        0,                                      // another value left at the default
        mAdams,                                 // max order for Adams method
        mBDF,                                   // max order for BDF method
        0.0, 0.0, 0.0, 0.0); // more options left at default values

  if (mLsodaStatus == -1) mLsodaStatus = 2;

  if ((mLsodaStatus != 1) && (mLsodaStatus != 2) && (mLsodaStatus != -1))
    {
      lsoda_freevectors(); // freevectors is part of LSODA
      fatalError();
    }

  mpStateX->setTime(mTime);
  mpStateX->updateDependentNumbers();
  *mpCurrentState = *mpStateX;

  return deltaT; //TODO
}

const double CLsodaMethod::step(const double & deltaT,
                                const CState * initialState)
{
  /* Reset lsoda */
  lsoda_freevectors();
  mLsodaStatus = 1;

  /* Configure lsoda */
  mRtol = * (C_FLOAT64 *) getValue("LSODA.RelativeTolerance");
  mAtol = * (C_FLOAT64 *) getValue("LSODA.AbsoluteTolerance");
  mAdams = * (C_INT32 *) getValue("LSODA.AdamsMaxOrder");
  mBDF = * (C_INT32 *) getValue("LSODA.BDFMaxOrder");
  mMaxSteps = * (C_INT32 *) getValue("LSODA.MaxStepsInternal");

  /* Release previous state and make the initialState the current */
  pdelete(mpStateX);
  mpStateX = new CStateX(*initialState);

  mDim = mpStateX->getVariableNumberSize();
  mY = const_cast< C_FLOAT64 * >(mpStateX->getVariableNumberVector().array());
  mTime = mpStateX->getTime();
  mYdot.resize(mDim);

  return step(deltaT);
}

/*******************/
/* private methods */
/*******************/

/*
  free allocated vectors
 */

/* this function has to be called by the upper level function
   to clean up the dynamic memory used
 */
void CLsodaMethod::lsoda_freevectors(void)
{
  C_INT32 i, lenyh;
  if (yh != (C_FLOAT64**) NULL)
    {
      lenyh = 1 + std::max(mxordn, mxords);
      for (i = 1; i <= lenyh; i++)
        mem_free((void *) yh[i]);
      for (i = 1; i <= nyh; i++)
        mem_free((void *) wm[i]);
      mem_free((void *) yh);
      yh = (C_FLOAT64**) NULL;
      mem_free((void *) wm);
      wm = (C_FLOAT64**) NULL;
      mem_free((void *) ewt);
      ewt = (C_FLOAT64*) NULL;
      mem_free((void *) savf);
      savf = (C_FLOAT64*) NULL;
      mem_free((void *) acor);
      acor = (C_FLOAT64*) NULL;
      mem_free((void *) ipvt);
      ipvt = (C_INT32*) NULL;
    }
}     /*   end lsoda_freevectors   */

/* this function is empty so that lsoda() does not clean
   up the memory used by itself.
 */
void CLsodaMethod::freevectors(void)
{}

/*
  Terminate lsoda due to illegal input.
 */
void CLsodaMethod::terminate(C_INT32 *istate)
{
  if ((illin == 5) && prfl)
    {
      printf("\nlsoda -- repeated occurrence of illegal input\n");
      printf("         run aborted.. apparent infinite loop");
    }
  else
    {
      illin++;
      *istate = -3;
    }
}         /*   end terminate   */

/*
  Terminate lsoda due to various error conditions.
 */

void CLsodaMethod::terminate2(C_FLOAT64 *y,
                              C_FLOAT64 *t)
{
  C_INT32 i;

  yp1 = yh[1];
  for (i = 1; i <= n; i++)
    y[i] = yp1[i];
  *t = tn;
  illin = 0;
  freevectors();
  return;
}         /*   end terminate2   */

/*
  The following block handles all successful returns from lsoda.
  If itask != 1, y is loaded from yh and t is set accordingly.
  *Istate is set to 2, the illegal input counter is zeroed, and the
  optional outputs are loaded into the work arrays before returning.
 */

void CLsodaMethod::successreturn(C_FLOAT64 *y,
                                 C_FLOAT64 *t,
                                 C_INT32 itask,
                                 C_INT32 ihit,
                                 C_FLOAT64 tcrit,
                                 C_INT32 *istate)
{
  C_INT32 i;

  yp1 = yh[1];
  for (i = 1; i <= n; i++)
    y[i] = yp1[i];
  *t = tn;
  if (itask == 4 || itask == 5)
    if (ihit)
      *t = tcrit;
  *istate = 2;
  illin = 0;
  freevectors();
}   /*   end successreturn   */

/*
  In this version all memory allocated using malloc is freed upon exit.
  Therefore *istate = 2 and *istate = 3 will not work.
 */

void CLsodaMethod::lsoda(C_INT32 neq,
                         C_FLOAT64 *y,
                         C_FLOAT64 *t,
                         C_FLOAT64 tout,
                         C_INT32 itol,
                         C_FLOAT64 *rtol,
                         C_FLOAT64 *atol,
                         C_INT32 itask,
                         C_INT32 *istate,
                         C_INT32 iopt,
                         C_INT32 jt,
                         C_INT32 iwork1,
                         C_INT32 iwork2,
                         C_INT32 iwork5,
                         C_INT32 iwork6,
                         C_INT32 iwork7,
                         C_INT32 iwork8,
                         C_INT32 iwork9,
                         C_FLOAT64 rwork1,
                         C_FLOAT64 rwork5,
                         C_FLOAT64 rwork6,
                         C_FLOAT64 rwork7)
/*
  If the user does not supply any of these values, the calling program
  should initialize those untouched working variables to zero.
 
  _ml = iwork1
  mu = iwork2
  ixpr = iwork5
  mxstep = iwork6
  mxhnil = iwork7
  mxordn = iwork8
  mxords = iwork9
 
  tcrit = rwork1
  h0 = rwork5
  hmax = rwork6
  hmin = rwork7
 */
{
  /* I had to introduce the model here so that callback function Eval works
     correctly */
  C_INT32 mxstp0 = 500, mxhnl0 = 10;

  /*C_INT32 i1, i2, kgo, lf0; */
  C_INT32 i, iflag, lenyh;
  C_INT32 ihit = 0;
  /*C_FLOAT64 ewti; */
  C_FLOAT64 atoli, ayi, big, h0 = 0., hmax, hmx, rh, rtoli,
                                  tcrit = 0., tdist, tnext, tol, tp, size, sum, w0;

  /*
    Block a.
    This code block is executed on every call.
    It tests *istate and itask for legality and branches appropriately.
    If *istate > 1 but the flag init shows that initialization has not
    yet been done, an error return occurs.
    If *istate = 1 and tout = t, return immediately.
  */

  if (*istate < 1 || *istate > 3)
    {
      if (prfl)
        printf("\nlsoda -- illegal istate = %ld", *istate);

      terminate(istate);
      return;
    }
  if (itask < 1 || itask > 5)
    {
      if (prfl)
        printf("\nlsoda -- illegal itask = %ld", itask);

      terminate(istate);
      return;
    }
  if (init == 0 && (*istate == 2 || *istate == 3))
    {
      if (prfl)
        printf("\nlsoda -- istate > 1 but lsoda not initialized");
      terminate(istate);
      return;
    }
  if (*istate == 1)
    {
      init = 0;
      if (tout == *t)
        {
          ntrep++;
          if (ntrep < 5)
            return;
          if (prfl)
            {
              printf("\nlsoda -- repeated calls with istate = 1 and tout = t");
              printf("\n         run aborted.. apparent infinite loop");
            }
          return;
        }
    }

  /*
    Block b.
    The next code block is executed for the initial call (*istate = 1),
    or for a continuation call with parameter changes (*istate = 3).
    It contains checking of all inputs and various initializations.

    First check legality of the non-optional inputs neq, itol, iopt,
    jt, _ml, and mu.
  */

  if (*istate == 1 || *istate == 3)
    {
      ntrep = 0;
      if (neq <= 0)
        {
          if (prfl)
            printf("\nlsoda -- neq = %ld is less than 1", neq);

          terminate(istate);
          return;
        }
      if (*istate == 3 && neq > n)
        {
          if (prfl)
            printf("\nlsoda -- istate = 3 and neq increased");
          terminate(istate);
          return;
        }
      n = neq;
      if (itol < 1 || itol > 4)
        {
          if (prfl)
            printf("\nlsoda -- itol = %ld illegal", itol);

          terminate(istate);
          return;
        }
      if (iopt < 0 || iopt > 1)
        {
          if (prfl)
            printf("\nlsoda -- iopt = %ld illegal", iopt);

          terminate(istate);
          return;
        }
      if (jt == 3 || jt < 1 || jt > 5)
        {
          if (prfl)
            printf("\nlsoda -- jt = %ld illegal", jt);

          terminate(istate);
          return;
        }
      jtyp = jt;
      if (jt > 2)
        {
          _ml = iwork1;
          mu = iwork2;
          if (_ml < 0 || _ml >= n)
            {
              if (prfl)
                printf("\nlsoda -- _ml = %ld not between 1 and neq", _ml);

              terminate(istate);
              return;
            }
          if (mu < 0 || mu >= n)
            {
              if (prfl)
                printf("\nlsoda -- mu = %ld not between 1 and neq", mu);

              terminate(istate);
              return;
            }
        }

      /* Next process and check the optional inpus.   */

      /* Default options.   */

      if (iopt == 0)
        {
          ixpr = 0;
          mxstep = mxstp0;
          mxhnil = mxhnl0;
          hmxi = 0.;
          hmin = 0.;
          if (*istate == 1)
            {
              h0 = 0.;
              mxordn = mord[1];
              mxords = mord[2];
            }
        }        /*   end if (iopt == 0)   */

      /* Optional inputs.   */

      else
        {/*   if (iopt = 1)  */
          ixpr = iwork5;
          if (ixpr < 0 || ixpr > 2)
            {
              if (prfl)
                printf("\nlsoda -- ixpr = %ld is illegal", ixpr);

              terminate(istate);
              return;
            }
          mxstep = iwork6;
          if (mxstep < 0)
            {
              if (prfl)
                printf("\nlsoda -- mxstep < 0");
              terminate(istate);
              return;
            }
          if (mxstep == 0)
            mxstep = mxstp0;
          mxhnil = iwork7;
          if (mxhnil < 0)
            {
              if (prfl)
                printf("\nlsoda -- mxhnil < 0");
              terminate(istate);
              return;
            }
          if (*istate == 1)
            {
              h0 = rwork5;
              mxordn = iwork8;
              if (mxordn < 0)
                {
                  if (prfl)
                    printf("\nlsoda -- mxordn = %ld is less than 0", mxordn);

                  terminate(istate);
                  return;
                }
              if (mxordn == 0)
                mxordn = 100;
              mxordn = std::min(mxordn, mord[1]);
              mxords = iwork9;
              if (mxords < 0)
                {
                  if (prfl)
                    printf("\nlsoda -- mxords = %ld is less than 0", mxords);

                  terminate(istate);
                  return;
                }
              if (mxords == 0)
                mxords = 100;
              mxords = std::min(mxords, mord[2]);
              if ((tout - *t) * h0 < 0.)
                {
                  if (prfl)
                    {
                      printf("\nlsoda -- tout = %g behind t = %g", tout, *t);
                      printf("\n         integration direction is given by %g",
                             h0);
                    }
                  terminate(istate);
                  return;
                }
            }         /*  end if (*istate == 1)  */
          hmax = rwork6;
          if (hmax < 0.)
            {
              if (prfl)
                printf("\nlsoda -- hmax < 0.");
              terminate(istate);
              return;
            }
          hmxi = 0.;
          if (hmax > 0)
            hmxi = 1. / hmax;
          hmin = rwork7;
          if (hmin < 0.)
            {
              if (prfl)
                printf("\nlsoda -- hmin < 0.");
              terminate(istate);
              return;
            }
        }      /*   end else   */      /*   end iopt = 1   */
    }    /*   end if (*istate == 1 || *istate == 3)   */
  /*
    If *istate = 1, meth is initialized to 1.

    Also allocate memory for yh, wm, ewt, savf, acor, ipvt.
  */
  if (*istate == 1)
    {
      /*
        If memory were not freed, *istate = 3 need not reallocate memory.
        Hence this section is not executed by *istate = 3.
      */
      sqrteta = sqrt(DBL_EPSILON);
      meth = 1;
      nyh = n;
      lenyh = 1 + std::max(mxordn, mxords);

      yh = (C_FLOAT64 **) mem_malloc((1 + lenyh) * sizeof(*yh));
      if (yh == NULL)
        {
          if (prfl)
            printf("\nlsoda -- insufficient memory for your problem");
          terminate(istate);
          return;
        }
      for (i = 1; i <= lenyh; i++)
        yh[i] = (C_FLOAT64 *) mem_malloc((1 + nyh) * sizeof(C_FLOAT64));

      wm = (C_FLOAT64 **) mem_malloc((1 + nyh) * sizeof(*wm));
      if (wm == NULL)
        {
          mem_free(yh);
          if (prfl)
            printf("\nlsoda -- insufficient memory for your problem");
          terminate(istate);
          return;
        }
      for (i = 1; i <= nyh; i++)
        wm[i] = (C_FLOAT64 *) mem_malloc((1 + nyh) * sizeof(C_FLOAT64));

      ewt = (C_FLOAT64 *) mem_malloc((1 + nyh) * sizeof(C_FLOAT64));
      if (ewt == NULL)
        {
          mem_free(yh);
          mem_free(wm);
          if (prfl)
            printf("\nlsoda -- insufficient memory for your problem");
          terminate(istate);
          return;
        }

      savf = (C_FLOAT64 *) mem_malloc((1 + nyh) * sizeof(C_FLOAT64));
      if (savf == NULL)
        {
          mem_free(yh);
          mem_free(wm);
          mem_free(ewt);
          if (prfl)
            printf("\nlsoda -- insufficient memory for your problem");
          terminate(istate);
          return;
        }

      /*
        printf("\nLSODA Block B - before acor alloc");
        printf("\n -  low = %lf, ampl = %lf, dens = %d",
        sparam[24].low, sparam[24].ampl, sparam[24].dens);
        printf("\nlow = %Fp", &sparam[24].low);
        printf("\nacor = %Fp", acor);
      */
      acor = (C_FLOAT64 *) mem_malloc((1 + nyh) * sizeof(C_FLOAT64));
      if (acor == NULL)
        {
          mem_free(yh);
          mem_free(wm);
          mem_free(ewt);
          mem_free(savf);
          if (prfl)
            printf("\nlsoda -- insufficient memory for your problem");
          terminate(istate);
          return;
        }

      ipvt = (C_INT32 *) mem_malloc((1 + nyh) * sizeof(C_INT32));
      if (ipvt == NULL)
        {
          mem_free(yh);
          mem_free(wm);
          mem_free(ewt);
          mem_free(savf);
          mem_free(acor);
          if (prfl)
            printf("\nlsoda -- insufficient memory for your problem");
          terminate(istate);
          return;
        }
    }
  /*
    Check rtol and atol for legality.
  */
  if (*istate == 1 || *istate == 3)
    {
      rtoli = rtol[1];
      atoli = atol[1];
      for (i = 1; i <= n; i++)
        {
          if (itol >= 3)
            rtoli = rtol[i];
          if (itol == 2 || itol == 4)
            atoli = atol[i];
          if (rtoli < 0.)
            {
              if (prfl)
                printf("\nlsoda -- rtol = %g is less than 0.", rtoli);
              terminate(istate);
              freevectors();
              return;
            }
          if (atoli < 0.)
            {
              if (prfl)
                printf("\nlsoda -- atol = %g is less than 0.", atoli);
              terminate(istate);
              freevectors();
              return;
            }
        }     /*   end for   */
    }   /*   end if (*istate == 1 || *istate == 3)   */
  /*
    If *istate = 3, set flag to signal parameter changes to stoda.
  */
  if (*istate == 3)
    {
      jstart = -1;
    }

  /*
    Block c.
    The next block is for the initial call only (*istate = 1).
    It contains all remaining initializations, the initial call to f,
    and the calculation of the initial step size.
    The error weights in ewt are inverted after being loaded.
  */
  if (*istate == 1)
    {
      tn = *t;
      tsw = *t;
      maxord = mxordn;
      if (itask == 4 || itask == 5)
        {
          tcrit = rwork1;
          if ((tcrit - tout) * (tout - *t) < 0.)
            {
              if (prfl)
                printf("\nlsoda -- itask = 4 or 5 and tcrit behind tout");
              terminate(istate);
              freevectors();
              return;
            }
          if (h0 != 0. && (*t + h0 - tcrit) * h0 > 0.)
            h0 = tcrit - *t;
        }
      jstart = 0;
      nhnil = 0;
      nst = 0;
      nje = 0;
      nslast = 0;
      hu = 0.;
      nqu = 0;
      mused = 0;
      miter = 0;
      ccmax = 0.3;
      maxcor = 3;
      msbp = 20;
      mxncf = 10;
      /*
        Initial call to f.
      */
      eval(*t, y, yh[2]);
      nfe = 1;
      /*
        Load the initial value vector in yh.
      */
      yp1 = yh[1];
      for (i = 1; i <= n; i++)
        yp1[i] = y[i];
      /*
        Load and invert the ewt array.  (h is temporarily set to 1.)
      */
      nq = 1;
      h = 1.;
      ewset(itol, rtol, atol, y);
      for (i = 1; i <= n; i++)

        {
          if (ewt[i] <= 0.)

            {
              if (prfl)
                printf("\nlsoda -- ewt[%ld] = %g <= 0.", i, ewt[i]);

              terminate(istate);
              return;
            }
          ewt[i] = 1. / ewt[i];
        }

      /*
        The coding below computes the step size, h0, to be attempted on the
        first step, unless the user has supplied a value for this.
        First check that tout - *t differs significantly from zero.
        A scalar tolerance quantity tol is computed, as max(rtol[i])
        if this is positive, or max(atol[i]/fabs(y[i])) otherwise, adjusted
        so as to be between 100*DBL_EPSILON and 0.001.
        Then the computed value h0 is given by

        h0^(-2) = 1. / (tol * w0^2) + tol * (norm(f))^2

        where   w0     = max(fabs(*t), fabs(tout)),
        f      = the initial value of the vector f(t,y), and
        norm() = the weighted vector norm used throughout, given by
        the vmnorm function routine, and weighted by the
        tolerances initially loaded into the ewt array.

        The sign of h0 is inferred from the initial values of tout and *t.
        fabs(h0) is made < fabs(tout-*t) in any case.
      */
      if (h0 == 0.)
        {
          tdist = fabs(tout - *t);
          /* :TODO: Visual C++ breaks on the follwing line */
          // w0 = std::max(fabs(*t), fabs(tout));
          C_FLOAT64 myHack = fabs(*t);
          C_FLOAT64 myHack2 = fabs(tout);
          w0 = std::max(myHack, myHack2);
          if (tdist < 2. * DBL_EPSILON * w0)
            {
              if (prfl)
                printf("\nlsoda -- tout too close to t to start integration\n ");
              terminate(istate);
              freevectors();
              return;
            }
          tol = rtol[1];
          if (itol > 2)
            {
              for (i = 2; i <= n; i++)
                tol = std::max(tol, rtol[i]);
            }
          if (tol <= 0.)
            {
              atoli = atol[1];
              for (i = 1; i <= n; i++)
                {
                  if (itol == 2 || itol == 4)
                    atoli = atol[i];
                  ayi = fabs(y[i]);
                  if (ayi != 0.)
                    tol = std::max(tol, atoli / ayi);
                }
            }
          tol = std::max(tol, 100. * DBL_EPSILON);
          tol = std::min(tol, 0.001);
          sum = vmnorm(n, yh[2], ewt);
          sum = 1. / (tol * w0 * w0) + tol * sum * sum;
          h0 = 1. / sqrt(sum);
          h0 = std::min(h0, tdist);
          h0 = h0 * ((tout - *t >= 0.) ? 1. : -1.);
        }                 /*   end if (h0 == 0.)   */
      /*
        Adjust h0 if necessary to meet hmax bound.
      */
      rh = fabs(h0) * hmxi;
      if (rh > 1.)
        h0 /= rh;
      /*
        Load h with h0 and scale yh[2] by h0.
      */
      h = h0;
      yp1 = yh[2];
      for (i = 1; i <= n; i++)
        yp1[i] *= h0;
    }         /* if (*istate == 1)   */

  /*
    Block d.
    The next code block is for continuation calls only (*istate = 2 or 3)
    and is to check stop conditions before taking a step.
  */
  if (*istate == 2 || *istate == 3)
    {
      nslast = nst;
      switch (itask)
        {
        case 1 :
          if ((tn - tout) * h >= 0.)
            {
              intdy(tout, 0, y, &iflag);
              if (iflag != 0)
                {
                  if (prfl)
                    printf("\nlsoda -- trouble from intdy,"
                           " itask = %ld, tout = %g",
                           itask, tout);
                  terminate(istate);
                  freevectors();
                  return;
                }
              *t = tout;
              *istate = 2;
              illin = 0;
              freevectors();
              return;
            }
          break;
        case 2 :
          break;
        case 3 :
          tp = tn - hu * (1. + 100. * DBL_EPSILON);
          if ((tp - tout) * h > 0.)
            {
              if (prfl)
                printf("\nlsoda -- itask = %ld and tout behind tcur - hu",
                       itask);

              terminate(istate);
              freevectors();
              return;
            }
          if ((tn - tout) * h < 0.)
            break;
          successreturn(y, t, itask, ihit, tcrit, istate);
          return;
        case 4 :
          tcrit = rwork1;
          if ((tn - tcrit) * h > 0.)
            {
              if (prfl)
                printf("\nlsoda -- itask = 4 or 5 and tcrit behind tcur");
              terminate(istate);
              freevectors();
              return;
            }
          if ((tcrit - tout) * h < 0.)
            {
              if (prfl)
                printf("\nlsoda -- itask = 4 or 5 and tcrit behind tout");
              terminate(istate);
              freevectors();
              return;
            }
          if ((tn - tout) * h >= 0.)
            {
              intdy(tout, 0, y, &iflag);
              if (iflag != 0)
                {
                  if (prfl)
                    printf("\nlsoda -- trouble from intdy,"
                           " itask = %ld, tout = %g",
                           itask, tout);
                  terminate(istate);
                  freevectors();
                  return;
                }
              *t = tout;
              *istate = 2;
              illin = 0;
              freevectors();
              return;
            }
        case 5 :
          if (itask == 5)
            {
              tcrit = rwork1;
              if ((tn - tcrit) * h > 0.)
                {
                  if (prfl)
                    printf("\nlsoda -- itask = 4 or 5 and tcrit behind tcur");
                  terminate(istate);
                  freevectors();
                  return;
                }
            }
          hmx = fabs(tn) + fabs(h);
          ihit = fabs(tn - tcrit) <= (100. * DBL_EPSILON * hmx);
          if (ihit)
            {
              *t = tcrit;
              successreturn(y, t, itask, ihit, tcrit, istate);
              return;
            }
          tnext = tn + h * (1. + 4. * DBL_EPSILON);
          if ((tnext - tcrit) * h <= 0.)
            break;
          h = (tcrit - tn) * (1. - 4. * DBL_EPSILON);
          if (*istate == 2)
            jstart = -2;
          break;
        }      /*   end switch   */
    }      /*   end if (*istate == 2 || *istate == 3)   */

  /*
    Block e.
    The next block is normally executed for all calls and contains
    the call to the one-step core integrator stoda.

    This is a looping point for the integration steps.

    First check for too many steps being taken, update ewt (if not at
    start of problem).  Check for too much accuracy being requested, and
    check for h below the roundoff level in *t.
  */
  while (1)
    {
      if (*istate != 1 || nst != 0)
        {
          if ((nst - nslast) >= mxstep)
            {
              if (prfl)
                printf("\nlsoda -- %ld steps taken before reaching tout",
                       mxstep);

              *istate = -1;
              terminate2(y, t);
              return;
            }
          ewset(itol, rtol, atol, yh[1]);
          for (i = 1; i <= n; i++)
            {
              if (ewt[i] <= 0.)
                {
                  if (prfl)
                    printf("\nlsoda -- ewt[%ld] = %g <= 0.", i, ewt[i]);

                  *istate = -6;
                  terminate2(y, t);
                  return;
                }
              ewt[i] = 1. / ewt[i];
            }
        }
      tolsf = DBL_EPSILON * vmnorm(n, yh[1], ewt);
      if (tolsf > 0.01)
        {
          tolsf = tolsf * 200.;
          if (nst == 0)
            {
              if (prfl)
                {
                  printf("\nlsoda -- at start of problem, too much accuracy");
                  printf("\n         requested for precision of machine,");
                  printf("\n         suggested scaling factor = %g", tolsf);
                }
              terminate(istate);
              freevectors();
              return;
            }
          if (prfl)
            {
              printf("\nlsoda -- at t = %g, too much accuracy requested", *t);
              printf("\n         for precision of machine, suggested");
              printf("\n         scaling factor = %g", tolsf);
            }
          *istate = -2;
          terminate2(y, t);
          return;
        }
      if ((tn + h) == tn)
        {
          nhnil++;
          if (nhnil <= mxhnil)
            {
              if (prfl)
                {
                  printf("\nlsoda -- warning..internal t = %g and h = %g are",
                         tn, h);
                  printf("\n         such that in the machine,"
                         " t + h = t on the next step");
                  printf("\n         solver will continue anyway.");
                }
              if ((nhnil == mxhnil) && prfl)
                {
                  printf("\nlsoda -- above warning has been issued %ld times,",
                         nhnil);
                  printf("\n         it will not be issued again"
                         " for this problem");
                }
            }
        }

      /*
        Call stoda
      */
      stoda(y);

      /*      in Win32 systems it seems that a sleep call is needed */
      /*      to yield some control? */
      /*      Sleep(0); */
      /*
        Print extra information
      */
      if ((ixpr == 2) && prfl)
        {
          printf("\nmeth= %ld,   order= %ld,   nfe= %ld,   nje= %ld",
                 meth, nq, nfe, nje);
          printf("\nt= %20.15e,   h= %20.15e,   nst=%ld", tn, h, nst);
        }

      if (kflag == 0)
        {
          /*
            Block f.
            The following block handles the case of a successful return from the
            core integrator (kflag = 0).
            If a method switch was just made, record tsw, reset maxord,
            set jstart to -1 to signal stoda to complete the switch,
            and do extra printing of data if ixpr != 0.
            Then, in any case, check for stop conditions.
          */
          init = 1;
          if (meth != mused)
            {
              tsw = tn;
              maxord = mxordn;
              if (meth == 2)
                maxord = mxords;
              jstart = -1;
              if (ixpr && prfl)
                {
                  if (meth == 2)
                    printf("\nlsoda -- a switch to the stiff"
                           " method has occurred");

                  if (meth == 1)
                    printf("\nlsoda -- a switch to the nonstiff method"
                           " has occurred");

                  printf("\n         at t = %g, tentative step size h = %g,"
                         " step nst = %ld",
                         tn, h, nst);
                }
            }         /*   end if (meth != mused)   */
          /*
            itask = 1.
            If tout has been reached, interpolate.
          */
          if (itask == 1)
            {
              if ((tn - tout) * h < 0.)
                continue;
              intdy(tout, 0, y, &iflag);
              *t = tout;
              *istate = 2;
              illin = 0;
              freevectors();
              return;
            }
          /*
            itask = 2.
          */
          if (itask == 2)
            {
              successreturn(y, t, itask, ihit, tcrit, istate);
              return;
            }
          /*
            itask = 3.
            Jump to exit if tout was reached.
          */
          if (itask == 3)
            {
              if ((tn - tout) * h >= 0.)
                {
                  successreturn(y, t, itask, ihit, tcrit, istate);
                  return;
                }
              continue;
            }
          /*
            itask = 4.
            See if tout or tcrit was reached.  Adjust h if necessary.
          */
          if (itask == 4)
            {
              if ((tn - tout) * h >= 0.)
                {
                  intdy(tout, 0, y, &iflag);
                  *t = tout;
                  *istate = 2;
                  illin = 0;
                  freevectors();
                  return;
                }
              else
                {
                  hmx = fabs(tn) + fabs(h);
                  ihit = fabs(tn - tcrit) <= (100. * DBL_EPSILON * hmx);
                  if (ihit)
                    {
                      successreturn(y, t, itask, ihit, tcrit, istate);
                      return;
                    }
                  tnext = tn + h * (1. + 4. * DBL_EPSILON);
                  if ((tnext - tcrit) * h <= 0.)
                    continue;
                  h = (tcrit - tn) * (1. - 4. * DBL_EPSILON);
                  jstart = -2;
                  continue;
                }
            }      /*   end if (itask == 4)   */
          /*
            itask = 5.
            See if tcrit was reached and jump to exit.
          */
          if (itask == 5)
            {
              hmx = fabs(tn) + fabs(h);
              ihit = fabs(tn - tcrit) <= (100. * DBL_EPSILON * hmx);
              successreturn(y, t, itask, ihit, tcrit, istate);
              return;
            }
        }   /*   end if (kflag == 0)   */
      /*
        kflag = -1, error test failed repeatedly or with fabs(h) = hmin.
        kflag = -2, convergence failed repeatedly or with fabs(h) = hmin.
      */
      if (kflag == -1 || kflag == -2)
        {
          if (prfl)
            printf("\nlsoda -- at t = %g and step size h = %g, the", tn, h);
          if (kflag == -1)
            {
              if (prfl)
                {
                  printf("\n         error test failed repeatedly or");
                  printf("\n         with fabs(h) = hmin");
                }
              *istate = -4;
            }
          if (kflag == -2)
            {
              if (prfl)
                {
                  printf("\n         corrector convergence "
                         " failed repeatedly or");
                  printf("\n         with fabs(h) = hmin");
                }
              *istate = -5;
            }
          big = 0.;
          imxer = 1;
          for (i = 1; i <= n; i++)
            {
              size = fabs(acor[i]) * ewt[i];
              if (big < size)
                {
                  big = size;
                  imxer = i;
                }
            }
          terminate2(y, t);
          return;
        }     /*   end if (kflag == -1 || kflag == -2)   */
    }   /*   end while   */
}     /*   end lsoda   */

void CLsodaMethod::stoda(C_FLOAT64 *y)
{
  C_INT32 corflag, orderflag;
  /*C_INT32 jb; */
  C_INT32 i, i1, j, m, ncf;
  C_FLOAT64 del, delp, dsm = 0., dup, exup, r, rh, rhup, told;
  C_FLOAT64 pdh, pnorm;

  /*
    stoda performs one step of the integration of an initial value
    problem for a system of ordinary differential equations.
    Note.. stoda is independent of the value of the iteration method
    indicator miter, when this is != 0, and hence is independent
    of the type of chord method used, or the Jacobian structure.
    Communication with stoda is done with the following variables:

    jstart = an integer used for input only, with the following
    values and meanings:

    0  perform the first step,
    > 0  take a new step continuing from the last,
    -1  take the next step with a new value of h,
    n, meth, miter, and/or matrix parameters.
    -2  take the next step with a new value of h,
    but with other inputs unchanged.

    kflag = a completion code with the following meanings:

    0  the step was successful,
    -1  the requested error could not be achieved,
    -2  corrector convergence could not be achieved,
    -3  fatal error in prja or solsy.

    miter = corrector iteration method:

    0  functional iteration,
    >0  a chord method corresponding to jacobian type jt.

  */
  kflag = 0;
  told = tn;
  ncf = 0;
  ierpj = 0;
  iersl = 0;
  jcur = 0;
  delp = 0.;

  /*
    On the first call, the order is set to 1, and other variables are
    initialized.  rmax is the maximum ratio by which h can be increased
    in a single step.  It is initially 1.e4 to compensate for the small
    initial h, but then is normally equal to 10.  If a filure occurs
    (in corrector convergence or error test), rmax is set at 2 for
    the next increase.
    cfode is called to get the needed coefficients for both methods.
  */
  if (jstart == 0)
    {
      lmax = maxord + 1;
      nq = 1;
      l = 2;
      ialth = 2;
      rmax = 10000.;
      rc = 0.;
      el0 = 1.;
      crate = 0.7;
      hold = h;
      nslp = 0;
      ipup = miter;
      /*
        Initialize switching parameters.  meth = 1 is assumed initially.
      */
      icount = 20;
      irflag = 0;
      pdest = 0.;
      pdlast = 0.;
      ratio = 5.;
      cfode(2);
      for (i = 1; i <= 5; i++)
        cm2[i] = tesco[i][2] * elco[i][i + 1];
      cfode(1);
      for (i = 1; i <= 12; i++)
        cm1[i] = tesco[i][2] * elco[i][i + 1];
      resetcoeff();
    }     /*   end if (jstart == 0)   */
  /*
    The following block handles preliminaries needed when jstart = -1.
    ipup is set to miter to force a matrix update.
    If an order increase is about to be considered (ialth = 1),
    ialth is reset to 2 to postpone consideration one more step.
    If the caller has changed meth, cfode is called to reset the coefficients of the method.
    If h is to be changed, yh must be rescaled.
    If h or meth is being changed, ialth is reset to l = nq + 1
    to prevent further changes in h for that many steps.
  */
  if (jstart == -1)
    {
      ipup = miter;
      lmax = maxord + 1;
      if (ialth == 1)
        ialth = 2;
      if (meth != mused)
        {
          cfode(meth);
          ialth = l;
          resetcoeff();
        }
      if (h != hold)
        {
          rh = h / hold;
          h = hold;
          scaleh(&rh, &pdh);
        }
    }      /*   if (jstart == -1)   */

  if (jstart == -2)
    {
      if (h != hold)
        {
          rh = h / hold;
          h = hold;
          scaleh(&rh, &pdh);
        }
    }     /*   if (jstart == -2)   */

  /*
    Prediction.
    This section computes the predicted values by effectively
    multiplying the yh array by the pascal triangle matrix.
    rc is the ratio of new to old values of the coefficient h * el[1].
    When rc differs from 1 by more than ccmax, ipup is set to miter
    to force pjac to be called, if a jacobian is involved.
    In any case, prja is called at least every msbp steps.
  */

  while (1)
    {
      while (1)
        {
          if (fabs(rc - 1.) > ccmax)
            ipup = miter;
          if (nst >= nslp + msbp)
            ipup = miter;
          tn += h;
          for (j = nq; j >= 1; j--)
            for (i1 = j; i1 <= nq; i1++)
              {
                yp1 = yh[i1];
                yp2 = yh[i1 + 1];
                for (i = 1; i <= n; i++)
                  yp1[i] += yp2[i];
              }
          pnorm = vmnorm(n, yh[1], ewt);

          correction(y, &corflag, pnorm, &del, &delp, &told, &ncf,
                     &rh, &m);
          if (corflag == 0)
            break;
          if (corflag == 1)
            {
              rh = std::max(rh, hmin / fabs(h));
              scaleh(&rh, &pdh);
              continue;
            }
          if (corflag == 2)
            {
              kflag = -2;
              hold = h;
              jstart = 1;
              return;
            }
        }      /*   end inner while (corrector loop)   */
      /*
        The corrector has converged.  jcur is set to 0
        to signal that the Jacobian involved may need updating later.
        The local error test is done now.
      */
      jcur = 0;
      if (m == 0)
        dsm = del / tesco[nq][2];
      if (m > 0)
        dsm = vmnorm(n, acor, ewt) / tesco[nq][2];
      if (dsm <= 1.)
        {
          /*
            After a successful step, update the yh array.
            Decrease icount by 1, and if it is -1, consider switching methods.
            If a method switch is made, reset various parameters,
            rescale the yh array, and exit.  If there is no switch,
            consider changing h if ialth = 1.  Otherwise decrease ialth by 1.
            If ialth is then 1 and nq < maxord, then acor is saved for
            use in a possible order increase on the next step.
            If a change in h is considered, an increase or decrease in order
            by one is considered also.  A change in h is made only if it is by
            a factor of at least 1.1.  If not, ialth is set to 3 to prevent
            testing for that many steps.
          */
          kflag = 0;
          nst++;
          hu = h;
          nqu = nq;
          mused = meth;
          for (j = 1; j <= l; j++)
            {
              yp1 = yh[j];
              r = el[j];
              for (i = 1; i <= n; i++)
                yp1[i] += r * acor[i];
            }
          icount--;
          if (icount < 0)
            {
              methodswitch(dsm, pnorm, &pdh, &rh);
              if (meth != mused)
                {
                  rh = std::max(rh, hmin / fabs(h));
                  scaleh(&rh, &pdh);
                  rmax = 10.;
                  endstoda();
                  break;
                }
            }
          /*
            No method switch is being made.  Do the usual step/order selection.
          */
          ialth--;
          if (ialth == 0)
            {
              rhup = 0.;
              if (l != lmax)
                {
                  yp1 = yh[lmax];
                  for (i = 1; i <= n; i++)
                    savf[i] = acor[i] - yp1[i];
                  dup = vmnorm(n, savf, ewt) / tesco[nq][3];
                  exup = 1. / (C_FLOAT64) (l + 1);
                  rhup = 1. / (1.4 * pow(dup, exup) + 0.0000014);
                }
              orderswitch(&rhup, dsm, &pdh, &rh, &orderflag);
              /*
                No change in h or nq.
              */
              if (orderflag == 0)
                {
                  endstoda();
                  break;
                }
              /*
                h is changed, but not nq.
              */
              if (orderflag == 1)
                {
                  rh = std::max(rh, hmin / fabs(h));
                  scaleh(&rh, &pdh);
                  rmax = 10.;
                  endstoda();
                  break;
                }
              /*
                both nq and h are changed.
              */
              if (orderflag == 2)
                {
                  resetcoeff();
                  rh = std::max(rh, hmin / fabs(h));
                  scaleh(&rh, &pdh);
                  rmax = 10.;
                  endstoda();
                  break;
                }
            }            /*   end if (ialth == 0)   */
          if (ialth > 1 || l == lmax)
            {
              endstoda();
              break;
            }
          yp1 = yh[lmax];
          for (i = 1; i <= n; i++)
            yp1[i] = acor[i];
          endstoda();
          break;
        }       /*   end if (dsm <= 1.)   */
      /*
        The error test failed.  kflag keeps track of multiple failures.
        Restore tn and the yh array to their previous values, and prepare
        to try the step again.  Compute the optimum step size for this or
        one lower.  After 2 or more failures, h is forced to decrease
        by a factor of 0.2 or less.
      */
      else
        {
          kflag--;
          tn = told;
          for (j = nq; j >= 1; j--)
            for (i1 = j; i1 <= nq; i1++)
              {
                yp1 = yh[i1];
                yp2 = yh[i1 + 1];
                for (i = 1; i <= n; i++)
                  yp1[i] -= yp2[i];
              }
          rmax = 2.;
          if (fabs(h) <= hmin * 1.00001)
            {
              kflag = -1;
              hold = h;
              jstart = 1;
              break;
            }
          if (kflag > -3)
            {
              rhup = 0.;
              orderswitch(&rhup, dsm, &pdh, &rh, &orderflag);
              if (orderflag == 1 || orderflag == 0)
                {
                  if (orderflag == 0)
                    rh = std::min(rh, 0.2);
                  rh = std::max(rh, hmin / fabs(h));
                  scaleh(&rh, &pdh);
                }
              if (orderflag == 2)
                {
                  resetcoeff();
                  rh = std::max(rh, hmin / fabs(h));
                  scaleh(&rh, &pdh);
                }
              continue;
            }     /*   if (kflag > -3)   */
          /*
            Control reaches this section if 3 or more failures have occurred.
            If 10 failures have occurred, exit with kflag = -1.
            It is assumed that the derivatives that have accumulated in the
            yh array have errors of the wrong order.  Hence the first
            derivative is recomputed, and the order is set to 1.  Then
            h is reduced by a factor of 10, and the step is retried,
            until it succeeds or h reaches hmin.
          */
          else
            {
              if (kflag == -10)
                {
                  kflag = -1;
                  hold = h;
                  jstart = 1;
                  break;
                }
              else
                {
                  rh = 0.1;
                  rh = std::max(hmin / fabs(h) , rh);
                  h *= rh;
                  yp1 = yh[1];
                  for (i = 1; i <= n; i++)
                    y[i] = yp1[i];

                  eval(tn, y, savf);

                  nfe++;
                  yp1 = yh[2];
                  for (i = 1; i <= n; i++)
                    yp1[i] = h * savf[i];
                  ipup = miter;
                  ialth = 5;
                  if (nq == 1)
                    continue;
                  nq = 1;
                  l = 2;
                  resetcoeff();
                  continue;
                }
            }     /*   end else -- kflag <= -3 */
        }     /*   end error failure handling   */
    }      /*   end outer while   */
}           /*   end stoda   */

void CLsodaMethod::ewset(C_INT32 itol,
                         C_FLOAT64 * rtol,
                         C_FLOAT64 * atol,
                         C_FLOAT64 * ycur)
{
  C_INT32 i;

  switch (itol)
    {
    case 1 :
      for (i = 1; i <= n; i++)
        ewt[i] = rtol[1] * fabs(ycur[i]) + atol[1];
      break;
    case 2 :
      for (i = 1; i <= n; i++)
        ewt[i] = rtol[1] * fabs(ycur[i]) + atol[i];
      break;
    case 3 :
      for (i = 1; i <= n; i++)
        ewt[i] = rtol[i] * fabs(ycur[i]) + atol[1];
      break;
    case 4 :
      for (i = 1; i <= n; i++)
        ewt[i] = rtol[i] * fabs(ycur[i]) + atol[i];
      break;
    }
}           /*   end ewset   */

/*
  xsetf sets the flag to control the printing of messages by lsoda.
  mflag = 0 means do not print (danger.. this risks losing valuable
  information).
  mflag = 1 means print (the default)
  A call to xsetf may be made at any time and will take effect
  immediately.
 */
void CLsodaMethod::xsetf(C_INT32 mflag)
{
  prfl = mflag;
}           /*   end xsetf   */

void CLsodaMethod::intdy(C_FLOAT64 t,
                         C_INT32 k,
                         C_FLOAT64 *dky,
                         C_INT32 * iflag)
/*
  intdy computes interpolated values of the k-th derivative of the
  dependent variable vector y, and stores it in dky.  This routine
  is called within the package with k = 0 and *t = tout, but may
  also be called by the user for any k up to the current order.
  (See detailed instructions in the usage documentation.)
 
  The computed values in dky are gotten by interpolation using the
  Nordsieck history array yh.  This array corresponds uniquely to a
  vector-valued polynomial of degree nqcur or less, and dky is set to the k-th derivative of this polynomial at t.
  The formula for dky is
 
  q
  dky[i] = sum c[k][j] * (t - tn)^(j-k) * h^(-j) * yh[j+1][i]
  j=k
 
  where c[k][j] = j*(j-1)*...*(j-k+1), q = nqcur, tn = tcur, h = hcur.
  The quantities nq = nqcur, l = nq+1, n = neq, tn, and h are declared
  static globally.  The above sum is done in reverse order.
  *iflag is returned negative if either k or t is out of bounds.
  */

{
  C_INT32 i, ic, j, jj, jp1;
  C_FLOAT64 c, r, s, tp;

  *iflag = 0;
  if (k < 0 || k > nq)
    {
      if (prfl)
        printf("\nintdy -- k = %ld illegal", k);

      *iflag = -1;
      return;
    }
  tp = tn - hu - 100. * DBL_EPSILON * (tn + hu);
  if ((t - tp) * (t - tn) > 0.)
    {
      if (prfl)
        {
          printf("\nintdy -- t = %g illegal", t);
          printf("\n         t not in interval tcur - hu to tcur");
        }
      *iflag = -2;
      return;
    }

  s = (t - tn) / h;
  ic = 1;
  for (jj = l - k; jj <= nq; jj++)
    ic *= jj;
  c = (C_FLOAT64) ic;
  yp1 = yh[l];
  for (i = 1; i <= n; i++)
    dky[i] = c * yp1[i];
  for (j = nq - 1; j >= k; j--)
    {
      jp1 = j + 1;
      ic = 1;
      for (jj = jp1 - k; jj <= j; jj++)
        ic *= jj;
      c = (C_FLOAT64) ic;
      yp1 = yh[jp1];
      for (i = 1; i <= n; i++)
        dky[i] = c * yp1[i] + s * dky[i];
    }
  if (k == 0)
    return;
  r = pow(h, (C_FLOAT64) (-k));
  for (i = 1; i <= n; i++)
    dky[i] *= r;
}      /*   end intdy   */

void CLsodaMethod::cfode(C_INT32 meth)
{
  C_INT32 i, nq, nqm1, nqp1;
  C_FLOAT64 agamq, fnq, fnqm1, pc[13], pint, ragq,
  rqfac, rq1fac, tsign, xpin;
  /*
    cfode is called by the integrator routine to set coefficients
    needed there.  The coefficients for the current method, as
    given by the value of meth, are set for all orders and saved.
    The maximum order assumed here is 12 if meth = 1 and 5 if meth = 2.
    (A smaller value of the maximum order is also allowed.)
    cfode is called once at the beginning of the problem, and
    is not called again unless and until meth is changed.

    The elco array contains the basic method coefficients.
    The coefficients el[i], 1 < i < nq+1, for the method of
    order nq are stored in elco[nq][i].  They are given by a generating
    polynomial, i.e.,

    l(x) = el[1] + el[2]*x + ... + el[nq+1]*x^nq.

    For the implicit Adams method, l(x) is given by

    dl/dx = (x+1)*(x+2)*...*(x+nq-1)/factorial(nq-1),   l(-1) = 0.

    For the bdf methods, l(x) is given by

    l(x) = (x+1)*(x+2)*...*(x+nq)/k,

    where   k = factorial(nq)*(1+1/2+...+1/nq).

    The tesco array contains test constants used for the
    local error test and the selection of step size and/or order.
    At order nq, tesco[nq][k] is used for the selection of step
    size at order nq-1 if k = 1, at order nq if k = 2, and at order
    nq+1 if k = 3.
  */
  if (meth == 1)
    {
      elco[1][1] = 1.;
      elco[1][2] = 1.;
      tesco[1][1] = 0.;
      tesco[1][2] = 2.;
      tesco[2][1] = 1.;
      tesco[12][3] = 0.;
      pc[1] = 1.;
      rqfac = 1.;
      for (nq = 2; nq <= 12; nq++)
        {
          /*
            The pc array will contain the coefficients of the polynomial

            p(x) = (x+1)*(x+2)*...*(x+nq-1).

            Initially, p(x) = 1.
          */
          rq1fac = rqfac;
          rqfac = rqfac / (C_FLOAT64) nq;
          nqm1 = nq - 1;
          fnqm1 = (C_FLOAT64) nqm1;
          nqp1 = nq + 1;
          /*
            Form coefficients of p(x)*(x+nq-1).
          */
          pc[nq] = 0.;
          for (i = nq; i >= 2; i--)
            pc[i] = pc[i - 1] + fnqm1 * pc[i];
          pc[1] = fnqm1 * pc[1];
          /*
            Compute integral, -1 to 0, of p(x) and x*p(x).
          */
          pint = pc[1];
          xpin = pc[1] / 2.;
          tsign = 1.;
          for (i = 2; i <= nq; i++)
            {
              tsign = -tsign;
              pint += tsign * pc[i] / (C_FLOAT64) i;
              xpin += tsign * pc[i] / (C_FLOAT64) (i + 1);
            }
          /*
            Store coefficients in elco and tesco.
          */
          elco[nq][1] = pint * rq1fac;
          elco[nq][2] = 1.;
          for (i = 2; i <= nq; i++)
            elco[nq][i + 1] = rq1fac * pc[i] / (C_FLOAT64) i;
          agamq = rqfac * xpin;
          ragq = 1. / agamq;
          tesco[nq][2] = ragq;
          if (nq < 12)
            tesco[nqp1][1] = ragq * rqfac / (C_FLOAT64) nqp1;
          tesco[nqm1][3] = ragq;
        }      /*   end for   */
      return;
    }      /*   end if (meth == 1)   */

  /*
    meth = 2.
  */
  pc[1] = 1.;
  rq1fac = 1.;
  /*
    The pc array will contain the coefficients of the polynomial

    p(x) = (x+1)*(x+2)*...*(x+nq).

    Initially, p(x) = 1.
  */
  for (nq = 1; nq <= 5; nq++)
    {
      fnq = (C_FLOAT64) nq;
      nqp1 = nq + 1;
      /*
        Form coefficients of p(x)*(x+nq).
      */
      pc[nqp1] = 0.;
      for (i = nq + 1; i >= 2; i--)
        pc[i] = pc[i - 1] + fnq * pc[i];
      pc[1] *= fnq;
      /*
        Store coefficients in elco and tesco.
      */
      for (i = 1; i <= nqp1; i++)
        elco[nq][i] = pc[i] / pc[2];
      elco[nq][2] = 1.;
      tesco[nq][1] = rq1fac;
      tesco[nq][2] = ((C_FLOAT64) nqp1) / elco[nq][1];
      tesco[nq][3] = ((C_FLOAT64) (nq + 2)) / elco[nq][1];
      rq1fac /= fnq;
    }
  return;
}       /*   end cfode   */

void CLsodaMethod::scaleh(C_FLOAT64 * rh,
                          C_FLOAT64 * pdh)
{
  C_FLOAT64 r;
  C_INT32 j, i;
  /*
    If h is being changed, the h ratio rh is checked against
    rmax, hmin, and hmxi, and the yh array is rescaled.  ialth is set to
    l = nq + 1 to prevent a change of h for that many steps, unless
    forced by a convergence or error test failure.
  */
  *rh = std::min(*rh, rmax);
  *rh = *rh / std::max(1., fabs(h) * hmxi * *rh);
  /*
    If meth = 1, also restrict the new step size by the stability region.
    If this reduces h, set irflag to 1 so that if there are roundoff
    problems later, we can assume that is the cause of the trouble.
  */
  if (meth == 1)
    {
      irflag = 0;
      *pdh = std::max(fabs(h) * pdlast, 0.000001);
      if ((*rh * *pdh * 1.00001) >= sm1[nq])
        {
          *rh = sm1[nq] / *pdh;
          irflag = 1;
        }
    }
  r = 1.;
  for (j = 2; j <= l; j++)
    {
      r *= *rh;
      yp1 = yh[j];
      for (i = 1; i <= n; i++)
        yp1[i] *= r;
    }
  h *= *rh;
  rc *= *rh;
  ialth = l;
}     /*   end scaleh   */

void CLsodaMethod::prja(C_FLOAT64 *y)
{
  C_INT32 i, ier, j;
  /*C_INT32 lenp, ml3, meb1, meband, mband, mba, j1, jj, i1, i2, ii, np1; */
  C_FLOAT64 fac, hl0, r, r0, yj;
  /*C_FLOAT64 con, yi, yjj; */
  /*
    prja is called by stoda to compute and process the matrix
    P = I - h * el[1] * J, where J is an approximation to the Jacobian.
    Here J is computed by finite differencing.
    J, scaled by -h * el[1], is stored in wm.  Then the norm of J (the
    matrix norm consistent with the weighted max-norm on vectors given
    by vmnorm) is computed, and J is overwritten by P.  P is then
    subjected to LU decomposition in preparation for later solution
    of linear systems with p as coefficient matrix.  This is done
    by dgefa if miter = 2, and by dgbfa if miter = 5.
  */
  nje++;
  ierpj = 0;
  jcur = 1;
  hl0 = h * el0;
  /*
    If miter = 2, make n calls to f to approximate J.
  */
  if (miter != 2)
    {
      if (prfl)
        printf("\nprja -- miter != 2");
      return;
    }

  if (miter == 2)
    {
      fac = vmnorm(n, savf, ewt);
      r0 = 1000. * fabs(h) * DBL_EPSILON * ((C_FLOAT64) n) * fac;
      if (r0 == 0.)
        r0 = 1.;
      for (j = 1; j <= n; j++)
        {
          yj = y[j];
          r = std::max(sqrteta * fabs(yj), r0 / ewt[j]);
          y[j] += r;
          fac = -hl0 / r;
          eval(tn, y, acor);

          for (i = 1; i <= n; i++)
            wm[i][j] = (acor[i] - savf[i]) * fac;
          y[j] = yj;
        }
      nfe += n;
      /*
        Compute norm of Jacobian.
      */
      pdnorm = fnorm(n, wm, ewt) / fabs(hl0);
      /*
        Add identity matrix.
      */
      for (i = 1; i <= n; i++)
        wm[i][i] += 1.;
      /*
        Do LU decomposition on P.
      */
      dgefa(wm, n, ipvt, &ier);
      if (ier != 0)
        ierpj = 1;
      return;
    }
}      /*   end prja   */

C_FLOAT64 CLsodaMethod::vmnorm(C_INT32 n,
                               C_FLOAT64 * v,
                               C_FLOAT64 * w)
/*
  This function routine computes the weighted max-norm
  of the vector of length n contained in the array v, with weights
  contained in the array w of length n.
 
  vmnorm = max(i = 1, ..., n) fabs(v[i]) * w[i].
 */
{
  C_INT32 i;
  C_FLOAT64 vm;

  vm = 0.;
  for (i = 1; i <= n; i++)
    vm = std::max(vm, fabs(v[i]) * w[i]);
  return vm;
}                  /*   end vmnorm   */

C_FLOAT64 CLsodaMethod::fnorm(C_INT32 n,
                              C_FLOAT64 ** a,
                              C_FLOAT64 * w)
/*
  This subroutine computes the norm of a full n by n matrix,
  stored in the array a, that is consistent with the weighted max-norm
  on vectors, with weights stored in the array w.
 
  fnorm = max(i=1,...,n) (w[i] * sum(j=1,...,n) fabs(a[i][j]) / w[j])
 */

{
  C_INT32 i, j;
  C_FLOAT64 an, sum, *ap1;

  an = 0.;
  for (i = 1; i <= n; i++)
    {
      sum = 0.;
      ap1 = a[i];
      for (j = 1; j <= n; j++)
        sum += fabs(ap1[j]) / w[j];
      an = std::max(an, sum * w[i]);
    }
  return an;
}     /*   end fnorm   */

void CLsodaMethod::correction(C_FLOAT64 *y,
                              C_INT32 *corflag,
                              C_FLOAT64 pnorm,
                              C_FLOAT64 *del,
                              C_FLOAT64 *delp,
                              C_FLOAT64 *told,
                              C_INT32 *ncf,
                              C_FLOAT64 *rh,
                              C_INT32 *m)
/*
 *corflag = 0 : corrector converged,
 1 : step size to be reduced, redo prediction,
 2 : corrector cannot converge, failure flag.
 */
{
  C_INT32 i;
  C_FLOAT64 rm, rate, dcon;

  /*
    Up to maxcor corrector iterations are taken.  A convergence test is
    made on the r.m.s. norm of each correction, weighted by the error
    weight vector ewt.  The sum of the corrections is accumulated in the
    vector acor[i].  The yh array is not altered in the corrector loop.
  */

  *m = 0;
  *corflag = 0;
  rate = 0.;
  *del = 0.;
  yp1 = yh[1];
  for (i = 1; i <= n; i++)
    y[i] = yp1[i];

  eval(tn, y, savf);

  nfe++;
  /*
    If indicated, the matrix P = I - h * el[1] * J is reevaluated and
    preprocessed before starting the corrector iteration.  ipup is set to 0 as an indicator that this has been done.
  */
  while (1)
    {
      if (*m == 0)
        {
          if (ipup > 0)
            {
              prja(y);
              ipup = 0;
              rc = 1.;
              nslp = nst;
              crate = 0.7;
              if (ierpj != 0)
                {
                  corfailure(told, rh, ncf, corflag);
                  return;
                }
            }
          for (i = 1; i <= n; i++)
            acor[i] = 0.;
        }   /*   end if (*m == 0)   */
      if (miter == 0)
        {
          /*
            In case of functional iteration, update y directly from
            the result of the last function evaluation.
          */
          yp1 = yh[2];
          for (i = 1; i <= n; i++)
            {
              savf[i] = h * savf[i] - yp1[i];
              y[i] = savf[i] - acor[i];
            }
          *del = vmnorm(n, y, ewt);
          yp1 = yh[1];
          for (i = 1; i <= n; i++)
            {
              y[i] = yp1[i] + el[1] * savf[i];
              acor[i] = savf[i];
            }
        }      /*   end functional iteration   */
      /*
        In the case of the chord method, compute the corrector error,
        and solve the linear system with that as right-hand side and
        P as coefficient matrix.
      */
      else
        {
          yp1 = yh[2];
          for (i = 1; i <= n; i++)
            y[i] = h * savf[i] - (yp1[i] + acor[i]);
          solsy(y);
          *del = vmnorm(n, y, ewt);
          yp1 = yh[1];
          for (i = 1; i <= n; i++)
            {
              acor[i] += y[i];
              y[i] = yp1[i] + el[1] * acor[i];
            }
        }   /*   end chord method   */
      /*
        Test for convergence.  If *m > 0, an estimate of the convergence
        rate constant is stored in crate, and this is used in the test.

        We first check for a change of iterates that is the size of
        roundoff error.  If this occurs, the iteration has converged, and a
        new rate estimate is not formed.
        In all other cases, force at least two iterations to estimate a
        local Lipschitz constant estimate for Adams method.
        On convergence, form pdest = local maximum Lipschitz constant
        estimate.  pdlast is the most recent nonzero estimate.
      */
      if (*del <= 100. * pnorm * DBL_EPSILON)
        break;
      if (*m != 0 || meth != 1)
        {
          if (*m != 0)
            {
              rm = 1024.0;
              if (*del <= (1024. * *delp))
                rm = *del / *delp;
              rate = std::max(rate, rm);
              crate = std::max(0.2 * crate, rm);
            }
          dcon = *del * std::min(1., 1.5 * crate) / (tesco[nq][2] * conit);
          if (dcon <= 1.)
            {
              pdest = std::max(pdest, rate / fabs(h * el[1]));
              if (pdest != 0.)
                pdlast = pdest;
              break;
            }
        }
      /*
        The corrector iteration failed to converge.
        If miter != 0 and the Jacobian is out of date, prja is called for
        the next try.   Otherwise the yh array is retracted to its values
        before prediction, and h is reduced, if possible.  If h cannot be
        reduced or mxncf failures have occured, exit with corflag = 2.
      */
      (*m)++;
      if (*m == maxcor || (*m >= 2 && *del > 2. * *delp))
        {
          if (miter == 0 || jcur == 1)
            {
              corfailure(told, rh, ncf, corflag);
              return;
            }
          ipup = miter;
          /*
            Restart corrector if Jacobian is recomputed.
          */
          *m = 0;
          rate = 0.;
          *del = 0.;
          yp1 = yh[1];
          for (i = 1; i <= n; i++)
            y[i] = yp1[i];

          eval(tn, y, savf);

          nfe++;
        }
      /*
        Iterate corrector.
      */
      else
        {
          *delp = *del;
          eval(tn, y, savf);
          nfe++;
        }
    }   /*   end while   */
}       /*   end correction   */

void CLsodaMethod::corfailure(C_FLOAT64 * told,
                              C_FLOAT64 * rh,
                              C_INT32 * ncf,
                              C_INT32 * corflag)
{
  C_INT32 j, i1, i;

  (*ncf)++;
  rmax = 2.;
  tn = *told;
  for (j = nq; j >= 1; j--)
    for (i1 = j; i1 <= nq; i1++)
      {
        yp1 = yh[i1];
        yp2 = yh[i1 + 1];
        for (i = 1; i <= n; i++)
          yp1[i] -= yp2[i];
      }
  if (fabs(h) <= hmin * 1.00001 || *ncf == mxncf)
    {
      *corflag = 2;
      return;
    }
  *corflag = 1;
  *rh = 0.25;
  ipup = miter;
}              /*   end corfailure   */

void CLsodaMethod::solsy(C_FLOAT64 * y)
/*
  This routine manages the solution of the linear system arising from
  a chord iteration.  It is called if miter != 0.
  If miter is 2, it calls dgesl to accomplish this.
  If miter is 5, it calls dgbsl.
 
  y = the right-hand side vector on input, and the solution vector
  on output.
 */
{
  iersl = 0;
  if (miter != 2)
    {
      if (prfl)
        printf("\nsolsy -- miter != 2");
      return;
    }

  if (miter == 2)
    dgesl(wm, n, ipvt, y, 0);
  return;
}          /*   end solsy   */

void CLsodaMethod::methodswitch(C_FLOAT64 dsm,
                                C_FLOAT64 pnorm,
                                C_FLOAT64 *pdh,
                                C_FLOAT64 *rh)
{
  C_INT32 lm1, lm1p1, lm2, lm2p1, nqm1, nqm2;
  C_FLOAT64 rh1, rh2, rh1it, exm2, dm2, exm1, dm1, alpha, exsm;

  /*
    We are current using an Adams method.  Consider switching to bdf.
    If the current order is greater than 5, assume the problem is
    not stiff, and skip this section.
    If the Lipschitz constant and error estimate are not polluted
    by roundoff, perform the usual test.
    Otherwise, switch to the bdf methods if the last step was
    restricted to insure stability (irflag = 1), and stay with Adams
    method if not.  When switching to bdf with polluted error estimates,
    in the absence of other information, double the step size.

    When the estimates are ok, we make the usual test by computing
    the step size we could have (ideally) used on this step,
    with the current (Adams) method, and also that for the bdf.
    If nq > mxords, we consider changing to order mxords on switching.
    Compare the two step sizes to decide whether to switch.
    The step size advantage must be at least ratio = 5 to switch.
  */
  if (meth == 1)
    {
      if (nq > 5)
        return;
      if (dsm <= (100. * pnorm * DBL_EPSILON) || pdest == 0.)
        {
          if (irflag == 0)
            return;
          rh2 = 2.;
          nqm2 = std::min(nq, mxords);
        }
      else
        {
          exsm = 1. / (C_FLOAT64) l;
          rh1 = 1. / (1.2 * pow(dsm, exsm) + 0.0000012);
          rh1it = 2. * rh1;
          *pdh = pdlast * fabs(h);
          if ((*pdh * rh1) > 0.00001)
            rh1it = sm1[nq] / *pdh;
          rh1 = std::min(rh1, rh1it);
          if (nq > mxords)
            {
              nqm2 = mxords;
              lm2 = mxords + 1;
              exm2 = 1. / (C_FLOAT64) lm2;
              lm2p1 = lm2 + 1;
              dm2 = vmnorm(n, yh[lm2p1], ewt) / cm2[mxords];
              rh2 = 1. / (1.2 * pow(dm2, exm2) + 0.0000012);
            }
          else
            {
              dm2 = dsm * (cm1[nq] / cm2[nq]);
              rh2 = 1. / (1.2 * pow(dm2, exsm) + 0.0000012);
              nqm2 = nq;
            }
          if (rh2 < ratio * rh1)
            return;
        }
      /*
        The method switch test passed.  Reset relevant quantities for bdf.
      */
      *rh = rh2;
      icount = 20;
      meth = 2;
      miter = jtyp;
      pdlast = 0.;
      nq = nqm2;
      l = nq + 1;
      return;
    }   /*   end if (meth == 1)   */
  /*
    We are currently using a bdf method, considering switching to Adams.
    Compute the step size we could have (ideally) used on this step,
    with the current (bdf) method, and also that for the Adams.
    If nq > mxordn, we consider changing to order mxordn on switching.
    Compare the two step sizes to decide whether to switch.
    The step size advantage must be at least 5/ratio = 1 to switch.
    If the step size for Adams would be so small as to cause
    roundoff pollution, we stay with bdf.
  */
  exsm = 1. / (C_FLOAT64) l;
  if (mxordn < nq)
    {
      nqm1 = mxordn;
      lm1 = mxordn + 1;
      exm1 = 1. / (C_FLOAT64) lm1;
      lm1p1 = lm1 + 1;
      dm1 = vmnorm(n, yh[lm1p1], ewt) / cm1[mxordn];
      rh1 = 1. / (1.2 * pow(dm1, exm1) + 0.0000012);
    }
  else
    {
      dm1 = dsm * (cm2[nq] / cm1[nq]);
      rh1 = 1. / (1.2 * pow(dm1, exsm) + 0.0000012);
      nqm1 = nq;
      exm1 = exsm;
    }
  rh1it = 2. * rh1;
  *pdh = pdnorm * fabs(h);
  if ((*pdh * rh1) > 0.00001)
    rh1it = sm1[nqm1] / *pdh;
  rh1 = std::min(rh1, rh1it);
  rh2 = 1. / (1.2 * pow(dsm, exsm) + 0.0000012);
  if ((rh1 * ratio) < (5. * rh2))
    return;
  alpha = std::max(0.001, rh1);
  dm1 *= pow(alpha, exm1);
  if (dm1 <= 1000. * DBL_EPSILON * pnorm)
    return;
  /*
    The switch test passed.  Reset relevant quantities for Adams.
  */
  *rh = rh1;
  icount = 20;
  meth = 1;
  miter = 0;
  pdlast = 0.;
  nq = nqm1;
  l = nq + 1;
}     /*   end methodswitch   */

/*
  This routine returns from stoda to lsoda.  Hence freevectors() is
  not executed.
 */

void CLsodaMethod::endstoda(void)
{
  C_FLOAT64 r;
  C_INT32 i;

  r = 1. / tesco[nqu][2];
  for (i = 1; i <= n; i++)
    acor[i] *= r;
  hold = h;
  jstart = 1;
}      /*   end endstoda   */

void CLsodaMethod::orderswitch(C_FLOAT64 * rhup,
                               C_FLOAT64 dsm,
                               C_FLOAT64 * pdh,
                               C_FLOAT64 * rh,
                               C_INT32 * orderflag)
/*
  Regardless of the success or failure of the step, factors
  rhdn, rhsm, and rhup are computed, by which h could be multiplied
  at order nq - 1, order nq, or order nq + 1, respectively.
  In the case of a failure, rhup = 0. to avoid an order increase.
  The largest of these is determined and the new order chosen
  accordingly.  If the order is to be increased, we compute one
  additional scaled derivative.
 
  orderflag = 0  : no change in h or nq,
  1  : change in h but not nq,
  2  : change in both h and nq.
 */

{
  C_INT32 newq, i;
  C_FLOAT64 exsm, rhdn, rhsm, ddn, exdn, r;

  *orderflag = 0;

  exsm = 1. / (C_FLOAT64) l;
  rhsm = 1. / (1.2 * pow(dsm, exsm) + 0.0000012);

  rhdn = 0.;
  if (nq != 1)
    {
      ddn = vmnorm(n, yh[l], ewt) / tesco[nq][1];
      exdn = 1. / (C_FLOAT64) nq;
      rhdn = 1. / (1.3 * pow(ddn, exdn) + 0.0000013);
    }
  /*
    If meth = 1, limit rh accordinfg to the stability region also.
  */
  if (meth == 1)
    {
      *pdh = std::max(fabs(h) * pdlast, 0.000001);
      if (l < lmax)
        *rhup = std::min(*rhup, sm1[l] / *pdh);
      rhsm = std::min(rhsm, sm1[nq] / *pdh);
      if (nq > 1)
        rhdn = std::min(rhdn, sm1[nq - 1] / *pdh);
      pdest = 0.;
    }
  if (rhsm >= *rhup)
    {
      if (rhsm >= rhdn)
        {
          newq = nq;
          *rh = rhsm;
        }
      else
        {
          newq = nq - 1;
          *rh = rhdn;
          if (kflag < 0 && *rh > 1.)
            *rh = 1.;
        }
    }
  else
    {
      if (*rhup <= rhdn)
        {
          newq = nq - 1;
          *rh = rhdn;
          if (kflag < 0 && *rh > 1.)
            *rh = 1.;
        }
      else
        {
          *rh = *rhup;
          if (*rh >= 1.1)
            {
              r = el[l] / (C_FLOAT64) l;
              nq = l;
              l = nq + 1;
              yp1 = yh[l];
              for (i = 1; i <= n; i++)
                yp1[i] = acor[i] * r;
              *orderflag = 2;
              return;
            }
          else
            {
              ialth = 3;
              return;
            }
        }
    }
  /*
    If meth = 1 and h is restricted by stability, bypass 10 percent test.
  */
  if (meth == 1)
    {
      if ((*rh * *pdh * 1.00001) < sm1[newq])
        if (kflag == 0 && *rh < 1.1)
          {
            ialth = 3;
            return;
          }
    }
  else
    {
      if (kflag == 0 && *rh < 1.1)
        {
          ialth = 3;
          return;
        }
    }
  if (kflag <= -2)
    *rh = std::min(*rh, 0.2);
  /*
    If there is a change of order, reset nq, l, and the coefficients.
    In any case h is reset according to rh and the yh array is rescaled.
    Then exit or redo the step.
  */
  if (newq == nq)
    {
      *orderflag = 1;
      return;
    }
  nq = newq;
  l = nq + 1;
  *orderflag = 2;
}      /*   end orderswitch   */

void CLsodaMethod::resetcoeff(void)
/*
  The el vector and related constants are reset whenever the order nq is changed, or at the start of the problem.
 */

{
  C_INT32 i;
  C_FLOAT64 *ep1;

  ep1 = elco[nq];
  for (i = 1; i <= l; i++)
    el[i] = ep1[i];
  rc = rc * el[1] / el0;
  el0 = el[1];
  conit = 0.5 / (C_FLOAT64) (nq + 2);
}     /*   end resetcoeff   */

void CLsodaMethod::eval(C_FLOAT64 t,
                        C_FLOAT64 * y,                    /* Fortran style vector */
                        C_FLOAT64 * ydot)  /* Fortran style vector */
{
  assert (y + 1 == mY);
  mpStateX->setTime(t);

  const_cast<CModel *>(mpStateX->getModel())->getDerivativesX_particles(mpStateX, mYdot);

  memcpy(ydot + 1, mYdot.array(), mYdot.size() * sizeof(C_FLOAT64));
  return;
}
