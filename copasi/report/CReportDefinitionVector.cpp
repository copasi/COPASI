// ReportDefinitionVector.cpp: implementation of the CReportDefinitionVector class.
//
//////////////////////////////////////////////////////////////////////

#include "CReportDefinitionVector.h"
#include "CKeyFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportDefinitionVector::CReportDefinitionVector(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "TrajectoryTask", CCopasiObject::Container),
    mKey(CKeyFactory::add("CReportDefinitionVector", this))
{}

CReportDefinitionVector::~CReportDefinitionVector()
{
  cleanup();
}

const std::vector< CReportDefinition*>* CReportDefinitionVector::getReportDefinitionsAddr()
{
  return &mReportDefinitions;
}

void CReportDefinitionVector::cleanup()
{
  CKeyFactory::remove(mKey);
  mReportDefinitions.clear();
}

const std::string& CReportDefinitionVector::getKey()
{
  return mKey;
}

void CReportDefinitionVector::load(CReadConfig & configBuffer)
{}

void CReportDefinitionVector::save(CWriteConfig & configBuffer)
{}

bool CReportDefinitionVector::addReportDefinition(const std::string name, const std::string comment)
{
  C_INT32 i;
  for (i = 0; i < mReportDefinitions.size(); i++)
    if (mReportDefinitions[i]->getName() == name)
      return false; // duplicate name

  CReportDefinition* pNewReportDef = new CReportDefinition();
  mReportDefinitions.push_back(pNewReportDef);
  pNewReportDef->setComment(comment);
  pNewReportDef->setObjectName(name);
  return true;
}
