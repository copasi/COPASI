/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MyLineEdit.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/20 13:36:30 $
   End CVS Header */

#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QWidget * parent, const char * name)
    : QLineEdit(parent, name)
{
  mChanged = false;
  mOldText = text();
  setupWidget();
}

MyLineEdit::MyLineEdit(const QString & contents, QWidget * parent, const char * name)
    : QLineEdit(contents, parent, name)
{
  mChanged = false;
  mOldText = contents;
  setupWidget();
}

void MyLineEdit::setupWidget()
{
  connect(this, SIGNAL(lostFocus()), this, SLOT(slotLostFocus()));
  connect(this, SIGNAL(returnPressed()), this, SLOT(slotReturnPressed()));
  connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(slotTextChanged(const QString &)));

  mOldColor = paletteBackgroundColor();
  int h, s, v;
  mOldColor.getHsv(&h, &s, &v);
  if (s < 20) s = 20;
  mNewColor.setHsv(240, s, v);
}

void MyLineEdit::process()
{
  if (mChanged)
    {
      mChanged = false;
      mOldText = text();
      emit edited();
    }
}

void MyLineEdit::slotLostFocus()
{process();}

void MyLineEdit::slotReturnPressed()
{process();}

void MyLineEdit::slotForceUpdate()
{process();}

void MyLineEdit::slotTextChanged(const QString & text)
{
  if (text != mOldText)
    {
      mChanged = true;
      setPaletteBackgroundColor(mNewColor);
    }
  else
    {
      mChanged = false;
      setPaletteBackgroundColor(mOldColor);
    }
}

void MyLineEdit::setText(const QString & text)
{
  mChanged = false;
  mOldText = text;
  QLineEdit::setText(text);
}
