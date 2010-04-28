// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/wizard/wizard.cpp,v $
//   $Revision: 1.12.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/28 15:30:47 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QDir>

#include "wizard.h"
#include "UI/CQMessageBox.h"
#include "UI/listviews.h"

#include "copasi.h"

#include "commandline/COptions.h"

// #include <qvariant.h>
// #include <iostream>
// #include <qmessagebox.h>
// #include <qdir.h>
// #include "UI/listviews.h"

/*
 *  Constructs a WizardDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
WizardDialog::WizardDialog(QWidget* parent, const char* /* name */, bool /* modal */, Qt::WindowFlags fl):
    QDialog(parent, fl)
{
  setupUi(this);

  std::string WizardDir;
  COptions::getValue("WizardDir", WizardDir);

  if (!WizardDir.empty())
    {
      // the next line will hopefully ensure that this works under windows as well.
      WizardDialog::helpPath = QDir(WizardDir.c_str()).absolutePath();
      QString source = WizardDialog::helpPath + "/" + WizardDialog::texts[0];
      this->textBrowser->setSource(source);
    }
  else
    {
      this->textBrowser->setText(WizardDialog::Error);;
    }

  buttonGroup = new QButtonGroup(this);

  buttonGroup->addButton(button1, 0);
  buttonGroup->addButton(button2, 1);
  buttonGroup->addButton(button3, 2);
  buttonGroup->addButton(button4, 3);
  buttonGroup->addButton(button5, 4);
  buttonGroup->addButton(button6, 5);

  buttonGroup->button(0)->setChecked(true);

  connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonGroup2_clicked(int)));
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
  retranslateUi(this);
}

const char* WizardDialog::texts[6] = {"TutWiz-Step1.html", "TutWiz-Step2.html", "TutWiz-Step3.html", "TutWiz-Step4.html", "TutWiz-Step5.html", "TutWiz-Step6.html"};

const char* WizardDialog::Error = "<html><head><title>Error</title></head><body><h1>Could not find help files.<br><br>Please set the COPASI_HELP_PATH environment variable to the absolute path that contains the html help files!</h1></body></html>";

QString WizardDialog::helpPath = "";

QWidget* copasiMainWindow = NULL;

void WizardDialog::buttonGroup2_clicked(int)
{
  int checkedId = this->buttonGroup->checkedId();

  if (checkedId == 0)
    {
      this->backButton->setEnabled(false);
      this->forwardButton->setEnabled(true);
    }
  else if (checkedId == 5)
    {
      this->forwardButton->setEnabled(false);
      this->backButton->setEnabled(true);
    }
  else
    {
      this->forwardButton->setEnabled(true);
      this->backButton->setEnabled(true);
    }

  if (WizardDialog::helpPath != "")
    {
      QString source = WizardDialog::helpPath + "/" + WizardDialog::texts[checkedId];
      this->textBrowser->setSource(source);
    }
}

void WizardDialog::forwardButton_clicked()
{
  buttonGroup->button(buttonGroup->checkedId() + 1)->setChecked(true);
  buttonGroup2_clicked(this->buttonGroup->checkedId());
}

void WizardDialog::backButton_clicked()
{
  buttonGroup->button(buttonGroup->checkedId() - 1)->setChecked(true);
  buttonGroup2_clicked(this->buttonGroup->checkedId());
}

void WizardDialog::textBrowser_anchorClicked(const QString &name, const QString & C_UNUSED(link))
{
  if (name == "Model Settings")
    {
      ListViews::switchAllListViewsToWidget(1, "");
    }
  else if (name == "Reaction Overview")
    {
      ListViews::switchAllListViewsToWidget(114, "");
    }
  else if (name == "Report Definition")
    {
      ListViews::switchAllListViewsToWidget(43, "");
    }
  else if (name == "Step 1")
    {
      buttonGroup->button(0)->setChecked(true);
      buttonGroup2_clicked(this->buttonGroup->checkedId());
    }
  else if (name == "Time Course")
    {
      ListViews::switchAllListViewsToWidget(23, "");
    }
  else if (name == "Plot Definition Overview")
    {
      ListViews::switchAllListViewsToWidget(42, "");
    }
  else
    {
      CQMessageBox::information(this, "Error", "Link not found",
                                QMessageBox::Ok, QMessageBox::Ok);
    }
}

void WizardDialog::setCopasiMainWindow(QWidget * copasiMainWindow)
{
  this->copasiMainWindow = copasiMainWindow;
}
