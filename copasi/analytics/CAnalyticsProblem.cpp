// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CAnalyticsProblem.h"
#include <copasi/CopasiDataModel/CDataModel.h>

CAnalyticsProblem::CAnalyticsProblem(const CDataContainer * pParent):
  CTrajectoryProblem(pParent),
  mpFlagLimitCrossings(NULL),
  mpCrossingsLimit(NULL),
  mpFlagLimitConvergence(NULL),
  mpConvergenceTolerance(NULL),
  mpFlagLimitOutConvergence(NULL),
  mpConvergenceOutTolerance(NULL),
  mpFlagLimitOutCrossings(NULL),
  mpOutCrossingsLimit(NULL),
  mpFlagLimitOutTime(NULL),
  mpSingleObjectCN(NULL),
  mpFlagPositiveDirection(NULL),
  mpThreshold(NULL)
//--- ETTORE start ---
  , mpObjectSelected(NULL)
//--- ETTORE end -----
{
  initializeParameter();
  initObjects();
  CONSTRUCTOR_TRACE;
}

CAnalyticsProblem::CAnalyticsProblem(const CAnalyticsProblem & src,
                                     const CDataContainer * pParent):
  CTrajectoryProblem(src, pParent),
  mpFlagLimitCrossings(NULL),
  mpCrossingsLimit(NULL),
  mpFlagLimitConvergence(NULL),
  mpConvergenceTolerance(NULL),
  mpFlagLimitOutConvergence(NULL),
  mpConvergenceOutTolerance(NULL),
  mpFlagLimitOutCrossings(NULL),
  mpOutCrossingsLimit(NULL),
  mpFlagLimitOutTime(NULL),
  mpSingleObjectCN(NULL),
  mpFlagPositiveDirection(NULL),
  mpThreshold(NULL)
//--- ETTORE start ---
  , mpObjectSelected(NULL)
//--- ETTORE end -----
{
  initializeParameter();
  initObjects();
  CONSTRUCTOR_TRACE;
}

void CAnalyticsProblem::initializeParameter()
{
  mpFlagLimitCrossings = assertParameter("LimitCrossings", CCopasiParameter::Type::BOOL, false);
  mpCrossingsLimit = assertParameter("NumCrossingsLimit", CCopasiParameter::Type::UINT, (unsigned C_INT32)0);
  mpFlagLimitOutTime = assertParameter("LimitOutTime", CCopasiParameter::Type::BOOL, false);
  mpFlagLimitOutCrossings = assertParameter("LimitOutCrossings", CCopasiParameter::Type::BOOL, false);
  mpFlagPositiveDirection = assertParameter("PositiveDirection", CCopasiParameter::Type::BOOL, true);
  mpOutCrossingsLimit = assertParameter("NumOutCrossingsLimit", CCopasiParameter::Type::UINT, (unsigned C_INT32)0);
  mpFlagLimitConvergence = assertParameter("LimitUntilConvergence", CCopasiParameter::Type::BOOL, false);
  mpConvergenceTolerance = assertParameter("ConvergenceTolerance", CCopasiParameter::Type::DOUBLE, (C_FLOAT64)1E-6);
  mpThreshold = assertParameter("Threshold", CCopasiParameter::Type::DOUBLE, (C_FLOAT64)0);
  mpFlagLimitOutConvergence = assertParameter("DelayOutputUntilConvergence", CCopasiParameter::Type::BOOL, false);
  mpConvergenceOutTolerance = assertParameter("OutputConvergenceTolerance", CCopasiParameter::Type::DOUBLE, (C_FLOAT64)1E-6);
  mpTriggerExpression = assertParameter("TriggerExpression", CCopasiParameter::Type::EXPRESSION, std::string(""));
  mpSingleObjectCN = assertParameter("SingleVariable", CCopasiParameter::Type::CN, CCommonName(""));
  setOutputEvent(false);
}

void CAnalyticsProblem::initObjects()
{
  //here we should create things like object references to results of the calculation
}

/**
 *  Destructor.
 */
CAnalyticsProblem::~CAnalyticsProblem()
{DESTRUCTOR_TRACE;}

std::ostream &operator<<(std::ostream &os, const CAnalyticsProblem & o)
{
  os << "Cross Section Problem description: Not implemented yet." << std::endl;
  const CDataModel* pDataModel = o.getObjectDataModel();
  assert(pDataModel != NULL);

  return os;
}

void CAnalyticsProblem::print(std::ostream * ostream) const
{*ostream << *this;}

bool CAnalyticsProblem::getFlagLimitCrossings() const
{return *mpFlagLimitCrossings;}

const unsigned C_INT32 & CAnalyticsProblem::getCrossingsLimit() const
{return *mpCrossingsLimit;}

bool CAnalyticsProblem::getFlagLimitOutCrossings() const
{return *mpFlagLimitOutCrossings;}

const unsigned C_INT32 & CAnalyticsProblem::getOutCrossingsLimit() const
{return *mpOutCrossingsLimit;}

bool CAnalyticsProblem::getFlagLimitOutTime() const
{return *mpFlagLimitOutTime;}

const C_FLOAT64 & CAnalyticsProblem::getTimeLimit() const
{return *mpDuration;}

bool CAnalyticsProblem::isPositiveDirection() const
{
  return *mpFlagPositiveDirection;
}
void CAnalyticsProblem::setPositiveDirection(bool isPositive)
{
  *mpFlagPositiveDirection = isPositive;
}

void CAnalyticsProblem::setFlagLimitCrossings(bool flagLimitCrossing)
{*mpFlagLimitCrossings = flagLimitCrossing;}

void CAnalyticsProblem::setCrossingsLimit(const unsigned C_INT32 &crossingLimit)
{*mpCrossingsLimit = crossingLimit;}

void CAnalyticsProblem::setFlagLimitOutCrossings(bool flagLimitCrossing)
{*mpFlagLimitOutCrossings = flagLimitCrossing;}

void CAnalyticsProblem::setFlagLimitOutTime(bool flagLimitTime)
{*mpFlagLimitOutTime = flagLimitTime;}

void CAnalyticsProblem::setTimeLimit(const C_FLOAT64 &timeLimit)
{*mpDuration = timeLimit;}

/**
 * return the variable
 */
const std::string& CAnalyticsProblem::getSingleObjectCN() const
{
  return *mpSingleObjectCN;
}

void CAnalyticsProblem::setSingleObjectCN(const CDataObject* pObject)
{
  if (pObject == NULL) return;

  setSingleObjectCN(pObject->getCN());
}

//--- ETTORE start ---
void CAnalyticsProblem::retrieveSelectedObject(const CDataObject* pObject)
{
  mpObjectSelected = pObject;
}

const CDataObject* CAnalyticsProblem::getSelectedObject()
{
  return mpObjectSelected;
}

//--- ETTORE end -----

const C_FLOAT64& CAnalyticsProblem::getThreshold() const
{
  return *mpThreshold;
}
void CAnalyticsProblem::setThreshold(const C_FLOAT64 &threshold)
{
  *mpThreshold = threshold;
}

/*
 * set the variable
 */
void CAnalyticsProblem::setSingleObjectCN(const std::string& cn)
{
  *mpSingleObjectCN = cn;
}

bool CAnalyticsProblem::getFlagLimitConvergence() const
{
  return *mpFlagLimitConvergence;
}

const C_FLOAT64 &CAnalyticsProblem::getConvergenceTolerance() const
{
  return *mpConvergenceTolerance;
}

void CAnalyticsProblem::setFlagLimitConvergence(bool flagLimitConvergence)
{
  *mpFlagLimitConvergence = flagLimitConvergence;
}

bool CAnalyticsProblem::getFlagLimitOutConvergence() const
{
  return *mpFlagLimitOutConvergence;
}

const C_FLOAT64 &CAnalyticsProblem::getConvergenceOutTolerance() const
{
  return *mpConvergenceOutTolerance;
}

void CAnalyticsProblem::setFlagLimitOutConvergence(bool flagLimitConvergence)
{
  *mpFlagLimitOutConvergence = flagLimitConvergence;
}
