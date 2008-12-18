// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/AboutDialog.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:54:59 $
// End CVS Header

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

#include "qdialog.h"
//Added by qt3to4:
#include <QPixmap>
#include <Q3VBoxLayout>

class Q3TextEdit;
class QPushButton;
class QPixmap;
class Q3VBoxLayout;

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
    Q3TextEdit* textEdit;
    QPixmap* backgroundPixmap;
    Q3VBoxLayout* mainLayout;
  };

#endif
