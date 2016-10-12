// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include "copasi.h"

#include "CQReportListItem.h"
#include "qtUtilities.h"
#include "report/CCopasiStaticString.h"
#include "report/CCopasiRootContainer.h"

CQReportListItem::CQReportListItem(const std::string & cn, CCopasiDataModel * pDataModel):
  QListWidgetItem(),
  mCN(cn)
{
  refreshText(pDataModel);
}

CQReportListItem::CQReportListItem(const CCopasiObject * pObject):
  QListWidgetItem(),
  mCN("")
{
  if (pObject)
    {
      setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mCN = pObject->getCN();
    }
  else
    {
      setText(QString("Not found"));
      mCN = CCopasiStaticString("NotFound").getCN();
    }
}

CQReportListItem::~CQReportListItem() {}

const CCopasiObjectName &
CQReportListItem::getCN() const
{
  return mCN;
}

void CQReportListItem::setObject(const CCopasiObject * pObject)
{
  if (pObject)
    {
      setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mCN = pObject->getCN();
    }
  else
    {
      setText(QString("Not found"));
      mCN = CCopasiStaticString("NotFound").getCN();
    }
}

void CQReportListItem::refreshText(CCopasiDataModel * pDataModel)
{
  const CCopasiObject * pObject = CObjectInterface::DataObject(pDataModel->getObjectFromCN(mCN));

  if (pObject)
    setText(FROM_UTF8(pObject->getObjectDisplayName()));
  else
    setText(QString("Not found: ") + FROM_UTF8(mCN));
}
