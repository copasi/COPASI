// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseML.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aruff $
//   $Date: 2008/03/20 14:28:52 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CMiaseML.h"
#include <iostream>

CMiaseSed::CMiaseSed()
{}

CMiaseSed::~CMiaseSed()
{
  mListofSimulations.clear();
  mListofTasks.clear();
  mListofModels.clear();
  mListofOutputs.clear();
}

void CMiaseSed::addSimulation (CMiaseSimulation* simulation)
{
  mListofSimulations.push_back(simulation);
}

void CMiaseSed::addTask (CMiaseTask* task)
{
  mListofTasks.push_back(task);
}

void CMiaseSed::addModelt (CMiaseModel* model)
{
  mListofModels.push_back(model);
}

void CMiaseSed::addOutput (CMiaseOutput* output)
{
  mListofOutputs.push_back(output);
}

CMiaseSimulation* CMiaseSed::getSimulation(int num)
{
  return mListofSimulations[ num ];
}

CMiaseSimulation* CMiaseSed::getSimulation(std::string id)
{
  int i;
  CMiaseSimulation* tmp;
  for (i = 0 ; i <= getNumOfSimulations() ; i++)
    {
      tmp = getSimulation(i);
      if (tmp->getId() == id)
        return tmp;
    }
}

CMiaseSimulation* CMiaseSed::getLastSimulation()
{
  return mListofSimulations[ mListofSimulations.size() ];
}

int CMiaseSed::getNumOfSimulations ()
{
  return mListofSimulations.size();
}

CMiaseTask* CMiaseSed::getTask(int num)
{
  return mListofTasks[ num ];
}

CMiaseSimulation* CMiaseSed::getTask(std::string id)
{
  int i;
  CMiaseTask* tmp;
  for (i = 0 ; i <= getNumOfTasks() ; i++)
    {
      tmp = getTask(i);
      if (tmp->getId() == id)
        return tmp;
    }
}

CMiaseTask* CMiaseSed::getLastTask()
{
  return mListofTasks[ mListofTasks.size() ];
}

int CMiaseSed::getNumOfTasks ()
{
  return mListofTasks.size();
}

CMiaseModel* CMiaseSed::getModel(int num)
{
  return mListofModels[ num ];
}

CMiaseSimulation* CMiaseSed::getModel(std::string id)
{
  int i;
  CMiaseModel* tmp;
  for (i = 0 ; i <= getNumOfModels() ; i++)
    {
      tmp = getModel(i);
      if (tmp->getId() == id)
        return tmp;
    }
}

CMiaseModel* CMiaseSed::getLastModel()
{
  return mListofModels[ mListofModels.size() ];
}

int CMiaseSed::getNumOfModels ()
{
  return mListofModels.size();
}

CMiaseOutput* CMiaseSed::getOutput(int num)
{
  return mListofOutputs[ num ];
}

CMiaseSimulation* CMiaseSed::getOutput(std::string id)
{
  int i;
  CMiaseOutput* tmp;
  for (i = 0 ; i <= getNumOfOutputs() ; i++)
    {
      tmp = getOutput(i);
      if (tmp->getId() == id)
        return tmp;
    }
}

CMiaseOutput* CMiaseSed::getLastOutput()
{
  return mListofOutputs[ mListofOutputs.size() ];
}

int CMiaseSed::getNumOfOutputs ()
{
  return mListofOutputs.size();
}

//*****************************************************************************

CMiaseML::CMiaseML() : CMiaseBase()
{}

CMiaseML::~CMiaseML()
{}

void CMiaseML::setMiaseSed(CMiaseSed* sed)
{
  mSed = sed;
}

CMiaseSed* CMiaseML::getSed()
{
  return mSed;
}

std::string CMiaseML::getXmlns()
{
  return mXmlns;
}

std::string CMiaseML::getVersion()
{
  return mVersion;
}

void CMiaseML::setXmlns(std::string xmlns)
{
  mXmlns = xmlns;
  std::cout << "::::::::::::::miaseML" << mXmlns << std::endl;
}

void CMiaseML::setVersion(std::string version)
{
  mVersion = version;
}
