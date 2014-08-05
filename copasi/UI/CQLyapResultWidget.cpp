// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

#include "copasi.h"

#include "CQLyapResultWidget.h"

#include <QtGui/QMessageBox>

#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CKeyFactory.h"
#include "model/CModel.h"
#include "lyap/CLyapProblem.h"
#include "commandline/CLocaleString.h"

#include "UI/CopasiFileDialog.h"

/*
 *  Constructs a CQLyapResultWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQLyapResultWidget::CQLyapResultWidget(QWidget* parent, const char* name, Qt::WFlags fl)
  : CopasiWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQLyapResultWidget::~CQLyapResultWidget()
{}

void CQLyapResultWidget::init()
{
  /*
    mSaveButton->setEnabled(false);
    mSaveButton->hide();
  */
}

/* This function loads the optimization result widget when its name is
  clicked in the tree   */
bool CQLyapResultWidget::loadFromBackend()
{
  //bool success = true;
  //std::ostringstream os;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  mpTask = dynamic_cast<CLyapTask*>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Lyapunov Exponents"]);

  if (!mpTask) return false;

  CLyapProblem * pProblem = dynamic_cast< CLyapProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  if (!mpTask->resultAvailable())
    {
      mTableExponents->setEnabled(false);
      mTableExponents->setRowCount(0);
      mLineEditSum->setEnabled(false);
      mLineEditSum->setText("");
      mLineEditDivergence->setEnabled(false);
      mLineEditDivergence->setText("");
      mLabelComment->setText("No result available.");
      return false;
    }

  mTableExponents->setEnabled(true);
  mLineEditSum->setEnabled(true);
  mLineEditDivergence->setEnabled(true);

  unsigned C_INT32 i, imax = pProblem->getExponentNumber();

  mTableExponents->setRowCount(imax);

  for (i = 0; i < imax; ++i)
    {
      QTableWidgetItem *pItem = mTableExponents->item(i, 0);

      if (pItem == NULL)
        {
          pItem = new QTableWidgetItem(QVariant::Double);
          pItem->setData(Qt::DisplayRole, mpTask->exponents()[i]);
          pItem->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
          mTableExponents->setItem(i, 0, pItem);
        }
      else
        {
          pItem->setData(Qt::DisplayRole, mpTask->exponents()[i]);
        }
    }

  mLineEditSum->setText(QString::number(mpTask->sumOfExponents()));

  if (mpTask->resultHasDivergence())
    {
      mLineEditDivergence->setEnabled(true);
      mLineEditDivergence->setText(QString::number(mpTask->averageDivergence()));
    }
  else
    {
      mLineEditDivergence->setEnabled(false);
      mLineEditDivergence->setText("");
    }

  //comment
  mLabelComment->setText("");

  if (mpTask->resultHasDivergence()
      && (mpTask->modelVariablesInResult() == mpTask->numberOfExponentsCalculated()))
    {
      if ((mpTask->sumOfExponents() < 0.0) && (mpTask->averageDivergence() < 0.0))
        {
          C_FLOAT64 factor = mpTask->averageDivergence() / mpTask->sumOfExponents();

          if (factor > 1.01)
            mLabelComment->setText("Warning: Divergence differs from sum of exponents. This may indicate that the strongly negative exponents are calculated inaccuratly.");
        }
    }

  return true;
}

bool CQLyapResultWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action
                                C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (this->isVisible())
    return loadFromBackend();
  else
    return true;
}

bool CQLyapResultWidget::leave()
{
  return true;
}

bool CQLyapResultWidget::enterProtected()
{
  return loadFromBackend();
}

void CQLyapResultWidget::saveToFile()
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

  if (mpTask != NULL)
    mpTask->printResult(&file);

  return;
}
