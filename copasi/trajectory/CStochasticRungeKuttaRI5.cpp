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

// Uncomment this line below to get debug print out.
// #define DEBUG_OUTPUT 1

// const C_FLOAT64 c01 = 0.0;
// const C_FLOAT64 c02 = 1.0;
const C_FLOAT64 c03 = 5.0 / 12.0;

// const C_FLOAT64 c11 = 0.0;
const C_FLOAT64 c12 = 1.0 / 4.0;
const C_FLOAT64 c13 = 1.0 / 4.0;

// const C_FLOAT64 c21 = 0.0;
// const C_FLOAT64 c22 = 0.0;
// const C_FLOAT64 c23 = 0.0;

// const C_FLOAT64 A012 = 1.0;
const C_FLOAT64 A013 = 25.0 / 144.0;
const C_FLOAT64 A023 = 35.0 / 144.0;

const C_FLOAT64 A112 = 1.0 / 4.0;
const C_FLOAT64 A113 = 1.0 / 4.0;
// const C_FLOAT64 A123 = 0.0;

// const C_FLOAT64 A212 = 0.0;
// const C_FLOAT64 A213 = 0.0;
// const C_FLOAT64 A223 = 0.0;

const C_FLOAT64 B012 = 1.0 / 3.0;
const C_FLOAT64 B013 = -5.0 / 6.0;
// const C_FLOAT64 B023 = 0.0;

const C_FLOAT64 B112 = 1.0 / 2.0;
const C_FLOAT64 B113 = -1.0 / 2.0;
// const C_FLOAT64 B123 = 0.0;

// const C_FLOAT64 B212 = 1.0;
// const C_FLOAT64 B213 = -1.0;
// const C_FLOAT64 B223 = 0.0;

const C_FLOAT64 alpha1 = 1.0 / 10.0;
const C_FLOAT64 alpha2 = 3.0 / 14.0;
const C_FLOAT64 alpha3 = 24.0 / 35.0;

// const C_FLOAT64 beta11 = 1.0;
// const C_FLOAT64 beta12 = -1.0;
// const C_FLOAT64 beta13 = -1.0;

// const C_FLOAT64 beta21 = 0.0;
// const C_FLOAT64 beta22 = 1.0;
// const C_FLOAT64 beta23 = -1.0;

const C_FLOAT64 beta31 = 1.0 / 2.0;
const C_FLOAT64 beta32 = -1.0 / 4.0;
const C_FLOAT64 beta33 = -1.0 / 4.0;

// const C_FLOAT64 beta41 = 0.0;
const C_FLOAT64 beta42 = 1.0 / 2.0;
const C_FLOAT64 beta43 = -1.0 / 2.0;

// H01 = A12
CStochasticRungeKuttaRI5::CStochasticRungeKuttaRI5(const CCopasiContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  CTrajectoryMethod(pParent, methodType, taskType),
  mContainerRates(),
  mContainerNoise(),
  mContainerRoots(),
  mpInternalStepSize(NULL),
  mpMaxInternalSteps(NULL)
{
  initializeParameter();
}

CStochasticRungeKuttaRI5::CStochasticRungeKuttaRI5(const CStochasticRungeKuttaRI5 & src,
    const CCopasiContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mContainerRates(),
  mContainerNoise(),
  mContainerRoots(),
  mpInternalStepSize(NULL),
  mpMaxInternalSteps(NULL)
{
  initializeParameter();
}

CStochasticRungeKuttaRI5::~CStochasticRungeKuttaRI5()
{}

void CStochasticRungeKuttaRI5::initializeParameter()
{
  mpInternalStepSize = assertParameter("Internal Steps Size", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
  mpMaxInternalSteps = assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) 100);
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
  return FAILURE;
}

void CStochasticRungeKuttaRI5::start()
{
  mContainerRates.initialize(mpContainer->getRate(false));
  mContainerNoise.initialize(mpContainer->getNoise(false));
  mContainerRoots.initialize(mpContainer->getRoots());
}

void CStochasticRungeKuttaRI5::evalRate(CVectorCore< C_FLOAT64 > & rates)
{
  mpContainer->updateSimulatedValues(false);
  rates = mContainerRates;
}

void CStochasticRungeKuttaRI5::evalNoise(CVectorCore< C_FLOAT64 > & noise)
{
  mpContainer->updateNoiseValues(false);
  noise = mContainerNoise;
}

void CStochasticRungeKuttaRI5::evalRoot(CVectorCore< C_FLOAT64 > & roots)
{
  mpContainer->updateSimulatedValues(false);
  roots = mContainerRoots;
}
