/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/CRandomSearch.cpp,v $
   $Revision: 1.23 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/08/11 20:37:04 $
   End CVS Header */

/***************************************************************************
                  CRandomSearch.cpp  -  Random Optimizer
                     -------------------
 
Programmer           : Rohan Luktuke
email                : rluktuke@vt.edu
 ***************************************************************************/

/***************************************************************************
 * This is the implementation of the Random Algorithm for Optimization.  The
 * class is inherited from the COptAlgorithm class
 ***************************************************************************/

#include "copasi.h"

#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "CRandomSearch.h"

#include "report/CCopasiObjectReference.h"
#include "randomGenerator/CRandom.h"

CRandomSearch::CRandomSearch():
    COptMethod(CCopasiMethod::RandomSearch)
{
  addParameter("Number of Iterations", CCopasiParameter::UINT, (unsigned C_INT32) 100000);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

CRandomSearch::CRandomSearch(const CRandomSearch & src):
    COptMethod(src)
{initObjects();}

/**
 * Destructor
 */
CRandomSearch::~CRandomSearch()
{//*** added similar to coptga
  cleanup();
}

void CRandomSearch::initObjects()
{
  addObjectReference("Current Iteration", mCurrentIteration, CCopasiObject::ValueInt);
}

#ifdef WIN32 
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

/**
 * Optimizer Function
 * Returns: true if properly initialized
 //*** should return a boolean
 */
bool CRandomSearch::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mIterations = * getValue("Number of Iterations").pUINT;
  mpRandom = CRandom::createGenerator(* (CRandom::Type *) getValue("Random Number Generator").pUINT,
                                      * getValue("Seed").pUINT);

  mBestValue = DBL_MAX * 2.0;

  mVariableSize = mpOptItem->size();
  mIndividual.resize(mVariableSize);

  return true;
}

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

/**
 * Optimizer Function
 * Returns: nothing
 //*** should return a boolean
 */ 
//C_INT32 CRandomSearch::optimise()
bool CRandomSearch::optimise()
{
  bool Continue = true;

  if (!initialize()) return false;

  C_FLOAT64 la;

  unsigned C_INT32 j;

  C_FLOAT64 mn;
  C_FLOAT64 mx;

  for (mCurrentIteration = 0; mCurrentIteration < mIterations && Continue; mCurrentIteration++)
    {
      for (j = 0; j < mVariableSize && Continue; j++)
        {
          // CALCULATE lower and upper bounds
          COptItem & OptItem = *(*mpOptItem)[j];
          mn = *OptItem.getLowerBoundValue();
          mx = *OptItem.getUpperBoundValue();

          C_FLOAT64 & mut = mIndividual[j];

          try
            {
              // determine if linear or log scale
              if ((mn < 0.0) || (mx <= 0.0))
                mut = mn + mpRandom->getRandomCC() * (mx - mn);
              else
                {
                  la = log10(mx) - log10(std::max(mn, DBL_MIN));

                  if (la < 1.8)
                    mut = mn + mpRandom->getRandomCC() * (mx - mn);
                  else
                    mut = pow(10, log10(std::max(mn, DBL_MIN)) + la * mpRandom->getRandomCC());
                }
            }

          catch (...)
            {
              mut = (mx + mn) * 0.5;
            }

          // force it to be within the bounds
          switch (OptItem.checkConstraint(mut))
            {
            case - 1:
              mut = *OptItem.getLowerBoundValue();
              if (!OptItem.checkLowerBound(mut)) // Inequality
                {
                  if (mut == 0.0)
                    mut = DBL_MIN;
                  else
                    mut += mut * DBL_EPSILON;
                }
              break;

            case 1:
              mut = *OptItem.getUpperBoundValue();
              if (!OptItem.checkUpperBound(mut)) // Inequality
                {
                  if (mut == 0.0)
                    mut = - DBL_MIN;
                  else
                    mut -= mut * DBL_EPSILON;
                }
              break;
            }

          // We need to set the value here so that further checks take
          // account of the value.
          (*(*mpSetCalculateVariable)[j])(mut);
        }

      Continue = evaluate(mIndividual);

      // COMPARE
      if (mValue < mBestValue && !isnan(mValue))
        {
          mBestValue = mValue;
          mpOptProblem->setSolutionVariables(mIndividual);
          Continue = mpOptProblem->setSolutionValue(mBestValue);

          // We found a new best value lets report it.
          //if (mpReport) mpReport->printBody();
          mpParentTask->doOutput();
        }
    }

  return Continue;
}

// evaluate the fitness of one individual
bool CRandomSearch::evaluate(const CVector< C_FLOAT64 > & individual)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  Continue = mpOptProblem->calculate();

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mValue = DBL_MAX;
  else
    mValue = mpOptProblem->getCalculateValue();

  return Continue;
}
