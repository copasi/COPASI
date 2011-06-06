// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskHeaderWidget.cpp,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/06 16:14:07 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QPalette>
#include "CQTaskHeaderWidget.h"
#include "qtUtilities.h"

CQTaskHeaderWidget::CQTaskHeaderWidget(QWidget* parent, Qt::WindowFlags f):
    QWidget(parent, f)
{
  setupUi(this);

  mUpdateChanged = false;
  mExecutableChanged = false;

  int h, s, v;

  mSavedColor = paletteBackgroundColor();
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
