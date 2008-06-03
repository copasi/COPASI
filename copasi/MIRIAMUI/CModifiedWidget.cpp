// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CModifiedWidget.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/03 13:21:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qlayout.h>
#include <qpushbutton.h>

#include "copasi.h"

#include "CQMiriamWidget.h"
#include "CModifiedWidget.h"

#include "MIRIAM/CModelMIRIAMInfo.h"

#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiObject.h"
#include "report/CKeyFactory.h"
#include "UI/qtUtilities.h"
#include "UI/CQMessageBox.h"
#include "UI/CQDateTimeEditTableItem.h"

#define COL_MARK               0
#define COL_DUMMY              1
#define COL_DATE_MODIFIED      2

/*
 *  Constructs a CModifiedWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CModifiedWidget::CModifiedWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiTableWidget(parent, false, name, f, false)
{
  if (!name)
    CopasiTableWidget::setName("ModifiedWidget");
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CModifiedWidget::~CModifiedWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

std::vector<const CCopasiObject*> CModifiedWidget::getObjects() const
  {
    std::vector<const CCopasiObject*> ret;

    if (dynamic_cast <CQMiriamWidget*> (parentWidget()))
      {
        const CCopasiVector<CModification>& tmp = dynamic_cast <CQMiriamWidget*> (parentWidget())->getMIRIAMInfo().getModifications();

        C_INT32 i, imax = tmp.size();
        for (i = 0; i < imax; ++i)
          ret.push_back(tmp[i]);
      }

    return ret;
  }

void CModifiedWidget::init()
{
  mShowNewObjectWarning = false;
  numCols = 3;
  table->setNumCols(numCols);
  table->setMinimumHeight(70);
  table->setMinimumWidth(300);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_DUMMY, "Dummy");
  tableHeader->setLabel(COL_DATE_MODIFIED, "Date and Time Modified");
  table->hideColumn(COL_DUMMY);
}

void CModifiedWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CModification *pModified = (const CModification*)obj;

  CQDateTimeEditTableItem* pDTE = NULL;
  if (dynamic_cast<CQDateTimeEditTableItem *>(table->cellWidget(row, COL_DATE_MODIFIED)))
    {
      pDTE = static_cast<CQDateTimeEditTableItem *>(table->cellWidget(row, COL_DATE_MODIFIED));
    }
  else
    {
      pDTE = new CQDateTimeEditTableItem(this, row, COL_DATE_MODIFIED, table);
      pDTE->dateEdit()->setRange(QDate(), QDate::currentDate());
      table->setCellWidget(row, COL_DATE_MODIFIED, pDTE);
    }
  if (pModified)
    {
      const std::string strDT = pModified->getDate();
      if (strDT.length())
      {pDTE->setDateTime(QDateTime::fromString(FROM_UTF8(strDT), Qt::ISODate));}
    }
}

void CModifiedWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CModification * pModified = static_cast< CModification * >(obj);

  if (dynamic_cast<CQDateTimeEditTableItem *>(table->cellWidget(row, COL_DATE_MODIFIED)))
    {
      CQDateTimeEditTableItem * pDTE = static_cast<CQDateTimeEditTableItem *> (table->cellWidget(row, COL_DATE_MODIFIED));
      std::string dt = "";
      if (pDTE->dateTime().isValid())
        dt = pDTE->dateTime().toString(Qt::ISODate).utf8();

      pModified->setDate(dt);
    }
}

void CModifiedWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != COL_DATE_MODIFIED)
    {
      CQDateTimeEditTableItem* pDTE = NULL;
      pDTE = new CQDateTimeEditTableItem(this, row, COL_DATE_MODIFIED, table);
      pDTE->dateEdit()->setRange(QDate(), QDate::currentDate());
      table->setCellWidget(row, COL_DATE_MODIFIED, pDTE);
    }
}

QString CModifiedWidget::defaultObjectName() const
  {return "";}

CCopasiObject* CModifiedWidget::createNewObject(const std::string & name)
{
  if (!dynamic_cast <CQMiriamWidget*> (parentWidget()))
    return NULL;
  std::string nname = name;
  int i = 0;
  CModification* pModified = NULL;

  while (!(pModified = dynamic_cast <CQMiriamWidget*> (parentWidget())->getMIRIAMInfo().createModification(name)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }

  return pModified;
}

void CModifiedWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (!dynamic_cast <CQMiriamWidget*> (parentWidget()))
    return;

  QString modifiedList = "Are you sure you want to delete listed Modified Date(s) ?\n";
  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      CModification * pModified =
        dynamic_cast< CModification *>(GlobalKeys.get(keys[i]));

      modifiedList.append(FROM_UTF8(pModified->getObjectName()));
      modifiedList.append(", ");
    }

  modifiedList.remove(modifiedList.length() - 2, 2);

  QString msg = modifiedList;

  C_INT32 choice = 0;
  choice = CQMessageBox::question(this,
                                  "CONFIRM DELETE",
                                  msg,
                                  "Continue", "Cancel", 0, 1, 1);

  switch (choice)
    {
    case 0:                                           // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            dynamic_cast <CQMiriamWidget*> (parentWidget())->getMIRIAMInfo().removeModification(keys[i]);
          }

        for (i = 0; i < imax; i++)
          protectedNotify(mOT, ListViews::DELETE, keys[i]);

        mChanged = true;
        break;
      }
    default:                                           // No or Escape
      break;
    }
}

void CModifiedWidget::slotDoubleClicked(int C_UNUSED(row), int C_UNUSED(col),
                                        int C_UNUSED(m), const QPoint & C_UNUSED(n))
{}
