/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/CopasiPlot.h,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/05 16:03:51 $
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

#include "copasi.h"
#include "CHistogram.h" 
//#include "plotspec.h"

#include "report/CCopasiObject.h"

class CCopasiContainer;
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

class CopasiPlot : public QwtPlot
  {
    Q_OBJECT
  public:
    CopasiPlot(const CPlotSpecification* plotspec, QWidget* parent = 0);

    bool initFromSpec(const CPlotSpecification* plotspec);

    ~CopasiPlot();

    // decides whether zooming is enabled and sets flags accordingly
    //void enableZoom(bool enabled);

    //public slots:
    // this method reads data to append to existing curves
    //void appendPlot();

    /**
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer
     * (default: CCopasiContainer::EmptyList)
     * @return bool success
     */
    bool compile(std::vector< CCopasiContainer * > listOfContainer =
                   std::vector< CCopasiContainer * >());

    void takeData();
    void doSeparator();

    void initPlot();
    void updatePlot();
    void finishPlot();

    bool saveData(const std::string & filename);

    QwtPlotZoomer* getZoomer()
    {return mZoomer;}

  private:
    // tell the curves where the data is located. Is used before redraw
    // and after reallocating the memory for the curve data
    void updateCurves(bool doHisto);

  private slots:
    void showCurve(QwtPlotItem *item, bool on);

  private:
    // a vector that contains pointers to vectors of data in the selected columns
    std::vector<QMemArray<double>* > data;

    //number of data lines in the local buffer
    unsigned C_INT32 ndata;

    std::vector<const C_FLOAT64 *> mObjectValues;

    std::vector< Refresh * > mObjectRefreshes;

    // holds column indices
    //    std::vector<C_INT32> indexTable;
    unsigned C_INT32 mItemCount;

    // holds the corresponding display names
    std::vector<std::string> mObjectNames;

    // for each channel in each curve tells where the data is stored
    std::vector<std::vector<C_INT32> > dataIndices;

    //stores the type of each item (curve)
    std::vector<C_INT32> mItemTypes;

    // stores the curves
    std::vector<QwtPlotItem*> mQwtItems;

    //the histograms (if there are some)
    std::vector<CHistogram> mHistograms;

    //points from the item index to the histogram index
    std::vector<C_INT32> mHistoIndices;

    // populate indexTable and dataIndices
    void createIndices(const CPlotSpecification* pspec);

    const CPlotSpecification * mpPlotSpecification;

  public:
    QwtPlotZoomer * mZoomer;
  };

#endif // COPASIPLOT_H
