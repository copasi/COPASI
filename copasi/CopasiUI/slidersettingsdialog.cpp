/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/slidersettingsdialog.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/11/02 17:00:57 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'slidersettingsdialog.ui'
 **
 ** Created: Tue Nov 2 17:20:57 2004
 **      by: The User Interface Compiler ($Id: slidersettingsdialog.cpp,v 1.1 2004/11/02 17:00:57 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "slidersettingsdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
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
  SliderSettingsDialogLayout = new QHBoxLayout(this, 11, 6, "SliderSettingsDialogLayout");
  SliderSettingsDialogLayout->setResizeMode(QLayout::Fixed);

  layout19 = new QVBoxLayout(0, 0, 6, "layout19");

  layout18 = new QGridLayout(0, 1, 1, 0, 6, "layout18");

  objectBrowseButton = new QPushButton(this, "objectBrowseButton");
  objectBrowseButton->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, objectBrowseButton->sizePolicy().hasHeightForWidth()));
  objectBrowseButton->setMinimumSize(QSize(40, 0));

  layout18->addWidget(objectBrowseButton, 1, 2);

  objectLabel = new QLabel(this, "objectLabel");
  objectLabel->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, objectLabel->sizePolicy().hasHeightForWidth()));

  layout18->addWidget(objectLabel, 1, 0);

  taskLabel = new QLabel(this, "taskLabel");
  taskLabel->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, taskLabel->sizePolicy().hasHeightForWidth()));

  layout18->addWidget(taskLabel, 0, 0);

  objectComboBox = new QComboBox(FALSE, this, "objectComboBox");
  objectComboBox->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, objectComboBox->sizePolicy().hasHeightForWidth()));
  objectComboBox->setMinimumSize(QSize(300, 0));
  objectComboBox->setDuplicatesEnabled(FALSE);

  layout18->addWidget(objectComboBox, 1, 1);

  taskComboBox = new QComboBox(FALSE, this, "taskComboBox");
  taskComboBox->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, taskComboBox->sizePolicy().hasHeightForWidth()));
  taskComboBox->setMinimumSize(QSize(300, 0));
  taskComboBox->setEditable(FALSE);
  taskComboBox->setSizeLimit(10);
  taskComboBox->setDuplicatesEnabled(FALSE);

  layout18->addWidget(taskComboBox, 0, 1);
  layout19->addLayout(layout18);

  layout15 = new QHBoxLayout(0, 0, 6, "layout15");

  layout14 = new QVBoxLayout(0, 0, 6, "layout14");
  spacer2 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout14->addItem(spacer2);

  layout12 = new QGridLayout(0, 1, 1, 0, 6, "layout12");

  minorTickSizeLabel = new QLabel(this, "minorTickSizeLabel");

  layout12->addWidget(minorTickSizeLabel, 2, 0);

  minValueLabel = new QLabel(this, "minValueLabel");

  layout12->addWidget(minValueLabel, 0, 0);

  majorTickSizeEdit = new QLineEdit(this, "majorTickSizeEdit");
  majorTickSizeEdit->setAlignment(int(QLineEdit::AlignRight));

  layout12->addWidget(majorTickSizeEdit, 1, 1);

  minValueEdit = new QLineEdit(this, "minValueEdit");
  minValueEdit->setAlignment(int(QLineEdit::AlignRight));

  layout12->addWidget(minValueEdit, 0, 1);

  minorTickSizeEdit = new QLineEdit(this, "minorTickSizeEdit");
  minorTickSizeEdit->setAlignment(int(QLineEdit::AlignRight));

  layout12->addWidget(minorTickSizeEdit, 2, 1);

  majorTickSizeLabel = new QLabel(this, "majorTickSizeLabel");

  layout12->addWidget(majorTickSizeLabel, 1, 0);
  layout14->addLayout(layout12);
  layout15->addLayout(layout14);
  spacer1 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  layout15->addItem(spacer1);

  layout13 = new QGridLayout(0, 1, 1, 0, 6, "layout13");

  numMinorTicksEdit = new QLineEdit(this, "numMinorTicksEdit");
  numMinorTicksEdit->setAlignment(int(QLineEdit::AlignRight));

  layout13->addWidget(numMinorTicksEdit, 3, 1);

  numMajorTicksEdit = new QLineEdit(this, "numMajorTicksEdit");
  numMajorTicksEdit->setAlignment(int(QLineEdit::AlignRight));

  layout13->addWidget(numMajorTicksEdit, 2, 1);

  numMinorTicksLabel = new QLabel(this, "numMinorTicksLabel");

  layout13->addWidget(numMinorTicksLabel, 3, 0);

  maxValueEdit = new QLineEdit(this, "maxValueEdit");
  maxValueEdit->setAlignment(int(QLineEdit::AlignRight));

  layout13->addWidget(maxValueEdit, 1, 1);

  maxValueLabel = new QLabel(this, "maxValueLabel");

  layout13->addWidget(maxValueLabel, 1, 0);

  objectValueLabel = new QLabel(this, "objectValueLabel");
  objectValueLabel->setMargin(0);

  layout13->addWidget(objectValueLabel, 0, 0);

  objectValueEdit = new QLineEdit(this, "objectValueEdit");
  objectValueEdit->setAlignment(int(QLineEdit::AlignRight));

  layout13->addWidget(objectValueEdit, 0, 1);

  numMajorTicksLabel = new QLabel(this, "numMajorTicksLabel");

  layout13->addWidget(numMajorTicksLabel, 2, 0);
  layout15->addLayout(layout13);
  layout19->addLayout(layout15);

  layout2 = new QHBoxLayout(0, 0, 6, "layout2");

  okButton = new QPushButton(this, "okButton");
  okButton->setDefault(TRUE);
  layout2->addWidget(okButton);

  cancelButton = new QPushButton(this, "cancelButton");
  layout2->addWidget(cancelButton);
  layout19->addLayout(layout2);
  SliderSettingsDialogLayout->addLayout(layout19);
  languageChange();
  resize(QSize(579, 241).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(minValueEdit, SIGNAL(returnPressed()), this, SLOT(minValueChanged()));
  connect(maxValueEdit, SIGNAL(returnPressed()), this, SLOT(maxValueChanged()));
  connect(majorTickSizeEdit, SIGNAL(returnPressed()), this, SLOT(majorTickSizeChanged()));
  connect(minorTickSizeEdit, SIGNAL(returnPressed()), this, SLOT(minorTickSizeChanged()));
  connect(numMajorTicksEdit, SIGNAL(returnPressed()), this, SLOT(numMajorTicksChanged()));
  connect(numMinorTicksEdit, SIGNAL(returnPressed()), this, SLOT(numMinorTicksChanged()));
  connect(objectValueEdit, SIGNAL(returnPressed()), this, SLOT(objectValueChanged()));
  connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonPressed()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonPressed()));
  connect(minValueEdit, SIGNAL(lostFocus()), this, SLOT(minValueChanged()));
  connect(maxValueEdit, SIGNAL(lostFocus()), this, SLOT(maxValueChanged()));
  connect(objectValueEdit, SIGNAL(lostFocus()), this, SLOT(objectValueChanged()));
  connect(majorTickSizeEdit, SIGNAL(lostFocus()), this, SLOT(majorTickSizeChanged()));
  connect(minorTickSizeEdit, SIGNAL(lostFocus()), this, SLOT(minorTickSizeChanged()));
  connect(numMajorTicksEdit, SIGNAL(lostFocus()), this, SLOT(numMajorTicksChanged()));
  connect(numMinorTicksEdit, SIGNAL(lostFocus()), this, SLOT(numMinorTicksChanged()));
  connect(taskComboBox, SIGNAL(highlighted(const QString&)), this, SLOT(updateObjectBox()));
  connect(objectComboBox, SIGNAL(highlighted(const QString&)), this, SLOT(updateSliderValues()));
  connect(objectBrowseButton, SIGNAL(clicked()), this, SLOT(browseButtonPressed()));

  // tab order
  setTabOrder(okButton, cancelButton);
  setTabOrder(cancelButton, taskComboBox);
  setTabOrder(taskComboBox, objectBrowseButton);
  setTabOrder(objectBrowseButton, objectValueEdit);
  setTabOrder(objectValueEdit, minValueEdit);
  setTabOrder(minValueEdit, maxValueEdit);
  setTabOrder(maxValueEdit, majorTickSizeEdit);
  setTabOrder(majorTickSizeEdit, numMajorTicksEdit);
  setTabOrder(numMajorTicksEdit, minorTickSizeEdit);
  setTabOrder(minorTickSizeEdit, numMinorTicksEdit);
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
  objectBrowseButton->setText(tr("..."));
  objectLabel->setText(tr("Object:"));
  taskLabel->setText(tr("Task:"));
  minorTickSizeLabel->setText(tr("Minor Ticksize:"));
  minValueLabel->setText(tr("Minimum Value:"));
  majorTickSizeEdit->setText(tr("10.0"));
  minValueEdit->setText(tr("0.0"));
  minorTickSizeEdit->setText(tr("1.0"));
  majorTickSizeLabel->setText(tr("Major Ticksize:"));
  numMinorTicksEdit->setText(tr("10.0"));
  numMajorTicksEdit->setText(tr("10.0"));
  numMinorTicksLabel->setText(tr("Number of Minor Ticks:"));
  maxValueEdit->setText(tr("100.0"));
  maxValueLabel->setText(tr("Maximum Value:"));
  objectValueLabel->setText(tr("Object Value:"));
  objectValueEdit->setText(tr("50.0"));
  numMajorTicksLabel->setText(tr("Number of Major Ticks:"));
  okButton->setText(tr("OK"));
  cancelButton->setText(tr("Cancel"));
}
