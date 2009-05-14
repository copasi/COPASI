// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ModelValuesWidget.cpp,v $
//   $Revision: 1.30 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/05/14 18:48:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "ModelValuesWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qstringlist.h>

//#include "MyTable.h"
#include "listviews.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "function/CExpression.h"
#include "model/CModel.h"
#include "model/CModelValue.h"
#include "report/CKeyFactory.h"

#define COL_NAME 1
#define COL_TYPE 2
#define COL_INITIAL 3
#define COL_TRANSIENT 4
#define COL_RATE 5
#define COL_IEXPRESSION 6
#define COL_EXPRESSION 7

std::vector<const CCopasiObject*> ModelValuesWidget::getObjects() const
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiVectorN<CModelValue>& tmp = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getModelValues();
  std::vector<const CCopasiObject*> ret;

  C_INT32 i, imax = tmp.size();

  for (i = 0; i < imax; ++i)
    ret.push_back(tmp[i]);

  return ret;
}

void ModelValuesWidget::init()
{
  mOT = ListViews::MODELVALUE;
  numCols = 8; // + 1;
  table->setNumCols(numCols);
  table->setColumnReadOnly(COL_TRANSIENT, true);
  table->setColumnReadOnly(COL_RATE, true);
  table->setColumnReadOnly(COL_IEXPRESSION, true);
  table->setColumnReadOnly(COL_EXPRESSION, true);

  //table->QTable::setNumRows(1);

  //Setting table headers
  Q3Header *tableHeader = table->horizontalHeader();

  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(COL_NAME, "Name");
  tableHeader->setLabel(COL_TYPE, "Type");
  tableHeader->setLabel(COL_INITIAL, "Initial Value");
  tableHeader->setLabel(COL_TRANSIENT, "Transient Value");
  tableHeader->setLabel(COL_RATE, "Rate");
  tableHeader->setLabel(COL_IEXPRESSION, "Initial Expression");
  tableHeader->setLabel(COL_EXPRESSION, "Expression");

  //for sbml ids
  //tableHeader->setLabel(numCols - 1, "SBML ID");
  //table->setColumnReadOnly(numCols - 1, true);

  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);
}

void ModelValuesWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;

  const CModelValue* pMV = dynamic_cast<const CModelValue*>(obj);

  if (!pMV) return;

  // Name
  table->setText(row, COL_NAME, FROM_UTF8(pMV->getObjectName()));

  // Type
  Q3ComboTableItem * pComboBox = new Q3ComboTableItem(table, mTypes);
  pComboBox->setCurrentItem(FROM_UTF8(CModelEntity::StatusName[pMV->getStatus()]));
  table->setItem(row, COL_TYPE, pComboBox);

  // Initial value
  table->setText(row, COL_INITIAL, QString::number(pMV->getInitialValue()));

  if (pMV->getStatus() == CModelEntity::ASSIGNMENT ||
      pMV->getInitialExpression() != "")
    table->item(row, COL_INITIAL)->setEnabled(false);
  else
    table->item(row, COL_INITIAL)->setEnabled(true);

  // Current value
  table->setText(row, COL_TRANSIENT, QString::number(pMV->getValue()));

  // Rate
  table->setText(row, COL_RATE, QString::number(pMV->getRate()));

  // Expression
  const CExpression * pExpression = NULL;

  if (pMV->getInitialExpression() != "")
    {
      pExpression = pMV->getInitialExpressionPtr();

      if (pExpression != NULL)
        table->setText(row, COL_IEXPRESSION, FROM_UTF8(pExpression->getDisplayString()));
      else
        table->clearCell(row, COL_IEXPRESSION);
    }

  // Expression
  pExpression = pMV->getExpressionPtr();

  if (pExpression != NULL)
    table->setText(row, COL_EXPRESSION, FROM_UTF8(pExpression->getDisplayString()));
  else
    table->clearCell(row, COL_EXPRESSION);
}

void ModelValuesWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;

  CModelValue* pMV = dynamic_cast<CModelValue*>(obj);

  if (!pMV) return;

  CModelEntity::Status OldStatus = pMV->getStatus();

  if (dynamic_cast<Q3ComboTableItem *>(table->item(row, COL_TYPE)))
    pMV->setStatus((CModelEntity::Status) mItemToType[static_cast<Q3ComboTableItem *>(table->item(row, COL_TYPE))->currentItem()]);

  if (pMV->getStatus() != CModelEntity::ASSIGNMENT &&
      OldStatus != CModelEntity::ASSIGNMENT)
    pMV->setInitialValue(table->text(row, COL_INITIAL).toDouble());
}

void ModelValuesWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != COL_TYPE)
    {
      Q3ComboTableItem * pComboBox = new Q3ComboTableItem(table, mTypes);
      pComboBox->setCurrentItem(0);
      table->setItem(row, COL_TYPE, pComboBox);
    }

  if (exc != COL_INITIAL)
    table->setText(row, COL_INITIAL, QString::number(0.0));

  if (exc != COL_TRANSIENT)
    table->clearCell(row, COL_TRANSIENT);

  if (exc != COL_IEXPRESSION)
    table->clearCell(row, COL_IEXPRESSION);

  if (exc != COL_EXPRESSION)
    table->clearCell(row, COL_EXPRESSION);
}

QString ModelValuesWidget::defaultObjectName() const
{
  return "quantity";
}

CCopasiObject* ModelValuesWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CModelValue* pMV;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  while (!(pMV = pDataModel->getModel()->createModelValue(nname)))
    {
      i++;
      nname = name + "_";
      nname += TO_UTF8(QString::number(i));
    }

  return pMV;
}

void ModelValuesWidget::deleteObjects(const std::vector<std::string> & keys)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  if (keys.size() == 0)
    return;

  QString ObjectType = "species";
  QString Objects;
  std::set< const CCopasiObject * > DeletedObjects;

  unsigned C_INT32 i, imax = keys.size();

  for (i = 0; i < imax; i++)
    {
      CModelValue * pValue =
        dynamic_cast< CModelValue *>(CCopasiRootContainer::getKeyFactory()->get(keys[i]));

      if (pValue == NULL)
        continue;

      Objects.append(FROM_UTF8(pValue->getObjectName()) + ", ");

      std::set< const CCopasiObject * > AdditionalObjects =
        pValue->getDeletedObjects();

      std::set< const CCopasiObject * >::const_iterator itDeleted = AdditionalObjects.begin();
      std::set< const CCopasiObject * >::const_iterator endDeleted = AdditionalObjects.end();

      for (; itDeleted != endDeleted; ++itDeleted)
        DeletedObjects.insert(*itDeleted);
    }

  Objects.remove(Objects.length() - 2, 2);

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(NULL, pModel, ObjectType,
                                Objects, DeletedObjects);

  switch (choice)
    {
      case QMessageBox::Ok:                     // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            pDataModel->getModel()->removeModelValue(keys[i]);
          }

        for (i = 0; i < imax; i++)
          protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, keys[i]);

        //TODO notify about metabs and reactions

        mChanged = true;
        break;
      }

      default:                     // No or Escape
        break;
    }
}

void ModelValuesWidget::valueChanged(unsigned C_INT32 row, unsigned C_INT32 col)
{
  switch (col)
    {
      case COL_TYPE:

        if (CModelEntity::ASSIGNMENT == (CModelEntity::Status) mItemToType[static_cast<Q3ComboTableItem *>(table->item(row, COL_TYPE))->currentItem()])
          table->item(row, COL_INITIAL)->setEnabled(false);
        else
          table->item(row, COL_INITIAL)->setEnabled(true);

        break;

      default:
        break;
    }

  return;
}
