// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// the window containing the plot and buttons for supported operations


#include <QToolBar>
#include <QPrinter>
#include <QPixmap>
#include <QPicture>
#include <QPrintDialog>

#include <QtSvg/QtSvg>
#include <QtSvg/QSvgGenerator>

#include "plotwindow.h"
#include "CopasiPlot.h"
#include "plot/CPlotSpecification.h"
#include "COutputHandlerPlot.h"

#include "UI/copasiui3window.h"
#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"
#include "resourcesUI/CQIconResource.h"

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

#include <qwt_plot.h>
#include <qwt_scale_engine.h>

#if QWT_VERSION > 0x060000
#include <qwt_plot_renderer.h>
#endif

#if QWT_VERSION < 0x060000
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
#endif

//-----------------------------------------------------------------------------
PlotWindow::PlotWindow(COutputHandlerPlot *pHandler, const CPlotSpecification *ptrSpec, CopasiUI3Window *pMainWindow):
  CWindowInterface(),
  mpPlot(NULL),
  mpHandler(pHandler),
  mpMainWindow(pMainWindow),
  mpWindowMenu(NULL),
  mpToolBar(NULL),
  mpaCloseWindow(NULL),
  mpaShowAll(NULL),
  mpaHideAll(NULL),
  mpaPrint(NULL),
  mpaSaveImage(NULL),
  mpaSaveData(NULL),
  mpaZoomOut(NULL),
  mpaToggleLogX(NULL),
  mpaToggleLogY(NULL),
  mpaDeactivatePlot(NULL),
  initializing(false)
{
  this->resize(640, 480);
  this->setWindowTitle(("COPASI Plot: " + ptrSpec->getTitle()).c_str());
#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin
  // set up the GUI - the toolbar
  createActions();
  createMenus();
  createToolBar();
  mpPlot = new CopasiPlot(ptrSpec, this);
  setCentralWidget(mpPlot);
  initializing  = true;
  mpaToggleLogX->setChecked(ptrSpec->isLogX());
  mpaToggleLogY->setChecked(ptrSpec->isLogY());
  initializing = false;
  addToMainWindow(mpMainWindow);

  if (ptrSpec->isActive())
    {
      mpaDeactivatePlot->setText("Deactivate");
    }
  else
    {
      mpaDeactivatePlot->setText("Activate");
    }

}

void PlotWindow::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(mpaSaveImage);
  fileMenu->addAction(mpaSaveData);
  fileMenu->addAction(mpaPrint);
  fileMenu->addSeparator();
  fileMenu->addAction(mpaCloseWindow);
  QMenu *viewMenu = menuBar()->addMenu("&View");
  viewMenu->addAction(mpaShowAll);
  viewMenu->addAction(mpaHideAll);
  viewMenu->addSeparator();
  viewMenu->addAction(mpaToggleLogX);
  viewMenu->addAction(mpaToggleLogY);
  viewMenu->addSeparator();
  viewMenu->addAction(mpaZoomOut);
  // add a place holder menu, to be filled by the main window
  mpWindowMenu = menuBar()->addMenu("&Window");
}
QMenu *PlotWindow::getWindowMenu() const
{
  return mpWindowMenu;
}

void PlotWindow::createActions()
{
  mpaToggleLogX = new QAction("Log &X", this);
  mpaToggleLogX->setCheckable(true);
  mpaToggleLogX->setToolTip("Toggle x-axis logscale.");
  connect(mpaToggleLogX, SIGNAL(toggled(bool)), this, SLOT(toggleLogX(bool)));
  mpaToggleLogY = new QAction("Log &Y", this);
  mpaToggleLogY->setCheckable(true);
  mpaToggleLogY->setToolTip("Toggle y-axis logscale.");
  connect(mpaToggleLogY, SIGNAL(toggled(bool)), this, SLOT(toggleLogY(bool)));
  mpaPrint = new QAction("Print", this);
  mpaPrint ->setToolTip("Print Plot");
  mpaPrint -> setShortcut(Qt::CTRL + Qt::Key_P);
  connect(mpaPrint, SIGNAL(triggered()), this, SLOT(printPlot()));
  mpaSaveImage = new QAction("Save Image", this);
  mpaSaveImage ->setShortcut(Qt::CTRL + Qt::Key_S);
  mpaSaveImage ->setToolTip("Save Plot as Image");
  connect(mpaSaveImage, SIGNAL(triggered()), this, SLOT(printAsImage()));
  mpaSaveData = new QAction("Save Data", this);
  mpaSaveData ->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
  mpaSaveData ->setToolTip("Save Data");
  connect(mpaSaveData, SIGNAL(triggered()), this, SLOT(slotSaveData()));
  mpaZoomOut = new QAction("Zoom out", this);
  mpaZoomOut ->setShortcut(Qt::CTRL + Qt::Key_0);
  mpaZoomOut ->setToolTip("Zoom out");
  connect(mpaZoomOut, SIGNAL(triggered()), this, SLOT(slotZoomOut()));
  mpaShowAll = new QAction("Show All", this);
  mpaShowAll ->setShortcut(Qt::CTRL + Qt::Key_A);
  mpaShowAll ->setToolTip("Show all curves");
  connect(mpaShowAll, SIGNAL(triggered()), this, SLOT(slotSelectAll()));
  mpaHideAll = new QAction("Hide All", this);
  mpaHideAll ->setShortcut(Qt::CTRL + Qt::Key_D);
  mpaHideAll ->setToolTip("Hide all curves");
  connect(mpaHideAll, SIGNAL(triggered()), this, SLOT(slotDeselectAll()));
  mpaCloseWindow = new QAction("Close", this);
  mpaCloseWindow->setObjectName("close");
  mpaCloseWindow->setShortcut(Qt::CTRL + Qt::Key_W);
  connect(mpaCloseWindow, SIGNAL(triggered()), this, SLOT(slotCloseWindow()));
  mpaDeactivatePlot = new QAction("Deactivate", this);
  mpaDeactivatePlot->setObjectName("deactivate");
  connect(mpaDeactivatePlot, SIGNAL(triggered()), this, SLOT(slotDeactivatePlot()));
}

void PlotWindow::createToolBar()
{
  mpToolBar = addToolBar("plot operations");
  mpToolBar->addAction(mpaPrint);
  mpToolBar->addAction(mpaSaveImage);
  mpToolBar->addAction(mpaSaveData);
  mpToolBar->addAction(mpaZoomOut);
  mpToolBar->addSeparator();
  mpToolBar->addAction(mpaToggleLogX);
  mpToolBar->addAction(mpaToggleLogY);
  mpToolBar->addSeparator();
  mpToolBar->addAction(mpaShowAll);
  mpToolBar->addAction(mpaHideAll);
  mpToolBar->addAction(mpaDeactivatePlot);
  mpToolBar->addSeparator();
  mpToolBar->addAction(mpaCloseWindow);
  //TODO button icons...
  setUnifiedTitleAndToolBarOnMac(true);
  //  plotTools->setStretchableWidget(new QWidget(plotTools));
}

bool PlotWindow::initFromSpec(const CPlotSpecification *ptrSpec)
{
  this->setWindowTitle(("COPASI Plot: " + ptrSpec->getTitle()).c_str());
  bool result = mpPlot->initFromSpec(ptrSpec);

  if (result)
    {
      initializing  = true;
      mpaToggleLogX->setChecked(ptrSpec->isLogX());
      mpaToggleLogY->setChecked(ptrSpec->isLogY());
      initializing = false;
    }

  return result;
}

// toggle log X
void PlotWindow::toggleLogX(bool logX)
{
  if (initializing) return;

  if (logX)
    {
#if QWT_VERSION > 0x060000
      mpPlot->setAxisScaleEngine(QwtPlot::xBottom, new QwtLogScaleEngine());
#else
      mpPlot->setAxisScaleEngine(QwtPlot::xBottom, new QwtLog10ScaleEngine());
#endif
    }
  else
    {
      mpPlot->setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine());
    }

  mpPlot->setAxisAutoScale(QwtPlot::xBottom);
  mpPlot->updateAxes();
  mpPlot->replot();
  mpPlot->update();
}

// toggle log Y
void PlotWindow::toggleLogY(bool logY)
{
  if (initializing) return;

  if (logY)
    {
#if QWT_VERSION > 0x060000
      mpPlot->setAxisScaleEngine(QwtPlot::yLeft, new QwtLogScaleEngine());
#else
      mpPlot->setAxisScaleEngine(QwtPlot::yLeft, new QwtLog10ScaleEngine());
#endif
    }
  else
    {
      mpPlot->setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine());
    }

  mpPlot->setAxisAutoScale(QwtPlot::yLeft);
  mpPlot->updateAxes();
  mpPlot->replot();
  mpPlot->update();
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
void PlotWindow::saveToFile(const QString &fileName) const
{
  QRect rect;
  rect.setSize(this->size());

  if (fileName.endsWith(".png"))
    {
      QPixmap pixmap(rect.width(), rect.height());
      pixmap.fill();
      QPainter painter(&pixmap);
      painter.begin(&pixmap);
#if QWT_VERSION > 0x060000
      QwtPlotRenderer renderer;
      renderer.render(mpPlot, &painter, rect);
#else
      mpPlot->print(&painter, rect, PrintFilter());
#endif
      painter.end();
      pixmap.save(fileName, "PNG");
    }
  else if (fileName.endsWith(".svg"))
    {
      QSvgGenerator generator;
      generator.setFileName(fileName);
      QPainter painter(&generator);
      painter.begin(&generator);
#if QWT_VERSION > 0x060000
      QwtPlotRenderer renderer;
      renderer.render(mpPlot, &painter, rect);
#else
      mpPlot->print(&painter, rect, PrintFilter());
#endif
      painter.end();
    }
  else if (fileName.endsWith(".pdf"))
    {
      QPrinter printer;
      printer.setOutputFileName(fileName);
      printer.setOutputFormat(QPrinter::PdfFormat);
      QPainter painter(&printer);
      painter.begin(&printer);
#if QWT_VERSION > 0x060000
      QwtPlotRenderer renderer;
      renderer.render(mpPlot, &painter, rect);
#else
      mpPlot->print(&painter, rect, PrintFilter());
#endif
      painter.end();
    }
}

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
                 "untitled.pdf", "PDF Files (*.pdf);;PNG Files (*.png);;SVG Files (*.svg)", "Save Plot as Image", new QString);

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
  saveToFile(fileName);
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
    {
#if QWT_VERSION > 0x060000
      QwtPlotRenderer renderer;
      renderer.renderTo(mpPlot, printer);
#else
      mpPlot->print(printer, PrintFilter());
#endif
    }
}

void PlotWindow::slotSaveData()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog", "untitled.txt", "TEXT Files (*.txt)", "Save Plot Data to");

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
    removeFromMainWindow(mpMainWindow);

  pdelete(mpToolBar);
}

bool PlotWindow::compile(CObjectInterface::ContainerList listOfContainer)
{
  mObjects.clear();
  bool success = true;

  if (mpPlot != NULL)
    success = mpPlot->compile(listOfContainer);

  return success;
};

void PlotWindow::output(const Activity &activity)
{if (mpPlot) mpPlot->output(activity);}

void PlotWindow::separate(const Activity &activity)
{if (mpPlot) mpPlot->separate(activity);};

void PlotWindow::finish()
{if (mpPlot) mpPlot->finish();};

const CObjectInterface::ObjectSet &PlotWindow::getObjects() const
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
  QWidget::close();
}

void PlotWindow::slotDeactivatePlot()
{
  if (mpPlot == NULL) return;

  CPlotSpecification* spec = const_cast<CPlotSpecification*>(mpPlot->getPlotSpecification());

  if (spec == NULL) return;

  spec->setActive(!spec->isActive());

  if (spec->isActive())
    {
      mpaDeactivatePlot->setText("Deactivate");
    }
  else
    {
      mpaDeactivatePlot->setText("Activate");
    }
}

void PlotWindow::closeEvent(QCloseEvent *closeEvent)
{
  mpMainWindow->removeWindow(this);
  mpHandler->removeInterface(this);
}

CopasiPlot *PlotWindow::getPlot() const
{
  return mpPlot;
}
