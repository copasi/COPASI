// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SensitivitiesWidget.h,v $
//   $Revision: 1.18 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/17 13:10:22 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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
  virtual bool taskFinishedEvent();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

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
   * updates the variable and target function boxes
   */
  void updateComboBoxes(CSensProblem::SubTaskType type);

  const CCopasiObject * mpSingleFunction;
  const CCopasiObject * mpSingleVariable;
  const CCopasiObject * mpSingleVariable2;

private slots:

  /*
    void on_SubTaskChooser_activated(int);
    void on_FunctionChooser_activated(int);
    void on_VariableChooser_activated(int);
    void on_Variable2Chooser_activated(int);

    void on_SingleFunctionChooser_clicked();
    void on_SingleVariableChooser_clicked();
    void on_SingleVariable2Chooser_clicked();
  */
  void slotChooseSubTask(int);
  void slotChooseFunction(int);
  void slotChooseVariable(int);
  void slotChooseVariable2(int);

  void slotChooseSingleFunction();
  void slotChooseSingleVariable();
  void slotChooseSingleVariable2();

protected slots:
};

#endif // SENSWIDGET_H
