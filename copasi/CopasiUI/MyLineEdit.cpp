/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MyLineEdit.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: chlee $ 
   $Date: 2003/10/23 19:15:50 $
   End CVS Header */

#include <qmessagebox.h>
#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QWidget * parent, const char * name)
    : QLineEdit(parent, name)
{}

MyLineEdit::MyLineEdit(const QString & contents, QWidget * parent, const char * name)
    : QLineEdit(contents, parent, name)
{}

void MyLineEdit::focusOutEvent(QFocusEvent *fe)
{
  //QMessageBox::information(this, "got it", "yipeee ");
  QLineEdit::focusOutEvent(fe);
  emit edited();
}
