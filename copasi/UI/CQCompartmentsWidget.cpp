// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartmentsWidget.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/05/25 17:31:50 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QHeaderView>

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"

#include "CQCompartmentsWidget.h"
#include "qtUtilities.h"
#include "copasi.h"
#include "CQMessageBox.h"

/*
 *  Constructs a CQCompartmentsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQCompartmentsWidget::CQCompartmentsWidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  //Create Source Data Model.
  mpCompartmentDM = new CQCompartmentDM(this);

  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setDynamicSortFilter(true);
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(COL_NAME_COMPARTMENTS);

  //Setting values for Types comboBox
  mpTypeDelegate = new CQIndexComboDelegate(&mpCompartmentDM->getTypes(), this);
  mpTblCompartments->setItemDelegateForColumn(COL_TYPE_COMPARTMENTS, mpTypeDelegate);

  mpTblCompartments->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblCompartments->verticalHeader()->hide();

  // Connect the table widget
  connect(mpCompartmentDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
          this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQCompartmentsWidget::~CQCompartmentsWidget()
{
  pdelete(mpTypeDelegate);
  pdelete(mpProxyModel);
  pdelete(mpCompartmentDM);
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQCompartmentsWidget::languageChange()
{
  retranslateUi(this);
}

void CQCompartmentsWidget::slotBtnDeleteClicked()
{
  if (mpTblCompartments->hasFocus())
    {deleteSelectedCompartments();}
}

void CQCompartmentsWidget::deleteSelectedCompartments()
{
  QModelIndexList selRows = mpTblCompartments->selectionModel()->selectedRows(0);

  if (selRows.empty())
    {return;}

  QModelIndexList mappedSelRows;
  QModelIndexList::const_iterator i;

  for (i = selRows.begin(); i != selRows.end(); ++i)
    {mappedSelRows.append(mpProxyModel->mapToSource(*i));}

  if (mpCompartmentDM->removeRows(mappedSelRows))
    protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, "");
}

void CQCompartmentsWidget::slotBtnClearClicked()
{

  int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Compartments?",
                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpCompartmentDM->clear();
      protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, "");
    }
}

bool CQCompartmentsWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  return true;
}

bool CQCompartmentsWidget::leave()
{
  return true;
}

bool CQCompartmentsWidget::enter(const std::string & C_UNUSED(key))
{
  mpProxyModel->setSourceModel(mpCompartmentDM);
  //Set Model for the TableView
  mpTblCompartments->setModel(NULL);
  mpTblCompartments->setModel(mpProxyModel);
  mpTblCompartments->resizeColumnsToContents();

  return true;
}

void CQCompartmentsWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft),
                                       const QModelIndex& C_UNUSED(bottomRight))
{
  mpTblCompartments->resizeColumnsToContents();
  protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, "");
  protectedNotify(ListViews::MODEL, ListViews::CHANGE, "");
}

void CQCompartmentsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (mpCompartmentDM->isDefaultRow(index))
    return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  std::string key = pModel->getCompartments()[index.row()]->getKey();

  if (CCopasiRootContainer::getKeyFactory()->get(key))
    mpListView->switchToOtherWidget(0, key);
}

void CQCompartmentsWidget::keyPressEvent(QKeyEvent* ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
}

void CQCompartmentsWidget::slotFilterChanged()
{
  QRegExp regExp(mpLEFilter->text() + "|No Name", Qt::CaseInsensitive, QRegExp::RegExp);
  mpProxyModel->setFilterRegExp(regExp);
}
