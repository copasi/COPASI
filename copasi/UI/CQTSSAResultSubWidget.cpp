// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 01:53:45 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQTSSAResultSubWidget.ui'
 **
 ** Created: Thu May 29 10:23:56 2008
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQTSSAResultSubWidget.h"

#include <qvariant.h>
#include <qregexp.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qtabwidget.h>
#include <qtextedit.h>
#include <qslider.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CTimeSeriesTable.h"
#include "CQArrayAnnotationsWidget.h"
#include "qmessagebox.h"
#include "qfiledialog.h"
#include "CQTSSAResultSubWidget.ui.h"

/*
 *  Constructs a CQTSSAResultSubWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQTSSAResultSubWidget::CQTSSAResultSubWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CQTSSAResultSubWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, sizePolicy().hasHeightForWidth()));
  CQTSSAResultSubWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "CQTSSAResultSubWidgetLayout");

  toplayout = new QHBoxLayout(0, 1, 1, "toplayout");

  comboBox = new QComboBox(FALSE, this, "comboBox");
  comboBox->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, comboBox->sizePolicy().hasHeightForWidth()));
  toplayout->addWidget(comboBox);
  spacer = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  toplayout->addItem(spacer);

  ButtonSaveData = new QPushButton(this, "ButtonSaveData");
  ButtonSaveData->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, ButtonSaveData->sizePolicy().hasHeightForWidth()));
  toplayout->addWidget(ButtonSaveData);

  CQTSSAResultSubWidgetLayout->addLayout(toplayout, 0, 0);

  tabWidget2 = new QTabWidget(this, "tabWidget2");
  tabWidget2->setMargin(1);

  tab = new QWidget(tabWidget2, "tab");
  tabLayout = new QVBoxLayout(tab, 11, 6, "tabLayout");

  optimizationResultText = new QTextEdit(tab, "optimizationResultText");
  optimizationResultText->setReadOnly(TRUE);
  tabLayout->addWidget(optimizationResultText);
  tabWidget2->insertTab(tab, QString::fromLatin1(""));

  tab_2 = new QWidget(tabWidget2, "tab_2");
  tabLayout_2 = new QVBoxLayout(tab_2, 11, 6, "tabLayout_2");

  dataTable = new CTimeSeriesTable(tab_2, "dataTable");
  tabLayout_2->addWidget(dataTable);
  tabWidget2->insertTab(tab_2, QString::fromLatin1(""));

  TabPage = new QWidget(tabWidget2, "TabPage");
  TabPageLayout = new QGridLayout(TabPage, 1, 1, 11, 6, "TabPageLayout");

  mTabWidget = new QTabWidget(TabPage, "mTabWidget");
  mTabWidget->setMargin(0);

  tab_3 = new QWidget(mTabWidget, "tab_3");
  tabLayout_3 = new QGridLayout(tab_3, 1, 1, 11, 6, "tabLayout_3");

  pArrayWidget = new CQArrayAnnotationsWidget(tab_3, "pArrayWidget");

  tabLayout_3->addWidget(pArrayWidget, 0, 0);
  mTabWidget->insertTab(tab_3, QString::fromLatin1(""));

  tab_4 = new QWidget(mTabWidget, "tab_4");
  tabLayout_4 = new QGridLayout(tab_4, 1, 1, 11, 6, "tabLayout_4");

  pArrayWidget2 = new CQArrayAnnotationsWidget(tab_4, "pArrayWidget2");

  tabLayout_4->addWidget(pArrayWidget2, 0, 0);
  mTabWidget->insertTab(tab_4, QString::fromLatin1(""));

  TabPage_2 = new QWidget(mTabWidget, "TabPage_2");
  TabPageLayout_2 = new QGridLayout(TabPage_2, 1, 1, 11, 6, "TabPageLayout_2");

  pArrayWidget3 = new CQArrayAnnotationsWidget(TabPage_2, "pArrayWidget3");

  TabPageLayout_2->addWidget(pArrayWidget3, 0, 0);
  mTabWidget->insertTab(TabPage_2, QString::fromLatin1(""));

  TabPage_3 = new QWidget(mTabWidget, "TabPage_3");
  TabPageLayout_3 = new QGridLayout(TabPage_3, 1, 1, 11, 6, "TabPageLayout_3");

  pArrayWidget4 = new CQArrayAnnotationsWidget(TabPage_3, "pArrayWidget4");

  TabPageLayout_3->addWidget(pArrayWidget4, 0, 0);
  mTabWidget->insertTab(TabPage_3, QString::fromLatin1(""));

  TabPageLayout->addMultiCellWidget(mTabWidget, 2, 2, 0, 7);

  mSlider = new QSlider(TabPage, "mSlider");
  mSlider->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)1, 0, 0, mSlider->sizePolicy().hasHeightForWidth()));
  mSlider->setMouseTracking(TRUE);
  mSlider->setAcceptDrops(TRUE);
  mSlider->setMaxValue(0);
  mSlider->setPageStep(1);
  mSlider->setTracking(TRUE);
  mSlider->setOrientation(QSlider::Horizontal);
  mSlider->setTickmarks(QSlider::NoMarks);
  mSlider->setTickInterval(1);

  TabPageLayout->addMultiCellWidget(mSlider, 1, 1, 0, 7);
  mSpacer = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  TabPageLayout->addItem(mSpacer, 0, 7);

  mLabel7 = new QLabel(TabPage, "mLabel7");
  mLabel7->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mLabel7->sizePolicy().hasHeightForWidth()));

  TabPageLayout->addWidget(mLabel7, 0, 2);

  pLabel1 = new QLabel(TabPage, "pLabel1");
  pLabel1->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, pLabel1->sizePolicy().hasHeightForWidth()));

  TabPageLayout->addWidget(pLabel1, 0, 0);

  mLabel2 = new QLabel(TabPage, "mLabel2");
  mLabel2->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mLabel2->sizePolicy().hasHeightForWidth()));
  QFont mLabel2_font(mLabel2->font());
  mLabel2_font.setBold(TRUE);
  mLabel2->setFont(mLabel2_font);

  TabPageLayout->addWidget(mLabel2, 0, 1);

  mLabel3 = new QLabel(TabPage, "mLabel3");
  mLabel3->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, mLabel3->sizePolicy().hasHeightForWidth()));

  TabPageLayout->addWidget(mLabel3, 0, 3);

  mLabel4 = new QLabel(TabPage, "mLabel4");
  mLabel4->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mLabel4->sizePolicy().hasHeightForWidth()));
  QFont mLabel4_font(mLabel4->font());
  mLabel4_font.setBold(TRUE);
  mLabel4->setFont(mLabel4_font);

  TabPageLayout->addWidget(mLabel4, 0, 4);

  mLabel5 = new QLabel(TabPage, "mLabel5");
  mLabel5->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, mLabel5->sizePolicy().hasHeightForWidth()));

  TabPageLayout->addWidget(mLabel5, 0, 5);

  mLabel6 = new QLabel(TabPage, "mLabel6");
  mLabel6->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mLabel6->sizePolicy().hasHeightForWidth()));

  TabPageLayout->addWidget(mLabel6, 0, 6);
  tabWidget2->insertTab(TabPage, QString::fromLatin1(""));

  TabPage_4 = new QWidget(tabWidget2, "TabPage_4");
  TabPageLayout_4 = new QGridLayout(TabPage_4, 1, 1, 11, 6, "TabPageLayout_4");

  mTabWidget_3 = new QTabWidget(TabPage_4, "mTabWidget_3");
  mTabWidget_3->setMargin(0);

  tab_5 = new QWidget(mTabWidget_3, "tab_5");
  tabLayout_5 = new QGridLayout(tab_5, 1, 1, 11, 6, "tabLayout_5");

  pArrayWidget_3 = new CQArrayAnnotationsWidget(tab_5, "pArrayWidget_3");

  tabLayout_5->addWidget(pArrayWidget_3, 0, 0);
  mTabWidget_3->insertTab(tab_5, QString::fromLatin1(""));

  tab_6 = new QWidget(mTabWidget_3, "tab_6");
  tabLayout_6 = new QGridLayout(tab_6, 1, 1, 11, 6, "tabLayout_6");

  pArrayWidget2_3 = new CQArrayAnnotationsWidget(tab_6, "pArrayWidget2_3");

  tabLayout_6->addWidget(pArrayWidget2_3, 0, 0);
  mTabWidget_3->insertTab(tab_6, QString::fromLatin1(""));

  TabPage_5 = new QWidget(mTabWidget_3, "TabPage_5");
  TabPageLayout_5 = new QGridLayout(TabPage_5, 1, 1, 11, 6, "TabPageLayout_5");

  pArrayWidget3_3 = new CQArrayAnnotationsWidget(TabPage_5, "pArrayWidget3_3");

  TabPageLayout_5->addWidget(pArrayWidget3_3, 0, 0);
  mTabWidget_3->insertTab(TabPage_5, QString::fromLatin1(""));

  TabPage_6 = new QWidget(mTabWidget_3, "TabPage_6");
  TabPageLayout_6 = new QGridLayout(TabPage_6, 1, 1, 11, 6, "TabPageLayout_6");

  pArrayWidget4_3 = new CQArrayAnnotationsWidget(TabPage_6, "pArrayWidget4_3");

  TabPageLayout_6->addWidget(pArrayWidget4_3, 0, 0);
  mTabWidget_3->insertTab(TabPage_6, QString::fromLatin1(""));

  TabPage_7 = new QWidget(mTabWidget_3, "TabPage_7");
  TabPageLayout_7 = new QGridLayout(TabPage_7, 1, 1, 11, 6, "TabPageLayout_7");

  pArrayWidget4_3_2 = new CQArrayAnnotationsWidget(TabPage_7, "pArrayWidget4_3_2");

  TabPageLayout_7->addWidget(pArrayWidget4_3_2, 0, 0);
  mTabWidget_3->insertTab(TabPage_7, QString::fromLatin1(""));

  TabPageLayout_4->addMultiCellWidget(mTabWidget_3, 2, 2, 0, 6);

  pLabel1_3 = new QLabel(TabPage_4, "pLabel1_3");
  pLabel1_3->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, pLabel1_3->sizePolicy().hasHeightForWidth()));

  TabPageLayout_4->addWidget(pLabel1_3, 0, 0);

  mLabel2_3 = new QLabel(TabPage_4, "mLabel2_3");
  mLabel2_3->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mLabel2_3->sizePolicy().hasHeightForWidth()));
  QFont mLabel2_3_font(mLabel2_3->font());
  mLabel2_3_font.setBold(TRUE);
  mLabel2_3->setFont(mLabel2_3_font);

  TabPageLayout_4->addWidget(mLabel2_3, 0, 1);

  mLabel3_3 = new QLabel(TabPage_4, "mLabel3_3");
  mLabel3_3->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, mLabel3_3->sizePolicy().hasHeightForWidth()));

  TabPageLayout_4->addWidget(mLabel3_3, 0, 2);

  mLabel4_3 = new QLabel(TabPage_4, "mLabel4_3");
  mLabel4_3->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mLabel4_3->sizePolicy().hasHeightForWidth()));
  QFont mLabel4_3_font(mLabel4_3->font());
  mLabel4_3_font.setBold(TRUE);
  mLabel4_3->setFont(mLabel4_3_font);

  TabPageLayout_4->addWidget(mLabel4_3, 0, 3);

  mLabel5_3 = new QLabel(TabPage_4, "mLabel5_3");
  mLabel5_3->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, mLabel5_3->sizePolicy().hasHeightForWidth()));

  TabPageLayout_4->addWidget(mLabel5_3, 0, 4);

  mLabel6_3 = new QLabel(TabPage_4, "mLabel6_3");
  mLabel6_3->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mLabel6_3->sizePolicy().hasHeightForWidth()));

  TabPageLayout_4->addWidget(mLabel6_3, 0, 5);
  mSpacer_3 = new QSpacerItem(181, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  TabPageLayout_4->addItem(mSpacer_3, 0, 6);

  mSlider_3 = new QSlider(TabPage_4, "mSlider_3");
  mSlider_3->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)1, 0, 0, mSlider_3->sizePolicy().hasHeightForWidth()));
  mSlider_3->setMouseTracking(TRUE);
  mSlider_3->setAcceptDrops(TRUE);
  mSlider_3->setMaxValue(0);
  mSlider_3->setPageStep(1);
  mSlider_3->setTracking(TRUE);
  mSlider_3->setOrientation(QSlider::Horizontal);
  mSlider_3->setTickmarks(QSlider::NoMarks);
  mSlider_3->setTickInterval(1);

  TabPageLayout_4->addMultiCellWidget(mSlider_3, 1, 1, 0, 6);
  tabWidget2->insertTab(TabPage_4, QString::fromLatin1(""));

  CQTSSAResultSubWidgetLayout->addWidget(tabWidget2, 1, 0);
  languageChange();
  resize(QSize(725, 411).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(ButtonSaveData, SIGNAL(clicked()), this, SLOT(saveDataToFile()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTSSAResultSubWidget::~CQTSSAResultSubWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQTSSAResultSubWidget::languageChange()
{
  setCaption(tr("Form1"));
  comboBox->clear();
  comboBox->insertItem(tr("Concentrations"));
  comboBox->insertItem(tr("Particle Numbers"));
  ButtonSaveData->setText(tr("Save data to file"));
  tabWidget2->changeTab(tab, tr("OptimizationResult"));
  tabWidget2->changeTab(tab_2, tr("TimeSeries"));
  mTabWidget->changeTab(tab_3, tr("Metabolites"));
  mTabWidget->changeTab(tab_4, tr("Modes"));
  mTabWidget->changeTab(TabPage_2, tr("Slow space"));
  mTabWidget->changeTab(TabPage_3, tr("Fast space"));
  QToolTip::add(mSlider, tr("move mouse-cursor over slider and use scrollwheel to adjust required step accurately"));
  QWhatsThis::add(mSlider, tr("use slider to adjust required step"));
  mLabel7->setText(QString::null);
  pLabel1->setText(tr("ILDM operation behavior at timepoint:"));
  mLabel2->setText(tr("0"));
  mLabel3->setText(tr("or step:"));
  mLabel4->setText(tr("0"));
  mLabel5->setText(tr("of"));
  mLabel6->setText(tr("0"));
  tabWidget2->changeTab(TabPage, tr("ILDM"));
  mTabWidget_3->changeTab(tab_5, tr("Amplitude"));
  mTabWidget_3->changeTab(tab_6, tr("Radical Pointer"));
  mTabWidget_3->changeTab(TabPage_5, tr("Fast Reaction Pointer"));
  mTabWidget_3->changeTab(TabPage_6, tr("Participation Index"));
  mTabWidget_3->changeTab(TabPage_7, tr("Importance Index"));
  pLabel1_3->setText(tr("CSP operation behavior at timepoint:"));
  mLabel2_3->setText(tr("0"));
  mLabel3_3->setText(tr("or step:"));
  mLabel4_3->setText(tr("0"));
  mLabel5_3->setText(tr("of"));
  mLabel6_3->setText(tr("0"));
  QToolTip::add(mSlider_3, tr("move mouse-cursor over slider and use scrollwheel to adjust required step accurately"));
  QWhatsThis::add(mSlider_3, tr("use slider to adjust required step"));
  tabWidget2->changeTab(TabPage_4, tr("CSP"));
}
