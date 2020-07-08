// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  CLNAResultSubwidget.h
 *
 *
 *  Created by Juergen Pahle on 2010-06-01.
 *
 */

#ifndef CLNARESULTSUBWIDGET_H
#define CLNARESULTSUBWIDGET_H

#include <QtCore/QVariant>

#include "ui_CLNAResultSubwidget.h"

#include "CQArrayAnnotationsWidget.h"

class CLNAMethod;

class CLNAResultSubwidget : public CopasiWidget, public Ui::CLNAResultSubwidget
{
  Q_OBJECT

public:
  CLNAResultSubwidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CLNAResultSubwidget();

  virtual void loadAll(const CLNAMethod * lnaMethod);
  virtual void loadCovarianceMatrix(const CLNAMethod * lnaMethod);
  virtual void loadCovarianceMatrixReduced(const CLNAMethod * lnaMethod);
  virtual void loadBMatrixReduced(const CLNAMethod * lnaMethod);
  virtual void clear();

protected:
  virtual void init();

protected slots:

  virtual void slotSave();
  virtual void slotScaled();

private:
  const CLNAMethod * mLNAMethod;
};

#endif // CLNARESULTSUBWIDGET_H
