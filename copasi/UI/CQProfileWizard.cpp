// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQProfileWizard.h"

#include "copasi/resourcesUI/CQIconResource.h"
#include <QMessageBox>
#include <QFileDialog>

#include "qtUtilities.h"

void CQProfileWizard::loadPage(int index)
{
  auto * previousPage = tabWidget->widget(index);
  if (!previousPage)
    return;

  auto * pProfileWidget =
    index == 0   ? dynamic_cast< CQProfileWidget * >(wdgGenerate)
    : index == 1 ? dynamic_cast< CQProfileWidget * >(wdgProcess)
                 : dynamic_cast< CQProfileWidget * >(wdgPlot);

  if (!pProfileWidget)
    return;

  pProfileWidget->loadSettings(&mSettings);
}

void CQProfileWizard::savePage(int index)
{
  auto * previousPage = tabWidget->widget(index);
  if (!previousPage)
    return;

  auto * pProfileWidget =
    index == 0   ? dynamic_cast< CQProfileWidget * >(wdgGenerate)
    : index == 1 ? dynamic_cast< CQProfileWidget * >(wdgProcess)
                 : dynamic_cast< CQProfileWidget * >(wdgPlot);

  if (!pProfileWidget)
    return;

  pProfileWidget->saveSettings(&mSettings);
}

CQProfileWizard::CQProfileWizard(QWidget * parent, const CProfileSettings * pSettings)
  : QDialog(parent)
  , mSettings()
  , mCurrentPage(0)
{
#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin

  setupUi(this);

  if (pSettings)
    mSettings = *pSettings;

  loadPage(mCurrentPage);
}

void CQProfileWizard::onTabChanged(int index)
{
  savePage(mCurrentPage);
  mCurrentPage = index;
  loadPage(index);
}

void CQProfileWizard::open()
{
  QDialog::open();
}

void CQProfileWizard::reject()
{
  QMessageBox::StandardButton result = QMessageBox::question(
    this,
    "Close Profile Wizard",
    "Are you sure you want to close the Profile Wizard?\n"
    "Any unsaved changes will be lost.",
    QMessageBox::Yes | QMessageBox::No,
    QMessageBox::No);

  if (result == QMessageBox::Yes)
  {
    QDialog::reject();
  }
}

void CQProfileWizard::clearSetttings()
{
  mSettings = CProfileSettings();
  mSettings.load();

  loadPage(mCurrentPage);
}

void CQProfileWizard::loadSettings()
{
  // open file dialog and open *settings.json files

  QString file = QFileDialog::getOpenFileName(this, "Select Settings File", "", "Settings Files (*.json);;All files (*)");
  if (file.isEmpty())
    return;

  mSettings = CProfileSettings::fromFile(TO_UTF8(file));
  loadPage(mCurrentPage);
}

void CQProfileWizard::saveSettings()
{

  // open file dialog and save to *settings.json files
  QString file = QFileDialog::getSaveFileName(this, "Save Settings File", "", "Settings Files (*.json);;All files (*)");
  if (file.isEmpty())
    return;

  savePage(mCurrentPage);
  mSettings.saveToFile(TO_UTF8(file));
}
