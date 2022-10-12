// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQTaskMethodWidget.h"
#include "CQComboDelegate.h"
#include "CQPushButtonDelegate.h"
#include "CCopasiSelectionDialog.h"
#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/copasi.h"

#include "qtUtilities.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CObjectLists.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/utility.h"
#include "copasi/utilities/CMethodFactory.h"

CQTaskMethodWidget::CQTaskMethodWidget(QWidget* parent, Qt::WindowFlags f):
  QWidget(parent, f),
  mpTask(NULL),
  mpMethod(NULL),
  mpActiveMethod(NULL),
  mMethodHistory(),
  mShowMethods(false)
{
  setupUi(this);

  mpLblMethod->hide();
  mpBoxMethod->hide();

  mpLblParameter->hide();
  mpParameterView->hide();
}

CQTaskMethodWidget::~CQTaskMethodWidget()
{
  clearHistory();
}

void CQTaskMethodWidget::slotChangeMethod(int /* index */)
{
  if (mpTask == NULL)
    return;

  CTaskEnum::Method Type =
    CTaskEnum::MethodName.toEnum(TO_UTF8(mpBoxMethod->currentText()), CTaskEnum::Method::UnsetMethod);

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

  for (i = 0; validMethods[i] != CTaskEnum::Method::UnsetMethod; i++)
    mpBoxMethod->insertItem(mpBoxMethod->count(), FROM_UTF8(CTaskEnum::MethodName[validMethods[i]]));

  if (i > 0)
    {
      mShowMethods = true;
      mpLblMethod->show();
      mpBoxMethod->show();

      connect(mpBoxMethod, SIGNAL(activated(int)), this, SLOT(slotChangeMethod(int)));
    }
  else
    {
      mShowMethods = false;
      mpLblMethod->hide();
      mpBoxMethod->hide();

      disconnect(mpBoxMethod, SIGNAL(activated(int)), this, SLOT(slotChangeMethod(int)));
    }
}

void CQTaskMethodWidget::showMethodParameters(bool show)
{
  mShowMethodParameters = show;

  if (mShowMethodParameters)
    {
      mpParameterView->show();
      mpParameterView->show();
    }
  else
    {
      mpParameterView->hide();
      mpParameterView->hide();
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

  return true;
}

bool CQTaskMethodWidget::saveMethod()
{
  if (!mpTask) return false;

  const CCopasiMethod * pMethod = mpTask->getMethod();

  if (!pMethod) return false;

  if (!mpActiveMethod) return false;

  bool changed = false;

  if (mShowMethodParameters)
    {
      if (!(*mpMethod == *mpActiveMethod))
        {
          changed = true;
        }
    }

  if (mShowMethods)
    {
      if (pMethod->getSubType() != mpActiveMethod->getSubType())
        {
          mpTask->setMethodType(mpActiveMethod->getSubType());
          mpMethod = mpTask->getMethod();

          changed = true;
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
      pdelete(found->second);
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
  if (mShowMethodParameters)
    {
      mpParameterView->clearGroups();
    }

  mpActiveMethod = getFromHistory(Type);

  if (mpActiveMethod == NULL)
    {
      mpActiveMethod = CMethodFactory::create(mpTask->getType(), Type, mpTask);
      mpTask->remove(mpActiveMethod);
      addToHistory(mpActiveMethod);
    }

  assert(mpActiveMethod != NULL);

  // We update the active methods parameters
  if (mShowMethodParameters)
    {
      mpParameterView->pushGroup(mpActiveMethod);

      mpParameterView->expandAll();
      mpParameterView->resizeColumnToContents(0);
    }

  return;
}

void CQTaskMethodWidget::clearHistory()
{
  mpParameterView->clearGroups();

  std::map< CTaskEnum::Method, CCopasiMethod * >::iterator it = mMethodHistory.begin();
  std::map< CTaskEnum::Method, CCopasiMethod * >::iterator end = mMethodHistory.end();

  for (; it != end; ++it)
    if (it->second != NULL)
      {
        it->second->setObjectParent(NULL);
        pdelete(it->second);
      }

  mMethodHistory.clear();

  mpActiveMethod = NULL;
}

void CQTaskMethodWidget::pushMethod(CCopasiMethod * pMethod)
{
  mpParameterView->pushGroup(pMethod);

  mpParameterView->expandAll();
  mpParameterView->resizeColumnToContents(0);
}

void CQTaskMethodWidget::popMethod(CCopasiMethod * pMethod)
{
  mpParameterView->popGroup(pMethod);

  mpParameterView->expandAll();
  mpParameterView->resizeColumnToContents(0);
}

void CQTaskMethodWidget::showMethodCheckbox(bool show)
{
  mpChkShowParameters->setVisible(show);
}
