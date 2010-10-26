// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelWidget.cpp,v $
//   $Revision: 1.2.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/10/26 14:49:54 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#include "model/CModel.h"
#include "copasi/report/CCopasiRootContainer.h"

CQModelWidget::CQModelWidget(QWidget* parent, const char* name) :
    CopasiWidget(parent, name),
    mpModel(NULL)
{
  setupUi(this);

  QStringList ComboEntries;
  const char ** pComboEntries;

  for (pComboEntries = CModel::TimeUnitNames; *pComboEntries != NULL; ++pComboEntries)
    {
      ComboEntries.push_front(QString::fromUtf8(*pComboEntries));
    }

  mpComboTimeUnit->clear();
  mpComboTimeUnit->insertStringList(ComboEntries, -1);

  ComboEntries.clear();

  for (pComboEntries = CModel::VolumeUnitNames; *pComboEntries != NULL; ++pComboEntries)
    {
      ComboEntries.push_front(QString::fromUtf8(*pComboEntries));
    }

  mpComboVolumeUnit->clear();
  mpComboVolumeUnit->insertStringList(ComboEntries, -1);

  ComboEntries.clear();

  for (pComboEntries = CModel::AreaUnitNames; *pComboEntries != NULL; ++pComboEntries)
    {
      ComboEntries.push_front(QString::fromUtf8(*pComboEntries));
    }

  mpComboAreaUnit->clear();
  mpComboAreaUnit->insertStringList(ComboEntries, -1);

  ComboEntries.clear();

  for (pComboEntries = CModel::LengthUnitNames; *pComboEntries != NULL; ++pComboEntries)
    {
      ComboEntries.push_front(QString::fromUtf8(*pComboEntries));
    }

  mpComboLengthUnit->clear();
  mpComboLengthUnit->insertStringList(ComboEntries, -1);

  ComboEntries.clear();

  for (pComboEntries = CModel::QuantityUnitNames; *pComboEntries != NULL; ++pComboEntries)
    {
      ComboEntries.push_front(QString::fromUtf8(*pComboEntries));
    }

  mpComboQuantityUnit->clear();
  mpComboQuantityUnit->insertStringList(ComboEntries, -1);

  ComboEntries.clear();

  for (pComboEntries = CModel::ModelTypeNames; *pComboEntries != NULL; ++pComboEntries)
    {
      ComboEntries.push_front(QString::fromUtf8(*pComboEntries));
    }

  mpComboModelType->clear();
  mpComboModelType->insertStringList(ComboEntries, -1);

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

  mpEditName->setText(FROM_UTF8(mpModel->getObjectName()));

  mpComboTimeUnit->setCurrentText(FROM_UTF8(mpModel->getTimeUnitName()));
  mpLblTimeUnit->setText("Time (" + mpComboTimeUnit->currentText() + ")");
  mpComboVolumeUnit->setCurrentText(FROM_UTF8(mpModel->getVolumeUnitName()));
  mpComboQuantityUnit->setCurrentText(FROM_UTF8(mpModel->getQuantityUnitName()));
  mpComboAreaUnit->setCurrentText(FROM_UTF8(mpModel->getAreaUnitName()));
  mpComboLengthUnit->setCurrentText(FROM_UTF8(mpModel->getLengthUnitName()));

  mpComboModelType->setCurrentText(CModel::ModelTypeNames[mpModel->getModelType()]);

  mpEditInitialTime->setText(QString::number(mpModel->getInitialTime()));
  mpEditInitialTime->setReadOnly(mpModel->isAutonomous());

  mpEditCurrentTime->setText(QString::number(mpModel->getTime()));

  return;
}

void CQModelWidget::save()
{
  if (mpModel == NULL)
    return;

  bool changed = false;

  if (TO_UTF8(mpEditName->text()) != mpModel->getObjectName())
    {
      mpModel->setTitle(TO_UTF8(mpEditName->text()));
      changed = true;
    }


  if (TO_UTF8(mpComboTimeUnit->currentText()) != mpModel->getTimeUnitName())
    {
      mpModel->setTimeUnit(TO_UTF8(mpComboTimeUnit->currentText()));
      changed = true;
    }

  if (TO_UTF8(mpComboVolumeUnit->currentText()) != mpModel->getVolumeUnitName())
    {
      mpModel->setVolumeUnit(TO_UTF8(mpComboVolumeUnit->currentText()));
      changed = true;
    }

  if (TO_UTF8(mpComboAreaUnit->currentText()) != mpModel->getAreaUnitName())
    {
      mpModel->setAreaUnit(TO_UTF8(mpComboAreaUnit->currentText()));
      changed = true;
    }

  if (TO_UTF8(mpComboLengthUnit->currentText()) != mpModel->getLengthUnitName())
    {
      mpModel->setLengthUnit(TO_UTF8(mpComboLengthUnit->currentText()));
      changed = true;
    }

  if (TO_UTF8(mpComboQuantityUnit->currentText()) != mpModel->getQuantityUnitName())
    {
      mpModel->setQuantityUnit(TO_UTF8(mpComboQuantityUnit->currentText()));
      changed = true;
    }

  if (TO_UTF8(mpComboModelType->currentText()) != std::string(CModel::ModelTypeNames[mpModel->getModelType()]))
    {
      mpModel->setModelType(toEnum(TO_UTF8(mpComboModelType->currentText()), CModel::ModelTypeNames, CModel::deterministic));
      changed = true;
    }

  if (mpEditInitialTime->text() != QString::number(mpModel->getInitialTime()))
    {
      mpModel->setInitialTime(mpEditInitialTime->text().toDouble());
      changed = true;
    }

  if (changed)
    {
      if (mpDataModel != NULL)
        {
          mpDataModel->changed();
        }

      protectedNotify(ListViews::MODEL, ListViews::CHANGE, mKey);
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
  mpBtnCommit->setFocus();

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
