// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQEventWidget1.h"

#include <utility>
#include <vector>
#include <string.h>

#include "copasi/UI/qtUtilities.h"

#include "CQMessageBox.h"
#include "CCopasiSelectionDialog.h"
#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"

#include "copasi/model/CEvent.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/core/CRootContainer.h"

/*
 *  Constructs a CQEventWidget1 which is a child of 'parent', with the
 *  name 'name'.'
 */
CQEventWidget1::CQEventWidget1(QWidget * parent, const char * name)
  : CopasiWidget(parent, name)
  , mExpressionTriggerValid(false)
  , mExpressionDelayValid(false)
  , mExpressionEAValid(false)
  , mEAName("")
  , mChanged(false)
  , mpEvent(NULL)
  , mAssignmentKey("")
  , mCurrentTarget(C_INVALID_INDEX)
  , mAssignments()
  , mObjectCNToCopy()
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQEventWidget1::~CQEventWidget1()
{
  // no need to delete child widgets, Qt does it all for us
}

/*! Slot to delete the active event widget */
void CQEventWidget1::slotBtnDelete()
{
  if (mpEvent == NULL)
    return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "event",
                                FROM_UTF8(mpEvent->getObjectName()),
                                mpEvent);

  if (choice == QMessageBox::Ok)
    {
      CUndoData UndoData;
      mpEvent->createUndoData(UndoData, CUndoData::Type::REMOVE);
      ListViews::addUndoMetaData(this, UndoData);

      slotNotifyChanges(mpDataModel->applyData(UndoData));
    }
}

/// Slot to create a new event; activated whenever the New button is clicked
void CQEventWidget1::slotBtnNew()
{
  std::string name = "event";
  int i = 1;

  assert(mpDataModel != NULL);

  while (!(mpEvent = mpDataModel->getModel()->createEvent(name)))
    {
      i++;
      name = "event";
      name += TO_UTF8(QString::number(i));
    }

  CUndoData UndoData(CUndoData::Type::INSERT, mpEvent);
  ListViews::addUndoMetaData(this, UndoData);
  UndoData.addMetaDataProperty("Widget Object CN (after)", mpEvent->getCN());
  UndoData.addMetaDataProperty("Widget Object Name (after)", mpEvent->getObjectName());

  slotNotifyChanges(mpDataModel->recordData(UndoData));
}

void CQEventWidget1::slotBtnCopy()
{
  std::string name = "event";
  int i = 1;

  assert(mpDataModel != NULL);

  while (!(mpEvent = mpDataModel->getModel()->createEvent(name)))
    {
      i++;
      name = "event";
      name += TO_UTF8(QString::number(i));
    }

  CData ToCopy = mpObject->toData();
  ToCopy.addProperty(CData::Property::OBJECT_NAME, name);
  ToCopy.removeProperty(CData::Property::OBJECT_INDEX);
  ToCopy.removeProperty(CData::OBJECT_UUID);
  ToCopy.removeProperty(CData::OBJECT_REFERENCES);

  CUndoData::CChangeSet Changes;
  mpEvent->applyData(ToCopy, Changes);

  CUndoData UndoData(CUndoData::Type::INSERT, mpEvent);
  ListViews::addUndoMetaData(this, UndoData);
  UndoData.addMetaDataProperty("Widget Object CN (after)", mpEvent->getCN());
  UndoData.addMetaDataProperty("Widget Object Name (after)", mpEvent->getObjectName());

  slotNotifyChanges(mpDataModel->recordData(UndoData));
}

/*! */
void CQEventWidget1::init()
{
  showDelayExpression(false);

  // SIGNAL-SLOT connections
  connect(mpComboBoxDelay, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChooseDelay(int)));
  connect(mpLBTarget, SIGNAL(currentRowChanged(int)), this, SLOT(slotActualizeAssignmentExpression(int)));

  //  mpExpressionTrigger->mpExpressionWidget->setBoolean(true);
  mpExpressionTrigger->mpExpressionWidget->setBoolean(true);
  mExpressionDelayValid = true;
  mpExpressionDelay->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);

  mExpressionTriggerValid = false;
  //  mpExpressionTrigger->mpExpressionWidget->setExpressionType(CQSimpleSelectionTree::TRANSIENT_EXPRESSION);

  mExpressionEAValid = false;
  mpExpressionEA->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);

  // ----- correlated to GUI layout of the event assignment ----

  // hide the label and widget with respect to expression
  mpLabelEA->setEnabled(false);
  mpExpressionEA->setEnabled(false);

  // Set the icons for the buttons
  mpBtnSelectObject->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnAddTarget->setIcon(CQIconResource::icon(CQIconResource::editAdd));
  mpBtnDeleteTarget->setIcon(CQIconResource::icon(CQIconResource::editDelete));
}

/*! Slot to add a new target without object target nor its expression
 *  Impact only on the appearance.
 */
void CQEventWidget1::slotAddTarget()
{
  CQSimpleSelectionTree::ObjectClasses Classes =
    CQSimpleSelectionTree::EventTarget;

  const CDataObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes);

  if (pObject == NULL)
    return;

  QString displayName(FROM_UTF8(pObject->getObjectDisplayName()));

  if (!mpLBTarget->findItems(displayName, Qt::MatchExactly).isEmpty())
    return;

  mAssignments.add(new CEventAssignment(pObject->getCN()), true);
  mpLBTarget->addItem(displayName);

  mpLBTarget->setCurrentRow((int)(mAssignments.size() - 1));
}

/*! Slot to remove the active target from the appearance
 * Impact only on the appearance.
 */
void CQEventWidget1::slotDeleteTarget()
{
  if (mCurrentTarget > mAssignments.size() - 1
      || mAssignments.size() == 0)
    return;

  size_t ToBeDeleted = mCurrentTarget;

  QListWidgetItem * pItem = mpLBTarget->takeItem((int) ToBeDeleted);
  pdelete(pItem);

  mAssignments.CDataVector< CEventAssignment >::remove(ToBeDeleted);

  mCurrentTarget = mpLBTarget->currentIndex().row();
}

int CQEventWidget1::getDelayTypeIndex()
{
  if (mpEvent->getDelayExpression().empty())
    {
      return 0; // "None"
    }

  if (!mpEvent->getDelayAssignment())
    {
      return 1; // Calculation and Assignment
    }

  return 2; // Assignment only
}

bool CQEventWidget1::loadFromEvent()
{
  if (mpEvent == NULL)
    return false;

  const CModel * pModel =
    dynamic_cast< const CModel * >(mpEvent->getObjectAncestor("Model"));

  if (pModel == NULL)
    return false;

  // *** Expression of Trigger
  mpExpressionTrigger->mpExpressionWidget->setExpression(mpEvent->getTriggerExpression());
  mpExpressionTrigger->updateWidget(); // bring into view mode

  // *** Expression of Priority
  mpExpressionPriority->mpExpressionWidget->setExpression(mpEvent->getPriorityExpression());
  mpExpressionPriority->updateWidget(); // bring into view mode

  // *** Expression of Delay
  mpExpressionDelay->mpExpressionWidget->setExpression(mpEvent->getDelayExpression());
  mpExpressionDelay->updateWidget(); // bring into view mode

  // ** delay type
  mpComboBoxDelay->setCurrentIndex(getDelayTypeIndex());

  mpFireAtInitialTime->setChecked(mpEvent->getFireAtInitialTime());
  mpTriggerPersistent->setChecked(!mpEvent->getPersistentTrigger());

  // copy assignment from event
  CDataVectorN< CEventAssignment >::const_iterator it = mpEvent->getAssignments().begin();
  CDataVectorN< CEventAssignment >::const_iterator end = mpEvent->getAssignments().end();

  mIgnoreUpdates = true;
  mAssignments.clear();
  QStringList Targets;

  int ijk = 0;

  for (; it != end; ++it, ijk++)
    {
      const CDataObject * pObject = CObjectInterface::DataObject(mpDataModel->getObject(it->getTargetCN()));

      if (pObject != NULL)
        {
          Targets.append(FROM_UTF8(pObject->getObjectDisplayName()));
          mAssignments.add(*it);
        }
    }

  // fill the list box and the expression widget with correct assignments
  mpLBTarget->clear();
  mpLBTarget->insertItems(0, Targets);
  mIgnoreUpdates = false;

  size_t NewTarget = mCurrentTarget;

  if (mCurrentTarget == C_INVALID_INDEX
      && mAssignments.size() > 0)
    {
      NewTarget = 0;
    }

  mpLBTarget->setCurrentRow((int) NewTarget);

  if (mAssignments.empty())
    {
      mpExpressionEA->mpExpressionWidget->clear();
      mpExpressionEA->updateWidget();
    }

  mChanged = false;

  return true;
}

/*! The slot to save all current values of the active event widget */
void CQEventWidget1::saveToEvent()
{
  if (mpEvent == NULL)
    return;

  mIgnoreUpdates = true;

  CData OldData(mpEvent->toData());

  if (mpEvent->getTriggerExpression() != mpExpressionTrigger->mpExpressionWidget->getExpression())
    {
      mpEvent->setTriggerExpression(mpExpressionTrigger->mpExpressionWidget->getExpression());
      mChanged = true;
    }

  if (mpEvent->getPriorityExpression() != mpExpressionPriority->mpExpressionWidget->getExpression())
    {
      mpEvent->setPriorityExpression(mpExpressionPriority->mpExpressionWidget->getExpression());
      mChanged = true;
    }

  std::string DelayExpression = mpComboBoxDelay->currentIndex() != 0 ? mpExpressionDelay->mpExpressionWidget->getExpression() : "";

  if (mpEvent->getDelayExpression() != DelayExpression)
    {
      mpEvent->setDelayExpression(DelayExpression);
      mChanged = true;
    }

  if (!mpEvent->getDelayExpression().empty()
      && mpComboBoxDelay->currentIndex() != getDelayTypeIndex())
    {
      mpEvent->setDelayAssignment(mpComboBoxDelay->currentIndex() == 2);
      mChanged = true;
    }

  if (mpEvent->getFireAtInitialTime() != mpFireAtInitialTime->isChecked())
    {
      mpEvent->setFireAtInitialTime(mpFireAtInitialTime->isChecked());
      mChanged = true;
    }

  if (mpEvent->getPersistentTrigger() == mpTriggerPersistent->isChecked())
    {
      mpEvent->setPersistentTrigger(!mpTriggerPersistent->isChecked());
    }

  if (mCurrentTarget != C_INVALID_INDEX
      && mAssignments.size() > mCurrentTarget)
    {
      mAssignments[mCurrentTarget].setExpression(mpExpressionEA->mpExpressionWidget->getExpression());
    }

  if (mAssignments != mpEvent->getAssignments())
    {
      mpEvent->getAssignments() = mAssignments;
      mChanged = true;
    }

  mIgnoreUpdates = false;

  if (mChanged)
    {
      CUndoData UndoData;
      mpEvent->createUndoData(UndoData, CUndoData::Type::CHANGE, OldData, static_cast< CCore::Framework >(mFramework));
      ListViews::addUndoMetaData(this, UndoData);

      slotNotifyChanges(mpDataModel->recordData(UndoData));
      loadFromEvent();
    }

  mChanged = false;
}

/*! The slot to update the active event widget */
bool CQEventWidget1::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  mpEvent = dynamic_cast< CEvent * >(mpObject);

  switch (objectType)
    {
      case ListViews::ObjectType::MODEL:

        // For a new model we need to remove references to no longer existing metabolites
        if (action != ListViews::CHANGE)
          {
            mObjectCN.clear();
            mpObject = NULL;
            mpEvent = NULL;
          }

        break;

      case ListViews::ObjectType::EVENT:

        // If the currently displayed metabolite is deleted we need to remove its references.
        if (action == ListViews::DELETE
            && mObjectCN == cn)
          {
            mObjectCN.clear();
            mpObject = NULL;
            mpEvent = NULL;
          }

        break;

      case ListViews::ObjectType::STATE:
        break;

      default:
        return true;
        break;
    }

  if (isVisible()
      && !mIgnoreUpdates)
    enterProtected();

  return true;
}

/*! Function to interact with an object of class CEvent */
bool CQEventWidget1::enterProtected()
{
  bool success = true;

  if (mObjectCNToCopy != "")
    {
      CObjectInterface::ContainerList List;
      List.push_back(mpDataModel);

      // This will check the current data model and the root container for the object;
      mpEvent = dynamic_cast< CEvent * >(const_cast< CDataObject * >(CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(List, mObjectCNToCopy))));
      mObjectCNToCopy.clear();
    }
  else
    {
      mpEvent = dynamic_cast< CEvent * >(mpObject);
    }

  mCurrentTarget = C_INVALID_INDEX;

  if (mpEvent)
    {
      success = loadFromEvent();
    }

  mpEvent = dynamic_cast< CEvent * >(mpObject);

  if (!success)
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::Events, std::string()); //TODO
    }

  return success;
}

/*! The slot to be done before leaving the active event widget */
bool CQEventWidget1::leaveProtected()
{
  // no saving if the dialog is not visible right now
  // (the changes would already have been saved the last time
  // it was visible and the pane was left)
  if (!isVisible())
    return true;

  saveToEvent();

  return true;
}

/// Slot to select an object from the existing ones -only- for target.
void CQEventWidget1::slotSelectObject()
{
  if (mCurrentTarget == C_INVALID_INDEX)
    return slotAddTarget();

  CQSimpleSelectionTree::ObjectClasses Classes =
    CQSimpleSelectionTree::EventTarget;

  const CDataObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes, mAssignments[mCurrentTarget].getTargetObject());

  if (pObject == NULL)
    return;

  if (mAssignments[mCurrentTarget].setTargetCN(pObject->getCN()))
    {
      // If the target key change was successful we need to update the label.
      mpLBTarget->item((int) mCurrentTarget)->setText(FROM_UTF8(pObject->getObjectDisplayName()));
    }
}

/// Slot to actualize the assignment expression widget of event assignment according to the target
void CQEventWidget1::slotActualizeAssignmentExpression(int index)
{
  if (mIgnoreUpdates)
    return;

  size_t NewTarget = (size_t) index;

  if (NewTarget != C_INVALID_INDEX
      && NewTarget >= mAssignments.size())
    {
      NewTarget = mAssignments.size() - 1;
    }

  // Save the current assignment
  if (NewTarget != mCurrentTarget
      && mCurrentTarget < mAssignments.size())
    {
      mAssignments[mCurrentTarget].setExpression(mpExpressionEA->mpExpressionWidget->getExpression());
    }

  mCurrentTarget = NewTarget;

  if (mCurrentTarget == C_INVALID_INDEX) // no target anymore
    {
      // hide the label and widget with respect to expression
      mpLabelEA->setEnabled(false);
      mpExpressionEA->setEnabled(false);

      return;
    }
  else
    {
      // show the label and widget with respect to expression
      mpLabelEA->setEnabled(true);
      mpExpressionEA->setEnabled(true);

      mpExpressionEA->mpExpressionWidget->setExpression(mAssignments[mCurrentTarget].getExpression());
      mpExpressionEA->updateWidget();
    }
}

/*! Function to apply the Delay Expression Widget */
void CQEventWidget1::showDelayExpression(bool show)
{
  if (show)
    {
      mpLabelDelayExpression->show();
      mpExpressionDelay->show();
    }
  else
    {
      mpLabelDelayExpression->hide();
      mpExpressionDelay->hide();
    }
}

//Slot to handle delay options
void CQEventWidget1::slotChooseDelay(int choice)
{
  if (choice != 0) // Not "None"
    {
      showDelayExpression(true);
    }
  else
    {
      showDelayExpression(false);
    }
}
