// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQTSSAResultSubWidget.ui.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/27 18:46:29 $
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

#include <qfileinfo.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qpainter.h>
#include <qpicture.h>

#include "qtUtilities.h"
#include "CopasiFileDialog.h"
#include "CQPrintAsDialog.h"
#include "optimization/COptProblem.h"
#include "optimization/COptTask.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "CQTSSATimeScaleWidget.h"
#include "tssanalysis/CTSSATask.h"
#include "tssanalysis/CTSSAProblem.h"

//#include "tssanalysis/CILDMMethod.h"
#include "tssanalysis/CTSSAMethod.h"

#include "utilities/CAnnotatedMatrix.h"
#include "model/CModel.h"

CTSSATask* pTSSTask;
CTSSAProblem* pProblem;
CTSSAMethod* pTimeScaleSeperation;

CQTSSATimeScaleWidget* mpTimeScaleWidget;

CModel* pModel;

const CArrayAnnotation * pResult;
const CArrayAnnotation * pResult2;
const CArrayAnnotation * pResult3;
const CArrayAnnotation * pResult4;

void CQTSSAResultSubWidget::saveDataToFile()
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
      QMessageBox::critical(this, "Save Error", FROM_UTF8(s), QMessageBox::Ok, QMessageBox::Cancel);
    }
}

void CQTSSAResultSubWidget::displayOptimizationTab(bool displayOptTab)
{
  if (displayOptTab)
    {
      tabWidget2->insertTab(tab, "OptimizationResults", 0);
      tabWidget2->setCurrentPage(0);
    }
  else
    tabWidget2->removePage(tab);
}

void CQTSSAResultSubWidget::toggleView()
{
  if (comboBox->currentItem() == 0)
    dataTable->showConcentrations(true);
  else
    dataTable->showConcentrations(false);
}

void CQTSSAResultSubWidget::init()
{
  mpTimeScaleWidget = new CQTSSATimeScaleWidget();
  mTabWidget->addTab(mpTimeScaleWidget, "Timescale");

  //set colorsettings for ArrayAnnotationWidgets
  CColorScaleAdvanced * tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));

  // mVslow_metab widget
  pArrayWidget->setColorCoding(tcs);
  pArrayWidget->setColorScalingAutomatic(true);
  // mVslow widget
  pArrayWidget2->setColorCoding(tcs);
  pArrayWidget2->setColorScalingAutomatic(true);
  // mVslow_space widget
  pArrayWidget3->setColorCoding(tcs);
  pArrayWidget3->setColorScalingAutomatic(true);
  // mVslow_space widget
  pArrayWidget4->setColorCoding(tcs);
  pArrayWidget4->setColorScalingAutomatic(true);

  connect(mSlider, SIGNAL(valueChanged(int)), this, SLOT(changeInterval()));
  connect(tabWidget2, SIGNAL(currentChanged(QWidget *)), this, SLOT(hideButtons()));

  dataTable->setNumRows(10);
  displayOptimizationTab(false);
}

CTimeSeriesTable* CQTSSAResultSubWidget::table()
{
  return dataTable;
}

/**
 * Fill the combobox mpSelectStep with count of steps the ILDM
 * Method is calculating with.
 **/
void CQTSSAResultSubWidget::setStepNumber()
{
  CTSSATask* pTSSTask =
    dynamic_cast<CTSSATask *>((*CCopasiDataModel::Global->getTaskList())["Time Scale Separation Analysis"]);
  if (!pTSSTask) return;
  pTimeScaleSeperation = dynamic_cast<CTSSAMethod*>(pTSSTask->getMethod());
  pProblem = dynamic_cast<CTSSAProblem*>(pTSSTask->getProblem());
  CModel* pModel = pProblem->getModel();
  QString a = FROM_UTF8(pModel->getTimeUnitName());
  mLabel7->setText(a);
  mLabel6->setNum((double)pProblem->getStepNumber());
  mSlider->setRange(1, pProblem->getStepNumber());
  mSlider->setValue(mSlider->minValue());
  changeInterval();
}

/**
 * Clear ArrayAnnotation-widgets.
 **/
void CQTSSAResultSubWidget::discardOldResults()
{
  pArrayWidget->setArrayAnnotation(NULL);
  pArrayWidget2->setArrayAnnotation(NULL);
  pArrayWidget3->setArrayAnnotation(NULL);
  pArrayWidget4->setArrayAnnotation(NULL);

  mpTimeScaleWidget->clearWidget();

  mLabel2->setNum(0);
  mLabel4->setNum(0);
  mLabel6->setNum(0);
}

/**
 * Get the results for the requested step from ILDM-method.
 * Fill widgets with this results.
 **/
void CQTSSAResultSubWidget::changeInterval()
{
  int step = mSlider->value();

  if (step == 1)
    mLabel2->setNum(0);
  else
    mLabel2->setNum((double)pTimeScaleSeperation->returnCurrentTime(step - 2));

  mLabel4->setNum(step);

  pTimeScaleSeperation->setAnnotationM(step);
  pResult = pTimeScaleSeperation->getVslowPrintAnn();
  pResult2 = pTimeScaleSeperation->getVslowMetabPrintAnn();
  pResult3 = pTimeScaleSeperation->getVslowSpacePrintAnn();
  pResult4 = pTimeScaleSeperation->getVfastSpacePrintAnn();
  pArrayWidget->setArrayAnnotation(pResult);
  pArrayWidget2->setArrayAnnotation(pResult2);
  pArrayWidget3->setArrayAnnotation(pResult3);
  pArrayWidget4->setArrayAnnotation(pResult4);
  mpTimeScaleWidget->paintTimeScale(pTimeScaleSeperation->getVec_TimeScale(step));
}

/**
 * Hide the above buttons if ILDM-tab is currently active.
 **/
void CQTSSAResultSubWidget::hideButtons()
{
  if (tabWidget2->currentPageIndex() == 1)
    {
      ButtonSaveData->setDisabled(true);
      comboBox->setDisabled(true);
    }
  else
    {
      ButtonSaveData->setEnabled(true);
      comboBox->setEnabled(true);
    }
}
/**
 * Able / Disable the slider.
 **/
void CQTSSAResultSubWidget::setStepSelectionDisabled(bool set)
{
  mSlider->setDisabled(set);
}

void CQTSSAResultSubWidget::activateTab(int tab)
{
  tabWidget2->setCurrentPage(tab);
}

void CQTSSAResultSubWidget::printAsImage()
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
