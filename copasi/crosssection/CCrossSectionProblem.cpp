// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/crosssection/CCrossSectionProblem.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2010/05/14 22:20:54 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CCrossSectionProblem.h"

CCrossSectionProblem::CCrossSectionProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::crosssection, pParent),
    mpFlagLimitCrossings(NULL),
    mpCrossingsLimit(NULL),
    mpFlagLimitTime(NULL),
    mpTimeLimit(NULL),
    mpOutputStartTime(NULL)
{
  addParameter("LimitCrossings", CCopasiParameter::BOOL, false);
  mpFlagLimitCrossings = getValue("LimitCrossings").pBOOL;

  addParameter("NumCrossingsLimit", CCopasiParameter::UINT, (unsigned C_INT32)0);
  mpCrossingsLimit = getValue("NumCrossingsLimit").pUINT;

  addParameter("LimitTime", CCopasiParameter::BOOL, true);
  mpFlagLimitTime = getValue("LimitTime").pBOOL;

  addParameter("TimeLimit", CCopasiParameter::DOUBLE, 100.0);
  mpTimeLimit = getValue("TimeLimit").pDOUBLE;

  addParameter("OutputStartTime", CCopasiParameter::DOUBLE, 0.0);
  mpOutputStartTime = getValue("OutputStartTime").pDOUBLE;

  mpTriggerExpression =
    assertParameter("TriggerExpression", CCopasiParameter::EXPRESSION, std::string(""))->getValue().pEXPRESSION;


  initObjects();
  CONSTRUCTOR_TRACE;
}

CCrossSectionProblem::CCrossSectionProblem(const CCrossSectionProblem & src,
    const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mpFlagLimitCrossings(NULL),
    mpCrossingsLimit(NULL),
    mpFlagLimitTime(NULL),
    mpTimeLimit(NULL),
    mpOutputStartTime(NULL)
{
  mpFlagLimitCrossings = getValue("LimitCrossings").pBOOL;
  mpCrossingsLimit = getValue("NumCrossingsLimit").pUINT;
  mpFlagLimitTime = getValue("LimitTime").pBOOL;
  mpTimeLimit = getValue("TimeLimit").pDOUBLE;
  mpOutputStartTime = getValue("OutputStartTime").pDOUBLE;
  mpTriggerExpression =
    assertParameter("TriggerExpression", CCopasiParameter::EXPRESSION, std::string(""))->getValue().pEXPRESSION;

  initObjects();
  CONSTRUCTOR_TRACE;
}

void CCrossSectionProblem::initObjects()
{
  //here we should create things like object references to results of the calculation
}

/**
 *  Destructor.
 */
CCrossSectionProblem::~CCrossSectionProblem()
{DESTRUCTOR_TRACE;}
