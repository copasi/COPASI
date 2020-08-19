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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*
 *  CMCAResultSubwidget.h
 *
 *
 *  Created by Paul on 4/2/10.
 *
 */

#ifndef CMCARESULTSUBWIDGET_H
#define CMCARESULTSUBWIDGET_H

#include <QtCore/QVariant>

#include "ui_CMCAResultSubwidget.h"

#include "CQArrayAnnotationsWidget.h"

class CMCAMethod;

class CMCAResultSubwidget : public CopasiWidget, public Ui::CMCAResultSubwidget
{
  Q_OBJECT

public:
  CMCAResultSubwidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CMCAResultSubwidget();

  virtual void loadAll(const CMCAMethod * mcaMethod);
  virtual void loadElasticities(const CMCAMethod * mcaMethod);
  virtual void loadConcentrationCCs(const CMCAMethod * mcaMethod);
  virtual void loadFluxCCs(const CMCAMethod * mcaMethod);
  virtual void clear();

protected slots:

  virtual void slotSave();
  virtual void slotScaled();

private:
  const CMCAMethod * mMCAMethod;
};

#endif // CMCARESULTSUBWIDGET_H
