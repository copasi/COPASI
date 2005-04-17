/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CMCAResultSubwidget.ui.h,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/17 20:09:15 $
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
#include "utilities/CAnnotatedMatrix.h"

void CMCAResultSubwidget::init()
{
  mTopLabel->setText("");
  mSaveButton->setEnabled(false);
  mSaveButton->hide();
}

void CMCAResultSubwidget::loadAll(const CMCAMethod * mcaMethod)
{
  if (mcaMethod)
    {
      mMCAMethod = mcaMethod;
      if (!mcaMethod->getModel()) return;

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
}

void CMCAResultSubwidget::loadElasticities(const CMCAMethod * mcaMethod)
{
  const CModel* model = mcaMethod->getModel();
  assert(model);
  unsigned C_INT32 numRows, numCols;
  numRows = model->getTotSteps();
  numCols = model->getMetabolitesX().size();
  mTableElasticities->setNumRows(numRows);
  mTableElasticities->setNumCols(numCols);
  unsigned C_INT32 i, j;
  QHeader* header = mTableElasticities->verticalHeader();
  for (i = 0; i < numRows;++i)
    {
      header->setLabel(i, FROM_UTF8(model->getReactionsX()[i]->getObjectName()));
    }
  header = mTableElasticities->horizontalHeader();
  for (i = 0; i < numCols;++i)
    {
      header->setLabel(i, FROM_UTF8(model->getMetabolitesX()[i]->getObjectName()));
    }
  const CAnnotatedMatrix & elasticities = (mComboScale->currentItem() == 0) ? mcaMethod->getScaledElasticities() : mcaMethod->getUnscaledElasticities();
  if (elasticities.numRows() == 0 || elasticities.numCols() == 0) return;
  for (i = 0; i < numRows;++i)
    {
      for (j = 0; j < numCols;++j)
        {
          mTableElasticities->setText(i, j, QString::number(elasticities[i][j]));
        }
    }
}

void CMCAResultSubwidget::loadConcentrationCCs(const CMCAMethod * mcaMethod)
{
  const CModel* model = mcaMethod->getModel();
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
      header->setLabel(i, FROM_UTF8(model->getReactionsX()[i]->getObjectName()));
    }
  const CAnnotatedMatrix & CCCs = (mComboScale->currentItem() == 0) ? mcaMethod->getScaledConcentrationCC() : mcaMethod->getUnscaledConcentrationCC();
  if (CCCs.numRows() == 0 || CCCs.numCols() == 0) return;
  for (i = 0; i < numRows;++i)
    {
      for (j = 0; j < numCols;++j)
        {
          mTableCCC->setText(i, j, QString::number(CCCs[i][j]));
        }
    }
}

void CMCAResultSubwidget::loadFluxCCs(const CMCAMethod * mcaMethod)
{
  const CModel* model = mcaMethod->getModel();
  assert(model);
  unsigned C_INT32 numRows, numCols;
  numCols = numRows = model->getTotSteps();
  mTableFCC->setNumRows(numRows);
  mTableFCC->setNumCols(numCols);

  unsigned C_INT32 i, j;
  QHeader* header = mTableFCC->verticalHeader();
  for (i = 0; i < numRows;++i)
    {
      header->setLabel(i, FROM_UTF8(model->getReactionsX()[i]->getObjectName()));
    }
  header = mTableFCC->horizontalHeader();
  for (i = 0; i < numCols;++i)
    {
      header->setLabel(i, FROM_UTF8(model->getReactionsX()[i]->getObjectName()));
    }
  const CAnnotatedMatrix & FCCs = (mComboScale->currentItem() == 0) ? mcaMethod->getScaledFluxCC() : mcaMethod->getUnscaledFluxCC();
  if (FCCs.numRows() == 0 || FCCs.numCols() == 0) return;
  for (i = 0; i < numRows;++i)
    {
      for (j = 0; j < numCols;++j)
        {
          mTableFCC->setText(i, j, QString::number(FCCs[i][j]));
        }
    }
}

void CMCAResultSubwidget::slotSave()
{}

void CMCAResultSubwidget::slotScaled()
{
  loadAll(mMCAMethod);
}
