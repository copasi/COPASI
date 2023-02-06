// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QtCore/QVariant>

#include <QGridLayout>
#include <QTableWidget>
#include <QLabel>

#include "copasi/UI/copasiWidget.h"
#include "copasi/utilities/CTaskEnum.h"

class CQTaskThread;
class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpacerItem;

class CQTaskHeaderWidget;
class CQTaskMethodWidget;
class CQTaskBtnWidget;

class CCopasiTask;
class CCopasiMethod;

//class CModel;
class CProgressBar;

class CCopasiException;

class TaskWidget : public CopasiWidget
{
  Q_OBJECT

public:
  TaskWidget(QWidget* parent = 0,
             const char* name = 0,
             Qt::WindowFlags fl = Qt::WindowFlags());

  ~TaskWidget();

  virtual bool runTask() = 0;

  CCopasiTask* getTask();

protected slots:

  void revertBtnClicked();

  void reportBtnClicked();

  void assistantBtnClicked();

public slots:

  void runBtnClicked();

  void adjustTable();

  void slotFinishThread();

private:
  bool loadTask();
  bool saveTask();

  bool loadCommon();
  bool saveCommon();

  bool loadMethod();
  bool saveMethod();

protected:

  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  virtual bool loadTaskProtected() = 0;
  virtual bool saveTaskProtected() = 0;

  CCopasiMethod * createMethod(const CTaskEnum::Method & type);

  virtual bool taskFinishedEvent();

  //this method should be called at the beginning or the end of the runTask() method
  //of the derived classes, respectively
  bool commonBeforeRunTask();
  bool commonAfterRunTask();

  bool commonRunTask();
  void finishTask();

  CProgressBar * mProgressBar;
  CQTaskHeaderWidget * mpHeaderWidget;
  CQTaskMethodWidget * mpMethodWidget;
  CQTaskBtnWidget * mpBtnWidget;
  QGridLayout * mpMethodLayout;

  QSpacerItem * mpSpacer1;
  QSpacerItem * mpSpacer2;

  CCopasiTask * mpTask;

  bool mChanged;
  CQTaskThread *mpTaskThread;
  bool mIgnoreProblemData;
};

#endif
