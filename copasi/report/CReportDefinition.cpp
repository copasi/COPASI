/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportDefinition.cpp,v $
   $Revision: 1.28 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/28 14:37:38 $
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
    mTaskType(CCopasiTask::timeCourse),
    mSeperator("\t"),
    mTable(true),
    mbTitle(true)
{}

CReportDefinition::CReportDefinition(const CReportDefinition & src,
                                     const CCopasiContainer * pParent):
    CCopasiObject(src, pParent),
    mKey(GlobalKeys.add("CReportDefinition", this)),
    mComment(src.mComment),
    mTaskType(src.mTaskType),
    mSeperator(src.mSeperator),
    mTable(src.mTable),
    mbTitle(src.mbTitle)
{}

CReportDefinition::~CReportDefinition()
{cleanup();}

void CReportDefinition::cleanup()
{
  GlobalKeys.remove(mKey);
  mHeaderVector.clear();
  mBodyVector.clear();
  mFooterVector.clear();
}

std::vector<CCopasiObjectName>* CReportDefinition::getBodyAddr()
{return &mBodyVector;}

std::vector<CCopasiObjectName>* CReportDefinition::getHeaderAddr()
{return &mHeaderVector;}

std::vector<CCopasiObjectName>* CReportDefinition::getFooterAddr()
{return &mFooterVector;}

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

void CReportDefinition::setTitle(bool title)
{mbTitle = title;}

bool CReportDefinition::isTable() const
  {return mTable;}

void CReportDefinition::setIsTable(bool table)
{mTable = table;}

const std::string & CReportDefinition::getKey() const
  {return mKey;}

void CReportDefinition::addTableElement(const std::string & cn)
{
  bool isFirst = false;
  if ((mHeaderVector.size() == 0) && (mBodyVector.size() == 0))
    isFirst = true;

  CCopasiObjectName SeperatorCN(mSeperator.getCN());
  CCopasiObjectName Title;

  if (!isFirst)
    {
      mHeaderVector.push_back(SeperatorCN);
      mBodyVector.push_back(SeperatorCN);
    }

  std::vector< CCopasiContainer * > ListOfContainer;

  CCopasiObject* pSelectedObject;
  pSelectedObject = CCopasiContainer::ObjectFromName(ListOfContainer, cn);
  if (pSelectedObject)
    {
      if (pSelectedObject->getObjectParent())
        {
          Title =
            pSelectedObject->getObjectParent()->getCN();
          Title += ",Reference=Name";
          getHeaderAddr()->push_back(Title);

          Title =
            CCopasiStaticString("[" + pSelectedObject->getObjectName() + "]").getCN();
        }
      else
        Title =
          CCopasiStaticString(pSelectedObject->getObjectName()).getCN();

      mHeaderVector.push_back(Title);
      mBodyVector.push_back(pSelectedObject->getCN());
    }
}
