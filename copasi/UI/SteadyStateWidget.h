/****************************************************************************
 ** Form interface generated from reading ui file '.\SteadyStateWidget.ui'
 **
 ** Created: Thu Feb 13 12:57:19 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#ifndef STEADYSTATEWIDGET_H
#define STEADYSTATEWIDGET_H
#include "copasi.h"
#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QCheckBox;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QTable;
class CSteadyStateTask;
class CSteadyStateProblem;
class CSteadyStateMethod;

class SteadyStateWidget : public QWidget
  {
    Q_OBJECT

  public:
    SteadyStateWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~SteadyStateWidget();
    CSteadyStateTask *mSteadyStateTask;
    void loadSteadyStateTask(CSteadyStateTask* steadystatetask);

    QFrame* line8;
    QFrame* line7;
    QLabel* taskDescriptionLabel;
    QRadioButton* taskJacobian;
    QRadioButton* taskStability;
    QFrame* line6;
    QLabel* taskNameLabel;
    QPushButton* bRunButton;
    QPushButton* commitChange;
    QPushButton* cancelChange;
    QLineEdit* taskName;
    QLabel* parameterValueLabel;
    QTable* parameterTable;
    QCheckBox* bExecutable;

  public slots:
    virtual void CancelChange();
    virtual void CommitChange();
    virtual void methodJacob();
    virtual void methodStability();
    virtual void RunButtonClicked();
    virtual void parameterValueChanged();
    virtual void RunTask();
    virtual void taskNameChanged();

  protected:
    QHBoxLayout* Layout5;
  };

#endif // STEADYSTATEWIDGET_H
