/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SliderSettingsDialog.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/03/30 12:11:58 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'SliderSettingsDialog.ui'
 **
 ** Created: Wed Mar 30 14:08:28 2005
 **      by: The User Interface Compiler ($Id: SliderSettingsDialog.cpp,v 1.6 2005/03/30 12:11:58 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "SliderSettingsDialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "qtUtilities.h"
#include "qlistbox.h"
#include "qvalidator.h"
#include "qregexp.h"
#include "CCopasiSelectionDialog.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiObjectName.h"
#include "model/CModel.h"
#include "SliderSettingsDialog.ui.h"

/*
 *  Constructs a SliderSettingsDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
SliderSettingsDialog::SliderSettingsDialog(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("SliderSettingsDialog");
  SliderSettingsDialogLayout = new QVBoxLayout(this, 11, 6, "SliderSettingsDialogLayout");
  SliderSettingsDialogLayout->setResizeMode(QLayout::Fixed);

  mpLayout11 = new QHBoxLayout(0, 0, 6, "mpLayout11");

  mpObjectLabel = new QLabel(this, "mpObjectLabel");
  mpObjectLabel->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, mpObjectLabel->sizePolicy().hasHeightForWidth()));
  mpLayout11->addWidget(mpObjectLabel);

  mpObjectNameLineEdit = new QLineEdit(this, "mpObjectNameLineEdit");
  mpObjectNameLineEdit->setEnabled(TRUE);
  mpObjectNameLineEdit->setReadOnly(TRUE);
  mpLayout11->addWidget(mpObjectNameLineEdit);

  mpObjectBrowseButton = new QPushButton(this, "mpObjectBrowseButton");
  mpObjectBrowseButton->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, mpObjectBrowseButton->sizePolicy().hasHeightForWidth()));
  mpObjectBrowseButton->setMinimumSize(QSize(40, 0));
  mpLayout11->addWidget(mpObjectBrowseButton);
  SliderSettingsDialogLayout->addLayout(mpLayout11);

  layout5 = new QHBoxLayout(0, 0, 6, "layout5");

  mpMinValueLabel = new QLabel(this, "mpMinValueLabel");
  layout5->addWidget(mpMinValueLabel);

  mpMinValueEdit = new QLineEdit(this, "mpMinValueEdit");
  mpMinValueEdit->setAlignment(int(QLineEdit::AlignRight));
  layout5->addWidget(mpMinValueEdit);
  mpSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  layout5->addItem(mpSpacer1);

  mpMaxValueLabel = new QLabel(this, "mpMaxValueLabel");
  layout5->addWidget(mpMaxValueLabel);

  mpMaxValueEdit = new QLineEdit(this, "mpMaxValueEdit");
  mpMaxValueEdit->setAlignment(int(QLineEdit::AlignRight));
  layout5->addWidget(mpMaxValueEdit);
  SliderSettingsDialogLayout->addLayout(layout5);

  layout10 = new QHBoxLayout(0, 0, 6, "layout10");

  mpLogCheckBox = new QCheckBox(this, "mpLogCheckBox");
  layout10->addWidget(mpLogCheckBox);

  mpGlobalCheckBox = new QCheckBox(this, "mpGlobalCheckBox");
  layout10->addWidget(mpGlobalCheckBox);
  mpSpacer1_2_2 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  layout10->addItem(mpSpacer1_2_2);
  SliderSettingsDialogLayout->addLayout(layout10);

  layout9 = new QHBoxLayout(0, 0, 6, "layout9");

  mpExtendedOptionsButton = new QPushButton(this, "mpExtendedOptionsButton");
  layout9->addWidget(mpExtendedOptionsButton);
  spacer6 = new QSpacerItem(300, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout9->addItem(spacer6);
  SliderSettingsDialogLayout->addLayout(layout9);

  mpExtendedOptionsFrame = new QFrame(this, "mpExtendedOptionsFrame");
  mpExtendedOptionsFrame->setFrameShape(QFrame::NoFrame);
  mpExtendedOptionsFrame->setFrameShadow(QFrame::Raised);
  mpExtendedOptionsFrameLayout = new QGridLayout(mpExtendedOptionsFrame, 1, 1, 11, 6, "mpExtendedOptionsFrameLayout");

  mpMinorMajorFactorLabel = new QLabel(mpExtendedOptionsFrame, "mpMinorMajorFactorLabel");

  mpExtendedOptionsFrameLayout->addWidget(mpMinorMajorFactorLabel, 1, 0);

  mpNumMinorTicksLabel = new QLabel(mpExtendedOptionsFrame, "mpNumMinorTicksLabel");

  mpExtendedOptionsFrameLayout->addWidget(mpNumMinorTicksLabel, 0, 0);

  mpNumMinorTicksEdit = new QLineEdit(mpExtendedOptionsFrame, "mpNumMinorTicksEdit");
  mpNumMinorTicksEdit->setAlignment(int(QLineEdit::AlignRight));

  mpExtendedOptionsFrameLayout->addWidget(mpNumMinorTicksEdit, 0, 1);

  mpMinorTickSizeEdit = new QLineEdit(mpExtendedOptionsFrame, "mpMinorTickSizeEdit");
  mpMinorTickSizeEdit->setAlignment(int(QLineEdit::AlignRight));

  mpExtendedOptionsFrameLayout->addWidget(mpMinorTickSizeEdit, 0, 4);

  mpObjectValueEdit = new QLineEdit(mpExtendedOptionsFrame, "mpObjectValueEdit");
  mpObjectValueEdit->setAlignment(int(QLineEdit::AlignRight));

  mpExtendedOptionsFrameLayout->addWidget(mpObjectValueEdit, 1, 4);

  mpMinorMajorFactorEdit = new QLineEdit(mpExtendedOptionsFrame, "mpMinorMajorFactorEdit");
  mpMinorMajorFactorEdit->setAlignment(int(QLineEdit::AlignRight));

  mpExtendedOptionsFrameLayout->addWidget(mpMinorMajorFactorEdit, 1, 1);
  mpSpacer1_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  mpExtendedOptionsFrameLayout->addItem(mpSpacer1_3, 1, 2);
  mpSpacer1_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  mpExtendedOptionsFrameLayout->addItem(mpSpacer1_2, 0, 2);

  mpObjectValueLabel = new QLabel(mpExtendedOptionsFrame, "mpObjectValueLabel");
  mpObjectValueLabel->setMargin(0);

  mpExtendedOptionsFrameLayout->addWidget(mpObjectValueLabel, 1, 3);

  mpMinorTickSizeLabel = new QLabel(mpExtendedOptionsFrame, "mpMinorTickSizeLabel");

  mpExtendedOptionsFrameLayout->addWidget(mpMinorTickSizeLabel, 0, 3);
  SliderSettingsDialogLayout->addWidget(mpExtendedOptionsFrame);

  mpLayout2 = new QHBoxLayout(0, 0, 6, "mpLayout2");

  mpOkButton = new QPushButton(this, "mpOkButton");
  mpOkButton->setDefault(TRUE);
  mpLayout2->addWidget(mpOkButton);

  mpCancelButton = new QPushButton(this, "mpCancelButton");
  mpLayout2->addWidget(mpCancelButton);
  SliderSettingsDialogLayout->addLayout(mpLayout2);
  languageChange();
  resize(QSize(486, 279).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpCancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonPressed()));
  connect(mpOkButton, SIGNAL(clicked()), this, SLOT(okButtonPressed()));
  connect(mpObjectValueEdit, SIGNAL(returnPressed()), this, SLOT(objectValueChanged()));
  connect(mpObjectValueEdit, SIGNAL(lostFocus()), this, SLOT(objectValueChanged()));
  connect(mpObjectValueEdit, SIGNAL(textChanged(const QString&)), this, SLOT(lineEditChanged()));
  connect(mpMinorTickSizeEdit, SIGNAL(returnPressed()), this, SLOT(minorTickSizeChanged()));
  connect(mpMinorTickSizeEdit, SIGNAL(lostFocus()), this, SLOT(minorTickSizeChanged()));
  connect(mpMinorTickSizeEdit, SIGNAL(textChanged(const QString&)), this, SLOT(lineEditChanged()));
  connect(mpMinorMajorFactorEdit, SIGNAL(textChanged(const QString&)), this, SLOT(lineEditChanged()));
  connect(mpNumMinorTicksEdit, SIGNAL(returnPressed()), this, SLOT(numMinorTicksChanged()));
  connect(mpNumMinorTicksEdit, SIGNAL(lostFocus()), this, SLOT(numMinorTicksChanged()));
  connect(mpNumMinorTicksEdit, SIGNAL(textChanged(const QString&)), this, SLOT(lineEditChanged()));
  connect(mpMinValueEdit, SIGNAL(returnPressed()), this, SLOT(minValueChanged()));
  connect(mpMinValueEdit, SIGNAL(lostFocus()), this, SLOT(minValueChanged()));
  connect(mpMinValueEdit, SIGNAL(textChanged(const QString&)), this, SLOT(lineEditChanged()));
  connect(mpMaxValueEdit, SIGNAL(returnPressed()), this, SLOT(maxValueChanged()));
  connect(mpMaxValueEdit, SIGNAL(lostFocus()), this, SLOT(maxValueChanged()));
  connect(mpMaxValueEdit, SIGNAL(textChanged(const QString&)), this, SLOT(lineEditChanged()));
  connect(mpObjectBrowseButton, SIGNAL(clicked()), this, SLOT(browseButtonPressed()));
  connect(mpExtendedOptionsButton, SIGNAL(clicked()), this, SLOT(extendedOptionsClicked()));
  connect(mpLogCheckBox, SIGNAL(toggled(bool)), this, SLOT(logCheckBoxToggled(bool)));

  // tab order
  setTabOrder(mpObjectNameLineEdit, mpObjectBrowseButton);
  setTabOrder(mpObjectBrowseButton, mpMinValueEdit);
  setTabOrder(mpMinValueEdit, mpMaxValueEdit);
  setTabOrder(mpMaxValueEdit, mpLogCheckBox);
  setTabOrder(mpLogCheckBox, mpGlobalCheckBox);
  setTabOrder(mpGlobalCheckBox, mpExtendedOptionsButton);
  setTabOrder(mpExtendedOptionsButton, mpNumMinorTicksEdit);
  setTabOrder(mpNumMinorTicksEdit, mpMinorTickSizeEdit);
  setTabOrder(mpMinorTickSizeEdit, mpMinorMajorFactorEdit);
  setTabOrder(mpMinorMajorFactorEdit, mpObjectValueEdit);
  setTabOrder(mpObjectValueEdit, mpOkButton);
  setTabOrder(mpOkButton, mpCancelButton);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
SliderSettingsDialog::~SliderSettingsDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void SliderSettingsDialog::languageChange()
{
  setCaption(tr("Slider Settings"));
  mpObjectLabel->setText(tr("Object:"));
  mpObjectBrowseButton->setText(tr("choose object"));
  mpMinValueLabel->setText(tr("Minimum Value:"));
  mpMinValueEdit->setText(tr("0.0"));
  mpMaxValueLabel->setText(tr("Maximum Value:"));
  mpMaxValueEdit->setText(tr("100.0"));
  mpLogCheckBox->setText(tr("logarithmic"));
  mpGlobalCheckBox->setText(tr("use for all tasks"));
  mpExtendedOptionsButton->setText(tr("more options"));
  mpMinorMajorFactorLabel->setText(tr("Ticksize factor:"));
  mpNumMinorTicksLabel->setText(tr("Number of Minor Ticks:"));
  mpNumMinorTicksEdit->setText(tr("10.0"));
  mpMinorTickSizeEdit->setText(tr("1.0"));
  mpObjectValueEdit->setText(tr("50.0"));
  mpMinorMajorFactorEdit->setText(tr("10.0"));
  mpObjectValueLabel->setText(tr("Object Value:"));
  mpMinorTickSizeLabel->setText(tr("Minor Ticksize:"));
  mpOkButton->setText(tr("OK"));
  mpCancelButton->setText(tr("Cancel"));
}
