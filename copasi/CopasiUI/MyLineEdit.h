/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MyLineEdit.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:44 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <qlineedit.h>

class MyLineEdit: public QLineEdit
  {
    Q_OBJECT
  public:
    MyLineEdit(QWidget * parent = 0, const char * name = 0);
    MyLineEdit (const QString & contents, QWidget * parent, const char * name = 0);

  protected:
    QColor mOldColor;
    QColor mNewColor;
    QColor mErrorColor;

    void process();
    void setupWidget();

    virtual void updateColor();

  protected slots:
    void slotLostFocus();
    void slotReturnPressed();
    void slotTextChanged(const QString & text);

  public slots:
    //force processing of changes in the LineEdit widget. This is
    //needed when the ReturnPressed and LostFocus signals do not apply
    void slotForceUpdate();

    virtual void setText(const QString & text);

  signals:
    void edited();
  };

#endif
