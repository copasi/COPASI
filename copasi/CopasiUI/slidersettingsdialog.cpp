/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/slidersettingsdialog.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/11/05 14:48:39 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'slidersettingsdialog.ui'
 **
 ** Created: Fri Nov 5 15:37:36 2004
 **      by: The User Interface Compiler ($Id: slidersettingsdialog.cpp,v 1.6 2004/11/05 14:48:39 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "slidersettingsdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "qtUtilities.h"
#include "qlistbox.h"
#include "qvalidator.h"
#include "qregexp.h"
#include "SimpleSelectionDialog.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiObjectName.h"
#include "model/CModel.h"
#include "slidersettingsdialog.ui.h"

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

  layout9 = new QGridLayout(0, 1, 1, 0, 6, "layout9");

  mpMinorMajorFactorLabel = new QLabel(this, "mpMinorMajorFactorLabel");

  layout9->addWidget(mpMinorMajorFactorLabel, 0, 3);

  mpMaxValueLabel = new QLabel(this, "mpMaxValueLabel");

  layout9->addWidget(mpMaxValueLabel, 1, 3);

  mpNumMinorTicksLabel = new QLabel(this, "mpNumMinorTicksLabel");

  layout9->addWidget(mpNumMinorTicksLabel, 2, 3);

  mpNumMinorTicksEdit = new QLineEdit(this, "mpNumMinorTicksEdit");
  mpNumMinorTicksEdit->setAlignment(int(QLineEdit::AlignRight));

  layout9->addWidget(mpNumMinorTicksEdit, 2, 4);

  mpMinorTickSizeEdit = new QLineEdit(this, "mpMinorTickSizeEdit");
  mpMinorTickSizeEdit->setAlignment(int(QLineEdit::AlignRight));

  layout9->addWidget(mpMinorTickSizeEdit, 2, 1);

  mpMinorTickSizeLabel = new QLabel(this, "mpMinorTickSizeLabel");

  layout9->addWidget(mpMinorTickSizeLabel, 2, 0);

  mpMinValueLabel = new QLabel(this, "mpMinValueLabel");

  layout9->addWidget(mpMinValueLabel, 1, 0);

  mpObjectValueEdit = new QLineEdit(this, "mpObjectValueEdit");
  mpObjectValueEdit->setAlignment(int(QLineEdit::AlignRight));

  layout9->addWidget(mpObjectValueEdit, 0, 1);

  mpMinorMajorFactorEdit = new QLineEdit(this, "mpMinorMajorFactorEdit");
  mpMinorMajorFactorEdit->setAlignment(int(QLineEdit::AlignRight));

  layout9->addWidget(mpMinorMajorFactorEdit, 0, 4);
  mpSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  layout9->addItem(mpSpacer1, 1, 2);

  mpMinValueEdit = new QLineEdit(this, "mpMinValueEdit");
  mpMinValueEdit->setAlignment(int(QLineEdit::AlignRight));

  layout9->addWidget(mpMinValueEdit, 1, 1);

  mpMaxValueEdit = new QLineEdit(this, "mpMaxValueEdit");
  mpMaxValueEdit->setAlignment(int(QLineEdit::AlignRight));

  layout9->addWidget(mpMaxValueEdit, 1, 4);

  mpObjectValueLabel = new QLabel(this, "mpObjectValueLabel");
  mpObjectValueLabel->setMargin(0);

  layout9->addWidget(mpObjectValueLabel, 0, 0);
  SliderSettingsDialogLayout->addLayout(layout9);

  mpLayout2 = new QHBoxLayout(0, 0, 6, "mpLayout2");

  mpOkButton = new QPushButton(this, "mpOkButton");
  mpOkButton->setDefault(TRUE);
  mpLayout2->addWidget(mpOkButton);

  mpCancelButton = new QPushButton(this, "mpCancelButton");
  mpLayout2->addWidget(mpCancelButton);
  SliderSettingsDialogLayout->addLayout(mpLayout2);
  languageChange();
  resize(QSize(611, 234).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpMinValueEdit, SIGNAL(returnPressed()), this, SLOT(minValueChanged()));
  connect(mpMaxValueEdit, SIGNAL(returnPressed()), this, SLOT(maxValueChanged()));
  connect(mpMinorTickSizeEdit, SIGNAL(returnPressed()), this, SLOT(minorTickSizeChanged()));
  connect(mpNumMinorTicksEdit, SIGNAL(returnPressed()), this, SLOT(numMinorTicksChanged()));
  connect(mpObjectValueEdit, SIGNAL(returnPressed()), this, SLOT(objectValueChanged()));
  connect(mpOkButton, SIGNAL(clicked()), this, SLOT(okButtonPressed()));
  connect(mpCancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonPressed()));
  connect(mpMinValueEdit, SIGNAL(lostFocus()), this, SLOT(minValueChanged()));
  connect(mpMaxValueEdit, SIGNAL(lostFocus()), this, SLOT(maxValueChanged()));
  connect(mpObjectValueEdit, SIGNAL(lostFocus()), this, SLOT(objectValueChanged()));
  connect(mpMinorTickSizeEdit, SIGNAL(lostFocus()), this, SLOT(minorTickSizeChanged()));
  connect(mpNumMinorTicksEdit, SIGNAL(lostFocus()), this, SLOT(numMinorTicksChanged()));
  connect(mpObjectBrowseButton, SIGNAL(clicked()), this, SLOT(browseButtonPressed()));

  // tab order
  setTabOrder(mpOkButton, mpCancelButton);
  setTabOrder(mpCancelButton, mpObjectBrowseButton);
  setTabOrder(mpObjectBrowseButton, mpObjectValueEdit);
  setTabOrder(mpObjectValueEdit, mpMinorMajorFactorEdit);
  setTabOrder(mpMinorMajorFactorEdit, mpMinValueEdit);
  setTabOrder(mpMinValueEdit, mpMaxValueEdit);
  setTabOrder(mpMaxValueEdit, mpMinorTickSizeEdit);
  setTabOrder(mpMinorTickSizeEdit, mpNumMinorTicksEdit);
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
  mpMinorMajorFactorLabel->setText(tr("Ticksize factor:"));
  mpMaxValueLabel->setText(tr("Maximum Value:"));
  mpNumMinorTicksLabel->setText(tr("Number of Minor Ticks:"));
  mpNumMinorTicksEdit->setText(tr("10.0"));
  mpMinorTickSizeEdit->setText(tr("1.0"));
  mpMinorTickSizeLabel->setText(tr("Minor Ticksize:"));
  mpMinValueLabel->setText(tr("Minimum Value:"));
  mpObjectValueEdit->setText(tr("50.0"));
  mpMinorMajorFactorEdit->setText(tr("10.0"));
  mpMinValueEdit->setText(tr("0.0"));
  mpMaxValueEdit->setText(tr("100.0"));
  mpObjectValueLabel->setText(tr("Object Value:"));
  mpOkButton->setText(tr("OK"));
  mpCancelButton->setText(tr("Cancel"));
}
