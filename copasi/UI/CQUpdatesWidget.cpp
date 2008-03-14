// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQUpdatesWidget.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/03/14 23:40:13 $
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
#include "parametertable.h" //for color table item

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

  //main tab widget
  mpMainTab = new QTabWidget(this, "MainTabWidget");
  mWidgetLayout->addMultiCellWidget(mpMainTab, 1, 2, 0, 2);

  // tab widget
  mpTab = new QTabWidget(mpMainTab, "TabWidget");
  mpMainTab->addTab(mpTab, "Update Sequences");

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

  // tab widget 2
  mpTab2 = new QTabWidget(mpMainTab, "TabWidget2");
  mpMainTab->addTab(mpTab2, "Object Lists");

  //objects table
  mpTableObj = new QTable(mpTab2, "TableObj");
  mpTab2->addTab(mpTableObj, "Species");

  //state table
  mpTableState = new QTable(mpTab2, "TableState");
  mpTab2->addTab(mpTableState, "State");
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

  loadObjectsTable(pModel);
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
        pTable->setText(i, 0, FROM_UTF8(it->second->getObjectDisplayName()));
      const CCopasiObject* tmp = list[i]->getObject();
      if (tmp)
        pTable->setText(i, 1, FROM_UTF8(tmp->getObjectDisplayName()));
    }
}

void CQUpdatesWidget::clearArrays()
{}

void CQUpdatesWidget::loadObjectsTable(CModel* pModel)
{
  if (!pModel) return;
  mpTableObj->setNumCols(5);
  mpTableObj->setNumRows(0);

  mpTableObj->horizontalHeader()->setLabel(0, "User order");
  mpTableObj->horizontalHeader()->setLabel(1, "status");
  mpTableObj->horizontalHeader()->setLabel(2, "");
  mpTableObj->horizontalHeader()->setLabel(3, "Reduced system");
  mpTableObj->horizontalHeader()->setLabel(4, "status");

  int i, imax;

  //metabolites
  imax = pModel->getMetabolites().size();
  if (imax > mpTableObj->numRows()) mpTableObj->setNumRows(imax);
  for (i = 0; i < imax; ++i)
    {
      mpTableObj->verticalHeader()->setLabel(i, QString::number(i));

      CMetab* pM = pModel->getMetabolites()[i];

      QColor c(100, 100, 100);
      if (pM->getStatus() == CModelEntity::FIXED) c = QColor(150, 150, 150);
      if (pM->getStatus() == CModelEntity::ASSIGNMENT) c = QColor(250, 150, 250);
      if (pM->getStatus() == CModelEntity::REACTIONS) c = QColor(250, 250, 200);
      if (pM->getStatus() == CModelEntity::ODE) c = QColor(150, 250, 250);
      if (pM->getStatus() == CModelEntity::TIME) c = QColor(250, 150, 150);

      mpTableObj->setItem(i, 0, new ColorTableItem(mpTableObj, QTableItem::Never, c,
                          FROM_UTF8(pM->getObjectName())));
      //mpTableObj->setText(i, 0, FROM_UTF8(pM->getObjectName()));
      std::string tmpString = CModelEntity::StatusName[pM->getStatus()];
      if (pM->isUsed())
        tmpString += " (Used = true, ";
      else
        tmpString += " (Used = false, ";
      if (pM->isUsedOnce())
        tmpString += "UsedOnce = true)";
      else
        tmpString += "UsedOnce = false)";

      mpTableObj->setItem(i, 1, new ColorTableItem(mpTableObj, QTableItem::Never, c,
                          FROM_UTF8(tmpString)));
      //mpTableObj->setText(i, 1, FROM_UTF8(tmpString));
    }
  mpTableObj->adjustColumn(0);
  mpTableObj->adjustColumn(1);
  mpTableObj->setColumnWidth(2, 10);

  //metabolitesX
  imax = pModel->getMetabolitesX().size();
  if (imax > mpTableObj->numRows()) mpTableObj->setNumRows(imax);
  for (i = 0; i < imax; ++i)
    {
      CMetab* pM = pModel->getMetabolitesX()[i];

      QColor c(100, 100, 100);
      if (pM->getStatus() == CModelEntity::FIXED) c = QColor(150, 150, 150);
      if (pM->getStatus() == CModelEntity::ASSIGNMENT) c = QColor(250, 150, 250);
      if (pM->getStatus() == CModelEntity::REACTIONS) c = QColor(250, 250, 200);
      if (pM->getStatus() == CModelEntity::ODE) c = QColor(150, 250, 250);
      if (pM->getStatus() == CModelEntity::TIME) c = QColor(250, 150, 150);

      mpTableObj->setItem(i, 3, new ColorTableItem(mpTableObj, QTableItem::Never, c,
                          FROM_UTF8(pM->getObjectName())));
      //mpTableObj->setText(i, 3, FROM_UTF8(pM->getObjectName()));

      std::string tmpString = CModelEntity::StatusName[pM->getStatus()];
      if (pM->isUsed())
        tmpString += " (Used = true, ";
      else
        tmpString += " (Used = false, ";
      if (pM->isUsedOnce())
        tmpString += "UsedOnce = true)";
      else
        tmpString += "UsedOnce = false)";
      mpTableObj->setItem(i, 4, new ColorTableItem(mpTableObj, QTableItem::Never, c,
                          FROM_UTF8(tmpString)));
      //      mpTableObj->setText(i, 4, FROM_UTF8(tmpString));
    }
  mpTableObj->adjustColumn(3);
  mpTableObj->adjustColumn(4);

  //state
  CStateTemplate & st = pModel->getStateTemplate();
  imax = st.size();
  mpTableState->setNumRows(0);
  mpTableState->setNumRows(imax + 1);
  mpTableState->setNumCols(3);
  mpTableState->horizontalHeader()->setLabel(0, "Name");
  mpTableState->horizontalHeader()->setLabel(1, "status");
  mpTableState->horizontalHeader()->setLabel(2, "");

  for (i = 0; i < imax; ++i)
    {
      mpTableState->verticalHeader()->setLabel(i, QString::number(i));

      CModelEntity* pME = *(st.getEntities() + i);

      //first column
      QColor c(100, 100, 100);
      if (dynamic_cast<CModel*>(pME)) c = QColor(250, 100, 100);
      if (dynamic_cast<CMetab*>(pME)) c = QColor(250, 250, 150);
      if (dynamic_cast<CCompartment*>(pME)) c = QColor(100, 250, 100);
      if (dynamic_cast<CModelValue*>(pME)) c = QColor(100, 100, 250);

      mpTableState->setItem(i, 0, new ColorTableItem(mpTableState, QTableItem::Never, c,
                            FROM_UTF8(pME->getObjectDisplayName())));
      //      mpTableState->setText(i, 0,FROM_UTF8(pME->getObjectDisplayName()));

      //second column
      std::string tmpString = CModelEntity::StatusName[pME->getStatus()];
      if (pME->isUsed())
        tmpString += " (Used = true, ";
      else
        tmpString += " (Used = false, ";
      if (pME->isUsedOnce())
        tmpString += "UsedOnce = true)";
      else
        tmpString += "UsedOnce = false)";

      c = QColor(100, 100, 100);
      if (pME->getStatus() == CModelEntity::FIXED) c = QColor(150, 150, 150);
      if (pME->getStatus() == CModelEntity::ASSIGNMENT) c = QColor(250, 150, 250);
      if (pME->getStatus() == CModelEntity::REACTIONS) c = QColor(250, 250, 200);
      if (pME->getStatus() == CModelEntity::ODE) c = QColor(150, 250, 250);
      if (pME->getStatus() == CModelEntity::TIME) c = QColor(250, 150, 150);

      mpTableState->setItem(i, 1, new ColorTableItem(mpTableState, QTableItem::Never, c,
                            FROM_UTF8(tmpString)));
      //mpTableState->setText(i, 1, FROM_UTF8(tmpString));
    }

  QColor c(200, 250, 250);
  for (i = st.beginIndependent() - st.getEntities(); i < st.endIndependent() - st.getEntities(); ++i)
    mpTableState->setItem(i, 2, new ColorTableItem(mpTableState, QTableItem::Never, c, ""));
  c = QColor(250, 200, 250);
  for (i = st.beginDependent() - st.getEntities(); i < st.endDependent() - st.getEntities(); ++i)
    mpTableState->setItem(i, 2, new ColorTableItem(mpTableState, QTableItem::Never, c, ""));
  c = QColor(200, 200, 200);
  for (i = st.beginFixed() - st.getEntities(); i < st.endFixed() - st.getEntities(); ++i)
    mpTableState->setItem(i, 2, new ColorTableItem(mpTableState, QTableItem::Never, c, ""));

  int tmpint = st.beginIndependent() - st.getEntities();
  mpTableState->setText(tmpint, 2, "beginIndependent ");
  tmpint = st.endIndependent() - st.getEntities();
  mpTableState->setText(tmpint, 2, mpTableState->text(tmpint, 2) + "endIndependent ");

  tmpint = st.beginDependent() - st.getEntities();
  mpTableState->setText(tmpint, 2, mpTableState->text(tmpint, 2) + "beginDependent ");
  tmpint = st.endDependent() - st.getEntities();
  mpTableState->setText(tmpint, 2, mpTableState->text(tmpint, 2) + "endDependent ");

  tmpint = st.beginFixed() - st.getEntities();
  mpTableState->setText(tmpint, 2, mpTableState->text(tmpint, 2) + "beginFixed ");
  tmpint = st.endFixed() - st.getEntities();
  mpTableState->setText(tmpint, 2, mpTableState->text(tmpint, 2) + "endFixed ");

  mpTableState->adjustColumn(0);
  mpTableState->adjustColumn(1);
  mpTableState->adjustColumn(2);
}

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
