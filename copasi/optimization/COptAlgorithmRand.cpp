/***************************************************************************
                      COptAlgorithmRand.cpp  -  Random Optimizer
                         -------------------

Programmer           : Rohan Luktuke
email                : rluktuke@vt.edu
 ***************************************************************************/

/***************************************************************************
 * This is the implementation of the Random Algorithm for Optimization.  The
 * class is inherited from the COptAlgorithm class
 ***************************************************************************/

#include<iostream>
#include<fstream>
#include<sys/timeb.h>
#include<time.h>
#include <vector>

#include "copasi.h"
#include "COptAlgorithmRand.h"
#include "CRealProblem.h"
#include "randomGenerator/CRandom.h"
#include "randomGenerator/CRandom.cpp"

#define TRUE 1
#define FALSE 0 
//enum answer{NO,YES};

using namespace std;

/**
 * Default constructor
 */
COptAlgorithmRand::COptAlgorithmRand(): COptAlgorithm()
{
  /**
   * Setting the Method Parameter to 1.
   */
  setMethodParameterNumber(1);

  //vector<COptAlgorithmParameter>& AlgorithmParameters = getMethodParameters();
  //CMethodParameterList AlgorithmParameters;
  /**
   * Specifying the values of the Method Parameter.
   */

  /** -- commented ... alternative class for specifying method parameters
  AlgorithmParameters.resize(1);
  AlgorithmParameters[0].setName("Iterations");
  //default value - 100 iterations
  AlgorithmParameters[0].setValue(100);
  */ 
  //AlgorithmParameters.add("Iterations",100.0);

  add("Iterations", 100000.0);

  /**
   * Declaring a variable of the enum CRandom::Type
   */
  CRandom::Type t;

  /**
   * Setting the value of t to r250
   */
  t = CRandom::r250;
  /**
   * Creating a Random number generator of type r250 with seed 2
   */
  rand = CRandom::createGenerator(t, 2);
}

/**
 * Copy Constructor
 * Parameter: COptAlgorithmRand&
 */
COptAlgorithmRand::COptAlgorithmRand(const COptAlgorithmRand& source):
    COptAlgorithm(source),
    rand(source.rand)
{}

/**
 * Destructor
 */
COptAlgorithmRand::~COptAlgorithmRand(){}

/**
 * Optimizer Function
 * Returns: nothing
 */
C_INT32 COptAlgorithmRand::optimise()
{
  C_INT32 linear;
  C_FLOAT64 la, x, candx;
  C_FLOAT64 *mMin, *mMax;
  C_INT32 count, i, j;
  //set candx to max value
  candx = DBL_MAX;
  //cout<<"inside optimise()";
  //count = (C_INT32) getMethodParameterValue(0);
  count = (C_INT32) getValue(0);
  /**
   * mMin and mMax store pointers to arrays mParameterMin/Max.
   * particular values can be accessed by using subscripts.
   */
  mMin = mOptProblem->getParameterMin();
  mMax = mOptProblem->getParameterMax();

  for (i = 0; i < count; i++)
    {
      //change parameters randomly
      for (j = 0; j < mOptProblem->getParameterNum(); j++)
        {
          linear = FALSE;
          la = 1.0;

          if (mMin[j] == 0.0)
            mMin[j] = DBL_EPSILON;

          if ((mMax[j] <= 0.0) || (mMin[j] <= 0.0))
            linear = TRUE;

          else
            {
              la = log10(mMax[j]) - log10(mMin[j]);
              if (la < 1.8)
                linear = TRUE;
            }

          if (linear)
            mOptProblem->setParameter(j, (mMin[j] + rand->getRandomCC() * (mMax[j] - mMin[j])));
          else
            mOptProblem->setParameter(j, (mMin[j] * pow(10, la * rand->getRandomCC())));

        } // j<..getParameterNum() loop ends

      // check parametric constraints
      mOptProblem->checkParametricConstraints();

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
          std::cout << "Best Parameters: (";
          for (C_INT32 p = 0; p < mOptProblem->getParameterNum(); p++)
            {
              mOptProblem->setBestParameter(p, mOptProblem->getParameter(p));
              std::cout << mOptProblem->getParameter(p) << ", ";
            }
          std::cout << ")" << std::endl;
        }
    }
  return 0;
}
