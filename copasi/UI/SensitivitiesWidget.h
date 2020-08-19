// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SENSWIDGET_H
#define SENSWIDGET_H

#include <QComboBox>

#include "ui_SensitivitiesWidget.h"

#include "copasi/UI/TaskWidget.h"
#include "copasi/UI/SensWidgetComboBox.h"

#include "copasi/copasi.h"
#include "copasi/sensitivities/CSensProblem.h"

class SensitivitiesWidget : public TaskWidget, public Ui::SensitivitiesWidget
{
  Q_OBJECT

public:

  explicit SensitivitiesWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~SensitivitiesWidget();

  virtual bool runTask();

protected:
  virtual bool loadTaskProtected();
  virtual bool saveTaskProtected();
  virtual bool taskFinishedEvent();

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

  const CDataObject * mpSingleFunction;
  const CDataObject * mpSingleVariable;
  const CDataObject * mpSingleVariable2;

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
