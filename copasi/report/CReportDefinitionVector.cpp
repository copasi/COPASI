/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportDefinitionVector.cpp,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/04/19 08:59:03 $
   End CVS Header */

// ReportDefinitionVector.cpp: implementation of the CReportDefinitionVector class.
//
//////////////////////////////////////////////////////////////////////

#include "copasi.h"
#include "CReportDefinitionVector.h"
#include "CKeyFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportDefinitionVector::CReportDefinitionVector(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiVectorN< CReportDefinition >(name, pParent),
    mKey(GlobalKeys.add("CReportDefinitionVector", this))
{}

CReportDefinitionVector::~CReportDefinitionVector()
{
  cleanup();
}

void CReportDefinitionVector::cleanup()
{
  GlobalKeys.remove(mKey);
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

  CReportDefinition* pNewReportDef = new CReportDefinition(name, this);
  pNewReportDef->setComment(comment);
  pNewReportDef->setObjectName(name);

  add(pNewReportDef);
  return true;
}
