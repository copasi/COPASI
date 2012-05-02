// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/plotwindow.cpp,v $
//   $Revision: 1.51 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/02 18:56:35 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// the window containing the plot and buttons for supported operations

#include <QtSvg>

#include <QToolBar>
#include <QPrinter>
#include <QPixmap>
#include <QPicture>
#include <QSvgGenerator>

#include "plotwindow.h"
#include "CopasiPlot.h"
#include "plot/CPlotSpecification.h"
#include "COutputHandlerPlot.h"

#include "UI/copasiui3window.h"
#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"

#ifdef DEBUG_UI
#include <QtDebug>
#endif

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

PlotWindow::PlotWindow(COutputHandlerPlot * pHandler, const CPlotSpecification* ptrSpec, CopasiUI3Window * pMainWindow):
    QMainWindow(),
    mpPlot(NULL),
    mpHandler(pHandler),
    mpMainWindow(pMainWindow)
{
  this->resize(640, 480);
  this->setWindowTitle(("COPASI Plot: " + ptrSpec->getTitle()).c_str());

  // set up the GUI - the toolbar
  createActions();
  createToolBar();

  mpPlot = new CopasiPlot(ptrSpec, this);
  setCentralWidget(mpPlot);

  mpMainWindow->addWindow(this);
}

void PlotWindow::createActions()
{
  printButton = new QToolButton;
  printButton -> setToolTip("Print Plot");
  printButton -> setText("Print");
  connect(printButton, SIGNAL(clicked()), this, SLOT(printPlot()));

  print2Button = new QToolButton;
  print2Button -> setToolTip("Print Image");
  print2Button -> setText("Save Image");
  connect(print2Button, SIGNAL(clicked()), this, SLOT(printAsImage()));

  saveButton = new QToolButton;
  saveButton -> setToolTip("Save Data");
  saveButton -> setText("Save Data");
  connect(saveButton, SIGNAL(clicked()), this, SLOT(slotSaveData()));

  zoomButton = new QToolButton;
  zoomButton->setToolTip("Zoom out");
  zoomButton->setText("Zoom out");
  connect(zoomButton, SIGNAL(clicked()), this, SLOT(slotZoomOut()));

  mpSelectAll = new QToolButton;
  mpSelectAll->setToolTip("Show all curves");
  mpSelectAll->setText("Show All");
  connect(mpSelectAll, SIGNAL(clicked()), this, SLOT(slotSelectAll()));

  mpDeselectAll = new QToolButton;
  mpDeselectAll->setToolTip("Hide all curves");
  mpDeselectAll->setText("Hide All");
  connect(mpDeselectAll, SIGNAL(clicked()), this, SLOT(slotDeselectAll()));
}

void PlotWindow::createToolBar()
{
  QToolBar * plotTools = addToolBar("plot operations");

  plotTools->addWidget(printButton);
  plotTools->addWidget(print2Button);
  plotTools->addWidget(saveButton);
  plotTools->addWidget(zoomButton);

  plotTools->addSeparator();

  plotTools->addWidget(mpSelectAll);
  plotTools->addWidget(mpDeselectAll);

  plotTools->addSeparator();

  QAction* closeAct = new QAction("Close", this);
  closeAct->setObjectName("close");
  closeAct->setShortcut(Qt::CTRL + Qt::Key_W);
  connect(closeAct, SIGNAL(triggered()), this, SLOT(slotCloseWindow()));
  plotTools->addAction(closeAct);

  //TODO button icons...

//  plotTools->setStretchableWidget(new QWidget(plotTools));
}

bool PlotWindow::initFromSpec(const CPlotSpecification* ptrSpec)
{
  this->setWindowTitle(("COPASI Plot: " + ptrSpec->getTitle()).c_str());
  return mpPlot->initFromSpec(ptrSpec);
}

//-----------------------------------------------------------------------------

/*void PlotWindow::enableZoom()
{
  zoomButton->setEnabled(false);
  mpPlot->enableZoom(true);
}*/

//-----------------------------------------------------------------------------

/*void PlotWindow::mouseReleased(const QMouseEvent &e)
{
  //TODO: if midbutton is clicked and we're zoomed out completely, zoomButton need to be enabled as well

  if (e.button() == RightButton)
    zoomButton->setEnabled(true);
}*/

//-----------------------------------------------------------------------------

void PlotWindow::printAsImage()
{
  // take a name from QFileDialog

  C_INT32 Answer = QMessageBox::No;
  QString fileName, extensionName;

  while (Answer == QMessageBox::No)
    {

//      QString userFilter = new QString;
      /*
            fileName = CopasiFileDialog::getSaveFileNameAndFilter(filter, this, "Save File Dialog",
                       QString::null, "PNG Files (*.png);;SVG Files (*.svg)", "Save to");
      */
      fileName = CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                 "untitled.png", "PNG Files (*.png);;SVG Files (*.svg)", "Save to", new QString);

      if (fileName.isEmpty()) return;

      /*
            QFileInfo fileInfo(fileName);
            extensionName = fileInfo.extension();
      */
#ifdef DEBUG_UI
//      qDebug() << "extensionName = " << extensionName;
#endif

      // check whether the file exists
      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  // print plot as an image

  QPainter painter;
  QRect rect;
  rect.setSize(this->size());

  if (fileName.endsWith(".png"))
    {
      QPixmap pixmap(rect.width(), rect.height());
      pixmap.fill();

      painter.begin(&pixmap);
      mpPlot->print(&painter, rect, PrintFilter());
      painter.end();

      pixmap.save(fileName, "PNG");
    }

  if (fileName.endsWith(".svg"))
    {
      QSvgGenerator generator;
      generator.setFileName(fileName);

      painter.begin(&generator);
      mpPlot->print(&painter, rect, PrintFilter());
      painter.end();
    }
}

void PlotWindow::printPlot()
{
  QPrinter printer;

  QString docName = mpPlot->title().text();

  if (docName.isEmpty())
    {
      //docName.replace (QRegExp (QString::fromLatin1 ("\n")), tr (" -- "));
      docName = QString::fromLatin1("A plot of selected COPASI output");
      printer.setDocName(docName);
    }

  printer.setCreator("COPASI");
  printer.setOrientation(QPrinter::Landscape);

  QPrintDialog dialog(&printer);

  if (dialog.exec())
    mpPlot->print(printer, PrintFilter());
}

void PlotWindow::slotSaveData()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog", "untitled.txt", "TEXT Files (*.txt)", "Save to");

      if (fileName.isNull()) return;

      // Checks whether the file exists
      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  bool success = false;

  if (mpPlot)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      success = mpPlot->saveData(TO_UTF8(fileName));
      setCursor(oldCursor);
    }

  if (!success)
    {
      std::string s = "Could not save data to ";
      s += TO_UTF8(fileName);
      CQMessageBox::critical(this, "Save Error", FROM_UTF8(s), QMessageBox::Ok, QMessageBox::NoButton);
    }
}

#include "scrollzoomer.h"

void PlotWindow::slotZoomOut()
{
  if (mpPlot && mpPlot->mpZoomer)
    mpPlot->mpZoomer->zoom(0);
}

//-----------------------------------------------------------------------------

PlotWindow::~PlotWindow()
{
  if (mpHandler)
    mpHandler->removeInterface(this);

  if (mpMainWindow != NULL)
    mpMainWindow->removeWindow(this);
}

bool PlotWindow::compile(std::vector< CCopasiContainer * > listOfContainer,
                         const CCopasiDataModel* pDataModel)
{
  mObjects.clear();
  bool success = true;

  if (mpPlot != NULL)
    success = mpPlot->compile(listOfContainer, pDataModel);

  return success;
};

void PlotWindow::output(const Activity & activity)
{if (mpPlot) mpPlot->output(activity);}

void PlotWindow::separate(const Activity & activity)
{if (mpPlot) mpPlot->separate(activity);};

void PlotWindow::finish()
{if (mpPlot) mpPlot->finish();};

const std::set< const CCopasiObject * > & PlotWindow::getObjects() const
{
  if (mpPlot)
    return mpPlot->getObjects();

  return mObjects;
}

void PlotWindow::slotSelectAll()
{
  // We show all curves in mpPlot
  mpPlot->setCurvesVisibility(true);
}

void PlotWindow::slotDeselectAll()
{
  // We hide all curves in mpPlot
  mpPlot->setCurvesVisibility(false);
}

void PlotWindow::slotCloseWindow()
{
  close();
}

CopasiPlot* PlotWindow::getPlot() const
{
  return mpPlot;
}
