// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"
#include "ReactionsWidget1.h"
#include "listviews.h"
#include "parametertable.h"
#include "MyLineEdit.h"
#include "qtUtilities.h"
#include "ChemEqValidator.h"
#include "FunctionWidget1.h"
#include "CQMessageBox.h"
#include "CQNameSelectionDialog.h"  // for Copy button compartment options

#include "resourcesUI/CQIconResource.h"
#include "model/CReactionInterface.h"

#include "copasi/core/CDataVector.h"
#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "model/CModel.h"
#include "function/CFunctionDB.h"
#include "function/CFunctionParameters.h"
#include "function/CFunctionParameter.h"
#include "report/CKeyFactory.h"
#include "model/CModelExpansion.h"    //for Copy button and options

//UNDO framework
#include "undoFramework/DeleteReactionCommand.h"
#include "undoFramework/CreateNewReactionCommand.h"
#include "undoFramework/ReactionChangeCommand.h"
#include "undoFramework/UndoReactionData.h"
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

  setWindowTitle(trUtf8("ReactionsWidget1"));

  mpEditReactionScheme->setValidator(new ChemEqValidator(mpEditReactionScheme));

  mpBtnEditFunction->setIcon(CQIconResource::icon(CQIconResource::edit));
  mpBtnAddFunction->setIcon(CQIconResource::icon(CQIconResource::editAdd));

#ifndef WITH_SDE_SUPPORT
  mpBoxAddNoise->hide();
#endif

  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  setUndoStack(pWindow->getUndoStack());
}

ReactionsWidget1::~ReactionsWidget1()
{
  pdelete(mpRi);
}

/* This function loads the reactions widget when its name is
   clicked in the tree   */
bool ReactionsWidget1::loadFromReaction(const CReaction* reaction)
{
  if (!reaction) return false;

  // this function is also called via notify, when the control has
  // not been entered, thus we need to ensure we are pointing to the
  // right object
  mpObject = const_cast<CReaction*>(reaction);

  // this loads the reaction into a CReactionInterface object.
  // the gui works on this object and later writes back the changes to the reaction
  pdelete(mpRi);
  mpRi = new CReactionInterface(mpDataModel->getModel());

  mpRi->initFromReaction(reaction);

  // update the widget.
  FillWidgetFromRI();

  return true; //TODO: really check
}

bool ReactionsWidget1::saveToReaction()
{
  CReaction* reac = dynamic_cast< CReaction * >(CRootContainer::getKeyFactory()->get(mKey));

  if (reac == NULL) return true;

  mpEditReactionScheme->slotForceUpdate();

  assert(mpDataModel != NULL);

  CModel * pModel = mpDataModel->getModel();

  if (pModel == NULL) return false;

  mIgnoreUpdates = true;
  bool changed = false;

  if (reac->isReversible() != mpRi->isReversible())
    {
      mpUndoStack->push(new ReactionChangeCommand(
                          CCopasiUndoCommand::REACTION_REVERSIBLE_CHANGE,
                          reac->isReversible(),
                          mpRi->isReversible(),
                          this,
                          reac,
                          FROM_UTF8(reac->getFunction()->getObjectName()),
                          FROM_UTF8(mpRi->getFunctionName())
                        ));

      changed = true;
    }

  std::string oldScheme = CChemEqInterface::getChemEqString(pModel, *reac, false);
  std::string newScheme = mpRi->getChemEqString();

  if (oldScheme != newScheme)
    {
      mpUndoStack->push(new ReactionChangeCommand(
                          CCopasiUndoCommand::REACTION_SCHEME_CHANGE,
                          FROM_UTF8(oldScheme),
                          FROM_UTF8(newScheme),
                          this,
                          reac,
                          FROM_UTF8(reac->getFunction()->getObjectName()),
                          FROM_UTF8(mpRi->getFunctionName())
                        ));

      changed = true;
    }

  if (reac->getFunction()->getObjectName() != mpRi->getFunctionName() && !mpRi->getFunctionName().empty())
    {
      mpUndoStack->push(new ReactionChangeCommand(
                          CCopasiUndoCommand::REACTION_FUNCTION_CHANGE,
                          FROM_UTF8(reac->getFunction()->getObjectName()),
                          FROM_UTF8(mpRi->getFunctionName()),
                          this,
                          reac
                        ));

      changed = true;
    }

  if (reac->getKineticLawUnitType() != mpRi->getKineticLawUnitType())
    {
      mpUndoStack->push(new ReactionChangeCommand(
                          CCopasiUndoCommand::REACTION_UNIT_CHANGE,
                          CReaction::KineticLawUnitTypeName[reac->getKineticLawUnitType()],
                          CReaction::KineticLawUnitTypeName[mpRi->getKineticLawUnitType()],
                          this,
                          reac
                        ));

      changed = true;
    }

  if ((reac->getScalingCompartment() != NULL &&
       reac->getScalingCompartment()->getObjectName() != mpRi->getScalingCompartment()) ||
      (reac->getScalingCompartment() == NULL &&
       !mpRi->getScalingCompartment().empty()))
    {
      mpUndoStack->push(new ReactionChangeCommand(
                          CCopasiUndoCommand::REACTION_SCALING_COMPARTMENT_CHANGE,
                          FROM_UTF8(reac->getScalingCompartment() != NULL ? reac->getScalingCompartment()->getObjectName() : ""),
                          FROM_UTF8(mpRi->getScalingCompartment()),
                          this,
                          reac
                        ));

      changed = true;
    }

  // Add Noise
  if (reac->hasNoise() != mpBoxAddNoise->isChecked())
    {
      mpUndoStack->push(new ReactionChangeCommand(
                          CCopasiUndoCommand::REACTION_ADD_NOISE_CHANGE,
                          reac->hasNoise(),
                          mpBoxAddNoise->isChecked(),
                          this,
                          reac
                        ));

      changed = true;
    }

  // Noise Expression
  if (reac->getNoiseExpression() != mpNoiseExpressionWidget->mpExpressionWidget->getExpression())
    {
      mpUndoStack->push(new ReactionChangeCommand(
                          CCopasiUndoCommand::REACTION_NOISE_EXPRESSION_CHANGE,
                          FROM_UTF8(reac->getNoiseExpression()),
                          FROM_UTF8(mpNoiseExpressionWidget->mpExpressionWidget->getExpression()),
                          this,
                          reac
                        ));
      changed = true;
    }

  mIgnoreUpdates = false;

  if (changed)
    {
      if (mpDataModel)
        mpDataModel->changed();

      protectedNotify(ListViews::REACTION, ListViews::CHANGE, mKey);   //Refresh all
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

  // tell the reaction interface
  //mpRi->setReactionName(rName);

  mpRi->setChemEqString(eq, "");

  // update the widget
  FillWidgetFromRI();
}

// added 5/19/04
void ReactionsWidget1::slotBtnNew()
{
  mpUndoStack->push(new CreateNewReactionCommand(this));
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
          cModelExpObj.duplicateMetab(MetabIt->getMetabolite(), "_copy", sourceObjects, origToCopyMapping);
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
          cModelExpObj.duplicateMetab(MetabIt->getMetabolite(), "_copy", sourceObjects, origToCopyMapping);
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
          cModelExpObj.duplicateMetab(MetabIt->getMetabolite(), "_copy", sourceObjects, origToCopyMapping);
        }
    }

  sourceObjects.addReaction(reac);
  cModelExpObj.duplicateReaction(reac, "_copy", sourceObjects, origToCopyMapping);

  protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, "");//Refresh all
  protectedNotify(ListViews::METABOLITE, ListViews::DELETE, ""); //Refresh all
  protectedNotify(ListViews::REACTION, ListViews::DELETE, "");   //Refresh all
  mpListView->switchToOtherWidget(C_INVALID_INDEX, origToCopyMapping.getDuplicateKey(mKey));

  pdelete(pDialog);
}

// Just added 5/18/04
void ReactionsWidget1::slotBtnDelete()
{
  mpUndoStack->push(new DeleteReactionCommand(this));
}

void ReactionsWidget1::FillWidgetFromRI()
{
  mpEditReactionScheme->setText(FROM_UTF8(mpRi->getChemEqString()));

  setFramework(mFramework);

  // the reversibility checkbox
  mpChkReversible->setChecked(false);

  if (mpRi->isReversible() == true)
    {
      mpChkReversible->setChecked(true);
    }

  mpMultiCompartment->setChecked(mpRi->isMulticompartment());

  // the function combobox
  QStringList comboEntries;
  vectorOfStrings2QStringList(mpRi->getListOfPossibleFunctions(), comboEntries);

  mpCmbRateLaw->clear();
  mpCmbRateLaw->insertItems(0, comboEntries);

  // Initialize scaling compartment combobox
  QMap<QString, QString> Compartments;

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

  mpComboBoxCompartment->blockSignals(true);
  mpComboBoxCompartment->clear();
  mpComboBoxCompartment->addItems(Compartments.values());
  mpComboBoxCompartment->setCurrentIndex(mpComboBoxCompartment->findText(FROM_UTF8(mpRi->getDefaultScalingCompartment())));
  mpComboBoxCompartment->blockSignals(false);

  // if there is a current function the parameter table is initialized
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

  // Noise Expression
  mpNoiseExpressionWidget->mpExpressionWidget->setExpression(mpRi->getNoiseExpression());
  mpNoiseExpressionWidget->updateWidget();
  mpBoxAddNoise->setChecked(mpRi->hasNoise());

#ifdef WITH_SDE_SUPPORT
  slotAddNoiseChanged(mpRi->hasNoise());
#else
  slotAddNoiseChanged(false);
#endif

  mpDefaultUnit->setChecked(mpRi->getKineticLawUnitType() == CReaction::Default);
  mpConcentrationUnit->setChecked(mpRi->getEffectiveKineticLawUnitType() == CReaction::ConcentrationPerTime);
  mpAmountUnit->setChecked(mpRi->getEffectiveKineticLawUnitType() == CReaction::AmountPerTime);

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

  mIgnoreUpdates = true;

  if (mpRi->getUsage(Index) == CFunctionParameter::PARAMETER)
    {
      if (sub != 0) return;

      if (mpRi->isLocalValue(Index))
        {
          mpUndoStack->push(
            new ReactionChangeCommand(
              CCopasiUndoCommand::REACTION_LOCAL_PARAMETER_VALUE_CHANGE,
              mpRi->getLocalValue(Index),
              newValue.toDouble(),
              this,
              reaction,
              index,
              index
            )
          );
        }
      else
        {
          QList<QVariant> list;
          list.append(index);
          list.append(mpRi->getLocalValue(Index));
          mpUndoStack->push(
            new ReactionChangeCommand(
              CCopasiUndoCommand::REACTION_MAPPING_PARAMETER_CHANGE,
              FROM_UTF8(mpRi->getMapping(Index)),
              newValue,
              this,
              reaction,
              list,
              list
            )
          );
        }

      // Run a table update, to update the mapped value, and it's
      // editing status, in the adjacent cell.
      mpParameterMapping->updateTable(*mpRi, dynamic_cast< CReaction * >(mpObject));
    }
  else if (mpRi->getUsage(Index) == CFunctionParameter::VOLUME)
    {
      if (sub != 0) return;

      mpUndoStack->push(
        new ReactionChangeCommand(
          CCopasiUndoCommand::REACTION_MAPPING_VOLUME_CHANGE,
          FROM_UTF8(mpRi->getMapping(Index)),
          newValue,
          this,
          reaction,
          index,
          index
        )
      );
    }
  else
    {
      if (sub == 0) //here we assume that vector parameters cannot be edited
        {
          //          mpRi->setMapping((int) Index, TO_UTF8(mpParameterMapping->item((int) mpParameterMapping->mIndex2Line[index], 3)->text()));
          mpUndoStack->push(
            new ReactionChangeCommand(
              CCopasiUndoCommand::REACTION_MAPPING_SPECIES_CHANGE,
              FROM_UTF8(mpRi->getMapping(Index)),
              newValue,
              this,
              reaction,
              index,
              index
            )
          );

          mpEditReactionScheme->setText(FROM_UTF8(mpRi->getChemEqString()));
        }
    }

  mIgnoreUpdates = false;

  if (mpDataModel != NULL) mpDataModel->changed();

  protectedNotify(ListViews::REACTION, ListViews::CHANGE, mKey);

  // if we don't stop here, we loose changes!
  // instead just prevent updating, that way the user has a chance to correct the reaction,
  // only if the user selects another reaction (or somehow else leaves the editing,
  // the changes will be lost)
  //
  if (!mpRi->isValid())
    return;

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
  CReaction * pReaction =
    dynamic_cast< CReaction * >(CRootContainer::getKeyFactory()->get(mKey));

  if (pReaction == NULL) return;

  const CFunction * pFunc = pReaction->getFunction();

  if (pFunc == NULL) return;

  mpListView->switchToOtherWidget(C_INVALID_INDEX, pFunc->getKey());
}

void ReactionsWidget1::slotNewFunction()
{
  // FunctionWidget1 * fw = new FunctionWidget1(NULL);
  // fw->show();
  // TODO: we could think about calling the function widget as a dialogue here...

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
  protectedNotify(ListViews::FUNCTION, ListViews::ADD, pFunc->getKey());

  mpListView->switchToOtherWidget(C_INVALID_INDEX, pFunc->getKey());
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
      mpRi->setKineticLawUnitType(CReaction::Default);
      mpComboBoxCompartment->setCurrentIndex(mpComboBoxCompartment->findText(FROM_UTF8(mpRi->getDefaultScalingCompartment())));
      slotConcentrationUnitChecked(mpRi->getEffectiveKineticLawUnitType() == CReaction::ConcentrationPerTime);
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

  if (mpRi->getKineticLawUnitType() != CReaction::Default)
    {
      mpRi->setKineticLawUnitType(checked ? CReaction::ConcentrationPerTime : CReaction::AmountPerTime);
    }

  mpParameterMapping->updateTable(*mpRi, dynamic_cast< CReaction * >(mpObject));
}

void ReactionsWidget1::slotAmountUnitChecked(const bool & checked)
{
  mpConcentrationUnit->setChecked(!checked);
  mpAmountUnit->setChecked(checked);
  mpComboBoxCompartment->setEnabled(!checked && !mpDefaultUnit->isChecked());

  if (mpRi->getKineticLawUnitType() != CReaction::Default)
    {
      mpRi->setKineticLawUnitType(checked ? CReaction::AmountPerTime : CReaction::ConcentrationPerTime);
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

bool ReactionsWidget1::update(ListViews::ObjectType objectType,
                              ListViews::Action action, const std::string & key)
{

  switch (objectType)
    {
      case ListViews::MODEL:

        // For a new model we need to remove references to no longer existing reaction
        if (action == ListViews::ADD)
          {
            mKey = "";
            mpObject = NULL;
            mpRi = NULL;
          }

        break;

      case ListViews::REACTION:

        // If the currently displayed reaction is deleted we need to remove its references.
        if (action == ListViews::DELETE && mKey == key)
          {
            mKey = "";
            mpObject = NULL;
            mpRi = NULL;
          }

        break;

      case ListViews::STATE:
      case ListViews::METABOLITE:
      case ListViews::COMPARTMENT:
        break;

      default:
        return true;
        break;
    }

  if (isVisible() && !mIgnoreUpdates)
    loadFromReaction(dynamic_cast< CReaction * >(CRootContainer::getKeyFactory()->get(mKey)));

  return true;
}

bool ReactionsWidget1::leave()
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

  mpListView->switchToOtherWidget(114, "");
  return false;
}

void ReactionsWidget1::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  const CReaction * pReaction = dynamic_cast< CReaction * >(CRootContainer::getKeyFactory()->get(mKey));

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
          mpEditFlux->setText(QString::number(pReaction->getFlux(), 'g', 10));

        break;

      case 1:
        Units = " [" + ((pModel != NULL) ? FROM_UTF8(CUnit::prettyPrint("1/(" + pModel->getTimeUnit() + ")")) : "?") + "]";
        TextLabel8->setText("Number Flux" + Units);

        if (pReaction != NULL)
          mpEditFlux->setText(QString::number(pReaction->getParticleFlux(), 'g', 10));

        break;
    }
}

//Undo methods
void ReactionsWidget1::createNewReaction()
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  std::string name = "reaction_1";
  size_t i = 1;

  while (!pModel->createReaction(name))
    {
      i++;
      name = "reaction_";
      name += TO_UTF8(QString::number(i));
    }

  std::string key = pModel->getReactions()[name].getKey();
  protectedNotify(ListViews::REACTION, ListViews::ADD, key);

  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void ReactionsWidget1::deleteReaction()
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  CReaction * pReaction =
    dynamic_cast< CReaction * >(CRootContainer::getKeyFactory()->get(mKey));

  if (pReaction == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "reaction",
                                FROM_UTF8(pReaction->getObjectName()),
                                pReaction);

  switch (choice)
    {
      case QMessageBox::Ok:                                                     // Yes or Enter
      {
        pModel->removeReaction(mKey);

        mpRi->setFunctionWithEmptyMapping("");

        protectedNotify(ListViews::REACTION, ListViews::DELETE, mKey);
        protectedNotify(ListViews::REACTION, ListViews::DELETE, "");//Refresh all as there may be dependencies.
        mpListView->switchToOtherWidget(CCopasiUndoCommand::REACTIONS, "");
        break;
      }

      default:                                                     // No or Escape
        break;
    }
}

void ReactionsWidget1::addReaction(std::string & reaObjectName, CReactionInterface *pRi)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  CReaction *pRea = pModel->createReaction(reaObjectName);
  std::string key = pRea->getKey();
  protectedNotify(ListViews::REACTION, ListViews::ADD, key);
  pRi->writeBackToReaction(pRea);

  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void ReactionsWidget1::deleteReaction(UndoReactionData *pReactionData)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  std::string key = pReactionData->getKey();
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
  pModel->removeReaction(key);

  if (mpRi != NULL) mpRi->setFunctionWithEmptyMapping("");

  protectedNotify(ListViews::REACTION, ListViews::DELETE, key);
  protectedNotify(ListViews::REACTION, ListViews::DELETE, "");//Refresh all as there may be dependencies.

  switchToWidget(CCopasiUndoCommand::REACTIONS);
}

bool ReactionsWidget1::changeReaction(
  const std::string &key,
  CCopasiUndoCommand::Type type,
  const QVariant &newValue,
  const QVariant &newSecondValue,
  ReactionChangeCommand* command)
{
  if (!mIgnoreUpdates)
    {
      mKey = key;
      mpObject = CRootContainer::getKeyFactory()->get(key);
      loadFromReaction(dynamic_cast<CReaction*>(mpObject));

      mpListView->switchToOtherWidget(C_INVALID_INDEX, mKey);
    }

  CReaction* pReaction = dynamic_cast<CReaction*>(mpObject);

  if (pReaction == NULL)
    return false;

  switch (type)
    {
      case CCopasiUndoCommand::REACTION_SCHEME_CHANGE:
      {

        // remove old, no longer referred to objects
        std::vector<std::string> previouslyCreatedObjects =
          command->getCreatedObjects();

        bool deletedObjects = false;

        if (!previouslyCreatedObjects.empty())
          {

            mpRi->clearChemEquation();
            pReaction->cleanup();
            pReaction->compile();

            deletedObjects = ReactionChangeCommand::removeCreatedObjects(previouslyCreatedObjects, false);
          }

        // set new
        mpRi->setChemEqString(
          TO_UTF8(newValue.toString()),
          TO_UTF8(newSecondValue.toString()));

        // create new objects
        std::vector<std::string> createdObjects;
        bool createdMetabs = mpRi->createMetabolites(createdObjects);
        
        bool notifyNeeded = mpRi->createOtherObjects(createdObjects) 
          || createdMetabs
          || deletedObjects;
        
        command->setCreatedObjects(createdObjects);

        mpRi->writeBackToReaction(pReaction);

        if (notifyNeeded)
        {
          bool oldNotify = mIgnoreUpdates;
          mIgnoreUpdates = false;
          protectedNotify(ListViews::MODEL, ListViews::CHANGE, "");
          mIgnoreUpdates = oldNotify;
        }


        break;
      }

      case CCopasiUndoCommand::REACTION_FAST_CHANGE:
        pReaction->setFast(newValue.toBool());
        break;

      case CCopasiUndoCommand::REACTION_REVERSIBLE_CHANGE:
        mpRi->setReversibility(
          newValue.toBool(),
          TO_UTF8(newSecondValue.toString()));
        mpRi->writeBackToReaction(pReaction);
        break;

      case CCopasiUndoCommand::REACTION_FUNCTION_CHANGE:
        mpRi->setFunctionAndDoMapping(TO_UTF8(newValue.toString()));
        mpRi->writeBackToReaction(pReaction);
        break;

      case CCopasiUndoCommand::REACTION_UNIT_CHANGE:
        mpRi->setKineticLawUnitType(toEnum(newValue.toByteArray().data(), CReaction::KineticLawUnitTypeName, CReaction::Default));
        mpRi->writeBackToReaction(pReaction);
        break;

      case CCopasiUndoCommand::REACTION_SCALING_COMPARTMENT_CHANGE:
        mpRi->setScalingCompartment(TO_UTF8(newValue.toString()));
        mpRi->writeBackToReaction(pReaction);
        break;

      case CCopasiUndoCommand::REACTION_LOCAL_PARAMETER_VALUE_CHANGE:
        mpRi->setLocalValue(newSecondValue.toInt(), newValue.toDouble());
        mpRi->writeBackToReaction(pReaction);
        break;

      case CCopasiUndoCommand::REACTION_MAPPING_PARAMETER_CHANGE:
      {
        QList<QVariant> list = newSecondValue.toList();
        mpRi->setMapping(list.at(0).toInt(), TO_UTF8(newValue.toString()));

        if (newValue.toString() == "unknown")
          {
            mpRi->setLocal(list.at(0).toInt());
            mpRi->setLocalValue(list.at(0).toInt(), list.at(1).toDouble());
          }

        mpRi->writeBackToReaction(pReaction);
        break;
      }

      case CCopasiUndoCommand::REACTION_MAPPING_VOLUME_CHANGE:

//    mpRi->setMapping(newSecondValue.toInt(), TO_UTF8(newValue.toString()));
//    mpRi->writeBackToReaction(pReaction);
//    break;
      case CCopasiUndoCommand::REACTION_MAPPING_SPECIES_CHANGE:
        mpRi->setMapping(newSecondValue.toInt(), TO_UTF8(newValue.toString()));
        mpRi->writeBackToReaction(pReaction);
        break;

      case CCopasiUndoCommand::REACTION_ADD_NOISE_CHANGE:
        mpRi->setHasNoise(newValue.toBool());
        pReaction->setHasNoise(newValue.toBool());
        break;

      case CCopasiUndoCommand::REACTION_NOISE_EXPRESSION_CHANGE:
        mpRi->setNoiseExpression(TO_UTF8(newValue.toString()));
        pReaction->setNoiseExpression(TO_UTF8(newValue.toString()));
        break;

      default:
        break;
    }

  if (mIgnoreUpdates) return true;

  assert(mpDataModel != NULL);
  mpDataModel->changed();
  protectedNotify(ListViews::REACTION, ListViews::CHANGE, mKey);

  FillWidgetFromRI();

  return true;
}

void ReactionsWidget1::addReaction(UndoReactionData *pData)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  CDataObject *pReaction = pData->restoreObjectIn(pModel);

  if (pReaction == NULL)
    return;

  protectedNotify(ListViews::REACTION, ListViews::ADD, pReaction->getKey());

  mpListView->switchToOtherWidget(C_INVALID_INDEX, pReaction->getKey());
}
