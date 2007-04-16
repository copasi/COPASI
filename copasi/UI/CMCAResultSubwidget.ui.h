// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CMCAResultSubwidget.ui.h,v $
//   $Revision: 1.21.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/04/16 14:40:21 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "UI/qtUtilities.h"

#include "model/CModel.h"
#include "steadystate/CMCAMethod.h"
#include "utilities/CAnnotatedMatrix.h"

void CMCAResultSubwidget::init()
{
  mSaveButton->setEnabled(false);
  mSaveButton->hide();

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
{}

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
