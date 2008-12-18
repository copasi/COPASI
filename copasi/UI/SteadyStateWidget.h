// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SteadyStateWidget.h,v $
//   $Revision: 1.38 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:58:29 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef STEADYSTATEWIDGET_H
#define STEADYSTATEWIDGET_H

#include "copasi.h"
//#include <qvariant.h>
//#include <qwidget.h>
#include "UI/TaskWidget.h"
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3Frame>
#include <Q3VBoxLayout>

class QCheckBox;
class Q3Frame;
class Q3GridLayout;

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
    SteadyStateWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
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
    Q3VBoxLayout* SteadyStateWidgetLayout;
    QCheckBox* taskJacobian;
    QCheckBox* taskStability;
    Q3GridLayout * mpLayoutProblem;
    Q3Frame* line1;
    //QLabel* parameterValueLabel;
    //QTable* parameterTable;
  };

#endif // STEADYSTATEWIDGET_H
