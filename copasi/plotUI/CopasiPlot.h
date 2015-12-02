// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// the plot object for COPASI

#ifndef COPASIPLOT_H
#define COPASIPLOT_H

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

// NaN are ignored bounding rectangle
class C2DCurveData :
#if QWT_VERSION > 0x060000
  public QwtSeriesData<QPointF>
#else
  public QwtData
#endif
{
public:
  C2DCurveData();
  C2DCurveData(const CVector< double > & x, const CVector< double > & y, size_t size);
  virtual ~C2DCurveData();

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

  void reallocated(const CVector< double > * pX, const CVector< double > * pY);

protected:
  C2DCurveData &operator = (const C2DCurveData & rhs);

private:
  const double * mpX;
  const double * mpY;
  size_t mSize;
  size_t mMaxSize;

  mutable size_t mLastRectangle;
  mutable double mMinX;
  mutable double mMaxX;
  mutable double mMinY;
  mutable double mMaxY;
};

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



class CSpectorgramData :
#if QWT_VERSION > 0x060000
  public QwtSeriesData<QPointF>
#else
  public QwtRasterData
#endif

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

#if QWT_VERSION > 0x060000
  virtual QwtSeriesData<QPointF> *copy() const;
  virtual QPointF sample(size_t i) const;
#else
  virtual QwtRasterData *copy() const;
#endif

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
  std::vector<double>::const_iterator mEndX;
  std::vector<double>::const_iterator mEndY;

  CMatrix<double>* mpMatrix;

  bool mLogZ;
  double mLimitZ;
  bool mBilinear;

};

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


class CPlotSpectogram : public QwtPlotSpectrogram
{
public:
  CPlotSpectogram(QMutex * pMutex,
                  const CPlotItem::Type & type,
                  const COutputInterface::Activity & activity,
                  const QString & title,
                  bool logZ = false,
                  double limitZ = std::numeric_limits<double>::quiet_NaN(),
                  bool bilinear = true);

  void setDataSize(const size_t & size);

  void reallocatedData(const CVector< double > * pX,
                       const CVector< double > * pY,
                       const CVector< double > * pZ);

  const CPlotItem::Type & getType() const;

  const COutputInterface::Activity & getActivity() const;

  bool getLogZ() const;
  void setLogZ(bool logZ);

  double getLimitZ() const;
  void setLimitZ(double limitZ);

  bool getBilinear() const;
  void setBilinear(bool bilinear);

protected:


private:
  QMutex * mpMutex;

  CPlotItem::Type mType;

  COutputInterface::Activity mActivity;

  bool mLogZ;
  double mLimitZ;
  bool mBilinear;
};

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

#if QWT_VERSION > 0x060000

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

//*******************************************************

class CPlotSpec2Vector;
class CPlotSpecification;
class QwtPlotZoomer;

class CopasiPlot : public QwtPlot, public COutputInterface
{
  Q_OBJECT
private:
  /**
   * Default constructor which may never be called.
   * @param QWidget* parent (default: NULL)
   */
  CopasiPlot(QWidget* parent = NULL);

public:
  /**
   * Specific constructor
   * @param const CPlotSpecification* plotspec
   * @param QWidget* parent (default: NULL)
   */
  CopasiPlot(const CPlotSpecification* plotspec, QWidget* parent = NULL);

  /**
   * Initialize the the plot from the specification
   * @param const CPlotSpecification* plotspec
   */
  bool initFromSpec(const CPlotSpecification* plotspec);

  /**
   * Destructor
   */
  virtual ~CopasiPlot();

  /**
   * compile the object list from name vector
   * @param CObjectInterface::ContainerList listOfContainer
   * @param  const CCopasiDataModel* pDataModel
   * @return bool success
   */
  virtual bool compile(CObjectInterface::ContainerList listOfContainer);

  /**
   * Perform an output event for the current activity
   * @param const Activity & activity
   */
  virtual void output(const Activity & activity);

  /**
   * Introduce an additional separator into the output
   * @param const Activity & activity
   */
  virtual void separate(const Activity & activity);

  /**
   * Finish the output
   */
  virtual void finish();

  /**
   * Save tab delimited data to file
   * @param const std::string & filename
   * @return bool success
   */
  bool saveData(const std::string & filename);

  /**
   * Shows or hide all curves depending on whether visibility is false or true
   * @param const bool & visibility
   */
  void setCurvesVisibility(const bool & visibility);

public slots:
  virtual void replot();
#if QWT_VERSION > 0x060000
  virtual void legendChecked(const QVariant &, bool on);
#endif

private:

  /**
   * @return a spectogram for the given plot item.
   */
  CPlotSpectogram* createSpectogram(CPlotItem *plotItem);

  /**
   * Tell the curves where the data is located. It must be called
   * after reallocating the memory for the curve data.
   */
  void updateCurves(const size_t & activity);

  /**
   * Resize the curve data
   */
  void resizeCurveData(const size_t & activity);

  /**
   * Redraw the plot
   */
  void updatePlot();

  /**
   * Clear all allocate buffers and set reset values
   */
  void clearBuffers();

  /**
   * Set the units of the indexed axis based on the
   * type of the object.
   * @param const C_INT32 & index
   * @param const CObjectInterface * pObject
   */
  void setAxisUnits(const C_INT32 & index,
                    const CObjectInterface * pObject);

private slots:
  /**
   * Slot used to turn curves on and of through the legend buttons.
   * @param QwtPlotItem *item
   * @param bool on
   */
  void showCurve(QwtPlotItem *item, bool on);

private:
  /**
   * The value for missing objects
   */
  static C_FLOAT64 MissingValue;

  /**
   * Mutex preventing access to data during reallocation.
   */
  QMutex mMutex;

  /**
   * Vector that contains pointers to vectors of data in the selected columns.
   */
  std::vector< std::vector< CVector< double > * > > mData;

  /**
   * Vector of pointers to the current object values
   */
  std::vector< std::vector< const C_FLOAT64 * > > mObjectValues;

  /**
   * Vector of bool indicating whether the current object value is integer
   */
  std::vector< std::vector< bool > > mObjectInteger;

  /**
   * The order of 2d curve objects used when the data is saved.
   * The first object in each vector is the object for the X axis.
   */
  std::vector< std::vector < const CObjectInterface * > > mSaveCurveObjects;

  /**
   * The order of histogram objects used when the data is saved.
   */
  std::vector< const CObjectInterface * > mSaveHistogramObjects;

  /**
   * Vector of actual data lines in the local buffers
   */
  std::vector< size_t > mDataSize;

  /**
   * Map curve and channel to index pair indicating where the data is stored.
   */
  std::vector< std::vector< std::pair < Activity, size_t > > > mDataIndex;

  /**
   * Map activity and object to index indicating where data is stored within
   * the current activity.
   */
  std::map< Activity, std::map< const CObjectInterface *, size_t > > mObjectIndex;

  /**
   * The list of curves
   */
  CVector< C2DPlotCurve * > mCurves;

  /**
   * A map between a specification identified by its key and a curve
   */
  std::map< std::string, C2DPlotCurve * > mCurveMap;

  /**
   * The list of spectograms
   */
  CVector< CPlotSpectogram * > mSpectograms;

  /**
   * A map between a specification identified by its key and a curve
   */
  std::map< std::string, CPlotSpectogram* > mSpectogramMap;

  /**
   * Vector of the activity of each item (curve)
   */
  // std::vector<Activity> mCurveActivities;

  /**
   * Map of curve to the index to the corresponding histogram.
   */
  //std::vector<size_t> mHistoIndices;

  /**
   * Count of data lines recorded during activity BEFORE.
   */
  size_t mDataBefore;

  /**
   * Count of data lines recorded during activity DURING.
   */
  size_t mDataDuring;

  /**
   * Count of data lines recorded during activity AFTER.
   */
  size_t mDataAfter;

  /**
   * Flag indicating whether there are any curves recording
   * data during activity BEFORE.
   */
  bool mHaveBefore;

  /**
   * Flag indicating whether there are any curves recording
   * data during activity DURING.
   */
  bool mHaveDuring;

  /**
   * Flag indicating whether there are any curves recording
   * data during activity AFTER.
   */
  bool mHaveAfter;

  /**
   * Pointer to the specification for the plot.
   */
  const CPlotSpecification * mpPlotSpecification;

  /**
   * The next time a plot update is performed
   */
  CCopasiTimeVariable mNextPlotTime;

  /**
   * Indicates whether redrawing/updating shall be suppressed during initialization.
   */
  bool mIgnoreUpdate;

public:
  /**
   * Pointer to the zooming engine for the plot.
   */
  QwtPlotZoomer * mpZoomer;

protected:
  bool mReplotFinished;

signals:
  void replotSignal();
};

#endif // COPASIPLOT_H
