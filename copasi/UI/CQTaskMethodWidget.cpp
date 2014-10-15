// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
  mpMethod(NULL),
  mpActiveMethod(NULL),
  mMethodHistory(),
  mShowMethods(false),
  mShowMethodParameters(false)
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
  clearHistory();
}

void CQTaskMethodWidget::changeMethod(int /* index */)
{
  if (mpTask == NULL)
    return;

  // We update the active methods parameters
  if (mShowMethodParameters)
    {
      unsigned C_INT32 i;
      QString Value;

      for (i = 0; i < mpActiveMethod->size(); i++)
        {
          if (!mpTableParameter->item(i, 0))
            continue;

          Value = mpTableParameter->item(i, 0)->text();
          setParameterValue(mpActiveMethod, i, Value);
        }
    }

  CTaskEnum::Method Type =
    toEnum(TO_UTF8(mpBoxMethod->currentText()), CTaskEnum::MethodName, CTaskEnum::UnsetMethod);

  setActiveMethod(Type);
  loadMethod();

  return;
}

void CQTaskMethodWidget::setTask(CCopasiTask * pTask)
{
  mpTask = pTask;

  if (mpTask != NULL)
    {
      mpMethod = mpTask->getMethod();

      if (mpMethod != NULL)
        {
          setActiveMethod(mpMethod->getSubType());
          *mpActiveMethod = *mpMethod;
        }
    }
  else
    {
      mpMethod = NULL;
      mpActiveMethod = NULL;
    }
}

void CQTaskMethodWidget::setValidMethods(const CTaskEnum::Method * validMethods)
{
  unsigned C_INT32 i;

  for (i = 0; validMethods[i] != CTaskEnum::UnsetMethod; i++)
    mpBoxMethod->insertItem(mpBoxMethod->count(), FROM_UTF8(CTaskEnum::MethodName[validMethods[i]]));

  if (i > 0)
    {
      mShowMethods = true;
      mpLblMethod->show();
      mpBoxMethod->show();

      connect(mpBoxMethod, SIGNAL(activated(int)), this, SLOT(changeMethod(int)));
    }
  else
    {
      mShowMethods = false;
      mpLblMethod->hide();
      mpBoxMethod->hide();

      disconnect(mpBoxMethod, SIGNAL(activated(int)), this, SLOT(changeMethod(int)));
    }
}

void CQTaskMethodWidget::showMethodParameters(const bool & show)
{
  mShowMethodParameters = show;

  if (mShowMethodParameters)
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

  if (!mpActiveMethod) return false;

  if (mShowMethods)
    {
      mpBoxMethod->setCurrentIndex(mpBoxMethod->findText(FROM_UTF8(CTaskEnum::MethodName[mpActiveMethod->getSubType()])));
    }

  if (mShowMethodParameters)
    {
      QString Value;

      mpTableParameter->setRowCount((int) mpActiveMethod->size());

      unsigned C_INT32 i;
      CCopasiParameter::Type Type;

      for (i = 0; i < mpActiveMethod->size(); i++)
        {
          // create item of the current row and give it a name
          mpTableParameter->setVerticalHeaderItem(i, new QTableWidgetItem());
          mpTableParameter->verticalHeaderItem(i)->setText(FROM_UTF8(mpActiveMethod->getName(i)));

          Value = getParameterValue(mpActiveMethod, i, &Type);

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

  if (mShowMethods)
    {
      if (pMethod->getSubType() != mpActiveMethod->getSubType())
        {
          mpTask->setMethodType(mpActiveMethod->getSubType());
          mpMethod = mpTask->getMethod();

          changed = true;
        }
    }

  if (mShowMethodParameters)
    {
      unsigned C_INT32 i;
      QString Value;
      CCopasiParameter::Type Type;

      for (i = 0; i < mpActiveMethod->size(); i++)
        {
          if (!mpTableParameter->item(i, 0))
            continue;

          Value = mpTableParameter->item(i, 0)->text();

          if (Value != getParameterValue(mpActiveMethod, i, &Type))
            {
              setParameterValue(mpActiveMethod, i, Value);
              changed = true;
            }
        }
    }

  if (changed)
    {
      *mpMethod = *mpActiveMethod;
    }

  return changed;
}

void CQTaskMethodWidget::addToHistory(CCopasiMethod * pMethod)
{
  if (pMethod == NULL)
    {
      return;
    }

  std::map< CTaskEnum::Method, CCopasiMethod * >::iterator found = mMethodHistory.find(pMethod->getSubType());

  if (found != mMethodHistory.end())
    {
      if (found->second != pMethod)
        {
          delete found->second;
          found->second = pMethod;
        }

      return;
    }

  mMethodHistory[pMethod->getSubType()] = pMethod;
}

void CQTaskMethodWidget::removeFromHistory(CCopasiMethod * pMethod)
{
  if (pMethod == NULL)
    {
      return;
    }

  std::map< CTaskEnum::Method, CCopasiMethod * >::iterator found = mMethodHistory.find(pMethod->getSubType());

  if (found != mMethodHistory.end())
    {
      mMethodHistory.erase(found);
    }
}

CCopasiMethod * CQTaskMethodWidget::getFromHistory(const CTaskEnum::Method & Type) const
{
  std::map< CTaskEnum::Method, CCopasiMethod * >::const_iterator found = mMethodHistory.find(Type);

  if (found != mMethodHistory.end())
    {
      return found->second;
    }

  return NULL;
}

void CQTaskMethodWidget::setActiveMethod(const CTaskEnum::Method & Type)
{
  mpActiveMethod = getFromHistory(Type);

  if (mpActiveMethod == NULL)
    {
      mpActiveMethod = mpTask->createMethod(Type);
      addToHistory(mpActiveMethod);
    }

  assert(mpActiveMethod != NULL);

  return;
}

void CQTaskMethodWidget::clearHistory()
{
  std::map< CTaskEnum::Method, CCopasiMethod * >::iterator it = mMethodHistory.begin();
  std::map< CTaskEnum::Method, CCopasiMethod * >::iterator end = mMethodHistory.end();

  for (; it != end; ++it)
    {
      delete it->second;
    }

  mMethodHistory.clear();
}
