#include "CKeyFactory.h"
#include "CReportDefinition.h"
#include "CReportBody.h"
#include "CReport.h"

//////////////////////////////////////////////////
//
//class CReport
//
//////////////////////////////////////////////////
CReport::CReport():
    CCopasiObject("Report", NULL, "Report", CCopasiObject::Container),
    mpReportDef(NULL),
    mAppend(true),
    mKey(CKeyFactory::add("Report", this))
{}

CReport::~CReport()
{cleanup();}

void CReport::cleanup()
{
  CKeyFactory::remove(mKey);
  pdelete(mpReportDef);
}

CReportDefinition* CReport::getDefReference()
{return mpReportDef;}

void CReport::setDefReference(CReportDefinition* reportDef)
{mpReportDef = reportDef;}

const std::string CReport::getTarget()
{return mTarget;}

void CReport::setTarget(const std::string *target)
{mTarget = target;}

bool CReport::append()
{return mAppend;}

void CReport::setAppend(bool append)
{mAppend = append;}

void CReport::printHeader()
{
  // for loop print out mpReportDef->getHeader()
}

void CReport::printBody()
{
  // for loop print out mpReportDef->getBody()
}

void CReport::printFooter()
{
  // for loop print out mpReportDef->getFooter()
}
