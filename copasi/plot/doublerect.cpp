/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/doublerect.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:00 $
   End CVS Header */

#include <qglobal.h>
#include "doublerect.h"

// from qwt examples/realtime_plot

DoublePoint::DoublePoint():
    _x(0.0),
    _y(0.0)
{}

DoublePoint::DoublePoint(double x, double y):
    _x(x),
    _y(y)
{}

DoublePoint &DoublePoint::operator=(const DoublePoint &other)
{
  _x = other._x;
  _y = other._y;

  return *this;
}

DoubleRect::DoubleRect()
{
  return;
}

DoubleRect::DoubleRect(double x1, double y1, double x2, double y2):
    _bottomLeft(x1, y1),
    _topRight(x2, y2)
{
  double h;
  if (_bottomLeft.X() > _topRight.X())
    {
      h = _topRight.X();
      _topRight.setX(_bottomLeft.X());
      _bottomLeft.setX(h);
    }
  if (_bottomLeft.Y() > _topRight.Y())
    {
      h = _topRight.Y();
      _topRight.setY(_bottomLeft.Y());
      _bottomLeft.setY(h);
    }
};
