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
    CCopasiVector< CReportDefinition >(name, pParent),
    mKey(CKeyFactory::add("CReportDefinitionVector", this))
{}

CReportDefinitionVector::~CReportDefinitionVector()
{
  cleanup();
}

void CReportDefinitionVector::cleanup()
{
  CKeyFactory::remove(mKey);
}

const std::string& CReportDefinitionVector::getKey()
{
  return mKey;
}

bool CReportDefinitionVector::addReportDefinition(const std::string name, const std::string comment)
{
  unsigned C_INT32 i;
  for (i = 0; i < size(); i++)
    if ((*this)[i]->getName() == name)
      return false; // duplicate name

  CReportDefinition* pNewReportDef = new CReportDefinition();
  pNewReportDef->setComment(comment);
  pNewReportDef->setObjectName(name);

  add(pNewReportDef);
  return true;
}
