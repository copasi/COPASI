// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/CQTSSAResultSubWidget.h,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTSSARESULTSUBWIDGET_H
#define CQTSSARESULTSUBWIDGET_H

#include <qvariant.h>

#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "CQArrayAnnotationsWidget.h"
#include "CTimeSeriesTable.h"
#include "copasi.h"

class Ui_CQTSSAResultSubWidget
  {
  public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QComboBox *comboBox;
    QSpacerItem *spacer;
    QPushButton *ButtonSaveData;
    QTabWidget *tabWidget2;
    QWidget *tab;
    QVBoxLayout *vboxLayout;
    Q3TextEdit *optimizationResultText;
    QWidget *tab1;
    QVBoxLayout *vboxLayout1;
    CTimeSeriesTable *dataTable;
    QWidget *TabPage_ILDM;
    QGridLayout *gridLayout1;
    QTabWidget *mTabWidget;
    QWidget *tab2;
    QGridLayout *gridLayout2;
    CQArrayAnnotationsWidget *pArrayWidget;
    QWidget *tab3;
    QGridLayout *gridLayout3;
    CQArrayAnnotationsWidget *pArrayWidget2;
    QWidget *TabPage;
    QGridLayout *gridLayout4;
    CQArrayAnnotationsWidget *pArrayWidget3;
    QWidget *TabPage1;
    QGridLayout *gridLayout5;
    CQArrayAnnotationsWidget *pArrayWidget4;
    QWidget *TabPage2;
    QVBoxLayout *vboxLayout2;
    CQArrayAnnotationsWidget *pArrayWidget_3_2;
    QSlider *mSlider;
    QSpacerItem *mSpacer;
    QLabel *mLabel7;
    QLabel *pLabel1;
    QLabel *mLabel2;
    QLabel *mLabel3;
    QLabel *mLabel4;
    QLabel *mLabel5;
    QLabel *mLabel6;
    QWidget *TabPage_ILDMM;
    QGridLayout *gridLayout6;
    QLabel *pLabel1_6;
    QLabel *mLabel6_6;
    QLabel *mLabel4_6;
    QLabel *mLabel2_6;
    QLabel *mLabel3_6;
    QSpacerItem *mSpacer_6;
    QLabel *mLabel5_6;
    QSlider *mSlider_4;
    QTabWidget *mTabWidget_4;
    QWidget *tab4;
    QGridLayout *gridLayout7;
    CQArrayAnnotationsWidget *pArrayWidget_5;
    QWidget *tab5;
    QGridLayout *gridLayout8;
    CQArrayAnnotationsWidget *pArrayWidget2_5;
    QWidget *TabPage3;
    QGridLayout *gridLayout9;
    CQArrayAnnotationsWidget *pArrayWidget3_5;
    QWidget *TabPage4;
    QGridLayout *gridLayout10;
    CQArrayAnnotationsWidget *pArrayWidget4_5;
    QWidget *TabPage_CSP;
    QGridLayout *gridLayout11;
    QTabWidget *mTabWidget_3;
    QWidget *tab6;
    QGridLayout *gridLayout12;
    CQArrayAnnotationsWidget *pArrayWidget_3;
    QWidget *tab7;
    QGridLayout *gridLayout13;
    CQArrayAnnotationsWidget *pArrayWidget2_3;
    QWidget *TabPage5;
    QGridLayout *gridLayout14;
    CQArrayAnnotationsWidget *pArrayWidget3_3;
    QWidget *TabPage6;
    QGridLayout *gridLayout15;
    CQArrayAnnotationsWidget *pArrayWidget4_3;
    QWidget *TabPage7;
    QGridLayout *gridLayout16;
    CQArrayAnnotationsWidget *pArrayWidget4_3_2;
    QLabel *pLabel1_3;
    QLabel *mLabel2_3;
    QLabel *mLabel3_3;
    QLabel *mLabel4_3;
    QLabel *mLabel5_3;
    QLabel *mLabel6_3;
    QSpacerItem *mSpacer_3;
    QSlider *mSlider_3;

    void setupUi(QWidget *CQTSSAResultSubWidget)
    {
      if (CQTSSAResultSubWidget->objectName().isEmpty())
        CQTSSAResultSubWidget->setObjectName(QString::fromUtf8("CQTSSAResultSubWidget"));
      CQTSSAResultSubWidget->resize(612, 473);
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(7));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(CQTSSAResultSubWidget->sizePolicy().hasHeightForWidth());
      CQTSSAResultSubWidget->setSizePolicy(sizePolicy);
      gridLayout = new QGridLayout(CQTSSAResultSubWidget);
      gridLayout->setSpacing(6);
      gridLayout->setMargin(11);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      hboxLayout = new QHBoxLayout();
      hboxLayout->setSpacing(1);
      hboxLayout->setMargin(1);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      comboBox = new QComboBox(CQTSSAResultSubWidget);
      comboBox->setObjectName(QString::fromUtf8("comboBox"));
      QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(0));
      sizePolicy1.setHorizontalStretch(0);
      sizePolicy1.setVerticalStretch(0);
      sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
      comboBox->setSizePolicy(sizePolicy1);

      hboxLayout->addWidget(comboBox);

      spacer = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      hboxLayout->addItem(spacer);

      ButtonSaveData = new QPushButton(CQTSSAResultSubWidget);
      ButtonSaveData->setObjectName(QString::fromUtf8("ButtonSaveData"));
      sizePolicy1.setHeightForWidth(ButtonSaveData->sizePolicy().hasHeightForWidth());
      ButtonSaveData->setSizePolicy(sizePolicy1);

      hboxLayout->addWidget(ButtonSaveData);

      gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

      tabWidget2 = new QTabWidget(CQTSSAResultSubWidget);
      tabWidget2->setObjectName(QString::fromUtf8("tabWidget2"));
      tab = new QWidget();
      tab->setObjectName(QString::fromUtf8("tab"));
      vboxLayout = new QVBoxLayout(tab);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      optimizationResultText = new Q3TextEdit(tab);
      optimizationResultText->setObjectName(QString::fromUtf8("optimizationResultText"));
      optimizationResultText->setReadOnly(true);

      vboxLayout->addWidget(optimizationResultText);

      tabWidget2->addTab(tab, QString());
      tab1 = new QWidget();
      tab1->setObjectName(QString::fromUtf8("tab1"));
      vboxLayout1 = new QVBoxLayout(tab1);
      vboxLayout1->setSpacing(6);
      vboxLayout1->setMargin(11);
      vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
      dataTable = new CTimeSeriesTable(tab1);
      dataTable->setObjectName(QString::fromUtf8("dataTable"));

      vboxLayout1->addWidget(dataTable);

      tabWidget2->addTab(tab1, QString());
      TabPage_ILDM = new QWidget();
      TabPage_ILDM->setObjectName(QString::fromUtf8("TabPage_ILDM"));
      gridLayout1 = new QGridLayout(TabPage_ILDM);
      gridLayout1->setSpacing(6);
      gridLayout1->setMargin(11);
      gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
      mTabWidget = new QTabWidget(TabPage_ILDM);
      mTabWidget->setObjectName(QString::fromUtf8("mTabWidget"));
      tab2 = new QWidget();
      tab2->setObjectName(QString::fromUtf8("tab2"));
      gridLayout2 = new QGridLayout(tab2);
      gridLayout2->setSpacing(6);
      gridLayout2->setMargin(11);
      gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
      pArrayWidget = new CQArrayAnnotationsWidget(tab2);
      pArrayWidget->setObjectName(QString::fromUtf8("pArrayWidget"));

      gridLayout2->addWidget(pArrayWidget, 0, 0, 1, 1);

      mTabWidget->addTab(tab2, QString());
      tab3 = new QWidget();
      tab3->setObjectName(QString::fromUtf8("tab3"));
      gridLayout3 = new QGridLayout(tab3);
      gridLayout3->setSpacing(6);
      gridLayout3->setMargin(11);
      gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
      pArrayWidget2 = new CQArrayAnnotationsWidget(tab3);
      pArrayWidget2->setObjectName(QString::fromUtf8("pArrayWidget2"));

      gridLayout3->addWidget(pArrayWidget2, 0, 0, 1, 1);

      mTabWidget->addTab(tab3, QString());
      TabPage = new QWidget();
      TabPage->setObjectName(QString::fromUtf8("TabPage"));
      gridLayout4 = new QGridLayout(TabPage);
      gridLayout4->setSpacing(6);
      gridLayout4->setMargin(11);
      gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
      pArrayWidget3 = new CQArrayAnnotationsWidget(TabPage);
      pArrayWidget3->setObjectName(QString::fromUtf8("pArrayWidget3"));

      gridLayout4->addWidget(pArrayWidget3, 0, 0, 1, 1);

      mTabWidget->addTab(TabPage, QString());
      TabPage1 = new QWidget();
      TabPage1->setObjectName(QString::fromUtf8("TabPage1"));
      gridLayout5 = new QGridLayout(TabPage1);
      gridLayout5->setSpacing(6);
      gridLayout5->setMargin(11);
      gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
      pArrayWidget4 = new CQArrayAnnotationsWidget(TabPage1);
      pArrayWidget4->setObjectName(QString::fromUtf8("pArrayWidget4"));

      gridLayout5->addWidget(pArrayWidget4, 0, 0, 1, 1);

      mTabWidget->addTab(TabPage1, QString());
      TabPage2 = new QWidget();
      TabPage2->setObjectName(QString::fromUtf8("TabPage2"));
      vboxLayout2 = new QVBoxLayout(TabPage2);
      vboxLayout2->setSpacing(6);
      vboxLayout2->setMargin(11);
      vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
      pArrayWidget_3_2 = new CQArrayAnnotationsWidget(TabPage2);
      pArrayWidget_3_2->setObjectName(QString::fromUtf8("pArrayWidget_3_2"));

      vboxLayout2->addWidget(pArrayWidget_3_2);

      mTabWidget->addTab(TabPage2, QString());

      gridLayout1->addWidget(mTabWidget, 2, 0, 1, 8);

      mSlider = new QSlider(TabPage_ILDM);
      mSlider->setObjectName(QString::fromUtf8("mSlider"));
      QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(1));
      sizePolicy2.setHorizontalStretch(0);
      sizePolicy2.setVerticalStretch(0);
      sizePolicy2.setHeightForWidth(mSlider->sizePolicy().hasHeightForWidth());
      mSlider->setSizePolicy(sizePolicy2);
      mSlider->setMouseTracking(true);
      mSlider->setAcceptDrops(true);
      mSlider->setMaximum(0);
      mSlider->setPageStep(1);
      mSlider->setTracking(true);
      mSlider->setOrientation(Qt::Horizontal);
      mSlider->setTickPosition(QSlider::NoTicks);
      mSlider->setTickInterval(1);

      gridLayout1->addWidget(mSlider, 1, 0, 1, 8);

      mSpacer = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      gridLayout1->addItem(mSpacer, 0, 7, 1, 1);

      mLabel7 = new QLabel(TabPage_ILDM);
      mLabel7->setObjectName(QString::fromUtf8("mLabel7"));
      QSizePolicy sizePolicy3(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(1));
      sizePolicy3.setHorizontalStretch(0);
      sizePolicy3.setVerticalStretch(0);
      sizePolicy3.setHeightForWidth(mLabel7->sizePolicy().hasHeightForWidth());
      mLabel7->setSizePolicy(sizePolicy3);
      mLabel7->setWordWrap(false);

      gridLayout1->addWidget(mLabel7, 0, 2, 1, 1);

      pLabel1 = new QLabel(TabPage_ILDM);
      pLabel1->setObjectName(QString::fromUtf8("pLabel1"));
      QSizePolicy sizePolicy4(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(1));
      sizePolicy4.setHorizontalStretch(0);
      sizePolicy4.setVerticalStretch(0);
      sizePolicy4.setHeightForWidth(pLabel1->sizePolicy().hasHeightForWidth());
      pLabel1->setSizePolicy(sizePolicy4);
      pLabel1->setWordWrap(false);

      gridLayout1->addWidget(pLabel1, 0, 0, 1, 1);

      mLabel2 = new QLabel(TabPage_ILDM);
      mLabel2->setObjectName(QString::fromUtf8("mLabel2"));
      sizePolicy3.setHeightForWidth(mLabel2->sizePolicy().hasHeightForWidth());
      mLabel2->setSizePolicy(sizePolicy3);
      QFont font;
      font.setBold(true);
      mLabel2->setFont(font);
      mLabel2->setWordWrap(false);

      gridLayout1->addWidget(mLabel2, 0, 1, 1, 1);

      mLabel3 = new QLabel(TabPage_ILDM);
      mLabel3->setObjectName(QString::fromUtf8("mLabel3"));
      sizePolicy4.setHeightForWidth(mLabel3->sizePolicy().hasHeightForWidth());
      mLabel3->setSizePolicy(sizePolicy4);
      mLabel3->setWordWrap(false);

      gridLayout1->addWidget(mLabel3, 0, 3, 1, 1);

      mLabel4 = new QLabel(TabPage_ILDM);
      mLabel4->setObjectName(QString::fromUtf8("mLabel4"));
      sizePolicy3.setHeightForWidth(mLabel4->sizePolicy().hasHeightForWidth());
      mLabel4->setSizePolicy(sizePolicy3);
      mLabel4->setFont(font);
      mLabel4->setWordWrap(false);

      gridLayout1->addWidget(mLabel4, 0, 4, 1, 1);

      mLabel5 = new QLabel(TabPage_ILDM);
      mLabel5->setObjectName(QString::fromUtf8("mLabel5"));
      sizePolicy4.setHeightForWidth(mLabel5->sizePolicy().hasHeightForWidth());
      mLabel5->setSizePolicy(sizePolicy4);
      mLabel5->setWordWrap(false);

      gridLayout1->addWidget(mLabel5, 0, 5, 1, 1);

      mLabel6 = new QLabel(TabPage_ILDM);
      mLabel6->setObjectName(QString::fromUtf8("mLabel6"));
      sizePolicy3.setHeightForWidth(mLabel6->sizePolicy().hasHeightForWidth());
      mLabel6->setSizePolicy(sizePolicy3);
      mLabel6->setWordWrap(false);

      gridLayout1->addWidget(mLabel6, 0, 6, 1, 1);

      tabWidget2->addTab(TabPage_ILDM, QString());
      TabPage_ILDMM = new QWidget();
      TabPage_ILDMM->setObjectName(QString::fromUtf8("TabPage_ILDMM"));
      gridLayout6 = new QGridLayout(TabPage_ILDMM);
      gridLayout6->setSpacing(6);
      gridLayout6->setMargin(11);
      gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
      pLabel1_6 = new QLabel(TabPage_ILDMM);
      pLabel1_6->setObjectName(QString::fromUtf8("pLabel1_6"));
      sizePolicy4.setHeightForWidth(pLabel1_6->sizePolicy().hasHeightForWidth());
      pLabel1_6->setSizePolicy(sizePolicy4);
      pLabel1_6->setWordWrap(false);

      gridLayout6->addWidget(pLabel1_6, 0, 0, 1, 1);

      mLabel6_6 = new QLabel(TabPage_ILDMM);
      mLabel6_6->setObjectName(QString::fromUtf8("mLabel6_6"));
      sizePolicy3.setHeightForWidth(mLabel6_6->sizePolicy().hasHeightForWidth());
      mLabel6_6->setSizePolicy(sizePolicy3);
      mLabel6_6->setWordWrap(false);

      gridLayout6->addWidget(mLabel6_6, 0, 5, 1, 1);

      mLabel4_6 = new QLabel(TabPage_ILDMM);
      mLabel4_6->setObjectName(QString::fromUtf8("mLabel4_6"));
      sizePolicy3.setHeightForWidth(mLabel4_6->sizePolicy().hasHeightForWidth());
      mLabel4_6->setSizePolicy(sizePolicy3);
      mLabel4_6->setFont(font);
      mLabel4_6->setWordWrap(false);

      gridLayout6->addWidget(mLabel4_6, 0, 3, 1, 1);

      mLabel2_6 = new QLabel(TabPage_ILDMM);
      mLabel2_6->setObjectName(QString::fromUtf8("mLabel2_6"));
      sizePolicy3.setHeightForWidth(mLabel2_6->sizePolicy().hasHeightForWidth());
      mLabel2_6->setSizePolicy(sizePolicy3);
      mLabel2_6->setFont(font);
      mLabel2_6->setWordWrap(false);

      gridLayout6->addWidget(mLabel2_6, 0, 1, 1, 1);

      mLabel3_6 = new QLabel(TabPage_ILDMM);
      mLabel3_6->setObjectName(QString::fromUtf8("mLabel3_6"));
      sizePolicy4.setHeightForWidth(mLabel3_6->sizePolicy().hasHeightForWidth());
      mLabel3_6->setSizePolicy(sizePolicy4);
      mLabel3_6->setWordWrap(false);

      gridLayout6->addWidget(mLabel3_6, 0, 2, 1, 1);

      mSpacer_6 = new QSpacerItem(309, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      gridLayout6->addItem(mSpacer_6, 0, 6, 1, 1);

      mLabel5_6 = new QLabel(TabPage_ILDMM);
      mLabel5_6->setObjectName(QString::fromUtf8("mLabel5_6"));
      sizePolicy4.setHeightForWidth(mLabel5_6->sizePolicy().hasHeightForWidth());
      mLabel5_6->setSizePolicy(sizePolicy4);
      mLabel5_6->setWordWrap(false);

      gridLayout6->addWidget(mLabel5_6, 0, 4, 1, 1);

      mSlider_4 = new QSlider(TabPage_ILDMM);
      mSlider_4->setObjectName(QString::fromUtf8("mSlider_4"));
      sizePolicy2.setHeightForWidth(mSlider_4->sizePolicy().hasHeightForWidth());
      mSlider_4->setSizePolicy(sizePolicy2);
      mSlider_4->setMouseTracking(true);
      mSlider_4->setAcceptDrops(true);
      mSlider_4->setMaximum(0);
      mSlider_4->setPageStep(1);
      mSlider_4->setTracking(true);
      mSlider_4->setOrientation(Qt::Horizontal);
      mSlider_4->setTickPosition(QSlider::NoTicks);
      mSlider_4->setTickInterval(1);

      gridLayout6->addWidget(mSlider_4, 1, 0, 1, 7);

      mTabWidget_4 = new QTabWidget(TabPage_ILDMM);
      mTabWidget_4->setObjectName(QString::fromUtf8("mTabWidget_4"));
      tab4 = new QWidget();
      tab4->setObjectName(QString::fromUtf8("tab4"));
      gridLayout7 = new QGridLayout(tab4);
      gridLayout7->setSpacing(6);
      gridLayout7->setMargin(11);
      gridLayout7->setObjectName(QString::fromUtf8("gridLayout7"));
      pArrayWidget_5 = new CQArrayAnnotationsWidget(tab4);
      pArrayWidget_5->setObjectName(QString::fromUtf8("pArrayWidget_5"));

      gridLayout7->addWidget(pArrayWidget_5, 0, 0, 1, 1);

      mTabWidget_4->addTab(tab4, QString());
      tab5 = new QWidget();
      tab5->setObjectName(QString::fromUtf8("tab5"));
      gridLayout8 = new QGridLayout(tab5);
      gridLayout8->setSpacing(6);
      gridLayout8->setMargin(11);
      gridLayout8->setObjectName(QString::fromUtf8("gridLayout8"));
      pArrayWidget2_5 = new CQArrayAnnotationsWidget(tab5);
      pArrayWidget2_5->setObjectName(QString::fromUtf8("pArrayWidget2_5"));

      gridLayout8->addWidget(pArrayWidget2_5, 0, 0, 1, 1);

      mTabWidget_4->addTab(tab5, QString());
      TabPage3 = new QWidget();
      TabPage3->setObjectName(QString::fromUtf8("TabPage3"));
      gridLayout9 = new QGridLayout(TabPage3);
      gridLayout9->setSpacing(6);
      gridLayout9->setMargin(11);
      gridLayout9->setObjectName(QString::fromUtf8("gridLayout9"));
      pArrayWidget3_5 = new CQArrayAnnotationsWidget(TabPage3);
      pArrayWidget3_5->setObjectName(QString::fromUtf8("pArrayWidget3_5"));

      gridLayout9->addWidget(pArrayWidget3_5, 0, 0, 1, 1);

      mTabWidget_4->addTab(TabPage3, QString());
      TabPage4 = new QWidget();
      TabPage4->setObjectName(QString::fromUtf8("TabPage4"));
      gridLayout10 = new QGridLayout(TabPage4);
      gridLayout10->setSpacing(6);
      gridLayout10->setMargin(11);
      gridLayout10->setObjectName(QString::fromUtf8("gridLayout10"));
      pArrayWidget4_5 = new CQArrayAnnotationsWidget(TabPage4);
      pArrayWidget4_5->setObjectName(QString::fromUtf8("pArrayWidget4_5"));

      gridLayout10->addWidget(pArrayWidget4_5, 0, 0, 1, 1);

      mTabWidget_4->addTab(TabPage4, QString());

      gridLayout6->addWidget(mTabWidget_4, 2, 0, 1, 7);

      tabWidget2->addTab(TabPage_ILDMM, QString());
      TabPage_CSP = new QWidget();
      TabPage_CSP->setObjectName(QString::fromUtf8("TabPage_CSP"));
      gridLayout11 = new QGridLayout(TabPage_CSP);
      gridLayout11->setSpacing(6);
      gridLayout11->setMargin(11);
      gridLayout11->setObjectName(QString::fromUtf8("gridLayout11"));
      mTabWidget_3 = new QTabWidget(TabPage_CSP);
      mTabWidget_3->setObjectName(QString::fromUtf8("mTabWidget_3"));
      tab6 = new QWidget();
      tab6->setObjectName(QString::fromUtf8("tab6"));
      gridLayout12 = new QGridLayout(tab6);
      gridLayout12->setSpacing(6);
      gridLayout12->setMargin(11);
      gridLayout12->setObjectName(QString::fromUtf8("gridLayout12"));
      pArrayWidget_3 = new CQArrayAnnotationsWidget(tab6);
      pArrayWidget_3->setObjectName(QString::fromUtf8("pArrayWidget_3"));

      gridLayout12->addWidget(pArrayWidget_3, 0, 0, 1, 1);

      mTabWidget_3->addTab(tab6, QString());
      tab7 = new QWidget();
      tab7->setObjectName(QString::fromUtf8("tab7"));
      gridLayout13 = new QGridLayout(tab7);
      gridLayout13->setSpacing(6);
      gridLayout13->setMargin(11);
      gridLayout13->setObjectName(QString::fromUtf8("gridLayout13"));
      pArrayWidget2_3 = new CQArrayAnnotationsWidget(tab7);
      pArrayWidget2_3->setObjectName(QString::fromUtf8("pArrayWidget2_3"));

      gridLayout13->addWidget(pArrayWidget2_3, 0, 0, 1, 1);

      mTabWidget_3->addTab(tab7, QString());
      TabPage5 = new QWidget();
      TabPage5->setObjectName(QString::fromUtf8("TabPage5"));
      gridLayout14 = new QGridLayout(TabPage5);
      gridLayout14->setSpacing(6);
      gridLayout14->setMargin(11);
      gridLayout14->setObjectName(QString::fromUtf8("gridLayout14"));
      pArrayWidget3_3 = new CQArrayAnnotationsWidget(TabPage5);
      pArrayWidget3_3->setObjectName(QString::fromUtf8("pArrayWidget3_3"));

      gridLayout14->addWidget(pArrayWidget3_3, 0, 0, 1, 1);

      mTabWidget_3->addTab(TabPage5, QString());
      TabPage6 = new QWidget();
      TabPage6->setObjectName(QString::fromUtf8("TabPage6"));
      gridLayout15 = new QGridLayout(TabPage6);
      gridLayout15->setSpacing(6);
      gridLayout15->setMargin(11);
      gridLayout15->setObjectName(QString::fromUtf8("gridLayout15"));
      pArrayWidget4_3 = new CQArrayAnnotationsWidget(TabPage6);
      pArrayWidget4_3->setObjectName(QString::fromUtf8("pArrayWidget4_3"));

      gridLayout15->addWidget(pArrayWidget4_3, 0, 0, 1, 1);

      mTabWidget_3->addTab(TabPage6, QString());
      TabPage7 = new QWidget();
      TabPage7->setObjectName(QString::fromUtf8("TabPage7"));
      gridLayout16 = new QGridLayout(TabPage7);
      gridLayout16->setSpacing(6);
      gridLayout16->setMargin(11);
      gridLayout16->setObjectName(QString::fromUtf8("gridLayout16"));
      pArrayWidget4_3_2 = new CQArrayAnnotationsWidget(TabPage7);
      pArrayWidget4_3_2->setObjectName(QString::fromUtf8("pArrayWidget4_3_2"));

      gridLayout16->addWidget(pArrayWidget4_3_2, 0, 0, 1, 1);

      mTabWidget_3->addTab(TabPage7, QString());

      gridLayout11->addWidget(mTabWidget_3, 2, 0, 1, 7);

      pLabel1_3 = new QLabel(TabPage_CSP);
      pLabel1_3->setObjectName(QString::fromUtf8("pLabel1_3"));
      sizePolicy4.setHeightForWidth(pLabel1_3->sizePolicy().hasHeightForWidth());
      pLabel1_3->setSizePolicy(sizePolicy4);
      pLabel1_3->setWordWrap(false);

      gridLayout11->addWidget(pLabel1_3, 0, 0, 1, 1);

      mLabel2_3 = new QLabel(TabPage_CSP);
      mLabel2_3->setObjectName(QString::fromUtf8("mLabel2_3"));
      sizePolicy3.setHeightForWidth(mLabel2_3->sizePolicy().hasHeightForWidth());
      mLabel2_3->setSizePolicy(sizePolicy3);
      mLabel2_3->setFont(font);
      mLabel2_3->setWordWrap(false);

      gridLayout11->addWidget(mLabel2_3, 0, 1, 1, 1);

      mLabel3_3 = new QLabel(TabPage_CSP);
      mLabel3_3->setObjectName(QString::fromUtf8("mLabel3_3"));
      sizePolicy4.setHeightForWidth(mLabel3_3->sizePolicy().hasHeightForWidth());
      mLabel3_3->setSizePolicy(sizePolicy4);
      mLabel3_3->setWordWrap(false);

      gridLayout11->addWidget(mLabel3_3, 0, 2, 1, 1);

      mLabel4_3 = new QLabel(TabPage_CSP);
      mLabel4_3->setObjectName(QString::fromUtf8("mLabel4_3"));
      sizePolicy3.setHeightForWidth(mLabel4_3->sizePolicy().hasHeightForWidth());
      mLabel4_3->setSizePolicy(sizePolicy3);
      mLabel4_3->setFont(font);
      mLabel4_3->setWordWrap(false);

      gridLayout11->addWidget(mLabel4_3, 0, 3, 1, 1);

      mLabel5_3 = new QLabel(TabPage_CSP);
      mLabel5_3->setObjectName(QString::fromUtf8("mLabel5_3"));
      sizePolicy4.setHeightForWidth(mLabel5_3->sizePolicy().hasHeightForWidth());
      mLabel5_3->setSizePolicy(sizePolicy4);
      mLabel5_3->setWordWrap(false);

      gridLayout11->addWidget(mLabel5_3, 0, 4, 1, 1);

      mLabel6_3 = new QLabel(TabPage_CSP);
      mLabel6_3->setObjectName(QString::fromUtf8("mLabel6_3"));
      sizePolicy3.setHeightForWidth(mLabel6_3->sizePolicy().hasHeightForWidth());
      mLabel6_3->setSizePolicy(sizePolicy3);
      mLabel6_3->setWordWrap(false);

      gridLayout11->addWidget(mLabel6_3, 0, 5, 1, 1);

      mSpacer_3 = new QSpacerItem(181, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      gridLayout11->addItem(mSpacer_3, 0, 6, 1, 1);

      mSlider_3 = new QSlider(TabPage_CSP);
      mSlider_3->setObjectName(QString::fromUtf8("mSlider_3"));
      sizePolicy2.setHeightForWidth(mSlider_3->sizePolicy().hasHeightForWidth());
      mSlider_3->setSizePolicy(sizePolicy2);
      mSlider_3->setMouseTracking(true);
      mSlider_3->setAcceptDrops(true);
      mSlider_3->setMaximum(0);
      mSlider_3->setPageStep(1);
      mSlider_3->setTracking(true);
      mSlider_3->setOrientation(Qt::Horizontal);
      mSlider_3->setTickPosition(QSlider::NoTicks);
      mSlider_3->setTickInterval(1);

      gridLayout11->addWidget(mSlider_3, 1, 0, 1, 7);

      tabWidget2->addTab(TabPage_CSP, QString());

      gridLayout->addWidget(tabWidget2, 1, 0, 1, 1);

      retranslateUi(CQTSSAResultSubWidget);
      QObject::connect(ButtonSaveData, SIGNAL(clicked()), CQTSSAResultSubWidget, SLOT(saveDataToFile()));

      QMetaObject::connectSlotsByName(CQTSSAResultSubWidget);
    } // setupUi

    void retranslateUi(QWidget *CQTSSAResultSubWidget)
    {
      CQTSSAResultSubWidget->setWindowTitle(QApplication::translate("CQTSSAResultSubWidget", "Form1", 0, QApplication::UnicodeUTF8));
      comboBox->clear();
      comboBox->insertItems(0, QStringList()
                            << QApplication::translate("CQTSSAResultSubWidget", "Concentrations", 0, QApplication::UnicodeUTF8)
                            << QApplication::translate("CQTSSAResultSubWidget", "Particle Numbers", 0, QApplication::UnicodeUTF8)
);
      ButtonSaveData->setText(QApplication::translate("CQTSSAResultSubWidget", "Save data to file", 0, QApplication::UnicodeUTF8));
      tabWidget2->setTabText(tabWidget2->indexOf(tab), QApplication::translate("CQTSSAResultSubWidget", "OptimizationResult", 0, QApplication::UnicodeUTF8));
      tabWidget2->setTabText(tabWidget2->indexOf(tab1), QApplication::translate("CQTSSAResultSubWidget", "TimeSeries", 0, QApplication::UnicodeUTF8));
      mTabWidget->setTabText(mTabWidget->indexOf(tab2), QApplication::translate("CQTSSAResultSubWidget", "Metabolites", 0, QApplication::UnicodeUTF8));
      mTabWidget->setTabText(mTabWidget->indexOf(tab3), QApplication::translate("CQTSSAResultSubWidget", "Modes", 0, QApplication::UnicodeUTF8));
      mTabWidget->setTabText(mTabWidget->indexOf(TabPage), QApplication::translate("CQTSSAResultSubWidget", "Slow space", 0, QApplication::UnicodeUTF8));
      mTabWidget->setTabText(mTabWidget->indexOf(TabPage1), QApplication::translate("CQTSSAResultSubWidget", "Fast space", 0, QApplication::UnicodeUTF8));
      mTabWidget->setTabText(mTabWidget->indexOf(TabPage2), QApplication::translate("CQTSSAResultSubWidget", "Reactions slow space", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mSlider->setProperty("toolTip", QVariant(QApplication::translate("CQTSSAResultSubWidget", "move mouse-cursor over slider and use scrollwheel to adjust required step accurately", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mSlider->setProperty("whatsThis", QVariant(QApplication::translate("CQTSSAResultSubWidget", "use slider to adjust required step", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mLabel7->setText(QString());
      pLabel1->setText(QApplication::translate("CQTSSAResultSubWidget", "ILDM operation behavior at timepoint:", 0, QApplication::UnicodeUTF8));
      mLabel2->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
      mLabel3->setText(QApplication::translate("CQTSSAResultSubWidget", "or step:", 0, QApplication::UnicodeUTF8));
      mLabel4->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
      mLabel5->setText(QApplication::translate("CQTSSAResultSubWidget", "of", 0, QApplication::UnicodeUTF8));
      mLabel6->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
      tabWidget2->setTabText(tabWidget2->indexOf(TabPage_ILDM), QApplication::translate("CQTSSAResultSubWidget", "ILDM", 0, QApplication::UnicodeUTF8));
      pLabel1_6->setText(QApplication::translate("CQTSSAResultSubWidget", "ILDM operation behavior at timepoint:", 0, QApplication::UnicodeUTF8));
      mLabel6_6->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
      mLabel4_6->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
      mLabel2_6->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
      mLabel3_6->setText(QApplication::translate("CQTSSAResultSubWidget", "or step:", 0, QApplication::UnicodeUTF8));
      mLabel5_6->setText(QApplication::translate("CQTSSAResultSubWidget", "of", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mSlider_4->setProperty("toolTip", QVariant(QApplication::translate("CQTSSAResultSubWidget", "move mouse-cursor over slider and use scrollwheel to adjust required step accurately", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mSlider_4->setProperty("whatsThis", QVariant(QApplication::translate("CQTSSAResultSubWidget", "use slider to adjust required step", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mTabWidget_4->setTabText(mTabWidget_4->indexOf(tab4), QApplication::translate("CQTSSAResultSubWidget", "Metabolites", 0, QApplication::UnicodeUTF8));
      mTabWidget_4->setTabText(mTabWidget_4->indexOf(tab5), QApplication::translate("CQTSSAResultSubWidget", "Modes", 0, QApplication::UnicodeUTF8));
      mTabWidget_4->setTabText(mTabWidget_4->indexOf(TabPage3), QApplication::translate("CQTSSAResultSubWidget", "Slow space", 0, QApplication::UnicodeUTF8));
      mTabWidget_4->setTabText(mTabWidget_4->indexOf(TabPage4), QApplication::translate("CQTSSAResultSubWidget", "Fast space", 0, QApplication::UnicodeUTF8));
      tabWidget2->setTabText(tabWidget2->indexOf(TabPage_ILDMM), QApplication::translate("CQTSSAResultSubWidget", "ILDM Modified", 0, QApplication::UnicodeUTF8));
      mTabWidget_3->setTabText(mTabWidget_3->indexOf(tab6), QApplication::translate("CQTSSAResultSubWidget", "Amplitude", 0, QApplication::UnicodeUTF8));
      mTabWidget_3->setTabText(mTabWidget_3->indexOf(tab7), QApplication::translate("CQTSSAResultSubWidget", "Radical Pointer", 0, QApplication::UnicodeUTF8));
      mTabWidget_3->setTabText(mTabWidget_3->indexOf(TabPage5), QApplication::translate("CQTSSAResultSubWidget", "Fast Reaction Pointer", 0, QApplication::UnicodeUTF8));
      mTabWidget_3->setTabText(mTabWidget_3->indexOf(TabPage6), QApplication::translate("CQTSSAResultSubWidget", "Participation Index", 0, QApplication::UnicodeUTF8));
      mTabWidget_3->setTabText(mTabWidget_3->indexOf(TabPage7), QApplication::translate("CQTSSAResultSubWidget", "Importance Index", 0, QApplication::UnicodeUTF8));
      pLabel1_3->setText(QApplication::translate("CQTSSAResultSubWidget", "CSP operation behavior at timepoint:", 0, QApplication::UnicodeUTF8));
      mLabel2_3->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
      mLabel3_3->setText(QApplication::translate("CQTSSAResultSubWidget", "or step:", 0, QApplication::UnicodeUTF8));
      mLabel4_3->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
      mLabel5_3->setText(QApplication::translate("CQTSSAResultSubWidget", "of", 0, QApplication::UnicodeUTF8));
      mLabel6_3->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mSlider_3->setProperty("toolTip", QVariant(QApplication::translate("CQTSSAResultSubWidget", "move mouse-cursor over slider and use scrollwheel to adjust required step accurately", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mSlider_3->setProperty("whatsThis", QVariant(QApplication::translate("CQTSSAResultSubWidget", "use slider to adjust required step", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      tabWidget2->setTabText(tabWidget2->indexOf(TabPage_CSP), QApplication::translate("CQTSSAResultSubWidget", "CSP", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQTSSAResultSubWidget);
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
          0xb1, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0xad, 0x94, 0x5f, 0x4c, 0x5b,
          0x55, 0x1c, 0xc7, 0x3f, 0xe7, 0xdc, 0x4b, 0x7b, 0x4b, 0xcb, 0xa0, 0x76,
          0x2d, 0x45, 0xc4, 0x31, 0x14, 0x32, 0x35, 0x99, 0xee, 0x61, 0x92, 0x60,
          0x9c, 0x51, 0xd8, 0x83, 0x89, 0x2c, 0xe0, 0x83, 0xf1, 0x71, 0x8b, 0x3e,
          0xbb, 0x18, 0x5f, 0x8d, 0xc9, 0x1e, 0x97, 0x2c, 0xf3, 0x9d, 0x2d, 0x2a,
          0x2f, 0x1a, 0xf6, 0x64, 0xb6, 0xf1, 0xe0, 0xfe, 0x38, 0x63, 0xa0, 0x71,
          0x89, 0x69, 0x70, 0x0e, 0xb0, 0xc5, 0x21, 0x42, 0xda, 0x02, 0x42, 0xa1,
          0xbd, 0x6d, 0x69, 0x6f, 0x7b, 0xcf, 0xf1, 0x01, 0x58, 0x52, 0x03, 0xce,
          0xb8, 0xfd, 0x9e, 0xce, 0x39, 0xf9, 0x9d, 0xcf, 0xf9, 0xfe, 0x7e, 0xdf,
          0x93, 0x9f, 0x88, 0xc5, 0x62, 0xec, 0x46, 0x5f, 0x5f, 0x9f, 0xe6, 0x09,
          0x44, 0x2c, 0x16, 0x13, 0x62, 0x17, 0x3c, 0x3e, 0x3e, 0xae, 0x7b, 0x7a,
          0x7a, 0xc8, 0xe7, 0xf3, 0x64, 0x32, 0x19, 0x6c, 0xdb, 0xfe, 0x4f, 0x90,
          0x7c, 0x3e, 0x4f, 0x22, 0x91, 0x20, 0x1e, 0x8f, 0xe3, 0x38, 0xce, 0xc3,
          0x73, 0x73, 0x57, 0xe9, 0xe8, 0xe8, 0x28, 0xad, 0xed, 0x1e, 0x22, 0x9d,
          0x65, 0x0e, 0x1f, 0x2d, 0x51, 0x75, 0x4b, 0x08, 0x21, 0x10, 0x12, 0x4c,
          0x13, 0xa4, 0xdc, 0x5e, 0xa3, 0x41, 0xeb, 0x9d, 0xc2, 0x84, 0xc0, 0x55,
          0x8a, 0x85, 0x3f, 0x3c, 0xe8, 0xcb, 0x06, 0x77, 0xef, 0x50, 0x0f, 0xde,
          0x7d, 0x39, 0xd2, 0x59, 0x66, 0x79, 0xe3, 0x26, 0x59, 0x7b, 0x8e, 0x9a,
          0xbb, 0x85, 0xd7, 0xa7, 0x70, 0xab, 0x16, 0xab, 0x69, 0x83, 0xec, 0x5a,
          0x05, 0xb4, 0x87, 0xa7, 0x0e, 0x36, 0xf0, 0xf4, 0xe1, 0x0a, 0xfe, 0x40,
          0x8d, 0x6a, 0x55, 0x83, 0x10, 0x98, 0x01, 0x08, 0x47, 0x8d, 0xba, 0x4a,
          0x1e, 0x82, 0x33, 0x99, 0x0c, 0x5d, 0x47, 0x4b, 0x64, 0xed, 0x39, 0xaa,
          0x3a, 0x8f, 0xe5, 0xf3, 0x31, 0x7f, 0xbf, 0x81, 0xdb, 0xd7, 0x0b, 0xcc,
          0xfe, 0xb2, 0x05, 0x94, 0x76, 0x32, 0xfd, 0x74, 0xf6, 0x58, 0x9c, 0x1c,
          0x6e, 0xa2, 0xf7, 0x0d, 0x03, 0xa5, 0x8b, 0xa0, 0xc1, 0xf2, 0xc9, 0xbd,
          0xc1, 0xb6, 0x6d, 0xe3, 0xb8, 0x25, 0x6a, 0x6e, 0x11, 0xcb, 0xe7, 0xe3,
          0xee, 0x1d, 0x18, 0x1b, 0x59, 0x01, 0x24, 0xfe, 0x26, 0x93, 0xae, 0xee,
          0x08, 0xd2, 0x23, 0xc8, 0x2c, 0x3a, 0x2c, 0x24, 0xb7, 0xb8, 0x74, 0xbe,
          0xc8, 0xf2, 0x62, 0x88, 0x77, 0x4f, 0x7b, 0xd0, 0x54, 0x50, 0x4a, 0xef,
          0x0d, 0xde, 0x6e, 0x99, 0xc0, 0xeb, 0x83, 0xf9, 0xfb, 0x26, 0x63, 0x23,
          0xcb, 0x80, 0xa2, 0x7f, 0xb0, 0x95, 0x81, 0x41, 0x83, 0x60, 0x44, 0x60,
          0x5a, 0x2e, 0xe5, 0x52, 0x33, 0x93, 0x37, 0x1c, 0xc6, 0x46, 0xfe, 0xe2,
          0xda, 0x37, 0x19, 0x5a, 0xa3, 0x5d, 0x0c, 0x0c, 0x5b, 0x48, 0x59, 0xac,
          0x03, 0xd7, 0xe9, 0x17, 0x12, 0xdc, 0xaa, 0xc5, 0xad, 0xab, 0x36, 0x50,
          0xa3, 0xff, 0x9d, 0x08, 0xef, 0x7d, 0xd8, 0x40, 0x4b, 0xb4, 0x88, 0x69,
          0xe5, 0xd9, 0x58, 0xb5, 0xb8, 0x7d, 0xad, 0xc4, 0xc9, 0xa1, 0x46, 0x4e,
          0x9f, 0x0d, 0x03, 0x26, 0xdf, 0x7e, 0xbd, 0x86, 0xbd, 0x2e, 0x31, 0x0c,
          0xb1, 0xbf, 0x62, 0xd3, 0x84, 0xd5, 0x94, 0x41, 0xf2, 0xd7, 0x0a, 0x07,
          0x0e, 0x1c, 0x60, 0xe0, 0x94, 0x89, 0x92, 0x9b, 0x98, 0x86, 0x81, 0xbd,
          0xd9, 0xcc, 0x97, 0x17, 0x0b, 0xcc, 0x4c, 0x65, 0x59, 0x5f, 0x71, 0xf8,
          0xe0, 0xe3, 0x30, 0x13, 0x37, 0xfc, 0x24, 0xa7, 0x73, 0x24, 0x67, 0x83,
          0x18, 0x75, 0xa4, 0x7f, 0x28, 0x96, 0x52, 0xb0, 0xbe, 0x5e, 0x41, 0x51,
          0xe6, 0xd0, 0x73, 0x16, 0xc1, 0xb0, 0xc0, 0x34, 0x0d, 0x8a, 0xb9, 0x20,
          0x23, 0xe7, 0x6d, 0x66, 0xa6, 0xb2, 0x84, 0x0e, 0x36, 0xd2, 0xfb, 0x7a,
          0x13, 0xfe, 0xe6, 0x32, 0x47, 0x5e, 0x6e, 0xdc, 0x36, 0x7e, 0xa9, 0x8a,
          0x90, 0xfb, 0x98, 0xb7, 0xdd, 0x63, 0x10, 0xca, 0x03, 0x28, 0xa4, 0x47,
          0x61, 0x58, 0x2e, 0x1b, 0xab, 0x41, 0xbe, 0xfa, 0xbc, 0xc0, 0xec, 0x94,
          0x0d, 0x28, 0xbc, 0x5e, 0x93, 0xb6, 0x8e, 0x06, 0x4c, 0xab, 0x84, 0xe1,
          0xd9, 0xbe, 0xae, 0xb4, 0x89, 0x34, 0xea, 0xc1, 0xf5, 0x3b, 0x01, 0xc1,
          0xb0, 0x00, 0xfc, 0xa4, 0x96, 0xaa, 0x54, 0xb6, 0x1a, 0x99, 0xfc, 0xde,
          0x61, 0x66, 0x2a, 0x4b, 0x4b, 0x4b, 0x23, 0xd1, 0x68, 0x0b, 0xe9, 0xd4,
          0x26, 0x17, 0x3e, 0x4d, 0xf3, 0x60, 0x2a, 0x48, 0xea, 0x41, 0x19, 0x89,
          0xa4, 0xfd, 0x59, 0x0f, 0x52, 0xa8, 0xfd, 0x15, 0x6b, 0x05, 0xed, 0x9d,
          0x35, 0x0e, 0x3d, 0xef, 0xe3, 0xcf, 0xdf, 0x4b, 0x4c, 0x7c, 0xe7, 0x70,
          0xea, 0x7d, 0x3f, 0xb9, 0xf5, 0x20, 0xaf, 0xbe, 0x16, 0x20, 0xda, 0xee,
          0xe5, 0xc2, 0x67, 0x35, 0xd2, 0x0b, 0x9b, 0x9c, 0xfb, 0x68, 0x11, 0xa7,
          0x54, 0xa4, 0x39, 0xe4, 0xe5, 0xc5, 0x63, 0x9a, 0x4c, 0xaa, 0x1e, 0x5c,
          0xaf, 0x58, 0x6b, 0xfc, 0x01, 0x97, 0xb7, 0x87, 0x02, 0x00, 0x5c, 0xb9,
          0xb4, 0xca, 0xe4, 0xcd, 0x32, 0x67, 0xce, 0x86, 0x38, 0xfe, 0x96, 0x4b,
          0xd7, 0x2b, 0x39, 0x3e, 0x39, 0xd7, 0x49, 0x28, 0xd2, 0x42, 0x61, 0x73,
          0x03, 0xa7, 0x56, 0xa3, 0x7f, 0x28, 0x44, 0x47, 0x77, 0x0d, 0xcd, 0xbf,
          0xfc, 0x63, 0x84, 0xa0, 0x5a, 0x85, 0xde, 0x13, 0x06, 0xe9, 0xa5, 0x20,
          0x57, 0xc7, 0x52, 0x7c, 0x71, 0x31, 0xc3, 0xc4, 0x2d, 0x3f, 0x47, 0x5e,
          0xb2, 0x30, 0x3c, 0x82, 0xd4, 0xfc, 0x32, 0x76, 0xd6, 0x81, 0x1d, 0xb3,
          0x7e, 0xfe, 0xb1, 0x48, 0x72, 0x30, 0x82, 0xd9, 0xb0, 0x8f, 0x79, 0xf9,
          0x7c, 0x1e, 0x57, 0x29, 0x10, 0x9a, 0x9a, 0x28, 0x30, 0x7c, 0xc6, 0x22,
          0xd2, 0xd6, 0xcd, 0xf5, 0x2b, 0x2b, 0x24, 0xef, 0xe5, 0x48, 0xde, 0xdb,
          0x00, 0x14, 0x20, 0x09, 0x86, 0x2c, 0xfa, 0x87, 0x9e, 0xe1, 0xa7, 0x1f,
          0x6c, 0xec, 0x92, 0x83, 0x53, 0x51, 0x14, 0x72, 0xfb, 0xf4, 0x38, 0x91,
          0x48, 0xb0, 0xb0, 0xe0, 0xc1, 0x08, 0x08, 0x14, 0x12, 0x45, 0x8d, 0xfe,
          0x21, 0xc9, 0xf1, 0x13, 0x51, 0xe6, 0x7e, 0x73, 0x58, 0x59, 0x54, 0x68,
          0x24, 0x6d, 0x1d, 0x1e, 0x5e, 0x38, 0xa6, 0xe9, 0xe8, 0x51, 0xbc, 0x39,
          0xd8, 0x4a, 0xb5, 0x02, 0xa6, 0x69, 0x33, 0x1d, 0xaf, 0xec, 0x0d, 0x8e,
          0xc7, 0xe3, 0xe8, 0xcb, 0x06, 0xe1, 0xa8, 0x81, 0xd7, 0x27, 0xd1, 0xae,
          0x40, 0x18, 0x0a, 0x43, 0x4a, 0x8c, 0x9d, 0xb1, 0x29, 0xa5, 0x41, 0x26,
          0xad, 0x48, 0xa7, 0x35, 0x8c, 0x2b, 0x4c, 0x53, 0x52, 0xc8, 0xc3, 0x74,
          0xbc, 0xcc, 0xda, 0xb2, 0xbb, 0x37, 0xd8, 0x71, 0x9c, 0xba, 0x79, 0xfa,
          0xb8, 0x21, 0x1f, 0x9d, 0xf2, 0x18, 0xe0, 0x58, 0x2c, 0x26, 0x1e, 0x95,
          0xf8, 0xbf, 0xc0, 0x4f, 0x1a, 0x1e, 0x8b, 0xc5, 0xc4, 0xdf, 0xe0, 0xa1,
          0x90, 0x17, 0x2a, 0xf6, 0xa9, 0x69, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
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
  class CQTSSAResultSubWidget: public Ui_CQTSSAResultSubWidget {};
} // namespace Ui

class CQTSSAResultSubWidget : public QWidget, public Ui::CQTSSAResultSubWidget
  {
    Q_OBJECT

  public:
    CQTSSAResultSubWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    ~CQTSSAResultSubWidget();

    void displayOptimizationTab(bool displayOptTab);
    void setStepNumber();
    void discardOldResults();
    void setStepSelectionDisabled(bool set);
    void activateTab(int tab);
    void changeToCSP();
    void changeToILDM();
    virtual void changeToILDMModified();
    void displayCSPDevelopment(bool displayCSPTab);

  public slots:
    virtual CTimeSeriesTable * table();
    void changeILDMInterval();
    void changeCSPInterval();
    void hideButtons();
    virtual void changeILDMModifiedInterval();

  protected slots:
    virtual void languageChange();

    void saveDataToFile();
    void toggleView();
    virtual void init();
  };

#endif // CQTSSARESULTSUBWIDGET_H
