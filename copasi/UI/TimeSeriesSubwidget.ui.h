// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TimeSeriesSubwidget.ui.h,v $
//   $Revision: 1.22 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/27 18:46:47 $
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
#include <qpicture.h>
#include <qlineedit.h>
#include <qcheckbox.h>

#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "CopasiFileDialog.h"
#include "CQPrintAsDialog.h"

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
                                          QString::null, "TEXT Files (*.txt);;All Files (*.*);;", "Save to");

      //std::cout << "fileName: " << fileName << std::endl;
      if (fileName.isEmpty()) return;

      if (!fileName.endsWith(".txt") &&
          !fileName.endsWith(".")) fileName += ".txt";

      fileName = fileName.remove(QRegExp("\\.$"));

      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  const CTimeSeries* timeSeries = this->table()->getTimeSeries();
  int failed = 0;
  if (timeSeries)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      failed = timeSeries->save((const char *)fileName.utf8(), !(this->table()->doShowConcentrations()), "\t");
      setCursor(oldCursor);
    }
  if (failed)
    {
      std::string s = "Could not save data to ";
      s += fileName.utf8();
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

void TimeSeriesSubWidget::printTableAsImage()
{
  CQPrintAsDialog *pDialog = new CQPrintAsDialog();

  if (pDialog->exec() == QDialog::Accepted)
    {
      /*
            QString sFileName = pDialog->mpEditFileName->text();
            QFileInfo fileInfo(sFileName);
            QString sName = fileInfo.baseName();
      */
      QString sName = pDialog->mpEditFileName->text();

      QPixmap pixmap = QPixmap::grabWidget(tabWidget2->currentPage());

      if (pDialog->mpCBPNG->isChecked()) // true
        {
          QString sNamePNG = sName + ".png";
          pixmap.save(sNamePNG, "PNG");
        }

      if (pDialog->mpCBSVG->isChecked()) // true
        {
          QString sNameSVG = sName + ".svg";

          QPicture pict;
          QPainter paint;
          paint.begin(&pict);
          paint.drawPixmap(0, 0, pixmap);
          paint.end();

          pict.save(sNameSVG, "SVG");
        }
    }
}
