/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentSet.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/02 15:11:33 $
   End CVS Header */

#include <algorithm>

#include "copasi.h"

#include "CExperimentSet.h"
#include "CExperiment.h"

#include "report/CKeyFactory.h"
#include "utilities/utility.h"

CExperimentSet::CExperimentSet(const std::string & name,
                               const CCopasiContainer * pParent):
    CCopasiParameterGroup(name, pParent, "CExperimentSet"),
    mpExperiments(NULL)
{initializeParameter();}

CExperimentSet::CExperimentSet(const CExperimentSet & src,
                               const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mpExperiments(NULL)
{initializeParameter();}

CExperimentSet::CExperimentSet(const CCopasiParameterGroup & group,
                               const CCopasiContainer * pParent):
    CCopasiParameterGroup(group, pParent),
    mpExperiments(NULL)
{initializeParameter();}

CExperimentSet::~CExperimentSet() {}

void CExperimentSet::initializeParameter()
{elevateChildren();}

bool CExperimentSet::elevateChildren()
{
  index_iterator it = mValue.pGROUP->begin();
  index_iterator end = mValue.pGROUP->end();

  for (; it != end; ++it)
    if (!elevate<CExperiment, CCopasiParameterGroup>(*it)) return false;

  mpExperiments = static_cast<std::vector<CExperiment * > * >(mValue.pVOID);

  sort();

  return true;
}

bool CExperimentSet::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;

  // First we need to sort the experiments so that we can make use of continued
  // file reading.
  sort();

  std::ifstream in;
  std::string CurrentFileName("");
  unsigned C_INT32 CurrentLineNumber = 0;

  std::vector< CExperiment * >::iterator it = mpExperiments->begin();
  std::vector< CExperiment * >::iterator end = mpExperiments->end();

  for (it = mpExperiments->begin(); it != end; ++it)
    {
      if (CurrentFileName != (*it)->getFileName())
        {
          CurrentFileName = (*it)->getFileName();
          CurrentLineNumber = 0;
          if (in.is_open())
            {
              in.close();
              in.clear();
            }

          in.open(CurrentFileName.c_str(), std::ios::binary);
          if (in.fail()) return false; // File can not be opened.
        }

      if (!(*it)->read(in, CurrentLineNumber)) return false;
      if (!(*it)->compile(listOfContainer)) return false;
    }

  return success;
}

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

  CExperiment * pExperiment = new CExperiment(experiment);
  pExperiment->setObjectName(name);
  addParameter(pExperiment);

  sort();

  return pExperiment;
}

CExperiment * CExperimentSet::getExperiment(const unsigned C_INT32 & index)
{return (*mpExperiments)[index];}

const CExperiment * CExperimentSet::getExperiment(const unsigned C_INT32 & index) const
  {return (*mpExperiments)[index];}

CExperiment * CExperimentSet::getExperiment(const std::string & name)
{return static_cast<CExperiment *>(getGroup(name));}

const CExperiment * CExperimentSet::getExperiment(const std::string & name) const
  {return static_cast<const CExperiment *>(getGroup(name));}

const CCopasiTask::Type & CExperimentSet::getExperimentType(const unsigned C_INT32 & index) const
  {return getExperiment(index)->getExperimentType();}

const CMatrix< C_FLOAT64 > & CExperimentSet::getIndependentData(const unsigned C_INT32 & index) const
  {return getExperiment(index)->getIndependentData();}

const CMatrix< C_FLOAT64 > & CExperimentSet::getDependentData(const unsigned C_INT32 & index) const
  {return getExperiment(index)->getDependentData();}

unsigned C_INT32 CExperimentSet::keyToIndex(const std::string & key) const
  {
    const CExperiment * pExp = dynamic_cast<const CExperiment *>(GlobalKeys.get(key));

    if (!pExp) return C_INVALID_INDEX;

    unsigned C_INT32 i, imax = size();

    for (i = 0; i < imax; i++)
      if (pExp == getExperiment(i)) return i;

    return C_INVALID_INDEX;
  }

void CExperimentSet::sort()
{
  std::vector< CExperiment * >::iterator it = mpExperiments->begin();
  std::vector< CExperiment * >::iterator end = mpExperiments->end();

  std::sort(it, end, &CExperiment::compare);

  return;
}

std::vector< std::string > CExperimentSet::getFileNames() const
  {
    std::vector< std::string > List;
    std::string currentFile = "";

    std::vector< CExperiment * >::iterator it = mpExperiments->begin();
    std::vector< CExperiment * >::iterator end = mpExperiments->end();

    for (; it != end; ++it)
      if (currentFile != (*it)->getFileName())
        {
          currentFile = (*it)->getFileName();
          List.push_back(currentFile);
        }

    return List;
  }
