// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit: public QLineEdit
{
  Q_OBJECT
public:
  MyLineEdit(QWidget * parent = 0, const char * name = 0);
  MyLineEdit(const QString & contents, QWidget * parent, const char * name = 0);
  bool isValid();

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
