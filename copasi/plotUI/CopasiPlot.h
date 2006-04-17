/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/CopasiPlot.h,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/17 01:36:10 $
   End CVS Header */

// the plot object for copasi

#ifndef COPASIPLOT_H
#define COPASIPLOT_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <qmemarray.h>

#include <qpainter.h>
#include <qwt_plot.h>
#include <qwt_painter.h>
#include <qwt_data.h>
#include <qwt_plot_curve.h>

#include "CHistogram.h"
#include "CPlotItem.h"

#include "report/CCopasiObject.h"
#include "utilities/COutputHandler.h"

class CCopasiObjectName;

//nan in data splits curve
class MyQwtPlotCurve : public QwtPlotCurve
  {
  public:
    MyQwtPlotCurve (const QString &title = QString::null)
        : QwtPlotCurve(title)
    {}

  protected:
    void myDrawLines(QPainter *painter,
                     const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                     int from, int to) const;

    //Reroute curve plotting to our own routine
    virtual void drawCurve(QPainter *painter, int style,
                           const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                           int from, int to) const;
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
     * @param std::vector< CCopasiContainer * > listOfContainer (default: empty list)
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer =
                           std::vector< CCopasiContainer * >());

    /**
     * Perform an output event for the current activity
     * @param const Activity & activity
     */
    virtual void output(const Activity & activity);

    /**
     * Introduce an additional seperator into the ouput
     * @param const Activity & activity
     */
    virtual void separate(const Activity & activity);

    /**
     * Finsh the output
     */
    virtual void finish();

    /**
     * Save tab delimeted data to file
     * @param const std::string & filename
     * @return bool success
     */
    bool saveData(const std::string & filename);

  private:
    /**
     * Tell the curves where the data is located. It must be called 
     * after reallocating the memory for the curve data.
     */
    void updateCurves(const unsigned C_INT32 & activity, const bool & doHisto);

    /**
     * Clear all allocate buffers and set reset values
     */
    void clearBuffers();

  private slots:
    /**
     * Slot used to turn curves on and of through the legend buttons.
     * @param QwtPlotItem *item
     * @param bool on
     */
    void showCurve(QwtPlotItem *item, bool on);

  private:
    /**
     * Vector that contains pointers to vectors of data in the selected columns.
     */
    std::vector< std::vector< QMemArray< double > * > > mData;

    /**
     * Vector of pointers to the current object values
     */
    std::vector< std::vector< const C_FLOAT64 * > > mObjectValues;

    /**
     * Vector of actual data lines in the local buffers
     */
    std::vector< unsigned C_INT32 > mDataSize;

    /**
     * Map curve and channel to index pair indicating where the data is stored.
     */
    std::vector< std::vector< std::pair < Activity, unsigned C_INT32 > > > mDataIndex;

    /**
     * Map activity and object to index indicating where data is stored within
     * the current activity.
     */
    std::map< Activity, std::map< CCopasiObject *, unsigned C_INT32 > > mObjectIndex;

    /**
     * The list of curves
     */
    std::vector<QwtPlotCurve*> mCurves;

    /**
     * Vector of type of each item (curve)
     */
    std::vector<CPlotItem::Type> mCurveTypes;

    /**
     * Vector of the activity of each item (curve)
     */
    std::vector<Activity> mCurveActivities;

    /**
     * List of the histograms (if there are some)
     */
    std::vector<CHistogram> mHistograms;

    /**
     * Map of curve to the index to the corresponding histogram.
     */
    std::vector<C_INT32> mHistoIndices;

    /**
     * Count af data lines recorded during activity BEFORE.
     */
    unsigned C_INT32 mDataBefore;

    /**
     * Count af data lines recorded during activity DURING.
     */
    unsigned C_INT32 mDataDuring;

    /**
     * Count af data lines recorded during activity AFTER.
     */
    unsigned C_INT32 mDataAfter;

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

  public:
    /**
     * Pointer to the zooming engine for the plot.
     */
    QwtPlotZoomer * mpZoomer;
  };

#endif // COPASIPLOT_H
