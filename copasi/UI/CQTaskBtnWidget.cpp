/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskBtnWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/05 16:24:07 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQTaskBtnWidget.ui'
 **
 ** Created: Tue Oct 4 17:05:39 2005
 **      by: The User Interface Compiler ($Id: CQTaskBtnWidget.cpp,v 1.1 2005/10/05 16:24:07 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQTaskBtnWidget.h"

#include <qvariant.h>
 #include <qframe.h>
 #include <qpushbutton.h>
 #include <qlayout.h>
 #include <qtooltip.h>
 #include <qwhatsthis.h>

/*
 *  Constructs a CQTaskBtnWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQTaskBtnWidget::CQTaskBtnWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CQTaskBtnWidget");
  CQTaskBtnWidgetLayout = new QGridLayout(this, 1, 1, 0, 6, "CQTaskBtnWidgetLayout");

  mpLine = new QFrame(this, "mpLine");
  mpLine->setFrameShape(QFrame::HLine);
  mpLine->setFrameShadow(QFrame::Sunken);
  mpLine->setFrameShape(QFrame::HLine);

  CQTaskBtnWidgetLayout->addMultiCellWidget(mpLine, 0, 0, 0, 3);

  mpBtnRevert = new QPushButton(this, "mpBtnRevert");

  CQTaskBtnWidgetLayout->addWidget(mpBtnRevert, 1, 1);

  mpBtnRun = new QPushButton(this, "mpBtnRun");

  CQTaskBtnWidgetLayout->addWidget(mpBtnRun, 1, 0);

  mpBtnReport = new QPushButton(this, "mpBtnReport");

  CQTaskBtnWidgetLayout->addWidget(mpBtnReport, 1, 2);

  mpBtnAssistant = new QPushButton(this, "mpBtnAssistant");

  CQTaskBtnWidgetLayout->addWidget(mpBtnAssistant, 1, 3);
  languageChange();
  resize(QSize(367, 35).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // tab order
  setTabOrder(mpBtnRun, mpBtnRevert);
  setTabOrder(mpBtnRevert, mpBtnReport);
  setTabOrder(mpBtnReport, mpBtnAssistant);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTaskBtnWidget::~CQTaskBtnWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQTaskBtnWidget::languageChange()
{
  setCaption(tr("CQTaskBtnWidget"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnRun->setText(tr("Run"));
  mpBtnReport->setText(tr("Report"));
  mpBtnAssistant->setText(tr("Output Assistant"));
}
