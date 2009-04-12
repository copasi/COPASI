// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SensitivitiesWidget.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/04/12 20:06:17 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SENSWIDGET_H
#define SENSWIDGET_H

#include "copasi.h"

#include "ui_SensitivitiesWidget.h"

//#include <qvariant.h>
//#include <qwidget.h>
#include "UI/TaskWidget.h"
#include "sensitivities/CSensProblem.h"

#include "UI/SensWidgetComboBox.h"

#include <qcombobox.h>
/*
//Added by qt3to4:
//#include <Q3VBoxLayout>
#include <QLabel>

#include <QVBoxLayout>
#include <QToolButton>

//class QToolButton;
 */

class SensitivitiesWidget : public TaskWidget, public Ui::SensitivitiesWidget
{
  Q_OBJECT

public:

  explicit SensitivitiesWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
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

protected:
  /*
  //    Q3VBoxLayout* SensitivitiesWidgetLayout;
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
  */

private:

  void init();

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
   * contains a valid CN. Returns false if invalid
   */
  bool checkSingleObject(const SensWidgetComboBox* box, const CCopasiObject * object);

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

  const CCopasiObject * mpSingleFunction;
  const CCopasiObject * mpSingleVariable;
  const CCopasiObject * mpSingleVariable2;

  //CSensProblem::SubTaskType mSubTaskType;

private slots:
  void on_SubTaskChooser_activated(int);
  void on_FunctionChooser_activated(int);
  void on_VariableChooser_activated(int);
  void on_Variable2Chooser_activated(int);

  void on_SingleFunctionChooser_clicked();
  void on_SingleVariableChooser_clicked();
  void on_SingleVariable2Chooser_clicked();

protected slots:
  virtual void languageChange();
};

#endif // SENSWIDGET_H
