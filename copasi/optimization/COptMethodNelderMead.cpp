// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// adapted by Stefan Hoops, August 2006, from the original Gepasi file
// nelmea.cpp :

#include <cmath>

#include "copasi/copasi.h"

#include "COptMethodNelderMead.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/core/CDataObjectReference.h"

COptMethodNelderMead::COptMethodNelderMead(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  COptMethod(pParent, methodType, taskType, false)
{
  assertParameter("Iteration Limit", CCopasiParameter::Type::UINT, (unsigned C_INT32) 200);
  assertParameter("Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.e-005);
  assertParameter("Scale", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 10.0);

  initObjects();
}

COptMethodNelderMead::COptMethodNelderMead(const COptMethodNelderMead & src,
    const CDataContainer * pParent):
  COptMethod(src, pParent)
{initObjects();}

COptMethodNelderMead::~COptMethodNelderMead()
{cleanup();}

void COptMethodNelderMead::initObjects()
{
  addObjectReference("Current Iteration", mIteration, CDataObject::ValueInt);
}

/*
  The code for COptMethodNelderMead::optimize() is derived from nelmin.c
  developed by:

       Peter & Nigel,
       Design Software,
       ----------------------
       42 Gubberley St,
       Kenmore, 4069,
       Australia.
 */
/************************************************/
/*                                              */
/*  CMATH.  Copyright (c) 1989 Design Software  */
/*                                              */
/************************************************/

/*
  Purpose ....
  -------
  Find the minimum value of a user-specified function.

  Input ...
  -----
  Fnelmin: User specified function to be minimized. NOTE that
  the function name must be passed.
  double Fnelmin (n, x)
  int    n;
  double x[];
  n      : INTEGER. The number of variables over which we are
  minimizing.
  xmin   : Array [n] of double; contains the coordinates
  of the starting point.  (see note 5)
  reqmin : The terminating limit for the variance of function values.
  step   : Array [n] of double; determines the
  size and shape of the initial simplex.
  The relative magnitudes of its N elements
  should reflect the units of the N variables.
  konvge : The convergence check is carried out every KONVGE
  iterations.
  kcount : Maximum number of function evaluations.
  reltol : relative tolerance on minimum check  (see note 6)
  abstol : absolute tolerance on minimum check  (see note 6)

  Output ...
  ------
  xmin   : Array [id] of double; contains the
  coordinates of the minimum.
  ynewlo : The minimum value of the function.
  icount : Function evaluations performed.
  numres : Number of restarts.
  ifault : return status flag ...
  = 0 No error.
  = 1 REQMIN, N or KONVGE illegal value.
  = 2 Termination because KCOUNT exceeded before convergence.
  = 3 could not allocate memory for workspace

  This C code written by ...  Peter & Nigel,
  ----------------------      Design Software,
  42 Gubberley St,
  Kenmore, 4069,
  Australia.

  Version ... 1.0 November 1987
  -------     2.0 March    1989      reltol, abstol added
  zero subscripts implemented
  2.1 15 April 1989      workspace allocated
  start[] removed from arguements
  2.2 28 April 1989      n added to Fnelmin()
  2.3 7  August  89      fixed true min. check
  2.4 12 Dec   1989      fixed memory (de)allocation

  Notes ...
  -----
  1. This algorithm is a modified version of ..
  Algorithm AS 47 Applied Statistics (J. R. Statist. Soc. C),
  (1971) VOL.20. NO.3

  2. The data values of RCOEFF (reflection), ECOEFF (extension),
  and CCOEFF (contraction) can be changed by rewriting the
  assignment statements below.  The values currently set are 1.0,
  2.0 and 0.5 respectively.  These values have been recommended
  by Nelder and Mead as being best for a general situation.

  3. The value of REQMIN must be set larger than the rounding
  error in computing the variance at the minimum.  This holds
  for both Double and Single precision calculations.
  Chambers and Ertel recommend that REQMIN be set to a value
  somewhere between the required accuracy of the function at
  the minimum and the square of this value.

  4. Note that the elements [0 .. n-1] are utilized in this
  version of the routine.

  6. reltol and abstol should be set to zero for well behaved
  functions where restarts are not a problem.

  7. References ...
  Nelder, J.A. and Mead, R. (1965) A simplex method for function
  minimization. Computer J. 7,308-313

  O'Neill, R. (1971) Algorithm AS47. Function minimization
  using a simplex algorithm. Appl. Statist. 20,338-345.

  Chambers, J.M. and Ertel, J.E. (1974) Remark AS R11.
  Appl. Statist. 23,250-251.

  Olsson, D.M. and Nelson, L.S. (1975) The Nelder - Mead
  simplex procedure for function minimization.
  Technometrics 17,45-51. (Examples of use.)

  Benyon, P.R. (1976) Remark AS R15. Appl. Statist. 25,97.

  Hill, I.D. (1978) Remark AS R28. Appl. Statist. 27,380-382.

  ----------------------------------------------------------------------
 */

bool COptMethodNelderMead::optimise()
{
  if (!initialize())
    {
      if (mProcessReport)
        mProcessReport.finishItem(mhIteration);

      return false;
    }

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Algorithm started.",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Nelder_-_Mead/"
      )
    );

  // set tolerances for local minima test to zero
  C_FLOAT64 abstol, reltol;
  abstol = reltol = 0.0;

  // test convergence every iteration
  size_t konvge;
  konvge = 1;

  size_t iBest, iWorst;

  // double zero, half, one, delta;
  C_FLOAT64 ccoeff, rcoeff, ecoeff;

  /* ---- reflection, extension and contraction coefficients. ---- */
  /* parameters from Nelder and Mead */
  //rcoeff = 1.0;
  //ccoeff = 0.5;
  //ecoeff = 2.0;

  /* Parameters from Parkinson and Hutchinson */
  rcoeff = 2.0;
  ccoeff = 0.25;
  ecoeff = 2.5;

  C_FLOAT64 z, sum, ylo;
  C_FLOAT64 curmin, del, x, yhi;
  C_FLOAT64 small;
  C_FLOAT64 factor = 0.8;

  size_t jcount, np1, i, j;

  bool ok, reflok, extnok, contok, quit, found;  /* boolean variables */

  // initial point is first guess but we have to make sure that we
  // are within the parameter domain
  bool pointInParameterDomain = true;

  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[i];

      switch (OptItem.checkConstraint(OptItem.getStartValue()))
        {
          case - 1:
            mCurrent[i] = *OptItem.getLowerBoundValue();
            pointInParameterDomain = false;
            break;

          case 1:
            mCurrent[i] = *OptItem.getUpperBoundValue();
            pointInParameterDomain = false;
            break;

          case 0:
            mCurrent[i] = OptItem.getStartValue();
            break;
        }

      *mProblemContext.master()->getContainerVariables(true)[i] = (mCurrent[i]);

      // set the magnitude of each parameter
      mStep[i] = (*OptItem.getUpperBoundValue() - *OptItem.getLowerBoundValue()) / mScale;
    }

  if (!pointInParameterDomain && (mLogVerbosity > 0))
    mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));

  evaluate();

  if (!std::isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mEvaluationValue;
      mContinue &= mProblemContext.master()->setSolution(mBestValue, mCurrent, true);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  quit = false;
  found = false;

  np1 = mVariableSize + 1;
  del = 1.0;

First:

  /* ---- Construct the initial simplex. ---- */
  for (i = 0; i < mVariableSize; ++i)
    mSimplex[i][mVariableSize] = mCurrent[i];

  mValue[mVariableSize] = mEvaluationValue;

  for (j = 0; j < mVariableSize && mContinue; ++j)
    {
      x = mCurrent[j];

      // -- move a little in one dimension only --
      mCurrent[j] += (mStep[j] * del);

      // Check constraint
      const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];

      if (mCurrent[j] > *OptItem.getUpperBoundValue())
        mCurrent[j] = x - (mStep[j] * del);

      // Store the simplex corner
      for (i = 0; i < mVariableSize; ++i)
        mSimplex[i][j] = mCurrent[i];

      // Calculate the value for the corner
      *mProblemContext.master()->getContainerVariables(true)[j] = (mCurrent[j]);
      mValue[j] = evaluate();

      if (mEvaluationValue < mBestValue)
        {
          // and store that value
          mBestValue = mEvaluationValue;
          mContinue &= mProblemContext.master()->setSolution(mBestValue, mCurrent, true);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);
        }

      // Reset
      mCurrent[j] = x;
      *mProblemContext.master()->getContainerVariables(true)[j] = (mCurrent[j]);
    }

  /* ---- Simplex construction complete; now do some work. ---- */

  while (!found && !quit && mContinue)
    {
      /* ---- take some steps ---- */

      for (jcount = 1; jcount <= konvge; ++jcount)
        {
          /* ---- take a single step ---- */

          /* ---- find highest and lowest y values.  yhi (=y[iWorst]) indicates
             the vertex of the simplex to be replaced.   */

          ylo = mValue[0];
          yhi = ylo;
          iBest = 0;
          iWorst = 0;

          for (i = 1; i < np1; ++i)
            {
              if (mValue[i] < ylo)     /* -- find the lowest value of the objective  */
                {
                  ylo = mValue[i];
                  iBest = i;
                }

              if (mValue[i] > yhi)    /* -- find the highest value of the objective -- */
                {
                  yhi = mValue[i];
                  iWorst = i;
                }
            }

          /* ---- Calculate mCentroid, the centroid of the simplex vertices
             excepting that with the y value yhi. (largest objective value)  */

          for (i = 0; i < mVariableSize; ++i)
            {
              /* -- calculate the average in each dimension -- */
              z = 0.0;

              for (j = 0; j < np1; ++j)
                z += mSimplex[i][j];

              z -= mSimplex[i][iWorst];
              mCentroid[i] = z / mVariableSize;
            }

          /* ---- reflection through the centroid. ---- */

          for (i = 0; i < mVariableSize; ++i)
            {
              mCurrent[i] = (1.0 + rcoeff) * mCentroid[i] - rcoeff * mSimplex[i][iWorst];
              *mProblemContext.master()->getContainerVariables(true)[i] = (mCurrent[i]);

              // enforce_bounds(&pstar[i], i);  /* make sure it is inside */
            }

          evaluate();
          reflok = (mEvaluationValue < ylo);    /* -- 1 if we have moved downhill -- */

          if (reflok) /* then */
            {
              ylo = mEvaluationValue;

              for (i = 0; i < mVariableSize; ++i)
                mSimplex[i][iWorst] = mCurrent[i];

              mValue[iWorst] = ylo;

              // and store that value
              if (mEvaluationValue < mBestValue)
                {
                  mBestValue = mEvaluationValue;
                  mContinue &= mProblemContext.master()->setSolution(mBestValue, mCurrent, true);

                  // We found a new best value lets report it.
                  mpParentTask->output(COutputInterface::DURING);
                }

              /* ---- successful reflection, so be bold and try extension */
              for (i = 0; i < mVariableSize; ++i)
                {
                  mCurrent[i] = ecoeff * mCurrent[i] + (1.0 - ecoeff) * mCentroid[i];
                  *mProblemContext.master()->getContainerVariables(true)[i] = (mCurrent[i]);

                  // enforce_bounds(&p2star[i], i);  /* make sure it is inside */
                }

              evaluate();
              extnok = (mEvaluationValue < ylo);    /* -- 1 if we continue moved downhill -- */

              if (extnok)
                {
                  /* ---- retain extension ---- */
                  ylo = mEvaluationValue;

                  for (i = 0; i < mVariableSize; ++i)
                    mSimplex[i][iWorst] = mCurrent[i];

                  mValue[iWorst] = ylo;

                  // and store that value
                  if (mEvaluationValue < mBestValue)
                    {
                      mBestValue = mEvaluationValue;
                      mContinue &= mProblemContext.master()->setSolution(mBestValue, mCurrent, true);

                      // We found a new best value lets report it.
                      mpParentTask->output(COutputInterface::DURING);
                    }
                }
            }   /* successful reflection */
          else    /* if reflok then else */
            {
              /* ---- reflection has not been successful.  ystar is the function
                 value at the extended point.  now look at the other points
                 of the simplex ...
                 if there are none > ystar then contract to a point within the simplex
                 if there is one   > ystar then reduce the size of the extension
                 if there are many > ystar then retain the reflection as is.  */

              size_t L = 0;

              for (i = 0; i < np1; ++i)
                if (mValue[i] > mEvaluationValue)
                  L++;

              if (L == 1) /* then */
                {
                  /* ---- reflection was not successful but we can try reducing the
                     extension by contracting on the reflection side of the centroid.
                     Record the reflection for the contraction below. */
                  for (i = 0; i < mVariableSize; ++i)
                    mSimplex[i][iWorst] = mCurrent[i];

                  mValue[iWorst] = mEvaluationValue;
                }

              if (L == 0 || L == 1) /* then */

                {
                  /* L == 0 : there are no other points with higher objectives so
                     try a contraction on the y(iWorst) side of the centroid.
                     i.e. within the simplex.
                     L == 1 : there is one other point with a higher objective so
                     try a contraction on the reflection side of the centroid.  */
                  for (i = 0; i < mVariableSize; ++i)
                    {
                      mCurrent[i] = ccoeff * mSimplex[i][iWorst] + (1.0 - ccoeff) * mCentroid[i];
                      *mProblemContext.master()->getContainerVariables(true)[i] = (mCurrent[i]);

                      // may not need to check boundaries since it is contraction
                      // enforce_bounds(&p2star[i], i);  /* make sure it is inside */
                    }

                  evaluate();
                  contok = (mEvaluationValue <= mValue[iWorst]);  /* -- 1 if we have not gone uphill -- */

                  if (contok) /* then */
                    {
                      /* ---- retain contraction ---- */
                      for (i = 0; i < mVariableSize; ++i)
                        mSimplex[i][iWorst] = mCurrent[i];

                      mValue[iWorst] = mEvaluationValue;
                    }
                  else
                    {
                      /* ---- contract whole simplex about a point within itself
                         but close to the current minimum. ---- */
                      for (j = 0; j < np1; ++j)
                        {
                          for (i = 0; i < mVariableSize; ++i)
                            {
                              mSimplex[i][j] = (mSimplex[i][j] + mSimplex[i][iBest]) * 0.5;
                              mCurrent[i] = mSimplex[i][j];
                              *mProblemContext.master()->getContainerVariables(true)[i] = (mCurrent[i]);

                              //enforce_bounds(&xmin[i], i);  /* make sure it is inside */
                            }

                          mValue[j] = evaluate();

                          if (mEvaluationValue < mBestValue)
                            {
                              /* ---- retain extension ---- */
                              // and store that value
                              mBestValue = mEvaluationValue;
                              mContinue &= mProblemContext.master()->setSolution(mBestValue, mCurrent, true);

                              // We found a new best value lets report it.
                              mpParentTask->output(COutputInterface::DURING);
                            }
                        }
                    }  /* if (contok) */
                }  /* contraction */
              else   /* if (L == 0) or (L == 1) then else */
                {
                  /* ---- Retain the first reflection as there are many points in
                     the simplex that have higher objective values than
                     this new point.  A change is better than nothing. ---- */
                  for (i = 0; i < mVariableSize; ++i)
                    mSimplex[i][iWorst] = mCurrent[i];

                  mValue[iWorst] = mEvaluationValue;
                }
            }   /* if Reflok then else .. */
        }   /* ---- procedure TakeAStep ----*/

      /* are we over the limit for number of function evaluations ? */
      //  quit = (icount > kcount);
      // are we above the iteration limit?
      ++mIteration;

      // signal another iteration
      if (mProcessReport)
        mContinue &= mProcessReport.progressItem(mhIteration);

      mpParentTask->output(COutputInterface::MONITORING);

      quit = (mIteration >= mIterationLimit);

      if (!quit) /* then */
        {
          /* ---- check to see if minimum reached.
            calculation of the variance must be done in the highest
            precision available. ---- */

          /* mean */
          sum = 0.0;
          curmin = 0.0;

          for (i = 0; i < np1; ++i)
            {
              sum += mValue[i];
              curmin += mValue[i] * mValue[i];
            }

          sum /= np1;
          curmin /= np1;

          /* ---- curmin is the variance of the n+1 Fnelmin values at the
             vertices.  If we haven't reached the minimum to the
             required accuracy then take a few more steps.    */
          found = (sqrt(curmin - sum * sum) < mTolerance);
        }
    }   /* while not found and not quit ... */

  if (mLogVerbosity > 0 && found)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Iteration " + std::to_string(mIteration) + ": Variance of the objective function values at the vertices of the simplex are lower than tolerance. Checking whether local minimum was found."
      ));

  /* **** bail out if necessary **** */
  if (quit || !mContinue) goto Finish;

  /* ---- Check around the currently selected point to see if it is a local minimum.  */
  small = fabs(mBestValue) * reltol + abstol;
  mCurrent = mProblemContext.master()->getSolutionVariables(true);

  for (i = 0; i < mVariableSize; ++i)
    *mProblemContext.master()->getContainerVariables(true)[i] = (mCurrent[i]);

  for (i = 0; i < mVariableSize; ++i)
    {
      /* ---- check along each dimension ---- */
      C_FLOAT64 delta = mStep[i] * 1.0e-03;

      /* -- check along one direction -- */
      *mProblemContext.master()->getContainerVariables(true)[i] = (mCurrent[i] + delta);
      evaluate();

      if ((mEvaluationValue - mBestValue) < -small)
        break;

      /* -- now check the other way -- */
      *mProblemContext.master()->getContainerVariables(true)[i] = (mCurrent[i] - delta);
      evaluate();

      if ((mEvaluationValue - mBestValue) < -small)
        break;

      /* -- back to start -- */
      *mProblemContext.master()->getContainerVariables(true)[i] = (mCurrent[i]);
    }

  ok = (i == mVariableSize);

  /* ---- return on finding a local minimum to the desired accuracy. ---- */

  if (ok)
    {
      if (mLogVerbosity > 0)
        mMethodLog.enterLogEntry(
          COptLogEntry(
            "Iteration " + std::to_string(mIteration) + ": Found a local minimum. Terminating."
          )
        );

      goto Finish;
    }

  /* ---- Reduce the size of the simplex and restart the procedure. ---- */

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Iteration " + std::to_string(mIteration) + ": No local minimum found. Reducing simplex size."
      ));

  found = 0;   /* -- we did not find a 1 minimum -- */
  del = std::max(del * factor, 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon());

  goto First;

Finish:  /* end of procedure */

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry("Algorithm finished.",
                   "Terminated after " + std::to_string(mIteration) + " of " + std::to_string(mIterationLimit) + " iterations."
                  ));

  if (mProcessReport)
    mProcessReport.finishItem(mhIteration);

  return true;
}

bool COptMethodNelderMead::cleanup()
{
  return true;
}

const C_FLOAT64 & COptMethodNelderMead::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  mContinue &= mProblemContext.master()->calculate();
  mEvaluationValue = mProblemContext.master()->getCalculateValue();

  // when we leave the either the parameter or functional domain
  // we penalize the objective value by forcing it to be larger
  // than the best value recorded so far.
  if (mEvaluationValue < mBestValue &&
      (!mProblemContext.master()->checkParametricConstraints() ||
       !mProblemContext.master()->checkFunctionalConstraints()))
    mEvaluationValue = mBestValue + mBestValue - mEvaluationValue;

  return mEvaluationValue;
}

bool COptMethodNelderMead::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mIterationLimit = getValue< unsigned C_INT32 >("Iteration Limit");
  mTolerance = getValue< C_FLOAT64 >("Tolerance");
  mScale = getValue< C_FLOAT64 >("Scale");

  mIteration = 0;

  if (mProcessReport)
    mhIteration =
      mProcessReport.addItem("Current Iteration",
                             mIteration,
                             & mIterationLimit);

  mVariableSize = mProblemContext.master()->getOptItemList(true).size();

  mSimplex.resize(mVariableSize, mVariableSize + 1);
  mValue.resize(mVariableSize + 1);
  mCentroid.resize(mVariableSize);

  mCurrent.resize(mVariableSize);
  mStep.resize(mVariableSize);

  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();

  mContinue = true;

  return true;
}

unsigned C_INT32 COptMethodNelderMead::getMaxLogVerbosity() const
{
  return 1;
}

C_FLOAT64 COptMethodNelderMead::getBestValue() const
{
  return mBestValue;
}

C_FLOAT64 COptMethodNelderMead::getCurrentValue() const
{
  return mBestValue;
}

const CVector< C_FLOAT64 > * COptMethodNelderMead::getBestParameters() const
{
  return &mCurrent;
}

const CVector< C_FLOAT64 > * COptMethodNelderMead::getCurrentParameters() const
{
  return &mCurrent;
}
