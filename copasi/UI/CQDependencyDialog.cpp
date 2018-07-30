// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQDependencyDialog.h"

#include "copasiui3window.h"
#include "qtUtilities.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

#include <copasi/core/CRootContainer.h>
#include <copasi/core/CDataVector.h>
#include <copasi/CopasiDataModel/CDataModel.h>

CQDependencyDialog::CQDependencyDialog(QWidget *parent, const char *name, bool modal, Qt::WindowFlags fl)
  : CWindowInterface(parent, fl)
  , mpParentWindow(NULL)
  , mCurrentKey()
{
  setupUi(this);

  widget->setVisibleDependencies(ALL_DEPENDENCIES);
  widget->setLabelWidth(100);
  widget->setStyleSheet("");
}

CQDependencyDialog::~CQDependencyDialog()
{}

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
  return mpWindowMenu;
}

void CQDependencyDialog::setParentWindow(CopasiUI3Window *pPW)
{
  mpParentWindow = pPW;
}

void CQDependencyDialog::loadFrom(const std::string &key)
{
  const CDataObject * pObject = CRootContainer::getKeyFactory()->get(key);

  CDataVector< CDataModel > * dmList = CRootContainer::getDatamodelList();

  if (pObject == NULL && !dmList->empty())
    {
      CDataModel & dm = dmList->operator[](dmList->size() - 1);
      // might be a cn
      pObject = CObjectInterface::DataObject(dm.getObjectFromCN(key));

      if (pObject == NULL)
        return;
    }

  mpLabel->setText(QString("Dependencies for %1: %2")
                   .arg(FROM_UTF8(pObject->getObjectType()))
                   .arg(FROM_UTF8(pObject->getObjectName())));
  widget->loadFrom(pObject);
}
