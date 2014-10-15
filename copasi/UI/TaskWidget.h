// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QtGui/QGridLayout>
#include <QtGui/QTableWidget>
#include <QtGui/QLabel>

#include "copasi/copasi.h"

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/UI/copasiWidget.h"

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

//class CModel;
class CProgressBar;

class CopasiPlot;
class CCopasiException;

class TaskWidget : public CopasiWidget
{
  Q_OBJECT

public:
  TaskWidget(QWidget* parent = 0,
             const char* name = 0,
             Qt::WFlags fl = 0);

  ~TaskWidget();

  //the TaskWidget interface
  virtual bool update(ListViews::ObjectType objectType,
                      ListViews::Action action,
                      const std::string & key);

  virtual bool leave();

  virtual bool runTask() = 0;

  CCopasiTask* getTask();

protected slots:
  void runBtnClicked();

  void revertBtnClicked();

  void reportBtnClicked();

  void assistantBtnClicked();

public slots:

  void adjustTable();

  void slotFinishThread();

protected:
  virtual bool enterProtected();

  virtual bool loadTask() = 0;

  virtual bool saveTask() = 0;

  CCopasiMethod * createMethod(const CTaskEnum::Method & type);

  //these methods should be called by the loadTask() or saveTask() methods
  //of the derived classes. They handle the "executable" checkbox
  bool loadCommon();
  bool saveCommon();

  bool loadMethod();
  bool saveMethod();
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
  CCopasiMethod * mpMethod;

  bool mChanged;
  CQTaskThread *mpTaskThread;
};

#endif
