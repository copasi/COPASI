// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodHookeJeeves.cpp,v $
//   $Revision: 1.10.10.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/31 16:31:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// hoojee.cpp : optimisation by the method of Hooke and Jeeves
//

/* Nonlinear Optimization using the algorithm of Hooke and Jeeves  */
/* 12 February 1994 author: Mark G. Johnson                 */

/* Adapted for Gepasi by Pedro Mendes, 18 August 1997              */

#include <float.h>

#include "copasi.h"
#include "mathematics.h"

#include "COptMethodHookeJeeves.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "report/CCopasiObjectReference.h"

COptMethodHookeJeeves::COptMethodHookeJeeves(const CCopasiContainer * pParent):
    COptMethod(CCopasiTask::optimization, CCopasiMethod::HookeJeeves, pParent)
{
  addParameter("Iteration Limit", CCopasiParameter::UINT, (unsigned C_INT32) 50);
  addParameter("Tolerance", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.e-005);
  addParameter("Rho", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.2);

  initObjects();
}

COptMethodHookeJeeves::COptMethodHookeJeeves(const COptMethodHookeJeeves & src,
    const CCopasiContainer * pParent):
    COptMethod(src, pParent)
{
  initObjects();
}

COptMethodHookeJeeves::~COptMethodHookeJeeves()
{cleanup();}

bool COptMethodHookeJeeves::optimise()
{
  mContinue = true;

  if (!initialize()) return false;

  C_FLOAT64 newf, steplength, tmp;
  bool Keep;
  unsigned C_INT32 iadj;

  // initial point is first guess
  unsigned C_INT32 i;

  // initialise the guess vector
  for (i = 0; i < mVariableSize; i++)
    {
      C_FLOAT64 & mut = mIndividual[i];
      COptItem & OptItem = *(*mpOptItem)[i];

      mut = OptItem.getStartValue();

      // force it to be within the bounds
      switch (OptItem.checkConstraint(mut))
        {
        case - 1:
          mut = *OptItem.getLowerBoundValue();
          break;

        case 1:
          mut = *OptItem.getUpperBoundValue();
          break;
        }

      // We need to set the value here so that further checks take
      // account of the value.
      (*(*mpSetCalculateVariable)[i])(mut);
    }

  mContinue &= evaluate();

  // The first value is also the best
  mBestValue = mEvaluationValue;
  mpOptProblem->setSolution(mBestValue, mIndividual);
  mpParentTask->output(COutputInterface::DURING);

  if (!mContinue)
    {
      cleanup();
      return false;
    }

  for (i = 0; i < mVariableSize; i++)
    {
      mNew[i] = mBefore[i] = mIndividual[i];
      mDelta[i] = fabs(mIndividual[i] * mRho);
      if (mDelta[i] == 0.0) mDelta[i] = mRho;
    }

  iadj = 0;
  steplength = mRho;

  newf = mBestValue;

  while ((mIteration < mIterationLimit) && (steplength > mTolerance) && mContinue)
    {
      // signal another iteration to Gepasi
      if (mpCallBack)
        mContinue &= mpCallBack->progress(mhIteration);

      mIteration++;
      iadj++;

      /* find best new point, one coord at a time */
      mNew = mBefore;

      newf = bestNearby();

      /* if we made some improvements, pursue that direction */
      Keep = true;
      while ((newf < mBestValue) && Keep && mContinue)
        {
          // We found a better value
          mBestValue = newf;
          mpOptProblem->setSolution(mBestValue, mNew);
          mpParentTask->output(COutputInterface::DURING);

          iadj = 0;
          for (i = 0; i < mVariableSize; i++)
            {
              C_FLOAT64 & mut = mNew[i];
              COptItem & OptItem = *(*mpOptItem)[i];

              /* firstly, arrange the sign of mDelta[] */
              if (mut <= mBefore[i])
                mDelta[i] = - fabs(mDelta[i]);
              else
                mDelta[i] = fabs(mDelta[i]);

              /* now, move further in this direction */
              tmp = mBefore[i];
              mBefore[i] = mut;
              mut = mut + mut - tmp;

              // force it to be within the bounds
              switch (OptItem.checkConstraint(mut))
                {
                case - 1:
                  mut = *OptItem.getLowerBoundValue();
                  break;

                case 1:
                  mut = *OptItem.getUpperBoundValue();
                  break;
                }

              // We need to set the value here so that further checks take
              // account of the value.
              (*(*mpSetCalculateVariable)[i])(mut);
            }

          newf = bestNearby();
          /* if the further (optimistic) move was bad.... */
          if (newf >= mBestValue) break;

          /* make sure that the differences between the new */
          /* and the old points are due to actual */
          /* displacements; beware of roundoff errors that */
          /* might cause newf < mBestValue */
          Keep = false;
          for (i = 0; i < mVariableSize; i++)
            if (fabs(mNew[i] - mBefore[i]) > (0.5 * fabs(mDelta[i])))
              {
                Keep = true;
                break;
              }
        }

      if ((steplength >= mTolerance) && (newf >= mBestValue))
        {
          steplength = steplength * mRho;
          for (i = 0; i < mVariableSize; i++)
            mDelta[i] *= mRho;
        }
    }

  cleanup();
  return true;
}

void COptMethodHookeJeeves::initObjects()
{
  addObjectReference("Current Iteration", mIteration, CCopasiObject::ValueInt);
}

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

bool COptMethodHookeJeeves::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mIterationLimit = * getValue("Iteration Limit").pUINT;
  mTolerance = * getValue("Tolerance").pDOUBLE;
  mRho = * getValue("Rho").pDOUBLE;

  mIteration = 0;
  if (mpCallBack)
    mhIteration =
      mpCallBack->addItem("Current Iteration",
                          CCopasiParameter::UINT,
                          & mIteration,
                          & mIterationLimit);

  mVariableSize = mpOptItem->size();

  mIndividual.resize(mVariableSize);
  mBefore.resize(mVariableSize);
  mNew.resize(mVariableSize);
  mDelta.resize(mVariableSize);

  mBestValue = mpOptProblem->getSolutionValue();

  return true;
}

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

bool COptMethodHookeJeeves::cleanup()
{
  return true;
}

bool COptMethodHookeJeeves::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  if (!mpOptProblem->checkParametricConstraints())
    {
      mEvaluationValue = DBL_MAX;
      return mContinue;
    }

  mContinue &= mpOptProblem->calculate();

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mEvaluationValue = 2.0 * DBL_MAX;
  else
    // get the value of the objective function
    mEvaluationValue = mpOptProblem->getCalculateValue();

  return mContinue;
}

// given a point, look for a better one nearby, one coord at a time
C_FLOAT64 COptMethodHookeJeeves::bestNearby()
{
  C_FLOAT64 minf = mBestValue;
  unsigned C_INT32 i;

  mIndividual = mNew;

  for (i = 0; i < mVariableSize; i++)
    (*(*mpSetCalculateVariable)[i])(mIndividual[i]);

  for (i = 0; i < mVariableSize; i++)
    {
      C_FLOAT64 & mut = mIndividual[i];
      COptItem & OptItem = *(*mpOptItem)[i];
      mut = mNew[i] + mDelta[i];

      // force it to be within the bounds
      switch (OptItem.checkConstraint(mut))
        {
        case - 1:
          mut = *OptItem.getLowerBoundValue();
          break;

        case 1:
          mut = *OptItem.getUpperBoundValue();
          break;
        }

      // We need to set the value here so that further checks take
      // account of the value.
      (*(*mpSetCalculateVariable)[i])(mut);

      if (!evaluate()) break;

      if (mEvaluationValue < minf)
        minf = mEvaluationValue;
      else
        {
          mDelta[i] = - mDelta[i];
          mut = mNew[i] + mDelta[i];

          // force it to be within the bounds
          switch (OptItem.checkConstraint(mut))
            {
            case - 1:
              mut = *OptItem.getLowerBoundValue();
              break;

            case 1:
              mut = *OptItem.getUpperBoundValue();
              break;
            }

          // We need to set the value here so that further checks take
          // account of the value.
          (*(*mpSetCalculateVariable)[i])(mut);

          if (!evaluate()) break;

          if (mEvaluationValue < minf)
            minf = mEvaluationValue;
          else
            {
              mut = mNew[i];
              (*(*mpSetCalculateVariable)[i])(mut);
            }
        }
    }

  mNew = mIndividual;

  return(minf);
}

/* Find a point X where the nonlinear function f(X) has a local    */
/* minimum.  X is an n-vector and f(X) is a scalar.  In mathe-    */
/* matical notation  f: R^n -> R^1.  The objective function f()    */
/* is not required to be continuous.  Nor does f() need to be    */
/* differentiable.  The program does not use or require     */
/* derivatives of f().         */

/* The software user supplies three things: a subroutine that    */
/* computes f(X), an initial "starting guess" of the minimum point */
/* X, and values for the algorithm convergence parameters.  Then   */
/* the program searches for a local minimum, beginning from the    */
/* starting guess, using the Direct Search algorithm of Hooke and  */
/* Jeeves.          */

/* This C program is adapted from the Algol pseudocode found in    */
/* "Algorithm 178: Direct Search" by Arthur F. Kaupe Jr., Commun-  */
/* ications of the ACM, Vol 6. p.313 (June 1963).  It includes the */
/* improvements suggested by Bell and Pike (CACM v.9, p. 684, Sept */
/* 1966) and those of Tomlin and Smith, "Remark on Algorithm 178"  */
/* (CACM v.12).  The original paper, which I don't recommend as    */
/* highly as the one by A. Kaupe, is:  R. Hooke and T. A. Jeeves, */
/* "Direct Search Solution of Numerical and Statistical Problems", */
/* Journal of the ACM, Vol. 8, April 1961, pp. 212-229.     */

/* Calling sequence:         */
/*  int hooke(mVariableSize, startpt, endpt, mRho, epsilon, mIterationLimit)    */
/*           */
/*     mVariableSize    {an integer}  This is the number of dimensions  */
/*     in the domain of f().  It is the number of    */
/*     coordinates of the starting point (and the    */
/*     minimum point.)       */
/*     startpt    {an array of C_FLOAT64s}  This is the user-    */
/*     supplied guess at the minimum.     */
/*     endpt    {an array of C_FLOAT64s}  This is the location of  */
/*     the local minimum, calculated by the program    */
/*     mRho    {a C_FLOAT64}  This is a user-supplied convergence */
/*     parameter (more detail below), which should be  */
/*     set to a value between 0.0 and 1.0. Larger    */
/*     values of mRho give greater probability of    */
/*     convergence on highly nonlinear functions, at a */
/*     cost of more function evaluations.  Smaller    */
/*     values of mRho reduces the number of evaluations */
/*     (and the program running time), but increases   */
/*     the risk of nonconvergence. See below.    */
/*     epsilon    {a C_FLOAT64}  This is the criterion for halting   */
/*     the search for a minimum.  When the algorithm   */
/*     begins to make less and less progress on each   */
/*     iteration, it checks the halting criterion: if  */
/*     the stepsize is below epsilon, terminate the    */
/*     iteration and return the current best estimate  */
/*     of the minimum.  Larger values of epsilon (such */
/*     as 1.0e-4) give quicker running time, but a    */
/*     less accurate estimate of the minimum.  Smaller */
/*     values of epsilon (such as 1.0e-7) give longer  */
/*     running time, but a more accurate estimate of   */
/*     the minimum.        */
/*     mIterationLimit    {an integer}  A second, rarely used, halting    */
/*     criterion.  If the algorithm uses >= mIterationLimit    */
/*     iterations, halt.       */

/* The user-supplied objective function f(x,n) should return a C   */
/* "C_FLOAT64".  Its  arguments are  x -- an array of C_FLOAT64s, and    */
/* n -- an integer.  x is the point at which f(x) should be    */
/* evaluated, and n is the number of coordinates of x. That is, */
/* n is the number of coefficients being fitted.     */

/* mRho, the algorithm convergence control      */
/* The algorithm works by taking "steps" from one estimate of */
/*    a minimum, to another (hopefully better) estimate.  Taking   */
/*    big steps gets to the minimum more quickly, at the risk of   */
/*    "stepping right over" an excellent point.  The stepsize is   */
/*    controlled by a user supplied parameter called mRho.  At each */
/*    iteration, the stepsize is multiplied by mRho  (0 < mRho < 1), */
/*    so the stepsize is successively reduced.      */
/* Small values of mRho correspond to big stepsize changes, */
/*    which make the algorithm run more quickly.  However, there   */
/*    is a chance (especially with highly nonlinear functions)    */
/*    that these big changes will accidentally overlook a    */
/*    promising search vector, leading to nonconvergence.    */
/* Large values of mRho correspond to small stepsize changes, */
/*    which force the algorithm to carefully examine nearby points */
/*    instead of optimistically forging ahead. This improves the  */
/*    probability of convergence.       */
/* The stepsize is reduced until it is equal to (or smaller   */
/*    than) epsilon.  So the number of iterations performed by    */
/*    Hooke-Jeeves is determined by mRho and epsilon:     */
/*     mRho**(number_of_iterations) = epsilon     */
/* In general it is a good idea to set mRho to an aggressively */
/*    small value like 0.5 (hoping for fast convergence).  Then, */
/*    if the user suspects that the reported minimum is incorrect  */
/*    (or perhaps not accurate enough), the program can be run    */
/*    again with a larger value of mRho such as 0.85, using the    */
/*    result of the first minimization as the starting guess to    */
/*    begin the second minimization.       */

/* Normal use: (1) Code your function f() in the C language    */
/*        (2) Install your starting guess {or read it in}    */
/*        (3) Run the program       */
/*        (4) {for the skeptical}: Use the computed minimum   */
/*        as the starting point for another run    */

/* Data Fitting:         */
/* Code your function f() to be the sum of the squares of the */
/* errors (differences) between the computed values and the   */
/* measured values.  Then minimize f() using Hooke-Jeeves.    */
/* EXAMPLE: you have 20 datapoints (ti, yi) and you want to   */
/* find A,B,C such that  (A*t*t) + (B*exp(t)) + (C*tan(t))    */
/* fits the data as closely as possible.  Then f() is just    */
/* f(x) = SUM (measured_y[i] - ((A*t[i]*t[i]) + (B*exp(t[i])) */
/*      + (C*tan(t[i]))))^2     */
/* where x[] is a 3-vector consisting of {A, B, C}.    */

/*           */
/*  The author of this software is M.G. Johnson.     */
/*  Permission to use, copy, modify, and distribute this software  */
/*  for any purpose without fee is hereby granted, provided that   */
/*  this entire notice is included in all copies of any software   */
/*  which is or includes a copy or modification of this software   */
/*  and in all copies of the supporting documentation for such    */
/*  software.  THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT    */
/*  ANY EXPRESS OR IMPLIED WARRANTY.  IN PARTICULAR, NEITHER THE   */
/*  AUTHOR NOR AT&T MAKE ANY REPRESENTATION OR WARRANTY OF ANY    */
/*  KIND CONCERNING THE MERCHANTABILITY OF THIS SOFTWARE OR ITS    */
/*  FITNESS FOR ANY PARTICULAR PURPOSE.       */
/*           */
