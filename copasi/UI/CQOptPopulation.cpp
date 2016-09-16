// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
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
#include "qlayout/CQZoomableView.h"
#include "UI/CColorScale.h"
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
  this->setWindowTitle("Population Visualization");

#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin



  // set up the GUI - the toolbar

  mpGS = new QGraphicsScene(this);
  mpGV = new CQZoomableView(this);
  mpGV->setScene(mpGS);
  this->setCentralWidget(mpGV);

  mpGV->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);


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
  fileMenu->addAction(mpaCloseWindow);
//  fileMenu->addAction(mpaSaveImage);

  QMenu *viewMenu = menuBar()->addMenu("&View");
//  viewMenu->addAction(mpaShowAll);
//  viewMenu->addSeparator();
  static_cast<CQZoomableView*>(mpGV)->fillZoomMenu(viewMenu);

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
  static_cast<CQZoomableView*>(mpGV)->fillZoomTooBar(mpToolBar);

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

  if (mpPopulationMethod == NULL)
    {
      mGraphInitialized = false;
      mDataInitialized = false;
    }
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
  if (activity != COutputInterface::Activity(0x08))
    return;

  if (!mDataInitialized)
    {
      if (!mpSourceMethod)
        return;

      CCopasiTask* pTask = dynamic_cast<CCopasiTask*>(mpSourceMethod->getObjectParent());

      if (!pTask)
        return;

      COptProblem* pProblem = dynamic_cast<COptProblem*>(pTask->getProblem());

      if (!pProblem)
        return;

      //now that we have access to the problem we can retrieve the range information for the parameters.
      mNumParameters = pProblem->getOptItemList().size();
      mRangeMax.resize(mNumParameters);
      mRangeMin.resize(mNumParameters);
      mIsLog.resize(mNumParameters);

      C_INT32 i;

      for (i = 0; i < mNumParameters; ++i)
        {
          COptItem* pOI = pProblem->getOptItemList()[i];
          mRangeMax[i] = *pOI->getUpperBoundValue();
          mRangeMin[i] = *pOI->getLowerBoundValue();

          //guess if log scaling should be used. This could also be retrieved from the method?
          if (mRangeMin[i] > 0.0 && mRangeMax[i] > 0.0 && mRangeMax[i] / mRangeMin[i] > 1000)
            mIsLog[i] = true;
          else
            mIsLog[i] = false;

        }

      mDataInitialized = true;
    }

  //copy the data
  mPopulation = mpPopulationMethod->getPopulation();
  mObjectiveValues = mpPopulationMethod->getObjectiveValues();


  mCounter++;

  emit updateSignal();

}


void CQOptPopulation::update()
{
  setUpdatesEnabled(false);

  if (!mGraphInitialized)
    {
      mpGS->clear();

      QGraphicsRectItem* rect = mpGS->addRect(-0, -0, 1, 1);
      rect->setBrush(QColor(220, 220, 220));


      C_INT32 numProjections = (mNumParameters + 1) / 2;
      mShiftX.resize(numProjections);
      mShiftY.resize(numProjections);
      mXIndex.resize(numProjections);
      mYIndex.resize(numProjections);
      mGraphicItems.resize(numProjections + 1); //extra space for the combined view

      //if there's more than 2 parameters, create the combined view
      if (mNumParameters > 2)
        {
          QGraphicsRectItem* rect = mpGS->addRect(-2.2, 0, 2.1, 2.1);
          rect->setBrush(QColor(230, 230, 250));

          mGraphicItems[numProjections].resize(mPopulation.size());
          unsigned C_INT32 i;

          for (i = 0; i < mPopulation.size(); ++i)
            {
              QGraphicsEllipseItem* ei = mpGS->addEllipse(-2.2, 0, 0.05, 0.05);
              mGraphicItems[numProjections][i] = ei;
              ei->setBrush(QColor(10, 100, 10));
              ei->setPen(QPen(QColor(0, 0, 0)));
            }

        }

      C_INT32 j;

      for (j = 0; j < numProjections; ++j)
        {
          mShiftX[j] = (j / 2) * 1.1;
          mShiftY[j] = (j % 2) * 1.1 ;
          mXIndex[j] = j * 2;
          mYIndex[j] = (j * 2 + 1) % mNumParameters;
          QGraphicsRectItem* rect = mpGS->addRect(mShiftX[j], mShiftY[j], 1, 1);
          rect->setBrush(QColor(240, 240, 240));

          mGraphicItems[j].resize(mPopulation.size());

          unsigned C_INT32 i;

          for (i = 0; i < mPopulation.size(); ++i)
            {

              QGraphicsEllipseItem* ei = mpGS->addEllipse(mShiftX[j], mShiftY[j], 0.05, 0.05);
              mGraphicItems[j][i] = ei;
              ei->setBrush(QColor(10, 100, 10));
              ei->setPen(QPen(QColor(0, 0, 0)));
            }
        }

      static_cast<CQZoomableView*>(mpGV)->slotFitOnScreen();

      mGraphInitialized = true;
    }

  //--------------------------------

  unsigned C_INT32 i;

  //Color scaling
  double tmp_min = 1e300;
  C_INT32 min_index = 0;
  CColorScaleAuto cs;
  cs.startAutomaticParameterCalculation();

  for (i = 0; i < mPopulation.size(); ++i)
    {
      cs.passValue(mObjectiveValues[i]);

      if (mObjectiveValues[i] < tmp_min)
        { tmp_min = mObjectiveValues[i]; min_index = i;}
    }

  cs.finishAutomaticParameterCalculation();
  //std::cout << std::endl;


  for (i = 0; i < mPopulation.size(); ++i)
    {

      //first scale the parameters to a unit box
      bool isOnBorder = false;
      std::vector<double> scaled_values; scaled_values.resize(mNumParameters);
      double p0 = 0; double p1 = 0; C_INT32 count = 0;
      C_INT32 j;

      for (j = 0; j < mNumParameters; ++j)
        {
          if (mIsLog[j])
            scaled_values[j] = (log(mPopulation[i]->operator[](j)) - log(mRangeMin[j])) / (log(mRangeMax[j]) - log(mRangeMin[j])) ;
          else
            scaled_values[j] = (mPopulation[i]->operator[](j) - mRangeMin[j]) / (mRangeMax[j] - mRangeMin[j]);

          if (scaled_values[j] < 0.01 || scaled_values[j] > 0.99)
            isOnBorder = true;

          if (j % 4 == 0)
            {p0 += scaled_values[j]; ++count;}

          if (j % 4 == 1)
            p1 += scaled_values[j];

          if (j % 4 == 2)
            p0 -= scaled_values[j];

          if (j % 4 == 3)
            p1 -= scaled_values[j];
        }

      //now update the graph

      if (mNumParameters > 2)
        {
          QGraphicsEllipseItem* gie = dynamic_cast<QGraphicsEllipseItem*>(mGraphicItems[mShiftX.size()][i]);

          if (gie)
            {
              gie->setX((p0 / count + 1) * 1.05  - 0.025);
              gie->setY((p1 / count + 1) * 1.05  - 0.025);
              gie->setBrush(cs.getColor(mObjectiveValues[i]));

              //highlight parameters on the border of the allowed space
              if (i == min_index)
                {
                  gie->setPen(QPen(QColor(0, 200, 0, 200), 0.01));
                  gie->setZValue(1.0);
                }
              else
                {
                  gie->setPen(isOnBorder ? QColor(200, 0, 0, 200) : QColor(0, 0, 0, 40));
                  gie->setZValue(0.0);
                }
            }
        }

      for (j = 0; j < mShiftX.size(); ++j) //loop over the different projections
        {
          QGraphicsEllipseItem* gie = dynamic_cast<QGraphicsEllipseItem*>(mGraphicItems[j][i]);

          if (gie)
            {
              gie->setX(scaled_values[mXIndex[j]] - 0.025);
              gie->setY(scaled_values[mYIndex[j]] - 0.025);
              gie->setBrush(cs.getColor(mObjectiveValues[i]));

              //highlight parameters on the border of the allowed space
              if (i == min_index)
                {
                  gie->setPen(QPen(QColor(0, 200, 0, 200), 0.01));
                  gie->setZValue(1.0);
                }
              else
                {
                  gie->setPen(isOnBorder ? QColor(200, 0, 0, 200) : QColor(0, 0, 0, 40));
                  gie->setZValue(0.0);
                }
            }
        }
    }

    setUpdatesEnabled(true);
    QWidget * viewport = mpGV->viewport();
    viewport->update();
}

