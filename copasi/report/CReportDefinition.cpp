// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CReportDefinition class.
 *  This class describes the Report Definition
 *
 *  Created for COPASI by Mudita Singhal
 */

#include "copasi.h"

#include "CKeyFactory.h"
#include "CReportDefinition.h"
#include "CReport.h"

#include "utilities/CCopasiMessage.h"
#include "copasi/undo/CData.h"
#include "copasi/core/CRootContainer.h"

//////////////////////////////////////////////////
//
//class CReportDefinition
//
//////////////////////////////////////////////////
// static
CReportDefinition * CReportDefinition::fromData(const CData & data)
{
  return new CReportDefinition(data.getProperty(CData::OBJECT_NAME).toString(),
                               NO_PARENT);
}

// virtual
CData CReportDefinition::toData() const
{
  CData Data = CDataObject::toData();

  Data.addProperty(CData::Property::COMMENT, mComment);
  Data.addProperty(CData::Property::TASK_TYPE, CTaskEnum::TaskName[mTaskType]);
  Data.addProperty(CData::Property::REPORT_SEPARATOR, mSeparator.getStaticString());
  Data.addProperty(CData::Property::REPORT_IS_TABLE, mTable);
  Data.addProperty(CData::Property::REPORT_SHOW_TITLE, mbTitle);
  Data.addProperty(CData::Property::REPORT_PRECISION, mPrecision);

  return Data;
}

// virtual
bool CReportDefinition::applyData(const CData & data)
{
  bool success = CDataObject::applyData(data);

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CReportDefinition::CReportDefinition(const std::string & name,
                                     const CDataContainer * pParent):
  CDataObject(name, pParent, "ReportDefinition"),
  mKey(CRootContainer::getKeyFactory()->add("Report", this)),
  mComment(""),
  mTaskType(CTaskEnum::Task::timeCourse),
  mSeparator("\t"),
  mTable(true),
  mbTitle(true),
  mPrecision(6)
{}

CReportDefinition::CReportDefinition(const CReportDefinition & src,
                                     const CDataContainer * pParent):
  CDataObject(src, pParent),
  mKey(CRootContainer::getKeyFactory()->add("Report", this)),
  mComment(src.mComment),
  mTaskType(src.mTaskType),
  mSeparator(src.mSeparator, NO_PARENT),
  mTable(src.mTable),
  mbTitle(src.mbTitle),
  mPrecision(src.mPrecision),
  mHeaderVector(src.mHeaderVector),
  mBodyVector(src.mBodyVector),
  mFooterVector(src.mFooterVector),
  mTableVector(src.mTableVector)
{}

CReportDefinition::~CReportDefinition()
{cleanup();}

void CReportDefinition::cleanup()
{
  CRootContainer::getKeyFactory()->remove(mKey);
  mHeaderVector.clear();
  mBodyVector.clear();
  mFooterVector.clear();
  mTableVector.clear();
}

bool CReportDefinition::preCompileTable(const CObjectInterface::ContainerList & listOfContainer)
{
  bool success = true;

  mHeaderVector.clear();
  mBodyVector.clear();
  mFooterVector.clear();

  std::vector<CRegisteredCommonName>::const_iterator it = mTableVector.begin();
  std::vector<CRegisteredCommonName>::const_iterator end = mTableVector.end();

  for (; it != end; ++it)
    {
      const CDataObject * pObject = CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(listOfContainer, *it));

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

/**
*Returns the comments in the report tag
*/

const std::string & CReportDefinition::getComment() const
{
  return mComment;
}

/**
*sets the comments in the report tag
*/

void 
CReportDefinition::setComment(const std::string & comment)
{
  mComment = comment;
}

std::vector<CRegisteredCommonName>* CReportDefinition::getBodyAddr()
{return &mBodyVector;}

const std::vector<CRegisteredCommonName>* CReportDefinition::getBodyAddr() const
{return &mBodyVector;}

std::vector<CRegisteredCommonName>* CReportDefinition::getHeaderAddr()
{return &mHeaderVector;}

const std::vector<CRegisteredCommonName>* CReportDefinition::getHeaderAddr() const
{return &mHeaderVector;}

std::vector<CRegisteredCommonName>* CReportDefinition::getFooterAddr()
{return &mFooterVector;}

const std::vector<CRegisteredCommonName>* CReportDefinition::getFooterAddr() const
{return &mFooterVector;}

std::vector<CRegisteredCommonName>* CReportDefinition::getTableAddr()
{return &mTableVector;}

const std::vector<CRegisteredCommonName>* CReportDefinition::getTableAddr() const
{return &mTableVector;}

bool CReportDefinition::setTaskType(const CTaskEnum::Task & taskType)
{mTaskType = taskType; return true;}

const CTaskEnum::Task & CReportDefinition::getTaskType() const
{return mTaskType;}

void CReportDefinition::setSeparator(const std::string & separator)
{mSeparator = separator;}

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

void CReportDefinition::addTableElement(const CDataObject * pObject)
{
  bool isFirst = false;

  if ((mHeaderVector.size() == 0) && (mBodyVector.size() == 0))
    isFirst = true;

  CCommonName SeparatorCN(mSeparator.getCN());
  CCommonName Title;

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
      if (pObject->getObjectType() == "Separator")
        {
          Title = "Separator=" + pObject->getCN().getObjectName();
        }
      else
        {
          Title = pObject->getCN() + ",Property=DisplayName";
        }
    }
  else
    Title =
      CDataString(pObject->getObjectName()).getCN();

  if (mbTitle)
    mHeaderVector.push_back(Title);

  if (pObject->getObjectType() == "Separator")
    {
      mBodyVector.push_back("Separator=" + pObject->getCN().getObjectName());
    }
  else
    {
      mBodyVector.push_back(pObject->getCN());
    }

  return;
}
