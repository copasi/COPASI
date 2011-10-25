// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DefaultplotDialog.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/25 17:15:43 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
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
  DefaultPlotDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
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
