/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanMethod.cpp,v $
   $Revision: 1.26 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/22 16:12:40 $
   End CVS Header */

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
#include "randomGenerator/CRandom.h" 
//#include "utilities/CWriteConfig.h"
#include "CScanProblem.h"
#include "CScanMethod.h"

// this will have to be defined somewhere else with the
// values of other distribution types
#define SD_UNIFORM 0
#define SD_GAUSS 1
#define SD_BOLTZ 2
#define SD_REGULAR 3

CScanMethod * CScanMethod::createMethod() {return new CScanMethod;}

CScanMethod::CScanMethod():
    CCopasiMethod(CCopasiTask::scan, CCopasiMethod::unset),
    scanProblem(NULL),
    mpRandomGenerator(NULL),
    mVariableSize(0),
    mpVariables(NULL)
{
  addParameter("Random Number Generator", CCopasiParameter::STRING,
               CRandom::TypeName[1]);
  addParameter("Random Number Seed", CCopasiParameter::INT, (C_INT32) 0);
}

CScanMethod::CScanMethod(const CScanMethod & src,
                         const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    scanProblem(NULL),
    mpRandomGenerator(NULL),
    mVariableSize(0),
    mpVariables(NULL)
{}

CScanMethod::~CScanMethod(){}

void CScanMethod::scan(unsigned C_INT32 s,
                       bool C_UNUSED(nl),
                       void (*pCallback)(CReport *),
                       CReport *pReport)
{
  mVariableSize = scanProblem->getVariableSize();
  mpVariables = scanProblem->getCalculateVariables();

  mpRandomGenerator =
    CRandom::createGenerator(CRandom::TypeNameToEnum(* (std::string *) getValue("Random Number Generator")),
                             * (C_INT32 *) getValue("Random Number Seed"));

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
  if (s < mVariableSize - 1)
    {
      for (i = s + 1; i < mVariableSize; i++)
        if (scanProblem->getScanItemParameter(i, "indp")) break;
      top = i;
    }
  else
    top = mVariableSize;

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
      setScanParameterValue(0, s, top);
      //different from SD_REGULR by initial value
      for (i = 0; i < * (unsigned C_INT32 *) scanProblem->getScanItemParameter(s, "density"); i++)
        {
          if (s != 0) scan(next, false, pCallback, pReport);
          else
            // some function
            {
              scanProblem->calculate();
              pCallback(pReport);
            }
          setScanParameterValue(i, s, top);
        }
      break;
    case SD_REGULAR:
      //start with min value - give 0 as first param in setscanparametervalue
      setScanParameterValue(0, s, top);

      for (i = 1; i <= * (unsigned C_INT32 *) scanProblem->getScanItemParameter(s, "density"); i++)
        {
          if (s != 0)
            scan(next, false, pCallback, pReport);
          else
            // some function
            {
              scanProblem->calculate();
              pCallback(pReport);
            }
          setScanParameterValue(i, s, top);
        }
      break;
    }

  pdelete(mpRandomGenerator);
} // scan() ends

void CScanMethod::setProblem(CScanProblem * problem)
{scanProblem = problem;}

void CScanMethod::setScanParameterValue(unsigned C_INT32 i,
                                        unsigned C_INT32 first,
                                        unsigned C_INT32 last)
{
  unsigned C_INT32 j;
  double min, max, incr, ampl;
  for (j = first; j < last; j++)
    {
      // making a copy of the min and max parameters of the scanItem j
      min = * (C_FLOAT64 *) scanProblem->getScanItemParameter(j, "min");
      max = * (C_FLOAT64 *) scanProblem->getScanItemParameter(j, "max");
      ampl = * (C_FLOAT64 *) scanProblem->getScanItemParameter(j, "ampl");
      incr = * (C_FLOAT64 *) scanProblem->getScanItemParameter(j, "incr");

      // switch the grid type and set values accordingly
      switch ((int)scanProblem->getScanItemParameter(j, "gridType"))
        {
        case SD_UNIFORM:
          if (scanProblem->getScanItemParameter(j, "log"))
            mpVariables[j] =
              min * pow(10, ampl * mpRandomGenerator->getRandomCO());
          else
            mpVariables[j] =
              min + ampl * mpRandomGenerator->getRandomCO();
          break;

        case SD_GAUSS:
          if (scanProblem->getScanItemParameter(j, "log"))
            mpVariables[j] = mpRandomGenerator->getRandomNormalLog(min, max);
          else
            mpVariables[j] = mpRandomGenerator->getRandomNormal(min, max);
          break;

        case SD_BOLTZ:
          if (scanProblem->getScanItemParameter(j, "log"))
            mpVariables[j] = mpRandomGenerator->getRandomNormalLog(min, max);
          else
            mpVariables[j] =
              mpRandomGenerator->getRandomNormalPositive(min, max);
          break;

        case SD_REGULAR:
          // log scale
          if (scanProblem->getScanItemParameter(j, "log"))
            mpVariables[j] = min * pow(10, incr * i);
          // non-log scale
          else
            mpVariables[j] = (min + incr * i);
          break;
        }
    }
}
