/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/plotwindow.h,v $
   $Revision: 1.19 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:30:41 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
class COutputHandlerPlot;

class PlotWindow : public QMainWindow, public COutputInterface
  {
    Q_OBJECT

  private:

    // points to the plot instance inside this window
    CopasiPlot *mpPlot;
    COutputHandlerPlot *mpHandler;

  public:
    PlotWindow(COutputHandlerPlot * pHandler, const CPlotSpecification* ptrSpec);

    bool initFromSpec(const CPlotSpecification* ptrSpec);

    //QToolButton * zoomButton;
    QToolButton * printButton;
    QToolButton * saveButton;

    ~PlotWindow();

    /**
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer);

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

    /**
     * Retreive the list of objects handled by the interface
     * @return const std::set< const CCopasiObject * > & objects
     */
    virtual const std::set< const CCopasiObject * > & getObjects() const;

  private slots:
    //void enableZoom();

    //void mouseReleased(const QMouseEvent &e);

    // prints the plot (to printer or file)
    void printPlot();

    void slotSaveData();
  };
