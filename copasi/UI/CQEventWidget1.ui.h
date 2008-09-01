// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQEventWidget1.ui.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/01 17:13:43 $
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
  /*  // check whether no empty expression widget exists
    if (!checkAllExpressionsOK())
      {
        QString msg = "There is at least one empty expression widget. Please check it.";

        CQMessageBox::critical(this, "Unable to save model with empty expression widget", msg,
                               QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
        return;
      }
  */
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
  protectedNotify(ListViews::EVENT, ListViews::ADD);
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
  mpCheckBoxDelay->setChecked(false);
  slotApplyDelay(false);

  // SIGNAL-SLOT connections

  connect(mpLineEditName, SIGNAL(edited()), this, SLOT(slotNameChanged()));

  connect(mpExpressionTrigger->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotExpressionTriggerValid(bool)));
  connect(mpExpressionDelay->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotExpressionDelayValid(bool)));
  connect(mpExpressionEA->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotExpressionEAValid(bool)));

  connect(mpLBTarget, SIGNAL(highlighted(int)), this, SLOT(slotActualizeAssignmentExpression(int)));
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
  mpBtnDeleteTarget->setDisabled(true);
  mpBtnRevert->setEnabled(false);

  // hide the label and widget wrt expression
  mpLabelEA->hide();
  mpExpressionEA->hide();

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

  enableBtnCommit();
}

/*! Slot to enable the Commit button if the mathematical expression of Trigger is valid */
void CQEventWidget1::slotExpressionTriggerValid(bool valid)
{
  std::cout << "CQEW1::slotExpressionTriggerValid - valid = " << valid << std::endl;

  if (mpExpressionTrigger->mpExpressionWidget->getExpression() == "")
    mpExpressionTrigger->mpBtnViewExpression->setEnabled(false);

  mExpressionTriggerValid = mpExpressionTrigger->mpBtnViewExpression->isEnabled();

  enableBtnCommit();
}

/*! Slot to enable the Commit button if the mathematical expression of EventAssignment is valid */
void CQEventWidget1::slotExpressionEAValid(bool valid)
{
  std::cout << "CQEW1::slotExpressionEAValid - valid = " << valid << std::endl;

  if (mpExpressionEA->mpExpressionWidget->getExpression() == "")
    mpExpressionEA->mpBtnViewExpression->setEnabled(false);

  mExpressionEAValid = mpExpressionEA->mpBtnViewExpression->isEnabled();

  enableBtnCommit();
}

/*! Slot to add a new target without object target nor its expression
 *  Impact only on the appearance.
 */
void CQEventWidget1::slotAddTarget()
{
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
  mpBtnRevert->setEnabled(true);

  mObjectOK = false;

  // clear the widget of assignment expression
  mpExpressionEA->mpExpressionWidget->clear();

  // insert new item on the list box mpLBTarget and set it as the active one
  std::cout << "CQEW1::slotAddTarget - before #item = " << mpLBTarget->count() << std::endl;
  mpLBTarget->insertItem("No Object - Please select one"); // add to the last one
  mpLBTarget->setCurrentItem(mpLBTarget->count() - 1);  // set the last one as active
  std::cout << "CQEW1::slotAddTarget - after #item = " << mpLBTarget->count() << std::endl;

  // ---- end of EA GUI layout ---
}

/*! Slot to remove the active target from the appearance
 * Impact only on the appearance.
 */
void CQEventWidget1::slotDeleteTarget()
{
  // disable delete buttons until the newly deleted assignment is saved
  mpBtnDeleteTarget->setEnabled(false);

  mpBtnSelectObject->setEnabled(true);
  mpBtnRevert->setEnabled(true);

  // remove item from combo box Target
  std::cout << "CQEW1::slotDeleteTarget - before #item = " << mpLBTarget->count() << std::endl;
  std::cout << "mpCBTarget->currentItem() = " << mpLBTarget->currentItem() << " will be deleted!!" << std::endl;
  std::cout << "correlated name = " << mpLBTarget->currentText() << std::endl;
  std::cout << "correlated expression on the widget = " << mpExpressionEA->mpExpressionWidget->getExpression() << std::endl;

  // save the position of deleting assignment
  unsigned C_INT32 posDelete = mpLBTarget->currentItem();

  std::string text = takeObjectName(mpLBTarget->currentText());

  if (text != "")
    {
      // check the deleted position on the event object
      // mPosDelete will be used in deleting assignment
      mPosDelete = mpEvent->getAssignmentIndex(getAssignmentKeyFromDisplayName(text));
      std::cout << "mPosDelete = " << mPosDelete << std::endl;
      mObjectKeyDisplayName.erase(mObjectKeyDisplayName.begin() + mPosDelete);
    }
  else
    mPosDelete = (unsigned C_INT32) - 1;

  std::cout << __FILE__ << " L" << __LINE__ << " - mPosDelete = " << mPosDelete << " - posDelete = " << posDelete << std::endl;

  // delete the highlighted item from appearance
  std::cout << "mpLBTarget->count() = " << mpLBTarget->count() << std::endl;

  mpLBTarget->removeItem(posDelete);

  std::cout << "mpLBTarget->count() = " << mpLBTarget->count() << std::endl;
  std::cout << "mObjectKeyDisplayName.size() = " << mObjectKeyDisplayName.size() << std::endl;
  std::cout << "current: mpLBTarget->currentItem() = " << mpLBTarget->currentItem() << std::endl;

  if (!mpLBTarget->count())  // the last item has been removed -> no target more on the combo box
    {
      // hide the label and widget wrt expression
      mpLabelEA->hide();
      mpExpressionEA->hide();

      mObjectOK = false;
      enableBtnCommit();

      mpBtnAddTarget->setEnabled(true);
      mpBtnSelectObject->setEnabled(false);
    }
  else // at least one target still exists on the combo box
    {
      bool containNoObject = false;

      unsigned int idxTarget = 0;
      for (; idxTarget < mpLBTarget->count(); idxTarget++)
        {
          if (mpLBTarget->text(idxTarget).contains("No Object"))
            {
              containNoObject = true;
              continue;
            }
        }

      std::cout << "mpCBTarget->currentItem() = " << mpLBTarget->currentItem() << std::endl;

      if (containNoObject)
        {
          mpBtnAddTarget->setEnabled(false);

          mObjectOK = false;
          enableBtnCommit();
        }
      else
        {
          // actualize the expression widget to the next one since the assignment is not really deleted from event
          int pos = mpEvent->getAssignmentIndex(getAssignmentKeyFromDisplayName(takeObjectName(mpLBTarget->currentText())));
          slotActualizeAssignmentExpression(pos);

          mpBtnAddTarget->setEnabled(true);

          mObjectOK = true;
          enableBtnCommit();
        }
    }

  std::cout << "CQEW1::slotDeleteTarget - after #item = " << mpLBTarget->count() << std::endl;

  std::cout << "mPosDelete = " << mPosDelete << std::endl;
}

/// Slot to save the active target by creating really the assignment
void CQEventWidget1::slotSaveTarget()
{
  //  std::cout << "CQEW1::slotSaveTarget - mEventKey = " << mEventKey << std::endl;
  std::cout << std::endl << "CQEW1::slotSaveTarget ... START" << std::endl;

  QString msg;

  // check existency of the object
  if (mpLBTarget->currentText().contains("No Object"))
    {
      msg = "No object is selected as shown on Assignment Target list box.\nPlease select one object first.\n";

      CQMessageBox::critical(this, "Unable to save target without object", msg,
                             QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
      return;
    }

  // check existency of the expression
  if (mpExpressionEA->mpExpressionWidget->getExpression() == "")
    {
      msg = "XXX - There is no expression defined on Assignment Expression widget.\nPlease fill the widget first.\n";

      CQMessageBox::critical(this, "Unable to save target without expression", msg,
                             QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
      return;
    }

  // name of the target
  std::string assignKey = mAssignmentKey;
  std::cout << "assignKey = " << assignKey << std::endl;
  std::cout << "pEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;
  std::cout << "mpExpressionEA->mpExpressionWidget->getExpression() = "
  << mpExpressionEA->mpExpressionWidget->getExpression() << std::endl;

  mpEvent->addAssignment(assignKey, mpExpressionEA->mpExpressionWidget->getExpression());

  std::cout << "mpExpressionEA->mpExpressionWidget->getExpression() = "
  << mpExpressionEA->mpExpressionWidget->getExpression() << std::endl;

  // ----- correlated to GUI layout of the event assignment ----

  // enable neccessary buttons
  mpBtnAddTarget->setEnabled(true);
  mpBtnSelectObject->setEnabled(true);
  mpBtnDeleteTarget->setEnabled(true);

  // ---- end of EA GUI layout ---

  std::cout << "CQEW1::slotSaveTarget ... END" << std::endl << std::endl;
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

  if (expr.empty())
    mpExpressionTrigger->mpBtnViewExpression->setEnabled(false);

  mpExpressionTrigger->updateWidget();    // bring into view mode

  // *** Expression of Delay
  expr = "";
  if (mpEvent->getDelayExpressionPtr() != NULL)
    {
      expr = mpEvent->getDelayExpressionPtr()->getInfix();
    }

  mpExpressionDelay->mpExpressionWidget->setExpression(expr);
  std::cout << "EXP of Delay: " << expr << std::endl;

  if (expr.empty())
    mpExpressionDelay->mpExpressionWidget->setExpression("0");

  mpExpressionDelay->updateWidget();    // bring into view mode

  if (expr.empty() || expr == "0")
    {
      mpCheckBoxDelay->setChecked(false);
      slotApplyDelay(false);
    }
  else
    {
      mpCheckBoxDelay->setChecked(true);
      slotApplyDelay(true);
    }

  // TODO: *** Expression of EventAssignment ***

  mPosDelete = -1; // by default -> means: no item will be deleted

  std::cout << "AA -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;

  // copy assignment from event
  std::vector<std::pair<std::string, CExpression*> > currentAssignment;
  currentAssignment.reserve(100);
  currentAssignment = mpEvent->getAssignmentExpressionVector();

  std::cout << "CC -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments()
  << " -vs- currentAssignment.size() = " << currentAssignment.size() << std::endl;

  mpEvent->showAssignments();

  // (re-)create mObjectKeyDisplayName
  std::vector<std::pair<std::string, CExpression*> >::iterator it;

  mObjectKeyDisplayName.resize(0);
  int ijk = 0;
  for (it = currentAssignment.begin(); it != currentAssignment.end(); ++it, ijk++)
    {
      QStringList sKeyDisplay = QStringList::split("_", FROM_UTF8(it->first));
      QString sObjectName = sKeyDisplay[0];
      QString sObjectIndex = sKeyDisplay[1];
      QString sName;
      std::cout << "it->first = " << it->first << std::endl;
      std::cout << sObjectName << " - " << sObjectIndex << std::endl;

      if (sObjectName == "Compartment")
        {
          sName = FROM_UTF8(GlobalKeys.get(it->first)->getObjectDisplayName() + ".Volume");
          std::cout << "Compartments: " << sName << std::endl;
        }
      if (sObjectName == "Metabolite")
        {
          sName = FROM_UTF8("[" + GlobalKeys.get(it->first)->getObjectDisplayName() + "]");
          std::cout << "Metabolites: " << sName << std::endl;
        }
      if (sObjectName.contains("ModelValue"))
        {
          sName = FROM_UTF8(GlobalKeys.get(it->first)->getObjectDisplayName());
          std::cout << "Global Quantities: " << sName << std::endl;
        }

      mObjectKeyDisplayName.push_back(std::pair<std::string, std::string>(it->first, sName.latin1()));
    }

  std::vector<std::pair<std::string, std::string> >::iterator itA = mObjectKeyDisplayName.begin();
  std::cout << "Key - Display Name" << std::endl;
  for (; itA != mObjectKeyDisplayName.end(); ++itA)
    std::cout << itA->first << " - " << itA->second << std::endl;

  std::cout << "Assignment" << std::endl;
  mpEvent->showAssignments();

  // fill the list box and the expression widget with correct assignments
  mpLBTarget->clear();

  unsigned C_INT32 idx = 0;
  for (it = currentAssignment.begin(); it != currentAssignment.end(); ++it)
    {
      mpLBTarget->insertItem(FROM_UTF8("<" + mObjectKeyDisplayName[idx].second + ">")); // the list box
      mpExpressionEA->mpExpressionWidget->setExpression(mpEvent->getAssignmentExpressionPtr(idx)->getInfix()); // the expression widget
      idx++;
    }

  std::cout << __LINE__ << " mpLBTarget->count() = " << mpLBTarget->count() << std::endl;
  // if not empty, set to the first entry
  if (mpLBTarget->count())
    {
      mObjectOK = true; // at least one object target exists
      mpBtnDeleteTarget->setEnabled(true);
      mpBtnSelectObject->setEnabled(true);

      mpLBTarget->setCurrentItem(mpLBTarget->count() - 1);
      slotActualizeAssignmentExpression(mpLBTarget->count() - 1);
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

  // disable commit button -> re-activate the button whenever there is something new on the event
  mpBtnCommit->setEnabled(false);
  mpBtnAddTarget->setEnabled(true);

  mpBtnRevert->setEnabled(false);

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

          QMessageBox::information(this, "Unable to rename Event", msg,
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
  if (mpExpressionDelay->mpExpressionWidget->getExpression() == "")
    mpExpressionDelay->mpExpressionWidget->setExpression("0");

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

  std::cout << "L" << __LINE__ << " A mpLBTarget->count() = " << mpLBTarget->count()
  << " -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;
  std::cout << "mPosDelete = " << mPosDelete << std::endl;

  bool success = true;

  mpEvent->showAssignments();

  // first of all, permanently remove the deleted assignment
  if (mPosDelete != (unsigned C_INT32) - 1)
    mpEvent->deleteAssignment(mPosDelete);

  std::cout << "L" << __LINE__ << " B mpLBTarget->count() = " << mpLBTarget->count()
  << " -vs- mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;

  mpEvent->showAssignments();

  // if new/modify assignment exists then the current position must be on it; otherwise, the expression cannot be saved
  int newPosition = -1;
  std::string newKey = "";
  std::string newExpression = "";

  if (mpLBTarget->count() != mObjectKeyDisplayName.size())
    {
      std::cout << "mpLBTarget->count() = " << mpLBTarget->count() << " - mObjectKeyDisplayName.size() = "
      << mObjectKeyDisplayName.size() << std::endl;
      std::cout << "Abort on L" << __LINE__ << std::endl;
    }

  if (mpLBTarget->count() > mpEvent->getNumAssignments())
    {
      newPosition = mpLBTarget->currentItem();
      newKey = mObjectKeyDisplayName[newPosition].first;
      newExpression = mpExpressionEA->mpExpressionWidget->getExpression();
    }

  std::cout << "New position: " << newPosition << " - key: " << newKey << " - expression: " << newExpression << std::endl;

  int modPosition = -1;
  std::string modExpression = "";

  if (mpLBTarget->count())
    {
      modPosition = mpLBTarget->currentItem();
      modExpression = mpExpressionEA->mpExpressionWidget->getExpression();
    }

  std::cout << "Mod position: " << modPosition << " - expression: " << modExpression << std::endl;

  int i;
  for (i = 0; i < (int) mpLBTarget->count(); i++)
    {
      if (i == newPosition)
        {
          // new assignment exists
          std::cout << "i: " << i << " --> new key " << newKey << " - new expression " << newExpression << std::endl;
          success = mpEvent->addAssignment(newKey, newExpression);
        }
      else
        {
          // modified assignment may exist
          mpLBTarget->setCurrentItem(i);
          slotActualizeAssignmentExpression(i);

          std::string assignKey = mObjectKeyDisplayName[i].first;
          std::string assignExpression = "";

          if (i == modPosition)
            assignExpression = modExpression;
          else
            assignExpression = mpExpressionEA->mpExpressionWidget->getExpression();

          std::cout << "i: " << i << " --> assignKey = " << assignKey << " - assignExpression = " << assignExpression << std::endl;

          success = mpEvent->updateAssignment(mpLBTarget->currentItem(), assignKey, assignExpression);
        }
    }

  if (!success)
    {
      QString msg;
      msg = "The current assignment fails to be saved";

      QMessageBox::critical(this, "Fail to Save Current Assignment", msg,
                            QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
      return;
    }

  mChanged = true;

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
bool CQEventWidget1::update(ListViews::ObjectType /* objectType */, ListViews::Action /* action */, const std::string & /* key */)
{
  return true;
}

/*! Function to interact with an object of class CEvent */
bool CQEventWidget1::enter(const std::string & key)
{
  std::cout << "CQEW1::enter - key = " << key << std::endl;
  mEventKey = key;
  mpEvent = dynamic_cast< CEvent * >(GlobalKeys.get(key));

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
  std::cout << "CQEW1::leave" << std::endl;

  if (mpBtnCommit->isEnabled())
    {
      mpExpressionTrigger->updateWidget();

      if (mpCheckBoxDelay->isChecked())
        mpExpressionDelay->updateWidget();

      saveToEvent();
      //  mObjectKeyDisplayName.resize(0);

      // enable/disable buttons
      mpBtnAddTarget->setEnabled(true);
      mpBtnCommit->setEnabled(false);
      mpBtnRevert->setEnabled(false);

      if (mpLBTarget->count()) // not empty
        mpBtnDeleteTarget->setEnabled(true);
      else      // empty
        mpBtnDeleteTarget->setEnabled(false);
    }

  return true;
}

/// Slot to select an object from the existing ones
void CQEventWidget1::slotSelectObject()
{
  CCopasiSimpleSelectionTree::SelectionFlag mExpressionType = CCopasiSimpleSelectionTree::TRANSIENT_EXPRESSION;

  QString oldText = mpLBTarget->currentText();
  QString newText = mpLBTarget->currentText();

  std::cout << "CQEW1::slotSelectObject" << std::endl;

  std::cout << "mpLBTarget->currentItem() = " << mpLBTarget->currentItem() << std::endl;

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

      // We need to escape >
      std::string::size_type pos = Insert.find_first_of("\\>");
      while (pos != std::string::npos)
        {
          Insert.insert(pos, "\\");
          pos += 2;
          pos = Insert.find_first_of("\\>", pos);
        }

      std::cout << "Insert object AFTER = " << Insert << std::endl;

      newText = FROM_UTF8("<" + Insert + ">");
      std::cout << "newText = " << newText << std::endl;

      // check duplicacy -> as single event cannot have multiple EventAssignment !!!
      //      bool duplicacy = false;
      unsigned int i;
      for (i = 0; i < mpLBTarget->count(); i++)
        {
          if (mpLBTarget->text(i) == newText)
            {
              QString msg = "A single event cannot have multiple EventAssignment assigning the same object.";
              msg += "\nThe selected object " + newText + ", however, has been listed on Target list box.";
              msg += "\nPlease select another object.\n";

              CQMessageBox::critical(this, "Unable to save target with duplicate object", msg,
                                     QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
              return;
            }
        }

      std::cout << FROM_UTF8("<" + Insert + ">") << std::endl;

      // the following call automatically slotActualizeAssignmentExpression
      std::cout << "mpLBTarget->currentItem() = " << mpLBTarget->currentItem() << std::endl;
      mpLBTarget->changeItem(FROM_UTF8("<" + Insert + ">"), mpLBTarget->currentItem());

      std::vector<std::pair<std::string, std::string> >::iterator it = mObjectKeyDisplayName.begin();
      std::cout << "B E F O R E" << std::endl;
      for (; it != mObjectKeyDisplayName.end(); ++it)
        std::cout << it->first << " - " << it->second << std::endl;

      mAssignmentKey = pObject->getObjectParent()->getKey();

      // as index starts from 0
      unsigned int index = mpLBTarget->currentItem();
      if (index + 1 > mObjectKeyDisplayName.size()) // new assignment target
        mObjectKeyDisplayName.push_back(std::make_pair(mAssignmentKey, Insert));
      else // target name is changed
        {
          mObjectKeyDisplayName[index].first = mAssignmentKey;
          mObjectKeyDisplayName[index].second = Insert;
        }

      std::cout << "A F T E R" << std::endl;
      for (it = mObjectKeyDisplayName.begin(); it != mObjectKeyDisplayName.end(); ++it)
        std::cout << it->first << " - " << it->second << std::endl;

      // show the label and widget wrt expression
      mpLabelEA->show();
      mpExpressionEA->show();

      // in case user replace other object target instead of one with 'No Object' text, which remains still.
      bool containNoObject = false;
      unsigned int j;
      for (j = 0; j < mpLBTarget->count(); j++)
        {
          if (mpLBTarget->text(j).contains("No Object"))
            {
              containNoObject = true;
              continue;
            }
        }

      // save object if neccessary

      if (newText != oldText && !containNoObject)
        {
          mObjectOK = true;
          enableBtnCommit();
        }

      // just a trick -> the following call automatically slotActualizeAssignmentExpression
      std::cout << "mpLBTarget->currentItem() = " << mpLBTarget->currentItem() << std::endl;
      mpLBTarget->changeItem(mpLBTarget->currentText(), mpLBTarget->currentItem());
    }
}

/// Slot to actualize the assignment expression widget of event assignment according to the target
void CQEventWidget1::slotActualizeAssignmentExpression(int index)
{
  std::cout << "CQEW1::slotActualizeAssignmentExpression - index = " << index << std::endl;

  std::cout << "mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;
  if (!mpEvent->getNumAssignments()) return; // no assignment

  if (index == -1) // no target anymore
    {
      mpLBTarget->clear();

      // hide the label and widget wrt expression
      mpLabelEA->show();
      mpExpressionEA->show();

      return;
    }

  if (index >= (int) mpEvent->getNumAssignments()) // ">=" since index 0 represents the first event assignment
    {
      std::cout << "index = " << index << " > mpEvent->getNumAssignments() = " << mpEvent->getNumAssignments() << std::endl;

      QString msg;

      mpExpressionEA->mpExpressionWidget->clear();

      // no object is selected
      if (mpLBTarget->currentText().contains("No Object"))
        {
          // hide the label and widget wrt expression
          mpLabelEA->hide();
          mpExpressionEA->hide();

          return;
        }

      // check existency of the expression
      if (mpExpressionEA->mpExpressionWidget->getExpression() == "")
        {
          /*   msg = "There is no expression defined on Assignment Expression widget.\nPlease fill the widget first.\n";

                CQMessageBox::critical(this, "Unable to save target without expression", msg,
                                       QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);
          */
          mpExpressionEA->updateWidget();
          return;
        }

      // never happens with new structure -> it will be deleted (15.05.08)
      msg = "The currently active event assignment is not saved.\nPlease save it first.\n";

      CQMessageBox::critical(this, "Unsaved current active event assignment", msg,
                             QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);

      return;
    }

  std::cout << "expression = " << mpEvent->getAssignmentExpressionStr(index) << std::endl;

  // show the label and widget wrt expression
  mpLabelEA->show();
  mpExpressionEA->show();

  // update expression widget wrt a chosen target
  std::string text = "";
  std::string objName = takeObjectName(mpLBTarget->currentText());

  unsigned int jk;
  for (jk = 0; jk < mObjectKeyDisplayName.size(); jk++)
    std::cout << "Key = " << mObjectKeyDisplayName[jk].first << " - Display Name = " << mObjectKeyDisplayName[jk].second << std::endl;

  for (jk = 0; jk < mpEvent->getNumAssignments(); jk++)
    std::cout << "Key = " << mpEvent->getAssignmentObjectKey(jk) << " - Expression = " << mpEvent->getAssignmentExpressionStr(jk) << std::endl;

  unsigned C_INT32 indexPos = mpEvent->getAssignmentIndex(getAssignmentKeyFromDisplayName(objName));

  if (indexPos != (unsigned C_INT32) - 1)
    text = mpEvent->getAssignmentExpressionStr(indexPos);

  mpExpressionEA->mpExpressionWidget->clear();

  if (!mpLBTarget->currentText().contains("No Object"))
    {
      mpExpressionEA->mpExpressionWidget->setExpression(text);
      mpExpressionEA->updateWidget();
    }
}

/*! Function to check whether all expressions (trigger, delay, assignment(s)) is OK
 *  \brief Current scenario: ONLY ONE new assignment is allowed to be exist at a time.
 *  Thus, 1) its index is the last; 2) it must currently be highlighted, otherwise its expression could not be saved.
 *  If one deletes the expression of one saved target, and highlights other targets without saving the modification,
 *  then the modification will be ignored. The modification itself cannot be saved unless a new expression is given.
 */
bool CQEventWidget1::checkAllExpressionsOK()
{
  /*  bool expressionEAValid = mExpressionEAValid; // capture the boolean value from current item

    std::cout << std::endl;
    std::cout << "mExpressionTriggerValid = " << mExpressionTriggerValid
    << " - mExpressionDelayValid = " << mExpressionDelayValid
    << " -> (mExpressionTriggerValid && mExpressionDelayValid) = " << (mExpressionTriggerValid && mExpressionDelayValid) << std::endl;
    std::cout << " - mExpressionEAValid = " << mExpressionEAValid << std::endl;

    std::vector<std::pair<std::string, CExpression *> >::iterator itA = mAssignsExpression.begin();
    std::vector<std::pair<std::string, std::string> >::iterator itB;
  */
  std::cout << "mpLBTarget->count() = " << mpLBTarget->count() << " - mpEvent->getNumAssignments() = "
  << mpEvent->getNumAssignments() << std::endl;

  if (mpLBTarget->count() == mpEvent->getNumAssignments()) // no new assignment exists
    return mExpressionEAValid;

  if (mpLBTarget->currentItem() == int(mpLBTarget->count()) - 1)  // check whether the last assignment target
    return mExpressionEAValid;
  else
    return false;

  /*
    if (mpLBTarget->count() && mExpressionEAValid)
      {
        unsigned int index = mpLBTarget->currentItem();

        if (index + 1 != mpLBTarget->count())  // the current highlighted item is not the last one
          {
            mpLBTarget->setCurrentItem(mpLBTarget->count() - 1); // set to the last one
            expressionEAValid = mExpressionEAValid;    // capture the boolean value from the last one
            mpLBTarget->setCurrentItem(index);     // set back to the previous item
          }
      }

    return ((mExpressionTriggerValid && mExpressionDelayValid) && expressionEAValid);
  */
}

/*! Function to enable/disable the button Commit */
void CQEventWidget1::enableBtnCommit()
{
  std::cout << "CQEW1::enableBtnCommit" << std::endl;

  bool bExpressionsOK = checkAllExpressionsOK();
  bool bObjectAndExpressionsOK = (mObjectOK && bExpressionsOK);

  std::cout << "mExpressionTriggerValid = " << mExpressionTriggerValid
  << " - mExpressionDelayValid = " << mExpressionDelayValid
  << " -> (mExpressionTriggerValid && mExpressionDelayValid) = " << (mExpressionTriggerValid && mExpressionDelayValid)
  << " - mObjectOK = " << mObjectOK
  << " - bExpressionsOK = " << bExpressionsOK
  << " -> bObjectAndExpressionsOK = " << bObjectAndExpressionsOK
  << " - mExpressionEAValid = " << mExpressionEAValid
  << " -> (bObjectAndExpressionsOK && mExpressionEAValid) = "
  << (bObjectAndExpressionsOK && mExpressionEAValid)
  << " ==> mpBtnCommit is enabled ? "
  << ((bObjectAndExpressionsOK && mExpressionEAValid) && (mExpressionTriggerValid && mExpressionDelayValid)) << std::endl;

  if ((bObjectAndExpressionsOK && mExpressionEAValid) && (mExpressionTriggerValid && mExpressionDelayValid))
    mpBtnCommit->setEnabled(true);
  else
    mpBtnCommit->setEnabled(false);

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

/*! Slot to apply the Delay Expression Widget */
void CQEventWidget1::slotApplyDelay(bool display)
{
  if (display)
    {
      mpLabelDelay->show();
      mpExpressionDelay->show();
    }
  else
    {
      mpLabelDelay->hide();
      mpExpressionDelay->hide();
    }
}

/*! Function to get the Assignment Key from the Display Name */
std::string CQEventWidget1::getAssignmentKeyFromDisplayName(const std::string displayName)
{
  std::vector<std::pair<std::string, std::string> >::iterator itA = mObjectKeyDisplayName.begin();
  for (; itA != mObjectKeyDisplayName.end(); ++itA)
    {
      if (displayName == itA->second) {return itA->first;}
    }
  return "";
}
