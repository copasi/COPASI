// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtGui/QSortFilterProxyModel>

#include "CQParameterOverviewWidget.h"
#include "CQParameterOverviewDM.h"
#include "CQMessageBox.h"
#include "CopasiFileDialog.h"
#include "qtUtilities.h"

#include "commandline/CLocaleString.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModelParameterSet.h"
#include "model/CModel.h"
#include "report/CCopasiRootContainer.h"

CQParameterOverviewWidget::CQParameterOverviewWidget(QWidget* parent, const char* name):
  CopasiWidget(parent, name),
  mpParameterSet(NULL),
  mpParameterSetCopy(NULL),
  mpParameterSetDM(NULL),
  mpParameterSetSortDM(NULL)
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

  // mpTreeView->expand(mpParameterSetSortDM->mapFromSource(mpParameterSetDM->index(0, 0, QModelIndex())));

  // mpTreeView->setRowHidden(1, mpParameterSetSortDM->mapFromSource(mpParameterSetDM->index(0, 0, QModelIndex())), true);
}

CQParameterOverviewWidget::~CQParameterOverviewWidget()
{
  // TODO Auto-generated destructor stub
}

// virtual
bool CQParameterOverviewWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  // placeholder, ensure compilation under MSVC
  // We need to handle at lease STATE CHANGE, and MODEL ADD/DELETE

  return true;
}

// virtual
bool CQParameterOverviewWidget::leave()
{
  if (mpParameterSet == NULL)
    {
      return false;
    }

  if (mpParameterSetCopy->diff(*mpParameterSet) != CModelParameter::Identical)
    {
      mpParameterSet->assignSetContent(*mpParameterSetCopy);

      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      (*CCopasiRootContainer::getDatamodelList())[0]->changed();

      if (mpParameterSet->isActive())
        {
          mpParameterSet->updateModel();
          protectedNotify(ListViews::STATE, ListViews::CHANGE, "");
        }
      else
        {
          protectedNotify(ListViews::PARAMETERSET, ListViews::CHANGE, mKey);
        }
    }

  return true;
}

// virtual
void CQParameterOverviewWidget::setFramework(int framework)
{
  mpParameterSetDM->setFramework(framework);
  mpTreeView->expandAll();
}

// virtual
bool CQParameterOverviewWidget::enterProtected()
{
  mpParameterSet = dynamic_cast< CModelParameterSet * >(mpObject);

  if (!mpParameterSet)
    {
      mpParameterSetDM->setModelParameterset(NULL);
      pdelete(mpParameterSetCopy);

      mpListView->switchToOtherWidget(1, "");
      return false;
    }

  CModelParameterSet * pOldParameterSet = mpParameterSetCopy;
  mpParameterSetCopy = new CModelParameterSet(*mpParameterSet, mpDataModel);
  mpParameterSetDM->setModelParameterset(mpParameterSetCopy);
  pdelete(pOldParameterSet);

  if (mpParameterSet->isActive())
    {
      mpTreeView->header()->hideSection(1);
    }

  mpTreeView->expandAll();

  for (int i = 0; i < 6; i++)
    {
      mpTreeView->resizeColumnToContents(i);
    }

  return true;
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

  mpParameterSet->saveToStream(file, mode, separator);

  file.close();
}

// virtual
void CQParameterOverviewWidget::dataChanged(const QModelIndex& /* topLeft */,
    const QModelIndex& /* bottomRight */)
{
}
