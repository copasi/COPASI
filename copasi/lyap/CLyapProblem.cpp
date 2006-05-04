/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/CLyapProblem.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/04 10:54:43 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CLyapProblem class.
 */

#include <math.h>
#include <string>

#include "copasi.h"
#include "CLyapProblem.h"
#include "model/CModel.h"
//#include "model/CState.h"
#include "CopasiDataModel/CCopasiDataModel.h"

/**
 *  Default constructor.
 */
CLyapProblem::CLyapProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::lyap, pParent),
    //mpDuration(NULL),
    //mpStepSize(NULL),
    //mpStepNumber(NULL),
    mpExponentNumber(NULL),
    mpTimeSeriesRequested(NULL),
    mpTransientTime(NULL)
{
  //addParameter("StepNumber", CCopasiParameter::UINT, (unsigned C_INT32) 100);
  //addParameter("StepSize", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.01);
  //addParameter("Duration", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.0);
  addParameter("ExponentNumber", CCopasiParameter::UINT, (unsigned C_INT32) 3);
  addParameter("TimeSeriesRequested", CCopasiParameter::BOOL, (bool) true);
  addParameter("TransientTime", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.0);

  //mpStepNumber = getValue("StepNumber").pUINT;
  //mpStepSize = getValue("StepSize").pDOUBLE;
  //mpDuration = getValue("Duration").pDOUBLE;
  mpExponentNumber = getValue("ExponentNumber").pUINT;
  mpTimeSeriesRequested = getValue("TimeSeriesRequested").pBOOL;
  mpTransientTime = getValue("TransientTime").pDOUBLE;

  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CLyapProblem &" src
 */
CLyapProblem::CLyapProblem(const CLyapProblem & src,
                           const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    //mpDuration(NULL),
    //mpStepSize(NULL),
    //mpStepNumber(NULL),
    mpExponentNumber(NULL),
    mpTimeSeriesRequested(NULL),
    mpTransientTime(NULL)
    //mStepNumberSetLast(src.mStepNumberSetLast)
{
  //mpStepNumber = getValue("StepNumber").pUINT;
  //mpStepSize = getValue("StepSize").pDOUBLE;
  //mpDuration = getValue("Duration").pDOUBLE;
  mpExponentNumber = getValue("ExponentNumber").pUINT;
  mpTimeSeriesRequested = getValue("TimeSeriesRequested").pBOOL;
  mpTransientTime = getValue("TransientTime").pDOUBLE;

  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CLyapProblem::~CLyapProblem()
{DESTRUCTOR_TRACE;}

bool CLyapProblem::elevateChildren()
{
  return true;
}

void CLyapProblem::initObjects()
{
  //   const_cast<CCopasiObject *>(getParameter("StepNumber")
  //                               ->getObject(CCopasiObjectName("Reference=Value")))
  //   ->setUpdateMethod(this,
  //                     (void (CLyapProblem::*)(const C_INT32 &)) &CLyapProblem::setStepNumber);

  /*  const_cast<CCopasiObject *>(getParameter("StepSize")
                                ->getObject(CCopasiObjectName("Reference=Value")))
    ->setUpdateMethod(this, &CLyapProblem::setStepSize);


    const_cast<CCopasiObject *>(getParameter("Duration")
                                ->getObject(CCopasiObjectName("Reference=Value")))
    ->setUpdateMethod(this, &CLyapProblem::setDuration);*/
}

void CLyapProblem::setExponentNumber(const unsigned C_INT32 & number)
{
  *mpExponentNumber = number;
}

const unsigned C_INT32 & CLyapProblem::getExponentNumber() const
  {return *mpExponentNumber;}

void CLyapProblem::setTransientTime(const C_FLOAT64 & startTime)
{
  *mpTransientTime = startTime;
}

const C_FLOAT64 & CLyapProblem::getTransientTime() const
  {return *mpTransientTime;}

void CLyapProblem::setTimeSeriesRequested(bool flag)
{
  *mpTimeSeriesRequested = flag;
}

bool CLyapProblem::timeSeriesRequested() const
  {return *mpTimeSeriesRequested;}
