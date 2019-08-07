// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "copasi/optimization/COptPopulationMethod.h"
#include "copasi/randomGenerator/CRandom.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/core/CDataObject.h"
#include "copasi/core/CDataObjectReference.h"

COptPopulationMethod::COptPopulationMethod(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType /*= CTaskEnum::optimization*/)
  : COptMethod(pParent, methodType, taskType)
  , mPopulationSize(0)
  , mGenerations(0)
  , mCurrentGeneration(0)
  , mhGenerations(C_INVALID_INDEX)
  , mVariableSize(0)
  , mIndividuals()
  , mValues()
  , mpRandom(NULL)
{
  initObjects();
}

COptPopulationMethod::COptPopulationMethod(const COptPopulationMethod & src,
    const CDataContainer * pParent)
  : COptMethod(src, pParent)
  , mPopulationSize(0)
  , mGenerations(0)
  , mCurrentGeneration(0)
  , mhGenerations(C_INVALID_INDEX)
  , mVariableSize(0)
  , mIndividuals()
  , mValues()
  , mpRandom(NULL)
{
  initObjects();
}

COptPopulationMethod::~COptPopulationMethod()
{
  cleanup();
}

void COptPopulationMethod::initObjects()
{
  if (getSubType() != CTaskEnum::Method::ParticleSwarm && getSubType() != CTaskEnum::Method::ScatterSearch)
    addObjectReference("Current Generation", mCurrentGeneration, CDataObject::ValueInt);
}

#include <iostream>

bool
COptPopulationMethod::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mCurrentGeneration = 0;
  mGenerations = 0;

  if (getParameter("Number of Generations") != NULL)
    mGenerations = getValue< unsigned C_INT32 >("Number of Generations");

  if (mpCallBack
      && (getSubType() != CTaskEnum::Method::ParticleSwarm && getSubType() != CTaskEnum::Method::ScatterSearch))
    {
      mhGenerations =
        mpCallBack->addItem("Current Generation",
                            mCurrentGeneration,
                            &mGenerations);
    }

  ++mCurrentGeneration;

  if (getParameter("Population Size") != NULL)
    mPopulationSize = getValue< unsigned C_INT32 >("Population Size");
  else
    mPopulationSize = 0;

  pdelete(mpRandom);

  if (getParameter("Random Number Generator") != NULL && getParameter("Seed") != NULL)
    {
      mpRandom = CRandom::createGenerator((CRandom::Type) getValue< unsigned C_INT32 >("Random Number Generator"),
                                          getValue< unsigned C_INT32 >("Seed"));
    }
  else
    {
      mpRandom = CRandom::createGenerator();
    }

  mVariableSize = mpOptItem->size();

  return true;
}

bool
COptPopulationMethod::cleanup()
{
  size_t i;

  pdelete(mpRandom);

  for (i = 0; i < mIndividuals.size(); i++)
    pdelete(mIndividuals[i]);

  mIndividuals.clear();
  return true;
}

C_INT32 COptPopulationMethod::getPopulationSize()
{
  return mPopulationSize;
}

C_INT32 COptPopulationMethod::getNumGenerations()
{
  return mGenerations;
}

C_INT32 COptPopulationMethod::getCurrentGeneration()
{
  return mCurrentGeneration;
}

const std::vector< CVector < C_FLOAT64 > * >& COptPopulationMethod::getPopulation()
{
  return mIndividuals;
}

const CVector< C_FLOAT64 >& COptPopulationMethod::getObjectiveValues()
{
  return mValues;
}

void COptPopulationMethod::print(std::ostream * ostream) const
{
  COptMethod::print(ostream);

  *ostream << std::endl << *this;
}

std::ostream &operator<<(std::ostream &os, const COptPopulationMethod & o)
{
  os << "Population Information: " << std::endl;
  os << "Population Size: " << o.mPopulationSize << std::endl;
  os << "# Generations / Iterations: " << o.mGenerations << std::endl;
  os << "Current Generation / Iteration: " << o.mCurrentGeneration << std::endl;
  os << "Population Values: " << std::endl << "   " << o.mValues << std::endl << std::endl;
  os << "Population:" << std::endl;

  std::vector< CVector < C_FLOAT64 > * >::const_iterator it = o.mIndividuals.begin();

  for (; it != o.mIndividuals.end(); ++it)
    {
      os << "   " << **it << std::endl;
    }

  return os;
}
