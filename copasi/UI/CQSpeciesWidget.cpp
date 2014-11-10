// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQSpeciesWidget.h"

#include <QtGui/QHeaderView>
#include <QtGui/QClipboard>
#include <QtGui/QKeyEvent>

#include "copasi.h"

#include "qtUtilities.h"
#include "CQMessageBox.h"

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"

#ifdef COPASI_UNDO
#include "copasiui3window.h"
#endif

/*
 *  Constructs a CQSpeciesWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQSpeciesWidget::CQSpeciesWidget(QWidget* parent, const char* name)
  : CopasiWidget(parent, name)
{
  setupUi(this);

  //Create Source Data Model.
  mpSpecieDM = new CQSpecieDM(this);

  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);
  mpProxyModel->setSourceModel(mpSpecieDM);

  mpTblSpecies->setModel(mpProxyModel);

  //Setting values for Compartment comboBox
  mpCompartmentDelegate = new CQComboDelegate(&mCompartments, this);
  mpTblSpecies->setItemDelegateForColumn(COL_COMPARTMENT, mpCompartmentDelegate);

  //Setting values for Types comboBox
  mpTypeDelegate = new CQIndexComboDelegate(&mpSpecieDM->getTypes(), this);
  mpTblSpecies->setItemDelegateForColumn(COL_TYPE_SPECIES, mpTypeDelegate);

  mpTblSpecies->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblSpecies->verticalHeader()->hide();
  mpTblSpecies->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

  // Connect the table widget
  connect(mpSpecieDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const std::string)));
  connect(mpSpecieDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
          this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));

#ifdef COPASI_UNDO
  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  mpSpecieDM->setUndoStack(pWindow->getUndoStack());
  connect(mpSpecieDM, SIGNAL(changeWidget(const size_t&)), this, SLOT(slotChangeWidget(const size_t&)));
#endif
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
  mpSpecieDM->insertRow();
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
  const QItemSelectionModel * pSelectionModel = mpTblSpecies->selectionModel();

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

bool CQSpeciesWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (!mIgnoreUpdates)
    {
      enterProtected();
    }

  return true;
}

bool CQSpeciesWidget::leave()
{
  return true;
}

bool CQSpeciesWidget::enterProtected()
{
  if (mpTblSpecies->selectionModel() != NULL)
    {
      disconnect(mpTblSpecies->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
                 this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
    }

  mpProxyModel->setSourceModel(mpSpecieDM);
  //Set Model for the TableView
  mpTblSpecies->setModel(NULL);
  mpTblSpecies->setModel(mpProxyModel);

  connect(mpTblSpecies->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
          this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
  updateDeleteBtns();
  mpTblSpecies->resizeColumnsToContents();
  setFramework(mFramework);
  refreshCompartments();

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

void CQSpeciesWidget::slotSelectionChanged(const QItemSelection& C_UNUSED(selected),
    const QItemSelection& C_UNUSED(deselected))
{
  updateDeleteBtns();
}

void CQSpeciesWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft),
                                  const QModelIndex& C_UNUSED(bottomRight))
{
  mpTblSpecies->resizeColumnsToContents();
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

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  std::string key = pModel->getMetabolites()[index.row()]->getKey();

  if (CCopasiRootContainer::getKeyFactory()->get(key))
    mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQSpeciesWidget::keyPressEvent(QKeyEvent* ev)
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
  QRegExp regExp(mpLEFilter->text() + "|New Species", Qt::CaseInsensitive, QRegExp::RegExp);
  mpProxyModel->setFilterRegExp(regExp);
}

void CQSpeciesWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  switch (mFramework)
    {
      case 0:
        mpTblSpecies->showColumn(COL_ICONCENTRATION);
        mpTblSpecies->showColumn(COL_CONCENTRATION);
        mpTblSpecies->showColumn(COL_CRATE);

        mpTblSpecies->hideColumn(COL_INUMBER);
        mpTblSpecies->hideColumn(COL_NUMBER);
        mpTblSpecies->hideColumn(COL_NRATE);

        mpSpecieDM->setFlagConc(true);
        break;

      case 1:
        mpTblSpecies->hideColumn(COL_ICONCENTRATION);
        mpTblSpecies->hideColumn(COL_CONCENTRATION);
        mpTblSpecies->hideColumn(COL_CRATE);

        mpTblSpecies->showColumn(COL_INUMBER);
        mpTblSpecies->showColumn(COL_NUMBER);
        mpTblSpecies->showColumn(COL_NRATE);

        mpSpecieDM->setFlagConc(false);
        break;
    }
}

void CQSpeciesWidget::refreshCompartments()
{
  const CCopasiVector < CCompartment > & compartments =
    (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments();
  mCompartments.clear();

  for (unsigned C_INT32 jj = 0; jj < compartments.size(); jj++)
    mCompartments.push_back(FROM_UTF8(compartments[jj]->getObjectName()));
}

#ifdef COPASI_UNDO
void CQSpeciesWidget:: slotChangeWidget(const size_t & id)
{
  mpListView->switchToOtherWidget(id, "");
}
#endif
