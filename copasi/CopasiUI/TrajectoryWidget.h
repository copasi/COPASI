/****************************************************************************
 ** Form interface generated from reading ui file '.\TrajectoryWidget.ui'
 **
 ** Created: Tue Feb 11 14:01:14 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#ifndef TRAJECTORYWIDGET_H
#define TRAJECTORYWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QSplitter;
class QTable;

class TrajectoryWidget : public QWidget
  {
    Q_OBJECT

  public:
    TrajectoryWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TrajectoryWidget();

    QFrame* line6;
    QSplitter* splitter3;
    QPushButton* commitChange;
    QPushButton* cancelChange;
    QFrame* line8;
    QLabel* taskNameLabel;
    QFrame* line7;
    QSplitter* splitter11;
    QLabel* parameterValueLabel;
    QTable* parameterTable;
    QLabel* TextLabel1;
    QLabel* TextLabel1_3;
    QLineEdit* nStepSize;
    QLineEdit* taskName;
    QLineEdit* nStepSize_2;
    QLabel* TextLabel1_2;
    QLabel* TextLabel1_2_2;
    QLineEdit* nStepNumber;
    QLineEdit* nStepNumber_2;

  public slots:
    virtual void taskNameChanged();
    virtual void methodJacob();
    virtual void methodStability();
    virtual void parameterValueChanged();
    virtual void CommitChange();
    virtual void CancelChange();

  protected:
    QVBoxLayout* layout15;
  };

#endif // TRAJECTORYWIDGET_H
