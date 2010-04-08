// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/03/21 15:21:13 $
// End CVS Header
// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  CMCAResultSubwidget.cpp
 *
 *
 *  Created by Paul on 4/2/10.
 *
 */

#include "CMCAResultSubwidget.h"

#include <qfileinfo.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qpainter.h>
#include <q3picture.h>

#include <QMessageBox>

#include "copasi.h"

#include "qtUtilities.h"
#include "model/CModel.h"
#include "steadystate/CMCAMethod.h"
#include "utilities/CAnnotatedMatrix.h"

#include "report/CCopasiRootContainer.h"
#include "steadystate/CMCATask.h"
#include "UI/CopasiFileDialog.h"

/*
 *  Constructs a CMCAResultSubwidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CMCAResultSubwidget::CMCAResultSubwidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : CopasiWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CMCAResultSubwidget::~CMCAResultSubwidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CMCAResultSubwidget::languageChange()
{
  retranslateUi(this);
}

void CMCAResultSubwidget::init()
{
  /*
    mSaveButton->setEnabled(false);
    mSaveButton->hide();
  */
  mMCAMethod = NULL;

  clear();
}

void CMCAResultSubwidget::loadAll(const CMCAMethod * mcaMethod)
{
  mMCAMethod = mcaMethod;

  if (mcaMethod)
    {
      if (!mcaMethod->getModel())
        {
          clear();
          return;
        }

      if (mcaMethod->getSteadyStateStatus() == CSteadyStateMethod::found)
        {
          mTopLabel->setText("Steady State found. All coefficients available.");
          this->loadElasticities(mcaMethod);
          this->loadConcentrationCCs(mcaMethod);
          this->loadFluxCCs(mcaMethod);
          mTabWidget->setTabEnabled(mTabWidget->page(1), true);
          mTabWidget->setTabEnabled(mTabWidget->page(2), true);
        }
      else
        {
          this->loadElasticities(mcaMethod);
          mTabWidget->setTabEnabled(mTabWidget->page(1), false);
          mTabWidget->setTabEnabled(mTabWidget->page(2), false);

          if (mcaMethod->getSteadyStateStatus() == CSteadyStateMethod::foundEquilibrium)
            mTopLabel->setText("Equilibrium steady state. Only elasticities available!");

          if (mcaMethod->getSteadyStateStatus() == CSteadyStateMethod::foundNegative)
            mTopLabel->setText("Invalid steady state (negative concentrations)!");

          if (mcaMethod->getSteadyStateStatus() == CSteadyStateMethod::notFound)
            mTopLabel->setText("No steady state found. Only elasticities available!");
        }
    }
  else
    {
      clear();
      return;
    }
}

void CMCAResultSubwidget::loadElasticities(const CMCAMethod * mcaMethod)
{
  //   const CModel* model = mcaMethod->getModel();
  //   assert(model);
  //   unsigned C_INT32 numRows, numCols;
  //   numRows = model->getTotSteps();
  //   numCols = model->getMetabolitesX().size();
  //   mTableElasticities->setNumRows(numRows);
  //   mTableElasticities->setNumCols(numCols);
  //   unsigned C_INT32 i, j;
  //   QHeader* header = mTableElasticities->verticalHeader();
  //   for (i = 0; i < numRows;++i)
  //     {
  //       header->setLabel(i, FROM_UTF8(model->getReactions()[i]->getObjectName()));
  //}
  //   header = mTableElasticities->horizontalHeader();
  //   for (i = 0; i < numCols;++i)
  //     {
  //       header->setLabel(i, FROM_UTF8(model->getMetabolitesX()[i]->getObjectName()));
  //}
  //   const CMatrix<C_FLOAT64> & elasticities = (mComboScale->currentItem() == 0) ? mcaMethod->getScaledElasticities() : mcaMethod->getUnscaledElasticities();
  //   if (elasticities.numRows() == 0 || elasticities.numCols() == 0) return;
  //   for (i = 0; i < numRows;++i)
  //     {
  //       for (j = 0; j < numCols;++j)
  //         {
  //           mTableElasticities->setText(i, j, QString::number(elasticities[i][j]));
  //}
  //}

  const CArrayAnnotation * elasticitiesAnn;

  if (mComboScale->currentItem() == 0)
    {
      elasticitiesAnn = mcaMethod->getScaledElasticitiesAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayElasticities->setColorCoding(tcs);
      mpArrayElasticities->setColorScalingAutomatic(true);
    }
  else
    {
      elasticitiesAnn = mcaMethod->getUnscaledElasticitiesAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayElasticities->setColorCoding(tcs);
      mpArrayElasticities->setColorScalingAutomatic(true);
    }

  mpArrayElasticities->setArrayAnnotation(elasticitiesAnn);
}

void CMCAResultSubwidget::loadConcentrationCCs(const CMCAMethod * mcaMethod)
{
  /*  const CModel* model = mcaMethod->getModel();
    assert(model);
    unsigned C_INT32 numRows, numCols;
    numRows = model->getNumVariableMetabs();
    numCols = model->getTotSteps();
    mTableCCC->setNumRows(numRows);
    mTableCCC->setNumCols(numCols);
    unsigned C_INT32 i, j;
    QHeader* header = mTableCCC->verticalHeader();
    for (i = 0; i < numRows;++i)
      {
        header->setLabel(i, FROM_UTF8(model->getMetabolitesX()[i]->getObjectName()));
      }
    header = mTableCCC->horizontalHeader();
    for (i = 0; i < numCols;++i)
      {
        header->setLabel(i, FROM_UTF8(model->getReactions()[i]->getObjectName()));
      }
    const CMatrix<C_FLOAT64> & CCCs = (mComboScale->currentItem() == 0) ? mcaMethod->getScaledConcentrationCC() : mcaMethod->getUnscaledConcentrationCC();
    if (CCCs.numRows() == 0 || CCCs.numCols() == 0) return;
    for (i = 0; i < numRows;++i)
      {
        for (j = 0; j < numCols;++j)
          {
            mTableCCC->setText(i, j, QString::number(CCCs[i][j]));
          }
      }*/
  const CArrayAnnotation * CCCAnn;

  if (mComboScale->currentItem() == 0)
    {
      CCCAnn = mcaMethod->getScaledConcentrationCCAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayCCC->setColorCoding(tcs);
      mpArrayCCC->setColorScalingAutomatic(true);
    }
  else
    {
      CCCAnn = mcaMethod->getUnscaledConcentrationCCAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayCCC->setColorCoding(tcs);
      mpArrayCCC->setColorScalingAutomatic(true);
    }

  mpArrayCCC->setArrayAnnotation(CCCAnn);
}

void CMCAResultSubwidget::loadFluxCCs(const CMCAMethod * mcaMethod)
{
  /*  const CModel* model = mcaMethod->getModel();
    assert(model);
    unsigned C_INT32 numRows, numCols;
    numCols = numRows = model->getTotSteps();
    mTableFCC->setNumRows(numRows);
    mTableFCC->setNumCols(numCols);

    unsigned C_INT32 i, j;
    QHeader* header = mTableFCC->verticalHeader();
    for (i = 0; i < numRows;++i)
      {
        header->setLabel(i, FROM_UTF8(model->getReactions()[i]->getObjectName()));
      }
    header = mTableFCC->horizontalHeader();
    for (i = 0; i < numCols;++i)
      {
        header->setLabel(i, FROM_UTF8(model->getReactions()[i]->getObjectName()));
      }
    const CMatrix<C_FLOAT64> & FCCs = (mComboScale->currentItem() == 0) ? mcaMethod->getScaledFluxCC() : mcaMethod->getUnscaledFluxCC();
    if (FCCs.numRows() == 0 || FCCs.numCols() == 0) return;
    for (i = 0; i < numRows;++i)
      {
        for (j = 0; j < numCols;++j)
          {
            mTableFCC->setText(i, j, QString::number(FCCs[i][j]));
          }
      }*/

  const CArrayAnnotation * FCCAnn;

  if (mComboScale->currentItem() == 0)
    {
      FCCAnn = mcaMethod->getScaledFluxCCAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayFCC->setColorCoding(tcs);
      mpArrayFCC->setColorScalingAutomatic(true);
    }
  else
    {
      FCCAnn = mcaMethod->getUnscaledFluxCCAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayFCC->setColorCoding(tcs);
      mpArrayFCC->setColorScalingAutomatic(true);
    }

  mpArrayFCC->setArrayAnnotation(FCCAnn);
}

void CMCAResultSubwidget::slotSave()
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

  std::ofstream file(utf8ToLocale(TO_UTF8(fileName)).c_str());

  if (file.fail())
    return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiTask* mpTask =
    dynamic_cast<CMCATask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Metabolic Control Analysis"]);

  if (mpTask != NULL)
    file << mpTask->getResult();

//    mpTask->printResult(file);

  return;
}

void CMCAResultSubwidget::slotScaled()
{
  loadAll(mMCAMethod);
}

void CMCAResultSubwidget::clear()
{
  mTopLabel->setText("No result available, please execute the MCA task.");

  //   mTableElasticities->setNumRows(0);
  //   mTableElasticities->setNumCols(0);
  //
  //   mTableCCC->setNumRows(0);
  //   mTableCCC->setNumCols(0);
  //
  //   mTableFCC->setNumRows(0);
  //   mTableFCC->setNumCols(0);

  mpArrayElasticities->setArrayAnnotation(NULL);
  mpArrayFCC->setArrayAnnotation(NULL);
  mpArrayCCC->setArrayAnnotation(NULL);

  return;
}
