/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentSet.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/23 19:17:28 $
   End CVS Header */

#include <algorithm>

#include "copasi.h"

#include "CExperimentSet.h"
#include "CExperiment.h"

CExperimentSet::CExperimentSet(const CCopasiContainer * pParent):
    CCopasiParameterGroup("Experiment Set", pParent),
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
{
  CExperiment * pExp;
  CCopasiParameterGroup * pGrp;

  index_iterator it = mValue.pGROUP->begin();
  index_iterator end = mValue.pGROUP->end();

  for (; it != end; ++it)
    {
      if (!(pGrp = dynamic_cast<CCopasiParameterGroup *>(*it)))
        pExp = new CExperiment();
      else
        pExp = new CExperiment(*pGrp);

      pdelete(*it);
      *it = pExp;
    }

  mpExperiments = static_cast<std::vector<CExperiment * > * >(mValue.pVOID);
}

#include <algorithm>

bool CExperimentSet::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;

  // First we need to sort the experiments so that we can make use of continued
  // file reading.
  std::vector< CExperiment * >::iterator it = mpExperiments->begin();
  std::vector< CExperiment * >::iterator end = mpExperiments->end();

  // We use the '<' operator defined in CExperiment.
  std::sort(it, end, &CExperiment::compare);

  std::ifstream in;
  std::string CurrentFileName("");
  unsigned C_INT32 CurrentLineNumber = 0;
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
  unsigned C_INT32 index = size();

  CExperiment * pExperiment = new CExperiment();
  addParameter(pExperiment);

  return pExperiment;
}

bool CExperimentSet::removeExperiment(const unsigned C_INT32 & index)
{return removeParameter(index);}

CExperiment * CExperimentSet::getExperiment(const unsigned C_INT32 & index)
{
  assert (index < size());
  return (*mpExperiments)[index];
}

const CExperiment * CExperimentSet::getExperiment(const unsigned C_INT32 & index) const
  {
    assert (index < size());
    return (*mpExperiments)[index];
  }

const CCopasiTask::Type & CExperimentSet::getExperimentType(const unsigned C_INT32 & index) const
  {return getExperiment(index)->getExperimentType();}

const CMatrix< C_FLOAT64 > & CExperimentSet::getIndependentData(const unsigned C_INT32 & index) const
  {return getExperiment(index)->getIndependentData();}

const CMatrix< C_FLOAT64 > & CExperimentSet::getDependentData(const unsigned C_INT32 & index) const
  {return getExperiment(index)->getDependentData();}
