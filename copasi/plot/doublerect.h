#ifndef DBLRECT_H
#define DBLRECT_H

// from qwt examples/realtime_plot

class DoublePoint
  {
  public:
    DoublePoint();
    DoublePoint(double, double);
    DoublePoint &operator=(const DoublePoint &);
    inline int operator==(const DoublePoint &) const;
    inline int operator!=(const DoublePoint &) const;

    inline void setPoint(double x, double y);
    inline void setX(double x) {_x = x;}
    inline void setY(double y) {_y = y;}
    const double &X() const {return _x;}
    const double &Y() const {return _y;}

  private:
    double _x;
    double _y;
  };

class DoubleRect
  {
  public:
    DoubleRect();
    DoubleRect(double x1, double y1, double x2, double y2);

    inline DoublePoint bottomLeft() const {return _bottomLeft;}
    inline DoublePoint topRight() const {return _topRight;}
    inline double left() const {return _bottomLeft.X();}
    inline double right() const {return _topRight.X();}
    inline double top() const {return _topRight.Y();}
    inline double bottom() const {return _bottomLeft.Y();}
    inline double width() const {return _topRight.X() - _bottomLeft.X();}
    inline double height() const {return _topRight.Y() - _bottomLeft.Y();}

  private:
    DoublePoint _bottomLeft;
    DoublePoint _topRight;
  };

int DoublePoint::operator!=(const DoublePoint &other) const
  {
    return !(other == *this);
  }

int DoublePoint::operator==(const DoublePoint &other) const
  {
    return other._x == _x && other._y == _y;
  }

void DoublePoint::setPoint(double x, double y)
{
  _x = x;
  _y = y;
}

#endif
