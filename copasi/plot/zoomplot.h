#ifndef _ZOOMPLOT_H
#define _ZOOMPLOT_H 1

#include <qlist.h>
#include <qscrollbar.h>
#include <qstack.h>
#include <qpoint.h>
#include <qwt_plot.h>
#include "doublerect.h" 
//#include "realtimeplot.h"

class QLabel;
class QMouseEvent;
class ZoomScrollBar;

class ZoomPlot: public QwtPlot
  {
    Q_OBJECT
  public:
    ZoomPlot(QWidget *parent = NULL);

    void setZoomable(bool);
    void enableScrollBars(bool);
    //void hideScrollBars();
    void zoomOut();

  protected:
    virtual void resizeEvent(QResizeEvent *);

  protected slots:
    virtual void mousePressed(const QMouseEvent &);
    virtual void mouseReleased(const QMouseEvent &);
    void hScrollSliderMoved(int);
    void vScrollSliderMoved(int);

  private:
    void zoom(QRect &zoomRectangle);
    void setMinZoomRect(QRect &) const;
    void rescale(const DoubleRect &);

  private:
    bool _zoomable;
    bool _maxXZoom, _maxYZoom;
    QPoint _zoomStartPoint;

    QStack<DoubleRect> _scaleStack;
    DoubleRect _initialScale;

  private:
    void updateScrollBars();
    void resizeScrollBars();

  private:
    bool _enableScrollBars;
    ZoomScrollBar *_vScrollBar;
    ZoomScrollBar *_hScrollBar;
    QLabel *_cornerWidget;
  };

class ZoomScrollBar: protected QScrollBar
  {
    Q_OBJECT
    friend class ZoomPlot;
  protected:
    ZoomScrollBar(Orientation, QWidget *);
    void setScale(double, double);
    void setSliderPosition(double, double);
    void getSliderPosition(double &, double &);
    double minSize() const;

    static int dimension();

  private:
    int mapToTick(double) const;
    double mapFromTick(int) const;

    double _min;
    double _max;
    const int c_ticks;
  };

#endif
