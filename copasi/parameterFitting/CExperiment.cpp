// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

#include <fstream>
#include <limits>
#include <cmath>

#include "copasi.h"

#include "CExperiment.h"
#include "CExperimentObjectMap.h"
#include "CFitTask.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "utilities/CTableCell.h"
#include "utilities/CSort.h"
#include "utilities/CDirEntry.h"
#include "utilities/utility.h"
#include "commandline/CLocaleString.h"

std::istream & skipLine(std::istream & in);

#define InvalidIndex std::numeric_limits< unsigned C_INT32 >::max()

const std::string CExperiment::TypeName[] =
{
  "ignored",
  "independent",
  "dependent",
  "Time",
  ""
};

const char* CExperiment::XMLType[] =
{
  "ignored",
  "independent",
  "dependent",
  "time",
  NULL
};

const std::string CExperiment::WeightMethodName[] =
{
  "Mean",
  "Mean Square",
  "Standard Deviation",
  "Value Scaling",
  ""
};

const char* CExperiment::WeightMethodType[] =
{
  "Mean",
  "MeanSquare",
  "StandardDeviation",
  "ValueScaling",
  NULL
};

CExperiment::CExperiment(const CCopasiContainer * pParent,
                         const std::string & name):
  CCopasiParameterGroup(name, pParent),
  mpFileName(NULL),
  mpFirstRow(NULL),
  mpLastRow(NULL),
  mpTaskType(NULL),
  mpNormalizeWeightsPerExperiment(NULL),
  mpSeparator(NULL),
  mpWeightMethod(NULL),
  mpRowOriented(NULL),
  mpHeaderRow(NULL),
  mpNumColumns(NULL),
  mColumnName(),
  mpObjectMap(NULL),
  mDataTime(0),
  mDataIndependent(0, 0),
  mDataDependent(0, 0),
  mScale(0, 0),
  mMissingData(false),
  mMeans(0),
  mColumnScale(0),
  mDefaultColumnScale(0),
  mDependentValues(0),
  mIndependentUpdateMethods(0),
  mRefreshMethods(),
  mIndependentObjects(),
  mIndependentValues(0),
  mNumDataRows(0),
  mpDataDependentCalculated(NULL),
  mMean(0),
  mMeanSD(0),
  mObjectiveValue(0),
  mRMS(0),
  mRowObjectiveValue(0),
  mRowRMS(0),
  mColumnObjectiveValue(0),
  mColumnRMS(0),
  mColumnValidValueCount(0),
  mDependentObjects(),
  mFittingPoints("Fitted Points", this),
  mExtendedTimeSeries(0),
  mStorageIt(NULL),
  mExtendedTimeSeriesSize(0)
{
  mStorageIt = mExtendedTimeSeries.array();

  initializeParameter();
}

CExperiment::CExperiment(const CExperiment & src,
                         const CCopasiContainer * pParent):
  CCopasiParameterGroup(src, static_cast< const CCopasiContainer * >((pParent != NULL) ? pParent : src.getObjectDataModel())),
  mpFileName(NULL),
  mpFirstRow(NULL),
  mpLastRow(NULL),
  mpTaskType(NULL),
  mpNormalizeWeightsPerExperiment(NULL),
  mpSeparator(NULL),
  mpWeightMethod(NULL),
  mpRowOriented(NULL),
  mpHeaderRow(NULL),
  mpNumColumns(NULL),
  mColumnName(src.mColumnName),
  mpObjectMap(NULL),
  mDataTime(src.mDataTime),
  mDataIndependent(src.mDataIndependent),
  mDataDependent(src.mDataDependent),
  mScale(src.mScale),
  mMissingData(src.mMissingData),
  mMeans(src.mMeans),
  mColumnScale(src.mColumnScale),
  mDefaultColumnScale(src.mDefaultColumnScale),
  mDependentValues(src.mDependentValues),
  mIndependentUpdateMethods(src.mIndependentUpdateMethods),
  mRefreshMethods(src.mRefreshMethods),
  mIndependentObjects(src.mIndependentObjects),
  mIndependentValues(src.mIndependentValues),
  mNumDataRows(src.mNumDataRows),
  mpDataDependentCalculated(src.mpDataDependentCalculated),
  mMean(src.mMean),
  mMeanSD(src.mMeanSD),
  mObjectiveValue(0),
  mRMS(src.mRMS),
  mRowObjectiveValue(src.mRowObjectiveValue),
  mRowRMS(src.mRowRMS),
  mColumnObjectiveValue(src.mColumnObjectiveValue),
  mColumnRMS(src.mColumnRMS),
  mColumnValidValueCount(src.mColumnValidValueCount),
  mDependentObjects(src.mDependentObjects),
  mFittingPoints(src.mFittingPoints, this),
  mExtendedTimeSeries(src.mExtendedTimeSeries),
  mStorageIt(src.mStorageIt),
  mExtendedTimeSeriesSize(src.mExtendedTimeSeriesSize)

{
  mStorageIt = mExtendedTimeSeries.array() + (src.mStorageIt - src.mExtendedTimeSeries.array());

  initializeParameter();
}

CExperiment::CExperiment(const CCopasiParameterGroup & group,
                         const CCopasiContainer * pParent):
  CCopasiParameterGroup(group, static_cast< const CCopasiContainer * >((pParent != NULL) ? pParent : group.getObjectDataModel())),
  mpFileName(NULL),
  mpFirstRow(NULL),
  mpLastRow(NULL),
  mpTaskType(NULL),
  mpNormalizeWeightsPerExperiment(NULL),
  mpSeparator(NULL),
  mpWeightMethod(NULL),
  mpRowOriented(NULL),
  mpHeaderRow(NULL),
  mpNumColumns(NULL),
  mColumnName(),
  mpObjectMap(NULL),
  mDataTime(0),
  mDataIndependent(0, 0),
  mDataDependent(0, 0),
  mScale(0, 0),
  mMissingData(false),
  mMeans(0),
  mColumnScale(0),
  mDefaultColumnScale(0),
  mDependentValues(0),
  mIndependentUpdateMethods(0),
  mRefreshMethods(),
  mIndependentObjects(),
  mIndependentValues(0),
  mNumDataRows(0),
  mpDataDependentCalculated(NULL),
  mMean(0),
  mMeanSD(0),
  mObjectiveValue(0),
  mRMS(0),
  mRowObjectiveValue(0),
  mRowRMS(0),
  mColumnObjectiveValue(0),
  mColumnRMS(0),
  mColumnValidValueCount(0),
  mDependentObjects(),
  mFittingPoints("Fitted Points", this),
  mExtendedTimeSeries(0),
  mStorageIt(NULL),
  mExtendedTimeSeriesSize(0)
{
  mStorageIt = mExtendedTimeSeries.array();

  initializeParameter();
}

CExperiment::~CExperiment() {}

CExperiment & CExperiment::operator = (const CExperiment & rhs)
{
  std::string Key = *getValue("Key").pKEY;

  clear();

  *static_cast<CCopasiParameterGroup *>(this) =
    *static_cast<const CCopasiParameterGroup *>(&rhs);

  setValue("Key", Key);

  mpFileName = getValue("File Name").pFILE;
  mpFirstRow = getValue("First Row").pUINT;
  mpLastRow = getValue("Last Row").pUINT;
  mpTaskType = (CCopasiTask::Type *) getValue("Experiment Type").pUINT;
  mpNormalizeWeightsPerExperiment = getValue("Normalize Weights per Experiment").pBOOL;
  mpSeparator = getValue("Separator").pSTRING;
  mpWeightMethod = (WeightMethod *) getValue("Weight Method").pUINT;
  mpRowOriented = getValue("Data is Row Oriented").pBOOL;
  mpHeaderRow = getValue("Row containing Names").pUINT;
  mpNumColumns = getValue("Number of Columns").pUINT;

  elevateChildren();

  return *this;
}

void CExperiment::initializeParameter()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
  mKey = CCopasiRootContainer::getKeyFactory()->add("Experiment", this);

  assertParameter("Key", CCopasiParameter::KEY, mKey)->setValue(mKey);

  mpFileName =
    assertParameter("File Name", CCopasiParameter::FILE, std::string(""))->getValue().pFILE;
  mpFirstRow =
    assertParameter("First Row", CCopasiParameter::UINT, (unsigned C_INT32) InvalidIndex)->getValue().pUINT;
  mpLastRow =
    assertParameter("Last Row", CCopasiParameter::UINT, (unsigned C_INT32) InvalidIndex)->getValue().pUINT;
  mpTaskType = (CCopasiTask::Type *)
               assertParameter("Experiment Type", CCopasiParameter::UINT, (unsigned C_INT32) CCopasiTask::unset)->getValue().pUINT;

  mpNormalizeWeightsPerExperiment =
    assertParameter("Normalize Weights per Experiment", CCopasiParameter::BOOL, true)->getValue().pBOOL;

  mpSeparator =
    assertParameter("Separator", CCopasiParameter::STRING, std::string("\t"))->getValue().pSTRING;
  mpWeightMethod = (WeightMethod *)
                   assertParameter("Weight Method", CCopasiParameter::UINT, (unsigned C_INT32) MEAN_SQUARE)->getValue().pUINT;
  mpRowOriented =
    assertParameter("Data is Row Oriented", CCopasiParameter::BOOL, (bool) true)->getValue().pBOOL;
  mpHeaderRow =
    assertParameter("Row containing Names", CCopasiParameter::UINT, (unsigned C_INT32) InvalidIndex)->getValue().pUINT;
  mpNumColumns =
    assertParameter("Number of Columns", CCopasiParameter::UINT, (unsigned C_INT32) 0)->getValue().pUINT;

  assertGroup("Object Map");

  // Old files have a typo in the name of the separator parameter.
  CCopasiParameter * pParameter = getParameter("Seperator");

  if (pParameter != NULL)
    {
      *mpSeparator =  *pParameter->getValue().pSTRING;
      removeParameter("Seperator");
    }

  elevateChildren();
}

bool CExperiment::elevateChildren()
{
  mpObjectMap =
    elevate<CExperimentObjectMap, CCopasiParameterGroup>(getGroup("Object Map"));

  if (!mpObjectMap) return false;

  CCopasiParameterGroup *pGroup = getGroup("Column Role");

  if (pGroup) // We have an old data format
    {
      size_t i, imax = pGroup->size();
      CExperimentObjectMap Roles;
      Roles.setNumCols(imax);

      for (i = 0; i < imax; i++)
        {
          Roles.setRole(i, *(Type *) pGroup->getValue(StringPrint("%d", i)).pUINT);
          Roles.setObjectCN(i, mpObjectMap->getObjectCN(i));
        }

      mpObjectMap->clear();
      *mpObjectMap = Roles;
      mpObjectMap =
        elevate<CExperimentObjectMap, CCopasiParameterGroup>(getGroup("Object Map"));

      removeParameter("Column Role");

      *mpWeightMethod = SD;
    }

  updateFittedPoints();

  return true;
}

void CExperiment::updateFittedPoints()
{
  size_t i, imax = mpObjectMap->size();

  mFittingPoints.clear();
  CFittingPoint * pPoint;

  for (i = 0; i < imax; i++)
    if (mpObjectMap->getRole(i) == dependent)
      {
        pPoint = new CFittingPoint(mpObjectMap->getObjectCN(i));
        mFittingPoints.add(pPoint, true);
      }
}

void CExperiment::updateFittedPointValues(const size_t & index, bool includeSimulation)
{
  CCopasiVector< CFittingPoint >::iterator it = mFittingPoints.begin();
  CCopasiVector< CFittingPoint >::iterator end = mFittingPoints.end();

  if (index >= mNumDataRows ||
      mpDataDependentCalculated == NULL)
    {
      for (; it != end; ++it)
        (*it)->setValues(std::numeric_limits<C_FLOAT64>::quiet_NaN(),
                         std::numeric_limits<C_FLOAT64>::quiet_NaN(),
                         std::numeric_limits<C_FLOAT64>::quiet_NaN(),
                         std::numeric_limits<C_FLOAT64>::quiet_NaN());

      return;
    }

  C_FLOAT64 Independent;

  if (*mpTaskType == CCopasiTask::timeCourse)
    Independent = mDataTime[index];
  else
    Independent = (C_FLOAT64) index;

  C_FLOAT64 Residual;

  C_FLOAT64 * pDataDependentCalculated =
    mpDataDependentCalculated + mDataDependent.numCols() * index;
  C_FLOAT64 * pDataDependent = mDataDependent[index];
  C_FLOAT64 * pScale = mScale[index];

  for (; it != end; ++it, ++pScale, ++pDataDependentCalculated, ++pDataDependent)
    {
#ifdef COPASI_PARAMETERFITTING_RESIDUAL_SCALING
      Residual = (*pDataDependentCalculated - *pDataDependent) / (*pDataDependentCalculated > 1 ? *pDataDependentCalculated : 1.0);
#else
      Residual = (*pDataDependentCalculated - *pDataDependent) * *pScale;
#endif

      (*it)->setValues(Independent,
                       *pDataDependent,
                       includeSimulation ? *pDataDependentCalculated : std::numeric_limits<C_FLOAT64>::quiet_NaN(),
                       Residual);
    }

  return;
}

void CExperiment::updateFittedPointValuesFromExtendedTimeSeries(const size_t & index)
{
  CCopasiVector< CFittingPoint >::iterator it = mFittingPoints.begin();
  CCopasiVector< CFittingPoint >::iterator end = mFittingPoints.end();

  if (index >= extendedTimeSeriesSize())
    {
      for (; it != end; ++it)
        (*it)->setValues(std::numeric_limits<C_FLOAT64>::quiet_NaN(),
                         std::numeric_limits<C_FLOAT64>::quiet_NaN(),
                         std::numeric_limits<C_FLOAT64>::quiet_NaN(),
                         std::numeric_limits<C_FLOAT64>::quiet_NaN());

      return;
    }

  size_t i;

  for (i = 1; it != end; ++it, ++i)
    {
      (*it)->setValues(mExtendedTimeSeries[index * (mDataDependent.numCols() + 1)],
                       std::numeric_limits<C_FLOAT64>::quiet_NaN(),
                       mExtendedTimeSeries[index * (mDataDependent.numCols() + 1) + i] ,
                       std::numeric_limits<C_FLOAT64>::quiet_NaN());
    }
}

C_FLOAT64 CExperiment::sumOfSquares(const size_t & index,
                                    C_FLOAT64 *& residuals) const
{
  C_FLOAT64 Residual;
  C_FLOAT64 s = 0.0;

  C_FLOAT64 const * pDataDependent = mDataDependent[index];
  C_FLOAT64 const * pEnd = pDataDependent + mDataDependent.numCols();
  C_FLOAT64 * const * ppDependentValues = mDependentValues.array();
  C_FLOAT64 const * pScale = mScale[index];

  std::vector< Refresh * >::const_iterator it = mRefreshMethods.begin();
  std::vector< Refresh * >::const_iterator end = mRefreshMethods.end();

  for (; it != end; ++it)
    (**it)();

  if (mMissingData)
    {
      if (residuals)
        for (; pDataDependent != pEnd;
             pDataDependent++, ppDependentValues++, pScale++, residuals++)
          {
            if (isnan(*pDataDependent))
              {
                // We ignore missing data, i.e., the residual is 0.
                *residuals = 0.0;
                continue;
              }

#ifdef COPASI_PARAMETERFITTING_RESIDUAL_SCALING
            *residuals = (*pDataDependent - **ppDependentValues) / std::max(1.0, **ppDependentValues);
#else
            *residuals = (*pDataDependent - **ppDependentValues) * *pScale;
#endif

            s += *residuals * *residuals;
          }
      else
        for (; pDataDependent != pEnd;
             pDataDependent++, ppDependentValues++, pScale++)
          {
            if (isnan(*pDataDependent)) continue;

#ifdef COPASI_PARAMETERFITTING_RESIDUAL_SCALING
            Residual = (*pDataDependent - **ppDependentValues) / std::max(1.0, **ppDependentValues);
#else
            Residual = (*pDataDependent - **ppDependentValues) * *pScale;
#endif

            s += Residual * Residual;
          }
    }
  else
    {
      if (residuals)
        for (; pDataDependent != pEnd;
             pDataDependent++, ppDependentValues++, pScale++, residuals++)
          {
#ifdef COPASI_PARAMETERFITTING_RESIDUAL_SCALING
            *residuals = (*pDataDependent - **ppDependentValues) / std::max(1.0, **ppDependentValues);
#else
            *residuals = (*pDataDependent - **ppDependentValues) * *pScale;
#endif

            s += *residuals * *residuals;
          }
      else
        for (; pDataDependent != pEnd;
             pDataDependent++, ppDependentValues++, pScale++)
          {

#ifdef COPASI_PARAMETERFITTING_RESIDUAL_SCALING
            Residual = (*pDataDependent - **ppDependentValues) / std::max(1.0, **ppDependentValues);
#else
            Residual = (*pDataDependent - **ppDependentValues) * *pScale;
#endif

            s += Residual * Residual;
          }
    }

  return s;
}

C_FLOAT64 CExperiment::sumOfSquaresStore(const size_t & index,
    C_FLOAT64 *& dependentValues)
{
  if (index == 0)
    mpDataDependentCalculated = dependentValues;

  C_FLOAT64 Residual;
  C_FLOAT64 s = 0.0;

  C_FLOAT64 const * pDataDependent = mDataDependent[index];
  C_FLOAT64 const * pEnd = pDataDependent + mDataDependent.numCols();
  C_FLOAT64 * const * ppDependentValues = mDependentValues.array();
  C_FLOAT64 const * pScale = mScale[index];

  std::vector< Refresh * >::const_iterator it = mRefreshMethods.begin();
  std::vector< Refresh * >::const_iterator end = mRefreshMethods.end();

  for (; it != end; ++it)
    (**it)();

  if (mMissingData)
    {
      for (; pDataDependent != pEnd;
           pDataDependent++, ppDependentValues++, pScale++, dependentValues++)
        {
          *dependentValues = **ppDependentValues;

          if (isnan(*pDataDependent)) continue;

#ifdef COPASI_PARAMETERFITTING_RESIDUAL_SCALING
          Residual = (*pDataDependent - *dependentValues) / std::max(1.0, *dependentValues);
#else
          Residual = (*pDataDependent - *dependentValues) * *pScale;
#endif

          s += Residual * Residual;
        }
    }
  else
    {
      for (; pDataDependent != pEnd;
           pDataDependent++, ppDependentValues++, pScale++, dependentValues++)
        {
          *dependentValues = **ppDependentValues;

#ifdef COPASI_PARAMETERFITTING_RESIDUAL_SCALING
          Residual = (*pDataDependent - *dependentValues) / std::max(1.0, *dependentValues);
#else
          Residual = (*pDataDependent - *dependentValues) * *pScale;
#endif

          s += Residual * Residual;
        }
    }

  return s;
}

void CExperiment::initExtendedTimeSeries(size_t s)
{
  mExtendedTimeSeriesSize = s;
  mExtendedTimeSeries.resize(s * (this->getDependentData().numCols() + 1)); //+1 for time
  mStorageIt = mExtendedTimeSeries.array();
}

void CExperiment::storeExtendedTimeSeriesData(C_FLOAT64 time)
{
  //first store time
  *mStorageIt = time; ++mStorageIt;

  //do all necessary refreshs
  std::vector< Refresh * >::const_iterator it = mRefreshMethods.begin();
  std::vector< Refresh * >::const_iterator end = mRefreshMethods.end();

  for (; it != end; ++it)
    (**it)();

  //store the calculated data
  C_FLOAT64 * const * ppDependentValues = mDependentValues.array();
  size_t  i, imax = mDataDependent.numCols();

  for (i = 0; i < imax; ++i, ++ppDependentValues, ++mStorageIt)
    *mStorageIt = **ppDependentValues;
}

size_t CExperiment::extendedTimeSeriesSize() const
{
  return mExtendedTimeSeriesSize;
}

bool CExperiment::calculateStatistics()
{
  C_FLOAT64 * pTime = NULL;
  C_FLOAT64 SavedTime = 0.0;

  if (*mpTaskType == CCopasiTask::timeCourse)
    {
      pTime = const_cast<C_FLOAT64 *>(&getObjectDataModel()->getModel()->getTime());
      SavedTime = *pTime;
    }

  size_t numRows = mDataDependent.numRows();
  size_t numCols = mDataDependent.numCols();

  // Overall statistic;
  mMean = 0.0;
  mMeanSD = 0.0;
  mObjectiveValue = 0.0;
  mRMS = 0.0;
  size_t ValidValueCount = 0;

  // per row statistic;
  mRowObjectiveValue.resize(numRows);
  mRowObjectiveValue = 0.0;
  mRowRMS.resize(numRows);
  mRowRMS = 0.0;
  CVector< size_t > RowCount;
  RowCount.resize(numRows);
  RowCount = 0;

  // per column statistic;
  mColumnObjectiveValue.resize(numCols);
  mColumnObjectiveValue = 0.0;
  mColumnRMS.resize(numCols);
  mColumnRMS = 0.0;
  mColumnValidValueCount.resize(numCols);
  mColumnValidValueCount = 0;

  size_t i, j;
  C_FLOAT64 Residual;

  if (mpDataDependentCalculated == NULL)
    return false;

  C_FLOAT64 * pDataDependentCalculated = mpDataDependentCalculated;
  C_FLOAT64 * pDataDependent = mDataDependent.array();
  C_FLOAT64 * pScale = mScale.array();

  for (i = 0; i < numRows; i++)
    {
      for (j = 0; j < numCols; j++, pDataDependentCalculated++, pDataDependent++, pScale++)
        {

#ifdef COPASI_PARAMETERFITTING_RESIDUAL_SCALING
          Residual = (*pDataDependentCalculated - *pDataDependent) * std::max(1.0, *pDataDependentCalculated);
#else
          Residual = (*pDataDependentCalculated - *pDataDependent) * *pScale;
#endif

          if (isnan(Residual)) continue;

          mMean += Residual;

          Residual = Residual * Residual;

          mObjectiveValue += Residual;
          ValidValueCount++;

          mRowObjectiveValue[i] += Residual;
          RowCount[i]++;

          mColumnObjectiveValue[j] += Residual;
          mColumnValidValueCount[j]++;
        }
    }

  if (ValidValueCount)
    {
      mMean /= ValidValueCount;
      mRMS = sqrt(mObjectiveValue / ValidValueCount);
    }
  else
    {
      mMean = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mRMS = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  for (i = 0; i < numRows; i++)
    {
      if (RowCount[i])
        mRowRMS[i] = sqrt(mRowObjectiveValue[i] / RowCount[i]);
      else
        mRowRMS[i] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  for (j = 0; j < numCols; j++)
    {
      if (mColumnValidValueCount[j])
        mColumnRMS[j] = sqrt(mColumnObjectiveValue[j] / mColumnValidValueCount[j]);
      else
        mColumnRMS[j] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  pDataDependentCalculated = mpDataDependentCalculated;
  pDataDependent = mDataDependent.array();
  pScale = mScale.array();

  for (i = 0; i < numRows; i++)
    {
      for (j = 0; j < numCols; j++, pDataDependentCalculated++, pDataDependent++, pScale++)
        {

#ifdef COPASI_PARAMETERFITTING_RESIDUAL_SCALING
          Residual = mMean - (*pDataDependentCalculated - *pDataDependent) / std::max(1.0, *pDataDependentCalculated);
#else
          Residual = mMean - (*pDataDependentCalculated - *pDataDependent) * *pScale;
#endif

          if (isnan(Residual)) continue;

          mMeanSD += Residual * Residual;
        }
    }

  if (ValidValueCount)
    mMeanSD = sqrt(mMeanSD / ValidValueCount);
  else
    mMeanSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  if (*mpTaskType == CCopasiTask::timeCourse) *pTime = SavedTime;

  return true;
}

bool CExperiment::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;

  if (!mpObjectMap->compile(listOfContainer))
    success = false;

  size_t LastMappedColumn = mpObjectMap->getLastColumn();
  const CVector< CCopasiObject * > & Objects = mpObjectMap->getMappedObjects();

  size_t i, imax = mpObjectMap->getLastNotIgnoredColumn();

  if (*mpNumColumns <= imax)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 4, imax + 1, *mpNumColumns + 1);
      return false; // More column types specified than we have data columns
    }

  if (LastMappedColumn < imax || LastMappedColumn == C_INVALID_INDEX)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 5, imax + 1);
      return false; // More column types specified than we have mapped columns
    }

  size_t IndependentCount = mDataIndependent.numCols();
  size_t DependentCount = mDataDependent.numCols();

  mDependentValues.resize(DependentCount);
  mIndependentUpdateMethods.resize(IndependentCount);
  mIndependentValues.resize(IndependentCount);
  mIndependentObjects.clear();
  mDependentObjects.clear();
  std::set< const CCopasiObject * > Dependencies;

  IndependentCount = 0;
  DependentCount = 0;

  bool TimeFound = false;

  for (i = 0; i <= imax; i++)
    switch (mpObjectMap->getRole(i))
      {
        case ignore:
          break;

        case independent:

          if (!Objects[i]) // Object not found
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 5, i + 1);
              return false;
            }

          if (!Objects[i]->isValueDbl())
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 6, Objects[i]->getObjectDisplayName().c_str(), i + 1);
              return false;
            }

          mIndependentObjects.insert(Objects[i]);
          mIndependentUpdateMethods[IndependentCount] =
            Objects[i]->getUpdateMethod();
          mIndependentValues[IndependentCount] =
            *(C_FLOAT64 *)Objects[i]->getValuePointer();
          // :TODO: do we have to check if getValuePointer() return a valid pointer?

          IndependentCount++;
          break;

        case dependent:

          if (!Objects[i]) // Object not found
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 5, i + 1);
              return false;
            }

          if (!Objects[i]->isValueDbl())
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 6, Objects[i]->getObjectDisplayName().c_str(), i + 1);
              return false;
            }

          mDependentValues[DependentCount] =
            (C_FLOAT64 *) Objects[i]->getValuePointer();
          // :TODO: do we have to check if getValuePointer() return a valid pointer?
          mDependentObjects[Objects[i]] = DependentCount;
          mColumnScale[DependentCount] = mpObjectMap->getScale(i);
          Dependencies.insert(Objects[i]->getValueObject());

          DependentCount++;
          break;

        case time:
          TimeFound = true;
          break;
      }

  /* We need to check whether a column is mapped to time */
  if (!TimeFound && *mpTaskType == CCopasiTask::timeCourse)
    success = false;

  // Allocation and initialization of statistical information
  size_t numRows = mDataDependent.numRows();
  size_t numCols = mDataDependent.numCols();

  // Overall statistic;
  mMean = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mMeanSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mObjectiveValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mRMS = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  // per row statistic;
  mRowObjectiveValue.resize(numRows);
  mRowObjectiveValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mRowRMS.resize(numRows);
  mRowRMS = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  // per column statistic;
  mColumnObjectiveValue.resize(numCols);
  mColumnObjectiveValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mColumnRMS.resize(numCols);
  mColumnRMS = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mColumnValidValueCount.resize(numCols);
  mColumnValidValueCount = std::numeric_limits<size_t>::quiet_NaN();

  CModel * pModel =
    dynamic_cast< CModel * >(getObjectDataModel()->ObjectFromName(listOfContainer, CCopasiObjectName("Model=" + CCopasiObjectName::escape(getObjectDataModel()->getModel()->getObjectName()))));

  mRefreshMethods = CCopasiObject::buildUpdateSequence(Dependencies, pModel->getUptoDateObjects());

  initializeScalingMatrix();

  return success;
}

bool CExperiment::read(std::istream & in,
                       size_t & currentLine)
{
  // Allocate for reading
  size_t i, imax = mpObjectMap->size();

  if (*mpNumColumns < imax)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 4, imax, *mpNumColumns);
      return false; // More column types specified than we have data columns
    }

  size_t IndependentCount = 0;
  size_t DependentCount = 0;
  size_t TimeCount = 0;
  size_t IgnoreCount = 0;

  for (i = 0; i < imax; i++)
    switch (mpObjectMap->getRole(i))
      {
        case ignore:
          IgnoreCount++;
          break;

        case independent:
          IndependentCount++;
          break;

        case dependent:
          DependentCount++;
          break;

        case time:
          TimeCount++;
          break;
      }

  mNumDataRows = *mpLastRow - *mpFirstRow +
                 ((*mpHeaderRow < *mpFirstRow || *mpLastRow < *mpHeaderRow) ? 1 : 0);

  mDataTime.resize(TimeCount ? mNumDataRows : 0);
  mDataIndependent.resize(mNumDataRows, IndependentCount);
  mDataDependent.resize(mNumDataRows, DependentCount);
  mpDataDependentCalculated = NULL;
  mColumnName.resize(IndependentCount + DependentCount + TimeCount);

  // resize the vectors for the statistics
  mMeans.resize(DependentCount);
  mColumnScale.resize(DependentCount);
  mDefaultColumnScale.resize(DependentCount);
  mColumnValidValueCount.resize(DependentCount);

  if (!TimeCount && *mpTaskType == CCopasiTask::timeCourse)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 3, getObjectName().c_str());
      return false;
    }

  if (DependentCount == 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 10, getObjectName().c_str());
      return false;
    }

  if (mNumDataRows == 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 9, getObjectName().c_str());
      return false;
    }

  CTableRow Row(*mpNumColumns, (*mpSeparator)[0]);
  const std::vector< CTableCell > & Cells = Row.getCells();

  size_t j;

  if (currentLine > *mpFirstRow) return false; // We are past our first line

  // forwind to our first line
  for (j = currentLine; j < *mpFirstRow && !in.fail(); j++)
    {
      skipLine(in);
      currentLine++;
    }

  for (j = 0; j < mNumDataRows && !in.fail(); j++, currentLine++)
    {
      in >> Row;

      if (currentLine == *mpHeaderRow)
        {
          j--;

          size_t Column = 0;

          for (i = 0; i < *mpNumColumns; i++)
            if (mpObjectMap->getRole(i) != ignore)
              mColumnName[Column++] = Cells[i].getName();

          continue;
        }

      IndependentCount = 0;
      DependentCount = 0;

      for (i = 0; i < imax; i++)
        {
          switch (mpObjectMap->getRole(i))
            {
              case ignore:
                break;

              case independent:

                if (!Cells[i].isValue())
                  {
                    CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 11,
                                   getObjectName().c_str(), currentLine, i + 1);
                    return false;
                  }

                mDataIndependent[j][IndependentCount++] =
                  Cells[i].getValue();
                break;

              case dependent:
                mDataDependent[j][DependentCount++] =
                  Cells[i].getValue();
                break;

              case time:

                if (!Cells[i].isValue())
                  {
                    CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 11,
                                   getObjectName().c_str(), currentLine, i + 1);
                    return false;
                  }

                mDataTime[j] = Cells[i].getValue();
                break;
            }
        }
    }

  if ((in.fail() && !in.eof()))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 8, mpFileName->c_str());
      return false;
    }

  if (j != mNumDataRows)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 7, mNumDataRows, j - 1);
      return false;
    }

  // If it is a time course this is the place to assert that it is sorted.
  if (*mpTaskType == CCopasiTask::timeCourse)
    {
      CVector<size_t> Pivot;
      sortWithPivot(mDataTime.array(), mDataTime.array() + mDataTime.size(), CompareDoubleWithNaN(), Pivot);

      mDataTime.applyPivot(Pivot);
      mDataIndependent.applyPivot(Pivot);
      mDataDependent.applyPivot(Pivot);

      for (mNumDataRows--; mNumDataRows != C_INVALID_INDEX; mNumDataRows--)
        if (!isnan(mDataTime[mNumDataRows])) break;

      mNumDataRows++;
    }

  return calculateWeights();
}

bool CExperiment::calculateWeights()
{
  // We need to calculate the means and the weights
  C_FLOAT64 MinWeight = std::numeric_limits< C_FLOAT64 >::max();

  size_t DependentCount = mMeans.size();
  CVector< C_FLOAT64 > MeanSquares(DependentCount);
  CVector< C_FLOAT64 > ColumnEpsilons(DependentCount);
  C_FLOAT64 * pColumnEpsilon;
  size_t i, j;

  mMeans = 0.0;
  MeanSquares = 0.0;
  ColumnEpsilons = std::numeric_limits< C_FLOAT64 >::infinity();

  mColumnValidValueCount = 0;
  mMissingData = false;

  // Calculate the means
  for (i = 0; i < mNumDataRows; i++)
    for (j = 0, pColumnEpsilon = ColumnEpsilons.array(); j < DependentCount; j++, pColumnEpsilon++)
      {
        C_FLOAT64 & Data = mDataDependent[i][j];

        if (!isnan(Data))
          {
            mColumnValidValueCount[j]++;
            mMeans[j] += Data;
            MeanSquares[j] += Data * Data;

            if (Data != 0.0 && fabs(Data) < *pColumnEpsilon)
              {
                *pColumnEpsilon = fabs(Data);
              }
          }
        else
          mMissingData = true;
      }

  // calculate the means;
  for (j = 0, pColumnEpsilon = ColumnEpsilons.array(); j < DependentCount; j++, pColumnEpsilon++)
    {
      if (*pColumnEpsilon == std::numeric_limits< C_FLOAT64 >::infinity())
        {
          // TODO CRITICAL We need to create a preference for this.
          *pColumnEpsilon = 1e8 * std::numeric_limits< C_FLOAT64 >::epsilon();
        }

      if (mColumnValidValueCount[j])
        {
          mMeans[j] /= mColumnValidValueCount[j];
          MeanSquares[j] /= mColumnValidValueCount[j];
        }
      else
        {
          // :TODO: We need to create an error message here to instruct the user
          // :TODO: to mark this column as ignored as it contains no data.
          mMeans[j] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
          MeanSquares[j] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
        }
    }

  for (i = 0; i < DependentCount; i++)
    {
      C_FLOAT64 & DefaultColumScale = mDefaultColumnScale[i];

      switch (*mpWeightMethod)
        {
          case SD:
            DefaultColumScale = MeanSquares[i] - mMeans[i] * mMeans[i];
            break;

          case MEAN:
            DefaultColumScale = mMeans[i] * mMeans[i];
            break;

          case MEAN_SQUARE:
            DefaultColumScale = MeanSquares[i];
            break;

          case VALUE_SCALING:
            DefaultColumScale = ColumnEpsilons[i] * ColumnEpsilons[i] * 1e-12;
            break;
        }

      if (DefaultColumScale < MinWeight) MinWeight = DefaultColumScale;
    }

  if (*mpNormalizeWeightsPerExperiment && *mpWeightMethod != VALUE_SCALING)
    {
      // We have to calculate the default weights
      for (i = 0; i < DependentCount; i++)
        mDefaultColumnScale[i] =
          (MinWeight + sqrt(std::numeric_limits< C_FLOAT64 >::epsilon()))
          / (mDefaultColumnScale[i] + sqrt(std::numeric_limits< C_FLOAT64 >::epsilon()));
    }

  return true;
}

const std::map< CCopasiObject *, size_t > & CExperiment::getDependentObjects() const
{return mDependentObjects;}

bool CExperiment::readColumnNames()
{
  mColumnName.resize(*mpNumColumns);

  if (*mpHeaderRow == InvalidIndex) return false;

  // Open the file
  std::ifstream in;
  in.open(CLocaleString::fromUtf8(getFileName()).c_str(), std::ios::binary);

  if (in.fail()) return false;

  // Forwind to header row.
  size_t i;

  for (i = 1; i < *mpHeaderRow && !in.fail(); i++)
    skipLine(in);

  // Read row
  CTableRow Row(*mpNumColumns, (*mpSeparator)[0]);
  const std::vector< CTableCell > & Cells = Row.getCells();
  in >> Row;

  if (in.fail() && !in.eof()) return false;

  for (i = 0; i < *mpNumColumns; i++)
    mColumnName[i] = Cells[i].getName();

  return true;
}

size_t CExperiment::guessColumnNumber() const
{
  size_t tmp, count = 0;

  std::ifstream in;
  in.open(CLocaleString::fromUtf8(getFileName()).c_str(), std::ios::binary);

  if (in.fail()) return false;

  // Forwind to first row.
  size_t i;

  for (i = 1; i < *mpFirstRow && !in.fail(); i++)
    skipLine(in);

  CTableRow Row(0, (*mpSeparator)[0]);

  for (i--; i < *mpLastRow; i++)
    if ((tmp = Row.guessColumnNumber(in, false)) > count)
      count = tmp;

  return count;
}

const std::vector< std::string > & CExperiment::getColumnNames() const
{return mColumnName;}

bool CExperiment::updateModelWithIndependentData(const size_t & index)
{
  size_t i, imax = mIndependentUpdateMethods.size();

  for (i = 0; i < imax; i++)
    (*mIndependentUpdateMethods[i])(mDataIndependent(index, i));

  return true;
}

bool CExperiment::restoreModelIndependentData()
{
  size_t i, imax = mIndependentUpdateMethods.size();

  for (i = 0; i < imax; i++)
    (*mIndependentUpdateMethods[i])(mIndependentValues[i]);

  return true;
}

const CCopasiTask::Type & CExperiment::getExperimentType() const
{return *mpTaskType;}

bool CExperiment::setExperimentType(const CCopasiTask::Type & type)
{
  switch (type)
    {
      case CCopasiTask::steadyState:
      case CCopasiTask::timeCourse:
        *mpTaskType = type;
        return true;
        break;

      default:
        break;
    }

  return false;
}

void CExperiment::setNormalizeWeightsPerExperiment(bool flag)
{
  *mpNormalizeWeightsPerExperiment = flag;
}

bool CExperiment::getNormalizeWeightsPerExperiment() const
{
  if (mpNormalizeWeightsPerExperiment)
    return *mpNormalizeWeightsPerExperiment;
  else
    return true;
}

const CVector< C_FLOAT64 > & CExperiment::getTimeData() const
{return mDataTime;}

const CMatrix< C_FLOAT64 > & CExperiment::getIndependentData() const
{return mDataIndependent;}

const CMatrix< C_FLOAT64 > & CExperiment::getDependentData() const
{return mDataDependent;}

const std::string & CExperiment::getFileName() const
{
  std::string * pFileName = const_cast<CExperiment *>(this)->mpFileName;

  if (CDirEntry::isRelativePath(*pFileName) &&
      !CDirEntry::makePathAbsolute(*pFileName,
                                   getObjectDataModel()->getFileName()))
    *pFileName = CDirEntry::fileName(*pFileName);

  return *mpFileName;
}

bool CExperiment::setFileName(const std::string & fileName)
{
  *mpFileName = fileName;
  return true;
}

CExperimentObjectMap & CExperiment::getObjectMap()
{return * mpObjectMap;}

const CCopasiVector< CFittingPoint > & CExperiment::getFittingPoints() const
{return mFittingPoints;}

const unsigned C_INT32 & CExperiment::getFirstRow() const
{return *mpFirstRow;}

bool CExperiment::setFirstRow(const unsigned C_INT32 & first)
{
  if (first > *mpLastRow ||
      (first == *mpLastRow && first == *mpHeaderRow)) return false;

  *mpFirstRow = first;
  return true;
}

const unsigned C_INT32 & CExperiment::getLastRow() const
{return *mpLastRow;}

bool CExperiment::setLastRow(const unsigned C_INT32 & last)
{
  if (*mpFirstRow > last ||
      (*mpFirstRow == last && last == *mpHeaderRow)) return false;

  *mpLastRow = last;
  return true;
}

const unsigned C_INT32 & CExperiment::getHeaderRow() const
{return *mpHeaderRow;}

bool CExperiment::setHeaderRow(const unsigned C_INT32 & header)
{
  if (header == *mpFirstRow && header == *mpLastRow) return false;

  *mpHeaderRow = header;
  return true;
}

const unsigned C_INT32 & CExperiment::getNumColumns() const
{return *mpNumColumns;}

bool CExperiment::setNumColumns(const unsigned C_INT32 & cols)
{
  *mpNumColumns = cols;
  return true;
}

size_t CExperiment::getNumDataRows() const
{return mNumDataRows;}

const std::string & CExperiment::getSeparator() const
{return *mpSeparator;}

bool CExperiment::setSeparator(const std::string & separator)
{
  *mpSeparator = separator;
  return true;
}

const CExperiment::WeightMethod & CExperiment::getWeightMethod() const
{return *mpWeightMethod;}

bool CExperiment::setWeightMethod(const CExperiment::WeightMethod & weightMethod)
{
  if (*mpWeightMethod == weightMethod) return true;

  // Reset to default weights
  *mpWeightMethod = weightMethod;
  std::vector< CCopasiParameter * >::iterator it = mpObjectMap->CCopasiParameter::getValue().pGROUP->begin();
  std::vector< CCopasiParameter * >::iterator end = mpObjectMap->CCopasiParameter::getValue().pGROUP->end();

  for (; it != end; ++ it)
    static_cast< CExperimentObjectMap::CDataColumn * >(*it)->setScale(std::numeric_limits<C_FLOAT64>::quiet_NaN());

  return true;
}

const bool & CExperiment::isRowOriented() const
{return *mpRowOriented;}

bool CExperiment::setIsRowOriented(const bool & isRowOriented)
{
  *mpRowOriented = isRowOriented;
  return true;
}

bool CExperiment::compare(const CExperiment * lhs,
                          const CExperiment * rhs)
{
  return (*lhs->mpFileName < *rhs->mpFileName ||
          (*lhs->mpFileName == *rhs->mpFileName &&
           *lhs->mpFirstRow < *rhs->mpFirstRow));
}

bool operator == (const CExperiment & lhs,
                  const CExperiment & rhs)
{
  std::string Key = *lhs.getValue("Key").pKEY;
  const_cast<CExperiment *>(&lhs)->setValue("Key", *rhs.getValue("Key").pKEY);

  bool Result =
    (*static_cast<const CCopasiParameterGroup *>(&lhs) ==
     *static_cast<const CCopasiParameterGroup *>(&rhs));

  const_cast<CExperiment *>(&lhs)->setValue("Key", Key);

  return Result;
}

void CExperiment::printResult(std::ostream * ostream) const
{
  std::ostream & os = *ostream;

  os << "File Name:\t" << getFileName() << std::endl;
  os << "Experiment:\t" << getObjectName() << std::endl;

  os << "Mean:\t" << mMean << std::endl;
  os << "Objective Value:\t" << mObjectiveValue << std::endl;
  os << "Root Mean Square:\t" << mRMS << std::endl;

  size_t i, imax = mNumDataRows;
  size_t j, jmax = mDataDependent.numCols();
  size_t k, kmax = mpObjectMap->getLastNotIgnoredColumn() + 1;

  const CVector<CCopasiObject *> & Objects =
    mpObjectMap->getMappedObjects();

  os << "Row\t";

  if (*mpTaskType == CCopasiTask::timeCourse)
    os << "Time\t";

  for (k = 0; k < kmax; k++)
    if (mpObjectMap->getRole(k) == CExperiment::dependent)
      {
        std::string Name;

        if (k < Objects.size() && Objects[k] != NULL)
          Name = Objects[k]->getObjectDisplayName();
        else
          Name = "unknown";

        os << Name << "(Data)\t";
        os << Name << "(Fit)\t";
        os << Name << "(Weighted Error)\t";
      }

  os << "Objective Value\tRoot Mean Square" << std::endl << std::endl;

  C_FLOAT64 * pDataDependentCalculated = mpDataDependentCalculated;

  if (pDataDependentCalculated)
    for (i = 0; i < imax; i++)
      {
        os << i + 1 << ".\t";

        if (*mpTaskType == CCopasiTask::timeCourse)
          os << mDataTime[i] << "\t";

        for (j = 0; j < jmax; j++, pDataDependentCalculated++)
          {
            os << mDataDependent(i, j) << "\t";
            os << *pDataDependentCalculated << "\t";
            os << mScale(i, j) *(*pDataDependentCalculated - mDataDependent(i, j)) << "\t";
          }

        os << mRowObjectiveValue[i] << "\t" << mRowRMS[i] << std::endl;
      }
  else
    for (i = 0; i < imax; i++)
      {
        os << i + 1 << ".\t";

        if (*mpTaskType == CCopasiTask::timeCourse)
          os << mDataTime[i] << "\t";

        for (j = 0; j < jmax; j++)
          {
            os << mDataDependent(i, j) << "\tNaN\tNaN\t";
          }

        if (i < mRowObjectiveValue.size())
          {
            os << mRowObjectiveValue[i] << "\t";
          }
        else
          {
            os << "NaN\t";
          }

        if (i < mRowRMS.size())
          {
            os << mRowRMS[i];
          }
        else
          {
            os << "NaN";
          }

        os << std::endl;
      }

  os << "Objective Value";

  if (*mpTaskType == CCopasiTask::timeCourse)
    os << "\t";

  for (j = 0; j < jmax; j++)
    {
      if (j < mColumnObjectiveValue.size())
        os << "\t\t\t" << mColumnObjectiveValue[j];
      else
        os << "\t\t\tNaN";
    }

  os << std::endl;

  os << "Root Mean Square";

  if (*mpTaskType == CCopasiTask::timeCourse)
    os << "\t";

  for (j = 0; j < jmax; j++)
    {
      if (j < mColumnRMS.size())
        os << "\t\t\t" << mColumnRMS[j];
      else
        os << "\t\t\tNaN";
    }

  os << std::endl;

  os << "Weight";

  if (*mpTaskType == CCopasiTask::timeCourse)
    os << "\t";

  for (j = 0; j < jmax; j++)
    {
      if (j < mColumnScale.size())
        os << "\t\t\t" << mColumnScale[j];
      else
        os << "\t\t\tNaN";
    }

  os << std::endl;

  return;
}

const C_FLOAT64 & CExperiment::getObjectiveValue() const
{return mObjectiveValue;}

const C_FLOAT64 & CExperiment::getRMS() const
{return mRMS;}

const C_FLOAT64 & CExperiment::getErrorMean() const
{return mMean;}

const C_FLOAT64 & CExperiment::getErrorMeanSD() const
{return mMeanSD;}

C_FLOAT64 CExperiment::getObjectiveValue(CCopasiObject *const& pObject) const
{
  std::map< CCopasiObject *, size_t >::const_iterator it
    = mDependentObjects.find(pObject);

  if (it != mDependentObjects.end())
    return mColumnObjectiveValue[it->second];
  else
    return std::numeric_limits<C_FLOAT64>::quiet_NaN();
}

C_FLOAT64 CExperiment::getDefaultScale(const CCopasiObject * const& pObject) const
{
  std::map< CCopasiObject *, size_t>::const_iterator it
    = mDependentObjects.find(const_cast<CCopasiObject*>(pObject));

  if (it == mDependentObjects.end())
    return std::numeric_limits<C_FLOAT64>::quiet_NaN();

  return mDefaultColumnScale[it->second];
}

C_FLOAT64 CExperiment::getRMS(CCopasiObject *const& pObject) const
{
  std::map< CCopasiObject *, size_t>::const_iterator it
    = mDependentObjects.find(pObject);

  if (it != mDependentObjects.end())
    return mColumnRMS[it->second];
  else
    return std::numeric_limits<C_FLOAT64>::quiet_NaN();
}

C_FLOAT64 CExperiment::getErrorSum(CCopasiObject *const& pObject) const
{
  std::map< CCopasiObject *, size_t>::const_iterator it
    = mDependentObjects.find(pObject);

  if (it == mDependentObjects.end() ||
      mpDataDependentCalculated == NULL)
    return std::numeric_limits<C_FLOAT64>::quiet_NaN();

  C_FLOAT64 Mean = 0;
  C_FLOAT64 Residual;
  size_t numRows = mDataDependent.numRows();
  size_t numCols = mDataDependent.numCols();

  const C_FLOAT64 *pDataDependentCalculated = mpDataDependentCalculated + it->second;
  const C_FLOAT64 *pEnd = pDataDependentCalculated + numRows * numCols;
  const C_FLOAT64 *pDataDependent = mDataDependent.array() + it->second;
  const C_FLOAT64 & Weight = sqrt(mColumnScale[it->second]);

  for (; pDataDependentCalculated != pEnd;
       pDataDependentCalculated += numCols, pDataDependent += numCols)
    {
      Residual = Weight * (*pDataDependentCalculated - *pDataDependent);

      if (isnan(Residual)) continue;

      Mean += Residual;
    }

  return Mean;
}

C_FLOAT64 CExperiment::getErrorMeanSD(CCopasiObject *const& pObject,
                                      const C_FLOAT64 & errorMean) const
{
  std::map< CCopasiObject *, size_t>::const_iterator it
    = mDependentObjects.find(pObject);

  if (it == mDependentObjects.end() ||
      mpDataDependentCalculated == NULL)
    return std::numeric_limits<C_FLOAT64>::quiet_NaN();

  C_FLOAT64 MeanSD = 0;
  C_FLOAT64 Residual;
  size_t numRows = mDataDependent.numRows();
  size_t numCols = mDataDependent.numCols();

  const C_FLOAT64 *pDataDependentCalculated = mpDataDependentCalculated + it->second;
  const C_FLOAT64 *pEnd = pDataDependentCalculated + numRows * numCols;
  const C_FLOAT64 *pDataDependent = mDataDependent.array() + it->second;
  const C_FLOAT64 *pScale = mScale.array() + it->second;

  for (; pDataDependentCalculated != pEnd;
       pDataDependentCalculated += numCols, pDataDependent += numCols)
    {

#ifdef COPASI_PARAMETERFITTING_RESIDUAL_SCALING
      Residual = errorMean - (*pDataDependentCalculated - *pDataDependent) / std::max(1.0, *pDataDependentCalculated);
#else
      Residual = errorMean - (*pDataDependentCalculated - *pDataDependent) * *pScale;
#endif

      if (isnan(Residual)) continue;

      MeanSD += Residual * Residual;
    }

  return MeanSD;
}

size_t CExperiment::getColumnValidValueCount(CCopasiObject *const& pObject) const
{
  std::map< CCopasiObject *, size_t>::const_iterator it
    = mDependentObjects.find(pObject);

  if (it != mDependentObjects.end())
    return mColumnValidValueCount[it->second];
  else
    return 0;
}

const std::set< const CCopasiObject * > & CExperiment::getIndependentObjects() const
{
  return mIndependentObjects;
}

void CExperiment::initializeScalingMatrix()
{
  mScale.resize(mDataDependent.numRows(), mDataDependent.numCols());

  // We need to initialize the scaling factors for the residuals
  C_FLOAT64 * pData = mDataDependent.array();
  C_FLOAT64 * pScale = mScale.array();
  C_FLOAT64 * pScaleEnd = pScale + mScale.size();

  C_FLOAT64 * pColumnScale = mColumnScale.array();
  C_FLOAT64 * pColumnScaleEnd = pColumnScale + mColumnScale.size();

  for (; pScale < pScaleEnd;)
    {
      for (pColumnScale = mColumnScale.array(); pColumnScale < pColumnScaleEnd; ++pColumnScale, ++pScale, ++pData)
        {
          switch (*mpWeightMethod)
            {
              case VALUE_SCALING:
                *pScale = 1.0 / std::max(fabs(*pData), *pColumnScale);
                break;

              default:
                *pScale = sqrt(*pColumnScale);
                break;
            }
        }
    }
}

void CExperiment::fixBuild55()
{
  mpObjectMap->fixBuild55();
}

/* CFittingPoint Implementation */

CFittingPoint::CFittingPoint(const std::string & name,
                             const CCopasiContainer * pParent):
  CCopasiContainer("Fitting Point", pParent, "Fitted Point"),
  mModelObjectCN(name),
  mIndependentValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
  mMeasuredValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
  mFittedValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
  mWeightedError(std::numeric_limits<C_FLOAT64>::quiet_NaN())
{initObjects();}

CFittingPoint::CFittingPoint(const CFittingPoint & src,
                             const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  mModelObjectCN(src.mModelObjectCN),
  mIndependentValue(src.mIndependentValue),
  mMeasuredValue(src.mMeasuredValue),
  mFittedValue(src.mFittedValue),
  mWeightedError(src.mWeightedError)
{initObjects();}

CFittingPoint::~CFittingPoint() {}

// virtual
std::string CFittingPoint::getObjectDisplayName(bool regular, bool richtext) const
{
  const CCopasiDataModel * pDataModel = this->getObjectDataModel();

  if (pDataModel == NULL)
    {
      return CCopasiContainer::getObjectDisplayName(regular, richtext);
    }

  const CCopasiObject * pObject = dynamic_cast< const CCopasiObject * >(pDataModel->getObject(mModelObjectCN));

  if (pObject == NULL)
    {
      return CCopasiContainer::getObjectDisplayName(regular, richtext);
    }

  return pObject->getObjectDisplayName(regular, richtext);
}

const std::string & CFittingPoint::getModelObjectCN() const
{
  return mModelObjectCN;
}

void CFittingPoint::setValues(const C_FLOAT64 & independent,
                              const C_FLOAT64 & measured,
                              const C_FLOAT64 & fitted,
                              const C_FLOAT64 & weightedError)
{
  mIndependentValue = independent;
  mMeasuredValue = measured;
  mFittedValue = fitted;
  mWeightedError = weightedError;
}

void CFittingPoint::initObjects()
{
  addObjectReference("Independent Value", mIndependentValue, CCopasiObject::ValueDbl);
  addObjectReference("Measured Value", mMeasuredValue, CCopasiObject::ValueDbl);
  addObjectReference("Fitted Value", mFittedValue, CCopasiObject::ValueDbl);
  addObjectReference("Weighted Error", mWeightedError, CCopasiObject::ValueDbl);
}

std::istream & skipLine(std::istream & in)
{
  char c;

  for (in.get(c); c != 0x0a && c != 0x0d; in.get(c))
    {
      if (in.fail() || in.eof()) break;
    }

  // Eat additional line break characters appearing on DOS and Mac text format;
  if ((c == 0x0d && in.peek() == 0x0a) ||  // DOS
      (c == 0x0a && in.peek() == 0x0d))   // Mac
    in.ignore(1);

  return in;
}
