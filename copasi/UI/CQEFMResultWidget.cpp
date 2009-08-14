// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMResultWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/08/14 13:41:37 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQEFMResultWidget.h"

CQEFMResultWidget::CQEFMResultWidget(QWidget* parent, const char* name) :
    CopasiWidget(parent, name)
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

bool CQEFMResultWidget::leave()
{
  return true;
}

bool CQEFMResultWidget::update(ListViews::ObjectType objectType,
                               ListViews::Action action,
                               const std::string & key)
{
  return true;
}

bool CQEFMResultWidget::enterProtected()
{
  return true;
}

void CQEFMResultWidget::slotSave()
{
  return;
}
