/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MyLineEdit.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:49 $
   End CVS Header */

#include "MyLineEdit.h"
#include <qvalidator.h>

MyLineEdit::MyLineEdit(QWidget * parent, const char * name)
    : QLineEdit(parent, name)
{
  setupWidget();
}

MyLineEdit::MyLineEdit(const QString & contents, QWidget * parent, const char * name)
    : QLineEdit(contents, parent, name)
{
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

  mErrorColor.setHsv(0, s, v);
}

void MyLineEdit::process()
{
  if (isModified())
    {
      clearModified();
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

void MyLineEdit::slotTextChanged(const QString & text)
{
  updateColor();
}

void MyLineEdit::updateColor()
{
  if (isModified())
    {
      setPaletteBackgroundColor(mNewColor);
    }
  else
    {
      setPaletteBackgroundColor(mOldColor);
    }

  const QValidator * val = validator();
  int dummy = 0;
  QString ttt = text();
  if (val)
    if (val->validate(ttt, dummy) == QValidator::Intermediate)
      setPaletteBackgroundColor(mErrorColor);
}

void MyLineEdit::setText(const QString & text)
{
  QLineEdit::setText(text);
  updateColor();
}
