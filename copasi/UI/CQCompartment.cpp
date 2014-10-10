// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQCompartment.h"

#include "CQExpressionWidget.h"
#include "CQMessageBox.h"
#include "CQCompartmentCopyOptions.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CCompartment.h"
#include "model/CChemEqInterface.h"
#include "model/CModelExpansion.h"    //for Copy button and options
#include "model/CReactionInterface.h" //for Copy button internal reactions only
#include "function/CExpression.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiRootContainer.h"
#include "report/CCopasiContainer.h"

//UNDO framework classes
#ifdef COPASI_UNDO
#include "model/CReactionInterface.h"
#include "undoFramework/DeleteCompartmentCommand.h"
#include "undoFramework/CreateNewCompartmentCommand.h"
//#include "undoFramework/CompartmentTypeChangeCommand.h"
#include "undoFramework/UndoCompartmentData.h"
#include "undoFramework/UndoReactionData.h"
#include "undoFramework/UndoSpecieData.h"
#include "copasiui3window.h"
#endif

/*
 *  Constructs a CQCompartment which is a child of 'parent', with the
 *  name 'name'.'
 */
CQCompartment::CQCompartment(QWidget* parent, const char* name):
  CopasiWidget(parent, name),
  mItemToType(),
  mpCompartment(NULL),
  mChanged(false),
  mExpressionValid(true),
  mInitialExpressionValid(true)
{
  setupUi(this);

  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);

  mpMetaboliteTable->horizontalHeader()->hide();

  mExpressionValid = false;
  mpExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);

  mInitialExpressionValid = false;
  mpInitialExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::InitialExpression);

#ifdef COPASI_EXTUNIT
  mpLblDim->show();
  mpComboBoxDim->show();
#else
  mpLblDim->hide();
  mpComboBoxDim->hide();
#endif

#ifdef COPASI_UNDO
  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  setUndoStack(pWindow->getUndoStack());
#endif
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQCompartment::~CQCompartment()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQCompartment::slotBtnNew()
{
#ifdef COPASI_UNDO
  mpUndoStack->push(new CreateNewCompartmentCommand(this));
#else
  leave();

  std::string name = "compartment_1";
  int i = 1;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  while (!(mpCompartment = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createCompartment(name)))
    {
      i++;
      name = "compartment_";
      name += TO_UTF8(QString::number(i));
    }

  std::string key = mpCompartment->getKey();

  protectedNotify(ListViews::COMPARTMENT, ListViews::ADD, key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);

#endif
}

void CQCompartment::copy()
{
  CModel * pModel = mpDataModel->getModel();
  CModelExpansion cModelExpObj = CModelExpansion(pModel);
  CModelExpansion::SetOfModelElements compartmentObjectsToCopy;
  CModelExpansion::ElementsMap origToCopyMappings;

  CQCompartmentCopyOptions * pDialog = new CQCompartmentCopyOptions(this);
  pDialog->exec();

  bool success = false;

  switch (pDialog->result())
    {
      case QDialog::Rejected:
        break;

      case CQCompartmentCopyOptions::COMP:      //compartment only

        compartmentObjectsToCopy.addObject(mpObject);
        success = true;
        break;

      case CQCompartmentCopyOptions::SPECIES: // include the species
      {
        compartmentObjectsToCopy.addObject(mpObject);
        CCopasiVectorNS < CMetab > & Metabolites = mpCompartment->getMetabolites();
        CCopasiVectorNS < CMetab >::const_iterator itMetab;

        for (itMetab = Metabolites.begin(); itMetab != Metabolites.end(); ++itMetab)
          {
            compartmentObjectsToCopy.addMetab(*itMetab);
          }
      }
      success = true;
      break;

      case CQCompartmentCopyOptions::INTREAC:    //also include the internal reactions
      {
        compartmentObjectsToCopy.addObject(mpObject);

        // Get all the compartment's species first
        CCopasiVectorNS < CMetab > & Metabolites = mpCompartment->getMetabolites();
        CCopasiVectorNS < CMetab >::const_iterator itMetab;

        for (itMetab = Metabolites.begin(); itMetab != Metabolites.end(); ++itMetab)
          {
            compartmentObjectsToCopy.addMetab(*itMetab);
          }

        // Now get the reactions which are not multi-compartment
        CCopasiVectorN< CReaction >::const_iterator it = pModel->getReactions().begin();
        CCopasiVectorN< CReaction >::const_iterator end = pModel->getReactions().end();
        CReactionInterface * pRi = new CReactionInterface(pModel);

        for (; it != end; ++it)
          {
            pRi->initFromReaction((*it)->getKey());

            if (!pRi->isMulticompartment())
              {
                if (pRi->getChemEqInterface().getCompartment()->getKey() == mKey)
                  compartmentObjectsToCopy.addReaction(*it);
              }
          }

        pdelete(pRi);
        success = true;
        break;
      }

      case CQCompartmentCopyOptions::ALLREAC:    //get everything in compartment

        compartmentObjectsToCopy.addObject(mpObject);
        compartmentObjectsToCopy.fillDependencies(pModel);
        success = true;
        break;
    }

  pdelete(pDialog);

  if (success)
    {
      cModelExpObj.duplicate(compartmentObjectsToCopy, "_copy", origToCopyMappings);

      protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, "");//Refresh all
      protectedNotify(ListViews::METABOLITE, ListViews::DELETE, ""); //Refresh all
      protectedNotify(ListViews::REACTION, ListViews::DELETE, "");   //Refresh all
      mpListView->switchToOtherWidget(C_INVALID_INDEX, origToCopyMappings.getDuplicateKey(mKey));
    }
}

void CQCompartment::slotBtnDelete()
{
#ifdef COPASI_UNDO
  mpUndoStack->push(new DeleteCompartmentCommand(this));
#else
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return;

  if (mpCompartment == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "compartment",
                                FROM_UTF8(mpCompartment->getObjectName()),
                                mpCompartment->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        pDataModel->getModel()->removeCompartment(mKey);

        protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, mKey);
        protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, ""); //Refresh all as there may be dependencies.
        break;
      }

      default:
        break;
    }

#endif
}

/*!
    If the simulation type is changed then COPASI will automatically adjust its appearance,
    especially correlating to the Expression Widget and its buttons.
 */
void CQCompartment::slotTypeChanged(int type)
{
  QString Units;

  const CModel * pModel = NULL;

  if (mpCompartment != NULL)
    pModel = dynamic_cast<const CModel *>(mpCompartment->getObjectAncestor("Model"));

  switch ((CModelEntity::Status) mItemToType[type])
    {
      case CModelEntity::FIXED:
        mpLblExpression->hide();
        mpExpressionEMW->hide();

        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());
        break;

      case CModelEntity::ASSIGNMENT:

        if (pModel)
          Units = FROM_UTF8(pModel->getVolumeUnitsDisplayString());

        if (!Units.isEmpty())
          Units = " (" + Units + ")";

        mpLblExpression->setText("Expression" + Units);

        mpLblExpression->show();
        mpExpressionEMW->show();

        mpBoxUseInitialExpression->setEnabled(false);
        slotInitialTypeChanged(false);

        mpExpressionEMW->updateWidget();
        break;

      case CModelEntity::ODE:

        if (pModel)
          Units = FROM_UTF8(pModel->getVolumeRateUnitsDisplayString());

        if (!Units.isEmpty())
          Units = " (" + Units + ")";

        mpLblExpression->setText("Expression" + Units);

        mpLblExpression->show();
        mpExpressionEMW->show();

        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

        mpExpressionEMW->updateWidget();

        break;

      default:
        break;
    }
}

/*!
    This function is used in case of not FIXED type
 */
void CQCompartment::slotInitialTypeChanged(bool useInitialAssignment)
{
  if (useInitialAssignment)
    {
      mpLblInitialExpression->show();
      mpInitialExpressionEMW->show();

      mpEditInitialVolume->setEnabled(false);
      mpInitialExpressionEMW->updateWidget();
    }
  else
    {
      mpLblInitialExpression->hide();
      mpInitialExpressionEMW->hide();

      mpEditInitialVolume->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::ASSIGNMENT);
    }
}

/*!
 */

void CQCompartment::slotExpressionValid(bool valid)
{
  mExpressionValid = valid;
}

void CQCompartment::slotInitialExpressionValid(bool valid)
{
  mInitialExpressionValid = valid;
}

bool CQCompartment::enterProtected()
{
  mpCompartment = dynamic_cast< CCompartment * >(mpObject);

  load();

  return true;
}

bool CQCompartment::leave()
{
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::FIXED)
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

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  const CModel * pModel = NULL;

  if (mpCompartment != NULL)
    pModel = dynamic_cast<const CModel *>(mpCompartment->getObjectAncestor("Model"));

  // Update the labels to reflect the model units
  QString ValueUnits;

  if (pModel)
    ValueUnits = FROM_UTF8(pModel->getVolumeUnitsDisplayString());

  if (!ValueUnits.isEmpty())
    ValueUnits = " (" + ValueUnits + ")";

  QString RateUnits;

  if (pModel)
    RateUnits = FROM_UTF8(pModel->getVolumeRateUnitsDisplayString());

  if (!RateUnits.isEmpty())
    RateUnits = " (" + RateUnits + ")";

  mpLblInitialValue->setText("Initial Volume" + ValueUnits);
  mpLblInitialExpression->setText("Initial Expression" + ValueUnits);
  mpLblVolume->setText("Volume" + ValueUnits);
  mpLblRate->setText("Rate" + RateUnits);

  //Dimensionality
  mpComboBoxDim->setCurrentIndex(mpCompartment->getDimensionality());
  //this assumes the indices of the entries in the combobox correspond 1to1 to the values of dimensionality

  // Simulation Type
  mpComboBoxType->setCurrentIndex(mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[mpCompartment->getStatus()])));

  // Initial Volume
  mpEditInitialVolume->setText(QString::number(mpCompartment->getInitialValue(), 'g', 10));

  // Transient Volume
  mpEditCurrentVolume->setText(QString::number(mpCompartment->getValue(), 'g', 10));

  // Concentration Rate
  mpEditRate->setText(QString::number(mpCompartment->getRate(), 'g', 10));

  // Expression
  mpExpressionEMW->mpExpressionWidget->setExpression(mpCompartment->getExpression());
  mpExpressionEMW->updateWidget();

  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpCompartment->getInitialExpression());
  mpInitialExpressionEMW->updateWidget();

  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentIndex());

  // Use Initial Expression
  if (mpCompartment->getStatus() == CModelEntity::ASSIGNMENT ||
      mpCompartment->getInitialExpression() == "")
    {
      mpBoxUseInitialExpression->setChecked(false);
    }
  else
    {
      mpBoxUseInitialExpression->setChecked(true);
    }

  loadMetaboliteTable();

  mChanged = false;
  return;
}

void CQCompartment::save()
{

  if (mpCompartment == NULL) return;

#ifdef COPASI_EXTUNIT

  //Dimensionality
  if ((C_INT32)mpCompartment->getDimensionality() != mpComboBoxDim->currentIndex()) //this makes assumptions about the order of entries in the combo box!
    {
      mpCompartment->setDimensionality(mpComboBoxDim->currentIndex());
      mChanged = true;
    }

#endif

  // Type
  if (mpCompartment->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()])
    {
      mpCompartment->setStatus((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()]);
      mChanged = true;
    }

  // Initial Volume
  if (QString::number(mpCompartment->getInitialValue(), 'g', 10) != mpEditInitialVolume->text())
    {
      mpCompartment->setInitialValue(mpEditInitialVolume->text().toDouble());
      mChanged = true;
    }

  // Expression
  if (mpCompartment->getExpression() != mpExpressionEMW->mpExpressionWidget->getExpression())
    {
      mpCompartment->setExpression(mpExpressionEMW->mpExpressionWidget->getExpression());
      mChanged = true;
    }

  // Initial Expression
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::ASSIGNMENT)
    {
      if (mpBoxUseInitialExpression->isChecked() &&
          mpCompartment->getInitialExpression() != mpInitialExpressionEMW->mpExpressionWidget->getExpression())
        {
          mpCompartment->setInitialExpression(mpInitialExpressionEMW->mpExpressionWidget->getExpression());
          mChanged = true;
        }
      else if (!mpBoxUseInitialExpression->isChecked() &&
               mpCompartment->getInitialExpression() != "")
        {
          mpCompartment->setInitialExpression("");
          mChanged = true;
        }
    }

  if (mChanged)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      (*CCopasiRootContainer::getDatamodelList())[0]->changed();
      protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, mKey);
    }

  mChanged = false;
}

void CQCompartment::destroy()
{}

void CQCompartment::slotMetaboliteTableCurrentChanged(int row, int col)
{
  if (mpCompartment == NULL) return;

  QTableWidgetItem * pItem = mpMetaboliteTable->item(row, col);

  std::string s1, s2;
  s1 = TO_UTF8(pItem->text());

  CCopasiContainer::objectMap::const_iterator it =
    mpCompartment->getMetabolites().getObjects().begin();
  CCopasiContainer::objectMap::const_iterator end =
    mpCompartment->getMetabolites().getObjects().end();

  for (; it != end; ++it)
    if (dynamic_cast< CMetab * >(it->second) != NULL)
      {
        s2 = it->second->getObjectName();

        if (s1 == s2)
          mpListView->switchToOtherWidget(C_INVALID_INDEX, it->second->getKey());
      }
}

void CQCompartment::loadMetaboliteTable()
{
  if (mpCompartment == NULL) return;

  mpMetaboliteTable->setRowCount(mpCompartment->getMetabolites().size());

  CCopasiContainer::objectMap::const_iterator it =
    mpCompartment->getMetabolites().getObjects().begin();
  CCopasiContainer::objectMap::const_iterator end =
    mpCompartment->getMetabolites().getObjects().end();

  for (int i = 0; it != end; ++it)
    {
      if (dynamic_cast< CMetab * >(it->second) != NULL)
        {
          mpMetaboliteTable->setItem(i++, 0, new QTableWidgetItem(FROM_UTF8(it->second->getObjectName())));
        }
    }

  mpMetaboliteTable->resizeRowsToContents();

  return;
}

//Undo methods
#ifdef COPASI_UNDO

void CQCompartment::createNewCompartment()
{
  leave();

  std::string name = "compartment_1";
  int i = 1;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  while (!(mpCompartment = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createCompartment(name)))
    {
      i++;
      name = "compartment_";
      name += TO_UTF8(QString::number(i));
    }

  std::string key = mpCompartment->getKey();

  protectedNotify(ListViews::COMPARTMENT, ListViews::ADD, key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQCompartment::deleteCompartment()
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return;

  if (mpCompartment == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "compartment",
                                FROM_UTF8(mpCompartment->getObjectName()),
                                mpCompartment->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        pDataModel->getModel()->removeCompartment(mKey);

        protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, mKey);
        protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, ""); //Refresh all as there may be dependencies.
        break;
      }

      default:
        break;
    }

  mpListView->switchToOtherWidget(111, "");
}

void CQCompartment::deleteCompartment(UndoCompartmentData *pCompartmentData)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  CCompartment * pCompartment = pModel->getCompartments()[pCompartmentData->getName()];
  std::string key = pCompartment->getKey();
  pModel->removeCompartment(key);
  mpCompartment = NULL;

#undef DELETE
  protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, key);
  protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, "");//Refresh all as there may be dependencies.

  mpListView->switchToOtherWidget(111, "");
}

void CQCompartment::addCompartment(UndoCompartmentData *pSData)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  //reinsert all the Compartments
  CCompartment *pCompartment =  pModel->createCompartment(pSData->getName());
  pCompartment->setInitialValue(pSData->getInitialValue());
  pCompartment->setStatus(pSData->getStatus());
  std::string key = pCompartment->getKey();
  protectedNotify(ListViews::COMPARTMENT, ListViews::ADD, key);

  //restore all the dependencies
  //reinsert all the species
  QList <UndoSpecieData *> *pSpecieData = pSData->getSpecieDependencyObjects();
  QList <UndoSpecieData *>::const_iterator i;

  for (i = pSpecieData->begin(); i != pSpecieData->end(); ++i)
    {
      UndoSpecieData * data = *i;
      //  beginInsertRows(QModelIndex(), 1, 1);
      CMetab *pSpecie =  pModel->createMetabolite(data->getName(), data->getCompartment(), data->getIConc(), data->getStatus());
      protectedNotify(ListViews::METABOLITE, ListViews::ADD, pSpecie->getKey());
      //endInsertRows();
    }

  //reinsert the dependency reaction
  QList <UndoReactionData *> *pReactionData = pSData->getReactionDependencyObjects();
  QList <UndoReactionData *>::const_iterator j;

  for (j = pReactionData->begin(); j != pReactionData->end(); ++j)
    {

      //UndoReactionData * rData = dynamic_cast<UndoReactionData*>(*j);
      UndoReactionData * rData = *j;

      //TODO check if reaction already exist in the model, better idea may be implemented in the future
      bool exist = false;

      for (int ii = 0; ii < pModel->getReactions().size(); ii++)
        {
          if (pModel->getReactions()[ii]->getObjectName() == rData->getName())
            {
              exist = true;
              ii = ii + pModel->getReactions().size() + 1; //jump out of the loop reaction exist already
            }
          else
            {
              exist = false;
            }
        }

      if (!exist)
        {
          protectedNotify(ListViews::METABOLITE, ListViews::ADD, ""); //Refresh all dependency species.
          CReaction *pRea =  pModel->createReaction(rData->getName());
          rData->getRi()->writeBackToReaction(pRea);
          protectedNotify(ListViews::REACTION, ListViews::ADD, pRea->getKey());
        }
    }

  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQCompartment::CompartmentTypeChanged(int type)
{
  ; //TODO
}
#endif
