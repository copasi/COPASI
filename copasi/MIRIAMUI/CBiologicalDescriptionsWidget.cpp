// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CBiologicalDescriptionsWidget.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/04/21 20:12:32 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qlayout.h>
#include <qpushbutton.h>
#include <sstream>

#include "MIRIAM/CBiologicalDescription.h"
#include "MIRIAM/CConstants.h"
#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiObject.h"
#include "report/CKeyFactory.h"
#include "UI/qtUtilities.h"
#include "UI/CQMessageBox.h"

#include "CMIRIAMModelWidget.h"
#include "CBiologicalDescriptionsWidget.h"

#define COL_MARK               0
#define COL_DUMMY              1
#define COL_RELATIONSHIP       2
#define COL_RESOURCE           3
#define COL_ID                 4

/*
 *  Constructs a CBiologicalDescriptionsWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CBiologicalDescriptionsWidget::CBiologicalDescriptionsWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiTableWidget(parent, false, name, f, false)
{
  if (!name)
    CopasiTableWidget::setName("BiologicalDescriptionsWidget");
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CBiologicalDescriptionsWidget::~CBiologicalDescriptionsWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

std::vector<const CCopasiObject*> CBiologicalDescriptionsWidget::getObjects() const
  {
    std::vector<const CCopasiObject*> ret;

    if (dynamic_cast <CMIRIAMModelWidget*> (parentWidget()))
      {
        const CCopasiVector<CBiologicalDescription>& tmp = dynamic_cast <CMIRIAMModelWidget*> (parentWidget())->getMIRIAMInfo().getBiologicalDescriptions();

        C_INT32 i, imax = tmp.size();
        for (i = 0; i < imax; ++i)
          ret.push_back(tmp[i]);
      }

    return ret;
  }

void CBiologicalDescriptionsWidget::init()
{
  //flagtoAdjust = false;
  mShowNewObjectWarning = false;
  numCols = 5;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_DUMMY, "Dummy");
  tableHeader->setLabel(COL_RELATIONSHIP, "Relationship");
  tableHeader->setLabel(COL_RESOURCE, "Resource");
  tableHeader->setLabel(COL_ID, "ID");
  table->hideColumn(COL_DUMMY);
  //table->setColumnWidth(COL_ID, 200);

  std::map<std::string, std::string> map = CConstants::getRelationships();
  std::map<std::string, std::string>::const_iterator it = map.begin();
  std::map<std::string, std::string>::const_iterator end = map.end();
  for (; it != end; it++)
  {mRelationships.push_back(FROM_UTF8(it->second));}

  map = CConstants::getResources();
  it = map.begin();
  end = map.end();
  for (; it != end; it++)
  {mResources.push_back(FROM_UTF8(it->first));}
}

void CBiologicalDescriptionsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CBiologicalDescription *pBiologicalDescription = (const CBiologicalDescription*)obj;

  table->setText(row, COL_DUMMY, QString::number(row));

  QComboTableItem * pComboBox = NULL;
  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_RELATIONSHIP)))
    {
      pComboBox = static_cast<QComboTableItem *>(table->item(row, COL_RELATIONSHIP));
      pComboBox->setCurrentItem(FROM_UTF8(pBiologicalDescription->getRelationship()));
    }
  else
    {
      pComboBox = new QComboTableItem(table, mRelationships);
      pComboBox->setCurrentItem(FROM_UTF8(pBiologicalDescription->getRelationship()));
      table->setItem(row, COL_RELATIONSHIP, pComboBox);
    }

  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_RESOURCE)))
    {
      pComboBox = static_cast<QComboTableItem *>(table->item(row, COL_RESOURCE));
      pComboBox->setCurrentItem(FROM_UTF8(pBiologicalDescription->getResource()));
    }
  else
    {
      pComboBox = new QComboTableItem(table, mResources);
      pComboBox->setCurrentItem(FROM_UTF8(pBiologicalDescription->getResource()));
      table->setItem(row, COL_RESOURCE, pComboBox);
    }

  table->setText(row, COL_ID, FROM_UTF8(pBiologicalDescription->getId()));
}

void CBiologicalDescriptionsWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CBiologicalDescription * pBiologicalDescription = static_cast< CBiologicalDescription * >(obj);

  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_RELATIONSHIP)))
    {
      const std::string relationship = (const char *) static_cast<QComboTableItem *>(table->item(row, COL_RELATIONSHIP))->currentText().utf8();
      //Don't handle this and return if relationship is changed.
      if (pBiologicalDescription->getRelationship() != relationship)
      {return;}
    }

  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_RESOURCE)))
    {
      QString resource = static_cast<QComboTableItem *>(table->item(row, COL_RESOURCE))->currentText();
      QString ID = table->text(row, COL_ID);
      pBiologicalDescription->setId((const char *) ID.utf8(), (const char *) resource.utf8());
    }
}

void CBiologicalDescriptionsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != COL_RELATIONSHIP)
    {
      QComboTableItem * pComboBox = new QComboTableItem(table, mRelationships);
      pComboBox->setCurrentItem(0);
      table->setItem(row, COL_RELATIONSHIP, pComboBox);
    }

  if (exc != COL_RESOURCE)
    {
      QComboTableItem * pComboBox = new QComboTableItem(table, mResources);
      pComboBox->setCurrentItem(0);
      table->setItem(row, COL_RESOURCE, pComboBox);
    }

  if (exc != COL_ID)
    table->clearCell(row, COL_ID);
}

QString CBiologicalDescriptionsWidget::defaultObjectName() const
{return "";}

CCopasiObject* CBiologicalDescriptionsWidget::createNewObject(const std::string & name)
{
  if (!dynamic_cast <CMIRIAMModelWidget*> (parentWidget()))
    return NULL;
  std::string nname = name;
  int i = 0;
  CBiologicalDescription* pBiologicalDescription = NULL;

  std::istringstream ss(name);
  unsigned C_INT32 row;
  ss >> row;
  const std::string relationship = (const char *) static_cast<QComboTableItem *>(table->item(row, COL_RELATIONSHIP))->currentText().utf8();
  const std::map<std::string, std::string> relationships = CConstants::getRelationships();
  std::string newTableName = CConstants::getKey(relationships, relationship);

  while (!(pBiologicalDescription = dynamic_cast <CMIRIAMModelWidget*> (parentWidget())->getMIRIAMInfo().createBiologicalDescription(name, newTableName)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }

  return pBiologicalDescription;
}

void CBiologicalDescriptionsWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (!dynamic_cast <CMIRIAMModelWidget*> (parentWidget()))
    return;

  QString BiologicalDescriptionList = "Are you sure you want to delete listed BIOLOGICAL DESCRIPTION(S) ?\n";
  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      CBiologicalDescription * pBiologicalDescription =
        dynamic_cast< CBiologicalDescription *>(GlobalKeys.get(keys[i]));

      BiologicalDescriptionList.append(FROM_UTF8(pBiologicalDescription->getObjectName()));
      BiologicalDescriptionList.append(", ");
    }

  BiologicalDescriptionList.remove(BiologicalDescriptionList.length() - 2, 2);

  QString msg = BiologicalDescriptionList;

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
            dynamic_cast <CMIRIAMModelWidget*> (parentWidget())->getMIRIAMInfo().removeBiologicalDescription(keys[i]);
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

void CBiologicalDescriptionsWidget::saveTable()
{
  if (!dynamic_cast <CMIRIAMModelWidget*> (parentWidget()))
    return;
  CopasiTableWidget::saveTable();

  std::string oldKey, newKey, changeKey = "";
  C_INT32 j, jmax = table->numRows() - 1;
  for (j = 0; j < jmax; ++j)
    {
      if (!mFlagDelete[j] && (mFlagNew[j] || mFlagChanged[j]))
        {
          if (dynamic_cast<QComboTableItem *>(table->item(j, COL_RELATIONSHIP)))
            {
              CBiologicalDescription * pBiologicalDescription = static_cast< CBiologicalDescription * > (GlobalKeys.get(mKeys[j]));
              const std::string relationship = (const char *) static_cast<QComboTableItem *>(table->item(j, COL_RELATIONSHIP))->currentText().utf8();
              if (pBiologicalDescription->getRelationship() != relationship)
                {
                  const std::map<std::string, std::string> relationships = CConstants::getRelationships();
                  std::string newTableName = CConstants::getKey(relationships, relationship);
                  oldKey = pBiologicalDescription->getKey();
                  newKey = dynamic_cast <CMIRIAMModelWidget*>(parentWidget())->getMIRIAMInfo().moveBiologicalDescription(oldKey, newTableName);
                  tableLineToObject(j, GlobalKeys.get(newKey));
                  mKeys[j] = newKey;
                  changeKey = newKey;
                }
            }
        }
    }
  if (newKey.length())
  {protectedNotify(mOT, ListViews::CHANGE, changeKey);}
}

void CBiologicalDescriptionsWidget::slotDoubleClicked(int C_UNUSED(row), int C_UNUSED(col),
    int C_UNUSED(m), const QPoint & C_UNUSED(n))
{}

void CBiologicalDescriptionsWidget::slotValueChanged(int row, int col)
{
  if (col == COL_RELATIONSHIP || col == COL_RESOURCE)
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
