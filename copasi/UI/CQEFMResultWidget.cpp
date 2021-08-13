// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQEFMResultWidget.h"
#include "CQEFMNetReactionDM.h"
#include "CQEFMReactionDM.h"
#include "CQEFMSpeciesDM.h"
#include "CopasiFileDialog.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "copasi/elementaryFluxModes/CEFMTask.h"
#include "copasi/elementaryFluxModes/CFluxMode.h"
#include "copasi/utilities/utility.h"
#include "copasi/commandline/CLocaleString.h"
#include <copasi/core/CRootContainer.h>
#include <copasi/commandline/CConfigurationFile.h>

CQEFMResultWidget::CQEFMResultWidget(QWidget *parent, const char *name) :
  CopasiWidget(parent, name),
  mpTask(NULL),
  mpProxyModelReactions(NULL),
  mpReactionDM(NULL),
  mpProxyModelSpecies(NULL),
  mpSpeciesDM(NULL),
  mpProxyModelNetReactions(NULL),
  mpNetReactionDM(NULL)
{
  setupUi(this);
  mpReactionMatrix->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpReactionMatrix->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
  mpReactionMatrix->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
  mpReactionMatrix->verticalHeader()->hide();
  //Create Source Data Model.
  mpReactionDM = new CQEFMReactionDM(this);
  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModelReactions = new CQSortFilterProxyModel();
  mpProxyModelReactions->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModelReactions->setFilterKeyColumn(COL_REACTION_NAME);
  mpProxyModelReactions->setSourceModel(mpReactionDM);
  //Set Model for the TableView
  mpReactionMatrix->setModel(NULL);
  mpReactionMatrix->setModel(mpProxyModelReactions);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpReactionMatrix->resizeColumnsToContents();
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      mpSpeciesMatrix->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
      mpSpeciesMatrix->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
    }

  mpSpeciesMatrix->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
  mpSpeciesMatrix->verticalHeader()->hide();
  //Create Source Data Model.
  mpSpeciesDM = new CQEFMSpeciesDM(this);
  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModelSpecies = new CQSortFilterProxyModel();
  mpProxyModelSpecies->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModelSpecies->setFilterKeyColumn(COL_REACTION_NAME);
  mpProxyModelSpecies->setSourceModel(mpSpeciesDM);
  //Set Model for the TableView
  mpSpeciesMatrix->setModel(NULL);
  mpSpeciesMatrix->setModel(mpProxyModelSpecies);
  mpNetReactions->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpSpeciesMatrix->resizeColumnsToContents();
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      mpNetReactions->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
      mpNetReactions->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
    }

  mpNetReactions->verticalHeader()->hide();
  //Create Source Data Model.
  mpNetReactionDM = new CQEFMNetReactionDM(this);
  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModelNetReactions = new CQSortFilterProxyModel();
  mpProxyModelNetReactions->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModelNetReactions->setFilterKeyColumn(COL_REACTION_NAME);
  mpProxyModelNetReactions->setSourceModel(mpNetReactionDM);
  //Set Model for the TableView
  mpNetReactions->setModel(NULL);
  mpNetReactions->setModel(mpProxyModelNetReactions);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpNetReactions->resizeColumnsToContents();
    }
}

CQEFMResultWidget::~CQEFMResultWidget()
{
  pdelete(mpProxyModelNetReactions);
  pdelete(mpProxyModelReactions);
  pdelete(mpProxyModelSpecies);
}

// virtual
bool CQEFMResultWidget::leaveProtected()
{
  return true;
}

// virtual
bool CQEFMResultWidget::updateProtected(ListViews::ObjectType objectType,
                                        ListViews::Action action,
                                        const CCommonName & cn)
{
  // We need to update the task when a new model is loaded.
  switch (objectType)
    {
      case ListViews::ObjectType::MODEL:
      case ListViews::ObjectType::REACTION:
      case ListViews::ObjectType::METABOLITE:
        switch (action)
          {
            case ListViews::ADD:
            case ListViews::DELETE:
              loadResult(NULL);
              break;

            default:
              break;
          }

        break;

      default:
        break;
    }

  return true;
}

// virtual
bool CQEFMResultWidget::enterProtected()
{
  return true;
}

// virtual
bool CQEFMResultWidget::loadResult(const CCopasiTask *pTask)
{
  mpTask = dynamic_cast<const CEFMTask *>(pTask);

  if (mpTask != NULL)
    {
      mpEditFluxModes->setText(QString::number(mpTask->getFluxModes().size()));
    }
  else
    {
      mpEditFluxModes->setText(QString::number(0));
    }

  bool success = true;
  success &= mpEFMListWidget->loadResult(mpTask);
  mpReactionDM->setTask(mpTask);
  mpProxyModelReactions->setSourceModel(mpReactionDM);
  //Set Model for the TableView
  mpReactionMatrix->setModel(NULL);
  mpReactionMatrix->setModel(mpProxyModelReactions);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpReactionMatrix->resizeColumnsToContents();
    }

  mpSpeciesDM->setTask(mpTask);
  mpProxyModelSpecies->setSourceModel(mpSpeciesDM);
  //Set Model for the TableView
  mpSpeciesMatrix->setModel(NULL);
  mpSpeciesMatrix->setModel(mpProxyModelSpecies);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpSpeciesMatrix->resizeColumnsToContents();
    }

  mpNetReactionDM->setTask(mpTask);
  mpProxyModelNetReactions->setSourceModel(mpNetReactionDM);
  //Set Model for the TableView
  mpNetReactions->setModel(NULL);
  mpNetReactions->setModel(mpProxyModelNetReactions);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpNetReactions->resizeColumnsToContents();
    }

  return success;
}

void CQEFMResultWidget::slotSave()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          CopasiFileDialog::getDefaultFileName(".txt"), "TEXT Files (*.txt)", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(CLocaleString::fromUtf8(TO_UTF8(fileName)).c_str());

  if (file.fail())
    return;

  if (mpTask != NULL)
    file << mpTask->getResult();

  return;
}
