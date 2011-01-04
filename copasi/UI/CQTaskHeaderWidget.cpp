// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskHeaderWidget.cpp,v $
//   $Revision: 1.9.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/04 13:57:48 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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

void CQTaskHeaderWidget::languageChange()
{
  retranslateUi(this);
}

bool CQTaskHeaderWidget::setTaskName(const std::string & name)
{
  mpLblName->setText("<h2>" + FROM_UTF8(name) + "</h2>");
  return true;
}

void CQTaskHeaderWidget::saved()
{
  mUpdateChanged = false;
  mpUpdateModel->setPaletteBackgroundColor(mSavedColor);

  mExecutableChanged = false;
  mpBoxExecutable->setPaletteBackgroundColor(mSavedColor);
}

void CQTaskHeaderWidget::slotUpdate()
{
  mUpdateChanged = !mUpdateChanged;

  if (mUpdateChanged)
    mpUpdateModel->setPaletteBackgroundColor(mChangedColor);
  else
    mpUpdateModel->setPaletteBackgroundColor(mSavedColor);
}

void CQTaskHeaderWidget::slotExecutable()
{
  mExecutableChanged = !mExecutableChanged;

  if (mExecutableChanged)
    mpBoxExecutable->setPaletteBackgroundColor(mChangedColor);
  else
    mpBoxExecutable->setPaletteBackgroundColor(mSavedColor);
}
