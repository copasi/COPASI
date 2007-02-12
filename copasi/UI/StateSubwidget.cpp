// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/StateSubwidget.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/12 14:29:14 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'StateSubwidget.ui'
 **
 ** Created: Do Feb 8 15:27:06 2007
 **      by: The User Interface Compiler ($Id: StateSubwidget.cpp,v 1.13 2007/02/12 14:29:14 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "StateSubwidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtabwidget.h>
#include <qtextedit.h>
#include <qtable.h>
#include <qsplitter.h>
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
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, sizePolicy().hasHeightForWidth()));
  StateSubwidgetLayout = new QVBoxLayout(this, 11, 6, "StateSubwidgetLayout");

  topLabel = new QLabel(this, "topLabel");
  StateSubwidgetLayout->addWidget(topLabel);

  tabWidget = new QTabWidget(this, "tabWidget");

  TabPage = new QWidget(tabWidget, "TabPage");
  TabPageLayout = new QVBoxLayout(TabPage, 11, 6, "TabPageLayout");

  optimizationResultText = new QTextEdit(TabPage, "optimizationResultText");
  optimizationResultText->setReadOnly(TRUE);
  TabPageLayout->addWidget(optimizationResultText);
  tabWidget->insertTab(TabPage, QString::fromLatin1(""));

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
  concentrationsTable->setReadOnly(TRUE);
  tabLayout->addWidget(concentrationsTable);
  tabWidget->insertTab(tab, QString::fromLatin1(""));

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
  numbersTable->setReadOnly(TRUE);
  tabLayout_2->addWidget(numbersTable);
  tabWidget->insertTab(tab_2, QString::fromLatin1(""));

  TabPage_2 = new QWidget(tabWidget, "TabPage_2");
  TabPageLayout_2 = new QHBoxLayout(TabPage_2, 11, 6, "TabPageLayout_2");

  mpModelValueTable = new QTable(TabPage_2, "mpModelValueTable");
  mpModelValueTable->setNumCols(mpModelValueTable->numCols() + 1);
  mpModelValueTable->horizontalHeader()->setLabel(mpModelValueTable->numCols() - 1, tr("Name"));
  mpModelValueTable->setNumCols(mpModelValueTable->numCols() + 1);
  mpModelValueTable->horizontalHeader()->setLabel(mpModelValueTable->numCols() - 1, tr("Type"));
  mpModelValueTable->setNumCols(mpModelValueTable->numCols() + 1);
  mpModelValueTable->horizontalHeader()->setLabel(mpModelValueTable->numCols() - 1, tr("Value"));
  mpModelValueTable->setNumCols(mpModelValueTable->numCols() + 1);
  mpModelValueTable->horizontalHeader()->setLabel(mpModelValueTable->numCols() - 1, tr("Rate"));
  mpModelValueTable->setNumRows(3);
  mpModelValueTable->setNumCols(4);
  TabPageLayout_2->addWidget(mpModelValueTable);
  tabWidget->insertTab(TabPage_2, QString::fromLatin1(""));

  TabPage_3 = new QWidget(tabWidget, "TabPage_3");
  TabPageLayout_3 = new QVBoxLayout(TabPage_3, 11, 6, "TabPageLayout_3");

  tableFlux = new QTable(TabPage_3, "tableFlux");
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
  tableFlux->setReadOnly(TRUE);
  TabPageLayout_3->addWidget(tableFlux);
  tabWidget->insertTab(TabPage_3, QString::fromLatin1(""));

  TabPage_4 = new QWidget(tabWidget, "TabPage_4");
  TabPageLayout_4 = new QVBoxLayout(TabPage_4, 11, 6, "TabPageLayout_4");

  splitterJacobian = new QSplitter(TabPage_4, "splitterJacobian");
  splitterJacobian->setOrientation(QSplitter::Vertical);
  splitterJacobian->setOpaqueResize(TRUE);

  QWidget* privateLayoutWidget = new QWidget(splitterJacobian, "layoutJacobian");
  layoutJacobian = new QGridLayout(privateLayoutWidget, 1, 1, 11, 6, "layoutJacobian");

  tableJacobian = new QTable(privateLayoutWidget, "tableJacobian");
  tableJacobian->setNumRows(3);
  tableJacobian->setNumCols(3);
  tableJacobian->setReadOnly(TRUE);

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
  tableEigenValues->setReadOnly(TRUE);

  layoutEigenvalues->addMultiCellWidget(tableEigenValues, 1, 1, 0, 1);
  spacer4 = new QSpacerItem(141, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutEigenvalues->addItem(spacer4, 0, 1);

  textLabelEigenvalues = new QLabel(privateLayoutWidget_2, "textLabelEigenvalues");

  layoutEigenvalues->addWidget(textLabelEigenvalues, 0, 0);
  TabPageLayout_4->addWidget(splitterJacobian);
  tabWidget->insertTab(TabPage_4, QString::fromLatin1(""));

  TabPage_5 = new QWidget(tabWidget, "TabPage_5");
  TabPageLayout_5 = new QVBoxLayout(TabPage_5, 11, 6, "TabPageLayout_5");

  splitterJacobianX = new QSplitter(TabPage_5, "splitterJacobianX");
  splitterJacobianX->setOrientation(QSplitter::Vertical);
  splitterJacobianX->setOpaqueResize(TRUE);

  QWidget* privateLayoutWidget_3 = new QWidget(splitterJacobianX, "layoutJacobianX");
  layoutJacobianX = new QGridLayout(privateLayoutWidget_3, 1, 1, 11, 6, "layoutJacobianX");

  tableJacobianX = new QTable(privateLayoutWidget_3, "tableJacobianX");
  tableJacobianX->setNumRows(3);
  tableJacobianX->setNumCols(3);
  tableJacobianX->setReadOnly(TRUE);

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
  tableEigenValuesX->setReadOnly(TRUE);

  layoutEigenvaluesX->addMultiCellWidget(tableEigenValuesX, 1, 1, 0, 1);
  spacer4_2 = new QSpacerItem(141, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutEigenvaluesX->addItem(spacer4_2, 0, 1);

  textLabelEigenvaluesX = new QLabel(privateLayoutWidget_4, "textLabelEigenvaluesX");

  layoutEigenvaluesX->addWidget(textLabelEigenvaluesX, 0, 0);
  TabPageLayout_5->addWidget(splitterJacobianX);
  tabWidget->insertTab(TabPage_5, QString::fromLatin1(""));

  TabPage_6 = new QWidget(tabWidget, "TabPage_6");
  TabPageLayout_6 = new QVBoxLayout(TabPage_6, 11, 6, "TabPageLayout_6");

  stabilityTextEdit = new QTextEdit(TabPage_6, "stabilityTextEdit");
  stabilityTextEdit->setReadOnly(TRUE);
  TabPageLayout_6->addWidget(stabilityTextEdit);
  tabWidget->insertTab(TabPage_6, QString::fromLatin1(""));

  TabPage_7 = new QWidget(tabWidget, "TabPage_7");
  TabPageLayout_7 = new QGridLayout(TabPage_7, 1, 1, 11, 6, "TabPageLayout_7");

  protocolTextEdit = new QTextEdit(TabPage_7, "protocolTextEdit");
  protocolTextEdit->setReadOnly(TRUE);
  protocolTextEdit->setUndoRedoEnabled(FALSE);
  protocolTextEdit->setAutoFormatting(int(QTextEdit::AutoAll));

  TabPageLayout_7->addWidget(protocolTextEdit, 0, 0);
  tabWidget->insertTab(TabPage_7, QString::fromLatin1(""));
  StateSubwidgetLayout->addWidget(tabWidget);
  languageChange();
  resize(QSize(600, 497).expandedTo(minimumSizeHint()));
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
  tabWidget->changeTab(TabPage, tr("Optimization Result"));
  concentrationsTable->horizontalHeader()->setLabel(0, tr("Metabolite name"));
  concentrationsTable->horizontalHeader()->setLabel(1, tr("Concentration"));
  concentrationsTable->horizontalHeader()->setLabel(2, tr("Rate"));
  concentrationsTable->horizontalHeader()->setLabel(3, tr("Transition Time"));
  tabWidget->changeTab(tab, tr("Concentrations"));
  numbersTable->horizontalHeader()->setLabel(0, tr("Metabolite name"));
  numbersTable->horizontalHeader()->setLabel(1, tr("Numbers"));
  numbersTable->horizontalHeader()->setLabel(2, tr("Number rate"));
  numbersTable->horizontalHeader()->setLabel(3, tr("Transition Time"));
  tabWidget->changeTab(tab_2, tr("Particle Numbers"));
  mpModelValueTable->horizontalHeader()->setLabel(0, tr("Name"));
  mpModelValueTable->horizontalHeader()->setLabel(1, tr("Type"));
  mpModelValueTable->horizontalHeader()->setLabel(2, tr("Value"));
  mpModelValueTable->horizontalHeader()->setLabel(3, tr("Rate"));
  tabWidget->changeTab(TabPage_2, tr("Model Quantities"));
  tableFlux->horizontalHeader()->setLabel(0, tr("Reaction name"));
  tableFlux->horizontalHeader()->setLabel(1, tr("Flux"));
  tableFlux->horizontalHeader()->setLabel(2, tr("Particle flux"));
  tableFlux->horizontalHeader()->setLabel(3, tr("Chemical equation"));
  tabWidget->changeTab(TabPage_3, tr("Fluxes"));
  textLabelJacobian->setText(tr("Jacobian (complete system)"));
  tableEigenValues->horizontalHeader()->setLabel(0, tr("Real"));
  tableEigenValues->horizontalHeader()->setLabel(1, tr("Imaginary"));
  textLabelEigenvalues->setText(tr("Eigenvalues (complete system)"));
  tabWidget->changeTab(TabPage_4, tr("Jacobian"));
  textLabelJacobianX->setText(tr("Jacobian (Reduced System)"));
  tableEigenValuesX->horizontalHeader()->setLabel(0, tr("Real"));
  tableEigenValuesX->horizontalHeader()->setLabel(1, tr("Imaginary"));
  textLabelEigenvaluesX->setText(tr("Eigenvalues (Reduced System)"));
  tabWidget->changeTab(TabPage_5, tr("Jacobian (Reduced System)"));
  tabWidget->changeTab(TabPage_6, tr("Stability"));
  tabWidget->changeTab(TabPage_7, tr("Protocol"));
}
