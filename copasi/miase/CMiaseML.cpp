// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseML.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/04/02 12:14:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CMiaseML.h"
#include <iostream>

CMiaseSed::CMiaseSed() : CMiaseBase()
{}

CMiaseSed::~CMiaseSed()
{
  //TODO:
  //delete content of following vectors:  mListofSimulations, mListofTasks,
  //                                      mListofModels, mListofOutputs
}

void CMiaseSed::addSimulation (CMiaseSimulation* simulation)
{
  mListofSimulations.push_back(simulation);
}

void CMiaseSed::addTask (CMiaseTask* task)
{
  mListofTasks.push_back(task);
}

void CMiaseSed::addModel (CMiaseModel* model)
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
  return mListofSimulations[ mListofSimulations.size() - 1 ];
}

int CMiaseSed::getNumOfSimulations ()
{
  return mListofSimulations.size();
}

CMiaseTask* CMiaseSed::getTask(int num)
{
  return mListofTasks[ num ];
}

CMiaseTask* CMiaseSed::getTask(std::string id)
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
  return mListofTasks[ mListofTasks.size() - 1 ];
}

int CMiaseSed::getNumOfTasks ()
{
  return mListofTasks.size();
}

CMiaseModel* CMiaseSed::getModel(int num)
{
  return mListofModels[ num ];
}

CMiaseModel* CMiaseSed::getModel(std::string id)
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
  return mListofModels[ mListofModels.size() - 1 ];
}

int CMiaseSed::getNumOfModels ()
{
  return mListofModels.size();
}

CMiaseOutput* CMiaseSed::getOutput(int num)
{
  return mListofOutputs[ num ];
}

CMiaseOutput* CMiaseSed::getOutput(std::string id)
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
  return mListofOutputs[ mListofOutputs.size() - 1 ];
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
}

void CMiaseML::setVersion(std::string version)
{
  mVersion = version;
}
