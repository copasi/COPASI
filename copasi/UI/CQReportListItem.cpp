/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportListItem.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:42 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include "copasi.h"

#include "CQReportListItem.h"
#include "qtUtilities.h"
#include "report/CCopasiStaticString.h"

CQReportListItem::CQReportListItem(QListBox * pListBox,
                                   const std::string & cn):
    QListBoxText(pListBox, ""),
    mCN(cn)
{
  refreshText();
}

CQReportListItem::CQReportListItem(QListBox * pListBox,
                                   const CCopasiObject * pObject):
    QListBoxText(pListBox, ""),
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
{QListBoxText::setText(text);}

const CCopasiObjectName & CQReportListItem::getCN() const {return mCN;};

void CQReportListItem::refreshText()
{
  CCopasiObject * pObject = CCopasiContainer::ObjectFromName(mCN);

  if (pObject)
    setText(FROM_UTF8(pObject->getObjectDisplayName()));
  else
    setText(QString("Not found: ") + FROM_UTF8(mCN));
}
