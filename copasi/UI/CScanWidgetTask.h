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

/*
 All rights reserved.
 */

#ifndef CSCANWIDGETTASK_H
#define CSCANWIDGETTASK_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CScanWidgetTask.h"

class CScanProblem;
class CDataObject;
class CModel;

class CScanWidgetTask: public QWidget, public Ui::CScanWidgetTask
{
  Q_OBJECT

public:
  CScanWidgetTask(QWidget *parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CScanWidgetTask();

  virtual void load(const CScanProblem * pg);
  virtual bool save(CScanProblem * pg) const;

protected:
  CDataObject* mpObject;
  const CModel* mpModel;

private:
  void init();

private slots:
  virtual void typeChanged(int n);
};

#endif // CSCANWIDGETTASK_H
