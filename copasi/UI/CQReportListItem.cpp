/* Begin CVS Header
$Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportListItem.cpp,v $
$Revision: 1.5 $
$Name:  $
$Author: gauges $
$Date: 2009/02/19 15:37:56 $
End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include "copasi.h"

#include "CQReportListItem.h"
#include "qtUtilities.h"
#include "report/CCopasiStaticString.h"
#include "report/CCopasiRootContainer.h"

CQReportListItem::CQReportListItem(Q3ListBox * pListBox,
                                   const std::string & cn):
    Q3ListBoxText(pListBox, ""),
    mCN(cn)
{
  refreshText();
}

CQReportListItem::CQReportListItem(Q3ListBox * pListBox,
                                   const CCopasiObject * pObject):
    Q3ListBoxText(pListBox, ""),
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

void CQReportListItem::setText(const QString & text)
{Q3ListBoxText::setText(text);}

const CCopasiObjectName & CQReportListItem::getCN() const {return mCN;};

void CQReportListItem::refreshText()
{
  assert(CCopasiRootContainer::Root->getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::Root->getDatamodelList())[0];
  assert(pDataModel != NULL);
  CCopasiObject * pObject = pDataModel->ObjectFromName(mCN);

  if (pObject)
    setText(FROM_UTF8(pObject->getObjectDisplayName()));
  else
    setText(QString("Not found: ") + FROM_UTF8(mCN));
}
