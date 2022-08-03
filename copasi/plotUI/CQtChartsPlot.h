// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// the plot object for COPASI

#ifndef CHARTSPLOT_H
#define CHARTSPLOT_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <QPainter>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>

#include <QRectF>

#include <copasi/config.h>

#ifdef COPASI_USE_QTCHARTS

#  include <QtCharts/QChartView>
#  include <QtCharts/QChart>
#  include <QtCharts/QAbstractSeries>
#  include <QtCharts/QAbstractAxis>
#  include <QtCharts/QScatterSeries>

#  include "copasi/plot/CPlotItem.h"

#  include "copasi/core/CDataObject.h"
#  include "copasi/output/COutputHandler.h"
#  include "copasi/plotUI/CPlotInterface.h"
#  include "copasi/utilities/CopasiTime.h"
#  include "copasi/core/CVector.h"
#  include "copasi/core/CMatrix.h"

//*******************************************************

class CPlotSpec2Vector;
class CPlotSpecification;
class CPlotSpectogram;

class CQtChartsPlot
  : public QT_CHARTS_NAMESPACE::QChartView
  , public CPlotInterface
{
  Q_OBJECT
private:
  /**
   * Default constructor which may never be called.
   * @param QWidget* parent (default: NULL)
   */
  CQtChartsPlot(QWidget * parent = NULL);

public:
  /**
   * Specific constructor
   * @param const CPlotSpecification* plotspec
   * @param QWidget* parent (default: NULL)
   */
  CQtChartsPlot(const CPlotSpecification * plotspec, QWidget * parent = NULL);

  /**
   * Initialize the the plot from the specification
   * @param const CPlotSpecification* plotspec
   */
  virtual bool initFromSpec(const CPlotSpecification * plotspec);

  void setSymbol(QT_CHARTS_NAMESPACE::QAbstractSeries * pCurve, CPlotItem::SymbolType symbol, QColor color, int symbolSize, float penWidth);

  virtual QString titleText() const;

  virtual void update();

  /**
   * @return the current plot specification
   */
  virtual const CPlotSpecification * getPlotSpecification() const;

  /**
   * Destructor
   */
  virtual ~CQtChartsPlot();

  /**
   * compile the object list from name vector
   * @param CObjectInterface::ContainerList listOfContainer
   * @param  const CDataModel* pDataModel
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
  virtual bool saveData(const std::string & filename);

  /**
   * Shows or hide all curves depending on whether visibility is false or true
   * @param const bool & visibility
   */
  virtual void setCurvesVisibility(const bool & visibility);

  static QPointF getRange(const QT_CHARTS_NAMESPACE::QAbstractAxis * axis);

public slots:
  virtual void replot();
  void connectMarkers();
  void disconnectMarkers();

  void handleMarkerClicked();

  virtual void toggleLogX(bool logX);
  virtual void toggleLogY(bool logY);
  virtual void render(QPainter *, QRect);
  virtual void resetZoom();

protected:
  bool viewportEvent(QEvent * event);
  void mousePressEvent(QMouseEvent * event);
  void mouseMoveEvent(QMouseEvent * event);
  void mouseReleaseEvent(QMouseEvent * event);
  void keyPressEvent(QKeyEvent * event);

private:
  bool m_isTouching;

private:
  /**
   * @return a spectogram for the given plot item.
   */
  CPlotSpectogram * createSpectogram(const CPlotItem * plotItem);

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
  void setAxisUnits(Axis axis,
                    const CObjectInterface * pObject);

private slots:
  /**
   * Slot used to turn curves on and of through the legend buttons.
   * @param QwtPlotItem *item
   * @param bool on
   */
  void showCurve(QT_CHARTS_NAMESPACE::QAbstractSeries * item, bool on);

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
  std::vector< std::vector< std::string > > mSaveCurveObjects;
  std::map< std::string, std::string > mCnNameMap;

  /**
   * The order of histogram objects used when the data is saved.
   */
  std::vector< std::string > mSaveHistogramObjects;

  /**
   * Vector of actual data lines in the local buffers
   */
  std::vector< size_t > mDataSize;

  /**
   * Map curve and channel to index pair indicating where the data is stored.
   */
  std::vector< std::vector< std::pair< Activity, size_t > > > mDataIndex;

  /**
   * Map activity and object to index indicating where data is stored within
   * the current activity.
   */
  std::map< Activity, std::map< std::string, size_t > > mObjectIndex;

  /**
   * The list of curves
   */
  std::vector< QT_CHARTS_NAMESPACE::QAbstractSeries * > mCurves;

  /**
   * A map between a specification identified by its key and a curve
   */
  std::map< std::string, QT_CHARTS_NAMESPACE::QAbstractSeries * > mCurveMap;

  /**
   * The list of spectograms
   */
  CVector< CPlotSpectogram * > mSpectograms;

  /**
   * A map between a specification identified by its key and a curve
   */
  std::map< std::string, CPlotSpectogram * > mSpectogramMap;

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

protected:
  bool mReplotFinished;

signals:
  void replotSignal();
};

QT_BEGIN_NAMESPACE
class QGestureEvent;
QT_END_NAMESPACE

class CopasiChart : public QT_CHARTS_NAMESPACE::QChart
{
public:
  explicit CopasiChart(QGraphicsItem * parent = nullptr, Qt::WindowFlags wFlags = {});
  ~CopasiChart();

protected:
  bool sceneEvent(QEvent * event);

private:
  bool gestureEvent(QGestureEvent * event);

private:
};

#endif // COPASI_USE_QTCHARTS
#endif // CHARTSPLOT_H
