/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CMCAResultSubwidget.ui.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/28 07:47:21 $
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

void CMCAResultSubwidget::init()
{
  mTopLabel->setText("");
}

void CMCAResultSubwidget::loadAll(CMCAMethod * mcaMethod)
{
  if (mcaMethod)
    {
      this->loadElasticities(mcaMethod);
      if (mcaMethod->isSteadyState())
        {
          mTopLabel->setText(QString::null);
          this->loadConcentrationCCs(mcaMethod);
          this->loadFluxCCs(mcaMethod);
          mTabWidget->setTabEnabled(mTabWidget->page(1), true);
          mTabWidget->setTabEnabled(mTabWidget->page(2), true);
        }
      else
        {
          mTopLabel->setText("Not at steady state. Only elasticities available!");
          mTabWidget->setTabEnabled(mTabWidget->page(1), false);
          mTabWidget->setTabEnabled(mTabWidget->page(2), false);
        }
    }
}

void CMCAResultSubwidget::loadElasticities(CMCAMethod * mcaMethod)
{
  CModel* model = mcaMethod->getModel();
  assert(model);
  unsigned C_INT32 numRows, numCols;
  numRows = model->getTotSteps();
  numCols = model->getMetabolites().size();
  mTableElasticities->setNumRows(numRows);
  mTableElasticities->setNumCols(numCols);
  unsigned C_INT32 i, j;
  QHeader* header = mTableElasticities->verticalHeader();
  for (i = 0; i < numRows;++i)
    {
      header->setLabel(i, QString(model->getReactions()[i]->getObjectName()));
    }
  header = mTableElasticities->horizontalHeader();
  for (i = 0; i < numCols;++i)
    {
      header->setLabel(i, QString(model->getMetabolites()[i]->getObjectName()));
    }
  CMatrix<C_FLOAT64> elasticities = mcaMethod->getDxv();
  if (elasticities.numRows() == 0 || elasticities.numCols() == 0) return;
  for (i = 0; i < numRows;++i)
    {
      for (j = 0; j < numCols;++j)
        {
          mTableElasticities->setText(i, j, QString::number(elasticities[i][j]));
        }
    }
}

void CMCAResultSubwidget::loadConcentrationCCs(CMCAMethod * mcaMethod)
{
  CModel* model = mcaMethod->getModel();
  assert(model);
  unsigned C_INT32 numRows, numCols;
  numRows = model->getMetabolitesInd().size();
  numCols = model->getTotSteps();
  mTableCCC->setNumRows(numRows);
  mTableCCC->setNumCols(numCols);
  unsigned C_INT32 i, j;
  QHeader* header = mTableCCC->verticalHeader();
  for (i = 0; i < numRows;++i)
    {
      header->setLabel(i, QString(model->getMetabolitesInd()[i]->getObjectName()));
    }
  header = mTableCCC->horizontalHeader();
  for (i = 0; i < numCols;++i)
    {
      header->setLabel(i, QString(model->getReactions()[i]->getObjectName()));
    }
  CMatrix<C_FLOAT64> CCCs = mcaMethod->getGamma();
  if (CCCs.numRows() == 0 || CCCs.numCols() == 0) return;
  for (i = 0; i < numRows;++i)
    {
      for (j = 0; j < numCols;++j)
        {
          mTableCCC->setText(i, j, QString::number(CCCs[i][j]));
        }
    }
}

void CMCAResultSubwidget::loadFluxCCs(CMCAMethod * mcaMethod)
{
  CModel* model = mcaMethod->getModel();
  assert(model);
  unsigned C_INT32 numRows, numCols;
  numCols = numRows = model->getTotSteps();
  mTableFCC->setNumRows(numRows);
  mTableFCC->setNumCols(numCols);

  unsigned C_INT32 i, j;
  QHeader* header = mTableFCC->verticalHeader();
  for (i = 0; i < numRows;++i)
    {
      header->setLabel(i, QString(model->getReactions()[i]->getObjectName()));
    }
  header = mTableFCC->horizontalHeader();
  for (i = 0; i < numCols;++i)
    {
      header->setLabel(i, QString(model->getReactions()[i]->getObjectName()));
    }
  CMatrix<C_FLOAT64> FCCs = mcaMethod->getFcc();
  if (FCCs.numRows() == 0 || FCCs.numCols() == 0) return;
  for (i = 0; i < numRows;++i)
    {
      for (j = 0; j < numCols;++j)
        {
          mTableFCC->setText(i, j, QString::number(FCCs[i][j]));
        }
    }
}
