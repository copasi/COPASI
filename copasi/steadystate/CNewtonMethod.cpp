// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <algorithm>
#include <cmath>

#include "copasi/copasi.h"

#include "CSteadyStateMethod.h"
#include "CSteadyStateProblem.h"
#include "CSteadyStateTask.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
//#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/utility.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CLeastSquareSolution.h"

// static
const CEnumAnnotation< std::string, CNewtonMethod::eTargetCriterion > CNewtonMethod::TargetCriterion(
{
  "Distance and Rate",
  "Distance",
  "Rate"});

CNewtonMethod::CNewtonMethod(const CDataContainer * pParent,
                             const CTaskEnum::Method & methodType,
                             const CTaskEnum::Task & taskType)
  : CSteadyStateMethod(pParent, methodType, taskType)
  , mUseNewton(true)
  , mUseIntegration(true)
  , mUseBackIntegration(false)
  , mAcceptNegative(false)
  , mForceNewton(true)
  , mKeepProtocol(true)
  , mIterationLimit(50)
  , mMaxDurationForward(1e9)
  , mMaxDurationBackward(1e6)
  , mDimension(0)
  , mpX(NULL)
  , mH()
  , mXold()
  , mdxdt()
  , mpTrajectory(NULL)
  , mStartState()
  , mUpdateConcentrations()
  , mTargetCriterion(eTargetCriterion::DistanceAndRate)
  , mTargetRate(std::numeric_limits< C_FLOAT64 >::infinity())
  , mTargetDistance(std::numeric_limits< C_FLOAT64 >::infinity())

{
  initializeParameter();
}

CNewtonMethod::CNewtonMethod(const CNewtonMethod & src,
                             const CDataContainer * pParent)
  : CSteadyStateMethod(src, pParent)
  , mUseNewton(src.mUseNewton)
  , mUseIntegration(src.mUseIntegration)
  , mUseBackIntegration(src.mUseBackIntegration)
  , mAcceptNegative(src.mAcceptNegative)
  , mForceNewton(src.mForceNewton)
  , mKeepProtocol(src.mKeepProtocol)
  , mIterationLimit(src.mIterationLimit)
  , mMaxDurationForward(src.mMaxDurationForward)
  , mMaxDurationBackward(src.mMaxDurationBackward)
  , mDimension(src.mDimension)
  , mpX(NULL)
  , mH(src.mH)
  , mXold(src.mXold)
  , mdxdt()
  , mpTrajectory(NULL)
  , mStartState(src.mStartState)
  , mUpdateConcentrations(src.mUpdateConcentrations)
  , mTargetCriterion(src.mTargetCriterion)
  , mTargetRate(src.mTargetRate)
  , mTargetDistance(src.mTargetDistance)

{
  initializeParameter();
}

CNewtonMethod::~CNewtonMethod()
{
  cleanup();
}

void CNewtonMethod::initializeParameter()
{
  CCopasiParameter * pParm;

  assertParameter("Use Newton", CCopasiParameter::Type::BOOL, true);
  assertParameter("Use Integration", CCopasiParameter::Type::BOOL, true);
  assertParameter("Use Back Integration", CCopasiParameter::Type::BOOL, false);
  assertParameter("Accept Negative Concentrations", CCopasiParameter::Type::BOOL, false);
  assertParameter("Iteration Limit", CCopasiParameter::Type::UINT, (unsigned C_INT32) 50);
  assertParameter("Maximum duration for forward integration", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1e9);
  assertParameter("Maximum duration for backward integration", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1e6);
  //assertParameter("Force additional Newton step", CCopasiParameter::Type::BOOL, true);
  //assertParameter("Keep Protocol", CCopasiParameter::Type::BOOL, true);

  assertParameter("Target Criterion", CCopasiParameter::Type::STRING, TargetCriterion[0]);
  pParm = getParameter("Target Criterion");

  if (pParm != NULL)
    pParm->setValidValues(TargetCriterion);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("Newton.UseNewton")) != NULL)
    {
      setValue("Use Newton", pParm->getValue< bool >());
      removeParameter("Newton.UseNewton");

      if ((pParm = getParameter("Newton.UseIntegration")) != NULL)
        {
          setValue("Use Integration", pParm->getValue< bool >());
          removeParameter("Newton.UseIntegration");
        }

      if ((pParm = getParameter("Newton.UseBackIntegration")) != NULL)
        {
          setValue("Use Back Integration", pParm->getValue< bool >());
          removeParameter("Newton.UseBackIntegration");
        }

      if ((pParm = getParameter("Newton.acceptNegativeConcentrations")) != NULL)
        {
          setValue("Accept Negative Concentrations", pParm->getValue< bool >());
          removeParameter("Newton.acceptNegativeConcentrations");
        }

      if ((pParm = getParameter("Newton.IterationLimit")) != NULL)
        {
          setValue("Iteration Limit", pParm->getValue< unsigned C_INT32 >());
          removeParameter("Newton.IterationLimit");
        }

      removeParameter("Newton.LSODA.RelativeTolerance");
      removeParameter("Newton.LSODA.AbsoluteTolerance");
      removeParameter("Newton.LSODA.AdamsMaxOrder");
      removeParameter("Newton.LSODA.BDFMaxOrder");
      removeParameter("Newton.LSODA.MaxStepsInternal");
    }
}

bool CNewtonMethod::elevateChildren()
{
  CSteadyStateMethod::initializeParameter();
  initializeParameter();
  return true;
}

void CNewtonMethod::cleanup()
{
  pdelete(mpTrajectory);
}

void CNewtonMethod::load(CReadConfig & configBuffer,
                         CReadConfig::Mode C_UNUSED(mode))
{
  if (configBuffer.getVersion() < "4.0")
    {
      C_FLOAT64 Dbl;
      C_INT32 Int;
      bool Bool;

      configBuffer.getVariable("SSStrategy", "C_INT32", &Int, CReadConfig::LOOP);

      switch (Int)
        {
          case 0:
            setValue("Use Newton", true);
            setValue("Use Integration", true);
            setValue("Use Back Integration", false);
            break;

          case 1:
            setValue("Use Newton", false);
            setValue("Use Integration", true);
            setValue("Use Back Integration", false);
            break;

          case 2:
            setValue("Use Newton", true);
            setValue("Use Integration", false);
            setValue("Use Back Integration", false);
            break;

          case 3:
            setValue("Use Newton", false);
            setValue("Use Integration", false);
            setValue("Use Back Integration", true);
            break;

          default:
            fatalError();
            break;
        }

      configBuffer.getVariable("SSBackIntegration", "bool", &Bool);
      setValue("Use Back Integration", Bool);

      configBuffer.getVariable("NewtonLimit", "C_INT32", &Int,
                               CReadConfig::SEARCH);
      setValue("Iteration Limit", Int);

      configBuffer.getVariable("SSResoltion", "C_FLOAT64", &Dbl); //typo is necessary!!
      //setValue("Steady State Resolution", Dbl);
      //setValue("Derivation Resolution", Dbl);
      //setValue("Stability Resolution", Dbl);
      setValue("Resolution", Dbl);
    }
}

//**********************************************************************************

CNewtonMethod::NewtonResultCode CNewtonMethod::doIntegration(bool forward)
{
  C_FLOAT64 iterationFactor = forward ? 10.0 : 2.0;
  C_FLOAT64 maxDuration = forward ? mMaxDurationForward : -mMaxDurationBackward;
  //minimum duration is either hardcoded or equal to maximum duration, whichever is smaller.
  C_FLOAT64 minDuration = forward ? (mMaxDurationForward < 1e-1 ? mMaxDurationForward : 1e-1)
                          : -(mMaxDurationBackward < 1e-2 ? mMaxDurationBackward : 1e-2);

  //progress bar
  size_t hProcess;
  unsigned C_INT32 Step = 0;
  unsigned C_INT32 MaxSteps;
  MaxSteps = (unsigned C_INT32) ceil(log(maxDuration / minDuration) / log(iterationFactor));

  std::string tmpstring = forward ? "forward integrating..." : "backward integrating...";

  if (mProcessReport)
    hProcess = mProcessReport.addItem(tmpstring,
                                      Step,
                                      &MaxSteps);

  //setup trajectory
  CTrajectoryProblem * pTrajectoryProblem = NULL;

  if (mpTrajectory)
    {
      mpTrajectory->setCallBack(mProcessReport);

      pTrajectoryProblem =
        dynamic_cast< CTrajectoryProblem * >(mpTrajectory->getProblem());
      assert(pTrajectoryProblem);
      pTrajectoryProblem->setStepNumber(1);
    }

  bool stepLimitReached = false;
  C_FLOAT64 duration;

  for (duration = minDuration; fabs(duration) <= fabs(maxDuration); duration *= iterationFactor, Step++)
    {
      if (mProcessReport && !mProcessReport.progressItem(hProcess))
        break;

      pTrajectoryProblem->setDuration(duration);

      try
        {
          // We must not use useInitialValues = true here as this will interfere with scan continuation.
          mpContainer->setState(mStartState);
          stepLimitReached = !mpTrajectory->process(false); //single step
        }

      catch (CCopasiException & /*Exception*/)
        {
          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration << " failed (Exception).\n\n";

          break;
        }

      if (containsNaN())
        {
          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration << " failed (NaN).\n\n";

          break;
        }

      if (!(mAcceptNegative || allPositive()))
        {
          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration
                       << " resulted in negative concentrations.\n\n";

          break;
        }

      calculateDerivativesX();
      C_FLOAT64 value = targetFunction();

      if (isSteadyState(value))
        {
          if (mProcessReport)
            mProcessReport.finishItem(hProcess);

          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration
                       << ". Criterion matched by " << targetValueToString() << ".\n\n";

          return CNewtonMethod::found;
        }
      else
        {
          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration
                       << ". Criterion not matched by " << targetValueToString() << ".\n\n";
        }

      if (mUseNewton)
        {
          if (mKeepProtocol)
            mMethodLog << "  Try Newton's method from this starting point. \n";

          NewtonResultCode returnCode = processNewton();

          if (mKeepProtocol)
            mMethodLog << "\n";

          // mpParentTask->separate(COutputInterface::DURING);

          if (returnCode == CNewtonMethod::found)
            {
              if (mProcessReport)
                mProcessReport.finishItem(hProcess);

              return CNewtonMethod::found;
            }
        }

      if (stepLimitReached)
        {
          if (mKeepProtocol)
            mMethodLog << "  Integration with duration " << duration
                       << " reached internal step limit.\n";

          break;
        }
    }

  if (mProcessReport)
    mProcessReport.finishItem(hProcess);

  return CNewtonMethod::notFound;
}

//**********************************************************************************

CSteadyStateMethod::ReturnCode CNewtonMethod::processInternal()
{
  //clear log
  mMethodLog.str("");

  if (mProcessReport)
    mProcessReport.setName("performing steady state calculation...");

  mStartState = mContainerState;

  NewtonResultCode returnCode;

  // Newton
  if (mUseNewton)
    {
      if (mKeepProtocol)
        mMethodLog << "Try Newton's method. \n";

      returnCode = processNewton();

      if (returnCode == CNewtonMethod::found)
        return returnProcess(true);
    }

  // forward integration
  if (mUseIntegration)
    {
      if (mKeepProtocol)
        mMethodLog << "\nTry forward integration. \n";

      returnCode = doIntegration(true); //true means forward

      if (returnCode == CNewtonMethod::found)
        return returnProcess(true);
    }

  // backward integration
  if (mUseBackIntegration)
    {
      if (mKeepProtocol)
        mMethodLog << "\nTry backward integration. \n";

      returnCode = doIntegration(false); //false means backwards

      if (returnCode == CNewtonMethod::found)
        return returnProcess(true);
    }

  return returnProcess(false);
}

//**************************************************************

CNewtonMethod::NewtonResultCode CNewtonMethod::doNewtonStep(C_FLOAT64 & currentValue)
{
  memcpy(mXold.array(), mpX, mDimension * sizeof(C_FLOAT64));

  // DebugFile << "Iteration: " << k << std::endl;

  calculateJacobian(currentValue, true);

  if (CLeastSquareSolution::solve(*mpJacobian, mdxdt, mH) != mpJacobian->numCols())
    {
      // We need to check that mH != 0
      C_FLOAT64 * pH = mH.array();
      C_FLOAT64 * pHEnd = pH + mH.size();

      for (; pH != pHEnd; ++pH)
        {
          if (fabs(*pH) > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            break;
        }

      if (pH == pHEnd)
        {
          if (mKeepProtocol)
            mMethodLog << "    Newton step failed. Jacobian could not be inverted.\n\n";

          return CNewtonMethod::singularJacobian;
        }
    }

  // Force the loop to be enterred at least once
  C_FLOAT64 newValue = currentValue * 1.001;

  //repeat till the new max rate is smaller than the old.
  //max 32 times
  size_t i;

  for (i = 0; (i < 32) && !(newValue < currentValue); i++)
    {
      C_FLOAT64 * pXit = mpX;
      C_FLOAT64 * pXoldIt = mXold.array();
      C_FLOAT64 * pHit = mH.array();
      C_FLOAT64 * pEnd = pHit + mDimension;

      for (; pHit != pEnd; ++pHit, ++pXit, ++pXoldIt)
        {
          *pXit = *pXoldIt - *pHit;
          (*pHit) *= 0.5;
        }

      calculateDerivativesX();
      newValue = targetFunction();

      // mpParentTask->output(COutputInterface::DURING);
    }

  if (i == 32)
    {
      //discard the step
      memcpy(mpX, mXold.array(), mDimension * sizeof(C_FLOAT64));

      calculateDerivativesX();
      currentValue = targetFunction();

      if (mKeepProtocol)
        mMethodLog << "    Newton step failed. Damping limit exceeded.\n";

      return CNewtonMethod::dampingLimitExceeded;

      //       if (isSteadyState(oldMaxRate) && (mAcceptNegative || allPositive()))
      //         ReturnCode = CNewtonMethod::found;
      //       else if (oldMaxRate < *mpSSResolution)
      //         ReturnCode = CNewtonMethod::notFound;
      //       else
      //         ReturnCode = CNewtonMethod::dampingLimitExceeded;

      //if (mProcessReport) mProcessReport.finish(hProcess);
    }

  if (!(mAcceptNegative || allPositive()))
    {
      if (mKeepProtocol)
        mMethodLog << "    Newton step failed. Negative volume or concentration found.\n\n";

      return CNewtonMethod::negativeValueFound;
    }

  currentValue = newValue; //return the new target value

  if (mKeepProtocol)
    {
      if (i <= 1)
        mMethodLog << "    Regular Newton step.      New value: " << targetValueToString() << "\n";
      else
        mMethodLog << "    Newton step with damping. New value: " << targetValueToString()
                   << " (" << i - 1 << " damping iteration(s))\n";
    }

  return CNewtonMethod::stepSuccesful;
}

//************************************************************

CNewtonMethod::NewtonResultCode CNewtonMethod::processNewton()
{
  NewtonResultCode result = CNewtonMethod::notFound;
  unsigned C_INT32 k;

  k = 0;
  //start progress bar
  size_t hProcess;

  if (mProcessReport)
    hProcess = mProcessReport.addItem("Newton method...",
                                      k,
                                      &mIterationLimit);

  calculateDerivativesX();
  C_FLOAT64 targetValue = targetFunction();

  {
    if (mKeepProtocol)
      mMethodLog << "   Starting Newton Iterations...\n";

    for (k = 0; k < mIterationLimit && !isSteadyState(targetValue); k++)
      {
        if (mProcessReport && !mProcessReport.progressItem(hProcess))
          break;

        result = doNewtonStep(targetValue);

        if (singularJacobian == result)
          break;

        if (dampingLimitExceeded == result)
          break;

        if (negativeValueFound == result)
          break;
      }
  }

  //check if ss was found. If not make sure the correct return value is set
  if (isSteadyState(targetValue))
    result = CNewtonMethod::found;
  else if (CNewtonMethod::stepSuccesful == result)
    result = CNewtonMethod::iterationLimitExceeded;

  //log
  if (mKeepProtocol)
    {
      if (CNewtonMethod::found == result)
        mMethodLog << "   Success: Target criterion matched by " << targetValueToString() << ".\n";
      else if (CNewtonMethod::dampingLimitExceeded == result)
        mMethodLog << "   Failed: Target criterion not matched after reaching iteration limit. " << targetValueToString() << "\n";
    }

  //do an additional Newton step to refine the result
  if ((CNewtonMethod::found == result) && mForceNewton && targetValue > 0.0)
    {
      bool tmp = true;

      ++k;

      if (mProcessReport && !mProcessReport.progressItem(hProcess))
        tmp = false;

      if (tmp)
        {
          if (mKeepProtocol)
            mMethodLog << "   Do additional step to refine result...\n";

          result = doNewtonStep(targetValue);

          if (CNewtonMethod::stepSuccesful == result)
            result = CNewtonMethod::found;

          if (CNewtonMethod::singularJacobian == result)
            {
              if (mKeepProtocol)
                mMethodLog << "   Additional step failed. Old values restored.\n";

              result = CNewtonMethod::found;
            }

          if (CNewtonMethod::dampingLimitExceeded == result)
            {
              if (mKeepProtocol)
                mMethodLog << "   Additional step failed. Old values restored.\n";

              result = CNewtonMethod::found;
            }

          if (CNewtonMethod::negativeValueFound == result)
            {
              if (mKeepProtocol)
                mMethodLog << "   Additional step failed. Old values restored.\n";

              result = CNewtonMethod::found;
            }
        }
    }

  //end progress bar
  if (mProcessReport)
    mProcessReport.finishItem(hProcess);

  return result;
}

void CNewtonMethod::calculateDerivativesX()
{
  mpContainer->updateSimulatedValues(true);
}

bool CNewtonMethod::containsNaN() const
{
  return !mpContainer->isStateValid();
}

bool CNewtonMethod::isSteadyState(const C_FLOAT64 & value) const
{
  if (value > *mpSSResolution)
    return false;

  if (containsNaN())
    return false;

  return true;
}

C_FLOAT64 CNewtonMethod::targetFunction()
{
  if (mTargetCriterion != eTargetCriterion::Rate)
    {
      calculateJacobian(std::max(mTargetRate, mTargetDistance), true);
    }

  // Assure that all values are updated.
  mpContainer->updateSimulatedValues(true);
  mpContainer->applyUpdateSequence(mUpdateConcentrations);

  mTargetRate = targetFunctionRate();
  mTargetDistance = targetFunctionDistance();

  return std::max(mTargetRate, mTargetDistance);
}

std::string CNewtonMethod::targetValueToString() const
{
  std::ostringstream os;

  switch (mTargetCriterion)
    {
      case eTargetCriterion::DistanceAndRate:
        os << "Distance: " << mTargetDistance << ", Rate: " << mTargetRate;
        break;

      case eTargetCriterion::Distance:
        os << "Distance: " << mTargetDistance;
        break;

      case eTargetCriterion::Rate:
        os << "Rate: " << mTargetRate;
        break;
    }

  return os.str();
}

C_FLOAT64 CNewtonMethod::targetFunctionRate()
{
  if (mTargetCriterion == eTargetCriterion::Distance)
    return 0.0;

  // Assure that all values are updated.

  C_FLOAT64 MaxRate = 0.0;
  C_FLOAT64 tmp;

  // We look at all ODE determined entity and dependent species rates.
  const C_FLOAT64 * pIt = mdxdt.begin();
  const C_FLOAT64 * pEnd = mdxdt.end();
  C_FLOAT64 * pCurrentState = mpX;
  const C_FLOAT64 * pAtol = mAtol.array();
  C_FLOAT64 ** ppCompartmentVolume = mCompartmentVolumes.array();

  for (; pIt != pEnd; ++pIt, ++pCurrentState, ++pAtol, ++ppCompartmentVolume)
    {
      tmp = fabs(*pIt) / std::max(fabs(*pCurrentState), *pAtol);

      if (std::isnan(tmp))
        return std::numeric_limits< C_FLOAT64 >::infinity();

      if (tmp > MaxRate)
        MaxRate = tmp;

      tmp = fabs(*pIt);

      if (*ppCompartmentVolume != NULL)
        {
          tmp /= mpContainer->getQuantity2NumberFactor() * **ppCompartmentVolume;
        }

      if (std::isnan(tmp))
        return std::numeric_limits< C_FLOAT64 >::infinity();

      if (tmp > MaxRate)
        MaxRate = tmp;
    }

  return MaxRate;
}

C_FLOAT64 CNewtonMethod::targetFunctionDistance()
{
  if (mTargetCriterion == eTargetCriterion::Rate
      || mdxdt.size() == 0)
    return 0.0;

  CVector< C_FLOAT64 > Distance;

  CMatrix< C_FLOAT64 > JacobianWithTime;
  mpContainer->calculateJacobian(JacobianWithTime, *mpDerivationFactor, true, !mpContainer->isAutonomous());

  CLeastSquareSolution::ResultInfo Info = CLeastSquareSolution::solve(JacobianWithTime, mdxdt, mAtol, mCompartmentVolumes, mpContainer->getQuantity2NumberFactor(), Distance);

  if (Info.rank == 0)
    {
      return std::numeric_limits< C_FLOAT64 >::infinity();
    }

  // We look at all ODE determined entity and dependent species rates.
  C_FLOAT64 * pDistance = Distance.begin();
  C_FLOAT64 * pDistanceEnd = Distance.end();
  C_FLOAT64 * pCurrentState = mpX;
  const C_FLOAT64 * pAtol = mAtol.array();
  C_FLOAT64 ** ppCompartmentVolume = mCompartmentVolumes.array();

  C_FLOAT64 AbsoluteDistance = 0.0;
  C_FLOAT64 RelativeDistance = 0.0;
  C_FLOAT64 tmp;

  // For non autonomous model the first value in the distance measures time and we must treat it differently.
  if (!mpContainer->isAutonomous())
    {
      C_FLOAT64 TargetRate = mTargetRate;

      if (mTargetCriterion == eTargetCriterion::Distance)
        {
          mTargetCriterion = eTargetCriterion::Rate;
          TargetRate = CNewtonMethod::targetFunctionRate();
          mTargetCriterion = eTargetCriterion::Distance;
        }

      AbsoluteDistance = RelativeDistance = *pDistance * *pDistance * TargetRate * TargetRate;
      ++pDistance;
    }

  for (; pDistance != pDistanceEnd; ++pDistance, ++pCurrentState, ++pAtol, ++ppCompartmentVolume)
    {
      // Prevent division by 0
      tmp = *pDistance / std::max(fabs(*pCurrentState), *pAtol);

      RelativeDistance += tmp * tmp;

      tmp = *pDistance;

      if (*ppCompartmentVolume != NULL)
        {
          tmp /= mpContainer->getQuantity2NumberFactor() * **ppCompartmentVolume;
        }

      AbsoluteDistance += tmp * tmp;
    }

  RelativeDistance =
    std::isnan(RelativeDistance) ? std::numeric_limits< C_FLOAT64 >::infinity() : sqrt(RelativeDistance + Info.relativeError * Info.relativeError);
  AbsoluteDistance =
    std::isnan(AbsoluteDistance) ? std::numeric_limits< C_FLOAT64 >::infinity() : sqrt(AbsoluteDistance + Info.absoluteError * Info.absoluteError);

  C_FLOAT64 TargetValue = std::max(RelativeDistance, AbsoluteDistance);

  return TargetValue;
}

//virtual
bool CNewtonMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CSteadyStateMethod::isValidProblem(pProblem))
    return false;

  if (!mpContainer->isAutonomous() && getValue< bool >("Use Newton"))
    CCopasiMessage(CCopasiMessage::WARNING, MCSteadyState + 1);

  //const CSteadyStateProblem * pP = dynamic_cast<const CSteadyStateProblem *>(pProblem);

  if (!((getValue< bool >("Use Newton"))
        || (getValue< bool >("Use Integration"))
        || (getValue< bool >("Use Back Integration"))))
    {
      //would do nothing
      CCopasiMessage(CCopasiMessage::ERROR, "At least one of the features \n   - UseNewton\n   - UseIntegration\n   - UseBackIntegration\nmust be activated.");
      return false;
    }

  if (getValue< C_FLOAT64 >("Maximum duration for forward integration") <= 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Maximum duration for forward integration needs to be positive.");
      return false;
    }

  if (getValue< C_FLOAT64 >("Maximum duration for backward integration") <= 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Maximum duration for backward integration needs to be positive.");
      return false;
    }

  return true;
}

bool CNewtonMethod::initialize(const CSteadyStateProblem * pProblem)
{
  if (!CSteadyStateMethod::initialize(pProblem))
    return false;

  CTrajectoryProblem * pTrajectoryProblem = NULL;
  CTrajectoryMethod * pTrajectoryMethod = NULL;

  cleanup();

  /* Configure Newton */
  mUseNewton = mUseIntegration = mUseBackIntegration = mAcceptNegative = mForceNewton = mKeepProtocol = false;

  if (getValue< bool >("Use Newton"))
    mUseNewton = true;

  if (getValue< bool >("Use Integration"))
    mUseIntegration = true;

  if (getValue< bool >("Use Back Integration"))
    mUseBackIntegration = true;

  if (getValue< bool >("Accept Negative Concentrations"))
    mAcceptNegative = true;

  mTargetCriterion = TargetCriterion.toEnum(getValue< std::string >("Target Criterion"), eTargetCriterion::DistanceAndRate);
  mTargetRate = std::numeric_limits< C_FLOAT64 >::infinity();
  mTargetDistance = std::numeric_limits< C_FLOAT64 >::infinity();

  mForceNewton = true;
  mKeepProtocol = true;

  mIterationLimit = getValue< unsigned C_INT32 >("Iteration Limit");

  mMaxDurationForward = getValue< C_FLOAT64 >("Maximum duration for forward integration");
  mMaxDurationBackward = getValue< C_FLOAT64 >("Maximum duration for backward integration");

  mpX = mContainerStateReduced.array() + mpContainer->getCountFixedEventTargets() + 1;
  mDimension = mContainerStateReduced.size() - mpContainer->getCountFixedEventTargets() - 1;

  mH.resize(mDimension);
  mXold.resize(mDimension);
  mdxdt.initialize(mDimension, mpContainer->getRate(false).array() + mpContainer->getCountFixedEventTargets() + 1);

  mCompartmentVolumes.resize(mDimension + mpContainer->getCountDependentSpecies());
  mCompartmentVolumes = NULL;

  if (mUseIntegration || mUseBackIntegration)
    {
      // create an appropriate trajectory task
      CDataModel * pDataModel = getObjectDataModel();
      assert(pDataModel != NULL);
      CTrajectoryTask * pSrc =
        dynamic_cast< CTrajectoryTask * >(&pDataModel->getTaskList()->operator[]("Time-Course"));

      if (pSrc)
        mpTrajectory = new CTrajectoryTask(*pSrc, this);
      else
        mpTrajectory = new CTrajectoryTask(this);

      pTrajectoryProblem =
        dynamic_cast< CTrajectoryProblem * >(mpTrajectory->getProblem());
      assert(pTrajectoryProblem);

      if (mpTrajectory->getMethod()->getSubType() != CTaskEnum::Method::deterministic)
        mpTrajectory->setMethodType(CTaskEnum::Method::deterministic);

      pTrajectoryMethod =
        dynamic_cast< CTrajectoryMethod * >(mpTrajectory->getMethod());
      assert(pTrajectoryMethod);

      pTrajectoryProblem->setStepNumber(1);
      pTrajectoryProblem->setStartInSteadyState(false);

      mpTrajectory->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
    }

  //
  CObjectInterface::ObjectSet Requested;
  CMathObject * pMathObject = mpContainer->getMathObject(mpX);
  CMathObject * pMathObjectEnd = pMathObject + mDimension;
  C_FLOAT64 ** ppCompartmentVolume = mCompartmentVolumes.array();

  for (; pMathObject != pMathObjectEnd; ++pMathObject, ++ppCompartmentVolume)
    {
      if (pMathObject->getEntityType() == CMath::EntityType::Species)
        {
          Requested.insert(pMathObject->getCorrespondingProperty());
          *ppCompartmentVolume = (C_FLOAT64 *) mpContainer->getCompartment(pMathObject)->getValuePointer();
        }
    }

  mpContainer->getTransientDependencies().getUpdateSequence(mUpdateConcentrations, CCore::SimulationContext::UseMoieties, mpContainer->getStateObjects(true), Requested, mpContainer->getSimulationUpToDateObjects());

  // Determine the compartment volumes for dependent species;
  pMathObjectEnd += mpContainer->getCountDependentSpecies();

  for (; pMathObject != pMathObjectEnd; ++pMathObject, ++ppCompartmentVolume)
    {
      if (pMathObject->getEntityType() == CMath::EntityType::Species)
        {
          *ppCompartmentVolume = (C_FLOAT64 *) mpContainer->getCompartment(pMathObject)->getValuePointer();
        }
    }

  return true;
}
