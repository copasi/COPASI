// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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
#include <QMenuBar>

#include <copasi/UI/listviews.h>

#include "plotwindow.h"

#ifdef COPASI_USE_QTCHARTS
#  include "CQtChartsPlot.h"
#endif

#ifdef COPASI_USE_QCUSTOMPLOT
#  include "CQCustomPlot.h"
#endif

#ifdef COPASI_USE_QWT
#  include "CQwtPlot.h"
#endif

#ifdef WITH_QT5_VISUALIZATION
#include "CQDataVizPlot.h"
#endif

#include "copasi/plot/CPlotSpecification.h"
#include "COutputHandlerPlot.h"

#include "copasi/UI/copasiui3window.h"
#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/resourcesUI/CQIconResource.h"

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

//-----------------------------------------------------------------------------
PlotWindow::PlotWindow(COutputHandlerPlot *pHandler, const CPlotSpecification *ptrSpec, CopasiUI3Window *pMainWindow)
  : CWindowInterface(),
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

  auto engine = getParameterValue(ptrSpec, "plot engine").toString();

  if (engine.isEmpty())
    engine = "QWT";

  mpPlot = createPlot(ptrSpec);
  setCentralWidget(dynamic_cast< QWidget * >(mpPlot));

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

  grabGesture(Qt::PanGesture);
  grabGesture(Qt::PinchGesture);
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
  viewMenu->addAction(mpaEditPlot);
  viewMenu->addAction(mpaDeactivatePlot);
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
  mpaSaveData ->setShortcut(QKeySequence(Qt::CTRL, Qt::SHIFT, Qt::Key_S));
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
  mpaDeactivatePlot->setToolTip("Disables / Enables the plot. When enabled it will automatically appear / update upon running the task.");
  mpaDeactivatePlot->setObjectName("deactivate");
  connect(mpaDeactivatePlot, SIGNAL(triggered()), this, SLOT(slotDeactivatePlot()));
  mpaEditPlot = new QAction("Edit", this);
  mpaEditPlot->setToolTip("Edits the plot specification");
  mpaEditPlot->setObjectName("edit");
  connect(mpaEditPlot, SIGNAL(triggered()), this, SLOT(slotEditPlot()));
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

  if (!mpPlot)
    return false;

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

CPlotInterface * PlotWindow::createPlot(const CPlotSpecification * pPlotSpec)
{
  QString engine = getParameterValue(pPlotSpec, "plot engine").toString();

#ifdef COPASI_USE_QTCHARTS

  if (engine.contains("Chart"))
    {
      return new CQtChartsPlot(pPlotSpec);
    }

#endif

#ifdef COPASI_USE_QCUSTOMPLOT

  if (engine.contains("Custom"))
    {
      return new CQCustomPlot(pPlotSpec);
    }

#endif

#ifdef WITH_QT5_VISUALIZATION

  if (engine.contains("surface"))
    {
      return new CQDataVizPlot(pPlotSpec, nullptr, CQDataVizPlot::PlotMode::Surface);
    }

  if (engine.contains("scatter"))
    {
      return new CQDataVizPlot(pPlotSpec, nullptr, CQDataVizPlot::PlotMode::Scatter);
    }

#endif

#ifdef COPASI_USE_QWT
  // by default return Qwt if we have it
  return new CQwtPlot(pPlotSpec);
#endif
  return nullptr;
}

// toggle log X
void PlotWindow::toggleLogX(bool logX)
{
  if (initializing || !mpPlot) return;

  mpPlot->toggleLogX(logX);
}

// toggle log Y
void PlotWindow::toggleLogY(bool logY)
{
  if (initializing || !mpPlot)
    return;

  mpPlot->toggleLogY(logY);
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
  if (!mpPlot)
    return;

  QRect rect;
  rect.setSize(this->size());

  mpPlot->saveToFile(fileName, rect);
}

void PlotWindow::printAsImage()
{
  if (!mpPlot)
    return;

  // take a name from QFileDialog
  C_INT32 Answer = QMessageBox::No;
  QString fileName, extensionName;

  while (Answer == QMessageBox::No)
    {
      //      QString userFilter = new QString;
      /*
            fileName = CopasiFileDialog::getSaveFileNameAndFilter(filter, this, "Save File Dialog",
                       QString(), "PNG Files (*.png);;SVG Files (*.svg)", "Save to");
      */
      fileName = CopasiFileDialog::getSaveFileName(
                   this,
                   "Save File Dialog",
                   CopasiFileDialog::getDefaultFileName(""),
                   mpPlot->getSaveFilters(),
                   "Save Plot as Image", new QString);

      if (fileName.isEmpty()) return;

      /*
            QFileInfo fileInfo(fileName);
            extensionName = fileInfo.extension();
      */
#ifdef DEBUG_UI
      //      qDebug() << "extensionName = " << extensionName;
#endif
      // check whether the file exists
      Answer = checkSelection(this, fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  // print plot as an image
  saveToFile(fileName);
}

void PlotWindow::printPlot()
{
  if (!mpPlot)
    return;

  QPrinter printer;
  QString docName = mpPlot->titleText();

  if (docName.isEmpty())
    {
      //docName.replace (QRegExp (QString::fromLatin1 ("\n")), tr (" -- "));
      docName = QString::fromLatin1("A plot of selected COPASI output");
      printer.setDocName(docName);
    }

  printer.setCreator("COPASI");
#if QT_VERSION < QT_VERSION_CHECK(5,15,0)
  printer.setOrientation(QPrinter::Landscape);
#elif QT_VERSION < QT_VERSION_CHECK(6,0,0)
  printer.setPageOrientation(QPageLayout::Landscape);
#endif
  QPrintDialog dialog(&printer);

  if (dialog.exec())
    {
      QPainter painter(&printer);
      mpPlot->render(&painter, QRect());
      //#ifdef COPASI_USE_QTCHARTS
//      #else
//#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
//      QwtPlotRenderer renderer;
//      renderer.renderTo(mpPlot, printer);
//#else
//      mpPlot->print(printer, PrintFilter());
//#endif
//#endif
    }
}

void PlotWindow::slotSaveData()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog", CopasiFileDialog::getDefaultFileName(".txt"), "TEXT Files (*.txt)", "Save Plot Data to");

      if (fileName.isNull()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, fileName);

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

void PlotWindow::slotZoomOut()
{
  if (mpPlot)
    mpPlot->resetZoom();
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
{
  if (mpPlot) mpPlot->output(activity);
}

void PlotWindow::separate(const Activity &activity)
{
  if (mpPlot) mpPlot->separate(activity);
}

void PlotWindow::finish()
{
  if (mpPlot) mpPlot->finish();
}

const CObjectInterface::ObjectSet &PlotWindow::getObjects() const
{
  if (mpPlot)
    return mpPlot->getObjects();

  return mObjects;
}

void PlotWindow::slotSelectAll()
{
  if (!mpPlot)
    return;

  // We show all curves in mpPlot
  mpPlot->setCurvesVisibility(true);
}

void PlotWindow::slotDeselectAll()
{
  if (!mpPlot)
    return;

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

void PlotWindow::slotEditPlot()
{
  if (mpPlot == NULL)
    return;

  CPlotSpecification * spec = const_cast< CPlotSpecification * >(mpPlot->getPlotSpecification());

  if (spec == NULL)
    return;

  CopasiUI3Window::getMainWindow()->getMainWidget()->switchToOtherWidget(ListViews::WidgetType::NotFound, spec->getCN());
}

void PlotWindow::closeEvent(QCloseEvent *closeEvent)
{
  mpMainWindow->removeWindow(this);
  mpHandler->removeInterface(this);
}

CPlotInterface *PlotWindow::getPlot() const
{
  return mpPlot;
}
