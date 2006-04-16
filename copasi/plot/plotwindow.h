/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/plotwindow.h,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/16 17:51:38 $
   End CVS Header */

#include <fstream>
#include <string>
#include <vector>
#include <qmainwindow.h>
#include <qtoolbutton.h>

#include "copasi.h"
#include "CopasiUI/CopasiFileDialog.h"
#include "utilities/COutputHandler.h"

class CopasiPlot;
class CPlotSpecification;
class CPlotSpec2Vector;
class CCopasiContainer;

class PlotWindow : public QMainWindow, public COutputInterface
  {
    Q_OBJECT

  private:

    // points to the plot instance inside this window
    CopasiPlot *mpPlot;
    COutputHandler *mpHandler;

  public:
    PlotWindow(COutputHandler * pHandler, const CPlotSpecification* ptrSpec);

    bool initFromSpec(const CPlotSpecification* ptrSpec);

    //QToolButton * zoomButton;
    QToolButton * printButton;
    QToolButton * saveButton;

    ~PlotWindow();

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

  private slots:
    //void enableZoom();

    //void mouseReleased(const QMouseEvent &e);

    // prints the plot (to printer or file)
    void printPlot();

    void slotSaveData();
  };
