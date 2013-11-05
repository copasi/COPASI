// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright � 1997   Josef Wilgen
// Copyright � 2002   Uwe Rathmann
//
// This file is published under the Qwt License, Version 1.0.
// You should have received a copy of this licence in the file
// QwtLicense.
//
// Modifications made to the original are
#ifndef _SCROLLZOOMER_H
#define _SCROLLZOOMER_H

#include <QtCore/qglobal.h>

#if QT_VERSION < 0x040000
# include <q3scrollview.h>
#endif

#include <qwt_plot_zoomer.h>
//Added by qt3to4:
#include <QtCore/QEvent>

class ScrollData;
class ScrollBar;

class LogPlotZoomer: public QwtPlotZoomer
{
  Q_OBJECT

public:
  LogPlotZoomer(QwtPlotCanvas *canvas);

public slots:
  virtual
  void move(double x, double y);

protected:
  virtual QwtText trackerText(const QwtDoublePoint &pos) const;
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

  ScrollZoomer(QwtPlotCanvas *);
  virtual ~ScrollZoomer();

  ScrollBar *horizontalScrollBar() const;
  ScrollBar *verticalScrollBar() const;

#if QT_VERSION < 0x040000
  void setHScrollBarMode(Q3ScrollView::ScrollBarMode);
  void setVScrollBarMode(Q3ScrollView::ScrollBarMode);

  Q3ScrollView::ScrollBarMode vScrollBarMode() const;
  Q3ScrollView::ScrollBarMode hScrollBarMode() const;
#else
  void setHScrollBarMode(Qt::ScrollBarPolicy);
  void setVScrollBarMode(Qt::ScrollBarPolicy);

  Qt::ScrollBarPolicy vScrollBarMode() const;
  Qt::ScrollBarPolicy hScrollBarMode() const;
#endif

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
