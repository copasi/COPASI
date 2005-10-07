/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskHeaderWidget.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/07 14:15:11 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQTaskHeaderWidget.ui'
 **
 ** Created: Fri Oct 7 13:41:48 2005
 **      by: The User Interface Compiler ($Id: CQTaskHeaderWidget.cpp,v 1.4 2005/10/07 14:15:11 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQTaskHeaderWidget.h"

#include <qvariant.h>
 #include <qlabel.h>
 #include <qcheckbox.h>
 #include <qlayout.h>
 #include <qtooltip.h>
 #include <qwhatsthis.h>
 #include "CQTaskHeaderWidget.ui.h"

/*
 *  Constructs a CQTaskHeaderWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQTaskHeaderWidget::CQTaskHeaderWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CQTaskHeaderWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, sizePolicy().hasHeightForWidth()));
  CQTaskHeaderWidgetLayout = new QHBoxLayout(this, 0, 6, "CQTaskHeaderWidgetLayout");

  mpLblName = new QLabel(this, "mpLblName");
  mpLblName->setMinimumSize(QSize(200, 0));
  CQTaskHeaderWidgetLayout->addWidget(mpLblName);
  mpSpacer1 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  CQTaskHeaderWidgetLayout->addItem(mpSpacer1);

  mpUpdateModel = new QCheckBox(this, "mpUpdateModel");
  CQTaskHeaderWidgetLayout->addWidget(mpUpdateModel);
  mpSpacer2 = new QSpacerItem(30, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);
  CQTaskHeaderWidgetLayout->addItem(mpSpacer2);

  mpBoxExecutable = new QCheckBox(this, "mpBoxExecutable");
  CQTaskHeaderWidgetLayout->addWidget(mpBoxExecutable);
  languageChange();
  resize(QSize(521, 28).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTaskHeaderWidget::~CQTaskHeaderWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQTaskHeaderWidget::languageChange()
{
  setCaption(tr("CQTaskHeaderWidget"));
  mpLblName->setText(tr("<h2>Task</h2>"));
  mpUpdateModel->setText(tr("update model"));
  mpBoxExecutable->setText(tr("executable"));
}
