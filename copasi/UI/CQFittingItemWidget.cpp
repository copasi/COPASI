/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingItemWidget.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/12 13:26:30 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Tue Oct 11 17:57:42 2005
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.cpp,v 1.4 2005/10/12 13:26:30 shoops Exp $)
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
 #include <qcombobox.h>
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
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, sizePolicy().hasHeightForWidth()));
  CQFittingItemWidgetLayout = new QGridLayout(this, 1, 1, 3, 0, "CQFittingItemWidgetLayout");

  mpLblLower = new QLabel(this, "mpLblLower");

  CQFittingItemWidgetLayout->addWidget(mpLblLower, 1, 0);
  mpSpacerLeft = new QSpacerItem(12, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  CQFittingItemWidgetLayout->addItem(mpSpacerLeft, 1, 1);

  mpLowerInf = new QCheckBox(this, "mpLowerInf");
  mpLowerInf->setChecked(TRUE);

  CQFittingItemWidgetLayout->addWidget(mpLowerInf, 1, 2);

  mpLayoutLower = new QHBoxLayout(0, 0, 6, "mpLayoutLower");

  mpEditLower = new QLineEdit(this, "mpEditLower");
  mpEditLower->setEnabled(FALSE);
  mpEditLower->setFrameShape(QLineEdit::LineEditPanel);
  mpEditLower->setFrameShadow(QLineEdit::Sunken);
  mpLayoutLower->addWidget(mpEditLower);

  mpBtnLowerEdit = new QToolButton(this, "mpBtnLowerEdit");
  mpLayoutLower->addWidget(mpBtnLowerEdit);

  CQFittingItemWidgetLayout->addLayout(mpLayoutLower, 1, 4);

  mpLblUpper = new QLabel(this, "mpLblUpper");

  CQFittingItemWidgetLayout->addWidget(mpLblUpper, 2, 0);

  mpLayoutUpper = new QHBoxLayout(0, 0, 6, "mpLayoutUpper");

  mpEditUpper = new QLineEdit(this, "mpEditUpper");
  mpEditUpper->setEnabled(FALSE);
  mpLayoutUpper->addWidget(mpEditUpper);

  mpBtnUpperEdit = new QToolButton(this, "mpBtnUpperEdit");
  mpLayoutUpper->addWidget(mpBtnUpperEdit);

  CQFittingItemWidgetLayout->addLayout(mpLayoutUpper, 2, 4);

  mpUpperInf = new QCheckBox(this, "mpUpperInf");
  mpUpperInf->setChecked(TRUE);

  CQFittingItemWidgetLayout->addWidget(mpUpperInf, 2, 2);

  mpLblExperiments = new QLabel(this, "mpLblExperiments");

  CQFittingItemWidgetLayout->addMultiCellWidget(mpLblExperiments, 3, 3, 0, 2);

  mpLayoutExperiments = new QHBoxLayout(0, 0, 6, "mpLayoutExperiments");

  mpBoxExperiments = new QComboBox(FALSE, this, "mpBoxExperiments");
  mpBoxExperiments->setEnabled(TRUE);
  mpBoxExperiments->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, mpBoxExperiments->sizePolicy().hasHeightForWidth()));
  mpBoxExperiments->setDuplicatesEnabled(FALSE);
  mpLayoutExperiments->addWidget(mpBoxExperiments);

  mpBtnExperiments = new QToolButton(this, "mpBtnExperiments");
  mpLayoutExperiments->addWidget(mpBtnExperiments);

  CQFittingItemWidgetLayout->addLayout(mpLayoutExperiments, 3, 4);

  mpLblObject = new QLabel(this, "mpLblObject");

  CQFittingItemWidgetLayout->addWidget(mpLblObject, 0, 0);

  mpLayoutObject = new QHBoxLayout(0, 0, 6, "mpLayoutObject");

  mpEditObject = new QLineEdit(this, "mpEditObject");
  mpEditObject->setEnabled(TRUE);
  mpEditObject->setReadOnly(TRUE);
  mpLayoutObject->addWidget(mpEditObject);

  mpBtnObject = new QToolButton(this, "mpBtnObject");
  mpLayoutObject->addWidget(mpBtnObject);

  CQFittingItemWidgetLayout->addLayout(mpLayoutObject, 0, 4);
  languageChange();
  resize(QSize(579, 94).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpLowerInf, SIGNAL(toggled(bool)), this, SLOT(slotNegativeInfinity()));
  connect(mpUpperInf, SIGNAL(toggled(bool)), this, SLOT(slotPositiveInfinity()));
  connect(mpBtnLowerEdit, SIGNAL(clicked()), this, SLOT(slotLowerEdit()));
  connect(mpBtnUpperEdit, SIGNAL(clicked()), this, SLOT(slotUpperEdit()));
  connect(mpBtnObject, SIGNAL(clicked()), this, SLOT(slotParamEdit()));
  connect(mpBtnExperiments, SIGNAL(clicked()), this, SLOT(slotExperiments()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingItemWidget::~CQFittingItemWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFittingItemWidget::languageChange()
{
  setCaption(tr("CQFittingItemWidget"));
  mpLblLower->setText(tr("Lower Bound"));
  mpLowerInf->setText(tr("- Infinity"));
  mpBtnLowerEdit->setText(tr("..."));
  mpLblUpper->setText(tr("Upper Bound"));
  mpBtnUpperEdit->setText(tr("..."));
  mpUpperInf->setText(tr("+ Infinity"));
  mpLblExperiments->setText(tr("Affected Experiments"));
  mpBtnExperiments->setText(tr("..."));
  mpLblObject->setText(tr("Object"));
  mpBtnObject->setText(tr("..."));
}
