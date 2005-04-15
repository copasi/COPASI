/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportDefinition.cpp,v $
   $Revision: 1.32 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/15 11:16:08 $
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
    mSeparator("\t"),
    mTable(true),
    mbTitle(true)
{}

CReportDefinition::CReportDefinition(const CReportDefinition & src,
                                     const CCopasiContainer * pParent):
    CCopasiObject(src, pParent),
    mKey(GlobalKeys.add("CReportDefinition", this)),
    mComment(src.mComment),
    mTaskType(src.mTaskType),
    mSeparator(src.mSeparator),
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

std::vector<CRegisteredObjectName>* CReportDefinition::getBodyAddr()
{return &mBodyVector;}

std::vector<CRegisteredObjectName>* CReportDefinition::getHeaderAddr()
{return &mHeaderVector;}

std::vector<CRegisteredObjectName>* CReportDefinition::getFooterAddr()
{return &mFooterVector;}

bool CReportDefinition::setTaskType(const CCopasiTask::Type & taskType)
{mTaskType = taskType; return true;}

const CCopasiTask::Type & CReportDefinition::getTaskType() const
  {return mTaskType;}

void CReportDefinition::setSeparator(const CCopasiStaticString& Separator)
{mSeparator = Separator;}

const CCopasiStaticString& CReportDefinition::getSeparator() const
  {return mSeparator;}

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

  CCopasiObjectName SeparatorCN(mSeparator.getCN());
  CCopasiObjectName Title;

  //std::vector< CCopasiContainer * > ListOfContainer;

  CCopasiObject* pSelectedObject;
  pSelectedObject = CCopasiContainer::ObjectFromName(cn);
  if (pSelectedObject)
    {
      if (!isFirst)
        {
          mHeaderVector.push_back(SeparatorCN);
          mBodyVector.push_back(SeparatorCN);
        }

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
