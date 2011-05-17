// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DefaultplotDialog.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/17 13:10:18 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef DEFAULTPLOTDIALOG_H
#define DEFAULTPLOTDIALOG_H

#include <QVariant>
#include <QDialog>
#include <vector>
#include "copasi.h"

#include "ui_DefaultplotDialog.h"

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
  virtual void newSlot();

protected:
  CCopasiTask* mpTask;
  std::vector<C_INT32> mList;
  int mIndex;

protected slots:

  virtual void slotCreate();
  virtual void slotSelect();


};

#endif // DEFAULTPLOTDIALOG_H
