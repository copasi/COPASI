// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTSSATimeScaleWidget.h,v $
//   $Revision: 1.3.2.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2011/10/28 15:09:17 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTSSATIMESCALEWIDGET_H
#define CQTSSATIMESCALEWIDGET_H

#include <qwidget.h>
#include <qlayout.h>
//Added by qt3to4:
//#include <QPaintEvent>
#include <QVBoxLayout>
#include "utilities/CVector.h"
#include <qslider.h>
#include <qpainter.h>

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
