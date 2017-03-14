// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLINEARCOLORMAP_H
#define CLINEARCOLORMAP_H

#include <qwt_color_map.h>

#if QWT_VERSION > 0x060000
#include <qwt_compat.h>
#endif

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

  void setAbsoluteStop(double value, const QColor& color);

protected:
  QColor mMissingColor;

  double mAbsoluteStop;
  QColor mAbsoluteStopColor;
  QColor mFrom;
  QColor mTo;
  CLinearColorMap *mpLower;
  CLinearColorMap *mpUpper;

};


#endif // CLINEARCOLORMAP_H
