/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/CRandomSearch.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/18 02:58:23 $
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

CRandomSearch::CRandomSearch():
    COptMethod(CCopasiMethod::RandomSearch)
{
  addParameter("RandomSearch.Iterations",
               CCopasiParameter::UINT,
               (unsigned C_INT32) 100000);
  addParameter("RandomSearch.RandomGenerator.Type",
               CCopasiParameter::INT,
               (C_INT32) CRandom::mt19937);
  addParameter("RandomSearch.RandomGenerator.Seed",
               CCopasiParameter::INT,
               (C_INT32) 0);
}

CRandomSearch::CRandomSearch(const CRandomSearch & src):
    COptMethod(src)
{}

/**
 * Destructor
 */
CRandomSearch::~CRandomSearch(){}

/**
 * Optimizer Function
 * Returns: nothing
 */
C_INT32 CRandomSearch::optimise()
{
  bool linear;
  C_FLOAT64 la, x, candx = DBL_MAX;
  C_INT32 i, imax = (C_INT32) getValue("RandomSearch.Iterations");
  C_INT32 j, jmax = mOptProblem->getVariableSize();

  /* Create a random number generator */
  CRandom::Type Type;
  Type = (CRandom::Type) (C_INT32) getValue("RandomSearch.RandomGenerator.Type");
  unsigned C_INT32 Seed;
  Seed = (unsigned C_INT32) getValue("RandomSearch.RandomGenerator.Seed");
  CRandom * pRand = CRandom::createGenerator(Type, Seed);

  assert(pRand);

  const double ** Minimum = mOptProblem->getParameterMin().array();
  const double ** Maximum = mOptProblem->getParameterMax().array();

  CVector< C_FLOAT64 > & Parameter = mOptProblem->getCalculateVariables();

  for (i = 0; i < imax; i++)
    {
      //change parameters randomly
      for (j = 0; j < jmax; j++)
        {
          linear = false;
          la = 1.0;

          if ((*Maximum[j] <= 0.0) || (*Minimum[j] < 0.0)) linear = true;
          else
            {
              la = log10(*Maximum[j]) - log10(std::min(*Minimum[j], DBL_EPSILON));
              if (la < 1.8) linear = true;
            }

          if (linear)
            Parameter[j] =
              *Minimum[j] + pRand->getRandomCC() * (*Maximum[j] - *Minimum[j]);
          else
            Parameter[j] = *Minimum[j] * pow(10, la * pRand->getRandomCC());
        } // j<..getParameterNum() loop ends

      // check parametric constraints
      if (!mOptProblem->checkParametricConstraints()) continue;

      // calculate the function in the problem
      x = mOptProblem->calculate();

      // check if better than previously stored
      if (x < candx)
        {
          if (!mOptProblem->checkFunctionalConstraints())
            continue;
          //set best value
          mOptProblem->setSolutionValue(x);
          candx = x;

          //store the combination of parameter values
          mOptProblem->getSolutionVariables() = Parameter;
        }
    }

  pdelete(pRand);

  return 0;
}
