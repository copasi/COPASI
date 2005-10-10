/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskHeaderWidget.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/10 18:50:57 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQTaskHeaderWidget.ui'
 **
 ** Created: Mon Oct 10 14:48:39 2005
 **      by: The User Interface Compiler ($Id: CQTaskHeaderWidget.cpp,v 1.5 2005/10/10 18:50:57 shoops Exp $)
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
  resize(QSize(521, 26).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBoxExecutable, SIGNAL(toggled(bool)), this, SLOT(slotExecutable()));
  connect(mpUpdateModel, SIGNAL(toggled(bool)), this, SLOT(slotUpdate()));
  init();
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
