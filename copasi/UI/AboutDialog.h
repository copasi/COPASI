// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/AboutDialog.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/07/16 19:05:20 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
