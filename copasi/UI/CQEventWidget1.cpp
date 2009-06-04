// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEventWidget1.cpp,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/06/04 19:33:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQEventWidget1.h"

#include <utility>

#include "UI/qtUtilities.h"

#include "CQMessageBox.h"
#include "CCopasiSelectionDialog.h"
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

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQEventWidget1::languageChange()
{
  retranslateUi(this);
}

/*! Slot to save all current values of the active event widget whenever the Commit button is clicked */
void CQEventWidget1::slotBtnCommitClicked()
{
  saveToEvent();
  loadFromEvent();
}

/*! Slot to delete the active event widget */
void CQEventWidget1::slotBtnDeleteClicked()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  unsigned C_INT32 index =
    pDataModel->getModel()->getEvents().CCopasiVector< CEvent >::getIndex(CCopasiRootContainer::getKeyFactory()->get(mEventKey));

  pDataModel->getModel()->removeEvent(mEventKey);

  unsigned C_INT32 size = pDataModel->getModel()->getEvents().size();

  mpEvent = NULL;

  if (size > 0)
    enter(pDataModel->getModel()->getEvents()[std::min(index, size - 1)]->getKey());
  else
    enter("");

  protectedNotify(ListViews::EVENT, ListViews::DELETE, mEventKey);
}

/// Slot to create a new event; activated whenever the New button is clicked
void CQEventWidget1::slotBtnNewClicked()
{
  // std::cout << "CQEW1::slotBtnNewClicked()" << std::endl;

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
      // std::cout << "NAME = " << name << std::endl;
    }

  protectedNotify(ListViews::EVENT, ListViews::ADD);
  enter((*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getEvents()[name]->getKey());
}

/*! Slot to go back to the previous values of the active event widget whenever the Revert button is clicked */
void CQEventWidget1::slotBtnRevertClicked()
{
  loadFromEvent();
}

/*! Slot to change the event name */
void CQEventWidget1::slotNameChanged()
{
  // std::cout << "CQEW1::slotNameChanged - rName = ";
  std::string rName = TO_UTF8(mpLineEditName->text());
  // std::cout << rName << std::endl;
}

/*! */
void CQEventWidget1::init()
{
  slotApplyDelay(false);

  // SIGNAL-SLOT connections
  connect(mpExpressionTrigger->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotExpressionTriggerValid(bool)));
  connect(mpExpressionDelay->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotExpressionDelayValid(bool)));
  connect(mpExpressionEA->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotExpressionEAValid(bool)));
  connect(mpCheckDelay, SIGNAL(toggled(bool)), this, SLOT(slotApplyDelay(bool)));
  connect(mpLBTarget, SIGNAL(currentRowChanged(int)), this, SLOT(slotActualizeAssignmentExpression(int)));

  mpExpressionTrigger->mpExpressionWidget->setBoolean(true);
  mExpressionDelayValid = true;
  mpExpressionDelay->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);

  mExpressionTriggerValid = false;
  //  mpExpressionTrigger->mpExpressionWidget->setExpressionType(CCopasiSimpleSelectionTree::TRANSIENT_EXPRESSION);

  mExpressionEAValid = false;
  mpExpressionEA->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);

  // ----- correlated to GUI layout of the event assignment ----

  // enable unnecessary buttons
  mpBtnAddTarget->setEnabled(true);
  mpBtnDeleteTarget->setEnabled(true);
  mpBtnRevert->setEnabled(true);

  // hide the label and widget with respect to expression
  mpLabelEA->hide();
  mpExpressionEA->hide();
}

/*! Slot to enable the Commit button if the mathematical expression of Delay is valid */
void CQEventWidget1::slotExpressionDelayValid(bool valid)
{
  // std::cout << "CQEW1::slotExpressionDelayValid - valid = " << std::endl;

  mExpressionDelayValid = valid;
}

/*! Slot to enable the Commit button if the mathematical expression of Trigger is valid */
void CQEventWidget1::slotExpressionTriggerValid(bool /* valid */)
{
  // std::cout << "CQEW1::slotExpressionTriggerValid - valid = " << valid << std::endl;

  if (mpExpressionTrigger->mpExpressionWidget->getExpression() == "")
    mpExpressionTrigger->mpBtnViewExpression->setEnabled(false);

  mExpressionTriggerValid = mpExpressionTrigger->mpBtnViewExpression->isEnabled();
}

/*! Slot to enable the Commit button if the mathematical expression of EventAssignment is valid */
void CQEventWidget1::slotExpressionEAValid(bool /* valid */)
{
  // std::cout << "CQEW1::slotExpressionEAValid - valid = " << valid << std::endl;

  if (mpExpressionEA->mpExpressionWidget->getExpression() == "")
    mpExpressionEA->mpBtnViewExpression->setEnabled(false);

  mExpressionEAValid = mpExpressionEA->mpBtnViewExpression->isEnabled();
}

/*! Slot to add a new target without object target nor its expression
 *  Impact only on the appearance.
 */
void CQEventWidget1::slotAddTarget()
{
  CCopasiSimpleSelectionTree::ObjectClasses Classes =
    CCopasiSimpleSelectionTree::Variables;

  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes);

  if (pObject == NULL) return;

  const CModelEntity * pME = dynamic_cast< const CModelEntity * >(pObject->getObjectParent());

  if (pME == NULL) return;

  mAssignments.push_back(CEventAssignment(pME->getKey()));
  mpLBTarget->addItem(FROM_UTF8(pME->getObjectDisplayName()));

  mpLBTarget->setCurrentRow(mAssignments.size() - 1);
}

/*! Slot to remove the active target from the appearance
 * Impact only on the appearance.
 */
void CQEventWidget1::slotDeleteTarget()
{
  if (mCurrentTarget > mAssignments.size() - 1) return;

  mAssignments.erase(mAssignments.begin() + mCurrentTarget);
  delete mpLBTarget->takeItem(mCurrentTarget);

  mCurrentTarget = C_INVALID_INDEX;

  mpLBTarget->setCurrentRow(std::max<unsigned C_INT32>(mCurrentTarget, mAssignments.size() - 1));
}

/*! Load all values with respect to a chosen saved event */
bool CQEventWidget1::loadFromEvent()
{
  if (mpEvent == NULL) return false;

  const CModel * pModel =
    dynamic_cast< const CModel * >(mpEvent->getObjectAncestor("Model"));

  if (pModel == NULL) return false;

  // *** Name
  mpLineEditName->setText(FROM_UTF8(mpEvent->getObjectName()));

  // *** Order
  mpSpinOrder->setRange(1, pModel->getEvents().size());
  mpSpinOrder->setValue(mpEvent->getOrder());

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
          mAssignments.push_back(**it);

#ifdef XXXX // Add type dependent information

          if (sObjectName == "Compartment")
            {
              sName = FROM_UTF8(CCopasiRootContainer::getKeyFactory()->get(it->first)->getObjectDisplayName() + ".Volume");
              // std::cout << "Compartments: " << UTF8_TO_CHAR(sName) << std::endl;
            }

          if (sObjectName == "Metabolite")
            {
              sName = FROM_UTF8("[" + CCopasiRootContainer::getKeyFactory()->get(it->first)->getObjectDisplayName() + "]");
              // std::cout << "Metabolites: " << UTF8_TO_CHAR(sName) << std::endl;
            }

          if (sObjectName.contains("ModelValue"))
            {
              sName = FROM_UTF8(CCopasiRootContainer::getKeyFactory()->get(it->first)->getObjectDisplayName());
              // std::cout << "Global Quantities: " << UTF8_TO_CHAR(sName) << std::endl;
            }

#endif // XXXX
        }
    }

  // fill the list box and the expression widget with correct assignments
  mpLBTarget->clear();
  mpLBTarget->insertItems(0, Targets);

  int NewTarget = mCurrentTarget;

  if (mCurrentTarget == C_INVALID_INDEX &&
      mAssignments.size() > 0)
    {
      NewTarget = 0;
    }

  mpLBTarget->setCurrentRow(NewTarget);

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

  // set name of event
  if (mpEvent->getObjectName() != TO_UTF8(mpLineEditName->text()))
    {
      if (!mpEvent->setObjectName(TO_UTF8(mpLineEditName->text())))  // the new name is rejected as it has been used
        {
          QString msg;
          msg = "Unable to rename event '" + FROM_UTF8(mpEvent->getObjectName()) + "'\n"
                + "to '" + mpLineEditName->text() + "' since an event with that name already exists.\n";

          CQMessageBox::information(this, "Unable to rename Event", msg,
                                    QMessageBox::Ok, QMessageBox::Ok);

          mpLineEditName->setText(FROM_UTF8(mpEvent->getObjectName()));
        }
      else  // the new name is accepted
        {
          protectedNotify(ListViews::EVENT, ListViews::RENAME, mEventKey);
          mChanged = true;
        }
    }

  // Order
  if (mpEvent->getOrder() != (unsigned C_INT32) mpSpinOrder->value())
    {
      mpEvent->setOrder(mpSpinOrder->value());
      mChanged = true;
    }

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
  std::vector< CEventAssignment >::const_iterator it = mAssignments.begin();
  std::vector< CEventAssignment >::const_iterator end = mAssignments.end();

  CCopasiVectorN< CEventAssignment > & OldAssignments = mpEvent->getAssignments();
  unsigned C_INT32 Found;

  // We first update all assignments.
  for (; it != end; ++it)
    {
      Found = OldAssignments.getIndex(it->getTargetKey());

      if (Found == C_INVALID_INDEX)
        {
          OldAssignments.add(*it);
          mChanged = true;
        }
      else if (OldAssignments[Found]->getExpression() != it->getExpression())
        {
          OldAssignments[Found]->setExpression(it->getExpression());
          mChanged = true;
        }
    }

  // Find the deleted assignments and mark them.
  CCopasiVectorN< CEventAssignment >::const_iterator itOld = OldAssignments.begin();
  CCopasiVectorN< CEventAssignment >::const_iterator endOld = OldAssignments.end();

  C_INT32 DeleteCount = OldAssignments.size() - mAssignments.size();
  std::vector< std::string > ToBeDeleted;

  for (; itOld != endOld && DeleteCount > 0; ++itOld)
    {
      const std::string & key = (*itOld)->getTargetKey();

      for (it = mAssignments.begin(); it != end; ++it)
        {
          if (key == it->getTargetKey()) break;
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
      protectedNotify(ListViews::EVENT, ListViews::CHANGE, mEventKey);
    }

  mChanged = false;
}

/*! The slot to update the active event widget */
bool CQEventWidget1::update(ListViews::ObjectType /* objectType */, ListViews::Action /* action */, const std::string & /* key */)
{
  return true;
}

/*! Function to interact with an object of class CEvent */
bool CQEventWidget1::enter(const std::string & key)
{
  // std::cout << "CQEW1::enter - key = " << key << std::endl;
  mEventKey = key;
  mpEvent = dynamic_cast< CEvent * >(CCopasiRootContainer::getKeyFactory()->get(key));
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
  mpExpressionTrigger->updateWidget();

  if (!mpCheckDelay->isChecked())
    mpExpressionDelay->updateWidget();

  saveToEvent();

  mpBtnAddTarget->setEnabled(true);

  if (mpLBTarget->count())
    mpBtnDeleteTarget->setEnabled(true);
  else
    mpBtnDeleteTarget->setEnabled(false);

  return true;
}

/// Slot to select an object from the existing ones -only- for target.
void CQEventWidget1::slotSelectObject()
{
  if (mCurrentTarget == C_INVALID_INDEX)
    return slotAddTarget();

  CCopasiSimpleSelectionTree::ObjectClasses Classes =
    CCopasiSimpleSelectionTree::Variables;

  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes);

  if (pObject == NULL) return;

  const CModelEntity * pME = dynamic_cast< const CModelEntity * >(pObject->getObjectParent());

  if (pME == NULL) return;

  // It is not possible to change the target key of an event assignment therefore we
  // add a new and delete the old;

  CEventAssignment NewTarget(pME->getKey());
  NewTarget.setExpression(mAssignments[mCurrentTarget].getExpression());

  mpLBTarget->insertItem(mCurrentTarget, FROM_UTF8(pME->getObjectDisplayName()));
  mAssignments.insert(mAssignments.begin() + mCurrentTarget, NewTarget);

  mCurrentTarget++;
  slotDeleteTarget();
}

/// Slot to actualize the assignment expression widget of event assignment according to the target
void CQEventWidget1::slotActualizeAssignmentExpression(int index)
{
  unsigned C_INT32 NewTarget = std::max<unsigned C_INT32>((unsigned C_INT32) index, mAssignments.size() - 1);

  // Save the current assignment
  if (NewTarget != mCurrentTarget &&
      mCurrentTarget < mAssignments.size())
    {
      mAssignments[mCurrentTarget].setExpression(mpExpressionEA->mpExpressionWidget->getExpression());
    }

  mCurrentTarget = NewTarget;

  if (mCurrentTarget == C_INVALID_INDEX) // no target anymore
    {
      // hide the label and widget with respect to expression
      mpLabelEA->hide();
      mpExpressionEA->hide();

      return;
    }
  else
    {
      // show the label and widget with respect to expression
      mpLabelEA->show();
      mpExpressionEA->show();

      mpExpressionEA->mpExpressionWidget->setExpression(mAssignments[mCurrentTarget].getExpression());
      mpExpressionEA->updateWidget();
    }
}

/*! Slot to apply the Delay Expression Widget */
void CQEventWidget1::slotApplyDelay(bool show)
{
  if (show)
    {
      mpBtnDelayAssignment->show();
      mpBtnDelayCalculation->show();
      mpLabelDelayExpression->show();
      mpExpressionDelay->show();
    }
  else
    {
      mpBtnDelayAssignment->hide();
      mpBtnDelayCalculation->hide();
      mpLabelDelayExpression->hide();
      mpExpressionDelay->hide();
    }
}
