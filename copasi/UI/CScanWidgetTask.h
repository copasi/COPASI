// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetTask.h,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/01/28 13:06:11 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/*
 All rights reserved.
 */

#ifndef CSCANWIDGETTASK_H
#define CSCANWIDGETTASK_H

#include "ui_CScanWidgetTask.h"

#include "scan/CScanProblem.h"

class CScanWidgetTask: public QWidget //, public Ui::CScanWidgetTask
  {
    Q_OBJECT

  public:
    CScanWidgetTask(QWidget *parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    ~CScanWidgetTask();

    virtual bool initFromScanProblem(CScanProblem * pg, const CModel * model);
    virtual bool saveToScanProblem(CScanProblem * pg) const;

  protected:
    CCopasiObject* mpObject;
    const CModel* mpModel;

  private:
    Ui::CScanWidgetTask ui;
    void init();

  private slots:
    virtual void typeChanged(int n);
  };

#endif // CSCANWIDGETTASK_H
