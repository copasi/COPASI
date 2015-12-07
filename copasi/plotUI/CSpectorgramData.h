// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CSPECTOGRAMDATA_H
#define CSPECTOGRAMDATA_H


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

};

#endif // CSPECTOGRAMDATA_H
