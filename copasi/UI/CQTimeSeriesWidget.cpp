// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTimeSeriesWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/01/06 19:14:16 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQTimeSeriesWidget.h"
#include "CQTimeSeriesDM.h"
#include "CopasiFileDialog.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "trajectory/CTrajectoryTask.h"

CQTimeSeriesWidget::CQTimeSeriesWidget(QWidget* parent):
    CopasiWidget(parent),
    mpTask(NULL),
    mpDataModel(NULL)
{
  setupUi(this);

  mpDataModel = new CQTimeSeriesDM(this);
  mpTableView->setModel(mpDataModel);
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

// virtual
bool CQTimeSeriesWidget::loadResult(const CCopasiTask * pTask)
{
  mpTask = dynamic_cast<const CTrajectoryTask *>(pTask);

  if (mpTask != NULL)
    {
      mpDataModel->setTimeSeries(&mpTask->getTimeSeries());
    }
  else
    {
      mpDataModel->setTimeSeries(NULL);
    }

  // mpTableView->resizeRowsToContents(); This is to slow
  int RowCount = mpDataModel->rowCount();

  if (RowCount > 0)
    {
      mpTableView->resizeRowToContents(0);
      int RowHeight = mpTableView->rowHeight(0);

      for (int i = 1; i < RowCount; ++i)
        {
          mpTableView->setRowHeight(i, RowHeight);
        }
    }

  // mpTableView->resizeColumnsToContents(); This is to slow

  return true;
}

// virtual
void CQTimeSeriesWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);
  mpDataModel->setFramework(framework);
  mpTableView->resizeColumnsToContents();
  mpTableView->resizeRowsToContents();
}

// virtual
bool CQTimeSeriesWidget::enterProtected()
{
  return true;
}

void CQTimeSeriesWidget::slotSave()
{
  if (mpTask == NULL) return;

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

  const CTimeSeries & TimeSeries = mpTask->getTimeSeries();

  int failed = 0;

  QCursor oldCursor = cursor();
  setCursor(Qt::WaitCursor);
  failed = TimeSeries.save(TO_UTF8(fileName), (mFramework == 1), "\t");
  setCursor(oldCursor);

  if (failed)
    {
      std::string s = "Could not save data to ";
      s += TO_UTF8(fileName);
      CQMessageBox::critical(this, "Save Error", FROM_UTF8(s), QMessageBox::Ok, QMessageBox::Cancel);
    }
}
