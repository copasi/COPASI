#include <qmessagebox.h>
#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QWidget * parent, const char * name)
    : QLineEdit(parent, name)
{
}

MyLineEdit::MyLineEdit(const QString & contents, QWidget * parent, const char * name)
    : QLineEdit(contents, parent, name)
{
}

void MyLineEdit::focusOutEvent(QFocusEvent *fe)
{
  //QMessageBox::information(this, "got it", "yipeee ");
  emit edited();
}