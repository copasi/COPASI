#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <qlineedit.h>

class MyLineEdit: public QLineEdit
  {
    Q_OBJECT
  public:
    MyLineEdit(QWidget * parent = 0, const char * name = 0);
    MyLineEdit (const QString & contents, QWidget * parent, const char * name = 0);
    void focusOutEvent (QFocusEvent *);
  protected:
    bool deleteConfirmation;

  signals:
    void edited();
  };

#endif
