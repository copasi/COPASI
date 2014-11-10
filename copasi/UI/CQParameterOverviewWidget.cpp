// Copyright (C) 2012 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtGui/QSortFilterProxyModel>

#include "CQParameterOverviewWidget.h"
#include "CQParameterOverviewDM.h"
#include "CQMessageBox.h"
#include "CopasiFileDialog.h"
#include "qtUtilities.h"
#include "CQNameSelectionDialog.h"
#include "CQPushButtonDelegate.h"
#include "CQComboDelegate.h"

#include "commandline/CLocaleString.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModelParameterSet.h"
#include "model/CModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CCopasiStaticString.h"

#ifdef COPASI_UNDO
#include "copasiui3window.h"
#endif

CQParameterOverviewWidget::CQParameterOverviewWidget(QWidget* parent, const char* name):
  CopasiWidget(parent, name),
  mpParameterSet(NULL),
  mpParameterSetCopy(NULL),
  mpParameterSetDM(NULL),
  mpParameterSetSortDM(NULL),
  mGlobalQuantities()
{
  setupUi(this);

  // create a new QListview to be displayed on the screen..and set its property
  mpParameterSetDM = new CQParameterOverviewDM(this);
  mpParameterSetSortDM = new QSortFilterProxyModel(this);

  mpParameterSetSortDM->setSourceModel(mpParameterSetDM);
  mpParameterSetSortDM->setSortRole(Qt::EditRole);
  mpParameterSetSortDM->setSortCaseSensitivity(Qt::CaseInsensitive);
  // pSortModel->sort(0, Qt::AscendingOrder);

  mpTreeView->setModel(mpParameterSetSortDM);
  mpTreeView->sortByColumn(0, Qt::AscendingOrder);

  CQPushButtonDelegate * pPushButtonDelegate = new CQPushButtonDelegate(CQPushButtonDelegate::PushButton, this);
  mpTreeView->setItemDelegateForColumn(1, pPushButtonDelegate);
  connect(pPushButtonDelegate, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotResolve(const QModelIndex &)));

  CQComboDelegate * pComboDelegate = new CQComboDelegate(&mGlobalQuantities, this);
  mpTreeView->setItemDelegateForColumn(5, pComboDelegate);

  connect(mpParameterSetDM, SIGNAL(signalOpenEditor(const QModelIndex &)), this, SLOT(slotOpenEditor(const QModelIndex &)));
  connect(mpParameterSetDM, SIGNAL(signalCloseEditor(const QModelIndex &)), this, SLOT(slotCloseEditor(const QModelIndex &)));

#ifdef COPASI_UNDO
  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  mpParameterSetDM->setUndoStack(pWindow->getUndoStack());
  connect(mpParameterSetDM, SIGNAL(changeWidget(const size_t&)), this, SLOT(slotChangeWidget(const size_t&)));
#endif
}

CQParameterOverviewWidget::~CQParameterOverviewWidget()
{
  // TODO Auto-generated destructor stub
}

// virtual
bool CQParameterOverviewWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  if (mIgnoreUpdates)
    {
      return true;
    }

  switch (objectType)
    {
      case ListViews::STATE:
        enterProtected();
        break;

      case ListViews::MODEL:

        if (action == ListViews::ADD ||
            action == ListViews::DELETE)
          {
            mKey = "";
            mpObject = NULL;

            enterProtected();
          }

        break;

      case ListViews::PARAMETEROVERVIEW:
      case ListViews::MODELPARAMETERSET:

        if (mKey == key)
          {
            switch (action)
              {
                case ListViews::DELETE:
                  mKey = "";
                  mpObject = NULL;

                  enterProtected();
                  break;

                case ListViews::CHANGE:
                  enterProtected();
                  break;

                default:
                  break;
              }
          }

        break;

      default:
        break;
    }

  return true;
}

// virtual
bool CQParameterOverviewWidget::leave()
{
  if (mpParameterSet == NULL)
    {
      return true;
    }

  if (mpParameterSet->diff(*mpParameterSetCopy,
                           static_cast< CModelParameter::Framework >(mFramework),
                           false) != CModelParameter::Identical)
    {
      mpParameterSet->assignSetContent(*mpParameterSetCopy, false);

      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      (*CCopasiRootContainer::getDatamodelList())[0]->changed();

      if (mpParameterSet->isActive())
        {
          mpParameterSet->updateModel();
          protectedNotify(ListViews::STATE, ListViews::CHANGE, "");
        }
      else
        {
          protectedNotify(ListViews::MODELPARAMETERSET, ListViews::CHANGE, mKey);
        }
    }

  return true;
}

// virtual
void CQParameterOverviewWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  if (mpParameterSet == NULL)
    {
      return;
    }

  if (!mpParameterSet->isActive())
    {
      mpParameterSetCopy->compareWithModel(static_cast< CModelParameter::Framework >(mFramework));
    }

  mpParameterSetDM->setFramework(framework);
  mpTreeView->expandAll();
  mpTreeView->resizeColumnToContents(3);
}

// virtual
bool CQParameterOverviewWidget::enterProtected()
{
  mpParameterSet = dynamic_cast< CModelParameterSet * >(mpObject);

  if (!mpParameterSet)
    {
      mpParameterSetDM->setModelParameterset(NULL);
      pdelete(mpParameterSetCopy);

      return false;
    }

  // We need to make sure the original is fully compiled.
  mpParameterSet->compile();

  CModelParameterSet * pOldParameterSet = mpParameterSetCopy;
  mpParameterSetCopy = new CModelParameterSet(*mpParameterSet, mpDataModel, false);

  mGlobalQuantities.clear();

  if (mpParameterSet->isActive())
    {
      mpTreeView->header()->hideSection(1);
    }
  else
    {
      mpParameterSetCopy->compareWithModel(static_cast< CModelParameter::Framework >(mFramework));
      mpHeaderWidget->hide();
      mpBtnWidget->hide();
    }

  buildSelectionList();

  mpParameterSetDM->setModelParameterset(mpParameterSetCopy);
  pdelete(pOldParameterSet);

  mpTreeView->expandAll();

  for (int i = 0; i < 6; i++)
    {
      mpTreeView->resizeColumnToContents(i);
    }

  return true;
}

void CQParameterOverviewWidget::buildSelectionList()
{
  // We build the selection for the global parameters for kinetic constants.
  const CModelParameterGroup *pGlobalQuantities =
    static_cast< CModelParameterGroup * >(mpParameterSetCopy->getModelParameter(CCopasiStaticString("Initial Global Quantities").getCN()));

  CModelParameterGroup::const_iterator it = pGlobalQuantities->begin();
  CModelParameterGroup::const_iterator end = pGlobalQuantities->end();

  mGlobalQuantities.clear();
  mGlobalQuantities.append("");

  for (; it != end; ++it)
    {
      if ((*it)->getCompareResult() != CModelParameter::Missing)
        {
          mGlobalQuantities.append(FROM_UTF8((*it)->getName()));
        }
    }
}

// virtual
void CQParameterOverviewWidget::slotBtnRevert()
{
  mpBtnRevert->setFocus();
  enterProtected();
}

// virtual
void CQParameterOverviewWidget::slotBtnCommit()
{
  mpBtnCommit->setFocus();
  leave();
  enterProtected();
}

// virtual
void CQParameterOverviewWidget::slotBtnDelete()
{
  if (mpParameterSet == NULL)
    {
      return;
    }

  CModel * pModel = mpParameterSet->getModel();

  if (pModel == NULL)
    {
      return;
    }

  mpParameterSetDM->setModelParameterset(NULL);

  pModel->getModelParameterSets().remove(mpParameterSet->getObjectName());

  // Notify the GUI of the delete.
  protectedNotify(ListViews::MODELPARAMETERSET, ListViews::DELETE, mKey);
}

// virtual
void CQParameterOverviewWidget::slotBtnNew()
{
  // This button is shown as Apply and is used to assign the parameter values to the model.

  // commit all changes
  slotBtnCommit();

  // Sanity checks
  if (mpParameterSet == NULL)
    {
      return;
    }

  CModel * pModel = mpParameterSet->getModel();

  if (pModel == NULL)
    {
      return;
    }

  // We first asked whether the user wants to save the current model values
  if (CQMessageBox::question(this, "Save current Model Parameters?",
                             "You are about to overwrite the current model values.\n"
                             "Do you want to save them?",
                             QMessageBox::Save | QMessageBox::Discard,
                             QMessageBox::Save) == QMessageBox::Save)
    {
      // Save the parameter set to a new or existing set
      CQNameSelectionDialog Dialog(this);

      CCopasiVectorN< CModelParameterSet > & Sets = pModel->getModelParameterSets();

      CCopasiVectorN< CModelParameterSet >::const_iterator it = Sets.begin();
      CCopasiVectorN< CModelParameterSet >::const_iterator end = Sets.end();
      QStringList SelectionList;

      for (; it != end; ++it)
        {
          SelectionList.append(FROM_UTF8((*it)->getName()));
        }

      Dialog.setSelectionList(SelectionList);
      QString Name;

      if (Dialog.exec() != QDialog::Rejected &&
          (Name = Dialog.getSelection()) != "")
        {
          if (SelectionList.indexOf(Name) == -1)
            {
              CModelParameterSet * pNew = new CModelParameterSet(pModel->getModelParameterSet(), pModel, false);
              pNew->setObjectName(TO_UTF8(Name));
              Sets.add(pNew, true);

              // Notify the GUI of the insert
              protectedNotify(ListViews::MODELPARAMETERSET, ListViews::ADD, pNew->getKey());
            }
          else
            {
              CModelParameterSet * pExisting = Sets[TO_UTF8(Name)];
              pExisting->assignSetContent(pModel->getModelParameterSet(), false);

              // Notify the GUI of the insert
              protectedNotify(ListViews::MODELPARAMETERSET, ListViews::CHANGE, pExisting->getKey());
            }
        }
    }

  mpParameterSet->updateModel();

  // Notify the GUI that the model state has changed.
  protectedNotify(ListViews::STATE, ListViews::CHANGE, pModel->getKey());

  enterProtected();
}

void CQParameterOverviewWidget::slotBtnCopy()
{
  // commit all changes
  slotBtnCommit();

  // Sanity checks
  if (mpParameterSet == NULL)
    {
      return;
    }

  CModel * pModel = mpParameterSet->getModel();

  if (pModel == NULL)
    {
      return;
    }

  CCopasiVectorN< CModelParameterSet > & Sets = pModel->getModelParameterSets();
  std::string Name = "Parameter Set";
  int i = 0;

  while (Sets.getIndex(Name) != C_INVALID_INDEX)
    {
      i++;
      Name = "Parameter Set ";
      Name += TO_UTF8(QString::number(i));
    }

  CModelParameterSet * pNew = new CModelParameterSet(pModel->getModelParameterSet(), pModel, false);
  pNew->setObjectName(Name);
  Sets.add(pNew, true);

  // Notify the GUI of the insert
  protectedNotify(ListViews::MODELPARAMETERSET, ListViews::ADD, pNew->getKey());

  mpListView->switchToOtherWidget(C_INVALID_INDEX, pNew->getKey());
}

// virtual
void CQParameterOverviewWidget::slotBtnSaveToFile()
{
  // Commit all changes
  slotBtnCommit();

  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          "untitled.tsv", "Tab Separated Files (*.tsv);;Comma Separated Files (*.csv);;TEXT Files (*.txt)", "Save as");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(CLocaleString::fromUtf8(TO_UTF8(fileName)).c_str());

  if (file.fail()) return;

  std::string mode;
  std::string separator;

  if (fileName.endsWith(".txt"))
    {
      mode = "report";
      separator = "\t";
    }
  else if (fileName.endsWith(".csv"))
    {
      mode = "table";
      separator = ",";
    }
  else
    {
      mode = "table";
      separator = "\t";
    }

  mpParameterSet->saveToStream(file, static_cast< CModelParameter::Framework >(mFramework), mode, separator);

  file.close();
}

// virtual
void CQParameterOverviewWidget::slotBtnSaveAs()
{
  // commit all changes
  slotBtnCommit();

  if (mpParameterSet == NULL)
    {
      return;
    }

  CModel * pModel = mpParameterSet->getModel();

  if (pModel == NULL)
    {
      return;
    }

  // Save the parameter set to a new or existing set
  CQNameSelectionDialog Dialog(this);

  CCopasiVectorN< CModelParameterSet > & Sets = pModel->getModelParameterSets();

  CCopasiVectorN< CModelParameterSet >::const_iterator it = Sets.begin();
  CCopasiVectorN< CModelParameterSet >::const_iterator end = Sets.end();
  QStringList SelectionList;

  for (; it != end; ++it)
    {
      SelectionList.append(FROM_UTF8((*it)->getName()));
    }

  Dialog.setSelectionList(SelectionList);

  if (Dialog.exec() == QDialog::Rejected)
    {
      return;
    }

  QString Name = Dialog.getSelection();

  if (Name == "")
    {
      return;
    }

  if (SelectionList.indexOf(Name) == -1)
    {
      CModelParameterSet * pNew = new CModelParameterSet(*mpParameterSet, pModel, false);
      pNew->setObjectName(TO_UTF8(Name));
      Sets.add(pNew, true);

      // Notify the GUI of the insert
      protectedNotify(ListViews::MODELPARAMETERSET, ListViews::ADD, pNew->getKey());
    }
  else
    {
      CModelParameterSet * pExisting = Sets[TO_UTF8(Name)];
      pExisting->assignSetContent(*mpParameterSet, false);

      // Notify the GUI of the insert
      protectedNotify(ListViews::MODELPARAMETERSET, ListViews::CHANGE, pExisting->getKey());
    }

  return;
}

void CQParameterOverviewWidget::slotOpenEditor(const QModelIndex & index)
{
  QModelIndex Tmp = index;
  const QAbstractItemModel *pModel = Tmp.model();

  while (pModel->inherits("QSortFilterProxyModel"))
    {
      Tmp = static_cast< const QSortFilterProxyModel *>(pModel)->mapToSource(index);
      pModel = Tmp.model();
    }

  mpTreeView->openPersistentEditor(mpParameterSetSortDM->mapFromSource(Tmp));
}

void CQParameterOverviewWidget::slotCloseEditor(const QModelIndex & index)
{
  QModelIndex Tmp = index;
  const QAbstractItemModel *pModel = Tmp.model();

  while (pModel->inherits("QSortFilterProxyModel"))
    {
      Tmp = static_cast< const QSortFilterProxyModel *>(pModel)->mapToSource(index);
      pModel = Tmp.model();
    }

  mpTreeView->closePersistentEditor(Tmp);
}

void CQParameterOverviewWidget::slotResolve(const QModelIndex & index)
{
  CModelParameter * pModelParameter = mpParameterSetDM->nodeFromIndex(index);

  if (pModelParameter == NULL)
    {
      return;
    }

  pModelParameter->refreshFromModel(true);

  mpParameterSetCopy->compareWithModel(static_cast< CModelParameter::Framework >(mFramework));

  buildSelectionList();

  mpParameterSetDM->setFramework(mFramework);

  mpTreeView->expandAll();
  mpTreeView->resizeColumnToContents(3);
}

#ifdef COPASI_UNDO
void CQParameterOverviewWidget:: slotChangeWidget(const size_t & id)
{
  leave();
  enterProtected();
  mpListView->switchToOtherWidget(id, "");
}
#endif
