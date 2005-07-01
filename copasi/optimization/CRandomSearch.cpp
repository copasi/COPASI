/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/CRandomSearch.cpp,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/01 19:27:03 $
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
#include "CRealProblem.h"
#include "randomGenerator/CRandom.h"

//** Taken from COptMethodGA
#include "COptProblem.h"
#include "COptItem.h" 
//#include "utilities/CProcessReport.h"
//#include "report/CCopasiObjectReference.h"
//**** include namespace to fix CRandomSearch is not class or namespace error
#include "CRandomSearch.h"

CRandomSearch::CRandomSearch():
    COptMethod(CCopasiMethod::RandomSearch)
{
  addParameter("Number of Iterations", CCopasiParameter::UINT, (unsigned C_INT32) 100000);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);
}

CRandomSearch::CRandomSearch(const CRandomSearch & src):
    COptMethod(src)
{}

/**
 * Destructor
 */
CRandomSearch::~CRandomSearch()
{//*** added similar to coptga
  cleanup();
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
  bool linear;
  bool Continue = true;

  if (!initialize()) return false;

  C_FLOAT64 la, candx = DBL_MAX;
  mIterations = * getValue("Number of Iterations").pUINT;

  unsigned C_INT32 i, j;

  C_FLOAT64 mn;
  C_FLOAT64 mx;

  for (i = 0; i < mIterations && Continue; i++)
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
              linear = false; la = 1.0;

              if (mn == 0.0) mn = DBL_EPSILON;

              if ((mn < 0.0) || (mx <= 0.0))
                linear = true;
              else
                {
                  la = log10(mx) - log10(mn);
                  if (la < 1.8) linear = true;
                }

              // set it to a random value within the interval
              if (linear)
                mut = mn + mpRandom->getRandomCC() * (mx - mn);
              else
                mut = mn * pow(10, la * mpRandom->getRandomCC());
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
        }

      Continue = evaluate(mIndividual);

      // COMPARE
      if (mValue < mBestValue)
        {
          mBestValue = mValue;
          mpOptProblem->setSolutionVariables(mIndividual);
          Continue = mpOptProblem->setSolutionValue(mBestValue);
        }
    }

  return Continue;
}

// evaluate the fitness of one individual
bool CRandomSearch::evaluate(const CVector< C_FLOAT64 > & individual)
{
  unsigned C_INT32 j;
  bool Continue = true;

  std::vector< UpdateMethod *>::const_iterator itMethod = mpSetCalculateVariable->begin();

  // set the paramter values
  for (j = 0; j < mVariableSize; j++, ++itMethod)
    (**itMethod)(individual[j]);

  // check whether the parametric constraints are fulfilled
  if (!mpOptProblem->checkParametricConstraints())
    {
      mValue = DBL_MAX;
      return Continue;
    }

  // evaluate the fitness
  try
  {Continue = mpOptProblem->calculate();}

  catch (...)
    {
      mValue = DBL_MAX;
      return Continue;
    }

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mValue = DBL_MAX;
  else
    mValue = mpOptProblem->getCalculateValue();

  return Continue;
}
