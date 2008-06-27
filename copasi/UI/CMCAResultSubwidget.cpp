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
 ** Form implementation generated from reading ui file 'CMCAResultSubwidget.ui'
 **
 ** Created: Fri Jun 27 10:54:34 2008
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CMCAResultSubwidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qtabwidget.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQArrayAnnotationsWidget.h"
#include "CMCAResultSubwidget.ui.h"

/*
 *  Constructs a CMCAResultSubwidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CMCAResultSubwidget::CMCAResultSubwidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CMCAResultSubwidget");
  CMCAResultSubwidgetLayout = new QVBoxLayout(this, 11, 6, "CMCAResultSubwidgetLayout");

  layout3 = new QHBoxLayout(0, 0, 6, "layout3");

  mTopLabel = new QLabel(this, "mTopLabel");
  layout3->addWidget(mTopLabel);

  mComboScale = new QComboBox(FALSE, this, "mComboScale");
  mComboScale->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, mComboScale->sizePolicy().hasHeightForWidth()));
  layout3->addWidget(mComboScale);
  CMCAResultSubwidgetLayout->addLayout(layout3);

  mTabWidget = new QTabWidget(this, "mTabWidget");

  tab = new QWidget(mTabWidget, "tab");
  tabLayout = new QGridLayout(tab, 1, 1, 0, 6, "tabLayout");

  mpArrayElasticities = new CQArrayAnnotationsWidget(tab, "mpArrayElasticities");

  tabLayout->addWidget(mpArrayElasticities, 0, 0);
  mTabWidget->insertTab(tab, QString::fromLatin1(""));

  tab_2 = new QWidget(mTabWidget, "tab_2");
  tabLayout_2 = new QGridLayout(tab_2, 1, 1, 0, 6, "tabLayout_2");

  mpArrayFCC = new CQArrayAnnotationsWidget(tab_2, "mpArrayFCC");

  tabLayout_2->addWidget(mpArrayFCC, 0, 0);
  mTabWidget->insertTab(tab_2, QString::fromLatin1(""));

  TabPage = new QWidget(mTabWidget, "TabPage");
  TabPageLayout = new QGridLayout(TabPage, 1, 1, 0, 6, "TabPageLayout");

  mpArrayCCC = new CQArrayAnnotationsWidget(TabPage, "mpArrayCCC");

  TabPageLayout->addWidget(mpArrayCCC, 0, 0);
  mTabWidget->insertTab(TabPage, QString::fromLatin1(""));
  CMCAResultSubwidgetLayout->addWidget(mTabWidget);

  layout13 = new QHBoxLayout(0, 0, 6, "layout13");
  spacer10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout13->addItem(spacer10);

  mSaveButton = new QPushButton(this, "mSaveButton");
  layout13->addWidget(mSaveButton);

  mpBtnPrintAsImage = new QPushButton(this, "mpBtnPrintAsImage");
  layout13->addWidget(mpBtnPrintAsImage);
  CMCAResultSubwidgetLayout->addLayout(layout13);
  languageChange();
  resize(QSize(580, 422).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mComboScale, SIGNAL(activated(int)), this, SLOT(slotScaled()));
  connect(mSaveButton, SIGNAL(clicked()), this, SLOT(slotSave()));
  connect(mpBtnPrintAsImage, SIGNAL(clicked()), this, SLOT(printAsImage()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CMCAResultSubwidget::~CMCAResultSubwidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CMCAResultSubwidget::languageChange()
{
  setCaption(tr("MCA Result Window"));
  mTopLabel->setText(QString::null);
  mComboScale->clear();
  mComboScale->insertItem(tr("scaled"));
  mComboScale->insertItem(tr("unscaled"));
  mTabWidget->changeTab(tab, tr("Elasticities"));
  mTabWidget->changeTab(tab_2, tr("Flux Control Coefficients"));
  mTabWidget->changeTab(TabPage, tr("Concentration Control Coefficients"));
  mSaveButton->setText(tr("Save data to file"));
  mpBtnPrintAsImage->setText(tr("Print as image"));
}
