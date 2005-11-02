/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingItemWidget.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/02 15:47:22 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Wed Nov 2 10:40:16 2005
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.cpp,v 1.8 2005/11/02 15:47:22 shoops Exp $)
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
 #include <qimage.h>
 #include <qpixmap.h>

#include "CQFittingItemWidget.ui.h"
static const unsigned char image0_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x00,
    0x8f, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xa5, 0x52, 0x49, 0x12, 0xc0,
    0x20, 0x08, 0x8b, 0x4e, 0x1f, 0xc6, 0xd3, 0x7c, 0x1a, 0x3f, 0xb3, 0x07,
    0x6d, 0x59, 0x9a, 0xee, 0x78, 0x10, 0x42, 0x58, 0x26, 0x5a, 0x00, 0x85,
    0x99, 0xe0, 0x3a, 0xce, 0x26, 0x28, 0x80, 0xa2, 0x25, 0x52, 0x9b, 0x27,
    0x62, 0x42, 0x79, 0x35, 0x12, 0xb6, 0x22, 0x75, 0x8d, 0x84, 0x34, 0x32,
    0xac, 0x62, 0x0f, 0x3c, 0x91, 0xf9, 0xfe, 0xb6, 0xfc, 0x32, 0xa6, 0x69,
    0x5a, 0xf9, 0x29, 0xe6, 0xd6, 0xfd, 0x7a, 0x9f, 0x88, 0xc8, 0x04, 0xe3,
    0x22, 0x46, 0xc7, 0xf9, 0x47, 0x4c, 0x29, 0xaf, 0xc6, 0x95, 0xd8, 0x9a,
    0x71, 0x6a, 0xc6, 0x16, 0xeb, 0xe8, 0x89, 0x32, 0x67, 0xe4, 0xe2, 0xcc,
    0xd3, 0xa1, 0x41, 0x2c, 0x7c, 0x17, 0x17, 0x00, 0x87, 0xa7, 0xe1, 0x3f,
    0x91, 0x63, 0x70, 0xe2, 0x74, 0x00, 0x3d, 0x09, 0x76, 0x83, 0xc1, 0xbe,
    0xf2, 0x57, 0x73, 0x22, 0xb6, 0x92, 0x93, 0x4f, 0xb1, 0x5f, 0xb6, 0x02,
    0x6f, 0x3b, 0x53, 0x57, 0x71, 0xe6, 0x68, 0xdf, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
  };

/*
 *  Constructs a CQFittingItemWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQFittingItemWidget::CQFittingItemWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  QImage img;
  img.loadFromData(image0_data, sizeof(image0_data), "PNG");
  image0 = img;
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
  mpBtnLowerEdit->setMaximumSize(QSize(20, 20));
  mpBtnLowerEdit->setIconSet(QIconSet(image0));
  mpLayoutLower->addWidget(mpBtnLowerEdit);

  CQFittingItemWidgetLayout->addLayout(mpLayoutLower, 1, 4);

  mpLblUpper = new QLabel(this, "mpLblUpper");

  CQFittingItemWidgetLayout->addWidget(mpLblUpper, 2, 0);

  mpLayoutUpper = new QHBoxLayout(0, 0, 6, "mpLayoutUpper");

  mpEditUpper = new QLineEdit(this, "mpEditUpper");
  mpEditUpper->setEnabled(FALSE);
  mpEditUpper->setFrameShape(QLineEdit::LineEditPanel);
  mpEditUpper->setFrameShadow(QLineEdit::Sunken);
  mpLayoutUpper->addWidget(mpEditUpper);

  mpBtnUpperEdit = new QToolButton(this, "mpBtnUpperEdit");
  mpBtnUpperEdit->setMaximumSize(QSize(20, 20));
  mpBtnUpperEdit->setIconSet(QIconSet(image0));
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
  mpBtnExperiments->setMaximumSize(QSize(20, 20));
  mpBtnExperiments->setIconSet(QIconSet(image0));
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
  mpBtnObject->setMaximumSize(QSize(20, 20));
  mpBtnObject->setIconSet(QIconSet(image0));
  mpLayoutObject->addWidget(mpBtnObject);

  CQFittingItemWidgetLayout->addLayout(mpLayoutObject, 0, 4);
  languageChange();
  resize(QSize(195, 94).expandedTo(minimumSizeHint()));
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
  mpBtnLowerEdit->setText(QString::null);
  mpLblUpper->setText(tr("Upper Bound"));
  mpBtnUpperEdit->setText(QString::null);
  mpUpperInf->setText(tr("+ Infinity"));
  mpLblExperiments->setText(tr("Affected Experiments"));
  mpBtnExperiments->setText(QString::null);
  mpLblObject->setText(tr("Object"));
  mpBtnObject->setText(QString::null);
}
