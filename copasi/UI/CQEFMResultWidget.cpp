// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMResultWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/29 16:35:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQEFMResultWidget.h"

#include "elementaryFluxModes/CEFMTask.h"
#include "elementaryFluxModes/CFluxMode.h"

CQEFMResultWidget::CQEFMResultWidget(QWidget* parent, const char* name) :
    CopasiWidget(parent, name),
    mpTask(NULL)
{
  setupUi(this);
}

CQEFMResultWidget::~CQEFMResultWidget()
{
}

void CQEFMResultWidget::languageChange()
{
  retranslateUi(this);
}

// virtual
bool CQEFMResultWidget::leave()
{
  return true;
}

// virtual
bool CQEFMResultWidget::update(ListViews::ObjectType /* objectType */,
                               ListViews::Action /* action */,
                               const std::string & /* key */)
{
  return true;
}

// virtual
bool CQEFMResultWidget::enterProtected()
{
  return true;
}

// virtual
bool CQEFMResultWidget::loadResult(const CCopasiTask * pTask)
{
  mpTask = dynamic_cast<const CEFMTask *>(pTask);

  if (mpTask != NULL)
    {
      mpEditFluxModes->setText(QString::number(mpTask->getFluxModes().size()));
    }
  else
    {
      mpEditFluxModes->setText(QString::number(0));
    }

  bool success = true;
  success &= mpEFMListWidget->loadResult(mpTask);

  return success;
}

void CQEFMResultWidget::slotSave()
{
  return;
}
