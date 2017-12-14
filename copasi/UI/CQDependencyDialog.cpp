// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQDependencyDialog.h"
#include "ui_CQDependencyDialog.h"

#include "copasiui3window.h"
#include "qtUtilities.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

CQDependencyDialog::CQDependencyDialog(QWidget *parent, const char *name, bool modal, Qt::WindowFlags fl)
  : CWindowInterface(parent, fl)
  , ui(new Ui::CQDependencyDialog)
  , mpParentWindow(NULL)
  , mCurrentKey()
{
  ui->setupUi(this);
  ui->widget->setVisibleDependencies(ALL_DEPENDENCIES);
  ui->widget->setLabelWidth(100);
  ui->widget->setStyleSheet("");
}

CQDependencyDialog::~CQDependencyDialog()
{
  delete ui;
}

void CQDependencyDialog::closeEvent(QCloseEvent* e)
{
  CWindowInterface::closeEvent(e);

  closeDialog();
}

void CQDependencyDialog::closeDialog()
{
  if (mpParentWindow)
    {
      mpParentWindow->slotShowDependencies(false);
    }
}

std::string CQDependencyDialog::getCurrentKey() const
{
  return mCurrentKey;
}

void CQDependencyDialog::setCurrentKey(const std::string &currentKey)
{
  mCurrentKey = currentKey;
}

QMenu *CQDependencyDialog::getWindowMenu() const
{
  return ui->mpWindowMenu;
}

void CQDependencyDialog::setParentWindow(CopasiUI3Window *pPW)
{
  mpParentWindow = pPW;
}

void CQDependencyDialog::loadFrom(const std::string &key)
{
  CDataObject* pObject = CRootContainer::getKeyFactory()->get(key);

  if (pObject == NULL) return;

  ui->mpLabel->setText(QString("Dependencies for %1: %2")
                       .arg(FROM_UTF8(pObject->getObjectType()))
                       .arg(FROM_UTF8(pObject->getObjectName())));
  ui->widget->loadFrom(pObject);
}
