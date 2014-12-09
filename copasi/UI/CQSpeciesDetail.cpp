// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQSpeciesDetail.h"
#include "CQMessageBox.h"
#include "CQNameSelectionDialog.h"  // for Copy button compartment options
#include "qtUtilities.h"

#include "model/CModel.h"
#include "model/CChemEqInterface.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModelExpansion.h"    //for Copy button and options

//UNDO framework classes
#ifdef COPASI_UNDO
#include "model/CReactionInterface.h"
#include "undoFramework/DeleteSpecieCommand.h"
#include "undoFramework/CreateNewSpecieCommand.h"
#include "undoFramework/SpecieTypeChangeCommand.h"
#include "undoFramework/SpecieInitialValueLostFocusCommand.h"
#include "undoFramework/UndoSpecieData.h"
#include "undoFramework/UndoReactionData.h"
#include "undoFramework/UndoGlobalQuantityData.h"
#include "undoFramework/UndoEventData.h"
#include "undoFramework/UndoEventAssignmentData.h"
#include "copasiui3window.h"
#endif

/*
 *  Constructs a CQSpeciesDetail which is a child of 'parent', with the
 *  name 'name'.'
 */
CQSpeciesDetail::CQSpeciesDetail(QWidget* parent, const char* name) :
  CopasiWidget(parent, name),
  mChanged(false),
  mpMetab(NULL),
  mpCurrentCompartment(NULL),
  mItemToType(),
  mInitialNumber(0.0),
  mInitialConcentration(0.0),
  mExpressionValid(false),
  mInitialExpressionValid(false)
{
  setupUi(this);

  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::REACTIONS]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

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

#ifdef COPASI_UNDO
  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  setUndoStack(pWindow->getUndoStack());
#endif
}

CQSpeciesDetail::~CQSpeciesDetail()
{
}

bool CQSpeciesDetail::leave()
{
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::FIXED &&
      (CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::REACTIONS)
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
            mpObject = NULL;
            mpMetab = NULL;
          }

        break;

      case ListViews::METABOLITE:

        // If the currently displayed metabolite is deleted we need to remove its references.
        if (action == ListViews::DELETE && mKey == key)
          {
            mKey = "";
            mpObject = NULL;
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
            (CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] == CModelEntity::ASSIGNMENT)
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
            mpEditCurrentValue->setText(QString::number(mpMetab->getConcentration(), 'g', 10));
            mpEditRate->setText(QString::number(mpMetab->getConcentrationRate(), 'g', 10));
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
            mpEditCurrentValue->setText(QString::number(mpMetab->getValue(), 'g', 10));
            mpEditRate->setText(QString::number(mpMetab->getRate(), 'g', 10));
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

  // Compartment
  const CCopasiVectorNS< CCompartment > & Compartments = pModel->getCompartments();
  const CCompartment * pCompartment;
  mpComboBoxCompartment->clear();

  mpComboBoxCompartment->setDuplicatesEnabled(false);
  size_t m;

  for (m = 0; m < Compartments.size(); m++)
    {
      pCompartment = Compartments[m];
      mpComboBoxCompartment->insertItem(mpComboBoxCompartment->count(), FROM_UTF8(pCompartment->getObjectName()));
    }

  mpCurrentCompartment = mpMetab->getCompartment();
  mpComboBoxCompartment->setCurrentIndex(mpComboBoxCompartment->findText(FROM_UTF8(mpCurrentCompartment->getObjectName())));

  // Simulation Type
  mpComboBoxType->setCurrentIndex(mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[mpMetab->getStatus()])));

  // Initial Concentration handled in slotTypeChanged
  mInitialConcentration = mpMetab->getInitialConcentration();

  // Initial Number handled in slotTypeChanged
  mInitialNumber = mpMetab->getInitialValue();

  // Transition Time
  mpEditTransitionTime->setText(QString::number(mpMetab->getTransitionTime(), 'g', 10));

  // Expression
  mpExpressionEMW->mpExpressionWidget->setExpression(mpMetab->getExpression());
  mpExpressionEMW->updateWidget();

  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpMetab->getInitialExpression());
  mpInitialExpressionEMW->updateWidget();

  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentIndex());

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
          mpComboBoxCompartment->setCurrentIndex(mpComboBoxCompartment->findText(FROM_UTF8(CompartmentToRemove)));

          slotCompartmentChanged(mpComboBoxCompartment->currentIndex());
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
  if (mpMetab->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()])
    {
      mpMetab->setStatus((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()]);
      mChanged = true;
    }

  // Initial Concentration and Initial Number
  switch (mFramework)
    {
      case 0:

        if (mpMetab->getInitialConcentration() != mInitialConcentration)
          {
            mpMetab->setInitialConcentration(mInitialConcentration);
            mChanged = true;
          }

        break;

      case 1:

        if (mpMetab->getInitialValue() != mInitialNumber)
          {
            mpMetab->setInitialValue(mInitialNumber);
            mChanged = true;
          }

        break;
    }

  // Expression
  if (mpMetab->getExpression() != mpExpressionEMW->mpExpressionWidget->getExpression())
    {
      mpMetab->setExpression(mpExpressionEMW->mpExpressionWidget->getExpression());
      mChanged = true;
    }

  // Initial Expression
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::ASSIGNMENT)
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

  mpReactionTable->setRowCount((int) Reactions.size());

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

void CQSpeciesDetail::slotBtnDelete()
{
#ifdef COPASI_UNDO
  mpUndoStack->push(new DeleteSpecieCommand(this));
#else

  if (mpMetab == NULL) return;

  CModel * pModel = const_cast< CModel *>(mpMetab->getModel());

  if (pModel == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "species",
                                FROM_UTF8(mpMetab->getObjectName()),
                                mpMetab->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        pModel->removeMetabolite(mKey);

#undef DELETE
        protectedNotify(ListViews::METABOLITE, ListViews::DELETE, mKey);
        protectedNotify(ListViews::METABOLITE, ListViews::DELETE, "");//Refresh all as there may be dependencies.
        //TODO notify about reactions
        break;
      }

      default:
        break;
    }

#endif
}

void CQSpeciesDetail::copy()
{
  if (mpMetab == NULL) return;

  CModel * pModel = NULL;

  if (mpMetab) pModel = mpDataModel->getModel();

  if (pModel == NULL) return; // for getting compartments and initializing cModelExpObj

  // Create and customize compartment choices dialog
  CQNameSelectionDialog * pDialog = new CQNameSelectionDialog(this);
  pDialog->setWindowTitle("Choose a compartment");
  pDialog->mpLblName->setText("compartment");
  pDialog->mpSelectionBox->clear();
  pDialog->mpSelectionBox->setDuplicatesEnabled(false);
  pDialog->mpSelectionBox->setEditable(false); // at least for now, unless we want to add new compartment creation here.

  // Use CModelExpansion for duplication
  CModelExpansion cModelExpObj = CModelExpansion(pModel);
  CModelExpansion::SetOfModelElements sourceObjects;
  CModelExpansion::ElementsMap origToCopyMapping;

  // for comboBox compartment list and setting compartment
  CCopasiVectorNS< CCompartment > & Compartments = pModel->getCompartments();

  CCopasiVectorN< CCompartment >::const_iterator it = Compartments.begin();
  CCopasiVectorN< CCompartment >::const_iterator end = Compartments.end();
  QStringList SelectionList;

  // Collect and load list of compartment names in comboBox
  for (; it != end; ++it)
    {
      SelectionList.append(FROM_UTF8((*it)->getObjectName()));
    }

  pDialog->setSelectionList(SelectionList);

  //Set the current compartment as the default
  mpCurrentCompartment = mpMetab->getCompartment();
  // to use here, and for testing if compartment changed after executing the dialog
  int origCompartmentIndex = pDialog->mpSelectionBox->findText(FROM_UTF8(mpCurrentCompartment->getObjectName()));
  pDialog->mpSelectionBox->setCurrentIndex(origCompartmentIndex);

  it = Compartments.begin(); // Reuse Compartments iterator to set compartment choice

  if (pDialog->exec() != QDialog::Rejected)
    {
      // Put species in different compartment (without name modification) by making
      // duplicateMetab think the other compartment was duplicated from the original
      if (origCompartmentIndex != pDialog->mpSelectionBox->currentIndex())
        {
          sourceObjects.addCompartment(mpMetab->getCompartment());
          origToCopyMapping.add(mpMetab->getCompartment(), *(it + pDialog->mpSelectionBox->currentIndex()));
        }

      sourceObjects.addMetab(mpMetab);
      cModelExpObj.duplicateMetab(mpMetab, "_copy", sourceObjects, origToCopyMapping);

      protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, "");//Refresh all
      protectedNotify(ListViews::METABOLITE, ListViews::DELETE, ""); //Refresh all
      protectedNotify(ListViews::REACTION, ListViews::DELETE, "");   //Refresh all
      mpListView->switchToOtherWidget(C_INVALID_INDEX, origToCopyMapping.getDuplicateKey(mKey));
    }

  pdelete(pDialog);
}

void CQSpeciesDetail::slotBtnNew()
{
#ifdef COPASI_UNDO
  mpUndoStack->push(new CreateNewSpecieCommand(this));
#else
  leave();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  if (pModel->getCompartments().size() == 0)
    pModel->createCompartment("compartment");

  std::string name = "species_1";
  int i = 1;

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
  protectedNotify(ListViews::METABOLITE, ListViews::ADD, key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);

#endif
}

void CQSpeciesDetail::slotCompartmentChanged(int compartment)
{
  if (!mpMetab || !mpCurrentCompartment) return;

  const CModel * pModel = mpMetab->getModel();

  if (pModel == NULL)
    return;

  QString Compartment = mpComboBoxCompartment->itemText(compartment);
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
}

void CQSpeciesDetail::slotInitialExpressionValid(bool valid)
{
  mInitialExpressionValid = valid;
}

void CQSpeciesDetail::slotInitialTypeChanged(bool useInitialExpression)
{
  if (useInitialExpression)
    {
      mpLblInitialExpression->show();
      mpInitialExpressionEMW->show();

      mpEditInitialValue->setEnabled(false);
      mpInitialExpressionEMW->updateWidget();
    }
  else
    {
      mpLblInitialExpression->hide();
      mpInitialExpressionEMW->hide();

      mpEditInitialValue->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::ASSIGNMENT);
    }
}

void CQSpeciesDetail::slotInitialValueLostFocus()
{
#ifdef COPASI_UNDO
  mpUndoStack->push(new SpecieInitialValueLostFocusCommand(this));
#else

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
        break;

      case 1:

        if (QString::number(mInitialNumber, 'g', 10) == mpEditInitialValue->text())
          return;

        mInitialNumber = mpEditInitialValue->text().toDouble();
        mInitialConcentration = CMetab::convertToConcentration(mInitialNumber,
                                *mpCurrentCompartment,
                                *pModel);
        break;
    }

#endif
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
        mpListView->switchToOtherWidget(C_INVALID_INDEX, pReaction->getKey());
    }
}

void CQSpeciesDetail::slotTypeChanged(int type)
{
#ifdef COPASI_UNDO

  if (mItemToType[type] == mpMetab->getStatus())
    {
      specieTypeChanged(type);
    }
  else
    {
      mpUndoStack->push(new SpecieTypeChangeCommand(mItemToType[type], mpMetab->getStatus(), this));
    }

#else

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
#endif
}

//Undo methods
#ifdef COPASI_UNDO

void CQSpeciesDetail::createNewSpecie()
{
  leave();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  if (pModel->getCompartments().size() == 0)
    pModel->createCompartment("compartment");

  std::string name = "species_1";
  int i = 1;

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
  protectedNotify(ListViews::METABOLITE, ListViews::ADD, key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQSpeciesDetail::deleteSpecie()
{
  if (mpMetab == NULL) return;

  CModel * pModel = const_cast< CModel *>(mpMetab->getModel());

  if (pModel == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "species",
                                FROM_UTF8(mpMetab->getObjectName()),
                                mpMetab->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        pModel->removeMetabolite(mKey);

#undef DELETE
        protectedNotify(ListViews::METABOLITE, ListViews::DELETE, mKey);
        protectedNotify(ListViews::METABOLITE, ListViews::DELETE, "");//Refresh all as there may be dependencies.
        //TODO notify about reactions
        break;
      }

      default:
        break;
    }

  mpListView->switchToOtherWidget(112, "");
}

void CQSpeciesDetail::deleteSpecie(UndoSpecieData *pSData)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  size_t index = pModel->findMetabByName(pSData->getName());
  CMetab *pSpecie = pModel->getMetabolites()[(int) index];
  std::string key = pSpecie->getKey();

  pModel->removeMetabolite(key);

#undef DELETE
  protectedNotify(ListViews::METABOLITE, ListViews::DELETE, key); //mKey);
  protectedNotify(ListViews::METABOLITE, ListViews::DELETE, "");//Refresh all as there may be dependencies.

  mpListView->switchToOtherWidget(112, "");
}

void CQSpeciesDetail::addSpecie(UndoSpecieData *pSData)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  //reinsert the species
  CMetab *pSpecie =  pModel->createMetabolite(pSData->getName(), pSData->getCompartment(), 1.0, pSData->getStatus());
  std::string key = pSpecie->getKey();

  if (pSData->getStatus() != CModelEntity::ASSIGNMENT)
    {
      pSpecie->setInitialConcentration(pSData->getIConc());
    }

  if (pSData->getStatus() == CModelEntity::ODE || pSData->getStatus() == CModelEntity::ASSIGNMENT)
    {
      if (pSData->getExpression() != "")
        {
          pSpecie->setExpression(pSData->getExpression());
          pSpecie->getExpressionPtr()->compile();
        }
    }

  // set initial expression
  if (pSData->getStatus() != CModelEntity::ASSIGNMENT && pSData->getInitialExpression() != "")
    {
      pSpecie->setInitialExpression(pSData->getInitialExpression());
    }

  protectedNotify(ListViews::METABOLITE, ListViews::ADD, key);

  //restore the reactions the species dependent on
  QList <UndoReactionData *> *reactionData = pSData->getReactionDependencyObjects();

  if (!reactionData->empty())
    {
      QList <UndoReactionData *>::const_iterator j;

      for (j = reactionData->begin(); j != reactionData->end(); ++j)
        {

          UndoReactionData * rData = *j;

          //need to make sure reaction doesn't exist in the model already
          if (pModel->getReactions().getIndex(rData->getName()) == C_INVALID_INDEX)
            {
              CReaction *pRea =  pModel->createReaction(rData->getName());
              CChemEqInterface *chem = new CChemEqInterface(pModel);
              chem->setChemEqString(rData->getRi()->getChemEqString());
              chem->writeToChemEq(pRea->getChemEq());
              rData->getRi()->createMetabolites();
              rData->getRi()->createOtherObjects();
              rData->getRi()->writeBackToReaction(pRea);

              protectedNotify(ListViews::REACTION, ListViews::ADD, pRea->getKey());
            }
        }
    }

  //reinsert the dependency global quantity
  QList <UndoGlobalQuantityData *> *pGlobalQuantityData = pSData->getGlobalQuantityDependencyObjects();

  if (!pGlobalQuantityData->empty())
    {
      QList <UndoGlobalQuantityData *>::const_iterator g;

      for (g = pGlobalQuantityData->begin(); g != pGlobalQuantityData->end(); ++g)
        {
          UndoGlobalQuantityData * gData = *g;

          if (pModel->getModelValues().getIndex(gData->getName()) == C_INVALID_INDEX)
            {
              CModelValue *pGlobalQuantity =  pModel->createModelValue(gData->getName()); //, gData->getInitialValue());

              if (pGlobalQuantity)
                {
                  pGlobalQuantity->setStatus(gData->getStatus());

                  if (gData->getStatus() != CModelEntity::ASSIGNMENT)
                    {
                      pGlobalQuantity->setInitialValue(gData->getInitialValue());
                    }

                  if (gData->getStatus() != CModelEntity::FIXED)
                    {
                      pGlobalQuantity->setExpression(gData->getExpression());
                      pGlobalQuantity->getExpressionPtr()->compile();
                    }

                  // set initial expression
                  if (gData->getStatus() != CModelEntity::ASSIGNMENT)
                    {
                      pGlobalQuantity->setInitialExpression(gData->getInitialExpression());
                      pGlobalQuantity->getInitialExpressionPtr()->compile();
                    }

                  protectedNotify(ListViews::MODELVALUE, ListViews::ADD, pGlobalQuantity->getKey());
                }
            }
        }
    }

  //reinsert the dependency events
  QList <UndoEventData *> *pEventData = pSData->getEventDependencyObjects();

  if (!pEventData->empty())
    {

      QList <UndoEventData *>::const_iterator ev;

      for (ev = pEventData->begin(); ev != pEventData->end(); ++ev)
        {

          UndoEventData * eData = *ev;

          CEvent *pEvent =  pModel->createEvent(eData->getName());
          std::string key = pEvent->getKey();

          //set the expressions
          pEvent->setTriggerExpression(eData->getTriggerExpression());
          pEvent->setDelayExpression(eData->getDelayExpression());
          pEvent->setPriorityExpression(eData->getPriorityExpression());

          QList <UndoEventAssignmentData *> *assignmentData = eData->getEventAssignmentData();
          QList <UndoEventAssignmentData *>::const_iterator i;

          for (i = assignmentData->begin(); i != assignmentData->end(); ++i)
            {
              UndoEventAssignmentData * assignData = *i;

              if (pEvent->getAssignments().getIndex(assignData->getTargetKey()) == C_INVALID_INDEX)
                {
                  CEventAssignment *eventAssign = new CEventAssignment(assignData->getTargetKey(), pEvent->getObjectParent());
                  eventAssign->setExpression(assignData->getExpression());
                  eventAssign->getExpressionPtr()->compile();
                  pEvent->getAssignments().add(eventAssign);
                }
            }

          protectedNotify(ListViews::EVENT, ListViews::ADD, key);
        }
    }

  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQSpeciesDetail::specieTypeChanged(int type)
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

void CQSpeciesDetail::specieTypeChanged(UndoSpecieData *pSData, int type)
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  //find the species of interest and switch to its widget
  size_t index = pModel->findMetabByName(pSData->getName());
  CMetab *pSpecie = pModel->getMetabolites()[(int) index];
  std::string key = pSpecie->getKey();
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);

  //set the species index
  mpComboBoxType->setCurrentIndex(mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[type])));
  mpMetab->setStatus((CModelEntity::Status)mItemToType[mpComboBoxType->currentIndex()]);
  specieTypeChanged(mpComboBoxType->currentIndex());
}

void CQSpeciesDetail::specieInitialValueLostFocus()
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
        break;

      case 1:

        if (QString::number(mInitialNumber, 'g', 10) == mpEditInitialValue->text())
          return;

        mInitialNumber = mpEditInitialValue->text().toDouble();
        mInitialConcentration = CMetab::convertToConcentration(mInitialNumber,
                                *mpCurrentCompartment,
                                *pModel);
        break;
    }
}

void CQSpeciesDetail::specieInitialValueLostFocus(UndoSpecieData *pSData)
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  //find the species of interest and switch to its widget
  size_t index = pModel->findMetabByName(pSData->getName());
  CMetab *pSpecie = pModel->getMetabolites()[(int) index];
  std::string key = pSpecie->getKey();
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);

  switch (mFramework)
    {
      case 0:
        mInitialConcentration = pSData->getIConc();
        pSData->setIConc(mpEditInitialValue->text().toDouble());
        mpEditInitialValue->setText(QString::number(mInitialConcentration, 'g', 10));
        break;

      case 1:
        mInitialNumber = pSData->getINumber();
        pSData->setINumber(mpEditInitialValue->text().toDouble());
        mpEditInitialValue->setText(QString::number(mInitialNumber, 'g', 10));
        break;
    }
}
#endif
