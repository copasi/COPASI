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

#ifndef C2DPLOTCURVE_H
#define C2DPLOTCURVE_H

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
#include <qwt_compat.h>
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

// NaN in data splits curve
class C2DPlotCurve : public QwtPlotCurve
{
public:
  C2DPlotCurve(QMutex * pMutex, const CPlotItem::Type & type,
               const COutputInterface::Activity & activity, const QString & title);

  void setDataSize(const size_t & size);

  void reallocatedData(const CVector< double > * pX, const CVector< double > * pY, const CVector< double > * pY2 = 0);

  void setIncrement(const C_FLOAT64 & increment);

  const C_FLOAT64 & getIncrement() const;

  const CPlotItem::Type & getType() const;

  const COutputInterface::Activity & getActivity() const;

protected:

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)

  void myDrawLines(QPainter *painter,
                   const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                   const QRectF &canvasRect, int from, int to) const;

  virtual void drawCurve(QPainter *p, int style, const QwtScaleMap &xMap,
                         const QwtScaleMap &yMap, const QRectF &canvasRect, int from, int to) const;

  virtual void drawSymbols(QPainter *p, const QwtSymbol &, const QwtScaleMap &xMap,
                           const QwtScaleMap &yMap, const QRectF &canvasRect, int from, int to) const;

#else

  void myDrawLines(QPainter *painter,
                   const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                   int from, int to) const;

  //Reroute curve plotting to our own routine
  virtual void drawCurve(QPainter *painter, int style,
                         const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                         int from, int to) const;

  //Reroute drawing to our own routine, mainly to disable plotting of NaN values.
  virtual void drawSymbols(QPainter *painter, const QwtSymbol &symbol,
                           const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                           int from, int to) const;
#endif

private:
  QMutex * mpMutex;

  CPlotItem::Type mCurveType;

  C_FLOAT64 mIncrement;

  COutputInterface::Activity mActivity;
};

#endif //C2DPLOTCURVE_H
