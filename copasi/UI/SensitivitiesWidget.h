/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SensitivitiesWidget.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/07/14 12:52:16 $
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

    enum ChoiceType {
      SubTask,
      Function,
      Variable,
      SecondVariable
    };
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
    void initCombos(CSensProblem);
    bool initCombos(CSensItem, SensitivitiesWidget::ChoiceType);

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

    enum Choice {
      Choice_SubTask = 1,
      Choice_Function = 2,
      Choice_Variable = 4,
      Choice_All = 7
    };

    CObjectLists::ListType mSubTask;
    CObjectLists::ListType mFunction;
    CObjectLists::ListType mVariable;
    CObjectLists::ListType mVariable2;

    CSensProblem * mpProblem;

    CSensItem mFunctionItem;
    CSensItem mVariableItem;
    CSensItem mVariable2Item;

  private slots:
    void on_SubTaskChooser_activated(int);
    void on_FunctionChooser_activated(int);
    void on_VariableChooser_activated(int);
    void on_VariableChooser2_activated(int);
  };

#endif // SENSWIDGET_H
