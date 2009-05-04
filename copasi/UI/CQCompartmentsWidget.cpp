// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartmentsWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/05/04 16:38:08 $
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
  mpProxyModel->setFilterKeyColumn(COL_NAME);

  //Setting values for Types comboBox
  mpTypeDelegate = new CQIndexComboDelegate(&mpCompartmentDM->getTypes(), this);
  mpTblCompartments->setItemDelegateForColumn(COL_TYPE, mpTypeDelegate);

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
    {deleteSelectedCompartment();}
}

void CQCompartmentsWidget::deleteSelectedCompartment()
{
  if (mpTblCompartments->selectionModel()->selectedIndexes().empty())
    {return;}

  int delRow = mpTblCompartments->selectionModel()->selectedIndexes().value(0).row();

  if (mpCompartmentDM->isDefaultRow(delRow))
    return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  QString compartmentList = "Are you sure you want to delete listed COMPARTMENT(S) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedMetabList = "Following SPECIES reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above COMPARTMENT(S) and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  CCompartment * pCompartment = pModel->getCompartments()[delRow];

  compartmentList.append(FROM_UTF8(pCompartment->getObjectName()));
  compartmentList.append(", ");

  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;

  pModel->appendDependentModelObjects(pCompartment->getDeletedObjects(),
                                      Reactions, Metabolites, Compartments, Values);

  if (Reactions.size() > 0)
    {
      reacFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Reactions.end();

      for (it = Reactions.begin(); it != itEnd; ++it)
        {
          effectedReacList.append(FROM_UTF8((*it)->getObjectName()));
          effectedReacList.append(", ");
        }

      effectedReacList.remove(effectedReacList.length() - 2, 2);
      effectedReacList.append("  ---> ");
      effectedReacList.append(FROM_UTF8(pCompartment->getObjectName()));
      effectedReacList.append("\n");
    }

  if (Metabolites.size() > 0)
    {
      metabFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Metabolites.end();

      for (it = Metabolites.begin(); it != itEnd; ++it)
        {
          effectedMetabList.append(FROM_UTF8((*it)->getObjectName()));
          effectedMetabList.append(", ");
        }

      effectedMetabList.remove(effectedMetabList.length() - 2, 2);
      effectedMetabList.append("  ---> ");
      effectedMetabList.append(FROM_UTF8(pCompartment->getObjectName()));
      effectedMetabList.append("\n");
    }

  if (Values.size() > 0)
    {
      valueFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Values.end();

      for (it = Values.begin(); it != itEnd; ++it)
        {
          effectedValueList.append(FROM_UTF8((*it)->getObjectName()));
          effectedValueList.append(", ");
        }

      effectedValueList.remove(effectedValueList.length() - 2, 2);
      effectedValueList.append("  ---> ");
      effectedValueList.append(FROM_UTF8(pCompartment->getObjectName()));
      effectedValueList.append("\n");
    }

  if (Compartments.size() > 0)
    {
      compartmentFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Compartments.end();

      for (it = Compartments.begin(); it != itEnd; ++it)
        {
          effectedCompartmentList.append(FROM_UTF8((*it)->getObjectName()));
          effectedCompartmentList.append(", ");
        }

      effectedCompartmentList.remove(effectedCompartmentList.length() - 2, 2);
      effectedCompartmentList.append("  ---> ");
      effectedCompartmentList.append(FROM_UTF8(pCompartment->getObjectName()));
      effectedCompartmentList.append("\n");
    }

  compartmentList.remove(compartmentList.length() - 2, 2);

  QString msg = compartmentList;

  if (compartmentFound)
    {
      msg.append("\n \n");
      msg.append(effectedCompartmentList);
    }

  if (metabFound)
    {
      msg.append("\n \n");
      msg.append(effectedMetabList);
    }

  if (reacFound)
    {
      msg.append("\n \n");
      msg.append(effectedReacList);
    }

  if (valueFound)
    {
      msg.append("\n \n");
      msg.append(effectedValueList);
    }

  C_INT32 choice = 0;
  //if (metabFound || reacFound || compartmentFound || valueFound)
  choice = CQMessageBox::question(this,
                                  "CONFIRM DELETE",
                                  msg,
                                  QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);

  if (choice == QMessageBox::Ok)
    {
      if (mpTblCompartments->hasFocus())
        {
          mpCompartmentDM->removeRow(delRow);
          protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, "");
        }
    }
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
