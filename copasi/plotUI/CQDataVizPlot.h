// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef DATA_VIZ_PLOT_H
#  define DATA_VIZ_PLOT_H

#include <copasi/config.h>

#  ifdef WITH_QT5_VISUALIZATION


#  ifdef WITH_DATAVISUALIZATION_NAMESPACES
#    define DATAVIS_NS_PREFIX QtDataVisualization::
#  else
#    define DATAVIS_NS_PREFIX
#  endif

#include <QObject>
#  include <QPainter>
#  include <QtCore/QMutex>
#  include <QtCore/QWaitCondition>
#  include <QWidget>
#  include <QMenu>

#  include "copasi/plot/CPlotItem.h"

#  include "copasi/core/CDataObject.h"
#  include "copasi/output/COutputHandler.h"
#  include "copasi/plotUI/CPlotInterface.h"
#  include "copasi/utilities/CopasiTime.h"
#  include "copasi/core/CVector.h"
#  include "copasi/core/CMatrix.h"

# include <QtDataVisualization/QAbstract3DGraph>
# include <QtDataVisualization/QAbstract3DSeries>
# include <QtDataVisualization/QAbstract3DAxis>

//*******************************************************

class CPlotSpec2Vector;
class CPlotSpecification;
class CPlotSpectogram;

class CQDataVizPlot
  : public QWidget
  , public CPlotInterface
{
  Q_OBJECT


private:
  /**
   * Default constructor which may never be called.
   * @param QWidget* parent (default: NULL)
   */
  CQDataVizPlot(QWidget * parent = NULL);

public:

  enum class PlotMode
  {
    Bars,
    Scatter,
    Surface
  };

  /**
   * Specific constructor
   * @param const CPlotSpecification* plotspec
   * @param QWidget* parent (default: NULL)
   */
  CQDataVizPlot(const CPlotSpecification * plotspec, QWidget * parent = NULL, PlotMode mode = PlotMode::Surface);

  /**
   * Initialize the the plot from the specification
   * @param const CPlotSpecification* plotspec
   */
  virtual bool initFromSpec(const CPlotSpecification * plotspec);

  bool createGraph(CQDataVizPlot::PlotMode mode);

  void removeSeries();

  //void setSymbol(QT_CHARTS_NAMESPACE::QAbstractSeries * pCurve, CPlotItem::SymbolType symbol, QColor color, int symbolSize, float penWidth);

  virtual QString titleText() const;

  virtual void update();

  /**
   * @return the current plot specification
   */
  virtual const CPlotSpecification * getPlotSpecification() const;

  /**
   * Destructor
   */
  virtual ~CQDataVizPlot();

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


  virtual void saveToFile(const QString & fileName, QRect & rect);

  /**
   * @return a string with supported file filters to save files
   */
  virtual QString getSaveFilters();


  //static QPointF getRange(const DATAVIS_NS_PREFIX QAbstractAxis * axis);

public slots:
  virtual void replot();

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
  DATAVIS_NS_PREFIX QAbstract3DGraph * mpGraph;
  QWidget * mpWidget;
  DATAVIS_NS_PREFIX QAbstract3DAxis * mpAxisX;
  DATAVIS_NS_PREFIX QAbstract3DAxis * mpAxisY;
  DATAVIS_NS_PREFIX QAbstract3DAxis * mpAxisZ;

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

  void createContextMenu();

private slots:
  /**
   * Slot used to turn curves on and of through the legend buttons.
   * @param QwtPlotItem *item
   * @param bool on
   */
  void showCurve(DATAVIS_NS_PREFIX QAbstract3DSeries * item, bool on);

  void slotShowContextMenu(const QPoint &);

  void changePresetCamera();
  void changeLabelBackground();
  void changeFont(const QFont & font);
  void changeFontSize(int fontsize);
  void rotateX(int rotation);
  void rotateY(int rotation);
  void setBackgroundEnabled(int enabled);
  void setGridEnabled(int enabled);
  void setSmoothBars(int smooth);
  void setReverseValueAxis(int enabled);
  void setReflection(bool enabled);

public slots:
  void changeRange(int range);
  void changeStyle(int style);
  void changeSelectionMode(int selectionMode);
  void changeTheme(int theme);
  void changeShadowQuality(int quality);
  void shadowQualityUpdatedByVisual(DATAVIS_NS_PREFIX QAbstract3DGraph::ShadowQuality shadowQuality);
  void changeLabelRotation(int rotation);
  void setAxisTitleVisibility(bool enabled);
  void setAxisTitleFixed(bool enabled);
  void zoomToSelectedBar();
  void toggleGradient();

  void contextActionTriggered(QAction * action);


signals:
  void shadowQualityChanged(int quality);
  void backgroundEnabledChanged(bool enabled);
  void gridEnabledChanged(bool enabled);
  void fontChanged(QFont font);
  void fontSizeChanged(int size);

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
  std::vector< DATAVIS_NS_PREFIX QAbstract3DSeries * > mCurves;

  /**
   * A map between a specification identified by its key and a curve
   */
  std::map< std::string, DATAVIS_NS_PREFIX QAbstract3DSeries * > mCurveMap;

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
  PlotMode mMode;
  bool mDataReady = false;
  QMenu * mpContextMenu;

signals:
  void replotSignal();
};


# endif // WITH_QT5_VISUALIZATION

#endif //DATA_VIZ_PLOT_H
