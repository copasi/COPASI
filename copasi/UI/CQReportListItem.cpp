/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportListItem.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/11 17:59:10 $
   End CVS Header */

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
  else if (mCN.getObjectType() == "Separator")
    setText(QString("Separator"));
  else
    setText(QString("Not found: ") + FROM_UTF8(mCN));
}
