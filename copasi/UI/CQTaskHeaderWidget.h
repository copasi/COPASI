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

#ifndef COPASI_CQTaskHeaderWidget
#define COPASI_CQTaskHeaderWidget

#include <QtCore/QVariant>

#include <string>

#include "copasi/UI/ui_CQTaskHeaderWidget.h"

class CQTaskHeaderWidget: public QWidget, public Ui::CQTaskHeaderWidget
{
  Q_OBJECT

public:
  CQTaskHeaderWidget(QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());

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
