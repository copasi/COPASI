// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CBANDEDGRAPHDATA_H
#define CBANDEDGRAPHDATA_H

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

class CBandedGraphData :
#if QWT_VERSION > 0x060000
  public QwtSeriesData<QPointF>
#else
  public QwtData
#endif

{
public:
  CBandedGraphData();
  CBandedGraphData(const CVector< double > & x,
                   const CVector< double > & y1,
                   const CVector< double > & y2,
                   size_t size);
  virtual ~CBandedGraphData();

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
  double y1(size_t i) const;
  double y2(size_t i) const;

  void setSize(const size_t & size);

  void reallocated(const CVector< double > * pX, const CVector< double > * pY1, const CVector< double > * pY2);

protected:
  CBandedGraphData &operator = (const CBandedGraphData & rhs);

private:
  const double * mpX;
  const double * mpY1;
  const double * mpY2;

  size_t mSize;
  size_t mMaxSize;

  mutable size_t mLastRectangle;
  mutable double mMinX;
  mutable double mMaxX;
  mutable double mMinY;
  mutable double mMaxY;
};

#endif // CBANDEDGRAPHDATA_H
