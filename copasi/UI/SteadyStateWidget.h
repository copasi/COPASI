/****************************************************************************
 ** Form interface generated from reading ui file '.\SteadyStateWidget.ui'
 **
 ** Created: Tue Feb 4 16:45:46 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#ifndef STEADYSTATEWIDGET_H
#define STEADYSTATEWIDGET_H

#include <qvariant.h>
#include <qwidget.h> 
//#include "model/model.h"
#include "copasi.h"
#include "Structures.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QSplitter;
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

    QFrame* line6;
    QSplitter* splitter3;
    QPushButton* commitChange;
    QPushButton* cancelChange;
    QSplitter* splitter11;
    QLabel* parameterValueLabel;
    QTable* parameterTable;
    QFrame* line8;
    QSplitter* splitter12;
    QLabel* taskDescriptionLabel;
    QRadioButton* taskJacobian;
    QRadioButton* taskStability;
    QFrame* line7;
    QSplitter* splitter7;
    QLabel* taskNameLabel;
    QLineEdit* taskName;

  public slots:
    virtual void taskNameChanged();
    virtual void methodJacob();
    virtual void methodStability();
    virtual void parameterValueChanged();
    virtual void CommitChange();
    virtual void CancelChange();

  protected:
    QVBoxLayout* layout15;
    QVBoxLayout* layout14;
    QHBoxLayout* Layout2;
  };

#endif // STEADYSTATEWIDGET_H
