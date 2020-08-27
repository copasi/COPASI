// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

/*
 * CQModelWidget.cpp
 *
 *  Created on: Aug 13, 2010
 *      Author: shoops
 */
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

#ifndef COPASI_EXTUNIT
  mpLblAreaUnit->hide();
  mpEditAreaUnit->hide();

  mpLblLengthUnit->hide();
  mpEditLengthUnit->hide();

  mpLblAvogadro->hide();
  mpEditAvogadro->hide();
  mpBtnUpdateAvogadro->hide();
#endif

  // mpBtnUpdateAvogadro->setIcon(CQIconResource::icon(CQIconResource::tool));
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

  mpEditTimeUnit->setText(FROM_UTF8(mpModel->getTimeUnit()));
  static_cast< const CQValidatorUnit * >(mpEditTimeUnit->validator())->saved();

  mpEditQuantityUnit->setText(FROM_UTF8(mpModel->getQuantityUnit()));
  static_cast< const CQValidatorUnit * >(mpEditQuantityUnit->validator())->saved();

  mpEditVolumeUnit->setText(FROM_UTF8(mpModel->getVolumeUnit()));
  static_cast< const CQValidatorUnit * >(mpEditVolumeUnit->validator())->saved();

  mpEditAreaUnit->setText(FROM_UTF8(mpModel->getAreaUnit()));
  static_cast< const CQValidatorUnit * >(mpEditAreaUnit->validator())->saved();

  mpEditLengthUnit->setText(FROM_UTF8(mpModel->getLengthUnit()));
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

  mpEditInitialTime->setText(convertToQString(mpModel->getInitialTime()));
  mpEditCurrentTime->setText(convertToQString(mpModel->getTime()));

  mpCheckStochasticCorrection->setChecked(mpModel->getModelType() == CModel::ModelType::deterministic);

  slotUnitChanged();

  return;
}

void CQModelWidget::save()
{
  if (mpModel == NULL)
    return;

  bool changed = false;
  CData OldData(mpModel->toData());

  mIgnoreUpdates = true;

  if (mpEditTimeUnit->text() != FROM_UTF8(mpModel->getTimeUnit()))
    {
      mpModel->setTimeUnit(TO_UTF8(mpEditTimeUnit->text()));
      changed = true;
    }

  if (mpEditVolumeUnit->text() != FROM_UTF8(mpModel->getVolumeUnit()))
    {
      mpModel->setVolumeUnit(TO_UTF8(mpEditVolumeUnit->text()));
      changed = true;
    }

  if (mpEditAreaUnit->text() != FROM_UTF8(mpModel->getAreaUnit()))
    {
      mpModel->setAreaUnit(TO_UTF8(mpEditAreaUnit->text()));
      changed = true;
    }

  if (mpEditLengthUnit->text() != FROM_UTF8(mpModel->getLengthUnit()))
    {
      mpModel->setLengthUnit(TO_UTF8(mpEditLengthUnit->text()));
      changed = true;
    }

  if (mpEditQuantityUnit->text() != FROM_UTF8(mpModel->getQuantityUnit()))
    {
      mpModel->setQuantityUnit(TO_UTF8(mpEditQuantityUnit->text()), static_cast< CCore::Framework >(mFramework));
      changed = true;
    }

  if (mpEditAvogadro->text() != QString::number(mpModel->getAvogadro(), 'g', 14))
    {
      mpModel->setAvogadro(mpEditAvogadro->text().toDouble(), static_cast< CCore::Framework >(mFramework));
      changed = true;
    }

  if (mpCheckStochasticCorrection->isChecked() != (mpModel->getModelType() == CModel::ModelType::deterministic))
    {
      mpModel->setModelType(mpCheckStochasticCorrection->isChecked() ? CModel::ModelType::deterministic : CModel::ModelType::stochastic);
      changed = true;
    }

  if (mpEditInitialTime->text() != convertToQString(mpModel->getInitialTime()))
    {
      mpModel->setInitialValue(mpEditInitialTime->text().toDouble());
      changed = true;
    }

  mIgnoreUpdates = false;

  if (changed)
    {
      CUndoData UndoData;
      mpModel->createUndoData(UndoData, CUndoData::Type::CHANGE, OldData, static_cast< CCore::Framework >(mFramework));
      ListViews::addUndoMetaData(this, UndoData);

      slotNotifyChanges(mpDataModel->recordData(UndoData));
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

bool CQModelWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
      case ListViews::ObjectType::MODEL:
        enter(cn);
        break;

      default:
        break;
    }

  return true;
}

bool CQModelWidget::leaveProtected()
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

  mpNotes->enter(mObjectCN);

  return true;
}

void CQModelWidget::slotUpdateAvogadro()
{
  CQUpdateAvogadro *pDialog = new CQUpdateAvogadro(this);

  pDialog->setSelection(mFramework == 0 ? 0 : 1);

  switch (pDialog->exec())
    {
      case QDialog::Accepted:
      {
        CData OldData(mpModel->toData());

        mpModel->setAvogadro(CUnit::Avogadro, static_cast< CCore::Framework >(pDialog->getSelection()));

        CUndoData UndoData;
        mpModel->createUndoData(UndoData, CUndoData::Type::CHANGE, OldData, static_cast< CCore::Framework >(pDialog->getSelection()));
        ListViews::addUndoMetaData(this, UndoData);

        slotNotifyChanges(mpDataModel->recordData(UndoData));

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
