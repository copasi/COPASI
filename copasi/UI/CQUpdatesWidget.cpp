// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QtGui/QTableWidget>
#include <QtGui/QTableWidgetItem>
#include <QtGui/QTabWidget>

#include "copasi.h"

#include "CQUpdatesWidget.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"

#include "model/CModel.h"
#include "math/CMathContainer.h"
#include "math/CMathUpdateSequence.h"

/**
 *  Constructs a CQUpdatesWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQUpdatesWidget::CQUpdatesWidget(QWidget* parent, const char* name, Qt::WFlags fl)
  : CopasiWidget(parent, name, fl)
{
  if (!name)
    setObjectName("CQUpdatesWidget");

  setWindowTitle("CQUpdatesWidget");

  mWidgetLayout = new QGridLayout(this);
  mWidgetLayout->setMargin(11);
  mWidgetLayout->setSpacing(6);
  mWidgetLayout->setObjectName("CQUpdatesWidgetLayout");

  // **********  Label **************
  mLabelTitle = new QLabel(this);
  mLabelTitle->setObjectName("updatesLabel");
  mLabelTitle->setText("Sequences of assignments");
  mLabelTitle->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  mLabelTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  mWidgetLayout->addWidget(mLabelTitle, 0, 0);

  //main tab widget
  mpMainTab = new QTabWidget(this);
  mpMainTab->setObjectName("MainTabWidget");
  mWidgetLayout->addWidget(mpMainTab, 1, 0, 2, 3);

  // tab widget
  mpTab = new QTabWidget(mpMainTab);
  mpTab->setObjectName("TabWidget");
  mpMainTab->addTab(mpTab, "Update Sequences");

  // 0
  mpTable0 = new QTableWidget(mpTab);
  mpTab->addTab(mpTable0, "Initial Assignments");

  // 1
  mpTable1 = new QTableWidget(mpTab);
  mpTab->addTab(mpTable1, "Constant Assignments");

  // 2
  mpTable2 = new QTableWidget(mpTab);
  mpTab->addTab(mpTable2, "Assignments during Simulation");

  // 3
  mpTable3 = new QTableWidget(mpTab);
  mpTab->addTab(mpTable3, "Assignments for output");

  // tab widget 2
  mpTab2 = new QTabWidget(mpMainTab);
  mpTab2->setObjectName("TabWidget2");
  mpMainTab->addTab(mpTab2, "Object Lists");

  //objects table
  mpTableObj = new QTableWidget(mpTab2);
  mpTab2->addTab(mpTableObj, "Species");

  //state table
  mpTableState = new QTableWidget(mpTab2);
  mpTab2->addTab(mpTableState, "State");
}

CQUpdatesWidget::~CQUpdatesWidget()
{}

void CQUpdatesWidget::loadWidget()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel* pModel = CCopasiRootContainer::getDatamodelList()->operator[](0).getModel();

  if (!pModel) return;

  pModel->compileIfNecessary(NULL);

  CMathContainer & Container = pModel->getMathContainer();

  loadOneTable(mpTable0, Container.getSynchronizeInitialValuesSequence(CModelParameter::ParticleNumbers));
  loadOneTable(mpTable1, Container.getApplyInitialValuesSequence());
  loadOneTable(mpTable2, Container.getSimulationValuesSequence(false));
  loadOneTable(mpTable3, Container.getTransientDataValueSequence());

  loadObjectsTable(pModel);
}

void CQUpdatesWidget::loadOneTable(QTableWidget * pTable, const CMathUpdateSequence & list)
{
  pTable->setColumnCount(2);
  pTable->setRowCount((int) list.size());
  CMathUpdateSequence::const_iterator it = list.begin();
  CMathUpdateSequence::const_iterator end = list.end();

  for (int i = 0; it != end; ++it, ++i)
    {
      const CCopasiObject * pDataObject = CObjectInterface::DataObject(*it);
      const CMathObject * pMathObject = dynamic_cast< const CMathObject * >(*it);

      if (pDataObject == NULL && pMathObject == NULL) continue;

      if (pDataObject != NULL)
        {
          pTable->setItem(i, 0, new QTableWidgetItem(FROM_UTF8(pDataObject->getObjectParent()->getObjectDisplayName())));
          pTable->setItem(i, 0, new QTableWidgetItem(FROM_UTF8(pDataObject->getObjectDisplayName())));
        }
      else if (pMathObject != NULL)
        {
          pTable->setItem(i, 0, new QTableWidgetItem("Math Container"));
          pTable->setItem(i, 0, new QTableWidgetItem(FROM_UTF8(pMathObject->getObjectDisplayName())));
        }
    }
}

void CQUpdatesWidget::clearArrays()
{}

void CQUpdatesWidget::loadObjectsTable(CModel* pModel)
{
  if (!pModel) return;

  mpTableObj->setColumnCount(5);
  mpTableObj->setRowCount(0);

  mpTableObj->setHorizontalHeaderItem(0, new QTableWidgetItem("User order"));
  mpTableObj->setHorizontalHeaderItem(1, new QTableWidgetItem("status"));
  mpTableObj->setHorizontalHeaderItem(2, new QTableWidgetItem(""));
  mpTableObj->setHorizontalHeaderItem(3, new QTableWidgetItem("Reduced system"));
  mpTableObj->setHorizontalHeaderItem(4, new QTableWidgetItem("status"));

  size_t i, imax;

  //metabolites
  imax = pModel->getMetabolites().size();

  if ((int) imax > mpTableObj->rowCount()) mpTableObj->setRowCount((int) imax);

  for (i = 0; i < imax; ++i)
    {
      mpTableObj->setVerticalHeaderItem((int) i, new QTableWidgetItem(QString::number(i)));

      CMetab* pM = &pModel->getMetabolites()[i];

      QColor c(100, 100, 100);

      if (pM->getStatus() == CModelEntity::FIXED) c = QColor(150, 150, 150);

      if (pM->getStatus() == CModelEntity::ASSIGNMENT) c = QColor(250, 150, 250);

      if (pM->getStatus() == CModelEntity::REACTIONS) c = QColor(250, 250, 200);

      if (pM->getStatus() == CModelEntity::ODE) c = QColor(150, 250, 250);

      if (pM->getStatus() == CModelEntity::TIME) c = QColor(250, 150, 150);

      mpTableObj->setItem((int) i, 0, new QTableWidgetItem(FROM_UTF8(pM->getObjectName())));

      //mpTableObj->setText(i, 0, FROM_UTF8(pM->getObjectName()));
      std::string tmpString = CModelEntity::StatusName[pM->getStatus()];

      if (pM->isUsed())
        tmpString += " (Used = true, ";
      else
        tmpString += " (Used = false, ";

      mpTableObj->setItem((int) i, 1, new QTableWidgetItem(FROM_UTF8(tmpString)));
      //mpTableObj->setText(i, 1, FROM_UTF8(tmpString));
    }

  mpTableObj->resizeColumnToContents(0);
  mpTableObj->resizeColumnToContents(1);
  mpTableObj->setColumnWidth(2, 10);

  //metabolitesX
  imax = pModel->getMetabolitesX().size();

  if ((int) imax > mpTableObj->rowCount()) mpTableObj->setRowCount((int) imax);

  for (i = 0; i < imax; ++i)
    {
      CMetab* pM = &pModel->getMetabolitesX()[i];

      QColor c(100, 100, 100);

      if (pM->getStatus() == CModelEntity::FIXED) c = QColor(150, 150, 150);

      if (pM->getStatus() == CModelEntity::ASSIGNMENT) c = QColor(250, 150, 250);

      if (pM->getStatus() == CModelEntity::REACTIONS) c = QColor(250, 250, 200);

      if (pM->getStatus() == CModelEntity::ODE) c = QColor(150, 250, 250);

      if (pM->getStatus() == CModelEntity::TIME) c = QColor(250, 150, 150);

      mpTableObj->setItem((int) i, 3, new QTableWidgetItem(FROM_UTF8(pM->getObjectName())));
      //mpTableObj->setText(i, 3, FROM_UTF8(pM->getObjectName()));

      std::string tmpString = CModelEntity::StatusName[pM->getStatus()];

      if (pM->isUsed())
        tmpString += " (Used = true, ";
      else
        tmpString += " (Used = false, ";

      mpTableObj->setItem((int) i, 4, new QTableWidgetItem(FROM_UTF8(tmpString)));
    }

  mpTableObj->resizeColumnToContents(3);
  mpTableObj->resizeColumnToContents(4);

  //state
  const CStateTemplate & st = pModel->getStateTemplate();
  imax = st.size();
  mpTableState->setRowCount(0);
  mpTableState->setRowCount((int)(imax + 1));
  mpTableState->setColumnCount(5);
  mpTableState->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
  mpTableState->setHorizontalHeaderItem(1, new QTableWidgetItem("status"));
  mpTableState->setHorizontalHeaderItem(2, new QTableWidgetItem(""));
  mpTableState->setHorizontalHeaderItem(3, new QTableWidgetItem("ATol(1)"));
  mpTableState->setHorizontalHeaderItem(4, new QTableWidgetItem("SS criterion(1)"));

  for (i = 0; i < imax; ++i)
    {
      mpTableState->setVerticalHeaderItem((int) i, new QTableWidgetItem(QString::number(i)));

      const CModelEntity * pME = *(st.getEntities().array() + i);

      //first column
      QColor c(100, 100, 100);

      if (dynamic_cast< const CModel * >(pME)) c = QColor(250, 100, 100);

      if (dynamic_cast< const CMetab * >(pME)) c = QColor(250, 250, 150);

      if (dynamic_cast< const CCompartment * >(pME)) c = QColor(100, 250, 100);

      if (dynamic_cast< const CModelValue * >(pME)) c = QColor(100, 100, 250);

      mpTableState->setItem((int) i, 0, new QTableWidgetItem(FROM_UTF8(pME->getObjectDisplayName())));
      //      mpTableState->setText(i, 0,FROM_UTF8(pME->getObjectDisplayName()));

      //second column
      std::string tmpString = CModelEntity::StatusName[pME->getStatus()];

      if (pME->isUsed())
        tmpString += " (Used = true, ";
      else
        tmpString += " (Used = false, ";

      c = QColor(100, 100, 100);

      if (pME->getStatus() == CModelEntity::FIXED) c = QColor(150, 150, 150);

      if (pME->getStatus() == CModelEntity::ASSIGNMENT) c = QColor(250, 150, 250);

      if (pME->getStatus() == CModelEntity::REACTIONS) c = QColor(250, 250, 200);

      if (pME->getStatus() == CModelEntity::ODE) c = QColor(150, 250, 250);

      if (pME->getStatus() == CModelEntity::TIME) c = QColor(250, 150, 150);

      mpTableState->setItem((int) i, 1, new QTableWidgetItem(FROM_UTF8(tmpString)));
      //mpTableState->setText(i, 1, FROM_UTF8(tmpString));
    }

  QColor c(200, 250, 250);

  for (i = st.beginIndependent() - st.getEntities().array(); i < (size_t)(st.endIndependent() - st.getEntities().array()); ++i)
    mpTableState->setItem((int) i, 2, new  QTableWidgetItem(""));

  c = QColor(250, 200, 250);

  for (i = st.beginDependent() - st.getEntities().array(); i < (size_t)(st.endDependent() - st.getEntities().array()); ++i)
    mpTableState->setItem((int) i, 2, new QTableWidgetItem(""));

  c = QColor(200, 200, 200);

  for (i = st.beginFixed() - st.getEntities().array(); i < (size_t)(st.endFixed() - st.getEntities().array()); ++i)
    mpTableState->setItem((int) i, 2, new QTableWidgetItem(""));

  int tmpint = st.beginIndependent() - st.getEntities().array();
  mpTableState->setItem(tmpint, 2, new QTableWidgetItem("beginIndependent "));
  tmpint = st.endIndependent() - st.getEntities().array();
  mpTableState->setItem(tmpint, 2, new QTableWidgetItem(mpTableState->item(tmpint, 2)->text() + "endIndependent "));

  tmpint = st.beginDependent() - st.getEntities().array();
  mpTableState->setItem(tmpint, 2, new QTableWidgetItem(mpTableState->item(tmpint, 2)->text() + "beginDependent "));
  tmpint = st.endDependent() - st.getEntities().array();
  mpTableState->setItem(tmpint, 2, new QTableWidgetItem(mpTableState->item(tmpint, 2)->text() + "endDependent "));

  tmpint = st.beginFixed() - st.getEntities().array();
  mpTableState->setItem(tmpint, 2, new QTableWidgetItem(mpTableState->item(tmpint, 2)->text() + "beginFixed "));
  tmpint = st.endFixed() - st.getEntities().array();
  mpTableState->setItem(tmpint, 2, new QTableWidgetItem("endFixed "));

  //add absolute Tolerances to table
  CVector< C_FLOAT64 > atolv = pModel->initializeAtolVector(1, false);
  tmpint = st.beginIndependent() - st.getEntities().array();

  for (i = 0; i < atolv.size(); ++i)
    {
      mpTableState->setItem((int) i + tmpint, 3, new QTableWidgetItem(QString::number(atolv[i])));

      const CModelEntity * pME = *(st.getEntities().array() + i + 1);
      C_FLOAT64 tmp = std::min(atolv[i], std::max(100.0 * std::numeric_limits< C_FLOAT64 >::min(), fabs(pME->getInitialValue())));
      mpTableState->setItem((int) i + tmpint, 4, new QTableWidgetItem(QString::number(tmp)));
    }

  mpTableState->resizeColumnToContents(0);
  mpTableState->resizeColumnToContents(1);
  mpTableState->resizeColumnToContents(2);
  mpTableState->resizeColumnToContents(3);
  mpTableState->resizeColumnToContents(4);
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

bool CQUpdatesWidget::enterProtected()
{
  loadWidget();

  return true;
}
