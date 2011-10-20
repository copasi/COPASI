// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.cpp,v $
//   $Revision: 1.105 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/20 14:06:21 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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
#include "CQLayoutMainWindow.h"

#include <QAction>
#include <QComboBox>
#include <QFrame>
#include <QLabel>
#include <QLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QMenu>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <QToolBar>
#include <qwt_slider.h>
#include <QGridLayout>
#include <QPixmap>
#include <QCloseEvent>

#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/CopasiFileDialog.h"
#include "copasi/layout/CLBase.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "CQCurrentValueTable.h"
#include "CQGLNetworkPainter.h"
#include "CQGLViewport.h"
#include "FontChooser.h"
#include "NodeSizePanel.h"
#include "ParaPanel.h"
#include "CQPlayerControlWidget.h"
#ifdef FRAMEBUFFER_SCREENSHOTS
#include "CQScreenshotOptionsDialog.h"
#endif // FRAMEBUFFER_SCREENSHOTS
#ifndef USE_CRENDER_EXTENSION
#include "load_data.xpm"
#endif // USE_CRENDER_EXTENSION

#ifdef DEBUG_UI
#include <QtDebug>
#endif

using namespace std;

const char* const CQLayoutMainWindow::ZOOM_FACTOR_STRINGS[] = {"1%", "2%", "3%", "4%", "5%", "10%", "20%", "30%", "40%", "50%", "100%", "150%", "200%", "300%", "400%", "500%", "1000%"};
const double CQLayoutMainWindow::ZOOM_FACTORS[] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 10.0};


#ifndef USE_CRENDER_EXTENSION
CQLayoutMainWindow::CQLayoutMainWindow(CLayout* pLayout):
    QMainWindow(NULL)
#else
CQLayoutMainWindow::CQLayoutMainWindow(QWidget* pParent):
    QFrame(pParent)
#endif // USE_CRENDER_EXTENSION
    , mpVisParameters(new CVisParameters)
    , mpParaPanel(new CQParaPanel)
    , mpValTable(new CQCurrentValueTable)
    , mpMainBox(new QFrame(this))
    , mpSplitter(new QSplitter(Qt::Horizontal, this->mpMainBox))
    , mpGLViewport(NULL)
    , mpTimeSlider(new QwtSlider(NULL, Qt::Horizontal, QwtSlider::BottomScale, QwtSlider::BgTrough))
    , mpFrame(new QFrame)
    , mpInfoBox(new QFrame)
    , mpControlWidget(new CQPlayerControlWidget)
    , mDataPresent(false)
    , mCurrentPlace(QString::null)
    , mpZoomActionGroup(new QActionGroup(this))
#ifdef USE_CRENDER_EXTENSION
    , mpLayout(NULL)
#else
    , mpLayout(pLayout)
#endif // USE_CRENDER_EXTENSION
{
#ifndef USE_CRENDER_EXTENSION
  this->setWindowTitle(tr("Reaction network graph"));
  this->setCentralWidget(mpMainBox);
#else
  this->QFrame::setLayout(new QVBoxLayout);
  this->layout()->addWidget(this->mpMainBox);
#endif // USE_CRENDER_EXTENSION
  this->mpMainBox->setLayout(new QVBoxLayout());

  // create split window with parameter panel and graph panel
  this->mpMainBox->layout()->addWidget(this->mpSplitter);

  this->mpSplitter->addWidget(this->mpInfoBox);
  this->mpInfoBox->setLayout(new QVBoxLayout);

  this->mpInfoBox->layout()->addWidget(this->mpParaPanel);
  this->mpInfoBox->layout()->addWidget(this->mpValTable);

  // Create OpenGL widget
  // we initialize it here because the parent has to be present
  this->mpGLViewport = new CQGLViewport(this->mpSplitter);
  this->mpGLViewport->setWindowTitle("Network layout");
  this->mpSplitter->addWidget(this->mpGLViewport);

  if (this->mpLayout != NULL)
    {
      this->mpGLViewport->createGraph(this->mpLayout); // create local data structures
    }

  this->mpSplitter->setStretchFactor(this->mpSplitter->indexOf(this->mpInfoBox), 0);
  this->mpSplitter->setStretchFactor(this->mpSplitter->indexOf(this->mpGLViewport), 1);

  this->mpMainBox->layout()->addWidget(this->mpFrame);

  connect(this->mpControlWidget, SIGNAL(play()), this, SLOT(startAnimation()));
  connect(this->mpControlWidget, SIGNAL(pause()), this, SLOT(pauseAnimation()));
  connect(this->mpControlWidget, SIGNAL(stop()), this, SLOT(stopAnimation()));
  connect(this->mpControlWidget, SIGNAL(forward()), this, SLOT(forwardAnimation()));
  connect(this->mpControlWidget, SIGNAL(backward()), this, SLOT(backwardAnimation()));
  connect(this->mpControlWidget, SIGNAL(step_backward()), this, SLOT(stepBackwardAnimation()));
  connect(this->mpControlWidget, SIGNAL(step_forward()), this, SLOT(stepForwardAnimation()));

  this->mpTimeSlider->setRange(0, 100, 1, 0);
  this->mpTimeSlider->setValue(0.0);
  this->mpTimeSlider->setEnabled(false);

  this->mpTimeSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  this->mpFrame->setFixedHeight(68);
  connect(this->mpTimeSlider, SIGNAL(valueChanged(double)),
          this, SLOT(showStep(double)));

  QGridLayout* pGridLayout = new QGridLayout(NULL);
  this->mpFrame->setLayout(pGridLayout);
  pGridLayout->addWidget(this->mpTimeSlider, 1, 1, 2, 1, Qt::AlignTop);
  pGridLayout->addWidget(this->mpControlWidget, 0, 0, 4, 1, Qt::AlignTop);
  QSpacerItem* pSpacer = new QSpacerItem(20, 20);
  pGridLayout->addItem(pSpacer, 1, 0);

#ifndef USE_CRENDER_EXTENSION
  loadData(); // try to load data (if already present)
  // the action have to be created before mpLoadDataAction is used below
  // the menus have to be created after the player control widget is created
  // since actions from the player control are added to the menu
  // the actions have to be created before the menus since some action go into
  // menus
  createActions();
  createMenus();

  this->mpToolbar = this->addToolBar(tr("layout toolbar"));
  this->mpToolbar->addAction(this->mpLoadDataAction);
  this->mpToolbar->addSeparator();
  QLabel* pLabel = new QLabel("zoom factor:");
  this->mpToolbar->addWidget(pLabel);
  this->mpZoomComboBox = new QComboBox(NULL);
  this->mpZoomComboBox->setWindowTitle("zoom box");
  this->mpToolbar->addWidget(this->mpZoomComboBox);

  int defaultIndex = -1;
  unsigned int i, iMax = sizeof(CQLayoutMainWindow::ZOOM_FACTOR_STRINGS) / sizeof(char*);

  for (i = 0; i < iMax; ++i)
    {
      this->mpZoomComboBox->addItem(QString(CQLayoutMainWindow::ZOOM_FACTOR_STRINGS[i]));

      if (std::string(CQLayoutMainWindow::ZOOM_FACTOR_STRINGS[i]) == std::string("100%"))
        {
          defaultIndex = i;
        }
    }

  // set 100% as the default zoom factor
  assert(defaultIndex != -1);
  this->mpZoomComboBox->setCurrentIndex(defaultIndex);
  this->mpZoomComboBox->setEditable(FALSE);
  connect(this->mpZoomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotActivated(int)));
  connect(this->mpGLViewport->getPainter() , SIGNAL(signalZoomIn()), this, SLOT(slotZoomIn()));
  connect(this->mpGLViewport->getPainter() , SIGNAL(signalZoomOut()), this, SLOT(slotZoomOut()));
#endif // USE_CRENDER_EXTENSION
  connect(this->mpValTable , SIGNAL(valueChanged(int)), this, SLOT(parameterTableValueChanged(int)));
  this->mLooping = false;

  this->setTabOrder(this->mpGLViewport, this->mpToolbar);
#ifndef USE_CRENDER_EXTENSION
  this->setTabOrder(this->mpToolbar, this->mpParaPanel);
#endif // USE_CRENDER_EXTENSION
  this->setTabOrder(this->mpParaPanel, this->mpValTable);
  this->setTabOrder(this->mpValTable, this->mpControlWidget);
}

void CQLayoutMainWindow::parameterTableValueChanged(int row)
{
  std::string key = this->mpValTable->getKeyForRow(row);
  bool value = this->mpValTable->getValueForRow(row);

  if (value == true)
    {
      this->addItemInAnimation(key);
    }
  else
    {
      this->removeItemInAnimation(key);
    }

  // redraw the layout if we are in animation mode
  if (this->mpGLViewport->isCircleMode())
    {
      this->mpGLViewport->updateWidget();
    }
}

bool CQLayoutMainWindow::getAnimationRunning()
{
  if (mpVisParameters != NULL)
    {
      return mpVisParameters->mAnimationRunning;
    }
  else
    return false;
}

void CQLayoutMainWindow::setAnimationRunning(bool animationRunningP)
{
  if (mpVisParameters != NULL)
    {
      mpVisParameters->mAnimationRunning = animationRunningP;
    }
}

C_FLOAT64 CQLayoutMainWindow::getMinNodeSize()
{
  C_FLOAT64 minNodeSize = 10.0;

  if (mpVisParameters != NULL)
    {

      minNodeSize = mpVisParameters->mMinNodeSize;
    }

  return minNodeSize;
}

C_FLOAT64 CQLayoutMainWindow::getMaxNodeSize()
{
  C_FLOAT64 maxNodeSize = 100.0;

  if (mpVisParameters != NULL)
    {
      maxNodeSize = mpVisParameters->mMaxNodeSize;
    }

  return maxNodeSize;
}

void CQLayoutMainWindow::setMinNodeSize(C_FLOAT64 minNdSize)
{
  if (mpVisParameters != NULL)
    mpVisParameters->mMinNodeSize = minNdSize;
}

void CQLayoutMainWindow::setMaxNodeSize(C_FLOAT64 maxNdSize)
{
  if (mpVisParameters != NULL)
    mpVisParameters->mMaxNodeSize = maxNdSize;
}

C_INT16 CQLayoutMainWindow::getFontSize()
{
  return mpGLViewport->getPainter()->getFontSize();
}

C_INT32 CQLayoutMainWindow::getStepsPerSecond()
{
  if (mpVisParameters != NULL)
    {
      return mpVisParameters->mStepsPerSecond;
    }
  else
    return 2;
}

void CQLayoutMainWindow::setStepsPerSecond(C_INT16 val)
{
  if (mpVisParameters != NULL)
    {
      mpVisParameters->mStepsPerSecond = val;
    }
}

size_t CQLayoutMainWindow::getCurrentStep()
{
  return (size_t) this->mpTimeSlider->value();
}

CVisParameters::SCALING_MODE CQLayoutMainWindow::getScalingMode()
{
  if (mpVisParameters != NULL)
    {
      return mpVisParameters->mScalingMode;
    }
  else
    return CVisParameters::INDIVIDUAL_SCALING;
}

CVisParameters::MAPPING_MODE CQLayoutMainWindow::getMappingMode()
{
  if (mpVisParameters != NULL)
    {
      return mpVisParameters->mMappingMode;
    }
  else
    return CVisParameters::SIZE_DIAMETER_MODE; // default mode
}

#ifndef USE_CRENDER_EXTENSION
void CQLayoutMainWindow::createActions()
{
  //   mpOpenSBMLFile = new QAction("SBML",
  //                              "Load SBML file",
  //                              CTRL + Key_F,
  //                              this);
  //   mpOpenSBMLFile->setStatusTip("Load SBML file with/without layout");
  //   connect(mpOpenSBMLFile, SIGNAL(activated()) , this, SLOT(loadSBMLFile()));

  //   openDataFile = new QAction("data",
  //                              "Load Simulation Data",
  //                              CTRL + Key_D,
  //                              this);
  //   openDataFile->setStatusTip("Load simulation data");
  //   connect(openDataFile, SIGNAL(activated()), this, SLOT(loadData()));

  mpCloseAction = new QAction("Close Window", this);
  mpCloseAction->setShortcut(Qt::CTRL + Qt::Key_W);
  mpCloseAction->setStatusTip("Close Layout Window");
  connect(mpCloseAction, SIGNAL(triggered()), this, SLOT(closeApplication()));

  mDataPresent = false;

  mpCreatePicture = new QAction("Create image", this);
  mpCreatePicture->setShortcut(Qt::CTRL + Qt::Key_I);
  mpCreatePicture->setStatusTip("create a picture from the current view and save it to file");
  connect(mpCreatePicture, SIGNAL(triggered()), this, SLOT(saveImage()));

  mpRectangularShape = new QAction("Rectangle", this);
  mpRectangularShape->setShortcut(Qt::CTRL + Qt::Key_R);
  mpRectangularShape->setStatusTip("Show labels as rectangles");
  connect(mpRectangularShape, SIGNAL(triggered()), this, SLOT(mapLabelsToRectangles()));

  mpCircularShape = new QAction("Circle", this);
  mpCircularShape->setShortcut(Qt::CTRL + Qt::Key_C);
  mpCircularShape->setStatusTip("Show labels as circles");
  connect(mpCircularShape, SIGNAL(triggered()), this, SLOT(mapLabelsToCircles()));

  mpMimaNodeSizes = new QAction("Set Min/Max Node Sizes", this);
  mpMimaNodeSizes->setShortcut(Qt::CTRL + Qt::Key_M);
  mpMimaNodeSizes->setToolTip("Change Min/Max for node sizes within animation");
  connect(mpMimaNodeSizes, SIGNAL(triggered()), this, SLOT(changeMinMaxNodeSizes()));

  mpSFontSize = new QAction("Set Font Size", this);
  mpSFontSize->setShortcut(Qt::CTRL + Qt::Key_F);
  mpSFontSize->setToolTip("Change the font size of the node labels in the graph view");
  connect(mpSFontSize, SIGNAL(triggered()), this, SLOT(changeFontSize()));

  mpLoadDataAction = new QAction(QPixmap(load_data_xpm), "Load data", this);
  connect(this->mpLoadDataAction, SIGNAL(triggered()), this, SLOT(loadData()));
}

void CQLayoutMainWindow::createMenus()
{
  this->mpFileMenu = this->menuBar()->addMenu(tr("File"));
  this->mpFileMenu->addSeparator();
  this->mpFileMenu->addAction(this->mpCloseAction);

  // play menu
  this->mpPlayMenu = this->menuBar()->addMenu("Play");
  this->mpPlayMenu->addAction(this->mpControlWidget->getPlayAction());
  this->mpPlayMenu->addAction(this->mpControlWidget->getPauseAction());
  this->mpPlayMenu->addAction(this->mpControlWidget->getStopAction());
  this->mpPlayMenu->addAction(this->mpControlWidget->getForwardAction());
  this->mpPlayMenu->addAction(this->mpControlWidget->getBackwardAction());
  this->mpPlayMenu->addAction(this->mpControlWidget->getStepForwardAction());
  this->mpPlayMenu->addAction(this->mpControlWidget->getStepBackwardAction());
  this->mpPlayMenu->addSeparator();
  this->mpLoopItemAction = this->mpPlayMenu->addAction("loop animation");
  this->mpLoopItemAction->setCheckable(true);
  this->mpLoopItemAction->setChecked(false);
  connect(this->mpLoopItemAction, SIGNAL(toggled(bool)) , this, SLOT(slotLoopActivated(bool)));
  this->mpPlayMenu->addSeparator();
  this->mpPlayMenu->addAction(this->mpLoadDataAction);

  // view menu
  this->mpViewMenu = this->menuBar()->addMenu("View");
  this->mpParameterTableAction = this->mpViewMenu->addAction("parameters");
  this->mpParameterTableAction->setCheckable(true);
  this->mpParameterTableAction->setChecked(true);
  connect(this->mpParameterTableAction, SIGNAL(toggled(bool)), this, SLOT(slotParameterTableToggled(bool)));
  this->mpValueTableAction = this->mpViewMenu->addAction("value table");
  this->mpValueTableAction->setCheckable(true);
  this->mpValueTableAction->setChecked(true);
  connect(this->mpValueTableAction, SIGNAL(toggled(bool)), this, SLOT(slotValueTableToggled(bool)));
  QAction* pAction = this->mpViewMenu->addAction("player control");
  pAction->setCheckable(true);
  pAction->setChecked(true);
  connect(pAction, SIGNAL(toggled(bool)), this, SLOT(slotPlayerControlToggled(bool)));
  pAction = this->mpViewMenu->addAction("toolbar");
  pAction->setCheckable(true);
  pAction->setChecked(true);
  mpViewMenu->addSeparator();
  connect(pAction, SIGNAL(toggled(bool)), this, SLOT(slotToolbarToggled(bool)));
  mpViewMenu->addAction("Reset View", this, SLOT(slotResetView()));
  this->mpZoomMenu = this->mpViewMenu->addMenu("Zoom");
  pAction = this->mpZoomActionGroup->addAction("1%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("2%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("3%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("4%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("5%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("10%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("20%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("30%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("40%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("50%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("100%");
  pAction->setCheckable(true);
  pAction->setChecked(true);
  pAction = this->mpZoomActionGroup->addAction("150%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("200%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("300%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("400%");
  pAction->setCheckable(true);
  pAction = this->mpZoomActionGroup->addAction("500%");
  pAction->setCheckable(true);
  connect(this->mpZoomActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(slotZoomItemActivated(QAction*)));
  this->mpZoomMenu->addActions(this->mpZoomActionGroup->actions());
  this->mpViewMenu->addSeparator();
  this->mpViewMenu->addAction(this->mpCreatePicture);

  this->mpOptionsMenu = this->menuBar()->addMenu("Options");
  this->mpLabelShapeMenu = this->mpOptionsMenu->addMenu("Shape of Label");
  this->mpLabelShapeMenu->addAction(this->mpRectangularShape);
  this->mpLabelShapeMenu->addAction(this->mpCircularShape);
  this->mpOptionsMenu->addAction(this->mpMimaNodeSizes);
  this->mpOptionsMenu->addAction(this->mpSFontSize);
}
#endif // USE_CRENDER_EXTENSION

void CQLayoutMainWindow::loadSBMLFile()
{
  CListOfLayouts *pLayoutList;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  if ((*CCopasiRootContainer::getDatamodelList())[0] != NULL)
    {
      pLayoutList = (*CCopasiRootContainer::getDatamodelList())[0]->getListOfLayouts();
    }
  else
    pLayoutList = NULL;

  mpGLViewport = new CQGLViewport(mpSplitter);

  if (pLayoutList != NULL)
    {
      CLayout * pLayout;

      if (pLayoutList->size() > 0)
        {
          pLayout = (*pLayoutList)[0];
          mpGLViewport->createGraph(pLayout); // create local data structures
        }
    }
}

void CQLayoutMainWindow::mapLabelsToCircles()
{
  if (mpGLViewport->getPainter() != NULL)
    {
      mpGLViewport->getPainter()->mapLabelsToCircles();

      if (mpGLViewport->getPainter()->getNumberOfSteps() > 0)
        showStep(this->mpTimeSlider->value());
    }
}

void CQLayoutMainWindow::mapLabelsToRectangles()
{
  if (mpGLViewport->getPainter() != NULL)
    {
      mpGLViewport->getPainter()->mapLabelsToRectangles();
      mpGLViewport->getPainter()->updateGL();
    }
}

void CQLayoutMainWindow::changeMinMaxNodeSizes()
{
  NodeSizePanel *panel = new NodeSizePanel(this);
  panel->exec();
}

void CQLayoutMainWindow::changeFontSize()
{
  // choose new font size (setting of size will be invoked from FontChooser panel
  FontChooser *fCh = new FontChooser(this);
  fCh->exec();
}

void CQLayoutMainWindow::loadData()
{
  bool successfulP = mpGLViewport->getPainter()->createDataSets();

  if (successfulP)
    {
      // set the number of steps in the control widget and place the current
      // step at 0
      this->mpControlWidget->setCurrentStep(0);
      this->mpTimeSlider->setEnabled(true);
      this->mDataPresent = true;
      mpParaPanel->enableStepNumberChoice();
      size_t maxVal = mpGLViewport->getPainter()->getNumberOfSteps();
      this->mpTimeSlider->setRange(0, maxVal - 1);
      this->mpControlWidget->setNumSteps(maxVal);
      mpGLViewport->getPainter()->updateGL();
      CQGLNetworkPainter* pPainter = this->mpGLViewport->getPainter();

      if (pPainter->getNumberOfSteps() > 1)
        {
          this->mpParaPanel->enableParameterChoice();
          this->mpParaPanel->enableStepNumberChoice();
          this->mpParaPanel->enableModeChoice();

          if (pPainter->isCircleMode())
            {
              showStep(this->mpTimeSlider->value());
            }
        }
      else
        {
          this->mpParaPanel->disableParameterChoice();
          this->mpParaPanel->disableStepNumberChoice();
          this->mpParaPanel->disableModeChoice();
        }
    }
}

void CQLayoutMainWindow::insertValueTable(CDataEntity dataSet)
{
  int i = 0;
  std::string key, name;
  C_FLOAT64 val;
  mpValTable->setNumRows((int) dataSet.getNumberOfElements());
  mpValTable->setNumCols(2);
  disconnect(this->mpValTable , SIGNAL(valueChanged(int)), this, SLOT(parameterTableValueChanged(int)));

  while ((key = mpGLViewport->getPainter()->getNodeNameEntry(i)) != "")
    {
      name = this->mpGLViewport->getPainter()->getNameForNodeKey(key);
      val = dataSet.getOrigValueForSpecies(key); // would be (- DBL_MAX) if key not present
      mpValTable->setRowInTable(i, key, name, val);
      i++;
    }

  connect(this->mpValTable , SIGNAL(valueChanged(int)), this, SLOT(parameterTableValueChanged(int)));
}

void CQLayoutMainWindow::updateValueTable(CDataEntity dataSet)
{
  int i = 0;
  std::string key, name;
  C_FLOAT64 val;
  disconnect(this->mpValTable , SIGNAL(valueChanged(int)), this, SLOT(parameterTableValueChanged(int)));

  while ((key = mpGLViewport->getPainter()->getNodeNameEntry(i)) != "")
    {
      name = mpGLViewport->getPainter()->getNameForNodeKey(key);
      val = dataSet.getOrigValueForSpecies(key); // would be (- DBL_MAX) if key not present

      if (mpValTable->numRows() > i)
        {
          mpValTable->updateRowInTable(i, val);
        }

      i++;
    }

  connect(this->mpValTable , SIGNAL(valueChanged(int)), this, SLOT(parameterTableValueChanged(int)));
}

// adds the item given by s to the list of items to animate (no change, if it is already present)
void CQLayoutMainWindow::addItemInAnimation(std::string key)
{
  mpGLViewport->getPainter()->setItemAnimated(key, true);
}

// removes the item given by s from the list of items to animate (no change, if it is not present in the list)
void CQLayoutMainWindow::removeItemInAnimation(std::string key)
{
  mpGLViewport->getPainter()->setItemAnimated(key, false);
}

void CQLayoutMainWindow::showAnimation()
{
  startAnimation();
}

void CQLayoutMainWindow::startAnimation()
{
  if (!this->mDataPresent)
    this->loadData(); // look for data

  if (this->mDataPresent)
    {// only if time series data present
      this->mpVisParameters->mAnimationRunning = true;
      this->mpTimeSlider->setEnabled(false);
      this->mpGLViewport->getPainter()->runAnimation();
      this->mpControlWidget->setNumSteps(this->mpGLViewport->getPainter()->getNumberOfSteps());
      this->mpParaPanel->disableParameterChoice();
      this->mpParaPanel->disableStepNumberChoice();
    }
  else
    {
      CQMessageBox::warning(this, "Missing Data",
                            "No data found: \nYou first have to create a time course.",
                            QMessageBox::Ok, QMessageBox::Ok);
    }
}

void CQLayoutMainWindow::saveImage()
{
#ifdef DEBUG_UI
//  qDebug() << "mCurrentPlace = " << mCurrentPlace;
#endif

#ifdef FRAMEBUFFER_SCREENSHOTS
  // get the parameters
  CQGLNetworkPainter* pPainter = this->mpGLViewport->getPainter();
  assert(pPainter != NULL);

  if (pPainter != NULL)
    {
      size_t step = pPainter->getCurrentStep();
      size_t lastFrame = pPainter->getNumberOfSteps();
      double x = pPainter->getCurrentPositionX();
      double y = pPainter->getCurrentPositionY();
      double layoutX = pPainter->getGraphMin().getX();
      double layoutY = pPainter->getGraphMin().getY();
      double layoutWidth = pPainter->getGraphMax().getX() - layoutX;
      double layoutHeight = pPainter->getGraphMax().getY() - layoutY;
      unsigned int imageWidth = pPainter->width();
      unsigned int imageHeight = pPainter->height();
      double zoomFactor = pPainter->getZoomFactor();
      double width = (double)imageWidth / zoomFactor;
      double height = (double)imageHeight / zoomFactor;
      // use more sophisticated dialog
      CQScreenshotOptionsDialog* pDialog = new CQScreenshotOptionsDialog(layoutX, layoutY, layoutWidth, layoutHeight,
          x, y, width, height, pPainter->width() , pPainter->height(), lastFrame, this);

      if (pDialog->exec() == QDialog::Accepted)
        {
          // ask for the filename
          // TODO use a nicer default filename
          QString fileName = CopasiFileDialog::getSaveFileName(this, "Save Image Dialog", QString("untitled.png"), QString("PNG (*.png);;All files (*)"), QString("Choose a filename to save the image(s) under"));

          if (!fileName.isEmpty() && !fileName.isNull())
            {
              // get the frames
              std::vector<size_t> v;

              switch (pDialog->getFrameOption())
                {
                  case CQScreenshotOptionsDialog::ALL_FRAMES:

                    // add all frames from 1 to lastFrame
                    if (lastFrame != 0)
                      {
                        for (size_t i = 1; i <= lastFrame; ++i)
                          {
                            v.push_back(i);
                          }
                      }
                    else
                      {
                        v.push_back(step);
                      }

                    break;
                  case CQScreenshotOptionsDialog::USER_DEFINED_FRAMES:
                    v.insert(v.begin(), pDialog->getFrameSet().begin(), pDialog->getFrameSet().end());

                    if (v.empty())
                      {
                        CQMessageBox::warning(this, "No frames selected",
                                              "The frame selection was invalid.\nExporting current frame.",
                                              QMessageBox::Ok, QMessageBox::Ok);
                        v.push_back(step);
                      }

                    break;
                  default:
                    v.push_back(step);
                    break;
                }

              bool result = pPainter->export_bitmap(pDialog->getX(), pDialog->getY(), pDialog->getWidth(), pDialog->getHeight(), pDialog->getImageWidth(), pDialog->getImageHeight(), fileName, v);

              if (result == false)
                {
                  CQMessageBox::warning(this, "Error creating image",
                                        "The image could not be created.",
                                        QMessageBox::Ok, QMessageBox::Ok);
                  return;
                }
            }
        }

      delete pDialog;
    }

#else
  QImage img = mpGLViewport->getPainter()->getImage();
  QString filename = CopasiFileDialog::getSaveFileName(this, "Save Image Dialog", "untitled.png",
                     "PNG Files (*.png)", "Choose a filename to save the image under");

  if (!filename.isNull())
    {
      img.save(filename, "PNG");

      mCurrentPlace = filename;
    }

#endif // FRAMEBUFFER_SCREENSHOTS
}

void CQLayoutMainWindow::pauseAnimation()
{
  // tell the painter that the anmation is paused
  this->mpGLViewport->getPainter()->pauseAnimation();
  this->mpVisParameters->mAnimationRunning = false;
  this->mpTimeSlider->setEnabled(true);
  mpParaPanel->enableParameterChoice();
  mpParaPanel->enableStepNumberChoice();
}

void CQLayoutMainWindow::endOfAnimationReached()
{
  if (this->mLooping)
    {
      this->mpControlWidget->getBackwardAction()->activate(QAction::Trigger);
    }
  else
    {
      this->mpControlWidget->getPauseAction()->activate(QAction::Trigger);
    }
}

void CQLayoutMainWindow::showStep(double i)
{
  this->mpControlWidget->setCurrentStep(static_cast<int>(i));
  mpGLViewport->getPainter()->showStep(static_cast<int>(i));
  mpGLViewport->getPainter()->updateGL();
  mpParaPanel->setStepNumber(static_cast<int>(i));
  CDataEntity* srcData = mpGLViewport->getPainter()->getDataSetAt(static_cast<int>(i));

  if (srcData)
    {
      updateValueTable(*srcData);
    }
}

void CQLayoutMainWindow::changeStepValue(int i)
{
  mpTimeSlider->setValue(i);
}

void CQLayoutMainWindow::setIndividualScaling()
{
  mpVisParameters->mScalingMode = mpVisParameters->INDIVIDUAL_SCALING;
  mpGLViewport->getPainter()->setScaleMode(mpVisParameters->INDIVIDUAL_SCALING);
  mpGLViewport->getPainter()->rescaleDataSets(mpVisParameters->INDIVIDUAL_SCALING);
  showStep(this->mpTimeSlider->value());
}

void CQLayoutMainWindow::setGlobalScaling()
{
  mpVisParameters->mScalingMode = mpVisParameters->GLOBAL_SCALING;
  mpGLViewport->getPainter()->setScaleMode(mpVisParameters->GLOBAL_SCALING);
  mpGLViewport->getPainter()->rescaleDataSets(mpVisParameters->GLOBAL_SCALING);
  showStep(this->mpTimeSlider->value());
}

void CQLayoutMainWindow::setSizeMode()
{
  mpVisParameters->mMappingMode = CVisParameters::SIZE_DIAMETER_MODE;
  mpGLViewport->getPainter()->rescaleDataSetsWithNewMinMax(0.0, 1.0, getMinNodeSize(), getMaxNodeSize(), mpVisParameters->mScalingMode); // only [0.240] of possible HSV values (not fill circle in order to get good color range)
  showStep(this->mpTimeSlider->value());
}

void CQLayoutMainWindow::setColorMode()
{
  mpVisParameters->mMappingMode = CVisParameters::COLOR_MODE;
  mpGLViewport->getPainter()->rescaleDataSetsWithNewMinMax(getMinNodeSize(), getMaxNodeSize(), 0.0, 1.0, mpVisParameters->mScalingMode); // rescaling, because min and max node size changed (interpretation as color value takes place elsewhere),only [0.240] of possible HSV values (not fill circle in order to get good color range)
  showStep(this->mpTimeSlider->value());
}

void CQLayoutMainWindow::setValueOnSlider(C_INT32 val)
{
  mpTimeSlider->setValue(val);
}

// set minimum possible node size for animation
void CQLayoutMainWindow::setMinValue(C_INT32 minNdSize)
{
  mpGLViewport->getPainter()->rescaleDataSetsWithNewMinMax(getMinNodeSize(), getMaxNodeSize(), minNdSize, getMaxNodeSize(), mpVisParameters->mScalingMode);
  setMinNodeSize(minNdSize);
  showStep(this->mpTimeSlider->value());
}

// set maximum possible node size for animation
void CQLayoutMainWindow::setMaxValue(C_INT32 maxNdSize)
{
  mpGLViewport->getPainter()->rescaleDataSetsWithNewMinMax(getMinNodeSize(), getMaxNodeSize(), getMinNodeSize(), maxNdSize, mpVisParameters->mScalingMode);
  setMaxNodeSize(maxNdSize);
  showStep(this->mpTimeSlider->value());
}

void CQLayoutMainWindow::setMinAndMaxValue(C_INT32 minNdSize, C_INT32 maxNdSize)
{
  mpGLViewport->getPainter()->rescaleDataSetsWithNewMinMax(getMinNodeSize(), getMaxNodeSize(), minNdSize, maxNdSize, mpVisParameters->mScalingMode);
  setMinNodeSize(minNdSize);
  setMaxNodeSize(maxNdSize);
  showStep(this->mpTimeSlider->value());
}

void CQLayoutMainWindow::setFontSizeForLabels(C_INT32 size)
{
  mpGLViewport->getPainter()->setFontSizeForLabels((unsigned int) size);
}

#ifndef USE_CRENDER_EXTENSION
void CQLayoutMainWindow::closeApplication()
{
  this->close();
}

void CQLayoutMainWindow::closeEvent(QCloseEvent *event)
{
  if (maybeSave())
    {
      this->mpControlWidget->getPauseAction()->activate(QAction::Trigger);
      event->accept();
    }
  else
    {
      event->ignore();
    }
}
#endif // USE_CRENDER_EXTENSION

QIcon CQLayoutMainWindow::createStartIcon()
{
  C_INT32 w = 19;
  C_INT32 h = 19;
  QImage img = QImage(w, h, QImage::Format_Indexed8);
  img.setNumColors(2);
  img.setColor(0, qRgb(0, 0, 200));
  C_INT16 x, y;

  for (x = 0; x < w; x++)
    {
      for (y = 0; y < h; y++)
        {
          img.setPixel(x, y, 0);
        }
    }

  C_INT32 delta = 0;
  img.setColor(1, qRgb(255, 0, 0));

  for (x = 3; x < w - 3; x++)
    {
      for (y = 3 + delta; y < h - 3 - delta; y++)
        {
          img.setPixel(x, y, 1);
        }

      if (fmod((double) x, 2.0) == 0)
        delta++;
    }

  QPixmap *pixmap = new QPixmap();
  pixmap->fromImage(img);
  QIcon iconset = QIcon(*pixmap);
  delete pixmap;
  return iconset;
}

QIcon CQLayoutMainWindow::createStopIcon()
{
  C_INT32 w = 20;
  C_INT32 h = 20;
  QImage img = QImage(w, h, QImage::Format_Indexed8);
  img.setNumColors(2);
  img.setColor(0, qRgb(0, 0, 200));
  C_INT16 x, y;

  for (x = 0; x < w; x++)
    {
      for (y = 0; y < h; y++)
        {
          img.setPixel(x, y, 0);
        }
    }

  C_INT32 delta = 4;
  img.setColor(1, qRgb(255, 0, 0));

  for (x = (delta - 1); x <= (w - delta); x++)
    {
      for (y = (delta - 1); y <= (h - delta); y++)
        {
          img.setPixel(x, y, 1);
        }
    }

  QPixmap *pixmap = new QPixmap();
  pixmap->fromImage(img);
  QIcon iconset = QIcon(*pixmap);
  delete pixmap;
  return iconset;
}

// returns true because window is opened from COPASI and can be easily reopened
bool CQLayoutMainWindow::maybeSave()
{
  //  int ret = QMessageBox::warning(this, "SimWiz",
  //                                 "Do you really want to quit?",
  //                                 //                   tr("Do you really want to quit?\n"
  //                                 //                      "XXXXXXXX"),
  //                                 QMessageBox::Yes | QMessageBox::Default,
  //                                 QMessageBox::No,
  //                                 QMessageBox::Cancel | QMessageBox::Escape);
  //  if (ret == QMessageBox::Yes)
  //    return true;
  //  else if (ret == QMessageBox::Cancel)
  //    return false;

  return true;
}


/**
 * Make the layout fit the screen.
 * Return the new zoom factor.
 */
double CQLayoutMainWindow::slotFitToScreen()
{
  double zoom = this->mpGLViewport->fitToScreen();
#ifndef USE_CRENDER_EXTENSION
  disconnect(mpZoomMenu, SIGNAL(triggered(QAction*)), this, SLOT(slotZoomItemActivated(QAction*)));
  QList<QAction*> actions = this->mpZoomActionGroup->actions();
  QList<QAction*>::iterator it = actions.begin(), endit = actions.end();

  while (it != endit)
    {
      if ((*it)->isChecked())
        {
          (*it)->setChecked(false);
          // only one item can be checked
          break;
        }

      ++it;
    }

  connect(mpZoomMenu, SIGNAL(triggered(QAction*)), this, SLOT(slotZoomItemActivated(QAction*)));

  disconnect(this->mpZoomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotActivated(int)));
  // add a new entry for the zoom factor only if there isn't one already
  unsigned int n = sizeof(CQLayoutMainWindow::ZOOM_FACTOR_STRINGS) / sizeof(char*);

  if (this->mpZoomComboBox > n)
    {
      this->mpZoomComboBox->setItemText(0, QString("%1").arg(zoom*100).append("%"));
    }
  else
    {
      this->mpZoomComboBox->insertItem(0, QString("%1").arg(zoom*100).append("%"));
    }

  this->mpZoomComboBox->setCurrentIndex(0);
  connect(this->mpZoomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotActivated(int)));
#endif // USE_CRENDER_EXTENSION
  return zoom;
}

void CQLayoutMainWindow::slotResetView()
{
#ifndef USE_CRENDER_EXTENSION
  // check the 100% zoom entry
  disconnect(mpZoomMenu, SIGNAL(triggered(QAction*)), this, SLOT(slotZoomItemActivated(QAction*)));
  this->mpZoomActionGroup->actions().at(10)->setChecked(true);
  connect(mpZoomMenu, SIGNAL(triggered(QAction*)), this, SLOT(slotZoomItemActivated(QAction*)));
  // update toolbar
  disconnect(this->mpZoomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotActivated(int)));
  this->mpZoomComboBox->setCurrentIndex(10);
  connect(this->mpZoomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotActivated(int)));
#endif // USE_CRENDER_EXTENSION
  this->mpGLViewport->resetView();
}

void CQLayoutMainWindow::setZoomFactor(double zoom)
{
  this->mpGLViewport->setZoomFactor(zoom);
}

void CQLayoutMainWindow::setZoomFactor(QString s)
{
  s.remove(s.size() - 1, 1);
  // create a number from the text
  double n = s.toDouble();
  n /= 100.0;
  this->setZoomFactor(n);
}

#ifndef USE_CRENDER_EXTENSION
void CQLayoutMainWindow::slotActivated(int index)
{
  // check if the number of entries in the combobox are greater than the number of
  // zoom items
  // If that is the case, remove the first one and reduce the index by 1
  unsigned int n = sizeof(CQLayoutMainWindow::ZOOM_FACTOR_STRINGS) / sizeof(char*);

  if (this->mpZoomComboBox->count() > n && index != 0)
    {
      --index;
      disconnect(this->mpZoomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotActivated(int)));
      this->mpZoomComboBox->removeItem(0);
      this->mpZoomComboBox->setCurrentIndex(index);
      connect(this->mpZoomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotActivated(int)));
    }

  // update menu items
  if (this->mpZoomComboBox->count() == n)
    {
      if (index >= 0 && index < n)
        {
          QAction* pAction = this->mpZoomActionGroup->actions().at(index);
          pAction->setChecked(true);
          this->setZoomFactor(pAction->text());
        }
    }
}

void CQLayoutMainWindow::slotZoomItemActivated(QAction* pAction)
{
  // if the item is not checked, uncheck all other and check this one
  // set the zoom factor

  // check if the number of zoom factors in the combobox is greater than
  // the number of items in the zoom combo box
  //
  // if so, delete the first entry from the list
  // the item that has been added by fitToScreen.
  const size_t n = sizeof(CQLayoutMainWindow::ZOOM_FACTOR_STRINGS) / sizeof(char*);

  if ((size_t)this->mpZoomComboBox->count() > n)
    {
      disconnect(this->mpZoomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotActivated(int)));
      this->mpZoomComboBox->removeItem(0);
      connect(this->mpZoomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotActivated(int)));
    }

  QString text = pAction->text();
  this->setZoomFactor(text);
  // update toolbar
  disconnect(this->mpZoomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotActivated(int)));
  this->mpZoomComboBox->setCurrentIndex(this->mpZoomComboBox->findText(text));
  connect(this->mpZoomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotActivated(int)));
}

void CQLayoutMainWindow::slotZoomIn()
{
  QAction* pAction = this->mpZoomActionGroup->checkedAction();
  QList<QAction*> actions = this->mpZoomActionGroup->actions();
  int index = actions.indexOf(pAction);

  if (index < actions.size() - 1)
    {
      ++index;
      actions.at(index)->setChecked(true);
    }
}

void CQLayoutMainWindow::slotZoomOut()
{
  QAction* pAction = this->mpZoomActionGroup->checkedAction();
  QList<QAction*> actions = this->mpZoomActionGroup->actions();
  int index = actions.indexOf(pAction);

  if (index > 0)
    {
      --index;
      actions.at(index)->setChecked(true);
    }
}
#else
void CQLayoutMainWindow::setLayout(CLayout* pLayout)
{
  if (this->mpLayout == pLayout) return;

  this->mpLayout = pLayout;

  if (this->mpLayout != NULL)
    {
      this->mpGLViewport->createGraph(this->mpLayout); // create local data structures
      this->loadData();
    }

  this->update();
}

CQPlayerControlWidget* CQLayoutMainWindow::getControlWidget()
{
  return this->mpControlWidget;
}

#endif // USE_CRENDER_EXTENSION

void CQLayoutMainWindow::stopAnimation()
{
  // go to step 0 and stop
  this->backwardAnimation();
  this->mapLabelsToRectangles();
}

void CQLayoutMainWindow::forwardAnimation()
{
  // go to last step and redisplay
  if (!this->mLooping)
    {
      this->pauseAnimation();
      double stepNumber = (double)(this->mpGLViewport->getPainter()->getNumberOfSteps() - 1);
      this->showStep(stepNumber);
      // update the slider
      disconnect(mpTimeSlider, SIGNAL(valueChanged(double)), this, SLOT(showStep(double)));
      this->mpTimeSlider->setValue(stepNumber);
      connect(mpTimeSlider, SIGNAL(valueChanged(double)), this, SLOT(showStep(double)));
    }
  else
    {
      this->backwardAnimation();
    }
}

void CQLayoutMainWindow::backwardAnimation()
{
  // go to step 0 and redisplay
  this->pauseAnimation();
  this->mpGLViewport->getPainter()->showStep(0);
  // update the slider
  disconnect(mpTimeSlider, SIGNAL(valueChanged(double)), this, SLOT(showStep(double)));
  this->mpTimeSlider->setValue(0.0);
  this->mpParaPanel->setStepNumber(0);
  connect(mpTimeSlider, SIGNAL(valueChanged(double)), this, SLOT(showStep(double)));

  if (this->mpControlWidget->isPlaying())
    {
      this->startAnimation();
    }
}

void CQLayoutMainWindow::stepForwardAnimation()
{
  // raise step by one if possible and continue animation
  // go to last step and redisplay
  size_t currentStep = this->getCurrentStep();
  ++currentStep;

  if (currentStep < this->mpGLViewport->getPainter()->getNumberOfSteps())
    {
      this->pauseAnimation();
      this->showStep((double)currentStep);
      // update the slider
      disconnect(mpTimeSlider, SIGNAL(valueChanged(double)), this, SLOT(showStep(double)));
      this->mpTimeSlider->setValue((double)currentStep);
      connect(mpTimeSlider, SIGNAL(valueChanged(double)), this, SLOT(showStep(double)));
    }
}

void CQLayoutMainWindow::stepBackwardAnimation()
{
  // lower step by one if possible and redisplay
  size_t currentStep = this->getCurrentStep();

  if (currentStep > 0)
    {
      --currentStep;
      this->pauseAnimation();
      this->showStep((double)currentStep);
      // update the slider
      disconnect(mpTimeSlider, SIGNAL(valueChanged(double)), this, SLOT(showStep(double)));
      this->mpTimeSlider->setValue((double)currentStep);
      connect(mpTimeSlider, SIGNAL(valueChanged(double)), this, SLOT(showStep(double)));
    }
}

void CQLayoutMainWindow::slotParameterTableToggled(bool checked)
{
  (checked == true) ? this->mpParaPanel->show() : this->mpParaPanel->hide();

  // if all object in the info box are hidden, we hide the info box
  if (!checked && !this->mpValueTableAction->isChecked())
    {
      this->mpInfoBox->hide();
    }
  else
    {
      this->mpInfoBox->show();
    }
}

void CQLayoutMainWindow::slotValueTableToggled(bool checked)
{
  (checked == true) ? this->mpValTable->show() : this->mpValTable->hide();

  // if all object in the info box are hidden, we hide the info box
  if (!checked && !this->mpParameterTableAction->isChecked())
    {
      this->mpInfoBox->hide();
    }
  else
    {
      this->mpInfoBox->show();
    }
}

void CQLayoutMainWindow::slotToolbarToggled(bool checked)
{
  (checked == true) ? this->mpToolbar->show() : this->mpToolbar->hide();
}

void CQLayoutMainWindow::slotPlayerControlToggled(bool checked)
{
  (checked == true) ? this->mpFrame->show() : this->mpFrame->hide();
}

void CQLayoutMainWindow::slotLoopActivated(bool checked)
{
  this->mLooping = checked;
}
