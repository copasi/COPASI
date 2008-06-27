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
 ** Form implementation generated from reading ui file 'TimeSeriesSubwidget.ui'
 **
 ** Created: Fri Jun 27 10:20:01 2008
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "TimeSeriesSubwidget.h"

#include <qvariant.h>
#include <qregexp.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CTimeSeriesTable.h"
#include "qmessagebox.h"
#include "qfiledialog.h"
#include "TimeSeriesSubwidget.ui.h"

/*
 *  Constructs a TimeSeriesSubWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
TimeSeriesSubWidget::TimeSeriesSubWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("TimeSeriesSubWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, sizePolicy().hasHeightForWidth()));
  TimeSeriesSubWidgetLayout = new QVBoxLayout(this, 11, 6, "TimeSeriesSubWidgetLayout");

  tabWidget2 = new QTabWidget(this, "tabWidget2");

  tab = new QWidget(tabWidget2, "tab");

  optimizationResultText = new QTextEdit(tab, "optimizationResultText");
  optimizationResultText->setGeometry(QRect(11, 11, 552, 278));
  optimizationResultText->setReadOnly(TRUE);
  tabWidget2->insertTab(tab, QString::fromLatin1(""));

  tab_2 = new QWidget(tabWidget2, "tab_2");
  tabLayout = new QVBoxLayout(tab_2, 11, 6, "tabLayout");

  dataTable = new CTimeSeriesTable(tab_2, "dataTable");
  tabLayout->addWidget(dataTable);
  tabWidget2->insertTab(tab_2, QString::fromLatin1(""));
  TimeSeriesSubWidgetLayout->addWidget(tabWidget2);

  layout16 = new QHBoxLayout(0, 0, 6, "layout16");
  spacer = new QSpacerItem(300, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout16->addItem(spacer);

  ButtonSaveData = new QPushButton(this, "ButtonSaveData");
  ButtonSaveData->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, ButtonSaveData->sizePolicy().hasHeightForWidth()));
  layout16->addWidget(ButtonSaveData);

  mpBtnPrintAsImage = new QPushButton(this, "mpBtnPrintAsImage");
  layout16->addWidget(mpBtnPrintAsImage);
  TimeSeriesSubWidgetLayout->addLayout(layout16);
  languageChange();
  resize(QSize(600, 382).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(ButtonSaveData, SIGNAL(clicked()), this, SLOT(saveDataToFile()));
  connect(mpBtnPrintAsImage, SIGNAL(clicked()), this, SLOT(printTableAsImage()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TimeSeriesSubWidget::~TimeSeriesSubWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void TimeSeriesSubWidget::languageChange()
{
  setCaption(tr("TimeSeries Result Window"));
  tabWidget2->changeTab(tab, tr("OptimizationResult"));
  tabWidget2->changeTab(tab_2, tr("TimeSeries"));
  ButtonSaveData->setText(tr("Save data to file"));
  mpBtnPrintAsImage->setText(tr("Print as image"));
}
