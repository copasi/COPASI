// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQCHECKMODELWINDOW_H
#define CQCHECKMODELWINDOW_H

#include "copasi/UI/CWindowInterface.h"
#include "copasi/UI/ui_CQCheckModelWindow.h"

class QMenu;
class QLineEdit;
class QComboBox;
class CModelAnalyzer;

class CQCheckModelWindow : public CWindowInterface, public Ui::CQCheckModelWindow
{
  Q_OBJECT

public:
  void setAnalyzer(CModelAnalyzer* analyzer);

  explicit CQCheckModelWindow(CopasiUI3Window * pMainWindow);

  virtual ~CQCheckModelWindow();

  //return a pointer to this plot windows 'window' menu.
  virtual QMenu *getWindowMenu() const;

public slots:

  void slotSaveAs();
  void displayResult();
  void findNext();
  void findText(const QString& text);

private:
  bool mbInitializing;
  CopasiUI3Window * mpMainWindow;
  CModelAnalyzer* mpAnalyzer;
  QComboBox* mpSelection;
  QLineEdit* mpFindBox;
};

#endif // CQCHECKMODELWINDOW_H
