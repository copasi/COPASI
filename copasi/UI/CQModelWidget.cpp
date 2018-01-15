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
#include <QCompleter>
#include <QTimer>

#include "CQModelWidget.h"
#include "CQUpdateAvogadro.h"
#include "qtUtilities.h"
#include "copasiui3window.h"
#include "CQCopasiApplication.h"
#include "CQValidatorUnit.h"

#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/model/CModel.h"
#include "copasi/utilities/CUnit.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnitDefinitionDB.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/undoFramework/ModelChangeCommand.h"

CQModelWidget::CQModelWidget(QWidget* parent, const char* name) :
  CopasiWidget(parent, name),
  mpModel(NULL),
  mpFocusUnit(NULL)
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
  mpEditAreaUnit->hide();

  mpLblLengthUnit->hide();
  mpEditLengthUnit->hide();

  mpLblAvogadro->hide();
  mpEditAvogadro->hide();
  mpBtnUpdateAvogadro->hide();
#endif

  mpBtnUpdateAvogadro->setIcon(CQIconResource::icon(CQIconResource::tool));
  mpEditAvogadro->setEnabled(false);

  QStringList unitEntries;

  std::vector< CUnit > ValidUnits = CRootContainer::getUnitList()->getAllValidUnits("s", 1);
  std::vector< CUnit >::const_iterator itUnit = ValidUnits.begin();
  std::vector< CUnit >::const_iterator endUnit = ValidUnits.end();

  for (; itUnit != endUnit; ++itUnit)
    {
      unitEntries.push_back(FROM_UTF8(itUnit->getExpression()));

      if (!itUnit->getExpression().compare(0, 2, "\xc2\xb5"))
        {
          unitEntries.push_back(FROM_UTF8(itUnit->getExpression().replace(0, 2, "u")));
        }
    }

  QCompleter *completer = new QCompleter(unitEntries, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  mpEditTimeUnit->setCompleter(completer);
  connect(mpEditTimeUnit, SIGNAL(textEdited(QString)), this, SLOT(slotShowCompleter()));

  unitEntries.clear();
  ValidUnits = CRootContainer::getUnitList()->getAllValidUnits("m", 3);
  itUnit = ValidUnits.begin();
  endUnit = ValidUnits.end();

  for (; itUnit != endUnit; ++itUnit)
    {
      unitEntries.push_back(FROM_UTF8(itUnit->getExpression()));

      if (!itUnit->getExpression().compare(0, 2, "\xc2\xb5"))
        {
          unitEntries.push_back(FROM_UTF8(itUnit->getExpression().replace(0, 2, "u")));
        }
    }

  completer = new QCompleter(unitEntries, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  mpEditVolumeUnit->setCompleter(completer);
  connect(mpEditVolumeUnit, SIGNAL(textEdited(QString)), this, SLOT(slotShowCompleter()));

  unitEntries.clear();
  ValidUnits = CRootContainer::getUnitList()->getAllValidUnits("m", 2);
  itUnit = ValidUnits.begin();
  endUnit = ValidUnits.end();

  for (; itUnit != endUnit; ++itUnit)
    {
      unitEntries.push_back(FROM_UTF8(itUnit->getExpression()));

      if (!itUnit->getExpression().compare(0, 2, "\xc2\xb5"))
        {
          unitEntries.push_back(FROM_UTF8(itUnit->getExpression().replace(0, 2, "u")));
        }
    }

  completer = new QCompleter(unitEntries, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  mpEditAreaUnit->setCompleter(completer);
  connect(mpEditAreaUnit, SIGNAL(textEdited(QString)), this, SLOT(slotShowCompleter()));

  unitEntries.clear();
  ValidUnits = CRootContainer::getUnitList()->getAllValidUnits("m", 1);
  itUnit = ValidUnits.begin();
  endUnit = ValidUnits.end();

  for (; itUnit != endUnit; ++itUnit)
    {
      unitEntries.push_back(FROM_UTF8(itUnit->getExpression()));

      if (!itUnit->getExpression().compare(0, 2, "\xc2\xb5"))
        {
          unitEntries.push_back(FROM_UTF8(itUnit->getExpression().replace(0, 2, "u")));
        }
    }

  completer = new QCompleter(unitEntries, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  mpEditLengthUnit->setCompleter(completer);
  connect(mpEditLengthUnit, SIGNAL(textEdited(QString)), this, SLOT(slotShowCompleter()));

  unitEntries.clear();
  ValidUnits = CRootContainer::getUnitList()->getAllValidUnits("#", 1);
  itUnit = ValidUnits.begin();
  endUnit = ValidUnits.end();

  for (; itUnit != endUnit; ++itUnit)
    {
      unitEntries.push_back(FROM_UTF8(itUnit->getExpression()));

      if (!itUnit->getExpression().compare(0, 2, "\xc2\xb5"))
        {
          unitEntries.push_back(FROM_UTF8(itUnit->getExpression().replace(0, 2, "u")));
        }
    }

  completer = new QCompleter(unitEntries, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  mpEditQuantityUnit->setCompleter(completer);
  connect(mpEditQuantityUnit, SIGNAL(textEdited(QString)), this, SLOT(slotShowCompleter()));
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

  mpEditAvogadro->setText(QString::number(mpModel->getAvogadro(), 'g', 14));

#ifdef COPASI_EXTUNIT

  if (mpModel->getAvogadro() == CUnit::Avogadro)
    {
      mpBtnUpdateAvogadro->hide();
    }
  else
    {
      mpBtnUpdateAvogadro->show();
    }

#endif

  mpEditInitialTime->setReadOnly(mpModel->isAutonomous());
  mpEditInitialTime->setText(convertToQString(mpModel->getInitialTime()));
  mpEditCurrentTime->setText(convertToQString(mpModel->getTime()));

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
                               OldValues, NewValues,
                               this));
      changed = true;
    }

  if (mpEditAvogadro->text() != QString::number(mpModel->getAvogadro(), 'g', 14))
    {
      QList< QVariant > OldValues, NewValues;

      OldValues.append(mpModel->getAvogadro());
      NewValues.append(mpEditAvogadro->text());
      OldValues.append(mFramework);
      NewValues.append(mFramework);

      mpUndoStack->push(
        new ModelChangeCommand(CCopasiUndoCommand::MODEL_AVOGADRO_NUMBER_CHANGE,
                               OldValues, NewValues,
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

  if (mpEditInitialTime->text() != convertToQString(mpModel->getInitialTime()))
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
      assert(mpDataModel != NULL);
      CModel * pModel = mpDataModel->getModel();
      assert(pModel != NULL);
      mpModel = pModel;
    }

  if (type == CCopasiUndoCommand::MODEL_TIME_UNIT_CHANGE)
    {
      mpModel->setTimeUnit(TO_UTF8(newValue.toString()));
    }
  else if (type == CCopasiUndoCommand::MODEL_QUANTITY_UNIT_CHANGE)
    {
      QList< QVariant > Values = newValue.toList();
      mpModel->setQuantityUnit(TO_UTF8(Values[0].toString()), (CCore::Framework) Values[1].toInt());
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
  else if (type == CCopasiUndoCommand::MODEL_AVOGADRO_NUMBER_CHANGE)
    {
      QList< QVariant > Values = newValue.toList();
      mpModel->setAvogadro(Values[0].toDouble(), (CCore::Framework) Values[1].toInt());
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
void CQModelWidget::slotUpdateAvogadro()
{
  CQUpdateAvogadro *pDialog = new CQUpdateAvogadro(this);

  pDialog->setSelection(mFramework == 0 ? 0 : 1);

  switch (pDialog->exec())
    {
      case QDialog::Accepted:
        if (mpUndoStack == NULL)
          {
            mpUndoStack = static_cast<CQCopasiApplication*>(qApp)
                          ->getMainWindow()->getUndoStack();
          }

        {
          QList< QVariant > OldValues, NewValues;

          OldValues.append(mpModel->getAvogadro());
          NewValues.append(CUnit::Avogadro);
          OldValues.append(pDialog->getSelection());
          NewValues.append(pDialog->getSelection());

          mpUndoStack->push(
            new ModelChangeCommand(CCopasiUndoCommand::MODEL_AVOGADRO_NUMBER_CHANGE,
                                   OldValues, NewValues,
                                   this));

          load();
        }

        break;

      case QDialog::Rejected:
        break;
    }
}

// virtual
void CQModelWidget::slotUnitChanged()
{
  if (mpEditTimeUnit->text() != "?")
    {
      QString Unit = FROM_UTF8(CUnit::prettyPrint(TO_UTF8(mpEditTimeUnit->text())));
      mpEditTimeUnit->setText(Unit);

      mpLblInitialTime->setText("Initial Time [" + Unit + "]");
      mpLblCurrentTime->setText("Time [" + Unit + "]");
    }

  if (mpEditQuantityUnit->text() != "?")
    {
      mpEditQuantityUnit->setText(FROM_UTF8(CUnit::prettyPrint(TO_UTF8(mpEditQuantityUnit->text()))));
    }

  if (mpEditVolumeUnit->text() != "?")
    {
      mpEditVolumeUnit->setText(FROM_UTF8(CUnit::prettyPrint(TO_UTF8(mpEditVolumeUnit->text()))));
    }

  if (mpEditAreaUnit->text() != "?")
    {
      mpEditAreaUnit->setText(FROM_UTF8(CUnit::prettyPrint(TO_UTF8(mpEditAreaUnit->text()))));
    }

  if (mpEditLengthUnit->text() != "?")
    {
      mpEditLengthUnit->setText(FROM_UTF8(CUnit::prettyPrint(TO_UTF8(mpEditLengthUnit->text()))));
    }
}

void CQModelWidget::slotShowCompleter()
{
  mpFocusUnit = qobject_cast<QLineEdit*> (sender());

  QTimer::singleShot(10, this, SLOT(slotDelayed()));
}

void CQModelWidget::slotDelayed()
{
  if (mpFocusUnit != NULL &&
      mpFocusUnit->text().isEmpty())
    {
      mpFocusUnit->completer()->setCompletionPrefix("");
      mpFocusUnit->completer()->complete();
    }

  mpFocusUnit = NULL;
}
