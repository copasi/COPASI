// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TimeSeriesSubwidget.ui.h,v $
//   $Revision: 1.27 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/07/03 10:21:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include <qpainter.h>
#include <q3picture.h>
#include <qlineedit.h>
#include <qcheckbox.h>

#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "CopasiFileDialog.h"

#include "optimization/COptProblem.h"
#include "optimization/COptTask.h"
#include "CopasiDataModel/CCopasiDataModel.h"

void TimeSeriesSubWidget::saveDataToFile()
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

  const CTimeSeries* timeSeries = this->table()->getTimeSeries();

  int failed = 0;

  if (timeSeries)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      failed = timeSeries->save(TO_UTF8(fileName), !(this->table()->doShowConcentrations()), "\t");
      setCursor(oldCursor);
    }

  if (failed)
    {
      std::string s = "Could not save data to ";
      s += TO_UTF8(fileName);
      CQMessageBox::critical(this, "Save Error", FROM_UTF8(s), QMessageBox::Ok, QMessageBox::Cancel);
    }
}

void TimeSeriesSubWidget::displayOptimizationTab(bool displayOptTab)
{
  if (displayOptTab)
    {
      tabWidget2->insertTab(tab, "OptimizationResults", 0);
      tabWidget2->setCurrentPage(0);
    }
  else
    tabWidget2->removePage(tab);
}

void TimeSeriesSubWidget::init()
{
  mFramework = 0;
  dataTable->setNumRows(10);
  displayOptimizationTab(false);
}

CTimeSeriesTable* TimeSeriesSubWidget::table()
{
  return dataTable;
}

void TimeSeriesSubWidget::setFramework(const int & framework)
{
  mFramework = framework;

  switch (mFramework)
    {
      case 0:
        dataTable->showConcentrations(true);
        break;

      case 1:
        dataTable->showConcentrations(false);
        break;
    }
}
