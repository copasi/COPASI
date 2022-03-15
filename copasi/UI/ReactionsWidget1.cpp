// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*********************************************************************
 **  $ CopasiUI/ReactionsWidget1.cpp
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the  information
 ** obtained from the data model about the Recations----It is Basically
 ** the Second level of Reactions.
 **********************************************************************/

#include <QWidget>

#include "copasi/copasi.h"
#include "ReactionsWidget1.h"
#include "listviews.h"
#include "parametertable.h"
#include "MyLineEdit.h"
#include "qtUtilities.h"
#include "ChemEqValidator.h"
#include "FunctionWidget1.h"
#include "CQMessageBox.h"
#include "CQNameSelectionDialog.h"  // for Copy button compartment options

#include "copasi/resourcesUI/CQIconResource.h"
#include "copasi/model/CReactionInterface.h"

#include "copasi/core/CDataVector.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CFunctionParameters.h"
#include "copasi/function/CFunctionParameter.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/model/CModelExpansion.h"    //for Copy button and options

//UNDO framework
#include "copasiui3window.h"
/*
 *  Constructs a ReactionsWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */

ReactionsWidget1::ReactionsWidget1(QWidget *parent, const char * name, Qt::WindowFlags f)
  : CopasiWidget(parent, name, f),
    mpRi(NULL)
{
  setupUi(this);

  if (!name)
    setObjectName("ReactionsWidget1");

  setWindowTitle("ReactionsWidget1");

  mpEditReactionScheme->setValidator(new ChemEqValidator(mpEditReactionScheme));

  mpBtnEditFunction->setIcon(CQIconResource::icon(CQIconResource::edit));
  mpBtnAddFunction->setIcon(CQIconResource::icon(CQIconResource::editAdd));
}

ReactionsWidget1::~ReactionsWidget1()
{
  pdelete(mpRi);
}

/* This function loads the reactions widget when its name is
   clicked in the tree   */
bool ReactionsWidget1::loadFromReaction(const CReaction * reaction)
{
  if (!reaction) return false;

  // this function is also called via notify, when the control has
  // not been entered, thus we need to ensure we are pointing to the
  // right object
  mpObject = const_cast<CReaction*>(reaction);

  // this loads the reaction into a CReactionInterface object.
  // the gui works on this object and later writes back the changes to the reaction
  pdelete(mpRi);
  mpRi = new CReactionInterface();

  mpRi->init(*reaction);

  // update the widget.
  FillWidgetFromRI();

  return true; //TODO: really check
}

bool ReactionsWidget1::saveToReaction()
{
  CReaction* reac = dynamic_cast< CReaction * >(mpObject);

  if (reac == NULL) return true;

  mpEditReactionScheme->slotForceUpdate();

  assert(mpDataModel != NULL);

  CModel * pModel = mpDataModel->getModel();

  if (pModel == NULL) return false;

  // The noise expression is the only this which has not been updated in the reaction interface
  if (mpNoiseExpressionWidget->mpExpressionWidget->isValid())
    {
      mpRi->setNoiseExpression(mpNoiseExpressionWidget->mpExpressionWidget->getExpression());
    }

  CUndoData UndoData(mpRi->createUndoData((CCore::Framework) mFramework));

  if (!UndoData.empty())
    {
      ListViews::addUndoMetaData(this, UndoData);
      slotNotifyChanges(mpDataModel->applyData(UndoData));

      CReaction * pReaction = dynamic_cast< CReaction * >(mpObject);

      if (pReaction != NULL) loadFromReaction(pReaction);
    }

  return true;
}

void ReactionsWidget1::slotCheckBoxClicked()
{
  mpEditReactionScheme->slotForceUpdate();

  // tell the reaction interface
  mpRi->setReversibility(mpChkReversible->isChecked(), "");

  // update the widget
  FillWidgetFromRI();
}

// the function has been changed
void ReactionsWidget1::slotComboBoxSelectionChanged(const QString & p2)
{
  // tell the reaction interface
  mpRi->setFunctionAndDoMapping(TO_UTF8(p2));

  // update the widget
  FillWidgetFromRI();
}

/*This function is called when the "Chemical Reaction" LineEdit is changed.*/
void ReactionsWidget1::slotLineEditChanged()
{
  std::string eq = TO_UTF8(mpEditReactionScheme->text());

  //first check if the string is a valid equation
  if (!CChemEqInterface::isValidEq(eq))
    {
      return;  // abort further processing
    }

  mpRi->setChemEqString(eq, "");

  // update the widget
  FillWidgetFromRI();
}

// added 5/19/04
void ReactionsWidget1::slotBtnNew()
{
  leaveProtected();

  std::string name = "reaction";
  int i = 1;

  assert(mpDataModel != NULL);

  CReaction * pReaction = NULL;

  while (!(pReaction = mpDataModel->getModel()->createReaction(name)))
    {
      i++;
      name = "reaction_";
      name += TO_UTF8(QString::number(i));
    }

  CUndoData UndoData(CUndoData::Type::INSERT, pReaction);
  ListViews::addUndoMetaData(this, UndoData);

  slotNotifyChanges(mpDataModel->recordData(UndoData));

  mpListView->switchToOtherWidget(ListViews::WidgetType::ReactionDetail, pReaction->getCN());
}

void ReactionsWidget1::slotBtnCopy()
{
}

void ReactionsWidget1::copy()
{
  CReaction* reac = dynamic_cast< CReaction * >(mpObject);

  if (reac == NULL) return;

  CModel * pModel = NULL;

  if (reac) pModel = mpDataModel->getModel();

  if (pModel == NULL) return; // for getting compartments and initializing cModelExpObj

  // Create and customize compartment choices dialog
  CQNameSelectionDialog * pDialog = new CQNameSelectionDialog(this);
  pDialog->resize(350, pDialog->height());
  pDialog->setToolTip("Cancel to re-use original species");
  pDialog->mpLblName->setText("compartment");
  pDialog->mpSelectionBox->clear();
  pDialog->mpSelectionBox->setDuplicatesEnabled(false);
  pDialog->mpSelectionBox->setEditable(false); // at least for now, unless we want to add new compartment creation here.

  // Use CModelExpansion for duplication
  CModelExpansion cModelExpObj = CModelExpansion(pModel);
  CModelExpansion::SetOfModelElements sourceObjects;
  CModelExpansion::ElementsMap origToCopyMapping;

  // for comboBox compartment list and setting compartment
  CDataVectorNS< CCompartment > & Compartments = pModel->getCompartments();

  CDataVectorN< CCompartment >::const_iterator Compartment_it = Compartments.begin();
  CDataVectorN< CCompartment >::const_iterator end = Compartments.end();
  QStringList SelectionList;

  // Collect and load list of compartment names in comboBox
  for (; Compartment_it != end; ++Compartment_it)
    {
      SelectionList.append(FROM_UTF8(Compartment_it->getObjectName()));
    }

  pDialog->setSelectionList(SelectionList);

  const CCompartment * origCompartment = NULL;
  // to use here, and for testing if compartment changed after executing the dialog
  int origCompartmentIndex;

  CDataVector< CChemEqElement >::const_iterator MetabIt;

  const CDataVector< CChemEqElement > & substratesToCopy = reac->getChemEq().getSubstrates();
  CUndoData UndoData;

  for (MetabIt = substratesToCopy.begin(); MetabIt != substratesToCopy.end(); MetabIt++)
    {
      pDialog->setWindowTitle("Create copy of " + FROM_UTF8(MetabIt->getMetabolite()->getObjectName()) + "?");
      origCompartment = MetabIt->getMetabolite()->getCompartment();
      origCompartmentIndex = pDialog->mpSelectionBox->findText(FROM_UTF8(origCompartment->getObjectName()));
      pDialog->mpSelectionBox->setCurrentIndex(origCompartmentIndex);

      Compartment_it = Compartments.begin(); // Reuse Compartments iterator to set compartment choice

      if (pDialog->exec() != QDialog::Rejected)
        {
          // Put species in different compartment (without name modification) by making
          // duplicateMetab think the other compartment was duplicated from the original
          if (origCompartmentIndex != pDialog->mpSelectionBox->currentIndex())
            {
              sourceObjects.addCompartment(origCompartment);
              origToCopyMapping.add(origCompartment, (Compartment_it + pDialog->mpSelectionBox->currentIndex()).constCast());
            }

          sourceObjects.addMetab(MetabIt->getMetabolite());

          cModelExpObj.duplicateMetab(MetabIt->getMetabolite(), "_copy", sourceObjects, origToCopyMapping, UndoData);
        }
    }

  const CDataVector< CChemEqElement > & productsToCopy = reac->getChemEq().getProducts();

  for (MetabIt = productsToCopy.begin(); MetabIt != productsToCopy.end(); MetabIt++)
    {
      pDialog->setWindowTitle("Create copy of " + FROM_UTF8(MetabIt->getMetabolite()->getObjectName()) + "?");
      origCompartment = MetabIt->getMetabolite()->getCompartment();
      origCompartmentIndex = pDialog->mpSelectionBox->findText(FROM_UTF8(origCompartment->getObjectName()));
      pDialog->mpSelectionBox->setCurrentIndex(origCompartmentIndex);

      Compartment_it = Compartments.begin();

      if (pDialog->exec() != QDialog::Rejected)
        {
          if (origCompartmentIndex != pDialog->mpSelectionBox->currentIndex())
            {
              sourceObjects.addCompartment(origCompartment);
              origToCopyMapping.add(origCompartment, (Compartment_it + pDialog->mpSelectionBox->currentIndex()).constCast());
            }

          sourceObjects.addMetab(MetabIt->getMetabolite());
          cModelExpObj.duplicateMetab(MetabIt->getMetabolite(), "_copy", sourceObjects, origToCopyMapping, UndoData);
        }
    }

  const CDataVector< CChemEqElement > & modifiersToCopy = reac->getChemEq().getModifiers();

  for (MetabIt = modifiersToCopy.begin(); MetabIt != modifiersToCopy.end(); MetabIt++)
    {
      pDialog->setWindowTitle("Create copy of " + FROM_UTF8(MetabIt->getMetabolite()->getObjectName()) + "?");
      origCompartment = MetabIt->getMetabolite()->getCompartment();
      origCompartmentIndex = pDialog->mpSelectionBox->findText(FROM_UTF8(origCompartment->getObjectName()));
      pDialog->mpSelectionBox->setCurrentIndex(origCompartmentIndex);

      Compartment_it = Compartments.begin();

      if (pDialog->exec() != QDialog::Rejected)
        {
          if (origCompartmentIndex != pDialog->mpSelectionBox->currentIndex())
            {
              sourceObjects.addCompartment(origCompartment);
              origToCopyMapping.add(origCompartment, (Compartment_it + pDialog->mpSelectionBox->currentIndex()).constCast());
            }

          sourceObjects.addMetab(MetabIt->getMetabolite());
          cModelExpObj.duplicateMetab(MetabIt->getMetabolite(), "_copy", sourceObjects, origToCopyMapping, UndoData);
        }
    }

  sourceObjects.addReaction(reac);
  cModelExpObj.duplicateReaction(reac, "_copy", sourceObjects, origToCopyMapping, UndoData);
  const CDataObject * pObject = origToCopyMapping.getDuplicateFromObject(mpObject);

  ListViews::addUndoMetaData(this, UndoData);
  UndoData.addMetaDataProperty("Widget Object CN", pObject->getCN());
  UndoData.addMetaDataProperty("Widget Object Name", pObject->getObjectDisplayName());

  slotNotifyChanges(mpDataModel->recordData(UndoData));

  if (pObject != NULL)
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::ReactionDetail, pObject->getCN());
    }

  pdelete(pDialog);
}

// Just added 5/18/04
void ReactionsWidget1::slotBtnDelete()
{
  CReaction * pReaction = dynamic_cast< CReaction * >(mpObject);

  if (pReaction == NULL) return;

  CModel * pModel = dynamic_cast< CModel * >(pReaction->getObjectAncestor("Model"));

  if (pModel == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "reaction",
                                FROM_UTF8(pReaction->getObjectName()),
                                pReaction);

  if (choice == QMessageBox::Ok)
    {
      CUndoData UndoData;
      pReaction->createUndoData(UndoData, CUndoData::Type::REMOVE);
      ListViews::addUndoMetaData(this, UndoData);

      slotNotifyChanges(mpDataModel->applyData(UndoData));
    }
}

void ReactionsWidget1::FillWidgetFromRI()
{
  setFramework(mFramework);

  mpEditReactionScheme->setText(FROM_UTF8(mpRi->getChemEqString()));
  mpChkReversible->setChecked(mpRi->isReversible());
  mpMultiCompartment->setChecked(mpRi->isMulticompartment());

  // Initialize scaling compartment combobox
  QMultiMap<QString, QString> Compartments;

  const CModel * pModel = static_cast< const CModel * >(mpObject->getObjectAncestor("Model"));

  if (pModel != NULL)
    {
      CDataVector< CCompartment >::const_iterator it = pModel->getCompartments().begin();
      CDataVector< CCompartment >::const_iterator end = pModel->getCompartments().end();

      for (; it != end; ++it)
        {
          QString Name = FROM_UTF8(it->getObjectName());
          Compartments.insertMulti(Name.toLower(), Name);
        }
    }

  std::set< std::string > ReactionCompartments = mpRi->getChemEqInterface().getCompartments();
  std::set< std::string >::const_iterator itReaComp = ReactionCompartments.begin();
  std::set< std::string >::const_iterator endReaComp = ReactionCompartments.end();

  for (; itReaComp != endReaComp; ++itReaComp)
    {
      QString Name = FROM_UTF8(*itReaComp);
      QList< QString > Values = Compartments.values(Name.toLower());

      if (!Values.contains(Name))
        {
          Compartments.insertMulti(Name.toLower(), Name);
        }
    }

  bool SignalsBlocked = mpComboBoxCompartment->blockSignals(true);
  mpComboBoxCompartment->clear();
  mpComboBoxCompartment->addItems(Compartments.values());
  mpComboBoxCompartment->setCurrentIndex(mpComboBoxCompartment->findText(FROM_UTF8(mpRi->getDefaultScalingCompartment())));
  mpComboBoxCompartment->blockSignals(SignalsBlocked);

  // if there is a current function the parameter table is initialized
  // the function combobox
  QStringList comboEntries;
  vectorOfStrings2QStringList(mpRi->getListOfPossibleFunctions(), comboEntries);

  SignalsBlocked = mpCmbRateLaw->blockSignals(true);
  mpCmbRateLaw->clear();
  mpCmbRateLaw->insertItems(0, comboEntries);

  if (mpRi->getFunctionName() != "")
    {
      if (comboEntries.filter(FROM_UTF8(mpRi->getFunctionName())).size() == 0)
        mpCmbRateLaw->insertItem(0, FROM_UTF8(mpRi->getFunctionName()));

      mpCmbRateLaw->setCurrentIndex(mpCmbRateLaw->findText(FROM_UTF8(mpRi->getFunctionName())));
      mpCmbRateLaw->setToolTip(FROM_UTF8(mpRi->getFunctionDescription()));

      assert(CRootContainer::getDatamodelList()->size() > 0);
      mpParameterMapping->updateTable(*mpRi, dynamic_cast< CReaction * >(mpObject));
    }
  else
    {
      mpCmbRateLaw->insertItem(0, "undefined");
      mpCmbRateLaw->setCurrentIndex(0);
      mpParameterMapping->initTable();
    }

  mpCmbRateLaw->blockSignals(SignalsBlocked);

  // Noise Expression
  mpNoiseExpressionWidget->mpExpressionWidget->setExpression(mpRi->getNoiseExpression());
  mpNoiseExpressionWidget->updateWidget();
  mpBoxAddNoise->setChecked(mpRi->hasNoise());

  slotAddNoiseChanged(mpRi->hasNoise());

  mpDefaultUnit->setChecked(mpRi->getKineticLawUnitType() == CReaction::KineticLawUnit::Default);
  mpConcentrationUnit->setChecked(mpRi->getEffectiveKineticLawUnitType() == CReaction::KineticLawUnit::ConcentrationPerTime);
  mpAmountUnit->setChecked(mpRi->getEffectiveKineticLawUnitType() == CReaction::KineticLawUnit::AmountPerTime);

  slotDefaultUnitChecked(mpDefaultUnit->isChecked());
  mpConcentrationUnit->setText(FROM_UTF8(CUnit::prettyPrint(mpRi->getConcentrationRateUnit())));
  mpAmountUnit->setText(FROM_UTF8(CUnit::prettyPrint(mpRi->getAmountRateUnit())));
}

void ReactionsWidget1::slotTableChanged(int index, int sub, QString newValue)
{
  size_t Index = index;

  CReaction* reaction = dynamic_cast<CReaction*>(mpObject);

  if (reaction == NULL)
    return;

  if (mpRi->getUsage(Index) == CFunctionParameter::Role::PARAMETER)
    {
      if (sub != 0) return;

      if (mpRi->isLocalValue(Index))
        {
          mpRi->setLocalValue(Index, newValue.toDouble());
        }
      else
        {
          mpRi->setMapping(Index, TO_UTF8(newValue));
        }

      // Run a table update, to update the mapped value, and it's
      // editing status, in the adjacent cell.

      if (reaction->getFunction() != &mpRi->getFunction())
        saveToReaction();

      mpParameterMapping->updateTable(*mpRi, dynamic_cast< CReaction * >(mpObject));
    }
  else if (mpRi->getUsage(Index) == CFunctionParameter::Role::VOLUME)
    {
      if (sub != 0) return;

      mpRi->setMapping(Index, TO_UTF8(newValue));
    }
  else
    {
      if (sub == 0) //here we assume that vector parameters cannot be edited
        {
          mpRi->setMapping(Index, TO_UTF8(newValue));

          // Update modifiers in reaction scheme
          mpEditReactionScheme->setText(FROM_UTF8(mpRi->getChemEqString()));
        }
    }

  // update the widget
  int rrr = mpParameterMapping->currentRow();
  int ccc = mpParameterMapping->currentColumn();
  mpParameterMapping->setCurrentCell(rrr, ccc);
}

void ReactionsWidget1::slotParameterStatusChanged(int index, bool local)
{
  // slot is a reminant of when a checkbox handled this.
  // This could be added in to slotTableChanged

  if (local)
    mpRi->setLocal(index);
  else
    mpRi->setMapping(index, "unknown"); //TODO keep global parameter
}

void ReactionsWidget1::slotGotoFunction()
{
  if (mpRi == NULL) return;

  mpListView->switchToOtherWidget(ListViews::WidgetType::FunctionDetail, mpRi->getFunction().getCN());
}

void ReactionsWidget1::slotNewFunction()
{
  // FunctionWidget1 * fw = new FunctionWidget1(NULL);
  // fw->show();
  // TODO: we could think about calling the function widget as a dialog here...

  std::string name = std::string("Rate Law for ") + mpObject->getObjectName();
  std::string nname = name;
  size_t i = 0;
  CDataVectorN<CFunction>& FunctionList
    = CRootContainer::getFunctionList()->loadedFunctions();
  CFunction* pFunc;

  while (FunctionList.getIndex(nname) != C_INVALID_INDEX)
    {
      i++;
      nname = name + "_";
      nname += TO_UTF8(QString::number(i));
    }

  CRootContainer::getFunctionList()->add(pFunc = new CKinFunction(nname), true);
  protectedNotify(ListViews::ObjectType::FUNCTION, ListViews::ADD, pFunc->getCN());

  mpListView->switchToOtherWidget(ListViews::WidgetType::FunctionDetail, pFunc->getCN());
}

void ReactionsWidget1::slotAddNoiseChanged(bool hasNoise)
{
  mpRi->setHasNoise(hasNoise);
  mpNoiseExpressionWidget->mpExpressionWidget->setExpression(mpRi->getNoiseExpression());

  if (hasNoise)
    {
      mpLblNoiseExpression->show();
      mpNoiseExpressionWidget->show();
      mpNoiseExpressionWidget->updateWidget();
    }
  else
    {
      mpLblNoiseExpression->hide();
      mpNoiseExpressionWidget->hide();
    }
}

void ReactionsWidget1::slotDefaultUnitChecked(const bool & checked)
{
  mpConcentrationUnit->setEnabled(!checked);
  mpAmountUnit->setEnabled(!checked);
  mpComboBoxCompartment->setEnabled(!checked && mpConcentrationUnit->isChecked());

  if (checked)
    {
      mpRi->setKineticLawUnitType(CReaction::KineticLawUnit::Default);
      mpComboBoxCompartment->setCurrentIndex(mpComboBoxCompartment->findText(FROM_UTF8(mpRi->getDefaultScalingCompartment())));
      slotConcentrationUnitChecked(mpRi->getEffectiveKineticLawUnitType() == CReaction::KineticLawUnit::ConcentrationPerTime);
    }
  else
    {
      mpRi->setKineticLawUnitType(mpRi->getEffectiveKineticLawUnitType());
    }
}

void ReactionsWidget1::slotConcentrationUnitChecked(const bool & checked)
{
  mpConcentrationUnit->setChecked(checked);
  mpAmountUnit->setChecked(!checked);
  mpComboBoxCompartment->setEnabled(checked && !mpDefaultUnit->isChecked());

  if (mpRi->getKineticLawUnitType() != CReaction::KineticLawUnit::Default)
    {
      mpRi->setKineticLawUnitType(checked ? CReaction::KineticLawUnit::ConcentrationPerTime : CReaction::KineticLawUnit::AmountPerTime);
    }

  mpParameterMapping->updateTable(*mpRi, dynamic_cast< CReaction * >(mpObject));
}

void ReactionsWidget1::slotAmountUnitChecked(const bool & checked)
{
  mpConcentrationUnit->setChecked(!checked);
  mpAmountUnit->setChecked(checked);
  mpComboBoxCompartment->setEnabled(!checked && !mpDefaultUnit->isChecked());

  if (mpRi->getKineticLawUnitType() != CReaction::KineticLawUnit::Default)
    {
      mpRi->setKineticLawUnitType(checked ? CReaction::KineticLawUnit::AmountPerTime : CReaction::KineticLawUnit::ConcentrationPerTime);
    }

  mpParameterMapping->updateTable(*mpRi, dynamic_cast< CReaction * >(mpObject));
}

// virtual
void ReactionsWidget1::slotCompartmentSelectionChanged(const QString & compartment)
{
  mpRi->setScalingCompartment(TO_UTF8(compartment));
  mpConcentrationUnit->setText(FROM_UTF8(CUnit::prettyPrint(mpRi->getConcentrationRateUnit())));
  mpParameterMapping->updateTable(*mpRi, dynamic_cast< CReaction * >(mpObject));
}

bool ReactionsWidget1::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  switch (objectType)
    {
      case ListViews::ObjectType::MODEL:

        // For a new model we need to remove references to no longer existing reaction
        if (action != ListViews::CHANGE)
          {
            mObjectCN.clear();
            mpObject = NULL;
            mpRi = NULL;
          }

        break;

      case ListViews::ObjectType::REACTION:

        // If the currently displayed reaction is deleted we need to remove its references.
        if (action == ListViews::DELETE && mObjectCN == cn)
          {
            mObjectCN.clear();
            mpObject = NULL;
            mpRi = NULL;
          }

        break;

      case ListViews::ObjectType::STATE:
      case ListViews::ObjectType::METABOLITE:
      case ListViews::ObjectType::COMPARTMENT:
        break;

      default:
        return true;
        break;
    }

  if (isVisible() && !mIgnoreUpdates)
    loadFromReaction(dynamic_cast< CReaction * >(mpObject));

  return true;
}

bool ReactionsWidget1::leaveProtected()
{
  saveToReaction();
  return true; //always return true. That means that the widget can be
  //left without saving
}

bool ReactionsWidget1::enterProtected()
{
  CReaction* reac = dynamic_cast< CReaction * >(mpObject);

  if (reac)
    return loadFromReaction(reac);

  mpListView->switchToOtherWidget(ListViews::WidgetType::Reactions, std::string());
  return false;
}

void ReactionsWidget1::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  const CReaction * pReaction = dynamic_cast< CReaction * >(mpObject);

  const CModel * pModel = NULL;

  if (pReaction != NULL)
    pModel = dynamic_cast<const CModel *>(pReaction->getObjectAncestor("Model"));

  QString Units;

  switch (mFramework)
    {
      case 0:
        Units = " [" + ((pModel != NULL) ? FROM_UTF8(CUnit::prettyPrint(pModel->getQuantityUnit() + "/(" + pModel->getTimeUnit() + ")")) : "?") + "]";
        TextLabel8->setText("Flux" + Units);

        if (pReaction != NULL)
          mpEditFlux->setText(convertToQString(pReaction->getFlux()));

        break;

      case 1:
        Units = " [" + ((pModel != NULL) ? FROM_UTF8(CUnit::prettyPrint("1/(" + pModel->getTimeUnit() + ")")) : "?") + "]";
        TextLabel8->setText("Number Flux" + Units);

        if (pReaction != NULL)
          mpEditFlux->setText(convertToQString(pReaction->getParticleFlux()));

        break;
    }
}
