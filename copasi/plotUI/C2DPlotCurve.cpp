// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

#include <cmath>

#include <copasi/plotUI/C2DCurveData.h>
#include <copasi/plotUI/CHistoCurveData.h>
#include <copasi/plotUI/CBandedGraphData.h>

#include <copasi/plotUI/C2DPlotCurve.h>

C2DPlotCurve::C2DPlotCurve(QMutex *pMutex, const CPlotItem::Type &type, const COutputInterface::Activity &activity, const QString &title):
  QwtPlotCurve(title),
  mpMutex(pMutex),
  mCurveType(type),
  mIncrement(1.0),
  mActivity(activity)
{
  assert(mpMutex != NULL);
}

void C2DPlotCurve::setDataSize(const size_t & size)
{
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)

  switch (mCurveType)
    {
      case CPlotItem::curve2d:
        static_cast< C2DCurveData * >(data())->setSize(size);
        break;

      case CPlotItem::bandedGraph:
        static_cast< CBandedGraphData * >(data())->setSize(size);
        break;

      case CPlotItem::histoItem1d:
        static_cast< CHistoCurveData * >(data())->setSize(size);
        break;

      default:
        fatalError();
        break;
    }

#else

  switch (mCurveType)
    {
      case CPlotItem::curve2d:
        static_cast< C2DCurveData * >(&data())->setSize(size);
        break;

      case CPlotItem::bandedGraph:
        static_cast< CBandedGraphData * >(&data())->setSize(size);
        break;

      case CPlotItem::histoItem1d:
        static_cast< CHistoCurveData * >(&data())->setSize(size);
        break;

      default:
        fatalError();
        break;
    }

#endif
}

void C2DPlotCurve::reallocatedData(const CVector< double > * pX, const CVector< double > * pY, const CVector< double > * pY2)
{
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)

  switch (mCurveType)
    {
      case CPlotItem::curve2d:
        static_cast< C2DCurveData * >(data())->reallocated(pX, pY);
        break;

      case CPlotItem::bandedGraph:
        static_cast< CBandedGraphData * >(data())->reallocated(pX, pY, pY2);
        break;

      case CPlotItem::histoItem1d:
        static_cast< CHistoCurveData * >(data())->reallocated(pX);
        break;

      default:
        fatalError();
        break;
    }

#else

  switch (mCurveType)
    {
      case CPlotItem::curve2d:
        static_cast< C2DCurveData * >(&data())->reallocated(pX, pY);
        break;

      case CPlotItem::bandedGraph:
        static_cast< CBandedGraphData * >(&data())->reallocated(pX, pY, pY2);
        break;

      case CPlotItem::histoItem1d:
        static_cast< CHistoCurveData * >(&data())->reallocated(pX);
        break;

      default:
        fatalError();
        break;
    }

#endif
}

void C2DPlotCurve::setIncrement(const C_FLOAT64 & increment)
{
  mIncrement = increment;
}

const C_FLOAT64 & C2DPlotCurve::getIncrement() const
{
  return mIncrement;
}

const CPlotItem::Type & C2DPlotCurve::getType() const
{
  return mCurveType;
}

const COutputInterface::Activity & C2DPlotCurve::getActivity() const
{
  return mActivity;
}

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)

//draw the several curves, separated by NaNs.
void C2DPlotCurve::myDrawLines(QPainter *painter,
                               const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                               const QRectF &canvasRect, int from, int to) const
{
  int to2;

  do
    {
      int i;

      for (i = from; i <= to; ++i)
        if (std::isnan(this->sample(i).x()) || std::isnan(sample(i).y())) //NaN
          break;

      if (i == from)
        {
          ++from;
          continue;
        }

      to2 = i - 1;

      QwtPlotCurve::drawLines(painter, xMap, yMap, canvasRect, from, to2);

      from = to2 + 2;
    }
  while (from < to);
}

//virtual
void C2DPlotCurve::drawCurve(QPainter *painter, int style,
                             const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                             const QRectF &canvasRect, int from, int to) const
{
  QMutexLocker Locker(mpMutex);

  if (style == Lines)
    {
      myDrawLines(painter, xMap, yMap, canvasRect, from, to);
    }
  else
    {
      QwtPlotCurve::drawCurve(painter, style, xMap, yMap, canvasRect, from, to);
    }
}

void C2DPlotCurve::drawSymbols(QPainter *painter, const QwtSymbol &symbol,
                               const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                               const QRectF &canvasRect, int from, int to) const
{

  int from2 = from;
  int to2;

  for (;;)
    {

      //find the next not-NaN point
      while (std::isnan(sample(from2).x()) || std::isnan(sample(from2).y()))
        {
          ++from2;

          if (from2 >= to)
            return;
        }

      //find the nex NaN point (or the end of data)
      to2 = from2;

      do
        {
          ++to2;

          if (to2 > to)
            break;
        }
      while (!(std::isnan(sample(to2).x()) || std::isnan(sample(to2).y())));

      --to2;

      QwtPlotCurve::drawSymbols(painter, symbol, xMap, yMap, canvasRect, from2, to2);

      //are we done?
      if (to2 >= to)
        return;

      //continue with the next data point
      from2 = to2 + 1;
    }
}

#else

//draw the several curves, separated by NaNs.
void C2DPlotCurve::myDrawLines(QPainter *painter,
                               const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                               int from, int to) const
{
  int to2;

  do
    {
      int i;

      for (i = from; i <= to; ++i)
        if (std::isnan(x(i)) || std::isnan(y(i))) //NaN
          break;

      if (i == from)
        {
          ++from;
          continue;
        }

      to2 = i - 1;

      QwtPlotCurve::drawLines(painter, xMap, yMap, from, to2);

      from = to2 + 2;
    }
  while (from < to);
}

//virtual
void C2DPlotCurve::drawCurve(QPainter *painter, int style,
                             const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                             int from, int to) const
{
  QMutexLocker Locker(mpMutex);

  if (style == Lines)
    {
      myDrawLines(painter, xMap, yMap, from, to);
    }
  else
    {
      QwtPlotCurve::drawCurve(painter, style, xMap, yMap, from, to);
    }
}

void C2DPlotCurve::drawSymbols(QPainter *painter, const QwtSymbol &symbol,
                               const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                               int from, int to) const
{

  int from2 = from;
  int to2;

  for (;;)
    {

      //find the next not-NaN point
      while (std::isnan(x(from2)) || std::isnan(y(from2)))
        {
          ++from2;

          if (from2 >= to)
            return;
        }

      //find the nex NaN point (or the end of data)
      to2 = from2;

      do
        {
          ++to2;

          if (to2 > to)
            break;
        }
      while (!(std::isnan(x(to2)) || std::isnan(y(to2))));

      --to2;

      QwtPlotCurve::drawSymbols(painter, symbol, xMap, yMap, from2, to2);

      //are we done?
      if (to2 >= to)
        return;

      //continue with the next data point
      from2 = to2 + 1;
    }
}

#endif
