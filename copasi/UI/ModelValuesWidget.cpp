// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ModelValuesWidget.cpp,v $
//   $Revision: 1.21.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/22 18:51:21 $
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
#include "function/CExpression.h"
#include "model/CModel.h"
#include "model/CModelValue.h"
#include "report/CKeyFactory.h"

#define COL_NAME 1
#define COL_TYPE 2
#define COL_INITIAL 3
#define COL_TRANSIENT 4
#define COL_RATE 5
#define COL_EXPRESSION 6

std::vector<const CCopasiObject*> ModelValuesWidget::getObjects() const
  {
    CCopasiVectorN<CModelValue>& tmp = CCopasiDataModel::Global->getModel()->getModelValues();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void ModelValuesWidget::init()
{
  mOT = ListViews::MODELVALUE;
  numCols = 7; // + 1;
  table->setNumCols(numCols);
  table->setColumnReadOnly (COL_TRANSIENT, true);
  table->setColumnReadOnly (COL_RATE, true);
  table->setColumnReadOnly (COL_EXPRESSION, true);

  //table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();

  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(COL_NAME, "Name");
  tableHeader->setLabel(COL_TYPE, "Type");
  tableHeader->setLabel(COL_INITIAL, "Initial Value");
  tableHeader->setLabel(COL_TRANSIENT, "Transient Value");
  tableHeader->setLabel(COL_RATE, "Rate");
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
  QComboTableItem * pComboBox = new QComboTableItem(table, mTypes);
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
  const CExpression * pExpression = pMV->getExpressionPtr();
  if (pExpression != NULL)
    table->setText(row, COL_EXPRESSION, FROM_UTF8(pMV->getExpression()));
  else
    table->setText(row, COL_EXPRESSION, "");
}

void ModelValuesWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CModelValue* pMV = dynamic_cast<CModelValue*>(obj);
  if (!pMV) return;

  CModelEntity::Status OldStatus = pMV->getStatus();
  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_TYPE)))
    pMV->setStatus((CModelEntity::Status) mItemToType[static_cast<QComboTableItem *>(table->item(row, COL_TYPE))->currentItem()]);

  if (pMV->getStatus() != CModelEntity::ASSIGNMENT &&
      OldStatus != CModelEntity::ASSIGNMENT)
    pMV->setInitialValue(table->text(row, COL_INITIAL).toDouble());
}

void ModelValuesWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != COL_TYPE)
    {
      QComboTableItem * pComboBox = new QComboTableItem(table, mTypes);
      pComboBox->setCurrentItem(0);
      table->setItem(row, COL_TYPE, pComboBox);
    }

  if (exc != COL_INITIAL)
    table->setText(row, COL_INITIAL, QString::number(0.0));

  if (exc != COL_TRANSIENT)
    table->clearCell(row, COL_TRANSIENT);

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
  while (!(pMV = CCopasiDataModel::Global->getModel()->createModelValue(nname)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }
  //std::cout << " *** created non concentration value: " << nname << " : " << pMV->getKey() << std::endl;
  return pMV;
}

void ModelValuesWidget::deleteObjects(const std::vector<std::string> & keys)
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;

  if (keys.size() == 0)
    return;

  QString valueList = "Are you sure you want to delete listed MODEL VALUE(S) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above MODEL VALUE(S) and will be deleted -\n";
  QString effectedMetabList = "Following SPECIES reference above MODEL VALUE(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above MODEL VALUE(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above MODEL VALUE(S) and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      CModelValue * pValue =
        dynamic_cast< CModelValue *>(GlobalKeys.get(keys[i]));

      valueList.append(FROM_UTF8(pValue->getObjectName()));
      valueList.append(", ");

      std::set< const CCopasiObject * > Reactions;
      std::set< const CCopasiObject * > Metabolites;
      std::set< const CCopasiObject * > Values;
      std::set< const CCopasiObject * > Compartments;

      pModel->appendDependentModelObjects(pValue->getDeletedObjects(),
                                          Reactions, Metabolites, Compartments, Values);

      if (Reactions.size() > 0)
        {
          reacFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Reactions.end();
          for (it = Reactions.begin(); it != itEnd; ++it)
            {
              effectedReacList.append(FROM_UTF8((*it)->getObjectName()));
              effectedReacList.append(", ");
            }

          effectedReacList.remove(effectedReacList.length() - 2, 2);
          effectedReacList.append("  ---> ");
          effectedReacList.append(FROM_UTF8(pValue->getObjectName()));
          effectedReacList.append("\n");
        }

      if (Metabolites.size() > 0)
        {
          metabFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Metabolites.end();
          for (it = Metabolites.begin(); it != itEnd; ++it)
            {
              effectedMetabList.append(FROM_UTF8((*it)->getObjectName()));
              effectedMetabList.append(", ");
            }

          effectedMetabList.remove(effectedMetabList.length() - 2, 2);
          effectedMetabList.append("  ---> ");
          effectedMetabList.append(FROM_UTF8(pValue->getObjectName()));
          effectedMetabList.append("\n");
        }

      if (Values.size() > 0)
        {
          valueFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Values.end();
          for (it = Values.begin(); it != itEnd; ++it)
            {
              effectedValueList.append(FROM_UTF8((*it)->getObjectName()));
              effectedValueList.append(", ");
            }

          effectedValueList.remove(effectedValueList.length() - 2, 2);
          effectedValueList.append("  ---> ");
          effectedValueList.append(FROM_UTF8(pValue->getObjectName()));
          effectedValueList.append("\n");
        }

      if (Compartments.size() > 0)
        {
          compartmentFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Compartments.end();
          for (it = Compartments.begin(); it != itEnd; ++it)
            {
              effectedCompartmentList.append(FROM_UTF8((*it)->getObjectName()));
              effectedCompartmentList.append(", ");
            }

          effectedCompartmentList.remove(effectedCompartmentList.length() - 2, 2);
          effectedCompartmentList.append("  ---> ");
          effectedCompartmentList.append(FROM_UTF8(pValue->getObjectName()));
          effectedCompartmentList.append("\n");
        }
    }

  valueList.remove(valueList.length() - 2, 2);

  QString msg = valueList;

  if (compartmentFound)
    {
      msg.append("\n \n");
      msg.append(effectedCompartmentList);
    }

  if (metabFound)
    {
      msg.append("\n \n");
      msg.append(effectedMetabList);
    }

  if (reacFound)
    {
      msg.append("\n \n");
      msg.append(effectedReacList);
    }

  if (valueFound)
    {
      msg.append("\n \n");
      msg.append(effectedValueList);
    }

  C_INT32 choice = 0;
  if (metabFound || reacFound || valueFound || valueFound)
    choice = CQMessageBox::warning(this,
                                   "CONFIRM DELETE",
                                   msg,
                                   "Continue", "Cancel", 0, 1, 1);

  switch (choice)
    {
    case 0:                     // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            CCopasiDataModel::Global->getModel()->removeModelValue(keys[i]);
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
      if (CModelEntity::ASSIGNMENT == (CModelEntity::Status) mItemToType[static_cast<QComboTableItem *>(table->item(row, COL_TYPE))->currentItem()])
        table->item(row, COL_INITIAL)->setEnabled(false);
      else
        table->item(row, COL_INITIAL)->setEnabled(true);
      break;

    default:
      break;
    }
  return;
}
