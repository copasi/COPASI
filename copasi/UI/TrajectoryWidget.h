/****************************************************************************
 ** Form interface generated from reading ui file '.\TrajectoryWidget.ui'
 **
 ** Created: Thu Feb 13 12:32:58 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#ifndef TRAJECTORYWIDGET_H
#define TRAJECTORYWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include "copasi.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
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

    QLabel* taskNameLabel;
    QFrame* line7;
    QLineEdit* nStepNumber_2;
    QTable* parameterTable;
    QFrame* line8;
    QLabel* TextLabel1_2;
    QLabel* parameterValueLabel;
    QLabel* TextLabel1_3;
    QLabel* TextLabel1_2_2;
    QLineEdit* nStepSize;
    QLineEdit* nStepNumber;
    QLabel* TextLabel1;
    QLineEdit* nStepSize_2;
    QCheckBox* bExecutable;
    QLineEdit* taskName;
    QFrame* line6;
    QPushButton* bRunTask;
    QPushButton* commitChange;
    QPushButton* cancelChange;

  public slots:
    virtual void CancelChange();
    virtual void CommitChange();
    virtual void RunTask();

  protected:
    QHBoxLayout* Layout7;
  };

#endif // TRAJECTORYWIDGET_H
