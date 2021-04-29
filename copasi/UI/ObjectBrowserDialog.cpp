// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include "ObjectBrowserDialog.h"
#include <QPushButton>
#include <QLayout>
#include <QGridLayout>
#include <QCloseEvent>

#include "copasi/copasi.h"

#include "copasiui3window.h"
#include "copasi/core/CDataObject.h"
#include "ObjectBrowserWidget.h"
//#include "qtUtilities.h"

/*
 *  Constructs a ObjectBrowserDialog which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
ObjectBrowserDialog::ObjectBrowserDialog(QWidget* parent, const char* name, bool modal, int state)
  : QDialog(parent),
    clearButton(NULL),
    toggleViewButton(NULL),
    cancelButton(NULL),
    okButton(NULL),
    Line1(NULL),
    spacer(NULL),
    objectBrowserWidget(NULL),
    ObjectBrowserDialogLayout(NULL)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setAttribute(Qt::WA_DeleteOnClose);
  ObjectBrowserDialogLayout = new QGridLayout(this);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
  ObjectBrowserDialogLayout->setMargin(11);
#else
  ObjectBrowserDialogLayout->setContentsMargins(11, 11, 11, 11);
#endif

  ObjectBrowserDialogLayout->setSpacing(6);
  ObjectBrowserDialogLayout->setObjectName(QString::fromUtf8("ObjectBrowserDialogLayout"));

  objectBrowserWidget = new ObjectBrowserWidget(this);
  ObjectBrowserDialogLayout->addWidget(objectBrowserWidget, 0, 0, 1, 2);

  Line1 = new QFrame(this);
  Line1->setObjectName("Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setFrameShadow(QFrame::Sunken);
  Line1->setFrameShape(QFrame::HLine);
  ObjectBrowserDialogLayout->addWidget(Line1, 1, 0, 1, 2);

  if (state == 0)
    {
      clearButton = new QPushButton(this);
      clearButton->setObjectName("clearButton");
      clearButton->setText("Clear");

      toggleViewButton = new QPushButton(this);
      toggleViewButton->setObjectName("toggleViewButton");
      toggleViewButton->setText("Selected Items");

      cancelButton = new QPushButton(this);
      cancelButton->setObjectName("cancelButton");
      cancelButton->setText("Cancel");

      okButton = new QPushButton(this);
      okButton->setObjectName("okButton");
      okButton->setText("OK");
      okButton->setDefault(true);
      okButton->setAutoDefault(true);

      connect(clearButton, SIGNAL(clicked()), objectBrowserWidget, SLOT(clearClicked()));
      connect(toggleViewButton, SIGNAL(clicked()), this, SLOT(toggleViewClicked()));
      connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
      connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));

      ObjectBrowserDialogLayout->addWidget(clearButton, 2, 0);
      ObjectBrowserDialogLayout->addWidget(toggleViewButton, 2, 1);
      ObjectBrowserDialogLayout->addWidget(cancelButton, 2, 2);
      ObjectBrowserDialogLayout->addWidget(okButton, 2, 3);

      setTabOrder(okButton, clearButton);
      setTabOrder(clearButton, toggleViewButton);
      setTabOrder(toggleViewButton, cancelButton);
      setTabOrder(cancelButton, objectBrowserWidget);
    }
  else
    {
      okButton = new QPushButton(this);
      okButton->setObjectName("okButton");
      okButton->setText("Close");
      okButton->setDefault(true);
      okButton->setAutoDefault(true);
      ObjectBrowserDialogLayout->addWidget(okButton, 2, 1, 1, 1);

      connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));

      setTabOrder(okButton, objectBrowserWidget);
    }

  if (!name)
    setObjectName("ObjectBrowser");

  resize(420, 460);
  setWindowTitle(QString::fromUtf8("Object Browser"));
}

ObjectBrowserDialog::~ObjectBrowserDialog()
{}

void ObjectBrowserDialog::setOutputVector(std::vector< const CDataObject * > * pObjectVector)
{
  if (objectBrowserWidget) objectBrowserWidget->setOutputVector(pObjectVector);
}

void ObjectBrowserDialog::cancelClicked()
{
  close();
}

void ObjectBrowserDialog::okClicked()
{
  objectBrowserWidget->commitClicked();
  done(QDialog::Accepted);
}

void ObjectBrowserDialog::toggleViewClicked()
{
  if (toggleViewButton->text() == "Selected Items")
    toggleViewButton->setText("Tree View");
  else
    toggleViewButton->setText("Selected Items");

  objectBrowserWidget->toggleViewClicked();
}

void ObjectBrowserDialog::selectObjects(std::vector< const CDataObject * > * pObjectVector)
{
  if (objectBrowserWidget) objectBrowserWidget->selectObjects(pObjectVector);
}
