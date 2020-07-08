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

#ifndef COPASI_CQTaskBtnWidget
#define COPASI_CQTaskBtnWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTaskBtnWidget.h"

class CQTaskBtnWidget: public QWidget, public Ui::CQTaskBtnWidget
{
  Q_OBJECT

public:
  CQTaskBtnWidget(QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());

  virtual ~CQTaskBtnWidget();

protected slots:
};

#endif // COPASI_CQTaskBtnWidget
