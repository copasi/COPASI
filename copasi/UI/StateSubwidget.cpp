// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/StateSubwidget.cpp,v $
//   $Revision: 1.17 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/12/05 20:16:26 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'StateSubwidget.ui'
 **
 ** Created: Wed Dec 5 15:07:10 2007
 **      by: The User Interface Compiler ($Id: StateSubwidget.cpp,v 1.17 2007/12/05 20:16:26 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "StateSubwidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qtextedit.h>
#include <qtable.h>
#include <qsplitter.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "CQArrayAnnotationsWidget.h"
#include "StateSubwidget.ui.h"

/*
 *  Constructs a StateSubwidget which is a child of 'parent', with the
 *  name 'name'.'
 */
StateSubwidget::StateSubwidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  if (!name)
    setName("StateSubwidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, sizePolicy().hasHeightForWidth()));
  StateSubwidgetLayout = new QVBoxLayout(this, 11, 6, "StateSubwidgetLayout");

  topLabel = new QLabel(this, "topLabel");
  StateSubwidgetLayout->addWidget(topLabel);

  mpTabWidget = new QTabWidget(this, "mpTabWidget");
  mpTabWidget->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)2, (QSizePolicy::SizeType)7, 0, 0, mpTabWidget->sizePolicy().hasHeightForWidth()));

  mpOptimizationPage = new QWidget(mpTabWidget, "mpOptimizationPage");
  mpOptimizationPageLayout = new QVBoxLayout(mpOptimizationPage, 11, 6, "mpOptimizationPageLayout");

  optimizationResultText = new QTextEdit(mpOptimizationPage, "optimizationResultText");
  optimizationResultText->setReadOnly(TRUE);
  mpOptimizationPageLayout->addWidget(optimizationResultText);
  mpTabWidget->insertTab(mpOptimizationPage, QString::fromLatin1(""));

  mpMetabolitesPage = new QWidget(mpTabWidget, "mpMetabolitesPage");
  mpMetabolitesPageLayout = new QVBoxLayout(mpMetabolitesPage, 11, 6, "mpMetabolitesPageLayout");

  mpTblMetabolites = new QTable(mpMetabolitesPage, "mpTblMetabolites");
  mpTblMetabolites->setNumCols(mpTblMetabolites->numCols() + 1);
  mpTblMetabolites->horizontalHeader()->setLabel(mpTblMetabolites->numCols() - 1, tr("Name"));
  mpTblMetabolites->setNumCols(mpTblMetabolites->numCols() + 1);
  mpTblMetabolites->horizontalHeader()->setLabel(mpTblMetabolites->numCols() - 1, tr("Type"));
  mpTblMetabolites->setNumCols(mpTblMetabolites->numCols() + 1);
  mpTblMetabolites->horizontalHeader()->setLabel(mpTblMetabolites->numCols() - 1, tr("Concentration"));
  mpTblMetabolites->setNumCols(mpTblMetabolites->numCols() + 1);
  mpTblMetabolites->horizontalHeader()->setLabel(mpTblMetabolites->numCols() - 1, tr("Rate"));
  mpTblMetabolites->setNumCols(mpTblMetabolites->numCols() + 1);
  mpTblMetabolites->horizontalHeader()->setLabel(mpTblMetabolites->numCols() - 1, tr("Transition Time"));
  mpTblMetabolites->setNumRows(0);
  mpTblMetabolites->setNumCols(5);
  mpTblMetabolites->setReadOnly(TRUE);
  mpMetabolitesPageLayout->addWidget(mpTblMetabolites);
  mpTabWidget->insertTab(mpMetabolitesPage, QString::fromLatin1(""));

  mpCompartmentsPage = new QWidget(mpTabWidget, "mpCompartmentsPage");
  mpCompartmentsPageLayout = new QVBoxLayout(mpCompartmentsPage, 11, 6, "mpCompartmentsPageLayout");

  mpTblCompartments = new QTable(mpCompartmentsPage, "mpTblCompartments");
  mpTblCompartments->setNumCols(mpTblCompartments->numCols() + 1);
  mpTblCompartments->horizontalHeader()->setLabel(mpTblCompartments->numCols() - 1, tr("Name"));
  mpTblCompartments->setNumCols(mpTblCompartments->numCols() + 1);
  mpTblCompartments->horizontalHeader()->setLabel(mpTblCompartments->numCols() - 1, tr("Type"));
  mpTblCompartments->setNumCols(mpTblCompartments->numCols() + 1);
  mpTblCompartments->horizontalHeader()->setLabel(mpTblCompartments->numCols() - 1, tr("Volume"));
  mpTblCompartments->setNumCols(mpTblCompartments->numCols() + 1);
  mpTblCompartments->horizontalHeader()->setLabel(mpTblCompartments->numCols() - 1, tr("Rate"));
  mpTblCompartments->setNumRows(0);
  mpTblCompartments->setNumCols(4);
  mpTblCompartments->setReadOnly(TRUE);
  mpCompartmentsPageLayout->addWidget(mpTblCompartments);
  mpTabWidget->insertTab(mpCompartmentsPage, QString::fromLatin1(""));

  mpModelQuantitiesPage = new QWidget(mpTabWidget, "mpModelQuantitiesPage");
  mpModelQuantitiesPageLayout = new QHBoxLayout(mpModelQuantitiesPage, 11, 6, "mpModelQuantitiesPageLayout");

  mpTblModelValues = new QTable(mpModelQuantitiesPage, "mpTblModelValues");
  mpTblModelValues->setNumCols(mpTblModelValues->numCols() + 1);
  mpTblModelValues->horizontalHeader()->setLabel(mpTblModelValues->numCols() - 1, tr("Name"));
  mpTblModelValues->setNumCols(mpTblModelValues->numCols() + 1);
  mpTblModelValues->horizontalHeader()->setLabel(mpTblModelValues->numCols() - 1, tr("Type"));
  mpTblModelValues->setNumCols(mpTblModelValues->numCols() + 1);
  mpTblModelValues->horizontalHeader()->setLabel(mpTblModelValues->numCols() - 1, tr("Value"));
  mpTblModelValues->setNumCols(mpTblModelValues->numCols() + 1);
  mpTblModelValues->horizontalHeader()->setLabel(mpTblModelValues->numCols() - 1, tr("Rate"));
  mpTblModelValues->setNumRows(0);
  mpTblModelValues->setNumCols(4);
  mpModelQuantitiesPageLayout->addWidget(mpTblModelValues);
  mpTabWidget->insertTab(mpModelQuantitiesPage, QString::fromLatin1(""));

  mpReactionsPage = new QWidget(mpTabWidget, "mpReactionsPage");
  mpReactionsPageLayout = new QVBoxLayout(mpReactionsPage, 11, 6, "mpReactionsPageLayout");

  mpTblReactions = new QTable(mpReactionsPage, "mpTblReactions");
  mpTblReactions->setNumCols(mpTblReactions->numCols() + 1);
  mpTblReactions->horizontalHeader()->setLabel(mpTblReactions->numCols() - 1, tr("Name"));
  mpTblReactions->setNumCols(mpTblReactions->numCols() + 1);
  mpTblReactions->horizontalHeader()->setLabel(mpTblReactions->numCols() - 1, tr("Flux"));
  mpTblReactions->setNumCols(mpTblReactions->numCols() + 1);
  mpTblReactions->horizontalHeader()->setLabel(mpTblReactions->numCols() - 1, tr("Chemical Equation"));
  mpTblReactions->setNumRows(0);
  mpTblReactions->setNumCols(3);
  mpTblReactions->setReadOnly(TRUE);
  mpReactionsPageLayout->addWidget(mpTblReactions);
  mpTabWidget->insertTab(mpReactionsPage, QString::fromLatin1(""));

  mpJacobianPage = new QWidget(mpTabWidget, "mpJacobianPage");
  mpJacobianPageLayout = new QGridLayout(mpJacobianPage, 1, 1, 11, 6, "mpJacobianPageLayout");

  splitter3 = new QSplitter(mpJacobianPage, "splitter3");
  splitter3->setOrientation(QSplitter::Vertical);

  QWidget* privateLayoutWidget = new QWidget(splitter3, "layoutJacobian");
  layoutJacobian = new QGridLayout(privateLayoutWidget, 1, 1, 11, 6, "layoutJacobian");
  spacer3 = new QSpacerItem(517, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutJacobian->addItem(spacer3, 0, 1);

  mpJacobianAnnotationWidget = new CQArrayAnnotationsWidget(privateLayoutWidget, "mpJacobianAnnotationWidget");

  layoutJacobian->addMultiCellWidget(mpJacobianAnnotationWidget, 1, 1, 0, 1);

  textLabelJacobian = new QLabel(privateLayoutWidget, "textLabelJacobian");

  layoutJacobian->addWidget(textLabelJacobian, 0, 0);

  QWidget* privateLayoutWidget_2 = new QWidget(splitter3, "layoutEigenvalues");
  layoutEigenvalues = new QGridLayout(privateLayoutWidget_2, 1, 1, 11, 6, "layoutEigenvalues");

  tableEigenValues = new QTable(privateLayoutWidget_2, "tableEigenValues");
  tableEigenValues->setNumCols(tableEigenValues->numCols() + 1);
  tableEigenValues->horizontalHeader()->setLabel(tableEigenValues->numCols() - 1, tr("Real"));
  tableEigenValues->setNumCols(tableEigenValues->numCols() + 1);
  tableEigenValues->horizontalHeader()->setLabel(tableEigenValues->numCols() - 1, tr("Imaginary"));
  tableEigenValues->setNumRows(0);
  tableEigenValues->setNumCols(2);
  tableEigenValues->setReadOnly(TRUE);

  layoutEigenvalues->addMultiCellWidget(tableEigenValues, 1, 1, 0, 1);
  spacer4 = new QSpacerItem(141, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutEigenvalues->addItem(spacer4, 0, 1);

  textLabelEigenvalues = new QLabel(privateLayoutWidget_2, "textLabelEigenvalues");

  layoutEigenvalues->addWidget(textLabelEigenvalues, 0, 0);

  mpJacobianPageLayout->addWidget(splitter3, 0, 0);
  mpTabWidget->insertTab(mpJacobianPage, QString::fromLatin1(""));

  mpReducedJacobianPage = new QWidget(mpTabWidget, "mpReducedJacobianPage");
  mpReducedJacobianPageLayout = new QVBoxLayout(mpReducedJacobianPage, 11, 6, "mpReducedJacobianPageLayout");

  splitter3_2 = new QSplitter(mpReducedJacobianPage, "splitter3_2");
  splitter3_2->setOrientation(QSplitter::Vertical);

  QWidget* privateLayoutWidget_3 = new QWidget(splitter3_2, "layoutJacobianX");
  layoutJacobianX = new QGridLayout(privateLayoutWidget_3, 1, 1, 11, 6, "layoutJacobianX");

  mpJacobianXAnnotationWidget = new CQArrayAnnotationsWidget(privateLayoutWidget_3, "mpJacobianXAnnotationWidget");

  layoutJacobianX->addMultiCellWidget(mpJacobianXAnnotationWidget, 1, 1, 0, 1);
  spacer3_2 = new QSpacerItem(518, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutJacobianX->addItem(spacer3_2, 0, 1);

  textLabelJacobianX = new QLabel(privateLayoutWidget_3, "textLabelJacobianX");

  layoutJacobianX->addWidget(textLabelJacobianX, 0, 0);

  QWidget* privateLayoutWidget_4 = new QWidget(splitter3_2, "layoutEigenvaluesX");
  layoutEigenvaluesX = new QGridLayout(privateLayoutWidget_4, 1, 1, 11, 6, "layoutEigenvaluesX");

  tableEigenValuesX = new QTable(privateLayoutWidget_4, "tableEigenValuesX");
  tableEigenValuesX->setNumCols(tableEigenValuesX->numCols() + 1);
  tableEigenValuesX->horizontalHeader()->setLabel(tableEigenValuesX->numCols() - 1, tr("Real"));
  tableEigenValuesX->setNumCols(tableEigenValuesX->numCols() + 1);
  tableEigenValuesX->horizontalHeader()->setLabel(tableEigenValuesX->numCols() - 1, tr("Imaginary"));
  tableEigenValuesX->setNumRows(0);
  tableEigenValuesX->setNumCols(2);
  tableEigenValuesX->setReadOnly(TRUE);

  layoutEigenvaluesX->addMultiCellWidget(tableEigenValuesX, 1, 1, 0, 1);
  spacer4_2 = new QSpacerItem(141, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutEigenvaluesX->addItem(spacer4_2, 0, 1);

  textLabelEigenvaluesX = new QLabel(privateLayoutWidget_4, "textLabelEigenvaluesX");

  layoutEigenvaluesX->addWidget(textLabelEigenvaluesX, 0, 0);
  mpReducedJacobianPageLayout->addWidget(splitter3_2);
  mpTabWidget->insertTab(mpReducedJacobianPage, QString::fromLatin1(""));

  mpStabilityPage = new QWidget(mpTabWidget, "mpStabilityPage");
  mpStabilityPageLayout = new QVBoxLayout(mpStabilityPage, 11, 6, "mpStabilityPageLayout");

  stabilityTextEdit = new QTextEdit(mpStabilityPage, "stabilityTextEdit");
  stabilityTextEdit->setReadOnly(TRUE);
  mpStabilityPageLayout->addWidget(stabilityTextEdit);
  mpTabWidget->insertTab(mpStabilityPage, QString::fromLatin1(""));

  mpProtocolPage = new QWidget(mpTabWidget, "mpProtocolPage");
  mpProtocolPageLayout = new QGridLayout(mpProtocolPage, 1, 1, 11, 6, "mpProtocolPageLayout");

  protocolTextEdit = new QTextEdit(mpProtocolPage, "protocolTextEdit");
  protocolTextEdit->setReadOnly(TRUE);
  protocolTextEdit->setUndoRedoEnabled(FALSE);
  protocolTextEdit->setAutoFormatting(int(QTextEdit::AutoAll));

  mpProtocolPageLayout->addWidget(protocolTextEdit, 0, 0);
  mpTabWidget->insertTab(mpProtocolPage, QString::fromLatin1(""));
  StateSubwidgetLayout->addWidget(mpTabWidget);
  languageChange();
  resize(QSize(733, 629).expandedTo(minimumSizeHint()));
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
  mpTabWidget->changeTab(mpOptimizationPage, tr("Optimization Result"));
  mpTblMetabolites->horizontalHeader()->setLabel(0, tr("Name"));
  mpTblMetabolites->horizontalHeader()->setLabel(1, tr("Type"));
  mpTblMetabolites->horizontalHeader()->setLabel(2, tr("Concentration"));
  mpTblMetabolites->horizontalHeader()->setLabel(3, tr("Rate"));
  mpTblMetabolites->horizontalHeader()->setLabel(4, tr("Transition Time"));
  mpTabWidget->changeTab(mpMetabolitesPage, tr("Metabolites"));
  mpTblCompartments->horizontalHeader()->setLabel(0, tr("Name"));
  mpTblCompartments->horizontalHeader()->setLabel(1, tr("Type"));
  mpTblCompartments->horizontalHeader()->setLabel(2, tr("Volume"));
  mpTblCompartments->horizontalHeader()->setLabel(3, tr("Rate"));
  mpTabWidget->changeTab(mpCompartmentsPage, tr("Compartments"));
  mpTblModelValues->horizontalHeader()->setLabel(0, tr("Name"));
  mpTblModelValues->horizontalHeader()->setLabel(1, tr("Type"));
  mpTblModelValues->horizontalHeader()->setLabel(2, tr("Value"));
  mpTblModelValues->horizontalHeader()->setLabel(3, tr("Rate"));
  mpTabWidget->changeTab(mpModelQuantitiesPage, tr("Model Quantities"));
  mpTblReactions->horizontalHeader()->setLabel(0, tr("Name"));
  mpTblReactions->horizontalHeader()->setLabel(1, tr("Flux"));
  mpTblReactions->horizontalHeader()->setLabel(2, tr("Chemical Equation"));
  mpTabWidget->changeTab(mpReactionsPage, tr("Reactions"));
  textLabelJacobian->setText(tr("Jacobian (complete system)"));
  tableEigenValues->horizontalHeader()->setLabel(0, tr("Real"));
  tableEigenValues->horizontalHeader()->setLabel(1, tr("Imaginary"));
  textLabelEigenvalues->setText(tr("Eigenvalues (complete system)"));
  mpTabWidget->changeTab(mpJacobianPage, tr("Jacobian"));
  textLabelJacobianX->setText(tr("Jacobian (Reduced System)"));
  tableEigenValuesX->horizontalHeader()->setLabel(0, tr("Real"));
  tableEigenValuesX->horizontalHeader()->setLabel(1, tr("Imaginary"));
  textLabelEigenvaluesX->setText(tr("Eigenvalues (Reduced System)"));
  mpTabWidget->changeTab(mpReducedJacobianPage, tr("Jacobian (Reduced System)"));
  mpTabWidget->changeTab(mpStabilityPage, tr("Stability"));
  mpTabWidget->changeTab(mpProtocolPage, tr("Protocol"));
}
