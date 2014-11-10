// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQTimeSeriesWidget.h"
#include "CQTimeSeriesDM.h"
#include "CopasiFileDialog.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include <QSortFilterProxyModel>

#include "trajectory/CTrajectoryTask.h"
#include "crosssection/CCrossSectionTask.h"

CQTimeSeriesWidget::CQTimeSeriesWidget(QWidget* parent):
  CopasiWidget(parent),
  mpTimeSeries(NULL),
  mpDataModel(NULL)
{
  setupUi(this);

  mpDataModel = new CQTimeSeriesDM(this);

  // Allow for a sorted view of mpDataModel
  QSortFilterProxyModel * sortProxyModel = new QSortFilterProxyModel(parent);
  sortProxyModel->setSourceModel(mpDataModel);
  connect(mpDataModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)),
          sortProxyModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)));

  mpTableView->setModel(sortProxyModel);
}

CQTimeSeriesWidget::~CQTimeSeriesWidget()
{
  // TODO Auto-generated destructor stub
}

// virtual
bool CQTimeSeriesWidget::update(ListViews::ObjectType objectType,
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
bool CQTimeSeriesWidget::leave()
{
  return true;
}

void CQTimeSeriesWidget::setTitle(const QString &title)
{
  mpLblResult->setText(title);
}

const CTimeSeries* getTimeSeriesFromTask(const CCopasiTask * pTask)
{
  const CTrajectoryTask *traj = dynamic_cast<const CTrajectoryTask *>(pTask);

  if (traj != NULL)
    return &traj->getTimeSeries();

  const CCrossSectionTask* cross = dynamic_cast<const CCrossSectionTask *>(pTask);

  if (cross != NULL)
    return &cross->getTimeSeries();

  return NULL;
}

// virtual
bool CQTimeSeriesWidget::loadResult(const CCopasiTask * pTask)
{
  mpTimeSeries = getTimeSeriesFromTask(pTask);
  mpDataModel->setTimeSeries(mpTimeSeries);

  // mpTableView->resizeRowsToContents(); This is to slow
  int RowCount = mpDataModel->rowCount();

  if (RowCount > 0)
    {
      mpTableView->resizeRowToContents(0);
      int RowHeight = mpTableView->rowHeight(0);

      mpTableView->verticalHeader()->setDefaultSectionSize(RowHeight);
    }

  // mpTableView->resizeColumnsToContents(); This is to slow

  return true;
}

// virtual
void CQTimeSeriesWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);
  mpDataModel->setFramework(framework);
}

// virtual
bool CQTimeSeriesWidget::enterProtected()
{
  return true;
}

void CQTimeSeriesWidget::slotSave()
{
  if (mpTimeSeries == NULL) return;

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

  int failed = 0;

  QCursor oldCursor = cursor();
  setCursor(Qt::WaitCursor);
  failed = mpTimeSeries->save(TO_UTF8(fileName), (mFramework == 1), "\t");
  setCursor(oldCursor);

  if (failed)
    {
      std::string s = "Could not save data to ";
      s += TO_UTF8(fileName);
      CQMessageBox::critical(this, "Save Error", FROM_UTF8(s), QMessageBox::Ok, QMessageBox::Cancel);
    }
}
