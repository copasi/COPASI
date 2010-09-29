// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSpeciesDetail.cpp,v $
//   $Revision: 1.2.4.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/09/29 16:10:11 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQSpeciesDetail.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "CTabWidget.h"

#include "model/CModel.h"
#include "model/CChemEqInterface.h"
#include "report/CCopasiRootContainer.h"

/*
 *  Constructs a CQSpeciesDetail which is a child of 'parent', with the
 *  name 'name'.'
 */
CQSpeciesDetail::CQSpeciesDetail(QWidget* parent, const char* name) :
    CopasiWidget(parent, name),
    mChanged(false),
    mInitialNumberLastChanged(true),
    mpMetab(NULL),
    mpCurrentCompartment(NULL),
    mItemToType(),
    mInitialNumber(0.0),
    mInitialConcentration(0.0),
    mExpressionValid(false),
    mInitialExpressionValid(false)
{
  setupUi(this);

  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::REACTIONS]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::REACTIONS);
  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);

//  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
//  int Width = fontMetrics().width("Concentration (" +
//                                  FROM_UTF8((*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getConcentrationUnitsDisplayString()) +
//                                  ")");
//

//  mpLblValue->setMinimumWidth(Width);

  mpExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);

  mpInitialExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::InitialExpression);

  mpReactionTable->verticalHeader()->hide();
  mpReactionTable->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpReactionTable->horizontalHeader()->hide();
  mpReactionTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
}

CQSpeciesDetail::~CQSpeciesDetail()
{
}

void CQSpeciesDetail::languageChange()
{
  retranslateUi(this);
}

bool CQSpeciesDetail::leave()
{
  // This is now always enabled, i.e., a save is always performed!
  if (mpBtnCommit->isEnabled())
    {
      if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::FIXED &&
          (CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::REACTIONS)
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
    }

  return true;
}

bool CQSpeciesDetail::update(ListViews::ObjectType objectType,
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
            mpMetab = NULL;
          }

        break;

      case ListViews::METABOLITE:

        // If the currently displayed metabolite is deleted we need to remove its references.
        if (action == ListViews::DELETE && mKey == key)
          {
            mKey = "";
            mpMetab = NULL;
          }

        break;

      case ListViews::STATE:
      case ListViews::COMPARTMENT:
        break;

      default:
        return true;
        break;
    }

  if (isVisible() && !mIgnoreUpdates)
    load();

  return true;
}

void CQSpeciesDetail::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  const CModel * pModel = NULL;

  if (mpMetab)
    pModel = mpMetab->getModel();

  QString ValueUnits;

  if (pModel)
    ValueUnits = FROM_UTF8(pModel->getConcentrationUnitsDisplayString());

  if (!ValueUnits.isEmpty())
    ValueUnits = " (" + ValueUnits + ")";

  QString RateUnits;

  if (pModel)
    RateUnits = FROM_UTF8(pModel->getConcentrationRateUnitsDisplayString());

  if (!RateUnits.isEmpty())
    RateUnits = " (" + RateUnits + ")";

  QString FrequencyUnits;

  if (pModel)
    FrequencyUnits = FROM_UTF8(pModel->getFrequencyUnitsDisplayString());

  if (!FrequencyUnits.isEmpty())
    FrequencyUnits = " (" + FrequencyUnits + ")";

  switch (mFramework)
    {
      case 0:
        mpLblValue->setText("Concentration" + ValueUnits);

        if (mpMetab != NULL &&
            (CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] == CModelEntity::ASSIGNMENT)
          mpLblExpression->setText("Expression" + ValueUnits);
        else
          mpLblExpression->setText("Expression" + RateUnits);

        mpLblRate->setText("Rate" + RateUnits);

        ValueUnits.replace(0, 1, '\n'); // Line break instead of space
        mpLblInitialValue->setText("Initial Concentration" + ValueUnits);
        mpLblInitialExpression->setText("Initial Expression" + ValueUnits);

        mpEditInitialValue->setText(QString::number(mInitialConcentration, 'g', 10));

        if (mpMetab != NULL)
          {
            mpEditInitialValue->setReadOnly(!mpMetab->isInitialConcentrationChangeAllowed());
            mpEditCurrentValue->setText(QString::number(mpMetab->getConcentration()));
            mpEditRate->setText(QString::number(mpMetab->getConcentrationRate()));
          }
        else
          {
            mpEditInitialValue->setReadOnly(false);
            mpEditCurrentValue->setText("");
            mpEditRate->setText("");
          }

        break;

      case 1:
        mpLblInitialValue->setText("Initial Particle Number");

        ValueUnits.replace(0, 1, '\n'); // Line break instead of space
        mpLblInitialExpression->setText("Initial Expression" + ValueUnits);

        if (mpMetab != NULL &&
            mpMetab->getStatus() == CModelEntity::ASSIGNMENT)
          mpLblExpression->setText("Expression" + ValueUnits);
        else
          mpLblExpression->setText("Expression" + RateUnits);

        mpLblValue->setText("Particle Number");
        mpLblRate->setText("Rate" + FrequencyUnits);

        mpEditInitialValue->setText(QString::number(mInitialNumber, 'g', 10));
        mpEditInitialValue->setReadOnly(false);

        if (mpMetab != NULL)
          {
            mpEditCurrentValue->setText(QString::number(mpMetab->getValue()));
            mpEditRate->setText(QString::number(mpMetab->getRate()));
          }
        else
          {
            mpEditCurrentValue->setText("");
            mpEditRate->setText("");
          }

        break;
    }
}

bool CQSpeciesDetail::enterProtected()
{
  mpMetab = dynamic_cast< CMetab * >(mpObject);

  if (!mpMetab)
    {

      mpListView->switchToOtherWidget(112, "");
      return false;
    }

  load();
  return true;
}

void CQSpeciesDetail::load()
{
  if (mpMetab == NULL) return;

  const CModel * pModel = NULL;

  if (mpMetab)
    pModel = mpMetab->getModel();

  QString TimeUnits;

  if (pModel)
    TimeUnits = FROM_UTF8(pModel->getTimeUnitsDisplayString());

  if (!TimeUnits.isEmpty())
    TimeUnits = " (" + TimeUnits + ")";

  // Update the labels to reflect the model units
  mpLblTransitionTime->setText("Transition Time " + TimeUnits);

  // Name
  mpEditName->setText(FROM_UTF8(mpMetab->getObjectName()));

  // Compartment
  const CCopasiVectorNS< CCompartment > & Compartments = pModel->getCompartments();
  const CCompartment * pCompartment;
  mpComboBoxCompartment->clear();

  mpComboBoxCompartment->setDuplicatesEnabled(false);
  unsigned C_INT32 m;

  for (m = 0; m < Compartments.size(); m++)
    {
      pCompartment = Compartments[m];
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

  // Transistion Time
  mpEditTransitionTime->setText(QString::number(mpMetab->getTransitionTime()));

  // Expression
  mpExpressionEMW->mpExpressionWidget->setExpression(mpMetab->getExpression());
  mpExpressionEMW->updateWidget();

  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpMetab->getInitialExpression());
  mpInitialExpressionEMW->updateWidget();

  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentItem());

  // Use Initial Expression
  if (mpMetab->getStatus() == CModelEntity::ASSIGNMENT ||
      mpMetab->getInitialExpression() == "")
    {
      mpBoxUseInitialExpression->setChecked(false);
      // slotInitialTypeChanged(false);
    }
  else
    {
      mpBoxUseInitialExpression->setChecked(true);
      // slotInitialTypeChanged(true);
    }

  loadReactionTable();

  // Update the units and values accordingly
  setFramework(mFramework);

  mChanged = false;
  return;
}

void CQSpeciesDetail::save()
{
  if (mpMetab == NULL) return;

  CModel * pModel = const_cast< CModel * >(mpMetab->getModel());

  if (pModel == NULL) return;

  // Name
  if (mpMetab->getObjectName() != TO_UTF8(mpEditName->text()))
    {
      if (!mpMetab->setObjectName(TO_UTF8(mpEditName->text())))
        {
          QString msg;
          msg = "Unable to rename species '" + FROM_UTF8(mpMetab->getObjectName()) + "'\n"
                + "to '" + mpEditName->text() + "' since a species with that name already exists.\n";

          CQMessageBox::information(this,
                                    "Unable to rename Species",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::Ok);

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

      if (!pModel->getCompartments()[TO_UTF8(Compartment)]->addMetabolite(mpMetab))
        {
          QString msg;
          msg = "Unable to move species '" + FROM_UTF8(mpMetab->getObjectName()) + "'\n"
                + "from compartment '" + FROM_UTF8(CompartmentToRemove) + "' to compartment '" + Compartment + "'\n"
                + "since a species with that name already exist in the target compartment.";

          CQMessageBox::information(this,
                                    "Unable to move Species",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::Ok);

          // Revert the changes
          mpComboBoxCompartment->setCurrentText(FROM_UTF8(CompartmentToRemove));
          slotCompartmentChanged(mpComboBoxCompartment->currentItem());
        }
      else
        {
          pModel->getCompartments()[CompartmentToRemove]->getMetabolites().remove(mpMetab->getObjectName());
          pModel->setCompileFlag();
          pModel->initializeMetabolites();
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
  if (mpMetab->getExpression() != mpExpressionEMW->mpExpressionWidget->getExpression())
    {
      mpMetab->setExpression(mpExpressionEMW->mpExpressionWidget->getExpression());
      mChanged = true;
    }

  // Initial Expression
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::ASSIGNMENT)
    {
      if (mpBoxUseInitialExpression->isChecked() &&
          mpMetab->getInitialExpression() != (mpInitialExpressionEMW->mpExpressionWidget->getExpression()))
        {
          mpMetab->setInitialExpression(mpInitialExpressionEMW->mpExpressionWidget->getExpression());
          mChanged = true;
        }
      else if (!mpBoxUseInitialExpression->isChecked() &&
               mpMetab->getInitialExpression() != "")
        {
          mpMetab->setInitialExpression("");
          mChanged = true;
        }
    }

  if (mChanged)
    {
      if (mpDataModel)
        mpDataModel->changed();

      protectedNotify(ListViews::METABOLITE, ListViews::CHANGE, mKey);
    }

  mChanged = false;
}

void CQSpeciesDetail::loadReactionTable()
{
  if (mpMetab == NULL) return;

  CModel * pModel = const_cast< CModel * >(mpMetab->getModel());

  if (pModel == NULL) return;

  std::set< const CCopasiObject * > Reactions;
  pModel->appendDependentReactions(mpMetab->getDeletedObjects(), Reactions);

  mpReactionTable->setRowCount(Reactions.size());

  std::set< const CCopasiObject * >::const_iterator it = Reactions.begin();
  std::set< const CCopasiObject * >::const_iterator end = Reactions.end();
  int i = 0;
  const CReaction * pReaction;

  for (; it != end; ++it, ++i)
    {
      pReaction = static_cast< const CReaction * >(*it);
      mpReactionTable->setItem(i, 0, new QTableWidgetItem(FROM_UTF8(pReaction->getObjectName()) + ":"));
      mpReactionTable->setItem(i, 1, new QTableWidgetItem(FROM_UTF8(CChemEqInterface::getChemEqString(pModel, *pReaction, false))));
    }

  if (i == 0)
    mpReactionTable->setItem(i, 0, new QTableWidgetItem("none"));

  // Resize columns to content.

  return;
}

void CQSpeciesDetail::slotBtnCommit()
{
  mpBtnCommit->setFocus();
  save();
  load();
}

void CQSpeciesDetail::slotBtnDelete()
{
  if (mpMetab == NULL) return;

  CModel * pModel = const_cast< CModel *>(mpMetab->getModel());

  if (pModel == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, pModel, "species",
                                FROM_UTF8(mpMetab->getObjectName()),
                                mpMetab->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        unsigned C_INT32 index =
          pModel->getMetabolites().getIndex(CCopasiRootContainer::getKeyFactory()->get(mKey));

        pModel->removeMetabolite(mKey);
        std::string deletedKey = mKey;

        unsigned C_INT32 size =
          pModel->getMetabolites().size();

        QObject *pParent = parent();
        CTabWidget * pTabWidget = NULL;

        while (pParent != NULL &&
               (pTabWidget = dynamic_cast< CTabWidget *>(pParent)) == NULL)
          {
            pParent = pParent->parent();
          }

        if (pTabWidget != NULL)
          {
            if (size > 0)
              pTabWidget->enter(pModel->getMetabolites()[std::min(index, size - 1)]->getKey());
            else
              pTabWidget->enter("");
          }

#undef DELETE
        protectedNotify(ListViews::METABOLITE, ListViews::DELETE, deletedKey);
        //TODO notify about reactions
        break;
      }

      default:
        break;
    }
}

void CQSpeciesDetail::slotBtnNew()
{
  save();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  if (pModel->getCompartments().size() == 0)
    pModel->createCompartment("compartment");

  std::string name = "species";
  int i = 0;

  while (!(mpMetab = pModel->createMetabolite(name, "", 1.0, CModelEntity::REACTIONS)))
    {
      i++;
      name = "species_";
      name += TO_UTF8(QString::number(i));
    }

  switch (mFramework)
    {
      case 0:
        mpMetab->setInitialConcentration(1.0);
        break;

      case 1:
        mpMetab->setInitialValue(100.0);
        break;
    }

  std::string key = mpMetab->getKey();
  enter(key);
  protectedNotify(ListViews::METABOLITE, ListViews::ADD, key);
  mpListView->switchToOtherWidget(-1, key);
}

void CQSpeciesDetail::slotBtnRevert()
{
  load();
}

void CQSpeciesDetail::slotCompartmentChanged(int compartment)
{
  if (!mpMetab || !mpCurrentCompartment) return;

  const CModel * pModel = mpMetab->getModel();

  if (pModel == NULL)
    return;

  QString Compartment = mpComboBoxCompartment->text(compartment);
  const CCompartment * pNewCompartment =
    pModel->getCompartments()[TO_UTF8(Compartment)];

  if (pNewCompartment == mpCurrentCompartment ||
      pNewCompartment == NULL) return;

  mInitialNumber *= pNewCompartment->getInitialValue() / mpCurrentCompartment->getInitialValue();

  if (mFramework == 1)
    mpEditInitialValue->setText(QString::number(mInitialNumber, 'g', 10));

  mpCurrentCompartment = pNewCompartment;
}

void CQSpeciesDetail::slotExpressionValid(bool valid)
{
  mExpressionValid = valid;
  mpBtnCommit->setEnabled(mExpressionValid && mInitialExpressionValid);
}

void CQSpeciesDetail::slotInitialExpressionValid(bool valid)
{
  mInitialExpressionValid = valid;
  mpBtnCommit->setEnabled(mExpressionValid && mInitialExpressionValid);
}

void CQSpeciesDetail::slotInitialTypeChanged(bool useInitialExpression)
{
  if (useInitialExpression)
    {
      gridLayout->addWidget(mpLblInitialExpression, 5, 0);

      mpLblInitialExpression->show();
      mpInitialExpressionEMW->show();

      mpEditInitialValue->setEnabled(false);
      mpInitialExpressionEMW->updateWidget();
    }
  else
    {
      gridLayout->remove(mpLblInitialExpression);

      mpLblInitialExpression->hide();
      mpInitialExpressionEMW->hide();

      mpEditInitialValue->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::ASSIGNMENT);
    }
}

void CQSpeciesDetail::slotInitialValueLostFocus()
{
  if (!mpMetab || !mpCurrentCompartment) return;

  const CModel * pModel = mpMetab->getModel();

  if (pModel == NULL)
    return;

  switch (mFramework)
    {
      case 0:

        if (QString::number(mInitialConcentration, 'g', 10) == mpEditInitialValue->text())
          return;

        mInitialConcentration = mpEditInitialValue->text().toDouble();
        mInitialNumber = CMetab::convertToNumber(mInitialConcentration,
                         *mpCurrentCompartment,
                         *pModel);

        mInitialNumberLastChanged = false;
        break;

      case 1:

        if (QString::number(mInitialNumber, 'g', 10) == mpEditInitialValue->text())
          return;

        mInitialNumber = mpEditInitialValue->text().toDouble();
        mInitialConcentration = CMetab::convertToConcentration(mInitialNumber,
                                *mpCurrentCompartment,
                                *pModel);

        mInitialNumberLastChanged = true;
        break;
    }
}

void CQSpeciesDetail::slotNameLostFocus()
{}

void CQSpeciesDetail::slotSwitchToReaction(int row, int /* column */)
{
  if (mpMetab == NULL) return;

  const CModel * pModel = mpMetab->getModel();

  if (pModel == NULL) return;

  std::set< const CCopasiObject * > Reactions;
  pModel->appendDependentReactions(mpMetab->getDeletedObjects(), Reactions);

  std::string s1, s2;
  s1 = TO_UTF8(mpReactionTable->item(row, 0)->text());
  s1 = s1.substr(0, s1.length() - 1);

  C_INT32 i = 0;
  std::set< const CCopasiObject * >::const_iterator it = Reactions.begin();
  std::set< const CCopasiObject * >::const_iterator end = Reactions.end();
  const CReaction * pReaction;

  for (; it != end; ++it, ++i)
    {
      pReaction = static_cast< const CReaction * >(*it);
      s2 = pReaction->getObjectName();

      if (s1 == s2)
        mpListView->switchToOtherWidget(0, pReaction->getKey());
    }
}

void CQSpeciesDetail::slotTypeChanged(int type)
{
  switch ((CModelEntity::Status) mItemToType[type])
    {
      case CModelEntity::FIXED:
        mpLblExpression->hide();
        mpExpressionEMW->hide();

        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());
        break;

      case CModelEntity::ASSIGNMENT:
        mpLblExpression->show();
        mpExpressionEMW->show();

        mpBoxUseInitialExpression->setEnabled(false);
        slotInitialTypeChanged(false);

        mpExpressionEMW->updateWidget();
        break;

      case CModelEntity::ODE:
        mpLblExpression->show();
        mpExpressionEMW->show();

        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

        mpExpressionEMW->updateWidget();
        break;

      case CModelEntity::REACTIONS:
        mpLblExpression->hide();
        mpExpressionEMW->hide();

        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());
        break;

      default:
        break;
    }

  // This will update the unit display.
  setFramework(mFramework);
}
