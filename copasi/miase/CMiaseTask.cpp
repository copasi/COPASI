// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseTask.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/04/02 12:14:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CMiaseTask.h"

CMiaseMeasurementData::CMiaseMeasurementData() : CMiaseBase()
{}

CMiaseMeasurementData::~CMiaseMeasurementData()
{}

std::string CMiaseMeasurementData::getSource()
{
  return mSource;
}

std::string CMiaseMeasurementData::getName()
{
  return mName;
}

void CMiaseMeasurementData::setSource(std::string source)
{
  mSource = source;
}

void CMiaseMeasurementData::setName(std::string name)
{
  mName = name;
}

//*****************************************************************************

CMiaseTask::CMiaseTask() : CMiaseBaseEnhanced()
{}

CMiaseTask::~CMiaseTask()
{
  //TODO:
  //delete content of following vector:  mListOfMeasurements
}

void CMiaseTask::addMeasurement (CMiaseMeasurementData* measurement)
{
  mListOfMeasurements.push_back(measurement);
}

CMiaseMeasurementData* CMiaseTask::getMeasurement(int num)
{
  return mListOfMeasurements[ num ];
}

int CMiaseTask::getNumberOfMeasurements()
{
  return mListOfMeasurements.size();
}

CMiaseMeasurementData* CMiaseTask::getLastMeasurement()
{
  return mListOfMeasurements[ mListOfMeasurements.size() - 1];
}

void CMiaseTask::setModelReference (std::string model)
{
  mModelReference = model;
}

void CMiaseTask::setSimulationReference (std::string simulation)
{
  mSimulationReference = simulation;
}

std::string CMiaseTask::getModelReference ()
{
  mModelReference;
}

std::string CMiaseTask::getSimulationReference ()
{
  mSimulationReference;
}
