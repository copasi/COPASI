// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQUpdatesWidget.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/02/19 15:00:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qtable.h>

#include "copasi.h"

#include "CQUpdatesWidget.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"

#include "model/CModel.h"

#include <qtabwidget.h>

/**
 *  Constructs a CQUpdatesWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQUpdatesWidget::CQUpdatesWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("CQUpdatesWidget");
  setCaption("CQUpdatesWidget");

  mWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "CQUpdatesWidgetLayout");

  // **********  Label **************
  mLabelTitle = new QLabel(this, "updatesLabel");
  mLabelTitle->setText("Sequences of assignments");
  mLabelTitle->setAlignment(int(QLabel::AlignVCenter
                                | QLabel::AlignLeft));
  mLabelTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  mWidgetLayout->addWidget(mLabelTitle, 0, 0);

  // tab widget
  mpTab = new QTabWidget(this, "TabWidget");
  mWidgetLayout->addMultiCellWidget(mpTab, 1, 2, 0, 2);

  // 0
  mpTable0 = new QTable(mpTab, "Table0");
  mpTab->addTab(mpTable0, "Initial Assignments");

  // 1
  mpTable1 = new QTable(mpTab, "Table1");
  mpTab->addTab(mpTable1, "Constant Assignments");

  // 2
  mpTable2 = new QTable(mpTab, "Table2");
  mpTab->addTab(mpTable2, "Assignments during Simulation");

  // 3
  mpTable3 = new QTable(mpTab, "Table3");
  mpTab->addTab(mpTable3, "Assignments for output");
}

CQUpdatesWidget::~CQUpdatesWidget()
{}

void CQUpdatesWidget::fillRefreshsMapRecursively(const CCopasiObject* obj)
{
  if (obj->getRefresh())
    mRefreshsMap[obj->getRefresh()] = obj;

  //recursion
  if (obj->isContainer())
    {
      CCopasiContainer* container;
      container = (CCopasiContainer*)obj;

      CCopasiContainer::objectMap::const_iterator it = container->getObjects().begin();
      // int cnt = container->getObjects().size();

      for (; it != container->getObjects().end(); ++it)
        {
          //the next line skips name references...
          if (it->second->getObjectName() == "Name") continue;

          if (it->second->getObjectType() == "Function") continue;

          //skip if the contained object is not owned by this container
          if (it->second->getObjectParent() != container) continue;

          fillRefreshsMapRecursively(it->second);
        }
      //return;
    }
}

void CQUpdatesWidget::loadWidget()
{

  CModel* pModel = CCopasiDataModel::Global->getModel();
  if (!pModel) return;
  pModel->compileIfNecessary(NULL);
  mRefreshsMap.clear();
  fillRefreshsMapRecursively(pModel);

  loadOneTable(mpTable0, pModel->getListOfInitialRefreshes());
  loadOneTable(mpTable1, pModel->getListOfConstantRefreshes());
  loadOneTable(mpTable2, pModel->getListOfSimulatedRefreshes());
  loadOneTable(mpTable3, pModel->getListOfNonSimulatedRefreshes());
}

void CQUpdatesWidget::loadOneTable(QTable* pTable, const std::vector< Refresh * > & list)
{
  pTable->setNumCols(2);

  C_INT32 i, imax = list.size();
  pTable->setNumRows(imax);
  for (i = 0; i < imax; ++i)
    {
      std::map<const Refresh*, const CCopasiObject*>::const_iterator it = mRefreshsMap.find(list[i]);
      if (it != mRefreshsMap.end() && it->second)
        pTable->setText(i, 0, it->second->getObjectDisplayName());
      const CCopasiObject* tmp = list[i]->getObject();
      if (tmp)
        pTable->setText(i, 1, tmp->getObjectDisplayName());
    }
}

void CQUpdatesWidget::clearArrays()
{}

//*************************************

bool CQUpdatesWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action
                             C_UNUSED(action), const std::string & C_UNUSED(key))
{
  return true;
}

bool CQUpdatesWidget::leave()
{
  return true;
}

bool CQUpdatesWidget::enter(const std::string & C_UNUSED(key))
{
  loadWidget();

  return true;
}
