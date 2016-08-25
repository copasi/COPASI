// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include <copasi/optimization/COptPopulationMethod.h>
#include <copasi/randomGenerator/CRandom.h>
#include <copasi/utilities/CProcessReport.h>
#include <copasi/report/CCopasiObject.h>
#include <copasi/report/CCopasiObjectReference.h>

COptPopulationMethod::COptPopulationMethod(const CCopasiContainer * pParent,
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
  const CCopasiContainer * pParent) 
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
  if (getSubType() != CTaskEnum::ParticleSwarm && getSubType() != CTaskEnum::ScatterSearch)
  addObjectReference("Current Generation", mCurrentGeneration, CCopasiObject::ValueInt);
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
    && (getSubType() != CTaskEnum::ParticleSwarm && getSubType() != CTaskEnum::ScatterSearch))
  {
    mhGenerations =
    mpCallBack->addItem("Current Generation",
      mCurrentGeneration,
      &mGenerations);
  }

  mCurrentGeneration++;



  if (getParameter("Population Size") != NULL)
  mPopulationSize = getValue< unsigned C_INT32 >("Population Size");
  else mPopulationSize = 0;

  if (getParameter("Random Number Generator") != NULL && getParameter("Seed") != NULL)
    mpRandom = CRandom::createGenerator((CRandom::Type) getValue< unsigned C_INT32 >("Random Number Generator"),
      getValue< unsigned C_INT32 >("Seed"));
    
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
