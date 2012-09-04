#ifndef VIEW_CURRENT_WORKER
#define VIEW_CURRENT_WORKER

#include <QObject>

class CopasiUI3Window ;
class DataModelGUI ;
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

private:

  TaskWidget* getWidgetForTask(CCopasiTask* task) const;

  static int getIndexForWidget(TaskWidget* widget);

  CopasiUI3Window* mpWindow;

  DataModelGUI* mpDataModel;

  Arguments *mpArgs;

};

#endif

