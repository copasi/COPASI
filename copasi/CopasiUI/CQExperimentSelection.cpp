/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQExperimentSelection.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:41 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQExperimentSelection.ui'
 **
 ** Created: Mon Oct 31 11:07:46 2005
 **      by: The User Interface Compiler ($Id: CQExperimentSelection.cpp,v 1.2 2006/04/27 01:27:41 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQExperimentSelection.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "CQExperimentSelection.ui.h"

/*
 *  Constructs a CQExperimentSelection as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CQExperimentSelection::CQExperimentSelection(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("CQExperimentSelection");
  CQExperimentSelectionLayout = new QVBoxLayout(this, 11, 6, "CQExperimentSelectionLayout");

  mpLayoutTop = new QHBoxLayout(0, 0, 6, "mpLayoutTop");

  mpBtnAll = new QPushButton(this, "mpBtnAll");
  mpLayoutTop->addWidget(mpBtnAll);

  mpBtnNone = new QPushButton(this, "mpBtnNone");
  mpLayoutTop->addWidget(mpBtnNone);
  CQExperimentSelectionLayout->addLayout(mpLayoutTop);

  layout16 = new QHBoxLayout(0, 0, 6, "layout16");

  mpTable = new QTable(this, "mpTable");
  mpTable->setNumCols(mpTable->numCols() + 1);
  mpTable->horizontalHeader()->setLabel(mpTable->numCols() - 1, tr("1"));
  mpTable->setNumRows(mpTable->numRows() + 1);
  mpTable->verticalHeader()->setLabel(mpTable->numRows() - 1, tr("1"));
  mpTable->setNumRows(mpTable->numRows() + 1);
  mpTable->verticalHeader()->setLabel(mpTable->numRows() - 1, tr("2"));
  mpTable->setNumRows(mpTable->numRows() + 1);
  mpTable->verticalHeader()->setLabel(mpTable->numRows() - 1, tr("3"));
  mpTable->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)5, 0, 0, mpTable->sizePolicy().hasHeightForWidth()));
  mpTable->setLineWidth(0);
  mpTable->setNumRows(3);
  mpTable->setNumCols(1);
  mpTable->setShowGrid(FALSE);
  mpTable->setSelectionMode(QTable::NoSelection);
  layout16->addWidget(mpTable);
  CQExperimentSelectionLayout->addLayout(layout16);
  spacer10 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQExperimentSelectionLayout->addItem(spacer10);

  mpLayoutBottom = new QHBoxLayout(0, 0, 6, "mpLayoutBottom");

  mpBtnOK = new QPushButton(this, "mpBtnOK");
  mpLayoutBottom->addWidget(mpBtnOK);

  mpBtnCancel = new QPushButton(this, "mpBtnCancel");
  mpLayoutBottom->addWidget(mpBtnCancel);
  CQExperimentSelectionLayout->addLayout(mpLayoutBottom);
  languageChange();
  resize(QSize(194, 180).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnAll, SIGNAL(clicked()), this, SLOT(slotBtnAll()));
  connect(mpBtnNone, SIGNAL(clicked()), this, SLOT(slotBtnNone()));
  connect(mpBtnCancel, SIGNAL(clicked()), this, SLOT(slotBtnCancel()));
  connect(mpBtnOK, SIGNAL(clicked()), this, SLOT(slotBtnOK()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQExperimentSelection::~CQExperimentSelection()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQExperimentSelection::languageChange()
{
  setCaption(tr("CQExperimentSelection"));
  mpBtnAll->setText(tr("Select All"));
  mpBtnNone->setText(tr("Deselect All"));
  mpTable->horizontalHeader()->setLabel(0, tr("1"));
  mpTable->verticalHeader()->setLabel(0, tr("1"));
  mpTable->verticalHeader()->setLabel(1, tr("2"));
  mpTable->verticalHeader()->setLabel(2, tr("3"));
  mpBtnOK->setText(tr("&OK"));
  mpBtnOK->setAccel(QKeySequence(tr("Alt+O")));
  mpBtnCancel->setText(tr("&Cancel"));
  mpBtnCancel->setAccel(QKeySequence(tr("Alt+C")));
}
