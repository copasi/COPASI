/**
 *  CReportDefinition class.
 *  This class describes the Report Definition
 *
 *  Created for Copasi by Mudita Singhal
 */

#include "copasi.h"

#include "CKeyFactory.h"
#include "CReportDefinition.h"
#include "CReportBody.h"
#include "CReport.h"

//////////////////////////////////////////////////
//
//class CReportDefinition
//
//////////////////////////////////////////////////
CReportDefinition::CReportDefinition(const std::string & name,
                                     const CCopasiContainer * pParent):
    CCopasiObject(name, pParent, "ReportDefinition"),
    mKey(CKeyFactory::add("CReportDefinition", this)),
    mComment(""),
    mpBody(new CReportBody),
    mSeperator("/t"),
    mbTitle(false)
{}

CReportDefinition::CReportDefinition(const CReportDefinition & src,
                                     const CCopasiContainer * pParent):
    CCopasiObject(src, pParent),
    mKey(CKeyFactory::add("CReportDefinition", this)),
    mComment(src.mComment),
    mpBody(new CReportBody(*mpBody)),
    mSeperator(src.mSeperator),
    mbTitle(src.mbTitle)
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

std::vector<CCopasiObjectName>* CReportDefinition::getBodyAddr()
{return &mBodyVector;}

std::vector<CCopasiObjectName>* CReportDefinition::getHeaderAddr()
{return &mHeaderVector;}

std::vector<CCopasiObjectName>* CReportDefinition::getFooterAddr()
{return &mFooterVector;}

CReportBody* CReportDefinition::getReportBody()
{return mpBody;}

void CReportDefinition::setReportBody(CReportBody *pNewBody)
{mpBody = pNewBody;}
