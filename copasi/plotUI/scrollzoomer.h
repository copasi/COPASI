// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Copyright 1997   Josef Wilgen
// Copyright 2002   Uwe Rathmann
//
// This file is published under the Qwt License, Version 1.0.
// You should have received a copy of this licence in the file
// QwtLicense.
//
// Modifications made to the original are
#ifndef _SCROLLZOOMER_H
#define _SCROLLZOOMER_H

#include <QtCore/qglobal.h>

#include <qwt_plot_zoomer.h>
//Added by qt3to4:
#include <QtCore/QEvent>

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
#  include <qwt_compat.h>
#endif

class ScrollData;
class ScrollBar;

class LogPlotZoomer: public QwtPlotZoomer
{
  Q_OBJECT

public:

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  LogPlotZoomer(QWidget *canvas);
#else
  LogPlotZoomer(QwtPlotCanvas *canvas);
#endif

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
public slots:
  virtual void moveTo(const QPointF &pos);
#else
public slots:
  virtual void move(double x, double y);
#endif

protected:
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  virtual QwtText trackerTextF(const QwtDoublePoint &pos) const;
#else
  virtual QwtText trackerText(const QwtDoublePoint &pos) const;
#endif
};

class ScrollZoomer: public LogPlotZoomer
{
  Q_OBJECT
public:
  enum ScrollBarPosition
  {
    AttachedToScale,
    OppositeToScale
  };

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  ScrollZoomer(QWidget *);
#else
  ScrollZoomer(QwtPlotCanvas *);
#endif
  virtual ~ScrollZoomer();

  ScrollBar *horizontalScrollBar() const;
  ScrollBar *verticalScrollBar() const;

  void setHScrollBarMode(Qt::ScrollBarPolicy);
  void setVScrollBarMode(Qt::ScrollBarPolicy);

  Qt::ScrollBarPolicy vScrollBarMode() const;
  Qt::ScrollBarPolicy hScrollBarMode() const;

  void setHScrollBarPosition(ScrollBarPosition);
  void setVScrollBarPosition(ScrollBarPosition);

  ScrollBarPosition hScrollBarPosition() const;
  ScrollBarPosition vScrollBarPosition() const;

  QWidget* cornerWidget() const;
  virtual void setCornerWidget(QWidget *);

  virtual bool eventFilter(QObject *, QEvent *);

  virtual void rescale();

protected:
  virtual ScrollBar *scrollBar(Qt::Orientation);
  virtual void updateScrollBars();
  virtual void layoutScrollBars(const QRect &);

private slots:
  void scrollBarMoved(Qt::Orientation o, double min, double max);

private:
  bool needScrollBar(Qt::Orientation) const;
  int oppositeAxis(int) const;

  QWidget *d_cornerWidget;

  ScrollData *d_hScrollData;
  ScrollData *d_vScrollData;
};

#endif
