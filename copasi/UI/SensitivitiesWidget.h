/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SensitivitiesWidget.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: ssahle $
   $Date: 2007/01/04 14:29:02 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SENSWIDGET_H
#define SENSWIDGET_H

#include "copasi.h"
//#include <qvariant.h>
//#include <qwidget.h>
#include "UI/TaskWidget.h"
#include "sensitivities/CSensProblem.h"

#include <qcombobox.h>

class QToolButton;
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

/**
  * This class handles a combo box to choose from lists of object lists
  */
class SensWidgetComboBox : public QComboBox
  {
    Q_OBJECT

  public:

    SensWidgetComboBox(QWidget * parent = 0, const char * name = 0);

    /**
     * this fills the combobox with a new list of entries. If the
     * old current value is still allowed in the new list, it is set.
     * Otherwise the box shows the first item.
     */
    void fillFromList(const std::vector<CObjectLists::ListType> & list);

    CObjectLists::ListType getCurrentObjectList() const;

    /**
     * set current selection (if possible). It returns true
     * if the operation was succesful.
     */
    bool setCurrentObjectList(CObjectLists::ListType lt);

  protected:

    std::vector<CObjectLists::ListType> mIndexTable;
  };

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

    //     enum ChoiceType {
    //       SubTask,
    //       Function,
    //       Variable,
    //       SecondVariable
    //     };

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

    SensWidgetComboBox* FunctionChooser;
    QLineEdit* FunctionLineEdit;
    QToolButton *SingleFunctionChooser;
    //    QListView* FunctionChoiceBox;

    SensWidgetComboBox* VariableChooser;
    QLineEdit* VariableLineEdit;
    QToolButton *SingleVariableChooser;
    //    QListView* VariableChoiceBox;

    SensWidgetComboBox* Variable2Chooser;
    QLineEdit* Variable2LineEdit;
    QToolButton *SingleVariable2Chooser;

  private:
    void initCombos();
    //void initCombos(CSensProblem *);
    //bool initCombos(CSensItem *, SensitivitiesWidget::ChoiceType);

    /**
     * This checks if the combo box is set to "single object" and only then enables
     * the two given widgets.
     */
    void updateLineeditEnable(const SensWidgetComboBox* box, QWidget* w1, QWidget* w2);

    /**
     * This calls updateLineeditEnable() for all three combo boxes
     */
    void updateAllLineditEnable();

    /**
     * if the combo box is set to "single object" check if the lineedit
     * contains a valid CN. Returns FALSE if invalid
     */
    bool checkSingleObject(const SensWidgetComboBox* box, CCopasiObject * object);

    /**
     * enables the run button if the contents of the widget is valid
     */
    void updateRunButton();

    /**
     * updates the variable and target function boxes
     */
    void updateComboBoxes(CSensProblem::SubTaskType type);

    //void updateFunctionsStringList(CSensProblem::SubTaskType);
    //void updateVariablesStringList(CSensProblem::SubTaskType);

    //QStringList mVariablesStringList;
    //QStringList mFunctionsStringList;

    // for indexing the dynamic entries of our combo boxes:
    //std::vector<CObjectLists::ListType> mVariablesIndexTable;
    //std::vector<CObjectLists::ListType> mFunctionsIndexTable;

    //CObjectLists::ListType mFunction;
    //CObjectLists::ListType mVariable;
    //CObjectLists::ListType mVariable2;

    CCopasiObject * mpSingleFunction;
    CCopasiObject * mpSingleVariable;
    CCopasiObject * mpSingleVariable2;

    //CSensProblem::SubTaskType mSubTaskType;

  private slots:
    void on_SubTaskChooser_activated(int);
    void on_FunctionChooser_activated(int);
    void on_VariableChooser_activated(int);
    void on_Variable2Chooser_activated(int);

    void on_SingleFunctionChooser_clicked();
    void on_SingleVariableChooser_clicked();
    void on_SingleVariable2Chooser_clicked();
  };

#endif // SENSWIDGET_H
