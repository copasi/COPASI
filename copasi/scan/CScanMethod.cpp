/**
 *  CScanMethod class.
 *  This class describes the Scan method
 *
 *  Created for Copasi by Rohan Luktuke 2002
 */

#include <string>

//#define COPASI_TRACE_CONSTRUCTION
#include "math.h"
#include "copasi.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"
#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"
#include "CScanProblem.h"
#include "CScanMethod.h"

// this will have to be defined somewhere else with the
// values of other distribution types
#define SD_REGULAR 1

CScanMethod * CScanMethod::createMethod() {return new CScanMethod;}

CScanMethod::CScanMethod()
{}

/**
 *  The main scan method.
 */

void CScanMethod::scan(unsigned C_INT32 s, bool C_UNUSED(nl))
{
  unsigned C_INT32 scanDimension = scanProblem->getListSize();
  unsigned C_INT32 i, next, top;
  //1.  find the first/last master scan item

  if (s > 0)
    {
      for (i = s - 1; i > 0; i--)
        //if(scanItem[i]->Indp) break;
        if (scanProblem->getScanItemParameter(i, "Indp") == 1.0) break;

      next = i;
    }

  else
    next = 0;

  /* 2.  find the last slave item */

  //if(s<scandimension-1)
  if (s < scanDimension - 1)
    {
      for (i = s + 1; i < scanDimension; i++)
        if (scanProblem->getScanItemParameter(i, "Indp") == 1.0) break;
      top = i;
    }
  else
    top = scanDimension;

  /* 3.  switch the grid type (distribution) - regular, normal etc */

  /* The "gridType" is just a temporary name for the parameter.
     A proper name will have to be given at the time of entering
     this parameter into the vector.
  */ 
  //switch(gridtype[distribution])
  switch ((int)scanProblem->getScanItemParameter(i, "gridType"))
    {
    case SD_REGULAR:
      //start with min value - give 0 as first param in setscanparametervalue
      setScanParameterValue(0, s, top);

      for (i = 1; i < scanProblem->getScanItemParameter(i, "density"); i++)
        {
          if (s != 0) scan(next, false);
          else
            {
              // some function
              //simulate();
            }
          setScanParameterValue(i, s, top);
        }
      break;
    }
} // scan() ends

/**
  *  Set a pointer to the problem.
  *  This method is used by CTrajectory
  *  @param "CTrajectoryProblem *" problem
  */
void CScanMethod::setProblem(CScanProblem * problem)
{scanProblem = problem;}

/**
 *  set the values master and all slave parameters
 * @param "C_INT32 i" initial value
 * @param "C_INT32 first" first parameter (master)
 * @param "C_INT32 last" last slave parameter
 */

void CScanMethod::setScanParameterValue(unsigned C_INT32 i,
                                        unsigned C_INT32 first,
                                        unsigned C_INT32 last)
{
  unsigned C_INT32 j;
  double min, max, incr;
  for (j = first; j < last; j++)
    {
      // making a copy of the min and max parameters of the scanItem j
      min = scanProblem->getScanItemParameter(j, "min");
      max = scanProblem->getScanItemParameter(j, "max");
      incr = scanProblem->getScanItemParameter(j, "incr");

      // switch the grid type and set values accordingly
      switch ((int)scanProblem->getScanItemParameter(j, "gridType"))
        {
        case SD_REGULAR:
          // log scale
          if (scanProblem->getScanItemParameter(j, "log") == 1.0)
            scanProblem->setScanItemParameter(j, "value", (min*pow(10, incr*i)));
          // non-log scale
          else
            scanProblem->setScanItemParameter(j, "value", (min + incr*i));
          break;
        }
    }
}
