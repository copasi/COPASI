// Copyright (C) 2011 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQTaskMethodWidget
#define COPASI_CQTaskMethodWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTaskMethodWidget.h"
#include "copasi/utilities/CCopasiMethod.h"

class CCopasiTask;

class CQTaskMethodWidget: public QWidget, public Ui::CQTaskMethodWidget
{
  Q_OBJECT

public:
  CQTaskMethodWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

  virtual ~CQTaskMethodWidget();

  void setTask(CCopasiTask * pTask);

  void setValidMethods(const unsigned int * validMethods);

  void showMethodParameters(const bool & show);

  bool loadMethod();

  bool saveMethod();

  void clearHistory();

protected slots:

  void changeMethod(int);

protected:
  void addToHistory(CCopasiMethod * pMethod);
  void removeFromHistory(CCopasiMethod * pMethod);
  CCopasiMethod * getFromHistory(const CCopasiMethod::SubType & Type) const;
  void setActiveMethod(const CCopasiMethod::SubType & Type);

protected:
  CCopasiTask * mpTask;
  CCopasiMethod * mpMethod;
  CCopasiMethod * mpActiveMethod;
  std::map< CCopasiMethod::SubType, CCopasiMethod * > mMethodHistory;
  bool mShowMethods;
  bool mShowMethodParameters;
};

#endif // COPASI_CQTaskMethodWidget
