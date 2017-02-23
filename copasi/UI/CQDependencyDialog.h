// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQDEPENDENCYDIALOG_H
#define CQDEPENDENCYDIALOG_H

#include <string>

#include <QMainWindow>

#include <copasi/UI/CWindowInterface.h>

namespace Ui
{
class CQDependencyDialog;
}

class CQDependencyDialog : public CWindowInterface
{
  Q_OBJECT

public:
  explicit CQDependencyDialog(QWidget* parent, const char* name = 0, bool modal = false, Qt::WFlags fl = 0);
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
  Ui::CQDependencyDialog *ui;
  CopasiUI3Window* mpParentWindow;
  std::string mCurrentKey;

};

#endif // CQDEPENDENCYDIALOG_H
