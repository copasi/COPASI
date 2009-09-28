// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelValue.cpp,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/09/28 18:11:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQModelValue.h"

#include "CQExpressionWidget.h"

#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"

#include "model/CModel.h"
#include "model/CModelValue.h"
#include "function/CExpression.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiRootContainer.h"

/*
 *  Constructs a CQModelValue which is a child of 'parent', with the
 *  name 'name'.'
 */
CQModelValue::CQModelValue(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQModelValue::~CQModelValue()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQModelValue::languageChange()
{
  retranslateUi(this);
}

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
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  while (!(mpModelValue = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createModelValue(name)))
    {
      i++;
      name = "quantity_";
      name += TO_UTF8(QString::number(i));
    }

  enter(mpModelValue->getKey());
  protectedNotify(ListViews::MODELVALUE, ListViews::ADD);
}

void CQModelValue::slotBtnDelete()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  if (mpModelValue == NULL)
    return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, pModel, "species",
                                FROM_UTF8(mpModelValue->getObjectName()),
                                mpModelValue->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        unsigned C_INT32 index =
          static_cast<CCopasiVector< CModelValue > *>(&pDataModel->getModel()->getModelValues())->getIndex(CCopasiRootContainer::getKeyFactory()->get(mKey));

        pDataModel->getModel()->removeModelValue(mKey);
        unsigned C_INT32 size =
          pDataModel->getModel()->getModelValues().size();

        mpModelValue = NULL;

        if (size > 0)
          enter(pDataModel->getModel()->getModelValues()[std::min(index, size - 1)]->getKey());
        else
          enter("");

#undef DELETE
        protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, mKey);
        break;
      }

      default:
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
        gridLayout->remove(mpLblExpression);

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
        gridLayout->addWidget(mpLblExpression, 2, 0);

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
        gridLayout->addWidget(mpLblExpression, 2, 0);

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
  mpExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);

  mInitialExpressionValid = false;
  mpInitialExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::InitialExpression);
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

bool CQModelValue::enterProtected()
{
  mpModelValue = dynamic_cast< CModelValue * >(mpObject);

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

  // Update Expression Widget
  mpExpressionEMW->updateWidget();

  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpModelValue->getInitialExpression());

  // Update Initial Expression Widget
  mpInitialExpressionEMW->updateWidget();

  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentItem());

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

  // set name of quantity
  if (mpModelValue->getObjectName() != TO_UTF8(mpEditName->text()))
    {
      if (!mpModelValue->setObjectName(TO_UTF8(mpEditName->text())))  // the new name is rejected as it has been used
        {
          QString msg;
          msg = "Unable to rename quantity '" + FROM_UTF8(mpModelValue->getObjectName()) + "'\n"
                + "to '" + mpEditName->text() + "' since a quantity with that name already exists.\n";

          CQMessageBox::information(this,
                                    "Unable to rename Quantity",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::Ok);

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
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      (*CCopasiRootContainer::getDatamodelList())[0]->changed();
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
      gridLayout->addWidget(mpLblInitialExpression, 4, 0);

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
      gridLayout->remove(mpLblInitialExpression);

      // hide label, widget, and all buttons
      mpLblInitialExpression->hide();
      mpInitialExpressionEMW->hide();

      // enable the option of use Initial Value
      mpEditInitialValue->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::ASSIGNMENT);

      // we don't need to update the Initial Expression Widget
    }
}
