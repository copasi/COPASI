/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TimeSeriesSubwidget.ui.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/11/03 16:15:36 $
   End CVS Header */

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

#include "qtUtilities.h"

void TimeSeriesSubWidget::saveDataToFile()
{
  QString fileName = QFileDialog::getSaveFileName(QString::null, QString::null, this, 0, "Save to");
  std::cout << "fileName: " << fileName << std::endl;
  if (fileName.isEmpty()) return;
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
      QMessageBox::critical(this, "Save Error", FROM_UTF8(s), QMessageBox::Ok, QMessageBox::Cancel);
    }
}

void TimeSeriesSubWidget::toggleView()
{
  if (comboBox->currentItem() == 0)
    dataTable->showConcentrations(true);
  else
    dataTable->showConcentrations(false);
}

void TimeSeriesSubWidget::init()
{
  dataTable->setNumRows(10);
}

CTimeSeriesTable* TimeSeriesSubWidget::table()
{
  return dataTable;
}
