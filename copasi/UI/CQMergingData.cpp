// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMergingData.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/15 17:07:54 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QSignalMapper>
#include <QComboBox>

#include <QTableWidget>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CMetab.h"
#include "model/CModelValue.h"
#include "model/CModelMerging.h"
#include "report/CCopasiRootContainer.h"
#include "UI/CCopasiSelectionDialog.h"
#include "CQMessageBox.h"

#include "UI/qtUtilities.h"
#include "resourcesUI/CQIconResource.h"


#include "CQMergingData.h"

class CMetab;
class CModelEntity;

#define COL_NAME 0
#define COL_TYPE 1
#define COL_TYPE_HIDDEN 2
#define COL_BTN 3
#define COL_OBJECT 4
#define COL_OBJECT_HIDDEN 5

/*
 *  Constructs a CQMergingData which is a child of 'parent', with the
 *  name 'name'.'
 */

CQMergingData::CQMergingData(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setupUi(this);

  load();
}
/*
 *  Destroys the object and frees any allocated resources
 */
CQMergingData::~CQMergingData()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQMergingData::load()
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  mpComboMap = NULL;
  mpBtnMap = NULL;

  //TODO QT4:  mpTable->setColumnReadOnly(COL_NAME, true);
  //mpTable->hideColumn(COL_TYPE_HIDDEN);
  mpTable->setColumnWidth(COL_BTN, 20);
  mpTable->horizontalHeaderItem(COL_BTN)->setText("");
  //TODO QT4:  mpTable->setColumnReadOnly(COL_OBJECT, true);
  //mpTable->hideColumn(COL_OBJECT_HIDDEN);

  pdelete(mpBtnMap);
  mpBtnMap = new QSignalMapper(this);
  connect(mpBtnMap, SIGNAL(mapped(int)), this, SLOT(slotModelObject(int)));

  pdelete(mpComboMap);
  mpComboMap = new QSignalMapper(this);
  connect(mpComboMap, SIGNAL(mapped(int)), this, SLOT(slotTypeChanged(int)));

  pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  size_t i, imax = pModel->getMetabolites().size();
  mColumnName.resize(imax);
  mColumnKey.resize(imax);
  mObjectKey.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      const CMetab* metab = pModel->getMetabolites()[i];
      mColumnName[i] =  metab->getObjectDisplayName();
      mColumnKey[i] =  metab->getKey();
      mObjectKey[i] = "";
    }

  const std::vector<std::string> & ColumnNames = mColumnName;

// QStringList ColumnTypes;

  const std::string * pTmp = CModelMerging::TypeName;

  while (*pTmp != "")
    {
      ColumnTypes.push_back(FROM_UTF8(*pTmp));
      pTmp++;
    }

  mpTable->setRowCount((int) imax);

  QToolButton* pBtn;
  QComboBox * pComboBox;
  CModelMerging::Type Type;

  for (i = 0; i < imax; i++)
    {

      // COL_NAME

      QTableWidgetItem *nameItem = new QTableWidgetItem();

      nameItem->setText(FROM_UTF8(ColumnNames[i]));
      mpTable->setItem((int) i, COL_NAME, nameItem);

      // COL_TYPE
      pComboBox = new QComboBox(mpTable);
      pComboBox->insertItems(0, ColumnTypes);
      pComboBox->setEditable(false);

      Type = CModelMerging::ignore;
      pComboBox->setCurrentIndex(Type);

      mpComboMap->setMapping(pComboBox, (int) i);
      connect(pComboBox, SIGNAL(activated(int)), mpComboMap, SLOT(map()));

      mpTable->setCellWidget((int) i, COL_TYPE, pComboBox);

      // COL_TYPE_HIDDEN
      QTableWidgetItem *typeItem = new QTableWidgetItem();
      typeItem->setText(QString::number(pComboBox->currentIndex()));
      mpTable->setItem((int) i, COL_TYPE_HIDDEN, typeItem);

      // COL_BTN
      pBtn = new QToolButton(mpTable);
      pBtn->setSizePolicy(QSizePolicy((QSizePolicy::Policy)1, (QSizePolicy::Policy)1));
      pBtn->setMaximumSize(QSize(20, 20));
      pBtn->setIcon(CQIconResource::icon(CQIconResource::copasi));

      if (Type == CModelMerging::ignore)
        pBtn->setEnabled(false);

      mpBtnMap->setMapping(pBtn, (int) i);
      connect(pBtn, SIGNAL(clicked()), mpBtnMap, SLOT(map()));

      mpTable->setCellWidget((int) i, COL_BTN, pBtn);
    }

  mpTable->resizeColumnToContents(COL_NAME);
  mpTable->resizeColumnToContents(COL_TYPE);
  mpTable->resizeColumnToContents(COL_TYPE_HIDDEN);
  mpTable->resizeColumnToContents(COL_BTN);
}
void CQMergingData::slotBtnMerge()
{

  CModelMerging merging(pModel);
  merging.simpleCall(mColumnKey, mObjectKey);

  accept();
}
/*
void CQMergingData::slotBtnRevert()
{
     load();
}
 */

void CQMergingData::slotBtnCancel()
{
  reject();
}

void CQMergingData::slotModelObject(int row)
{

  CQSimpleSelectionTree::ObjectClasses Classes;

  Classes =
    CQSimpleSelectionTree::Variables |
    CQSimpleSelectionTree::ObservedValues |
    CQSimpleSelectionTree::ObservedConstants;

  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes);

  if (pObject)
    {

      std::string key;

      //if (pObject->isReference())
      //{
      CCopasiObject* parent = pObject->getObjectParent();
      assert(parent);

      CModelEntity* tmp;
      tmp = dynamic_cast< CModelEntity * >(parent);

      if (parent->getObjectType() != "Metabolite" || pObject->getObjectName() != "Concentration")
        {
          CQMessageBox::critical(this, QString("Error"),
                                 QString("The choice of the object is incorrect! "),
                                 QMessageBox::Ok, QMessageBox::Ok);

          return;
        }

      key = tmp->getKey();
      //}

      size_t i, imax = pModel->getMetabolites().size();
      size_t ikey, ireset;

      if (pModel->getMetabolites()[row]->getKey() == key)
        {
          CQMessageBox::information(this, QString("Information"),
                                    QString("The choice of the object is incorrect "),
                                    QMessageBox::Ok, QMessageBox::Ok);

          return;
        }

      for (i = 0; i < imax; ++i)
        {
          // CMetab * metab =  pModel->getMetabolites()[i];

          if (key == mObjectKey[i])
            {
              CQMessageBox::information(this, QString("Information"),
                                        QString("The object is already reserved for merging."),
                                        QMessageBox::Ok, QMessageBox::Ok);

              return;
            }
        }

      QTableWidgetItem *objectItem = new QTableWidgetItem();

      objectItem->setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mpTable->setItem(row, COL_OBJECT, objectItem);

      QTableWidgetItem *objectItem1 = new QTableWidgetItem();
      objectItem1->setText(FROM_UTF8(pObject->getCN()));
      mpTable->setItem(row, COL_OBJECT_HIDDEN, objectItem1);

      /* reset the type choice for the object, which is  not more reserved for merging */

      if (mObjectKey[row] != "")
        {
          for (i = 0; i < imax; ++i)
            {
              CMetab * metab =  pModel->getMetabolites()[i];

              if (mObjectKey[row] == metab->getKey())
                ireset = i;
            }

          QTableWidgetItem *resetItem = new QTableWidgetItem();
          mpTable->setItem((int) ireset, COL_NAME, resetItem);
          resetItem->setBackground(Qt::transparent);
          resetItem->setText(FROM_UTF8(mColumnName[ireset]));

          //static_cast<QComboBox *>(mpTable->cellWidget(ireset, COL_TYPE))->insertItem(1,ColumnTypes[1]);
          static_cast<QComboBox *>(mpTable->cellWidget((int) ireset, COL_TYPE))->insertItem(CModelMerging::merge, ColumnTypes[CModelMerging::merge]);
        }

      /* set the type of the reserved object to "ignore" and make the type choise impossible */

      bool ismetab = false;

      for (i = 0; i < imax; ++i)
        {
          CMetab * metab =  pModel->getMetabolites()[i];

          if (metab->getKey() == key)
            {
              ikey = i;
              ismetab = true;
            }
        }

      static_cast<QComboBox *>(mpTable->cellWidget((int) ikey, COL_TYPE))->setCurrentIndex(CModelMerging::ignore);

      static_cast<QComboBox *>(mpTable->cellWidget((int) ikey, COL_TYPE))->removeItem(CModelMerging::merge);

      QTableWidgetItem *ikeyItem = new QTableWidgetItem();

      mpTable->setItem((int) ikey, COL_NAME, ikeyItem);

      ikeyItem->setBackground(Qt::cyan);

      ikeyItem->setText(FROM_UTF8(mColumnName[ikey]));

      mObjectKey[row] = key;

      mpTable->resizeColumnToContents(COL_OBJECT);

      mpTable->resizeColumnToContents(COL_OBJECT_HIDDEN);
    }
}

void CQMergingData::slotTypeChanged(int row)
{
  bool empty = true;

  size_t i, imax = pModel->getMetabolites().size();
  size_t ireset;

  for (i = 0; i < imax; ++i)
    {
      CMetab * metab =  pModel->getMetabolites()[i];

      if (mObjectKey[row] == metab->getKey())
        {
          empty = false;
          ireset = i;
        }
    }

  CModelMerging::Type NewType;

  NewType =
    static_cast<CModelMerging::Type>(static_cast<QComboBox *>(mpTable->cellWidget(row, COL_TYPE))->currentIndex());

  CModelMerging::Type OldType =
    static_cast<CModelMerging::Type>(mpTable->item(row, COL_TYPE_HIDDEN)->text().toLong());

  if (OldType == NewType) return;

  bool BtnEnabled = true;

  //CCopasiObjectName CN = CCopasiObjectName(TO_UTF8(mpTable->item(row, COL_OBJECT_HIDDEN)->text()));
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  switch (NewType)
    {
      case CModelMerging::ignore:
      {
        mObjectKey[row] = "";

        if (!empty)
          {
            QTableWidgetItem *resetItem = new QTableWidgetItem();
            mpTable->setItem((int) ireset, COL_NAME, resetItem);
            resetItem->setBackground(Qt::transparent);
            resetItem->setText(FROM_UTF8(mColumnName[ireset]));
            //static_cast<QComboBox *>(mpTable->cellWidget(ireset, COL_TYPE))->insertItem(1,ColumnTypes[1]);
            static_cast<QComboBox *>(mpTable->cellWidget((int) ireset, COL_TYPE))->insertItem(CModelMerging::merge, ColumnTypes[CModelMerging::merge]);
          }

        BtnEnabled = false;

        QTableWidgetItem *objectItem = new QTableWidgetItem();
        objectItem->setText(FROM_UTF8(mObjectKey[row]));
        mpTable->setItem(row, COL_OBJECT, objectItem);

        QTableWidgetItem *objectItem1 = new QTableWidgetItem();
        objectItem1->setText(FROM_UTF8(mObjectKey[row]));
        mpTable->setItem(row, COL_OBJECT_HIDDEN, objectItem1);

        break;
      }
      case CModelMerging::merge:

        slotModelObject(row);

        BtnEnabled = true;

        break;
    }

  static_cast<QToolButton *>(mpTable->cellWidget(row, COL_BTN))->setEnabled(BtnEnabled);

  QTableWidgetItem *itemValue = new QTableWidgetItem();

  itemValue->setText(QString::number(NewType));

  mpTable->setItem(row, COL_TYPE_HIDDEN, itemValue);

  return;
}
