/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SteadyStateWidget.h,v $
   $Revision: 1.28 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/10/04 09:55:52 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 02/03 
Comment : SteadyStateWidget
Contact: Please contact lixu1@vt.edu.
 *********************************************************/
#ifndef STEADYSTATEWIDGET_H
#define STEADYSTATEWIDGET_H

#include "copasi.h"
#include <qvariant.h>
#include <qwidget.h>
#include "copasiWidget.h"

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
class CModel;

class SteadyStateWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

    SteadyStateWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~SteadyStateWidget();
    //    CSteadyStateTask *mSteadyStateTask;
    //   CSteadyStateTask* getSteadyStateTask() const {return mSteadyStateTask;};

    void loadSteadyStateTask();
    //    void setModel(CModel* newModel);

    QFrame* line7;
    QFrame* line6;
    QFrame* line8;
    QFrame* line8_2;
    QLabel* taskNameLabel;
    QRadioButton* taskJacobian;
    QLabel* taskDescriptionLabel;
    QLabel* parameterValueLabel;
    QRadioButton* taskStability;
    QCheckBox* bExecutable;
    QLineEdit* taskName;
    QTable* parameterTable;
    QPushButton* bRunButton;
    QPushButton* cancelChange;
    QPushButton* ExportFileButton;
    QPushButton* reportDefinitionButton;

  signals:
    //virtual void runFinished(CModel*);

  public slots:
    virtual void CancelButtonClicked();
    virtual void CommitButtonClicked();
    virtual void ExportToFileButtonClicked();
    virtual void parameterValueChanged();
    //virtual void RunButtonChecked();
    virtual void runSteadyStateTask();
    virtual void ReportDefinitionClicked();

  protected:
    QGridLayout* SteadyStateWidgetLayout;
    QHBoxLayout* Layout2;
    std::string objKey;
    QWidget* pParent;
  };

#endif // STEADYSTATEWIDGET_H
