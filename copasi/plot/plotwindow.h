/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/plotwindow.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/06 20:03:20 $
   End CVS Header */

#include <fstream>
#include <string>
#include <vector>
#include <qmainwindow.h>
#include <qtoolbutton.h>
#include "copasi.h"

class CopasiPlot;
class CPlotSpec;

class PlotWindow : public QMainWindow
  {
    Q_OBJECT

  private:

    // points to the plot instance inside this window
    CopasiPlot *plot;

  public:
    PlotWindow(const CPlotSpec* ptrSpec);

    bool initFromSpec(const CPlotSpec* ptrSpec);

    QToolButton * zoomButton;

    ~PlotWindow();

    void takeData(const std::vector<C_FLOAT64> & data);
    void updatePlot();

  private slots:
    void enableZoom();

    void mouseReleased(const QMouseEvent &e);

    // prints the plot (to printer or file)
    void printPlot();
  };
