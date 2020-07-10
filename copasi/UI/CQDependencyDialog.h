// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQDEPENDENCYDIALOG_H
#define CQDEPENDENCYDIALOG_H

#include <string>

#include <QMainWindow>

#include <copasi/UI/CWindowInterface.h>
#include "copasi/UI/ui_CQDependencyDialog.h"

class CQDependencyDialog : public CWindowInterface, public Ui::CQDependencyDialog
{
  Q_OBJECT

public:
  explicit CQDependencyDialog(QWidget* parent, const char* name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQDependencyDialog();

  virtual QMenu *getWindowMenu() const;
  void setParentWindow(CopasiUI3Window* pPW);

  void loadFrom(const std::string& key);

  std::string getCurrentKey() const;
  void setCurrentKey(const std::string &currentKey);

public slots:
  void closeDialog();

protected:

  void closeEvent(QCloseEvent* e);

private:
  CopasiUI3Window* mpParentWindow;
  std::string mCurrentKey;
};

#endif // CQDEPENDENCYDIALOG_H
