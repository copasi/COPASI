/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CStochDirectMethod.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:03 $
   End CVS Header */

#include "copasi.h"
#include "CStochDirectMethod.h"
#include "CTrajectoryMethod.h"
#include "model/CCompartment.h"

CStochDirectMethod::CStochDirectMethod()
    : CStochMethod()
{}

C_FLOAT64 CStochDirectMethod::doSingleStep(C_FLOAT64 initial_time, C_FLOAT64 end_time)
{
  //updatePropensities();
  C_FLOAT64 step_time = generateReactionTime();
  if ((step_time + initial_time) >= end_time)
    {
      return end_time;
    }
  else
    {
      C_INT32 rxn = generateReactionIndex();
      updateSystemState(rxn);
      return initial_time + step_time;
    }
}
