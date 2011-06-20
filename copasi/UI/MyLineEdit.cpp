// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/MyLineEdit.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/20 16:07:10 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "MyLineEdit.h"
#include <qvalidator.h>

MyLineEdit::MyLineEdit(QWidget * parent, const char * name)
    : QLineEdit(parent)
{
  setObjectName(name);
  setupWidget();
}

MyLineEdit::MyLineEdit(const QString & contents, QWidget * parent, const char * name)
    : QLineEdit(contents, parent)
{
  setObjectName(name);
  setupWidget();
}

void MyLineEdit::setupWidget()
{
  connect(this, SIGNAL(lostFocus()), this, SLOT(slotLostFocus()));
  connect(this, SIGNAL(returnPressed()), this, SLOT(slotReturnPressed()));
  connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(slotTextChanged(const QString &)));

  mOldColor = palette().color(backgroundRole());
  int h, s, v;
  mOldColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;

  mNewColor.setHsv(240, s, v);

  mErrorColor.setHsv(0, s, v);
}

void MyLineEdit::process()
{
  if (isModified())
    {
      setModified(false);
      updateColor();
      emit edited();
    }
}

void MyLineEdit::slotLostFocus()
{process();}

void MyLineEdit::slotReturnPressed()
{process();}

void MyLineEdit::slotForceUpdate()
{process();}

void MyLineEdit::slotTextChanged(const QString & /* text */)
{
  updateColor();
}

void MyLineEdit::updateColor()
{
  QPalette palette;

  if (isModified())
    {
      palette.setColor(backgroundRole(), mNewColor);
      setPalette(palette);
    }
  else
    {
      palette.setColor(backgroundRole(), mOldColor);
      setPalette(palette);
    }

  const QValidator * val = validator();

  int dummy = 0;

  QString ttt = text();

  if (val)
    if (val->validate(ttt, dummy) == QValidator::Intermediate)
      {
        QPalette palette;
        palette.setColor(backgroundRole(), mErrorColor);
        setPalette(palette);
      }
}

void MyLineEdit::setText(const QString & text)
{
  QLineEdit::setText(text);
  updateColor();
}

bool MyLineEdit::isValid()
{return (palette().color(backgroundRole()) != mErrorColor);}
