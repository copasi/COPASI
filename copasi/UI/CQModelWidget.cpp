// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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
#include <QUndoStack>

#include "CQModelWidget.h"
#include "qtUtilities.h"
#include "copasiui3window.h"
#include "CQCopasiApplication.h"
#include "CQValidatorUnit.h"

#include "resourcesUI/CQIconResource.h"

#include "model/CModel.h"
#include "utilities/CUnit.h"
#include "report/CCopasiRootContainer.h"

#include "undoFramework/ModelChangeCommand.h"

CQModelWidget::CQModelWidget(QWidget* parent, const char* name) :
  CopasiWidget(parent, name),
  mpModel(NULL)
{
  setupUi(this);

  CQValidatorUnit * pValidator = new CQValidatorUnit(mpEditTimeUnit);
  pValidator->setConstraint("s");
  mpEditTimeUnit->setValidator(pValidator);

  pValidator = new CQValidatorUnit(mpEditQuantityUnit);
  pValidator->setConstraint("#");
  mpEditQuantityUnit->setValidator(pValidator);

  pValidator = new CQValidatorUnit(mpEditVolumeUnit);
  pValidator->setConstraint("m^3");
  mpEditVolumeUnit->setValidator(pValidator);

  pValidator = new CQValidatorUnit(mpEditAreaUnit);
  pValidator->setConstraint("m^2");
  mpEditAreaUnit->setValidator(pValidator);

  pValidator = new CQValidatorUnit(mpEditLengthUnit);
  pValidator->setConstraint("m");
  mpEditLengthUnit->setValidator(pValidator);

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

  mpEditTimeUnit->setText(FROM_UTF8(mpModel->getTimeUnitName()));
  static_cast< const CQValidatorUnit * >(mpEditTimeUnit->validator())->saved();

  mpEditQuantityUnit->setText(FROM_UTF8(mpModel->getQuantityUnitName()));
  static_cast< const CQValidatorUnit * >(mpEditQuantityUnit->validator())->saved();

  mpEditVolumeUnit->setText(FROM_UTF8(mpModel->getVolumeUnitName()));
  static_cast< const CQValidatorUnit * >(mpEditVolumeUnit->validator())->saved();

  mpEditAreaUnit->setText(FROM_UTF8(mpModel->getAreaUnitName()));
  static_cast< const CQValidatorUnit * >(mpEditAreaUnit->validator())->saved();

  mpEditLengthUnit->setText(FROM_UTF8(mpModel->getLengthUnitName()));
  static_cast< const CQValidatorUnit * >(mpEditLengthUnit->validator())->saved();

#ifndef COPASI_EXTUNIT
  mpEditAreaUnit->hide();
  mpEditLengthUnit->hide();
#endif

  mpEditInitialTime->setReadOnly(mpModel->isAutonomous());
  mpEditInitialTime->setText(QString::number(mpModel->getInitialTime(), 'g', 10));
  mpEditCurrentTime->setText(QString::number(mpModel->getTime(), 'g', 10));

  mpCheckStochasticCorrection->setChecked(mpModel->getModelType() == CModel::deterministic);

  slotUnitChanged();

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

  if (mpEditTimeUnit->text() != FROM_UTF8(mpModel->getTimeUnitName()))
    {
      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_TIME_UNIT_CHANGE,
                               FROM_UTF8(mpModel->getTimeUnitName()),
                               mpEditTimeUnit->text(),
                               this));
      changed = true;
    }

  if (mpEditVolumeUnit->text() != FROM_UTF8(mpModel->getVolumeUnitName()))
    {
      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_VOLUME_UNIT_CHANGE,
                               FROM_UTF8(mpModel->getVolumeUnitName()),
                               mpEditVolumeUnit->text(),
                               this));
      changed = true;
    }

  if (mpEditAreaUnit->text() != FROM_UTF8(mpModel->getAreaUnitName()))
    {
      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_AREA_UNIT_CHANGE,
                               FROM_UTF8(mpModel->getAreaUnitName()),
                               mpEditAreaUnit->text(),
                               this));
      changed = true;
    }

  if (mpEditLengthUnit->text() != FROM_UTF8(mpModel->getLengthUnitName()))
    {
      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_LENGTH_UNIT_CHANGE,
                               FROM_UTF8(mpModel->getLengthUnitName()),
                               mpEditLengthUnit->text(),
                               this));
      changed = true;
    }

  if (mpEditQuantityUnit->text() != FROM_UTF8(mpModel->getQuantityUnitName()))
    {
      QList< QVariant > OldValues, NewValues;

      OldValues.append(FROM_UTF8(mpModel->getQuantityUnitName()));
      NewValues.append(mpEditQuantityUnit->text());
      OldValues.append(mFramework);
      NewValues.append(mFramework);

      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_QUANTITY_UNIT_CHANGE,
                               FROM_UTF8(mpModel->getQuantityUnitName()),
                               mpEditQuantityUnit->text(),
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

  if (mpModel == NULL)
    {
      GET_MODEL_OR(pModel, return false);
      mpModel = pModel;
    }

  if (type == CCopasiUndoCommand::MODEL_TIME_UNIT_CHANGE)
    {
      mpModel->setTimeUnit(TO_UTF8(newValue.toString()));
    }
  else if (type == CCopasiUndoCommand::MODEL_QUANTITY_UNIT_CHANGE)
    {
      mpModel->setQuantityUnit(TO_UTF8(newValue.toString()), (CModelParameter::Framework) mFramework);
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

// virtual
void CQModelWidget::slotUnitChanged()
{
  QString Unit = FROM_UTF8(CUnit::prettyPrint(TO_UTF8(mpEditTimeUnit->text())));
  mpEditTimeUnit->setText(Unit);

  mpLblInitialTime->setText("Initial Time [" + Unit + "]");
  mpLblCurrentTime->setText("Time [" + Unit + "]");

  Unit = FROM_UTF8(CUnit::prettyPrint(TO_UTF8(mpEditQuantityUnit->text())));
  mpEditQuantityUnit->setText(Unit);

  Unit = FROM_UTF8(CUnit::prettyPrint(TO_UTF8(mpEditVolumeUnit->text())));
  mpEditVolumeUnit->setText(Unit);

  Unit = FROM_UTF8(CUnit::prettyPrint(TO_UTF8(mpEditAreaUnit->text())));
  mpEditAreaUnit->setText(Unit);

  Unit = FROM_UTF8(CUnit::prettyPrint(TO_UTF8(mpEditLengthUnit->text())));
  mpEditLengthUnit->setText(Unit);
}
