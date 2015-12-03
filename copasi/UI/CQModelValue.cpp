// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
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
#include "UI/CQValidatorUnit.h"

//UNDO framework classes
#include "model/CReactionInterface.h"
#include "undoFramework/DeleteGlobalQuantityCommand.h"
#include "undoFramework/CreateNewGlobalQuantityCommand.h"
//#include "undoFramework/GlobalQuantityTypeChangeCommand.h"
#include "undoFramework/UndoGlobalQuantityData.h"
#include "undoFramework/UndoReactionData.h"
#include "undoFramework/UndoEventData.h"
#include "undoFramework/UndoSpeciesData.h"
#include "undoFramework/UndoEventAssignmentData.h"

#include <copasi/undoFramework/GlobalQuantityChangeCommand.h>
#include "copasiui3window.h"

/*
 *  Constructs a CQModelValue which is a child of 'parent', with the
 *  name 'name'.'
 */
CQModelValue::CQModelValue(QWidget* parent, const char* name)
  : CopasiWidget(parent, name),
    mKeyToCopy(""),
    mpModelValue(NULL)
{
  setupUi(this);

  init();

  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  setUndoStack(pWindow->getUndoStack());
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQModelValue::~CQModelValue()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/// Slot to create a new quantity; activated whenever the New button is clicked
void CQModelValue::slotBtnNew()
{
  mpUndoStack->push(new CreateNewGlobalQuantityCommand(this));
}

void CQModelValue::slotBtnCopy()
{
  mKeyToCopy = mKey;
}

void CQModelValue::slotBtnDelete()
{
  mpUndoStack->push(new DeleteGlobalQuantityCommand(this));
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
        // hide label, widget, and all buttons
        mpLblExpression->hide();
        mpExpressionEMW->hide();

        // enable the option of use Initial Expression
        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

        // we don't need to update the expression widget as it is already hidden

        break;

      case CModelEntity::ASSIGNMENT:
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
}

void CQModelValue::slotInitialExpressionValid(bool valid)
{
  mInitialExpressionValid = valid;
}

void CQModelValue::init()
{
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);

  mExpressionValid = false;
  mpExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);

  mInitialExpressionValid = false;
  mpInitialExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::InitialExpression);

  mpEditUnits->setValidator(new CQValidatorUnit(mpEditUnits));
}

void CQModelValue::destroy()
{}

bool CQModelValue::update(ListViews::ObjectType  objectType,
                          ListViews::Action action,
                          const std::string & key)
{
  switch (objectType)
    {
      case ListViews::MODEL:

        // For a new model we need to remove references to no longer existing metabolites
        if (action == ListViews::ADD)
          {
            mKey = "";
            mpObject = NULL;
            mpModelValue = NULL;
          }

        break;

      case ListViews::MODELVALUE:

        // If the currently displayed metabolite is deleted we need to remove its references.
        if (action == ListViews::DELETE && mKey == key)
          {
            mKey = "";
            mpObject = NULL;
            mpModelValue = NULL;
          }

        break;

      case ListViews::STATE:
        break;

      default:
        return true;
        break;
    }

  if (isVisible() && !mIgnoreUpdates)
    load();

  return true;
}

bool CQModelValue::leave()
{
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::FIXED)
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

  return true;
}

bool CQModelValue::enterProtected()
{
  mpModelValue = NULL;

  if (mKeyToCopy != "")
    {
      mpModelValue = dynamic_cast<CModelValue *>(CCopasiRootContainer::getKeyFactory()->get(mKeyToCopy));
      mKeyToCopy = "";
    }
  else
    {
      mpModelValue = dynamic_cast<CModelValue *>(mpObject);
    }

  if (!mpModelValue)
    {
      mpListView->switchToOtherWidget(115, "");
      return false;
    }

  load();

  mpModelValue = dynamic_cast<CModelValue *>(mpObject);

  return true;
}

/*!
    Load any saved values to the screen
 */
void CQModelValue::load()
{
  if (mpModelValue == NULL) return;

  // Units
  mpEditUnits->setText(FROM_UTF8(mpModelValue->getUnit().getExpression()));

  // Type
  mpComboBoxType->setCurrentIndex(mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[mpModelValue->getStatus()])));

  // Initial Value
  mpEditInitialValue->setText(QString::number(mpModelValue->getInitialValue(), 'g', 10));

  // Current Value
  mpEditCurrentValue->setText(QString::number(mpModelValue->getValue(), 'g', 10));

  // Rate
  mpEditRate->setText(QString::number(mpModelValue->getRate(), 'g', 10));

  // Expression
  mpExpressionEMW->mpExpressionWidget->setExpression(mpModelValue->getExpression());

  // Update Expression Widget
  mpExpressionEMW->updateWidget();

  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpModelValue->getInitialExpression());

  // Update Initial Expression Widget
  mpInitialExpressionEMW->updateWidget();

  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentIndex());

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

  mIgnoreUpdates = true;

  // set status
  if (mpModelValue->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()])
    {
      mpUndoStack->push(new GlobalQuantityChangeCommand(
                          CCopasiUndoCommand::GLOBALQUANTITY_SIMULATION_TYPE_CHANGE,
                          (int)mpModelValue->getStatus(),
                          mItemToType[mpComboBoxType->currentIndex()],
                          mpModelValue,
                          this
                        ));
      mChanged = true;
    }

  // set initial value
  if (QString::number(mpModelValue->getInitialValue(), 'g', 10) != mpEditInitialValue->text() &&
      mpModelValue->getStatus() != CModelEntity::ASSIGNMENT)
    {
      mpUndoStack->push(new GlobalQuantityChangeCommand(
                          CCopasiUndoCommand::GLOBALQUANTITY_INITAL_VALUE_CHANGE,
                          mpModelValue->getInitialValue(),
                          mpEditInitialValue->text().toDouble(),
                          mpModelValue,
                          this
                        ));
      mChanged = true;
    }

  // set expression
  if (mpModelValue->getExpression() != mpExpressionEMW->mpExpressionWidget->getExpression())
    {
      mpUndoStack->push(new GlobalQuantityChangeCommand(
                          CCopasiUndoCommand::GLOBALQUANTITY_EXPRESSION_CHANGE,
                          FROM_UTF8(mpModelValue->getExpression()),
                          FROM_UTF8(mpExpressionEMW->mpExpressionWidget->getExpression()),
                          mpModelValue,
                          this
                        ));
      mChanged = true;
    }

  // set initial expression
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::ASSIGNMENT)
    {
      if (mpBoxUseInitialExpression->isChecked() &&
          mpModelValue->getInitialExpression() != mpInitialExpressionEMW->mpExpressionWidget->getExpression())
        {
          mpUndoStack->push(new GlobalQuantityChangeCommand(
                              CCopasiUndoCommand::GLOBALQUANTITY_INITIAL_EXPRESSION_CHANGE,
                              FROM_UTF8(mpModelValue->getInitialExpression()),
                              FROM_UTF8(mpInitialExpressionEMW->mpExpressionWidget->getExpression()),
                              mpModelValue,
                              this,
                              mpModelValue->getInitialValue()
                            ));
          mChanged = true;
        }
      else if (!mpBoxUseInitialExpression->isChecked() &&
               mpModelValue->getInitialExpression() != "")
        {
          mpUndoStack->push(new GlobalQuantityChangeCommand(
                              CCopasiUndoCommand::GLOBALQUANTITY_INITIAL_EXPRESSION_CHANGE,
                              FROM_UTF8(mpModelValue->getInitialExpression()),
                              QString(""),
                              mpModelValue,
                              this,
                              mpModelValue->getInitialValue()
                            ));
          mChanged = true;
        }
    }

  // set unit
  if (mpModelValue->getUnit().getExpression() != TO_UTF8(mpEditUnits->text()))
    {
      mpUndoStack->push(new GlobalQuantityChangeCommand(
                          CCopasiUndoCommand::GLOBALQUANTITY_UNIT_CHANGE,
                          FROM_UTF8(mpModelValue->getUnit().getExpression()),
                          mpEditUnits->text(),
                          mpModelValue,
                          this
                        ));

      mChanged = true;
    }

  mIgnoreUpdates = false;

  if (mChanged)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      (*CCopasiRootContainer::getDatamodelList())[0]->changed();
      protectedNotify(ListViews::MODELVALUE, ListViews::CHANGE, mKey);

      load();
    }

  mChanged = false;
}

/*!
    If the initial expression is chosen to be used by checking the mpBoxUseInitialExpression check box being represented by
    the boolean parameter useInitialAssignment (true if checked; false otherwise), COPASI will show the Initial Expression
    Widget with its correct push buttons. Otherwise, the widget and its buttons will be hidden.
 */
void CQModelValue::slotInitialTypeChanged(bool useInitialAssignment)
{
  if (useInitialAssignment)  // use Initial Expression (ie. the mpBoxUseInitialExpression is checked)
    {
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
      // hide label, widget, and all buttons
      mpLblInitialExpression->hide();
      mpInitialExpressionEMW->hide();

      // enable the option of use Initial Value
      mpEditInitialValue->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::ASSIGNMENT);

      // we don't need to update the Initial Expression Widget
    }
}

//Undo methods
void CQModelValue::createNewGlobalQuantity()
{
  // save the current setting values
  leave();

  // standard name
  std::string name = "quantity_1";

  // if the standard name already exists then creating the new event will fail
  // thus, a growing index will automatically be added to the standard name
  int i = 1;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  while (!(mpModelValue = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createModelValue(name)))
    {
      i++;
      name = "quantity_";
      name += TO_UTF8(QString::number(i));
    }

  std::string key = mpModelValue->getKey();
  protectedNotify(ListViews::MODELVALUE, ListViews::ADD, key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQModelValue::deleteGlobalQuantity()
{

  if (mpModelValue == NULL)
    return;

  GET_MODEL_OR_RETURN(pModel);

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "quantity",
                                FROM_UTF8(mpModelValue->getObjectName()),
                                mpModelValue->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        pDataModel->getModel()->removeModelValue(mKey);
        mpModelValue = NULL;

#undef DELETE
        protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, mKey);
        protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, "");//Refresh all as there may be dependencies.
        break;
      }

      default:
        break;
    }

  mpListView->switchToOtherWidget(CCopasiUndoCommand::GLOBALQUANTITYIES, "");
}

void CQModelValue::deleteGlobalQuantity(UndoGlobalQuantityData *pGlobalQuantityData)
{
  GET_MODEL_OR_RETURN(pModel);

  mpListView->switchToOtherWidget(CCopasiUndoCommand::GLOBALQUANTITYIES, "");

  std::string key = pGlobalQuantityData->getKey();
  pModel->removeModelValue(key);
  mpModelValue = NULL;

#undef DELETE
  protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, key);
  protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, "");//Refresh all as there may be dependencies.
}

void CQModelValue::addGlobalQuantity(UndoGlobalQuantityData *pData)
{
  GET_MODEL_OR_RETURN(pModel);

  CModelValue *pGlobalQuantity =  pData->restoreObjectIn(pModel);

  if (pGlobalQuantity == NULL)
    return;

  protectedNotify(ListViews::MODELVALUE, ListViews::ADD, pGlobalQuantity->getKey());

  mpListView->switchToOtherWidget(C_INVALID_INDEX, pGlobalQuantity->getKey());
}

bool
CQModelValue::changeValue(const std::string& key,
                          CCopasiUndoCommand::Type type,
                          const QVariant& newValue,
                          double iValue /* = std::numeric_limits<double>::quiet_NaN()*/)
{
  if (!mIgnoreUpdates)
    {
      mKey = key;
      mpObject = CCopasiRootContainer::getKeyFactory()->get(mKey);
      mpModelValue = dynamic_cast<CModelValue*>(mpObject);
      load();
    }

  mpListView->switchToOtherWidget(C_INVALID_INDEX, mKey);
  qApp->processEvents();

  switch (type)
    {
      case CCopasiUndoCommand::GLOBALQUANTITY_EXPRESSION_CHANGE:
        mpModelValue->setExpression(TO_UTF8(newValue.toString()));
        break;

      case CCopasiUndoCommand::GLOBALQUANTITY_INITAL_VALUE_CHANGE:
        mpModelValue->setInitialValue(newValue.toDouble());
        break;

      case CCopasiUndoCommand::GLOBALQUANTITY_INITIAL_EXPRESSION_CHANGE:
        mpModelValue->setInitialExpression(TO_UTF8(newValue.toString()));

        if (newValue.toString().isEmpty())
          mpModelValue->setInitialValue(iValue);

        break;

      case CCopasiUndoCommand::GLOBALQUANTITY_SIMULATION_TYPE_CHANGE:
        mpModelValue->setStatus((CModelEntity::Status) newValue.toInt());
        break;

      case CCopasiUndoCommand::GLOBALQUANTITY_UNIT_CHANGE:
        mpModelValue->setUnitExpression(TO_UTF8(newValue.toString()));
        break;

      default:
        return false;
    }

  if (mIgnoreUpdates) return true;

  (*CCopasiRootContainer::getDatamodelList())[0]->changed();
  protectedNotify(ListViews::MODELVALUE, ListViews::CHANGE, mKey);

  load();

  return true;
}
