/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/MyLineEdit.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:39 $
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
  emit edited();
}
