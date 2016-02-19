// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CBrowseModelVersionDialog.cpp
 *
 *  Created on: 21 Feb 2016
 *      Author: Peyman Zarrineh
 */

#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include "CBrowseModelVersionDialog.h"
#include "ui_CBrowseModelVersionDialog.h"

CBrowseModelVersionDialog::CBrowseModelVersionDialog(QWidget *parent, CModelVersion  * ModelVersion, DataModelGUI * ModelGUI) :
  QDialog(parent),
  ui(new Ui::CBrowseModelVersionDialog)
{
  ui->setupUi(this);

  // set "the dialog table pointer" points to main table in the table of this dialog

  int NumberOfVersions = ModelVersion->getNumberOfVersions();
  mpModelVersion = ModelVersion;
  mpDataModelGUI = ModelGUI;
  int i;
  ui->tableView->setModel(mpModelVersion->getModelVersionHierarchy());
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  for (i = NumberOfVersions; i < mpModelVersion->getModelVersionHierarchy()->rowCount(); i++)
    {
      ui->tableView->setRowHidden(i, true);
    }

  ui->tableView->setColumnHidden(4, true);
  ui->tableView->setColumnHidden(5, true);
  ui->DeleteButton->setEnabled(false);
  ui->RestoreButton->setEnabled(false);
  ui->CloseButton->setEnabled(true);
  ui->tableView->setEnabled(true);
}

CBrowseModelVersionDialog::~CBrowseModelVersionDialog()
{
  delete ui;
}

void CBrowseModelVersionDialog::on_RestoreButton_clicked()
{

  QModelIndex selectedIndex = ui->tableView->currentIndex();
  QString Version = mpModelVersion->getModelVersionHierarchy()->item(selectedIndex.row(), 0)->text();
  QMessageBox msgBox;
  msgBox.setWindowTitle("Version Restoring Warning");
  msgBox.setText("The current model will be replaced, losing edits. To keep the current model create a version. Do you still want to restore this version?");
  msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  int ret = msgBox.exec();

  switch (ret)
    {
      case QMessageBox::Ok:
      {
        int i = mpModelVersion->restoreVersion(Version);

        if (i == 1)
          {
            QMessageBox::about(this, tr("Error"), tr("Version name is empty"));
          }

        if (i == 2)
          {
            QMessageBox::about(this, tr("Error"), tr("Version name does not exist in version hierarchy"));
          }

        // Load the selected version in combined archive as the current model
        if (i == 0)
          {
            QString dataFile;

            if (mpModelVersion->getPathFile() == "")
              {
                dataFile = Version;
              }
            else
              {
                dataFile = mpModelVersion->getPathFile() +  "/" + Version;
              }

            QFile Fout(dataFile);

            if (!Fout.exists())
              {
                QMessageBox::about(this, tr("Error"), tr("Version file does not exist in the folder"));
              }
            else
              {
                mpDataModelGUI->loadModel(dataFile.toStdString());
              }
          }

        ui->DeleteButton->setEnabled(false);
        ui->RestoreButton->setEnabled(false);
        ui->CloseButton->setEnabled(true);
        ui->tableView->setEnabled(true);
      }

      case QMessageBox::Cancel:
      {
        ui->DeleteButton->setEnabled(false);
        ui->RestoreButton->setEnabled(false);
        ui->CloseButton->setEnabled(true);
        ui->tableView->setEnabled(true);
      }
    }
}

void CBrowseModelVersionDialog::on_DeleteButton_clicked()
{
  QModelIndex selectedIndex = ui->tableView->currentIndex();
  QString Version = mpModelVersion->getModelVersionHierarchy()->item(selectedIndex.row(), 0)->text();
  QMessageBox::NoIcon;
  QMessageBox msgBox;
  msgBox.setWindowTitle("Version Deletion Warning");
  msgBox.setText("Are you sure you want delete this version?");
  msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  int ret = msgBox.exec();

  switch (ret)
    {
      case QMessageBox::Ok:
      {
        int i;
        i = mpModelVersion->deleteVersion(Version);

        if (i == 1)
          {
            QMessageBox::about(this, tr("Error"), tr("Version name is empty"));
          }

        if (i == 2)
          {
            QMessageBox::about(this, tr("Error"), tr("Version name does not exist in version hierarchy"));
          }

        if (i == 3)
          {
            QMessageBox::about(this, tr("Error"), tr("Root version cannot be deleted in the presence of any other version"));
          }

        // Delete the selected version from
        if (i == 0)
          {
            QDir destination;
            QString dataFile;// = mpModelVersionHierarchy->getPathFile() + QLatin1Char('/') + QString("VersionHierarchy.xml");

            if (mpModelVersion->getPathFile() == "")
              {
                dataFile = Version;
              }
            else
              {
                dataFile = mpModelVersion->getPathFile() + "/" + Version;
              }

            destination.remove(dataFile);
          }

        int NumberOfVersions = mpModelVersion->getNumberOfVersions();
        ui->tableView->setModel(mpModelVersion->getModelVersionHierarchy());
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for (i = NumberOfVersions; i < mpModelVersion->getModelVersionHierarchy()->rowCount(); i++)
          {
            ui->tableView->setRowHidden(i, true);
          }

        ui->tableView->setColumnHidden(4, true);
        ui->tableView->setColumnHidden(5, true);

        ui->DeleteButton->setEnabled(false);
        ui->RestoreButton->setEnabled(false);
        ui->CloseButton->setEnabled(true);
        ui->tableView->setEnabled(true);
      }

      case QMessageBox::Cancel:
      {
        ui->DeleteButton->setEnabled(false);
        ui->RestoreButton->setEnabled(false);
        ui->CloseButton->setEnabled(true);
        ui->tableView->setEnabled(true);
      }
    }
}

void CBrowseModelVersionDialog::on_tableView_clicked()
{
  ui->DeleteButton->setEnabled(true);
  ui->RestoreButton->setEnabled(true);
  ui->CloseButton->setEnabled(true);
  ui->tableView->setEnabled(true);
}

void CBrowseModelVersionDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
  if (index.column() == mpModelVersion->getModelVersionHierarchy()->columnCount() - 1)
    {
      QString text = QInputDialog::getText(this, tr("Update Comments"), tr("Update selected Comments:"), QLineEdit::Normal);

      if (text.isEmpty() == false)
        {
          mpModelVersion->updateSelectedCell(index, text);
        }
    }
}
