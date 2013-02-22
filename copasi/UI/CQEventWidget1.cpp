// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

#include "UI/qtUtilities.h"

#include "CQMessageBox.h"
#include "CCopasiSelectionDialog.h"
#include "resourcesUI/CQIconResource.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CEvent.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiMessage.h"
#include "report/CCopasiRootContainer.h"

/*
 *  Constructs a CQEventWidget1 which is a child of 'parent', with the
 *  name 'name'.'
 */
CQEventWidget1::CQEventWidget1(QWidget * parent, const char * name)
  : CopasiWidget(parent, name)
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
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  pDataModel->getModel()->removeEvent(mKey);

  mpEvent = NULL;

  protectedNotify(ListViews::EVENT, ListViews::DELETE, mKey);
}

/// Slot to create a new event; activated whenever the New button is clicked
void CQEventWidget1::slotBtnNew()
{
  // save the current setting values
  saveToEvent();

  // standard name
  std::string name = "event";

  // if the standard name already exists then creating the new event will fail
  // thus, a growing index will automatically be added to the standard name
  int i = 0;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  while (!(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createEvent(name))
    {
      i++;
      name = "event_";
      name += TO_UTF8(QString::number(i));
    }

  std::string key = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getEvents()[name]->getKey();
  protectedNotify(ListViews::EVENT, ListViews::ADD, key);
  enter(key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQEventWidget1::slotBtnCopy()
{
  QMessageBox::warning(this, "Warning", "Not Implemented");
}

/*! */
void CQEventWidget1::init()
{
  slotApplyDelay(false);

  // SIGNAL-SLOT connections
  connect(mpCheckDelay, SIGNAL(toggled(bool)), this, SLOT(slotApplyDelay(bool)));
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

  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes);

  if (pObject == NULL) return;

  const CModelEntity * pME = dynamic_cast< const CModelEntity * >(pObject->getObjectParent());

  if (pME == NULL) return;

  mAssignments.add(new CEventAssignment(pME->getKey()), true);
  mpLBTarget->addItem(FROM_UTF8(pME->getObjectDisplayName()));

  mpLBTarget->setCurrentRow((int)(mAssignments.size() - 1));
}

/*! Slot to remove the active target from the appearance
 * Impact only on the appearance.
 */
void CQEventWidget1::slotDeleteTarget()
{
  if (mCurrentTarget > mAssignments.size() - 1 ||
      mAssignments.size() == 0) return;

  size_t ToBeDeleted = mCurrentTarget;

  QListWidgetItem * pItem = mpLBTarget->takeItem((int) ToBeDeleted);
  pdelete(pItem);

  mAssignments.remove(ToBeDeleted);

  mCurrentTarget = mpLBTarget->currentIndex().row();
}

/*! Load all values with respect to a chosen saved event */
bool CQEventWidget1::loadFromEvent()
{
  if (mpEvent == NULL) return false;

  const CModel * pModel =
    dynamic_cast< const CModel * >(mpEvent->getObjectAncestor("Model"));

  if (pModel == NULL) return false;

  // *** Expression of Trigger
  mpExpressionTrigger->mpExpressionWidget->setExpression(mpEvent->getTriggerExpression());
  mpExpressionTrigger->updateWidget();    // bring into view mode

  // *** Expression of Delay
  mpExpressionDelay->mpExpressionWidget->setExpression(mpEvent->getDelayExpression());
  mpExpressionDelay->updateWidget();    // bring into view mode

  if (mpEvent->getDelayExpression() == "")
    {
      mpCheckDelay->setChecked(false);
    }
  else if (mpEvent->getDelayAssignment())
    {
      mpBtnDelayAssignment->setChecked(true);
      mpCheckDelay->setChecked(true);
    }
  else
    {
      mpBtnDelayCalculation->setChecked(true);
      mpCheckDelay->setChecked(true);
    }

  // copy assignment from event
  CCopasiVectorN< CEventAssignment >::const_iterator it = mpEvent->getAssignments().begin();
  CCopasiVectorN< CEventAssignment >::const_iterator end = mpEvent->getAssignments().end();

  mAssignments.clear();
  QStringList Targets;

  int ijk = 0;

  for (; it != end; ++it, ijk++)
    {
      const CModelEntity * pEntity =
        dynamic_cast< CModelEntity * >(CCopasiRootContainer::getKeyFactory()->get((*it)->getTargetKey()));

      if (pEntity != NULL)
        {
          Targets.append(FROM_UTF8(pEntity->getObjectDisplayName()));
          mAssignments.add(**it);

#ifdef XXXX // Add type dependent information

          if (sObjectName == "Compartment")
            {
              sName = FROM_UTF8(CCopasiRootContainer::getKeyFactory()->get(it->first)->getObjectDisplayName() + ".Volume");
            }

          if (sObjectName == "Metabolite")
            {
              sName = FROM_UTF8("[" + CCopasiRootContainer::getKeyFactory()->get(it->first)->getObjectDisplayName() + "]");
            }

          if (sObjectName.contains("ModelValue"))
            {
              sName = FROM_UTF8(CCopasiRootContainer::getKeyFactory()->get(it->first)->getObjectDisplayName());
            }

#endif // XXXX
        }
    }

  // fill the list box and the expression widget with correct assignments
  mpLBTarget->clear();
  mpLBTarget->insertItems(0, Targets);

  size_t NewTarget = mCurrentTarget;

  if (mCurrentTarget == C_INVALID_INDEX &&
      mAssignments.size() > 0)
    {
      NewTarget = 0;
    }

  mpLBTarget->setCurrentRow((int) NewTarget);

  mChanged = false;

  return true;
}

/*! The slot to save all current values of the active event widget */
void CQEventWidget1::saveToEvent()
{
  if (mpEvent == NULL) return;

  const CModel * pModel =
    dynamic_cast< const CModel * >(mpEvent->getObjectAncestor("Model"));

  if (pModel == NULL) return;

  if (mpEvent->getTriggerExpression() != mpExpressionTrigger->mpExpressionWidget->getExpression())
    {
      mpEvent->setTriggerExpression(mpExpressionTrigger->mpExpressionWidget->getExpression());
      mChanged = true;
    }

  if (mpCheckDelay->isChecked())
    {
      if (mpEvent->getDelayExpression() != mpExpressionDelay->mpExpressionWidget->getExpression())
        {
          mpEvent->setDelayExpression(mpExpressionDelay->mpExpressionWidget->getExpression());
          mChanged = true;
        }

      if (mpEvent->getDelayAssignment() != mpBtnDelayAssignment->isChecked())
        {
          mpEvent->setDelayAssignment(mpBtnDelayAssignment->isChecked());
          mChanged = true;
        }
    }
  else if (mpEvent->getDelayExpression() != "")
    {
      mpEvent->setDelayExpression("");
      mChanged = true;
    }

  // Save the event assignments
  // First we make sure that the current assignment is saved
  if (mCurrentTarget != C_INVALID_INDEX)
    {
      mAssignments[mCurrentTarget]->setExpression(mpExpressionEA->mpExpressionWidget->getExpression());
    }

  CCopasiVector< CEventAssignment >::const_iterator it = mAssignments.begin();
  CCopasiVector< CEventAssignment >::const_iterator end = mAssignments.end();

  CCopasiVectorN< CEventAssignment > & OldAssignments = mpEvent->getAssignments();
  size_t Found;

  // We first update all assignments.
  for (; it != end; ++it)
    {
      Found = OldAssignments.getIndex((*it)->getTargetKey());

      if (Found == C_INVALID_INDEX)
        {
          OldAssignments.add(**it);
          mChanged = true;
        }
      else if (OldAssignments[Found]->getExpression() != (*it)->getExpression())
        {
          OldAssignments[Found]->setExpression((*it)->getExpression());
          mChanged = true;
        }
    }

  // Find the deleted assignments and mark them.
  CCopasiVectorN< CEventAssignment >::const_iterator itOld = OldAssignments.begin();
  CCopasiVectorN< CEventAssignment >::const_iterator endOld = OldAssignments.end();

  size_t DeleteCount = 0;

  if (OldAssignments.size() > mAssignments.size())
    {
      DeleteCount = OldAssignments.size() - mAssignments.size();
    }

  std::vector< std::string > ToBeDeleted;

  for (; itOld != endOld && DeleteCount > 0; ++itOld)
    {
      const std::string & key = (*itOld)->getTargetKey();

      for (it = mAssignments.begin(); it != end; ++it)
        {
          if (key == (*it)->getTargetKey()) break;
        }

      if (it == end)
        {
          ToBeDeleted.push_back(key);
          DeleteCount--;
          mChanged = true;
        }
    }

  // Delete the assignments marked to be deleted.
  std::vector< std::string >::const_iterator itDelete = ToBeDeleted.begin();
  std::vector< std::string >::const_iterator endDelete = ToBeDeleted.end();

  for (; itDelete != endDelete; ++itDelete)
    {
      OldAssignments.remove(*itDelete);
    }

  if (mChanged)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      (*CCopasiRootContainer::getDatamodelList())[0]->changed();
      protectedNotify(ListViews::EVENT, ListViews::CHANGE, mKey);
    }

  mChanged = false;
}

/*! The slot to update the active event widget */
bool CQEventWidget1::update(ListViews::ObjectType /* objectType */, ListViews::Action /* action */, const std::string & /* key */)
{
  return true;
}

/*! Function to interact with an object of class CEvent */
bool CQEventWidget1::enterProtected()
{
  mpEvent = dynamic_cast< CEvent * >(mpObject);
  mCurrentTarget = C_INVALID_INDEX;

  if (mpEvent)
    {
      return loadFromEvent();
    }

  mpListView->switchToOtherWidget(114, ""); //TODO
  return false;
}

/*! The slot to be done before leaving the active event widget */
bool CQEventWidget1::leave()
{
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

  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes);

  if (pObject == NULL) return;

  const CModelEntity * pME = dynamic_cast< const CModelEntity * >(pObject->getObjectParent());

  if (pME == NULL) return;

  if (mAssignments[mCurrentTarget]->setTargetKey(pME->getKey()))
    {
      // If the target key change was successful we need to update the label.
      mpLBTarget->item((int) mCurrentTarget)->setText(FROM_UTF8(pME->getObjectDisplayName()));
    }
}

/// Slot to actualize the assignment expression widget of event assignment according to the target
void CQEventWidget1::slotActualizeAssignmentExpression(int index)
{
  size_t NewTarget = (size_t) index;

  if (NewTarget != C_INVALID_INDEX &&
      NewTarget >= mAssignments.size())
    {
      NewTarget = mAssignments.size() - 1;
    }

  // Save the current assignment
  if (NewTarget != mCurrentTarget &&
      mCurrentTarget < mAssignments.size())
    {
      mAssignments[mCurrentTarget]->setExpression(mpExpressionEA->mpExpressionWidget->getExpression());
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

      mpExpressionEA->mpExpressionWidget->setExpression(mAssignments[mCurrentTarget]->getExpression());
      mpExpressionEA->updateWidget();
    }
}

/*! Slot to apply the Delay Expression Widget */
void CQEventWidget1::slotApplyDelay(bool show)
{
  mpBtnDelayAssignment->setEnabled(show);
  mpBtnDelayCalculation->setEnabled(show);

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
