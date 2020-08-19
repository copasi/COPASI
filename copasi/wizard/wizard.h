// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#ifndef WIZARDDIALOG_H
#define WIZARDDIALOG_H

#include <QtCore/QVariant>

#include "copasi/wizard/ui_wizard.h"

class QUrl;

class WizardDialog : public QDialog, public Ui::WizardDialog
{
  Q_OBJECT

public:
  WizardDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
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
