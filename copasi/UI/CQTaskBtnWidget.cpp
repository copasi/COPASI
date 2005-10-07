/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskBtnWidget.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/07 18:41:23 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQTaskBtnWidget.ui'
 **
 ** Created: Fri Oct 7 14:23:55 2005
 **      by: The User Interface Compiler ($Id: CQTaskBtnWidget.cpp,v 1.4 2005/10/07 18:41:23 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQTaskBtnWidget.h"

#include <qvariant.h>
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
  CQTaskBtnWidgetLayout = new QVBoxLayout(this, 0, 6, "CQTaskBtnWidgetLayout");
  mpSpacer = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Preferred);
  CQTaskBtnWidgetLayout->addItem(mpSpacer);

  mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");

  mpBtnRun = new QPushButton(this, "mpBtnRun");

  mpGridLayout->addWidget(mpBtnRun, 1, 0);

  mpBtnAssistant = new QPushButton(this, "mpBtnAssistant");

  mpGridLayout->addWidget(mpBtnAssistant, 1, 3);

  mpBtnRevert = new QPushButton(this, "mpBtnRevert");

  mpGridLayout->addWidget(mpBtnRevert, 1, 1);

  mpBtnReport = new QPushButton(this, "mpBtnReport");

  mpGridLayout->addWidget(mpBtnReport, 1, 2);
  CQTaskBtnWidgetLayout->addLayout(mpGridLayout);
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
  mpBtnRun->setText(tr("Run"));
  mpBtnAssistant->setText(tr("Output Assistant"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnReport->setText(tr("Report"));
}
