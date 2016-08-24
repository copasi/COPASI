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
#include "optimization/COptPopulationMethod.h"
#include "optimization/COptTask.h"
#include "optimization/COptProblem.h"
#include "optimization/COptItem.h"

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
  mCounter(0),
  mDataInitialized(false),
  mGraphInitialized(false),
  initializing(false),
  mNumParameters(0)
{
  this->resize(640, 480);
  this->setWindowTitle("Population Visualisation");

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
  
  connect(this, SIGNAL(updateSignal()), this, SLOT(update()));

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

void CQOptPopulation::setMethod(COptMethod* pMethod)
{
  mpSourceMethod = pMethod;
  mpPopulationMethod = dynamic_cast<COptPopulationMethod*>(pMethod);
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


void CQOptPopulation::output(const Activity & activity)
{
  if (activity != COutputInterface::Activity(0x08) )
    return;
  
  if (!mDataInitialized)
  {
    CCopasiTask* pTask = dynamic_cast<CCopasiTask*>(mpSourceMethod->getObjectParent());
    if (!pTask)
      return;
    COptProblem* pProblem = dynamic_cast<COptProblem*>(pTask->getProblem());
    if(!pProblem)
      return;
    
    //now that we have access to the problem we can retrieve the range information for the parameters.
    mNumParameters = pProblem->getOptItemList().size();
    mRangeMax.resize(mNumParameters);
    mRangeMin.resize(mNumParameters);
    mIsLog.resize(mNumParameters);
    
    unsigned C_INT32 i;
    for (i=0; i<mNumParameters; ++i)
    {
      COptItem* pOI = pProblem->getOptItemList()[i];
      mRangeMax[i]=*pOI->getUpperBoundValue();
      mRangeMin[i]=*pOI->getLowerBoundValue();

      //guess if log scaling should be used. This could also be retrieved from the method?
      if (mRangeMin[i]>0.0 && mRangeMax[i]>0.0 && mRangeMax[i]/mRangeMin[i]>1000)
        mIsLog[i]=true;
      else
        mIsLog[i]=false;
      
    }
    
    mDataInitialized=true;
  }
  
  //copy the data
  mPopulation = mpPopulationMethod->getPopulation();
  mObjectiveValues = mpPopulationMethod->getObjectiveValues();
  
  
  mCounter++;
  
  emit updateSignal();
  
}


void CQOptPopulation::update()
{
 
  if (!mGraphInitialized)
  {
 
    mpGS = new QGraphicsScene(this);
    mpGV = new QGraphicsView(mpGS, this);
    this->setCentralWidget(mpGV);
    
    
    mpGS->addRect(-3,-3,6,6);
    //mpGV->fitInView(-4,-4,8,8);
    mpGV->resetMatrix();
    mpGV->scale(10,10);
    mpGV->setDragMode(QGraphicsView::ScrollHandDrag);
    
    mGraphInitialized=true;
  }
  
  unsigned C_INT32 i;
  for (i=0; i<mPopulation.size(); ++i)
  {
    std::cout <<mPopulation[i]->operator[](0) << "  " << mPopulation[i]->operator[](1) << std::endl;
    
    double xx =0;
    if (mIsLog[0])
      xx = log(mPopulation[i]->operator[](0));
    else
      xx = mPopulation[i]->operator[](0);
    double yy =0;
    if (mIsLog[1])
      yy = log(mPopulation[i]->operator[](1));
    else
      yy = mPopulation[i]->operator[](1);
    
   mpGS->addEllipse(xx,
                    yy,
                    0.1,0.1);
  }
  
 //®std::cout << "output in main thread" << std::endl;
 
 /*  if (mNextPlotTime < CCopasiTimeVariable::getCurrentWallTime())
    {
      // skip rendering when shift is pressed
      Qt::KeyboardModifiers mods = QApplication::keyboardModifiers();

      if (((int)mods & (int)Qt::ShiftModifier) == (int)Qt::ShiftModifier &&
          !mNextPlotTime.isZero())
        {
          mReplotFinished = true;
          return;
        }

      CCopasiTimeVariable Delta = CCopasiTimeVariable::getCurrentWallTime();

      {
        QMutexLocker Locker(&mMutex);
        updateCurves(C_INVALID_INDEX);
      }

      QwtPlot::replot();

      Delta = CCopasiTimeVariable::getCurrentWallTime() - Delta;

      if (!mSpectogramMap.empty())
        mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime() + 10 * Delta.getMicroSeconds();
      else
        mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime() + 3 * Delta.getMicroSeconds();
    }

  mReplotFinished = true;*/
}

