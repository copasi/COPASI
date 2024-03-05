// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
#include <cmath>

#include "copasi/copasi.h"
#include "CScanProblem.h"

#include <copasi/CopasiDataModel/CDataModel.h>
#include <copasi/utilities/CCopasiTask.h>
#include <copasi/core/CDataVector.h>

// static
const CEnumAnnotation< std::string, CScanProblem::OutputType > CScanProblem::OutputTypeName(
{
  "none",
  "subTaskBefore",
  "subTaskDuring",
  "subTaskAfter"
});

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CScanProblem::CScanProblem(const CDataContainer * pParent):
  CCopasiProblem(CTaskEnum::Task::scan, pParent),
  mpScanItems(NULL)
{
  initializeParameter();
}

/**
 *  Copy constructor.
 *  @param "const CScanProblem &" src
 */
CScanProblem::CScanProblem(const CScanProblem & src,
                           const CDataContainer * pParent):
  CCopasiProblem(src, pParent),
  mpScanItems(NULL)
{
  initializeParameter();
}

/**
 *  Destructor.
 */
CScanProblem::~CScanProblem()
{}

// virtual
bool CScanProblem::elevateChildren()
{
  CCopasiParameter * pParameter = getParameter("Output in subtask");

  if (pParameter != nullptr)
    {
      setValue("Subtask Output", OutputTypeName[pParameter->getValue< bool >() ? OutputType::subTaskDuring : OutputType::subTaskNone]);
      pdelete(pParameter);
    }

  return CCopasiProblem::elevateChildren();
}

void CScanProblem::initializeParameter()
{
  assertParameter("Subtask", CCopasiParameter::Type::UINT, (unsigned C_INT32) CTaskEnum::Task::timeCourse);

  addGroup("ScanItems");
  mpScanItems = dynamic_cast<CCopasiParameterGroup*>(getParameter("ScanItems"));

  assertParameter("Subtask Output", CCopasiParameter::Type::STRING, OutputTypeName[OutputType::subTaskDuring]);
  assertParameter("Adjust initial conditions", CCopasiParameter::Type::BOOL, false);
  assertParameter("Continue on Error", CCopasiParameter::Type::BOOL, false);
}

//***********************************
// virtual
CCopasiTask * CScanProblem::getSubTask() const
{
  CDataModel* pDataModel = getObjectDataModel();
  CTaskEnum::Task SubTaskType = getSubtask();

  if (pDataModel != NULL)
    {
      CDataVectorN< CCopasiTask >::iterator it = pDataModel->getTaskList()->begin();
      CDataVectorN< CCopasiTask >::iterator end = pDataModel->getTaskList()->end();

      for (; it != end; ++it)
        if (it->getType() == SubTaskType)
          return &*it;
    }

  return NULL;
}

void CScanProblem::setSubtask(CTaskEnum::Task type)
{
  setValue("Subtask", (unsigned C_INT32)type);
}

CTaskEnum::Task CScanProblem::getSubtask() const
{
  return (CTaskEnum::Task) getValue< unsigned C_INT32 >("Subtask");
}

bool CScanProblem::getOutputInSubtask() const
{
  return getOutputSpecification() == CScanProblem::OutputType::subTaskDuring;
}

//************************************

CScanProblem::OutputFlags CScanProblem::getOutputSpecification() const
{
  OutputFlags OutputSpecification;

  size_t pos = 0;
  std::string Flags = getValue< std::string >("Subtask Output");

  while ((pos = Flags.find("|")) != std::string::npos)
    {
      OutputSpecification |= OutputTypeName.toEnum(Flags.substr(0, pos));
      Flags.erase(0, pos + 1);
    }

  OutputSpecification |= OutputTypeName.toEnum(Flags);

  return OutputSpecification;
}

std::string CScanProblem::getOutputSpecificationString() const
{
  std::string Flags;
  std::string Separator;
  auto outputSpecification = getOutputSpecification();

for (const std::string & token : outputSpecification.getAnnotations(OutputTypeName))
    {
      Flags += Separator + token;
      Separator = "|";
    }

  return Flags;
}

void CScanProblem::setOutputInSubtask(bool outputDuring)
{
  setOutputSpecification(CScanProblem::OutputType::subTaskDuring);
}

void CScanProblem::setOutputSpecification(const CScanProblem::OutputFlags & outputSpecification)
{
  std::string Flags;
  std::string Separator;

for (const std::string & token : outputSpecification.getAnnotations(OutputTypeName))
    {
      Flags += Separator + token;
      Separator = "|";
    }

  setOutputSpecification(Flags);
}

void CScanProblem::setOutputSpecification(const std::string & specification)
{
  if (specification.empty())
    setValue("Subtask Output", OutputTypeName[OutputType::subTaskNone]);
  else
    setValue("Subtask Output", specification);
}

void CScanProblem::setOutputSpecification(const std::vector< std::string > & specification)
{
  std::string Flags;
  std::string Separator;

for (const std::string & token : specification)
    {
      Flags += Separator + token;
      Separator = "|";
    }

  setOutputSpecification(Flags);
}

//************************************

void CScanProblem::setContinueFromCurrentState(bool aic)
{
  setValue("Adjust initial conditions", aic);
}

bool CScanProblem::getContinueFromCurrentState() const
{return getValue< bool >("Adjust initial conditions");}

bool CScanProblem::getContinueOnError() const
{
  return getValue< bool >("Continue on Error");
}

void CScanProblem::setContinueOnError(bool coe)
{
  setValue("Continue on Error", coe);
}

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

  if (tmp->getType() != CCopasiParameter::Type::GROUP)
    {
      // ERROR: not a parameter group!!!
      return NULL;
    }

  return (CCopasiParameterGroup*)tmp;
}

CCopasiParameterGroup* CScanProblem::getScanItem(size_t index)
{
  CCopasiParameter* tmp = mpScanItems->getParameter(index);

  if (tmp->getType() != CCopasiParameter::Type::GROUP)
    {
      // ERROR: not a parameter group!!!
      return NULL;
    }

  return static_cast<CCopasiParameterGroup *>(tmp);
}

//CScanProblem::Type CScanProblem::getScanItemType(size_t index);
CCopasiParameterGroup* CScanProblem::addScanItem(CScanProblem::Type type, size_t steps, const CDataObject* obj)
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
CCopasiParameterGroup* CScanProblem::createScanItem(CScanProblem::Type type, size_t steps, const CDataObject* obj)
{
  CCopasiParameterGroup * tmp = new CCopasiParameterGroup("ScanItem");

  //create common parameters
  tmp->addParameter("Number of steps", CCopasiParameter::Type::UINT, (unsigned C_INT32) steps);
  tmp->addParameter("Type", CCopasiParameter::Type::UINT, (unsigned C_INT32) type);

  if (obj)
    tmp->addParameter("Object", CCopasiParameter::Type::CN, obj->getCN());
  else
    tmp->addParameter("Object", CCopasiParameter::Type::CN, CCommonName(""));

  //create specific parameters
  if ((type == SCAN_LINEAR) || (type == SCAN_RANDOM))
    {
      tmp->addParameter("Minimum", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 0.0);
      tmp->addParameter("Maximum", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 1.0);
      tmp->addParameter("log", CCopasiParameter::Type::BOOL, false);
    }

  if (type == SCAN_LINEAR)
    {
      tmp->addParameter("Values", CCopasiParameter::Type::STRING, std::string(""));
      tmp->addParameter("Use Values", CCopasiParameter::Type::BOOL, false);
    }

  if (type == SCAN_RANDOM)
    {
      tmp->addParameter("Distribution type", CCopasiParameter::Type::UINT, (unsigned C_INT32)0);
    }

  if (type == SCAN_BREAK)
    {
      tmp->addParameter("Report break", CCopasiParameter::Type::UINT, (unsigned C_INT32)0);
      tmp->addParameter("Plot break", CCopasiParameter::Type::UINT, (unsigned C_INT32)0);
    }

  if (type == SCAN_PARAMETER_SET)
    {
      tmp->addParameter("ParameterSet CNs", CCopasiParameter::Type::GROUP);
    }

  return tmp;
}

void CScanProblem::clearScanItems()
{
  mpScanItems->clear();
}

bool CScanProblem::restore(const bool & updateModel)
{
  CCopasiTask * pSubTask = getSubTask();

  if (pSubTask != NULL)
    return pSubTask->restore(updateModel);

  return true;
}

void CScanProblem::fixBuild81()
{
  CCopasiParameterGroup::index_iterator it = mpScanItems->beginIndex();
  CCopasiParameterGroup::index_iterator end = mpScanItems->endIndex();

  for (; it != end; ++it)
    {
      if ((*it)->getType() != CCopasiParameter::Type::GROUP)
        {
          continue;
        }

      CCopasiParameterGroup * pGroup = static_cast< CCopasiParameterGroup * >(*it);
      CCopasiParameter * pParam = pGroup->getParameter("Type");

      if (pParam == NULL || (Type) pParam->getValue< unsigned C_INT32 >() != SCAN_RANDOM)
        {
          continue;
        }

      // Check whether distribution type is set and not uniform
      pParam = pGroup->getParameter("Distribution type");

      if (pParam == NULL || (Type) pParam->getValue< unsigned C_INT32 >() == 0)
        {
          continue;
        }

      // Check whether log is set and true
      pParam = pGroup->getParameter("log");

      if (pParam == NULL || pParam->getValue< bool >() == false)
        {
          continue;
        }

      // We need to fix min and max
      pParam = pGroup->getParameter("Minimum");

      if (pParam != NULL)
        {
          pParam->setValue(log(pParam->getValue< C_FLOAT64 >()));
        }

      pParam = pGroup->getParameter("Maximum");

      if (pParam != NULL)
        {
          pParam->setValue(log(pParam->getValue< C_FLOAT64 >()));
        }
    }

  return;
}
