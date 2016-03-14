// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQModelWidget.cpp
 *
 *  Created on: Aug 13, 2010
 *      Author: shoops
 */

#include "CQModelWidget.h"
#include "qtUtilities.h"

#include "copasi/model/CModel.h"
#include "copasi/utilities/CUnit.h"
#include "copasi/report/CCopasiRootContainer.h"

#include <QUndoStack>
#include <copasi/undoFramework/ModelChangeCommand.h>
#include <copasi/UI/copasiui3window.h>
#include <copasi/UI/CQCopasiApplication.h>

CQModelWidget::CQModelWidget(QWidget* parent, const char* name) :
  CopasiWidget(parent, name),
  mpModel(NULL)
{
  setupUi(this);

  updateUnitComboBoxes();

  mpUndoStack = NULL;

#ifndef COPASI_EXTUNIT
  mpLblAreaUnit->hide();
  mpComboAreaUnit->hide();

  mpLblLengthUnit->hide();
  mpComboLengthUnit->hide();
#endif
}

CQModelWidget::~CQModelWidget()
{}

void CQModelWidget::load()
{
  if (mpModel == NULL)
    return;

  mpComboTimeUnit->setCurrentIndex(mpComboTimeUnit->findText(FROM_UTF8(mpModel->getTimeUnitName())));
  mpComboVolumeUnit->setCurrentIndex(mpComboVolumeUnit->findText(FROM_UTF8(mpModel->getVolumeUnitName())));
  mpComboQuantityUnit->setCurrentIndex(mpComboQuantityUnit->findText(FROM_UTF8(mpModel->getQuantityUnitName())));
  mpComboAreaUnit->setCurrentIndex(mpComboAreaUnit->findText(FROM_UTF8(mpModel->getAreaUnitName())));
  mpComboLengthUnit->setCurrentIndex(mpComboLengthUnit->findText(FROM_UTF8(mpModel->getLengthUnitName())));

  mpCheckStochasticCorrection->setChecked(mpModel->getModelType() == CModel::deterministic);

  mpLblInitialTime->setText("Initial Time (" + mpComboTimeUnit->currentText() + ")");
  mpEditInitialTime->setText(QString::number(mpModel->getInitialTime()));
  mpEditInitialTime->setReadOnly(mpModel->isAutonomous());

  mpLblCurrentTime->setText("Time (" + mpComboTimeUnit->currentText() + ")");
  mpEditCurrentTime->setText(QString::number(mpModel->getTime()));

  return;
}

void CQModelWidget::save()
{
  if (mpModel == NULL)
    return;

  bool changed = false;

  mIgnoreUpdates = true;

  if (mpUndoStack == NULL)
    {
      mpUndoStack = static_cast<CQCopasiApplication*>(qApp)
                    ->getMainWindow()->getUndoStack();
    }

  if (TO_UTF8(mpComboTimeUnit->currentText()) != mpModel->getTimeUnitName())
    {
      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_TIME_UNIT_CHANGE,
                               FROM_UTF8(mpModel->getTimeUnitName()),
                               mpComboTimeUnit->currentText(),
                               this));
      changed = true;
    }

  if (TO_UTF8(mpComboVolumeUnit->currentText()) != mpModel->getVolumeUnitName())
    {
      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_VOLUME_UNIT_CHANGE,
                               FROM_UTF8(mpModel->getVolumeUnitName()),
                               mpComboVolumeUnit->currentText(),
                               this));
      changed = true;
    }

  if (TO_UTF8(mpComboAreaUnit->currentText()) != mpModel->getAreaUnitName())
    {
      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_AREA_UNIT_CHANGE,
                               FROM_UTF8(mpModel->getAreaUnitName()),
                               mpComboAreaUnit->currentText(),
                               this));
      changed = true;
    }

  if (TO_UTF8(mpComboLengthUnit->currentText()) != mpModel->getLengthUnitName())
    {
      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_LENGTH_UNIT_CHANGE,
                               FROM_UTF8(mpModel->getLengthUnitName()),
                               mpComboLengthUnit->currentText(),
                               this));
      changed = true;
    }

  if (TO_UTF8(mpComboQuantityUnit->currentText()) != mpModel->getQuantityUnitName())
    {
      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_QUANTITY_UNIT_CHANGE,
                               FROM_UTF8(mpModel->getQuantityUnitName()),
                               mpComboQuantityUnit->currentText(),
                               this));
      changed = true;
    }

  if (mpCheckStochasticCorrection->isChecked() != (mpModel->getModelType() == CModel::deterministic))
    {
      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_STOCHASTIC_CORRECTION_CHANGE,
                               mpModel->getModelType() == CModel::deterministic,
                               mpCheckStochasticCorrection->isChecked(),
                               this));
      changed = true;
    }

  if (mpEditInitialTime->text() != QString::number(mpModel->getInitialTime()))
    {
      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_INITIAL_TIME_CHANGE,
                               mpModel->getInitialTime(),
                               mpEditInitialTime->text().toDouble(),
                               this));
      changed = true;
    }

  mIgnoreUpdates = false;

  if (changed)
    {
      if (mpDataModel != NULL)
        {
          mpDataModel->changed();
        }

      protectedNotify(ListViews::MODEL, ListViews::CHANGE, mKey);

      load();
    }

  return;
}

void CQModelWidget::slotBtnRevertClicked()
{
  load();
}

void CQModelWidget::slotBtnOKClicked()
{
  save();
  load();
}

bool CQModelWidget::update(ListViews::ObjectType objectType,
                           ListViews::Action C_UNUSED(action), const std::string & key)
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
      case ListViews::MODEL:
        enter(key);
        break;

      case ListViews::UNIT:
        updateUnitComboBoxes();
        break;

      default:
        break;
    }

  return true;
}

bool CQModelWidget::leave()
{
  save();

  mpNotes->leave();

  return true;
}

bool CQModelWidget::enterProtected()
{
  if (mpObject != NULL)
    mpModel = dynamic_cast< CModel * >(mpObject);
  else
    mpModel = NULL;

  load();

  mpNotes->enter(mKey);

  return true;
}

bool
CQModelWidget::changeValue(CCopasiUndoCommand::Type type, const QVariant& newValue)
{
  mpListView->switchToOtherWidget(C_INVALID_INDEX, mKey);
  qApp->processEvents();

  if (type == CCopasiUndoCommand::MODEL_TIME_UNIT_CHANGE)
    {
      mpModel->setTimeUnit(TO_UTF8(newValue.toString()));
    }
  else if (type == CCopasiUndoCommand::MODEL_QUANTITY_UNIT_CHANGE)
    {
      mpModel->setQuantityUnit(TO_UTF8(newValue.toString()));
    }
  else if (type == CCopasiUndoCommand::MODEL_VOLUME_UNIT_CHANGE)
    {
      mpModel->setVolumeUnit(TO_UTF8(newValue.toString()));
    }
  else if (type == CCopasiUndoCommand::MODEL_AREA_UNIT_CHANGE)
    {
      mpModel->setAreaUnit(TO_UTF8(newValue.toString()));
    }
  else if (type == CCopasiUndoCommand::MODEL_LENGTH_UNIT_CHANGE)
    {
      mpModel->setLengthUnit(TO_UTF8(newValue.toString()));
    }
  else if (type == CCopasiUndoCommand::MODEL_INITIAL_TIME_CHANGE)
    {
      mpModel->setInitialTime(newValue.toDouble());
    }
  else if (type == CCopasiUndoCommand::MODEL_STOCHASTIC_CORRECTION_CHANGE)
    {
      if (newValue.toBool())
        {
          mpModel->setModelType(CModel::deterministic);
        }
      else
        {
          mpModel->setModelType(CModel::stochastic);
        }
    }
  else
    {
      return false;
    }

  if (mIgnoreUpdates) return true;

  if (mpDataModel != NULL)
    {
      mpDataModel->changed();
    }

  protectedNotify(ListViews::MODEL, ListViews::CHANGE, mKey);

  load();

  return true;
}

void CQModelWidget::updateUnitComboBoxes()
{
  QStringList ComboEntries;

  // Take advantage of the implicit sorting in std::set
  std::set< CUnitDefinition > timeUnitDefSet,
      quantityUnitDefSet,
      volumeUnitDefSet,
      areaUnitDefSet,
      lengthUnitDefSet;

  CUnitDefinitionDB::const_iterator it = CCopasiRootContainer::getUnitList()->begin(),
                                    end = CCopasiRootContainer::getUnitList()->end();

  // Grab the appropriate units
  for (; it != end; ++it)
    {
      if (it->isUnitType(CUnit::time))
        timeUnitDefSet.insert(CUnitDefinition(*it, NULL));

      if (it->isUnitType(CUnit::quantity))
        quantityUnitDefSet.insert(CUnitDefinition(*it, NULL));

      if (it->isUnitType(CUnit::volume))
        volumeUnitDefSet.insert(CUnitDefinition(*it, NULL));

      if (it->isUnitType(CUnit::area))
        areaUnitDefSet.insert(CUnitDefinition(*it, NULL));

      if (it->isUnitType(CUnit::length))
        lengthUnitDefSet.insert(CUnitDefinition(*it, NULL));
    }

  std::set< CUnitDefinition >::const_iterator itDS = timeUnitDefSet.begin(),
                                              endDS = timeUnitDefSet.end();

  // Set time unit options
  for (; itDS != endDS; ++itDS)
    {
      ComboEntries.push_back(QString::fromUtf8(itDS->getSymbol().c_str()));
    }

  mpComboTimeUnit->clear();
  mpComboTimeUnit->insertItems(0, ComboEntries);

  // Set quantity unit options
  ComboEntries.clear();
  itDS = quantityUnitDefSet.begin();
  endDS = quantityUnitDefSet.end();

  for (; itDS != endDS; ++itDS)
    {
      ComboEntries.push_back(QString::fromUtf8(itDS->getSymbol().c_str()));
    }

  mpComboQuantityUnit->clear();
  mpComboQuantityUnit->insertItems(0, ComboEntries);

  // Set volume unit options
  ComboEntries.clear();
  itDS = volumeUnitDefSet.begin();
  endDS = volumeUnitDefSet.end();

  for (; itDS != endDS; ++itDS)
    {
      ComboEntries.push_back(QString::fromUtf8(itDS->getSymbol().c_str()));
    }

  mpComboVolumeUnit->clear();
  mpComboVolumeUnit->insertItems(0, ComboEntries);

  // Set area unit options
  ComboEntries.clear();
  itDS = areaUnitDefSet.begin();
  endDS = areaUnitDefSet.end();

  for (; itDS != endDS; ++itDS)
    {
      ComboEntries.push_back(QString::fromUtf8(itDS->getSymbol().c_str()));
    }

  mpComboAreaUnit->clear();
  mpComboAreaUnit->insertItems(0, ComboEntries);

  // Set length unit options
  ComboEntries.clear();
  itDS = lengthUnitDefSet.begin();
  endDS = lengthUnitDefSet.end();

  for (; itDS != endDS; ++itDS)
    {
      ComboEntries.push_back(QString::fromUtf8(itDS->getSymbol().c_str()));
    }

  mpComboLengthUnit->clear();
  mpComboLengthUnit->insertItems(0, ComboEntries);
}
