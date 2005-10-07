/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingItemWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/07 16:43:28 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Fri Oct 7 11:52:16 2005
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.cpp,v 1.1 2005/10/07 16:43:28 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQFittingItemWidget.h"

#include <qvariant.h>
 #include <qpushbutton.h>
 #include <qlabel.h>
 #include <qcheckbox.h>
 #include <qlineedit.h>
 #include <qtoolbutton.h>
 #include <qlayout.h>
 #include <qtooltip.h>
 #include <qwhatsthis.h>
 #include "CQFittingItemWidget.ui.h"

/*
 *  Constructs a CQFittingItemWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQFittingItemWidget::CQFittingItemWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CQFittingItemWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, sizePolicy().hasHeightForWidth()));
  CQFittingItemWidgetLayout = new QGridLayout(this, 1, 1, 3, 0, "CQFittingItemWidgetLayout");

  mpLblLower = new QLabel(this, "mpLblLower");

  CQFittingItemWidgetLayout->addWidget(mpLblLower, 1, 0);

  mpLblUpper = new QLabel(this, "mpLblUpper");

  CQFittingItemWidgetLayout->addWidget(mpLblUpper, 2, 0);

  mpLblObject = new QLabel(this, "mpLblObject");

  CQFittingItemWidgetLayout->addWidget(mpLblObject, 0, 0);

  mpLowerInf = new QCheckBox(this, "mpLowerInf");
  mpLowerInf->setChecked(TRUE);

  CQFittingItemWidgetLayout->addWidget(mpLowerInf, 1, 4);

  mpUpperInf = new QCheckBox(this, "mpUpperInf");
  mpUpperInf->setChecked(TRUE);

  CQFittingItemWidgetLayout->addWidget(mpUpperInf, 2, 4);

  mpLayoutUpper = new QHBoxLayout(0, 0, 6, "mpLayoutUpper");

  mpEditUpper = new QLineEdit(this, "mpEditUpper");
  mpEditUpper->setEnabled(FALSE);
  mpLayoutUpper->addWidget(mpEditUpper);

  mpBtnUpperEdit = new QToolButton(this, "mpBtnUpperEdit");
  mpLayoutUpper->addWidget(mpBtnUpperEdit);

  CQFittingItemWidgetLayout->addLayout(mpLayoutUpper, 2, 2);

  mpLayoutObject = new QHBoxLayout(0, 0, 6, "mpLayoutObject");

  mpEditObject = new QLineEdit(this, "mpEditObject");
  mpEditObject->setEnabled(FALSE);
  mpLayoutObject->addWidget(mpEditObject);

  mpBtnObject = new QToolButton(this, "mpBtnObject");
  mpLayoutObject->addWidget(mpBtnObject);

  CQFittingItemWidgetLayout->addLayout(mpLayoutObject, 0, 2);

  mpLayoutLower = new QHBoxLayout(0, 0, 6, "mpLayoutLower");

  mpEditLower = new QLineEdit(this, "mpEditLower");
  mpEditLower->setEnabled(FALSE);
  mpEditLower->setFrameShape(QLineEdit::LineEditPanel);
  mpEditLower->setFrameShadow(QLineEdit::Sunken);
  mpLayoutLower->addWidget(mpEditLower);

  mpBtnLowerEdit = new QToolButton(this, "mpBtnLowerEdit");
  mpLayoutLower->addWidget(mpBtnLowerEdit);

  CQFittingItemWidgetLayout->addLayout(mpLayoutLower, 1, 2);
  mpSpacerRight = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  CQFittingItemWidgetLayout->addMultiCell(mpSpacerRight, 1, 2, 3, 3);
  mpSpacerLeft = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  CQFittingItemWidgetLayout->addMultiCell(mpSpacerLeft, 1, 2, 1, 1);
  languageChange();
  resize(QSize(190, 72).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpLowerInf, SIGNAL(toggled(bool)), this, SLOT(slotNegativeInfinity()));
  connect(mpUpperInf, SIGNAL(toggled(bool)), this, SLOT(slotPositiveInfinity()));
  connect(mpBtnLowerEdit, SIGNAL(clicked()), this, SLOT(slotLowerEdit()));
  connect(mpBtnUpperEdit, SIGNAL(clicked()), this, SLOT(slotUpperEdit()));
  connect(mpBtnObject, SIGNAL(clicked()), this, SLOT(slotParamEdit()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingItemWidget::~CQFittingItemWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFittingItemWidget::languageChange()
{
  setCaption(tr("Form1"));
  mpLblLower->setText(tr("Lower Bound"));
  mpLblUpper->setText(tr("Upper Bound"));
  mpLblObject->setText(tr("Object"));
  mpLowerInf->setText(tr("- Infinity"));
  mpUpperInf->setText(tr("+ Infinity"));
  mpBtnUpperEdit->setText(tr("..."));
  mpBtnObject->setText(tr("..."));
  mpBtnLowerEdit->setText(tr("..."));
}
