/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodHGASA.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/20 20:41:16 $
   End CVS Header */

/***************************************************************************
                    COptMethodHGASA.cpp  - Hybrid GA/SA  Optimizer
                    -------------------------------------------------
                       
         Implemented by Dingjun Chen
        
                       Starting Date: Mar. 2004 
   
                       COPASI project group
 ***************************************************************************/

/*************************************************************************************/
#define BESTFOUNDSOFAR 2
#define NumDirection 10
#define TRUE 1
#define FALSE 0
#define PI 3.1415926

#include <vector>

#include "copasi.h"
#include "COptMethod.h"
#include "CRealProblem.h"
#include "randomGenerator/CRandom.h"

COptMethodHGASA::COptMethodHGASA(const COptMethodHGASA & src):
    COptMethod(src)
{}

COptMethodHGASA::COptMethodHGASA(): COptMethod(CCopasiMethod::HybridGASA)
{
  addParameter("HybridGASA.Iterations",
               CCopasiParameter::UINT,
               (unsigned C_INT32) 10000);
  addParameter("HybridGASA.PopulationSize",
               CCopasiParameter::UINT,
               (unsigned C_INT32) 600);
  addParameter("HybridGASA.RandomGenerator.Type",
               CCopasiParameter::INT,
               (C_INT32) CRandom::mt19937);
  addParameter("HybridGASA.RandomGenerator.Seed",
               CCopasiParameter::INT,
               (C_INT32) 0);
}

/**
 * Destructor
 */
COptMethodHGASA::~COptMethodHGASA()
{}

/**
 * GA Optimizer Function:
 * Returns: nothing
 */
C_INT32 COptMethodHGASA::optimise()
{
  NumGeneration = (C_INT32) getValue("HybridGASA.Iterations");
  PopulationSize = (C_INT32) getValue("HybridGASA.PopulationSize");
  NumParameter = mOptProblem->getVariableSize();

  /* Create a random number generator */
  CRandom::Type Type;
  Type = (CRandom::Type) (C_INT32) getValue("HybridGASA.RandomGenerator.Type");
  C_INT32 Seed;
  Seed = (C_INT32) getValue("HybridGASA.RandomGenerator.Seed");
  CRandom * pRand = CRandom::createGenerator(Type, Seed);

  assert(pRand);

  double * Minimum = mOptProblem->getParameterMin().array();
  double * Maximum = mOptProblem->getParameterMax().array();

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
              if (Minimum[j] == 0.0) Minimum[j] = DBL_EPSILON;
              if ((Maximum[j] <= 0.0) || (Minimum[j] <= 0.0)) linear = TRUE;
              else
                {
                  la = log10(Maximum[j]) - log10(Minimum[j]);
                  if (la < 1.8) linear = TRUE;
                }
              // set it to a random value within the interval
              if (linear)
                individual[i][j] = Minimum[j] + pRand->getRandomCC() * (Maximum[j] - Minimum[j]);
              else
                individual[i][j] = Minimum[j] * pow(10, la * pRand->getRandomCC());
            }
          catch (int)
            {
              individual[i][j] = (Maximum[j] - Minimum[j]) * 0.5 + Minimum[j];
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

  //double a1=0.00000000001;
  //double b1=0.9;

  // Iterations of GA
  for (i = 0; i < NumGeneration; i++)
    {
      std::cout << std::endl;
      std::cout << "GA is processing at generation " << i << std::endl;

      TrackDataFile(i);
      // replicate the individuals
      replicate();

      //Mutating some offspring
      for (int nn = PopulationSize; nn < 2*PopulationSize; nn++)
        {
          double mut;

          // mutate the parameters
          // calculate the mutatated parameter, only some of offspring mutated
          //if (floor(10*rand()/RAND_MAX) >= 2)

          if (pRand->getRandomCC() >= 0.15)
            {
              for (int j = 0; j < NumParameter; j++)
                {
                  if (floor(10*rand() / RAND_MAX) > 5)
                    {
                      //mut = individual[nn][j] + floor(1000000*rand()/RAND_MAX)/1000000;
                      //   if(i<5000) mut = individual[nn][j] + pRand->getRandomCC()*(Maximum[j]-Minimum[j])/(i*i);

                      // if(i<NumGeneration/2)  mut = individual[nn][j]*(1 + pRand->getRandomCC());
                      // mut = individual[nn][j]+(Maximum[j]-individual[nn][j])*(1-pow((pRand->getRandomCC()),pow((1-i/NumGeneration),2)));
                      //  if(i>=NumGeneration/2) mut = individual[nn][j] *(1+ (1-pow((pRand->getRandomCC()),pow((1-i/NumGeneration),2))));

                      //   if(i>=5000) mut = individual[nn][j] + pRand->getRandomCC()*(Maximum[j]-Minimum[j])/sqrt(i);
                      //   if(i>=5000) mut = individual[nn][j] + pRand->getRandomCC()*(Maximum[j]-Minimum[j])/sqrt(i);
                      //   if(i<5000) mut = individual[nn][j] *(1+ (1-pow((pRand->getRandomCC()),pow((1-i/NumGeneration),2))));

                      //if(i < NumGeneration/16) mut = individual[nn][j]*(1 + pRand->getRandomCC());
                      //  if(i < NumGeneration/16) mut = individual[nn][j]+ pRand->getRandomCC();
                      //else  mut = individual[nn][j]*(1 + pRand->getRandomCC()*(pow((a1+1-b1),i/NumGeneration)-(1-b1)));
                      //   else  mut = individual[nn][j]+ pRand->getRandomCC()*(pow((a1+1-b1),i/NumGeneration)-(1-b1));

                      if (i < NumGeneration*0.5) mut = individual[nn][j] * (1 + pRand->getRandomCC());
                      else
                        {
                          if (i < NumGeneration*0.6) mut = individual[nn][j] * (1 + 0.5 * pRand->getRandomCC());
                          else
                            {
                              if (i < NumGeneration*0.7) mut = individual[nn][j] * (1 + 0.25 * pRand->getRandomCC());
                              else
                                {
                                  if (i < NumGeneration*0.8) mut = individual[nn][j] * (1 + 0.1 * pRand->getRandomCC());
                                  else
                                    {
                                      if (i < NumGeneration*0.9) mut = individual[nn][j] * (1 + 0.01 * pRand->getRandomCC());
                                      else
                                        {
                                          if (i < NumGeneration*0.95) mut = individual[nn][j] * (1 + 0.001 * pRand->getRandomCC());
                                          else mut = individual[nn][j] * (1 + 0.0001 * pRand->getRandomCC());
                                        }
                                    }
                                }
                            }
                        }
                    }
                  else
                    {
                      //mut = individual[nn][j] - floor(1000000*rand()/RAND_MAX)/1000000;
                      //  if(i<5000) mut = individual[nn][j] - pRand->getRandomCC()*(Maximum[j]-Minimum[j])/(i*i);
                      //   if(i>=5000) mut = individual[nn][j] - pRand->getRandomCC()*(Maximum[j]-Minimum[j])/sqrt(i);

                      // mut = individual[nn][j]+(individual[nn][j]-Minimum[j])*(1-pow((pRand->getRandomCC()),pow((1-i/NumGeneration),2)));
                      //  if(i< NumGeneration/2)  mut = individual[nn][j]*(1 - pRand->getRandomCC());
                      //  if(i>= NumGeneration/2) mut = individual[nn][j] *(1- (1-pow((pRand->getRandomCC()),pow((1-i/NumGeneration),2))));

                      //if(i< NumGeneration/16) mut = individual[nn][j]*(1 - pRand->getRandomCC());
                      //   if(i< NumGeneration/16) mut = individual[nn][j] - pRand->getRandomCC();
                      //else  mut = individual[nn][j]*(1 - pRand->getRandomCC()*(pow((a1+1-b1),i/NumGeneration)-(1-b1)));
                      //    else  mut = individual[nn][j] - pRand->getRandomCC()*(pow((a1+1-b1),i/NumGeneration)-(1-b1));

                      if (i < NumGeneration*0.5) mut = individual[nn][j] * (1 - pRand->getRandomCC());
                      else
                        {
                          if (i < NumGeneration*0.6) mut = individual[nn][j] * (1 - 0.5 * pRand->getRandomCC());
                          else
                            {
                              if (i < NumGeneration*0.7) mut = individual[nn][j] * (1 - 0.25 * pRand->getRandomCC());
                              else
                                {
                                  if (i < NumGeneration*0.8) mut = individual[nn][j] * (1 - 0.1 * pRand->getRandomCC());
                                  else
                                    {
                                      if (i < NumGeneration*0.9) mut = individual[nn][j] * (1 - 0.01 * pRand->getRandomCC());
                                      else
                                        {
                                          if (i < NumGeneration*0.95) mut = individual[nn][j] * (1 - 0.001 * pRand->getRandomCC());
                                          else mut = individual[nn][j] * (1 - 0.0001 * pRand->getRandomCC());
                                        }
                                    }
                                }
                            }
                        }
                      // mut = individual[nn][j] * (1 + floor(1000000*rand()/RAND_MAX)/1000000);
                      //mut = individual[nn][j] * (1 + pRand->getRandomCC());
                    }
                  // check boundary and force it to be within the bounds
                  if (mut <= Minimum[j]) mut = Minimum[j] + DBL_EPSILON;
                  else
                    {
                      if (mut < Minimum[j]) mut = Minimum[j];
                    }

                  if (mut >= Maximum[j]) mut = Maximum[j] - DBL_EPSILON;
                  else
                    {
                      if (mut > Maximum[j]) mut = Maximum[j];
                    }
                  // store it
                  individual[nn][j] = mut;
                }
            }
          // evaluate the fitness
          for (int kk = 0; kk < NumParameter; kk++)
            {
              Parameter[kk] = individual[nn][kk];
            }
          CandidateValue[nn] = mOptProblem->calculate();
        }

      // select approprate individuals as new population
      // select(1);
      //select(2);
      if ((i % 2) == 0) select(2);
      else select(3);
      // if((i%2)==0) select(3);
      //  else select(4);

      // Here introduce SA to optimise some top indiviudals
      //if(i>=0.5*NumGeneration)
      if ((i >= 1) && (i % 1000 == 0))
        {
          for (int optKK = 0; optKK < 6; optKK++)
            {
              optimise(optKK);
            }
        }

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
        //if((u50==0)&&(i-last_update>150))
        {
          for (int mm = PopulationSize / 2; mm < PopulationSize; mm++)
            {
              for (int jj = 0; jj < NumParameter; jj++)
                {
                  try
                    {
                      // determine if linear or log scale
                      linear = FALSE; la = 1.0;
                      if (Minimum[jj] == 0.0) Minimum[jj] = DBL_EPSILON;
                      if ((Maximum[jj] <= 0.0) || (Minimum[jj] <= 0.0)) linear = TRUE;
                      else
                        {
                          la = log10(Maximum[jj]) - log10(Minimum[jj]);
                          if (la < 1.8) linear = TRUE;
                        }
                      // set it to a random value within the interval
                      if (linear)
                        individual[mm][jj] = Minimum[jj] + pRand->getRandomCC() * (Maximum[jj] - Minimum[jj]);
                      else
                        individual[mm][jj] = Minimum[jj] * pow(10, la * pRand->getRandomCC());
                    }
                  catch (int)
                    {
                      individual[mm][jj] = (Maximum[jj] - Minimum[jj]) * 0.5 + Minimum[jj];
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
          //u50=150; u30=100; u10=50;
        }
      else
        {
          if ((u30 == 0) && (i - last_update > 30))
            //if((u30==0)&&(i-last_update>100))
            {
              for (int mm = (int)floor(PopulationSize * 0.7); mm < PopulationSize; mm++)
                {
                  for (int jj = 0; jj < NumParameter; jj++)
                    {
                      try
                        {
                          // determine if linear or log scale
                          linear = FALSE; la = 1.0;
                          if (Minimum[jj] == 0.0) Minimum[jj] = DBL_EPSILON;
                          if ((Maximum[jj] <= 0.0) || (Minimum[jj] <= 0.0)) linear = TRUE;
                          else
                            {
                              la = log10(Maximum[jj]) - log10(Minimum[jj]);
                              if (la < 1.8) linear = TRUE;
                            }
                          // set it to a random value within the interval
                          if (linear)
                            individual[mm][jj] = Minimum[jj] + pRand->getRandomCC() * (Maximum[jj] - Minimum[jj]);
                          else
                            individual[mm][jj] = Minimum[jj] * pow(10, la * pRand->getRandomCC());
                        }
                      catch (int)
                        {
                          individual[mm][jj] = (Maximum[jj] - Minimum[jj]) * 0.5 + Minimum[jj];
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
              //u30=100; u10=50;
            }
          else
            {
              if ((u10 == 0) && (i - last_update > 10))
                //if((u10==0)&&(i-last_update>50))
                {
                  for (int mm = (int) floor(PopulationSize * 0.9); mm < PopulationSize; mm++)
                    {
                      for (int jj = 0; jj < NumParameter; jj++)
                        {
                          try
                            {
                              // determine if linear or log scale
                              linear = FALSE; la = 1.0;
                              if (Minimum[jj] == 0.0) Minimum[jj] = DBL_EPSILON;
                              if ((Maximum[jj] <= 0.0) || (Minimum[jj] <= 0.0)) linear = TRUE;
                              else
                                {
                                  la = log10(Maximum[jj]) - log10(Minimum[jj]);
                                  if (la < 1.8) linear = TRUE;
                                }
                              // set it to a random value within the interval
                              if (linear)
                                individual[mm][jj] = Minimum[jj] + pRand->getRandomCC() * (Maximum[jj] - Minimum[jj]);
                              else
                                individual[mm][jj] = Minimum[jj] * pow(10, la * pRand->getRandomCC());
                            }
                          catch (int)
                            {
                              individual[mm][jj] = (Maximum[jj] - Minimum[jj]) * 0.5 + Minimum[jj];
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

/*
// evaluate the fitness of one individual
double COptMethodHGASA::evaluate(int i)
{
 int j;
 bool outside_range = FALSE;
 double fitness;
 double fitness0;
 double tmp; 
 
 // evaluate the fitness
 try
 {
  fitness0=0;
  for(j=0; j<NumParameter; j++)
   {
     fitness=fitness0+pow(individual[i][j],4.0)-16.0*pow(individual[i][j],2.0)+5.0*individual[i][j];
     fitness0=fitness;
    }
    fitness=fitness0/2.0;
 }
 catch(int)
 {
  fitness = DBL_MAX;
 }
 
 return fitness;
}
 */

// copy individual o to position d
void COptMethodHGASA::copy(int o, int d)
{
  int i;

  for (i = 0; i < NumParameter; i++)
    {
      individual[d][i] = individual[o][i];
    }

  CandidateValue[d] = CandidateValue[o];
}

// swap individuals o and d
void COptMethodHGASA::swap(int o, int d)
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
void COptMethodHGASA::exchange(int o, int d)
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

void COptMethodHGASA::crossover(int p1, int p2, int c1, int c2)
{
  int i, j, s, e;
  int pp1, pp2, tmp, l;

  //srand(time(NULL)); rand();

  try
    {
      if (NumParameter > 1)
        {
          // get a random number of crossover points, always less than half the number of genes
          NumCrossPoint = (int)fabs(floor((NumParameter / 2) * rand() / RAND_MAX));
          // NumCrossPoint = (int)floor((NumParameter/2)*pRand->getRandomCC());
        }
      else NumCrossPoint = 0;
      // if less than 0 just copy parent to child
      if (NumCrossPoint == 0)
        {
          for (j = 0; j < NumParameter; j++)
            {
              individual[c1][j] = individual[p1][j];
              individual[c2][j] = individual[p2][j];
            }
          return;
        }
      // chose first point
      CrossPoint[0] = 1 + (int)fabs(floor((NumParameter - NumCrossPoint) * rand() / RAND_MAX));
      //CrossPoint[0] = 1 + (int)floor((NumParameter-NumCrossPoint)*pRand->getRandomCC());
      // chose the others
      for (i = 1; i < NumCrossPoint; i++)
        {
          l = NumParameter - NumCrossPoint + i - 1 - CrossPoint[i - 1];
          CrossPoint[i] = 1 + CrossPoint[i - 1] + (l == 0 ? 0 : (int)fabs(floor(l * rand() / RAND_MAX)));
          //CrossPoint[i] = 1 + CrossPoint[i-1] + (l==0 ? 0 : (int)floor(l*pRand->getRandomCC()));
        }
      // copy segments
      pp1 = p2; pp2 = p1;
      for (i = 0; i <= NumCrossPoint; i++)
        {
          // swap the indexes
          tmp = pp1;
          pp1 = pp2;
          pp2 = tmp;
          if (i == 0) s = 0; else s = CrossPoint[i - 1];
          if (i == NumCrossPoint) e = NumParameter; else e = CrossPoint[i];
          for (j = s; j < e; j++)
            {
              individual[c1][j] = individual[pp1][j];
              individual[c2][j] = individual[pp2][j];
            }
        }
    }
  catch (int)
    {}}

// replicate the individuals w/ crossover
void COptMethodHGASA::replicate(void)
{
  int i, parent1, parent2;

  // reproduce in consecutive pairs
  for (i = 0; i < PopulationSize / 2; i++)
    {
      parent1 = (int)fabs(floor(PopulationSize * rand() / RAND_MAX));
      parent2 = (int)fabs(floor(PopulationSize * rand() / RAND_MAX));
      crossover(parent1, parent2, PopulationSize + i*2, PopulationSize + i*2 + 1);
    }
  // check if there is one left over and just copy it
  if (PopulationSize % 2 > 0) copy(PopulationSize - 1, 2*PopulationSize - 1);
}

// select PopulationSize individuals
void COptMethodHGASA::select(int SelectionStrategy)
{
  int i, j, TournamentSize, RandomRival;
  int RandomIndividual;
  //srand(time(NULL)); rand();

  switch (SelectionStrategy)
    {
    case 1:      // parent-offspring competition
      for (i = PopulationSize; i < 2*PopulationSize; i++)
        {
          // if offspring is fitter keep it
          for (j = 0; j < PopulationSize; j++)
            {
              if (CandidateValue[i] < CandidateValue[j]) exchange(i, j);
            }
        }
      break;
    case 2:      // tournament competition
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
    }
}

// check the best individual at this generation
int COptMethodHGASA::fittest(void)
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

void COptMethodHGASA::TrackDataFile(int i)
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

// SA optimization function

C_INT32 COptMethodHGASA::optimise(int index)
{
  //C_INT32 NumSignificantPoint, NumTempChange, NumIteration = (C_INT32) getValue("SimulatedAnnealing.Iterations");
  C_INT32 NumSignificantPoint, NumTempChange, NumIteration = 1000;
  C_INT32 j, NumParameter = mOptProblem->getVariableSize();

  //variable settings neccessary for SA
  CVector<double> candparameter(NumParameter);  //one-dimentional array of candidate value for parameters
  double candFuncValue;                // candidate value of objective function

  CVector<double> thisparameter(NumParameter);  //current parameters
  double thisFuncValue;                //current value of the objective function

  CVector <double> newparameter(NumParameter);   //new parameter value
  double newFuncValue;     //function value of new point

  CVector <double> step(NumParameter);   //array of maximum steps for each parameter
  CVector <int> NumStepAccep(NumParameter);       //number of steps accepted

  double TempDecreaseRate = 0.85; //temperature decrease rate
  double BoltzmannConstant = 1.0; //Boltzmann constant

  double InitialTemp = 1.0; //initial temperature
  double t;  //current temperature

  double ConvgCriterion = 0.01; // convergence criterion or program termination criterion
  double ChangeValue, EnergyDifference;

  CVector <double> fk(BESTFOUNDSOFAR);
  bool ready;

  /* Create a random number generator */
  CRandom::Type Type;
  Type = (CRandom::Type) (C_INT32) getValue("HybridGASA.RandomGenerator.Type");
  unsigned C_INT32 Seed;
  Seed = (unsigned C_INT32) getValue("HybridGASA.RandomGenerator.Seed");
  CRandom * pRandSA = CRandom::createGenerator(Type, Seed);

  assert(pRandSA);

  double * Minimum = mOptProblem->getParameterMin().array();
  double * Maximum = mOptProblem->getParameterMax().array();

  CVector< C_FLOAT64 > & SAParameter = mOptProblem->getCalculateVariables();

  //double * Parameter;

  //dump_datafile_init()

  //inital temperature
  t = InitialTemp;

  //inital point
  NumSignificantPoint = 0;

  /*
  //generate initial parameters randomly
  for (j = 0; j < NumParameter; j++)
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
          Minimum[j] + pRandSA->getRandomCC() * (Maximum[j] - Minimum[j]);
      else
        Parameter[j] = Minimum[j] * pow(10, la * pRandSA->getRandomCC());
    } //  Initialization ends
  */

  for (j = 0; j < NumParameter; j++)
    {
      SAParameter[j] = individual[index][j];
    }

  for (int kk = 0; kk < NumParameter; kk++)
    candparameter[kk] = thisparameter[kk] = newparameter[kk] = SAParameter[kk];

  // calculate the function fitness value
  double FitnessValue = mOptProblem->calculate();
  thisFuncValue = candFuncValue = FitnessValue;

  //Remember them
  for (int mm = 0; mm < BESTFOUNDSOFAR; mm++) fk[mm] = thisFuncValue;

  //initial step sizes
  for (int jj = 0; jj < NumParameter; jj++)
    {
      NumStepAccep[jj] = 0;
      step[jj] = fabs(candparameter[jj]);
    }

  //no temperature reductions yet
  NumTempChange = 0;

  do
    {
      for (int ff = 0; ff < NumIteration; ff++) //step adjustments
        {
          std::cout << "New individual begins ......" << index << std::endl;
          std::cout << "New iteration begins ......" << std::endl;
          std::cout << "Current Temperature: " << t << std::endl;
          std::cout << "Number of Temperature Change: " << NumTempChange << std::endl;

          for (j = 0; j < NumDirection; j++) // adjustment in all directions
            {
              for (int hh = 0; hh < NumParameter; hh++)
                {
                  // ChangeValue=tan(2*PI*rand()/RAND_MAX)*(t/pow(pow(2,2.0)+t*t,(NumParameter+1)/2.0));
                  ChangeValue = tan(2 * PI * pRandSA->getRandomCC()) * (t / pow(pow(2, 2.0) + t * t, (NumParameter + 1) / 2.0));
                  newparameter[hh] = thisparameter[hh] + step[hh] * ChangeValue;

                  if (newparameter[hh] < Minimum[hh]) newparameter[hh] = Minimum[hh] + pRandSA->getRandomCC() * (Maximum[hh] - Minimum[hh]);
                  if (newparameter[hh] > Maximum[hh]) newparameter[hh] = Minimum[hh] + pRandSA->getRandomCC() * (Maximum[hh] - Minimum[hh]);
                  for (int exchange = 0; exchange < NumParameter; exchange++)
                    {
                      SAParameter[exchange] = newparameter[exchange];
                    }

                  // calculate the function value
                  double FitnessValue = mOptProblem->calculate();
                  newFuncValue = FitnessValue;

                  //Calculate the energy difference
                  EnergyDifference = newFuncValue - thisFuncValue;

                  //keep newparameter if energy is reduced
                  if (newFuncValue <= thisFuncValue)
                    {
                      for (int exchange = 0; exchange < NumParameter; exchange++)
                        {
                          thisparameter[exchange] = newparameter[exchange];
                        }
                      thisFuncValue = newFuncValue;

                      NumSignificantPoint++; // a new point counted
                      NumStepAccep[hh]++; //a new point in this coordinate counted

                      if (thisFuncValue < candFuncValue)
                        {
                          for (int aa = 0; aa < NumParameter; aa++)
                            individual[index][aa] = SAParameter[aa] = candparameter[aa] = thisparameter[aa];
                          CandidateValue[index] = candFuncValue = thisFuncValue;

                          if (!mOptProblem->checkFunctionalConstraints())
                            continue;

                          //set the  best function value
                          //mOptProblem->setBestValue(candFuncValue);
                          //std::cout << "the Best value (" << NumSignificantPoint << "): " << candFuncValue << std::endl;

                          //store the combination of the best parameter values found so far at current temperature
                          //mOptProblem->getBestParameter() = *mParameters;

                          //std::cout << "the Best Parameters: (";
                          //for (int kk = 0; kk < mOptProblem->getParameterNum(); kk++)
                          // std::cout << mOptProblem->getParameter(kk) << ", ";

                          // std::cout << ")" << std::endl;
                        }
                    }
                  else
                    {
                      //keep newparameter with probability, if newFuncValue is increased
                      double Probability = exp(-(newFuncValue - thisFuncValue) / (BoltzmannConstant * t));
                      if (Probability > pRandSA->getRandomCC())
                        {
                          //Keep the new point
                          for (int exchange = 0; exchange < NumParameter; exchange++)
                            {
                              thisparameter[exchange] = newparameter[exchange];
                            }
                          thisFuncValue = newFuncValue;
                          NumSignificantPoint++; // a new point counted
                          NumStepAccep[hh]++; //a new point in this coordinate counted
                        }
                    }
                }
            }

          //update the step sizes
          for (int nn = 0; nn < NumParameter; nn++)
            {
              double StepAdjustment = (double) NumStepAccep[nn] / (double)NumDirection;
              if (StepAdjustment > 0.6) step[nn] *= 1 + 5 * (StepAdjustment - 0.6);
              if (StepAdjustment < 0.4) step[nn] /= 1 + 5 * (0.4 - StepAdjustment);
              NumStepAccep[nn] = 0;
            }
        }

      //update the temperature
      t *= TempDecreaseRate;
      NumTempChange++;

      // if this is the first cycle then ignore the convergence test
      if (NumTempChange == 1) ready = FALSE;
      else
        {
          ready = TRUE;
          //check if there is not much change for termination criterion since last BESTFOUNDSOFAR times
          for (int ii = 0; ii < BESTFOUNDSOFAR; ii++)
            if (fabs(fk[ii] - thisFuncValue) > ConvgCriterion)
              {
                ready = FALSE;
                break;
              }
          if (!ready)
            {
              for (int aa = 0; aa < BESTFOUNDSOFAR - 1; aa++)
                fk[aa] = fk[aa + 1];
              fk[BESTFOUNDSOFAR - 1] = thisFuncValue;
            }
          else
            //check the termination criterion of not much larger than last optimal
            if (fabs(thisFuncValue - candFuncValue) > ConvgCriterion)ready = FALSE;
        }

      if (!ready)
        {
          NumSignificantPoint++;
          for (int kk = 0; kk < NumParameter; kk++)
            thisparameter[kk] = candparameter[kk];
          thisFuncValue = candFuncValue;
        }
    }
  while (!ready); // do-while loop ends

  pdelete(pRandSA);
  return 0;
}

/**********************************the end **************************************/
