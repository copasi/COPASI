/**
 *  File name: CRealProblem.cpp
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *           functions. It's used by COptAlgorithm class and COptimization class
 */

#include "CRealProblem.h"

//? Do I need to call super() ? find out

//  Default constructor
CRealProblem::CRealProblem() : COptProblem()
{}

// Destructor
CRealProblem::~CRealProblem()
{ }

// calculate function for optimization
// YOHE: Here is the N-Dimensional Test Function I use:
//        f(x) = (1/2)Sum(j=1, n)(Xj^4 - 16Xj^2 + 5Xj)
//        where, x = [X1, X2, ... , Xj, ..., Xn]
//        Number of global minima = 1;
//       Global minimum found by TRUST:
//        [-2.90354, -2.90354, ..., -2.90354].
// calculate function for optimization
C_FLOAT64 CRealProblem::calculate()
{
  int j;

  double fitness;
  double fitness0;

  int parameterNum = getParameterNum();
  double * parameterValues = getParameterValues();

  //YOHE: this is the mathematics function used only for testing purpose
  // evaluate the fitness

  try
    {
      fitness0 = 0;

      for (j = 0; j < parameterNum; j++)
        {
          fitness = fitness0 + pow(parameterValues[j], 4.0) - 16.0 * pow(parameterValues[j], 2.0)
                    + 5.0 * parameterValues[j];
          fitness0 = fitness;
        }

      fitness = fitness0 / 2.0;
    }
  catch (unsigned int e)
    {
      fitness = DBL_MAX;
    }

  //set the best value as the fitness;
  //setBestValue(fitness);
  //cout<<"fitness is:\t"<<fitness;
  return fitness;
}
