// ReportDefinitionVector.cpp: implementation of the CReportDefinitionVector class.
//
//////////////////////////////////////////////////////////////////////

#include "CReportDefinitionVector.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportDefinitionVector::CReportDefinitionVector(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "TrajectoryTask", CCopasiObject::Container)
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
