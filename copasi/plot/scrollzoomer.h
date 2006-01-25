/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/scrollzoomer.h,v $
   $Revision: 1.1.2.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/01/25 11:48:07 $
   End CVS Header */

#ifndef _SCROLLZOOMER_H
 #define _SCROLLZOOMER_H

#include <qglobal.h>
 #if QT_VERSION < 0x040000
 #include <qscrollview.h>
 #endif
 #include <qwt_plot_zoomer.h>

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
    void setHScrollBarMode(QScrollView::ScrollBarMode);
    void setVScrollBarMode(QScrollView::ScrollBarMode);

    QScrollView::ScrollBarMode vScrollBarMode () const;
    QScrollView::ScrollBarMode hScrollBarMode () const;
#else
    void setHScrollBarMode(Qt::ScrollBarPolicy);
    void setVScrollBarMode(Qt::ScrollBarPolicy);

    Qt::ScrollBarPolicy vScrollBarMode () const;
    Qt::ScrollBarPolicy hScrollBarMode () const;
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
