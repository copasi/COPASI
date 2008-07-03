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
 ** Created: Thu Jul 3 09:08:53 2008
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQMoietiesTaskResult.h"

#include <qvariant.h>
#include <qtabwidget.h>
#include <qtable.h>
#include <qlabel.h>
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
  CQMoietiesTaskResultLayout = new QGridLayout(this, 1, 1, 11, 6, "CQMoietiesTaskResultLayout");

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

  CQMoietiesTaskResultLayout->addMultiCellWidget(mpTabWidget, 1, 1, 0, 1);

  mpLblResult = new QLabel(this, "mpLblResult");
  mpLblResult->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpLblResult->sizePolicy().hasHeightForWidth()));

  CQMoietiesTaskResultLayout->addWidget(mpLblResult, 0, 0);

  mpBtnSave = new QPushButton(this, "mpBtnSave");

  CQMoietiesTaskResultLayout->addWidget(mpBtnSave, 0, 1);
  languageChange();
  resize(QSize(337, 237).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnSave, SIGNAL(clicked()), this, SLOT(slotSave()));
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
  mpTabWidget->changeTab(mpMoieties, tr("Moieties"));
  mpTabWidget->changeTab(mpStoichiometry, tr("Stoichiometry"));
  mpTabWidget->changeTab(mpLinkMatrix, tr("Link Matrix"));
  mpTabWidget->changeTab(mpReducedStoichiometry, tr("Reduced Stoichiometry"));
  mpLblResult->setText(tr("<h2>Moieties Result</h2>"));
  mpBtnSave->setText(tr("save data"));
}
