// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskMethodWidget.cpp,v $
//   $Revision: 1.1.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:12:57 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQTaskMethodWidget.h"
#include "qtUtilities.h"

#include "copasi.h"

#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiMethod.h"
#include "utilities/utility.h"

CQTaskMethodWidget::CQTaskMethodWidget(QWidget* parent, Qt::WindowFlags f):
    QWidget(parent, f),
    mpTask(NULL),
    mpMethod(NULL)
{
  setupUi(this);

  mpTableParameter->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTableParameter->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTableParameter->horizontalHeader()->hide();

  mpLblMethod->hide();
  mpBoxMethod->hide();

  mpLblParameter->hide();
  mpTableParameter->hide();
}

CQTaskMethodWidget::~CQTaskMethodWidget()
{
  // TODO Auto-generated destructor stub
}

void CQTaskMethodWidget::languageChange()
{
  retranslateUi(this);
}

void CQTaskMethodWidget::changeMethod(int /* index */)
{
  if (mpTask == NULL)
    return;

  if (mpMethod != mpTask->getMethod())
    pdelete(mpMethod);

  CCopasiMethod::SubType Type =
    toEnum(TO_UTF8(mpBoxMethod->currentText()), CCopasiMethod::SubTypeName, CCopasiMethod::unset);

  mpMethod = mpTask->createMethod(Type);

  loadMethod();

  return;

}

void CQTaskMethodWidget::setTask(CCopasiTask * pTask)
{
  mpTask = pTask;

  if (mpTask != NULL)
    {
      mpMethod = mpTask->getMethod();
    }
  else
    {
      mpMethod = NULL;
    }
}

void CQTaskMethodWidget::setValidMethods(const unsigned int * validMethods)
{
  unsigned C_INT32 i;

  for (i = 0; validMethods[i] != CCopasiMethod::unset; i++)
    mpBoxMethod->insertItem(QString::fromUtf8(CCopasiMethod::SubTypeName[validMethods[i]]));

  if (i > 0)
    {
      mpLblMethod->show();
      mpBoxMethod->show();

      connect(mpBoxMethod, SIGNAL(activated(int)), this, SLOT(changeMethod(int)));
    }
  else
    {
      mpLblMethod->hide();
      mpBoxMethod->hide();

      disconnect(mpBoxMethod, SIGNAL(activated(int)), this, SLOT(changeMethod(int)));
    }
}

void CQTaskMethodWidget::enableMethodParameter(const bool & enable)
{
  if (enable)
    {
      mpLblParameter->show();
      mpTableParameter->show();
    }
  else
    {
      mpLblParameter->hide();
      mpTableParameter->hide();
    }
}

bool CQTaskMethodWidget::loadMethod()
{
  if (!mpTask) return false;

  if (!mpMethod) return false;

  if (mpBoxMethod->isShown())
    mpBoxMethod->setCurrentText(QString::fromUtf8(CCopasiMethod::SubTypeName[mpMethod->getSubType()]));

  if (mpTableParameter->isShown())
    {
      QString Value;

      mpTableParameter->setRowCount((int) mpMethod->size());

      unsigned C_INT32 i;
      CCopasiParameter::Type Type;

      for (i = 0; i < mpMethod->size(); i++)
        {
          // create item of the current row and give it a name
          mpTableParameter->setVerticalHeaderItem(i, new QTableWidgetItem());
          mpTableParameter->verticalHeaderItem(i)->setText(FROM_UTF8(mpMethod->getName(i)));

          Value = getParameterValue(mpMethod, i, &Type);

          QTableWidgetItem *pValueItem = new QTableWidgetItem();
          pValueItem->setData(Qt::EditRole, QVariant(Value));
          pValueItem->setTextAlignment(Qt::AlignRight);
          mpTableParameter->setItem(i, 0, pValueItem);
        }
    }

  mpTableParameter->resizeColumnsToContents();

  return true;
}

bool CQTaskMethodWidget::saveMethod()
{
  if (!mpTask) return false;

  const CCopasiMethod * pMethod = mpTask->getMethod();

  if (!pMethod) return false;

  bool changed = false;


  if (pMethod->getSubType() != mpMethod->getSubType())
    {
      mpTask->setMethodType(mpMethod->getSubType());
      changed = true;
    }

  mpMethod = mpTask->getMethod();

  unsigned C_INT32 i;
  QString Value;
  CCopasiParameter::Type Type;

  for (i = 0; i < mpMethod->size(); i++)
    {
      if (!mpTableParameter)
        break;

      if (!mpTableParameter->item(i, 0))
        continue;

      Value = mpTableParameter->item(i, 0)->text();

      if (Value != getParameterValue(mpMethod, i, &Type))
        {
          setParameterValue(mpMethod, i, Value);
          changed = true;
        }
    }

  return changed;
}
