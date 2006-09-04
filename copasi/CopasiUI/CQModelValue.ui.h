/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQModelValue.ui.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/04 20:05:07 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include <qmessagebox.h>

#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CModelValue.h"
#include "function/CExpression.h"
#include "report/CKeyFactory.h"

void CQModelValue::slotBtnCommit()
{
  save();
  load();
}

void CQModelValue::slotBtnRevert()
{
  load();
}

void CQModelValue::slotBtnNew()
{
  save();

  std::string name = "quantity";
  int i = 0;

  while (!(mpModelValue = CCopasiDataModel::Global->getModel()->createModelValue(name)))
    {
      i++;
      name = "quantity_";
      name += (const char *) QString::number(i).utf8();
    }

  enter(mpModelValue->getKey());
  protectedNotify(ListViews::MODELVALUE, ListViews::ADD);
}

void CQModelValue::slotBtnDelete()
{
  QString valuesList = "Are you sure you want to delete listed quantity(s) ?\n";
  QString effectedReacList = "Following reation(s) reference above quantity(s) and will be deleted -\n";
  QString effectedModelValuesList = "Following global quantities(s) reference above quantity(s) and will be deleted -\n";
  std::set<std::string> effectedKeys;
  std::set< const CCopasiObject * > effectedObjects;
  bool dependentReactionFound = false;
  bool dependentModelValuesFound = false;

  valuesList.append(FROM_UTF8(mpModelValue->getObjectName()));
  valuesList.append(", ");

  effectedKeys =
    CCopasiDataModel::Global->getModel()->listReactionsDependentOnModelValue(mpModelValue->getKey());

  if (effectedKeys.size() > 0)
    {
      dependentReactionFound = true;
      std::set<std::string>::const_iterator it, itEnd = effectedKeys.end();
      for (it = effectedKeys.begin(); it != itEnd; ++it)
        {
          effectedReacList.append(FROM_UTF8(GlobalKeys.get(*it)->getObjectName()));
          effectedReacList.append(", ");
        }

      effectedReacList.remove(effectedReacList.length() - 2, 2);
      effectedReacList.append("  ---> ");
      effectedReacList.append(FROM_UTF8(mpModelValue->getObjectName()));
      effectedReacList.append("\n");
    }

  CCopasiDataModel::Global->getModel()->appendDependentModelValues(mpModelValue->getDeletedObjects(), effectedObjects);

  if (effectedObjects.size() > 0)
    {
      dependentModelValuesFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = effectedObjects.end();
      for (it = effectedObjects.begin(); it != itEnd; ++it)
        {
          effectedModelValuesList.append(FROM_UTF8((*it)->getObjectName()));
          effectedModelValuesList.append(", ");
        }

      effectedModelValuesList.remove(effectedModelValuesList.length() - 2, 2);
      effectedModelValuesList.append("  ---> ");
      effectedModelValuesList.append(FROM_UTF8(mpModelValue->getObjectName()));
      effectedModelValuesList.append("\n");
    }

  valuesList.remove(valuesList.length() - 2, 2);

  QString msg = valuesList;
  if (dependentReactionFound)
    {
      msg.append("\n \n");
      msg.append(effectedReacList);
    }

  if (dependentModelValuesFound)
    {
      msg.append("\n \n");
      msg.append(effectedModelValuesList);
    }

  C_INT32 choice;
  if (dependentReactionFound || dependentModelValuesFound)
    choice = QMessageBox::warning(this,
                                  "CONFIRM DELETE",
                                  msg,
                                  "Continue", "Cancel", 0, 0, 1);
  else
    choice = 0;

  switch (choice)
    {
    case 0:                                                     // Yes or Enter
      {
        unsigned C_INT32 size =
          CCopasiDataModel::Global->getModel()->getModelValues().size();
        unsigned C_INT32 index =
          static_cast<CCopasiVector< CModelValue > *>(&CCopasiDataModel::Global->getModel()->getModelValues())->getIndex(GlobalKeys.get(mKey));

        CCopasiDataModel::Global->getModel()->removeModelValue(mKey);
        mpModelValue = NULL;

        if (size > 1)
          {
            enter(CCopasiDataModel::Global->getModel()->getModelValues()[std::min(index, size - 2)]->getKey());
            //for (i = 0; i < imax; i++)
          }
        else
          {
            enter("");
          }
#undef DELETE
        protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, mKey);
        break;
      }
    case 1:                                                     // No or Escape
      break;
    }
}

void CQModelValue::slotTypeChanged(int type)
{
  if (CModelEntity::FIXED == (CModelEntity::Status) type)
    {
      mpLblExpression->hide();
      mpEditExpression->hide();
      mpBtnObject->hide();
    }
  else
    {
      mpLblExpression->show();
      mpEditExpression->show();
      mpBtnObject->show();
    }

  mpEditExpression->setExpression(mpModelValue->getExpression());
}

void CQModelValue::slotExpressionValid(bool valid)
{
  mpBtnCommit->setEnabled(valid);
}

void CQModelValue::init()
{
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);
}

void CQModelValue::destroy()
{}

bool CQModelValue::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  return true;
}

bool CQModelValue::leave()
{
  if (mpBtnCommit->isEnabled())
    save();

  return true;
}

bool CQModelValue::enter(const std::string & key)
{
  mKey = key;
  mpModelValue = dynamic_cast< CModelValue * >(GlobalKeys.get(key));

  if (!mpModelValue) return false;

  load();
  return true;
}

void CQModelValue::load()
{
  if (mpModelValue == NULL) return;

  mpEditName->setText(FROM_UTF8(mpModelValue->getObjectName()));

  mpComboBoxType->setCurrentText(FROM_UTF8(CModelEntity::StatusName[mpModelValue->getStatus()]));
  slotTypeChanged(mpModelValue->getStatus());

  mpEditInitialValue->setText(QString::number(mpModelValue->getInitialValue()));
  mpEditCurrentValue->setText(QString::number(mpModelValue->getValue()));

  mpEditExpression->setExpression(mpModelValue->getExpression());

  mChanged = false;
}

void CQModelValue::save()
{
  if (mpModelValue == NULL) return;

  if (mpModelValue->getObjectName() != (const char *) mpEditName->text().utf8())
    {
      if (!mpModelValue->setObjectName((const char *) mpEditName->text().utf8()))
        {
          QString msg;
          msg = "Unable to rename quantity '" + FROM_UTF8(mpModelValue->getObjectName()) + "'\n"
                + "to '" + mpEditName->text() + "' since a quantity with that name already exists.\n";

          QMessageBox::warning(this,
                               "Unable to rename Quantity",
                               msg,
                               QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);

          mpEditName->setText(FROM_UTF8(mpModelValue->getObjectName()));
        }
      else
        {
          protectedNotify(ListViews::MODELVALUE, ListViews::RENAME, mKey);
          mChanged = true;
        }
    }

  if (mpModelValue->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()])
    {
      mpModelValue->setStatus((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()]);
      mChanged = true;
    }

  if (QString::number(mpModelValue->getInitialValue()) != mpEditInitialValue->text())
    {
      mpModelValue->setInitialValue(mpEditInitialValue->text().toDouble());
      mChanged = true;
    }

  if (mpModelValue->getExpression() != mpEditExpression->getExpression())
    {
      mpModelValue->setExpression(mpEditExpression->getExpression());
      mChanged = true;
    }

  if (mChanged) CCopasiDataModel::Global->changed();

  mChanged = false;
}

void CQModelValue::slotNameLostFocus()
{
  if (mpEditName->text() != FROM_UTF8(mpModelValue->getObjectName()))
    mpEditExpression->currentObjectRenamed(mpModelValue, mpEditName->text());
}
