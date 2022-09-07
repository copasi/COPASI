// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQCUSTOM_PLOT_H
#define CQCUSTOM_PLOT_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <QPainter>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>

#include <QRectF>

#include <copasi/config.h>

#ifdef COPASI_USE_QCUSTOMPLOT

#include <qcustomplot.h>

#include "copasi/plot/CPlotItem.h"

#include "copasi/core/CDataObject.h"
#include "copasi/output/COutputHandler.h"
#include "copasi/plotUI/CPlotInterface.h"
#include "copasi/utilities/CopasiTime.h"
#include "copasi/core/CVector.h"
#include "copasi/core/CMatrix.h"

//*******************************************************

class CHistoHelper;
class CPlotSpec2Vector;
class CPlotSpecification;
class CPlotSpectogram;

class CQCustomPlot
  : public QCustomPlot
  , public CPlotInterface
{
  Q_OBJECT
private:
  /**
   * Default constructor which may never be called.
   * @param QWidget* parent (default: NULL)
   */
  CQCustomPlot(QWidget* parent = NULL);

public:
  /**
   * Specific constructor
   * @param const CPlotSpecification* plotspec
   * @param QWidget* parent (default: NULL)
   */
  CQCustomPlot(const CPlotSpecification* plotspec, QWidget* parent = NULL);

  /**
   * Initialize the the plot from the specification
   * @param const CPlotSpecification* plotspec
   */
  virtual bool initFromSpec(const CPlotSpecification* plotspec);

  void setSymbol(QCPAbstractPlottable * pCurve, QCPScatterStyle::ScatterShape symbol, QColor color, int symbolSize, float penWidth);

  virtual QString titleText() const;

  virtual void update();

  /**
   * @return the current plot specification
   */
  virtual const CPlotSpecification* getPlotSpecification() const;

  /**
   * Destructor
   */
  virtual ~CQCustomPlot();

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

public slots:
  virtual void replot();

  virtual void toggleLogX(bool logX);
  virtual void toggleLogY(bool logY);
  virtual void render(QPainter *, QRect);
  virtual void resetZoom();

protected:
  void toggleLog(QCPAxis * axis, bool useLog);
  void mouseMoveEvent(QMouseEvent * event);
  void mousePressEvent(QMouseEvent * event);
  void mouseReleaseEvent(QMouseEvent * event);
  void wheelEvent(QWheelEvent * event);
  /*bool viewportEvent(QEvent * event);
  void mousePressEvent(QMouseEvent * event);
  void mouseMoveEvent(QMouseEvent * event);
  void mouseReleaseEvent(QMouseEvent * event);
  void keyPressEvent(QKeyEvent * event);*/

private:
  bool m_isTouching = false;

private:

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

  virtual void saveToFile(const QString & fileName, QRect & rect);

private slots:
  /**
   * Slot used to turn curves on and of through the legend buttons.
   * @param QwtPlotItem *item
   * @param bool on
   */
  void showCurve(QCPAbstractPlottable * item, bool on);
  void legendClicked(QCPLegend * legend, QCPAbstractLegendItem * item, QMouseEvent * event);
  void displayToolTip(QCPAbstractPlottable * plottable,
                      int dataIndex,
                      QMouseEvent * event);

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
  std::vector< std::vector < std::string > > mSaveCurveObjects;
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
  std::vector< std::vector< std::pair < Activity, size_t > > > mDataIndex;

  /**
   * Map activity and object to index indicating where data is stored within
   * the current activity.
   */
  std::map< Activity, std::map< std::string, size_t > > mObjectIndex;

  /**
   * The list of curves
   */
  std::vector< QCPAbstractPlottable * > mCurves;

  /**
   * A map between a specification identified by its key and a curve
   */
  std::map< std::string, QCPAbstractPlottable * > mCurveMap;

  std::map< QCPAbstractPlottable *, QCPAbstractPlottable * > mY2Map;

  std::map< QCPAbstractPlottable *, CHistoHelper * > mHisto;

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
  QCPTextElement * mpTitle;
  QSharedPointer< QCPAxisTicker > mLogTicker;
  QSharedPointer< QCPAxisTicker > mDefaultTicker;

signals:
  void replotSignal();
};

#endif // COPASI_USE_QCUSTOMPLOT
#endif // CQCUSTOM_PLOT_H
