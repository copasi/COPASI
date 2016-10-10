// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CStochasticRungeKuttaRI5.h"

#include "copasi.h"

#include "CTrajectoryProblem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "math/CMathContainer.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "randomGenerator/CRandom.h"

// Uncomment this line below to get debug print out.
// #define DEBUG_OUTPUT 1

const C_FLOAT64 c01 = 0.0;
const C_FLOAT64 c02 = 1.0;
const C_FLOAT64 c03 = 5.0 / 12.0;

const C_FLOAT64 c11 = 0.0;
const C_FLOAT64 c12 = 1.0 / 4.0;
const C_FLOAT64 c13 = 1.0 / 4.0;

const C_FLOAT64 c21 = 0.0;
const C_FLOAT64 c22 = 0.0;
const C_FLOAT64 c23 = 0.0;

const C_FLOAT64 A021 = 1.0;
const C_FLOAT64 A031 = 25.0 / 144.0;
const C_FLOAT64 A032 = 35.0 / 144.0;

const C_FLOAT64 A121 = 1.0 / 4.0;
const C_FLOAT64 A131 = 1.0 / 4.0;
const C_FLOAT64 A132 = 0.0;

const C_FLOAT64 A221 = 0.0;
const C_FLOAT64 A231 = 0.0;
const C_FLOAT64 A232 = 0.0;

const C_FLOAT64 B021 = 1.0 / 3.0;
const C_FLOAT64 B031 = -5.0 / 6.0;
const C_FLOAT64 B032 = 0.0;

const C_FLOAT64 B121 = 1.0 / 2.0;
const C_FLOAT64 B131 = -1.0 / 2.0;
const C_FLOAT64 B132 = 0.0;

const C_FLOAT64 B221 = 1.0;
const C_FLOAT64 B231 = -1.0;
const C_FLOAT64 B232 = 0.0;

const C_FLOAT64 alpha1 = 1.0 / 10.0;
const C_FLOAT64 alpha2 = 3.0 / 14.0;
const C_FLOAT64 alpha3 = 24.0 / 35.0;

const C_FLOAT64 beta11 = 1.0;
const C_FLOAT64 beta12 = -1.0;
const C_FLOAT64 beta13 = -1.0;

const C_FLOAT64 beta21 = 0.0;
const C_FLOAT64 beta22 = 1.0;
const C_FLOAT64 beta23 = -1.0;

const C_FLOAT64 beta31 = 1.0 / 2.0;
const C_FLOAT64 beta32 = -1.0 / 4.0;
const C_FLOAT64 beta33 = -1.0 / 4.0;

const C_FLOAT64 beta41 = 0.0;
const C_FLOAT64 beta42 = 1.0 / 2.0;
const C_FLOAT64 beta43 = -1.0 / 2.0;

CStochasticRungeKuttaRI5::CStochasticRungeKuttaRI5(const CCopasiContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  CTrajectoryMethod(pParent, methodType, taskType),
  mContainerRates(),
  mContainerNoise(),
  mContainerRoots(),
  mpInternalStepSize(NULL),
  mpMaxInternalSteps(NULL),
  mpRandom(NULL),
  mRootFinder(),
  mpRootValueCalculator(NULL)
{
  mpRootValueCalculator = new CRootFinder::EvalTemplate< CStochasticRungeKuttaRI5 >(this, & CStochasticRungeKuttaRI5::evalRoot);
  initializeParameter();
}

CStochasticRungeKuttaRI5::CStochasticRungeKuttaRI5(const CStochasticRungeKuttaRI5 & src,
    const CCopasiContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mContainerRates(),
  mContainerNoise(),
  mContainerRoots(),
  mpInternalStepSize(NULL),
  mpMaxInternalSteps(NULL),
  mpRandom(NULL),
  mRootFinder(),
  mpRootValueCalculator(NULL)
{
  initializeParameter();
}

CStochasticRungeKuttaRI5::~CStochasticRungeKuttaRI5()
{}

void CStochasticRungeKuttaRI5::initializeParameter()
{
  mpInternalStepSize = assertParameter("Internal Steps Size", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
  mpMaxInternalSteps = assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) 100);
  mpForcePhysicalCorrectness = assertParameter("Force Physical Correctness", CCopasiParameter::BOOL, true);
  mpRootRelativeTolerance = assertParameter("Tolerance for Root Finder", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
}

bool CStochasticRungeKuttaRI5::elevateChildren()
{
  initializeParameter();
  return true;
}

// virtual
void CStochasticRungeKuttaRI5::stateChange(const CMath::StateChange & change)
{
  if (change & (CMath::ContinuousSimulation | CMath::State))
    {}
}

CTrajectoryMethod::Status CStochasticRungeKuttaRI5::step(const double & deltaT)
{
  Status Result = NORMAL;

  // Check whether we have a new target time
  if (mTargetTime != mTime + deltaT)
    {
      mTargetTime = mTime + deltaT;
      mInternalSteps = 0;
      mRootCounter = 0;
    }

  while (mTime < mTargetTime && Result == NORMAL)
    {
      Result = internalStep();

      mInternalSteps++;

      if (*mpInternalStepSize * mInternalSteps > *mpMaxInternalSteps * deltaT)
        {
          Result = FAILURE;
        }
    }

  return Result;
}

void CStochasticRungeKuttaRI5::start()
{
  mNumVariables = mContainerState.size() - mpContainer->getCountFixedEventTargets() - 1;
  mContainerVariables.initialize(mNumVariables, mContainerState.begin() + mpContainer->getCountFixedEventTargets() + 1);
  mContainerRates.initialize(mNumVariables, const_cast< C_FLOAT64 * >(mpContainer->getRate(false).begin()) + mpContainer->getCountFixedEventTargets() + 1);

  mContainerNoise.initialize(mpContainer->getNoise(false));
  assert(mContainerNoise.size() == mNumVariables);

  mNumNoise = mpContainer->getCountNoise();

  mContainerRoots.initialize(mpContainer->getRoots());
  mNumRoots = mContainerRoots.size();

  mH10.resize(mNumVariables);
  mSumAll1.resize(mNumVariables);
  mSumPartial1.resize(mNumNoise, mNumVariables);

  mH20.resize(mNumVariables);
  mH2k.resize(mNumNoise, mNumVariables);
  mHH2k.resize(mNumNoise, mNumVariables);
  mSumAll2.resize(mNumVariables);
  mSumPartial2.resize(mNumNoise, mNumVariables);

  mH30.resize(mNumVariables);
  mH3k.resize(mNumNoise, mNumVariables);
  mHH3k.resize(mNumNoise, mNumVariables);

  mA.resize(3, mNumVariables);
  mB.resize(3);
  mBB.resize(3);

  CMatrix< C_FLOAT64 > * pMatrix = mB.begin();
  CMatrix< C_FLOAT64 > * pMatrixEnd = pMatrix + 3;

  for (; pMatrix != pMatrixEnd; ++pMatrix)
    {
      pMatrix->resize(mNumNoise, mNumVariables);
    }

  pMatrix = mBB.begin();
  pMatrixEnd = pMatrix + 3;

  for (; pMatrix != pMatrixEnd; ++pMatrix)
    {
      pMatrix->resize(mNumNoise, mNumVariables);
    }

  mPhysicalValues.resize(mNumVariables);
  mNoiseInputValues.resize(mNumNoise);
  mNoiseUpdateSequences.resize(mNumNoise);

  // Noise output values are all values in mContainerNoise
  ObjectSet NoiseObjects;
  CMathObject * pObject = mpContainer->getMathObject(mContainerNoise.begin());
  CMathObject * pObjectEnd = pObject + mNumVariables;
  bool * pPhysicalValue = mPhysicalValues.begin();

  for (; pObject != pObjectEnd; ++pObject)
    {
      NoiseObjects.insert(pObject);

      *pPhysicalValue = (pObject->getEntityType() == CMath::Compartment ||
                         pObject->getEntityType() == CMath::Species);
    }

  // Noise input values are all math objects of ValueType = Noise and SimulationType = ODE or SimulationTypeUndefined
  pObject = mpContainer->getMathObject(mContainerNoise.begin());
  pObjectEnd = mpContainer->getMathObject(mpContainer->getValues().begin()) + mpContainer->getValues().size();
  C_FLOAT64 ** ppNoiseInput = mNoiseInputValues.begin();
  UpdateSequence * pUpdateSequence = mNoiseUpdateSequences.begin();

  for (; pObject != pObjectEnd && pObject->getValueType() == CMath::Noise; ++pObject)
    {
      if (pObject->getSimulationType() == CMath::ODE ||
          pObject->getSimulationType() == CMath::SimulationTypeUndefined)
        {
          *ppNoiseInput = (C_FLOAT64 *) pObject->getValuePointer();

          ObjectSet Objects;
          Objects.insert(pObject);

          mpContainer->getTransientDependencies().getUpdateSequence(*pUpdateSequence, CMath::Default, mpContainer->getStateObjects(false), Objects);
          UpdateSequence Sequence;
          mpContainer->getTransientDependencies().getUpdateSequence(Sequence, CMath::Default, Objects, NoiseObjects);
          pUpdateSequence->insert(pUpdateSequence->end(), Sequence.begin(), Sequence.end());

          // Advance pointer
          ++ppNoiseInput;
          ++pUpdateSequence;
        }
    }

  assert(ppNoiseInput == mNoiseInputValues.begin() + mNumNoise);

  mTime = *mpContainerStateTime;
  mTargetTime = mTime;
  mCurrentTime = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mH10 = mContainerVariables;

  mStepSize = *mpInternalStepSize;
  mSqrtStepSize = sqrt(mStepSize);

  mpRandom = &mpContainer->getRandomGenerator();
  mRootFinder.initialize(mpRootValueCalculator, *mpRootRelativeTolerance, mNumRoots + 1);
  mRoots.initialize(mRootFinder.getRootValues());
  mRootsFound.initialize(mRootFinder.getToggledRoots());
  mDiscreteRoots.initialize(mpContainer->getRootIsDiscrete());
}

void CStochasticRungeKuttaRI5::evalRate(C_FLOAT64 * pRates)
{
  mpContainer->updateSimulatedValues(false);
  memcpy(pRates, mContainerRates.begin(), mNumVariables * sizeof(C_FLOAT64));
}

void CStochasticRungeKuttaRI5::evalNoise(C_FLOAT64 * pNoise,
    const size_t & noiseDimension)
{
  C_FLOAT64 ** ppNoiseValue = mNoiseInputValues.begin();
  C_FLOAT64 ** ppNoiseValueEnd = mNoiseInputValues.end();

  for (; ppNoiseValue != ppNoiseValueEnd; ++ppNoiseValue)
    {
      **ppNoiseValue = 0.0;
    }

  mContainerNoise = 0.0;
  mpContainer->applyUpdateSequence(mNoiseUpdateSequences[noiseDimension]);

  memcpy(pNoise, mContainerNoise.begin(), mNumVariables * sizeof(C_FLOAT64));
}

void CStochasticRungeKuttaRI5::evalRoot(const double & time, CVectorCore< C_FLOAT64 > & rootValues)
{
  // Sanity Checks
  assert(rootValues.size() == mNumRoots + 1);

  calculateStateVariables(time);
  *mpContainerStateTime = time;

  mpContainer->updateSimulatedValues(false);

  rootValues[0] = calculateSmallestPhysicalValue();

  if (mNumRoots > 0)
    {
      memcpy(rootValues.begin() + 1, mContainerRoots.begin(), mNumRoots * sizeof(C_FLOAT64));
    }
}

void CStochasticRungeKuttaRI5::generateRandomNumbers()
{
  C_FLOAT64 * pRandom = mRandomIHat.begin();
  C_FLOAT64 * pRandomEnd = pRandom + mNumNoise;

  for (; pRandom != pRandomEnd; ++pRandom)
    *pRandom = randomIHat();

  pRandom = mRandomITilde.begin();
  pRandomEnd = pRandom + mNumNoise;

  // mRandomITilde[0] and mRandomITilde[mNumNoise - 1] are not needed
  for (++pRandom; pRandom != pRandomEnd; ++pRandom)
    *pRandom = randomITilde();

  C_FLOAT64 * pRandomMatrix = mRandomIMatrix.array();

  for (size_t k = 0; k < mNumNoise; ++k)
    {
      for (size_t l = 0; l < mNumNoise; ++l)
        {
          if (k < l)
            {
              *pRandom = 0.5 * (mRandomIHat[k] * mRandomIHat[l] - mRandomITilde[k]);
            }
          else if (l < k)
            {
              *pRandom = 0.5 * (mRandomIHat[k] * mRandomIHat[l] + mRandomITilde[l]);
            }
          else
            {
              *pRandom = 0.5 * (mRandomIHat[k] * mRandomIHat[k] - 1.0);
            }
        }
    }
}

C_FLOAT64 CStochasticRungeKuttaRI5::randomIHat()
{
  static const double sqrt3 = sqrt(3.0);

  switch (mpRandom->getRandomU(5))
    {
      case 0:
        return -sqrt3;
        break;

      case 1:
        return sqrt3;
        break;

      default:
        return 0;
        break;
    }
}

C_FLOAT64 CStochasticRungeKuttaRI5::randomITilde()
{
  return mpRandom->getRandomU(1) ? 1.0 : -1.0;
}

void CStochasticRungeKuttaRI5::buildStage1()
{
  *mpContainerStateTime = mTime + c01 * mStepSize;
  mContainerVariables = mH10;

  evalRate(mA[0]);

  *mpContainerStateTime = mTime + c11 * mStepSize;
  mContainerVariables = mH10;

  for (size_t k = 0; k < mNumNoise; ++k)
    {
      evalNoise(mB[0][k], k);
    }

  *mpContainerStateTime = mTime + c21 * mStepSize;
  mContainerVariables = mH10;

  for (size_t k = 0; k < mNumNoise; ++k)
    {
      evalNoise(mBB[0][k], k);
    }

  // Calculate mSumAll1 needed in stages 2 and 3
  mSumAll1 = 0.0;
  C_FLOAT64 * pI = mRandomIHat.begin();

  for (size_t l = 0; l < mNumNoise; ++l, ++pI)
    {
      C_FLOAT64 * pV = mSumAll1.begin();
      C_FLOAT64 * pVEnd = pV + mNumVariables;
      C_FLOAT64 * pB = mB[0][l];

      for (; pV != pVEnd; ++pV, ++pB)
        {
          *pV += *pB **pI;
        }
    }

  // Calculate mSumPartial1[k] needed in stages 2 and 3
  mSumPartial1 = 0.0;
  pI = mRandomIMatrix.array();

  for (size_t k = 0; k < mNumNoise; ++k)
    {

      for (size_t l = 0; l < mNumNoise; ++l, ++pI)
        {
          C_FLOAT64 * pV = mSumPartial1[k];
          C_FLOAT64 * pVEnd = pV + mNumVariables;
          C_FLOAT64 * pB = mB[0][l];

          for (; pV != pVEnd; ++pV, ++pB)
            if (l != k)
              {
                *pV += *pB **pI;
              }
        }
    }
}

void CStochasticRungeKuttaRI5::buildStage2()
{
  // Calculate H20
  C_FLOAT64 * pV = mH20.begin();
  C_FLOAT64 * pVEnd = mH20.end();
  C_FLOAT64 * pY = mH10.begin();
  C_FLOAT64 * pA = mA[0];
  C_FLOAT64 * pSum = mSumAll1.begin();

  for (; pV != pVEnd; ++pV, ++pY, ++pA, ++pSum)
    {
      *pV = *pY;
      *pV += A021 **pA * mStepSize;
      *pV += B021 **pSum * mSqrtStepSize;
    }

  // Calculate H2k for k = 0, ... m-1
  for (size_t k = 0; k < mNumNoise; ++k)
    {
      pV = mH2k[k];
      pVEnd = pV + mNumVariables;
      pY = mH10.begin();
      pA = mA[0];
      pSum = mB[0][k];

      for (; pV != pVEnd; ++pV, ++pY, ++pA, ++pSum)
        {
          *pV = *pY;
          *pV += A121 **pA * mStepSize;
          *pV += B121 **pSum * mSqrtStepSize;
        }
    }

  // Calculate HH2k for k = 0, ... m-1
  for (size_t k = 0; k < mNumNoise; ++k)
    {
      pV = mHH2k[k];
      pVEnd = pV + mNumVariables;
      pY = mH10.begin();
      pA = mA[0];
      pSum = mSumPartial1[k];

      for (; pV != pVEnd; ++pV, ++pY, ++pA, ++pSum)
        {
          *pV = *pY;
          *pV += A221 **pA * mStepSize;
          *pV += B221 **pSum * mSqrtStepSize;
        }
    }

  *mpContainerStateTime = mTime + c02 * mStepSize;
  mContainerVariables = mH20;

  evalRate(mA[1]);

  *mpContainerStateTime = mTime + c12 * mStepSize;

  for (size_t k = 0; k < mNumNoise; ++k)
    {
      memcpy(mContainerVariables.begin(), mH2k[k], mNumVariables * sizeof(C_FLOAT64));
      evalNoise(mB[1][k], k);
    }

  *mpContainerStateTime = mTime + c22 * mStepSize;

  for (size_t k = 0; k < mNumNoise; ++k)
    {
      memcpy(mContainerVariables.begin(), mHH2k[k], mNumVariables * sizeof(C_FLOAT64));
      evalNoise(mBB[1][k], k);
    }

  // Calculate mSumAll2 needed in stage 3
  mSumAll2 = 0.0;
  C_FLOAT64 * pI = mRandomIHat.begin();

  for (size_t l = 0; l < mNumNoise; ++l, ++pI)
    {
      C_FLOAT64 * pV = mSumAll2.begin();
      C_FLOAT64 * pVEnd = pV + mNumVariables;
      C_FLOAT64 * pB = mB[1][l];

      for (; pV != pVEnd; ++pV, ++pB)
        {
          *pV += *pB **pI;
        }
    }

  // Calculate mSumPartial2[k] needed in stage 3
  mSumPartial2 = 0.0;
  pI = mRandomIMatrix.array();

  for (size_t k = 0; k < mNumNoise; ++k)
    {
      for (size_t l = 0; l < mNumNoise; ++l, ++pI)
        {
          C_FLOAT64 * pV = mSumPartial2[k];
          C_FLOAT64 * pVEnd = pV + mNumVariables;
          C_FLOAT64 * pB = mB[1][l];

          for (; pV != pVEnd; ++pV, ++pB)
            if (l != k)
              {
                *pV += *pB **pI;
              }
        }
    }
}

void CStochasticRungeKuttaRI5::buildStage3()
{
  // Calculate H30
  C_FLOAT64 * pV = mH30.begin();
  C_FLOAT64 * pVEnd = mH30.end();
  C_FLOAT64 * pY = mH10.begin();
  C_FLOAT64 * pA1 = mA[0];
  C_FLOAT64 * pSum1 = mSumAll1.begin();
  C_FLOAT64 * pA2 = mA[1];
  C_FLOAT64 * pSum2 = mSumAll2.begin();

  for (; pV != pVEnd; ++pV, ++pY, ++pA1, ++pSum1, ++pA2, ++pSum2)
    {
      *pV = *pY;
      *pV += A031 **pA1 * mStepSize;
      *pV += A032 **pA2 * mStepSize;
      *pV += B031 **pSum1 * mSqrtStepSize;
      *pV += B032 **pSum2 * mSqrtStepSize;
    }

  // Calculate H3k for k = 0, ... m-1
  for (size_t k = 0; k < mNumNoise; ++k)
    {
      pV = mH3k[k];
      pVEnd = pV + mNumVariables;
      pY = mH10.begin();
      pA1 = mA[0];
      pSum1 = mB[0][k];
      pA2 = mA[1];
      pSum2 = mB[1][k];

      for (; pV != pVEnd; ++pV, ++pY, ++pA1, ++pSum1, ++pA2, ++pSum2)
        {
          *pV = *pY;
          *pV += A131 **pA1 * mStepSize;
          *pV += A132 **pA2 * mStepSize;
          *pV += B131 **pSum1 * mSqrtStepSize;
          *pV += B132 **pSum2 * mSqrtStepSize;
        }
    }

  // Calculate HH3k for k = 0, ... m-1
  for (size_t k = 0; k < mNumNoise; ++k)
    {
      pV = mHH3k[k];
      pVEnd = pV + mNumVariables;
      pY = mH10.begin();
      pA1 = mA[0];
      pSum1 = mSumPartial1[k];
      pA2 = mA[1];
      pSum2 = mSumPartial2[k];

      for (; pV != pVEnd; ++pV, ++pY, ++pA1, ++pSum1, ++pA2, ++pSum2)
        {
          *pV = *pY;
          *pV += A231 **pA1 * mStepSize;
          *pV += A232 **pA2 * mStepSize;
          *pV += B231 **pSum1 * mSqrtStepSize;
          *pV += B232 **pSum2 * mSqrtStepSize;
        }
    }

  *mpContainerStateTime = mTime + c03 * mStepSize;
  mContainerVariables = mH30;

  evalRate(mA[2]);

  *mpContainerStateTime = mTime + c13 * mStepSize;

  for (size_t k = 0; k < mNumNoise; ++k)
    {
      memcpy(mContainerVariables.begin(), mH3k[k], mNumVariables * sizeof(C_FLOAT64));
      evalNoise(mB[2][k], k);
    }

  *mpContainerStateTime = mTime + c23 * mStepSize;

  for (size_t k = 0; k < mNumNoise; ++k)
    {
      memcpy(mContainerVariables.begin(), mHH3k[k], mNumVariables * sizeof(C_FLOAT64));
      evalNoise(mBB[2][k], k);
    }
}

void CStochasticRungeKuttaRI5::calculateStateVariables(const double & time)
{
  // Sanity Checks
  assert(mTime <= time && time < mTime + *mpInternalStepSize);

  if (time == mCurrentTime) return;

  mStepSize = time - mTime;
  mSqrtStepSize = sqrt(mStepSize);
  mCurrentTime = time;

  buildStage1();
  buildStage2();
  buildStage3();

  C_FLOAT64 * pY = mContainerVariables.begin();
  C_FLOAT64 * pYEnd = mContainerVariables.end();
  C_FLOAT64 * pLeft = mH10.begin();
  C_FLOAT64 * pA0 = mA[0];
  C_FLOAT64 * pA1 = mA[1];
  C_FLOAT64 * pA2 = mA[2];
  C_FLOAT64 * pB0 = mB[0].array();
  C_FLOAT64 * pB1 = mB[1].array();
  C_FLOAT64 * pB2 = mB[2].array();
  C_FLOAT64 * pBB0 = mBB[0].array();
  C_FLOAT64 * pBB1 = mBB[1].array();
  C_FLOAT64 * pBB2 = mBB[2].array();

  for (; pY != pYEnd;
       ++pY, ++pLeft,
       ++pA0, ++pA1, ++pA2,
       ++pB0, ++pB1, ++pB2,
       ++pBB0, ++pBB1, ++pBB2)
    {
      *pY = *pLeft;
      *pY += mStepSize * (alpha1 **pA0 + alpha2 **pA1 + alpha3 **pA2);

      C_FLOAT64 * pIHat = mRandomIHat.begin();
      C_FLOAT64 * pIHatEnd = mRandomIHat.end();
      C_FLOAT64 * pIMatrix = mRandomIMatrix.array();

      C_FLOAT64 * pB0k = pB0;
      C_FLOAT64 * pB1k = pB1;
      C_FLOAT64 * pB2k = pB2;
      C_FLOAT64 * pBB0k = pBB0;
      C_FLOAT64 * pBB1k = pBB1;
      C_FLOAT64 * pBB2k = pBB2;

      for (; pIHat != pIHatEnd;
           ++pIHat, pIMatrix += mNumNoise + 1,
           pB0k += mNumNoise, pB1k += mNumNoise, pB2k += mNumNoise,
           pBB0k += mNumNoise, pBB1k += mNumNoise, pBB2k += mNumNoise)
        {
          *pY += mSqrtStepSize *
                 ((beta11 **pIHat + beta21 **pIMatrix) **pB0k +
                  (beta12 **pIHat + beta22 **pIMatrix) **pB1k +
                  (beta13 **pIHat + beta23 **pIMatrix) **pB2k +
                  (beta31 **pIHat + beta41) **pBB0k +
                  (beta32 **pIHat + beta42) **pBB1k +
                  (beta33 **pIHat + beta43) **pBB2k);
        }
    }
}

CTrajectoryMethod::Status CStochasticRungeKuttaRI5::internalStep()
{
  Status Result = NORMAL;

  generateRandomNumbers();

  // Check whether we have negative compartment sizes and particle numbers
  // or any other roots.
  if ((*mpForcePhysicalCorrectness || mNumRoots > 0) &&
      mRootFinder.checkRoots(mTime, std::min(mTime + mStepSize, mTargetTime)))
    {
      calculateStateVariables(mRootFinder.getRootTime());
      *mpContainerStateTime = mRootFinder.getRootTime();

      // If only the the first root is found we can continue with the integration otherwise
      // we have found a possible trigger for an event.
      C_INT * pRootFound = mRootsFound.begin() + 1;
      C_INT * pRootFoundEnd = mRootsFound.end();

      for (; pRootFound != pRootFoundEnd; ++pRootFound)
        if (*pRootFound != CMath::NoToggle)
          {
            Result = ROOT;
          }

      // We should peek ahead to check for roots which are triggered simultaneously
    }
  else
    {
      calculateStateVariables(std::min(mTime + mStepSize, mTargetTime));
    }

  // Check whether the new state is valid
  if (!mpContainer->isStateValid())
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 25, mTime);
    }

  mTime = *mpContainerStateTime;
  mH10 = mContainerVariables;

  return Result;
}

C_FLOAT64 CStochasticRungeKuttaRI5::calculateSmallestPhysicalValue() const
{
  if (*mpForcePhysicalCorrectness) return 1.0;

  C_FLOAT64 SmallestPhysicalValue = std::numeric_limits< C_FLOAT64 >::infinity();

  const C_FLOAT64 * pV = mContainerVariables.begin();
  const C_FLOAT64 * pVEnd = mContainerVariables.end();
  const bool * pPhysicalValue = mPhysicalValues.begin();

  for (; pV != pVEnd; ++pV, ++pPhysicalValue)
    if (*pPhysicalValue && *pV < SmallestPhysicalValue)
      {
        SmallestPhysicalValue = *pV;
      }

  return SmallestPhysicalValue;
}
