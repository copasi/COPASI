/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/plotwindow.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/04 21:05:09 $
   End CVS Header */

// the window containing the plot and buttons for supported operations

//#include <fstream>
//#include <math.h>
//#include <qmainwindow.h>
#include <qtoolbar.h> 
//#include <qtoolbutton.h>
//#include <qtimer.h>
#include <qprinter.h>

#include "plotwindow.h" 
//#include "plotspec.h"
#include "CopasiPlot.h" 
// #include "plotwidget1.h"

// taken from qwt examples/bode
class PrintFilter: public QwtPlotPrintFilter
  {
  public:
    PrintFilter() {};

    virtual QFont font(const QFont &f, Item, int) const
      {
        QFont f2 = f;
        f2.setPointSize(f.pointSize() * 0.75);
        return f2;
      }
  };

//-----------------------------------------------------------------------------

PlotWindow::PlotWindow(const CPlotSpec* ptrSpec)
{
  // set up the GUI - the toolbar
  QToolBar * plotTools = new QToolBar(this, "plot operations");
  plotTools->setLabel("Plot Operations");

  QToolButton * autoUpdateButton = new QToolButton(plotTools, "auto update plot");
  autoUpdateButton -> setTextLabel("Update plot automatically");
  autoUpdateButton -> setToggleButton(true);
  autoUpdateButton -> setText("AutoUpdate");

  zoomButton = new QToolButton(plotTools, "zoom");
  zoomButton->setText("Zoom");
  zoomButton->setTextLabel("Zoom");
  //zoomButton->setToggleButton(true);

  QToolButton * printButton = new QToolButton(plotTools, "print plot");
  printButton -> setTextLabel("Print plot");
  printButton -> setText("Print");

  plotTools->setStretchableWidget(new QWidget(plotTools));

  plot = new CopasiPlot(ptrSpec, this);
  setCentralWidget(plot);

  //connect(appendPlot, SIGNAL(clicked()), this, SLOT(append()));
  connect(autoUpdateButton, SIGNAL(toggled(bool)), this, SLOT(autoUpdate(bool)));
  connect(zoomButton, SIGNAL(clicked()), this, SLOT(enableZoom()));
  connect(printButton, SIGNAL(clicked()), this, SLOT(printPlot()));
  connect(plot, SIGNAL(plotMouseReleased(const QMouseEvent &)), this, SLOT(mouseReleased(const QMouseEvent&)));
  //connect(timer, SIGNAL(timeout()), this, SLOT(append()));
}

bool PlotWindow::initFromSpec(const CPlotSpec* ptrSpec)
{
  plot->initFromSpec(ptrSpec);
}

//-----------------------------------------------------------------------------

//void PlotWindow::append()
//{
//  plot->appendPlot();
//}

//-----------------------------------------------------------------------------

void PlotWindow::autoUpdate(bool toggled)
{
  if (toggled)
    {
      // zoom out first
      plot->zoomOut();

      plot->setAxisAutoScale(QwtPlot::yLeft);
      plot->setAxisAutoScale(QwtPlot::yRight);
      plot->setAxisAutoScale(QwtPlot::xBottom);
      plot->setAxisAutoScale(QwtPlot::xTop);

      // disable zooming
      zoomButton->setEnabled(false);
      plot->enableZoom(false);

      // initiate the first update
      //      append();  //for now

      // NB: timeout is hard-coded for now - maybe add something in the GUI to let the user decide
      //timer->start(5000);
    }
  else
    {
      //timer->stop();
      zoomButton->setEnabled(true);
    }
}

//-----------------------------------------------------------------------------

void PlotWindow::enableZoom()
{
  zoomButton->setEnabled(false);
  plot->enableZoom(true);
}

//-----------------------------------------------------------------------------

void PlotWindow::mouseReleased(const QMouseEvent &e)
{
  //TODO: if midbutton is clicked and we're zoomed out completely, zoomButton need to be enabled as well

  if (e.button() == RightButton)
    zoomButton->setEnabled(true);
}

//-----------------------------------------------------------------------------

void PlotWindow::printPlot()
{
  QPrinter printer;

  QString docName = plot->title();
  if (docName.isEmpty())
    {
      //docName.replace (QRegExp (QString::fromLatin1 ("\n")), tr (" -- "));
      docName = QString::fromLatin1("A plot of selected Copasi output");
      printer.setDocName (docName);
    }

  printer.setCreator(docName);
  printer.setOrientation(QPrinter::Landscape);

  if (printer.setup())
    plot->print(printer, PrintFilter());
}

//-----------------------------------------------------------------------------

//void PlotWindow::reloadPlot(CPlotSpec* plotspec, std::vector<int> deletedCurveKeys)
//{
//  plot->reloadPlot(plotspec, deletedCurveKeys);
//}

//-----------------------------------------------------------------------------

PlotWindow::~PlotWindow()
{}

void PlotWindow::takeData(const std::vector<C_FLOAT64> & data)
{if (plot) plot->takeData(data);};

void PlotWindow::updatePlot()
{if (plot) plot->updatePlot();};
