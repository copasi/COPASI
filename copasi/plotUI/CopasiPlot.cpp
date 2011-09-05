// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/CopasiPlot.cpp,v $
//   $Revision: 1.75 $
//   $Name:  $
//   $Author: tjohann $
//   $Date: 2011/09/05 12:06:51 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/CopasiPlot.cpp,v $
//   $Revision: 1.75 $
//   $Name:  $
//   $Author: tjohann $
//   $Date: 2011/09/05 12:06:51 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qstring.h>
#include <qcolor.h>   //might need to go to the header file
#include <qcursor.h>
#include <QMutexLocker>

#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_scale_engine.h>

#include <float.h>
#include <limits>
#include <algorithm>

#include "scrollzoomer.h"

#include "CopasiPlot.h"
#include "plot/CPlotSpecification.h"
#include "UI/qtUtilities.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "commandline/CLocaleString.h"

#define ActivitySize 8

//********************  data  *********************************************
C2DCurveData::C2DCurveData():
    QwtData(),
    mpX(NULL),
    mpY(NULL),
    mSize(0),
    mMaxSize(0),
    mLastRectangle(0),
    mMinX(std::numeric_limits<double>::quiet_NaN()),
    mMaxX(std::numeric_limits<double>::quiet_NaN()),
    mMinY(std::numeric_limits<double>::quiet_NaN()),
    mMaxY(std::numeric_limits<double>::quiet_NaN())
{}

C2DCurveData::C2DCurveData(const CVector< C_FLOAT64 > & x, const CVector< C_FLOAT64 > & y, size_t size):
    QwtData(),
    mpX(x.array()),
    mpY(y.array()),
    mSize(size),
    mMaxSize(x.size()),
    mLastRectangle(0),
    mMinX(std::numeric_limits<double>::quiet_NaN()),
    mMaxX(std::numeric_limits<double>::quiet_NaN()),
    mMinY(std::numeric_limits<double>::quiet_NaN()),
    mMaxY(std::numeric_limits<double>::quiet_NaN())
{
  assert(x.size() == y.size());
  assert(mSize <= mMaxSize);
}

C2DCurveData::~C2DCurveData()
{}

QwtData * C2DCurveData::copy() const
{
  C2DCurveData * pCopy = new C2DCurveData();

  *pCopy = *this;

  return pCopy;
}

size_t C2DCurveData::size() const
{
  return mSize;
}

double C2DCurveData::x(size_t i) const
{
  return *(mpX + i);
}

double C2DCurveData::y(size_t i) const
{
  return *(mpY + i);
}

QwtDoubleRect C2DCurveData::boundingRect() const
{
  if (mSize <= 0)
    return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

  if (mLastRectangle == mSize)
    return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);

  const double *xIt = mpX + mLastRectangle;
  const double *yIt = mpY + mLastRectangle;
  const double *end = mpX + mSize;

  mLastRectangle = mSize;

  // We have to remember whether we have an initial NaN
  bool MinXisNaN = isnan(mMinX);
  bool MaxXisNaN = isnan(mMaxX);
  bool MinYisNaN = isnan(mMinY);
  bool MaxYisNaN = isnan(mMaxY);

  while (xIt < end)
    {
      const double xv = *xIt++;

      if (!isnan(xv))
        {
          if (xv < mMinX || MinXisNaN)
            {
              mMinX = xv;
              MinXisNaN = false;
            }

          if (xv > mMaxX || MaxXisNaN)
            {
              mMaxX = xv;
              MaxXisNaN = false;
            }
        }

      const double yv = *yIt++;

      if (!isnan(yv))
        {
          if (yv < mMinY || MinYisNaN)
            {
              mMinY = yv;
              MinYisNaN = false;
            }

          if (yv > mMaxY || MaxYisNaN)
            {
              mMaxY = yv;
              MaxYisNaN = false;
            }
        }
    }

  if (isnan(mMinX + mMaxX + mMinY + mMaxY))
    return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

  // We need to avoid very small data ranges (absolute and relative)
  C_FLOAT64 minRange = fabs(mMinX + mMaxX) * 5.e-5 + DBL_MIN * 100.0;

  if (mMaxX - mMinX < minRange)
    {
      mMinX = mMinX - minRange * 0.5;
      mMaxX = mMaxX + minRange * 0.5;
    }

  minRange = fabs(mMinY + mMaxY) * 5e-5 + DBL_MIN * 100.0;

  if (mMaxY - mMinY < minRange)
    {
      mMinY = mMinY - minRange * 0.5;
      mMaxY = mMaxY + minRange * 0.5;
    }

  return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);
}

void C2DCurveData::setSize(const size_t & size)
{
  mSize = size;
  assert(mSize <= mMaxSize);
}

void C2DCurveData::reallocated(const CVector< double > * pX, const CVector< double > *pY)
{
  mpX = pX->array();
  mpY = pY->array();
  mMaxSize = pX->size();

  assert(mSize <= mMaxSize);
}

C2DCurveData & C2DCurveData::operator = (const C2DCurveData & rhs)
{
  mpX = rhs.mpX;
  mpY = rhs.mpY;
  mSize = rhs.mSize;
  mMaxSize = rhs.mMaxSize;
  mLastRectangle = rhs.mLastRectangle;
  mMinX = rhs.mMinX;
  mMaxX = rhs.mMaxX;
  mMinY = rhs.mMinY;
  mMaxY = rhs.mMaxY;

  return * this;
}

#ifdef COPASI_BANDED_GRAPH
//********************  CBandedGraphData  *********************************
CBandedGraphData::CBandedGraphData():
    QwtData(),
    mpX(NULL),
    mpY1(NULL),
    mpY2(NULL),
    mSize(0),
    mMaxSize(0),
    mLastRectangle(0),
    mMinX(std::numeric_limits<double>::quiet_NaN()),
    mMaxX(std::numeric_limits<double>::quiet_NaN()),
    mMinY(std::numeric_limits<double>::quiet_NaN()),
    mMaxY(std::numeric_limits<double>::quiet_NaN())
{}

CBandedGraphData::CBandedGraphData(const CVector< double > & x,
                                   const CVector< double > & y1,
                                   const CVector< double > & y2,
                                   size_t size):
    QwtData(),
    mpX(x.array()),
    mpY1(y1.array()),
    mpY2(y2.array()),
    mSize(size),
    mMaxSize(x.size()),
    mLastRectangle(0),
    mMinX(std::numeric_limits<double>::quiet_NaN()),
    mMaxX(std::numeric_limits<double>::quiet_NaN()),
    mMinY(std::numeric_limits<double>::quiet_NaN()),
    mMaxY(std::numeric_limits<double>::quiet_NaN())
{
  assert(x.size() == y1.size());
  assert(x.size() == y2.size());
  assert(mSize <= mMaxSize);
}

CBandedGraphData::~CBandedGraphData()
{}

QwtData *
CBandedGraphData::copy() const
{
  CBandedGraphData * pCopy = new CBandedGraphData();

  *pCopy = *this;

  return pCopy;
}

size_t
CBandedGraphData::size() const
{return 2*mSize;}


double CBandedGraphData::x(size_t i) const
{
  // to make a polygon out of the two data curves
  // one curve goes in order, the other backwards
  if (i >= mSize)
    i = (2 * mSize - i - 1);

  return *(mpX + i);
}

double CBandedGraphData::y(size_t i) const
{
  double ret;

  // to make a polygon out of the two data curves
  // one curve goes in order, the other backwards
  if (i < mSize)
    ret = *(mpY1 + i);
  else
    ret = *(mpY2 + (2 * mSize - i - 1));

  return ret;
}

double CBandedGraphData::y1(size_t i) const
{
  return *(mpY1 + i);
}

double CBandedGraphData::y2(size_t i) const
{
  return *(mpY2 + i);
}

QwtDoubleRect
CBandedGraphData::boundingRect() const
{
  if (mSize <= 0)
    return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

  if (mLastRectangle == mSize)
    return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);

  const double *xIt = mpX + mLastRectangle;
  const double *yIt1 = mpY1 + mLastRectangle;
  const double *yIt2 = mpY2 + mLastRectangle;
  const double *end = mpX + mSize;

  mLastRectangle = mSize;

  // We have to remember whether we have an initial NaN
  bool MinXisNaN = isnan(mMinX);
  bool MaxXisNaN = isnan(mMaxX);
  bool MinYisNaN = isnan(mMinY);
  bool MaxYisNaN = isnan(mMaxY);

  while (xIt < end)
    {
      const double xv = *xIt++;

      if (!isnan(xv))
        {
          if (xv < mMinX || MinXisNaN)
            {
              mMinX = xv;
              MinXisNaN = false;
            }

          if (xv > mMaxX || MaxXisNaN)
            {
              mMaxX = xv;
              MaxXisNaN = false;
            }
        }

      double yv1 = *yIt1++;
      double yv2 = *yIt2++;

      if (isnan(yv1) || isnan(yv2))
        {
          yv1 = isnan(yv1) ? yv2 : yv1;
          yv2 = yv1;
        }
      else if (yv1 > yv2)
        {
          double tmp = yv1;
          yv1 = yv2;
          yv2 = tmp;
        } // now: yv1 <= yv2

      if (!isnan(yv1))
        {
          if (yv1 < mMinY || MinYisNaN)
            {
              mMinY = yv1;
              MinYisNaN = false;
            }

          if (yv2 > mMaxY || MaxYisNaN)
            {
              mMaxY = yv2;
              MaxYisNaN = false;
            }
        }
    }

  if (isnan(mMinX + mMaxX + mMinY + mMaxY))
    return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

  // We need to avoid very small data ranges (absolute and relative)
  C_FLOAT64 minRange = fabs(mMinX + mMaxX) * 5.e-5 + DBL_MIN * 100.0;

  if (mMaxX - mMinX < minRange)
    {
      mMinX = mMinX - minRange * 0.5;
      mMaxX = mMaxX + minRange * 0.5;
    }

  minRange = fabs(mMinY + mMaxY) * 5e-5 + DBL_MIN * 100.0;

  if (mMaxY - mMinY < minRange)
    {
      mMinY = mMinY - minRange * 0.5;
      mMaxY = mMaxY + minRange * 0.5;
    }

  return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);
}

void
CBandedGraphData::setSize(const size_t & size)
{
  mSize = size;
  assert(mSize <= mMaxSize);
}

void
CBandedGraphData::reallocated(const CVector< double > * pX, const CVector< double > *pY1, const CVector< double > *pY2)
{
  mpX = pX->array();
  mpY1 = pY1->array();
  mpY2 = pY2->array();
  mMaxSize = pX->size();

  assert(mSize <= mMaxSize);
}

CBandedGraphData & CBandedGraphData::operator = (const CBandedGraphData & rhs)
{
  mpX = rhs.mpX;
  mpY1 = rhs.mpY1;
  mpY2 = rhs.mpY2;
  mSize = rhs.mSize;
  mMaxSize = rhs.mMaxSize;
  mLastRectangle = rhs.mLastRectangle;
  mMinX = rhs.mMinX;
  mMaxX = rhs.mMaxX;
  mMinY = rhs.mMinY;
  mMaxY = rhs.mMaxY;

  return * this;
}
#endif COPASI_BANDED_GRAPH

//********************  data  *********************************************
CHistoCurveData::CHistoCurveData():
    QwtData(),
    mpX(NULL),
    mSize(0),
    mMaxSize(0),
    mLastRectangle(0),
    mMinX(std::numeric_limits<double>::quiet_NaN()),
    mMaxX(std::numeric_limits<double>::quiet_NaN()),
    mMinY(std::numeric_limits<double>::quiet_NaN()),
    mMaxY(std::numeric_limits<double>::quiet_NaN()),
    mIncrement(1.0),
    mMap(),
    mHistoX(0),
    mHistoY(0)
{}

CHistoCurveData::CHistoCurveData(const CVector< C_FLOAT64 > & x,
                                 size_t size,
                                 const C_FLOAT64 & increment):
    QwtData(),
    mpX(x.array()),
    mSize(size),
    mMaxSize(x.size()),
    mLastRectangle(0),
    mMinX(std::numeric_limits<double>::quiet_NaN()),
    mMaxX(std::numeric_limits<double>::quiet_NaN()),
    mMinY(std::numeric_limits<double>::quiet_NaN()),
    mMaxY(std::numeric_limits<double>::quiet_NaN()),
    mIncrement(increment),
    mMap(),
    mHistoX(0),
    mHistoY(0)
{
  assert(mSize <= mMaxSize);
}

CHistoCurveData::~CHistoCurveData()
{}

QwtData * CHistoCurveData::copy() const
{
  CHistoCurveData * pCopy = new CHistoCurveData();

  *pCopy = *this;

  return pCopy;
}

size_t CHistoCurveData::size() const
{
  return mHistoX.size();
}

double CHistoCurveData::x(size_t i) const
{
  return mHistoX[i];
}

double CHistoCurveData::y(size_t i) const
{
  return mHistoY[i];
}

QwtDoubleRect CHistoCurveData::boundingRect() const
{
  if (mSize <= 0)
    return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

  if (mLastRectangle == mSize)
    return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);

  const double *xIt = mpX + mLastRectangle;
  const double *end = mpX + mSize;

  mLastRectangle = mSize;

  double InvIncrement = 1.0 / mIncrement;

  for (; xIt != end; ++xIt)
    {
      //just ignore breaks. Later we perhaps want to start a new histogram...
      if (isnan(*xIt)) //NaN
        continue;

      if (-std::numeric_limits< C_FLOAT64 >::infinity() < *xIt &&
          *xIt < std::numeric_limits< C_FLOAT64 >::infinity())
        {
          mMap[(C_INT32) floor(*xIt * InvIncrement)]++;
          mMap[(C_INT32) floor(*xIt * InvIncrement) + 1];
        }
    }

  //construct arrays
  mHistoX.resize(mMap.size() + 1);
  mHistoY.resize(mMap.size() + 1);

  double *pX = mHistoX.array();
  double *pY = mHistoY.array();

  //add one bin to the left
  if (mMap.size() > 0)
    {
      *pX = (mMap.begin()->first - 1) * mIncrement;
    }
  else
    {
      *pX = 0.0;
    }

  *pY = 0.0;

  mMinX = mMaxX = *pX++;
  mMinY = mMaxY = *pY++;

  C_FLOAT64 tmpFactor = 1.0 / (mSize * mIncrement);
  std::map<C_INT32, C_INT32>::const_iterator it = mMap.begin();
  std::map<C_INT32, C_INT32>::const_iterator itEnd = mMap.end();

  for (; it != itEnd; ++it, ++pX, ++pY)
    {
      //TODO use pointer increments instead of [...]
      *pX = it->first * mIncrement;
      *pY = (double)it->second * tmpFactor;

      if (*pX < mMinX)
        mMinX = *pX;

      if (*pX > mMaxX)
        mMaxX = *pX;

      if (*pY < mMinY)
        mMinY = *pY;

      if (*pY > mMaxY)
        mMaxY = *pY;
    }

  return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);
}

void CHistoCurveData::setSize(const size_t & size)
{
  mSize = size;
  assert(mSize <= mMaxSize);
}

void CHistoCurveData::reallocated(const CVector< double > * pX)
{
  mpX = pX->array();
  mMaxSize = pX->size();

  assert(mSize <= mMaxSize);
}

CHistoCurveData & CHistoCurveData::operator = (const CHistoCurveData & rhs)
{
  mpX = rhs.mpX;
  mSize = rhs.mSize;
  mMaxSize = rhs.mMaxSize;

  mLastRectangle = rhs.mLastRectangle;
  mMinX = rhs.mMinX;
  mMaxX = rhs.mMaxX;
  mMinY = rhs.mMinY;
  mMaxY = rhs.mMaxY;

  mIncrement = rhs.mIncrement;
  mMap = rhs.mMap;
  mHistoX = rhs.mHistoX;
  mHistoY = rhs.mHistoY;

  return * this;
}

//********************  curve  ********************************************

void C2DPlotCurve::setDataSize(const size_t & size)
{
  switch (mCurveType)
    {
      case CPlotItem::curve2d:
        static_cast< C2DCurveData * >(&data())->setSize(size);
        break;

#ifdef COPASI_BANDED_GRAPH
      case CPlotItem::bandedGraph:
        static_cast< CBandedGraphData * >(&data())->setSize(size);
        break;
#endif // COPASI_BANDED_GRAPH

      case CPlotItem::histoItem1d:
        static_cast< CHistoCurveData * >(&data())->setSize(size);
        break;

      default:
        fatalError();
        break;
    }
}

#ifndef COPASI_BANDED_GRAPH
void C2DPlotCurve::reallocatedData(const CVector< double > * pX, const CVector< double > * pY)
#else
void C2DPlotCurve::reallocatedData(const CVector< double > * pX, const CVector< double > * pY, const CVector< double > * pY2)
#endif // COPASI_BANDED_GRAPH
{

  switch (mCurveType)
    {
      case CPlotItem::curve2d:
        static_cast< C2DCurveData * >(&data())->reallocated(pX, pY);
        break;

#ifdef COPASI_BANDED_GRAPH
      case CPlotItem::bandedGraph:
        static_cast< CBandedGraphData * >(&data())->reallocated(pX, pY, pY2);
        break;
#endif // COPASI_BANDED_GRAPH

      case CPlotItem::histoItem1d:
        static_cast< CHistoCurveData * >(&data())->reallocated(pX);
        break;

      default:
        fatalError();
        break;
    }
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
        if (isnan(x(i))) //NaN
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

//************************************
C_FLOAT64 CopasiPlot::MissingValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();

CopasiPlot::CopasiPlot(QWidget* parent):
    QwtPlot(parent),
    mCurveMap(),
    mpPlotSpecification(NULL),
    mNextPlotTime(),
    mIgnoreUpdate(false),
    mpZoomer(NULL)
{}

CopasiPlot::CopasiPlot(const CPlotSpecification* plotspec, QWidget* parent):
    QwtPlot(parent),
    mCurveMap(),
    mpPlotSpecification(NULL),
    mNextPlotTime(),
    mIgnoreUpdate(false),
    mpZoomer(NULL)
{
  QwtLegend *legend = new QwtLegend;
  legend->setItemMode(QwtLegend::CheckableItem);

  // whole legend can not be displayed at bottom on DARWIN
  // maybe a Qwt bug ?!?
#ifdef Darwin
  insertLegend(legend, QwtPlot::TopLegend);
#else
  insertLegend(legend, QwtPlot::BottomLegend);
#endif

  // Set up the zoom facility
  mpZoomer = new ScrollZoomer(canvas());
  mpZoomer->setRubberBandPen(QColor(Qt::black));
  mpZoomer->setTrackerPen(QColor(Qt::black));
  mpZoomer->setTrackerMode(QwtPicker::AlwaysOn);
  mpZoomer->setTrackerFont(this->font());

  // white background better for printing...
  setCanvasBackground(Qt::white);

  //  setTitle(FROM_UTF8(plotspec->getTitle()));
  setCanvasLineWidth(0);

  canvas()->setPaintAttribute(QwtPlotCanvas::PaintPacked, true);

  connect(this, SIGNAL(legendChecked(QwtPlotItem *, bool)),
          SLOT(showCurve(QwtPlotItem *, bool)));

  // Size the vectors to be able to store information for all activities.
  mData.resize(ActivitySize);
  mObjectValues.resize(ActivitySize);
  mObjectInteger.resize(ActivitySize);
  mDataSize.resize(ActivitySize);
  mDataIndex.clear();

  // Initialize from the plot specification
  initFromSpec(plotspec);
  connect(this, SIGNAL(replotSignal()), this, SLOT(replot()));
}

bool CopasiPlot::initFromSpec(const CPlotSpecification* plotspec)
{
  mIgnoreUpdate = true;
  mpPlotSpecification = plotspec;

  if (mpZoomer) mpZoomer->setEnabled(false);

  size_t k, kmax = mpPlotSpecification->getItems().size();

  setTitle(FROM_UTF8(mpPlotSpecification->getTitle()));

  CPlotItem* pItem;
  QColor curveColours[6] = {QColor(255, 0, 0), QColor(0, 0, 255), QColor(0, 230, 0), QColor(0, 190, 240), QColor(240, 0, 255), QColor(240, 200, 0)} ; //TODO

  mCurves.resize(kmax);
  mHistoIndices.resize(kmax);

  std::map< std::string, C2DPlotCurve * >::iterator found;

  std::map< std::string, C2DPlotCurve * > CurveMap = mCurveMap;
  mCurveMap.clear();

  size_t HistogramIndex = 0;

  for (k = 0; k < kmax; k++)
    {
      pItem = mpPlotSpecification->getItems()[k];

      C2DPlotCurve * pCurve;
      bool Visible = true;

      // Qwt does not like it to reuse the curve as this may lead to access
      // violation. We therefore delete the curves but remember their visibility.
      if ((found = CurveMap.find(pItem->CCopasiParameter::getKey())) != CurveMap.end())
        {
          pCurve = found->second;
          Visible = pCurve->isVisible();
          pdelete(pCurve);
          CurveMap.erase(found);
        }

      // set up the curve
      pCurve = new C2DPlotCurve(&mMutex,
                                pItem->getType(),
                                pItem->getActivity(),
                                FROM_UTF8(pItem->getTitle()));
      mCurves[k] = pCurve;
      mCurveMap[pItem->CCopasiParameter::getKey()] = pCurve;

      pCurve->setPen(curveColours[k % 6]);
      pCurve->attach(this);

      showCurve(pCurve, Visible);

      switch (pCurve->getType())
        {
          case CPlotItem::curve2d:

            switch (*pItem->getValue("Line type").pUINT)
              {
                case 0:           //curve
                  pCurve->setStyle(QwtPlotCurve::Lines);
                  pCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
                  break;
                case 1:           //points
                  pCurve->setStyle(QwtPlotCurve::Dots);
                  break;
                case 2:           //symbols
                  pCurve->setStyle(QwtPlotCurve::NoCurve);
                  const QColor &c = curveColours[k % 6];
                  pCurve->setSymbol(QwtSymbol(QwtSymbol::Cross, QBrush(c), QPen(c), QSize(5, 5)));
                  break;
              }

            break;

#ifdef COPASI_BANDED_GRAPH
          case CPlotItem::bandedGraph:
            pCurve->setStyle(QwtPlotCurve::Lines);
            pCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
            {
              QColor &c = curveColours[k % 6];
              c.setAlpha(64);
              pCurve->setBrush(c);
            }
            break;
#endif // COPASI_BANDED_GRAPH

          case CPlotItem::histoItem1d:
            // Store the index of the histogram to be created
            mHistoIndices[k] = HistogramIndex++;
            pCurve->setIncrement(*pItem->getValue("increment").pDOUBLE);

            pCurve->setStyle(QwtPlotCurve::Steps);
            pCurve->setYAxis(QwtPlot::yRight);
            pCurve->setCurveAttribute(QwtPlotCurve::Inverted);
            break;

          default :
            mIgnoreUpdate = false;
            fatalError();
            break;
        }
    }

  // Remove unused curves if definition has changed
  std::map< std::string, C2DPlotCurve * >::iterator it = CurveMap.begin();
  std::map< std::string, C2DPlotCurve * >::iterator end = CurveMap.end();

  for (; it != end; ++it)
    pdelete(it->second);

  if (plotspec->isLogX())
    setAxisScaleEngine(xBottom, new QwtLog10ScaleEngine());
  else
    setAxisScaleEngine(xBottom, new QwtLinearScaleEngine());

  setAxisAutoScale(xBottom);

  if (plotspec->isLogY())
    setAxisScaleEngine(yLeft, new QwtLog10ScaleEngine());
  else
    setAxisScaleEngine(yLeft, new QwtLinearScaleEngine());

  setAxisAutoScale(yLeft);

  mIgnoreUpdate = false;

  return true; //TODO really check!
}

bool CopasiPlot::compile(std::vector< CCopasiContainer * > listOfContainer,
                         const CCopasiDataModel* pDataModel)
{
  clearBuffers();

  size_t i, imax;
  size_t j, jmax;

  std::pair< std::set< const CCopasiObject * >::iterator, bool > Inserted;
  std::pair< Activity, size_t > DataIndex;
  std::vector< std::set < const CCopasiObject * > > ActivityObjects;

  ActivityObjects.resize(ActivitySize);

  // Loop over all curves.
  imax = mpPlotSpecification->getItems().size();
  mDataIndex.resize(imax);

  std::vector< std::vector < const CCopasiObject * > >::iterator itX;
  assert(pDataModel != NULL);

  for (i = 0; i < imax; ++i)
    {
      CPlotItem * pItem = mpPlotSpecification->getItems()[i];
      Activity ItemActivity = pItem->getActivity();
      DataIndex.first = ItemActivity;

      // Loop over all channels
      jmax = pItem->getNumChannels();
      mDataIndex[i].resize(jmax);

      for (j = 0; j < jmax; ++j)
        {
          const CCopasiObject* pObj =
            pDataModel->ObjectFromName(listOfContainer, pItem->getChannels()[j]);

          if (pObj)
            mObjects.insert(pObj);
          else
            CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 6,
                           pItem->getChannels()[j].c_str());

          // Remember the actual order for saving the data.
          // Note, we are currently only dealing with 2D curves and histograms.
          // In addition the data is not normalized. The same data column may appear
          // multiple times, e.g. as X value and as Y value for another curve.
          if (j == 0)
            {
              // We have an X value
              for (itX = mSaveCurveObjects.begin(); itX != mSaveCurveObjects.end(); ++itX)
                if (*itX->begin() == pObj) break;

              if (itX == mSaveCurveObjects.end())
                {
                  std::vector < const CCopasiObject * > NewX;
                  NewX.push_back(pObj);

                  mSaveCurveObjects.push_back(NewX);
                  itX = mSaveCurveObjects.end() - 1;

                  setAxisUnits(xBottom, pObj);
                }

              if (pItem->getType() == CPlotItem::histoItem1d)
                mSaveHistogramObjects.push_back(pObj);
            }
          else
            {
              itX->push_back(pObj);
              setAxisUnits(yLeft, pObj);
            }

          Inserted = ActivityObjects[ItemActivity].insert(pObj);

          if (Inserted.second)
            {
              if (ItemActivity & COutputInterface::BEFORE) mHaveBefore = true;

              if (ItemActivity & COutputInterface::DURING) mHaveDuring = true;

              if (ItemActivity & COutputInterface::AFTER) mHaveAfter = true;

              // The insert was successful
              DataIndex.second = ActivityObjects[ItemActivity].size() - 1;

              // Allocate the data buffer
              mData[ItemActivity].push_back(new CVector<double>(1000));

              // Store the pointer to the current object value. (Only if it has a double or integer value
              // and the value pointer actually exists. If not, use a dummy value.)
              void * tmp;

              if ((pObj && (pObj->isValueInt() || pObj->isValueDbl())) && (tmp = pObj->getValuePointer()))
                {
                  mObjectValues[ItemActivity].push_back((C_FLOAT64 *) tmp); //pObj->getValuePointer());
                  mObjectInteger[ItemActivity].push_back(pObj->isValueInt());
                }
              else
                {
                  mObjectValues[ItemActivity].push_back(&MissingValue);
                  mObjectInteger[ItemActivity].push_back(false);
                }

              // Store [curve][channel] to data index
              mDataIndex[i][j] = DataIndex;

              // Store the [Activity][object] to data index.
              mObjectIndex[ItemActivity][pObj] = DataIndex.second;
            }
          else
            {
              // The object already existed we only need to
              // store [curve][channel] to data index.
              DataIndex.second = mObjectIndex[ItemActivity][pObj];
              mDataIndex[i][j] = DataIndex;
            }
        }
    }

  // We need to set the curve data here!
  size_t k = 0;
  std::vector< C2DPlotCurve * >::iterator itCurves = mCurves.begin();
  std::vector< C2DPlotCurve * >::iterator endCurves = mCurves.end();

  for (; itCurves != endCurves; ++itCurves, ++k)
    {
      std::vector< CVector< double > * > & data = mData[(*itCurves)->getActivity()];

      switch ((*itCurves)->getType())
        {
          case CPlotItem::curve2d:
            (*itCurves)->setData(C2DCurveData(*data[mDataIndex[k][0].second],
                                              *data[mDataIndex[k][1].second],
                                              0));
            break;

#ifdef COPASI_BANDED_GRAPH
          case CPlotItem::bandedGraph:
            (*itCurves)->setData(CBandedGraphData(*data[mDataIndex[k][0].second],
                                                  *data[mDataIndex[k][1].second],
                                                  *data[mDataIndex[k][2].second],
                                                  0));
            break;
#endif // COPASI_BANDED_GRAPH

          case CPlotItem::histoItem1d:
            (*itCurves)->setData(CHistoCurveData(*data[mDataIndex[k][0].second],
                                                 0,
                                                 mCurves[k]->getIncrement()));

            break;

          default:
            fatalError();
            break;
        }
    }

  mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime();
  mReplotFinished = true;

  return true;
}

void CopasiPlot::output(const Activity & activity)
{
  size_t i, imax;
  C_INT32 ItemActivity;

  if (mHaveBefore && (activity == COutputInterface::BEFORE)) mDataBefore++;
  else if (mHaveDuring && (activity == COutputInterface::DURING)) mDataDuring++;
  else if (mHaveAfter && (activity == COutputInterface::AFTER)) mDataAfter++;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if (ItemActivity & activity && mData[ItemActivity].size())
      {
        std::vector< CVector< double > * > & data = mData[ItemActivity];
        size_t & ndata = mDataSize[ItemActivity];

        if ((imax = data.size()) != 0)
          {
            if (ndata >= data[0]->size())
              {
                resizeCurveData(ItemActivity);
              }

            //the data that needs to be stored internally:
            for (i = 0; i < imax; ++i)
              if (mObjectInteger[ItemActivity][i])
                (*data[i])[ndata] = *(C_INT32 *)mObjectValues[ItemActivity][i];
              else
                (*data[i])[ndata] = *mObjectValues[ItemActivity][i];

            ++ndata;
          }
      }

  updatePlot();
}

void CopasiPlot::separate(const Activity & activity)
{
  size_t i, imax;
  C_INT32 ItemActivity;

  if (mHaveBefore && (activity == COutputInterface::BEFORE)) mDataBefore++;

  if (mHaveDuring && (activity == COutputInterface::DURING)) mDataDuring++;

  if (mHaveAfter && (activity == COutputInterface::AFTER)) mDataAfter++;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if (ItemActivity & activity && mData[ItemActivity].size())
      {
        std::vector< CVector< double > * > & data = mData[ItemActivity];
        size_t & ndata = mDataSize[ItemActivity];

        if ((imax = data.size()) != 0)
          {
            if (ndata >= data[0]->size())
              {
                resizeCurveData(ItemActivity);
              }

            //the data that needs to be stored internally:
            for (i = 0; i < imax; ++i)
              (*data[i])[ndata] = MissingValue;

            ++ndata;
          }
      }

  updatePlot();

  return;
}

void CopasiPlot::finish()
{
  // We need to force a replot, i.e., the next mNextPlotTime should be in the past.
  mNextPlotTime = 0;
  replot();

  if (mpZoomer)
    {
      mpZoomer->setEnabled(true);
      mpZoomer->setZoomBase();
    }
}

void CopasiPlot::updateCurves(const size_t & activity)
{
  if (activity == C_INVALID_INDEX)
    {
      C_INT32 ItemActivity;

      for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
        updateCurves(ItemActivity);

      return;
    }

  size_t k = 0;
  std::vector< C2DPlotCurve * >::iterator itCurves = mCurves.begin();
  std::vector< C2DPlotCurve * >::iterator endCurves = mCurves.end();

  for (; itCurves != endCurves; ++itCurves, ++k)
    if ((size_t)(*itCurves)->getActivity() == activity)
      {
        (*itCurves)->setDataSize(mDataSize[activity]);
      }
}

void CopasiPlot::resizeCurveData(const size_t & activity)
{
  QMutexLocker Locker(&mMutex);

  std::vector< CVector< double > * > & data = mData[activity];
  std::vector< CVector< double > * >::iterator it = data.begin();
  std::vector< CVector< double > * >::iterator end = data.end();

  size_t newSize = 2 * (*it)->size();

  for (; it != end; ++it)
    (*it)->resize(newSize, true);

  // Tell the curves that the location of the data has changed
  // otherwise repaint events could crash
  size_t k = 0;
  std::vector< C2DPlotCurve * >::iterator itCurves = mCurves.begin();
  std::vector< C2DPlotCurve * >::iterator endCurves = mCurves.end();

  for (; itCurves != endCurves; ++itCurves, ++k)
    {
      if ((size_t)(*itCurves)->getActivity() == activity)
        {
          std::vector< CVector< double > * > & data = mData[activity];

          switch ((*itCurves)->getType())
            {
              case CPlotItem::curve2d:
                (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                                             data[mDataIndex[k][1].second]);
                break;

#ifdef COPASI_BANDED_GRAPH
              case CPlotItem::bandedGraph:
                (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                                             data[mDataIndex[k][1].second],
                                             data[mDataIndex[k][2].second]);
                break;
#endif // COPASI_BANDED_GRAPH

              case CPlotItem::histoItem1d:
                (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                                             NULL);
                break;

              default:
                fatalError();
                break;
            }
        }
    }
}

void CopasiPlot::updatePlot()
{
  if (mReplotFinished)
    {
      mReplotFinished = false;
      emit replotSignal();
    }
}

//-----------------------------------------------------------------------------

/*void CopasiPlot::enableZoom(bool enabled)
{
  zoomOn = enabled;
}*/

//-----------------------------------------------------------------------------

CopasiPlot::~CopasiPlot()
{
  clearBuffers();
}

bool CopasiPlot::saveData(const std::string & filename)
{
  // No objects.
  if (!mObjects.size()) return true;

  // Find out whether we have any data.
  C_INT32 ItemActivity;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if (mDataSize[ItemActivity] != 0) break;

  // No data
  if (ItemActivity == ActivitySize) return true;

  std::ofstream fs(CLocaleString::fromUtf8(filename).c_str());

  if (!fs.good()) return false;

  // Write the table header
  fs << "# ";

  std::vector< std::vector < const CCopasiObject * > >::const_iterator itX;
  std::vector< std::vector < const CCopasiObject * > >::const_iterator endX =
    mSaveCurveObjects.end();

  std::vector < const CCopasiObject * >::const_iterator it;
  std::vector < const CCopasiObject * >::const_iterator end;

  for (itX = mSaveCurveObjects.begin(); itX != endX; ++itX)
    for (it = itX->begin(), end = itX->end(); it != end; ++it)
      if (*it != NULL)
        fs << (*it)->getObjectDisplayName() << "\t";
      else
        fs << "Not found\t";

  fs << "\n";

  size_t i, imax = mObjects.size();
  std::vector< CVector< double > * > Data;
  Data.resize(imax);

  std::vector< CVector< double > * >::const_iterator itData;
  std::vector< CVector< double > * >::const_iterator endData = Data.end();

  std::vector< size_t > Offset;
  std::vector< size_t >::const_iterator itOffset;

  Offset.resize(imax);

  std::map< Activity, std::map< const CCopasiObject *, size_t > >::iterator itActivity;
  std::map< const CCopasiObject *, size_t >::iterator itObject;

  if (mDataBefore)
    {
      for (itX = mSaveCurveObjects.begin(), i = 0; itX != endX; ++itX)
        for (it = itX->begin(), end = itX->end(); it != end; ++it, ++i)
          {
            if ((itActivity = mObjectIndex.find(COutputInterface::BEFORE)) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::AFTER][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                continue;
              }

            Data[i] = NULL;
          }

      for (i = 0; i < mDataBefore; i++)
        {
          for (itData = Data.begin(); itData != endData; ++itData)
            {
              if (*itData) fs << (**itData)[i];
              else fs << MissingValue;

              fs << "\t";
            }

          fs << std::endl;
        }
    }

  if (mDataDuring)
    {
      for (itX = mSaveCurveObjects.begin(), i = 0; itX != endX; ++itX)
        for (it = itX->begin(), end = itX->end(); it != end; ++it, ++i)
          {
            if ((itActivity = mObjectIndex.find(COutputInterface::DURING)) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING][itObject->second];
                Offset[i] = mDataBefore;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataBefore;
                continue;
              }

            Data[i] = NULL;
          }

      for (i = 0; i < mDataDuring; i++)
        {
          for (itData = Data.begin(), itOffset = Offset.begin(); itData != endData; ++itData)
            {
              if (*itData) fs << (**itData)[i + *itOffset];
              else fs << MissingValue;

              fs << "\t";
            }

          fs << std::endl;
        }
    }

  if (mDataAfter)
    {
      for (itX = mSaveCurveObjects.begin(), i = 0; itX != endX; ++itX)
        for (it = itX->begin(), end = itX->end(); it != end; ++it, ++i)
          {
            if ((itActivity = mObjectIndex.find(COutputInterface::AFTER)) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::AFTER][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataBefore;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataDuring;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataBefore + mDataDuring;
                continue;
              }

            Data[i] = NULL;
          }

      for (i = 0; i < mDataAfter; i++)
        {
          for (itData = Data.begin(), itOffset = Offset.begin(); itData != endData; ++itData)
            {
              if (*itData) fs << (**itData)[i + *itOffset];
              else fs << MissingValue;

              fs << "\t";
            }

          fs << std::endl;
        }
    }

  bool FirstHistogram = true;
  size_t HistogramIndex = 0;

  std::vector< C2DPlotCurve * >::iterator itCurves = mCurves.begin();
  std::vector< C2DPlotCurve * >::iterator endCurves = mCurves.end();

  for (; itCurves != endCurves; ++itCurves)
    {
      if ((*itCurves)->getType() == CPlotItem::histoItem1d)
        {
          if (FirstHistogram)
            {
              fs << "\n# The histograms: \n";
              FirstHistogram = false;
            }

          if (mSaveHistogramObjects[HistogramIndex] != NULL)
            fs << mSaveHistogramObjects[HistogramIndex]->getObjectDisplayName();
          else
            fs << "Not found";

          fs << std::endl;

          CHistoCurveData * pData = static_cast< CHistoCurveData * >(&(*itCurves)->data());
          size_t i, imax = pData->size();

          for (i = 0; i < imax; ++i)
            {
              fs << pData->x(i) << "\t" << pData->y(i) << "\n";
            }
        }
    }

  fs.close();

  if (!fs.good()) return false;

  return true;
}

void CopasiPlot::showCurve(QwtPlotItem *item, bool on)
{
  item->setVisible(on);
  item->setItemAttribute(QwtPlotItem::AutoScale, on);
  QWidget *w = legend()->find(item);

  if (w && w->inherits("QwtLegendItem"))
    static_cast< QwtLegendItem * >(w)->setChecked(on);

  if (!mIgnoreUpdate)
    replot();
}

void CopasiPlot::setCurvesVisibility(const bool & visibility)
{
  std::map< std::string, C2DPlotCurve * >::iterator it = mCurveMap.begin();
  std::map< std::string, C2DPlotCurve * >::iterator end = mCurveMap.end();

  for (; it != end; ++it)
    {
      it->second->setVisible(visibility);
      it->second->setItemAttribute(QwtPlotItem::AutoScale, visibility);
      QWidget *w = legend()->find(it->second);

      if (w && w->inherits("QwtLegendItem"))
        static_cast< QwtLegendItem * >(w)->setChecked(visibility);
    }

  if (!mIgnoreUpdate)
    replot();
}

void CopasiPlot::clearBuffers()
{
  mObjects.clear();

  size_t Activity;
  size_t i, imax;

  for (Activity = 0; Activity < ActivitySize; Activity++)
    {
      std::vector< CVector< double > * > & data = mData[Activity];

      // Delete each QMemArray
      for (i = 0, imax = data.size(); i < imax; i++)
        if (data[i] != NULL) delete data[i];

      data.clear();

      mObjectValues[Activity].clear();
      mObjectInteger[Activity].clear();
      mDataSize[Activity] = 0;
    }

  mDataIndex.clear();
  mObjectIndex.clear();

  mSaveCurveObjects.clear();
  mSaveHistogramObjects.clear();

  mDataBefore = 0;
  mDataDuring = 0;
  mDataAfter = 0;

  mHaveBefore = false;
  mHaveDuring = false;
  mHaveAfter = false;
}

void CopasiPlot::setAxisUnits(const C_INT32 & index,
                              const CCopasiObject * pObject)
{
  if (pObject == NULL) return;

  std::string Units = pObject->getUnits();

  if (Units != "")
    setAxisTitle(index, FROM_UTF8(Units));

  return;
}

// virtual
void CopasiPlot::replot()
{
  if (mNextPlotTime < CCopasiTimeVariable::getCurrentWallTime())
    {
      CCopasiTimeVariable Delta = CCopasiTimeVariable::getCurrentWallTime();

      {
        QMutexLocker Locker(&mMutex);
        updateCurves(C_INVALID_INDEX);
      }

      QwtPlot::replot();

      Delta = CCopasiTimeVariable::getCurrentWallTime() - Delta;
      mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime() + 3 * Delta.getMicroSeconds();
    }

  mReplotFinished = true;
}
