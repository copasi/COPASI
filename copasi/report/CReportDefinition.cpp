/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportDefinition.cpp,v $
   $Revision: 1.24 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/06/10 19:29:44 $
   End CVS Header */

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
    mKey(GlobalKeys.add("CReportDefinition", this)),
    mComment(""),
    mpBody(new CReportBody),
    mSeperator("/t"),
    mbTitle(false)
{}

CReportDefinition::CReportDefinition(const CReportDefinition & src,
                                     const CCopasiContainer * pParent):
    CCopasiObject(src, pParent),
    mKey(GlobalKeys.add("CReportDefinition", this)),
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
  GlobalKeys.remove(mKey);
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

bool CReportDefinition::setTaskType(const CCopasiTask::Type & taskType)
{mTaskType = taskType; return true;}

const CCopasiTask::Type & CReportDefinition::getTaskType() const
  {return mTaskType;}

void CReportDefinition::setSeperator(const CCopasiStaticString& Seperator)
{mSeperator = Seperator;}

const CCopasiStaticString& CReportDefinition::getSeperator() const
  {return mSeperator;}

bool CReportDefinition::getTitle() const
  {return mbTitle;}

void CReportDefinition::setTitle(bool mTitle)
{mbTitle = mTitle;}

const std::string & CReportDefinition::getKey() const
  {return mKey;}
