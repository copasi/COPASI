// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSpeciesWidget.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/06/12 19:58:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QHeaderView>

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"

#include "CQSpeciesWidget.h"
#include "qtUtilities.h"
#include "copasi.h"
#include "CQMessageBox.h"

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
  mpProxyModel->setDynamicSortFilter(true);
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(COL_NAME_SPECIES);

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
          this, SLOT(slotNotifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)));
  connect(mpSpecieDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
          this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
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

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQSpeciesWidget::languageChange()
{
  retranslateUi(this);
}

void CQSpeciesWidget::slotBtnDeleteClicked()
{
  if (mpTblSpecies->hasFocus())
    {deleteSelectedSpecies();}
}

void CQSpeciesWidget::deleteSelectedSpecies()
{
  QModelIndexList selRows = mpTblSpecies->selectionModel()->selectedRows(0);

  if (selRows.empty())
    {return;}

  QModelIndexList mappedSelRows;
  QModelIndexList::const_iterator i;

  for (i = selRows.begin(); i != selRows.end(); ++i)
    {mappedSelRows.append(mpProxyModel->mapToSource(*i));}

  if (mpSpecieDM->removeRows(mappedSelRows))
    protectedNotify(ListViews::REACTION, ListViews::DELETE, "");
}

void CQSpeciesWidget::slotBtnClearClicked()
{

  int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Species?",
                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpSpecieDM->clear();
      protectedNotify(ListViews::METABOLITE, ListViews::DELETE, "");
    }
}

bool CQSpeciesWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  return true;
}

bool CQSpeciesWidget::leave()
{
  return true;
}

bool CQSpeciesWidget::enter(const std::string & C_UNUSED(key))
{
  mpProxyModel->setSourceModel(mpSpecieDM);
  //Set Model for the TableView
  mpTblSpecies->setModel(NULL);
  mpTblSpecies->setModel(mpProxyModel);
  mpTblSpecies->resizeColumnsToContents();
  setFramework(mFramework);
  refreshCompartments();

  return true;
}

void CQSpeciesWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft),
                                  const QModelIndex& C_UNUSED(bottomRight))
{
  mpTblSpecies->resizeColumnsToContents();
  setFramework(mFramework);
  refreshCompartments();
}

void CQSpeciesWidget::slotNotifyGUI(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  protectedNotify(objectType, action, key);
}

void CQSpeciesWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (mpSpecieDM->isDefaultRow(index))
    return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  std::string key = pModel->getMetabolites()[index.row()]->getKey();

  if (CCopasiRootContainer::getKeyFactory()->get(key))
    mpListView->switchToOtherWidget(0, key);
}

void CQSpeciesWidget::keyPressEvent(QKeyEvent* ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
}

void CQSpeciesWidget::slotFilterChanged()
{
  QRegExp regExp(mpLEFilter->text() + "|No Name", Qt::CaseInsensitive, QRegExp::RegExp);
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
