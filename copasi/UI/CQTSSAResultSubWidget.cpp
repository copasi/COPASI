// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/01/12 14:07:01 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQTSSAResultSubWidget.ui'
 **
 ** Created: Tue May 15 09:22:46 2007
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
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
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "ctimeseriestable.h"
#include "qmessagebox.h"
#include "qfiledialog.h"
#include "CTimeSeriesTable.h"
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
  CQTSSAResultSubWidgetLayout = new QVBoxLayout(this, 11, 6, "CQTSSAResultSubWidgetLayout");

  toplayout = new QHBoxLayout(0, 1, 1, "toplayout");

  comboBox = new QComboBox(FALSE, this, "comboBox");
  comboBox->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, comboBox->sizePolicy().hasHeightForWidth()));
  toplayout->addWidget(comboBox);
  spacer = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  toplayout->addItem(spacer);

  ButtonSaveData = new QPushButton(this, "ButtonSaveData");
  ButtonSaveData->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, ButtonSaveData->sizePolicy().hasHeightForWidth()));
  toplayout->addWidget(ButtonSaveData);
  CQTSSAResultSubWidgetLayout->addLayout(toplayout);

  tabWidget2 = new QTabWidget(this, "tabWidget2");

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
  CQTSSAResultSubWidgetLayout->addWidget(tabWidget2);
  languageChange();
  resize(QSize(600, 382).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(ButtonSaveData, SIGNAL(clicked()), this, SLOT(saveDataToFile()));
  connect(comboBox, SIGNAL(activated(const QString&)), this, SLOT(toggleView()));
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
}
