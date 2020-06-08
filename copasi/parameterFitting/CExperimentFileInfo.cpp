// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include <sstream>

#include "copasi/copasi.h"

#include "CExperimentFileInfo.h"
#include "CExperiment.h"
#include "CExperimentSet.h"

#include "copasi/commandline/CLocaleString.h"

CExperimentFileInfo::CExperimentFileInfo():
  mpSet(NULL),
  mFileName(""),
  mList(),
  mLines(0),
  mUsedEnd(C_INVALID_INDEX),
  mEmptyLines()
{
}

CExperimentFileInfo::CExperimentFileInfo(CExperimentSet & set):
  mpSet(&set),
  mFileName(""),
  mList(),
  mLines(0),
  mUsedEnd(C_INVALID_INDEX),
  mEmptyLines()
{
}

CExperimentFileInfo::~CExperimentFileInfo()
{
  size_t i, imax;

  for (i = 0, imax = mList.size(); i < imax; i++)
    pdelete(mList[i]);

  mList.clear();
}

bool
CExperimentFileInfo::setFileName(const std::string & fileName)
{
  mFileName = fileName;
  countLines();
  return sync();
}

size_t
CExperimentFileInfo::countLines()
{
  mLines = 0;
  mEmptyLines.clear();

  std::ifstream in;
  in.open(CLocaleString::fromUtf8(mFileName).c_str(), std::ios::binary);

  if (in.fail())  // File can not be opened.
    {
      return mLines;
    }

  bool isEmpty;

  // count lines in file
  while (!in.eof())
    {
      isEmpty = true;
      char c;

      for (in.get(c); c != 0x0a && c != 0x0d; in.get(c))
        {
          if (in.fail() || in.eof()) break;

          switch (c)
            {
              case '\x20':
              case '\x09':
              case '\x0d':
              case '\x0a':
                break;

              default:
                isEmpty = false;
                break;
            }
        }

      // Eat additional line break characters appearing on DOS and Mac text format;
      if ((c == 0x0d && in.peek() == 0x0a) || // DOS
          (c == 0x0a && in.peek() == 0x0d))   // Mac
        in.ignore(1);

      mLines++;

      if (isEmpty)
        mEmptyLines.push_back(mLines);
    }

  return mLines;
}

const std::string &
CExperimentFileInfo::getFileName() const
{
  return mFileName;
}

bool
CExperimentFileInfo::sync()
{
  mpSet->sort();

  size_t i, imax;

  for (i = 0, imax = mList.size(); i < imax; i++)
    pdelete(mList[i]);

  mList.clear();

  // Find the desired file name
  for (i = 0, imax = mpSet->getExperimentCount(); i < imax; i++)
    if (mpSet->getExperiment(i)->getFileName() == mFileName) break;

  // Continue as long as the file name does not change
  for (; i < imax; i++)
    {
      if (mpSet->getExperiment(i)->getFileName() != mFileName) break;

      mList.push_back(new CExperimentInfo(*mpSet->getExperiment(i)));
    }

  mUsedEnd = C_INVALID_INDEX;

  return validate();
}

void
CExperimentFileInfo::removeInvalidExperiments()
{
  size_t Last = 0;
  size_t i, imax;

  for (i = 0, imax = mList.size(); i < imax; i++)
    {
      if (Last >= mList[i]->First)
        {
          // this experiment and all following are invalid
          // remove them
          removeLastExperiments(i);
          return;
        }

      Last = mList[i]->Last;

      // ensure there are no empty lines between first and last
      size_t line = getInterruption(mList[i]->First, mList[i]->Last);

      if (line != C_INVALID_INDEX)
        {
          // adjust this experiment to end before the empty line
          mList[i]->Last = line - 1;
          mList[i]->pExperiment->setLastRow((int)line - 1);

          // remove the remaining ones
          removeLastExperiments(i + 1);
          return;
        }
      else if (Last > mLines)
        {
          // adjust this experiment
          mList[i]->Last = mLines - 1;
          mList[i]->pExperiment->setLastRow((int)mLines - 1);

          // remove the remaining ones
          removeLastExperiments(i + 1);
          return;

        }
    }
}

void CExperimentFileInfo::removeLastExperiments(size_t start)
{
  for (size_t j = mList.size() - 1; j >= start; --j)
    {
      pdelete(mList[j]);
      mpSet->removeExperiment(j);
      mList.erase(mList.begin() + j);
    }
}

bool
CExperimentFileInfo::validate() const
{
  size_t Last = 0;
  size_t i, imax;

  for (i = 0, imax = mList.size(); i < imax; i++)
    {
      if (Last >= mList[i]->First) return false;

      Last = mList[i]->Last;

      if (Last > mLines) return false;
    }

  return true;
}

bool
CExperimentFileInfo::validateFirst(const size_t & index,
                                   const size_t & value)
{
  if (mLines < value ||
      mList[index]->Last < value ||
      (value == mList[index]->Last &&
       value == mList[index]->pExperiment->getHeaderRow())) return false;

  size_t Saved = mList[index]->First;
  mList[index]->First = value;

  bool Result = validate();
  mList[index]->First = Saved;

  return Result;
}

bool
CExperimentFileInfo::validateLast(const size_t & index,
                                  const size_t & value)
{
  if (mLines < value ||
      value < mList[index]->First ||
      (value == mList[index]->First &&
       value == mList[index]->pExperiment->getHeaderRow())) return false;

  size_t Saved = mList[index]->Last;
  mList[index]->Last = value;

  bool Result = validate();
  mList[index]->Last = Saved;

  return Result;
}

bool
CExperimentFileInfo::validateHeader(const size_t & index,
                                    const size_t & value)
{
  return (value <= mLines &&
          (mList[index]->First < mList[index]->Last ||
           value < mList[index]->First ||
           mList[index]->Last < value));
}

std::vector< std::string >
CExperimentFileInfo::getExperimentNames() const
{
  std::vector< std::string > List;

  size_t i, imax;

  for (i = 0, imax = mList.size(); i < imax; i++)
    List.push_back(mList[i]->pExperiment->getObjectName());

  return List;
}

CExperiment*
CExperimentFileInfo::getExperiment(const std::string & name)
{
  size_t i, imax;

  for (i = 0, imax = mList.size(); i < imax; i++)
    if (mList[i]->pExperiment->getObjectName() == name)
      return mList[i]->pExperiment;

  return NULL;
}

bool
CExperimentFileInfo::getFirstUnusedSection(size_t & First,
    size_t & Last)
{
  mUsedEnd = 0;

  return getNextUnusedSection(First, Last);
}

bool
CExperimentFileInfo::getNextUnusedSection(size_t & First,
    size_t & Last)
{
  First = mUsedEnd + 1;

  size_t i, imax = mList.size();

  for (i = 0; i < imax; i++)
    {
      if (First < mList[i]->First)
        {
          Last = mList[i]->First - 1;
          mUsedEnd = Last;

          return adjustForEmptyLines(First, Last);
        }

      if (mList[i]->Last + 1 > First)
        First = mList[i]->Last + 1;
    }

  if (First < mLines)
    {
      Last = mLines;
      mUsedEnd = Last;

      return adjustForEmptyLines(First, Last);
    }

  First = C_INVALID_INDEX;
  Last = C_INVALID_INDEX;

  mUsedEnd = mLines;

  return false;
}

bool
CExperimentFileInfo::adjustForEmptyLines(size_t & First,
    size_t & Last)
{
  std::vector<size_t>::const_iterator it = mEmptyLines.begin();
  std::vector<size_t>::const_iterator end = mEmptyLines.end();

  while (it != end && *it < First) ++it;

  if (it == end)
    return true;

  if (it != end && *it == First)
    {
      if (First == Last)
        return getNextUnusedSection(First, Last);

      First++;
      return adjustForEmptyLines(First, Last);
    }

  if (*it <= Last)
    {
      Last = *it - 1;
      mUsedEnd = Last;
    }

  return true;
}

size_t
CExperimentFileInfo::getInterruption(size_t first, size_t last) const
{
  std::vector< size_t >::const_iterator it = mEmptyLines.begin();

  for (; it != mEmptyLines.end(); ++it)
    {
      if (*it > first && *it < last)
        return *it;
    }

  return C_INVALID_INDEX;
}

CExperimentFileInfo::CExperimentInfo::CExperimentInfo():
  pExperiment(NULL),
  First(C_INVALID_INDEX),
  Last(C_INVALID_INDEX)
{}

CExperimentFileInfo::CExperimentInfo::CExperimentInfo(CExperiment & Experiment):
  pExperiment(&Experiment),
  First(pExperiment->getFirstRow()),
  Last(pExperiment->getLastRow())
{}

CExperimentFileInfo::CExperimentInfo::~CExperimentInfo() {}
