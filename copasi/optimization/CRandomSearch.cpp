/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/CRandomSearch.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2005/06/21 20:38:30 $
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
  /*addParameter("RandomSearch.Iterations",
               CCopasiParameter::UINT,
               (unsigned C_INT32) 100000);
  addParameter("RandomSearch.RandomGenerator.Type",
               CCopasiParameter::INT,
               (C_INT32) CRandom::mt19937);
  addParameter("RandomSearch.RandomGenerator.Seed",
               CCopasiParameter::INT,
               (C_INT32) 0); */ 
  //*** Redefined changing the names displayed
  addParameter("Number of Iterations",
               CCopasiParameter::UINT,
               (unsigned C_INT32) 100000);
  addParameter("Random Generator Type",
               CCopasiParameter::INT,
               (C_INT32) CRandom::mt19937);
  addParameter("Seed",
               CCopasiParameter::INT,
               (C_INT32) 0);
  //*** added random number generator parameter
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
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
/**
 * Optimizer Function
 * Returns: true if properly initialized
//*** should return a boolean
 */
bool CRandomSearch::initialize()
{
  //unsigned C_INT32 i;

  if (!COptMethod::initialize()) return false;

  //C_FLOAT64 la, x, candx = DBL_MAX;
  C_FLOAT64 candx = DBL_MAX;
  //C_INT32 i, imax = (C_INT32) getValue("Number of Iterations");
  mIterations = * getValue("Number of Iterations").pUINT;
  //C_INT32 j, jmax = mpOptProblem->getVariableSize();
  //C_INT32 jmax = mpOptProblem->getVariableSize();
  //mGenerations = * (unsigned C_INT32 *) getValue("Number of Generations");
  //mPopulationSize = * (unsigned C_INT32 *) getValue("Population Size");
  mpRandom = CRandom::createGenerator(* (CRandom::Type *) getValue("Random Number Generator").pUINT,
                                      * getValue("Seed").pUINT);

  //CRandom::Type Type;
  Type = * (CRandom::Type *) getValue("Random Generator Type").pUINT;
  //unsigned C_INT32 Seed;
  Seed = * getValue("Seed").pUINT;

  //***mIndividual defined as C_FLOAT64 member variable

  mVariableSize = mpOptItem->size();
  //*** Single mIndividual defined as a member
  mIndividual.resize(mVariableSize);
  /*for (i = 0; i < 2*mPopulationSize; i++)
    mIndividual[i] = new CVector< C_FLOAT64 >(mVariableSize);

  /*mCrossOverFalse.resize(mVariableSize);
  mCrossOverFalse = false;
  mCrossOver.resize(mVariableSize);

  mValue.resize(2*mPopulationSize);

  mShuffle.resize(mPopulationSize);
  for (i = 0; i < mPopulationSize; i++)
    mShuffle[i] = i;

  mWins.resize(2*mPopulationSize);

  // initialise the variance for mutations
  mMutationVarians = 0.1;*/

  return true;
}

/**
 * Optimizer Function
 * Returns: nothing
//*** should return a boolean
 */ 
//C_INT32 CRandomSearch::optimise()
bool CRandomSearch::optimise()
{
  bool linear;

  if (!initialize()) return false;

  C_FLOAT64 la, candx = DBL_MAX;
  //C_INT32 i, imax = (C_INT32) getValue("RandomSearch.Iterations");
  mIterations = * getValue("Number of Iterations").pUINT;
  //C_INT32 j, jmax = mpOptProblem->getVariableSize();
  C_INT32 i, j;
  //C_INT32 varSize = mpOptProblem->getVariableSize();
  C_FLOAT64 mn;
  C_FLOAT64 mx;

  /* Create a random number generator * /
  CRandom::Type Type;
  Type = (CRandom::Type) (C_INT32) getValue("RandomSearch.RandomGenerator.Type");
  unsigned C_INT32 Seed;
  Seed = (unsigned C_INT32) getValue("RandomSearch.RandomGenerator.Seed");*/
  CRandom * pRand = CRandom::createGenerator(Type, Seed);
  assert(pRand);

  for (i = 0; i < mIterations; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {
          // CALCULATE lower and upper bounds
          COptItem & OptItem = *(*mpOptItem)[j];
          mn = *OptItem.getLowerBoundValue();
          mx = *OptItem.getUpperBoundValue();

          C_FLOAT64 mut = mIndividual[j];

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
                mut = mn + pRand->getRandomCC() * (mx - mn);
              else
                mut = mn * pow(10, la * pRand->getRandomCC());
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
      try
        {
          // calculate its fitness
          mValue = evaluate(mIndividual);
        }
      catch (...)
        {
          mValue = DBL_MAX;
        }

      // COMPARE
      if (i == 0 && j == 0)
        {
          //*** initialize mBestValue to start with mValue
          mBestValue = mValue;
          mpOptProblem->setSolutionValue(mBestValue);
          mpOptProblem->setSolutionVariables(mIndividual);
        }
      if (mValue < mBestValue)
        {
          mBestValue = mValue;
          mpOptProblem->setSolutionValue(mBestValue);
          mpOptProblem->setSolutionVariables(mIndividual);
        }
      /*// get the index of the fittest
      mBestIndex = fittest();
      // and store that value
      mBestValue = mValue[mBestIndex];*/
    }

  // *** This is not used anymore, use different means
  /*const double ** Minimum = mpOptProblem->getParameterMin().array();
  //const double ** Maximum = mpOptProblem->getParameterMax().array();

  unsigned C_INT32 i;

  // initialise the population
  // first individual is the initial guess
  for (i = 0; i < mVariableSize; i++)
    (*mIndividual[0])[i] = *(*mpOptItem)[i]->getObjectValue();

  try
    {
      // calculate the fitness
      mValue[0] = evaluate(*mIndividual[0]);
    }

  catch (...)
    {
      mValue[0] = DBL_MAX;
    }

  // the others are random
  creation(1, mPopulationSize);
  // initialise the update register
  // get the index of the fittest
  mBestIndex = fittest();
  // and store that value
  mBestValue = mValue[mBestIndex];

  CVector< C_FLOAT64 > & Parameter = mpOptProblem->getCalculateVariables();

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
      if (!mpOptProblem->checkParametricConstraints()) continue;

      // calculate the function in the problem
      x = mpOptProblem->calculate();

      // check if better than previously stored
      if (x < candx)
        {
          if (!mpOptProblem->checkFunctionalConstraints())
            continue;
          //set best value
          mpOptProblem->setSolutionValue(x);
          candx = x;

          //store the combination of parameter values
          mpOptProblem->getSolutionVariables() = Parameter;
        }
    }*/

  pdelete(pRand);

  return 0;
}

// evaluate the fitness of one individual
C_FLOAT64 CRandomSearch::evaluate(const CVector< C_FLOAT64 > & individual)
{
  unsigned C_INT32 j;

  std::vector< UpdateMethod *>::const_iterator itMethod = mpSetCalculateVariable->begin();

  // set the paramter values
  for (j = 0; j < mVariableSize; j++, ++itMethod)
    (**itMethod)(individual[j]);

  // check whether the parametric constraints are fulfilled
  if (!mpOptProblem->checkParametricConstraints()) return DBL_MAX;

  // evaluate the fitness
  try
    {
      if (!mpOptProblem->calculate()) return DBL_MAX;
    }

  catch (...)
    {
      return DBL_MAX;
    }

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints()) return DBL_MAX;

  return mpOptProblem->getCalculateValue();
}

// check the best individual at this generation
/*unsigned C_INT32 CRandomSearch::fittest()
{
  unsigned C_INT32 i, BestIndex = 0;
  C_FLOAT64 BestValue = mValue[0];
 
  //for (i = 1; i < mPopulationSize; i++)
  for (i = 1; i < mIterations; i++)
    if (mValue[i] < BestValue)
      {
        BestIndex = i;
        BestValue = mValue[i];
      }
 
  return BestIndex;
}*/
