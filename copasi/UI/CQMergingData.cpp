// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMergingData.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:54 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CMetab.h"
#include "model/CModelValue.h"
#include "model/CModelMerging.h"
#include "report/CCopasiRootContainer.h"
#include "UI/CCopasiSelectionDialog.h"
#include "CQMessageBox.h"

#include "UI/qtUtilities.h"
#include <qsignalmapper.h>
#include <qcombobox.h>
#include <qapplication.h>

#include <QHeaderView>
#include <QTableWidget>

#include "CQMergingData.h"

class CMetab;
class CModelEntity;

#define COL_NAME 0
#define COL_TYPE 1
#define COL_TYPE_HIDDEN 2
#define COL_BTN 3
#define COL_OBJECT 4
#define COL_OBJECT_HIDDEN 5

static const unsigned char copasi_data[] =
{
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
  0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
  0x5c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xa5, 0x93, 0x4d, 0x4f, 0x13,
  0x71, 0x10, 0x87, 0x9f, 0xff, 0xee, 0xd6, 0xd6, 0xb6, 0xdb, 0x52, 0x5a,
  0x40, 0x81, 0x16, 0x85, 0x5a, 0x5e, 0x04, 0xa2, 0xa9, 0x26, 0x26, 0x98,
  0x88, 0x89, 0x07, 0xaf, 0xc6, 0x0f, 0xe8, 0x47, 0xc0, 0x98, 0x78, 0x30,
  0x6a, 0x0c, 0x97, 0x62, 0xc4, 0x82, 0xc8, 0x6b, 0x63, 0x43, 0xaa, 0xa0,
  0xad, 0x5d, 0xe8, 0xf2, 0x62, 0x29, 0xdd, 0x6d, 0x3b, 0x1e, 0x10, 0x22,
  0x41, 0xf4, 0xe0, 0x9c, 0x26, 0x33, 0xf3, 0xfc, 0x0e, 0xbf, 0x99, 0x51,
  0x99, 0x4c, 0x86, 0xff, 0x09, 0xe3, 0x6f, 0x4d, 0x9f, 0xaf, 0x2c, 0xae,
  0xab, 0x61, 0xdb, 0x65, 0xb6, 0xb6, 0x2a, 0x78, 0xbd, 0x06, 0x3d, 0x3d,
  0x77, 0xd4, 0x3f, 0x05, 0x4c, 0xd3, 0x96, 0x4a, 0xe5, 0x80, 0x6c, 0xb6,
  0x40, 0xa1, 0x50, 0xc7, 0xeb, 0x15, 0x62, 0x31, 0x61, 0x60, 0x20, 0x4a,
  0x38, 0x5c, 0x91, 0xdd, 0xdd, 0x76, 0x75, 0xae, 0x80, 0xcf, 0x57, 0x97,
  0xf9, 0xf9, 0x0d, 0xe6, 0xe6, 0x2c, 0x82, 0x41, 0xc5, 0xc4, 0x44, 0x37,
  0x89, 0x44, 0x02, 0x91, 0x1f, 0x18, 0x86, 0xf0, 0x3b, 0x7c, 0x46, 0xc0,
  0xb6, 0xbf, 0xca, 0xcc, 0xcc, 0x67, 0x2c, 0xeb, 0x80, 0x64, 0xd2, 0xc3,
  0xe8, 0x68, 0x2f, 0xe1, 0xf0, 0x80, 0x72, 0x1c, 0x00, 0x3f, 0xae, 0xfb,
  0x17, 0x0f, 0xf2, 0xf9, 0x9c, 0x64, 0xe7, 0x4a, 0x04, 0xfc, 0x1a, 0x93,
  0x93, 0x7d, 0xf4, 0xf5, 0x5d, 0x53, 0x67, 0xc7, 0xcf, 0x11, 0xc8, 0xe7,
  0xd7, 0x64, 0x61, 0xe1, 0x3b, 0x83, 0xa9, 0x20, 0xe9, 0xf4, 0x75, 0x9a,
  0x4d, 0xdf, 0x29, 0x38, 0xac, 0xd6, 0x44, 0x73, 0x04, 0x6b, 0x7d, 0x95,
  0xda, 0x4e, 0x85, 0x50, 0x7b, 0x94, 0xee, 0xe1, 0x34, 0x5f, 0x1b, 0x09,
  0x65, 0x94, 0x4a, 0x39, 0xc9, 0x66, 0xbf, 0x91, 0x4c, 0x06, 0x19, 0x1b,
  0xeb, 0x3a, 0x05, 0x07, 0xdc, 0x05, 0xd9, 0x2f, 0x16, 0x59, 0x5a, 0x5a,
  0xa2, 0xb4, 0xd1, 0xc4, 0xda, 0x0f, 0x50, 0x6f, 0x18, 0xb4, 0x7b, 0x3e,
  0x71, 0x75, 0x3e, 0xc7, 0xed, 0xc7, 0x0f, 0xc4, 0x98, 0x9d, 0x9d, 0xc7,
  0x34, 0x03, 0xa4, 0x52, 0x09, 0x74, 0xbd, 0xf7, 0x04, 0xbe, 0xb0, 0xf1,
  0x42, 0x16, 0x3f, 0xac, 0x91, 0x2b, 0x18, 0x78, 0xc2, 0x31, 0xe2, 0x63,
  0x6d, 0xdc, 0x1c, 0xe9, 0xc7, 0x17, 0x08, 0x52, 0xdb, 0xb6, 0xc9, 0x3e,
  0x7f, 0x49, 0x7e, 0xe6, 0x15, 0x86, 0x65, 0xd9, 0x8c, 0x8f, 0xb7, 0x61,
  0x9a, 0xc9, 0x13, 0x58, 0xcf, 0x3f, 0x93, 0x77, 0xaf, 0x57, 0xd8, 0xb9,
  0x18, 0x65, 0xf0, 0x5e, 0x92, 0xc1, 0xf1, 0x1b, 0xb8, 0x44, 0x14, 0x40,
  0x03, 0xd0, 0xcd, 0x4d, 0xb1, 0x1b, 0x21, 0x76, 0xec, 0x6f, 0x67, 0xd7,
  0x98, 0x08, 0x94, 0xe5, 0xcd, 0xdb, 0x45, 0x0e, 0x82, 0x31, 0x26, 0x1f,
  0x3d, 0x04, 0x7f, 0x5c, 0xfd, 0x6e, 0xbe, 0x6e, 0xbd, 0x97, 0xcc, 0xf4,
  0x3a, 0x5e, 0xd1, 0xb8, 0x9c, 0x7e, 0x88, 0xd1, 0xd1, 0x11, 0xa1, 0x54,
  0x72, 0xb0, 0xac, 0x15, 0xe9, 0xe8, 0x18, 0x51, 0xf5, 0xba, 0xcd, 0x8f,
  0xea, 0x01, 0xa1, 0x78, 0x83, 0x20, 0x45, 0xcc, 0xe6, 0xb6, 0xb4, 0x9a,
  0x0d, 0xaa, 0xd5, 0x2a, 0x85, 0x8f, 0xab, 0x7c, 0x59, 0x2c, 0x72, 0xa8,
  0x5d, 0x62, 0xfc, 0xfe, 0x18, 0x46, 0xf7, 0x5d, 0xa5, 0xa6, 0xa6, 0x9e,
  0xc8, 0xf4, 0xf4, 0x17, 0xa2, 0x51, 0x97, 0x91, 0xe1, 0x5e, 0xa2, 0xa1,
  0x06, 0x9b, 0xb3, 0x4f, 0x29, 0xe7, 0xca, 0x38, 0xc5, 0x0b, 0x38, 0x7b,
  0xa0, 0xeb, 0x1a, 0x8e, 0x3f, 0x42, 0x35, 0x10, 0xa3, 0x2b, 0xd5, 0xc6,
  0xc8, 0xad, 0x21, 0x22, 0xf1, 0xb4, 0x02, 0x50, 0x99, 0x4c, 0x86, 0x5a,
  0xad, 0x20, 0xcb, 0xcb, 0x6b, 0x2c, 0x2f, 0x7b, 0xa8, 0x1f, 0x2a, 0xdc,
  0x9a, 0x8d, 0xb3, 0x5f, 0xa7, 0xbe, 0x27, 0xe8, 0x2d, 0xa1, 0x27, 0x2e,
  0xa4, 0x46, 0x4d, 0xae, 0x0c, 0xc5, 0x69, 0xef, 0x8a, 0xa0, 0x79, 0xfa,
  0x4f, 0xfc, 0x52, 0xc7, 0xdf, 0xe8, 0xf1, 0x6c, 0x8a, 0xeb, 0x7a, 0x68,
  0xb5, 0xe4, 0xa8, 0xd3, 0x82, 0x96, 0x80, 0xae, 0x0c, 0xfc, 0xc1, 0x10,
  0xd2, 0xda, 0xe1, 0xd0, 0xe9, 0x3c, 0x73, 0x5c, 0x27, 0x26, 0xba, 0xee,
  0xd1, 0x0a, 0x35, 0xed, 0x57, 0x41, 0x83, 0xe3, 0xb4, 0x76, 0x08, 0xd0,
  0xf9, 0xc7, 0x4b, 0xfc, 0x09, 0x52, 0xcb, 0x07, 0x62, 0x36, 0x43, 0x92,
  0xc6, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60,
  0x82
};

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

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
//void CQMergingData::languageChange()
//{
//  retranslateUi(this);
//}

void CQMergingData::load()
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  QImage copasi;
  copasi.loadFromData(copasi_data, sizeof(copasi_data), "PNG");
  mCopasi = copasi;

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
      pComboBox->insertStringList(ColumnTypes);
      pComboBox->setEditable(false);

      Type = CModelMerging::ignore;
      pComboBox->setCurrentItem(Type);

      mpComboMap->setMapping(pComboBox, (int) i);
      connect(pComboBox, SIGNAL(activated(int)), mpComboMap, SLOT(map()));

      mpTable->setCellWidget((int) i, COL_TYPE, pComboBox);

      // COL_TYPE_HIDDEN
      QTableWidgetItem *typeItem = new QTableWidgetItem();
      typeItem->setText(QString::number(pComboBox->currentItem()));
      mpTable->setItem((int) i, COL_TYPE_HIDDEN, typeItem);

      // COL_BTN
      pBtn = new QToolButton(mpTable);
      pBtn->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, pBtn->sizePolicy().hasHeightForWidth()));
      pBtn->setMaximumSize(QSize(20, 20));
      pBtn->setIconSet(QIcon(mCopasi));

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

      static_cast<QComboBox *>(mpTable->cellWidget((int) ikey, COL_TYPE))->setCurrentItem(CModelMerging::ignore);

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
    static_cast<CModelMerging::Type>(static_cast<QComboBox *>(mpTable->cellWidget(row, COL_TYPE))->currentItem());

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
