/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/plotwindow.cpp,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/02 11:52:02 $
   End CVS Header */

// the window containing the plot and buttons for supported operations

#include <qtoolbar.h>
#include <qprinter.h>

#include "plotwindow.h"
#include "CopasiPlot.h"
#include "CPlotSpecification.h"

#include "CopasiUI/qtUtilities.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qcursor.h>
#include <qregexp.h>

C_INT32 checkSelection(const QString & file);

// taken from qwt examples/bode
class PrintFilter: public QwtPlotPrintFilter
  {
  public:
    PrintFilter() {};

    virtual QFont font(const QFont &f, Item, int) const
      {
        QFont f2 = f;
        f2.setPointSize((int)(f.pointSize() * 0.75));
        return f2;
      }
  };

//-----------------------------------------------------------------------------

PlotWindow::PlotWindow(CPlotSpec2Vector* psv, const CPlotSpecification* ptrSpec)
{
  this->resize(640, 480);
  this->setCaption(("Copasi Plot: " + ptrSpec->getTitle()).c_str());

  // set up the GUI - the toolbar
  QToolBar * plotTools = new QToolBar(this, "plot operations");
  plotTools->setLabel("Plot Operations");

  zoomButton = new QToolButton(plotTools, "zoom");
  zoomButton->setText("Zoom");
  zoomButton->setTextLabel("Zoom");
  //zoomButton->setToggleButton(true);

  printButton = new QToolButton(plotTools, "print plot");
  printButton -> setTextLabel("Print plot");
  printButton -> setText("Print");

  saveButton = new QToolButton(plotTools, "save data");
  saveButton -> setTextLabel("Save data...");
  saveButton -> setText("Save data...");

  plotTools->setStretchableWidget(new QWidget(plotTools));

  mpPlot = new CopasiPlot(psv, ptrSpec, this);
  setCentralWidget(mpPlot);

  connect(zoomButton, SIGNAL(clicked()), this, SLOT(enableZoom()));
  connect(printButton, SIGNAL(clicked()), this, SLOT(printPlot()));
  connect(saveButton, SIGNAL(clicked()), this, SLOT(slotSaveData()));
  connect(mpPlot, SIGNAL(plotMouseReleased(const QMouseEvent &)), this, SLOT(mouseReleased(const QMouseEvent&)));
}

bool PlotWindow::initFromSpec(CPlotSpec2Vector* psv, const CPlotSpecification* ptrSpec)
{
  this->setCaption(("Copasi Plot: " + ptrSpec->getTitle()).c_str());
  return mpPlot->initFromSpec(psv, ptrSpec);
}

//-----------------------------------------------------------------------------

void PlotWindow::enableZoom()
{
  zoomButton->setEnabled(false);
  mpPlot->enableZoom(true);
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

  QString docName = mpPlot->title();
  if (docName.isEmpty())
    {
      //docName.replace (QRegExp (QString::fromLatin1 ("\n")), tr (" -- "));
      docName = QString::fromLatin1("A plot of selected Copasi output");
      printer.setDocName (docName);
    }

  printer.setCreator(docName);
  printer.setOrientation(QPrinter::Landscape);

  if (printer.setup())
    mpPlot->print(printer, PrintFilter());
}

void PlotWindow::slotSaveData()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName = QFileDialog::getSaveFileName(QString::null, QString::null, this, 0, "Save to");
      //std::cout << "fileName: " << fileName << std::endl;
      if (fileName.isEmpty()) return;

      if (!fileName.endsWith(".txt") &&
          !fileName.endsWith(".")) fileName += ".txt";

      fileName = fileName.remove(QRegExp("\\.$"));

      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  bool success = false;
  if (mpPlot)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      success = mpPlot->saveData((const char *)fileName.utf8());
      setCursor(oldCursor);
    }
  if (!success)
    {
      std::string s = "Could not save data to ";
      s += fileName.utf8();
      QMessageBox::critical(this, "Save Error", FROM_UTF8(s), QMessageBox::Ok, QMessageBox::Cancel);
    }
}

//-----------------------------------------------------------------------------

PlotWindow::~PlotWindow()
{}

void PlotWindow::takeData(const std::vector<C_FLOAT64> & data)
{if (mpPlot) mpPlot->takeData(data);};

void PlotWindow::updatePlot()
{if (mpPlot) mpPlot->updatePlot();};
