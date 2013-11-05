// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
    \file AboutDialog.h
    \brief Header file of class AboutDialog
 */

#ifndef AboutDialog_H__
#define AboutDialog_H__

#include <QtGui/QDialog>

class QTextEdit;
class QPushButton;
class QPixmap;
class QVBoxLayout;

class AboutDialog: public QDialog
{
  Q_OBJECT

public:
  AboutDialog(QWidget* parent,
              const QString & text,
              const int & width,
              const int & heigth);
  virtual ~AboutDialog();

  static const char* text;

protected slots:
  void closeButton_clicked();

protected:
  QPushButton* closeButton;
  QTextEdit* textEdit;
  QVBoxLayout* mainLayout;
};

#endif
