/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodEP2.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/18 02:58:23 $
   End CVS Header */

/***************************************************************************
                    COptMethodEP2.cpp  - Evolutionary Program  Optimizer
                    -------------------------------------------------
                       
         Implemented by Dingjun Chen
        
                       Starting Date: Dec. 2003 
   
                       COPASI project group
 ***************************************************************************/

/***************************************************************************
 * This is the implementation of the  Eovlutionary Program for Optimization.  The
 * class is inherited from the COptAlgorithm class
 ***************************************************************************/

#include <vector>

#include "copasi.h"
#include "COptMethod.h"
#include "CRealProblem.h"
#include "randomGenerator/CRandom.h"

COptMethodEP2::COptMethodEP2(const COptMethodEP2 & src):
    COptMethod(src)
{}

COptMethodEP2::COptMethodEP2(): COptMethod(CCopasiMethod::EvolutionaryProgram2)
{
  addParameter("EvolutionaryProgram2.Iterations",
               CCopasiParameter::UINT,
               (unsigned C_INT32) 10000);
  addParameter("EvolutionaryProgram2.PopulationSize",
               CCopasiParameter::UINT,
               (unsigned C_INT32) 600);
  addParameter("EvolutionaryProgram2.RandomGenerator.Type",
               CCopasiParameter::INT,
               (C_INT32)CRandom::mt19937);
  addParameter("EvolutionaryProgram2.RandomGenerator.Seed",
               CCopasiParameter::INT,
               (C_INT32) 0);
}

/**
 * Destructor
 */
COptMethodEP2::~COptMethodEP2()
{}

/**
 * GA Optimizer Function:
 * Returns: nothing
 */
C_INT32 COptMethodEP2::optimise()
{
  NumGeneration = (C_INT32) getValue("EvolutionaryProgram2.Iterations");
  PopulationSize = (C_INT32) getValue("EvolutionaryProgram2.PopulationSize");
  NumParameter = mOptProblem->getVariableSize();

  /* Create a random number generator */
  CRandom::Type Type;
  Type = (CRandom::Type) (C_INT32) getValue("EvolutionaryProgram2.RandomGenerator.Type");
  C_INT32 Seed;
  Seed = (C_INT32) getValue("EvolutionaryProgram2.RandomGenerator.Seed");
  CRandom * pRand = CRandom::createGenerator(Type, Seed);

  assert(pRand);

  const double ** Minimum = mOptProblem->getParameterMin().array();
  const double ** Maximum = mOptProblem->getParameterMax().array();

  CVector< C_FLOAT64 > & Parameter = mOptProblem->getCalculateVariables();

#ifdef XXXX
  double **Parameter;
  Parameter = new double * [2 * PopulationSize];

  for (int ii = 0; ii < 2*PopulationSize; ii++)
    {
      Parameter[ii] = new double[NumParameter];
    }

  for (int dd = 0; dd < 2*PopulationSize; dd++)
    Parameter[dd] = mParameters->array();
#endif // XXXX

  double current_best_value, la;
  int i, j, last_update, u10, u30, u50;
  bool linear;

  // create array for function value of candidate
  CandidateValue = new double[2 * PopulationSize];

  // create array for function value rate of candidate
  CandidateValueRate = new double[PopulationSize];

  // create array for tournament competition strategy
  WinScore = new int[2 * PopulationSize];

  // create array for crossover points
  CrossPoint = new int[NumParameter];

  // create the population array
  individual = new double * [2 * PopulationSize];
  // create the individuals
  for (i = 0; i < 2*PopulationSize; i++)
    {
      individual[i] = new double[NumParameter];
    }

  // Prepare inital population
  //Generate the initial population at random
  for (i = 0; i < PopulationSize; i++)
    {
      for (j = 0; j < NumParameter; j++)
        {
          try
            {
              // determine if linear or log scale
              linear = FALSE; la = 1.0;
              if ((*Maximum[j] <= 0.0) || (*Minimum[j] < 0.0)) linear = TRUE;
              else
                {
                  la = log10(*Maximum[j]) - log10(std::min(*Minimum[j], DBL_EPSILON));
                  if (la < 1.8) linear = TRUE;
                }
              // set it to a random value within the interval
              if (linear)
                individual[i][j] = *Minimum[j] + pRand->getRandomCC() * (*Maximum[j] - *Minimum[j]);
              else
                individual[i][j] = *Minimum[j] * pow(10, la * pRand->getRandomCC());
            }
          catch (int)
            {
              individual[i][j] = (*Maximum[j] - *Minimum[j]) * 0.5 + *Minimum[j];
            }
        }
      try
        {
          // calculate its fitness value
          for (int kk = 0; kk < NumParameter; kk++) {Parameter[kk] = individual[i][kk];}
          CandidateValue[i] = mOptProblem->calculate();
        }
      catch (int)
        {
          CandidateValue[i] = DBL_MAX;
        }
    } // initialization ends

  //Set fitness map rate
  // double q=0.8;
  // double constant1=100;
  double constant1 = 100;
  // double constant2=20;
  double constant2 = 10;
  /* for (i=0; i<PopulationSize; i++)
   {
    CandidateValueRate[i]=1-q*pow((1-q),i);
   }
  */ 
  // get the index of the fittest
  BestFoundSoFar = fittest();

  // initialise the update registers
  last_update = 0;
  u10 = u30 = u50 = 0;

  // store that value
  current_best_value = Get_BestFoundSoFar_candidate();

  std::ofstream finalout("debugopt.dat");
  if (!finalout)
    {
      std::cout << "debugopt.dat cannot be opened!" << std::endl;
      exit(1);
    }
  finalout << "----------------------------- the best result at each generation---------------------" << std::endl;
  finalout << "Generation\t" << "Best candidate value for object function\t" << "Display " << NumParameter << " parameters" << std::endl;
  finalout << std::endl;
  finalout.close();

  srand(time(NULL)); rand();

  // Iterations of GA
  for (i = 0; i < NumGeneration; i++)
    {
      std::cout << std::endl;
      std::cout << "EP2 is processing at generation " << i << std::endl;

      TrackDataFile(i);

      select(5);
      //Mutating all parents
      for (int nn = PopulationSize; nn < 2*PopulationSize; nn++)
        {
          double mut;

          // mutate the parameters
          for (int j = 0; j < NumParameter; j++)
            {
              if (floor(10*rand() / RAND_MAX) > 5)
                {
                  //  if(i<NumGeneration*0.5) mut = individual[nn-PopulationSize][j]*(1 + pRand->getRandomCC());
                  if (i < NumGeneration*0.5) mut = individual[nn - PopulationSize][j] * (1 + sqrt(constant1 * CandidateValueRate[nn] + constant2) * pRand->getRandomCC());
                  else
                    {
                      if (i < NumGeneration*0.6) mut = individual[nn - PopulationSize][j] * (1 + sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.5 * pRand->getRandomCC());
                      else
                        {
                          if (i < NumGeneration*0.7) mut = individual[nn - PopulationSize][j] * (1 + sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.25 * pRand->getRandomCC());
                          else
                            {
                              if (i < NumGeneration*0.8) mut = individual[nn - PopulationSize][j] * (1 + sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.1 * pRand->getRandomCC());
                              else
                                {
                                  if (i < NumGeneration*0.9) mut = individual[nn - PopulationSize][j] * (1 + sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.01 * pRand->getRandomCC());
                                  else
                                    {
                                      if (i < NumGeneration*0.95) mut = individual[nn - PopulationSize][j] * (1 + sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.001 * pRand->getRandomCC());
                                      else mut = individual[nn - PopulationSize][j] * (1 + sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.0001 * pRand->getRandomCC());
                                    }
                                }
                            }
                        }
                    }
                }
              else
                {
                  if (i < NumGeneration*0.5) mut = individual[nn - PopulationSize][j] * (1 - sqrt(constant1 * CandidateValueRate[nn] + constant2) * pRand->getRandomCC());
                  else
                    {
                      if (i < NumGeneration*0.6) mut = individual[nn - PopulationSize][j] * (1 - sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.5 * pRand->getRandomCC());
                      else
                        {
                          if (i < NumGeneration*0.7) mut = individual[nn - PopulationSize][j] * (1 - sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.25 * pRand->getRandomCC());
                          else
                            {
                              if (i < NumGeneration*0.8) mut = individual[nn - PopulationSize][j] * (1 - sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.1 * pRand->getRandomCC());
                              else
                                {
                                  if (i < NumGeneration*0.9) mut = individual[nn - PopulationSize][j] * (1 - sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.01 * pRand->getRandomCC());
                                  else
                                    {
                                      if (i < NumGeneration*0.95) mut = individual[nn - PopulationSize][j] * (1 - sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.001 * pRand->getRandomCC());
                                      else mut = individual[nn - PopulationSize][j] * (1 - sqrt(constant1 * CandidateValueRate[nn] + constant2) * 0.0001 * pRand->getRandomCC());
                                    }
                                }
                            }
                        }
                    }
                }
              // check boundary and force it to be within the bounds
              if (mut <= *Minimum[j]) mut = *Minimum[j] + DBL_EPSILON;
              else
                {
                  if (mut < *Minimum[j]) mut = *Minimum[j];
                }

              if (mut >= *Maximum[j]) mut = *Maximum[j] - DBL_EPSILON;
              else
                {
                  if (mut > *Maximum[j]) mut = *Maximum[j];
                }
              // store it
              individual[nn][j] = mut;
            }
          // evaluate the fitness
          for (int kk = 0; kk < NumParameter; kk++)
            {
              Parameter[kk] = individual[nn][kk];
            }
          CandidateValue[nn] = mOptProblem->calculate();
        }

      // select approprate individuals as new population
      select(2);

      // get the index of the fittest
      BestFoundSoFar = fittest();
      if (Get_BestFoundSoFar_candidate() != current_best_value)
        {
          last_update = i;
          current_best_value = Get_BestFoundSoFar_candidate();
        }

      if (u10) u10--;
      if (u30) u30--;
      if (u50) u50--;

      if ((u50 == 0) && (i - last_update > 50))
        {
          for (int mm = PopulationSize / 2; mm < PopulationSize; mm++)
            {
              for (int jj = 0; jj < NumParameter; jj++)
                {
                  try
                    {
                      // determine if linear or log scale
                      linear = FALSE; la = 1.0;
                      if ((*Maximum[jj] <= 0.0) || (*Minimum[jj] < 0.0)) linear = TRUE;
                      else
                        {
                          la = log10(*Maximum[jj]) - log10(std::min(*Minimum[jj], DBL_EPSILON));
                          if (la < 1.8) linear = TRUE;
                        }
                      // set it to a random value within the interval
                      if (linear)
                        individual[mm][jj] = *Minimum[jj] + pRand->getRandomCC() * (*Maximum[jj] - *Minimum[jj]);
                      else
                        individual[mm][jj] = *Minimum[jj] * pow(10, la * pRand->getRandomCC());
                    }
                  catch (int)
                    {
                      individual[mm][jj] = (*Maximum[jj] - *Minimum[jj]) * 0.5 + *Minimum[jj];
                    }
                }
              try
                {
                  // calculate its fitness
                  for (int kk = 0; kk < NumParameter; kk++) {Parameter[kk] = individual[mm][kk];}
                  CandidateValue[mm] = mOptProblem->calculate();
                }
              catch (int)
                {
                  CandidateValue[mm] = DBL_MAX;
                }
            }
          //end external for loop
          BestFoundSoFar = fittest();
          u50 = 50; u30 = 30; u10 = 10;
        }
      else
        {
          if ((u30 == 0) && (i - last_update > 30))
            {
              for (int mm = (int)floor(PopulationSize * 0.7); mm < PopulationSize; mm++)
                {
                  for (int jj = 0; jj < NumParameter; jj++)
                    {
                      try
                        {
                          // determine if linear or log scale
                          linear = FALSE; la = 1.0;
                          if ((*Maximum[jj] <= 0.0) || (*Minimum[jj] < 0.0)) linear = TRUE;
                          else
                            {
                              la = log10(*Maximum[jj]) - log10(std::min(*Minimum[jj], DBL_EPSILON));
                              if (la < 1.8) linear = TRUE;
                            }
                          // set it to a random value within the interval
                          if (linear)
                            individual[mm][jj] = *Minimum[jj] + pRand->getRandomCC() * (*Maximum[jj] - *Minimum[jj]);
                          else
                            individual[mm][jj] = *Minimum[jj] * pow(10, la * pRand->getRandomCC());
                        }
                      catch (int)
                        {
                          individual[mm][jj] = (*Maximum[jj] - *Minimum[jj]) * 0.5 + *Minimum[jj];
                        }
                    }
                  try
                    {
                      // calculate its fitness
                      for (int kk = 0; kk < NumParameter; kk++) {Parameter[kk] = individual[mm][kk];}
                      CandidateValue[mm] = mOptProblem->calculate();
                    }
                  catch (int)
                    {
                      CandidateValue[mm] = DBL_MAX;
                    }
                }
              //end external for loop
              BestFoundSoFar = fittest();
              u30 = 30; u10 = 10;
            }
          else
            {
              if ((u10 == 0) && (i - last_update > 10))
                {
                  for (int mm = (int) floor(PopulationSize * 0.9); mm < PopulationSize; mm++)
                    {
                      for (int jj = 0; jj < NumParameter; jj++)
                        {
                          try
                            {
                              // determine if linear or log scale
                              linear = FALSE; la = 1.0;
                              if ((*Maximum[jj] <= 0.0) || (*Minimum[jj] < 0.0)) linear = TRUE;
                              else
                                {
                                  la = log10(*Maximum[jj]) - log10(std::min(*Minimum[jj], DBL_EPSILON));
                                  if (la < 1.8) linear = TRUE;
                                }
                              // set it to a random value within the interval
                              if (linear)
                                individual[mm][jj] = *Minimum[jj] + pRand->getRandomCC() * (*Maximum[jj] - *Minimum[jj]);
                              else
                                individual[mm][jj] = *Minimum[jj] * pow(10, la * pRand->getRandomCC());
                            }
                          catch (int)
                            {
                              individual[mm][jj] = (*Maximum[jj] - *Minimum[jj]) * 0.5 + *Minimum[jj];
                            }
                        }
                      try
                        {
                          // calculate its fitness
                          for (int kk = 0; kk < NumParameter; kk++) {Parameter[kk] = individual[mm][kk];}
                          CandidateValue[mm] = mOptProblem->calculate();
                        }
                      catch (int)
                        {
                          CandidateValue[mm] = DBL_MAX;
                        }
                    }
                  //end external for loop
                  BestFoundSoFar = fittest();
                  u10 = 10;
                  //u10=50;
                }
            }
        }
    } // end iteration of generations

  for (int kk = 0; kk < NumParameter; kk++)
    {
      Parameter[kk] = individual[BestFoundSoFar][kk];
    }

  //set the  BestFoundSoFar function value
  mOptProblem->setSolutionValue(Get_BestFoundSoFar_candidate());

  //store the combination of the BestFoundSoFar parameter values found so far
  mOptProblem->getSolutionVariables() = Parameter;

  //free memory space
  delete individual;
  delete CrossPoint;
  delete WinScore;
  delete CandidateValue;

  std::cout << std::endl;
  std::cout << "GA has successfully done!" << std::endl;

  return 0;
}

// copy individual o to position d
void COptMethodEP2::copy(int o, int d)
{
  int i;

  for (i = 0; i < NumParameter; i++)
    {
      individual[d][i] = individual[o][i];
    }

  CandidateValue[d] = CandidateValue[o];
}

// swap individuals o and d
void COptMethodEP2::swap(int o, int d)
{
  int i;
  double tmp;

  for (i = 0; i < NumParameter; i++)
    {
      tmp = individual[d][i];
      individual[d][i] = individual[o][i];
      individual[o][i] = tmp;
    }

  tmp = CandidateValue[d];
  CandidateValue[d] = CandidateValue[o];
  CandidateValue[o] = tmp;

  i = WinScore[d];
  WinScore[d] = WinScore[o];
  WinScore[o] = i;
}

// exchange individuals o and d
void COptMethodEP2::exchange(int o, int d)
{
  int i;
  double tmp;

  for (i = 0; i < NumParameter; i++)
    {
      tmp = individual[d][i];
      individual[d][i] = individual[o][i];
      individual[o][i] = tmp;
    }

  tmp = CandidateValue[d];
  CandidateValue[d] = CandidateValue[o];
  CandidateValue[o] = tmp;
}

// select PopulationSize individuals
void COptMethodEP2::select(int SelectionStrategy)
{
  int i, j, TournamentSize, RandomRival;
  int RandomIndividual;
  //srand(time(NULL)); rand();

  switch (SelectionStrategy)
    {
    case 1:       // parent-offspring competition
      for (i = PopulationSize; i < 2*PopulationSize; i++)
        {
          // if offspring is fitter keep it
          for (j = 0; j < PopulationSize; j++)
            {
              if (CandidateValue[i] < CandidateValue[j]) exchange(i, j);
            }
        }
      break;
    case 2:       // tournament competition
      // compete with 20% of the population
      TournamentSize = PopulationSize / 5;
      // but at least one
      if (TournamentSize < 1) TournamentSize = 1;
      // parents and offspring are all in competition
      for (i = 0; i < 2*PopulationSize; i++)
        {
          WinScore[i] = 0;
          for (j = 0; j < TournamentSize; j++)
            {
              // get random rival
              RandomRival = (int)fabs(floor((PopulationSize * 2 - 1) * rand() / RAND_MAX));
              if (CandidateValue[i] <= CandidateValue[RandomRival]) WinScore[i]++;
            }
        }
      // selection of top PopulationSize winners
      for (i = 0; i < PopulationSize; i++)
        {
          for (j = i + 1; j < 2*PopulationSize; j++)
          {if (WinScore[i] < WinScore[j]) swap(i, j);}
        }
      break;

      // ranking strategy without proportionate-fitness
    case 3:
      for (i = 0; i < PopulationSize; i++)
        {
          for (j = i + 1; j < 2*PopulationSize; j++)
            {
              if (CandidateValue[i] > CandidateValue[j]) exchange(i, j);
            }
        }

      break;
      // Randomly select P individuals from population of 2P
    case 4:
      for (i = 0; i < PopulationSize; i++)
        {
          RandomIndividual = (int)fabs(floor((PopulationSize * 2 - 1) * rand() / RAND_MAX));
          exchange(i, RandomIndividual);
        }

      break;

      // ranking strategy for EP2
    case 5:
      for (i = 0; i < PopulationSize; i++)
        {
          for (j = i + 1; j < PopulationSize; j++)
            {
              if (CandidateValue[i] > CandidateValue[j]) exchange(i, j);
            }
        }
      for (i = 0; i < PopulationSize; i++)
        {
          CandidateValueRate[i] = (CandidateValue[i] - CandidateValue[0]) / (CandidateValue[PopulationSize - 1] - CandidateValue[0]);
        }
      break;
    }
}

// check the best individual at this generation
int COptMethodEP2::fittest(void)
{
  int i, b;
  double f;
  f = CandidateValue[0];
  b = 0;
  for (i = 1; i < PopulationSize; i++)
    {
      if (CandidateValue[i] < f)
        {
          b = i;
          f = CandidateValue[i];
        }
    }
  return b;
}

void COptMethodEP2::TrackDataFile(int i)
{
  std::ofstream finalout("debugopt.dat", std::ios::app);

  if (!finalout)
    {
      std::cout << "debugopt.dat cannot be opened!" << std::endl;
      exit(1);
    }
  finalout << "#" << i << "\t" << std::setprecision(8) << CandidateValue[BestFoundSoFar] << std::endl;

  for (int j = 0; j < NumParameter; j++)
    {
      finalout << std::setprecision(8) << individual[BestFoundSoFar][j] << "\t";
    }

  finalout << std::endl;
  finalout << std::endl;

  finalout.close();
}

/**********************************the end **************************************/
