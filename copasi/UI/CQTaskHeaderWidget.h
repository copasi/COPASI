// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskHeaderWidget.h,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:38 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQTaskHeaderWidget
#define COPASI_CQTaskHeaderWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTaskHeaderWidget.h"

class CQTaskHeaderWidget: public QWidget, public Ui::CQTaskHeaderWidget
{
  Q_OBJECT

public:
  CQTaskHeaderWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

  virtual ~CQTaskHeaderWidget();

  bool setTaskName(const std::string & name);
  void saved();

protected slots:

  void slotUpdate();
  void slotExecutable();

protected:
  bool mExecutableChanged;
  bool mUpdateChanged;
  QColor mSavedColor;
  QColor mChangedColor;
};

#endif // CQTASKHEADERWIDGET_H
