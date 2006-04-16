/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CopasiPlot.h,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/16 21:05:31 $
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
  public:
    CopasiPlot(const CPlotSpecification* plotspec, QWidget* parent = 0);

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

    bool saveData(const std::string & filename);

  private:
    QwtPlotZoomer* getZoomer()
    {return mZoomer;}

    // tell the curves where the data is located. Is used before redraw
    // and after reallocating the memory for the curve data
    void updateCurves(const unsigned C_INT32 & activity, const bool & doHisto);

    void clearBuffers();

  private slots:
    void showCurve(QwtPlotItem *item, bool on);

  private:
    // a vector that contains pointers to vectors of data in the selected columns
    std::vector< std::vector< QMemArray< double > * > > mData;

    // holds pointer to the current object values
    std::vector< std::vector< const C_FLOAT64 * > > mObjectValues;

    // number of actual data lines in the local buffer
    std::vector< unsigned C_INT32 > mDataSize;

    // for each curve and each channel tells where the data is stored
    std::vector< std::vector< std::pair < Activity, unsigned C_INT32 > > > mDataIndex;

    // for each activity and object tells where the data is stored
    std::map< Activity, std::map< CCopasiObject *, unsigned C_INT32 > > mObjectIndex;

    // stores the curves
    std::vector<QwtPlotCurve*> mCurves;

    //stores the type of each item (curve)
    std::vector<CPlotItem::Type> mCurveTypes;

    //stores the activity of each item (curve)
    std::vector<Activity> mCurveActivities;

    //the histograms (if there are some)
    std::vector<CHistogram> mHistograms;

    //points from the item index to the histogram index
    std::vector<C_INT32> mHistoIndices;

    unsigned C_INT32 mDataBefore;
    unsigned C_INT32 mDataDuring;
    unsigned C_INT32 mDataAfter;

    bool mHaveBefore;
    bool mHaveDuring;
    bool mHaveAfter;

    const CPlotSpecification * mpPlotSpecification;

  public:
    QwtPlotZoomer * mZoomer;
  };

#endif // COPASIPLOT_H
