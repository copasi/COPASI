/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/plotwindow.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/05 16:03:51 $
   End CVS Header */

#include <fstream>
#include <string>
#include <vector>
#include <qmainwindow.h>
#include <qtoolbutton.h>

#include "copasi.h"
#include "CopasiUI/CopasiFileDialog.h"

class CopasiPlot;
class CPlotSpecification;
class CPlotSpec2Vector;
class CCopasiContainer;

class PlotWindow : public QMainWindow
  {
    Q_OBJECT

  private:

    // points to the plot instance inside this window
    CopasiPlot *mpPlot;

  public:
    PlotWindow(CPlotSpec2Vector* psv, const CPlotSpecification* ptrSpec);

    bool initFromSpec(const CPlotSpecification* ptrSpec);

    //QToolButton * zoomButton;
    QToolButton * printButton;
    QToolButton * saveButton;

    ~PlotWindow();

    /**
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer
     * (default: CCopasiContainer::EmptyList)
     * @return bool success
     */
    bool compile(std::vector< CCopasiContainer * > listOfContainer =
                   std::vector< CCopasiContainer * >());

    void takeData();
    void updatePlot();
    void doSeparator();
    void initPlot();
    void finishPlot();

  private slots:
    //void enableZoom();

    //void mouseReleased(const QMouseEvent &e);

    // prints the plot (to printer or file)
    void printPlot();

    void slotSaveData();
  };
