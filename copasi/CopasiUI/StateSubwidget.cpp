/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/StateSubwidget.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:51 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'StateSubwidget.ui'
 **
 ** Created: Sat Oct 9 15:44:20 2004
 **      by: The User Interface Compiler ($Id: StateSubwidget.cpp,v 1.1.1.1 2004/10/26 15:17:51 anuragr Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "StateSubwidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtabwidget.h>
#include <qtable.h>
#include <qsplitter.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "model/CModel.h"
#include "model/CMetabNameInterface.h"
#include "steadystate/CSteadyStateTask.h"
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

  topLabel = new QLabel(this, "topLabel");
  StateSubwidgetLayout->addWidget(topLabel);

  tabWidget = new QTabWidget(this, "tabWidget");

  tab = new QWidget(tabWidget, "tab");
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
  tabWidget->insertTab(tab, QString(""));

  tab_2 = new QWidget(tabWidget, "tab_2");
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
  tabWidget->insertTab(tab_2, QString(""));

  TabPage = new QWidget(tabWidget, "TabPage");
  TabPageLayout = new QVBoxLayout(TabPage, 11, 6, "TabPageLayout");

  tableFlux = new QTable(TabPage, "tableFlux");
  tableFlux->setNumCols(tableFlux->numCols() + 1);
  tableFlux->horizontalHeader()->setLabel(tableFlux->numCols() - 1, tr("Reaction name"));
  tableFlux->setNumCols(tableFlux->numCols() + 1);
  tableFlux->horizontalHeader()->setLabel(tableFlux->numCols() - 1, tr("Flux"));
  tableFlux->setNumCols(tableFlux->numCols() + 1);
  tableFlux->horizontalHeader()->setLabel(tableFlux->numCols() - 1, tr("Particle flux"));
  tableFlux->setNumCols(tableFlux->numCols() + 1);
  tableFlux->horizontalHeader()->setLabel(tableFlux->numCols() - 1, tr("Chemical equation"));
  tableFlux->setNumRows(3);
  tableFlux->setNumCols(4);
  TabPageLayout->addWidget(tableFlux);
  tabWidget->insertTab(TabPage, QString(""));

  TabPage_2 = new QWidget(tabWidget, "TabPage_2");
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
  tableEigenValues->setNumCols(tableEigenValues->numCols() + 1);
  tableEigenValues->horizontalHeader()->setLabel(tableEigenValues->numCols() - 1, tr("Real"));
  tableEigenValues->setNumCols(tableEigenValues->numCols() + 1);
  tableEigenValues->horizontalHeader()->setLabel(tableEigenValues->numCols() - 1, tr("Imaginary"));
  tableEigenValues->setNumRows(3);
  tableEigenValues->setNumCols(2);

  layoutEigenvalues->addMultiCellWidget(tableEigenValues, 1, 1, 0, 1);
  spacer4 = new QSpacerItem(141, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutEigenvalues->addItem(spacer4, 0, 1);

  textLabelEigenvalues = new QLabel(privateLayoutWidget_2, "textLabelEigenvalues");

  layoutEigenvalues->addWidget(textLabelEigenvalues, 0, 0);
  TabPageLayout_2->addWidget(splitterJacobian);
  tabWidget->insertTab(TabPage_2, QString(""));

  TabPage_3 = new QWidget(tabWidget, "TabPage_3");
  TabPageLayout_3 = new QVBoxLayout(TabPage_3, 11, 6, "TabPageLayout_3");

  splitterJacobianX = new QSplitter(TabPage_3, "splitterJacobianX");
  splitterJacobianX->setOrientation(QSplitter::Vertical);
  splitterJacobianX->setOpaqueResize(TRUE);

  QWidget* privateLayoutWidget_3 = new QWidget(splitterJacobianX, "layoutJacobianX");
  layoutJacobianX = new QGridLayout(privateLayoutWidget_3, 1, 1, 11, 6, "layoutJacobianX");

  tableJacobianX = new QTable(privateLayoutWidget_3, "tableJacobianX");
  tableJacobianX->setNumRows(3);
  tableJacobianX->setNumCols(3);

  layoutJacobianX->addMultiCellWidget(tableJacobianX, 1, 1, 0, 1);

  textLabelJacobianX = new QLabel(privateLayoutWidget_3, "textLabelJacobianX");

  layoutJacobianX->addWidget(textLabelJacobianX, 0, 0);
  spacer3_2 = new QSpacerItem(191, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutJacobianX->addItem(spacer3_2, 0, 1);

  QWidget* privateLayoutWidget_4 = new QWidget(splitterJacobianX, "layoutEigenvaluesX");
  layoutEigenvaluesX = new QGridLayout(privateLayoutWidget_4, 1, 1, 11, 6, "layoutEigenvaluesX");

  tableEigenValuesX = new QTable(privateLayoutWidget_4, "tableEigenValuesX");
  tableEigenValuesX->setNumCols(tableEigenValuesX->numCols() + 1);
  tableEigenValuesX->horizontalHeader()->setLabel(tableEigenValuesX->numCols() - 1, tr("Real"));
  tableEigenValuesX->setNumCols(tableEigenValuesX->numCols() + 1);
  tableEigenValuesX->horizontalHeader()->setLabel(tableEigenValuesX->numCols() - 1, tr("Imaginary"));
  tableEigenValuesX->setNumRows(3);
  tableEigenValuesX->setNumCols(2);

  layoutEigenvaluesX->addMultiCellWidget(tableEigenValuesX, 1, 1, 0, 1);
  spacer4_2 = new QSpacerItem(141, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutEigenvaluesX->addItem(spacer4_2, 0, 1);

  textLabelEigenvaluesX = new QLabel(privateLayoutWidget_4, "textLabelEigenvaluesX");

  layoutEigenvaluesX->addWidget(textLabelEigenvaluesX, 0, 0);
  TabPageLayout_3->addWidget(splitterJacobianX);
  tabWidget->insertTab(TabPage_3, QString(""));

  TabPage_4 = new QWidget(tabWidget, "TabPage_4");
  TabPageLayout_4 = new QVBoxLayout(TabPage_4, 11, 6, "TabPageLayout_4");

  stabilityTextEdit = new QTextEdit(TabPage_4, "stabilityTextEdit");
  TabPageLayout_4->addWidget(stabilityTextEdit);
  tabWidget->insertTab(TabPage_4, QString(""));
  StateSubwidgetLayout->addWidget(tabWidget);
  languageChange();
  resize(QSize(551, 422).expandedTo(minimumSizeHint()));
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
  topLabel->setText(tr("textLabel1"));
  concentrationsTable->horizontalHeader()->setLabel(0, tr("Metabolite name"));
  concentrationsTable->horizontalHeader()->setLabel(1, tr("Concentration"));
  concentrationsTable->horizontalHeader()->setLabel(2, tr("Rate"));
  concentrationsTable->horizontalHeader()->setLabel(3, tr("Transition Time"));
  tabWidget->changeTab(tab, tr("Concentrations"));
  numbersTable->horizontalHeader()->setLabel(0, tr("Metabolite name"));
  numbersTable->horizontalHeader()->setLabel(1, tr("Numbers"));
  numbersTable->horizontalHeader()->setLabel(2, tr("Number rate"));
  numbersTable->horizontalHeader()->setLabel(3, tr("Transition Time"));
  tabWidget->changeTab(tab_2, tr("Particle numbers"));
  tableFlux->horizontalHeader()->setLabel(0, tr("Reaction name"));
  tableFlux->horizontalHeader()->setLabel(1, tr("Flux"));
  tableFlux->horizontalHeader()->setLabel(2, tr("Particle flux"));
  tableFlux->horizontalHeader()->setLabel(3, tr("Chemical equation"));
  tabWidget->changeTab(TabPage, tr("Fluxes"));
  textLabelJacobian->setText(tr("Jacobian (complete system)"));
  tableEigenValues->horizontalHeader()->setLabel(0, tr("Real"));
  tableEigenValues->horizontalHeader()->setLabel(1, tr("Imaginary"));
  textLabelEigenvalues->setText(tr("Eigenvalues (complete system)"));
  tabWidget->changeTab(TabPage_2, tr("Jacobian"));
  textLabelJacobianX->setText(tr("Jacobian (reduced system)"));
  tableEigenValuesX->horizontalHeader()->setLabel(0, tr("Real"));
  tableEigenValuesX->horizontalHeader()->setLabel(1, tr("Imaginary"));
  textLabelEigenvaluesX->setText(tr("Eigenvalues (reduced system)"));
  tabWidget->changeTab(TabPage_3, tr("Jacobian (reduced system)"));
  tabWidget->changeTab(TabPage_4, tr("Stability"));
}
