/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentSet.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/19 21:12:54 $
   End CVS Header */

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
