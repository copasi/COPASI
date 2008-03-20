// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseSimulation.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aruff $
//   $Date: 2008/03/20 14:28:52 $
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

UniformTimeCourse::UniformTimeCourse() : CMiaseSimulation()
{}

UniformTimeCourse::~UniformTimeCourse()
{}

double UniformTimeCourse::returnInitialTime()
{
  return mInitialTime;
}

double UniformTimeCourse::returnOutputStartTime()
{
  return mOutputStartTime;
}

double UniformTimeCourse::returnOutputEndTime()
{
  return mOutputEndTime;
}

int UniformTimeCourse::returnNumberOfPoints()
{
  return mNumberOfPoints;
}

void UniformTimeCourse::setInitialTime(double initialTime)
{
  mInitialTime = initialTime;
}

void UniformTimeCourse::setOutputStartTime(double outputStartTime)
{
  mOutputStartTime = outputStartTime;
}

void UniformTimeCourse::setOutputEndTime(double outputEndTime)
{
  mOutputEndTime = outputEndTime;
}

void UniformTimeCourse::setNumberOfPoints(double numberOfPoints)
{
  mNumberOfPoints = numberOfPoints;
}

//*****************************************************************************
