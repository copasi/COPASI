/**
 *  CReportDefinition class.
 *  This class describes the Report Definition
 *
 *  Created for Copasi by Mudita Singhal
 */

#include "CKeyFactory.h"
#include "CReportDefinition.h"
#include "CReportBody.h"
#include "CReport.h"

//////////////////////////////////////////////////
//
//class CReportDefinition
//
//////////////////////////////////////////////////
CReportDefinition::CReportDefinition():
    CCopasiObject("ReportDefinition", NULL, "ReportDefinition", CCopasiObject::Container),
    mKey(CKeyFactory::add("CReportDefinition", this)),
    mComment(""),
    mpBody(new CReportBody),
    mSeperator("/t")
{}

CReportDefinition::~CReportDefinition()
{cleanup();}

void CReportDefinition::cleanup()
{
  pdelete(mpBody);
  CKeyFactory::remove(mKey);
  mHeaderVector.clear();
  mFooterVector.clear();
}

std::vector<CCopasiObjectName>* CReportDefinition::getHeaderAddr()
{return &mHeaderVector;}

std::vector<CCopasiObjectName>* CReportDefinition::getFooterAddr()
{return &mFooterVector;}

CReportBody* CReportDefinition::getReportBody()
{return mpBody;}

void CReportDefinition::setReportBody(CReportBody *pNewBody)
{mpBody = pNewBody;}
