// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseTask.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/03/20 18:33:37 $
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
  mListOfMeasurements.clear();
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
  return mListOfMeasurements[ mListOfMeasurements.size() ];
}

void CMiaseTask::setModelReference (CMiaseModel* model)
{
  mModelReference = model;
}

void CMiaseTask::setSimulationReference (CMiaseSimulation* simulation)
{
  mSimulationReference = simulation;
}

CMiaseModel* CMiaseTask::getModelReference ()
{
  mModelReference;
}

CMiaseSimulation* CMiaseTask::getSimulationReference ()
{
  mSimulationReference;
}
