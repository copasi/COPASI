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
#include <QtCore/QEvent>
#include <qwt_plot_canvas.h>
#include <qwt_plot_layout.h>
#include <qwt_scale_engine.h>
#include <qwt_text.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <QtCore/QChildEvent>
#include "scrollbar.h"
#include "scrollzoomer.h"

#include <QStack>
#include <QVector>
#include <QRect>

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
LogPlotZoomer::LogPlotZoomer(QWidget *canvas) :
  QwtPlotZoomer(canvas)
#else
LogPlotZoomer::LogPlotZoomer(QwtPlotCanvas * canvas):
  QwtPlotZoomer(canvas)
#endif
{}

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
QwtText LogPlotZoomer::trackerTextF(const QwtDoublePoint &pos) const
#else
QwtText LogPlotZoomer::trackerText(const QwtDoublePoint &pos) const
#endif
{
  switch (rubberBand())
    {
      case HLineRubberBand:
        return QString("%1.4g").arg(pos.y());

      case VLineRubberBand:
        return QString("%1.4g").arg(pos.x());

      default:
        return QString("%1.4g %2.4g").arg(pos.x()).arg(pos.y());
    }

  return QwtText(); // make some dumb compilers happy
}

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
void LogPlotZoomer::moveTo(const QPointF& pos)
{
  double x = pos.x();
  double y = pos.y();
#else
void LogPlotZoomer::move(double x, double y)
{
#endif
  //QwtPlotZoomer::move(x,y);

  x = qwtMax(x, (double)zoomBase().left());
  x = qwtMin(x, (double)(zoomBase().right() - zoomRect().width()));

  y = qwtMax(y, (double)zoomBase().top());
  y = qwtMin(y, (double)(zoomBase().bottom() - zoomRect().height()));

  if (x != zoomRect().left() || y != zoomRect().top())
    {
      //zoomStack()[zoomRectIndex()].moveTo(x, y);
      QwtDoubleRect & rect = const_cast< QwtDoubleRect & >(zoomStack()[zoomRectIndex()]);

      //handle x axis
      const int xAxis = QwtPlotZoomer::xAxis();
      const QwtScaleEngine *sex = plot()->axisScaleEngine(xAxis);

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)

      if (dynamic_cast<const QwtLogScaleEngine*>(sex))
#else
      if (dynamic_cast<const QwtLog10ScaleEngine*>(sex))
#endif
        {
          //logarithmic
          double factor = rect.right() / rect.left();
          rect.setRight(x * factor);
          rect.setLeft(x);
        }
      else
        {
          rect.moveLeft(x);
        }

      const int yAxis = QwtPlotZoomer::yAxis();

      const QwtScaleEngine *sey = plot()->axisScaleEngine(yAxis);

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)

      if (dynamic_cast<const QwtLogScaleEngine*>(sey))
#else
      if (dynamic_cast<const QwtLog10ScaleEngine*>(sey))
#endif
        {
          //logarithmic
          double factor = rect.bottom() / rect.top();
          rect.setBottom(y * factor);
          rect.setTop(y);
        }
      else
        {
          rect.moveTop(y);
        }

      //zoomStack()[zoomRectIndex()].moveTo(x, y);
      rescale();
    }
}

//******************************************

class ScrollData
{
public:
  ScrollData():
    scrollBar(NULL),
    position(ScrollZoomer::OppositeToScale),
    mode(Qt::ScrollBarAsNeeded)
  {
  }

  ~ScrollData()
  {
    delete scrollBar;
  }

  ScrollBar *scrollBar;
  ScrollZoomer::ScrollBarPosition position;
  Qt::ScrollBarPolicy mode;
};

//******************************************

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
ScrollZoomer::ScrollZoomer(QWidget *canvas):
  LogPlotZoomer(canvas),
#else
ScrollZoomer::ScrollZoomer(QwtPlotCanvas * canvas):
  LogPlotZoomer(canvas),
#endif
  d_cornerWidget(NULL),
  d_hScrollData(NULL),
  d_vScrollData(NULL)
{
  if (!canvas)
    return;

  d_hScrollData = new ScrollData;
  d_vScrollData = new ScrollData;
}

ScrollZoomer::~ScrollZoomer()
{
  delete d_cornerWidget;
  delete d_vScrollData;
  delete d_hScrollData;
}

void ScrollZoomer::rescale()
{
  QwtPlotZoomer::rescale();
  updateScrollBars();
}

ScrollBar *ScrollZoomer::scrollBar(Qt::Orientation o)
{
  ScrollBar *&sb = (o == Qt::Vertical)
                   ? d_vScrollData->scrollBar : d_hScrollData->scrollBar;

  if (sb == NULL)
    {
      sb = new ScrollBar(o, canvas());
      sb->hide();
      connect(sb,
              SIGNAL(valueChanged(Qt::Orientation, double, double)),
              SLOT(scrollBarMoved(Qt::Orientation, double, double)));
    }

  return sb;
}

ScrollBar *ScrollZoomer::horizontalScrollBar() const
{
  return d_hScrollData->scrollBar;
}

ScrollBar *ScrollZoomer::verticalScrollBar() const
{
  return d_vScrollData->scrollBar;
}

void ScrollZoomer::setHScrollBarMode(Qt::ScrollBarPolicy mode)
{
  if (hScrollBarMode() != mode)
    {
      d_hScrollData->mode = mode;
      updateScrollBars();
    }
}

void ScrollZoomer::setVScrollBarMode(Qt::ScrollBarPolicy mode)
{
  if (vScrollBarMode() != mode)
    {
      d_vScrollData->mode = mode;
      updateScrollBars();
    }
}

Qt::ScrollBarPolicy ScrollZoomer::hScrollBarMode() const
{
  return d_hScrollData->mode;
}

Qt::ScrollBarPolicy ScrollZoomer::vScrollBarMode() const
{
  return d_vScrollData->mode;
}

void ScrollZoomer::setHScrollBarPosition(ScrollBarPosition pos)
{
  if (d_hScrollData->position != pos)
    {
      d_hScrollData->position = pos;
      updateScrollBars();
    }
}

void ScrollZoomer::setVScrollBarPosition(ScrollBarPosition pos)
{
  if (d_vScrollData->position != pos)
    {
      d_vScrollData->position = pos;
      updateScrollBars();
    }
}

ScrollZoomer::ScrollBarPosition ScrollZoomer::hScrollBarPosition() const
{
  return d_hScrollData->position;
}

ScrollZoomer::ScrollBarPosition ScrollZoomer::vScrollBarPosition() const
{
  return d_vScrollData->position;
}

void ScrollZoomer::setCornerWidget(QWidget *w)
{
  if (w != d_cornerWidget)
    {
      if (canvas())
        {
          delete d_cornerWidget;
          d_cornerWidget = w;

          if (d_cornerWidget->parent() != canvas())
            {
              d_cornerWidget->setParent(canvas());
            }

          updateScrollBars();
        }
    }
}

QWidget *ScrollZoomer::cornerWidget() const
{
  return d_cornerWidget;
}

bool ScrollZoomer::eventFilter(QObject *o, QEvent *e)
{
  if (o == canvas())
    {
      switch (e->type())
        {
          case QEvent::Resize:
          {
            const int fw = ((QwtPlotCanvas *)canvas())->frameWidth();

            QRect rect;
            rect.setSize(((QResizeEvent *)e)->size());
            rect.setRect(rect.x() + fw, rect.y() + fw,
                         rect.width() - 2 * fw, rect.height() - 2 * fw);

            layoutScrollBars(rect);
            break;
          }

          case QEvent::ChildRemoved:
          {
            const QObject *child = ((QChildEvent *)e)->child();

            if (child == d_cornerWidget)
              d_cornerWidget = NULL;
            else if (child == d_hScrollData->scrollBar)
              d_hScrollData->scrollBar = NULL;
            else if (child == d_vScrollData->scrollBar)
              d_vScrollData->scrollBar = NULL;

            break;
          }

          default:
            break;
        }
    }

  return QwtPlotZoomer::eventFilter(o, e);
}

bool ScrollZoomer::needScrollBar(Qt::Orientation o) const
{
  Qt::ScrollBarPolicy mode;

  double zoomMin, zoomMax, baseMin, baseMax;

  if (o == Qt::Horizontal)
    {
      mode = d_hScrollData->mode;
      baseMin = zoomBase().left();
      baseMax = zoomBase().right();
      zoomMin = zoomRect().left();
      zoomMax = zoomRect().right();
    }
  else
    {
      mode = d_vScrollData->mode;
      baseMin = zoomBase().top();
      baseMax = zoomBase().bottom();
      zoomMin = zoomRect().top();
      zoomMax = zoomRect().bottom();
    }

  bool needed = false;

  switch (mode)
    {
      case Qt::ScrollBarAlwaysOn:
        needed = true;
        break;

      case Qt::ScrollBarAlwaysOff:
        needed = false;
        break;

      default:
      {
        if (baseMin < zoomMin || baseMax > zoomMax)
          needed = true;

        break;
      }
    }

  return needed;
}

void ScrollZoomer::updateScrollBars()
{
  if (!canvas())
    return;

  const int xAxis = QwtPlotZoomer::xAxis();
  const int yAxis = QwtPlotZoomer::yAxis();

  int xScrollBarAxis = xAxis;

  if (hScrollBarPosition() == OppositeToScale)
    xScrollBarAxis = oppositeAxis(xScrollBarAxis);

  int yScrollBarAxis = yAxis;

  if (vScrollBarPosition() == OppositeToScale)
    yScrollBarAxis = oppositeAxis(yScrollBarAxis);

  QwtPlotLayout *layout = plot()->plotLayout();

  bool showHScrollBar = needScrollBar(Qt::Horizontal);

  if (showHScrollBar)
    {
      ScrollBar *sb = scrollBar(Qt::Horizontal);

      sb->setPalette(plot()->palette());

      const QwtScaleEngine *se = plot()->axisScaleEngine(xAxis);
      sb->setInverted(se->testAttribute(QwtScaleEngine::Inverted));
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
      sb->setLogScale(dynamic_cast<const QwtLogScaleEngine*>(se));
#else
      sb->setLogScale(dynamic_cast<const QwtLog10ScaleEngine*>(se));
#endif

      sb->setBase(zoomBase().left(), zoomBase().right());
      sb->moveSlider(zoomRect().left(), zoomRect().right());

      if (!sb->isVisibleTo(canvas()))
        {
          sb->show();
          layout->setCanvasMargin(layout->canvasMargin(xScrollBarAxis)
                                  + sb->extent(), xScrollBarAxis);
        }
    }
  else
    {
      if (horizontalScrollBar())
        {
          horizontalScrollBar()->hide();
          layout->setCanvasMargin(layout->canvasMargin(xScrollBarAxis)
                                  - horizontalScrollBar()->extent(), xScrollBarAxis);
        }
    }

  bool showVScrollBar = needScrollBar(Qt::Vertical);

  if (showVScrollBar)
    {
      ScrollBar *sb = scrollBar(Qt::Vertical);

      sb->setPalette(plot()->palette());

      const QwtScaleEngine *se = plot()->axisScaleEngine(yAxis);
      sb->setInverted(!(se->testAttribute(QwtScaleEngine::Inverted)));
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
      sb->setLogScale(dynamic_cast<const QwtLogScaleEngine*>(se));
#else
      sb->setLogScale(dynamic_cast<const QwtLog10ScaleEngine*>(se));
#endif

      sb->setBase(zoomBase().top(), zoomBase().bottom());
      sb->moveSlider(zoomRect().top(), zoomRect().bottom());

      if (!sb->isVisibleTo(canvas()))
        {
          sb->show();
          layout->setCanvasMargin(layout->canvasMargin(yScrollBarAxis)
                                  + sb->extent(), yScrollBarAxis);
        }
    }
  else
    {
      if (verticalScrollBar())
        {
          verticalScrollBar()->hide();
          layout->setCanvasMargin(layout->canvasMargin(yScrollBarAxis)
                                  - verticalScrollBar()->extent(), yScrollBarAxis);
        }
    }

  if (showHScrollBar && showVScrollBar)
    {
      if (d_cornerWidget == NULL)
        {
          d_cornerWidget = new QWidget(canvas());
          d_cornerWidget->setPalette(plot()->palette());
        }

      d_cornerWidget->show();
    }
  else
    {
      if (d_cornerWidget)
        d_cornerWidget->hide();
    }

  layoutScrollBars(((QwtPlotCanvas *)canvas())->contentsRect());
}

void ScrollZoomer::layoutScrollBars(const QRect &rect)
{
  int hPos = xAxis();

  if (hScrollBarPosition() == OppositeToScale)
    hPos = oppositeAxis(hPos);

  int vPos = yAxis();

  if (vScrollBarPosition() == OppositeToScale)
    vPos = oppositeAxis(vPos);

  ScrollBar *hScrollBar = horizontalScrollBar();
  ScrollBar *vScrollBar = verticalScrollBar();

  const int hdim = hScrollBar ? hScrollBar->extent() : 0;
  const int vdim = vScrollBar ? vScrollBar->extent() : 0;

  if (hScrollBar && hScrollBar->isVisible())
    {
      int x = rect.x();
      int y = (hPos == QwtPlot::xTop)
              ? rect.top() : rect.bottom() - hdim + 1;
      int w = rect.width();

      if (vScrollBar && vScrollBar->isVisible())
        {
          if (vPos == QwtPlot::yLeft)
            x += vdim;

          w -= vdim;
        }

      hScrollBar->setGeometry(x, y, w, hdim);
    }

  if (vScrollBar && vScrollBar->isVisible())
    {
      int pos = yAxis();

      if (vScrollBarPosition() == OppositeToScale)
        pos = oppositeAxis(pos);

      int x = (vPos == QwtPlot::yLeft)
              ? rect.left() : rect.right() - vdim + 1;
      int y = rect.y();

      int h = rect.height();

      if (hScrollBar && hScrollBar->isVisible())
        {
          if (hPos == QwtPlot::xTop)
            y += hdim;

          h -= hdim;
        }

      vScrollBar->setGeometry(x, y, vdim, h);
    }

  if (hScrollBar && hScrollBar->isVisible() &&
      vScrollBar && vScrollBar->isVisible())
    {
      if (d_cornerWidget)
        {
          QRect cornerRect(
            vScrollBar->pos().x(), hScrollBar->pos().y(),
            vdim, hdim);
          d_cornerWidget->setGeometry(cornerRect);
        }
    }
}

void ScrollZoomer::scrollBarMoved(Qt::Orientation o, double min, double)
{
  if (o == Qt::Horizontal)
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
    moveTo(QPointF(min, zoomRect().top()));

#else
    move(min, zoomRect().top());
#endif
  else
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
    moveTo(QPointF(zoomRect().left(), min));

#else
    move(zoomRect().left(), min);
#endif

  emit zoomed(zoomRect());
}

int ScrollZoomer::oppositeAxis(int axis) const
{
  switch (axis)
    {
      case QwtPlot::xBottom:
        return QwtPlot::xTop;

      case QwtPlot::xTop:
        return QwtPlot::xBottom;

      case QwtPlot::yLeft:
        return QwtPlot::yRight;

      case QwtPlot::yRight:
        return QwtPlot::yLeft;

      default:
        break;
    }

  return axis;
}
