/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/plotwindow.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/03/16 14:51:29 $
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
    CopasiPlot *mpPlot;

  public:
    PlotWindow(CPlotSpec2Vector* psv, const CPlotSpecification* ptrSpec);

    bool initFromSpec(CPlotSpec2Vector* psv, const CPlotSpecification* ptrSpec);

    QToolButton * zoomButton;
    QToolButton * printButton;
    QToolButton * saveButton;

    ~PlotWindow();

    void takeData(const std::vector<C_FLOAT64> & data);
    void updatePlot();

  private slots:
    void enableZoom();

    void mouseReleased(const QMouseEvent &e);

    // prints the plot (to printer or file)
    void printPlot();

    void slotSaveData();
  };
