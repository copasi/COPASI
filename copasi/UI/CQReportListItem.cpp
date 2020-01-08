// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include "copasi/copasi.h"

#include "CQReportListItem.h"
#include "qtUtilities.h"
#include "copasi/core/CDataString.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

CQReportListItem::CQReportListItem(const std::string & cn, CDataModel * pDataModel):
  QTableWidgetItem(),
  mCN(cn)
{
  refreshText(pDataModel);
}

CQReportListItem::CQReportListItem(const CDataObject * pObject):
  QTableWidgetItem(),
  mCN("")
{
  setObject(pObject);
}

CQReportListItem::~CQReportListItem() {}

const CCommonName &
CQReportListItem::getCN() const
{
  return mCN;
}

void
CQReportListItem::setObject(const CDataObject * pObject)
{
  if (pObject)
    {
      setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mCN = pObject->getCN();
    }
  else
    {
      setText(QString("Not found"));
      mCN = CDataString("NotFound").getCN();
    }
}

void CQReportListItem::refreshText(CDataModel * pDataModel)
{
  const CDataObject * pObject = CObjectInterface::DataObject(pDataModel->getObjectFromCN(mCN));

  if (pObject)
    setText(FROM_UTF8(pObject->getObjectDisplayName()));
  else
    setText(QString("Not found: ") + FROM_UTF8(mCN));
}
