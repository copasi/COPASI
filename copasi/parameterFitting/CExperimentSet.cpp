// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <algorithm>
#include <limits>
#include <cmath>

#include "copasi/copasi.h"

#include "CExperimentSet.h"
#include "CExperiment.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/utility.h"
#include "copasi/commandline/CLocaleString.h"

CExperimentSet::CExperimentSet(const CDataContainer * pParent,
                               const std::string & name):
  CCopasiParameterGroup(name, pParent, "CExperimentSet"),
  mpExperiments(NULL),
  mNonExperiments(0),
  mDependentObjects(0),
  mDependentObjectiveValues(0),
  mDependentRMS(0),
  mDependentErrorMean(0),
  mDependentErrorMeanSD(0),
  mDependentDataCount(0),
  mValidValueCount(0)
{initializeParameter();}

CExperimentSet::CExperimentSet(const CExperimentSet & src,
                               const CDataContainer * pParent):
  CCopasiParameterGroup(src, static_cast< const CDataContainer * >((pParent != NULL) ? pParent : src.getObjectDataModel())),
  mpExperiments(NULL),
  mNonExperiments(0),
  mDependentObjects(0),
  mDependentObjectiveValues(0),
  mDependentRMS(0),
  mDependentErrorMean(0),
  mDependentErrorMeanSD(0),
  mDependentDataCount(0),
  mValidValueCount(0)
{initializeParameter();}

CExperimentSet::CExperimentSet(const CCopasiParameterGroup & group,
                               const CDataContainer * pParent):
  CCopasiParameterGroup(group, static_cast< const CDataContainer * >((pParent != NULL) ? pParent : group.getObjectDataModel())),
  mpExperiments(NULL),
  mNonExperiments(0),
  mDependentObjects(0),
  mDependentObjectiveValues(0),
  mDependentRMS(0),
  mDependentErrorMean(0),
  mDependentErrorMeanSD(0),
  mDependentDataCount(0),
  mValidValueCount(0)
{initializeParameter();}

CExperimentSet::~CExperimentSet() {}

void CExperimentSet::initializeParameter()
{elevateChildren();}

bool CExperimentSet::elevateChildren()
{
  index_iterator it = beginIndex();
  index_iterator end = endIndex();

  for (; it != end; ++it)
    {
      if (dynamic_cast< CCopasiParameterGroup * >(*it) == NULL) continue;

      if (!elevate<CExperiment, CCopasiParameterGroup>(*it)) return false;
    }

  mpExperiments = static_cast< std::vector< CExperiment * > * >(mpValue);

  sort();

  return true;
}

bool CExperimentSet::compile(const CMathContainer * pMathContainer)
{
  bool success = true;

  // First we need to sort the experiments so that we can make use of continued
  // file reading.
  sort();

  CObjectInterface::ObjectSet DependentObjects;

  std::ifstream in;
  std::string CurrentFileName("");
  size_t CurrentLineNumber = 1;

  std::vector< CExperiment * >::iterator it = mpExperiments->begin() + mNonExperiments;
  std::vector< CExperiment * >::iterator end = mpExperiments->end();

  for (; it != end; ++it)
    {
      if (CurrentFileName != (*it)->getFileName())
        {
          CurrentFileName = (*it)->getFileName();
          CurrentLineNumber = 1;

          if (in.is_open())
            {
              in.close();
              in.clear();
            }

          in.open(CLocaleString::fromUtf8(CurrentFileName).c_str(), std::ios::binary);

          if (in.fail())
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 8, CurrentFileName.c_str());
              return false; // File can not be opened.
            }
        }

      if (!(*it)->read(in, CurrentLineNumber))
        {
          return false;
        }

      if (!(*it)->compile(pMathContainer))
        {
          return false;
        }

      const std::map< const CObjectInterface *, size_t > & ExpDependentObjects = (*it)->getDependentObjectsMap();
      std::map< const CObjectInterface *, size_t >::const_iterator itObject  = ExpDependentObjects.begin();
      std::map< const CObjectInterface *, size_t >::const_iterator endObject = ExpDependentObjects.end();

      for (; itObject != endObject; ++itObject)
        {
          DependentObjects.insert(itObject->first);
        }
    }

  mDependentObjects.resize(DependentObjects.size());
  const CObjectInterface ** ppInsert = mDependentObjects.array();
  CObjectInterface::ObjectSet::const_iterator itObject = DependentObjects.begin();
  CObjectInterface::ObjectSet::const_iterator endObject = DependentObjects.end();

  for (; itObject != endObject; ++itObject, ++ppInsert)
    *ppInsert = *itObject;

  // Allocation and initialization of statistical information
  mDependentObjectiveValues.resize(mDependentObjects.size());
  mDependentObjectiveValues = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  mDependentRMS.resize(mDependentObjects.size());
  mDependentRMS = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  mDependentErrorMean.resize(mDependentObjects.size());
  mDependentErrorMean = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  mDependentErrorMeanSD.resize(mDependentObjects.size());
  mDependentErrorMeanSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  mDependentDataCount.resize(mDependentObjects.size());
  mDependentDataCount = std::numeric_limits<size_t>::quiet_NaN();

  return success;
}

bool CExperimentSet::calculateStatistics()
{
  mDependentObjectiveValues.resize(mDependentObjects.size());
  mDependentObjectiveValues = 0.0;

  mDependentRMS.resize(mDependentObjects.size());
  mDependentRMS = 0.0;

  mDependentErrorMean.resize(mDependentObjects.size());
  mDependentErrorMean = 0.0;

  mDependentErrorMeanSD.resize(mDependentObjects.size());
  mDependentErrorMeanSD = 0.0;

  mDependentDataCount.resize(mDependentObjects.size());
  mDependentDataCount = 0;
  mValidValueCount = 0;

  // calculate the per experiment and per dependent value statistics.
  std::vector< CExperiment * >::iterator it = mpExperiments->begin() + mNonExperiments;
  std::vector< CExperiment * >::iterator end = mpExperiments->end();

  size_t i, Count;
  C_FLOAT64 Tmp;

  for (; it != end; ++it)
    {
      (*it)->calculateStatistics();

      const CObjectInterface ** ppObject = mDependentObjects.array();
      const CObjectInterface ** ppEnd = ppObject + mDependentObjects.size();

      for (i = 0; ppObject != ppEnd; ++ppObject, ++i)
        {
          Count = (*it)->getColumnValidValueCount(*ppObject);

          if (Count)
            {
              mDependentObjectiveValues[i] += (*it)->getObjectiveValue(*ppObject);

              Tmp = (*it)->getRMS(*ppObject);
              mDependentRMS[i] += Tmp * Tmp * Count;

              mDependentErrorMean[i] += (*it)->getErrorSum(*ppObject);

              mDependentDataCount[i] += Count;
              mValidValueCount += Count;
            }
        }
    }

  size_t imax = mDependentObjects.size();

  for (i = 0; i != imax; i++)
    {
      Count = mDependentDataCount[i];

      if (Count)
        {
          mDependentRMS[i] = sqrt(mDependentRMS[i] / Count);
          mDependentErrorMean[i] /= Count;
        }
      else
        {
          mDependentRMS[i] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
          mDependentErrorMean[i] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
        }
    }

  it = mpExperiments->begin() + mNonExperiments;

  // We need to loop again to calculate the std. deviation.
  for (; it != end; ++it)  //over experiments
    {
      const CObjectInterface ** ppObject = mDependentObjects.array();
      const CObjectInterface ** ppEnd = ppObject + mDependentObjects.size();

      for (i = 0; ppObject != ppEnd; ++ppObject, ++i)
        {
          Count = (*it)->getColumnValidValueCount(*ppObject);

          if (Count)
            mDependentErrorMeanSD[i] +=
              (*it)->getErrorMeanSD(*ppObject, mDependentErrorMean[i]);
        }
    }

  for (i = 0; i != imax; i++)
    {
      Count = mDependentDataCount[i];

      if (Count)
        mDependentErrorMeanSD[i] = sqrt(mDependentErrorMeanSD[i] / Count);
      else
        mDependentErrorMeanSD[i] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  // This is the time to call the output handler to plot the fitted points.
  size_t j, jmax;

  imax = 0;

  for (it = mpExperiments->begin() + mNonExperiments; it != end; ++it)
    {
      imax = std::max(imax, (*it)->getDependentData().numRows());
    }

  CCopasiTask * pParentTask = dynamic_cast< CCopasiTask *>(getObjectAncestor("Task"));
  assert(pParentTask != NULL);

  for (i = 0, j = 0; i < imax; i++)
    {
      for (it = mpExperiments->begin() + mNonExperiments; it != end; ++it)
        (*it)->updateFittedPointValues(i);

      pParentTask->output(COutputInterface::AFTER);

      // TODO the 3 below relies on the fact that currently the number of intermittend point is CFitProblem::numIntermediateSteps
      jmax = std::min(j + 3, (imax - 1) * 3);

      for (; j < jmax; j++)
        {
          for (it = mpExperiments->begin() + mNonExperiments; it != end; ++it)
            {
              if ((*it)->getExperimentType() == CTaskEnum::Task::timeCourse)
                {
                  (*it)->updateFittedPointValuesFromExtendedTimeSeries(j);
                }
            }

          pParentTask->output(COutputInterface::AFTER);
        }
    }

  return true;
}

const CVector< const CObjectInterface * > & CExperimentSet::getDependentObjects() const
{return mDependentObjects;}

const CVector< C_FLOAT64 > & CExperimentSet::getDependentObjectiveValues() const
{return mDependentObjectiveValues;}

const CVector< C_FLOAT64 > & CExperimentSet::getDependentRMS() const
{return mDependentRMS;}

const CVector< C_FLOAT64 > & CExperimentSet::getDependentErrorMean() const
{return mDependentErrorMean;}

const CVector< C_FLOAT64 > & CExperimentSet::getDependentErrorMeanSD() const
{return mDependentErrorMeanSD;}

const CVector< size_t > & CExperimentSet::getDependentDataCount() const
{return mDependentDataCount;}

size_t CExperimentSet::getExperimentCount() const
{return size() - mNonExperiments;}

CExperiment * CExperimentSet::addExperiment(const CExperiment & experiment)
{
  // We need to make sure that the experiment name is unique.
  std::string name = experiment.getObjectName();

  int i = 0;

  while (getParameter(name))
    {
      i++;
      name = StringPrint("%s_%d", experiment.getObjectName().c_str(), i);
    }

  CExperiment * pExperiment = new CExperiment(experiment, NO_PARENT);
  pExperiment->setObjectName(name);
  addParameter(pExperiment);

  sort();

  return pExperiment;
}

void CExperimentSet::removeExperiment(const size_t & index)
{
  removeParameter(index + mNonExperiments);
}

CExperiment * CExperimentSet::getExperiment(const size_t & index)
{
  if (index >= mpExperiments->size())
    return NULL;

  return (*mpExperiments)[index + mNonExperiments];
}

const CExperiment * CExperimentSet::getExperiment(const size_t & index) const
{
  return (*mpExperiments)[index + mNonExperiments];
}

CExperiment * CExperimentSet::getExperiment(const std::string & name)
{
  return static_cast<CExperiment *>(getGroup(name));
}

const CExperiment * CExperimentSet::getExperiment(const std::string & name) const
{
  return static_cast<const CExperiment *>(getGroup(name));
}

bool CExperimentSet::hasDataForTaskType(const CTaskEnum::Task & type) const
{
  std::vector< CExperiment * >::const_iterator it = mpExperiments->begin() + mNonExperiments;
  std::vector< CExperiment * >::const_iterator end = mpExperiments->end();

  for (; it != end; ++it)
    {
      if ((*it)->getExperimentType() == type)
        {
          return true;
        }
    }

  return false;
}

const CTaskEnum::Task & CExperimentSet::getExperimentType(const size_t & index) const
{return getExperiment(index)->getExperimentType();}

const CMatrix< C_FLOAT64 > & CExperimentSet::getIndependentData(const size_t & index) const
{return getExperiment(index)->getIndependentData();}

const CMatrix< C_FLOAT64 > & CExperimentSet::getDependentData(const size_t & index) const
{return getExperiment(index)->getDependentData();}

size_t CExperimentSet::keyToIndex(const std::string & key) const
{
  const CExperiment * pExp = dynamic_cast<const CExperiment *>(CRootContainer::getKeyFactory()->get(key));

  if (!pExp) return C_INVALID_INDEX;

  size_t i, imax = size();

  for (i = 0; i < imax; i++)
    if (pExp == getExperiment(i)) return i;

  return C_INVALID_INDEX;
}

void CExperimentSet::sort()
{
  // First we make sure that all experiments are at the end of the group
  index_iterator it = beginIndex();
  index_iterator end = endIndex();

  index_iterator swapTarget = beginIndex();
  mNonExperiments = 0;

  for (; it != end; ++it)
    if (dynamic_cast< CExperiment * >(*it) == NULL)
      {
        if (it != swapTarget)
          swap(it, swapTarget);

        swapTarget++;
        mNonExperiments++;
      }

  // Now sort the experiments
  std::vector< CExperiment * >::iterator startSort = mpExperiments->begin() + mNonExperiments;
  std::vector< CExperiment * >::iterator endSort = mpExperiments->end();

  std::sort(startSort, endSort, &CExperiment::compare);

  return;
}

std::vector< std::string > CExperimentSet::getFileNames() const
{
  std::vector< std::string > List;
  std::string currentFile = "";

  std::vector< CExperiment * >::iterator it = mpExperiments->begin() + mNonExperiments;
  std::vector< CExperiment * >::iterator end = mpExperiments->end();

  for (; it != end; ++it)
    if (currentFile != (*it)->getFileName())
      {
        currentFile = (*it)->getFileName();
        List.push_back(currentFile);
      }

  return List;
}

size_t CExperimentSet::getDataPointCount() const
{
  size_t Count = 0;
  std::vector< CExperiment * >::iterator it = mpExperiments->begin() + mNonExperiments;
  std::vector< CExperiment * >::iterator end = mpExperiments->end();

  for (; it != end; ++it)
    Count += (*it)->getDependentData().numRows() * (*it)->getDependentData().numCols();

  return Count;
}

const size_t & CExperimentSet::getValidValueCount() const
{
  return mValidValueCount;
}

void CExperimentSet::fixBuild55()
{
  std::vector< CExperiment * >::iterator it = mpExperiments->begin() + mNonExperiments;
  std::vector< CExperiment * >::iterator end = mpExperiments->end();

  for (; it != end; ++it)
    {
      (*it)->fixBuild55();
    }

  return;
}

CCrossValidationSet::CCrossValidationSet(const CDataContainer * pParent,
    const std::string & name):
  CExperimentSet(name, pParent),
  mpWeight(NULL),
  mpThreshold(NULL)
{initializeParameter();}

CCrossValidationSet::CCrossValidationSet(const CCrossValidationSet & src,
    const CDataContainer * pParent):
  CExperimentSet(src, pParent),
  mpWeight(NULL),
  mpThreshold(NULL)
{initializeParameter();}

CCrossValidationSet::CCrossValidationSet(const CCopasiParameterGroup & group,
    const CDataContainer * pParent):
  CExperimentSet(group, pParent),
  mpWeight(NULL),
  mpThreshold(NULL)
{initializeParameter();}

CCrossValidationSet::~CCrossValidationSet() {}

void CCrossValidationSet::setWeight(const C_FLOAT64 & weight)
{
  if (weight < 0.0)
    *mpWeight = 0.0;
  else if (weight > 1.0)
    *mpWeight = 1.0;
  else
    *mpWeight = weight;
}

const C_FLOAT64 & CCrossValidationSet::getWeight() const
{return *mpWeight;}

void CCrossValidationSet::setThreshold(const unsigned C_INT32 & threshold)
{*mpThreshold = threshold;}

const unsigned C_INT32 & CCrossValidationSet::getThreshold() const
{return *mpThreshold;}

void CCrossValidationSet::initializeParameter()
{
  mpWeight = assertParameter("Weight", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0);
  mpThreshold = assertParameter("Threshold", CCopasiParameter::Type::UINT, (unsigned C_INT32) 5);

  elevateChildren();
}
