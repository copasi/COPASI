// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CScanProblem class.
 */

#include <string>

#include "copasi.h"
#include "CScanProblem.h"
//#include "model/CModel.h"
//#include "model/CState.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CScanProblem::CScanProblem(const CCopasiContainer * pParent):
  CCopasiProblem(CCopasiTask::scan, pParent)
{
  addParameter("Subtask", CCopasiParameter::UINT, (unsigned C_INT32) CCopasiTask::timeCourse);

  addGroup("ScanItems");
  mpScanItems = dynamic_cast<CCopasiParameterGroup*>(getParameter("ScanItems"));

  addParameter("Output in subtask", CCopasiParameter::BOOL, true);
  addParameter("Adjust initial conditions", CCopasiParameter::BOOL, false);

  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CScanProblem &" src
 */
CScanProblem::CScanProblem(const CScanProblem & src,
                           const CCopasiContainer * pParent):
  CCopasiProblem(src, pParent)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CScanProblem::~CScanProblem()
{DESTRUCTOR_TRACE;}

//***********************************

void CScanProblem::setSubtask(CCopasiTask::Type type)
{
  setValue("Subtask", (unsigned C_INT32)type);
}

CCopasiTask::Type CScanProblem::getSubtask() const
{return *(CCopasiTask::Type *) getValue("Subtask").pUINT;}

//************************************

void CScanProblem::setOutputInSubtask(bool ois)
{
  setValue("Output in subtask", ois);
}

const bool & CScanProblem::getOutputInSubtask() const
{return * getValue("Output in subtask").pBOOL;}

//************************************

void CScanProblem::setContinueFromCurrentState(bool aic)
{
  setValue("Adjust initial conditions", aic);
}

bool CScanProblem::getContinueFromCurrentState() const
{return * getValue("Adjust initial conditions").pBOOL;}

//************************************

void CScanProblem::load(CReadConfig & C_UNUSED(configBuffer),
                        CReadConfig::Mode C_UNUSED(mode))
{}

size_t CScanProblem::getNumberOfScanItems() const
{
  return mpScanItems->size();
}

const CCopasiParameterGroup* CScanProblem::getScanItem(size_t index) const
{
  CCopasiParameter* tmp = mpScanItems->getParameter(index);

  if (tmp->getType() != CCopasiParameter::GROUP)
    {
      // ERROR: not a parameter group!!!
      return NULL;
    }

  return (CCopasiParameterGroup*)tmp;
}

CCopasiParameterGroup* CScanProblem::getScanItem(size_t index)
{
  CCopasiParameter* tmp = mpScanItems->getParameter(index);

  if (tmp->getType() != CCopasiParameter::GROUP)
    {
      // ERROR: not a parameter group!!!
      return NULL;
    }

  return (CCopasiParameterGroup*)tmp;
}

//CScanProblem::Type CScanProblem::getScanItemType(size_t index);
CCopasiParameterGroup* CScanProblem::addScanItem(CScanProblem::Type type, size_t steps, const CCopasiObject* obj)
{
  CCopasiParameterGroup * pItem = createScanItem(type, steps, obj);
  mpScanItems->addParameter(pItem);

  return pItem;
}

bool CScanProblem::removeScanItem(const size_t & index)
{
  return mpScanItems->removeParameter(index);
}

// static
CCopasiParameterGroup* CScanProblem::createScanItem(CScanProblem::Type type, size_t steps, const CCopasiObject* obj)
{
  CCopasiParameterGroup * tmp = new CCopasiParameterGroup("ScanItem");

  //create common parameters
  tmp->addParameter("Number of steps", CCopasiParameter::UINT, (unsigned C_INT32) steps);
  tmp->addParameter("Type", CCopasiParameter::UINT, (unsigned C_INT32) type);

  if (obj)
    tmp->addParameter("Object", CCopasiParameter::CN, obj->getCN());
  else
    tmp->addParameter("Object", CCopasiParameter::CN, CCopasiObjectName(""));

  //create specific parameters
  if ((type == SCAN_LINEAR) || (type == SCAN_RANDOM))
    {
      tmp->addParameter("Minimum", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.0);
      tmp->addParameter("Maximum", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.0);
      tmp->addParameter("log", CCopasiParameter::BOOL, false);
    }

  if (type == SCAN_RANDOM)
    {
      tmp->addParameter("Distribution type", CCopasiParameter::UINT, (unsigned C_INT32)0);
    }

  if (type == SCAN_BREAK)
    {
      tmp->addParameter("Report break", CCopasiParameter::UINT, (unsigned C_INT32)0);
      tmp->addParameter("Plot break", CCopasiParameter::UINT, (unsigned C_INT32)0);
    }

  return tmp;
}

void CScanProblem::clearScanItems()
{
  mpScanItems->clear();
}
