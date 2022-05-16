// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
    \file AboutDialog.h
    \brief Header file of class AboutDialog
 */

#ifndef AboutDialog_H__
#define AboutDialog_H__

#include <QDialog>

class QTextEdit;
class QPushButton;
class QPixmap;
class QVBoxLayout;

class AboutDialog: public QDialog
{
  Q_OBJECT

public:
  AboutDialog(QWidget *parent,
              const QString &text,
              const int &width,
              const int &heigth);
  virtual ~AboutDialog();

  static QString getDefaultVersionText();
  static const char *text;

protected slots:
  void closeButton_clicked();

protected:
  QTextEdit *textEdit;
  QVBoxLayout *mainLayout;
};

#endif
