// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQCompartment.ui.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/01 17:51:00 $
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

void CQCompartment::init()
{
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);

  mpMetaboliteTable->header()->hide();

  // :TODO: Enable this for initial expressions
  mpComboBoxInitialType->hide();
  mpComboBoxInitialSelection->hide();
}

void CQCompartment::slotBtnCommit()
{
  save();
  load();
}

void CQCompartment::slotBtnRevert()
{
  load();
}

void CQCompartment::slotBtnNew()
{
  save();

  std::string name = "compartment";
  int i = 0;

  while (!(mpCompartment = CCopasiDataModel::Global->getModel()->createCompartment(name)))
    {
      i++;
      name = "compartment_";
      name += (const char *)QString::number(i).utf8();
    }

  enter(mpCompartment->getKey());
  protectedNotify(ListViews::METABOLITE, ListViews::ADD);
}

void CQCompartment::slotBtnDelete()
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL) return;

  if (mpCompartment == NULL) return;

  QString compartmentList = "Are you sure you want to delete listed COMPARTMENT(S) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedMetabList = "Following METABOLITE(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above COMPARTMENT(S) and will be deleted -\n";

  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  compartmentList.append(FROM_UTF8(mpCompartment->getObjectName()));
  compartmentList.append(", ");

  pModel->appendDependentModelObjects(mpCompartment->getDeletedObjects(),
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
      effectedReacList.append(FROM_UTF8(mpCompartment->getObjectName()));
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
      effectedMetabList.append(FROM_UTF8(mpCompartment->getObjectName()));
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
      effectedValueList.append(FROM_UTF8(mpCompartment->getObjectName()));
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
      effectedCompartmentList.append(FROM_UTF8(mpCompartment->getObjectName()));
      effectedCompartmentList.append("\n");
    }

  compartmentList.remove(compartmentList.length() - 2, 2);

  QString msg = compartmentList;

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
    case 0:                                 // Yes or Enter
      {
        unsigned C_INT32 Index =
          CCopasiDataModel::Global->getModel()->getCompartments().getIndex(mpCompartment->getObjectName());
        CCopasiDataModel::Global->getModel()->removeCompartment(mKey);

        unsigned C_INT32 Size =
          CCopasiDataModel::Global->getModel()->getCompartments().size();

        if (Size > 0)
          enter(CCopasiDataModel::Global->getModel()->getCompartments()[std::min(Index, Size - 1)]->getKey());
        else
          enter("");

        protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, mKey);

        //TODO notify about metabs and reactions
        break;
      }
    default:                                 // No or Escape
      break;
    }
}

void CQCompartment::slotTypeChanged(int type)
{
  switch ((CModelEntity::Status) mItemToType[type])
    {
    case CModelEntity::FIXED:
      mpLblExpression->hide();
      mpEditExpression->hide();
      mpBtnObject->hide();

      mpEditInitialVolume->setEnabled(true);
      break;

    case CModelEntity::ASSIGNMENT:
      mpLblExpression->show();
      mpEditExpression->show();
      mpBtnObject->show();

      mpEditInitialVolume->setEnabled(false);

      mpEditExpression->setExpression(mpCompartment->getExpression());
      break;

    case CModelEntity::ODE:
      mpLblExpression->show();
      mpEditExpression->show();
      mpBtnObject->show();

      mpEditInitialVolume->setEnabled(true);

      mpEditExpression->setExpression(mpCompartment->getExpression());
      break;

    default:
      break;
    }
}

void CQCompartment::slotInitialTypeChanged(int /* initialType */)
{
  // :TODO: Enable this for initial expressions
}

void CQCompartment::slotInitialAssignment(int /* initialAssignment */)
{
  // :TODO: Enable this for initial expressions
}

void CQCompartment::slotNameLostFocus()
{
  if (mpEditName->text() != FROM_UTF8(mpCompartment->getObjectName()))
    mpEditExpression->currentObjectRenamed(mpCompartment, mpEditName->text());
}

void CQCompartment::slotExpressionValid(bool valid)
{
  mpBtnCommit->setEnabled(valid);
}

bool CQCompartment::enter(const std::string & key)
{
  mKey = key;
  mpCompartment = dynamic_cast< CCompartment * >(GlobalKeys.get(key));

  if (!mpCompartment)
    {
      mpListView->switchToOtherWidget(111, "");
      return false;
    }

  load();
  return true;
}

bool CQCompartment::leave()
{
  if (mpBtnCommit->isEnabled())
    save();

  return true;
}

bool CQCompartment::update(ListViews::ObjectType objectType,
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

void CQCompartment::load()
{
  if (mpCompartment == NULL) return;

  // Update the labels to reflect the model units
  mpLblVolume->setText("Volume ("
                       + FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnitName()) + ")");

  mpLblRate->setText("Rate ("
                     + FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnitName())
                     + "/" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnitName()) + ")");

  // Name
  mpEditName->setText(FROM_UTF8(mpCompartment->getObjectName()));

  // Simulation Type
  mpComboBoxType->setCurrentText(FROM_UTF8(CModelEntity::StatusName[mpCompartment->getStatus()]));

  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentItem());

  // Initial Volume
  mpEditInitialVolume->setText(QString::number(mpCompartment->getInitialValue(), 'g', 10));

  // Transient Volume
  mpEditCurrentVolume->setText(QString::number(mpCompartment->getValue()));

  // Concentration Rate
  mpEditRate->setText(QString::number(mpCompartment->getRate()));

  // Expression
  mpEditExpression->setExpression(mpCompartment->getExpression());

  loadMetaboliteTable();

  mChanged = false;
  return;
}

void CQCompartment::save()
{
  if (mpCompartment == NULL) return;

  // Name
  if (mpCompartment->getObjectName() != (const char *) mpEditName->text().utf8())
    {
      if (!mpCompartment->setObjectName((const char *) mpEditName->text().utf8()))
        {
          QString msg;
          msg = "Unable to rename compartment '" + FROM_UTF8(mpCompartment->getObjectName()) + "'\n"
                + "to '" + mpEditName->text() + "' since a compartment with that name already exists.\n";

          CQMessageBox::information(this,
                                    "Unable to rename Compartment",
                                    msg,
                                    QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);

          mpEditName->setText(FROM_UTF8(mpCompartment->getObjectName()));
        }
      else
        {
          protectedNotify(ListViews::COMPARTMENT, ListViews::RENAME, mKey);
          mChanged = true;
        }
    }

  // Type
  if (mpCompartment->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()])
    {
      mpCompartment->setStatus((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()]);
      mChanged = true;
    }

  // Initial Volume
  if (QString::number(mpCompartment->getInitialValue(), 'g', 10) != mpEditInitialVolume->text())
    {
      mpCompartment->setInitialValue(mpEditInitialVolume->text().toDouble());
      mChanged = true;
    }

  // Expression
  if (mpCompartment->getExpression() != mpEditExpression->getExpression())
    {
      mpCompartment->setExpression(mpEditExpression->getExpression());
      mChanged = true;
    }

  if (mChanged) CCopasiDataModel::Global->changed();

  mChanged = false;
}

void CQCompartment::destroy()
{}

void CQCompartment::slotMetaboliteTableCurrentChanged(QListViewItem * pItem)
{
  if (mpCompartment == NULL) return;

  std::string s1, s2;
  s1 = pItem->text(0).utf8();

  std::multimap< const std::string, CCopasiObject * >::const_iterator it =
    mpCompartment->getMetabolites().getObjects().begin();
  std::multimap< const std::string, CCopasiObject * >::const_iterator end =
    mpCompartment->getMetabolites().getObjects().end();

  for (; it != end; ++it)
    if (dynamic_cast< CMetab * >(it->second) != NULL)
      {
        s2 = it->second->getObjectName();

        if (s1 == s2)
          mpListView->switchToOtherWidget(0, it->second->getKey());
      }
}

void CQCompartment::loadMetaboliteTable()
{
  if (mpCompartment == NULL) return;

  mpMetaboliteTable->clear();
  mpMetaboliteTable->setColumnWidth(0, 10);

  std::multimap< const std::string, CCopasiObject * >::const_iterator it =
    mpCompartment->getMetabolites().getObjects().begin();
  std::multimap< const std::string, CCopasiObject * >::const_iterator end =
    mpCompartment->getMetabolites().getObjects().end();

  for (; it != end; ++it)
    if (dynamic_cast< CMetab * >(it->second) != NULL)
      new QListViewItem(mpMetaboliteTable, FROM_UTF8(it->second->getObjectName()));

  return;
}
