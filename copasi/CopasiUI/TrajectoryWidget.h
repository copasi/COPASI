/****************************************************************************
 ** Form interface generated from reading ui file '.\TrajectoryWidget.ui'
 **
 ** Created: Thu Feb 20 14:48:29 2003
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
class QComboBox;
class QCheckBox;
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

    QLabel* taskNameLabel;
    QCheckBox* bExecutable;
    QPushButton* commitChange;
    QPushButton* bRunTask;
    QPushButton* cancelChange;
    QFrame* line8;
    QFrame* line6;
    QLabel* parameterValueLabel;
    QTable* parameterTable;
    QFrame* line7;
    QFrame* line7_2;
    QLabel* TextLabel1;
    QLabel* TextLabel1_3;
    QLineEdit* taskName;
    QLabel* TextLabel1_3_2;
    QLineEdit* nStartTime;
    QComboBox* ComboBox1;
    QLineEdit* nStepSize;
    QLabel* TextLabel1_2_2;
    QLineEdit* nEndTime;
    QLineEdit* nStepNumber;
    QLabel* TextLabel1_2;

  public slots:
    virtual void CancelChange();
    virtual void CommitChange();
    virtual void EnableRunTask();
    virtual void RunTask();
  };

#endif // TRAJECTORYWIDGET_H
