// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

CQReportListItem::CQReportListItem(const std::string & cn):
  QListWidgetItem(),
  mCN(cn)
{
  refreshText();
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

const CCopasiObjectName & CQReportListItem::getCN() const {return mCN;};

void CQReportListItem::refreshText()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  const CCopasiObject * pObject = pDataModel->getDataObject(mCN);

  if (pObject)
    setText(FROM_UTF8(pObject->getObjectDisplayName()));
  else
    setText(QString("Not found: ") + FROM_UTF8(mCN));
}
