// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQTimeSeriesWidget.h"
#include "CQTimeSeriesDM.h"
#include "CopasiFileDialog.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include <QSortFilterProxyModel>

#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/crosssection/CCrossSectionTask.h"

#ifdef WITH_TIME_SENS
#include "copasi/timesens/CTimeSensTask.h"
#endif // WITH_TIME_SENS

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
bool CQTimeSeriesWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  // We need to update the task when a new model is loaded.
  switch (objectType)
    {
      case ListViews::ObjectType::MODEL:

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
bool CQTimeSeriesWidget::leaveProtected()
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

#ifdef WITH_TIME_SENS
  const CTimeSensTask* sens = dynamic_cast<const CTimeSensTask *>(pTask);

  if (sens != NULL)
    return &sens->getTimeSeries();

#endif // WITH_TIME_SENS

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
                                          CopasiFileDialog::getDefaultFileName(".txt"), "TEXT Files (*.txt)", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, fileName);

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
