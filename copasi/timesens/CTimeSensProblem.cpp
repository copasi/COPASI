// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 *  CTimeSensProblem class.
 *  This class describes the time sensitivities problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *
 */

#include <limits.h>
#include <cmath>
#include <string>

#include "copasi/copasi.h"
#include "CTimeSensProblem.h"
#include "copasi/model/CModel.h"
//#include "copasi/model/CState.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

/**
 *  Default constructor.
 */
CTimeSensProblem::CTimeSensProblem(const CDataContainer * pParent):
  CTrajectoryProblem(CTaskEnum::Task::timeSens, pParent),
  mpStateResultAnnotation(NULL),
  mpTargetsResultAnnotation(NULL),
  mpScaledStateResultAnnotation(NULL),
  mpScaledTargetsResultAnnotation(NULL),
  mpParametersGroup(NULL)
{
  initializeParameter();
  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CTimeSensProblem &" src
 */
CTimeSensProblem::CTimeSensProblem(const CTimeSensProblem & src,
                                   const CDataContainer * pParent):
  CTrajectoryProblem(src, pParent),
  mpStateResultAnnotation(NULL),
  mpTargetsResultAnnotation(NULL),
  mpScaledStateResultAnnotation(NULL),
  mpScaledTargetsResultAnnotation(NULL),
  mpParametersGroup(NULL)
{
  initializeParameter();
  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CTimeSensProblem::~CTimeSensProblem()
{DESTRUCTOR_TRACE;}

void CTimeSensProblem::initializeParameter()
{
  mpParametersGroup = assertGroup("ListOfParameters");
  mpTargetsGroup = assertGroup("ListOfTargets");
}

void CTimeSensProblem::initObjects()
{
  mpStateResultAnnotation = new CDataArray("State Sensitivities array", this, &mStateResult, false);
  mpStateResultAnnotation->setDescription("Time-Course Sensitivities of state variables");
  mpStateResultAnnotation->setMode(CDataArray::Mode::Objects);

  mpTargetsResultAnnotation = new CDataArray("Target Sensitivities array", this, &mTargetsResult, false);
  mpTargetsResultAnnotation->setDescription("Time-Course Sensitivities target objects");
  mpTargetsResultAnnotation->setMode(CDataArray::Mode::Objects);

  mpScaledStateResultAnnotation = new CDataArray("Scaled State Sensitivities array", this, &mScaledStateResult, false);
  mpScaledStateResultAnnotation->setDescription("Time-Course Sensitivities of state variables");
  mpScaledStateResultAnnotation->setMode(CDataArray::Mode::Objects);

  mpScaledTargetsResultAnnotation = new CDataArray("Scaled Target Sensitivities array", this, &mScaledTargetsResult, false);
  mpScaledTargetsResultAnnotation->setDescription("Time-Course Sensitivities target objects");
  mpScaledTargetsResultAnnotation->setMode(CDataArray::Mode::Objects);
}

//virtual
bool CTimeSensProblem::elevateChildren()
{
  return CTrajectoryProblem::elevateChildren();
}

//**********************************

CCommonName CTimeSensProblem::getParameterCN(size_t index)
{
  if (mpParametersGroup == NULL)
    return CCommonName();

  size_t numParameters = getNumParameters();

  if (index >= numParameters)
    return CCommonName();

  CCopasiParameter* current = mpParametersGroup->getParameter(index);

  if (current == NULL)
    return CCommonName();

  return current->getValue<std::string>();
}

void CTimeSensProblem::removeParameterCN(size_t index)
{
  if (mpParametersGroup == NULL)
    return;

  size_t numParameters = getNumParameters();

  if (index >= numParameters) return;

  mpParametersGroup->removeParameter(index);
}

void CTimeSensProblem::removeParameterCN(const CCommonName & cn)
{
  if (mpParametersGroup == NULL)
    return;

  size_t numParameters = getNumParameters();

  for (int i = numParameters - 1; i >= 0 ; --i)
    {
      CCommonName currentCn = getParameterCN(i);
      CCopasiParameter* current = mpParametersGroup->getParameter(i);

      if (current && current->getValue<std::string>() == cn)
        mpParametersGroup->removeParameter(i);
    }
}

size_t CTimeSensProblem::getNumParameters()
{
  if (mpParametersGroup == NULL)
    return 0;

  return mpParametersGroup->size();
}

void CTimeSensProblem::addParameterCN(const CCommonName & cn)
{
  if (mpParametersGroup == NULL)
    return;

  mpParametersGroup->addParameter("ParameterCN", CCopasiParameter::Type::CN, cn);
}


void CTimeSensProblem::clearParameterCNs()
{
  if (mpParametersGroup == NULL)
    return;

  mpParametersGroup->clear();
}

//***********************************

CCommonName CTimeSensProblem::getTargetCN(size_t index)
{
  if (mpTargetsGroup == NULL)
    return CCommonName();

  size_t numTargets = getNumTargets();

  if (index >= numTargets)
    return CCommonName();

  CCopasiParameter* current = mpTargetsGroup->getParameter(index);

  if (current == NULL)
    return CCommonName();

  return current->getValue<std::string>();
}

void CTimeSensProblem::removeTargetCN(size_t index)
{
  if (mpTargetsGroup == NULL)
    return;

  size_t numTargets = getNumTargets();

  if (index >= numTargets) return;

  mpTargetsGroup->removeParameter(index);
}

void CTimeSensProblem::removeTargetCN(const CCommonName & cn)
{
  if (mpTargetsGroup == NULL)
    return;

  size_t numTargets = getNumTargets();

  for (int i = numTargets - 1; i >= 0 ; --i)
    {
      CCommonName currentCn = getTargetCN(i);
      CCopasiParameter* current = mpTargetsGroup->getParameter(i);

      if (current && current->getValue<std::string>() == cn)
        mpTargetsGroup->removeParameter(i);
    }
}

size_t CTimeSensProblem::getNumTargets()
{
  if (mpTargetsGroup == NULL)
    return 0;

  return mpTargetsGroup->size();
}

void CTimeSensProblem::addTargetCN(const CCommonName & cn)
{
  if (mpTargetsGroup == NULL)
    return;

  mpTargetsGroup->addParameter("TargetCN", CCopasiParameter::Type::CN, cn);
}


void CTimeSensProblem::clearTargetCNs()
{
  if (mpTargetsGroup == NULL)
    return;

  mpTargetsGroup->clear();
}

//***********************************

CArray & CTimeSensProblem::getStateResult()
{
  return mStateResult;
}

const CArray & CTimeSensProblem::getStateResult() const
{
  return mStateResult;
}

CDataArray * CTimeSensProblem::getStateResultAnnotated()
{
  return mpStateResultAnnotation;
}

const CDataArray * CTimeSensProblem::getStateResultAnnotated() const
{
  return mpStateResultAnnotation;
}

CArray & CTimeSensProblem::getTargetsResult()
{
  return mTargetsResult;
}

const CArray & CTimeSensProblem::getTargetsResult() const
{
  return mTargetsResult;
}

CDataArray * CTimeSensProblem::getTargetsResultAnnotated()
{
  return mpTargetsResultAnnotation;
}

const CDataArray * CTimeSensProblem::getTargetsResultAnnotated() const
{
  return mpTargetsResultAnnotation;
}

CArray & CTimeSensProblem::getScaledStateResult()
{
  return mScaledStateResult;
}

const CArray & CTimeSensProblem::getScaledStateResult() const
{
  return mScaledStateResult;
}

CDataArray * CTimeSensProblem::getScaledStateResultAnnotated()
{
  return mpScaledStateResultAnnotation;
}

const CDataArray * CTimeSensProblem::getScaledStateResultAnnotated() const
{
  return mpScaledStateResultAnnotation;
}

CArray & CTimeSensProblem::getScaledTargetsResult()
{
  return mScaledTargetsResult;
}

const CArray & CTimeSensProblem::getScaledTargetsResult() const
{
  return mScaledTargetsResult;
}

CDataArray * CTimeSensProblem::getScaledTargetsResultAnnotated()
{
  return mpScaledTargetsResultAnnotation;
}

const CDataArray * CTimeSensProblem::getScaledTargetsResultAnnotated() const
{
  return mpScaledTargetsResultAnnotation;
}

