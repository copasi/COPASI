// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>
#include <string>
#include <cmath>

#include "copasi.h"
#include "COptMethodDE.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "randomGenerator/CRandom.h"
#include "utilities/CProcessReport.h"
#include "utilities/CSort.h"
#include "report/CCopasiObjectReference.h"

COptMethodDE::COptMethodDE(const CCopasiContainer * pParent):
  COptMethod(CCopasiTask::optimization, CCopasiMethod::DifferentialEvolution, pParent),
  mGenerations(0),
  mPopulationSize(0),
  mpRandom(NULL),
  mVariableSize(0),
  mIndividual(0),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mValue(0),
  mMutationVarians(0.1),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestIndex(C_INVALID_INDEX),
  mGeneration(0)

{
  addParameter("Number of Generations", CCopasiParameter::UINT, (unsigned C_INT32) 2000);
  addParameter("Population Size", CCopasiParameter::UINT, (unsigned C_INT32) 10);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

COptMethodDE::COptMethodDE(const COptMethodDE & src,
                           const CCopasiContainer * pParent):
  COptMethod(src, pParent),
  mGenerations(0),
  mPopulationSize(0),
  mpRandom(NULL),
  mVariableSize(0),
  mIndividual(0),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mValue(0),
  mMutationVarians(0.1),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestIndex(C_INVALID_INDEX),
  mGeneration(0)
{initObjects();}

COptMethodDE::~COptMethodDE()
{cleanup();}

// evaluate the fitness of one individual
bool COptMethodDE::evaluate(const CVector< C_FLOAT64 > & /* individual */)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  Continue &= mpOptProblem->calculate();

  // check whether the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mEvaluationValue = std::numeric_limits<C_FLOAT64>::infinity();
  else
    mEvaluationValue = mpOptProblem->getCalculateValue();

  return Continue;
}

bool COptMethodDE::replicate()
{
  size_t i, j;
  unsigned C_INT32 a, b, c;
  bool Continue = true;

  for (i = mPopulationSize; i < 2 * mPopulationSize && Continue; i++)
    {
      //MUTATION
      do
        {
          a = mpRandom->getRandomU(mPopulationSize - 1);
        }
      while (i == a);

      do
        {
          b = mpRandom->getRandomU(mPopulationSize - 1);
        }
      while (b == i || b == a);

      do
        {
          c = mpRandom->getRandomU(mPopulationSize - 1);
        }
      while (c == i || c == a || c == b);

      // MUTATE CURRENT GENERATION
      for (j = 0; j < mVariableSize; j++)
        {
          COptItem & OptItem = *(*mpOptItem)[j];
          C_FLOAT64 & mut = (*mIndividual[i])[j];

          mut = (*mIndividual[c])[j] + 2 * ((*mIndividual[a])[j] - (*mIndividual[b])[j]);

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
          (*(*mpSetCalculateVariable)[j])(mut);
        }

      Continue &= evaluate(*mIndividual[i]);
      mValue[i] = mEvaluationValue;
    }

  //CROSSOVER MUTATED GENERATION WITH THE CURRENT ONE
  for (i = 2 * mPopulationSize; i < 3 * mPopulationSize && Continue; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {

          COptItem & OptItem = *(*mpOptItem)[j];
          C_FLOAT64 & mut = (*mIndividual[i])[j];

          size_t r = mpRandom->getRandomU(mPopulationSize - 1);

          if (r < 0.6 * mPopulationSize)
            {
              mut = (*mIndividual[i - mPopulationSize])[j] *
                    mpRandom->getRandomNormal(1, mMutationVarians);
            }

          else
            mut = (*mIndividual[i - 2 * mPopulationSize])[j];

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

          (*(*mpSetCalculateVariable)[j])(mut);
        }

      Continue &= evaluate(*mIndividual[i]);
      mValue[i] = mEvaluationValue;
    }

  //SELECT NEXT GENERATION
  for (i = 2 * mPopulationSize; i < 3 * mPopulationSize && Continue; i++)
    {
      if (mValue[i - mPopulationSize] > mValue[i] && mValue[i - 2 * mPopulationSize] > mValue[i])
        {
          *mIndividual[i - 2 * mPopulationSize] = *mIndividual[i];
          mValue[i - 2 * mPopulationSize] = mValue[i];
        }
      else if (mValue[i - mPopulationSize] < mValue[i - 2 * mPopulationSize])
        {
          *mIndividual[i - 2 * mPopulationSize] = *mIndividual[i - mPopulationSize];
          mValue[i - 2 * mPopulationSize] = mValue[i - mPopulationSize];
        }
      else if (mBestIndex != i && mBestIndex == C_INVALID_INDEX)
        {
          for (j = 0; j < mVariableSize; j++)
            {
              COptItem & OptItem = *(*mpOptItem)[j];
              C_FLOAT64 & mut = (*mIndividual[i - 2 * mPopulationSize])[j];

              size_t r = mpRandom->getRandomU(mPopulationSize - 1);

              if (r < 0.6 * mPopulationSize)
                mut *= mpRandom->getRandomNormal(1, mMutationVarians);

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

              (*(*mpSetCalculateVariable)[j])(mut);
            }

          Continue &= evaluate(*mIndividual[i - 2 * mPopulationSize]);
          mValue[i - 2 * mPopulationSize] = mEvaluationValue;
        }
    }

  return Continue;
}

// check the best individual at this generation
size_t COptMethodDE::fittest()
{
  size_t i, BestIndex = C_INVALID_INDEX;
  C_FLOAT64 BestValue = std::numeric_limits< C_FLOAT64 >::max();

  for (i = 0; i < mPopulationSize; i++)
    if (mValue[i] < BestValue)
      {
        BestIndex = i;
        BestValue = mValue[i];
      }

  return BestIndex;
}

// check the best individual at this generation
void COptMethodDE::boost()
{
  size_t i;

  for (i = 2 * mPopulationSize; i < 3 * mPopulationSize; i++)
    if (mValue[i] < mValue[i - 2 * mPopulationSize])
      {
        *mIndividual[i - 2 * mPopulationSize] = *mIndividual[i];
        mValue[i - 2 * mPopulationSize] = mValue[i];
      }
}

// Initialize the population
bool COptMethodDE::creation(size_t first, size_t last)
{
  size_t Last = std::min(last, (size_t) mPopulationSize);
  size_t i, j;

  C_FLOAT64 mn;
  C_FLOAT64 mx;
  C_FLOAT64 la;

  bool Continue = true;

  for (i = first; i < Last && Continue; i++)
    {
      // We do not want to loose the best individual;
      if (mBestIndex != i)
        for (j = 0; j < mVariableSize; j++)
          {
            // calculate lower and upper bounds
            COptItem & OptItem = *(*mpOptItem)[j];
            mn = *OptItem.getLowerBoundValue();
            mx = *OptItem.getUpperBoundValue();

            C_FLOAT64 & mut = (*mIndividual[i])[j];

            try
              {
                // determine if linear or log scale
                if ((mn < 0.0) || (mx <= 0.0))
                  mut = mn + mpRandom->getRandomCC() * (mx - mn);
                else
                  {
                    la = log10(mx) - log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()));

                    if (la < 1.8)
                      mut = mn + mpRandom->getRandomCC() * (mx - mn);
                    else
                      mut = pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min())) + la * mpRandom->getRandomCC());
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
                  break;

                case 1:
                  mut = *OptItem.getUpperBoundValue();
                  break;
              }

            // We need to set the value here so that further checks take
            // account of the value.
            (*(*mpSetCalculateVariable)[j])(mut);
          }

      // calculate its fitness
      Continue &= evaluate(*mIndividual[i]);
      mValue[i] = mEvaluationValue;
    }

  return Continue;
}

void COptMethodDE::initObjects()
{
  addObjectReference("Current Generation", mGeneration, CCopasiObject::ValueInt);
}

bool COptMethodDE::initialize()
{
  cleanup();

  size_t i;

  if (!COptMethod::initialize())
    {
      if (mpCallBack)
        mpCallBack->finishItem(mhGenerations);

      return false;
    }

  mGenerations = * getValue("Number of Generations").pUINT;
  mGeneration = 0;

  if (mpCallBack)
    mhGenerations =
      mpCallBack->addItem("Current Generation",
                          mGeneration,
                          & mGenerations);

  mGeneration++;

  mPopulationSize = * getValue("Population Size").pUINT;

  if (mPopulationSize < 4)
    {
      mPopulationSize = 4;
      setValue("Population Size", mPopulationSize);
    }

  mpRandom =
    CRandom::createGenerator(* (CRandom::Type *) getValue("Random Number Generator").pUINT,
                             * getValue("Seed").pUINT);

  mVariableSize = mpOptItem->size();

  mIndividual.resize(3 * mPopulationSize);

  for (i = 0; i < 3 * mPopulationSize; i++)
    mIndividual[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mValue.resize(3 * mPopulationSize);
  mValue = std::numeric_limits<C_FLOAT64>::infinity();
  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();

  mMutationVarians = 0.1;

  return true;
}

bool COptMethodDE::cleanup()
{
  size_t i;

  pdelete(mpRandom);

  for (i = 0; i < mIndividual.size(); i++)
    pdelete(mIndividual[i]);

  return true;
}

bool COptMethodDE::optimise()
{
  bool Continue = true;

  if (!initialize())
    {
      if (mpCallBack)
        mpCallBack->finishItem(mhGenerations);

      return false;
    }

  size_t i;

  // initialise the population
  // first individual is the initial guess
  for (i = 0; i < mVariableSize; i++)
    {
      C_FLOAT64 & mut = (*mIndividual[0])[i];
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

  Continue &= evaluate(*mIndividual[0]);
  mValue[0] = mEvaluationValue;

  if (!isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mValue[0];
      Continue &= mpOptProblem->setSolution(mBestValue, *mIndividual[0]);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  // the others are random
  Continue &= creation(1, mPopulationSize);

  mBestIndex = fittest();

  if (mBestIndex != C_INVALID_INDEX &&
      mValue[mBestIndex] < mBestValue)
    {
      // and store that value
      mBestValue = mValue[mBestIndex];
      Continue = mpOptProblem->setSolution(mBestValue, *mIndividual[mBestIndex]);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  if (!Continue)
    {
      if (mpCallBack)
        mpCallBack->finishItem(mhGenerations);

      cleanup();
      return true;
    }

  size_t Stalled = 0;

  // ITERATE FOR gener GENERATIONS
  for (mGeneration = 2;
       mGeneration <= mGenerations && Continue;
       mGeneration++, Stalled++)
    {
      if (Stalled > 10)
        {
          Continue &= creation((size_t) 0.4 * mPopulationSize, (size_t) 0.8 * mPopulationSize);
        }

      // perturb the population a bit
      Continue &= creation((size_t)(mPopulationSize * 0.9), mPopulationSize);

      Continue &= replicate();

      // get the index of the fittest
      mBestIndex = fittest();

      if (mBestIndex != C_INVALID_INDEX &&
          mValue[mBestIndex] < mBestValue)
        {
          Stalled = 0;
          mBestValue = mValue[mBestIndex];

          Continue &= mpOptProblem->setSolution(mBestValue, *mIndividual[mBestIndex]);

          // We found a new best value lets report it.
          //if (mpReport) mpReport->printBody();
          mpParentTask->output(COutputInterface::DURING);
        }

      if (mpCallBack)
        Continue &= mpCallBack->progressItem(mhGenerations);
    }

  if (mpCallBack)
    mpCallBack->finishItem(mhGenerations);

  cleanup();

  return true;
}
