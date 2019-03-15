// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*
 * CBrowseModelVersionDialog.cpp
 *
 *  Created on: 21 Feb 2016
 *      Author: Peyman Zarrineh
 */

#include "../versioningUI/CBrowseModelVersionDialog.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QDir>

#include "copasi/versioningUI/ui_CBrowseModelVersionDialog.h"
#include "copasi/versioningUI/CQModelVersionHierarchyDM.h"

#include "copasi/UI/qtUtilities.h"
#include "copasi/UI/CQCopasiApplication.h"
#include "copasi/UI/copasiui3window.h"
#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/DataModelGUI.h"

#include "copasi/CopasiDataModel/CDataModel.h"

#ifdef COPASI_Provenance
#include "copasi/Provenance/CProvenanceXMLWriter.h"
#endif

CBrowseModelVersionDialog::CBrowseModelVersionDialog(QWidget *parent,
    DataModelGUI * pDataModelGUI,
    CDataModel * pDataModel
#ifdef COPASI_Provenance
//                                                     , QString PathProvenance,   QString ProvenanceParentOfCurrentModel
    , QString PathProvenance
#endif
                                                    ) :
  QDialog(parent),
  ui(new Ui::CBrowseModelVersionDialog),
  mpModelVersion(NULL),
  mpModelVersionDM(NULL),
  mpDataModelGUI(pDataModelGUI),
  mpDataModel(pDataModel)
{
  ui->setupUi(this);
  //mLastSavedParentOfCurrentModel = LastSavedParentOfCurrentModel;
  // set "the dialog table pointer" points to main table in the table of this dialog

  mpModelVersion = mpDataModel->getModelVersionHierarchy();
  mpModelVersion->readVersionXML();

  mpModelVersionDM = new CQModelVersionHierarchyDM(this);
  mpModelVersionDM->setModelVersionHierarchy(mpModelVersion);

  ui->tableView->setModel(mpModelVersionDM);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  ui->DeleteButton->setEnabled(false);
  ui->RestoreButton->setEnabled(false);
  ui->CloseButton->setEnabled(true);
  ui->tableView->setEnabled(true);
#ifdef COPASI_Provenance
  mPathProvenance = PathProvenance;
  //mProvenanceParentOfCurrentModel =  ProvenanceParentOfCurrentModel;
#endif
}

CBrowseModelVersionDialog::~CBrowseModelVersionDialog()
{
  delete ui;
}

void CBrowseModelVersionDialog::slotRestoreButtonClicked()
{
  QModelIndex selectedIndex = mpModelVersionDM->index(ui->tableView->currentIndex().row(), (int) CQModelVersionHierarchyDM::Column::Name);
  QString Version = mpModelVersionDM->data(selectedIndex, Qt::DisplayRole).toString();

  switch (CQMessageBox::question(this,
                                 "Version Restore Question",
                                 "The current model will be replaced. All changes made after the last version save will be lost. To keep the current model please create a new version. Do you still want to restore this version?",
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Cancel))
    {
      case QMessageBox::Ok:
      {
        int i = mpModelVersion->restoreVersion(TO_UTF8(Version));

        if (i == 1)
          {
            QMessageBox::about(this, tr("Error"), tr("Version name is empty"));
          }
        else if (i == 2)
          {
            QMessageBox::about(this, tr("Error"), tr("Version name does not exist in version hierarchy"));
          }
        else
          {
            CQCopasiApplication::instance()->getMainWindow()->slotFileOpen(FROM_UTF8((mpDataModel->getFileName())));
          }

        ui->DeleteButton->setEnabled(false);
        ui->RestoreButton->setEnabled(false);
        ui->CloseButton->setEnabled(true);
        ui->tableView->setEnabled(true);
      }
      break;

      case QMessageBox::Cancel:
      {
        ui->DeleteButton->setEnabled(false);
        ui->RestoreButton->setEnabled(false);
        ui->CloseButton->setEnabled(true);
        ui->tableView->setEnabled(true);
      }
    }
}

void CBrowseModelVersionDialog::slotDeleteButtonClicked()
{
  QModelIndex selectedIndex = mpModelVersionDM->index(ui->tableView->currentIndex().row(), (int) CQModelVersionHierarchyDM::Column::Name);
  QString Version = mpModelVersionDM->data(selectedIndex, Qt::DisplayRole).toString();

  switch (CQMessageBox::question(this,
                                 "Version Delete Question",
                                 "Are you sure you want delete this version?",
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Cancel))
    {
      case QMessageBox::Ok:
      {
        int i;
        //bool isParrentOfLastSavedVersion = false;
        //if(mLastSavedParentOfCurrentModel==Version)
        //{
        //    isParrentOfLastSavedVersion = true;
        //    ParentVersion = mpModelVersion->getParentVersion(Version);
        //}
#ifdef COPASI_Provenance
        bool isParrentOfCurrentVersion = false;
        QString ParentOfCurrentModel = FROM_UTF8(mpModelVersion->getCurrentVersion().mParentName);

        if (ParentOfCurrentModel == Version)
          {
            isParrentOfCurrentVersion = true;
          }

        QList<QString> ChildrenVersions = mpModelVersion->getChildrenOfVersionForProvenanceXML(Version);
#endif

        i = mpModelVersion->deleteVersion(TO_UTF8(Version));
        mpModelVersionDM->setModelVersionHierarchy(mpModelVersion);

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

        ui->DeleteButton->setEnabled(false);
        ui->RestoreButton->setEnabled(false);
        ui->CloseButton->setEnabled(true);
        ui->tableView->setEnabled(true);
      }
      break;

      case QMessageBox::Cancel:
        ui->DeleteButton->setEnabled(false);
        ui->RestoreButton->setEnabled(false);
        ui->CloseButton->setEnabled(true);
        ui->tableView->setEnabled(true);
        break;
    }
}

void CBrowseModelVersionDialog::slotRowSelected(QModelIndex /* index */)
{
  ui->DeleteButton->setEnabled(true);
  ui->RestoreButton->setEnabled(true);
  ui->CloseButton->setEnabled(true);
  ui->tableView->setEnabled(true);
}

//#ifdef COPASI_Provenance
//QString CBrowseModelVersionDialog::getProvenanceParentOfCurrentModel()
//{
//  return(mProvenanceParentOfCurrentModel);
//}

//#endif

//QString CBrowseModelVersionDialog::getLastSavedParentOfCurrentModel()
//{
//    return(mLastSavedParentOfCurrentModel);
//}
