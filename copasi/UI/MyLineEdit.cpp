// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "MyLineEdit.h"
#include <QtGui/QValidator>

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
  connect(this, SIGNAL(editingFinished()), this, SLOT(slotLostFocus()));
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
