// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CLNAResultSubwidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: jpahle $
//   $Date: 2011/05/24 17:33:45 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  CLNAResultSubwidget.cpp
 *
 *
 *  Created by Juergen Pahle on 2010-06-01.
 *
 */

#include "CLNAResultSubwidget.h"

#include <qfileinfo.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qpainter.h>
#include <q3picture.h>

#include <QMessageBox>

#include "copasi.h"

#include "qtUtilities.h"
#include "model/CModel.h"
#include "lna/CLNAMethod.h"
#include "utilities/CAnnotatedMatrix.h"

#include "report/CCopasiRootContainer.h"
#include "lna/CLNATask.h"
#include "UI/CopasiFileDialog.h"
#include "commandline/CLocaleString.h"

/*
 *  Constructs a CLNAResultSubwidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CLNAResultSubwidget::CLNAResultSubwidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : CopasiWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CLNAResultSubwidget::~CLNAResultSubwidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void CLNAResultSubwidget::init()
{
  /*
    mSaveButton->setEnabled(false);
    mSaveButton->hide();
  */
  mLNAMethod = NULL;

  clear();
}

void CLNAResultSubwidget::loadAll(const CLNAMethod * lnaMethod)
{
  mLNAMethod = lnaMethod;

  if (lnaMethod)
    {
      if (!lnaMethod->getModel())
        {
          clear();
          return;
        }

      if ((lnaMethod->getSteadyStateStatus() == CSteadyStateMethod::found) && (lnaMethod->getEigenValueStatus() == CLNAMethod::allNeg))
        {
          mTopLabel->setText("Steady State found.");
          this->loadCovarianceMatrix(lnaMethod);
          this->loadCovarianceMatrixReduced(lnaMethod);
          this->loadBMatrixReduced(lnaMethod);
          mTabWidget->setTabEnabled(mTabWidget->page(0), true);
          mTabWidget->setTabEnabled(mTabWidget->page(1), true);
          mTabWidget->setTabEnabled(mTabWidget->page(2), true);
        }
      else if ((lnaMethod->getSteadyStateStatus() == CSteadyStateMethod::foundEquilibrium) && (lnaMethod->getEigenValueStatus() == CLNAMethod::allNeg))
        {
          mTopLabel->setText("Equilibrium steady state.");
          this->loadCovarianceMatrix(lnaMethod);
          this->loadCovarianceMatrixReduced(lnaMethod);
          this->loadBMatrixReduced(lnaMethod);
          mTabWidget->setTabEnabled(mTabWidget->page(0), true);
          mTabWidget->setTabEnabled(mTabWidget->page(1), true);
          mTabWidget->setTabEnabled(mTabWidget->page(2), true);
        }
      else
        {
          if (lnaMethod->getSteadyStateStatus() == CSteadyStateMethod::foundNegative)
            {
              mTopLabel->setText("Invalid steady state (negative concentrations). No LNA calculated!");
            }
          else if (lnaMethod->getSteadyStateStatus() == CSteadyStateMethod::notFound)
            {
              mTopLabel->setText("No steady state found. No LNA calculated!");
            }
          else if (lnaMethod->getEigenValueStatus() == CLNAMethod::nonNegEigenvaluesExist)
            {
              mTopLabel->setText("The reduced system has non-negative Eigen values! No LNA calculated!");
            }

          /*
                this->loadCovarianceMatrix(lnaMethod);
                this->loadCovarianceMatrixReduced(lnaMethod);
                this->loadBMatrixReduced(lnaMethod);
          */

          mpArrayCovarianceMatrix->setArrayAnnotation(NULL);
          mpArrayCovarianceMatrixReduced->setArrayAnnotation(NULL);
          mpArrayBMatrixReduced->setArrayAnnotation(NULL);
        }
    }
  else
    {
      clear();
      return;
    }
}

void CLNAResultSubwidget::loadCovarianceMatrix(const CLNAMethod * lnaMethod)
{
  const CArrayAnnotation * covarianceMatrixAnn;

  if (mComboScale->currentItem() == 0)
    {
      covarianceMatrixAnn = lnaMethod->getScaledCovarianceMatrixAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayCovarianceMatrix->setColorCoding(tcs);
      mpArrayCovarianceMatrix->setColorScalingAutomatic(true);
    }
  else
    {
      covarianceMatrixAnn = lnaMethod->getUnscaledCovarianceMatrixAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayCovarianceMatrix->setColorCoding(tcs);
      mpArrayCovarianceMatrix->setColorScalingAutomatic(true);
    }

  mpArrayCovarianceMatrix->setArrayAnnotation(covarianceMatrixAnn);
}

void CLNAResultSubwidget::loadCovarianceMatrixReduced(const CLNAMethod * lnaMethod)
{
  const CArrayAnnotation * covarianceMatrixReducedAnn;

  if (mComboScale->currentItem() == 0)
    {
      covarianceMatrixReducedAnn = lnaMethod->getScaledCovarianceMatrixReducedAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayCovarianceMatrixReduced->setColorCoding(tcs);
      mpArrayCovarianceMatrixReduced->setColorScalingAutomatic(true);
    }
  else
    {
      covarianceMatrixReducedAnn = lnaMethod->getUnscaledCovarianceMatrixReducedAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayCovarianceMatrixReduced->setColorCoding(tcs);
      mpArrayCovarianceMatrixReduced->setColorScalingAutomatic(true);
    }

  mpArrayCovarianceMatrixReduced->setArrayAnnotation(covarianceMatrixReducedAnn);
}

void CLNAResultSubwidget::loadBMatrixReduced(const CLNAMethod * lnaMethod)
{
  const CArrayAnnotation * bMatrixReducedAnn;

  if (mComboScale->currentItem() == 0)
    {
      bMatrixReducedAnn = lnaMethod->getScaledBMatrixReducedAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayBMatrixReduced->setColorCoding(tcs);
      mpArrayBMatrixReduced->setColorScalingAutomatic(true);
    }
  else
    {
      bMatrixReducedAnn = lnaMethod->getUnscaledBMatrixReducedAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayBMatrixReduced->setColorCoding(tcs);
      mpArrayBMatrixReduced->setColorScalingAutomatic(true);
    }

  mpArrayBMatrixReduced->setArrayAnnotation(bMatrixReducedAnn);
}

void CLNAResultSubwidget::slotSave()
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

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiTask* mpTask =
    dynamic_cast<CLNATask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Linear Noise Approximation"]);

  if (mpTask != NULL)
    file << mpTask->getResult();

//    mpTask->printResult(file);

  return;
}

void CLNAResultSubwidget::slotScaled()
{
  loadAll(mLNAMethod);
}

void CLNAResultSubwidget::clear()
{
  mTopLabel->setText("No result available, please execute the LNA task.");

  mpArrayCovarianceMatrix->setArrayAnnotation(NULL);
  mpArrayCovarianceMatrixReduced->setArrayAnnotation(NULL);
  mpArrayBMatrixReduced->setArrayAnnotation(NULL);

  return;
}
