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
    COptMethod()
{
  setName("RandomSearch");
  mTypeEnum = COptMethod::RandomSearch;
  setType(COptMethod::TypeName[mTypeEnum]);

  add("RandomSearch.Iterations", 100000.0);
  add("RandomSearch.RandomGenerator.Type", CRandom::mt19937);
  add("RandomSearch.RandomGenerator.Seed", 0);
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
  C_INT32 j, jmax = mParameters->size();

  /* Create a random number generator */
  CRandom::Type Type;
  Type = (CRandom::Type) (C_INT32) getValue("RandomSearch.RandomGenerator.Type");
  unsigned C_INT32 Seed;
  Seed = (unsigned C_INT32) getValue("RandomSearch.RandomGenerator.Seed");
  CRandom * pRand = CRandom::createGenerator(Type, Seed);

  assert(pRand);

  C_FLOAT64 * Minimum = mParameterMin->array();
  C_FLOAT64 * Maximum = mParameterMax->array();
  C_FLOAT64 * Parameter = mParameters->array();

  for (i = 0; i < imax; i++)
    {
      //change parameters randomly
      for (j = 0; j < jmax; j++)
        {
          linear = false;
          la = 1.0;

          if (Minimum[j] == 0.0) Minimum[j] = DBL_EPSILON;

          if ((Maximum[j] <= 0.0) || (Minimum[j] <= 0.0)) linear = true;

          else
            {
              la = log10(Maximum[j]) - log10(Minimum[j]);
              if (la < 1.8) linear = true;
            }

          if (linear)
            Parameter[j] =
              Minimum[j] + pRand->getRandomCC() * (Maximum[j] - Minimum[j]);
          else
            Parameter[j] = Minimum[j] * pow(10, la * pRand->getRandomCC());
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
          mOptProblem->setBestValue(x);
          std::cout << "Best value (" << i << "): " << x << std::endl;
          candx = x;

          //store the combination of parameter values
          mOptProblem->getBestParameter() = *mParameters;

          std::cout << "Best Parameters: (";
          for (C_INT32 p = 0; p < mOptProblem->getParameterNum(); p++)
            std::cout << mOptProblem->getParameter(p) << ", ";

          std::cout << ")" << std::endl;
        }
    }

  pdelete(pRand);

  return 0;
}
