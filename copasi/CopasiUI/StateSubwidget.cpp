/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/StateSubwidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/30 10:03:26 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'StateSubwidget.ui'
 **
 ** Created: Thu Sep 30 11:21:05 2004
 **      by: The User Interface Compiler ($Id: StateSubwidget.cpp,v 1.1 2004/09/30 10:03:26 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "StateSubwidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qtable.h>
#include <qsplitter.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "StateSubwidget.ui.h"

/*
 *  Constructs a StateSubwidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
StateSubwidget::StateSubwidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("StateSubwidget");
  StateSubwidgetLayout = new QVBoxLayout(this, 11, 6, "StateSubwidgetLayout");

  tabWidget2 = new QTabWidget(this, "tabWidget2");

  tab = new QWidget(tabWidget2, "tab");
  tabLayout = new QVBoxLayout(tab, 11, 6, "tabLayout");

  concentrationsTable = new QTable(tab, "concentrationsTable");
  concentrationsTable->setNumCols(concentrationsTable->numCols() + 1);
  concentrationsTable->horizontalHeader()->setLabel(concentrationsTable->numCols() - 1, tr("Metabolite name"));
  concentrationsTable->setNumCols(concentrationsTable->numCols() + 1);
  concentrationsTable->horizontalHeader()->setLabel(concentrationsTable->numCols() - 1, tr("Concentration"));
  concentrationsTable->setNumCols(concentrationsTable->numCols() + 1);
  concentrationsTable->horizontalHeader()->setLabel(concentrationsTable->numCols() - 1, tr("Rate"));
  concentrationsTable->setNumCols(concentrationsTable->numCols() + 1);
  concentrationsTable->horizontalHeader()->setLabel(concentrationsTable->numCols() - 1, tr("Transition Time"));
  concentrationsTable->setNumRows(3);
  concentrationsTable->setNumCols(4);
  tabLayout->addWidget(concentrationsTable);
  tabWidget2->insertTab(tab, QString(""));

  tab_2 = new QWidget(tabWidget2, "tab_2");
  tabLayout_2 = new QVBoxLayout(tab_2, 11, 6, "tabLayout_2");

  numbersTable = new QTable(tab_2, "numbersTable");
  numbersTable->setNumCols(numbersTable->numCols() + 1);
  numbersTable->horizontalHeader()->setLabel(numbersTable->numCols() - 1, tr("Metabolite name"));
  numbersTable->setNumCols(numbersTable->numCols() + 1);
  numbersTable->horizontalHeader()->setLabel(numbersTable->numCols() - 1, tr("Numbers"));
  numbersTable->setNumCols(numbersTable->numCols() + 1);
  numbersTable->horizontalHeader()->setLabel(numbersTable->numCols() - 1, tr("Number rate"));
  numbersTable->setNumCols(numbersTable->numCols() + 1);
  numbersTable->horizontalHeader()->setLabel(numbersTable->numCols() - 1, tr("Transition Time"));
  numbersTable->setNumRows(3);
  numbersTable->setNumCols(4);
  tabLayout_2->addWidget(numbersTable);
  tabWidget2->insertTab(tab_2, QString(""));

  TabPage = new QWidget(tabWidget2, "TabPage");
  TabPageLayout = new QVBoxLayout(TabPage, 11, 6, "TabPageLayout");

  tableFlux = new QTable(TabPage, "tableFlux");
  tableFlux->setNumCols(tableFlux->numCols() + 1);
  tableFlux->horizontalHeader()->setLabel(tableFlux->numCols() - 1, tr("Reaction name"));
  tableFlux->setNumCols(tableFlux->numCols() + 1);
  tableFlux->horizontalHeader()->setLabel(tableFlux->numCols() - 1, tr("Flux"));
  tableFlux->setNumCols(tableFlux->numCols() + 1);
  tableFlux->horizontalHeader()->setLabel(tableFlux->numCols() - 1, tr("Particle flux"));
  tableFlux->setNumRows(3);
  tableFlux->setNumCols(3);
  TabPageLayout->addWidget(tableFlux);
  tabWidget2->insertTab(TabPage, QString(""));

  TabPage_2 = new QWidget(tabWidget2, "TabPage_2");
  TabPageLayout_2 = new QVBoxLayout(TabPage_2, 11, 6, "TabPageLayout_2");

  splitterJacobian = new QSplitter(TabPage_2, "splitterJacobian");
  splitterJacobian->setOrientation(QSplitter::Vertical);
  splitterJacobian->setOpaqueResize(TRUE);

  QWidget* privateLayoutWidget = new QWidget(splitterJacobian, "layoutJacobian");
  layoutJacobian = new QGridLayout(privateLayoutWidget, 1, 1, 11, 6, "layoutJacobian");

  tableJacobian = new QTable(privateLayoutWidget, "tableJacobian");
  tableJacobian->setNumRows(3);
  tableJacobian->setNumCols(3);

  layoutJacobian->addMultiCellWidget(tableJacobian, 1, 1, 0, 1);

  textLabelJacobian = new QLabel(privateLayoutWidget, "textLabelJacobian");

  layoutJacobian->addWidget(textLabelJacobian, 0, 0);
  spacer3 = new QSpacerItem(191, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutJacobian->addItem(spacer3, 0, 1);

  QWidget* privateLayoutWidget_2 = new QWidget(splitterJacobian, "layoutEigenvalues");
  layoutEigenvalues = new QGridLayout(privateLayoutWidget_2, 1, 1, 11, 6, "layoutEigenvalues");

  tableEigenValues = new QTable(privateLayoutWidget_2, "tableEigenValues");
  tableEigenValues->setNumRows(3);
  tableEigenValues->setNumCols(3);

  layoutEigenvalues->addMultiCellWidget(tableEigenValues, 1, 1, 0, 1);
  spacer4 = new QSpacerItem(141, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutEigenvalues->addItem(spacer4, 0, 1);

  textLabelEigenvalues = new QLabel(privateLayoutWidget_2, "textLabelEigenvalues");

  layoutEigenvalues->addWidget(textLabelEigenvalues, 0, 0);
  TabPageLayout_2->addWidget(splitterJacobian);
  tabWidget2->insertTab(TabPage_2, QString(""));
  StateSubwidgetLayout->addWidget(tabWidget2);
  languageChange();
  resize(QSize(503, 611).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
StateSubwidget::~StateSubwidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void StateSubwidget::languageChange()
{
  setCaption(tr("Form1"));
  concentrationsTable->horizontalHeader()->setLabel(0, tr("Metabolite name"));
  concentrationsTable->horizontalHeader()->setLabel(1, tr("Concentration"));
  concentrationsTable->horizontalHeader()->setLabel(2, tr("Rate"));
  concentrationsTable->horizontalHeader()->setLabel(3, tr("Transition Time"));
  tabWidget2->changeTab(tab, tr("Concentrations"));
  numbersTable->horizontalHeader()->setLabel(0, tr("Metabolite name"));
  numbersTable->horizontalHeader()->setLabel(1, tr("Numbers"));
  numbersTable->horizontalHeader()->setLabel(2, tr("Number rate"));
  numbersTable->horizontalHeader()->setLabel(3, tr("Transition Time"));
  tabWidget2->changeTab(tab_2, tr("Particle numbers"));
  tableFlux->horizontalHeader()->setLabel(0, tr("Reaction name"));
  tableFlux->horizontalHeader()->setLabel(1, tr("Flux"));
  tableFlux->horizontalHeader()->setLabel(2, tr("Particle flux"));
  tabWidget2->changeTab(TabPage, tr("Fluxes"));
  textLabelJacobian->setText(tr("Jacobian"));
  textLabelEigenvalues->setText(tr("Eigenvalues"));
  tabWidget2->changeTab(TabPage_2, tr("Jacobian"));
}
