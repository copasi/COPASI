/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodSteepestDescent.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/08/09 16:52:27 $
   End CVS Header */

#include "copasi.h"

#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "FminBrent.h"

#include "report/CCopasiObjectReference.h"

COptMethodSteepestDescent::COptMethodSteepestDescent(const CCopasiContainer * pParent):
    COptMethod(CCopasiMethod::SteepestDescent, pParent),
    mpDescent(new FDescentTemplate<COptMethodSteepestDescent>(this, &COptMethodSteepestDescent::descentLine))
{
  addParameter("Iteration Limit", CCopasiParameter::UINT, (unsigned C_INT32) 50);
  addParameter("Tolerance", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.001);
}

COptMethodSteepestDescent::COptMethodSteepestDescent(const COptMethodSteepestDescent & src,
    const CCopasiContainer * pParent): COptMethod(src, pParent),
    mpDescent(new FDescentTemplate<COptMethodSteepestDescent>(this, &COptMethodSteepestDescent::descentLine))
{}

COptMethodSteepestDescent::~COptMethodSteepestDescent()
{
  pdelete(mpDescent);

  cleanup();
}

bool COptMethodSteepestDescent::setCallBack(CProcessReport * pCallBack)
{
  CCopasiMethod::setCallBack(pCallBack);

  /*  pCallBack->addItem(...);*/

  return true;
}

bool COptMethodSteepestDescent::optimise()
{
  if (!initialize()) return false;

  C_INT32 i, k;
  C_FLOAT64 tmp, x0, alpha, mn, mx, norm, daux, fmn, fmx;
  bool calc_grad;

  // initial point is first guess even though it might be outside the domain
  for (i = 0; i < mVariableSize; i++)
    mIndividual[i] = *(*mpOptItem)[i]->getObjectValue();

  fmx = mBestValue = evaluate();

  for (mCurrentIteration = 0; mCurrentIteration < mIterations && mContinue; mCurrentIteration++)
    {
      // calculate the direction of steepest descent
      // by central finite differences
      gradient();
      // minimise the function in this direction
      // find brackets for the minimisation
      //  mn = 0.0; md = 1.0;
      //  mnbrak(&mn, &md, &mx, &fmn, &fmd, &fmx, descent_line);
      // make sure that no parameter will exceed its bounds
      x0 = DBL_MAX;

      for (i = 0; i < mVariableSize; i++)
        {
          if (fabs(mGradient[i]) > DBL_EPSILON)
            {
              if (mGradient[i] > 0)
                {
                  tmp = *(*mpOptItem)[i]->getUpperBoundValue();
                }

              else
                {
                  tmp = *(*mpOptItem)[i]->getLowerBoundValue();
                }

              // calculate the size of the largest jump
              tmp = (tmp - mIndividual[i]) / mGradient[i];
              // keep it if it is the smallest
              if (tmp < x0) x0 = tmp;
            }
          else mGradient[i] = 0.0;
        }

      // we will move at a rate of 1/10 this size
      mn = mx = alpha = 0.0;

      for (k = 0, calc_grad = false; (k < 9) && !calc_grad; k++)
        {
          // set the minimum to the last successful step
          mn = mx;
          fmn = fmx;
          // increment alpha
          alpha += 0.1 * x0;
          // set the maximum to it
          mx = alpha;
          // take one step in that direction
          for (i = 0, norm = 0.0; i < mVariableSize; i++)
            {
              (*(*mpSetCalculateVariable)[i])(mIndividual[i] + alpha * mGradient[i]);
              if ((daux = fabs(alpha * mGradient[i])) > norm) norm = daux;
            }

          fmx = evaluate();

          // if this was an upward step find the minimum
          if (fmx > fmn)
            {
              //md = mn + (mx-mn)/2;
              //Brent(mn, md, mx, descent_line, &alpha, &tmp, 1e-6, 50);

              FminBrent(mn, mx, mpDescent, &alpha, &tmp, mTolerance, 5);
              // take one step in that direction
              for (i = 0, norm = 0.0; i < mVariableSize; i++)
                {
                  (*(*mpSetCalculateVariable)[i])(mIndividual[i] + alpha * mGradient[i]);
                  if ((daux = fabs(alpha * mGradient[i])) > norm) norm = daux;
                }

              fmx = evaluate();

              // time to evaluate the new steepest descent direction
              calc_grad = true;
            }
          // check if this aproximation is good enough
          if (fabs(fmx - mBestValue) < mTolerance)
            //   if(norm < mTolerance)
            {
              // an acceptable solution
              mBestValue = fmx;
              for (i = 0; i < mVariableSize; i++)
                mIndividual[i] = *(*mpOptItem)[i]->getObjectValue();
              mpOptProblem->setSolutionVariables(mIndividual);
              mContinue = mpOptProblem->setSolutionValue(mBestValue);
              mpParentTask->doOutput();
              return true;
            }
        }
      // this is the best approximation thus far
      mBestValue = fmx;
      for (i = 0; i < mVariableSize; i++)
        mIndividual[i] = *(*mpOptItem)[i]->getObjectValue();

      //if(callback != NULL) callback(mBestValue);
      if (!isnan(mBestValue))
        {
          mpOptProblem->setSolutionVariables(mIndividual);
          mContinue = mpOptProblem->setSolutionValue(mBestValue);

          // We found a new best value lets report it.
          //if (mpReport) mpReport->printBody();
          mpParentTask->doOutput();
        }
    }

  return false;
}

bool COptMethodSteepestDescent::cleanup()
{
  // pdelete all used variables
  return true;
}

bool COptMethodSteepestDescent::initialize()
{
  if (!COptMethod::initialize()) return false;

  mIterations = * getValue("Iteration Limit").pUINT;
  mTolerance = * getValue("Tolerance").pDOUBLE;

  mContinue = true;
  mVariableSize = mpOptItem->size();
  mIndividual.resize(mVariableSize);
  mGradient.resize(mVariableSize);

  return true;
}

void COptMethodSteepestDescent::gradient()
{
  unsigned C_INT32 i;

  C_FLOAT64 y;
  C_FLOAT64 x;

  y = evaluate();

  for (i = 0; i < mVariableSize && mContinue; i++)
    {
      if ((x = *(*mpOptItem)[i]->getObjectValue()) != 0.0)
        {
          (*(*mpSetCalculateVariable)[i])(x * 1.001);
          mGradient[i] = (y - evaluate()) / (x * 0.001);
        }

      else
        {
          (*(*mpSetCalculateVariable)[i])(1e-7);
          mGradient[i] = (y - evaluate()) / 1e-7;
        }

      (*(*mpSetCalculateVariable)[i])(x);
    }
}

const C_FLOAT64 COptMethodSteepestDescent::descentLine(const C_FLOAT64 & x)
{
  for (C_INT32 i = 0; i < mVariableSize; i++)
    (*(*mpSetCalculateVariable)[i])(mIndividual[i] + x * mGradient[i]);

  return evaluate();
}

// evaluate the fitness of one individual
const C_FLOAT64 & COptMethodSteepestDescent::evaluate()
{
  // evaluate the fitness
  mContinue = mpOptProblem->calculate();

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mValue = DBL_MAX;
  else
    mValue = mpOptProblem->getCalculateValue();

  return mpOptProblem->getCalculateValue();
}

void COptMethodSteepestDescent::initObjects()
{
  addObjectReference("Current Iteration", mCurrentIteration, CCopasiObject::ValueInt);
}
