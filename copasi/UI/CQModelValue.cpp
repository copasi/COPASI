// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

//UNDO framework classes
#ifdef COPASI_UNDO
#include "model/CReactionInterface.h"
#include "undoFramework/DeleteGlobalQuantityCommand.h"
#include "undoFramework/CreateNewGlobalQuantityCommand.h"
//#include "undoFramework/GlobalQuantityTypeChangeCommand.h"
#include "undoFramework/UndoGlobalQuantityData.h"
#include "undoFramework/UndoReactionData.h"
#include "copasiui3window.h"
#endif

/*
 *  Constructs a CQModelValue which is a child of 'parent', with the
 *  name 'name'.'
 */
CQModelValue::CQModelValue(QWidget* parent, const char* name)
  : CopasiWidget(parent, name),
    mKeyToCopy("")
{
  setupUi(this);

  init();

#ifdef COPASI_UNDO
  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  setUndoStack(pWindow->getUndoStack());
#endif
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
#ifdef COPASI_UNDO
  mpUndoStack->push(new CreateNewGlobalQuantityCommand(this));
#else
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
#endif
}

void CQModelValue::slotBtnCopy()
{
  mKeyToCopy = mKey;
}

void CQModelValue::slotBtnDelete()
{
#ifdef COPASI_UNDO
  mpUndoStack->push(new DeleteGlobalQuantityCommand(this));
#else
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  if (mpModelValue == NULL)
    return;

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

#endif
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

  // set status
  if (mpModelValue->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()])
    {
      mpModelValue->setStatus((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()]);
      mChanged = true;
    }

  // set initial value
  if (QString::number(mpModelValue->getInitialValue(), 'g', 10) != mpEditInitialValue->text() &&
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
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::ASSIGNMENT)
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
#ifdef COPASI_UNDO

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

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  if (mpModelValue == NULL)
    return;

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

  mpListView->switchToOtherWidget(115, "");
}

void CQModelValue::deleteGlobalQuantity(UndoGlobalQuantityData *pGlobalQuantityData)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  CModelValue * pGQ = pModel->getModelValues()[pGlobalQuantityData->getName()];
  std::string key = pGQ->getKey();
  pModel->removeModelValue(key);
  mpModelValue = NULL;

#undef DELETE
  protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, key);
  protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, "");//Refresh all as there may be dependencies.

  mpListView->switchToOtherWidget(115, "");
}

void CQModelValue::addGlobalQuantity(UndoGlobalQuantityData *pSData)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  //reinsert the Global Quantity
  CModelValue *pGlobalQuantity =  pModel->createModelValue(pSData->getName(), pSData->getInitialValue());
  pGlobalQuantity->setStatus(pSData->getStatus());
  std::string key = pGlobalQuantity->getKey();
  protectedNotify(ListViews::MODELVALUE, ListViews::ADD, key);

  //restore the reactions the Global Quantity dependent on
  QList <UndoReactionData *> *reactionData = pSData->getReactionDependencyObjects();

  QList <UndoReactionData *>::const_iterator j;

  for (j = reactionData->begin(); j != reactionData->end(); ++j)
    {
      UndoReactionData * rData = *j;

      //TODO check if reaction already exist in the model, better ideal may be implemented in the future
      bool exist = false;

      for (int ii = 0; ii < pModel->getReactions().size(); ii++)
        {
          if (pModel->getReactions()[ii]->getObjectName() == rData->getName())
            {
              exist = true;
              ii = ii + pModel->getReactions().size() + 1; //jump out of the loop reaction exist already
            }
          else
            {
              exist = false;
            }
        }

      if (!exist)
        {
          CReaction *pRea =  pModel->createReaction(rData->getName());
          rData->getRi()->writeBackToReaction(pRea);
          protectedNotify(ListViews::REACTION, ListViews::ADD, pRea->getKey());
        }
    }

  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQModelValue::globalQuantityTypeChanged(int type)
{
  ; //TODO
}
#endif
