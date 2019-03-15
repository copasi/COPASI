// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef VIEW_CURRENT_WORKER
#define VIEW_CURRENT_WORKER

#include <QtCore/QObject>
#include "copasi/UI/DataModelGUI.h"
#include "copasi/UI/listviews.h"

class CopasiUI3Window;
class Arguments;
class CCopasiTask;
class TaskWidget;

class Worker : public QObject
{
  Q_OBJECT

public:

  Worker(CopasiUI3Window* window, Arguments* args);

  static int getIndexForTask(CCopasiTask* task);

public slots:

  void finishedLoading(bool success);

  bool slotNotify(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);

private:

  TaskWidget* getWidgetForTask(CCopasiTask* task) const;

  static int getIndexForWidget(TaskWidget* widget);

  CopasiUI3Window* mpWindow;

  DataModelGUI* mpDataModel;

  Arguments *mpArgs;

  bool mTaskStarted;
};

#endif
