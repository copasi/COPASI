
/* COptMethodSA code */

/***************************************************************************************
 * This is the implementation of the Simulated Annealing for Optimization.  The
 * class is inherited from the COptAlgorithm class
 *
 *       Implemented by Dingjun Chen
 *  Starting Date: 09/22/03
 *
 ***************************************************************************************/

#define BESTFOUNDSOFAR 2
#define NumDirection 10
#define TRUE 1
#define FALSE 0 
// #define PI 3.1415926

#include <vector>
#include <math.h>

#include "copasi.h"
#include "COptMethod.h"
#include "COptMethodSA.h"
#include "CRealProblem.h"
#include "randomGenerator/CRandom.h"

static double PI = 4.0 * atan(1.0);

COptMethodSA::COptMethodSA():
    COptMethod()
{
  setName("SimulatedAnnealing");
  mTypeEnum = COptMethod::SimulatedAnnealing;
  setType(COptMethod::TypeName[mTypeEnum]);

  add("SimulatedAnnealing.Iterations", 10000, CParameter::UINT);
  add("SimulatedAnnealing.RandomGenerator.Type", CRandom::mt19937, CParameter::INT);
  add("SimulatedAnnealing.RandomGenerator.Seed", 0, CParameter::INT);
}

COptMethodSA::COptMethodSA(const COptMethodSA & src):
    COptMethod(src)
{}

/**
 * Destructor
 */
COptMethodSA::~COptMethodSA(){}

/**
 * Optimizer Function
 * Returns: nothing
 */

C_INT32 COptMethodSA::optimise()
{
  C_FLOAT64 la;
  C_INT32 NumSignificantPoint, NumTempChange, NumIteration = (C_INT32) getValue("SimulatedAnnealing.Iterations");
  C_INT32 j, NumParameter = mParameters->size();

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

  double ConvgCriterion = 0.00001; // convergence criterion or program termination criterion
  double ChangeValue, EnergyDifference;

  CVector <double> fk(BESTFOUNDSOFAR);
  bool ready, linear;

  /* Create a random number generator */
  CRandom::Type Type;
  Type = (CRandom::Type) (C_INT32) getValue("SimulatedAnnealing.RandomGenerator.Type");
  unsigned C_INT32 Seed;
  Seed = (unsigned C_INT32) getValue("SimulatedAnnealing.RandomGenerator.Seed");
  CRandom * pRand = CRandom::createGenerator(Type, Seed);

  assert(pRand);

  double * Minimum = mParameterMin->array();
  double * Maximum = mParameterMax->array();
  double * Parameter = mParameters->array();

  //dump_datafile_init()

  //inital temperature
  t = InitialTemp;

  //inital point
  NumSignificantPoint = 0;

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
          Minimum[j] + pRand->getRandomCC() * (Maximum[j] - Minimum[j]);
      else
        Parameter[j] = Minimum[j] * pow(10, la * pRand->getRandomCC());
    } //  Initialization ends

  for (int kk = 0; kk < NumParameter; kk++)
    candparameter[kk] = thisparameter[kk] = newparameter[kk] = Parameter[kk];

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
          std::cout << "New iteration begins ......" << std::endl;
          std::cout << "Current Temperature: " << t << std::endl;
          std::cout << "Number of Temperature Change: " << NumTempChange << std::endl;

          for (j = 0; j < NumDirection; j++) // adjustment in all directions
            {
              for (int hh = 0; hh < NumParameter; hh++)
                {
                  // ChangeValue=tan(2*PI*rand()/RAND_MAX)*(t/pow(pow(2,2.0)+t*t,(NumParameter+1)/2.0));
                  ChangeValue = tan(2 * PI * pRand->getRandomCC()) * (t / pow(pow(2, 2.0) + t * t, (NumParameter + 1) / 2.0));
                  newparameter[hh] = thisparameter[hh] + step[hh] * ChangeValue;

                  if (newparameter[hh] < Minimum[hh]) newparameter[hh] = Minimum[hh] + pRand->getRandomCC() * (Maximum[hh] - Minimum[hh]);
                  if (newparameter[hh] > Maximum[hh]) newparameter[hh] = Minimum[hh] + pRand->getRandomCC() * (Maximum[hh] - Minimum[hh]);
                  for (int exchange = 0; exchange < NumParameter; exchange++)
                    {
                      Parameter[exchange] = newparameter[exchange];
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
                            Parameter[aa] = candparameter[aa] = thisparameter[aa];
                          candFuncValue = thisFuncValue;

                          if (!mOptProblem->checkFunctionalConstraints())
                            continue;

                          //set the  best function value
                          mOptProblem->setBestValue(candFuncValue);
                          std::cout << "the Best value (" << NumSignificantPoint << "): " << candFuncValue << std::endl;

                          //store the combination of the best parameter values found so far at current temperature
                          mOptProblem->getBestParameter() = *mParameters;

                          std::cout << "the Best Parameters: (";
                          for (int kk = 0; kk < mOptProblem->getParameterNum(); kk++)
                            std::cout << mOptProblem->getParameter(kk) << ", ";

                          std::cout << ")" << std::endl;
                        }
                    }
                  else
                    {
                      //keep newparameter with probability, if newFuncValue is increased
                      double Probability = exp(-(newFuncValue - thisFuncValue) / (BoltzmannConstant * t));
                      if (Probability > pRand->getRandomCC())
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

  pdelete(pRand);
  return 0;
}
