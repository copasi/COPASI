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
 ** Form implementation generated from reading ui file 'CQMoietiesTaskResult.ui'
 **
 ** Created: Fri Jun 27 13:46:44 2008
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQMoietiesTaskResult.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qtabwidget.h>
#include <qtable.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQMoietiesTaskResult.ui.h"

/*
 *  Constructs a CQMoietiesTaskResult which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMoietiesTaskResult::CQMoietiesTaskResult(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  if (!name)
    setName("CQMoietiesTaskResult");
  CQMoietiesTaskResultLayout = new QVBoxLayout(this, 11, 6, "CQMoietiesTaskResultLayout");

  mpLblResult = new QLabel(this, "mpLblResult");
  CQMoietiesTaskResultLayout->addWidget(mpLblResult);

  mpTabWidget = new QTabWidget(this, "mpTabWidget");
  mpTabWidget->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)2, (QSizePolicy::SizeType)5, 0, 0, mpTabWidget->sizePolicy().hasHeightForWidth()));
  mpTabWidget->setMinimumSize(QSize(210, 180));

  mpMoieties = new QTable(mpTabWidget, "mpMoieties");
  mpTabWidget->insertTab(mpMoieties, QString::fromLatin1(""));

  mpStoichiometry = new CQArrayAnnotationsWidget(mpTabWidget, "mpStoichiometry");
  mpTabWidget->insertTab(mpStoichiometry, QString::fromLatin1(""));

  mpLinkMatrix = new CQArrayAnnotationsWidget(mpTabWidget, "mpLinkMatrix");
  mpTabWidget->insertTab(mpLinkMatrix, QString::fromLatin1(""));

  mpReducedStoichiometry = new CQArrayAnnotationsWidget(mpTabWidget, "mpReducedStoichiometry");
  mpTabWidget->insertTab(mpReducedStoichiometry, QString::fromLatin1(""));
  CQMoietiesTaskResultLayout->addWidget(mpTabWidget);

  layout3 = new QHBoxLayout(0, 0, 6, "layout3");
  spacer3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout3->addItem(spacer3);

  mpBtnSave = new QPushButton(this, "mpBtnSave");
  layout3->addWidget(mpBtnSave);

  mpBtnPrintAsImage = new QPushButton(this, "mpBtnPrintAsImage");
  layout3->addWidget(mpBtnPrintAsImage);
  CQMoietiesTaskResultLayout->addLayout(layout3);
  languageChange();
  resize(QSize(433, 265).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnSave, SIGNAL(clicked()), this, SLOT(slotSave()));
  connect(mpBtnPrintAsImage, SIGNAL(clicked()), this, SLOT(printAsImage()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMoietiesTaskResult::~CQMoietiesTaskResult()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMoietiesTaskResult::languageChange()
{
  setCaption(tr("Moieties Result"));
  mpLblResult->setText(tr("<h2>Moieties Result</h2>"));
  mpTabWidget->changeTab(mpMoieties, tr("Moieties"));
  mpTabWidget->changeTab(mpStoichiometry, tr("Stoichiometry"));
  mpTabWidget->changeTab(mpLinkMatrix, tr("Link Matrix"));
  mpTabWidget->changeTab(mpReducedStoichiometry, tr("Reduced Stoichiometry"));
  mpBtnSave->setText(tr("Save data to file"));
  mpBtnPrintAsImage->setText(tr("Print as image"));
}
