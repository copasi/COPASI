#include "copasi.h"

#include "CStochDirectMethod.h"

CStochDirectMethod::CStochDirectMethod()
    : CStochMethod()
{}

C_FLOAT64 CStochDirectMethod::doSingleStep(C_FLOAT64 initial_time)
{
  //updatePropensities();
  C_INT32 rxn = generateReactionIndex();
  C_FLOAT64 step_time = generateReactionTime();
  updateSystemState(rxn);
  return initial_time + step_time;
}
