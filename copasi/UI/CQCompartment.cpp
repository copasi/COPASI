// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQCompartment.h"
#include "copasiui3window.h"

#include "CQExpressionWidget.h"
#include "CQMessageBox.h"
#include "CQCompartmentCopyOptions.h"

#include "copasi/copasi.h"

#include "qtUtilities.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CChemEqInterface.h"
#include "copasi/model/CModelExpansion.h"    //for Copy button and options
#include "copasi/model/CReactionInterface.h" //for Copy button internal reactions only
#include "copasi/function/CExpression.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/core/CDataContainer.h"

#include "copasi/undo/CUndoStack.h"
#include "copasi/undo/CUndoData.h"

/*
 *  Constructs a CQCompartment which is a child of 'parent', with the
 *  name 'name'.'
 */
CQCompartment::CQCompartment(QWidget* parent, const char* name):
  CopasiWidget(parent, name),
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
  leaveProtected();

  std::string name = "compartment";
  int i = 1;

  assert(mpDataModel != NULL);

  while (!(mpCompartment = mpDataModel->getModel()->createCompartment(name)))
    {
      i++;
      name = "compartment_";
      name += TO_UTF8(QString::number(i));
    }

  CUndoData UndoData(CUndoData::Type::INSERT, mpCompartment);
  ListViews::addUndoMetaData(this, UndoData);
  UndoData.addMetaDataProperty("Widget Object CN (after)", mpCompartment->getCN());
  UndoData.addMetaDataProperty("Widget Object Name (after)", mpCompartment->getObjectName());

  slotNotifyChanges(mpDataModel->recordData(UndoData));

  mpListView->switchToOtherWidget(ListViews::WidgetType::CompartmentDetail, mpCompartment->getCN());
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
        CReactionInterface * pRi = new CReactionInterface();

        for (; it != end; ++it)
          {
            pRi->init(*it);

            if (!pRi->isMulticompartment())
              {
                if (pRi->getChemEqInterface().getCompartment()->getCN() == mObjectCN)
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
      CUndoData UndoData(cModelExpObj.duplicate(compartmentObjectsToCopy, "_copy", origToCopyMappings));
      const CDataObject * pObject = origToCopyMappings.getDuplicateFromObject(mpObject);

      ListViews::addUndoMetaData(this, UndoData);
      UndoData.addMetaDataProperty("Widget Object CN (after)", pObject->getCN());
      UndoData.addMetaDataProperty("Widget Object Name (after)", pObject->getObjectName());

      slotNotifyChanges(mpDataModel->recordData(UndoData));

      if (pObject != NULL)
        {
          mpListView->switchToOtherWidget(ListViews::WidgetType::CompartmentDetail, pObject->getCN());
        }
    }
}

void CQCompartment::slotBtnDelete()
{
  if (mpCompartment == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "compartment",
                                FROM_UTF8(mpCompartment->getObjectName()),
                                mpCompartment);

  if (choice == QMessageBox::Ok)
    {
      CUndoData UndoData;
      mpCompartment->createUndoData(UndoData, CUndoData::Type::REMOVE);
      ListViews::addUndoMetaData(this, UndoData);

      slotNotifyChanges(mpDataModel->applyData(UndoData));
    }
}

/*!
    If the simulation type is changed then COPASI will automatically adjust its appearance,
    especially correlating to the Expression Widget and its buttons.
 */
void CQCompartment::slotTypeChanged(const QString & type)
{
  if (mpCompartment == NULL) return;

  switch (CModelEntity::StatusName.toEnum(TO_UTF8(type)))
    {
      case CModelEntity::Status::FIXED:
        mpLblExpression->hide();
        mpExpressionEMW->hide();

        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

        mpBoxAddNoise->hide();
        mpBoxAddNoise->setChecked(false);
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
        mpBoxAddNoise->setChecked(false);
        slotAddNoiseChanged(false);

        break;

      case CModelEntity::Status::ODE:
        mpLblExpression->setText("Expression" + mRateUnits);

        mpLblExpression->show();
        mpExpressionEMW->show();

        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

        mpExpressionEMW->updateWidget();

        mpBoxAddNoise->show();
        slotAddNoiseChanged(mpBoxAddNoise->isChecked());

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

      mpEditInitialVolume->setEnabled(CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType-> currentText())) != CModelEntity::Status::ASSIGNMENT);
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

bool CQCompartment::leaveProtected()
{
  if (CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType-> currentText())) != CModelEntity::Status::FIXED)
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

bool CQCompartment::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  mpCompartment = dynamic_cast< CCompartment * >(mpObject);

  switch (objectType)
    {
      case ListViews::ObjectType::MODEL:

        // For a new or deleted model we need to remove references to no longer existing compartment
        if (action != ListViews::CHANGE)
          {
            mObjectCN.clear();
            mpObject = NULL;
            mpCompartment = NULL;

            // we also have to clear the widgets that might store old data
            mpExpressionEMW->reset();
            mpInitialExpressionEMW->reset();
          }

        break;

      case ListViews::ObjectType::COMPARTMENT:

        // If the currently displayed compartment is deleted we need to remove its references.
        if (action == ListViews::DELETE && mObjectCN == cn)
          {
            mObjectCN.clear();
            mpObject = NULL;
            mpCompartment = NULL;

            // we also have to clear the widgets that might store old data
            mpExpressionEMW->reset();
            mpInitialExpressionEMW->reset();
          }

        break;

      case ListViews::ObjectType::STATE:
      case ListViews::ObjectType::METABOLITE:
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
  slotDimesionalityChanged(mpCompartment->getDimensionality());

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
  slotTypeChanged(mpComboBoxType->currentText());

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

  CData OldData(mpCompartment->toData());

#ifdef COPASI_EXTUNIT

  //Dimensionality
  if ((C_INT32)mpCompartment->getDimensionality() != mpComboBoxDim->currentIndex()) //this makes assumptions about the order of entries in the combo box!
    {
      mpCompartment->setDimensionality((unsigned C_INT32) mpComboBoxDim->currentIndex());
      mChanged = true;
    }

#endif

  // Type
  if (mpCompartment->getStatus() != CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType-> currentText())))
    {
      mpCompartment->setStatus(CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType->currentText())));
      mChanged = true;
    }

  // Initial Volume
  if (convertToQString(mpCompartment->getInitialValue()) != mpEditInitialVolume->text())
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
  if (CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType-> currentText())) != CModelEntity::Status::ASSIGNMENT)
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

  // Add Noise
  if (mpCompartment->hasNoise() != mpBoxAddNoise->isChecked())
    {
      mpCompartment->setHasNoise(mpBoxAddNoise->isChecked());
      mChanged = true;
    }

  // Noise Expression
  if (mpCompartment->getNoiseExpression() != mpNoiseExpressionWidget->mpExpressionWidget->getExpression())
    {
      mpCompartment->setNoiseExpression(mpNoiseExpressionWidget->mpExpressionWidget->getExpression());
      mChanged = true;
    }

  mIgnoreUpdates = false;

  if (mChanged)
    {
      CUndoData UndoData;
      mpCompartment->createUndoData(UndoData, CUndoData::Type::CHANGE, OldData, static_cast< CCore::Framework >(mFramework));
      ListViews::addUndoMetaData(this, UndoData);

      slotNotifyChanges(mpDataModel->applyData(UndoData));
      load();
    }
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
          mpListView->switchToOtherWidget(ListViews::WidgetType::SpeciesDetail, (*it)->getCN());
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

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpMetaboliteTable->resizeRowsToContents();
    }

  return;
}
