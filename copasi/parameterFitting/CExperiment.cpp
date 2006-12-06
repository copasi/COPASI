/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperiment.cpp,v $
   $Revision: 1.49 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/06 16:46:55 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <fstream>
#include <limits>
#include <math.h>
#include <float.h>

#include "copasi.h"

#include "CExperiment.h"
#include "CExperimentObjectMap.h"
#include "CFitTask.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "utilities/CTableCell.h"
#include "utilities/CSort.h"
#include "utilities/CDirEntry.h"
#include "utilities/utility.h"

std::istream & skipLine(std::istream & in);

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
    ""
  };

const char* CExperiment::WeightMethodType[] =
  {
    "Mean",
    "MeanSquare",
    "StandardDeviation",
    NULL
  };

CExperiment::CExperiment(const std::string & name,
                         const CCopasiContainer * pParent):
    CCopasiParameterGroup(name, pParent),
    mpFileName(NULL),
    mpFirstRow(NULL),
    mpLastRow(NULL),
    mpTaskType(NULL),
    mpSeparator(NULL),
    mpRowOriented(NULL),
    mpHeaderRow(NULL),
    mpNumColumns(NULL),
    mColumnName(),
    mpObjectMap(NULL),
    mDataTime(0),
    mDataIndependent(0, 0),
    mDataDependent(0, 0),
    mMeans(0),
    mWeight(0),
    mDefaultWeight(0),
    mDependentValues(0),
    mIndependentUpdateMethods(0),
    mRefreshMethods(),
    mIndependentValues(0),
    mNumDataRows(0),
    mpDataDependentCalculated(NULL),
    mDependentObjects(),
    mFittingPoints("Fitted Points", this)
{initializeParameter();}

CExperiment::CExperiment(const CExperiment & src,
                         const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mpFileName(NULL),
    mpFirstRow(NULL),
    mpLastRow(NULL),
    mpTaskType(NULL),
    mpSeparator(NULL),
    mpRowOriented(NULL),
    mpHeaderRow(NULL),
    mpNumColumns(NULL),
    mColumnName(src.mColumnName),
    mpObjectMap(NULL),
    mDataTime(src.mDataTime),
    mDataIndependent(src.mDataIndependent),
    mDataDependent(src.mDataDependent),
    mMeans(src.mMeans),
    mWeight(src.mWeight),
    mDefaultWeight(src.mDefaultWeight),
    mDependentValues(src.mDependentValues),
    mIndependentUpdateMethods(src.mIndependentUpdateMethods),
    mRefreshMethods(src.mRefreshMethods),
    mIndependentValues(src.mIndependentValues),
    mNumDataRows(src.mNumDataRows),
    mpDataDependentCalculated(src.mpDataDependentCalculated),
    mDependentObjects(src.mDependentObjects),
    mFittingPoints(src.mFittingPoints, this)
{initializeParameter();}

CExperiment::CExperiment(const CCopasiParameterGroup & group,
                         const CCopasiContainer * pParent):
    CCopasiParameterGroup(group, pParent),
    mpFileName(NULL),
    mpFirstRow(NULL),
    mpLastRow(NULL),
    mpTaskType(NULL),
    mpSeparator(NULL),
    mpRowOriented(NULL),
    mpHeaderRow(NULL),
    mpNumColumns(NULL),
    mColumnName(),
    mpObjectMap(NULL),
    mDataTime(0),
    mDataIndependent(0, 0),
    mDataDependent(0, 0),
    mMeans(0),
    mWeight(0),
    mDefaultWeight(0),
    mDependentValues(0),
    mIndependentUpdateMethods(0),
    mRefreshMethods(),
    mIndependentValues(0),
    mNumDataRows(0),
    mpDataDependentCalculated(NULL),
    mDependentObjects(),
    mFittingPoints("Fitted Points", this)
{initializeParameter();}

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
  mpSeparator = getValue("Seperator").pSTRING;
  mpWeightMethod = (WeightMethod *) getValue("Weight Method").pUINT;
  mpRowOriented = getValue("Data is Row Oriented").pBOOL;
  mpHeaderRow = getValue("Row containing Names").pUINT;
  mpNumColumns = getValue("Number of Columns").pUINT;

  elevateChildren();

  return *this;
}

void CExperiment::initializeParameter()
{
  GlobalKeys.remove(mKey);
  mKey = GlobalKeys.add("Experiment", this);

  assertParameter("Key", CCopasiParameter::KEY, mKey)->setValue(mKey);

  mpFileName =
    assertParameter("File Name", CCopasiParameter::FILE, std::string(""))->getValue().pFILE;
  mpFirstRow =
    assertParameter("First Row", CCopasiParameter::UINT, (unsigned C_INT32) C_INVALID_INDEX)->getValue().pUINT;
  mpLastRow =
    assertParameter("Last Row", CCopasiParameter::UINT, (unsigned C_INT32) C_INVALID_INDEX)->getValue().pUINT;
  mpTaskType = (CCopasiTask::Type *)
               assertParameter("Experiment Type", CCopasiParameter::UINT, (unsigned C_INT32) CCopasiTask::unset)->getValue().pUINT;
  mpSeparator =
    assertParameter("Seperator", CCopasiParameter::STRING, std::string("\t"))->getValue().pSTRING;
  mpWeightMethod = (WeightMethod *)
                   assertParameter("Weight Method", CCopasiParameter::UINT, (unsigned C_INT32) MEAN_SQUARE)->getValue().pUINT;
  mpRowOriented =
    assertParameter("Data is Row Oriented", CCopasiParameter::BOOL, (bool) true)->getValue().pBOOL;
  mpHeaderRow =
    assertParameter("Row containing Names", CCopasiParameter::UINT, (unsigned C_INT32) C_INVALID_INDEX)->getValue().pUINT;
  mpNumColumns =
    assertParameter("Number of Columns", CCopasiParameter::UINT, (unsigned C_INT32) 0)->getValue().pUINT;

  assertGroup("Object Map");

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
      unsigned C_INT32 i, imax = pGroup->size();
      CExperimentObjectMap Roles;
      Roles.setNumCols(imax);

      for (i = 0; i < imax; i++)
        {
          Roles.setRole(i, * (Type *) pGroup->getValue(StringPrint("%d", i)).pUINT);
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
  unsigned C_INT32 i, imax = mpObjectMap->size();

  mFittingPoints.resize(0);
  CFittingPoint * pPoint;

  for (i = 0; i < imax; i++)
    if (mpObjectMap->getRole(i) == dependent)
      {
        pPoint = new CFittingPoint(mpObjectMap->getObjectCN(i));
        mFittingPoints.add(pPoint, true);
      }
}

void CExperiment::updateFittedPointValues(const unsigned C_INT32 & index)
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
    Independent = index;

  C_FLOAT64 Residual;

  C_FLOAT64 * pDataDependentCalculated =
    mpDataDependentCalculated + mDataDependent.numCols() * index;
  C_FLOAT64 * pDataDependent = mDataDependent[index];
  C_FLOAT64 * pWeight = mWeight.array();

  for (; it != end; ++it, ++pWeight, ++pDataDependentCalculated, ++pDataDependent)
    {
      Residual = *pWeight * (*pDataDependentCalculated - *pDataDependent);
      (*it)->setValues(Independent,
                       *pDataDependent,
                       *pDataDependentCalculated,
                       Residual);
    }

  return;
}

C_FLOAT64 CExperiment::sumOfSquares(const unsigned C_INT32 & index,
                                    C_FLOAT64 *& residuals) const
  {
    C_FLOAT64 Residual;
    C_FLOAT64 s = 0.0;

    C_FLOAT64 const * pDataDependent = mDataDependent[index];
    C_FLOAT64 const * pEnd = pDataDependent + mDataDependent.numCols();
    C_FLOAT64 * const * ppDependentValues = mDependentValues.array();
    C_FLOAT64 const * pWeight = mWeight.array();

    std::vector< Refresh * >::const_iterator it = mRefreshMethods.begin();
    std::vector< Refresh * >::const_iterator end = mRefreshMethods.end();

    for (; it != end; ++it)
      (**it)();

    if (mMissingData)
      {
        if (residuals)
          for (; pDataDependent != pEnd;
               pDataDependent++, ppDependentValues++, pWeight++, residuals++)
            {
              if (isnan(*pDataDependent)) continue;

              *residuals = (*pDataDependent - **ppDependentValues) * *pWeight;
              s += *residuals * *residuals;
            }
        else
          for (; pDataDependent != pEnd;
               pDataDependent++, ppDependentValues++, pWeight++)
            {
              if (isnan(*pDataDependent)) continue;

              Residual = (*pDataDependent - **ppDependentValues) * *pWeight;
              s += Residual * Residual;
            }
      }
    else
      {
        if (residuals)
          for (; pDataDependent != pEnd;
               pDataDependent++, ppDependentValues++, pWeight++, residuals++)
            {
              *residuals = (*pDataDependent - **ppDependentValues) * *pWeight;
              s += *residuals * *residuals;
            }
        else
          for (; pDataDependent != pEnd;
               pDataDependent++, ppDependentValues++, pWeight++)
            {
              Residual = (*pDataDependent - **ppDependentValues) * *pWeight;
              s += Residual * Residual;
            }
      }

    return s;
  }

C_FLOAT64 CExperiment::sumOfSquaresStore(const unsigned C_INT32 & index,
    C_FLOAT64 *& dependentValues)
{
  if (index == 0)
    mpDataDependentCalculated = dependentValues;

  C_FLOAT64 Residual;
  C_FLOAT64 s = 0.0;

  C_FLOAT64 const * pDataDependent = mDataDependent[index];
  C_FLOAT64 const * pEnd = pDataDependent + mDataDependent.numCols();
  C_FLOAT64 * const * ppDependentValues = mDependentValues.array();
  C_FLOAT64 const * pWeight = mWeight.array();

  std::vector< Refresh * >::const_iterator it = mRefreshMethods.begin();
  std::vector< Refresh * >::const_iterator end = mRefreshMethods.end();

  for (; it != end; ++it)
    (**it)();

  if (mMissingData)
    {
      for (; pDataDependent != pEnd;
           pDataDependent++, ppDependentValues++, pWeight++, dependentValues++)
        {
          *dependentValues = **ppDependentValues;
          if (isnan(*pDataDependent)) continue;

          Residual = (*pDataDependent - *dependentValues) * *pWeight;
          s += Residual * Residual;
        }
    }
  else
    {
      for (; pDataDependent != pEnd;
           pDataDependent++, ppDependentValues++, pWeight++, dependentValues++)
        {
          *dependentValues = **ppDependentValues;
          Residual = (*pDataDependent - *dependentValues) * *pWeight;
          s += Residual * Residual;
        }
    }
  return s;
}

bool CExperiment::calculateStatistics()
{
  CFitTask * pTask =
    dynamic_cast<CFitTask *>(getObjectAncestor("Task"));

  C_FLOAT64 * pTime;
  C_FLOAT64 SavedTime;
  if (*mpTaskType == CCopasiTask::timeCourse)
    {
      pTime = const_cast<C_FLOAT64 *>(&CCopasiDataModel::Global->getModel()->getTime());
      SavedTime = *pTime;
    }

  unsigned C_INT32 numRows = mDataDependent.numRows();
  unsigned C_INT32 numCols = mDataDependent.numCols();

  // Overall statistic;
  mMean = 0.0;
  mMeanSD = 0.0;
  mObjectiveValue = 0.0;
  mRMS = 0.0;
  unsigned C_INT32 Count = 0;

  // per row statistic;
  mRowObjectiveValue.resize(numRows);
  mRowObjectiveValue = 0.0;
  mRowRMS.resize(numRows);
  mRowRMS = 0.0;
  CVector< unsigned C_INT32 > RowCount;
  RowCount.resize(numRows);
  RowCount = 0;

  // per column statistic;
  mColumnObjectiveValue.resize(numCols);
  mColumnObjectiveValue = 0.0;
  mColumnRMS.resize(numCols);
  mColumnRMS = 0.0;
  mColumnCount.resize(numCols);
  mColumnCount = 0;

  unsigned C_INT32 i, j;
  C_FLOAT64 Residual;

  if (mpDataDependentCalculated == NULL)
    return false;

  C_FLOAT64 * pDataDependentCalculated = mpDataDependentCalculated;
  C_FLOAT64 * pDataDependent = mDataDependent.array();

  for (i = 0; i < numRows; i++)
    {
      for (j = 0; j < numCols; j++, pDataDependentCalculated++, pDataDependent++)
        {
          Residual = mWeight[j] * (*pDataDependentCalculated - *pDataDependent);

          if (isnan(Residual)) continue;

          mMean += Residual;

          Residual = Residual * Residual;

          mObjectiveValue += Residual;
          Count++;

          mRowObjectiveValue[i] += Residual;
          RowCount[i]++;

          mColumnObjectiveValue[j] += Residual;
          mColumnCount[j]++;
        }
    }

  if (Count)
    {
      mMean /= Count;
      mRMS = sqrt(mObjectiveValue / Count);
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
      if (mColumnCount[j])
        mColumnRMS[j] = sqrt(mColumnObjectiveValue[j] / mColumnCount[j]);
      else
        mColumnRMS[j] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  pDataDependentCalculated = mpDataDependentCalculated;
  pDataDependent = mDataDependent.array();

  for (i = 0, Count = 0; i < numRows; i++)
    {
      for (j = 0; j < numCols; j++, pDataDependentCalculated++, pDataDependent++)
        {
          Residual = mMean - mWeight[j] * (*pDataDependentCalculated - *pDataDependent);

          if (isnan(Residual)) continue;

          mMeanSD += Residual * Residual;

          Count++;
        }
    }

  if (Count)
    mMeanSD = sqrt(mMeanSD / Count);
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

  unsigned C_INT32 LastMappedColumn = mpObjectMap->getLastColumn();
  const CVector< CCopasiObject * > & Objects = mpObjectMap->getMappedObjects();

  unsigned C_INT32 i, imax = mpObjectMap->getLastNotIgnoredColumn();
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

  unsigned C_INT32 IndependentCount = mDataIndependent.numCols();
  unsigned C_INT32 DependentCount = mDataDependent.numCols();

  mDependentValues.resize(DependentCount);
  mIndependentUpdateMethods.resize(IndependentCount);
  mIndependentValues.resize(IndependentCount);
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
        mWeight[DependentCount] = sqrt(mpObjectMap->getWeight(i));
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
  unsigned C_INT32 numRows = mDataDependent.numRows();
  unsigned C_INT32 numCols = mDataDependent.numCols();

  // Overall statistic;
  mMean = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mMeanSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mObjectiveValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mRMS = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  // per row statistic;
  mRowObjectiveValue.resize(numRows);
  mRowObjectiveValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mRowRMS.resize(numRows);
  mRowRMS = std::numeric_limits<unsigned C_INT32>::quiet_NaN();

  // per column statistic;
  mColumnObjectiveValue.resize(numCols);
  mColumnObjectiveValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mColumnRMS.resize(numCols);
  mColumnRMS = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mColumnCount.resize(numCols);
  mColumnCount = std::numeric_limits<unsigned C_INT32>::quiet_NaN();

  CModel * pModel =
    dynamic_cast< CModel * >(CCopasiContainer::ObjectFromName(listOfContainer, CCopasiObjectName("Model=" + CCopasiDataModel::Global->getModel()->getObjectName())));

  mRefreshMethods = CCopasiObject::buildUpdateSequence(Dependencies, pModel);

  return success;
}

bool CExperiment::read(std::istream & in,
                       unsigned C_INT32 & currentLine)
{
  // Allocate for reading
  unsigned C_INT32 i, imax = mpObjectMap->size();
  if (*mpNumColumns < imax)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 4, imax, *mpNumColumns);
      return false; // More column types specified than we have data columns
    }

  unsigned C_INT32 IndependentCount = 0;
  unsigned C_INT32 DependentCount = 0;
  unsigned C_INT32 TimeCount = 0;
  unsigned C_INT32 IgnoreCount = 0;

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

  if (!TimeCount && *mpTaskType == CCopasiTask::timeCourse)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 3);
      return false;
    }

  if (DependentCount == 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 10, getObjectName().c_str());
      return false;
    }

  mNumDataRows = *mpLastRow - *mpFirstRow +
                 ((*mpHeaderRow < *mpFirstRow || *mpLastRow < *mpHeaderRow) ? 1 : 0);

  if (mNumDataRows == 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 9, getObjectName().c_str());
      return false;
    }

  mDataTime.resize(TimeCount ? mNumDataRows : 0);
  mDataIndependent.resize(mNumDataRows, IndependentCount);
  mDataDependent.resize(mNumDataRows, DependentCount);
  mpDataDependentCalculated = NULL;
  mColumnName.resize(IndependentCount + DependentCount + TimeCount);

  CTableRow Row(*mpNumColumns, (*mpSeparator)[0]);
  const std::vector< CTableCell > & Cells = Row.getCells();

  unsigned C_INT32 j;

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

          unsigned C_INT32 Column = 0;
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
              mDataIndependent[j][IndependentCount++] =
                Cells[i].getValue();
              break;

            case dependent:
              mDataDependent[j][DependentCount++] =
                Cells[i].getValue();
              break;

            case time:
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
      CVector<unsigned C_INT32> Pivot;
      sortWithPivot(mDataTime.array(), mDataTime.array() + mDataTime.size(), Pivot);

      mDataTime.applyPivot(Pivot);
      mDataIndependent.applyPivot(Pivot);
      mDataDependent.applyPivot(Pivot);

      for (mNumDataRows--; mNumDataRows != C_INVALID_INDEX; mNumDataRows--)
        if (!isnan(mDataTime[mNumDataRows])) break;

      mNumDataRows++;
    }

  // resize the vectors for the statistics
  mMeans.resize(DependentCount);
  mWeight.resize(DependentCount);
  mDefaultWeight.resize(DependentCount);

  return calculateWeights();
}

bool CExperiment::calculateWeights()
{
  // We need to calculate the means and the weights
  C_FLOAT64 MinWeight = DBL_MAX;

  unsigned C_INT32 DependentCount = mMeans.size();
  CVector< C_FLOAT64 > MeanSquares(DependentCount);
  CVector< unsigned C_INT32 > Counts(DependentCount);
  unsigned C_INT32 i, j;

  mMeans = 0.0;
  MeanSquares = 0.0;
  Counts = 0;
  mMissingData = false;

  // Calculate the means
  for (i = 0; i < mNumDataRows; i++)
    for (j = 0; j < DependentCount; j++)
      {
        C_FLOAT64 & Data = mDataDependent[i][j];
        if (!isnan(Data))
          {
            Counts[j]++;
            mMeans[j] += Data;
          }
        else
          mMissingData = true;
      }

  // calculate the means;
  for (j = 0; j < DependentCount; j++)
    {
      if (Counts[j])
        mMeans[j] /= Counts[j];
      else
        // :TODO: We need to create an error message here to instruct the user
        // :TODO: to mark this column as ignored as it contains no data.
        mMeans[j] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  // Guess missing dependent values
  for (j = 0; j < DependentCount; j++)
    {
      C_FLOAT64 & Mean = mMeans[j];
      C_FLOAT64 & MeanSquare = MeanSquares[j];

      for (i = 0; i < mNumDataRows; i++)
        {
          C_FLOAT64 & Data = mDataDependent[i][j];

          if (isnan(Data)) continue;

          MeanSquare += Data * Data;
        }

      MeanSquare /= Counts[j];
    }

  for (i = 0; i < DependentCount; i++)
    {
      C_FLOAT64 & DefaultWeight = mDefaultWeight[i];

      switch (*mpWeightMethod)
        {
        case SD:
          DefaultWeight = MeanSquares[i] - mMeans[i] * mMeans[i];
          break;

        case MEAN:
          DefaultWeight = fabs(mMeans[i]);
          break;

        case MEAN_SQUARE:
          DefaultWeight = sqrt(MeanSquares[i]);
          break;
        }

      if (DefaultWeight < MinWeight) MinWeight = DefaultWeight;
    }

  // We have to calculate the default weights
  for (i = 0; i < DependentCount; i++)
    mDefaultWeight[i] =
      (MinWeight + sqrt(DBL_EPSILON)) / (mDefaultWeight[i] + sqrt(DBL_EPSILON));

  return true;
}

const std::map< CCopasiObject *, unsigned C_INT32 > & CExperiment::getDependentObjects() const
{return mDependentObjects;}

bool CExperiment::readColumnNames()
{
  mColumnName.resize(*mpNumColumns);

  if (*mpHeaderRow == C_INVALID_INDEX) return false;

  // Open the file
  std::ifstream in;
  in.open(utf8ToLocale(getFileName()).c_str(), std::ios::binary);
  if (in.fail()) return false;

  // Forwind to header row.
  unsigned C_INT32 i;
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

unsigned C_INT32 CExperiment::guessColumnNumber() const
  {
    unsigned C_INT32 tmp, count = 0;

    std::ifstream in;
    in.open(utf8ToLocale(getFileName()).c_str(), std::ios::binary);
    if (in.fail()) return false;

    // Forwind to first row.
    unsigned C_INT32 i;
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

bool CExperiment::updateModelWithIndependentData(const unsigned C_INT32 & index)
{
  unsigned C_INT32 i, imax = mIndependentUpdateMethods.size();

  for (i = 0; i < imax; i++)
    (*mIndependentUpdateMethods[i])(mDataIndependent(index, i));

  return true;
}

bool CExperiment::restoreModelIndependentData()
{
  unsigned C_INT32 i, imax = mIndependentUpdateMethods.size();

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
                                     CCopasiDataModel::Global->getFileName()))
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

const unsigned C_INT32 CExperiment::getNumDataRows() const
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
    static_cast< CExperimentObjectMap::CDataColumn * >(*it)->setWeight(std::numeric_limits<C_FLOAT64>::quiet_NaN());

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

    unsigned i, imax = mNumDataRows;
    unsigned j, jmax = mDataDependent.numCols();
    unsigned k, kmax = mpObjectMap->getLastNotIgnoredColumn() + 1;

    const CVector<CCopasiObject *> & Objects =
      mpObjectMap->getMappedObjects();

    os << "Row\t";
    if (*mpTaskType == CCopasiTask::timeCourse)
      os << "Time\t";

    for (k = 0; k < kmax; k++)
      if (mpObjectMap->getRole(k) == CExperiment::dependent)
        {
          std::string Name;
          if (Objects[k])
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
              os << mWeight[j] * (*pDataDependentCalculated - mDataDependent(i, j)) << "\t";
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
          os << mRowObjectiveValue[i] << "\t" << mRowRMS[i] << std::endl;
        }

    os << "Objective Value";
    if (*mpTaskType == CCopasiTask::timeCourse)
      os << "\t";
    for (j = 0; j < jmax; j++)
      os << "\t\t\t" << mColumnObjectiveValue[j];
    os << std::endl;

    os << "Root Mean Square";
    if (*mpTaskType == CCopasiTask::timeCourse)
      os << "\t";
    for (j = 0; j < jmax; j++)
      os << "\t\t\t" << mColumnRMS[j];
    os << std::endl;

    os << "Weight";
    if (*mpTaskType == CCopasiTask::timeCourse)
      os << "\t";
    for (j = 0; j < jmax; j++)
      os << "\t\t\t" << mWeight[j];
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
    std::map< CCopasiObject *, unsigned C_INT32 >::const_iterator it
    = mDependentObjects.find(pObject);

    if (it != mDependentObjects.end())
      return mColumnObjectiveValue[it->second];
    else
      return std::numeric_limits<C_FLOAT64>::quiet_NaN();
  }

C_FLOAT64 CExperiment::getDefaultWeight(CCopasiObject * const& pObject) const
  {
    std::map< CCopasiObject *, unsigned C_INT32>::const_iterator it
    = mDependentObjects.find(pObject);

    if (it == mDependentObjects.end())
      return std::numeric_limits<C_FLOAT64>::quiet_NaN();

    return mDefaultWeight[it->second];
  }

C_FLOAT64 CExperiment::getRMS(CCopasiObject *const& pObject) const
  {
    std::map< CCopasiObject *, unsigned C_INT32>::const_iterator it
    = mDependentObjects.find(pObject);

    if (it != mDependentObjects.end())
      return mColumnRMS[it->second];
    else
      return std::numeric_limits<C_FLOAT64>::quiet_NaN();
  }

C_FLOAT64 CExperiment::getErrorMean(CCopasiObject *const& pObject) const
  {
    std::map< CCopasiObject *, unsigned C_INT32>::const_iterator it
    = mDependentObjects.find(pObject);

    if (it == mDependentObjects.end() ||
        mpDataDependentCalculated == NULL)
      return std::numeric_limits<C_FLOAT64>::quiet_NaN();

    C_FLOAT64 Mean = 0;
    C_FLOAT64 Residual;
    unsigned C_INT32 numRows = mDataDependent.numRows();
    unsigned C_INT32 numCols = mDataDependent.numCols();

    const C_FLOAT64 *pDataDependentCalculated = mpDataDependentCalculated + it->second;
    const C_FLOAT64 *pEnd = pDataDependentCalculated + numRows * numCols;
    const C_FLOAT64 *pDataDependent = mDataDependent.array() + it->second;
    const C_FLOAT64 & Weight = mWeight[it->second];

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
    std::map< CCopasiObject *, unsigned C_INT32>::const_iterator it
    = mDependentObjects.find(pObject);

    if (it == mDependentObjects.end() ||
        mpDataDependentCalculated == NULL)
      return std::numeric_limits<C_FLOAT64>::quiet_NaN();

    C_FLOAT64 MeanSD = 0;
    C_FLOAT64 Residual;
    unsigned C_INT32 numRows = mDataDependent.numRows();
    unsigned C_INT32 numCols = mDataDependent.numCols();

    const C_FLOAT64 *pDataDependentCalculated = mpDataDependentCalculated + it->second;
    const C_FLOAT64 *pEnd = pDataDependentCalculated + numRows * numCols;
    const C_FLOAT64 *pDataDependent = mDataDependent.array() + it->second;
    const C_FLOAT64 & Weight = mWeight[it->second];

    for (; pDataDependentCalculated != pEnd;
         pDataDependentCalculated += numCols, pDataDependent += numCols)
      {
        Residual = errorMean - Weight * (*pDataDependentCalculated - *pDataDependent);
        if (isnan(Residual)) continue;
        MeanSD += Residual * Residual;
      }

    return MeanSD;
  }

unsigned C_INT32 CExperiment::getCount(CCopasiObject *const& pObject) const
  {
    std::map< CCopasiObject *, unsigned C_INT32>::const_iterator it
    = mDependentObjects.find(pObject);

    if (it != mDependentObjects.end())
      return mColumnCount[it->second];
    else
      return 0;
  }

/* CFittingPoint Implementation */

CFittingPoint::CFittingPoint(const std::string & name,
                             const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Fitted Point"),
    mIndependentValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mMeasuredValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mFittedValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mWeightedError(std::numeric_limits<C_FLOAT64>::quiet_NaN())
{initObjects();}

CFittingPoint::CFittingPoint(const CFittingPoint & src,
                             const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mIndependentValue(src.mIndependentValue),
    mMeasuredValue(src.mMeasuredValue),
    mFittedValue(src.mFittedValue),
    mWeightedError(src.mWeightedError)
{initObjects();}

CFittingPoint::~CFittingPoint() {}

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
  if ((c == 0x0d && in.peek() == 0x0a) || // DOS
      (c == 0x0a && in.peek() == 0x0d))   // Mac
    in.ignore(1);

  return in;
}
