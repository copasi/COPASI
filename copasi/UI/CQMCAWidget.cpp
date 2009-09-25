// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMCAWidget.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/25 21:02:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQMCAWidget.h"

#include <qmessagebox.h>
//#include <q3table.h>

#include <QHeaderView>

#include "CMCAResultWidget.h"
#include "UI/CQTaskBtnWidget.h"
#include "UI/CQTaskHeaderWidget.h"
#include "UI/CProgressBar.h"
#include "UI/qtUtilities.h"

#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CMCATask.h"
#include "steadystate/CMCAProblem.h"
#include "steadystate/CMCAMethod.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"
#include "report/CCopasiRootContainer.h"

/*
 *  Constructs a CQMCAWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMCAWidget::CQMCAWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMCAWidget::~CQMCAWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMCAWidget::languageChange()
{
  retranslateUi(this);
}

void CQMCAWidget::slotSteadyStateChecked()
{
  loadParameterTable();
}

bool CQMCAWidget::runTask()
{
  CMCATask * pTask =
    dynamic_cast< CMCATask * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  bool success = commonRunTask();

  commonAfterRunTask();

  CMCAResultWidget *pResult = dynamic_cast< CMCAResultWidget * >(mpListView->findWidgetFromId(241));

  if (pResult) pResult->loadFromBackend();

  if (success && pResult)
    mpListView->switchToOtherWidget(241, ""); //change to the results window

  return success;
}

CCopasiMethod * CQMCAWidget::createMethod(const CCopasiMethod::SubType & /* type */)
{return new CMCAMethod;}

bool CQMCAWidget::loadTask()
{
  CMCATask * pTask = dynamic_cast< CMCATask * >(mpTask);

  if (!pTask) return false;

  loadCommon();
//  loadMethod(); --> we cannot do that because of different structure -- 08.04.09

  CMCAProblem * pProblem =
    dynamic_cast< CMCAProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  // instead calling loadMethod(), the following codes is used
  mpCheckSteadyState->setChecked(pProblem->isSteadyStateRequested());

//  mpTblParameter->setNumRows(0);
  mpTblParameter->setRowCount(0);
  bool success = loadParameterTable();

  mChanged = false;

  return success;
}

bool CQMCAWidget::saveTask()
{
  CMCATask * pTask = dynamic_cast< CMCATask * >(mpTask);

  if (!pTask) return false;

  saveCommon();
  saveMethod();

  CMCAProblem * pProblem =
    dynamic_cast< CMCAProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  if (mpCheckSteadyState->isChecked() != pProblem->isSteadyStateRequested())
    {
      pProblem->setSteadyStateRequested(mpCheckSteadyState->isChecked());
      mChanged = true;
    }

  bool success = saveParameterTable();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  if (mChanged)(*CCopasiRootContainer::getDatamodelList())[0]->changed();

  mChanged = false;
  return success;
}

void CQMCAWidget::init()
{
  mpHeaderWidget->setTaskName("Metabolic Control Analysis");
  mpHeaderWidget->mpUpdateModel->hide();

  vboxLayout->insertWidget(0, mpHeaderWidget);  // header
  vboxLayout->insertSpacing(1, 14);       // space between header and body
  vboxLayout->addWidget(mpBtnWidget);     // 'footer'

  addMethodParameterTable(0);
}

bool CQMCAWidget::loadParameterTable()
{
// temporary because of migrating from Q3Table to QTableWidget - 26.03.09
//  bool init = (mpTblParameter->numRows() == 0);
  bool init = (mpTblParameter->rowCount() == 0);

  unsigned C_INT32 NumRows = mpMethod->size();
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  if (mpCheckSteadyState->isChecked())
    {
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Steady-State"]);

      if (!pSteadyStateTask) return false;

      NumRows += pSteadyStateTask->getMethod()->size();
    }

  /*
    mpTblParameter->setNumRows(NumRows);
    Q3Header *rowHeader = mpTblParameter->verticalHeader();
  */

  mpTblParameter->setRowCount(NumRows);
  QHeaderView *rowHeader = mpTblParameter->verticalHeader();
  QHeaderView *colHeader = mpTblParameter->horizontalHeader();

  unsigned C_INT32 i, k;
  CCopasiParameter::Type Type;
  QString value;

  for (i = 0; i < mpMethod->size() && init; i++)
    {
//      rowHeader->setLabel(i, FROM_UTF8(mpMethod->getName(i)));
      // create item of the current row and give it a name
      mpTblParameter->setVerticalHeaderItem(i, new QTableWidgetItem());
      mpTblParameter->verticalHeaderItem(i)->setText(FROM_UTF8(mpMethod->getName(i)));

      value = getParameterValue(mpMethod, i, &Type);
//      mpTblParameter->setText(i, 0, value);
      QTableWidgetItem *itemValue = new QTableWidgetItem(value);
      itemValue->setTextAlignment(Qt::AlignRight);
      mpTblParameter->setItem(i, 0, itemValue);
    }

  if (mpCheckSteadyState->isChecked())
    {
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Steady-State"]);

      if (!pSteadyStateTask) return false;

      CCopasiMethod * pMethod = pSteadyStateTask->getMethod();

      for (i = mpMethod->size(), k = 0; k < pMethod->size(); k++, i++)
        {
//          rowHeader->setLabel(i, FROM_UTF8(pMethod->getName(k)));
          // create item of the current row and give it a name
          mpTblParameter->setVerticalHeaderItem(i, new QTableWidgetItem());
          mpTblParameter->verticalHeaderItem(i)->setText(FROM_UTF8(pMethod->getName(k)));

          value = getParameterValue(pMethod, k, &Type);
//          mpTblParameter->setText(i, 0, value);
          QTableWidgetItem *itemValue = new QTableWidgetItem(value);
          itemValue->setTextAlignment(Qt::AlignRight);
          mpTblParameter->setItem(i, 0, itemValue);
        }
    }

  // appearance purpose
  mpTblParameter->resizeColumnsToContents();
  mpTblParameter->resizeRowsToContents();

  QAbstractItemModel* m = mpTblParameter->model();

  unsigned C_INT32 singleFrame = mpTblParameter->frameWidth();
  unsigned C_INT32 doubleFrame = 2 * singleFrame;
  std::cout << "doubleFrame = " << doubleFrame << std::endl;

  unsigned C_INT32 index;

  unsigned C_INT32 colCount = m->columnCount();
  unsigned C_INT32 w = 0;

  for (index = 0; index < colCount; index++)
    {
      w += mpTblParameter->columnWidth(index) + doubleFrame;
      std::cout << "i=" << index << ": w = " << w << std::endl;
//    std::cout << "sizeHintForColumn = " << mpTblParameter->sizeHintForColumn(i) << std::endl;
    }

  unsigned C_INT32 rowCount = m->rowCount();
  unsigned C_INT32 h = 0;

  for (index = 0; index < rowCount; index++)
    {
      h += mpTblParameter->rowHeight(index) + singleFrame;
      std::cout << "i=" << index << ": h = " << h << std::endl;
//    std::cout << "sizeHintForRow = " << mpTblParameter->sizeHintForRow(i) << std::endl;
    }

  std::cout << "w = " << w << " - h = " << h << std::endl;

  w += rowHeader->sizeHint().width();
  h += colHeader->sizeHint().height();

  std::cout << "colCount = " << colCount << " - rowCount = " << rowCount << std::endl;

  std::cout << "rowHeader->sizeHint().width() = " << rowHeader->sizeHint().width() << std::endl;
  std::cout << "colHeader->sizeHint().height() = " << colHeader->sizeHint().height() << std::endl;

  std::cout << "w = " << w << " - h = " << h << std::endl;

  // mpTblParameter->setFixedHeight(h);
  mpTblParameter->setFixedWidth(w);

  return true;
}

bool CQMCAWidget::saveParameterTable()
{
// temporary because of migrating from Q3Table to QTableWidget - 26.03.09
  unsigned C_INT32 i, k;
  QString value;
  CCopasiParameter::Type Type;

  for (i = 0; i < mpMethod->size(); i++)
    {
//      value = mpTblParameter->text(i, 0);
      value = mpTblParameter->item(i, 0)->text();
      std::cout << "value = " << value.toFloat() << std::endl;

      if (value != getParameterValue(mpMethod, i, &Type))
        {
          setParameterValue(mpMethod, i, value);
          mChanged = true;
        }
    }

  if (mpCheckSteadyState->isChecked())
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Steady-State"]);

      if (!pSteadyStateTask) return false;

      CCopasiMethod * pMethod = pSteadyStateTask->getMethod();

      for (i = mpMethod->size(), k = 0; k < pMethod->size(); i++, k++)
        {
//          value = mpTblParameter->text(i, 0);
          value = mpTblParameter->item(i, 0)->text();

          if (value != getParameterValue(pMethod, k, &Type))
            {
              setParameterValue(pMethod, k, value);
              mChanged = true;
            }
        }
    }

  return true;
}
