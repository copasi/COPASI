/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperiment.cpp,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/06 22:19:49 $
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
    mDependentValues(0),
    mIndependentUpdateMethods(0),
    mIndependentValues(0),
    mNumDataRows(0)
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
    mDependentValues(src.mDependentValues),
    mIndependentUpdateMethods(src.mIndependentUpdateMethods),
    mIndependentValues(src.mIndependentValues),
    mNumDataRows(src.mNumDataRows)
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
    mDependentValues(0),
    mIndependentUpdateMethods(0),
    mIndependentValues(0)
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
    assertParameter("File Name", CCopasiParameter::STRING, std::string(""))->getValue().pSTRING;
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
          return false;  // The column must be mapped
        mIndependentUpdateMethods[IndependentCount] =
          Objects[i]->getUpdateMethod();
        mIndependentValues[IndependentCount++] =
          *(C_FLOAT64 *)Objects[i]->getReference();
        break;

      case dependent:
        if (!Objects[i]) // Object not found
          return false;  // The column must be mapped
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

  if ((in.fail() && !in.eof()) ||
      j != mNumDataRows) return false;

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

      C_FLOAT64 & Weight = mWeight[i];
      Weight = 0;

      if (Count > 1)
        {
          for (j = 0; j < mNumDataRows; j++)
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
  in.open(this->mpFileName->c_str(), std::ios::binary);
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
    in.open(this->mpFileName->c_str(), std::ios::binary);
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
  {return *mpFileName;}

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

bool CExperiment::setSeparator(const std::string & seperator)
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
