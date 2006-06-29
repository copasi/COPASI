/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SensitivitiesWidget.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/06/29 17:22:29 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SENSWIDGET_H
#define SENSWIDGET_H

#include "copasi.h"
//#include <qvariant.h>
//#include <qwidget.h>
#include "TaskWidget.h"
#include "sensitivities/CSensProblem.h"

class QComboBox;
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
    QVBoxLayout* SensitivitiesWidgetLayout;
    //QGridLayout* mpSensitivitiesLayout;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLabel* TextLabel4;

    QComboBox* SubTaskChooser;

    QComboBox* FunctionChooser;
    QLineEdit* FunctionLineEdit;
    //    QListView* FunctionChoiceBox;

    QComboBox* VariableChooser;
    QLineEdit* VariableLineEdit;
    //    QListView* VariableChoiceBox;

    QComboBox* VariableChooser2;
    QLineEdit* VariableLineEdit2;

  private:
    void initCombos();
    //std::vector<QCheckListItem *> initCheckboxes(CObjectLists::ListType);

    void updateFunctionsStringList(CSensProblem::SubTaskType);
    void updateVariablesStringList(CSensProblem::SubTaskType);

    QStringList mVariablesStringList;
    QStringList mFunctionsStringList;

    // for indexing the dynamic entries of our combo boxes:
    std::vector<CObjectLists::ListType> mVariablesIndexTable;
    std::vector<CObjectLists::ListType> mFunctionsIndexTable;

    // bitfield for checking if all mandatory choices are done:
    // 1 - SubTaskChooser
    // 2 - FunctionChooser
    // 4 - VariableChooser
    int mChoicesDone;

  private slots:
    void on_SubTaskChooser_activated(int);
    void on_FunctionChooser_activated(int);
    void on_VariableChooser_activated(int);
    void on_VariableChooser2_activated(int);
  };

#endif // SENSWIDGET_H
