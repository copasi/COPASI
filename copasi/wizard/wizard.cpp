// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QtCore/QDir>
#include <QButtonGroup>

#include "wizard.h"
#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/listviews.h"
#include "copasi/UI/copasiui3window.h"

#include "copasi/copasi.h"

#include "copasi/commandline/COptions.h"

#include "copasi/resourcesUI/CQIconResource.h"

#include <iostream>

/*
 *  Constructs a WizardDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
WizardDialog::WizardDialog(QWidget* parent, const char* /* name */, bool /* modal */, Qt::WindowFlags fl):
  QDialog(parent, fl),
  copasiMainWindow(NULL),
  buttonGroup(NULL)
{
  setupUi(this);

#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin

  std::string WizardDir;
  COptions::getValue("WizardDir", WizardDir);

  if (!WizardDir.empty())
    {
      // the next line will hopefully ensure that this works under windows as well.
      WizardDialog::helpPath = "file:///" + QDir(WizardDir.c_str()).absolutePath();
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
  connect(textBrowser, SIGNAL(anchorClicked(const QUrl &)), this, SLOT(textBrowser_anchorClicked(const QUrl &)));
}

/*
 *  Destroys the object and frees any allocated resources
 */
WizardDialog::~WizardDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

const char* WizardDialog::texts[6] = {"TutWiz-Step1.html", "TutWiz-Step2.html", "TutWiz-Step3.html", "TutWiz-Step4.html", "TutWiz-Step5.html", "TutWiz-Step6.html"};

const char* WizardDialog::Error = "<html><head><title>Error</title></head><body><h1>Could not find help files.<br><br>Please set the COPASI_HELP_PATH environment variable to the absolute path that contains the html help files!</h1></body></html>";

QString WizardDialog::helpPath = "";

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

void WizardDialog::textBrowser_anchorClicked(const QUrl & url)
{
  QString name = url.fragment();

  // std::cout << name.toUtf8().data() << std::endl;

  CopasiUI3Window * pMainWindow = dynamic_cast<CopasiUI3Window *>(copasiMainWindow);

  if (name == "Model Settings")
    {
      if (pMainWindow)
        pMainWindow->getMainWidget()->switchToOtherWidget(ListViews::WidgetType::Model, std::string());
    }
  else if (name == "Reaction Overview")
    {
      if (pMainWindow)
        pMainWindow->getMainWidget()->switchToOtherWidget(ListViews::WidgetType::Reactions, std::string());
    }
  else if (name == "Report Definition")
    {
      if (pMainWindow)
        pMainWindow->getMainWidget()->switchToOtherWidget(ListViews::WidgetType::ReportTemplates, std::string());
    }
  else if (name == "Step 1")
    {
      buttonGroup->button(0)->setChecked(true);
      buttonGroup2_clicked(this->buttonGroup->checkedId());
    }
  else if (name == "Time Course")
    {
      if (pMainWindow)
        pMainWindow->getMainWidget()->switchToOtherWidget(ListViews::WidgetType::TimeCourse, std::string());
    }
  else if (name == "Plot Definition Overview")
    {
      if (pMainWindow)
        pMainWindow->getMainWidget()->switchToOtherWidget(ListViews::WidgetType::Plots, std::string());
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
