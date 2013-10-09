// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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
  QPalette palette;
  palette.setColor(mpUpdateModel->backgroundRole(), mSavedColor);
  mpUpdateModel->setPalette(palette);

  mExecutableChanged = false;
  palette.setColor(mpBoxExecutable->backgroundRole(), mSavedColor);
  mpBoxExecutable->setPalette(palette);
}

void CQTaskHeaderWidget::slotUpdate()
{
  mUpdateChanged = !mUpdateChanged;
  QPalette palette;

  if (mUpdateChanged)
    {
      palette.setColor(mpUpdateModel->backgroundRole(), mChangedColor);
      mpUpdateModel->setPalette(palette);
    }
  else
    {
      palette.setColor(mpUpdateModel->backgroundRole(), mSavedColor);
      mpUpdateModel->setPalette(palette);
    }
}

void CQTaskHeaderWidget::slotExecutable()
{
  mExecutableChanged = !mExecutableChanged;
  QPalette palette;

  if (mExecutableChanged)
    {
      palette.setColor(mpBoxExecutable->backgroundRole(), mChangedColor);
      mpBoxExecutable->setPalette(palette);
    }
  else
    {
      palette.setColor(mpBoxExecutable->backgroundRole(), mSavedColor);
      mpBoxExecutable->setPalette(palette);
    }
}
