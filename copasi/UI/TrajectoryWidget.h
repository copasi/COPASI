/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TrajectoryWidget.h,v $
   $Revision: 1.24 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/30 11:46:43 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 02/03 
Comment : TrajectoryWidget
Contact: Please contact lixu1@vt.edu.
 *********************************************************/
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

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

    //void setModel(CModel* newModel);

  signals:
    //virtual void runFinished(CModel*);

  protected slots:
    virtual void CancelChange();
    virtual void CommitChange();
    //virtual void EnableRunTask();
    virtual void ExportToFile();
    virtual void runTrajectoryTask();
    virtual void UpdateMethod(const bool & update = true);
    virtual void ReportDefinitionClicked();

    virtual void StartTimeSlot();
    virtual void EndTimeSlot();
    virtual void StepsizeSlot();
    virtual void NumStepsSlot();

  private:

    std::string objKey;
    void loadTrajectoryTask();
    void saveTrajectoryTask();
    void loadMethodParameters();

    QWidget* pParent;
    QGridLayout* TrajectoryWidgetLayout;
    QHBoxLayout* Layout2;
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
    //    QPushButton* commitChange;
    QPushButton* cancelChange;
    QPushButton* ExportToFileButton;
    QPushButton* reportDefinitionButton;
  };

#endif // TRAJECTORYWIDGET_H
