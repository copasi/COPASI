/****************************************************************************
 ** Form interface generated from reading ui file '.\TrajectoryWidget.ui'
 **
 ** Created: Sun Mar 2 14:02:22 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#ifndef TRAJECTORYWIDGET_H
#define TRAJECTORYWIDGET_H
#include "copasi.h"
#include <qvariant.h>
#include <qwidget.h>

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

class TrajectoryWidget : public QWidget
  {
    Q_OBJECT

  public:
    TrajectoryWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TrajectoryWidget();
    CTrajectoryTask* mTrajectoryTask;
    void loadTrajectoryTask(CTrajectoryTask *trajectorytask);

    QFrame* line6;
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
    QPushButton* bRunTask;
    QPushButton* commitChange;
    QPushButton* cancelChange;

  public slots:
    virtual void CancelChange();
    virtual void CommitChange();
    virtual void EnableRunTask();
    virtual void UpdateMethod();
    virtual void RunTask();

  protected:
    QGridLayout* TrajectoryWidgetLayout;
    QHBoxLayout* Layout2;
  };

#endif // TRAJECTORYWIDGET_H
