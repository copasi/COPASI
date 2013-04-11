// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

/**
 *  CReportTemplate class.
 *  This class describes the Report Template
 *
 *  Created for Copasi by Mudita Singhal
 */

#include "copasi.h"

#include "CKeyFactory.h"
#include "CReportTemplate.h"
#include "CReport.h"

#include "utilities/CCopasiMessage.h"
#include "copasi/report/CCopasiRootContainer.h"

//////////////////////////////////////////////////
//
//class CReportTemplate
//
//////////////////////////////////////////////////
CReportTemplate::CReportTemplate(const std::string & name,
                                     const CCopasiContainer * pParent):
    CCopasiObject(name, pParent, "ReportTemplate"),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Report", this)),
    mComment(""),
    mTaskType(CCopasiTask::timeCourse),
    mSeparator("\t"),
    mTable(true),
    mbTitle(true),
    mPrecision(6)
{}

CReportTemplate::CReportTemplate(const CReportTemplate & src,
                                     const CCopasiContainer * pParent):
    CCopasiObject(src, pParent),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Report", this)),
    mComment(src.mComment),
    mTaskType(src.mTaskType),
    mSeparator(src.mSeparator),
    mTable(src.mTable),
    mbTitle(src.mbTitle),
    mPrecision(src.mPrecision)
{}

CReportTemplate::~CReportTemplate()
{cleanup();}

void CReportTemplate::cleanup()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
  mHeaderVector.clear();
  mBodyVector.clear();
  mFooterVector.clear();
  mTableVector.clear();
}

bool CReportTemplate::preCompileTable(const std::vector< CCopasiContainer * > & listOfContainer)
{
  bool success = true;

  mHeaderVector.clear();
  mBodyVector.clear();
  mFooterVector.clear();

  std::vector<CRegisteredObjectName>::const_iterator it = mTableVector.begin();
  std::vector<CRegisteredObjectName>::const_iterator end = mTableVector.end();

  CCopasiDataModel* pDataModel = getObjectDataModel();
  CCopasiObject * pObject;

  for (; it != end; ++it)
    {
      pObject = pDataModel->ObjectFromName(listOfContainer, *it);

      if (pObject != NULL)
        {
          addTableElement(pObject);
        }
      else
        {
          CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 6, it->c_str());
        }
    }

  return success;
}

std::vector<CRegisteredObjectName>* CReportTemplate::getBodyAddr()
{return &mBodyVector;}

std::vector<CRegisteredObjectName>* CReportTemplate::getHeaderAddr()
{return &mHeaderVector;}

std::vector<CRegisteredObjectName>* CReportTemplate::getFooterAddr()
{return &mFooterVector;}

std::vector<CRegisteredObjectName>* CReportTemplate::getTableAddr()
{return &mTableVector;}

bool CReportTemplate::setTaskType(const CCopasiTask::Type & taskType)
{mTaskType = taskType; return true;}

const CCopasiTask::Type & CReportTemplate::getTaskType() const
{return mTaskType;}

void CReportTemplate::setSeparator(const CCopasiReportSeparator & Separator)
{mSeparator = Separator;}

const CCopasiReportSeparator & CReportTemplate::getSeparator() const
{return mSeparator;}

bool CReportTemplate::getTitle() const
{return mbTitle;}

void CReportTemplate::setTitle(bool title)
{mbTitle = title;}

bool CReportTemplate::isTable() const
{return mTable;}

void CReportTemplate::setIsTable(bool table)
{mTable = table;}

void CReportTemplate::setPrecision(const unsigned C_INT32 & precision)
{mPrecision = precision;}

const unsigned C_INT32 & CReportTemplate::getPrecision() const
{return mPrecision;}

const std::string & CReportTemplate::getKey() const
{return mKey;}

void CReportTemplate::addTableElement(const CCopasiObject * pObject)
{
  bool isFirst = false;

  if ((mHeaderVector.size() == 0) && (mBodyVector.size() == 0))
    isFirst = true;

  CCopasiObjectName SeparatorCN(mSeparator.getCN());
  CCopasiObjectName Title;

  if (!pObject) return;

  // Add separator
  if (!isFirst)
    {
      if (mbTitle)
        mHeaderVector.push_back(SeparatorCN);

      mBodyVector.push_back(SeparatorCN);
    }

  // Determine column title
  if (pObject->getObjectParent())
    {
      Title = pObject->getCN() + ",Property=DisplayName";
    }
  else
    Title =
      CCopasiStaticString(pObject->getObjectName()).getCN();

  if (mbTitle)
    mHeaderVector.push_back(Title);

  mBodyVector.push_back(pObject->getCN());

  return;
}
