/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/plotwindow.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:00 $
   End CVS Header */

#include <fstream>
#include <string>
#include <vector>
#include <qmainwindow.h>
#include <qtoolbutton.h>
#include "copasi.h"

class CopasiPlot;
class CPlotSpecification;
class CPlotSpec2Vector;

class PlotWindow : public QMainWindow
  {
    Q_OBJECT

  private:

    // points to the plot instance inside this window
    CopasiPlot *plot;

  public:
    PlotWindow(CPlotSpec2Vector* psv, const CPlotSpecification* ptrSpec);

    bool initFromSpec(CPlotSpec2Vector* psv, const CPlotSpecification* ptrSpec);

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
