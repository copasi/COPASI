// ReportDefinitionVector.cpp: implementation of the CReportDefinitionVector class.
//
//////////////////////////////////////////////////////////////////////

#include "CReportDefinitionVector.h"
#include "CKeyFactory.cpp" 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportDefinitionVector::CReportDefinitionVector(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "TrajectoryTask", CCopasiObject::Container),
    mKey(CKeyFactory::add("SteadyStateTask", this))
{}

CReportDefinitionVector::~CReportDefinitionVector()
{
  cleanup();
}

const std::vector< CReportDefinition >* CReportDefinitionVector::getReportDefinitionsAddr()
{
  return &mReportDefinitions;
}

void CReportDefinitionVector::cleanup()
{
  mReportDefinitions.clear();
}

std::string CReportDefinitionVector::getKey()
{
  return mKey;
}
