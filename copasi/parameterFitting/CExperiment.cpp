/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperiment.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/01 03:01:39 $
   End CVS Header */

#include <fstream>
#include <limits>
#include <math.h>
#include <float.h>

#include "copasi.h"

#include "CExperiment.h"
#include "CExperimentObjectMap.h"

#include "report/CKeyFactory.h"
#include "utilities/CTableCell.h"
#include "utilities/CSort.h"
#include "utilities/utility.h"

const std::string CExperiment::TypeName[] =
  {
    "ignored",
    "independent",
    "dependent",
    "Time"
  };

const char* CExperiment::XMLType[] =
  {
    "ignored",
    "independent",
    "dependent",
    "time",
    NULL
  };

CExperiment::CExperiment(const std::string & name,
                         const CCopasiContainer * pParent):
    CCopasiParameterGroup(name, pParent),
    mpFileName(NULL),
    mpFirstRow(NULL),
    mpTaskType(NULL),
    mpSeparator(NULL),
    mpRowOriented(NULL),
    mpNameRow(NULL),
    mpNumRows(NULL),
    mpNumColumns(NULL),
    mpColumnType(NULL),
    mColumnName(),
    mpObjectMap(NULL),
    mDataTime(0),
    mDataIndependent(0, 0),
    mDataDependent(0, 0),
    mMeans(0),
    mWeight(0),
    mDependentValues(0),
    mIndependentUpdateMethods(0)
{initializeParameter();}

CExperiment::CExperiment(const CExperiment & src,
                         const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mpFileName(NULL),
    mpFirstRow(NULL),
    mpTaskType(NULL),
    mpSeparator(NULL),
    mpRowOriented(NULL),
    mpNameRow(NULL),
    mpNumRows(NULL),
    mpNumColumns(NULL),
    mpColumnType(NULL),
    mColumnName(src.mColumnName),
    mpObjectMap(NULL),
    mDataTime(src.mDataTime),
    mDataIndependent(src.mDataIndependent),
    mDataDependent(src.mDataDependent),
    mMeans(src.mMeans),
    mWeight(src.mWeight),
    mDependentValues(src.mDependentValues),
    mIndependentUpdateMethods(src.mIndependentUpdateMethods)
{initializeParameter();}

CExperiment::CExperiment(const CCopasiParameterGroup & group,
                         const CCopasiContainer * pParent):
    CCopasiParameterGroup(group, pParent),
    mpFileName(NULL),
    mpFirstRow(NULL),
    mpTaskType(NULL),
    mpSeparator(NULL),
    mpRowOriented(NULL),
    mpNameRow(NULL),
    mpNumRows(NULL),
    mpNumColumns(NULL),
    mpColumnType(NULL),
    mColumnName(),
    mpObjectMap(NULL),
    mDataTime(0),
    mDataIndependent(0, 0),
    mDataDependent(0, 0),
    mMeans(0),
    mWeight(0),
    mDependentValues(0),
    mIndependentUpdateMethods(0)
{initializeParameter();}

CExperiment::~CExperiment() {}

void CExperiment::initializeParameter()
{
  GlobalKeys.remove(mKey);
  mKey = GlobalKeys.add("Experiment", this);

  assertParameter("Key", CCopasiParameter::KEY, mKey)->setValue(mKey);

  mpFileName =
    assertParameter("File Name", CCopasiParameter::STRING, std::string(""))->getValue().pSTRING;
  mpFirstRow =
    assertParameter("Position in File", CCopasiParameter::UINT, (unsigned C_INT32) C_INVALID_INDEX)->getValue().pUINT;
  mpTaskType = (CCopasiTask::Type *)
               assertParameter("Experiment Type", CCopasiParameter::UINT, (unsigned C_INT32) CCopasiTask::unset)->getValue().pUINT;
  mpSeparator =
    assertParameter("Seperator", CCopasiParameter::STRING, std::string("\t"))->getValue().pSTRING;
  mpRowOriented =
    assertParameter("Data is Row Oriented", CCopasiParameter::BOOL, (bool) true)->getValue().pBOOL;
  mpNameRow =
    assertParameter("Row containing Names", CCopasiParameter::UINT, (unsigned C_INT32) C_INVALID_INDEX)->getValue().pUINT;
  mpNumRows =
    assertParameter("Number of Rows", CCopasiParameter::UINT, (unsigned C_INT32) 0)->getValue().pUINT;
  mpNumColumns =
    assertParameter("Number of Columns", CCopasiParameter::UINT, (unsigned C_INT32) 0)->getValue().pUINT;

  mpColumnType = assertGroup("Column Role");
  assertGroup("Object Map");

  elevateChildren();
}

bool CExperiment::elevateChildren()
{
  mpColumnType =
    elevate<CCopasiParameterGroup, CCopasiParameterGroup>(mpColumnType);
  if (!mpColumnType) return false;

  mpObjectMap =
    elevate<CExperimentObjectMap, CCopasiParameterGroup>(getGroup("Object Map"));
  if (!mpObjectMap) return false;

  return true;
}

C_FLOAT64 CExperiment::sumOfSquares(const unsigned C_INT32 & index)
{
  C_FLOAT64 s = 0.0;

  unsigned C_INT32 i , imax = mDataDependent.numCols();

  for (i = 0; i < imax; i++)
    s += pow(mDataDependent(index, i) - *mDependentValues[i], 2) * mWeight[i];

  return s;
}

bool CExperiment::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;

  if (!mpObjectMap->compile(listOfContainer))
    success = false;

  unsigned C_INT32 LastMappedColumn = mpObjectMap->getLastColumn();
  const CVector< CCopasiObject * > & Objects = mpObjectMap->getMappedObjects();

  unsigned C_INT32 i, imax = mpColumnType->size();
  if (*mpNumColumns < imax)
    success = false; // More column types specified than we have data columns

  if (imax < LastMappedColumn)
    success = false; // An unspecified column, i.e, ignored column is mapped

  unsigned C_INT32 IndependentCount = mDataIndependent.numCols();
  unsigned C_INT32 DependentCount = mDataDependent.numCols();

  mDependentValues.resize(DependentCount);
  mIndependentUpdateMethods.resize(IndependentCount);

  IndependentCount = 0;
  DependentCount = 0;

  bool TimeFound = false;

  for (i = 0; i < imax; i++)
    switch (getColumnType(i))
      {
      case ignore:
        if (i < LastMappedColumn && Objects[i])
          success = false; // An ignored column is mapped.
        break;

      case independent:
        if ((i < LastMappedColumn && !Objects[i]) || // Object not found
            i >= LastMappedColumn) success = false;  // The column must be mapped
        mIndependentUpdateMethods[IndependentCount++] =
          Objects[i]->getUpdateMethod();
        break;

      case dependent:
        if ((i < LastMappedColumn && !Objects[i]) || // Object not found
            i >= LastMappedColumn) success = false;  // The column must be mapped
        mDependentValues[DependentCount++] =
          (C_FLOAT64 *) Objects[i]->getReference();
        break;

      case time:
        TimeFound = true;
        break;
      }

  /* We need to check whether a column is mapped to time */
  if (!TimeFound && *mpTaskType == CCopasiTask::timeCourse)
    success = false;

  return success;
}

bool CExperiment::read(std::istream & in,
                       unsigned C_INT32 & currentLine)
{
  // Allocate for reading
  unsigned C_INT32 i, imax = mpColumnType->size();
  if (*mpNumColumns < imax)
    return false; // More column types specified than we have data columns

  unsigned C_INT32 IndependentCount = 0;
  unsigned C_INT32 DependentCount = 0;

  for (i = 0; i < imax; i++)
    switch (getColumnType(i))
      {
      case ignore:
        break;

      case independent:
        IndependentCount++;
        break;

      case dependent:
        DependentCount++;
        break;

      case time:
        break;
      }

  unsigned C_INT32 NumRows =
    (*mpNameRow != C_INVALID_INDEX) ? *mpNumRows - 1 : *mpNumRows;

  mDataTime.resize(NumRows);
  mDataIndependent.resize(NumRows, IndependentCount);
  mDataDependent.resize(NumRows, DependentCount);
  mColumnName.resize(IndependentCount + DependentCount);

  CTableRow Row(*mpNumColumns, (*mpSeparator)[0]);
  const std::vector< CTableCell > & Cells = Row.getCells();

  unsigned C_INT32 j;

  if (currentLine > *mpFirstRow) return false; // We are past our first line

  // forwind to our first line
  for (j = currentLine; j < *mpFirstRow && !in.fail(); j++)
    {
      in.ignore(LONG_MAX, '\x0a');
      currentLine++;
    }

  for (j = 0; j < NumRows && !in.fail(); j++)
    {
      in >> Row;
      currentLine++;

      if (j == *mpNameRow)
        {
          j--;
          for (i = 0; i < *mpNumColumns; i++)
            mColumnName[i] = Cells[i].getName();

          continue;
        }

      IndependentCount = 0;
      DependentCount = 0;

      for (i = 0; i < imax; i++)
        {
          switch (getColumnType(i))
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

  if ((in.fail() && !in.eof()) ||
      j != NumRows) return false;

  // We need to calculate the means and the weights
  mMeans.resize(DependentCount);
  mWeight.resize(DependentCount);
  C_FLOAT64 MaxWeight = 0.0;
  C_FLOAT64 MinWeight = DBL_MAX;

  unsigned C_INT32 Count;

  for (i = 0; i < DependentCount; i++)
    {
      C_FLOAT64 & Mean = mMeans[i];
      Mean = 0.0;
      Count = 0;

      for (j = 0; j < NumRows; j++)
        {
          C_FLOAT64 & Data = mDataDependent[j][i];
          if (!isnan(Data))
            {
              Count++;
              Mean += Data;
            }
        }

      if (Count)
        Mean /= Count;
      else
        Mean = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      C_FLOAT64 & Weight = mWeight[i];
      Weight = 0;

      if (Count > 1)
        {
          for (j = 0; j < NumRows; j++)
            {
              C_FLOAT64 & Data = mDataDependent[j][i];
              if (!isnan(Data))
                Weight += pow((Mean - Data), 2);
            }

          if (Weight > 0)
            {
              Weight = (Count - 1.0) / Weight;

              if (Weight > MaxWeight) MaxWeight = Weight;
              if (Weight < MinWeight) MinWeight = Weight;
            }
          else
            Weight = -Count; // All values where equal to the mean
        }
      else
        Weight = -1.0; // One or less values
    }

  // We have to make a guess for the weights which could not be calculated
  for (i = 0; i < DependentCount; i++)
    {
      if (!(mWeight[i] < -0.5)) continue;

      if (mWeight[i] < -1.5)
        mWeight[i] *= -MaxWeight; // All values where equal to the mean
      else
        mWeight[i] = 0.5 * (MaxWeight + MinWeight); // One or less values
    }

  // If it is a time course this is the place to assert that it is sorted.
  if (*mpTaskType == CCopasiTask::timeCourse)
    {
      CVector<unsigned C_INT32> Pivot;
      sortWithPivot(mDataTime.array(), mDataTime.array() + mDataTime.size(), Pivot);

      mDataTime.applyPivot(Pivot);
      mDataIndependent.applyPivot(Pivot);
      mDataDependent.applyPivot(Pivot);
    }

  return true;
}

const CCopasiTask::Type & CExperiment::getExperimentType() const
  {return *mpTaskType;}

const CVector< C_FLOAT64 > & CExperiment::getTimeData() const
  {return mDataTime;}

const CMatrix< C_FLOAT64 > & CExperiment::getIndependentData() const
  {return mDataIndependent;}

const CMatrix< C_FLOAT64 > & CExperiment::getDependentData() const
  {return mDataDependent;}

const std::string & CExperiment::getFileName() const
  {return *mpFileName;}

bool CExperiment::setFileName(const std::string & fileName)
{
  *mpFileName = fileName;
  return true;
}

bool CExperiment::addColumnType(const unsigned C_INT32 & index, const Type & type)
{
  std::string Index = StringPrint("%d", index);
  if (mpColumnType->getParameter(Index)) return false;

  return mpColumnType->addParameter(Index, CCopasiParameter::UINT,
                                    (unsigned C_INT32) type);
}

bool CExperiment::removeColumnType(const unsigned C_INT32 & index)
{return removeParameter(StringPrint("%d", index));}

const CExperiment::Type & CExperiment::getColumnType(const unsigned C_INT32 & index) const
  {
    return
    * static_cast<CExperiment::Type *>(mpColumnType->getValue(StringPrint("%d", index)).pVOID);
  }

bool CExperiment::setColumnType(const unsigned C_INT32 & index,
                                const CExperiment::Type & type)
{
  return mpColumnType->setValue(StringPrint("%d", index), (unsigned C_INT32) type);
}

const unsigned C_INT32 & CExperiment::getNumColumns() const
  {return *mpNumColumns;}

bool CExperiment::setNumColumns(const unsigned C_INT32 & cols)
{
  *mpNumColumns = cols;
  return true;
}

const unsigned C_INT32 & CExperiment::getNumRows() const
  {return *mpNumRows;}

bool CExperiment::setNumRows(const unsigned C_INT32 & rows)
{
  *mpNumRows = rows;
  return true;
}

const std::string & CExperiment::getSeperator() const
  {return *mpSeparator;}

bool CExperiment::setSeperator(const std::string & seperator)
{
  *mpSeparator = seperator;
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
