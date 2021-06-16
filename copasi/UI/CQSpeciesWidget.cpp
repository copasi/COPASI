// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQSpeciesWidget.h"

#include <QHeaderView>
#include <QClipboard>
#include <QKeyEvent>

#include "copasi/copasi.h"

#include "qtUtilities.h"
#include "CQMessageBox.h"

#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include <copasi/commandline/CConfigurationFile.h>

#include "copasiui3window.h"

/*
 *  Constructs a CQSpeciesWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQSpeciesWidget::CQSpeciesWidget(QWidget *parent, const char *name)
  : CopasiWidget(parent, name)
{
  setupUi(this);
  //Create Source Data Model.
  mpSpecieDM = new CQSpecieDM(this);
  mpSpecieDM->setDataModel(mpDataModel);
  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);
  mpProxyModel->setSourceModel(mpSpecieDM);
  mpTblSpecies->setModel(mpProxyModel);
  //Setting values for Compartment comboBox
  mpCompartmentDelegate = new CQComboDelegate(this, mCompartments);
  mpTblSpecies->setItemDelegateForColumn(COL_COMPARTMENT, mpCompartmentDelegate);
  //Setting values for Types comboBox
  mpTypeDelegate = new CQComboDelegate(this, mpSpecieDM->getTypes(), false);
  mpTblSpecies->setItemDelegateForColumn(COL_TYPE_SPECIES, mpTypeDelegate);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpTblSpecies->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#endif

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      mpTblSpecies->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
      mpTblSpecies->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
    }

  mpTblSpecies->verticalHeader()->hide();
  mpTblSpecies->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
  // Connect the table widget
  connect(mpSpecieDM, SIGNAL(signalNotifyChanges(const CUndoData::CChangeSet &)),
          this, SLOT(slotNotifyChanges(const CUndoData::CChangeSet &)));
  connect(mpSpecieDM, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
  connect(this, SIGNAL(initFilter()), this, SLOT(slotFilterChanged()));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
  connect(mpTblSpecies, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotSelectionChanged()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQSpeciesWidget::~CQSpeciesWidget()
{
  pdelete(mpCompartmentDelegate);
  pdelete(mpTypeDelegate);
  pdelete(mpProxyModel);
  pdelete(mpSpecieDM);
  // no need to delete child widgets, Qt does it all for us
}

void CQSpeciesWidget::slotBtnNewClicked()
{
  mpSpecieDM->insertRow(mpSpecieDM->rowCount() - 1, QModelIndex());
  updateDeleteBtns();
}

void CQSpeciesWidget::slotBtnDeleteClicked()
{
  if (mpTblSpecies->hasFocus())
    {deleteSelectedSpecies();}

  updateDeleteBtns();
}

void CQSpeciesWidget::deleteSelectedSpecies()
{
  const QItemSelectionModel *pSelectionModel = mpTblSpecies->selectionModel();
  QModelIndexList mappedSelRows;
  size_t i, imax = mpSpecieDM->rowCount();

  for (i = 0; i < imax; i++)
    {
      if (pSelectionModel->isRowSelected((int) i, QModelIndex()))
        {
          mappedSelRows.append(mpProxyModel->mapToSource(mpProxyModel->index((int) i, 0)));
        }
    }

  if (mappedSelRows.empty())
    {return;}

  mpSpecieDM->removeRows(mappedSelRows);
}

void CQSpeciesWidget::slotBtnClearClicked()
{
  int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all Species?",
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpSpecieDM->clear();
    }

  updateDeleteBtns();
}

bool CQSpeciesWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (mIgnoreUpdates || !isVisible())
    {
      return true;
    }

  if (objectType == ListViews::ObjectType::MODEL ||
      objectType == ListViews::ObjectType::STATE ||
      objectType == ListViews::ObjectType::METABOLITE)
    {
      enterProtected();
    }

  return true;
}

bool CQSpeciesWidget::leaveProtected()
{
  return true;
}

bool CQSpeciesWidget::enterProtected()
{
  QByteArray State = mpTblSpecies->horizontalHeader()->saveState();
  blockSignals(true);

  mpSpecieDM->setDataModel(mpDataModel);
  mpProxyModel->setSourceModel(mpSpecieDM);
  //Set Model for the TableView
  mpTblSpecies->setModel(NULL);
  mpTblSpecies->setModel(mpProxyModel);

  updateDeleteBtns();
  mpTblSpecies->horizontalHeader()->restoreState(State);
  blockSignals(false);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblSpecies->resizeColumnsToContents();
    }

  setFramework(mFramework);
  refreshCompartments();
  emit initFilter();

  return true;
}

void CQSpeciesWidget::updateDeleteBtns()
{
  bool selected = false;
  QModelIndexList selRows = mpTblSpecies->selectionModel()->selectedRows();

  if (selRows.size() == 0)
    selected = false;
  else
    {
      if (selRows.size() == 1)
        {
          if (mpSpecieDM->isDefaultRow(mpProxyModel->mapToSource(selRows[0])))
            selected = false;
          else
            selected = true;
        }
      else
        selected = true;
    }

  mpBtnDelete->setEnabled(selected);

  if (mpProxyModel->rowCount() - 1)
    mpBtnClear->setEnabled(true);
  else
    mpBtnClear->setEnabled(false);
}

void CQSpeciesWidget::slotSelectionChanged()
{
  updateDeleteBtns();
}

void CQSpeciesWidget::dataChanged(const QModelIndex &C_UNUSED(topLeft),
                                  const QModelIndex &C_UNUSED(bottomRight))
{
  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblSpecies->resizeColumnsToContents();
    }

  setFramework(mFramework);
  refreshCompartments();
  updateDeleteBtns();
}

void CQSpeciesWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (index.row() < 0)
    return;

  if (mpSpecieDM->isDefaultRow(index))
    {
      slotBtnNewClicked();
    }

  CDataVector < CMetab > * pVector = dynamic_cast< CDataVector < CMetab > * >(mpObject);

  if (pVector != NULL &&
      index.row() < pVector->size())
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::SpeciesDetail, pVector->operator [](index.row()).getCN());
    }
}

void CQSpeciesWidget::keyPressEvent(QKeyEvent *ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C && (ev->modifiers() & Qt::ControlModifier))
    {
      QModelIndexList selRows = mpTblSpecies->selectionModel()->selectedRows(0);

      if (selRows.empty())
        {return;}

      QString str;
      QModelIndexList::const_iterator i;

      for (i = selRows.begin(); i != selRows.end(); ++i)
        {
          for (int x = 0; x < mpSpecieDM->columnCount(); ++x)
            {
              if (!mpTblSpecies->isColumnHidden(x))
                {
                  if (!str.isEmpty())
                    str += "\t";

                  str += mpSpecieDM->index(mpProxyModel->mapToSource(*i).row(), x).data().toString();
                }
            }

          str += "\n";
        }

      QApplication::clipboard()->setText(str);
    }
}

void CQSpeciesWidget::slotFilterChanged()
{
  QString Filter = mpLEFilter->text();

  setFilterExpression(mpProxyModel, Filter.isEmpty(), Filter + "|New Species");

  while (mpProxyModel->canFetchMore(QModelIndex()))
    mpProxyModel->fetchMore(QModelIndex());
}

void CQSpeciesWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);
  mpSpecieDM->setFramework(framework);

  switch (mFramework)
    {
      case 0:
        mpTblSpecies->showColumn(COL_ICONCENTRATION);
        mpTblSpecies->showColumn(COL_CONCENTRATION);
        mpTblSpecies->showColumn(COL_CRATE);
        mpTblSpecies->hideColumn(COL_INUMBER);
        mpTblSpecies->hideColumn(COL_NUMBER);
        mpTblSpecies->hideColumn(COL_NRATE);
        break;

      case 1:
        mpTblSpecies->hideColumn(COL_ICONCENTRATION);
        mpTblSpecies->hideColumn(COL_CONCENTRATION);
        mpTblSpecies->hideColumn(COL_CRATE);
        mpTblSpecies->showColumn(COL_INUMBER);
        mpTblSpecies->showColumn(COL_NUMBER);
        mpTblSpecies->showColumn(COL_NRATE);
        break;
    }
}

CQBaseDataModel * CQSpeciesWidget::getCqDataModel()
{
  return mpSpecieDM;
}

void CQSpeciesWidget::refreshCompartments()
{
  const CDataVector < CCompartment > &compartments =
    mpDataModel->getModel()->getCompartments();
  mCompartments.clear();

  for (unsigned C_INT32 jj = 0; jj < compartments.size(); jj++)
    mCompartments.push_back(FROM_UTF8(compartments[jj].getObjectName()));

  mpCompartmentDelegate->setItems(-1, mCompartments);
}
