// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQEventWidget1.ui.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/14 12:34:49 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
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

#include <utility>

#include "UI/qtUtilities.h"

#include "CQMessageBox.h"
#include "CCopasiSelectionDialog.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CEvent.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiMessage.h"

/*! Slot to save all current values of the active event widget whenever the Commit button is clicked */
void CQEventWidget1::slotBtnCommitClicked()
{
  saveToEvent();
  loadFromEvent();
}

/*! Slot to delete the active event widget */
void CQEventWidget1::slotBtnDeleteClicked()
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;
  /*
    CEvent * pEvent = dynamic_cast< CEvent * >(GlobalKeys.get(mEventKey));
    if (pEvent == NULL) return;
  */
  QString eventList = "Are you sure you want to delete listed EVENT(S) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above EVENT(S) and will be deleted -\n";
  QString effectedMetabList = "Following SPECIES reference above EVENT(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above EVENT(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above EVENT(S) and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  eventList.append(FROM_UTF8(mpEvent->getObjectName()));
  eventList.append(", ");

  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;

  pModel->appendDependentModelObjects(mpEvent->getDeletedObjects(),
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
      effectedReacList.append(FROM_UTF8(mpEvent->getObjectName()));
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
      effectedMetabList.append(FROM_UTF8(mpEvent->getObjectName()));
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
      effectedValueList.append(FROM_UTF8(mpEvent->getObjectName()));
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
      effectedCompartmentList.append(FROM_UTF8(mpEvent->getObjectName()));
      effectedCompartmentList.append("\n");
    }

  eventList.remove(eventList.length() - 2, 2);

  QString msg = eventList;

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
    case 0:                                                     // Yes or Enter
      {
        unsigned C_INT32 index
        = static_cast<CCopasiVector< CEvent > *>(&CCopasiDataModel::Global->getModel()->getEvents())->getIndex(GlobalKeys.get(mEventKey));
        //        = CCopasiDataModel::Global->getModel()->getEvents().getIndex(mpRi->getReactionName());

        CCopasiDataModel::Global->getModel()->removeEvent(mEventKey);
        unsigned C_INT32 size
        = CCopasiDataModel::Global->getModel()->getEvents().size();

        mpEvent = NULL;

        if (size > 0)
          enter(CCopasiDataModel::Global->getModel()->getEvents()[std::min(index, size - 1)]->getKey());
        else
          enter("");

        protectedNotify(ListViews::EVENT, ListViews::DELETE, mEventKey);
        break;
      }
    default:                                                     // No or Escape
      break;
    }
}

/// Slot to create a new event; activated whenever the New button is clicked
void CQEventWidget1::slotBtnNewClicked()
{
  std::cout << "CQEW1::slotBtnNewClicked()" << std::endl;

  // save the current setting values
  saveToEvent();

  // standard name
  std::string name = "event";

  // if the standard name already exists then creating the new event will fail
  // thus, a growing index will automatically be added to the standard name
  int i = 0;
  while (!CCopasiDataModel::Global->getModel()->createEvent(name))
    {
      i++;
      name = "event_";
      name += (const char *) QString::number(i).utf8();
      std::cout << "NAME = " << name << std::endl;
    }
  /*
    std::cout << "CQEW1::slotBtnNewClicked() - CCopasiDataModel::Global->getModel()->getEvents()[name]->getKey() = "
     << CCopasiDataModel::Global->getModel()->getEvents()[name]->getKey()
     << " - name = " << name << std::endl;
  */
  protectedNotify(ListViews::EVENT, ListViews::ADD);
  /*
    std::cout << "CQEW1::slotBtnNewClicked() - CCopasiDataModel::Global->getModel()->getEvents()[name]->getKey() = "
     << CCopasiDataModel::Global->getModel()->getEvents()[name]->getKey()
     << " - name = " << name << std::endl;

    std::cout << "mpEvent->getKey() = " << mpEvent->getKey()
     << " - name = " << name << std::endl;
  */
  enter(CCopasiDataModel::Global->getModel()->getEvents()[name]->getKey());
}

/*! Slot to go back to the previous values of the active event widget whenever the Revert button is clicked */
void CQEventWidget1::slotBtnRevertClicked()
{
  loadFromEvent();
}

/*! Slot to change the event name */
void CQEventWidget1::slotNameChanged()
{
  std::cout << "CQEW1::slotNameChanged - rName = ";
  std::string rName = (const char *)mpLineEditName->text().utf8();
  std::cout << rName << std::endl;
}

/*! */
void CQEventWidget1::init()
{
  // SIGNAL-SLOT connection
  connect(mpLineEditName, SIGNAL(edited()), this, SLOT(slotNameChanged()));

  connect(mpExpressionTrigger->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotExpressionTriggerValid(bool)));
  connect(mpExpressionDelay->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotExpressionDelayValid(bool)));
  connect(mpExpressionEA->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotExpressionEAValid(bool)));

  connect(mpCBTarget, SIGNAL(activated(int)), this, SLOT(slotActualizeAssignmentExpression(int)));
  mpExpressionTrigger->mpExpressionWidget->setBoolean(true);
  mExpressionDelayValid = true;
  mpExpressionDelay->mpExpressionWidget->setExpressionType(CCopasiSimpleSelectionTree::TRANSIENT_EXPRESSION);

  mExpressionTriggerValid = false;
  mpExpressionTrigger->mpExpressionWidget->setExpressionType(CCopasiSimpleSelectionTree::TRANSIENT_EXPRESSION);

  mExpressionEAValid = false;
  mpExpressionEA->mpExpressionWidget->setExpressionType(CCopasiSimpleSelectionTree::TRANSIENT_EXPRESSION);

  // ----- correlated to GUI layout of the event assignment ----

  // enable unneccessary buttons
  mpBtnAddTarget->setEnabled(true);

  // disable neccessary buttons
  //  mpBtnSelectObject->setDisabled(true);
  mpBtnDeleteTarget->setDisabled(true);
  mpBtnSaveTarget->setDisabled(true);
  mpBtnRevert->setEnabled(false);
  //  std::cout << "L" << __LINE__ << " - mpBtnRevert->setEnabled(false)" << std::cout;
  //  {int y; std::cin >> y;}

  // hide the label and widget wrt expression
  mpLabelEA->hide();
  mpExpressionEA->hide();

  mpBtnSaveTarget->hide();

  // ----- end ----

  mCurrentAssignment.reserve(100);
  mObjectKeyDisplayName.reserve(100);
  mObjectKeyDisplayName.resize(0);
}

/*! Slot to enable the Commit button if the mathematical expression of Delay is valid */
void CQEventWidget1::slotExpressionDelayValid(bool valid)
{
  std::cout << "CQEW1::slotExpressionDelayValid - valid = " << std::endl;
  mExpressionDelayValid = valid;
  /*
    if (mpExpressionDelay->mpExpressionWidget->text() == "")
  //    mpExpressionDelay->mpExpressionWidget->setText("0");
      mpExpressionDelay->mpBtnViewExpression->setEnabled(true);
  */
  //  mExpressionTriggerValid = mpExpressionTrigger->mpBtnViewExpression->isEnabled();
  //  mExpressionDelayValid = mpExpressionDelay->mpBtnViewExpression->isEnabled();
  //  mExpressionEAValid = mpExpressionEA->mpBtnViewExpression->isEnabled();
  /*
    std::cout << "mExpressionTriggerValid = " << mExpressionTriggerValid
     << " - mExpressionEAValid = " << mExpressionEAValid
     << " - (mExpressionTriggerValid && mExpressionEAValid) = " << (mExpressionTriggerValid && mExpressionEAValid)
              << " !! mExpressionDelayValid = " << mExpressionDelayValid
     << " --> (mExpressionDelayValid && (mExpressionTriggerValid && mExpressionEAValid)) = "
     << (mExpressionDelayValid && (mExpressionTriggerValid && mExpressionEAValid)) << std::endl;
    std::cout << "mObjectOK = " << mObjectOK << std::endl;
    mpBtnCommit->setEnabled((mObjectOK && mExpressionDelayValid) && (mExpressionTriggerValid && mExpressionEAValid));
  */
  enableBtnCommit();
}

/*! Slot to enable the Commit button if the mathematical expression of Trigger is valid */
void CQEventWidget1::slotExpressionTriggerValid(bool valid)
{
  std::cout << "CQEW1::slotExpressionTriggerValid - valid = " << valid << std::endl;
  //  mExpressionTriggerValid = valid;

  if (mpExpressionTrigger->mpExpressionWidget->text() == "")
    mpExpressionTrigger->mpBtnViewExpression->setEnabled(false);

  mExpressionTriggerValid = mpExpressionTrigger->mpBtnViewExpression->isEnabled();
  //  mExpressionDelayValid = mpExpressionDelay->mpBtnViewExpression->isEnabled();
  //  mExpressionEAValid = mpExpressionEA->mpBtnViewExpression->isEnabled();

  /*
    std::cout << "mExpressionDelayValid = " << mExpressionDelayValid
     << " - mExpressionEAValid = " << mExpressionEAValid
     << " - (mExpressionDelayValid && mExpressionEAValid) = " << (mExpressionDelayValid && mExpressionEAValid)
              << " !! mExpressionTriggerValid = " << mExpressionTriggerValid
     << " --> (mExpressionTriggerValid && (mExpressionDelayValid && mExpressionEAValid)) = "
     << (mExpressionTriggerValid && (mExpressionDelayValid && mExpressionEAValid)) << std::endl;
    std::cout << "mObjectOK = " << mObjectOK << std::endl;
  */
  //  mpBtnCommit->setEnabled((mObjectOK && mExpressionTriggerValid) && (mExpressionDelayValid && mExpressionEAValid));
  enableBtnCommit();
}

/*! Slot to enable the Commit button if the mathematical expression of EventAssignment is valid */
void CQEventWidget1::slotExpressionEAValid(bool valid)
{
  std::cout << "CQEW1::slotExpressionEAValid - valid = " << valid << std::endl;
  //  mExpressionEAValid = valid;

  //  if (valid)
  //    mpExpressionEA->mpExpressionWidgte->setColor(Valid);
  //    mpExpressionEA->mpExpressionWidgte->setColor(Valid);

  if (mpExpressionEA->mpExpressionWidget->text() == "")
    mpExpressionEA->mpBtnViewExpression->setEnabled(false);

  //  mExpressionTriggerValid = mpExpressionTrigger->mpBtnViewExpression->isEnabled();
  //  mExpressionDelayValid = mpExpressionDelay->mpBtnViewExpression->isEnabled();
  mExpressionEAValid = mpExpressionEA->mpBtnViewExpression->isEnabled();
  /*
    std::cout << "mExpressionTriggerValid = " << mExpressionTriggerValid
              << " - mExpressionDelayValid = " << mExpressionDelayValid
     << " - (mExpressionTriggerValid && mExpressionDelayValid) = " << (mExpressionTriggerValid && mExpressionDelayValid)
     << " !! mExpressionEAValid = " << mExpressionEAValid
     << " --> (mExpressionEAValid && (mExpressionTriggerValid && mExpressionDelayValid)) = "
     << (mExpressionEAValid && (mExpressionTriggerValid && mExpressionDelayValid)) << std::endl;
    std::cout << "mObjectOK = " << mObjectOK << std::endl;

    mpBtnCommit->setEnabled((mObjectOK && mExpressionEAValid) && (mExpressionTriggerValid && mExpressionDelayValid));
  */
  enableBtnCommit();
}

/*! Slot to add a new target without object target nor its expression
 *  Impact only on the appearance.
 */
void CQEventWidget1::slotAddTarget()
{
  // save current setting before taking the new one
  //  slotBtnNewClicked();  --> this is for creating a new event

  std::cout << "CQEW1::slotaddTarget - mEventKey = " << mEventKey << std::endl;

  // ----- correlated to GUI layout of the event assignment ----

  // hide the label and widget wrt expression
  mpLabelEA->hide();
  mpExpressionEA->hide();

  // disable add/delete buttons until the newly added assignment is saved
  mpBtnAddTarget->setDisabled(true);
  mpBtnDeleteTarget->setDisabled(true);

  // enable neccessary buttons
  mpBtnSelectObject->setEnabled(true);
  //  mpBtnDeleteTarget->setEnabled(true);
  mpBtnSaveTarget->setEnabled(true);
  mpBtnRevert->setEnabled(true);

  mObjectOK = false;
  /*
    // show the label and widget wrt expression
    mpLabelEA->show();
    mpExpressionEA->show();
  */
  // clear the widget of assignment expression
  mpExpressionEA->mpExpressionWidget->clear();

  // insert new item on the combo box mpCBTarget and set it as the active one
  std::cout << "CQEW1::slotAddTarget - before #item = " << mpCBTarget->count() << std::endl;
  mpCBTarget->insertItem("No Object - Please select one"); // add to the last one
  mpCBTarget->setCurrentItem(mpCBTarget->count() - 1);  // set the last one as active
  std::cout << "CQEW1::slotAddTarget - after #item = " << mpCBTarget->count() << std::endl;

  // ---- end of EA GUI layout ---
  /*
    // add the new assignment to pEvent
    CEvent* pEvent = dynamic_cast< CEvent * >(GlobalKeys.get(mEventKey));
  */ /*
    if (!pEvent)
    {
   std::string errorMessage = std::string("There is no event with key " + mEventKey);
   std::cout << "ERROR: There is no event with key " << mEventKey << std::endl;
   CCopasiMessage(CCopasiMessage::EXCEPTION, errorMessage.c_str());
    }

    // name of the target
    std::string assignKey = "Assignment_" + QString::number(pEvent->getNumAssignments()); // index starts from 0
    std::cout << "pEvent->getNumAssignments() = " << pEvent->getNumAssignments() << std::endl;

    pEvent->addAssignment(assignKey, "");
    pdelete(pEvent);
  */
  /*
    // if the standard name already exists then creating the new event will fail
    // thus, a growing index will automatically be added to the standard name
    int i=0;
    while (!CCopasiDataModel::Global->getModel()->createEvent(name))
    {
      i++;
      name = "event_";
      name += QString::number(i).utf8();
   std::cout << "NAME = " << name << std::endl;
    }
  */
}

/*! Slot to remove the active target from the appearance
 * Impact only on the appearance.
 */
void CQEventWidget1::slotDeleteTarget()
{
  // disable add/delete buttons until the newly deleted assignment is saved
  mpBtnDeleteTarget->setEnabled(false);
  mpBtnAddTarget->setEnabled(false);

  mpBtnRevert->setEnabled(true);

  // remove item from combo box Target
  std::cout << "CQEW1::slotDeleteTarget - before #item = " << mpCBTarget->count() << std::endl;
  std::cout << "mpCBTarget->currentItem() = " << mpCBTarget->currentItem() << " will be deleted!!" << std::endl;
  std::cout << "correlated name = " << mpCBTarget->currentText() << std::endl;
  std::cout << "correlated expression on the widget = " << mpExpressionEA->mpExpressionWidget->text() << std::endl;
  //  mDeletedAssignment = make_pair(mpCBTarget->currentText().utf8(), mpExpressionEA->mpExpressionWidget->text().utf8());

  // save the position of deleting assignment
  unsigned C_INT32 posDelete = mpCBTarget->currentItem();
  /*  mPosDelete = posDelete;
    std::cout << "posDelete = " << posDelete << std::endl;*/

  std::string text = takeObjectName(mpCBTarget->currentText());

  if (text != "")
    {
      // check the deleted position on the event object
      mPosDelete = mpEvent->getAssignmentIndex(text);
      std::cout << "mPosDelete = " << mPosDelete << std::endl;
      /*
          mDeleteAssignment.first = text;
          mDeleteAssignment.second = mpEvent->getAssignmentExpressionVector().second;
      */
      mDeletedAssign.first = mpCBTarget->currentItem();
      mDeletedAssign.second = text;
    }
  else
    mPosDelete = (unsigned C_INT32) - 1;

  /*  std::cout << "A - name = " << mDeleteAssignment.first
              << " - expression = " << mDeleteAssignment.second.getInfix() << std::endl;
  */

  std::cout << "A - name = " << mDeletedAssign.first
  << " - expression = " << mDeletedAssign.second << std::endl;

  std::cout << "B - mPosDelete = " << mPosDelete << " - posDelete = " << posDelete << std::endl;

  //  std::cout << "mCurrentAssignment.size() B = " << mCurrentAssignment.size() << std::endl;

  // delete the assignment from mCurrentAssignment
  //  std::vector<std::pair<std::string, CExpression> >::iterator it = mCurrentAssignment.begin();

  //  std::cout << "A - name = " << mCurrentAssignment[0+posDelete].first
  //            << " - expression = " << mCurrentAssignment[0+posDelete].second.getInfix() << std::endl;

  //  std::cout << "B - name = " << (it+posDelete)->first
  //            << " - expression = " << (it+posDelete)->second.getInfix() << std::endl;

  //  mCurrentAssignment.erase(it+posDelete, it+posDelete+1);

  //  std::cout << "mCurrentAssignment.size() A = " << mCurrentAssignment.size() << std::endl;

  // delete the highlighted item from appearance
  mpCBTarget->removeItem(posDelete);

  std::cout << "current: mpCBTarget->currentItem() = " << mpCBTarget->currentItem() << std::endl;

  /*
    // copy ...
    mDeletedAssignment = mpEvent->getAssignmentExpressionVector();
    // ... delete the corresponding item from the vector
    mpEvent->deleteAssignment(posDelete);

    std::cout << "AFTER DELETE: mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;
    std::cout << "AFTER DELETE: mDeletedAssignment.size() = " << mDeletedAssignment.size() << std::endl;
  */
  if (!mpCBTarget->count())  // the last item has been removed -> no target more on the combo box
    {
      // hide the label and widget wrt expression
      mpLabelEA->hide();
      mpExpressionEA->hide();
      /*
          // enable the delete button
          mpBtnDeleteTarget->setEnabled(false);

          // show the add button
          mpBtnAddTarget->setEnabled(true);
      */
      mObjectOK = false;
      enableBtnCommit();

      mpBtnAddTarget->setEnabled(true);
    }
  else // at least one target still exists on the combo box
    {
      std::cout << "mpCBTarget->currentItem() = " << mpCBTarget->currentItem() << std::endl;

      // if (mpCBTarget->current
      // actualize the expression widget to the next one since the assignment is not really deleted from event
      //    slotActualizeAssignmentExpression(mpCBTarget->currentItem());
      int pos = mpEvent->getAssignmentIndex(takeObjectName(mpCBTarget->currentText()));
      slotActualizeAssignmentExpression(pos);
      /*
          // enable the delete button
          mpBtnDeleteTarget->setEnabled(true);

          // show the add button
          mpBtnAddTarget->setEnabled(true);
      */
      //    {int y; std::cin >> y;}
      mObjectOK = true;
      enableBtnCommit();
    }

  //  {int y; std::cin >> y;}
  // ... and swap
  /*  mpEvent->setAssignmentExpressionVector(mDeletedAssignment);

    std::cout << "AFTER SWAP: mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;
    std::cout << "AFTER SWAP: mDeletedAssignment.size() = " << mDeletedAssignment.size() << std::endl;
  */
  std::cout << "CQEW1::slotDeleteTarget - after #item = " << mpCBTarget->count() << std::endl;

  std::cout << "mPosDelete = " << mPosDelete << std::endl;
}

/// Slot to save the active target by creating really the assignment
void CQEventWidget1::slotSaveTarget()
{
  //  std::cout << "CQEW1::slotSaveTarget - mEventKey = " << mEventKey << std::endl;
  std::cout << std::endl << "CQEW1::slotSaveTarget ... START" << std::endl;

  QString msg;

  // check existency of the object
  if (mpCBTarget->currentText().contains("No Object"))
    {
      msg = "No object is selected as shown on Assignment Target combo box.\nPlease select one object first.\n";

      CQMessageBox::critical(this, "Unable to save target without object", msg,
                             QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
      return;
    }

  // check existency of the expression
  if (mpExpressionEA->mpExpressionWidget->text() == "")
    {
      msg = "XXX - There is no expression defined on Assignment Expression widget.\nPlease fill the widget first.\n";

      CQMessageBox::critical(this, "Unable to save target without expression", msg,
                             QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
      return;
    }

  // work with object of class CEvent
  //  CEvent* pEvent = dynamic_cast< CEvent * >(GlobalKeys.get(mEventKey));
  //  if (!pEvent) return;

  // name of the target
  //  std::string assignKey = "Assignment_" + QString::number(pEvent->getNumAssignments()); // index starts from 0
  //  std::string assignKey = mpCBTarget->currentText();
  std::string assignKey = mAssignmentKey;
  std::cout << "assignKey = " << assignKey << std::endl;
  std::cout << "pEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;
  std::cout << "mpExpressionEA->mpExpressionWidget->getExpression() = "
  << mpExpressionEA->mpExpressionWidget->getExpression() << std::endl;
  //  {int y; std::cout << "L: " << __LINE__ << std::endl; std::cin >> y;}

  //  pEvent->addAssignment(assignKey, mpExpressionEA->mpExpressionWidget->text());
  mpEvent->addAssignment(assignKey, mpExpressionEA->mpExpressionWidget->getExpression());
  //  pdelete(pEvent);

  std::cout << "mpExpressionEA->mpExpressionWidget->getExpression() = "
  << mpExpressionEA->mpExpressionWidget->getExpression() << std::endl;

  // ----- correlated to GUI layout of the event assignment ----

  // disable unneccessary buttons
  mpBtnSaveTarget->setDisabled(true);

  // enable neccessary buttons
  mpBtnAddTarget->setEnabled(true);
  mpBtnSelectObject->setEnabled(true);
  mpBtnDeleteTarget->setEnabled(true);
  //  mpBtnCommit->setEnabled(true);

  // ---- end of EA GUI layout ---

  /*
    if (!pEvent)
    {
   std::string errorMessage = std::string("There is no event with key " + mEventKey);
   std::cout << "ERROR: There is no event with key " << mEventKey << std::endl;
   CCopasiMessage(CCopasiMessage::EXCEPTION, errorMessage.c_str());
    }

    // name of the target
    std::string assignKey = "Assignment_" + QString::number(pEvent->getNumAssignments()); // index starts from 0
    std::cout << "pEvent->getNumAssignments() = " << pEvent->getNumAssignments() << std::endl;

    pEvent->addAssignment(assignKey, "");
    pdelete(pEvent);
  */

  std::cout << "CQEW1::slotSaveTarget ... END" << std::endl << std::endl;
}

/* Slot to load all values wrt the active event widget */
bool CQEventWidget1::loadFromEvent(const CEvent *pEvent)
{
  std::cout << "CQEW1::loadFromEvent" << std::endl;

  if (!pEvent) return false;

  // Name
  mpLineEditName->setText(FROM_UTF8(pEvent->getObjectName()));

  // Expression of Trigger
  //  ((CQExpressionWidget *)mpEditExpressionTrigger->widget(0))->setExpression(pEvent->getExpression());
  mpExpressionTrigger->mpExpressionWidget->setExpression(pEvent->getExpressionTrigger());
  std::cout << "EXP of Trigger: " << pEvent->getExpressionTrigger() << std::endl;
  if (pEvent->getExpressionTrigger() == "")
    mpExpressionTrigger->mpBtnViewExpression->setEnabled(false);

  // Expression of Delay
  //  ((CQExpressionWidget *)mpEditExpressionDelay->widget(0))->setExpression(pEvent->getExpression());
  mpExpressionDelay->mpExpressionWidget->setExpression(pEvent->getExpressionDelay());
  std::cout << "EXP of Delay: " << pEvent->getExpressionDelay() << std::endl;
  if (pEvent->getExpressionDelay() == "")
    mpExpressionDelay->mpBtnViewExpression->setEnabled(false);

  // Expression of EventAssignment
  //  ((CQExpressionWidget *)mpEditExpressionEA->widget(0))->setExpression(pEvent->getExpression());
  /* temporary
    mpExpressionEA->mpExpressionWidget->setExpression(pEvent->getAssignmentExpressionStr());
    std::cout << "EXP of EA: " << pEvent->getAssignmentExpressionStr() << std::endl;
    if (pEvent->getAssignmentExpressionStr() == "")
      mpExpressionEA->mpBtnViewExpression->setEnabled(false);
  */
  //  mChangedTrigger = mChangedDelay = mChangedEA = false;
  mChanged = false;

  return true; //TODO: really check
}

/*! Load all values wrt a chosen saved event */
bool CQEventWidget1::loadFromEvent()
{
  std::cout << std::endl << "CQEW1::loadFromEvent ... START" << std::endl;

  if (!mpEvent) return false;

  // *** Name
  mpLineEditName->setText(FROM_UTF8(mpEvent->getObjectName()));

  // *** Expression of Trigger
  std::string expr;
  if (mpEvent->getTriggerExpressionPtr() != NULL)
    {
      expr = mpEvent->getTriggerExpressionPtr()->getInfix();
    }
  mpExpressionTrigger->mpExpressionWidget->setExpression(expr);
  std::cout << "EXP of Trigger: " << expr << std::endl;
  //  if (mpEvent->getExpressionTrigger() == " ")
  if (expr.empty())
    mpExpressionTrigger->mpBtnViewExpression->setEnabled(false);

  // *** Expression of Delay
  expr = "";
  if (mpEvent->getDelayExpressionPtr() != NULL)
    {
      expr = mpEvent->getDelayExpressionPtr()->getInfix();
    }
  mpExpressionDelay->mpExpressionWidget->setExpression(expr);
  std::cout << "EXP of Delay: " << expr << std::endl;
  //  if (mpEvent->getExpressionDelay() == "")
  //    mpExpressionDelay->mpBtnViewExpression->setEnabled(false);

  // TODO: *** Expression of EventAssignment ***

  mPosDelete = -1; // by default -> means: no item will be deleted

  //  std::cout << "AA -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments()
  //   << " -vs- mCurrentAssignment.size() = " << mCurrentAssignment.size() << std::endl;
  std::cout << "AA -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;

  // copy assignment from event
  //  mCurrentAssignment.resize(0);
  //  mCurrentAssignment.clear();
  //  if (!mCurrentAssignment.empty())
  //    mCurrentAssignment.clear();

  //  std::vector<std::pair<std::string, CExpression

  //  mCurrentAssignment.reserve(100);
  //  std::cout << "BB -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments()
  //   << " -vs- mCurrentAssignment.size() = " << mCurrentAssignment.size() << std::endl;

  //  mCurrentAssignment = *(mpEvent->getAssignmentExpressionVector());
  std::vector<std::pair<std::string, CExpression*> > currentAssignment;
  currentAssignment.reserve(100);
  currentAssignment = mpEvent->getAssignmentExpressionVector();

  std::cout << "CC -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments()
  //   << " -vs- mCurrentAssignment.size() = " << mCurrentAssignment.size() << std::endl;
  << " -vs- currentAssignment.size() = " << currentAssignment.size() << std::endl;

  mpEvent->showAssignments();
  std::vector<std::pair<std::string, CExpression*> >::iterator it;

  const CModelEntity* pME = NULL;

  if (mObjectKeyDisplayName.size() != currentAssignment.size()) // happens only at the first time after loading a cps file
    {
      for (it = currentAssignment.begin(); it != currentAssignment.end(); ++it)
        {
          QStringList sKeyDisplay = QStringList::split("_", FROM_UTF8(it->first));
          QString sObjectName = sKeyDisplay[0];
          QString sObjectIndex = sKeyDisplay[1];
          QString sName;
          std::cout << "it->first = " << it->first << std::endl;
          std::cout << sObjectName << " - " << sObjectIndex << std::endl;
          //   std::cout << sKeyDisplay[0] << " - " << sKeyDisplay[1] << std::endl;
          /*
                pME = dynamic_cast<const CModelEntity*>(mCommon.KeyMap.get(mKey));
                if (pME == NULL) fatalError();
                mAssignmentPair.first = pME->getKey();
          */
          if (sObjectName == "Compartment")
            {
              //              std::cout << "Compartments: " << CCopasiDataModel::Global->getModel()->getCompartments()[sObjectIndex.toULong()]->getKey() << std::endl;
              //     std::cout << "Compartments: " << CCopasiDataModel::Global->getModel()->getCompartments()[sObjectIndex.toULong()]->getObjectDisplayName() << std::endl;
              //              sName = FROM_UTF8(CCopasiDataModel::Global->getModel()->getCompartments()[sObjectIndex.toULong()]->getObjectDisplayName() + ".Volume");

              sName = FROM_UTF8(GlobalKeys.get(it->first)->getObjectDisplayName() + ".Volume");
              std::cout << "Compartments: " << sName << std::endl;
            }
          if (sObjectName == "Metabolite")
            {
              //              std::cout << "Metabolites: " << CCopasiDataModel::Global->getModel()->getMetabolites()[sObjectIndex.toULong()]->getKey() << std::endl;
              //     std::cout << "Metabolites: " << CCopasiDataModel::Global->getModel()->getMetabolites()[sObjectIndex.toULong()]->getObjectDisplayName() << std::endl;
              //              sName = FROM_UTF8("[" + CCopasiDataModel::Global->getModel()->getMetabolites()[sObjectIndex.toULong()]->getObjectDisplayName() + "]");
              sName = FROM_UTF8("[" + GlobalKeys.get(it->first)->getObjectDisplayName() + "]");
              std::cout << "Metabolites: " << sName << std::endl;
              //              std::cout << "Metabolites: " << std::endl;
            }
          if (sObjectName.contains("ModelValue"))
            {
              //              std::cout << "Global Quantities: " << CCopasiDataModel::Global->getModel()->getModelValues()[sObjectIndex.toULong()]->getKey() << std::endl;
              //              sName = FROM_UTF8(CCopasiDataModel::Global->getModel()->getModelValues()[sObjectIndex.toULong()]->getObjectDisplayName());
              sName = FROM_UTF8(GlobalKeys.get(it->first)->getObjectDisplayName());
              std::cout << "Global Quantities: " << sName << std::endl;
            }

          //   mObjectKeyDisplayName.push_back(std::make_pair(it->first, std::string((const char *)sName.local8Bit())));
          mObjectKeyDisplayName.push_back(std::make_pair(it->first, sName.latin1()));
        }
    }
  else
    std::cout << "mObjectKeyDisplayName.size() = " << mObjectKeyDisplayName.size() << std::endl;

  std::vector<std::pair<std::string, std::string> >::iterator itA = mObjectKeyDisplayName.begin();
  std::cout << "Key - Display Name" << std::endl;
  for (; itA != mObjectKeyDisplayName.end(); ++itA)
    std::cout << itA->first << " - " << itA->second << std::endl;

  std::cout << "Assignment" << std::endl;
  mpEvent->showAssignments();

  //  {int y; std::cout << "L" << __LINE__ << std::endl; std::cin >> y;}

  /*
    //swap process
    std::vector<std::pair<std::string, CExpression> > mAssignmentAux;
    std::vector<std::pair<std::string, CExpression> >::iterator it = mCurrentAssignment.end();
  //  std::vector<std::pair<std::string, CExpression> >::iterator itB = mAssignmentAux.begin();
    for (; it != mCurrentAssignment.begin(); --it)
    {
      mAssignmentAux.push_back(*it);
    }

    std::cout << "DD -vs- mAssignmentAux.size() = " << mAssignmentAux.size()
     << " -vs- mCurrentAssignment.size() = " << mCurrentAssignment.size() << std::endl;

    if (!mCurrentAssignment.empty())
      mCurrentAssignment.clear();

    std::cout << "EE -vs- mAssignmentAux.size() = " << mAssignmentAux.size()
     << " -vs- mCurrentAssignment.size() = " << mCurrentAssignment.size() << std::endl;

    mCurrentAssignment = mAssignmentAux;
  */
  /*  std::vector<std::pair<std::string, CExpression> >::iterator it = mpEvent
    for (int j=0; j<mpEvent->getnumAssignments(); j++)
      mCurrentAssignment->push_back()
  */
  //  std::cout << "mpCBTarget->count() = " << mpCBTarget->count()
  //  std::cout << "FF -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments()
  //   << " -vs- mCurrentAssignment.size() = " << mCurrentAssignment.size() << std::endl;
  //  {int y; std::cin >> y;}

  // fill the combo box and the expression widget with correct assignments
  mpCBTarget->clear();

  unsigned C_INT32 idx = 0;
  //  std::vector<std::pair<std::string, CExpression> >::iterator it;
  //  for (it = mCurrentAssignment.begin(); it != mCurrentAssignment.end(); ++it)
  for (it = currentAssignment.begin(); it != currentAssignment.end(); ++it)
    {
      //    mpCBTarget->insertItem(FROM_UTF8("<" + it->first + ">")); // the combo box
      mpCBTarget->insertItem(FROM_UTF8("<" + mObjectKeyDisplayName[idx].second + ">")); // the combo box
      mpExpressionEA->mpExpressionWidget->setExpression(mpEvent->getAssignmentExpressionPtr(idx)->getInfix()); // the expression widget
      idx++;
    }

  std::cout << __LINE__ << " mpCBTarget->count() = " << mpCBTarget->count() << std::endl;
  // if not empty, set to the first entry
  if (mpCBTarget->count())
    {
      mObjectOK = true; // at least one object target exists
      mpBtnDeleteTarget->setEnabled(true);
      mpBtnSelectObject->setEnabled(true);
      //    mpCBTarget->setCurrentItem(0);
      //    slotActualizeAssignmentExpression(0);
      mpCBTarget->setCurrentItem(mpCBTarget->count() - 1);
      slotActualizeAssignmentExpression(mpCBTarget->count() - 1);
    }
  else
    {
      mObjectOK = false; // no object target
      mpBtnDeleteTarget->setEnabled(false);
      mpBtnSelectObject->setEnabled(false);

      mpExpressionEA->mpExpressionWidget->clear(); // do we still need it ???

      // hide the label and widget wrt expression
      mpLabelEA->hide();
      mpExpressionEA->hide();
    }

  /*
    // an item has been added and the user will cancel the change
    if (mpCBTarget->count() == mpEvent->getNumAssignments()+1)
    {
      std::cout << "Adding is cancelled" << std::endl;
      // just remove the last one since the candidate new one must be there
  //    mpCBTarget->setCurrentItem(mpCBTarget->count()-1);
      slotDeleteTarget();
    }
    // an item has been deleted and the user will cancel the change
    else if (mpCBTarget->count() == mpEvent->getNumAssignments()-1)
    {
      std::cout << "Deleting is cancelled" << std::endl;
      // add the removed assignment by taking the correlated values from event
   std::cout << "====== mpCBTarget->currentItem() BEFORE = " << mpCBTarget->currentItem() << std::endl;
   std::cout << "mpCBTarget->count() = " << mpCBTarget->count() << std::endl;
  // mpCBTarget->insertItem(mEAName, mpCBTarget->currentItem());  // it will automatically be the current item
  // mpCBTarget->insertItem(mDeletedAssignment.first, mpCBTarget->currentItem());  // it will automatically be the current item

   if (mpCBTarget->count() == 1)
     mpCBTarget->setCurrentItem(0);

   std::cout << "mpCBTarget->currentItem() AFTER = " << mpCBTarget->currentItem() << std::endl;
   std::cout << "mpCBTarget->count() = " << mpCBTarget->count() << std::endl;

  // mpExpressionEA->mpExpressionWidget->setText(mDeletedAssignment.second);
  //    slotActualizeAssignmentExpression(mpCBTarget->currentItem());
    }
    else if (mpCBTarget->count() != mpEvent->getNumAssignments())
    {
      std::cout << "ERROR on L" << __LINE__ << " in " << __FILE__ << std::endl;
      std::cout << "mpCBTarget->count() = " << mpCBTarget->count()
       << " -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;
      return false;
    }
  */ /*
    // actualize the EventAssignment by setting to the current entry
    mpCBTarget->setCurrentItem(mpCBTarget->currentItem());
    slotActualizeAssignmentExpression(mpCBTarget->currentItem());

    // actualize the EventAssignment by setting to the current entry
    mpCBTarget->setCurrentItem(0);
    slotActualizeAssignmentExpression(0);
  */
  // disable commit button -> re-activate the button whenever there is something new on the event
  mpBtnCommit->setEnabled(false);
  mpBtnAddTarget->setEnabled(true);

  mpBtnRevert->setEnabled(false);

  //  mChangedTrigger = mChangedDelay = mChangedEA = false;
  mChanged = false;

  mpEvent->showAssignments();

  std::cout << "CQEW1::loadFromEvent ... END" << std::endl << std::endl;

  return true; //TODO: really check
}

/*! The slot to save all current values of the active event widget */
void CQEventWidget1::saveToEvent()
{

  std::cout << std::endl << "CQEW1::saveToEvent ... START" << std::endl;

  if (!mpEvent) return;

  std::cout << "-> A mEventKey = " << mEventKey << std::endl;

  // set name of event
  if (mpEvent->getObjectName() != (const char *) mpLineEditName->text().utf8())
    {
      if (!mpEvent->setObjectName((const char *) mpLineEditName->text().utf8()))  // the new name is rejected as it has been used
        {
          QString msg;
          msg = "Unable to rename event '" + FROM_UTF8(mpEvent->getObjectName()) + "'\n"
                + "to '" + mpLineEditName->text() + "' since an event with that name already exists.\n";

          QMessageBox::information(this,
                                   "Unable to rename Event",
                                   msg,
                                   QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);

          mpLineEditName->setText(FROM_UTF8(mpEvent->getObjectName()));
        }
      else  // the new name is accepted
        {
          protectedNotify(ListViews::EVENT, ListViews::RENAME, mEventKey);
          mChanged = true;
        }
    }

  std::cout << "-> B mEventKey = " << mEventKey << std::endl;

  //  update(pEvent->getActionObjectKey, objKey);
  //  pEvent->setObjectName((const char *)mpLineEditName->text().utf8());

  //mpRi->setReactionName((const char *)mpLineEditName->text().utf8());

  // set expression of Trigger
  std::cout << "Expression Trigger: " << mpExpressionTrigger->mpExpressionWidget->getExpression() << std::endl;
  std::string expr;
  if (mpEvent->getTriggerExpressionPtr() != NULL)
    {
      expr = mpEvent->getTriggerExpressionPtr()->getInfix();
    }
  if (expr != mpExpressionTrigger->mpExpressionWidget->getExpression())
    {
      CExpression* pNewExpression = dynamic_cast<CExpression*>(CEvaluationTree::create(CEvaluationTree::Boolean));
      pNewExpression->setInfix(mpExpressionTrigger->mpExpressionWidget->getExpression());
      mpEvent->setTriggerExpressionPtr(pNewExpression);
      mChanged = true;
    }

  std::cout << "-> C mEventKey = " << mEventKey << std::endl;

  // set expression of Delay
  if (mpExpressionDelay->mpExpressionWidget->text() == "")
    mpExpressionDelay->mpExpressionWidget->setText("0");
  //    mpExpressionDelay->mpBtnViewExpression->setEnabled(false);

  std::cout << "Expression Delay: " << (mpExpressionDelay->mpExpressionWidget->getExpression()) << std::endl;
  expr = "";
  if (mpEvent->getDelayExpressionPtr() != NULL)
    {
      expr = mpEvent->getDelayExpressionPtr()->getInfix();
    }
  if (expr != mpExpressionDelay->mpExpressionWidget->getExpression())
    {
      CExpression* pNewExpression = new CExpression;
      pNewExpression->setInfix(mpExpressionDelay->mpExpressionWidget->getExpression());
      mpEvent->setDelayExpressionPtr(pNewExpression);
      mChanged = true;
    }

  // TODO: ---- about EventAssignment ----

  std::cout << "L" << __LINE__ << " A mpCBTarget->count() = " << mpCBTarget->count()
  << " -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;
  std::cout << "mPosDelete = " << mPosDelete << std::endl;

  bool success = true;

  mpEvent->showAssignments();
  // first of all, permanently remove the deleted assignment
  if (mPosDelete > (unsigned C_INT32) - 1)
    mpEvent->deleteAssignment(mPosDelete);
  /*
    mCurrentAssignment = mpEvent->getAssignmentExpressionVector();

    std::cout << "CC -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments()
     << " -vs- mCurrentAssignment.size() = " << mCurrentAssignment.size() << std::endl;
  */

  std::cout << "L" << __LINE__ << " B mpCBTarget->count() = " << mpCBTarget->count()
  << " -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;

  mpEvent->showAssignments();
  //  {int y; std::cout << "CQEW1 L: " << __LINE__ << std::endl; std::cin >> y;}

  // if new/modify assignment exists then the current position must be on it; otherwise, the expression cannot be saved
  int newPosition = -1;
  std::string newKey = "";
  std::string newExpression = "";

  if (mpCBTarget->count() != (int) mObjectKeyDisplayName.size())
    {
      std::cout << "mpCBTarget->count() = " << mpCBTarget->count() << " - mObjectKeyDisplayName.size() = "
      << mObjectKeyDisplayName.size() << std::endl;
      std::cout << "Abort on L" << __LINE__ << std::endl;
    }

  if (mpCBTarget->count() > (int) mpEvent->getNumAssignments())
    {

      // std::string Key = CCopasiDataModel::Global->getModel()->getKey();
      // std::cout << "Key = " << Key << std::endl;

      newPosition = mpCBTarget->currentItem();
      //    newKey = takeObjectName(mpCBTarget->currentText());
      newKey = mObjectKeyDisplayName[newPosition].first;
      newExpression = mpExpressionEA->mpExpressionWidget->getExpression();
    }

  std::cout << "New position: " << newPosition << " - key: " << newKey << " - expression: " << newExpression << std::endl;
  //  {int y; std::cout << "L: " << __LINE__ << std::endl; std::cin >> y;}

  int modPosition = -1;
  std::string modExpression = "";

  if (mpCBTarget->count())
    {
      modPosition = mpCBTarget->currentItem();
      modExpression = mpExpressionEA->mpExpressionWidget->getExpression();
    }

  std::cout << "Mod position: " << modPosition << " - expression: " << modExpression << std::endl;

  //  {int y; std::cout << "L: " << __LINE__ << std::endl; std::cin >> y;}

  for (int i = 0; i < mpCBTarget->count(); i++)
    {
      if (i == newPosition)
        {
          // new assignment exists
          std::cout << "i: " << i << " --> new key " << newKey << " - new expression " << newExpression << std::endl;
          success = mpEvent->addAssignment(newKey, newExpression);
          //      mpCBTarget->setCurrentItem(i);
          //   slotActualizeAssignmentExpression(i);
          //   {int y; std::cout << "AA" << std::endl; std::cin >> y;}
        }
      else
        {
          // modified assignment may exist
          mpCBTarget->setCurrentItem(i);
          slotActualizeAssignmentExpression(i);

          //   std::string assignKey = takeObjectName(mpCBTarget->currentText());
          std::string assignKey = mObjectKeyDisplayName[i].first;
          std::string assignExpression = "";

          if (i == modPosition)
            assignExpression = modExpression;
          else
            assignExpression = mpExpressionEA->mpExpressionWidget->getExpression();

          std::cout << "i: " << i << " --> assignKey = " << assignKey << " - assignExpression = " << assignExpression << std::endl;
          //      {int y; std::cout << "BB - 1" << std::endl; std::cin >> y;}
          success = mpEvent->updateAssignment(mpCBTarget->currentItem(), assignKey, assignExpression);
          //   {int y; std::cout << "BB - 2" << std::endl; std::cin >> y;}
        }
      // {int y; std::cout << "CC" << std::endl; std::cin >> y;}
    }

  /*
    std::pair<std::string, CExpression> newAssignment;
    std::pair<std::string, CExpression> modifyAssignment;

    // check whether the currently highlighted assignment is new, modify, or as before.
    // deleted assignment is not longer on the combo box; it is then impossible to be chosen.
    if (mpCBTarget->currentItem() == mpEvent->getNumAssignments())
    {
      // new assignment since index starts from 0
      newAssignment.first = takeObjectName(mpCBTarget->currentText());
   newAssignment.second =
   mpExpressionEA->mpExpressionWidget->setExpression(mpEvent->getAssignmentExpressionStr(idx));
    }

    // save last expression, either new or modification
    std::string lastExpression = mpExpressionEA->mpExpressionWidget->getExpression();
    int posExpression = mpCBTarget->currentItem();
    std::cout << "new expression " << newExpression << " on position " << posExpression << std::endl;
  */
  /*
    // remove all assignments from event
    mpEvent->clearAssignment();

    std::cout << "mCurrentAssignment.size() = " << mCurrentAssignment.size() << std::endl;

    // save new expression, either new or modification
    std::string newExpression = mpExpressionEA->mpExpressionWidget->getExpression();
    int posExpression = mpCBTarget->currentItem();
    std::cout << "new expression " << newExpression << " on position " << posExpression << std::endl;

    {int y; std::cout << "AA" << std::endl; std::cin >> y;}

    for (int i=0; i<mpCBTarget->count(); i++)
  //  for (int i=mpCBTarget->count(); i>0; i--)
    {
      QString tmp = mpCBTarget->text(i);
   tmp.remove("<");
   tmp.remove(">");
   std::string assignKey = tmp;

   std::cout << "i : " << i << " - assignKey = " << assignKey << std::endl;

  //    if (i==mCurrentAssignment.size()) // there is a new assignment !!
      if (i==posExpression) // there is a new expression !!
   {
     std::cout << "newExpression = " << newExpression << std::endl;
        {int y; std::cout << "BB" << std::endl; std::cin >> y;}
     success = mpEvent->addAssignment(assignKey, newExpression);
      }
   else
   {
        mpCBTarget->setCurrentItem(i);
     slotActualizeAssignmentExpression(i);
     std::cout << "mpExpressionEA->mpExpressionWidget->getExpression() = " << mpExpressionEA->mpExpressionWidget->getExpression() << std::endl;
        {int y; std::cout << "CC" << std::endl; std::cin >> y;}
        success = mpEvent->addAssignment(assignKey, mpExpressionEA->mpExpressionWidget->getExpression());
      }
   {int y; std::cout << "DD" << std::endl; std::cin >> y;}
    }
    {int y; std::cout << "EE" << std::endl; std::cin >> y;}
  */
  if (!success)
    {
      QString msg;
      msg = "The current assignment fails to be saved";

      QMessageBox::critical(this, "Fail to Save Current Assignment", msg,
                            QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
      return;
    }

  mChanged = true;

  //  pdelete(pEvent);
  /*
    std::cout << "mpExpressionEA->mpExpressionWidget->getExpression() = "
              << mpExpressionEA->mpExpressionWidget->getExpression() << std::endl;

    // ----- correlated to GUI layout of the event assignment ----

    // disable unneccessary buttons
    mpBtnSaveTarget->setDisabled(true);
  */
  /*  // enable neccessary buttons
    mpBtnAddTarget->setEnabled(true);
  //  mpBtnSelectObject->setEnabled(true);
    mpBtnDeleteTarget->setEnabled(true);
  */
  // :TODO Bug 322: This should only be called when actual changes have been saved.
  //  CCopasiDataModel::Global->changed(); --> what does it do ??

  if (mChanged)
    {
      CCopasiDataModel::Global->changed();
      protectedNotify(ListViews::EVENT, ListViews::CHANGE, mEventKey);
    }

  mChanged = false;

  mpBtnRevert->setEnabled(false);

  std::cout << "CQEW1::saveToEvent ... END" << std::endl << std::endl;
}

/*! The slot to update the active event widget */
bool CQEventWidget1::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string &key)
{
  //  std::cout << "CQEW1::update - mEventKey = " << mEventKey << std::endl;
  return true;
}

/*! Function to interact with an object of class CEvent */
bool CQEventWidget1::enter(const std::string & key)
{
  std::cout << "CQEW1::enter - key = " << key << std::endl;
  mEventKey = key;
  //  CEvent* pEvent = dynamic_cast< CEvent * >(GlobalKeys.get(key));
  mpEvent = dynamic_cast< CEvent * >(GlobalKeys.get(key));

  if (mpEvent)
    {
      //    load();
      //    return loadFromEvent(mpEvent);
      return loadFromEvent();
    }

  mpListView->switchToOtherWidget(114, ""); //TODO
  return false;
}

/*! The slot to be done before leaving the active event widget */
bool CQEventWidget1::leave()
{
  std::cout << "CQEW1::leave" << std::endl;
  saveToEvent();
  mObjectKeyDisplayName.resize(0);
  return true;
}

/// Slot to select an object from the existing ones
void CQEventWidget1::slotSelectObject()
{
  CCopasiSimpleSelectionTree::SelectionFlag mExpressionType = CCopasiSimpleSelectionTree::TRANSIENT_EXPRESSION;

  QString oldText = mpCBTarget->currentText();
  QString newText = mpCBTarget->currentText();
  unsigned C_INT32 index = mpCBTarget->currentItem();

  std::cout << "CQEW1::slotSelectObject" << std::endl;
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, mExpressionType);

  if (pObject)
    {
      // Check whether the object is valid
      if (!CCopasiSimpleSelectionTree::filter(mExpressionType, pObject))
        {
          CQMessageBox::critical(this, "Invalid Selection",
                                 "The use of the selected object is not allowed in this type of expression.");
          return;
        }

      // Check whether only allowable object (Transient Volumes, Transient Concentrations, Transient Values) has been selected

      QString objectName = FROM_UTF8(pObject->getObjectName());
      std::cout << "Get Object Name = " << objectName << std::endl;

      if (objectName != "Volume" && objectName != "Concentration" && objectName != "Value")
        {

          QString msg = "The selected object " + objectName + " is not allowed.";
          msg += "\nPlease choose one of Transient Volumes, Transient Concentrations, or Transient Values.\n";

          CQMessageBox::critical(this, "Unallowable object has been chosen", msg,
                                 QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
          return;
        }

      std::cout << "*** TEST BEFORE ***" << std::endl;
      std::string Insert = pObject->getObjectDisplayName();
      std::cout << "Insert object BEFORE = " << Insert << std::endl;

      /*
         std::cout << "Get Display Name = " << pObject->getObjectDisplayName() << std::endl;
         std::cout << "Get Object Type = " << pObject->getObjectType() << std::endl;
         std::cout << "Get Object Parent = " << pObject->getObjectParent()->getKey() << std::endl;
         std::cout << "Get CN = " << pObject->getCN() << std::endl;
      */
      //      mParseList[Insert] = pObject;

      // We need to escape >
      std::string::size_type pos = Insert.find_first_of("\\>");
      while (pos != std::string::npos)
        {
          Insert.insert(pos, "\\");
          pos += 2;
          pos = Insert.find_first_of("\\>", pos);
        }

      //   CCopasiDataModel::Global->getModel()->getEvents()[name]->getKey()
      //   getModel->getEvents()[mEventKey]

      std::cout << "Insert object AFTER = " << Insert << std::endl;

      newText = FROM_UTF8("<" + Insert + ">");
      std::cout << "newText = " << newText << std::endl;

      // check duplicacy -> as single event cannot have multiple EventAssignment !!!
      bool duplicacy = false;
      for (int i = 0; i < mpCBTarget->count(); i++)
        {
          if (mpCBTarget->text(i) == newText)
            {

              QString msg = "A single event cannot have multiple EventAssignment assigning the same object.";
              msg += "\nThe selected object " + newText + ", however, has been listed on Target combo box.";
              msg += "\nPlease select another object.\n";

              CQMessageBox::critical(this, "Unable to save target with duplicate object", msg,
                                     QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
              return;
            }
        }

      //      insert(FROM_UTF8("<" + Insert + ">"));
      std::cout << FROM_UTF8("<" + Insert + ">") << std::endl;

      //      mpCBTarget->changeItem(FROM_UTF8("<" + Insert + ">"), mpCBTarget->currentItem());
      mpCBTarget->changeItem(FROM_UTF8("<" + Insert + ">"), mpCBTarget->currentItem());

      std::vector<std::pair<std::string, std::string> >::iterator it = mObjectKeyDisplayName.begin();
      std::cout << "B E F O R E" << std::endl;
      for (; it != mObjectKeyDisplayName.end(); ++it)
        std::cout << it->first << " - " << it->second << std::endl;

      mAssignmentKey = pObject->getObjectParent()->getKey();

      if (mpCBTarget->count() > (int) mpEvent->getNumAssignments())
        {
          // new assignment -> not able to add one more new assignment before the current new one is saved
          if (mObjectKeyDisplayName.size() == mpEvent->getNumAssignments() + 1)
            mObjectKeyDisplayName.pop_back();
          mObjectKeyDisplayName.push_back(std::make_pair(mAssignmentKey, Insert));
        }
      else
        {
          mObjectKeyDisplayName[index].first = mAssignmentKey;
          mObjectKeyDisplayName[index].second = Insert;
        }

      std::cout << "A F T E R" << std::endl;
      for (it = mObjectKeyDisplayName.begin(); it != mObjectKeyDisplayName.end(); ++it)
        std::cout << it->first << " - " << it->second << std::endl;

      //   {int y; std::cout << "L: " << __LINE__ << std::endl; std::cin >> y;}

      // enable Commit button
      //   mObjectOK = true;
      //      mpBtnCommit->setEnabled((mObjectOK && mExpressionEAValid) && (mExpressionTriggerValid && mExpressionDelayValid));

      //  if (mpCBTarget->currentText().contains("No Object"))
      //  {
      // show the label and widget wrt expression
      mpLabelEA->show();
      mpExpressionEA->show();

      // in case user replace other object target instead of one with 'No Object' text.
      bool containNoObject = false;

      for (int i = 0; i < mpCBTarget->count(); i++)
        {
          if (mpCBTarget->text(i).contains("No Object"))
            {
              containNoObject = true;
              continue;
            }
        }

      // std::cout << "A - mpCBTarget->currentItem() = " <<  mpCBTarget->currentItem() << std::endl;
      // save object if neccessary

      /*    if (newText != oldText)

         mpEvent->updateAssignment(mpCBTarget->currentItem(), newText, mpExpressionEA->mpExpressionWidget->getExpression());
      */
      //    if (newText != oldText && !mpCBTarget->currentText().contains("No Object"))
      if (newText != oldText && !containNoObject)
        {
          //    mpBtnCommit->setEnabled(true);
          //    mpBtnSaveTarget->setEnabled(true);
          mObjectOK = true;
          enableBtnCommit();
          /*
             std::cout << "B - mpCBTarget->currentItem() = " <<  mpCBTarget->currentItem() << std::endl;
             std::cout << "BA - index = " <<  index << std::endl;
             mpCBTarget->removeItem(index);
             mpCBTarget->insertItem(FROM_UTF8("<" + Insert + ">"), index);
             std::cout << "C - mpCBTarget->currentItem() = " <<  mpCBTarget->currentItem() << std::endl;
             mpCBTarget->setCurrentItem(index);
             std::cout << "D - mpCBTarget->currentItem() = " <<  mpCBTarget->currentItem() << std::endl;
          */
        }
    }

  //    slotSaveTarget();
}

/// Slot to actualize the assignment expression widget of event assignment according to the target
void CQEventWidget1::slotActualizeAssignmentExpression(int index)
{
  std::cout << "CQEW1::slotActualizeAssignmentExpression - index = " << index << std::endl;

  //  std::string name = "Assignment_" + QString::number(index);

  //  std::cout << "name = " << name << std::endl;

  //  if (!mpEvent) return;

  std::cout << "mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;
  if (!mpEvent->getNumAssignments()) return; // no assignment
  //  std::cout << "mCurrentAssignment.size() = " << mCurrentAssignment.size() << std::endl;
  //  if (!mCurrentAssignment.size()) return;  // no assignment

  if (index >= (int) mpEvent->getNumAssignments()) // ">=" since index 0 represents the first event assignment
    //  if (index >= mCurrentAssignment.size()) // ">=" since index 0 represents the first event assignment
    {
      std::cout << "index = " << index << " > mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;

      QString msg;

      mpExpressionEA->mpExpressionWidget->clear();

      // no object is selected
      if (mpCBTarget->currentText().contains("No Object"))
        {
          // hide the label and widget wrt expression
          mpLabelEA->hide();
          mpExpressionEA->hide();

          /*
                msg = "No object is selected as shown on Assignment Target combo box.\nPlease select one object first.\n";

                CQMessageBox::critical(this, "Unable to save target without object", msg,
                                       QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
          */
          return;
        }

      // check existency of the expression
      if (mpExpressionEA->mpExpressionWidget->text() == "")
        {
          msg = "There is no expression defined on Assignment Expression widget.\nPlease fill the widget first.\n";

          CQMessageBox::critical(this, "Unable to save target without expression", msg,
                                 QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
          return;
        }

      // never happens with new structure -> it will be deleted (15.05.08)
      msg = "The currently active event assignment is not saved.\nPlease save it first.\n";

      CQMessageBox::critical(this, "Unsaved current active event assignment", msg,
                             QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);

      return;
    }

  /*
    std::cout << "AAA" << std::endl;
    if (mpCBTarget->currentText().contains("No Object"))
    {
      // hide the label and widget wrt expression
      mpLabelEA->hide();
      mpExpressionEA->hide();
      return;
    }

    std::cout << "BBB" << std::endl;

    // empty expression widget
    if (!mpExpressionEA->mpExpressionWidget->length())
    {
      mpExpressionEA->mpExpressionWidget->clear();
      return;
    }
  */
  //  std::cout << "expression = " << mpEvent->getAssignmentExpressionStr(index) << std::endl;
  std::cout << "expression = " << mpEvent->getAssignmentExpressionStr(index) << std::endl;
  //  std::cout << "expression = " << mCurrentAssignment[index].second.getInfix() << std::endl;
  //    std::cout << "expression = " << CCopasiDataModel::Global->getModel()->getEvents()[mEventKey]->getAssignmentExpressionStr(index) << std::endl;

  // show the label and widget wrt expression
  mpLabelEA->show();
  mpExpressionEA->show();

  // update expression widget wrt a chosen target
  //  QString text = FROM_UTF8(mpEvent->getAssignmentExpressionStr(index));
  std::string text = mpEvent->getAssignmentExpressionStr(index);
  //  QString text = mCurrentAssignment[index].second.getInfix();
  std::cout << "text = " << text << std::endl;
  /*  QString newText = text;
    QString newTextAux;
    while (text.contains("<CN"))
    {
      unsigned C_INT32 posStart = text.find("<CN");
      unsigned C_INT32 posEnd = text.find("Reference");
  // std::cout << "start: " << posStart << " - end: " << posEnd << std::endl;
   newTextAux = text.remove(posStart, (posEnd+9) - posStart +1);
  //    std::cout << "newTextAux = " << newTextAux << std::endl;
   newTextAux = newTextAux.insert(posStart, "<");
  //    std::cout << "newTextAux = " << newTextAux << std::endl;
    text = newTextAux;
   newText = text;
  //    std::cout << "text new = " << text << std::endl;
    }
    std::cout << "L" << __LINE__ << " - newText = " << newText << std::endl;
    {int y; std::cout << "L: " << __LINE__ << std::endl; std::cin >> y;}
  */
  mpExpressionEA->mpExpressionWidget->clear();
  //  mpExpressionEA->mpExpressionWidget->setText(newText);
  mpExpressionEA->mpExpressionWidget->setExpression(text);

  // disable commit button -> re-activate the button whenever there is something new on the EventAssignment expression
  mpBtnCommit->setEnabled(false);
  // so do the button Revert
  //  mpBtnRevert->setEnabled(false);
}
/*
/// Slot to actualize the assignment expression widget of event assignment according to the target
void CQEventWidget1::slotActualizeAssignmentExpression(std::string & key)
{
  std::cout << "CQEW1::slotActualizeAssignmentExpression - key = " << key << std::endl;

//  std::string name = "Assignment_" + QString::number(index);

//  std::cout << "name = " << name << std::endl;

//  if (!mpEvent) return;

  std::cout << "mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;
  if (!mpEvent->getNumAssignments()) return; // no assignment
//  std::cout << "mCurrentAssignment.size() = " << mCurrentAssignment.size() << std::endl;
//  if (!mCurrentAssignment.size()) return;  // no assignment

//  if (text.contains("No Object")) return; // no specific object target

  // save the deleted text without character "<" and ">"
  std::string key = takeObjectName(text);
  if (key == "") return;

  std::cout << "key = " << key << std::endl;

  std::cout << "expression = " << mpEvent->getAssignmentExpressionStr(key) << std::endl;

  // show the label and widget wrt expression
  mpLabelEA->show();
  mpExpressionEA->show();

  // update expression widget wrt a chosen target
//  QString text = mpEvent->getAssignmentExpressionStr(index);
//  QString text = mCurrentAssignment[index].second.getInfix();
  QString text = FROM_UTF8(mpEvent->getAssignmentExpressionStr(key));
  std::cout << "text = " << text << std::endl;
  QString newText = text;
  QString newTextAux;
  while (text.contains("<CN"))
  {
    unsigned C_INT32 posStart = text.find("<CN");
    unsigned C_INT32 posEnd = text.find("Reference");
// std::cout << "start: " << posStart << " - end: " << posEnd << std::endl;
 newTextAux = text.remove(posStart, (posEnd+9) - posStart +1);
//    std::cout << "newTextAux = " << newTextAux << std::endl;
 newTextAux = newTextAux.insert(posStart, "<");
//    std::cout << "newTextAux = " << newTextAux << std::endl;
  text = newTextAux;
 newText = text;
//    std::cout << "text new = " << text << std::endl;
  }
  std::cout << "newText = " << newText << std::endl;

  mpExpressionEA->mpExpressionWidget->clear();
  mpExpressionEA->mpExpressionWidget->setText(newText);

  // disable commit button -> re-activate the button whenever there is something new on the EventAssignment expression
  mpBtnCommit->setEnabled(false);
  // so do the button Revert
//  mpBtnRevert->setEnabled(false);
}
 */
/*! Function to enable/disable the button Commit */
void CQEventWidget1::enableBtnCommit()
{
  std::cout << "CQEW1::enableBtnCommit" << std::endl;

  std::cout << "mExpressionTriggerValid = " << mExpressionTriggerValid
  << " - mExpressionDelayValid = " << mExpressionDelayValid
  << " -> (mExpressionTriggerValid && mExpressionDelayValid) = " << (mExpressionTriggerValid && mExpressionDelayValid)
  << " - mObjectOK = " << mObjectOK
  << " - mExpressionEAValid = " << mExpressionEAValid
  << " -> (mObjectOK && mExpressionEAValid) = "
  << (mObjectOK && mExpressionEAValid)
  << " ==> mpBtnCommit is enabled ? "
  << ((mObjectOK && mExpressionEAValid) && (mExpressionTriggerValid && mExpressionDelayValid)) << std::endl;

  mpBtnCommit->setEnabled((mObjectOK && mExpressionEAValid) && (mExpressionTriggerValid && mExpressionDelayValid));

  if (mExpressionEAValid || mExpressionTriggerValid) // trick to trigger the button Revert
    mpBtnRevert->setEnabled(true);
}

/*! Function to take only the object name without characters "<" and ">" */
std::string CQEventWidget1::takeObjectName(QString text)
{
  if (text.contains("No Object"))
    return "";

  text.remove("<");
  text.remove(">");
  std::string key = text.latin1();
  std::cout << "CQEW1::takeObjectName - key = " << key << std::endl;
  return key;
}
