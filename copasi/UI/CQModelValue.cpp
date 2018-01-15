// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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

#include "copasi.h"

#include "qtUtilities.h"
#include "CQValidatorUnit.h"
#include "copasiui3window.h"
#include "CQDependencyWidget.h"
#include "CQDependenciesWidget.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/function/CExpression.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

//UNDO framework classes
#include "copasi/model/CReactionInterface.h"
#include "copasi/undoFramework/DeleteGlobalQuantityCommand.h"
#include "copasi/undoFramework/CreateNewGlobalQuantityCommand.h"
//#include "undoFramework/GlobalQuantityTypeChangeCommand.h"
#include "copasi/undoFramework/UndoGlobalQuantityData.h"
#include "copasi/undoFramework/UndoReactionData.h"
#include "copasi/undoFramework/UndoEventData.h"
#include "copasi/undoFramework/UndoSpeciesData.h"
#include "copasi/undoFramework/UndoEventAssignmentData.h"

#include "copasi/undoFramework/GlobalQuantityChangeCommand.h"

/*
 *  Constructs a CQModelValue which is a child of 'parent', with the
 *  name 'name'.'
 */
CQModelValue::CQModelValue(QWidget* parent, const char* name)
  : CopasiWidget(parent, name),
    mKeyToCopy(""),
    mpModelValue(NULL),
    mpDependencies(new CQDependenciesWidget(parent))
{
  setupUi(this);

  init();

  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  setUndoStack(pWindow->getUndoStack());

  mpDependencies->setVisibleDependencies(REACTION | EVENT | SPECIES | PARAMETERS | COMPARTMENT);
  mpLblType->setMinimumWidth(90);
  //mpDependencies->setLabelWidth(mpLblType->width() + 14);
  mpDependencies->setLabelWidth(90 - 3);
  gridLayout->removeItem(mpSpacer);
  gridLayout->addWidget(mpDependencies, gridLayout->rowCount(), 0, 1, -1);
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
  deleteGlobalQuantity();
}

/*!
    If the simulation type is changed then COPASI will automatically adjust its appearance,
    especially correlating to the Expression Widget and its buttons.
 */
void CQModelValue::slotTypeChanged(int type)
{
  switch ((CModelEntity::Status) mItemToType[type])
    {
      case CModelEntity::Status::FIXED:
        // hide label, widget, and all buttons
        mpLblExpression->hide();
        mpExpressionEMW->hide();

        // enable the option of use Initial Expression
        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

        mpBoxAddNoise->hide();
        slotAddNoiseChanged(false);

        break;

      case CModelEntity::Status::ASSIGNMENT:
        // show label, widget, and correct buttons
        mpLblExpression->show();   // show the label
        mpExpressionEMW->show();  // show the widget

        // disable the option of use Initial Expression
        mpBoxUseInitialExpression->setEnabled(false);
        slotInitialTypeChanged(false);

        // update the expression widget
        mpExpressionEMW->updateWidget();

        mpBoxAddNoise->hide();
        slotAddNoiseChanged(false);

        break;

      case CModelEntity::Status::ODE:
        // show label, widget, and correct buttons
        mpLblExpression->show();   // show the label
        mpExpressionEMW->show();  // show the widget

        // enable the option of use Initial Expression
        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

        // update the expression widget
        mpExpressionEMW->updateWidget();

#ifdef WITH_SDE_SUPPORT
        mpBoxAddNoise->show();
        slotAddNoiseChanged(mpBoxAddNoise->isChecked());
#else
        mpBoxAddNoise->hide();
        slotAddNoiseChanged(false);
#endif

        break;

      default:
        break;
    }
}

void CQModelValue::slotAddNoiseChanged(bool hasNoise)
{
  if (hasNoise)
    {
      if (mpModelValue != NULL &&
          mpModelValue->getNoiseExpression().empty())
        {
          mpNoiseExpressionWidget->mpExpressionWidget->setExpression(mpModelValue->getDefaultNoiseExpression());
        }

      mpLblNoiseExpression->show();
      mpNoiseExpressionWidget->show();
      mpNoiseExpressionWidget->updateWidget();
    }
  else
    {
      mpLblNoiseExpression->hide();
      mpNoiseExpressionWidget->hide();
    }
}

void CQModelValue::init()
{
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ODE]));

  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::FIXED));
  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::ASSIGNMENT));
  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::ODE));

  mpExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);
  mpInitialExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::InitialExpression);
  mpNoiseExpressionWidget->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);

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

        // For a new model we need to remove references to no longer existing modelvalue
        if (action == ListViews::ADD)
          {
            mKey = "";
            mpObject = NULL;
            mpModelValue = NULL;
          }

        break;

      case ListViews::MODELVALUE:

        // If the currently displayed modelvalue is deleted we need to remove its references.
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
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::Status::FIXED)
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
      mpModelValue = dynamic_cast<CModelValue *>(CRootContainer::getKeyFactory()->get(mKeyToCopy));
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

  // Unit expression
  mpEditUnits->setText(FROM_UTF8(mpModelValue->getUnitExpression()));

  // Update the unit labels
  slotUnitChanged();

  // Type
  mpComboBoxType->setCurrentIndex(mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[mpModelValue->getStatus()])));

  // Initial Value
  mpEditInitialValue->setText(convertToQString(mpModelValue->getInitialValue()));

  // Current Value
  mpEditCurrentValue->setText(convertToQString(mpModelValue->getValue()));

  // Rate
  mpEditRate->setText(convertToQString(mpModelValue->getRate()));

  // Expression
  mpExpressionEMW->mpExpressionWidget->setExpression(mpModelValue->getExpression());

  // Update Expression Widget
  mpExpressionEMW->updateWidget();

  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpModelValue->getInitialExpression());

  // Update Initial Expression Widget
  mpInitialExpressionEMW->updateWidget();

  // Noise Expression
  mpNoiseExpressionWidget->mpExpressionWidget->setExpression(mpModelValue->getNoiseExpression());
  mpNoiseExpressionWidget->updateWidget();
  mpBoxAddNoise->setChecked(mpModelValue->hasNoise());

  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentIndex());

  // Use Initial Expression
  if (mpModelValue->getStatus() == CModelEntity::Status::ASSIGNMENT ||
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

  mpDependencies->loadFrom(mpObject);

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
      QString currentTypeName = FROM_UTF8(CModelEntity::StatusName[(int)mpModelValue->getStatus()]);
      QString newTypeName = FROM_UTF8(CModelEntity::StatusName[(int)mItemToType[mpComboBoxType->currentIndex()]]);

      mpUndoStack->push(new GlobalQuantityChangeCommand(
                          CCopasiUndoCommand::GLOBALQUANTITY_SIMULATION_TYPE_CHANGE,
                          currentTypeName,
                          newTypeName,
                          mpModelValue,
                          this,
                          mpModelValue->getInitialValue()
                        ));

      mChanged = true;
    }

  // set initial value
  if (convertToQString(mpModelValue->getInitialValue()) != mpEditInitialValue->text() &&
      mpModelValue->getStatus() != CModelEntity::Status::ASSIGNMENT)
    {
      mpUndoStack->push(new GlobalQuantityChangeCommand(
                          CCopasiUndoCommand::GLOBALQUANTITY_INITIAL_VALUE_CHANGE,
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
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::Status::ASSIGNMENT)
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

  // Add Noise
  if (mpModelValue->hasNoise() != mpBoxAddNoise->isChecked())
    {
      mpUndoStack->push(new GlobalQuantityChangeCommand(
                          CCopasiUndoCommand::GLOBALQUANTITY_ADD_NOISE_CHANGE,
                          mpModelValue->hasNoise(),
                          mpBoxAddNoise->isChecked(),
                          mpModelValue,
                          this
                        ));

      mChanged = true;
    }

  // Noise Expression
  if (mpModelValue->getNoiseExpression() != mpNoiseExpressionWidget->mpExpressionWidget->getExpression())
    {
      mpUndoStack->push(new GlobalQuantityChangeCommand(
                          CCopasiUndoCommand::GLOBALQUANTITY_NOISE_EXPRESSION_CHANGE,
                          FROM_UTF8(mpModelValue->getNoiseExpression()),
                          FROM_UTF8(mpNoiseExpressionWidget->mpExpressionWidget->getExpression()),
                          mpModelValue,
                          this
                        ));
      mChanged = true;
    }

  // set unit
  if (mpModelValue->getUnitExpression() != TO_UTF8(mpEditUnits->text()))
    {
      mpUndoStack->push(new GlobalQuantityChangeCommand(
                          CCopasiUndoCommand::GLOBALQUANTITY_UNIT_CHANGE,
                          FROM_UTF8(mpModelValue->getUnitExpression()),
                          mpEditUnits->text(),
                          mpModelValue,
                          this
                        ));

      mChanged = true;
    }

  mIgnoreUpdates = false;

  if (mChanged)
    {
      mpDataModel->changed();
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
      mpEditInitialValue->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::Status::ASSIGNMENT);

      // we don't need to update the Initial Expression Widget
    }
}

void CQModelValue::slotUnitChanged()
{
  // Update the labels to reflect the model units
  QString ValueUnits = "";
  QString RateUnits = "";

  if (!mpEditUnits->text().isEmpty())
    {
      ValueUnits = " [" + FROM_UTF8(CUnit::prettyPrint(TO_UTF8(mpEditUnits->text()))) + "]";
      RateUnits = " [" + FROM_UTF8(CUnit::prettyPrint(std::string(TO_UTF8(mpEditUnits->text())) + "/(" + mpDataModel->getModel()->getTimeUnit() + ")")) + "]";
    }

  mpLblInitialValue->setText("Initial Value" + ValueUnits);
  mpLblValue->setText("Value" + ValueUnits);
  mpLblRate->setText("Rate" + RateUnits);
}

//Undo methods
void CQModelValue::createNewGlobalQuantity()
{
  // save the current setting values
  leave();

  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  // standard name
  std::string name = "quantity_1";

  // if the standard name already exists then creating the new event will fail
  // thus, a growing index will automatically be added to the standard name
  int i = 1;

  while (!(mpModelValue = pModel->createModelValue(name)))
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

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "quantity",
                                FROM_UTF8(mpModelValue->getObjectName()),
                                mpModelValue);

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        mpUndoStack->push(new DeleteGlobalQuantityCommand(this));
        break;
      }

      default:
        break;
    }

  mpListView->switchToOtherWidget(CCopasiUndoCommand::GLOBALQUANTITIES, "");
}

void CQModelValue::deleteGlobalQuantity(UndoGlobalQuantityData *pGlobalQuantityData)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  std::string key = pGlobalQuantityData->getKey();
  pModel->removeModelValue(key);
  mpModelValue = NULL;

#undef DELETE
  protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, key);
  protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, "");//Refresh all as there may be dependencies.

  switchToWidget(CCopasiUndoCommand::GLOBALQUANTITIES);
}

void CQModelValue::addGlobalQuantity(UndoGlobalQuantityData *pData)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  CDataObject *pGlobalQuantity =  pData->restoreObjectIn(pModel);

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
      mpObject = CRootContainer::getKeyFactory()->get(mKey);
      mpModelValue = dynamic_cast<CModelValue*>(mpObject);
      load();
    }

  mpListView->switchToOtherWidget(C_INVALID_INDEX, mKey);

  switch (type)
    {
      case CCopasiUndoCommand::GLOBALQUANTITY_EXPRESSION_CHANGE:
        mpModelValue->setExpression(TO_UTF8(newValue.toString()));
        break;

      case CCopasiUndoCommand::GLOBALQUANTITY_INITIAL_VALUE_CHANGE:
        mpModelValue->setInitialValue(newValue.toDouble());
        break;

      case CCopasiUndoCommand::GLOBALQUANTITY_INITIAL_EXPRESSION_CHANGE:
        mpModelValue->setInitialExpression(TO_UTF8(newValue.toString()));

        if (newValue.toString().isEmpty())
          mpModelValue->setInitialValue(iValue);

        break;

      case CCopasiUndoCommand::GLOBALQUANTITY_SIMULATION_TYPE_CHANGE:
      {
        QString newTypeName = newValue.toString();
        int index = newTypeName.length() > 1
                    ? mItemToType[mpComboBoxType->findText(newTypeName)]
                    : newValue.toInt();
        mpModelValue->setStatus((CModelEntity::Status)index);

        if (iValue == iValue
            && mpModelValue->getStatus() != CModelEntity::Status::ASSIGNMENT)
          mpModelValue->setInitialValue(iValue);

        break;
      }

      case CCopasiUndoCommand::GLOBALQUANTITY_ADD_NOISE_CHANGE:
        mpModelValue->setHasNoise(newValue.toBool());
        break;

      case CCopasiUndoCommand::GLOBALQUANTITY_NOISE_EXPRESSION_CHANGE:
        mpModelValue->setNoiseExpression(TO_UTF8(newValue.toString()));
        break;

      case CCopasiUndoCommand::GLOBALQUANTITY_UNIT_CHANGE:
        mpModelValue->setUnitExpression(TO_UTF8(newValue.toString()));
        break;

      default:
        return false;
    }

  if (mIgnoreUpdates) return true;

  assert(mpDataModel != NULL);
  mpDataModel->changed();
  protectedNotify(ListViews::MODELVALUE, ListViews::CHANGE, mKey);

  load();

  return true;
}
