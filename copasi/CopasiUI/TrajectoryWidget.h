/****************************************************************************
 ** Form interface generated from reading ui file '.\TrajectoryWidget.ui'
 **
 ** Created: Sun Mar 2 20:34:14 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#ifndef TRAJECTORYWIDGET_H
#define TRAJECTORYWIDGET_H
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
class CTrajectoryTask;
class CTrajectoryProblem;
class CTrajectoryMethod;
class CModel;

class TrajectoryWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    TrajectoryWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TrajectoryWidget();
    CTrajectoryTask* mTrajectoryTask;
    void loadTrajectoryTask(CTrajectoryTask *trajectorytask);

    QFrame* line8;
    QTable* parameterTable;
    QLabel* taskNameLabel;
    QFrame* line7;
    QFrame* line7_2;
    QLineEdit* taskName;
    QComboBox* ComboBox1;
    QLineEdit* nStartTime;
    QCheckBox* bExecutable;
    QLabel* parameterValueLabel;
    QLabel* TextLabel1;
    QLabel* TextLabel1_3;
    QLabel* TextLabel1_3_2;
    QLineEdit* nStepSize;
    QLabel* TextLabel1_2_2;
    QLineEdit* nEndTime;
    QLineEdit* nStepNumber;
    QLabel* TextLabel1_2;
    QFrame* line6;
    QPushButton* bRunTask;
    QPushButton* commitChange;
    QPushButton* cancelChange;
    QPushButton* ExportToFileButton;

  signals:
    virtual void runFinished(CModel*);

  public slots:
    virtual void CancelChange();
    virtual void CommitChange();
    virtual void EnableRunTask();
    virtual void ExportToFile();
    virtual void RunTask();
    virtual void UpdateMethod();

  protected:
    QGridLayout* TrajectoryWidgetLayout;
    QHBoxLayout* Layout2;
  };

#endif // TRAJECTORYWIDGET_H
