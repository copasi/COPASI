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
#define SD_UNIFORM 0
#define SD_GAUSS 1
#define SD_BOLTZ 2
#define SD_REGULAR 3

CScanMethod * CScanMethod::createMethod() {return new CScanMethod;}

CScanMethod::CScanMethod()
{}

CScanMethod::CScanMethod(const CScanMethod & src)
{}

CScanMethod::~CScanMethod(){}

void CScanMethod::scan(unsigned C_INT32 s, bool C_UNUSED(nl))
{
  unsigned C_INT32 scanDimension = scanProblem->getListSize();
  unsigned C_INT32 i, next, top;
  //1.  find the first/last master scan item

  if (s > 0)
    {
      for (i = s - 1; i > 0; i--)
        //if(scanItem[i]->Indp) break;
        if (scanProblem->getScanItemParameter(i, "indp")) break;

      next = i;
    }

  else
    next = 0;

  /* 2.  find the last slave item */

  //if(s<scandimension-1)
  if (s < scanDimension - 1)
    {
      for (i = s + 1; i < scanDimension; i++)
        if (scanProblem->getScanItemParameter(i, "indp")) break;
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
  switch ((int)scanProblem->getScanItemParameter(s, "gridType"))
    {
    case SD_UNIFORM:
    case SD_GAUSS:
    case SD_BOLTZ:
      // start with the min values
      scanProblem->setScanParameterValue(0, s, top);
      //different from SD_REGULR by initial value
      for (i = 0; i < scanProblem->getScanItemParameter(s, "density"); i++)
        {
          if (s != 0) scan(next, false);
          else
            // some function
            simulate();
          scanProblem->setScanParameterValue(i, s, top);
        }
      break;
    case SD_REGULAR:
      //start with min value - give 0 as first param in setscanparametervalue
      scanProblem->setScanParameterValue(0, s, top);

      for (i = 1; i <= scanProblem->getScanItemParameter(s, "density"); i++)
        {
          if (s != 0)
            scan(next, false);
          else
            // some function
            simulate();
          scanProblem->setScanParameterValue(i, s, top);
        }
      break;
    }
} // scan() ends

C_FLOAT64 CScanMethod::simulate()
{
  scanProblem->calculate();
  return 0;
}

/**
  *  Set a pointer to the problem.
  *  This method is used by CTrajectory
  *  @param "CTrajectoryProblem *" problem
  */
void CScanMethod::setProblem(CScanProblem * problem)
{scanProblem = problem;}
