/****************************************************************************
 **  $ CopasiUI/ScanWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Scan Widget
 *****************************************************************************/
#ifndef SCANWIDGET_H
#define SCANWIDGET_H

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
class QTable;
class CSteadyStateTask;
class CSteadyStateProblem;
class CSteadyStateMethod;
class CModel;

class ScanWidget : public QWidget
  {
    Q_OBJECT

  public:
    ScanWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ScanWidget();
    CSteadyStateTask *mSteadyStateTask;
    void loadScan(CSteadyStateTask* steadystatetask);

    QFrame* line7;
    QFrame* line6;
    QFrame* line8;
    QFrame* line8_2;
    QLabel* taskNameLabel;
    QCheckBox* taskJacobian;
    QLabel* taskDescriptionLabel;
    QLabel* parameterValueLabel;
    QCheckBox* taskStability;
    QCheckBox* bExecutable;
    QLineEdit* taskName;
    QTable* parameterTable, *parameterTable1;
    QPushButton* bRunButton;
    QPushButton* commitChange;
    QPushButton* cancelChange;
    QPushButton* ExportFileButton;

  signals:
    virtual void runFinished(CModel*);

  public slots:
    virtual void CancelChange();
    virtual void CommitChange();
    // virtual void ExportToFile();
    //virtual void parameterValueChanged();
    //virtual void RunButtonClicked();
    //virtual void RunTask();

  protected:
    QGridLayout* ScanWidgetLayout;
    QHBoxLayout* Layout2;
  };

#endif
