/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MyLineEdit.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:55 $
   End CVS Header */

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
