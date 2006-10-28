/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/SSAWidget.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/28 00:18:41 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SSAWIDGET_H
#define SSAWIDGET_H

//#include "copasi.h"
#include "UI/TaskWidget.h"
//#include "ssa/CSSATask.h"

class CSSATask;

class QToolButton;

class SSAWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    explicit SSAWidget(QWidget * parent = 0, const char* name = 0, WFlags fl = 0);

    ~SSAWidget();

    virtual bool runTask();

  protected:
    CSSATask *task;

    virtual bool loadTask();
    virtual bool saveTask();
    virtual CCopasiMethod* createMethod(const CCopasiMethod::SubType&);

  private slots:
    void on_RunButton_clicked();
  };
#endif // SSAWIDGET_H
