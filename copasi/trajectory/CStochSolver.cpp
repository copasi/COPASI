#include <math.h>

#include "copasi.h"
#include "CStochSolver.h"
#include "model/model.h"

CStochSolver::CStochSolver()
    : mMethod(0),
      mMaxTime(0),
      mMaxSteps(0)
{
}

#ifdef XXXX
CStochSolver::CStochSolver(std::string method_name, CModel *model, C_FLOAT64 maxtime, C_INT32 maxsteps)
{
    (void) Initialize(method_name, model, maxtime, maxsteps);
}
#endif // XXXX

void CStochSolver::Initialize(std::string method_name, CModel *model, C_FLOAT64 maxtime, C_INT32 maxsteps)
{
    CStochSolver::Type method;
    if (method_name == "DIRECT" || method_name == "direct" || method_name == "Direct")
    {
        // Only have one type implemented so far
        mMethodType = CStochSolver::DIRECT;
        mMethod = new CStochDirectMethod(model);
    }
    else if (method_name == "NEXTREACTION" || method_name == "nextreaction" || method_name == "NextReaction")
    {
        mMethodType = CStochSolver::NEXTREACTION;
        // must still implement this
        // mMethod = new CStochNextReactionMethod(model);
    }
    mMethod->InitMethod();
    mMaxTime = maxtime;
    mMaxSteps = maxsteps;
}

CStochMethod *CStochSolver::GetStochMethod()
{
    return mMethod;
}

CStochMethod::CStochMethod(CModel *model)
    : mModel(model),
      mFail(0)
{}

C_INT32 CStochMethod::UpdatePropensities()
{
    mA0 = 0;
    for (C_INT32 i = 0; i < mModel->getReactions().size(); i++)
    {
        CalculateAmu(i);
        mA0 += mAmu[i];
    }
    return 0;
}

C_INT32 CStochMethod::CalculateAmu(C_INT32 index)
{
    // We need the product of the cmu and hmu for this step. We
    // calculate this in one go, as there are fewer steps to perform.
    C_FLOAT32 amu = 1; // initially
    C_INT32 total_substrates = 0;
    C_INT32 num_ident = 0;
    C_INT32 number = 0;
    C_INT32 lower_bound;
    // First, find the step (reaction) associated with this index.
    // Keep a pointer to this.
    CReaction *step = &mModel->getReactions()[index];
    // Iterate through each reactant type in the step 
    std::vector<CStepMetab>::iterator it;
    for (it = step->substrates().begin(); it < step->substrates().end(); it++)
    {
        num_ident = it.GetNumIdent(); // XXX To do: NumberIdentical()
        total_substrates += num_ident;
        number = it.GetMetab()->getNumber(); // XXX To do: Number()
        lower_bound = number - num_ident;
        while (number > lower_bound)
        {
            amu *= number;
            number--;
        }
    }
    amu /= pow(volume, total_substrates-1); // XXX To do: get volume
    amu *= rate_with_factor; // XXX To do: rate (including factor from dynamics)
    mAmu[index] = amu;
}
    
CStochDirectMethod::CStochDirectMethod(CModel *model)
    : CStochMethod(model)
{
}

C_INT32 CStochDirectMethod::InitMethod()
{
    // Populate the vector of propensities
    for (C_INT32 i = 0; i < mModel->getSteps()->size(); i++)
    {
        mAmu.push_back(0);
    }
    return 0;
}

C_FLOAT64 CStochDirectMethod::DoStep(C_FLOAT64 initial_time)
{
    UpdatePropensities();
    C_INT32 rxn = GetReaction();
    C_FLOAT64 step_time = GetTime();
    UpdateSystemState(rxn);
    return initial_time + step_time;
    
}

C_INT32 CStochDirectMethod::GetReaction()
{
    C_FLOAT32 rand1 = GetUniformRandom(); // XXX To do: implement random number generation
    C_FLOAT64 sum;
    C_INT32 index = 0;
    while (index < mModel->getSteps()->size())
    {
        sum += mAmu[index] / mA0;
        if (rand1 <= sum)
        {
            return index;
        }
    }
    index++;
    // shouldn't get here
    return mFail;
}

C_FLOAT64 CStochDirectMethod::GetTime()
{
    C_FLOAT32 rand2 = GetUniformRandom(); // XXX To do: implement random number generation
    return -1 * log(rand2 / mA0);
}

C_INT32 CStochDirectMethod::UpdateSystemState(C_INT32 rxn)
{
    // Change the particle numbers according to which step took place
    CStep *step = &(*mModel->getSteps())[rxn];
    std::vector<CStep::CId2Metab>::iterator it;
    // Update the substrate numbers
    for (it = step.substrates()->begin(); it < step->substrates()->end(); it++)
    {
        it.mpMetabolite->IncrementNumber(it.NumberChange()); // XXX To do: Implement IncrementNumber(C_INT32 nc)
    }
    // Update the product numbers (if the metabolite isn't also a substrate; if it is, do nothing)

    for (it = step->products().begin(); it < step->products().end(); it++)
    {
        if (!it.IsSubstrate()) // XXX To do: Implement IsSubstrate
        {
            it.mpMetabolite->IncrementNumber(it.NumberChange()); // XXX To do: Implement IncrementNumber(C_INT32 nc)
        }
    }
    return 0;
}
