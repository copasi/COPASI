
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
    mAppend(true)
    //,mKey(CKeyFactory::add("Report", this))
{}

CReport::~CReport()
{cleanup();}

void CReport::cleanup()
{
  //  CKeyFactory::remove(mKey);
  // mpReportDef pointer shall be dealt outside, where it is created
  //  pdelete(mpReportDef);
}

CReportDefinition* CReport::getReportDefinition()
{return mpReportDef;}

void CReport::setReportDefinition(CReportDefinition* reportDef)
{mpReportDef = reportDef;}

const std::string& CReport::getTarget()
{return mTarget;}

void CReport::setTarget(std::string target)
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

void CReport::compile()
{}
