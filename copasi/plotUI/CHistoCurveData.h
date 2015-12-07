// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CHISTOCURVEDATA_H
#define CHISTOCURVEDATA_H


#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <QtGui/QPainter>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>

#include <QRectF>

#include <qwt_plot.h>
#include <qwt_painter.h>

#if QWT_VERSION > 0x060000
#include <qwt_compat.h>
#else
#include <qwt_data.h>
#include <qwt_raster_data.h>
#endif

#include <qwt_plot_curve.h>
#include <qwt_plot_spectrogram.h>

#include "plot/CPlotItem.h"

#include "report/CCopasiObject.h"
#include "utilities/COutputHandler.h"
#include "utilities/CopasiTime.h"
#include "utilities/CVector.h"
#include "utilities/CMatrix.h"

class CHistoCurveData :
#if QWT_VERSION > 0x060000
  public QwtSeriesData<QPointF>
#else
  public QwtData
#endif

{
public:
  CHistoCurveData();
  CHistoCurveData(const CVector< double > & x, size_t size,
                  const C_FLOAT64 & increment);
  virtual ~CHistoCurveData();

#if QWT_VERSION > 0x060000
  virtual QwtSeriesData<QPointF> *copy() const;
  virtual QPointF sample(size_t i) const;
#else
  virtual QwtData *copy() const;
#endif

  virtual QwtDoubleRect boundingRect() const;

  virtual size_t size() const;

  virtual double x(size_t i) const;
  virtual double y(size_t i) const;

  void setSize(const size_t & size);

  void reallocated(const CVector< double > * pX);

protected:
  CHistoCurveData &operator = (const CHistoCurveData & rhs);

private:
  const double * mpX;
  size_t mSize;
  size_t mMaxSize;

  mutable size_t mLastRectangle;
  mutable double mMinX;
  mutable double mMaxX;
  mutable double mMinY;
  mutable double mMaxY;

  double mIncrement;

  mutable std::map<C_INT32, C_INT32> mMap;
  mutable CVector< double > mHistoX;
  mutable CVector< double > mHistoY;
};

#endif //CHISTOCURVEDATA_H
