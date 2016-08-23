// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QtSvg/QtSvg>

#include <QtGui/QToolBar>
#include <QtGui/QPrinter>
#include <QtGui/QPixmap>
#include <QtGui/QPicture>
#include <QtSvg/QSvgGenerator>

#include "CQOptPopulation.h"

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
CQOptPopulation::CQOptPopulation(COutputHandler * pHandler, CopasiUI3Window * pMainWindow):
  CWindowInterface(),
  mpHandler(pHandler),
  mpMainWindow(pMainWindow),
  mpWindowMenu(NULL),
  mpToolBar(NULL),
  mpaCloseWindow(NULL),
  initializing(false)
{
  this->resize(640, 480);
  this->setWindowTitle("");

#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin

  // set up the GUI - the toolbar
  createActions();
  createMenus();
  createToolBar();

  //setCentralWidget(mpPlot);

  initializing  = true;
  initializing = false;

  addToMainWindow(mpMainWindow);
}

void CQOptPopulation::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu("&File");
//  fileMenu->addAction(mpaSaveImage);

  QMenu *viewMenu = menuBar()->addMenu("&View");
//  viewMenu->addAction(mpaShowAll);
//  viewMenu->addSeparator();

  // add a place holder menu, to be filled by the main window
  mpWindowMenu = menuBar()->addMenu("&Window");
}
QMenu *CQOptPopulation::getWindowMenu() const
{
  return mpWindowMenu;
}

void CQOptPopulation::createActions()
{
  //mpaToggleLogX = new QAction("Log &X", this);
  //mpaToggleLogX->setCheckable(true);
  //mpaToggleLogX->setToolTip("Toggle x-axis logscale.");
  //connect(mpaToggleLogX, SIGNAL(toggled(bool)), this, SLOT(toggleLogX(bool)));

  mpaCloseWindow = new QAction("Close", this);
  mpaCloseWindow->setObjectName("close");
  mpaCloseWindow->setShortcut(Qt::CTRL + Qt::Key_W);
  connect(mpaCloseWindow, SIGNAL(triggered()), this, SLOT(slotCloseWindow()));
}

void CQOptPopulation::createToolBar()
{
  mpToolBar = addToolBar("plot operations");

//  mpToolBar->addAction(mpaPrint);

//  mpToolBar->addSeparator();

  mpToolBar->addAction(mpaCloseWindow);

  //TODO button icons...

  setUnifiedTitleAndToolBarOnMac(true);
}

bool CQOptPopulation::initFromSpec()
{
  return false;
}

void CQOptPopulation::saveToFile(const QString& fileName) const
{
}



void CQOptPopulation::slotSaveData()
{
}


//-----------------------------------------------------------------------------

CQOptPopulation::~CQOptPopulation()
{
  if (mpHandler)
    mpHandler->removeInterface(this);

  if (mpMainWindow != NULL)
    removeFromMainWindow(mpMainWindow);

  pdelete(mpToolBar);
}

bool CQOptPopulation::compile(CObjectInterface::ContainerList listOfContainer)
{
  mObjects.clear();
  bool success = true;

  return success;
};

void CQOptPopulation::output(const Activity & activity)
{
}

void CQOptPopulation::separate(const Activity & activity)
{
};

void CQOptPopulation::finish()
{
};

const CObjectInterface::ObjectSet & CQOptPopulation::getObjects() const
{

  return mObjects;
}


void CQOptPopulation::slotCloseWindow()
{
  QWidget::close();
}

void CQOptPopulation::closeEvent(QCloseEvent *closeEvent)
{
  mpMainWindow->removeWindow(this);
  mpHandler->removeInterface(this);
}

