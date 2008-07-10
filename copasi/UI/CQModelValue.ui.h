// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQModelValue.ui.h,v $
//   $Revision: 1.28 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/10 20:40:09 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CModelValue.h"
#include "function/CExpression.h"
#include "report/CKeyFactory.h"

/*!
    After clicking the Commit button, COPASI will internally, automatically save any inputs and load them.
 */
void CQModelValue::slotBtnCommit()
{
  save();
  load();
}

void CQModelValue::slotBtnRevert()
{
  load();
}

/// Slot to create a new quantity; activated whenever the New button is clicked
void CQModelValue::slotBtnNew()
{
  // save the current setting values
  save();

  // standard name
  std::string name = "quantity";

  // if the standard name already exists then creating the new event will fail
  // thus, a growing index will automatically be added to the standard name
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
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;
  /*
  std::set< const CCopasiObject * > DeletedObjects;
  unsigned C_INT32 NumberDeleted = 0;
  */

  QString valueList = "Are you sure you want to delete listed MODEL VALUE(S) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above MODEL VALUE(S) and will be deleted -\n";
  QString effectedMetabList = "Following SPECIES reference above MODEL VALUE(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above MODEL VALUE(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above MODEL VALUE(S) and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  valueList.append(FROM_UTF8(mpModelValue->getObjectName()));
  valueList.append(", ");

  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;

  pModel->appendDependentModelObjects(mpModelValue->getDeletedObjects(),
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
      effectedReacList.append(FROM_UTF8(mpModelValue->getObjectName()));
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
      effectedMetabList.append(FROM_UTF8(mpModelValue->getObjectName()));
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
      effectedValueList.append(FROM_UTF8(mpModelValue->getObjectName()));
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
      effectedCompartmentList.append(FROM_UTF8(mpModelValue->getObjectName()));
      effectedCompartmentList.append("\n");
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
    choice = CQMessageBox::question(this,
                                    "CONFIRM DELETE",
                                    msg,
                                    "Continue", "Cancel", 0, 1, 1);

  switch (choice)
    {
    case 0:  // Yes or Enter
      {
        unsigned C_INT32 index =
          static_cast<CCopasiVector< CModelValue > *>(&CCopasiDataModel::Global->getModel()->getModelValues())->getIndex(GlobalKeys.get(mKey));

        CCopasiDataModel::Global->getModel()->removeModelValue(mKey);
        unsigned C_INT32 size =
          CCopasiDataModel::Global->getModel()->getModelValues().size();

        mpModelValue = NULL;

        if (size > 0)
          enter(CCopasiDataModel::Global->getModel()->getModelValues()[std::min(index, size - 1)]->getKey());
        else
          enter("");

#undef DELETE
        protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, mKey);
        break;
      }

    default:  // No or Escape
      break;
    }
}

/*!
    If the simulation type is changed then COPASI will automatically adjust its appearance,
    especially correlating to the Expression Widget and its buttons.
 */
void CQModelValue::slotTypeChanged(int type)
{
  switch ((CModelEntity::Status) mItemToType[type])
    {
    case CModelEntity::FIXED:
      // remove expression layout from GUI screen
      CQModelValueLayout->remove(mpLblExpression);

      // hide label, widget, and all buttons
      mpLblExpression->hide();
      mpExpressionEMW->hide();

      // enable the option of use Initial Expression
      mpBoxUseInitialExpression->setEnabled(true);
      slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

      // we don't need to update the expression widget as it is already hidden

      break;

    case CModelEntity::ASSIGNMENT:
      // add expression layout
      CQModelValueLayout->addWidget(mpLblExpression, 2, 0);

      // show label, widget, and correct buttons
      mpLblExpression->show();   // show the label
      mpExpressionEMW->show();  // show the widget

      // disable the option of use Initial Expression
      mpBoxUseInitialExpression->setEnabled(false);
      slotInitialTypeChanged(false);

      // update the expression widget
      mpExpressionEMW->updateWidget();

      break;

    case CModelEntity::ODE:
      // add expression layout
      CQModelValueLayout->addWidget(mpLblExpression, 2, 0);

      // show label, widget, and correct buttons
      mpLblExpression->show();   // show the label
      mpExpressionEMW->show();  // show the widget

      // enable the option of use Initial Expression
      mpBoxUseInitialExpression->setEnabled(true);
      slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

      // update the expression widget
      mpExpressionEMW->updateWidget();

      break;

    default:
      break;
    }
}

/*!
    This function is used in case of not FIXED type
 */
void CQModelValue::slotExpressionValid(bool valid)
{
  mExpressionValid = valid;
  mpBtnCommit->setEnabled(mExpressionValid && mInitialExpressionValid);
}

void CQModelValue::slotInitialExpressionValid(bool valid)
{
  mInitialExpressionValid = valid;
  mpBtnCommit->setEnabled(mExpressionValid && mInitialExpressionValid);
}

void CQModelValue::init()
{
  connect(mpExpressionEMW->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotExpressionValid(bool)));
  connect(mpInitialExpressionEMW->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotInitialExpressionValid(bool)));

  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);

  mExpressionValid = false;
  mpExpressionEMW->mpExpressionWidget->setExpressionType(CCopasiSimpleSelectionTree::TRANSIENT_EXPRESSION);

  mInitialExpressionValid = false;
  mpInitialExpressionEMW->mpExpressionWidget->setExpressionType(CCopasiSimpleSelectionTree::TRANSIENT_EXPRESSION);
}

void CQModelValue::destroy()
{}

bool CQModelValue::update(ListViews::ObjectType /* objectType */,
                          ListViews::Action /* action */,
                          const std::string & /* key */)
{
  return true;
}

bool CQModelValue::leave()
{
  if (mpBtnCommit->isEnabled())
    {
      if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::FIXED)
        {
          // -- Expression --
          mpExpressionEMW->updateWidget();
        }

      if (mpBoxUseInitialExpression->isChecked())
        {
          // -- Initial Expression --
          mpInitialExpressionEMW->updateWidget();
        }

      save();
    }

  return true;
}

bool CQModelValue::enter(const std::string & key)
{
  mKey = key;
  mpModelValue = dynamic_cast< CModelValue * >(GlobalKeys.get(key));

  if (!mpModelValue)
    {
      mpListView->switchToOtherWidget(115, "");
      return false;
    }

  load();
  return true;
}

/*!
    Load any saved values to the screen
 */
void CQModelValue::load()
{
  if (mpModelValue == NULL) return;

  // Name
  mpEditName->setText(FROM_UTF8(mpModelValue->getObjectName()));

  // Type
  mpComboBoxType->setCurrentText(FROM_UTF8(CModelEntity::StatusName[mpModelValue->getStatus()]));

  // Initial Value
  mpEditInitialValue->setText(QString::number(mpModelValue->getInitialValue()));

  // Current Value
  mpEditCurrentValue->setText(QString::number(mpModelValue->getValue()));

  // Rate
  mpEditRate->setText(QString::number(mpModelValue->getRate()));

  // Expression
  mpExpressionEMW->mpExpressionWidget->setExpression(mpModelValue->getExpression());
  slotTypeChanged(mpComboBoxType->currentItem());

  // Update Expression Widget
  mpExpressionEMW->updateWidget();

  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpModelValue->getInitialExpression());

  // Update Initial Expression Widget
  mpInitialExpressionEMW->updateWidget();

  // Use Initial Expression
  if (mpModelValue->getStatus() == CModelEntity::ASSIGNMENT ||
      mpModelValue->getInitialExpression() == "")
    {
      mpBoxUseInitialExpression->setChecked(false);
      //      slotInitialTypeChanged(false);
    }
  else
    {
      mpBoxUseInitialExpression->setChecked(true);
      //      slotInitialTypeChanged(true);
    }

  mChanged = false;
}

/*!
    Save any inputs and set them as initial setting values
 */
void CQModelValue::save()
{
  if (mpModelValue == NULL) return;

  // set name of quantitiy
  if (mpModelValue->getObjectName() != (const char *) mpEditName->text().utf8())
    {
      if (!mpModelValue->setObjectName((const char *) mpEditName->text().utf8()))  // the new name is rejected as it has been used
        {
          QString msg;
          msg = "Unable to rename quantity '" + FROM_UTF8(mpModelValue->getObjectName()) + "'\n"
                + "to '" + mpEditName->text() + "' since a quantity with that name already exists.\n";

          CQMessageBox::information(this,
                                    "Unable to rename Quantity",
                                    msg,
                                    QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);

          mpEditName->setText(FROM_UTF8(mpModelValue->getObjectName()));
        }
      else  // the new name is accepted
        {
          protectedNotify(ListViews::MODELVALUE, ListViews::RENAME, mKey);
          mChanged = true;
        }
    }

  // set status
  if (mpModelValue->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()])
    {
      mpModelValue->setStatus((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()]);
      mChanged = true;
    }

  // set initial value
  if (QString::number(mpModelValue->getInitialValue()) != mpEditInitialValue->text() &&
      mpModelValue->getStatus() != CModelEntity::ASSIGNMENT)
    {
      mpModelValue->setInitialValue(mpEditInitialValue->text().toDouble());
      mChanged = true;
    }

  // set expression
  if (mpModelValue->getExpression() != mpExpressionEMW->mpExpressionWidget->getExpression())
    {
      //      mpModelValue->setExpression(((CQExpressionWidget *)mpEditExpression->widget(0))->getExpression());
      mpModelValue->setExpression(mpExpressionEMW->mpExpressionWidget->getExpression());
      mChanged = true;
    }

  // set initial expression
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::ASSIGNMENT)
    {
      if (mpBoxUseInitialExpression->isChecked() &&
          mpModelValue->getInitialExpression() != mpInitialExpressionEMW->mpExpressionWidget->getExpression())
        {
          mpModelValue->setInitialExpression(mpInitialExpressionEMW->mpExpressionWidget->getExpression());
          mChanged = true;
        }
      else if (!mpBoxUseInitialExpression->isChecked() &&
               mpModelValue->getInitialExpression() != "")
        {
          mpModelValue->setInitialExpression("");
          mChanged = true;
        }
    }

  if (mChanged)
    {
      CCopasiDataModel::Global->changed();
      protectedNotify(ListViews::MODELVALUE, ListViews::CHANGE, mKey);
    }

  mChanged = false;
}

void CQModelValue::slotNameLostFocus()
{
  if (mpEditName->text() != FROM_UTF8(mpModelValue->getObjectName()))
    {}}

/*!
    If the initial expression is chosen to be used by checking the mpBoxUseInitialExpression check box being represented by
    the boolean parameter useInitialAssignment (true if checked; false otherwise), COPASI will show the Initial Expression
    Widget with its correct push buttons. Otherwise, the widget and its buttons will be hidden.
 */
void CQModelValue::slotInitialTypeChanged(bool useInitialAssignment)
{
  if (useInitialAssignment)  // use Initial Expression (ie. the mpBoxUseInitialExpression is checked)
    {
      // add the layout of initial expression to the CQModelValueLayout
      CQModelValueLayout->addWidget(mpLblInitialExpression, 4, 0);

      // show label, widget, and the correct buttons
      mpLblInitialExpression->show();  // show the label
      mpInitialExpressionEMW->show(); // show the widget

      // enable the option of use Initial Value
      mpEditInitialValue->setEnabled(false);

      // update the Initial Expression Widget
      mpInitialExpressionEMW->updateWidget();
    }
  else  // mpBoxUseInitialExpression is not checked
    {
      // remove the layout of initial expression from GUI screen
      CQModelValueLayout->remove(mpLblInitialExpression);

      // hide label, widget, and all buttons
      mpLblInitialExpression->hide();
      mpInitialExpressionEMW->hide();

      // enable the option of use Initial Value
      mpEditInitialValue->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::ASSIGNMENT);

      // we don't need to update the Initial Expression Widget
    }
}
