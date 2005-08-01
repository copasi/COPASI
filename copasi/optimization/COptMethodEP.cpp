/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodEP.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2005/08/01 07:00:06 $
   End CVS Header */

#include "copasi.h"

#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "randomGenerator/CRandom.h"
#include "report/CCopasiObjectReference.h"

COptMethodEP::COptMethodEP(const CCopasiContainer * pParent):
    COptMethod(CCopasiMethod::EvolutionaryProgram2, pParent),
    mGenerations(0),
    mPopulationSize(0),
    mpRandom(NULL),
    mVariableSize(0),
    mIndividual(0),
    mEvaluationValue(DBL_MAX),
    mValue(0),
    mWins(0),
    mBestValue(DBL_MAX),
    mBestIndex(C_INVALID_INDEX),
    mGeneration(0)
{
  addParameter("Number of Generations", CCopasiParameter::UINT, (unsigned C_INT32) 200);
  addParameter("Population Size", CCopasiParameter::UINT, (unsigned C_INT32) 20);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

COptMethodEP::COptMethodEP(const COptMethodEP & src,
                           const CCopasiContainer * pParent): COptMethod(src, pParent),
    mGenerations(0),
    mPopulationSize(0),
    mpRandom(NULL),
    mVariableSize(0),
    mIndividual(0),
    mEvaluationValue(DBL_MAX),
    mValue(0),
    mWins(0),
    mBestValue(DBL_MAX),
    mBestIndex(C_INVALID_INDEX),
    mGeneration(0)
{initObjects();}

COptMethodEP::~COptMethodEP()
{
  cleanup();
}

bool COptMethodEP::setCallBack(CProcessReport * pCallBack)
{
  CCopasiMethod::setCallBack(pCallBack);

  if (!pCallBack) return true;

  mGeneration = 0;
  mhGenerations =
    pCallBack->addItem("Current Generation",
                       CCopasiParameter::UINT,
                       & mGeneration,
                       & mGenerations);

  return true;
}

bool COptMethodEP::optimise()
{
  if (!initialize()) return false;
  unsigned C_INT32 i;
  bool Continue = true;

  // initialise the parameters to update the variances
  tau1 = 1.0 / sqrt(2 * mVariableSize);
  tau2 = 1.0 / sqrt(2 * sqrt(mVariableSize));

  // initialise the population
  Continue = creation();

  // iterate over Generations
  for (i = 0; i < mGenerations; i++)
    {
      // replicate the individuals
      Continue = replicate();
      // select the most fit
      Continue = select();
      // get the index of the fittest
      mBestIndex = fittest();
      // signal another generation

      if (mpCallBack)
        Continue = mpCallBack->progress(mhGenerations);
    }

  /* Declare the solution */
  mBestValue = mValue[mBestIndex];
  mpOptProblem->setSolutionVariables(*mIndividual[mBestIndex]);
  Continue = mpOptProblem->setSolutionValue(mBestValue);
  mpParentTask->doOutput();
  return Continue;
}

bool COptMethodEP::cleanup()
{
  unsigned C_INT32 i;
  // pdelete all used variables
  pdelete(mpRandom);
  for (i = 0; i < 2*mPopulationSize; i++)
    pdelete(mIndividual[i]);
  return true;
}

bool COptMethodEP::initialize()
{
  unsigned C_INT32 i;
  if (!COptMethod::initialize()) return false;

  mGenerations = * getValue("Number of Generations").pUINT;
  mGeneration = 1;

  mPopulationSize = * getValue("Population Size").pUINT;
  mpRandom =
    CRandom::createGenerator(* (CRandom::Type *) getValue("Random Number Generator").pUINT,
                             * (unsigned C_INT32 *) getValue("Seed").pUINT);

  mVariableSize = mpOptItem->size();

  mIndividual.resize(2*mPopulationSize);
  for (i = 0; i < 2*mPopulationSize; i++)
    mIndividual[i] = new CVector< C_FLOAT64 >(mVariableSize);
  mContinue = true;

  mValue.resize(2*mPopulationSize);

  mWins.resize(2*mPopulationSize);

  return true;
}

// evaluate the fitness of one individual
bool COptMethodEP::evaluate(const CVector< C_FLOAT64 > & individual)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  Continue = mpOptProblem->calculate();

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mEvaluationValue = DBL_MAX;
  else
    mEvaluationValue = mpOptProblem->getCalculateValue();

  return Continue;
}

void COptMethodEP::initObjects()
{
  addObjectReference("Current Generation", mGeneration, CCopasiObject::ValueInt);
}

bool COptMethodEP::creation()
{
  unsigned C_INT32 i, half;
  C_INT32 j;
  C_FLOAT64 mn, mx, la, la1;
  C_INT32 loczero; // loczero is 1 for positive domain, -1 for negative domain and 0 for mixed
  bool linear;
  half = mPopulationSize / 2;

  // set the first half of the individuals to the initial guess

  // for(i=0; i<half; i++)

  for (j = 0; j < mVariableSize; j++)
    {
      (*mIndividual[0])[j] = *(*mpOptItem)[j]->getObjectValue();
      //   indv[0][nparam+j] = sqrt(fabs(*(parameter[j]->Parameter.Value)));
      (*mIndividual[0])[mVariableSize + j] = fabs(*(*mpOptItem)[j]->getObjectValue()) * 0.5;
    }

  // calculate the fitness
  mContinue = evaluate(*mIndividual[0]);
  //candx[0] = evaluate(0);

  // and copy it to the rest
  // for(i=1; i<half; i++)
  //  candx[i] = candx[0];
  // set the other half to random values within the boundaries
  // for(i=half; i<mVariableSizeze; i++)

  for (i = 1; i < mPopulationSize; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {
          // calculate lower and upper bounds
          COptItem & OptItem = *(*mpOptItem)[j];
          mn = *OptItem.getLowerBoundValue();
          mx = *OptItem.getUpperBoundValue();
          // if in the wrong order switch them
          if (mn > mx)
            {
              la = mn;
              mn = mx;
              mx = la;
            }
          // initialize control variables
          linear = false; la = 1.0;
          // if only one of mx and mn is zero we go linear
          if (((mn == 0.0) && (mx != 0.0)) || ((mx == 0.0) && (mn != 0.0)))
            linear = true;
          else
            {
              // if mn is zero make it slightly larger
              if (mn == 0.0) mn = pow(10, DBL_MIN_10_EXP);
              // if mx is zero make it slightly smaller
              if (mx == 0.0) mx = pow(-10, DBL_MIN_10_EXP);
              // find out where zero is
              if ((mn < 0.0) && (mx < 0.0)) loczero = -1;
              else
                {
                  if ((mn > 0.0) && (mx > 0.0)) loczero = 1;
                  else loczero = 0;
                }
              switch (loczero)
                {
                case - 1: la = log10(-mn) - log10(-mx);
                  if (la < 1.8) linear = 1;
                  break;
                case 1: la = log10(mx) - log10(mn);
                  if (la < 1.8) linear = 1;
                  break;
                case 0: la = log10(mx) - DBL_MIN_10_EXP;
                  la1 = log10(-mn) - DBL_MIN_10_EXP;
                  if ((la + la1) < 1.8) linear = 1;
                  break;
                }
            }
          // if we decided it is linear, no problems with zero so
          // put mn and mx back to what they were and get the number
          if (linear)
            {
              COptItem & OptItem = *(*mpOptItem)[j];
              mn = *OptItem.getLowerBoundValue();
              mx = *OptItem.getUpperBoundValue();
              try
                {
                  (*mIndividual[i])[j] = mn + mpRandom->getRandomCC() * (mx - mn);
                }
              catch (unsigned int e)
                {
                  (*mIndividual[i])[j] = mx;
                }
            }
          // else if it is not linear we need to distinguish the 3 cases
          else
            {
              try
                {
                  switch (loczero)
                    {
                    case - 1: (*mIndividual[i])[j] = - (-mx * pow(10, la * mpRandom->getRandomCC()));
                      break;
                    case 1: (*mIndividual[i])[j] = mn * pow(10, la * mpRandom->getRandomCC());
                      break;
                    case 0: la = (fabs(mx) + fabs(mn)) * 0.5 * 0.01;
                      do
                        {
                          (*mIndividual[i])[j] = mpRandom->getRandomNormal(0, la);
                        }
                      while (((*mIndividual[i])[j] < mn) || ((*mIndividual[i])[j] > mx));
                      break;

                      // 2 never happens, this is the old case 0 kept here as it can later be useful
                    case 2: if (mpRandom->getRandomCC() < (la1 / (la + la1)))
                        (*mIndividual[i])[j] = - (pow(10, DBL_MIN_10_EXP) * pow(10, la1 * mpRandom->getRandomCC()));
                      else
                        (*mIndividual[i])[j] = pow(10, DBL_MIN_10_EXP) * pow(10, la * mpRandom->getRandomCC());
                      break;
                    }
                }
              catch (unsigned C_INT32 e)
                {
                  (*mIndividual[i])[j] = mx;
                }
            }
          // set the variance of the mutations
          // indv[i][nparam+j] = sqrt(fabs(indv[i][j]));
          (*mIndividual[i])[mVariableSize + j] = fabs((*mIndividual[i])[j]) * 0.5;
        }
      // calculate its fitness
      mValue[i] = evaluate(*mIndividual[i]);
    }
  // get the index of the fittest
  mBestIndex = fittest();

  return true;
}

bool COptMethodEP::select()
{
  unsigned C_INT32 i, j, nopp, opp;

  // tournament competition
  // compete with 20% of the population
  nopp = (unsigned int) (mPopulationSize * 0.2);

  // but at least one
  if (nopp < 1) nopp = 1;

  // parents and offspring are all in competition
  for (i = 0; i < 2*mPopulationSize; i++)
    {
      mWins[i] = 0;
      for (j = 0; j < nopp; j++)
        {
          // get random opponent
          opp = mpRandom->getRandomU(mPopulationSize * 2);
          if (mValue[i] <= mValue[opp]) mWins[i]++;
        }
    }
  // selection of top winners
  for (i = 0; i < mPopulationSize; i++)
    for (j = i + 1; j < 2*mPopulationSize; j++)
      if (mWins[i] < mWins[j])
        {
          swap(i, j);
          break; // <todo=confirm>
        }
  return true;
}

bool COptMethodEP::swap(unsigned C_INT32 from, unsigned C_INT32 to)
{
  CVector< C_FLOAT64 > * pTmp = mIndividual[to];
  mIndividual[to] = mIndividual[from];
  mIndividual[from] = pTmp;

  C_FLOAT64 dTmp = mValue[to];
  mValue[to] = mValue[from];
  mValue[from] = dTmp;

  C_INT32 iTmp = mWins[to];
  mWins[to] = mWins[from];
  mWins[from] = iTmp;

  return true;
}

unsigned C_INT32 COptMethodEP::fittest()
{
  unsigned C_INT32 i, BestIndex = 0;
  C_FLOAT64 BestValue = mValue[0];

  for (i = 1; i < mPopulationSize; i++)
    if (mValue[i] < BestValue && !isnan(mValue[i]))
      {
        BestIndex = i;
        BestValue = mValue[i];
      }

  return BestIndex;
}

bool COptMethodEP::replicate()
{
  unsigned C_INT32 i;
  C_INT32 j;
  bool Continue = true;

  // iterate over parents
  for (i = 0; i < mPopulationSize; i++)
    {
      // replicate them
      for (j = 0; j < 2*mVariableSize; j++)
        (*mIndividual[mPopulationSize + i])[j] = (*mIndividual[i])[j];
      mValue[mPopulationSize + i] = mValue[i];
      // possibly mutate the offspring
      Continue = mutate(mPopulationSize + i);
    }

  return Continue;
}

bool COptMethodEP::mutate(unsigned C_INT32 i)
{
  C_INT32 j;
  C_FLOAT64 mn, mx, mut, v1;

  try
    {
      v1 = mpRandom->getRandomNormal01();
      // update the variances
      for (j = 0; j < mVariableSize; j++)
        {
          (*mIndividual[i])[mVariableSize + j] = (*mIndividual[i])[mVariableSize + j] * exp(tau1 * v1 + tau2 * mpRandom->getRandomNormal01());
          if ((*mIndividual[i])[mVariableSize + j] < 1e-8)
            (*mIndividual[i])[mVariableSize + j] = 1e-8;
        }
      // mutate the parameters
      for (j = 0; j < mVariableSize; j++)
        {
          // calculate lower and upper bounds
          COptItem & OptItem = *(*mpOptItem)[j];
          mn = *OptItem.getLowerBoundValue();
          mx = *OptItem.getUpperBoundValue();

          // calculate the mutatated parameter

          mut = sqrt((*mIndividual[i])[mVariableSize + j]);
          mut *= mpRandom->getRandomNormal01();
          mut = (*mIndividual[i])[j] + mut;
          // force it to be within the bounds
          if (OptItem.getLowerRelation() == "<")

          {if (mut <= mn) mut = mn + DBL_EPSILON;}
          else
          {if (mut < mn) mut = mn;}

          if (OptItem.getUpperRelation() == ">")

          {if (mut >= mx) mut = mx - DBL_EPSILON;}
          else
          {if (mut > mx) mut = mx;}
          // store it
          (*mIndividual[i])[j] = mut;
        }
    }

  catch (unsigned int e)
    {
    }
  // evaluate the fitness
  mValue[i] = evaluate(*mIndividual[i]);

  return true;
}
