/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/wizard/wizard.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/09/29 03:37:00 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'wizard.ui'
 **
 ** Created: Tue Sep 28 23:32:28 2004
 **      by: The User Interface Compiler ($Id: wizard.cpp,v 1.7 2004/09/29 03:37:00 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "wizard.h"

#include <qvariant.h>
#include <iostream>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qtextbrowser.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "qmessagebox.h"
#include "qdir.h"
#include "../CopasiUI/listviews.h"
#include "wizard.ui.h"

/*
 *  Constructs a WizardDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
WizardDialog::WizardDialog(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("WizardDialog");
  setModal(FALSE);
  WizardDialogLayout = new QVBoxLayout(this, 11, 6, "WizardDialogLayout");
  WizardDialogLayout->setResizeMode(QLayout::Fixed);

  layout12 = new QHBoxLayout(0, 0, 6, "layout12");

  buttonGroup = new QButtonGroup(this, "buttonGroup");
  buttonGroup->setFrameShape(QButtonGroup::NoFrame);
  buttonGroup->setFrameShadow(QButtonGroup::Plain);
  buttonGroup->setLineWidth(0);
  buttonGroup->setFlat(TRUE);
  buttonGroup->setExclusive(TRUE);
  buttonGroup->setProperty("selectedId", 0);

  button1 = new QPushButton(buttonGroup, "button1");
  button1->setEnabled(TRUE);
  button1->setGeometry(QRect(0, 80, 170, 50));
  button1->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)7, 0, 0, button1->sizePolicy().hasHeightForWidth()));
  button1->setFocusPolicy(QPushButton::NoFocus);
  button1->setToggleButton(TRUE);
  button1->setOn(TRUE);
  button1->setAutoDefault(FALSE);
  button1->setDefault(FALSE);
  button1->setFlat(TRUE);
  buttonGroup->insert(button1, 0);

  button6 = new QPushButton(buttonGroup, "button6");
  button6->setGeometry(QRect(0, 330, 170, 50));
  button6->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)7, 0, 0, button6->sizePolicy().hasHeightForWidth()));
  button6->setBackgroundOrigin(QPushButton::AncestorOrigin);
  button6->setToggleButton(TRUE);
  button6->setAutoDefault(FALSE);
  button6->setFlat(TRUE);
  buttonGroup->insert(button6, 5);

  button2 = new QPushButton(buttonGroup, "button2");
  button2->setGeometry(QRect(0, 130, 170, 50));
  button2->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)7, 0, 0, button2->sizePolicy().hasHeightForWidth()));
  button2->setToggleButton(TRUE);
  button2->setAutoDefault(FALSE);
  button2->setFlat(TRUE);
  buttonGroup->insert(button2, 1);

  button3 = new QPushButton(buttonGroup, "button3");
  button3->setGeometry(QRect(0, 180, 170, 50));
  button3->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)7, 0, 0, button3->sizePolicy().hasHeightForWidth()));
  button3->setToggleButton(TRUE);
  button3->setAutoDefault(FALSE);
  button3->setFlat(TRUE);
  buttonGroup->insert(button3, 2);

  button4 = new QPushButton(buttonGroup, "button4");
  button4->setGeometry(QRect(0, 230, 170, 50));
  button4->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)7, 0, 0, button4->sizePolicy().hasHeightForWidth()));
  button4->setToggleButton(TRUE);
  button4->setAutoDefault(FALSE);
  button4->setFlat(TRUE);
  buttonGroup->insert(button4, 3);

  button5 = new QPushButton(buttonGroup, "button5");
  button5->setGeometry(QRect(0, 280, 170, 50));
  button5->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)7, 0, 0, button5->sizePolicy().hasHeightForWidth()));
  button5->setToggleButton(TRUE);
  button5->setAutoDefault(FALSE);
  button5->setFlat(TRUE);
  buttonGroup->insert(button5, 4);
  layout12->addWidget(buttonGroup);

  textBrowser = new QTextBrowser(this, "textBrowser");
  textBrowser->setEnabled(TRUE);
  textBrowser->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, textBrowser->sizePolicy().hasHeightForWidth()));
  textBrowser->setMinimumSize(QSize(700, 500));
  textBrowser->setFocusPolicy(QTextBrowser::WheelFocus);
  textBrowser->setResizePolicy(QTextBrowser::Manual);
  textBrowser->setTextFormat(QTextBrowser::AutoText);
  textBrowser->setWordWrap(QTextBrowser::WidgetWidth);
  layout12->addWidget(textBrowser);
  WizardDialogLayout->addLayout(layout12);

  layout9 = new QHBoxLayout(0, 0, 6, "layout9");

  backButton = new QPushButton(this, "backButton");
  backButton->setEnabled(FALSE);
  backButton->setAutoDefault(FALSE);
  layout9->addWidget(backButton);

  forwardButton = new QPushButton(this, "forwardButton");
  forwardButton->setAutoDefault(FALSE);
  layout9->addWidget(forwardButton);
  QSpacerItem* spacer = new QSpacerItem(310, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout9->addItem(spacer);

  cancelButton = new QPushButton(this, "cancelButton");
  cancelButton->setAutoDefault(FALSE);
  layout9->addWidget(cancelButton);
  WizardDialogLayout->addLayout(layout9);
  languageChange();
  resize(QSize(900, 564).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(buttonGroup, SIGNAL(clicked(int)), this, SLOT(buttonGroup2_clicked(int)));
  connect(forwardButton, SIGNAL(clicked()), this, SLOT(forwardButton_clicked()));
  connect(backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));
  connect(textBrowser, SIGNAL(anchorClicked(const QString&, const QString&)), this, SLOT(textBrowser_anchorClicked(const QString&, const QString&)));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
WizardDialog::~WizardDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void WizardDialog::languageChange()
{
  setCaption(tr("Tutorial"));
  buttonGroup->setTitle(QString::null);
  button1->setText(tr("Step 1\n"
                        "Naming and Description"));
  button6->setText(tr("Step 6\n"
                        "Plotting a Trajectory"));
  button2->setText(tr("Step 2\n"
                        "Creating Reactions"));
  button3->setText(tr("Step 3\n"
                        "Refining the Model"));
  button4->setText(tr("Step 4\n"
                        "Defining the Output"));
  button5->setText(tr("Step 5\n"
                        "Calculating a Time Course"));
  backButton->setText(tr("<< back"));
  forwardButton->setText(tr("forward >>"));
  cancelButton->setText(tr("Cancel"));
}
