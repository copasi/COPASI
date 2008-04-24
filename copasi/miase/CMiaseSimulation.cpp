// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseSimulation.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/04/02 12:14:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CMiaseSimulation.h"

CMiaseSimulation::CMiaseSimulation() : CMiaseBaseEnhanced()
{}

CMiaseSimulation::~CMiaseSimulation()
{}

//*****************************************************************************

CMiaseUniformTimeCourse::CMiaseUniformTimeCourse() : CMiaseSimulation()
{}

CMiaseUniformTimeCourse::~CMiaseUniformTimeCourse()
{}

double CMiaseUniformTimeCourse::getInitialTime()
{
  return mInitialTime;
}

double CMiaseUniformTimeCourse::getOutputStartTime()
{
  return mOutputStartTime;
}

double CMiaseUniformTimeCourse::getOutputEndTime()
{
  return mOutputEndTime;
}

int CMiaseUniformTimeCourse::getNumberOfPoints()
{
  return mNumberOfPoints;
}

void CMiaseUniformTimeCourse::setInitialTime(double initialTime)
{
  mInitialTime = initialTime;
}

void CMiaseUniformTimeCourse::setOutputStartTime(double outputStartTime)
{
  mOutputStartTime = outputStartTime;
}

void CMiaseUniformTimeCourse::setOutputEndTime(double outputEndTime)
{
  mOutputEndTime = outputEndTime;
}

void CMiaseUniformTimeCourse::setNumberOfPoints(double numberOfPoints)
{
  mNumberOfPoints = numberOfPoints;
}

//*****************************************************************************
