// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTSSATimeScaleWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/02/24 17:33:04 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTSSATIMESCALEWIDGET_H
#define CQTSSATIMESCALEWIDGET_H

#include <qwidget.h>
#include <qlayout.h>
#include "utilities/CVector.h"
#include <qslider.h>
#include <qpainter.h>

class PaintWidget : public QWidget
  {
    Q_OBJECT

  public:
    PaintWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
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
    CQTSSATimeScaleWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
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
