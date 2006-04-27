/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/AboutDialog.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:40 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef AboutDialog_H__
#define AboutDialog_H__

#include "qdialog.h"

class QTextEdit;
class QPushButton;
class QPixmap;
class QVBoxLayout;

class AboutDialog: public QDialog
  {
    Q_OBJECT

  public:
    AboutDialog(QWidget* parent,
                const char * text,
                const int & width,
                const int & heigth);
    virtual ~AboutDialog();

    static const char* text;

  protected slots:
    void closeButton_clicked();

  protected:
    QPushButton* closeButton;
    QTextEdit* textEdit;
    QPixmap* backgroundPixmap;
    QVBoxLayout* mainLayout;
  };

#endif
