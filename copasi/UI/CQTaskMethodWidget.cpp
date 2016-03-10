// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQTaskMethodWidget.h"
#include "qtUtilities.h"
#include "CQTaskMethodParametersDM.h"
#include "CQComboDelegate.h"
#include "CQPushButtonDelegate.h"
#include "CCopasiSelectionDialog.h"
#include "resourcesUI/CQIconResource.h"

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CObjectLists.h"
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
  mShowMethodParameters(false),
  mpMethodParameterDM(NULL),
  mpComboBoxDelegate(NULL),
  mpPushButtonDelegate(NULL)
{
  setupUi(this);

  // create a new QListview to be displayed on the screen..and set its property
  mpMethodParameterDM = new CQTaskMethodParametersDM(this);
  mpParameterView->setModel(mpMethodParameterDM);

  mpComboBoxDelegate = new CQComboDelegate(this);
  mpPushButtonDelegate = new CQPushButtonDelegate(CQIconResource::icon(CQIconResource::copasi), QString(),
      CQPushButtonDelegate::ToolButton, this);

  mpLblMethod->hide();
  mpBoxMethod->hide();

  mpLblParameter->hide();
  mpParameterView->hide();

  connect(mpMethodParameterDM, SIGNAL(signalCreateComboBox(const QModelIndex &)), this, SLOT(slotCreateComboBox(const QModelIndex &)));
  connect(mpMethodParameterDM, SIGNAL(signalCreatePushButton(const QModelIndex &)), this, SLOT(slotCreatePushButton(const QModelIndex &)));
  connect(mpMethodParameterDM, SIGNAL(signalCloseEditor(const QModelIndex &)), this, SLOT(slotCloseEditor(const QModelIndex &)));
  connect(mpPushButtonDelegate, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotPushButtonClicked(const QModelIndex &)));
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

void CQTaskMethodWidget::showMethodParameters(const bool & show)
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
      mpMethodParameterDM->clearMethods();
    }

  mpActiveMethod = getFromHistory(Type);

  if (mpActiveMethod == NULL)
    {
      mpActiveMethod = mpTask->createMethod(Type);
      mpTask->remove(mpActiveMethod);
      addToHistory(mpActiveMethod);
    }

  assert(mpActiveMethod != NULL);

  // We update the active methods parameters
  if (mShowMethodParameters)
    {
      mpMethodParameterDM->pushMethod(mpActiveMethod);

      mpParameterView->expandAll();
      mpParameterView->resizeColumnToContents(0);
    }

  return;
}

void CQTaskMethodWidget::clearHistory()
{
  mpMethodParameterDM->clearMethods();

  std::map< CTaskEnum::Method, CCopasiMethod * >::iterator it = mMethodHistory.begin();
  std::map< CTaskEnum::Method, CCopasiMethod * >::iterator end = mMethodHistory.end();

  for (; it != end; ++it)
    if (it->second != NULL)
      {
        it->second->setObjectParent(NULL);
        delete it->second;
      }

  mMethodHistory.clear();
}

void CQTaskMethodWidget::pushMethod(CCopasiMethod * pMethod)
{
  mpMethodParameterDM->pushMethod(pMethod);

  mpParameterView->expandAll();
  mpParameterView->resizeColumnToContents(0);
}

void CQTaskMethodWidget::popMethod(CCopasiMethod * pMethod)
{
  mpMethodParameterDM->popMethod(pMethod);

  mpParameterView->expandAll();
  mpParameterView->resizeColumnToContents(0);
}

void CQTaskMethodWidget::slotCreateComboBox(const QModelIndex & index)
{
  QModelIndex Source = index;

  while (Source.model()->inherits("QSortFilterProxyModel"))
    {
      Source = static_cast< const QSortFilterProxyModel *>(Source.model())->mapToSource(index);
    }

  mpParameterView->setItemDelegateForRow(Source.row(), mpComboBoxDelegate);
  mpParameterView->openPersistentEditor(Source);
  mpParameterView->expandAll();
}

void CQTaskMethodWidget::slotCreatePushButton(const QModelIndex & index)
{
  QModelIndex Source = index;

  while (Source.model()->inherits("QSortFilterProxyModel"))
    {
      Source = static_cast< const QSortFilterProxyModel *>(Source.model())->mapToSource(index);
    }

  mpParameterView->setItemDelegateForRow(Source.row(), mpPushButtonDelegate);
  mpParameterView->openPersistentEditor(Source);
  mpParameterView->expandAll();
}

void CQTaskMethodWidget::slotCloseEditor(const QModelIndex & index)
{
  QModelIndex Source = index;

  while (Source.model()->inherits("QSortFilterProxyModel"))
    {
      Source = static_cast< const QSortFilterProxyModel *>(Source.model())->mapToSource(index);
    }

  if (mpParameterView->itemDelegateForRow(Source.row()) != mpComboBoxDelegate) return;

  mpParameterView->setItemDelegateForRow(Source.row(), mpParameterView->itemDelegate());
  mpParameterView->expandAll();
}

void CQTaskMethodWidget::slotPushButtonClicked(const QModelIndex & index)
{
  QModelIndex Source = index;

  while (Source.model()->inherits("QSortFilterProxyModel"))
    {
      Source = static_cast< const QSortFilterProxyModel *>(Source.model())->mapToSource(index);
    }

  if (mpParameterView->itemDelegateForRow(Source.row()) != mpPushButtonDelegate) return;

  CCopasiParameter * pParameter = CQTaskMethodParametersDM::nodeFromIndex(Source);

  if (pParameter->getType() != CCopasiParameter::GROUP) return;

  CCopasiParameterGroup * pGroup = static_cast< CCopasiParameterGroup * >(pParameter);

  CCopasiParameterGroup::elements::const_iterator it = pGroup->getElementTemplates().beginIndex();
  CCopasiParameterGroup::elements::const_iterator end = pGroup->getElementTemplates().endIndex();

  for (; it != end; ++it)
    {
      switch ((*it)->getType())
        {
          case CCopasiParameter::CN:
            modifySelectCNs(*pGroup, **it);
            break;

          default:
            break;
        }
    }
}

void CQTaskMethodWidget::modifySelectCNs(CCopasiParameterGroup & group, const CCopasiParameter & cnTemplate)
{
  // OpenSelectionDialog
  std::vector< const CCopasiObject * > Selection;
  CObjectInterface::ContainerList ContainerList;
  ContainerList.push_back(group.getObjectDataModel());

  // Create the current selection
  CCopasiParameterGroup::elements::iterator it = group.beginIndex();
  CCopasiParameterGroup::elements::iterator end = group.endIndex();

  for (; it != end; ++it)
    {
      const CCopasiObject * pObject = CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(ContainerList, (*it)->getValue< CCopasiObjectName >()));

      if (pObject != NULL)
        {
          Selection.push_back(pObject);
        }
    }

  CModel * pModel = group.getObjectDataModel()->getModel();

  std::vector<const CCopasiObject * > ValidObjects;

  const std::vector< std::pair < CCopasiObjectName, CCopasiObjectName > > & ValidValues = cnTemplate.getValidValues< CCopasiObjectName >();
  std::vector< std::pair < CCopasiObjectName, CCopasiObjectName > >::const_iterator itValidValues = ValidValues.begin();
  std::vector< std::pair < CCopasiObjectName, CCopasiObjectName > >::const_iterator endValidValues = ValidValues.end();

  for (; itValidValues != endValidValues; ++itValidValues)
    {
      CObjectLists::ListType ListType = toEnum(itValidValues->first, CObjectLists::ListTypeName, CObjectLists::EMPTY_LIST);
      std::vector<const CCopasiObject * > Tmp = CObjectLists::getListOfConstObjects(ListType, pModel);
      ValidObjects.insert(ValidObjects.end(), Tmp.begin(), Tmp.end());
    }

  std::vector< const CCopasiObject * > NewSelection = CCopasiSelectionDialog::getObjectVector(this, ValidObjects, &Selection);

  // Modify group parameters;
  mpMethodParameterDM->beginResetModel();
  group.clear();

  std::vector< const CCopasiObject * >::const_iterator itNew = NewSelection.begin();
  std::vector< const CCopasiObject * >::const_iterator endNew = NewSelection.end();

  for (; itNew != endNew; ++itNew)
    {
      group.addParameter("Reaction", CCopasiParameter::CN, (*itNew)->getCN());
    }

  mpMethodParameterDM->endResetModel();
}
