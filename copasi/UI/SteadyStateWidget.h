// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SteadyStateWidget.h,v $
//   $Revision: 1.37 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/12 14:29:14 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef STEADYSTATEWIDGET_H
#define STEADYSTATEWIDGET_H

#include "copasi.h"
//#include <qvariant.h>
//#include <qwidget.h>
#include "UI/TaskWidget.h"

class QCheckBox;
class QFrame;
class QGridLayout;

//class QLabel;
//class QLineEdit;
//class QPushButton;
//class QRadioButton;
//class QTable;
//class CSteadyStateTask;
//class CSteadyStateProblem;
//class CSteadyStateMethod;
//class CModel;

class SteadyStateWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    SteadyStateWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~SteadyStateWidget();

    virtual bool runTask();

  protected slots:
    //virtual void parameterValueChanged();
    virtual void taskJacobianToggled();

  protected:
    virtual bool loadTask();
    virtual bool saveTask();

    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    //QFrame* line_ss;
    QVBoxLayout* SteadyStateWidgetLayout;
    QCheckBox* taskJacobian;
    QCheckBox* taskStability;
    QGridLayout * mpLayoutProblem;
    QFrame* line1;
    //QLabel* parameterValueLabel;
    //QTable* parameterTable;
  };

#endif // STEADYSTATEWIDGET_H
