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
 ** Form implementation generated from reading ui file 'CMCAResultSubwidget.ui'
 **
 ** Created: Mon Apr 16 10:28:14 2007
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
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

  mSaveButton = new QPushButton(this, "mSaveButton");
  mSaveButton->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, mSaveButton->sizePolicy().hasHeightForWidth()));
  layout3->addWidget(mSaveButton);
  CMCAResultSubwidgetLayout->addLayout(layout3);

  mTabWidget = new QTabWidget(this, "mTabWidget");

  tab = new QWidget(mTabWidget, "tab");
  tabLayout = new QHBoxLayout(tab, 0, 6, "tabLayout");

  mpArrayElasticities = new CQArrayAnnotationsWidget(tab, "mpArrayElasticities");
  tabLayout->addWidget(mpArrayElasticities);
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
  languageChange();
  resize(QSize(580, 422).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mComboScale, SIGNAL(activated(int)), this, SLOT(slotScaled()));
  connect(mSaveButton, SIGNAL(clicked()), this, SLOT(slotSave()));
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
  setCaption(tr("Form1"));
  mTopLabel->setText(QString::null);
  mComboScale->clear();
  mComboScale->insertItem(tr("scaled"));
  mComboScale->insertItem(tr("unscaled"));
  mSaveButton->setText(tr("Save data to file"));
  mTabWidget->changeTab(tab, tr("Elasticities"));
  mTabWidget->changeTab(tab_2, tr("Flux Control Coefficients"));
  mTabWidget->changeTab(TabPage, tr("Concentration Control Coefficients"));
}
