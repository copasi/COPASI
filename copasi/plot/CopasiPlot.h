/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CopasiPlot.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/20 19:57:37 $
   End CVS Header */

// the plot object for copasi

#ifndef COPASIPLOT_H
#define COPASIPLOT_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <qmemarray.h>

#include "copasi.h"
#include "zoomplot.h" 
//#include "plotspec.h"

class CPlotSpec;

class CopasiPlot : public ZoomPlot
  {
    Q_OBJECT
  public:
    CopasiPlot(const CPlotSpec* plotspec, QWidget* parent = 0);

    bool initFromSpec(const CPlotSpec* plotspec);

    ~CopasiPlot();

    // paints only an interval of points that is
    // essential for appending points. Using replot instead
    // is simply to slow for curves with a lot of points.
    void drawCurveInterval(long curveId, int from, int to);

    // decides whether zooming is enabled and sets flags accordingly
    void enableZoom(bool enabled);

    //public slots:
    // this method reads data to append to existing curves
    void appendPlot();

    // adds/removes curves as necessary; otherwise simply display the existing curves
    //void reload2Plot(CPlotSpec* ptspec, std::vector<int> deletedCurveIndices);

    void takeData(const std::vector<C_FLOAT64> & dataVector);
    void updatePlot();

  private slots:
    void mousePressed(const QMouseEvent &e);

    void mouseReleased(const QMouseEvent &e);

    // hides or redisplays the curve with the given key
    //void redrawCurve(long key);
    void toggleCurve(long curveId);

  private:
    //std::istream* sourcefile;

    // a vector that contains pointers to vectors of data in the selected columns
    std::vector<QMemArray<double>* > data;

    //number of data lines in the local buffer
    unsigned C_INT32 ndata;

    // holds column indices
    std::vector<C_INT32> indexTable;

    // for each channel in each curve tells where the data is stored
    std::vector<std::vector<C_INT32> > dataIndices;

    // populate indexTable and dataIndices
    void createIndices(const CPlotSpec* pspec);

    // whether zooming is enabled
    bool zoomOn;

    QPoint cursorPos;
  };

#endif // COPASIPLOT_H
