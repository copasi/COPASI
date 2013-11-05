// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTSSATIMESCALEWIDGET_H
#define CQTSSATIMESCALEWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QLayout>
#include <QtGui/QPaintEvent>
#include <QtGui/QVBoxLayout>
#include "utilities/CVector.h"
#include <QtGui/QSlider>
#include <QtGui/QPainter>

class PaintWidget : public QWidget
{
  Q_OBJECT

public:
  PaintWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~PaintWidget();

  void paintTimeScale(int select);

  CVector< C_FLOAT64> mVector;
  bool mClear;

protected:
  void paintEvent(QPaintEvent *);

private:
  int mSelection;
};

class CQTSSATimeScaleWidget : public QWidget
{
  Q_OBJECT

public:
  CQTSSATimeScaleWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CQTSSATimeScaleWidget();

  void paintTimeScale(CVector< C_FLOAT64> vector);
  void clearWidget();

public slots:
  void changedInterval();

private:
  QVBoxLayout * mpVLayout;
  PaintWidget * mpPaintWidget;
  QSlider * mpSlider;
};

#endif // CQTSSATIMESCALEWIDGET_H
