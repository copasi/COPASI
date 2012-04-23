// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQParameterOverviewWidget.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/23 15:50:54 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtGui/QSortFilterProxyModel>

#include "CQParameterOverviewWidget.h"
#include "CQParameterOverviewDM.h"

#include "model/CModelParameterSet.h"

CQParameterOverviewWidget::CQParameterOverviewWidget(QWidget* parent, const char* name):
    CopasiWidget(parent, name),
    mpParameterSet(NULL),
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

  mpTreeView->expand(mpParameterSetSortDM->mapFromSource(mpParameterSetDM->index(0, 0, QModelIndex())));
}

CQParameterOverviewWidget::~CQParameterOverviewWidget()
{
  // TODO Auto-generated destructor stub
}

// virtual
bool CQParameterOverviewWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  // placeholder, ensure compilation under MSVC
  return true;
}

// virtual
bool CQParameterOverviewWidget::leave()
{
  // placeholder, ensure compilation under MSVC
  return true;
}

// virtual
bool CQParameterOverviewWidget::enterProtected()
{
  mpParameterSet = dynamic_cast< CModelParameterSet * >(mpObject);

  if (!mpParameterSet)
    {

      mpListView->switchToOtherWidget(1, "");
      return false;
    }

  mpParameterSetDM->setModelParameterset(mpParameterSet);
  mpTreeView->expandAll();

  return true;

}

// virtual
void CQParameterOverviewWidget::slotBtnSave()
{

}

// virtual
void CQParameterOverviewWidget::dataChanged(const QModelIndex& topLeft,
    const QModelIndex& bottomRight)
{

}
