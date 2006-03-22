/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingResultTab1.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/22 16:52:55 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQFittingResultTab1.ui'
 **
 ** Created: Tue Mar 21 11:12:51 2006
 **      by: The User Interface Compiler ($Id: CQFittingResultTab1.cpp,v 1.1 2006/03/22 16:52:55 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQFittingResultTab1.h"

#include <qvariant.h>
 #include <qlabel.h>
 #include <qlineedit.h>
 #include <qlayout.h>
 #include <qtooltip.h>
 #include <qwhatsthis.h>
 #include "CQFittingResultTab1.ui.h"

/*
 *  Constructs a CQFittingResultTab1 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQFittingResultTab1::CQFittingResultTab1(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CQFittingResultTab1");
  CQFittingResultTab1Layout = new QVBoxLayout(this, 11, 6, "CQFittingResultTab1Layout");

  mpLayoutGrid = new QGridLayout(0, 1, 1, 0, 1, "mpLayoutGrid");

  mpLblObjectiveValue = new QLabel(this, "mpLblObjectiveValue");

  mpLayoutGrid->addWidget(mpLblObjectiveValue, 0, 0);

  mpEditCPUTime = new QLineEdit(this, "mpEditCPUTime");
  mpEditCPUTime->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCPUTime->setFrameShadow(QLineEdit::Sunken);
  mpEditCPUTime->setReadOnly(TRUE);

  mpLayoutGrid->addWidget(mpEditCPUTime, 3, 1);

  mpEditEvaluations = new QLineEdit(this, "mpEditEvaluations");
  mpEditEvaluations->setReadOnly(TRUE);

  mpLayoutGrid->addWidget(mpEditEvaluations, 3, 0);

  mpLblEvaluations = new QLabel(this, "mpLblEvaluations");

  mpLayoutGrid->addWidget(mpLblEvaluations, 2, 0);

  mpEditRMS = new QLineEdit(this, "mpEditRMS");
  mpEditRMS->setFrameShape(QLineEdit::LineEditPanel);
  mpEditRMS->setFrameShadow(QLineEdit::Sunken);
  mpEditRMS->setReadOnly(TRUE);

  mpLayoutGrid->addWidget(mpEditRMS, 1, 1);

  mpLblCPUTime = new QLabel(this, "mpLblCPUTime");

  mpLayoutGrid->addWidget(mpLblCPUTime, 2, 1);

  mpEditSpeed = new QLineEdit(this, "mpEditSpeed");
  mpEditSpeed->setReadOnly(TRUE);

  mpLayoutGrid->addWidget(mpEditSpeed, 3, 2);

  mpEditObjectiveValue = new QLineEdit(this, "mpEditObjectiveValue");
  mpEditObjectiveValue->setReadOnly(TRUE);

  mpLayoutGrid->addWidget(mpEditObjectiveValue, 1, 0);

  mpEditStdDeviation = new QLineEdit(this, "mpEditStdDeviation");
  mpEditStdDeviation->setReadOnly(TRUE);

  mpLayoutGrid->addWidget(mpEditStdDeviation, 1, 2);

  mpLblSpeed = new QLabel(this, "mpLblSpeed");

  mpLayoutGrid->addWidget(mpLblSpeed, 2, 2);

  mpLblRMS = new QLabel(this, "mpLblRMS");

  mpLayoutGrid->addWidget(mpLblRMS, 0, 1);

  mpLblStdDeviation = new QLabel(this, "mpLblStdDeviation");

  mpLayoutGrid->addWidget(mpLblStdDeviation, 0, 2);
  CQFittingResultTab1Layout->addLayout(mpLayoutGrid);
  mpSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQFittingResultTab1Layout->addItem(mpSpacer);
  languageChange();
  resize(QSize(360, 264).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingResultTab1::~CQFittingResultTab1()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFittingResultTab1::languageChange()
{
  setCaption(tr("CQFittingResultTab1"));
  mpLblObjectiveValue->setText(tr("Objective Value"));
  mpLblEvaluations->setText(tr("Function Evaluations"));
  mpLblCPUTime->setText(tr("CPU Time [s]"));
  mpLblSpeed->setText(tr("Evaluations/second [1/s]"));
  mpLblRMS->setText(tr("Root Mean Square"));
  mpLblStdDeviation->setText(tr("Standard Deviation"));
}
