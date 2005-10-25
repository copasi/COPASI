/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentFileInfo.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/25 17:00:56 $
   End CVS Header */

#include "copasi.h"

#include "CExperimentFileInfo.h"
 #include "CExperiment.h"
 #include "CExperimentSet.h"

CExperimentFileInfo::CExperimentFileInfo():
    mpSet(NULL),
    mFilename(""),
    mList(),
    mLines(0),
    mUnusedEnd(C_INVALID_INDEX)
{}

CExperimentFileInfo::CExperimentFileInfo(CExperimentSet & set):
    mpSet(&set),
    mFilename(""),
    mList(),
    mLines(0),
    mUnusedEnd(C_INVALID_INDEX)
{}

CExperimentFileInfo::~CExperimentFileInfo()
{}

bool CExperimentFileInfo::setFilename(const std::string & filename)
{
  mFilename = filename;
  mLines = 0;

  std::ifstream in;
  in.open(mFilename.c_str(), std::ios::binary);
  if (in.fail()) return false; // File can not be opened.

  // forwind to count lines in file
  while (true)
    {
      in.ignore(LONG_MAX, '\x0a');
      if (in.eof() || in.fail()) break;

      mLines++;
    }

  return sync();
}

bool CExperimentFileInfo::sync()
{
  unsigned C_INT32 i, imax = mpSet->size();

  for (i = 0; i < imax; i++)
    if (mpSet->getExperiment(i)->getFileName() == mFilename) break;

  mList.clear();

  for (i = 0; i < imax; i++)
    {
      if (mpSet->getExperiment(i)->getFileName() != mFilename) break;
      mList.push_back(new CExperimentInfo(*mpSet->getExperiment(i)));
    }

  unsigned C_INT32 Last = 0;

  for (i = 0, imax = mList.size(); i < imax; i++)
    {
      if (Last <= mList[i]->First) return false;

      Last = mList[i]->Last;

      if (Last > mLines) return false;
    }

  mUnusedEnd = C_INVALID_INDEX;

  return true;
}

std::vector< std::string > CExperimentFileInfo::getExperimentNames() const
  {
    std::vector< std::string > List;

    unsigned C_INT32 i, imax;

    for (i = 0, imax = mList.size(); i < imax; i++)
      List.push_back(mList[i]->pExperiment->getObjectName());

    return List;
  }

bool CExperimentFileInfo::getFirstUnusedSection(unsigned C_INT32 & First,
    unsigned C_INT32 & Last)
{
  mUnusedEnd = 0;

  return getNextUnusedSection(First, Last);
}

bool CExperimentFileInfo::getNextUnusedSection(unsigned C_INT32 & First,
    unsigned C_INT32 & Last)
{
  First = mUnusedEnd;

  unsigned C_INT32 i, imax;

  for (i = 0, imax = mList.size(); i < imax; i++)
    if (First < mList[i]->First) break;

  for (; i < imax; i++)
    {
      Last = mList[i]->First;

      if (First < Last)
        {
          mUnusedEnd = Last;

          return true;
        }

      First = mList[i]->Last;
    }

  Last = mLines;

  if (First < Last)
    {
      mUnusedEnd = Last;

      return true;
    }

  First = C_INVALID_INDEX;
  Last = C_INVALID_INDEX;

  mUnusedEnd = Last;

  return false;
}

CExperimentFileInfo::CExperimentInfo::CExperimentInfo():
    pExperiment(NULL),
    First(C_INVALID_INDEX),
    Last(C_INVALID_INDEX)
{}

CExperimentFileInfo::CExperimentInfo::CExperimentInfo(CExperiment & Experiment):
    pExperiment(&Experiment),
    First(* Experiment.getValue("Position in File").pUINT),
    Last(C_INVALID_INDEX)
{
  Last = First + *pExperiment->getValue("Number of Rows").pUINT - 1;

  if (*pExperiment->getValue("Row containing Names").pUINT != C_INVALID_INDEX)
    Last++;
}

CExperimentFileInfo::CExperimentInfo::~CExperimentInfo() {}
