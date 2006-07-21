/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentFileInfo.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/21 18:06:04 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sstream>

#include "copasi.h"

#include "CExperimentFileInfo.h"
#include "CExperiment.h"
#include "CExperimentSet.h"

CExperimentFileInfo::CExperimentFileInfo():
    mpSet(NULL),
    mFileName(""),
    mList(),
    mLines(0),
    mUsedEnd(C_INVALID_INDEX),
    mEmptyLines()
{}

CExperimentFileInfo::CExperimentFileInfo(CExperimentSet & set):
    mpSet(&set),
    mFileName(""),
    mList(),
    mLines(0),
    mUsedEnd(C_INVALID_INDEX),
    mEmptyLines()
{}

CExperimentFileInfo::~CExperimentFileInfo()
{
  unsigned C_INT32 i, imax;

  for (i = 0, imax = mList.size(); i < imax; i++)
    pdelete(mList[i]);

  mList.clear();
}

bool CExperimentFileInfo::setFileName(const std::string & fileName)
{
  mFileName = fileName;
  mLines = 0;
  mEmptyLines.clear();

  std::ifstream in;
  in.open(utf8ToLocale(mFileName).c_str(), std::ios::binary);
  if (in.fail()) return false; // File can not be opened.

  bool isEmpty;

  // forwind to count lines in file
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

      // Eat additional line break characters only appearing on dos text format;
      if ((c == 0x0d && in.peek() == 0x0a))
        in.ignore(1);

      mLines++;

      if (isEmpty)
        mEmptyLines.push_back(mLines);
    }

  return sync();
}

const std::string & CExperimentFileInfo::getFileName() const
{return mFileName;}

bool CExperimentFileInfo::sync()
{
  mpSet->sort();

  unsigned C_INT32 i, imax;

  for (i = 0, imax = mList.size(); i < imax; i++)
    pdelete(mList[i]);

  mList.clear();

  // Find the desired file name
  for (i = 0, imax = mpSet->size(); i < imax; i++)
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

bool CExperimentFileInfo::validate() const
  {
    unsigned C_INT32 Last = 0;
    unsigned C_INT32 i, imax;

    for (i = 0, imax = mList.size(); i < imax; i++)
      {
        if (Last >= mList[i]->First) return false;

        Last = mList[i]->Last;

        if (Last > mLines) return false;
      }

    return true;
  }

bool CExperimentFileInfo::validateFirst(const unsigned C_INT32 & index,
                                        const unsigned C_INT32 & value)
{
  if (mLines < value ||
      mList[index]->Last < value ||
      (value == mList[index]->Last &&
       value == mList[index]->pExperiment->getHeaderRow())) return false;

  unsigned C_INT32 Saved = mList[index]->First;
  mList[index]->First = value;

  bool Result = validate();
  mList[index]->First = Saved;

  return Result;
}

bool CExperimentFileInfo::validateLast(const unsigned C_INT32 & index,
                                       const unsigned C_INT32 & value)
{
  if (mLines < value ||
      value < mList[index]->First ||
      (value == mList[index]->First &&
       value == mList[index]->pExperiment->getHeaderRow())) return false;

  unsigned C_INT32 Saved = mList[index]->Last;
  mList[index]->Last = value;

  bool Result = validate();
  mList[index]->Last = Saved;

  return Result;
}

bool CExperimentFileInfo::validateHeader(const unsigned C_INT32 & index,
    const unsigned C_INT32 & value)
{
  return (value <= mLines &&
          (mList[index]->First < mList[index]->Last ||
           value < mList[index]->First ||
           mList[index]->Last < value));
}

std::vector< std::string > CExperimentFileInfo::getExperimentNames() const
  {
    std::vector< std::string > List;

    unsigned C_INT32 i, imax;

    for (i = 0, imax = mList.size(); i < imax; i++)
      List.push_back(mList[i]->pExperiment->getObjectName());

    return List;
  }

CExperiment * CExperimentFileInfo::getExperiment(const std::string & name)
{
  unsigned C_INT32 i, imax;

  for (i = 0, imax = mList.size(); i < imax; i++)
    if (mList[i]->pExperiment->getObjectName() == name)
      return mList[i]->pExperiment;

  return NULL;
}

bool CExperimentFileInfo::getFirstUnusedSection(unsigned C_INT32 & First,
    unsigned C_INT32 & Last)
{
  mUsedEnd = 0;

  return getNextUnusedSection(First, Last);
}

bool CExperimentFileInfo::getNextUnusedSection(unsigned C_INT32 & First,
    unsigned C_INT32 & Last)
{
  First = mUsedEnd + 1;

  unsigned C_INT32 i, imax = mList.size();

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

bool CExperimentFileInfo::adjustForEmptyLines(unsigned C_INT32 & First,
    unsigned C_INT32 & Last)
{
  std::vector<unsigned C_INT32>::const_iterator it = mEmptyLines.begin();
  std::vector<unsigned C_INT32>::const_iterator end = mEmptyLines.end();

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
