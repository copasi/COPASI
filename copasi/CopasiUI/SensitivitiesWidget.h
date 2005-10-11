/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SensitivitiesWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/11 16:33:26 $
   End CVS Header */

#ifndef SENSWIDGET_H
#define SENSWIDGET_H

#include "copasi.h" 
//#include <qvariant.h>
//#include <qwidget.h>
#include "TaskWidget.h"

//class QVBoxLayout;
//class QHBoxLayout;
//class QGridLayout;
//class QCheckBox;
//class QFrame;
//class QLabel;
//class QLineEdit;
//class QPushButton;
//class QRadioButton;
//class QTable;

class SensitivitiesWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    //virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    //virtual bool leave();
    //virtual bool enter(const std::string & key = "");

    explicit SensitivitiesWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~SensitivitiesWidget();

    virtual bool runTask();

  protected:
    virtual bool loadTask();
    virtual bool saveTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    //QCheckBox* taskJacobian;
    //QCheckBox* taskStability;
    //QLabel* taskDescriptionLabel;
    //QLabel* parameterValueLabel;
    //QCheckBox* bExecutable;
    // QCheckBox* setInitialState;
    //QLineEdit* taskName;
    //QTable* parameterTable;
    //QPushButton* bRunButton;
    //QPushButton* cancelChange;
    //QPushButton* ExportFileButton;
    //QPushButton* reportDefinitionButton;

  public slots:
    //virtual void CancelButtonClicked();
    //virtual void CommitButtonClicked();
    //virtual void ExportToFileButtonClicked();
    //virtual void parameterValueChanged();
    //virtual void RunButtonChecked();
    //virtual void runTask();
    //virtual void ReportDefinitionClicked();

  protected:
    //QVBoxLayout* SensitivitiesWidgetLayout;
    //QGridLayout* mpGridLayout;
    //QTable* mpTblParameter;
    //QLabel* mpLblParameter;
  };

#endif // STEADYSTATEWIDGET_H
