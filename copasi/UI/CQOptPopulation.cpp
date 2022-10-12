// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// the window containing the plot and buttons for supported operations

#include <QtSvg/QtSvg>

#include <QToolBar>
#include <QPrinter>
#include <QPixmap>
#include <QPicture>
#include <QtSvg/QSvgGenerator>
#include <QMutexLocker>
#include <QLabel>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>

#include "CQOptPopulation.h"

#include "copasi/UI/copasiui3window.h"
#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/qlayout/CQZoomableView.h"
#include "copasi/UI/CColorScale.h"
#include "copasi/resourcesUI/CQIconResource.h"
#include "copasi/optimization/COptPopulationMethod.h"
#include "copasi/optimization/COptTask.h"
#include "copasi/optimization/COptProblem.h"
#include "copasi/optimization/COptItem.h"

#include "copasi/utilities/CVersion.h"

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

#include <qwt_plot.h>
#include <qwt_scale_engine.h>

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
#include <qwt_plot_renderer.h>
#endif

#if QWT_VERSION < QT_VERSION_CHECK(6,0,0)
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

#include <QGraphicsEllipseItem>
class CQEllipseItem : public QGraphicsEllipseItem
{
public:
  explicit CQEllipseItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr)
    : QGraphicsEllipseItem(x, y, w, h, parent)
  {
  }

  ~CQEllipseItem()
  {
  }

protected:
  virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem* option, QWidget * widget = nullptr)
  {
    double scaleValue = scale();
    double m11 = painter->transform().m11();

    painter->save();
    painter->scale(scaleValue, scaleValue);

    QGraphicsEllipseItem::paint(painter, option, widget);

    painter->restore();
  }
};

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
  mDidAllocate(false),
  mInUpdate(false),
  initializing(false),
  mNumParameters(0),
  mDiameter(0.05),
  mMutex()
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

  mpLabel = new QLabel(this);
  connect(this, SIGNAL(setDebugText(QString)), mpLabel, SLOT(setText(QString)));
  statusBar()->addPermanentWidget(mpLabel);

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
  fileMenu->addAction(mpaSaveToFile);
  fileMenu->addSeparator();
  fileMenu->addAction(mpaCloseWindow);

  QMenu *viewMenu = menuBar()->addMenu("&View");
//  viewMenu->addAction(mpaShowAll);
//  viewMenu->addSeparator();
  static_cast<CQZoomableView*>(mpGV)->fillZoomMenu(viewMenu);
  viewMenu->addSeparator();
  viewMenu->addAction(mpaRefresh);
  viewMenu->addSeparator();
  viewMenu->addAction(mpaDecreaseCircle);
  viewMenu->addAction(mpaResetCircle);
  viewMenu->addAction(mpaIncreaseCircle);

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

  mpaSaveToFile = new QAction("Save Image", this);
  mpaSaveToFile->setShortcut(Qt::CTRL + Qt::Key_S);
  mpaSaveToFile->setToolTip("Save as Image");
  connect(mpaSaveToFile, SIGNAL(triggered()), this, SLOT(slotSaveImage()));

  mpaCloseWindow = new QAction("Close", this);
  mpaCloseWindow->setObjectName("close");
  mpaCloseWindow->setShortcut(Qt::CTRL + Qt::Key_W);
  connect(mpaCloseWindow, SIGNAL(triggered()), this, SLOT(slotCloseWindow()));

  mpaRefresh = new QAction("Repaint (Full refresh)", this);
  connect(mpaRefresh, SIGNAL(triggered()), this, SLOT(slotFullRefresh()));
  mpaResetCircle = new QAction("Reset Circle", this);
  connect(mpaResetCircle, SIGNAL(triggered()), this, SLOT(slotResizeCircle()));
  mpaDecreaseCircle = new QAction("Decrease Circle", this);
  connect(mpaDecreaseCircle, SIGNAL(triggered()), this, SLOT(slotResizeCircle()));
  mpaIncreaseCircle = new QAction("Increase Circle", this);
  connect(mpaIncreaseCircle, SIGNAL(triggered()), this, SLOT(slotResizeCircle()));
}

void CQOptPopulation::setCircle(qreal diameter)
{
  mDiameter = diameter;
  mGraphInitialized = false;
  mDataInitialized = false;
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
  QString fileType = QFileInfo(fileName).suffix();

  if (fileType == "pdf")
    {
      QPrinter printer(QPrinter::HighResolution);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setOutputFileName(fileName);
      QPainter painter(&printer);
      painter.setRenderHints(
        QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
      mpGS->render(&painter, QRect(), mpGS->itemsBoundingRect());
      painter.end();
    }
  else if (fileType == "svg")
    {
      QRectF rect = mpGS->itemsBoundingRect();
      QSvgGenerator generator;
      generator.setDescription(QString("Exported using COPASI: %1").arg(CVersion::VERSION.getVersion().c_str()));
      generator.setFileName(fileName);
      generator.setViewBox(rect);
      generator.setSize(QSize(rect.width(), rect.height()));
      QPainter painter;
      painter.begin(&generator);
      mpGS->render(&painter);
      painter.end();
    }
  else
    {
      const int scale = 2;
      QImage image(QSize(width() * scale, height() * scale), QImage::Format_ARGB32);
      QPainter painter(&image);
      painter.setRenderHints(
        QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
      mpGS->render(&painter, image.rect(), mpGS->itemsBoundingRect());
      painter.end();
      image.save(fileName);
    }
}

void CQOptPopulation::slotSaveData()
{
}

void CQOptPopulation::slotSaveImage()
{
  QString fileName = CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                     CopasiFileDialog::getDefaultFileName(".pdf"), "PDF Files (*.pdf);;PNG Files (*.png);;SVG Files (*.svg)", "Save as Image", new QString);

  if (fileName.isEmpty())
    return;

  saveToFile(fileName);
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
  mGraphInitialized = false;
  bool success = true;

  mDidAllocate = false;

  if (!mpPopulationMethod)
    {
      mPopulation = std::vector< CVector< C_FLOAT64 > * > {};
      mObjectiveValues = std::vector< C_FLOAT64 >();
      mDidAllocate = true;
    }

  mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime();

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

void CQOptPopulation::slotFullRefresh()
{
  mGraphInitialized = false;
  emit updateSignal();
}

void CQOptPopulation::slotResizeCircle()
{
  QObject * pSender = sender();

  if (pSender == mpaResetCircle)
    setCircle(0.05);

  if (pSender == mpaDecreaseCircle)
    setCircle(mDiameter / 2.0);

  if (pSender == mpaIncreaseCircle)
    setCircle(mDiameter * 2.0);
}

void CQOptPopulation::closeEvent(QCloseEvent *closeEvent)
{
  mpMainWindow->removeWindow(this);
  mpHandler->removeInterface(this);
}

std::vector< C_FLOAT64 > to_std_vector(const CVector<C_FLOAT64>& other)
{
  std::vector< C_FLOAT64 > result(other.begin(), other.end());
  return result;
}

void CQOptPopulation::output(const Activity& activity)
{

  if (activity == COutputInterface::Activity(COutputInterface::BEFORE))
    {
      if (mDidAllocate)
        {
          for (auto * item : mPopulation)
            delete item;

          mPopulation.clear();
          mObjectiveValues.clear();
        }

      if (!mpPopulationMethod)
        {
          mPopulation = std::vector< CVector< C_FLOAT64 >* > {};
          mObjectiveValues = std::vector< C_FLOAT64 >();
          mDidAllocate = true;
        }
    }

  if (activity != COutputInterface::Activity(COutputInterface::MONITORING))
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

  QMutexLocker lock(&mMutex);

  //copy the data
  if (mpPopulationMethod)
    {
      mPopulation = mpPopulationMethod->getPopulation();
      mObjectiveValues = to_std_vector(mpPopulationMethod->getObjectiveValues());
    }
  else
    {
      const auto* current = mpSourceMethod->getCurrentParameters();

      if (current != NULL)
        {
          double lastObjective = mObjectiveValues.empty() ? std::numeric_limits< double >::infinity() : mObjectiveValues.back();

          if (lastObjective != mpSourceMethod->getCurrentValue())
            {
              mPopulation.push_back(new CVector< C_FLOAT64 >(*current));
              mObjectiveValues.push_back(mpSourceMethod->getCurrentValue());
            }

          if (mPopulation.size() > mMaxIterations)
            {
              mPopulation.erase(mPopulation.begin());
              mObjectiveValues.erase(mObjectiveValues.begin());
            }
        }
    }

  unsigned C_INT32 i;

  //Color scaling
  double tmp_min = std::numeric_limits<double>::infinity();

  mCS.startAutomaticParameterCalculation();

  for (i = 0; i < mPopulation.size(); ++i)
    {
      double current = mObjectiveValues[i];
      mCS.passValue(current);

      if (current < tmp_min)
        {
          tmp_min = current;
          mMinIndex = i;
        }
    }

  mCS.finishAutomaticParameterCalculation();

  mCounter++;

  emit setDebugText(QString("min: %1, total: %2").arg(tmp_min).arg(mPopulation.size()));
  emit updateSignal();
}

void updateItem(QGraphicsEllipseItem * gie, double x, double y, QColor color, bool isBest, bool isOnBorder)
{
  if (!gie)
    return;

  gie->setX(x);
  gie->setY(y);
  gie->setBrush(color);

  //highlight parameters on the border of the allowed space
  if (isBest)
    {
      gie->setPen(QPen(QColor(0, 200, 0, 200), 0.01));
      gie->setZValue(1.0);
    }
  else
    {
      gie->setPen(QPen(isOnBorder ? QColor(200, 0, 0, 200) : QColor(0, 0, 0, 40), 0));
      gie->setZValue(0.0);
    }

  gie->setVisible(true);
}

QString vec_to_string(CVector<C_FLOAT64>* pVec)
{
  if (!pVec)
    return "null";

  if (pVec->size() == 0)
    return "empty";

  QString result = QString::number(pVec->operator[](0));

  for (int i = 1; i < pVec->size(); ++i)
    {
      result.append(QString(", %1").arg(pVec->operator[](i)));
    }

  return result;
}

void CQOptPopulation::update()
{

  if (CCopasiTimeVariable::getCurrentWallTime() < mNextPlotTime)
    return;

  if (mpSourceMethod == NULL)
    return;

  QMutexLocker lock(&mMutex);
  mInUpdate = true;
  setUpdatesEnabled(false);

  size_t numMembers = mPopulation.size();

  if (!mGraphInitialized)
    {

      if (!mpPopulationMethod)
        numMembers = mMaxIterations;

      mpGS->clear();

      QGraphicsRectItem* rect = mpGS->addRect(-0, -0, 1, 1, QPen(Qt::black, 0));
      rect->setBrush(QColor(220, 220, 220));

      C_INT32 numProjections = (mNumParameters + 1) / 2;
      mShiftX.resize(numProjections);
      mShiftY.resize(numProjections);
      mXIndex.resize(numProjections);
      mYIndex.resize(numProjections);
      mGraphicItems.resize(numProjections + 1); //extra space for the combined view
      mLineItems.resize(numProjections + 1); //extra space for the combined view

      //if there's more than 2 parameters, create the combined view
      if (mNumParameters > 2)
        {
          QGraphicsRectItem* rect = mpGS->addRect(-2.2, 0, 2.1, 2.1, QPen(Qt::black, 0));
          rect->setBrush(QColor(230, 230, 250));

          mGraphicItems[numProjections].resize(numMembers);
          mLineItems[numProjections].resize(numMembers);

          unsigned C_INT32 i;

          for (i = 0; i < numMembers; ++i)
            {
              //QGraphicsEllipseItem* ei = mpGS->addEllipse(-2.2, 0, 0.05, 0.05, QPen(Qt::black, 0));
              QGraphicsEllipseItem * ei = mpGS->addEllipse(-2.2, 0, mDiameter, mDiameter, QPen(Qt::black, 0));
              //QGraphicsEllipseItem * ei = new CQEllipseItem(-2.2, 0, mDiameter, mDiameter);
              //mpGS->addItem(ei);
              mGraphicItems[numProjections][i] = ei;
              ei->setBrush(QColor(10, 100, 10));
              ei->setPen(QPen(QColor(0, 0, 0), 0));
              ei->setVisible(false);

              QGraphicsLineItem * line = mpGS->addLine(0.0, 0.0, 0.01, 0.01, QPen(Qt::gray, 0, Qt::DotLine));
              mLineItems[numProjections][i] = line;
              line->setVisible(false);
            }
        }

      C_INT32 j;

      for (j = 0; j < numProjections; ++j)
        {
          mShiftX[j] = (j / 2) * 1.1;
          mShiftY[j] = (j % 2) * 1.1;
          mXIndex[j] = j * 2;
          mYIndex[j] = (j * 2 + 1) % mNumParameters;
          QGraphicsRectItem* rect = mpGS->addRect(mShiftX[j], mShiftY[j], 1, 1, QPen(Qt::black, 0));
          rect->setBrush(QColor(240, 240, 240));

          mGraphicItems[j].resize(numMembers);
          mLineItems[j].resize(numMembers);

          unsigned C_INT32 i;

          for (i = 0; i < numMembers; ++i)
            {

              //QGraphicsEllipseItem* ei = mpGS->addEllipse(mShiftX[j], mShiftY[j], 0.05, 0.05, QPen(Qt::black, 0));
              QGraphicsEllipseItem * ei = mpGS->addEllipse(mShiftX[j], mShiftY[j], mDiameter, mDiameter, QPen(Qt::black, 0));
              //QGraphicsEllipseItem * ei = new CQEllipseItem(mShiftX[j], mShiftY[j], mDiameter, mDiameter);
              //mpGS->addItem(ei);
              mGraphicItems[j][i] = ei;
              ei->setBrush(QColor(10, 100, 10));
              ei->setPen(QPen(QColor(0, 0, 0), 0));
              ei->setVisible(false);

              QGraphicsLineItem * line = mpGS->addLine(0.0, 0.0, 0.01, 0.01, QPen(Qt::gray, 0, Qt::DotLine));
              mLineItems[j][i] = line;
              line->setVisible(false);
            }
        }

      static_cast<CQZoomableView*>(mpGV)->slotFitOnScreen();

      numMembers = mPopulation.size();

      mGraphInitialized = true;
    }

  //--------------------------------

  unsigned C_INT32 i;
  CCopasiTimeVariable Delta = CCopasiTimeVariable::getCurrentWallTime();

  std::vector< double > last_values;
  //std::vector< std::vector< double > > last_values;
  //last_values.resize(numMembers);

  QPointF last_point;

  for (i = 0; i < numMembers; ++i)
    {

      //first scale the parameters to a unit box
      bool isOnBorder = false;
      std::vector<double> scaled_values; scaled_values.resize(mNumParameters);
      double p0 = 0; double p1 = 0; C_INT32 count = 0;
      C_INT32 j;

      CVector< C_FLOAT64 >* current = mPopulation[i];

      for (j = 0; j < mNumParameters; ++j)
        {
          if (mIsLog[j])
            scaled_values[j] = (log(current->operator[](j)) - log(mRangeMin[j])) / (log(mRangeMax[j]) - log(mRangeMin[j]));
          else
            scaled_values[j] = (current->operator[](j) - mRangeMin[j]) / (mRangeMax[j] - mRangeMin[j]);

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

          if (!mpPopulationMethod && i > 1)
            {
              QGraphicsLineItem * line = dynamic_cast< QGraphicsLineItem * >(mLineItems[mShiftX.size()][i]);
              line->setLine(-2.2 + last_point.x(), last_point.y(),
                            -2.2 + (p0 / count + 1) * 1.05,
                            (p1 / count + 1) * 1.05);
              line->setVisible(true);
            }

          QGraphicsEllipseItem* gie = dynamic_cast<QGraphicsEllipseItem*>(mGraphicItems[mShiftX.size()][i]);

          if (gie)
            gie->setToolTip(QString("obj: %1, (%2)").arg(mObjectiveValues[i]).arg(vec_to_string(current)));

          updateItem(gie,
                     (p0 / count + 1) * 1.05 - mDiameter / 2.0,
                     (p1 / count + 1) * 1.05 - mDiameter / 2.0,
                     mCS.getColor(mObjectiveValues[i]),
                     i == mMinIndex,
                     isOnBorder);

          last_point.setX((p0 / count + 1) * 1.05);
          last_point.setY((p1 / count + 1) * 1.05);
        }

      for (j = 0; j < (int)mShiftX.size(); ++j) //loop over the different projections
        {
          if (!mpPopulationMethod && i > 1)
            {
              QGraphicsLineItem * line = dynamic_cast< QGraphicsLineItem  * >(mLineItems[j][i]);
              line->setLine(mShiftX[j] + last_values[mXIndex[j]], mShiftY[j]  + last_values[mYIndex[j]],
                            mShiftX[j] + scaled_values[mXIndex[j]], mShiftY[j] + scaled_values[mYIndex[j]]);
              line->setVisible(true);
            }

          QGraphicsEllipseItem* gie = dynamic_cast<QGraphicsEllipseItem*>(mGraphicItems[j][i]);

          updateItem(gie,
                     scaled_values[mXIndex[j]] - mDiameter / 2.0,
                     scaled_values[mYIndex[j]] - mDiameter / 2.0,
                     mCS.getColor(mObjectiveValues[i]),
                     i == mMinIndex,
                     isOnBorder);

          if (gie) gie->setToolTip(QString("obj: %1, (%2)").arg(mObjectiveValues[i]).arg(vec_to_string(current)));
        }

      last_values = scaled_values;
    }

  setUpdatesEnabled(true);
  mInUpdate = false;
  QWidget * viewport = mpGV->viewport();
  viewport->update();

  Delta = CCopasiTimeVariable::getCurrentWallTime() - Delta;
  mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime() + 3 * Delta.getMicroSeconds();
}
