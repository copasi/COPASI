// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLINEARCOLORMAP_H
#define CLINEARCOLORMAP_H

#include <qwt_color_map.h>

class CLinearColorMap : public QwtLinearColorMap
{
public:
  CLinearColorMap(const QColor &from, const QColor &to,
                  QwtColorMap::Format = QwtColorMap::RGB);

  CLinearColorMap(const CLinearColorMap &);

  virtual ~CLinearColorMap();

  CLinearColorMap &operator=(const CLinearColorMap &);

  virtual QwtColorMap *copy() const;

  virtual QRgb rgb(const QwtDoubleInterval &, double value) const;

protected:
  QColor mMissingColor;

};


#endif // CLINEARCOLORMAP_H
