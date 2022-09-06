// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQTaskMethodWidget
#define COPASI_CQTaskMethodWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTaskMethodWidget.h"
#include "copasi/utilities/CTaskEnum.h"

class CCopasiTask;
class CCopasiMethod;
class CQParameterGroupDM;
class CQComboDelegate;
class CQPushButtonDelegate;
class CCopasiParameterGroup;

class CQTaskMethodWidget: public QWidget, public Ui::CQTaskMethodWidget
{
  Q_OBJECT

public:
  CQTaskMethodWidget(QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());

  virtual ~CQTaskMethodWidget();

  void setTask(CCopasiTask * pTask);

  void setValidMethods(const CTaskEnum::Method * validMethods);

  bool loadMethod();

  bool saveMethod();

  void clearHistory();

  void pushMethod(CCopasiMethod * pMethod);

  void popMethod(CCopasiMethod * pMethod);

  void showMethodCheckbox(bool show);

public slots:
  void slotChangeMethod(int);
  void showMethodParameters(bool show);

protected:
  void addToHistory(CCopasiMethod * pMethod);
  void removeFromHistory(CCopasiMethod * pMethod);
  CCopasiMethod * getFromHistory(const CTaskEnum::Method & Type) const;
  void setActiveMethod(const CTaskEnum::Method & Type);

protected:
  CCopasiTask * mpTask;
  CCopasiMethod * mpMethod;
  CCopasiMethod * mpActiveMethod;
  std::map< CTaskEnum::Method, CCopasiMethod * > mMethodHistory;
  bool mShowMethods;
  bool mShowMethodParameters;
};

#endif // COPASI_CQTaskMethodWidget
