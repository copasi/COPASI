// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QtGui/QPalette>
#include "CQTaskHeaderWidget.h"
#include "qtUtilities.h"

CQTaskHeaderWidget::CQTaskHeaderWidget(QWidget* parent, Qt::WindowFlags f):
  QWidget(parent, f)
{
  setupUi(this);

  mUpdateChanged = false;
  mExecutableChanged = false;

  int h, s, v;

  mSavedColor = palette().color(backgroundRole());
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;

  mChangedColor.setHsv(240, s, v);
}

CQTaskHeaderWidget::~CQTaskHeaderWidget()
{
  // TODO Auto-generated destructor stub
}

bool CQTaskHeaderWidget::setTaskName(const std::string & name)
{
  mpLblName->setText("<h2>" + FROM_UTF8(name) + "</h2>");
  return true;
}

void CQTaskHeaderWidget::saved()
{
  mUpdateChanged = false;
  mpUpdateModel->setStyleSheet("background-color:" + mSavedColor.name() + ";");

  mExecutableChanged = false;
  mpBoxExecutable->setStyleSheet("background-color:" + mSavedColor.name() + ";");
}

void CQTaskHeaderWidget::slotUpdate()
{
  mUpdateChanged = !mUpdateChanged;

  if (mUpdateChanged)
    {
      mpUpdateModel->setStyleSheet("background-color:" + mChangedColor.name() + ";");
    }
  else
    {
      mpUpdateModel->setStyleSheet("background-color:" + mSavedColor.name() + ";");
    }
}

void CQTaskHeaderWidget::slotExecutable()
{
  mExecutableChanged = !mExecutableChanged;

  if (mExecutableChanged)
    {
      mpBoxExecutable->setStyleSheet("background-color:" + mChangedColor.name() + ";");
    }
  else
    {
      mpBoxExecutable->setStyleSheet("background-color:" + mSavedColor.name() + ";");
    }
}
