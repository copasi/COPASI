// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/wizard/wizard.h,v $
//   $Revision: 1.12.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/13 21:47:07 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef WIZARDDIALOG_H
#define WIZARDDIALOG_H

#include <qvariant.h>

#include "copasi/wizard/ui_wizard.h"

class QUrl;

class WizardDialog : public QDialog, public Ui::WizardDialog
{
  Q_OBJECT

public:
  WizardDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~WizardDialog();

  static const char* texts[6];

  virtual void setCopasiMainWindow(QWidget * copasiMainWindow);

public slots:
  virtual void buttonGroup2_clicked(int);
  virtual void forwardButton_clicked();
  virtual void backButton_clicked();
  virtual void textBrowser_anchorClicked(const QUrl & url);

protected:
  static const char* Error;
  static QString helpPath;
  QWidget* copasiMainWindow;
  QButtonGroup * buttonGroup;

protected slots:


};

#endif // WIZARDDIALOG_H
