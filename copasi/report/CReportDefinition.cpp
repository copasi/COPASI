// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportDefinition.cpp,v $
//   $Revision: 1.40 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/23 18:52:49 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CReportDefinition class.
 *  This class describes the Report Definition
 *
 *  Created for Copasi by Mudita Singhal
 */

#include "copasi.h"

#include "CKeyFactory.h"
#include "CReportDefinition.h"
#include "CReport.h"

#include "utilities/CCopasiMessage.h"

//////////////////////////////////////////////////
//
//class CReportDefinition
//
//////////////////////////////////////////////////
CReportDefinition::CReportDefinition(const std::string & name,
                                     const CCopasiContainer * pParent):
    CCopasiObject(name, pParent, "ReportDefinition"),
    mKey(GlobalKeys.add("Report", this)),
    mComment(""),
    mTaskType(CCopasiTask::timeCourse),
    mSeparator("\t"),
    mTable(true),
    mbTitle(true),
    mPrecision(6)
{}

CReportDefinition::CReportDefinition(const CReportDefinition & src,
                                     const CCopasiContainer * pParent):
    CCopasiObject(src, pParent),
    mKey(GlobalKeys.add("Report", this)),
    mComment(src.mComment),
    mTaskType(src.mTaskType),
    mSeparator(src.mSeparator),
    mTable(src.mTable),
    mbTitle(src.mbTitle),
    mPrecision(src.mPrecision)
{}

CReportDefinition::~CReportDefinition()
{cleanup();}

void CReportDefinition::cleanup()
{
  GlobalKeys.remove(mKey);
  mHeaderVector.clear();
  mBodyVector.clear();
  mFooterVector.clear();
  mTableVector.clear();
}

bool CReportDefinition::preCompileTable(const std::vector< CCopasiContainer * > & listOfContainer)
{
  bool success = true;

  mHeaderVector.clear();
  mBodyVector.clear();
  mFooterVector.clear();

  std::vector<CRegisteredObjectName>::const_iterator it = mTableVector.begin();
  std::vector<CRegisteredObjectName>::const_iterator end = mTableVector.end();

  CCopasiObject * pObject;

  for (; it != end; ++it)
    {
      pObject = CCopasiContainer::ObjectFromName(listOfContainer, *it);

      if (!pObject)
        CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 6, it->c_str());
      else
        addTableElement(CCopasiContainer::ObjectFromName(listOfContainer, *it));
    }

  return success;
}

std::vector<CRegisteredObjectName>* CReportDefinition::getBodyAddr()
{return &mBodyVector;}

std::vector<CRegisteredObjectName>* CReportDefinition::getHeaderAddr()
{return &mHeaderVector;}

std::vector<CRegisteredObjectName>* CReportDefinition::getFooterAddr()
{return &mFooterVector;}

std::vector<CRegisteredObjectName>* CReportDefinition::getTableAddr()
{return &mTableVector;}

bool CReportDefinition::setTaskType(const CCopasiTask::Type & taskType)
{mTaskType = taskType; return true;}

const CCopasiTask::Type & CReportDefinition::getTaskType() const
  {return mTaskType;}

void CReportDefinition::setSeparator(const CCopasiReportSeparator & Separator)
{mSeparator = Separator;}

const CCopasiReportSeparator & CReportDefinition::getSeparator() const
  {return mSeparator;}

bool CReportDefinition::getTitle() const
  {return mbTitle;}

void CReportDefinition::setTitle(bool title)
{mbTitle = title;}

bool CReportDefinition::isTable() const
  {return mTable;}

void CReportDefinition::setIsTable(bool table)
{mTable = table;}

void CReportDefinition::setPrecision(const unsigned C_INT32 & precision)
{mPrecision = precision;}

const unsigned C_INT32 & CReportDefinition::getPrecision() const
  {return mPrecision;}

const std::string & CReportDefinition::getKey() const
  {return mKey;}

void CReportDefinition::addTableElement(const CCopasiObject * pObject)
{
  bool isFirst = false;
  if ((mHeaderVector.size() == 0) && (mBodyVector.size() == 0))
    isFirst = true;

  CCopasiObjectName SeparatorCN(mSeparator.getCN());
  CCopasiObjectName Title;

  if (!pObject) return;

  if (!isFirst)
    {
      mHeaderVector.push_back(SeparatorCN);
      mBodyVector.push_back(SeparatorCN);
    }

  if (pObject->getObjectParent())
    {
      Title =
        pObject->getObjectParent()->getCN();
      Title += ",Reference=Name";
      getHeaderAddr()->push_back(Title);

      Title =
        CCopasiStaticString("[" + pObject->getObjectName() + "]").getCN();
    }
  else
    Title =
      CCopasiStaticString(pObject->getObjectName()).getCN();

  mHeaderVector.push_back(Title);
  mBodyVector.push_back(pObject->getCN());

  return;
}
