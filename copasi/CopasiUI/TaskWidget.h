/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TaskWidget.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/05 13:47:33 $
   End CVS Header */

#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include "copasi.h"
#include <qvariant.h>
#include <qwidget.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QCheckBox;
class QComboBox;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QTable;
//class CModel;
class CProgressBar;

class TaskWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    TaskWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TaskWidget();

    //the CopasiWidget interface
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

    virtual bool runTask() = 0;

  protected slots:
    virtual void runTaskClicked();
    virtual void CancelChangeClicked();
    virtual void ReportDefinitionClicked();
    virtual void outputDefinitionClicked();

  protected:
    std::string objKey;
    CProgressBar * mProgressBar;

    virtual bool loadTask() = 0;
    virtual bool saveTask() = 0;

    //these methods should be called by the loadTask() or saveTask() methods
    //of the derived classes. They handle the "executable" checkbox
    bool loadExecutable();
    bool saveExecutable();

    //these methods should be called by the constructor, loadTask(), or saveTask() methods
    //of the derived classes. They handle the method parameters table
    bool constructMethodParameterTable();
    bool loadMethodParameters();
    bool saveMethodParameters();
    //add label and table to the layout, using standard copasi design
    bool addMethodParameterTableToLayout(unsigned int row, unsigned int maxcol);

    //this method should be called at the beginning or the end of the runTask() method
    //of the derived classes, respectively
    bool commonBeforeRunTask();
    bool commonAfterRunTask();

    QFrame* lineButton;
    QFrame* tmpLine;
    QTable* parameterTable;
    QLabel* methodParLabel;

    QVBoxLayout* mainLayout;
    QGridLayout* TaskWidgetLayout;
    QHBoxLayout* buttonLayout;
    QHBoxLayout* nameLayout;

    QLabel* taskNameLabel;
  private:
    QCheckBox* bExecutable;
  protected:
    QCheckBox* setInitialState;

    QPushButton* runTaskButton;
    QPushButton* cancelChangeButton;
    QPushButton* reportDefinitionButton;
    QPushButton* outputDefinitionButton;
  };

#endif
