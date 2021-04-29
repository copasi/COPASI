// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CSPECTOGRAMDATA_H
#define CSPECTOGRAMDATA_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <QPainter>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>

#include <QRectF>

#include <qwt_plot.h>
#include <qwt_painter.h>

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
#  include <qwt_compat.h>
#else
#include <qwt_data.h>
#include <qwt_raster_data.h>
#endif

#include <qwt_plot_curve.h>
#include <qwt_plot_spectrogram.h>

#include "copasi/plot/CPlotItem.h"

#include "copasi/core/CDataObject.h"
#include "copasi/output/COutputHandler.h"
#include "copasi/utilities/CopasiTime.h"
#include "copasi/core/CVector.h"
#include "copasi/core/CMatrix.h"

class CSpectorgramData :
  public QwtRasterData
{
public:
  CSpectorgramData();
  CSpectorgramData(const CSpectorgramData& other);
  CSpectorgramData(const CVector< double > & x,
                   const CVector< double > & y,
                   const CVector< double > & z,
                   size_t size,
                   bool logZ,
                   double limitZ = std::numeric_limits<double>::quiet_NaN(),
                   bool bilinear = true);
  virtual ~CSpectorgramData();

  virtual QwtRasterData *copy() const;

  virtual QwtDoubleRect boundingRect() const;

  virtual QwtDoubleInterval range() const;

  virtual size_t size() const;

  virtual double value(double x, double y) const;

  void setSize(const size_t & size);

  void reallocated(const CVector< double > * pX,
                   const CVector< double > * pY,
                   const CVector< double > * pZ);

  double getLimitZ() const;
  void setLimitZ(double limitZ);

  bool getBilinear() const;
  void setBilinear(bool bilinear);

#if QWT_VERSION >= 0x060200
  virtual QwtInterval interval(Qt::Axis axis) const
  {
    return d_intervals[axis];
  }
  void setInterval(Qt::Axis axis, const QwtInterval & interval)
  {
    d_intervals[axis] = interval;
  }

protected:
  QwtInterval d_intervals[3];
#endif

protected:
  CSpectorgramData &operator = (const CSpectorgramData & rhs);

private:

  void calculateExtremes() const;
  void initializeMatrix();
  double bilinearAround(int xIndex, int yIndex,
                        double x,
                        double y) const;

  const double * mpX;
  const double * mpY;
  const double * mpZ;

  size_t mSize;
  size_t mMaxSize;

  mutable size_t mLastRectangle;
  mutable double mMinX;
  mutable double mMaxX;
  mutable double mMinY;
  mutable double mMaxY;
  mutable double mMinZ;
  mutable double mMaxZ;

  std::vector<double> mValuesX;
  std::vector<double> mValuesY;
  std::vector<double>::iterator mEndX;
  std::vector<double>::iterator mEndY;

  CMatrix<double>* mpMatrix;

  bool mLogZ;
  double mLimitZ;
  bool mBilinear;

  double mDistanceX;
  double mDistanceY;

  size_t mSizeX;
  size_t mSizeY;
};

#endif // CSPECTOGRAMDATA_H
