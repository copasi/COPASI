/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/plotwindow.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/04 21:05:10 $
   End CVS Header */

#include <fstream>
#include <string>
#include <vector>
#include <qmainwindow.h>
#include <qtoolbutton.h> 
//#include <qtimer.h>
#include "copasi.h"
class PlotTaskSpec;
class CopasiPlot;
class CPlotSpec;

class PlotWindow : public QMainWindow
  {
    Q_OBJECT

  private:
    // a timer that controls automatic updates of the plot
    //QTimer* timer;

    // points to the specification of the plot inside this window - temporary perhaps
    //PlotTaskSpec* ptspec;

    //CPlotSpec* pSpec;

    // points to the plot instance inside this window
    CopasiPlot *plot;

  public:
    PlotWindow(const CPlotSpec* ptrSpec);

    bool initFromSpec(const CPlotSpec* ptrSpec);

    QToolButton * zoomButton;

    ~PlotWindow();

    // reloads the plot inside the window, updating it as necessary
    //void reloadPlot(CPlotSpec* plotspec, std::vector<int> deletedCurveKeys);

    void takeData(const std::vector<C_FLOAT64> & data);
    void updatePlot();

  private slots:
    //void append();

    // let the plot updates itself at regular intervals - the length of the interval is fixed for now
    void autoUpdate(bool toggled);

    void enableZoom();

    void mouseReleased(const QMouseEvent &e);

    // prints the plot (to printer or file)
    void printPlot();
  };
