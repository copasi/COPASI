#include "copasi.h"
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
