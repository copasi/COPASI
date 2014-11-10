// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QtGui/QWidget>

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

#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "function/CFunctionDB.h"
#include "function/CFunctionParameters.h"
#include "function/CFunctionParameter.h"
#include "report/CKeyFactory.h"
#include "model/CModelExpansion.h"    //for Copy button and options

//UNDO framework
#ifdef COPASI_UNDO
#include "undoFramework/DeleteReactionCommand.h"
#include "undoFramework/CreateNewReactionCommand.h"
#include "undoFramework/ReactionLineEditChangedCommand.h"
#include "copasiui3window.h"
#endif
/*
 *  Constructs a ReactionsWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */

ReactionsWidget1::ReactionsWidget1(QWidget *parent, const char * name, Qt::WFlags f)
  : CopasiWidget(parent, name, f),
    mpRi(NULL)
{
  setupUi(this);

  if (!name)
    setObjectName("ReactionsWidget1");

  setWindowTitle(trUtf8("ReactionsWidget1"));

  LineEdit2->setValidator(new ChemEqValidator(LineEdit2));

#ifndef COPASI_DEBUG
  mpFast->hide();
#endif

#ifdef COPASI_UNDO
  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  setUndoStack(pWindow->getUndoStack());
#endif
}

ReactionsWidget1::~ReactionsWidget1()
{}

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
  mpRi = new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel());

  mpRi->initFromReaction(reaction->getKey());

  // update the widget.
  FillWidgetFromRI();

  mpFast->setChecked(reaction->isFast());

  return true; //TODO: really check
}

bool ReactionsWidget1::saveToReaction()
{
  CReaction* reac = dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (reac == NULL) return true;

  if (!LineEdit2->isValid()) return false;

  LineEdit2->slotForceUpdate();

  if (!mpRi->isValid()) return false;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return false;

  if (reac->isFast() != mpFast->isChecked())
    {
      reac->setFast(mpFast->isChecked());
    }

  // Before we save any changes we must check whether any local reaction parameters,
  // which are used in any mathematical expression in the model are removed.
  // If that is the case the user must have option to cancel the changes or remove the
  // affected expressions.
  std::set< const CCopasiObject * > DeletedParameters = mpRi->getDeletedParameters();

  if (DeletedParameters.size() != 0)
    {
      QString ObjectType = "parameter(s)";
      QString Objects;

      std::set< const CCopasiObject * >::const_iterator itParameter, endParameter = DeletedParameters.end();
      std::set< const CCopasiObject * > DeletedObjects;

      for (itParameter = DeletedParameters.begin(); itParameter != endParameter; ++itParameter) //all parameters
        {
          Objects.append(FROM_UTF8((*itParameter)->getObjectName()) + ", ");
          DeletedObjects.insert(static_cast< const CCopasiObject * >((*itParameter)->getObject(CCopasiObjectName("Reference=Value"))));
        }

      Objects.remove(Objects.length() - 2, 2);

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(NULL, ObjectType,
                                    Objects, DeletedObjects);

      switch (choice)
        {
          case QMessageBox::Ok:

            for (itParameter = DeletedParameters.begin(); itParameter != endParameter; ++itParameter) //all parameters
              pModel->removeLocalReactionParameter((*itParameter)->getKey());

            protectedNotify(ListViews::REACTION, ListViews::DELETE, "");
            break;

          default:
            return true;
            break;
        }
    }

  // We need to check whether the current reaction still exists, since it is possible that
  // removing a local reaction parameter triggers its deletion.
  reac = dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (reac == NULL)
    {
      mpRi->setFunctionWithEmptyMapping("");

      protectedNotify(ListViews::REACTION, ListViews::DELETE, mKey);
      protectedNotify(ListViews::REACTION, ListViews::DELETE, ""); //Refresh all as there may be dependencies.
      return true;
    }

  //first check if new metabolites need to be created
  bool createdMetabs = mpRi->createMetabolites();
  bool createdObjects = mpRi->createOtherObjects();

  //this writes all changes to the reaction
  mpRi->writeBackToReaction(reac);

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  //(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->compile();

  //this tells the gui what it needs to know.
  if (createdObjects)
    protectedNotify(ListViews::MODEL, ListViews::CHANGE, "");
  else
    {
      if (createdMetabs) protectedNotify(ListViews::METABOLITE, ListViews::ADD, "");

      // :TODO Bug 322: This should only be called when actual changes have been saved.
      if (!this->isHidden())
        protectedNotify(ListViews::REACTION, ListViews::CHANGE, mKey);
    }

  //TODO: detect rename events (mpRi->writeBackToReaction has to do this)

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  if (!this->isHidden())
    (*CCopasiRootContainer::getDatamodelList())[0]->changed();

  return true;
}

void ReactionsWidget1::slotCheckBoxClicked()
{
  LineEdit2->slotForceUpdate();

  // tell the reaction interface
  mpRi->setReversibility(CheckBox->isChecked(), "");

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
#ifdef COPASI_UNDO
  mpUndoStack->push(new ReactionLineEditChangedCommand(this));
#else
  //std::string rName = TO_UTF8(LineEdit1->text());

  std::string eq = TO_UTF8(LineEdit2->text());

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
#endif
}

// added 5/19/04
void ReactionsWidget1::slotBtnNew()
{
#ifdef COPASI_UNDO
  mpUndoStack->push(new CreateNewReactionCommand(this));
#else
  std::string name = "reaction_1";
  size_t i = 1;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  while (!pDataModel->getModel()->createReaction(name))
    {
      i++;
      name = "reaction_";
      name += TO_UTF8(QString::number(i));
    }

  std::string key = pDataModel->getModel()->getReactions()[name]->getKey();
  protectedNotify(ListViews::REACTION, ListViews::ADD, key);
//  enter(key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
#endif
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
  CCopasiVectorNS< CCompartment > & Compartments = pModel->getCompartments();

  CCopasiVectorN< CCompartment >::const_iterator Compartment_it = Compartments.begin();
  CCopasiVectorN< CCompartment >::const_iterator end = Compartments.end();
  QStringList SelectionList;

  // Collect and load list of compartment names in comboBox
  for (; Compartment_it != end; ++Compartment_it)
    {
      SelectionList.append(FROM_UTF8((*Compartment_it)->getObjectName()));
    }

  pDialog->setSelectionList(SelectionList);

  const CCompartment * origCompartment = NULL;
  // to use here, and for testing if compartment changed after executing the dialog
  int origCompartmentIndex;

  CCopasiVector< CChemEqElement >::const_iterator MetabIt;

  const CCopasiVector< CChemEqElement > & substratesToCopy = reac->getChemEq().getSubstrates();

  for (MetabIt = substratesToCopy.begin(); MetabIt != substratesToCopy.end(); MetabIt++)
    {
      pDialog->setWindowTitle("Create copy of " + FROM_UTF8((*MetabIt)->getMetabolite()->getObjectName()) + "?");
      origCompartment = (*MetabIt)->getMetabolite()->getCompartment();
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
              origToCopyMapping.add(origCompartment, *(Compartment_it + pDialog->mpSelectionBox->currentIndex()));
            }

          sourceObjects.addMetab((*MetabIt)->getMetabolite());
          cModelExpObj.duplicateMetab((*MetabIt)->getMetabolite(), "_copy", sourceObjects, origToCopyMapping);
        }
    }

  const CCopasiVector< CChemEqElement > & productsToCopy = reac->getChemEq().getProducts();

  for (MetabIt = productsToCopy.begin(); MetabIt != productsToCopy.end(); MetabIt++)
    {
      pDialog->setWindowTitle("Create copy of " + FROM_UTF8((*MetabIt)->getMetabolite()->getObjectName()) + "?");
      origCompartment = (*MetabIt)->getMetabolite()->getCompartment();
      origCompartmentIndex = pDialog->mpSelectionBox->findText(FROM_UTF8(origCompartment->getObjectName()));
      pDialog->mpSelectionBox->setCurrentIndex(origCompartmentIndex);

      Compartment_it = Compartments.begin();

      if (pDialog->exec() != QDialog::Rejected)
        {
          if (origCompartmentIndex != pDialog->mpSelectionBox->currentIndex())
            {
              sourceObjects.addCompartment(origCompartment);
              origToCopyMapping.add(origCompartment, *(Compartment_it + pDialog->mpSelectionBox->currentIndex()));
            }

          sourceObjects.addMetab((*MetabIt)->getMetabolite());
          cModelExpObj.duplicateMetab((*MetabIt)->getMetabolite(), "_copy", sourceObjects, origToCopyMapping);
        }
    }

  const CCopasiVector< CChemEqElement > & modifiersToCopy = reac->getChemEq().getModifiers();

  for (MetabIt = modifiersToCopy.begin(); MetabIt != modifiersToCopy.end(); MetabIt++)
    {
      pDialog->setWindowTitle("Create copy of " + FROM_UTF8((*MetabIt)->getMetabolite()->getObjectName()) + "?");
      origCompartment = (*MetabIt)->getMetabolite()->getCompartment();
      origCompartmentIndex = pDialog->mpSelectionBox->findText(FROM_UTF8(origCompartment->getObjectName()));
      pDialog->mpSelectionBox->setCurrentIndex(origCompartmentIndex);

      Compartment_it = Compartments.begin();

      if (pDialog->exec() != QDialog::Rejected)
        {
          if (origCompartmentIndex != pDialog->mpSelectionBox->currentIndex())
            {
              sourceObjects.addCompartment(origCompartment);
              origToCopyMapping.add(origCompartment, *(Compartment_it + pDialog->mpSelectionBox->currentIndex()));
            }

          sourceObjects.addMetab((*MetabIt)->getMetabolite());
          cModelExpObj.duplicateMetab((*MetabIt)->getMetabolite(), "_copy", sourceObjects, origToCopyMapping);
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
#ifdef COPASI_UNDO
  mpUndoStack->push(new DeleteReactionCommand(this));
#else
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  CReaction * pReaction =
    dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (pReaction == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(NULL, "reaction",
                                FROM_UTF8(pReaction->getObjectName()),
                                pReaction->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:                                                     // Yes or Enter
      {
        pDataModel->getModel()->removeReaction(mKey);

        mpRi->setFunctionWithEmptyMapping("");

        protectedNotify(ListViews::REACTION, ListViews::DELETE, mKey);
        protectedNotify(ListViews::REACTION, ListViews::DELETE, "");//Refresh all as there may be dependencies.
        break;
      }

      default:                                                     // No or Escape
        break;
    }

#endif
}

void ReactionsWidget1::FillWidgetFromRI()
{
  LineEdit2->setText(FROM_UTF8(mpRi->getChemEqString()));

  setFramework(mFramework);

  // the reversibility checkbox
  CheckBox->setChecked(false);

  if (mpRi->isReversible() == true)
    {
      CheckBox->setChecked(true);
    }

  mpMultiCompartment->setChecked(mpRi->isMulticompartment());

  // the function combobox
  QStringList comboEntries;
  vectorOfStrings2QStringList(mpRi->getListOfPossibleFunctions(), comboEntries);

  ComboBox1->clear();
  ComboBox1->insertItems(0, comboEntries);

  // if there is a current function the parameter table is initialized
  if (mpRi->getFunctionName() != "")
    {
      if (comboEntries.filter(FROM_UTF8(mpRi->getFunctionName())).size() == 0)
        ComboBox1->insertItem(0, FROM_UTF8(mpRi->getFunctionName()));

      ComboBox1->setCurrentIndex(ComboBox1->findText(FROM_UTF8(mpRi->getFunctionName())));
      ComboBox1->setToolTip(FROM_UTF8(mpRi->getFunctionDescription()));

      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      table->updateTable(*mpRi, dynamic_cast< CReaction * >(mpObject));
    }
  else
    {
      ComboBox1->insertItem(0, "undefined");
      ComboBox1->setCurrentIndex(0);
      table->initTable();
    }
}

void ReactionsWidget1::slotTableChanged(int index, int sub, QString newValue)
{
  size_t Index = index;
  bool SkipFillWidget = false;

  // setValue
  if (mpRi->getUsage(Index) == CFunctionParameter::PARAMETER)
    {
      if (sub != 0) return;

      if (mpRi->isLocalValue(Index))
        {
          mpRi->setLocalValue(Index, newValue.toDouble()); // TODO: check
          SkipFillWidget = true;
        }
      else
        mpRi->setMapping(Index, TO_UTF8(newValue));
    }
  else if (mpRi->getUsage(Index) == CFunctionParameter::VOLUME)
    {
      if (sub != 0) return;

      mpRi->setMapping(Index, TO_UTF8(newValue));
    }
  else
    {
      if (sub == 0) //here we assume that vector parameters cannot be edited
        {
//          mpRi->setMapping((int) Index, TO_UTF8(table->item((int) table->mIndex2Line[index], 3)->text()));
          mpRi->setMapping((int) Index, TO_UTF8(newValue));
        }
    }

  // if we don't stop here, we loose changes!
  // instead just prevent updating, that way the user has a chance to correct the reaction,
  // only if the user selects another reaction (or somehow else leaves the editing,
  // the changes will be lost)
  //
  if (!mpRi->isValid())
    return;

  // update the widget
  int rrr = table->currentRow();
  int ccc = table->currentColumn();
  table->setCurrentCell(rrr, ccc);

  // Save changes when leaving cell
  leave();

  // Will ultimately update mpRi for updateTable and FillWidgetFromRI
  enterProtected();
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
    dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

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
  CCopasiVectorN<CFunction>& FunctionList
  = CCopasiRootContainer::getFunctionList()->loadedFunctions();
  CFunction* pFunc;

  while (FunctionList.getIndex(nname) != C_INVALID_INDEX)
    {
      i++;
      nname = name + "_";
      nname += TO_UTF8(QString::number(i));
    }

  CCopasiRootContainer::getFunctionList()->add(pFunc = new CKinFunction(nname), true);
  protectedNotify(ListViews::FUNCTION, ListViews::ADD, pFunc->getKey());

  mpListView->switchToOtherWidget(C_INVALID_INDEX, pFunc->getKey());
}

bool ReactionsWidget1::update(ListViews::ObjectType objectType,
                              ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
      case ListViews::MODEL:
      case ListViews::STATE:
      case ListViews::COMPARTMENT:
      case ListViews::METABOLITE:
        return loadFromReaction(dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey)));
        break;

      default:
        break;
    }

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

  const CReaction * pReaction = dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  const CModel * pModel = NULL;

  if (pReaction != NULL)
    pModel = dynamic_cast<const CModel *>(pReaction->getObjectAncestor("Model"));

  QString Units;

  switch (mFramework)
    {
      case 0:

        if (pModel)
          Units = FROM_UTF8(pModel->getQuantityRateUnitsDisplayString());

        if (!Units.isEmpty())
          Units = " (" + Units + ")";

        TextLabel8->setText("Flux" + Units);

        if (pReaction != NULL)
          LineEdit3->setText(QString::number(pReaction->getFlux(), 'g', 10));

        break;

      case 1:

        if (pModel)
          Units = FROM_UTF8(pModel->getFrequencyUnitsDisplayString());

        if (!Units.isEmpty())
          Units = " (" + Units + ")";

        TextLabel8->setText("Particle Flux" + Units);

        if (pReaction != NULL)
          LineEdit3->setText(QString::number(pReaction->getParticleFlux(), 'g', 10));

        break;
    }
}

//Undo methods
#ifdef COPASI_UNDO
void ReactionsWidget1::lineEditChanged()
{
  //std::string rName = TO_UTF8(LineEdit1->text());

  std::string eq = TO_UTF8(LineEdit2->text());

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
  mpListView->switchToOtherWidget(C_INVALID_INDEX, mKey);
}
void ReactionsWidget1::restoreLineEditChanged(std::string & eq, std::string &funcName)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  if (eq == "")
    {
      mpListView->switchToOtherWidget(114, "");
      CReaction *pRea = dynamic_cast< CReaction * >(mpObject);
      std::string key = pRea->getKey();
      std::string rName = pRea->getObjectName();
      pDataModel->getModel()->removeReaction(key);
      protectedNotify(ListViews::REACTION, ListViews::DELETE, key);

      //recreate empty reaction
      pDataModel->getModel()->createReaction(rName);
      std::string newKey = pDataModel->getModel()->getReactions()[rName]->getKey();
      protectedNotify(ListViews::REACTION, ListViews::ADD, newKey);

      mpListView->switchToOtherWidget(C_INVALID_INDEX, newKey);
      return;
    }

  //first check if the string is a valid equation
  if (!CChemEqInterface::isValidEq(eq))
    {
      return;  // abort further processing
    }

  CReaction *pRea = dynamic_cast< CReaction * >(mpObject);
  std::string key = pRea->getKey();
  mpRi->setChemEqString(eq, funcName);
  mpRi->writeBackToReaction(NULL);

  // update the widget
  FillWidgetFromRI();
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key); //switch to reaction widget
}

void ReactionsWidget1::createNewReaction()
{
  std::string name = "reaction_1";
  size_t i = 1;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  while (!pDataModel->getModel()->createReaction(name))
    {
      i++;
      name = "reaction_";
      name += TO_UTF8(QString::number(i));
    }

  std::string key = pDataModel->getModel()->getReactions()[name]->getKey();
  protectedNotify(ListViews::REACTION, ListViews::ADD, key);

  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void ReactionsWidget1::deleteReaction()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  CReaction * pReaction =
    dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (pReaction == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(NULL, "reaction",
                                FROM_UTF8(pReaction->getObjectName()),
                                pReaction->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:                                                     // Yes or Enter
      {
        pDataModel->getModel()->removeReaction(mKey);

        mpRi->setFunctionWithEmptyMapping("");

        protectedNotify(ListViews::REACTION, ListViews::DELETE, mKey);
        protectedNotify(ListViews::REACTION, ListViews::DELETE, "");//Refresh all as there may be dependencies.
        mpListView->switchToOtherWidget(114, "");
        break;
      }

      default:                                                     // No or Escape
        break;
    }
}

void ReactionsWidget1::deleteReaction(CReaction *pReaction)
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  std::string key = pDataModel->getModel()->getReactions()[pReaction->getObjectName()]->getKey();
  pDataModel->getModel()->removeReaction(key);
  protectedNotify(ListViews::REACTION, ListViews::DELETE, key);

  mpListView->switchToOtherWidget(114, "");
}

void ReactionsWidget1::addReaction(std::string & reaObjectName, CReactionInterface *pRi)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CReaction *pRea = pDataModel->getModel()->createReaction(reaObjectName);
  std::string key = pRea->getKey();
  protectedNotify(ListViews::REACTION, ListViews::ADD, key);
  pRi->writeBackToReaction(pRea);

  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}
#endif
