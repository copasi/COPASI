// the plot object for copasi

#ifndef COPASIPLOT_H
#define COPASIPLOT_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <qmemarray.h>

#include "zoomplot.h"
#include "plotspec.h"

class CopasiPlot : public ZoomPlot
  {
    Q_OBJECT
  public:
    CopasiPlot(PlotTaskSpec* plotspec, QWidget* parent = 0);

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
    void reloadPlot(PlotTaskSpec* ptspec, std::vector<int> deletedCurveIndices);

  private slots:
    void mousePressed(const QMouseEvent &e);

    void mouseReleased(const QMouseEvent &e);

    // hides or redisplays the curve with the given key
    void redrawCurve(long key);

  private:
    std::istream* sourcefile;

    // a vector that contains pointers to vectors of data in the selected columns
    std::vector<QMemArray<double>* > data;

    // the starting row in the data file to read data from
    int startRow;

    // the current position in the file
    std::streampos pos;

    // the spec of this plot
    PlotTaskSpec* ptspec;

    // whether zooming is enabled
    bool zoomOn;

    QPoint cursorPos;
  };

#endif // COPASIPLOT_H
