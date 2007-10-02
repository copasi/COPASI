// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.ui.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/10/02 18:18:01 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include "model/CMetab.h"
#include "model/CCompartment.h"
#include "model/CChemEqInterface.h"
#include "function/CExpression.h"
#include "report/CKeyFactory.h"

void CQMetabolite::init()
{
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::REACTIONS]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::REACTIONS);
  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);

  mpReactionTable->header()->hide();

  // :TODO: Enable this for initial expressions
  mpComboBoxInitialType->hide();
  mpComboBoxInitialSelection->hide();

  mInitialNumberLastChanged = true;
  mShowConcentration = true;
}

void CQMetabolite::slotBtnCommit()
{
  mpBtnCommit->setFocus();
  save();
  load();
}

void CQMetabolite::slotBtnRevert()
{
  load();
}

void CQMetabolite::slotBtnNew()
{
  save();

  if (CCopasiDataModel::Global->getModel()->getCompartments().size() == 0)
    CCopasiDataModel::Global->getModel()->createCompartment("compartment");

  std::string name = "metabolite";
  int i = 0;

  while (!(mpMetab = CCopasiDataModel::Global->getModel()->createMetabolite(name, "", 1.0, CModelEntity::REACTIONS)))
    {
      i++;
      name = "metabolite_";
      name += (const char *)QString::number(i).utf8();
    }

  enter(mpMetab->getKey());
  protectedNotify(ListViews::METABOLITE, ListViews::ADD);
}

void CQMetabolite::slotBtnDelete()
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL) return;

  if (mpMetab == NULL) return;

  QString metaboliteList = "Are you sure you want to delete listed METABOLITE(S) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above METABOLITE(S) and will be deleted -\n";
  QString effectedMetabList = "Following METABOLITE(S) reference above METABOLITE(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above METABOLITE(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above METABOLITE(S) and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  metaboliteList.append(FROM_UTF8(mpMetab->getObjectName()));
  metaboliteList.append(", ");

  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;

  pModel->appendDependentModelObjects(mpMetab->getDeletedObjects(),
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
      effectedReacList.append(FROM_UTF8(mpMetab->getObjectName()));
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
      effectedMetabList.append(FROM_UTF8(mpMetab->getObjectName()));
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
      effectedValueList.append(FROM_UTF8(mpMetab->getObjectName()));
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
      effectedCompartmentList.append(FROM_UTF8(mpMetab->getObjectName()));
      effectedCompartmentList.append("\n");
    }

  metaboliteList.remove(metaboliteList.length() - 2, 2);

  QString msg = metaboliteList;

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
        unsigned C_INT32 index =
          CCopasiDataModel::Global->getModel()->getMetabolites().getIndex(GlobalKeys.get(mKey));

        CCopasiDataModel::Global->getModel()->removeMetabolite(mKey);

        unsigned C_INT32 size =
          CCopasiDataModel::Global->getModel()->getMetabolites().size();

        if (size > 0)
          enter(CCopasiDataModel::Global->getModel()->getMetabolites()[std::min(index, size - 1)]->getKey());
        else
          enter("");

#undef DELETE
        protectedNotify(ListViews::METABOLITE, ListViews::DELETE, mKey);
        //TODO notify about reactions
        break;
      }
    default:                                                     // No or Escape
      break;
    }
}

void CQMetabolite::slotCompartmentChanged(int compartment)
{
  if (!mpMetab || !mpCurrentCompartment) return;

  QString Compartment = mpComboBoxCompartment->text(compartment);
  const CCompartment * pNewCompartment =
    CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)Compartment.utf8()];

  if (pNewCompartment == mpCurrentCompartment ||
      pNewCompartment == NULL) return;

  mInitialNumber *= pNewCompartment->getInitialValue() / mpCurrentCompartment->getInitialValue();

  if (!mShowConcentration)
    mpEditInitialValue->setText(QString::number(mInitialNumber, 'g', 10));

  mpCurrentCompartment = pNewCompartment;
}

void CQMetabolite::slotTypeChanged(int type)
{
  switch ((CModelEntity::Status) mItemToType[type])
    {
    case CModelEntity::FIXED:
      mpLblExpression->hide();
      mpEditExpression->hide();
      mpBtnObject->hide();

      mpEditInitialValue->setEnabled(true);
      break;

    case CModelEntity::ASSIGNMENT:
      mpLblExpression->show();
      mpEditExpression->show();
      mpBtnObject->show();

      mpEditInitialValue->setEnabled(false);

      mpEditExpression->setExpression(mpMetab->getExpression());
      break;

    case CModelEntity::ODE:
      mpLblExpression->show();
      mpEditExpression->show();
      mpBtnObject->show();

      mpEditInitialValue->setEnabled(true);

      mpEditExpression->setExpression(mpMetab->getExpression());
      break;

    case CModelEntity::REACTIONS:
      mpLblExpression->hide();
      mpEditExpression->hide();
      mpBtnObject->hide();

      mpEditInitialValue->setEnabled(true);
      break;

    default:
      break;
    }
}

void CQMetabolite::slotInitialTypeChanged(int /* initialType */)
{
  // :TODO: Enable this for initial expressions
}

void CQMetabolite::slotInitialAssignment(int /* initialAssignment */)
{
  // :TODO: Enable this for initial expressions
}

void CQMetabolite::slotNameLostFocus()
{
  if (mpEditName->text() != FROM_UTF8(mpMetab->getObjectName()))
    mpEditExpression->currentObjectRenamed(mpMetab, mpEditName->text());
}

void CQMetabolite::slotExpressionValid(bool valid)
{
  mpBtnCommit->setEnabled(valid);
}

bool CQMetabolite::enter(const std::string & key)
{
  mKey = key;
  mpMetab = dynamic_cast< CMetab * >(GlobalKeys.get(key));

  if (!mpMetab)
    {
      pListView->switchToOtherWidget(112, "");
      return false;
    }

  load();
  return true;
}

bool CQMetabolite::leave()
{
  if (mpBtnCommit->isEnabled())
    save();

  return true;
}

bool CQMetabolite::update(ListViews::ObjectType objectType,
                          ListViews::Action /* action */,
                          const std::string & /* key */)
{
  if (!isVisible() || mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::STATE:
    case ListViews::MODEL:
    case ListViews::METABOLITE:
    case ListViews::COMPARTMENT:
      load();
      break;

    default:
      break;
    }
  return true;
}

void CQMetabolite::load()
{
  if (mpMetab == NULL) return;

  // Update the labels to reflect the model units
  mpLblTransitionTime->setText("Transition Time (" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnitName()) + ")");

  // Name
  mpEditName->setText(FROM_UTF8(mpMetab->getObjectName()));

  // Compartment
  CCopasiVectorNS< CCompartment > & Compartments = CCopasiDataModel::Global->getModel()->getCompartments();
  CCompartment * pCompartment;
  mpComboBoxCompartment->clear();

  mpComboBoxCompartment->setDuplicatesEnabled (false);
  unsigned C_INT32 m;
  for (m = 0; m < Compartments.size(); m++)
    {
      pCompartment = Compartments[m];
      //mpComboBoxCompartment->insertStringList(pCompartment->getObjectName().,j);
      mpComboBoxCompartment->insertItem(FROM_UTF8(pCompartment->getObjectName()));
    }

  mpCurrentCompartment = mpMetab->getCompartment();
  mpComboBoxCompartment->setCurrentText(FROM_UTF8(mpCurrentCompartment->getObjectName()));

  // Simulation Type
  mpComboBoxType->setCurrentText(FROM_UTF8(CModelEntity::StatusName[mpMetab->getStatus()]));

  // Initial Concentration handled in slotTypeChanged
  mInitialConcentration = mpMetab->getInitialConcentration();

  // Initial Number handled in slotTypeChanged
  mInitialNumber = mpMetab->getInitialValue();

  mInitialNumberLastChanged = true;

  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentItem());

  // Transistion Time
  mpEditTransitionTime->setText(QString::number(mpMetab->getTransitionTime()));

  // Expression
  mpEditExpression->setExpression(mpMetab->getExpression());

  loadReactionTable();

  // Update the units and values accordingly
  mShowConcentration = !mShowConcentration;
  slotToggleDisplay();

  mChanged = false;
  return;
}

void CQMetabolite::save()
{
  if (mpMetab == NULL) return;

  // Name
  if (mpMetab->getObjectName() != (const char *) mpEditName->text().utf8())
    {
      if (!mpMetab->setObjectName((const char *) mpEditName->text().utf8()))
        {
          QString msg;
          msg = "Unable to rename metabolite '" + FROM_UTF8(mpMetab->getObjectName()) + "'\n"
                + "to '" + mpEditName->text() + "' since a metabolites with that name already exists.\n";

          CQMessageBox::information(this,
                                    "Unable to rename Metabolite",
                                    msg,
                                    QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);

          mpEditName->setText(FROM_UTF8(mpMetab->getObjectName()));
        }
      else
        {
          protectedNotify(ListViews::METABOLITE, ListViews::RENAME, mKey);
          mChanged = true;
        }
    }

  // Compartment
  if (mpCurrentCompartment != mpMetab->getCompartment())
    {
      QString Compartment = mpComboBoxCompartment->currentText();
      std::string CompartmentToRemove = mpMetab->getCompartment()->getObjectName();

      if (!CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)Compartment.utf8()]->addMetabolite(mpMetab))
        {
          QString msg;
          msg = "Unable to move metabolite '" + FROM_UTF8(mpMetab->getObjectName()) + "'\n"
                + "from compartment '" + FROM_UTF8(CompartmentToRemove) + "' to compartment '" + Compartment + "'\n"
                + "since a metabolite with that name already exist in the target compartment.";

          CQMessageBox::information(this,
                                    "Unable to move Metabolite",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);

          // Revert the changes
          mpComboBoxCompartment->setCurrentText(FROM_UTF8(CompartmentToRemove));
          slotCompartmentChanged(mpComboBoxCompartment->currentItem());
        }
      else
        {
          CCopasiDataModel::Global->getModel()->getCompartments()[CompartmentToRemove]->getMetabolites().remove(mpMetab->getObjectName());
          CCopasiDataModel::Global->getModel()->setCompileFlag();
          CCopasiDataModel::Global->getModel()->initializeMetabolites();
          protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, "");
          mChanged = true;
        }
    }

  // Type
  if (mpMetab->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()])
    {
      mpMetab->setStatus((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()]);
      mChanged = true;
    }

  // Initial Concentration and Initial Number
  if (mInitialNumberLastChanged)
    {
      if (mpMetab->getInitialValue() != mInitialNumber)
        {
          mpMetab->setInitialValue(mInitialNumber);
          mChanged = true;
        }
    }
  else
    {
      mpMetab->setInitialConcentration(mInitialConcentration);
      mChanged = true;
    }

  // Expression
  if (mpMetab->getExpression() != mpEditExpression->getExpression())
    {
      mpMetab->setExpression(mpEditExpression->getExpression());
      mChanged = true;
    }

  if (mChanged)
    {
      CCopasiDataModel::Global->changed();
      protectedNotify(ListViews::METABOLITE, ListViews::CHANGE, mKey);
    }

  mChanged = false;
}

void CQMetabolite::destroy()
{}

void CQMetabolite::slotReactionTableCurrentChanged(QListViewItem * pItem)
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL) return;

  if (mpMetab == NULL) return;

  std::set< const CCopasiObject * > Reactions;
  pModel->appendDependentReactions(mpMetab->getDeletedObjects(), Reactions);

  std::string s1, s2;
  s1 = pItem->text(0).utf8();
  s1 = s1.substr(0, s1.length() - 2);

  C_INT32 i = 0;
  std::set< const CCopasiObject * >::const_iterator it = Reactions.begin();
  std::set< const CCopasiObject * >::const_iterator end = Reactions.end();
  const CReaction * pReaction;

  for (; it != end; ++it, ++i)
    {
      pReaction = static_cast< const CReaction * >(*it);
      s2 = pReaction->getObjectName();

      if (s1 == s2)
        pListView->switchToOtherWidget(0, pReaction->getKey());
    }
}

void CQMetabolite::slotInitialValueLostFocus()
{
  if (mShowConcentration)
    {
      if (QString::number(mInitialConcentration, 'g', 10) == mpEditInitialValue->text())
        return;

      if (!mpMetab || !mpCurrentCompartment) return;

      mInitialConcentration = mpEditInitialValue->text().toDouble();
      mInitialNumber = CMetab::convertToNumber(mInitialConcentration,
                       *mpCurrentCompartment,
                       *CCopasiDataModel::Global->getModel());

      mInitialNumberLastChanged = false;
    }
  else
    {
      if (QString::number(mInitialNumber, 'g', 10) == mpEditInitialValue->text())
        return;

      if (!mpMetab || !mpCurrentCompartment) return;

      mInitialNumber = mpEditInitialValue->text().toDouble();
      mInitialConcentration = CMetab::convertToConcentration(mInitialNumber,
                              *mpCurrentCompartment,
                              *CCopasiDataModel::Global->getModel());

      mInitialNumberLastChanged = true;
    }
}

void CQMetabolite::loadReactionTable()
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL) return;

  if (mpMetab == NULL) return;

  std::set< const CCopasiObject * > Reactions;
  pModel->appendDependentReactions(mpMetab->getDeletedObjects(), Reactions);

  mpReactionTable->clear();
  mpReactionTable->setColumnWidth(0, 10);
  mpReactionTable->setColumnWidth(1, 10);

  std::set< const CCopasiObject * >::const_iterator it = Reactions.begin();
  std::set< const CCopasiObject * >::const_iterator end = Reactions.end();
  C_INT32 i = 0;
  const CReaction * pReaction;

  for (; it != end; ++it, ++i)
    {
      pReaction = static_cast< const CReaction * >(*it);
      new QListViewItem(mpReactionTable,
                        FROM_UTF8(pReaction->getObjectName()) + ": ",
                        FROM_UTF8(CChemEqInterface::getChemEqString(CCopasiDataModel::Global->getModel(), *pReaction, false)));
    }

  if (i == 0)
    new QListViewItem(mpReactionTable, "none");

  return;
}

void CQMetabolite::slotToggleDisplay()
{
  mShowConcentration = !mShowConcentration;

  int Width = fontMetrics().width("Concentration (" +
                                  FROM_UTF8(CCopasiDataModel::Global->getModel()->getConcentrationUnitName()) +
                                  ")");
  mpLblValue->setMinimumWidth(Width);

  if (mShowConcentration)
    {
      // Update the labels to reflect the model units
      mpLblValue->setText("Concentration ("
                          + FROM_UTF8(CCopasiDataModel::Global->getModel()->getConcentrationUnitName()) + ")");

      mpLblRate->setText("Rate ("
                         + FROM_UTF8(CCopasiDataModel::Global->getModel()->getConcentrationRateUnitName()) + ")");

      mpEditInitialValue->setText(QString::number(mInitialConcentration, 'g', 10));
      mpEditCurrentValue->setText(QString::number(mpMetab->getConcentration()));
      mpEditRate->setText(QString::number(mpMetab->getConcentrationRate()));

      mpBtnToggle->setText("Particle Number");
    }
  else
    {
      // Update the labels to reflect the model units
      mpLblValue->setText("Particle Number");

      mpLblRate->setText("Rate (1/"
                         + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnitName()) + ")");

      mpEditInitialValue->setText(QString::number(mInitialNumber, 'g', 10));
      mpEditCurrentValue->setText(QString::number(mpMetab->getValue()));
      mpEditRate->setText(QString::number(mpMetab->getRate()));

      mpBtnToggle->setText("Concentration");
    }
}
