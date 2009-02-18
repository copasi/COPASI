// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/StateSubwidget.h,v $
//   $Revision: 1.21 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:49:08 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef STATESUBWIDGET_H
#define STATESUBWIDGET_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3GridLayout>
#include <Q3Frame>
#include <QPixmap>
#include <QLabel>
#include <Q3VBoxLayout>

class CModel;
class CSteadyStateTask;

#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3Table>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <Qt3Support/Q3VBoxLayout>
#include <QtGui/QWidget>
#include "CQArrayAnnotationsWidget.h"
#include "copasiWidget.h"

#include "UI/listviews.h"

class Ui_StateSubwidget
  {
  public:
    Q3VBoxLayout *vboxLayout;
    QLabel *topLabel;
    QTabWidget *mpTabWidget;
    QWidget *mpOptimizationPage;
    Q3VBoxLayout *vboxLayout1;
    Q3TextEdit *optimizationResultText;
    QWidget *mpMetabolitesPage;
    Q3VBoxLayout *vboxLayout2;
    Q3Table *mpTblMetabolites;
    QWidget *mpCompartmentsPage;
    Q3VBoxLayout *vboxLayout3;
    Q3Table *mpTblCompartments;
    QWidget *mpModelQuantitiesPage;
    Q3HBoxLayout *hboxLayout;
    Q3Table *mpTblModelValues;
    QWidget *mpReactionsPage;
    Q3VBoxLayout *vboxLayout4;
    Q3Table *mpTblReactions;
    QWidget *mpJacobianPage;
    Q3VBoxLayout *vboxLayout5;
    Q3GridLayout *gridLayout;
    QSpacerItem *spacer3;
    CQArrayAnnotationsWidget *mpJacobianAnnotationWidget;
    QLabel *textLabelJacobian;
    Q3Frame *line1;
    Q3GridLayout *gridLayout1;
    Q3Table *tableEigenValues;
    QSpacerItem *spacer4;
    QLabel *textLabelEigenvalues;
    QWidget *mpReducedJacobianPage;
    Q3VBoxLayout *vboxLayout6;
    Q3GridLayout *gridLayout2;
    CQArrayAnnotationsWidget *mpJacobianXAnnotationWidget;
    QSpacerItem *spacer3_2;
    QLabel *textLabelJacobianX;
    Q3Frame *line2;
    Q3GridLayout *gridLayout3;
    Q3Table *tableEigenValuesX;
    QSpacerItem *spacer4_2;
    QLabel *textLabelEigenvaluesX;
    QWidget *mpStabilityPage;
    Q3VBoxLayout *vboxLayout7;
    Q3TextEdit *stabilityTextEdit;
    QWidget *mpProtocolPage;
    Q3GridLayout *gridLayout4;
    Q3TextEdit *protocolTextEdit;

    void setupUi(CopasiWidget *StateSubwidget)
    {
      if (StateSubwidget->objectName().isEmpty())
        StateSubwidget->setObjectName(QString::fromUtf8("StateSubwidget"));
      StateSubwidget->resize(733, 625);
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(7));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(StateSubwidget->sizePolicy().hasHeightForWidth());
      StateSubwidget->setSizePolicy(sizePolicy);
      vboxLayout = new Q3VBoxLayout(StateSubwidget);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      topLabel = new QLabel(StateSubwidget);
      topLabel->setObjectName(QString::fromUtf8("topLabel"));
      topLabel->setWordWrap(false);

      vboxLayout->addWidget(topLabel);

      mpTabWidget = new QTabWidget(StateSubwidget);
      mpTabWidget->setObjectName(QString::fromUtf8("mpTabWidget"));
      QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(2), static_cast<QSizePolicy::Policy>(7));
      sizePolicy1.setHorizontalStretch(0);
      sizePolicy1.setVerticalStretch(0);
      sizePolicy1.setHeightForWidth(mpTabWidget->sizePolicy().hasHeightForWidth());
      mpTabWidget->setSizePolicy(sizePolicy1);
      mpOptimizationPage = new QWidget();
      mpOptimizationPage->setObjectName(QString::fromUtf8("mpOptimizationPage"));
      vboxLayout1 = new Q3VBoxLayout(mpOptimizationPage);
      vboxLayout1->setSpacing(6);
      vboxLayout1->setMargin(11);
      vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
      optimizationResultText = new Q3TextEdit(mpOptimizationPage);
      optimizationResultText->setObjectName(QString::fromUtf8("optimizationResultText"));
      optimizationResultText->setReadOnly(true);

      vboxLayout1->addWidget(optimizationResultText);

      mpTabWidget->addTab(mpOptimizationPage, QString());
      mpMetabolitesPage = new QWidget();
      mpMetabolitesPage->setObjectName(QString::fromUtf8("mpMetabolitesPage"));
      vboxLayout2 = new Q3VBoxLayout(mpMetabolitesPage);
      vboxLayout2->setSpacing(6);
      vboxLayout2->setMargin(11);
      vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
      mpTblMetabolites = new Q3Table(mpMetabolitesPage);
      mpTblMetabolites->setObjectName(QString::fromUtf8("mpTblMetabolites"));
      mpTblMetabolites->setNumRows(0);
      mpTblMetabolites->setNumCols(5);
      mpTblMetabolites->setReadOnly(true);

      vboxLayout2->addWidget(mpTblMetabolites);

      mpTabWidget->addTab(mpMetabolitesPage, QString());
      mpCompartmentsPage = new QWidget();
      mpCompartmentsPage->setObjectName(QString::fromUtf8("mpCompartmentsPage"));
      vboxLayout3 = new Q3VBoxLayout(mpCompartmentsPage);
      vboxLayout3->setSpacing(6);
      vboxLayout3->setMargin(11);
      vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
      mpTblCompartments = new Q3Table(mpCompartmentsPage);
      mpTblCompartments->setObjectName(QString::fromUtf8("mpTblCompartments"));
      mpTblCompartments->setNumRows(0);
      mpTblCompartments->setNumCols(4);
      mpTblCompartments->setReadOnly(true);

      vboxLayout3->addWidget(mpTblCompartments);

      mpTabWidget->addTab(mpCompartmentsPage, QString());
      mpModelQuantitiesPage = new QWidget();
      mpModelQuantitiesPage->setObjectName(QString::fromUtf8("mpModelQuantitiesPage"));
      hboxLayout = new Q3HBoxLayout(mpModelQuantitiesPage);
      hboxLayout->setSpacing(6);
      hboxLayout->setMargin(11);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpTblModelValues = new Q3Table(mpModelQuantitiesPage);
      mpTblModelValues->setObjectName(QString::fromUtf8("mpTblModelValues"));
      mpTblModelValues->setNumRows(0);
      mpTblModelValues->setNumCols(4);

      hboxLayout->addWidget(mpTblModelValues);

      mpTabWidget->addTab(mpModelQuantitiesPage, QString());
      mpReactionsPage = new QWidget();
      mpReactionsPage->setObjectName(QString::fromUtf8("mpReactionsPage"));
      vboxLayout4 = new Q3VBoxLayout(mpReactionsPage);
      vboxLayout4->setSpacing(6);
      vboxLayout4->setMargin(11);
      vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
      mpTblReactions = new Q3Table(mpReactionsPage);
      mpTblReactions->setObjectName(QString::fromUtf8("mpTblReactions"));
      mpTblReactions->setNumRows(0);
      mpTblReactions->setNumCols(3);
      mpTblReactions->setReadOnly(true);

      vboxLayout4->addWidget(mpTblReactions);

      mpTabWidget->addTab(mpReactionsPage, QString());
      mpJacobianPage = new QWidget();
      mpJacobianPage->setObjectName(QString::fromUtf8("mpJacobianPage"));
      vboxLayout5 = new Q3VBoxLayout(mpJacobianPage);
      vboxLayout5->setSpacing(6);
      vboxLayout5->setMargin(11);
      vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
      gridLayout = new Q3GridLayout(1, 1);
      gridLayout->setSpacing(6);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      spacer3 = new QSpacerItem(516, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

      gridLayout->addItem(spacer3, 0, 1, 1, 1);

      mpJacobianAnnotationWidget = new CQArrayAnnotationsWidget(mpJacobianPage);
      mpJacobianAnnotationWidget->setObjectName(QString::fromUtf8("mpJacobianAnnotationWidget"));

      gridLayout->addWidget(mpJacobianAnnotationWidget, 1, 0, 1, 2);

      textLabelJacobian = new QLabel(mpJacobianPage);
      textLabelJacobian->setObjectName(QString::fromUtf8("textLabelJacobian"));
      textLabelJacobian->setWordWrap(false);

      gridLayout->addWidget(textLabelJacobian, 0, 0, 1, 1);

      vboxLayout5->addLayout(gridLayout);

      line1 = new Q3Frame(mpJacobianPage);
      line1->setObjectName(QString::fromUtf8("line1"));
      line1->setFrameShape(Q3Frame::HLine);
      line1->setFrameShadow(Q3Frame::Sunken);

      vboxLayout5->addWidget(line1);

      gridLayout1 = new Q3GridLayout(1, 1);
      gridLayout1->setSpacing(6);
      gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
      tableEigenValues = new Q3Table(mpJacobianPage);
      tableEigenValues->setObjectName(QString::fromUtf8("tableEigenValues"));
      tableEigenValues->setNumRows(0);
      tableEigenValues->setNumCols(2);
      tableEigenValues->setReadOnly(true);

      gridLayout1->addWidget(tableEigenValues, 1, 0, 1, 2);

      spacer4 = new QSpacerItem(141, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      gridLayout1->addItem(spacer4, 0, 1, 1, 1);

      textLabelEigenvalues = new QLabel(mpJacobianPage);
      textLabelEigenvalues->setObjectName(QString::fromUtf8("textLabelEigenvalues"));
      textLabelEigenvalues->setWordWrap(false);

      gridLayout1->addWidget(textLabelEigenvalues, 0, 0, 1, 1);

      vboxLayout5->addLayout(gridLayout1);

      mpTabWidget->addTab(mpJacobianPage, QString());
      mpReducedJacobianPage = new QWidget();
      mpReducedJacobianPage->setObjectName(QString::fromUtf8("mpReducedJacobianPage"));
      vboxLayout6 = new Q3VBoxLayout(mpReducedJacobianPage);
      vboxLayout6->setSpacing(6);
      vboxLayout6->setMargin(11);
      vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
      gridLayout2 = new Q3GridLayout(1, 1);
      gridLayout2->setSpacing(6);
      gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
      mpJacobianXAnnotationWidget = new CQArrayAnnotationsWidget(mpReducedJacobianPage);
      mpJacobianXAnnotationWidget->setObjectName(QString::fromUtf8("mpJacobianXAnnotationWidget"));

      gridLayout2->addWidget(mpJacobianXAnnotationWidget, 1, 0, 1, 2);

      spacer3_2 = new QSpacerItem(518, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

      gridLayout2->addItem(spacer3_2, 0, 1, 1, 1);

      textLabelJacobianX = new QLabel(mpReducedJacobianPage);
      textLabelJacobianX->setObjectName(QString::fromUtf8("textLabelJacobianX"));
      textLabelJacobianX->setWordWrap(false);

      gridLayout2->addWidget(textLabelJacobianX, 0, 0, 1, 1);

      vboxLayout6->addLayout(gridLayout2);

      line2 = new Q3Frame(mpReducedJacobianPage);
      line2->setObjectName(QString::fromUtf8("line2"));
      line2->setFrameShape(Q3Frame::HLine);
      line2->setFrameShadow(Q3Frame::Sunken);

      vboxLayout6->addWidget(line2);

      gridLayout3 = new Q3GridLayout(1, 1);
      gridLayout3->setSpacing(6);
      gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
      tableEigenValuesX = new Q3Table(mpReducedJacobianPage);
      tableEigenValuesX->setObjectName(QString::fromUtf8("tableEigenValuesX"));
      tableEigenValuesX->setNumRows(0);
      tableEigenValuesX->setNumCols(2);
      tableEigenValuesX->setReadOnly(true);

      gridLayout3->addWidget(tableEigenValuesX, 1, 0, 1, 2);

      spacer4_2 = new QSpacerItem(141, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      gridLayout3->addItem(spacer4_2, 0, 1, 1, 1);

      textLabelEigenvaluesX = new QLabel(mpReducedJacobianPage);
      textLabelEigenvaluesX->setObjectName(QString::fromUtf8("textLabelEigenvaluesX"));
      textLabelEigenvaluesX->setWordWrap(false);

      gridLayout3->addWidget(textLabelEigenvaluesX, 0, 0, 1, 1);

      vboxLayout6->addLayout(gridLayout3);

      mpTabWidget->addTab(mpReducedJacobianPage, QString());
      mpStabilityPage = new QWidget();
      mpStabilityPage->setObjectName(QString::fromUtf8("mpStabilityPage"));
      vboxLayout7 = new Q3VBoxLayout(mpStabilityPage);
      vboxLayout7->setSpacing(6);
      vboxLayout7->setMargin(11);
      vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
      stabilityTextEdit = new Q3TextEdit(mpStabilityPage);
      stabilityTextEdit->setObjectName(QString::fromUtf8("stabilityTextEdit"));
      stabilityTextEdit->setReadOnly(true);

      vboxLayout7->addWidget(stabilityTextEdit);

      mpTabWidget->addTab(mpStabilityPage, QString());
      mpProtocolPage = new QWidget();
      mpProtocolPage->setObjectName(QString::fromUtf8("mpProtocolPage"));
      gridLayout4 = new Q3GridLayout(mpProtocolPage);
      gridLayout4->setSpacing(6);
      gridLayout4->setMargin(11);
      gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
      protocolTextEdit = new Q3TextEdit(mpProtocolPage);
      protocolTextEdit->setObjectName(QString::fromUtf8("protocolTextEdit"));
      protocolTextEdit->setReadOnly(true);
      protocolTextEdit->setUndoRedoEnabled(false);
      protocolTextEdit->setAutoFormatting(Q3TextEdit::AutoAll);

      gridLayout4->addWidget(protocolTextEdit, 0, 0, 1, 1);

      mpTabWidget->addTab(mpProtocolPage, QString());

      vboxLayout->addWidget(mpTabWidget);

      retranslateUi(StateSubwidget);

      QMetaObject::connectSlotsByName(StateSubwidget);
    } // setupUi

    void retranslateUi(CopasiWidget *StateSubwidget)
    {
      StateSubwidget->setCaption(QApplication::translate("StateSubwidget", "Steady-State Result Window", 0, QApplication::UnicodeUTF8));
      topLabel->setText(QApplication::translate("StateSubwidget", "textLabel1", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpOptimizationPage), QApplication::translate("StateSubwidget", "Optimization Result", 0, QApplication::UnicodeUTF8));
      mpTblMetabolites->horizontalHeader()->setLabel(0, QApplication::translate("StateSubwidget", "Name", 0, QApplication::UnicodeUTF8));
      mpTblMetabolites->horizontalHeader()->setLabel(1, QApplication::translate("StateSubwidget", "Type", 0, QApplication::UnicodeUTF8));
      mpTblMetabolites->horizontalHeader()->setLabel(2, QApplication::translate("StateSubwidget", "Concentration", 0, QApplication::UnicodeUTF8));
      mpTblMetabolites->horizontalHeader()->setLabel(3, QApplication::translate("StateSubwidget", "Rate", 0, QApplication::UnicodeUTF8));
      mpTblMetabolites->horizontalHeader()->setLabel(4, QApplication::translate("StateSubwidget", "Transition Time", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpMetabolitesPage), QApplication::translate("StateSubwidget", "Species", 0, QApplication::UnicodeUTF8));
      mpTblCompartments->horizontalHeader()->setLabel(0, QApplication::translate("StateSubwidget", "Name", 0, QApplication::UnicodeUTF8));
      mpTblCompartments->horizontalHeader()->setLabel(1, QApplication::translate("StateSubwidget", "Type", 0, QApplication::UnicodeUTF8));
      mpTblCompartments->horizontalHeader()->setLabel(2, QApplication::translate("StateSubwidget", "Volume", 0, QApplication::UnicodeUTF8));
      mpTblCompartments->horizontalHeader()->setLabel(3, QApplication::translate("StateSubwidget", "Rate", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpCompartmentsPage), QApplication::translate("StateSubwidget", "Compartments", 0, QApplication::UnicodeUTF8));
      mpTblModelValues->horizontalHeader()->setLabel(0, QApplication::translate("StateSubwidget", "Name", 0, QApplication::UnicodeUTF8));
      mpTblModelValues->horizontalHeader()->setLabel(1, QApplication::translate("StateSubwidget", "Type", 0, QApplication::UnicodeUTF8));
      mpTblModelValues->horizontalHeader()->setLabel(2, QApplication::translate("StateSubwidget", "Value", 0, QApplication::UnicodeUTF8));
      mpTblModelValues->horizontalHeader()->setLabel(3, QApplication::translate("StateSubwidget", "Rate", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpModelQuantitiesPage), QApplication::translate("StateSubwidget", "Model Quantities", 0, QApplication::UnicodeUTF8));
      mpTblReactions->horizontalHeader()->setLabel(0, QApplication::translate("StateSubwidget", "Name", 0, QApplication::UnicodeUTF8));
      mpTblReactions->horizontalHeader()->setLabel(1, QApplication::translate("StateSubwidget", "Flux", 0, QApplication::UnicodeUTF8));
      mpTblReactions->horizontalHeader()->setLabel(2, QApplication::translate("StateSubwidget", "Chemical Equation", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpReactionsPage), QApplication::translate("StateSubwidget", "Reactions", 0, QApplication::UnicodeUTF8));
      textLabelJacobian->setText(QApplication::translate("StateSubwidget", "Jacobian (Complete System)", 0, QApplication::UnicodeUTF8));
      tableEigenValues->horizontalHeader()->setLabel(0, QApplication::translate("StateSubwidget", "Real", 0, QApplication::UnicodeUTF8));
      tableEigenValues->horizontalHeader()->setLabel(1, QApplication::translate("StateSubwidget", "Imaginary", 0, QApplication::UnicodeUTF8));
      textLabelEigenvalues->setText(QApplication::translate("StateSubwidget", "Eigenvalues (Complete System)", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpJacobianPage), QApplication::translate("StateSubwidget", "Jacobian (Complete)", 0, QApplication::UnicodeUTF8));
      textLabelJacobianX->setText(QApplication::translate("StateSubwidget", "Jacobian (Reduced System)", 0, QApplication::UnicodeUTF8));
      tableEigenValuesX->horizontalHeader()->setLabel(0, QApplication::translate("StateSubwidget", "Real", 0, QApplication::UnicodeUTF8));
      tableEigenValuesX->horizontalHeader()->setLabel(1, QApplication::translate("StateSubwidget", "Imaginary", 0, QApplication::UnicodeUTF8));
      textLabelEigenvaluesX->setText(QApplication::translate("StateSubwidget", "Eigenvalues (Reduced System)", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpReducedJacobianPage), QApplication::translate("StateSubwidget", "Jacobian (Reduced)", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpStabilityPage), QApplication::translate("StateSubwidget", "Stability", 0, QApplication::UnicodeUTF8));
      mpTabWidget->setTabText(mpTabWidget->indexOf(mpProtocolPage), QApplication::translate("StateSubwidget", "Protocol", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(StateSubwidget);
    } // retranslateUi

  protected:
    enum IconID
    {
      image0_ID,
      unknown_ID
    };
    static QPixmap qt_get_icon(IconID id)
    {
      static const unsigned char image0_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
          0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x03,
          0xb1, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0xad, 0x94, 0x51, 0x4c, 0x5b,
          0x55, 0x18, 0xc7, 0x7f, 0xe7, 0xdc, 0x4b, 0x7b, 0x4b, 0x61, 0x50, 0xbb,
          0x96, 0x32, 0x44, 0x18, 0xca, 0x32, 0x35, 0x8b, 0xee, 0x61, 0x92, 0x60,
          0x9c, 0x51, 0xd8, 0x83, 0x89, 0x2c, 0xe0, 0x83, 0xf1, 0x71, 0x8b, 0x3e,
          0xbb, 0x18, 0x5f, 0x8d, 0xc9, 0x1e, 0x97, 0x2c, 0xf3, 0x9d, 0x2d, 0x6a,
          0x78, 0xd0, 0xb0, 0x27, 0xb3, 0xcd, 0x07, 0xd9, 0xe6, 0x8c, 0x81, 0xc6,
          0x25, 0xa6, 0xc1, 0x39, 0x40, 0x8a, 0x43, 0x84, 0xf4, 0x16, 0x10, 0x0a,
          0xed, 0x6d, 0x4b, 0x7b, 0xdb, 0x7b, 0x8e, 0x0f, 0xc0, 0x92, 0x1a, 0x70,
          0xc6, 0xed, 0x7b, 0x3a, 0xe7, 0xe4, 0x3b, 0xbf, 0xf3, 0xff, 0xfe, 0xdf,
          0xc9, 0x27, 0xe2, 0xf1, 0x38, 0xbb, 0xd1, 0xdb, 0xdb, 0xab, 0x79, 0x02,
          0x11, 0x8f, 0xc7, 0x85, 0xd8, 0x05, 0x8f, 0x8d, 0x8d, 0xe9, 0xae, 0xae,
          0x2e, 0x72, 0xb9, 0x1c, 0xb6, 0x6d, 0xe3, 0x38, 0xce, 0x7f, 0x82, 0xe4,
          0x72, 0x39, 0x66, 0x67, 0x67, 0x49, 0x24, 0x12, 0xb8, 0xae, 0xfb, 0xf0,
          0xdc, 0xdc, 0x55, 0x3a, 0x32, 0x32, 0x42, 0xf4, 0x50, 0x1d, 0x91, 0x8e,
          0x2d, 0x3a, 0x8f, 0x15, 0xa9, 0x78, 0x45, 0x84, 0x10, 0x08, 0x09, 0xa6,
          0x09, 0x52, 0x6e, 0xaf, 0xd1, 0xa0, 0xf5, 0x4e, 0x61, 0x42, 0xe0, 0x29,
          0xc5, 0xc2, 0x1f, 0x3e, 0xf4, 0x15, 0x83, 0xbb, 0x77, 0xa8, 0x05, 0xef,
          0xbe, 0x1c, 0xe9, 0xd8, 0x62, 0x79, 0xe3, 0x26, 0x19, 0x67, 0x8e, 0xaa,
          0xb7, 0x85, 0x3f, 0xa0, 0xf0, 0x2a, 0x16, 0xab, 0xb6, 0x41, 0x66, 0xad,
          0x0c, 0xda, 0xc7, 0x53, 0x07, 0xeb, 0x38, 0x74, 0xb8, 0x4c, 0xb0, 0xa1,
          0x4a, 0xa5, 0xa2, 0x41, 0x08, 0xcc, 0x06, 0x88, 0xc4, 0x8c, 0x9a, 0x4a,
          0x1e, 0x82, 0x6d, 0xdb, 0xe6, 0xf0, 0xb1, 0x22, 0x19, 0x67, 0x8e, 0x8a,
          0xce, 0x61, 0x05, 0x02, 0xcc, 0xdf, 0xaf, 0xe3, 0xf6, 0x8d, 0x3c, 0x33,
          0xbf, 0x6c, 0x01, 0xc5, 0x9d, 0xcc, 0x20, 0x9d, 0x47, 0x2c, 0x4e, 0x0d,
          0x35, 0xd2, 0xf3, 0xba, 0x81, 0xd2, 0x05, 0xd0, 0x60, 0x05, 0xe4, 0xde,
          0x60, 0xc7, 0x71, 0x70, 0xbd, 0x22, 0x55, 0xaf, 0x80, 0x15, 0x08, 0x70,
          0xf7, 0x0e, 0x8c, 0x0e, 0xaf, 0x00, 0x92, 0x60, 0xa3, 0x49, 0x57, 0x77,
          0x14, 0xe9, 0x13, 0xa4, 0x17, 0x5d, 0x16, 0x92, 0x5b, 0x5c, 0xbe, 0x50,
          0x60, 0x79, 0x31, 0xcc, 0x3b, 0x67, 0x7c, 0x68, 0xca, 0x28, 0xa5, 0xf7,
          0x06, 0x6f, 0x5b, 0x26, 0xf0, 0x07, 0x60, 0xfe, 0xbe, 0xc9, 0xe8, 0xf0,
          0x32, 0xa0, 0xe8, 0x1b, 0x68, 0xa1, 0x7f, 0xc0, 0x20, 0x14, 0x15, 0x98,
          0x96, 0x47, 0xa9, 0xd8, 0xc4, 0xc4, 0x98, 0xcb, 0xe8, 0xf0, 0x5f, 0x5c,
          0xff, 0x3a, 0x4d, 0x4b, 0xac, 0x8b, 0xfe, 0x21, 0x0b, 0x29, 0x0b, 0x35,
          0xe0, 0x1a, 0xfd, 0x42, 0x82, 0x57, 0xb1, 0xb8, 0x75, 0xcd, 0x01, 0xaa,
          0xf4, 0xbd, 0x1d, 0xe5, 0xdd, 0x0f, 0xea, 0x68, 0x8e, 0x15, 0x30, 0xad,
          0x1c, 0x1b, 0xab, 0x16, 0xb7, 0xaf, 0x17, 0x39, 0x35, 0x58, 0xcf, 0x99,
          0x73, 0x11, 0xc0, 0xe4, 0x9b, 0xaf, 0xd6, 0x70, 0xd6, 0x25, 0x86, 0x21,
          0xf6, 0x57, 0x6c, 0x9a, 0xb0, 0x9a, 0x32, 0x48, 0xfe, 0x5a, 0xe6, 0xc0,
          0x81, 0x03, 0xf4, 0x9f, 0x36, 0x51, 0x72, 0x13, 0xd3, 0x30, 0x70, 0x36,
          0x9b, 0xf8, 0xe2, 0x52, 0x9e, 0xe9, 0xc9, 0x0c, 0xeb, 0x2b, 0x2e, 0xef,
          0x7f, 0x14, 0x61, 0x7c, 0x2c, 0x48, 0x72, 0x2a, 0x4b, 0x72, 0x26, 0x84,
          0x51, 0x43, 0xfa, 0x87, 0x62, 0x29, 0x05, 0xeb, 0xeb, 0x65, 0x14, 0x25,
          0x3a, 0x9e, 0xb5, 0x08, 0x45, 0x04, 0xa6, 0x69, 0x50, 0xc8, 0x86, 0x18,
          0xbe, 0xe0, 0x30, 0x3d, 0x99, 0x21, 0x7c, 0xb0, 0x9e, 0x9e, 0xd7, 0x1a,
          0x09, 0x36, 0x95, 0x38, 0xfa, 0x52, 0x3d, 0x00, 0xe9, 0xa5, 0x0a, 0x42,
          0xee, 0xd3, 0xbc, 0x6d, 0x8f, 0x41, 0x28, 0x1f, 0xa0, 0x90, 0x3e, 0x85,
          0x61, 0x79, 0x6c, 0xac, 0x86, 0xf8, 0xf2, 0xb3, 0x3c, 0x33, 0x93, 0x0e,
          0xa0, 0xf0, 0xfb, 0x4d, 0x5a, 0xdb, 0xeb, 0x30, 0xad, 0x22, 0x86, 0x6f,
          0xfb, 0xba, 0xd2, 0x26, 0xd2, 0xa8, 0x05, 0xd7, 0xee, 0x04, 0x84, 0x22,
          0x02, 0x08, 0x92, 0x5a, 0xaa, 0x50, 0xde, 0xaa, 0x67, 0xe2, 0x7b, 0x97,
          0xe9, 0xc9, 0x0c, 0xcd, 0xcd, 0xf5, 0xc4, 0x62, 0xcd, 0xd8, 0xa9, 0x4d,
          0x2e, 0x7e, 0x62, 0xf3, 0x60, 0x32, 0x44, 0xea, 0x41, 0x09, 0x89, 0xa4,
          0xed, 0x19, 0x1f, 0x52, 0xa8, 0xfd, 0x15, 0x6b, 0x05, 0x6d, 0x9d, 0x55,
          0x3a, 0x9e, 0x0b, 0xf0, 0xe7, 0xef, 0x45, 0xc6, 0xbf, 0x73, 0x39, 0xfd,
          0x5e, 0x90, 0xec, 0x7a, 0x88, 0x57, 0x5e, 0x6d, 0x20, 0xd6, 0xe6, 0xe7,
          0xe2, 0xa7, 0x55, 0xec, 0x85, 0x4d, 0xce, 0x7f, 0xb8, 0x88, 0x5b, 0x2c,
          0xd0, 0x14, 0xf6, 0xf3, 0xc2, 0x71, 0x4d, 0x3a, 0x55, 0x0b, 0xae, 0x55,
          0xac, 0x35, 0xc1, 0x06, 0x8f, 0xb7, 0x06, 0x1b, 0x00, 0xb8, 0x7a, 0x79,
          0x95, 0x89, 0x9b, 0x25, 0xce, 0x9e, 0x0b, 0x73, 0xe2, 0x4d, 0x8f, 0xae,
          0x97, 0xb3, 0x7c, 0x7c, 0xbe, 0x93, 0x70, 0xb4, 0x99, 0xfc, 0xe6, 0x06,
          0x6e, 0xb5, 0x4a, 0xdf, 0x60, 0x98, 0xf6, 0xee, 0x2a, 0x9a, 0x7f, 0xf9,
          0xc7, 0x08, 0x41, 0xa5, 0x02, 0x3d, 0x27, 0x0d, 0xec, 0xa5, 0x10, 0xd7,
          0x46, 0x53, 0x7c, 0x7e, 0x29, 0xcd, 0xf8, 0xad, 0x20, 0x47, 0x5f, 0xb4,
          0x30, 0x7c, 0x82, 0xd4, 0xfc, 0x32, 0x4e, 0xc6, 0x85, 0x9d, 0x66, 0xfd,
          0xfc, 0x63, 0x81, 0xe4, 0x40, 0x14, 0xb3, 0x6e, 0x9f, 0xe6, 0xe5, 0x72,
          0x39, 0x3c, 0xa5, 0x40, 0x68, 0xaa, 0x22, 0xcf, 0xd0, 0x59, 0x8b, 0x68,
          0x6b, 0x37, 0x37, 0xae, 0xae, 0x90, 0xbc, 0x97, 0x25, 0x79, 0x6f, 0x03,
          0x50, 0x80, 0x24, 0x14, 0xb6, 0xe8, 0x1b, 0x7c, 0x9a, 0x9f, 0x7e, 0x70,
          0x70, 0x8a, 0x2e, 0x6e, 0x59, 0x91, 0xcf, 0xee, 0xe3, 0xf1, 0xec, 0xec,
          0x2c, 0x0b, 0x0b, 0x3e, 0x8c, 0x06, 0x81, 0x42, 0xa2, 0xa8, 0xd2, 0x37,
          0x28, 0x39, 0x71, 0x32, 0xc6, 0xdc, 0x6f, 0x2e, 0x2b, 0x8b, 0x0a, 0x8d,
          0xa4, 0xb5, 0xdd, 0xc7, 0xf3, 0xc7, 0x35, 0xed, 0x47, 0x14, 0x6f, 0x0c,
          0xb4, 0x50, 0x29, 0x83, 0x69, 0x3a, 0x4c, 0x25, 0xca, 0x7b, 0x83, 0x13,
          0x89, 0x04, 0xfa, 0x8a, 0x41, 0x24, 0x66, 0xe0, 0x0f, 0x48, 0xb4, 0x27,
          0x10, 0x86, 0xc2, 0x90, 0x12, 0x63, 0x67, 0x6c, 0x4a, 0x69, 0x90, 0xb6,
          0x15, 0xb6, 0xad, 0xe1, 0x5b, 0x85, 0x69, 0x4a, 0xf2, 0x39, 0x98, 0x4a,
          0x94, 0x58, 0x5b, 0xf6, 0xf6, 0x06, 0xbb, 0xae, 0x5b, 0x33, 0x4f, 0x1f,
          0x37, 0xe4, 0xa3, 0x53, 0x1e, 0x03, 0x1c, 0x8f, 0xc7, 0xc5, 0xa3, 0x12,
          0xff, 0x17, 0xf8, 0x49, 0xc3, 0xe3, 0xf1, 0xb8, 0xf8, 0x1b, 0x8b, 0xe6,
          0x90, 0x0a, 0x47, 0x48, 0x10, 0x66, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
          0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

      switch (id)
        {
        case image0_ID: {QImage img; img.loadFromData(image0_data, sizeof(image0_data), "PNG"); return QPixmap::fromImage(img);}
        default: return QPixmap();
        } // switch
    } // icon
  };

namespace Ui
  {
  class StateSubwidget: public Ui_StateSubwidget {};
} // namespace Ui

class StateSubwidget : public CopasiWidget, public Ui::StateSubwidget
  {
    Q_OBJECT

  public:
    StateSubwidget(QWidget* parent = 0, const char* name = 0);
    ~StateSubwidget();

    void displayOptimizationTab(bool displayOptTab);
    virtual bool loadAll(const CSteadyStateTask * pTask);
    void clear();
    virtual void setFramework(int framework);
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected:
    const CSteadyStateTask * mpTask;
    CModel * mpModel;

    virtual void init();
    void loadMetabolites();
    void loadCompartments();
    void loadReactions();
    void loadModelValues();
    void loadJacobian();
    void showUnits();

  protected slots:
    virtual void languageChange();
  };

#endif // STATESUBWIDGET_H
