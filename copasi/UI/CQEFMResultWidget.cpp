// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "elementaryFluxModes/CEFMTask.h"
#include "elementaryFluxModes/CFluxMode.h"
#include "utilities/utility.h"
#include "commandline/CLocaleString.h"

CQEFMResultWidget::CQEFMResultWidget(QWidget* parent, const char* name) :
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
  mpReactionMatrix->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
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
  mpReactionMatrix->resizeColumnsToContents();

  mpSpeciesMatrix->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
  mpSpeciesMatrix->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
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
  mpSpeciesMatrix->resizeColumnsToContents();

  mpNetReactions->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
  mpNetReactions->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
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
  mpNetReactions->resizeColumnsToContents();
}

CQEFMResultWidget::~CQEFMResultWidget()
{
}

// virtual
bool CQEFMResultWidget::leave()
{
  return true;
}

// virtual
bool CQEFMResultWidget::update(ListViews::ObjectType objectType,
                               ListViews::Action action,
                               const std::string & /* key */)
{
  // We need to update the task when a new model is loaded.
  switch (objectType)
    {
      case ListViews::MODEL:

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
bool CQEFMResultWidget::loadResult(const CCopasiTask * pTask)
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
  mpReactionMatrix->resizeColumnsToContents();

  mpSpeciesDM->setTask(mpTask);

  mpProxyModelSpecies->setSourceModel(mpSpeciesDM);

  //Set Model for the TableView
  mpSpeciesMatrix->setModel(NULL);
  mpSpeciesMatrix->setModel(mpProxyModelSpecies);
  mpSpeciesMatrix->resizeColumnsToContents();

  mpNetReactionDM->setTask(mpTask);

  mpProxyModelNetReactions->setSourceModel(mpNetReactionDM);

  //Set Model for the TableView
  mpNetReactions->setModel(NULL);
  mpNetReactions->setModel(mpProxyModelNetReactions);
  mpNetReactions->resizeColumnsToContents();

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
                                          "untitled.txt", "TEXT Files (*.txt)", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(CLocaleString::fromUtf8(TO_UTF8(fileName)).c_str());

  if (file.fail())
    return;

  if (mpTask != NULL)
    file << mpTask->getResult();

  return;
}
