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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQCompartment.h"
#include "copasiui3window.h"

#include "CQExpressionWidget.h"
#include "CQMessageBox.h"
#include "CQCompartmentCopyOptions.h"

#include "copasi.h"

#include "qtUtilities.h"

#include "CopasiDataModel/CDataModel.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CCompartment.h"
#include "model/CChemEqInterface.h"
#include "model/CModelExpansion.h"    //for Copy button and options
#include "model/CReactionInterface.h" //for Copy button internal reactions only
#include "function/CExpression.h"
#include "report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CDataContainer.h"

//UNDO framework classes
#include "model/CReactionInterface.h"
#include "undoFramework/DeleteCompartmentCommand.h"
#include "undoFramework/CreateNewCompartmentCommand.h"
//#include "undoFramework/CompartmentTypeChangeCommand.h"
#include "undoFramework/UndoCompartmentData.h"
#include "undoFramework/UndoReactionData.h"
#include "undoFramework/UndoSpeciesData.h"
#include "copasi/undoFramework/CompartmentChangeCommand.h"

#include "undo/CUndoStack.h"
#include "undo/CUndoData.h"

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
  mInitialExpressionValid(true),
  mValueUnits("?"),
  mRateUnits("?")
{
  setupUi(this);

  mpComboBoxType->blockSignals(true);
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ODE]));
  mpComboBoxType->blockSignals(false);

  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::FIXED));
  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::ASSIGNMENT));
  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::ODE));

  mpMetaboliteTable->horizontalHeader()->hide();

  mpExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);
  mpInitialExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::InitialExpression);
  mpNoiseExpressionWidget->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);

#ifdef COPASI_EXTUNIT
  mpLblDim->show();
  mpComboBoxDim->show();
#else
  mpLblDim->hide();
  mpComboBoxDim->hide();
#endif

  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  setUndoStack(pWindow->getUndoStack());
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
  mpUndoStack->push(new CreateNewCompartmentCommand(this));
}

void CQCompartment::slotBtnCopy() {}

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
        CDataVectorNS < CMetab > & Metabolites = mpCompartment->getMetabolites();
        CDataVectorNS < CMetab >::const_iterator itMetab;

        for (itMetab = Metabolites.begin(); itMetab != Metabolites.end(); ++itMetab)
          {
            compartmentObjectsToCopy.addMetab(itMetab);
          }
      }

      success = true;
      break;

      case CQCompartmentCopyOptions::INTREAC:    //also include the internal reactions
      {
        compartmentObjectsToCopy.addObject(mpObject);

        // Get all the compartment's species first
        CDataVectorNS < CMetab > & Metabolites = mpCompartment->getMetabolites();
        CDataVectorNS < CMetab >::const_iterator itMetab;

        for (itMetab = Metabolites.begin(); itMetab != Metabolites.end(); ++itMetab)
          {
            compartmentObjectsToCopy.addMetab(itMetab);
          }

        // Now get the reactions which are not multi-compartment
        CDataVectorN< CReaction >::const_iterator it = pModel->getReactions().begin();
        CDataVectorN< CReaction >::const_iterator end = pModel->getReactions().end();
        CReactionInterface * pRi = new CReactionInterface(pModel);

        for (; it != end; ++it)
          {
            pRi->initFromReaction(it->getKey());

            if (!pRi->isMulticompartment())
              {
                if (pRi->getChemEqInterface().getCompartment()->getKey() == mKey)
                  compartmentObjectsToCopy.addReaction(it);
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
  deleteCompartment();
}

/*!
    If the simulation type is changed then COPASI will automatically adjust its appearance,
    especially correlating to the Expression Widget and its buttons.
 */
void CQCompartment::slotTypeChanged(int type)
{
  if (mpCompartment == NULL) return;

  switch ((CModelEntity::Status) mItemToType[type])
    {
      case CModelEntity::Status::FIXED:
        mpLblExpression->hide();
        mpExpressionEMW->hide();

        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

        mpBoxAddNoise->hide();
        slotAddNoiseChanged(false);
        break;

      case CModelEntity::Status::ASSIGNMENT:
        mpLblExpression->setText("Expression" + mValueUnits);

        mpLblExpression->show();
        mpExpressionEMW->show();

        mpBoxUseInitialExpression->setEnabled(false);
        slotInitialTypeChanged(false);

        mpExpressionEMW->updateWidget();

        mpBoxAddNoise->hide();
        slotAddNoiseChanged(false);

        break;

      case CModelEntity::Status::ODE:
        mpLblExpression->setText("Expression" + mRateUnits);

        mpLblExpression->show();
        mpExpressionEMW->show();

        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

        mpExpressionEMW->updateWidget();

#ifdef WITH_SDE_SUPPORT
        mpBoxAddNoise->show();
        slotAddNoiseChanged(mpBoxAddNoise->isChecked());
#else
        mpBoxAddNoise->hide();
        slotAddNoiseChanged(false);
#endif

        break;

      default:
        break;
    }
}

void CQCompartment::slotAddNoiseChanged(bool hasNoise)
{
  if (hasNoise)
    {
      if (mpCompartment != NULL &&
          mpCompartment->getNoiseExpression().empty())
        {
          mpNoiseExpressionWidget->mpExpressionWidget->setExpression(mpCompartment->getDefaultNoiseExpression());
        }

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

      mpEditInitialVolume->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::Status::ASSIGNMENT);
    }
}

/*!
 */

bool CQCompartment::enterProtected()
{
  mpCompartment = dynamic_cast< CCompartment * >(mpObject);

  load();

  return true;
}

bool CQCompartment::leave()
{
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::Status::FIXED)
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
                           ListViews::Action action,
                           const std::string & key)
{

  switch (objectType)
    {
      case ListViews::MODEL:

        // For a new model we need to remove references to no longer existing compartment
        if (action == ListViews::ADD)
          {
            mKey = "";
            mpObject = NULL;
            mpCompartment = NULL;
          }

        break;

      case ListViews::COMPARTMENT:

        // If the currently displayed compartment is deleted we need to remove its references.
        if (action == ListViews::DELETE && mKey == key)
          {
            mKey = "";
            mpObject = NULL;
            mpCompartment = NULL;
          }

        break;

      case ListViews::STATE:
      case ListViews::METABOLITE:
        break;

      default:
        return true;
        break;
    }

  if (isVisible() && !mIgnoreUpdates)
    load();

  return true;
}

void CQCompartment::load()
{
  if (mpCompartment == NULL) return;

  //Dimensionality
  mpComboBoxDim->setCurrentIndex(mpCompartment->getDimensionality());
  // slotDimesionalityChanged(mpCompartment->getDimensionality());

  // Simulation Type
  mpComboBoxType->setCurrentIndex(mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[mpCompartment->getStatus()])));

  // Initial Volume
  mpEditInitialVolume->setText(convertToQString(mpCompartment->getInitialValue()));

  // Transient Volume
  mpEditCurrentVolume->setText(convertToQString(mpCompartment->getValue()));

  // Concentration Rate
  mpEditRate->setText(convertToQString(mpCompartment->getRate()));

  // Expression
  mpExpressionEMW->mpExpressionWidget->setExpression(mpCompartment->getExpression());
  mpExpressionEMW->updateWidget();

  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpCompartment->getInitialExpression());
  mpInitialExpressionEMW->updateWidget();

  // Noise Expression
  mpNoiseExpressionWidget->mpExpressionWidget->setExpression(mpCompartment->getNoiseExpression());
  mpNoiseExpressionWidget->updateWidget();
  mpBoxAddNoise->setChecked(mpCompartment->hasNoise());

  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentIndex());

  // Use Initial Expression
  if (mpCompartment->getStatus() == CModelEntity::Status::ASSIGNMENT ||
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

  mIgnoreUpdates = true;

  CUndoData Data(CUndoData::Type::CHANGE, mpCompartment);

#ifdef COPASI_EXTUNIT

  //Dimensionality
  if ((C_INT32)mpCompartment->getDimensionality() != mpComboBoxDim->currentIndex()) //this makes assumptions about the order of entries in the combo box!
    {
      Data.addProperty(CData::SPATIAL_DIMENSION, mpCompartment->getDimensionality(), (unsigned C_INT32) mpComboBoxDim->currentIndex());

      mpUndoStack->push(new CompartmentChangeCommand(
                          CCopasiUndoCommand::COMPARTMENT_SPATIAL_DIMENSION_CHANGE,
                          mpCompartment->getDimensionality(),
                          mpComboBoxDim->currentIndex(),
                          mpCompartment,
                          this
                        ));

      mChanged = true;
    }

#endif

  // Type
  if (mpCompartment->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()])
    {
      Data.addProperty(CData::SIMULATION_TYPE,
                       (unsigned C_INT32) mpCompartment->getStatus(),
                       (unsigned C_INT32) mItemToType[mpComboBoxType->currentIndex()]);

      QString currentTypeName = FROM_UTF8(CModelEntity::StatusName[(int)mpCompartment->getStatus()]);
      QString newTypeName = FROM_UTF8(CModelEntity::StatusName[(int)mItemToType[mpComboBoxType->currentIndex()]]);

      mpUndoStack->push(new CompartmentChangeCommand(
                          CCopasiUndoCommand::COMPARTMENT_SIMULATION_TYPE_CHANGE,
                          currentTypeName,
                          newTypeName,
                          mpCompartment,
                          this,
                          mpCompartment->getInitialValue()
                        ));

      mChanged = true;
    }

  // Initial Volume
  if (convertToQString(mpCompartment->getInitialValue()) != mpEditInitialVolume->text())
    {
      Data.addProperty(CData::INITIAL_VALUE,
                       mpCompartment->getInitialValue(),
                       mpEditInitialVolume->text().toDouble());

      mpCompartment->appendDependentData(Data, (CCore::Framework) mFramework);

      mpUndoStack->push(new CompartmentChangeCommand(
                          CCopasiUndoCommand::COMPARTMENT_INITIAL_VOLUME_CHANGE,
                          mpCompartment->getInitialValue(),
                          mpEditInitialVolume->text().toDouble(),
                          mpCompartment,
                          this
                        ));
      mChanged = true;
    }

  // Expression
  if (mpCompartment->getExpression() != mpExpressionEMW->mpExpressionWidget->getExpression())
    {
      Data.addProperty(CData::EXPRESSION,
                       mpCompartment->getExpression(),
                       mpExpressionEMW->mpExpressionWidget->getExpression());

      mpUndoStack->push(new CompartmentChangeCommand(
                          CCopasiUndoCommand::COMPARTMENT_EXPRESSION_CHANGE,
                          FROM_UTF8(mpCompartment->getExpression()),
                          FROM_UTF8(mpExpressionEMW->mpExpressionWidget->getExpression()),
                          mpCompartment,
                          this
                        ));
      mChanged = true;
    }

  // Initial Expression
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::Status::ASSIGNMENT)
    {
      if (mpBoxUseInitialExpression->isChecked() &&
          mpCompartment->getInitialExpression() != mpInitialExpressionEMW->mpExpressionWidget->getExpression())
        {
          Data.addProperty(CData::INITIAL_EXPRESSION,
                           mpCompartment->getInitialExpression(),
                           mpInitialExpressionEMW->mpExpressionWidget->getExpression());

          mpUndoStack->push(new CompartmentChangeCommand(
                              CCopasiUndoCommand::COMPARTMENT_INITIAL_EXPRESSION_CHANGE,
                              FROM_UTF8(mpCompartment->getInitialExpression()),
                              FROM_UTF8(mpInitialExpressionEMW->mpExpressionWidget->getExpression()),
                              mpCompartment,
                              this,
                              mpCompartment->getInitialValue()
                            ));

          mChanged = true;
        }
      else if (!mpBoxUseInitialExpression->isChecked() &&
               mpCompartment->getInitialExpression() != "")
        {
          Data.addProperty(CData::INITIAL_EXPRESSION,
                           mpCompartment->getInitialExpression(),
                           "");

          mpUndoStack->push(new CompartmentChangeCommand(
                              CCopasiUndoCommand::COMPARTMENT_INITIAL_EXPRESSION_CHANGE,
                              FROM_UTF8(mpCompartment->getInitialExpression()),
                              QString(""),
                              mpCompartment,
                              this
                            ));
          mChanged = true;
        }
    }

  // Add Noise
  if (mpCompartment->hasNoise() != mpBoxAddNoise->isChecked())
    {
      Data.addProperty(CData::ADD_NOISE,
                       mpCompartment->hasNoise(),
                       mpBoxAddNoise->isChecked());

      mpUndoStack->push(new CompartmentChangeCommand(
                          CCopasiUndoCommand::COMPARTMENT_ADD_NOISE_CHANGE,
                          mpCompartment->hasNoise(),
                          mpBoxAddNoise->isChecked(),
                          mpCompartment,
                          this
                        ));

      mChanged = true;
    }

  // Noise Expression
  if (mpCompartment->getNoiseExpression() != mpNoiseExpressionWidget->mpExpressionWidget->getExpression())
    {
      Data.addProperty(CData::NOISE_EXPRESSION,
                       mpCompartment->getNoiseExpression(),
                       mpNoiseExpressionWidget->mpExpressionWidget->getExpression());

      mpUndoStack->push(new CompartmentChangeCommand(
                          CCopasiUndoCommand::COMPARTMENT_NOISE_EXPRESSION_CHANGE,
                          FROM_UTF8(mpCompartment->getNoiseExpression()),
                          FROM_UTF8(mpNoiseExpressionWidget->mpExpressionWidget->getExpression()),
                          mpCompartment,
                          this
                        ));
      mChanged = true;
    }

  mIgnoreUpdates = false;

  if (mChanged)
    {
      assert(mpDataModel != NULL);

      mpDataModel->applyData(Data);
      mpDataModel->changed();
      protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, mKey);

      load();
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

  CDataContainer::objectMap::const_iterator it =
    mpCompartment->getMetabolites().getObjects().begin();
  CDataContainer::objectMap::const_iterator end =
    mpCompartment->getMetabolites().getObjects().end();

  for (; it != end; ++it)
    if (dynamic_cast< CMetab * >(*it) != NULL)
      {
        s2 = (*it)->getObjectName();

        if (s1 == s2)
          mpListView->switchToOtherWidget(C_INVALID_INDEX, (*it)->getKey());
      }
}

void CQCompartment::slotDimesionalityChanged(int dim)
{
  // Update the labels to reflect the model units
  QString Lable = "Value";
  mValueUnits = "?";
  mRateUnits = "?";

  CModel * pModel = mpCompartment->getModel();

  if (pModel != NULL)
    {
      std::string tmp;

      switch (dim)
        {
          case 0:
            Lable = "Value";
            tmp = "1";
            break;

          case 1:
            Lable = "Length";
            tmp = pModel->getLengthUnit();
            break;

          case 2:
            Lable = "Area";
            tmp = pModel->getAreaUnit();
            break;

          case 3:
            Lable = "Volume";
            tmp = pModel->getVolumeUnit();
            break;
        }

      mValueUnits = " [" + FROM_UTF8(CUnit::prettyPrint(tmp)) + "]";
      mRateUnits = " [" + FROM_UTF8(CUnit::prettyPrint(tmp + "/(" + pModel->getTimeUnit() + ")")) + "]";
    }

  mpLblInitialValue->setText("Initial " + Lable + mValueUnits);
  mpLblInitialExpression->setText("Initial Expression" + mValueUnits);
  mpLblVolume->setText(Lable + mValueUnits);
  mpLblRate->setText("Rate" + mRateUnits);
}

void CQCompartment::loadMetaboliteTable()
{
  if (mpCompartment == NULL) return;

  mpMetaboliteTable->setRowCount(mpCompartment->getMetabolites().size());

  CDataContainer::objectMap::const_iterator it =
    mpCompartment->getMetabolites().getObjects().begin();
  CDataContainer::objectMap::const_iterator end =
    mpCompartment->getMetabolites().getObjects().end();

  for (int i = 0; it != end; ++it)
    {
      if (dynamic_cast< CMetab * >(*it) != NULL)
        {
          mpMetaboliteTable->setItem(i++, 0, new QTableWidgetItem(FROM_UTF8((*it)->getObjectName())));
        }
    }

  mpMetaboliteTable->resizeRowsToContents();

  return;
}

//Undo methods
void CQCompartment::createNewCompartment()
{
  leave();

  std::string name = "compartment_1";
  int i = 1;

  assert(mpDataModel != NULL);

  while (!(mpCompartment = mpDataModel->getModel()->createCompartment(name)))
    {
      i++;
      name = "compartment_";
      name += TO_UTF8(QString::number(i));
    }

  mpDataModel->recordData(CUndoData(CUndoData::Type::INSERT, mpCompartment));
  mpDataModel->changed();

  std::string key = mpCompartment->getKey();

  protectedNotify(ListViews::COMPARTMENT, ListViews::ADD, key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQCompartment::deleteCompartment()
{
  if (mpCompartment == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "compartment",
                                FROM_UTF8(mpCompartment->getObjectName()),
                                mpCompartment);

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        mpDataModel->recordData(CUndoData(CUndoData::Type::REMOVE, mpCompartment));
        mpDataModel->changed();

        mpUndoStack->push(new DeleteCompartmentCommand(this));
        break;
      }

      default:
        break;
    }

  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);
}

void CQCompartment::deleteCompartment(UndoCompartmentData *pCompartmentData)
{
  CModel * pModel = mpCompartment != NULL ? mpCompartment->getModel()
                    : mpDataModel->getModel();

  assert(pModel != NULL);

  CCompartment* pComp = &pModel->getCompartments()[pCompartmentData->getName()];

  if (pComp == NULL) return;

  std::string key = pComp->getKey();
  pModel->removeCompartment(key);
  mpCompartment = NULL;

#undef DELETE
  protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, key);
  protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, "");//Refresh all as there may be dependencies.

  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);
}

void CQCompartment::addCompartment(UndoCompartmentData *pData)
{
  //reinsert all the Compartments
  CModel * pModel = mpCompartment != NULL ? mpCompartment->getModel()
                    : mpDataModel->getModel();
  assert(pModel != NULL);
  pData->restoreObjectIn(pModel);
  protectedNotify(ListViews::COMPARTMENT, ListViews::ADD, pData->getKey());
  switchToWidget(C_INVALID_INDEX, pData->getKey());
}

bool CQCompartment::changeValue(const std::string& key,
                                CCopasiUndoCommand::Type type,
                                const QVariant& newValue,
                                double iValue,
                                UndoCompartmentData* pUndoData)
{
  if (!mIgnoreUpdates)
    {
      mKey = key;
      mpObject = CRootContainer::getKeyFactory()->get(key);
      mpCompartment = dynamic_cast<CCompartment*>(mpObject);
      load();
      switchToWidget(C_INVALID_INDEX, mKey);
    }

  if (mpCompartment == NULL)
    return false;

  switch (type)
    {
      case CCopasiUndoCommand::COMPARTMENT_EXPRESSION_CHANGE:
        mpCompartment->setExpression(TO_UTF8(newValue.toString()));
        break;

      case CCopasiUndoCommand::COMPARTMENT_INITIAL_EXPRESSION_CHANGE:
        mpCompartment->setInitialExpression(TO_UTF8(newValue.toString()));

        if (newValue.toString().isEmpty())
          {
            mpCompartment->setInitialValue(iValue);
          }

        break;

      case CCopasiUndoCommand::COMPARTMENT_INITIAL_VOLUME_CHANGE:
        mpCompartment->setInitialValue(newValue.toDouble());

        if (pUndoData != NULL)
          {
            CModel * pModel = mpCompartment->getModel();
            assert(pModel != NULL);
            pUndoData->fillDependentObjects(pModel);
          }

        break;

      case CCopasiUndoCommand::COMPARTMENT_SIMULATION_TYPE_CHANGE:
      {
        QString newTypeName = newValue.toString();
        int index = newTypeName.length() > 1
                    ? mItemToType[mpComboBoxType->findText(newTypeName)]
                    : newValue.toInt();
        mpCompartment->setStatus((CModelEntity::Status)index);

        if (iValue == iValue
            && mpCompartment->getStatus() != CModelEntity::Status::ASSIGNMENT)
          mpCompartment->setInitialValue(iValue);

        break;
      }

      case CCopasiUndoCommand::COMPARTMENT_SPATIAL_DIMENSION_CHANGE:
        mpCompartment->setDimensionality(newValue.toInt());
        break;

      case CCopasiUndoCommand::COMPARTMENT_ADD_NOISE_CHANGE:
        mpCompartment->setHasNoise(newValue.toBool());
        break;

      case CCopasiUndoCommand::COMPARTMENT_NOISE_EXPRESSION_CHANGE:
        mpCompartment->setNoiseExpression(TO_UTF8(newValue.toString()));
        break;

      default:
        return false;
    }

  if (mIgnoreUpdates) return true;

  assert(mpDataModel != NULL);
  mpDataModel->changed();
  protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, mKey);

  load();

  return true;
}
