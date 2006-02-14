/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/scrollbar.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/14 14:35:29 $
   End CVS Header */

#ifndef _SCROLLBAR_H
 #define _SCROLLBAR_H 1

#include <qscrollbar.h>

class ScrollBar: public QScrollBar
  {
    Q_OBJECT

  public:
    ScrollBar(QWidget *parent = NULL);
    ScrollBar(Qt::Orientation, QWidget *parent = NULL);
    ScrollBar(double minBase, double maxBase, bool logscale,
              Qt::Orientation o, QWidget *parent = NULL);

    void setInverted(bool);
    bool isInverted() const;

    void setLogScale(bool l);
    bool isLogScale() const;

    double minBaseValue() const;
    double maxBaseValue() const;

    double minSliderValue() const;
    double maxSliderValue() const;

    int extent() const;

  signals:
    void sliderMoved(Qt::Orientation, double, double);
    void valueChanged(Qt::Orientation, double, double);

  public slots:
    virtual void setBase(double min, double max);
    virtual void moveSlider(double min, double max);

  protected:
    void sliderRange(int value, double &min, double &max) const;
    int mapToTick(double) const;
    double mapFromTick(int) const;

  private slots:
    void catchValueChanged(int value);
    void catchSliderMoved(int value);

  private:
    void init();

    bool d_inverted;
    double d_minBase;
    double d_maxBase;
    int d_baseTicks;
    bool mLogScale;
  };

#endif
