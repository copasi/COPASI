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

std::string CReportDefinitionVector::getKey()
{
  return mKey;
}

void CReportDefinitionVector::load(CReadConfig & configBuffer)
{}

void CReportDefinitionVector::save(CWriteConfig & configBuffer)
{}
