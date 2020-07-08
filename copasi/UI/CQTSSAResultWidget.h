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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TSSARESULTWIDGET_H
#define TSSARESULTWIDGET_H

#include "copasi/UI/copasiWidget.h"
#include <QGridLayout>

class CQTSSAResultSubWidget;

class CQTSSAResultWidget : public CopasiWidget
{
  Q_OBJECT

public:
  CQTSSAResultWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQTSSAResultWidget();

  CQTSSAResultSubWidget* getSubWidget();

protected slots:

protected:
  virtual bool enterProtected();
  QGridLayout* mWidgetLayout;
  CQTSSAResultSubWidget* mCentralWidget;
};

#endif
