/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/zoomplot.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:32:40 $
   End CVS Header */

// taken from the realtime_plot example

#include <qevent.h>
#include <qlabel.h>
#include <qwt_math.h>
#include <qwt_scale.h>
#include <qwt_plot_canvas.h>
#include "zoomplot.h"

ZoomScrollBar::ZoomScrollBar(Orientation o, QWidget *parent):
    QScrollBar(o, parent),
    c_ticks(1000000)
{
  setScale(0.0, 1.0);
}

double ZoomScrollBar::minSize() const
  {
    return 2 * (_max - _min) / (c_ticks - 1);
  }

void ZoomScrollBar::setScale(double minV, double maxV)
{
  _min = minV;
  _max = maxV;
}

void ZoomScrollBar::setSliderPosition(double bottom, double top)
{
  int visibleTicks = (int)((top - bottom) / (_max - _min) * c_ticks);

  // setRange initiates a valueChanged of the scrollbars
  // in some situations. So we block
  // and unblock the signals.

  blockSignals(TRUE);

  setRange(visibleTicks / 2, c_ticks - visibleTicks / 2);
  int steps = visibleTicks / 200;
  if (steps <= 0)
    steps = 1;
  setSteps(steps, visibleTicks);

  int tick = mapToTick(bottom + (top - bottom) / 2);
  if (orientation() == Vertical)
    tick = c_ticks - tick;

  directSetValue(tick);
  blockSignals(FALSE);

  rangeChange();
}

void ZoomScrollBar::getSliderPosition(double &bottom, double &top)
{
  int tick = value();
  if (orientation() == Vertical)
    tick = c_ticks - tick;

  int visibleTicks = pageStep();

  bottom = mapFromTick(tick - visibleTicks / 2);
  top = mapFromTick(tick + visibleTicks / 2);
}

int ZoomScrollBar::mapToTick(double v) const
  {
    return (int) ((v - _min) / (_max - _min) * c_ticks);
  }

double ZoomScrollBar::mapFromTick(int tick) const
  {
    return _min + (_max - _min) * tick / c_ticks;
  }

int ZoomScrollBar::dimension()
{
  // width of the vertical or height of an horizontal scrollbar.
  // Taken from the QT code.

  return 16;
}

ZoomPlot::ZoomPlot(QWidget *parent):
    QwtPlot(parent)
{
  setFrameStyle(NoFrame);
  setLineWidth(0);

  canvas()->setLineWidth(2);

  for (int i = 0; i < axisCnt; i++)
    setAxisLabelFormat(i, 'g', 8);

  enableGridX(TRUE);
  enableGridY(TRUE);
  setGridMajPen(QPen(gray, 0, DotLine));

  enableGridXMin(FALSE);
  enableGridYMin(FALSE);
  setGridMinPen(QPen(gray, 0, DotLine));

  setCanvasBackground(QColor(29, 100, 141)); // nice blue

  setOutlineStyle(Qwt::Rect);
  setOutlinePen(QPen(black));
  enableOutline(FALSE);

  // something for zooming. There is a limit for zooming when
  // the values on the axes get useless or doesn't differ
  // anymore. So we have to prevent the user from it using
  // the _maxXZoom, _maxYZoom flags indicating when the limit
  // is reached.

  _scaleStack.setAutoDelete(TRUE);
  _zoomable = TRUE;
  _maxXZoom = _maxYZoom = FALSE;

  /* the following connections are made in the subclass CopasiPlot
  connect(this, SIGNAL(plotMousePressed(const QMouseEvent &)),
      SLOT(mousePressed(const QMouseEvent&)));
  connect(this, SIGNAL(plotMouseReleased(const QMouseEvent &)),
      SLOT(mouseReleased(const QMouseEvent&)));
  */

  // enable scrollbars

  _vScrollBar = _hScrollBar = NULL;
  _cornerWidget = NULL;
  _enableScrollBars = FALSE;
  enableScrollBars(TRUE);
}

void ZoomPlot::setZoomable(bool enabled)
{
  _zoomable = enabled;
}

void ZoomPlot::mousePressed(const QMouseEvent &e)
{
  if (!_zoomable)
    return;

  switch (e.button())
    {
    case LeftButton:
      if (_maxXZoom && _maxYZoom)
        return;

      _zoomStartPoint = e.pos();
      setOutlineStyle(Qwt::Rect);
      enableOutline(TRUE);
    default:;
    }
}

void ZoomPlot::mouseReleased(const QMouseEvent &e)
{
  if (!_zoomable)
    return;

  switch (e.button())
    {
    case LeftButton:
      {
        if (_maxXZoom && _maxYZoom)
          return;

        enableOutline(FALSE);

        QRect zoomRectangle;
        zoomRectangle.setCoords
        (
          qwtMin(_zoomStartPoint.x(), e.pos().x()),
          qwtMin(_zoomStartPoint.y(), e.pos().y()),
          qwtMax(_zoomStartPoint.x(), e.pos().x()),
          qwtMax(_zoomStartPoint.y(), e.pos().y())
);

        if (zoomRectangle.width() > 10 || zoomRectangle.height() > 10)
          {
            DoubleRect *scaleRect = new DoubleRect(
                                      axisScale(QwtPlot::xBottom)->lBound(),
                                      axisScale(QwtPlot::yLeft)->lBound(),
                                      axisScale(QwtPlot::xBottom)->hBound(),
                                      axisScale(QwtPlot::yLeft)->hBound()
);
            if (_scaleStack.isEmpty())
              _initialScale = *scaleRect;
            _scaleStack.push(scaleRect);

            zoom(zoomRectangle);
            updateScrollBars();
          }

        break;
      }

    case MidButton:
      {
        if (_scaleStack.isEmpty())
          return;
        DoubleRect *scale = _scaleStack.pop();
        rescale(*scale);
        delete scale;
        updateScrollBars();

        _maxXZoom = _maxYZoom = FALSE;
        break;
      }

    case RightButton:
      {
        /* moved to zoomOut()
        if (_scaleStack.isEmpty())
            return;

        _scaleStack.clear();
        rescale(_initialScale);

        updateScrollBars();

        _maxXZoom = _maxYZoom = FALSE;
        */
        zoomOut();
        break;
      }
    default:;
    }
}

void ZoomPlot::zoom(QRect &zoomRectangle)
{
  setMinZoomRect(zoomRectangle);

  int x1, x2, y1, y2;
  zoomRectangle.coords(&x1, &y1, &x2, &y2);

  double x1Trans = invTransform(QwtPlot::xBottom, x1);
  double x2Trans = invTransform(QwtPlot::xBottom, x2);
  double y1Trans = invTransform(QwtPlot::yLeft, y1);
  double y2Trans = invTransform(QwtPlot::yLeft, y2);

  if (x2Trans < x1Trans)
    {
      double h = x1Trans;
      x1Trans = x2Trans;
      x2Trans = h;
    }
  if (y2Trans < y1Trans)
    {
      double h = y1Trans;
      y1Trans = y2Trans;
      y2Trans = h;
    }

  if (x1Trans < _initialScale.left())
    x1Trans = _initialScale.left();
  if (x2Trans > _initialScale.right())
    x2Trans = _initialScale.right();
  if (y1Trans < _initialScale.bottom())
    y1Trans = _initialScale.bottom();
  if (y2Trans > _initialScale.top())
    y2Trans = _initialScale.top();

  const int c_precision = 8;
  double factor = pow(10.0, c_precision - 1);
  double xMin = _initialScale.width() / factor;
  if (_hScrollBar)
    {
      if (xMin < _hScrollBar->minSize())
        xMin = _hScrollBar->minSize();
    }

  double yMin = _initialScale.height() / factor;
  if (_vScrollBar)
    {
      if (yMin < _vScrollBar->minSize())
        yMin = _vScrollBar->minSize();
    }

  if (x2Trans - x1Trans < xMin)
    {
      double delta = (xMin - (x2Trans - x1Trans)) / 2.0;
      x1Trans -= delta;
      x2Trans += delta;
      _maxXZoom = TRUE;
    }

  if (y2Trans - y1Trans < yMin)
    {
      double delta = (yMin - (y2Trans - y1Trans)) / 2.0;
      y1Trans -= delta;
      y2Trans += delta;
      _maxYZoom = TRUE;
    }

  DoubleRect rect(x1Trans, y1Trans, x2Trans, y2Trans);
  rescale(rect);
}

void ZoomPlot::setMinZoomRect(QRect &zoomRectangle) const
  {
    int x1, x2, y1, y2;
    zoomRectangle.coords(&x1, &y1, &x2, &y2);

    // -----------------------------------------------
    // limit selected area to a minimum of 11x11 points
    // -----------------------------------------------
    const int minDist = 5;
    int lim = minDist - (y2 - y1) / 2;
    if (lim > 0)
      {
        y1 -= lim;
        y2 += lim;
      }
    lim = minDist - (x2 - x1 + 1) / 2;
    if (lim > 0)
      {
        x1 -= lim;
        x2 += lim;
      }

    zoomRectangle.setCoords(x1, y1, x2, y2);
  }

void ZoomPlot::rescale(const DoubleRect &rect)
{
  setAxisScale(QwtPlot::xBottom, rect.left(), rect.right());
  setAxisScale(QwtPlot::yLeft, rect.bottom(), rect.top());

  replot();
}

void ZoomPlot::enableScrollBars(bool enable)
{
  if (_enableScrollBars == enable)
    return;

  _enableScrollBars = enable;
  if (enable == FALSE)
    {
      delete _vScrollBar;
      delete _hScrollBar;
      _vScrollBar = _hScrollBar = NULL;
    }
  else
    {
      _hScrollBar = new ZoomScrollBar(QScrollBar::Horizontal, this);
      _vScrollBar = new ZoomScrollBar(QScrollBar::Vertical, this);

      connect(_vScrollBar, SIGNAL(valueChanged(int)),
              SLOT(vScrollSliderMoved(int)));
      connect(_hScrollBar, SIGNAL(valueChanged(int)),
              SLOT(hScrollSliderMoved(int)));

      _vScrollBar->hide();
      _hScrollBar->hide();
    }
  updateScrollBars();
}

void ZoomPlot::updateScrollBars()
{
  if (axisAutoScale(QwtPlot::xBottom))
    {
      if (_hScrollBar)
        _hScrollBar->hide();
    }
  else
    {
      if (_hScrollBar)
        {
          const QwtScaleDiv &xScaleDiv = *axisScale(QwtPlot::xBottom);
          if (xScaleDiv.lBound() > _initialScale.left() ||
              xScaleDiv.hBound() < _initialScale.right())
            {
              _hScrollBar->setScale(_initialScale.left(),
                                    _initialScale.right());
              _hScrollBar->setSliderPosition(xScaleDiv.lBound(),
                                             xScaleDiv.hBound());
              _hScrollBar->show();
            }
          else
            _hScrollBar->hide();
        }
    }

  if (axisAutoScale(QwtPlot::yLeft))
    {
      if (_vScrollBar)
        _vScrollBar->hide();
    }
  else
    {
      if (_vScrollBar)
        {
          const QwtScaleDiv &yScaleDiv = *axisScale(QwtPlot::yLeft);
          if (yScaleDiv.lBound() > _initialScale.bottom() ||
              yScaleDiv.hBound() < _initialScale.top())
            {
              _vScrollBar->setScale(_initialScale.bottom(),
                                    _initialScale.top());
              _vScrollBar->setSliderPosition(yScaleDiv.lBound(),
                                             yScaleDiv.hBound());
              _vScrollBar->show();
            }
          else
            _vScrollBar->hide();
        }
    }
  resizeScrollBars();
}

void ZoomPlot::resizeScrollBars()
{
  QPoint pos = canvas()->pos();
  int fw = canvas()->frameWidth();

  if (_hScrollBar && _hScrollBar->isVisible())
    {
      int x = pos.x() + fw;
      int w = canvas()->width() - 2 * fw;
      if (_vScrollBar && _vScrollBar->isVisible())
        w -= ZoomScrollBar::dimension();
      int y = pos.y() + fw;
      int h = ZoomScrollBar::dimension();

      _hScrollBar->setGeometry(x, y, w, h);
    }
  if (_vScrollBar && _vScrollBar->isVisible())
    {
      int x = pos.x() + canvas()->width() - fw - ZoomScrollBar::dimension();
      int w = ZoomScrollBar::dimension();
      int y = pos.y() + fw;
      int h = canvas()->height() - 2 * fw;
      if (_hScrollBar && _hScrollBar->isVisible())
        {
          y += ZoomScrollBar::dimension();
          h -= ZoomScrollBar::dimension();
        }

      _vScrollBar->setGeometry(x, y, w, h);
    }
  if (_hScrollBar && _hScrollBar->isVisible() &&
      _vScrollBar && _vScrollBar->isVisible())
    {
      if (_cornerWidget == NULL)
        _cornerWidget = new QLabel(this);
      _cornerWidget->setGeometry(
        _vScrollBar->pos().x(), _hScrollBar->pos().y(),
        ZoomScrollBar::dimension(), ZoomScrollBar::dimension());
      _cornerWidget->show();
    }
  else
    {
      delete _cornerWidget;
      _cornerWidget = NULL;
    }
}

void ZoomPlot::hScrollSliderMoved(int)
{
  double coord[4];

  _hScrollBar->getSliderPosition(coord[0], coord[1]);
  const QwtScaleDiv *yScaleDiv = axisScale(QwtPlot::yLeft);
  coord[2] = yScaleDiv->lBound();
  coord[3] = yScaleDiv->hBound();

  DoubleRect rect(coord[0], coord[2], coord[1], coord[3]);
  rescale(rect);
}

void ZoomPlot::vScrollSliderMoved(int)
{
  double coord[4];

  const QwtScaleDiv *xScaleDiv = axisScale(QwtPlot::xBottom);
  coord[0] = xScaleDiv->lBound();
  coord[1] = xScaleDiv->hBound();
  _vScrollBar->getSliderPosition(coord[2], coord[3]);

  DoubleRect rect(coord[0], coord[2], coord[1], coord[3]);
  rescale(rect);
}

void ZoomPlot::resizeEvent(QResizeEvent *e)
{
  QwtPlot::resizeEvent(e);
  if (_enableScrollBars)
    resizeScrollBars();
}

void ZoomPlot::zoomOut()
{
  if (_scaleStack.isEmpty())
    return;

  _scaleStack.clear();
  rescale(_initialScale);

  updateScrollBars();

  _maxXZoom = _maxYZoom = FALSE;
}
