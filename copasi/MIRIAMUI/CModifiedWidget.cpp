// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CModifiedWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/20 19:06:27 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qlayout.h>
#include <qpushbutton.h>

#include "model/CModel.h"
#include "MIRIAM/CAuthor.h"
#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiObject.h"
#include "report/CKeyFactory.h"
#include "UI/qtUtilities.h"
#include "UI/CQMessageBox.h"
#include "UI/CQDateTimeEditTableItem.h"

#include "CModifiedWidget.h"

#define COL_MARK               0
#define COL_DATE_MODIFIED      1

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

    const CCopasiVector<CModified>& tmp = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getModifieds();

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void CModifiedWidget::init()
{
  mShowNewObjectWarning = false;
  numCols = 2;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_DATE_MODIFIED, "Date and Time Modified");
}

void CModifiedWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CModified *pModified = (const CModified*)obj;

  CQDateTimeEditTableItem* pDTWidget = NULL;
  if (dynamic_cast<CQDateTimeEditTableItem *>(table->cellWidget(row, COL_DATE_MODIFIED)))
    {
      pDTWidget = static_cast<CQDateTimeEditTableItem *>(table->cellWidget(row, COL_DATE_MODIFIED));
    }
  else
    {
      pDTWidget = new CQDateTimeEditTableItem(this, row, COL_DATE_MODIFIED, table);
      pDTWidget->dateEdit()->setRange(QDate(), QDate::currentDate());
      table->setCellWidget(row, COL_DATE_MODIFIED, pDTWidget);
    }
  pDTWidget->setDateTime(QDateTime::fromString(FROM_UTF8(pModified->getDateModified()), Qt::ISODate));
}

void CModifiedWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CModified * pModified = static_cast< CModified * >(obj);

  if (dynamic_cast<CQDateTimeEditTableItem *>(table->cellWidget(row, COL_DATE_MODIFIED)))
    {
      CQDateTimeEditTableItem * pDTE = static_cast<CQDateTimeEditTableItem *> (table->cellWidget(row, COL_DATE_MODIFIED));
      std::string dt = "";
      if (pDTE->dateTime().toString(Qt::ISODate).ascii())
      {dt = pDTE->dateTime().toString(Qt::ISODate).ascii();}
      pModified->setDateModified(dt);
    }
}

void CModifiedWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != COL_DATE_MODIFIED)
    {
      if (!dynamic_cast<CQDateTimeEditTableItem *>(table->cellWidget(row, COL_DATE_MODIFIED)))
        {
          CQDateTimeEditTableItem* pDTE = new CQDateTimeEditTableItem(this, row, COL_DATE_MODIFIED, table);
          pDTE->dateEdit()->setRange(QDate(), QDate::currentDate());
          table->setCellWidget(row, COL_DATE_MODIFIED, pDTE);
        }
    }
}

QString CModifiedWidget::defaultObjectName() const
  {return "Modified";}

CCopasiObject* CModifiedWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CModified* pModified = NULL;

  while (!(pModified = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().createModified(name)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }

  return pModified;
}

void CModifiedWidget::deleteObjects(const std::vector<std::string> & keys)
{

  QString modifiedList = "Are you sure you want to delete listed Modified Date(s) ?\n";
  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      CModified * pModified =
        dynamic_cast< CModified *>(GlobalKeys.get(keys[i]));

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
            CCopasiDataModel::Global->getModel()->getMIRIAMInfo().removeModified(keys[i]);
          }

        //for (i = 0; i < imax; i++)
        //protectedNotify(ListViews::MODEL, ListViews::DELETE, keys[i]);

        mChanged = true;
        break;
      }
    default:                                           // No or Escape
      break;
    }
}
