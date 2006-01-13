/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperiment.cpp,v $
   $Revision: 1.23.2.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/13 14:13:17 $
   End CVS Header */

#include <fstream>
#include <limits>
#include <math.h>
#include <float.h>

#include "copasi.h"

#include "CExperiment.h"
#include "CExperimentObjectMap.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "utilities/CTableCell.h"
#include "utilities/CSort.h"
#include "utilities/CDirEntry.h"
#include "utilities/utility.h"

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
    mpColumnType(NULL),
    mColumnName(),
    mpObjectMap(NULL),
    mDataTime(0),
    mDataIndependent(0, 0),
    mDataDependent(0, 0),
    mMeans(0),
    mWeight(0),
    mWeightSquare(0),
    mDependentValues(0),
    mIndependentUpdateMethods(0),
    mIndependentValues(0),
    mNumDataRows(0),
    mDataDependentCalculated(0)
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
    mpColumnType(NULL),
    mColumnName(src.mColumnName),
    mpObjectMap(NULL),
    mDataTime(src.mDataTime),
    mDataIndependent(src.mDataIndependent),
    mDataDependent(src.mDataDependent),
    mMeans(src.mMeans),
    mWeight(src.mWeight),
    mWeightSquare(src.mWeightSquare),
    mDependentValues(src.mDependentValues),
    mIndependentUpdateMethods(src.mIndependentUpdateMethods),
    mIndependentValues(src.mIndependentValues),
    mNumDataRows(src.mNumDataRows),
    mDataDependentCalculated(src.mDataDependentCalculated)
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
    mpColumnType(NULL),
    mColumnName(),
    mpObjectMap(NULL),
    mDataTime(0),
    mDataIndependent(0, 0),
    mDataDependent(0, 0),
    mMeans(0),
    mWeight(0),
    mWeightSquare(0),
    mDependentValues(0),
    mIndependentUpdateMethods(0),
    mIndependentValues(0),
    mNumDataRows(0),
    mDataDependentCalculated(0)
{initializeParameter();}

CExperiment::~CExperiment() {}

CExperiment & CExperiment::operator = (const CExperiment & rhs)
{
  std::string Key = *getValue("Key").pKEY;

  *static_cast<CCopasiParameterGroup *>(this) =
    *static_cast<const CCopasiParameterGroup *>(&rhs);

  setValue("Key", Key);

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
  mpRowOriented =
    assertParameter("Data is Row Oriented", CCopasiParameter::BOOL, (bool) true)->getValue().pBOOL;
  mpHeaderRow =
    assertParameter("Row containing Names", CCopasiParameter::UINT, (unsigned C_INT32) C_INVALID_INDEX)->getValue().pUINT;
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

C_FLOAT64 CExperiment::sumOfSquares(const unsigned C_INT32 & index,
                                    C_FLOAT64 *& dependentValues,
                                    C_FLOAT64 *& residuals) const
  {
    C_FLOAT64 Residual;
    C_FLOAT64 s = 0.0;

    C_FLOAT64 const * pDataDependent = mDataDependent[index];
    C_FLOAT64 const * pEnd = pDataDependent + mDataDependent.numCols();
    C_FLOAT64 * const * ppDependentValues = mDependentValues.array();
    C_FLOAT64 const * pWeight = mWeight.array();

    if (residuals)
      for (; pDataDependent != pEnd;
           pDataDependent++, ppDependentValues++, pWeight++, dependentValues++, residuals++)
        {
          *dependentValues = **ppDependentValues;
          *residuals = (*pDataDependent - *dependentValues) * *pWeight;
          s += *residuals * *residuals;
        }
    else
      for (; pDataDependent != pEnd;
           pDataDependent++, ppDependentValues++, pWeight++, dependentValues++)
        {
          *dependentValues = **ppDependentValues;
          Residual = (*pDataDependent - *dependentValues) * *pWeight;
          s += Residual * Residual;
        }

    return s;
  }

void CExperiment::storeCalculatedValues(const unsigned C_INT32 & index)
{
  C_FLOAT64 * pDataDependentCalculated = mDataDependentCalculated[index];
  C_FLOAT64 * pEnd = pDataDependentCalculated + mDataDependentCalculated.numCols();
  C_FLOAT64 * const * ppDependentValues = mDependentValues.array();

  for (; pDataDependentCalculated != pEnd; pDataDependentCalculated++, ppDependentValues++)
    *pDataDependentCalculated = **ppDependentValues;

  return;
}

bool CExperiment::calculateStatistics()
{
  unsigned C_INT32 numRows = mDataDependent.numRows();
  unsigned C_INT32 numCols = mDataDependent.numCols();

  // Overall statistic;
  mMean = 0.0;
  mSD = 0.0;
  unsigned C_INT32 Count = 0;

  // per row statistic;
  mRowMean.resize(numRows);
  mRowMean = 0.0;
  mRowSD.resize(numRows);
  mRowSD = 0.0;
  CVector< unsigned C_INT32 > RowCount;
  RowCount.resize(numRows);
  RowCount = 0;

  // per column statistic;
  mColumnMean.resize(numCols);
  mColumnMean = 0.0;
  mColumnSD.resize(numCols);
  mColumnSD = 0.0;
  CVector< unsigned C_INT32 > ColumnCount;
  ColumnCount.resize(numCols);
  ColumnCount = 0;

  unsigned C_INT32 i, j;
  C_FLOAT64 Residual;

  for (i = 0; i < numRows; i++)
    {
      for (j = 0; j < numCols; j++)
        {
          Residual = mDataDependentCalculated(i, j) - mDataDependent(i, j);

          if (isnan(Residual)) continue;

          mMean += Residual;
          Count++;

          mRowMean[i] += Residual;
          RowCount[i]++;

          mColumnMean[j] += Residual;
          ColumnCount[j]++;
        }
    }

  if (Count)
    mMean /= Count;
  else
    mMean = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  for (i = 0; i < numRows; i++)
    {
      if (RowCount[i])
        mRowMean[i] /= RowCount[i];
      else
        mRowMean[i] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  for (j = 0; j < numCols; j++)
    {
      if (ColumnCount[j])
        mColumnMean[j] /= ColumnCount[j];
      else
        mColumnMean[j] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  for (i = 0; i < numRows; i++)
    {
      for (j = 0; j < numCols; j++)
        {
          Residual = mDataDependentCalculated(i, j) - mDataDependent(i, j);

          if (isnan(Residual)) continue;

          mSD += (Residual - mMean) * (Residual - mMean);
          mRowSD[i] += (Residual - mRowMean[i]) * (Residual - mRowMean[i]);
          mColumnSD[j] += (Residual - mColumnMean[j]) * (Residual - mColumnMean[j]);
        }
    }

  if (Count)
    mSD = sqrt(mSD / Count);
  else
    mSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  for (i = 0; i < numRows; i++)
    {
      if (RowCount[i])
        mRowSD[i] = sqrt(mRowSD[i] / RowCount[i]);
      else
        mRowSD[i] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  for (j = 0; j < numCols; j++)
    {
      if (ColumnCount[j])
        mColumnSD[j] = sqrt(mColumnSD[j] / ColumnCount[j]);
      else
        mColumnSD[j] = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  return true;
}

bool CExperiment::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;

  if (!mpObjectMap->compile(listOfContainer))
    success = false;

  unsigned C_INT32 LastMappedColumn = mpObjectMap->getLastColumn();
  const CVector< CCopasiObject * > & Objects = mpObjectMap->getMappedObjects();

  unsigned C_INT32 i, imax = getLastNotIgnoredColumn();
  if (*mpNumColumns <= imax)
    success = false; // More column types specified than we have data columns

  if (LastMappedColumn < imax)
    success = false; // More column types specified than we have mapped columns

  unsigned C_INT32 IndependentCount = mDataIndependent.numCols();
  unsigned C_INT32 DependentCount = mDataDependent.numCols();

  mDependentValues.resize(DependentCount);
  mIndependentUpdateMethods.resize(IndependentCount);
  mIndependentValues.resize(IndependentCount);

  IndependentCount = 0;
  DependentCount = 0;

  bool TimeFound = false;

  for (i = 0; i <= imax; i++)
    switch (getColumnType(i))
      {
      case ignore:
        break;

      case independent:
        if (!Objects[i]) // Object not found
          return false;  // :TODO: create error message The column must be mapped
        mIndependentUpdateMethods[IndependentCount] =
          Objects[i]->getUpdateMethod();
        mIndependentValues[IndependentCount++] =
          *(C_FLOAT64 *)Objects[i]->getReference();
        break;

      case dependent:
        if (!Objects[i]) // Object not found
          return false;  // :TODO: create error message The column must be mapped
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
  unsigned C_INT32 TimeCount = 0;
  unsigned C_INT32 IgnoreCount = 0;

  for (i = 0; i < imax; i++)
    switch (getColumnType(i))
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
  mDataDependentCalculated.resize(mNumDataRows, DependentCount);
  mColumnName.resize(IndependentCount + DependentCount + TimeCount);

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

  for (j = 0; j < mNumDataRows && !in.fail(); j++, currentLine++)
    {
      in >> Row;
      if (currentLine == *mpHeaderRow)
        {
          j--;

          unsigned C_INT32 Column = 0;
          for (i = 0; i < *mpNumColumns; i++)
            if (getColumnType(i) != ignore)
              mColumnName[Column++] = Cells[i].getName();

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

  // :TODO: write proper error message
  if ((in.fail() && !in.eof()) ||
      j != mNumDataRows) return false;

  // We need to calculate the means and the weights
  mMeans.resize(DependentCount);
  mWeight.resize(DependentCount);
  mWeightSquare.resize(DependentCount);
  C_FLOAT64 MaxWeight = 0.0;
  C_FLOAT64 MinWeight = DBL_MAX;

  unsigned C_INT32 Count;

  for (i = 0; i < DependentCount; i++)
    {
      C_FLOAT64 & Mean = mMeans[i];
      Mean = 0.0;
      Count = 0;

      for (j = 0; j < mNumDataRows; j++)
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

      C_FLOAT64 & WeightSquare = mWeightSquare[i];
      WeightSquare = 0;

      if (Count)
        {
          for (j = 0; j < mNumDataRows; j++)
            {
              C_FLOAT64 & Data = mDataDependent[j][i];
              if (!isnan(Data))
                WeightSquare += (Mean - Data) * (Mean - Data);
            }

          if (WeightSquare > 0)
            {
              WeightSquare = Count / WeightSquare;

              if (WeightSquare > MaxWeight) MaxWeight = WeightSquare;
              if (WeightSquare < MinWeight) MinWeight = WeightSquare;
            }
          else
            WeightSquare = -Count; // All values where equal to the mean
        }
      else
        WeightSquare = -1.0; // Zero values
    }

  // We have to make a guess for the weights which could not be calculated
  for (i = 0; i < DependentCount; i++)
    {
      if (mWeightSquare[i] < -1.5)
        mWeightSquare[i] *= -MaxWeight; // All values where equal to the mean
      else if (mWeightSquare[i] < -0.5)
        mWeightSquare[i] = 0.5 * (MaxWeight + MinWeight); // One or less values

      mWeight[i] = sqrt(mWeightSquare[i]);
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

  // Guess missing dependent values
  for (i = 0; i < mNumDataRows; i++)
    for (j = 0; j < DependentCount; j++)
      if (isnan(mDataDependent[i][j])) mDataDependent[i][j] = mMeans[j];

  return true;
}

bool CExperiment::readColumnNames()
{
  mColumnName.resize(*mpNumColumns);

  if (*mpHeaderRow == C_INVALID_INDEX) return false;

  // Open the file
  std::ifstream in;
  in.open(getFileName().c_str(), std::ios::binary);
  if (in.fail()) return false;

  // Forwind to header row.
  unsigned C_INT32 i;
  for (i = 1; i < *mpHeaderRow && !in.fail(); i++)
    in.ignore(LONG_MAX, '\x0a');

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
    in.open(getFileName().c_str(), std::ios::binary);
    if (in.fail()) return false;

    // Forwind to first row.
    unsigned C_INT32 i;
    for (i = 1; i < *mpFirstRow && !in.fail(); i++)
      in.ignore(LONG_MAX, '\x0a');

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
    if (!(*mIndependentUpdateMethods[i])(mDataIndependent(index, i)))
      return false;

  return true;
}

bool CExperiment::restoreModelIndependentData()
{
  unsigned C_INT32 i, imax = mIndependentUpdateMethods.size();

  for (i = 0; i < imax; i++)
    if (!(*mIndependentUpdateMethods[i])(mIndependentValues[i]))
      return false;

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

bool CExperiment::addColumnType(const unsigned C_INT32 & index, const Type & type)
{
  std::string Index = StringPrint("%d", index);
  if (mpColumnType->getParameter(Index)) return false;

  return mpColumnType->addParameter(Index, CCopasiParameter::UINT,
                                    (unsigned C_INT32) type);
}

bool CExperiment::removeColumnType(const unsigned C_INT32 & index)
{return mpColumnType->removeParameter(StringPrint("%d", index));}

const CExperiment::Type & CExperiment::getColumnType(const unsigned C_INT32 & index) const
  {
    CCopasiParameter * pParm = mpColumnType->getParameter(StringPrint("%d", index));

    if (!pParm)
      {
        const_cast<CExperiment *>(this)->addColumnType(index, dependent);
        pParm = mpColumnType->getParameter(StringPrint("%d", index));
      }

    return * static_cast<CExperiment::Type *>(pParm->getValue().pVOID);
  }

bool CExperiment::setColumnType(const unsigned C_INT32 & index,
                                const CExperiment::Type & type)
{
  CCopasiParameter * pParm = mpColumnType->getParameter(StringPrint("%d", index));

  if (pParm)
    return pParm->setValue((unsigned C_INT32) type);
  else
    return addColumnType(index, type);
}

unsigned C_INT32 CExperiment::getLastNotIgnoredColumn() const
  {
    unsigned C_INT32 i = mpColumnType->size();

    for (i = mpColumnType->size() - 1; i != C_INVALID_INDEX; i--)
      if (getColumnType(i) != ignore) return i;

    return C_INVALID_INDEX;
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
  return (lhs->getFileName() < rhs->getFileName() ||
          (lhs->getFileName() == rhs->getFileName() &&
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

    os << "Error Mean:\t" << mMean << std::endl;
    os << "Error Standard Deviation:\t" << mSD << std::endl;

    unsigned i, imax = mNumDataRows;
    unsigned j, jmax = mDataDependent.numCols();
    unsigned k, kmax = getLastNotIgnoredColumn() + 1;

    const CVector<CCopasiObject *> & Objects =
      mpObjectMap->getMappedObjects();

    os << "Row\t";
    for (k = 0; k < kmax; k++)
      if (getColumnType(k) == CExperiment::dependent)
        {
          if (Objects[k])
            {
              os << Objects[k]->getObjectDisplayName() << " [Data]\t";
              os << Objects[k]->getObjectDisplayName() << " [Fit]\t";
              os << Objects[k]->getObjectDisplayName() << " [Error]";
            }
          os << "\t";
        }
    os << "Mean\tStandard Deviation" << std::endl << std::endl;

    for (i = 0; i < imax; i++)
      {
        os << i + 1 << ".\t";
        for (j = 0; j < jmax; j++)
          {
            os << mDataDependent(i, j) << "\t";
            os << mDataDependentCalculated(i, j) << "\t";
            os << mDataDependentCalculated(i, j) - mDataDependent(i, j) << "\t";
          }
        os << mRowMean[i] << "\t" << mRowSD[i] << std::endl;
      }

    os << "Mean";
    for (j = 0; j < jmax; j++)
      os << "\t" << mMeans[j] << "\t\t" << mColumnMean[j];
    os << std::endl;

    os << "Weight";
    for (j = 0; j < jmax; j++)
      os << "\t\t\t" << mWeight[j];
    os << std::endl;

    os << "Standard Deviation";
    for (j = 0; j < jmax; j++)
      os << "\t\t\t" << mColumnSD[j];
    os << std::endl;

    return;
  }
