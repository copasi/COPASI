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

#include "copasi.h"
#include "CTimeSensProblem.h"
#include "model/CModel.h"
//#include "model/CState.h"
#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

/**
 *  Default constructor.
 */
CTimeSensProblem::CTimeSensProblem(const CDataContainer * pParent):
  CTrajectoryProblem(CTaskEnum::Task::timeSens, pParent),
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
}

void CTimeSensProblem::initObjects()
{
  mpResultAnnotation = new CDataArray("Sensitivities array", this, &mResult, false);
  mpResultAnnotation->setDescription("Time-Course Sensitivities");
  mpResultAnnotation->setMode(CDataArray::Mode::Objects);
}

//virtual
bool CTimeSensProblem::elevateChildren()
{
  return CTrajectoryProblem::elevateChildren();
}

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

  for (size_t i = numParameters - 1; i >= 0 ; --i)
    {
      CCommonName currentCn = getParameterCN(i);
      CCopasiParameter* current = mpParametersGroup->getParameter(i);

      if (current->getValue<std::string>() == cn)
        mpParametersGroup->removeParameter(i);
    }
}

void CTimeSensProblem::clearParameterCNs()
{
  if (mpParametersGroup == NULL)
    return;

  mpParametersGroup->clear();
}

CArray & CTimeSensProblem::getResult()
{
  return mResult;
}

const CArray & CTimeSensProblem::getResult() const
{
  return mResult;
}

CDataArray * CTimeSensProblem::getResultAnnotated()
{
  return mpResultAnnotation;
}

const CDataArray * CTimeSensProblem::getResultAnnotated() const
{
  return mpResultAnnotation;
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

