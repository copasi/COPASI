// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CReferencesWidget.cpp,v $
//   $Revision: 1.8.6.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/01 17:47:12 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qlayout.h>
#include <qpushbutton.h>

#include "copasi.h"

#include "MIRIAM/CReference.h"
#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "commandline/CConfigurationFile.h"
#include "report/CCopasiObject.h"
#include "report/CKeyFactory.h"
#include "UI/qtUtilities.h"
#include "UI/CQMessageBox.h"

#include "CQMiriamWidget.h"
#include "CReferencesWidget.h"

#define COL_MARK               0
#define COL_DUMMY              1
#define COL_RESOURCE           2
#define COL_ID                 3
#define COL_DESCRIPTION        4

/*
 *  Constructs a CReferencesWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CReferencesWidget::CReferencesWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiTableWidget(parent, false, name, f, false)
{
  if (!name)
    CopasiTableWidget::setName("ReferencesWidget");

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CReferencesWidget::~CReferencesWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

std::vector<const CCopasiObject*> CReferencesWidget::getObjects() const
  {
    std::vector<const CCopasiObject*> ret;

    if (dynamic_cast <CQMiriamWidget*> (parentWidget()))
      {
        const CCopasiVector<CReference>& tmp = dynamic_cast <CQMiriamWidget*> (parentWidget())->getMIRIAMInfo().getReferences();

        C_INT32 i, imax = tmp.size();
        for (i = 0; i < imax; ++i)
          ret.push_back(tmp[i]);
      }

    return ret;
  }

void CReferencesWidget::init()
{
  mOT = ListViews::MIRIAM;
  //flagtoAdjust = false;
  mShowNewObjectWarning = false;
  numCols = 5;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_RESOURCE, "Resource");
  tableHeader->setLabel(COL_ID, "ID");
  tableHeader->setLabel(COL_DESCRIPTION, "Description");
  table->hideColumn(COL_DUMMY);

  updateResourcesList();
}

void CReferencesWidget::updateResourcesList()
{
  mResources.clear();
  // Build the list of known resources
  const CMIRIAMResources * pResource = &CCopasiDataModel::Global->getConfiguration()->getRecentMIRIAMResources();
  mResources.push_back("-- select --");

  unsigned C_INT32 i, imax = pResource->getResourceList().size();
  for (i = 0; i < imax; i++)
    if (pResource->getMIRIAMResource(i).getMIRIAMCitation())
      mResources.push_back(FROM_UTF8(pResource->getMIRIAMResource(i).getMIRIAMDisplayName()));
}

void CReferencesWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CReference *pReference = (const CReference*)obj;

  table->setText(row, COL_DUMMY, QString::number(row));

  QComboTableItem * pComboBox = NULL;
  if ((pComboBox = dynamic_cast<QComboTableItem *>(table->item(row, COL_RESOURCE))) == NULL)
    {
      pComboBox = new QComboTableItem(table, mResources);
      table->setItem(row, COL_RESOURCE, pComboBox);
    }

  std::string Resource = pReference->getResource();
  if (Resource == "")
    pComboBox->setCurrentItem(0);
  else
    pComboBox->setCurrentItem(FROM_UTF8(Resource));

  table->setText(row, COL_ID, FROM_UTF8(pReference->getId()));
  table->setText(row, COL_DESCRIPTION, FROM_UTF8(pReference->getDescription()));
}

void CReferencesWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CReference * pReference = static_cast< CReference * >(obj);

  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_RESOURCE)))
    {
      QString resource = static_cast<QComboTableItem *>(table->item(row, COL_RESOURCE))->currentText();
      pReference->setResource((const char *) resource.utf8());
    }

  QString ID = table->text(row, COL_ID);
  pReference->setId((const char *) ID.utf8());
  pReference->setDescription((const char *) table->text(row, COL_DESCRIPTION).utf8());
  pReference->clearInvalidEntries();
}

void CReferencesWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != COL_RESOURCE)
    {
      QComboTableItem * pComboBox = new QComboTableItem(table, mResources);
      pComboBox->setCurrentItem(0);
      table->setItem(row, COL_RESOURCE, pComboBox);
    }

  if (exc != COL_ID)
    table->clearCell(row, COL_ID);

  if (exc != COL_DESCRIPTION)
    table->clearCell(row, COL_DESCRIPTION);
}

QString CReferencesWidget::defaultObjectName() const
{return "";}

CCopasiObject* CReferencesWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CReference* pReference = NULL;

  if (!dynamic_cast <CQMiriamWidget*> (parentWidget()))
    return NULL;

  while (!(pReference = dynamic_cast <CQMiriamWidget*> (parentWidget())->getMIRIAMInfo().createReference(name)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }

  return pReference;
}

void CReferencesWidget::deleteObjects(const std::vector<std::string> & keys)
{
  CQMiriamWidget * pMiriamWidget = dynamic_cast <CQMiriamWidget*> (parentWidget());
  if (pMiriamWidget == NULL)
    return;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++)
    pMiriamWidget->getMIRIAMInfo().removeReference(keys[i]);

  for (i = 0; i < imax; i++)
    protectedNotify(mOT, ListViews::DELETE, keys[i]);

  mChanged = true;
}

void CReferencesWidget::slotDoubleClicked(int C_UNUSED(row), int C_UNUSED(col),
    int C_UNUSED(m), const QPoint & C_UNUSED(n))
{}

void CReferencesWidget::slotValueChanged(int row, int col)
{
  if (col == COL_RESOURCE)
    {
      int selectedItem = -1;
      if (row == table->numRows() - 1) //new Object
        {
          if (dynamic_cast<QComboTableItem *>(table->item(row, col)))
            {
              selectedItem = static_cast<QComboTableItem *>(table->item(row, col))->currentItem();
            }
        }
      CopasiTableWidget::slotValueChanged(row, col);
      if (selectedItem > -1)
      {static_cast<QComboTableItem *>(table->item(row, col))->setCurrentItem(selectedItem);}
    }
  else
  {CopasiTableWidget::slotValueChanged(row, col);}
}
