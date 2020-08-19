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

#ifndef DEFAULTPLOTDIALOG_H
#define DEFAULTPLOTDIALOG_H

#include <QtCore/QVariant>
#include "copasi/UI/ui_DefaultplotDialog.h"

#include <vector>

#include "copasi/copasi.h"

class CCopasiProblem;
class CCopasiTask;

class DefaultPlotDialog : public QDialog, public Ui::DefaultPlotDialog
{
  Q_OBJECT

public:
  DefaultPlotDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
  ~DefaultPlotDialog();

public slots:
  virtual void setTask(CCopasiTask * t);

protected:

  void fillList();

  CCopasiTask* mpTask;
  std::vector< C_INT32 > mList;
  int mIndex;

protected slots:

  ///connected to create button
  virtual void slotCreate();

  ///called when selection in listbox is changed
  virtual void slotSelect();

  ///connected to check box
  virtual void slotToggleAll(bool flag);
};

#endif // DEFAULTPLOTDIALOG_H
