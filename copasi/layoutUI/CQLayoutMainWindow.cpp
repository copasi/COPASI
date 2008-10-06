// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.cpp,v $
//   $Revision: 1.85 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/10/06 15:51:45 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQLayoutMainWindow.h"

#include <qaction.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qmenubar.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qvbox.h>
#include <qfiledialog.h>
#include <qwt_slider.h>

#include <iostream>
#include <math.h>

#include "copasi/layout/CLBase.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "CQCurrentValueTable.h"
#include "CQGLNetworkPainter.h"
#include "CQGLViewport.h"
#include "FontChooser.h"
#include "NodeSizePanel.h"
#include "ParaPanel.h"
#include "CQPlayerControlWidget.h"
#include "load_data.xpm"

using namespace std;

CQLayoutMainWindow::CQLayoutMainWindow(CLayout* pLayout, QWidget *parent, const char *name) : QMainWindow(parent, name)
{
  mpLayout = pLayout;
  mCurrentPlace = QString::null;
  mDataPresent = false;
  mpVisParameters = new CVisParameters();
  setCaption(tr("Reaction network graph"));
  mpMainBox = new QVBox(this);

  // create split window with parameter panel and graph panel
  mpSplitter = new QSplitter(Qt::Horizontal, mpMainBox);
  mpSplitter->setCaption("Test");

  mpInfoBox = new QVBox(mpSplitter);

  mpParaPanel = new CQParaPanel(mpInfoBox);

  mpValTable = new CQCurrentValueTable(mpInfoBox);
  // Create OpenGL widget
  mpGLViewport = new CQGLViewport(mpSplitter, "Network layout");
  if (pLayout != NULL)
    {
      CLDimensions dim = pLayout->getDimensions();
      CLPoint c1;
      CLPoint c2(dim.getWidth(), dim.getHeight());
      mpGLViewport->createGraph(mpLayout); // create local data structures
    }
  mpSplitter->setResizeMode(mpInfoBox, QSplitter::KeepSize);

  mpFrame = new QFrame(mpMainBox);

  this->mpControlWidget = new CQPlayerControlWidget(mpFrame);
  connect(this->mpControlWidget, SIGNAL(play()), this, SLOT(startAnimation()));
  connect(this->mpControlWidget, SIGNAL(pause()), this, SLOT(pauseAnimation()));
  connect(this->mpControlWidget, SIGNAL(stop()), this, SLOT(stopAnimation()));
  connect(this->mpControlWidget, SIGNAL(forward()), this, SLOT(forwardAnimation()));
  connect(this->mpControlWidget, SIGNAL(backward()), this, SLOT(backwardAnimation()));
  connect(this->mpControlWidget, SIGNAL(step_backward()), this, SLOT(stepBackwardAnimation()));
  connect(this->mpControlWidget, SIGNAL(step_forward()), this, SLOT(stepForwardAnimation()));

  mpTimeSlider = new QwtSlider(mpFrame, Qt::Horizontal, QwtSlider::BottomScale, QwtSlider::BgTrough);
  mpTimeSlider->setRange(0, 100, 1, 0);
  mpTimeSlider->setValue(0.0);
  this->mpTimeSlider->setEnabled(false);

  mpTimeSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  mpFrame->setFixedHeight(68);
  connect(mpTimeSlider, SIGNAL(valueChanged(double)),
          this, SLOT(showStep(double)));

  QGridLayout* bottomBoxlayout = new QGridLayout(mpFrame, 2, 2, 3, 6);
  bottomBoxlayout->addMultiCellWidget(mpTimeSlider, 0, 1, 1, 1, Qt::AlignTop);
  bottomBoxlayout->addMultiCellWidget(this->mpControlWidget, 0, 1, 0, 0, Qt::AlignTop);
  QSpacerItem* theSpacer = new QSpacerItem(20, 20);
  bottomBoxlayout->addItem(theSpacer, 1, 0);

  setCentralWidget(mpMainBox);
  loadData(); // try to load data (if already present)
  // the action have to be created before mpLoadDataAction is used below
  // the menus have to be created after the player control widget is created
  // since actions from the player control are added to the menu
  // the actions have to be created before the menus since some action go into
  // menus
  createActions();
  createMenus();

  this->mpToolbar = new QToolBar(this, "layout toolbar");
  this->mpLoadDataAction->addTo(this->mpToolbar);
  this->mpToolbar->addSeparator();
  QLabel* pLabel = new QLabel("zoom factor:", this->mpToolbar);
  pLabel->show();
  this->mpZoomComboBox = new QComboBox("zoom box", this->mpToolbar);
  QStringList l;
  l.push_back("1%");
  l.push_back("2%");
  l.push_back("3%");
  l.push_back("4%");
  l.push_back("5%");
  l.push_back("10%");
  l.push_back("20%");
  l.push_back("30%");
  l.push_back("40%");
  l.push_back("50%");
  l.push_back("100%");
  l.push_back("150%");
  l.push_back("200%");
  l.push_back("300%");
  l.push_back("400%");
  l.push_back("500%");
  this->mpZoomComboBox->insertStringList(l);
  this->mpZoomComboBox->setCurrentItem(10);
  this->mpZoomComboBox->setEditable(FALSE);
  this->mpZoomComboBox->show();
  connect(this->mpZoomComboBox, SIGNAL(activated(int)), this, SLOT(slotActivated(int)));
  connect(this->mpValTable , SIGNAL(valueChanged(int)), this, SLOT(parameterTableValueChanged(int)));
  connect(this->mpGLViewport->getPainter() , SIGNAL(signalZoomIn()), this, SLOT(slotZoomIn()));
  connect(this->mpGLViewport->getPainter() , SIGNAL(signalZoomOut()), this, SLOT(slotZoomOut()));
  this->mLooping = false;

  this->setTabOrder(this->mpGLViewport, this->mpToolbar);
  this->setTabOrder(this->mpToolbar, this->mpParaPanel);
  this->setTabOrder(this->mpParaPanel, this->mpValTable);
  this->setTabOrder(this->mpValTable, this->mpControlWidget);
  this->show();
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

C_INT32 CQLayoutMainWindow::getCurrentStep()
{
  return (C_INT32) this->mpTimeSlider->value();
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

  mpCloseAction = new QAction ("close",
                               "Close Window",
                               CTRL + Key_Q ,
                               this);
  mpCloseAction->setStatusTip("Close Layout Window");
  connect(mpCloseAction, SIGNAL(activated()), this, SLOT(closeApplication()));

  mDataPresent = false;

  mpCreatePicture = new QAction("image",
                                "Create image",
                                CTRL + Key_I,
                                this);
  mpCreatePicture->setStatusTip("create a picture from the current view and save it to file");
  connect(mpCreatePicture, SIGNAL(activated()), this, SLOT(saveImage()));

  mpRectangluarShape = new QAction ("rectangle",
                                    "rectangle",
                                    CTRL + Key_R ,
                                    this);
  mpRectangluarShape->setStatusTip("Show labels as rectangles");
  connect(mpRectangluarShape, SIGNAL(activated()), this, SLOT(mapLabelsToRectangles()));

  mpCircularShape = new QAction ("circle",
                                 "circle",
                                 CTRL + Key_C ,
                                 this);
  connect(mpCircularShape, SIGNAL(activated()), this, SLOT(mapLabelsToCircles()));
  mpCircularShape->setStatusTip("Show labels as circles");

  mpMimaNodeSizes = new QAction ("minmax",
                                 "Set Min/Max Node Sizes",
                                 CTRL + Key_M,
                                 this);

  connect(mpMimaNodeSizes, SIGNAL(activated()), this, SLOT(changeMinMaxNodeSizes()));
  mpMimaNodeSizes->setToolTip("Change Min/Max for node sizes within animation");

  mpSFontSize = new QAction("fontsiz",
                            "Set Font Size",
                            CTRL + Key_F,
                            this);

  connect(mpSFontSize, SIGNAL(activated()), this, SLOT(changeFontSize()));
  mpSFontSize->setToolTip("Change the font size of the node labels in the graph view");

  this->mpLoadDataAction = new QAction(QPixmap(load_data_xpm),
                                       "load data",
                                       QKeySequence(),
                                       this);
  connect(this->mpLoadDataAction, SIGNAL(activated()), this, SLOT(loadData()));
}

void CQLayoutMainWindow::createMenus()
{
  mpFileMenu = new QPopupMenu(this);
  mpFileMenu->insertSeparator();
  mpCloseAction->addTo(mpFileMenu);

  mpLabelShapeMenu = new QPopupMenu(this);

  mpRectangluarShape->addTo(mpLabelShapeMenu);
  mpCircularShape->addTo(mpLabelShapeMenu);
  // play menu
  this->mpPlayMenu = new QPopupMenu(this);
  this->mpControlWidget->getPlayAction()->addTo(this->mpPlayMenu);
  this->mpControlWidget->getPauseAction()->addTo(this->mpPlayMenu);
  this->mpControlWidget->getStopAction()->addTo(this->mpPlayMenu);
  this->mpControlWidget->getForwardAction()->addTo(this->mpPlayMenu);
  this->mpControlWidget->getBackwardAction()->addTo(this->mpPlayMenu);
  this->mpControlWidget->getStepForwardAction()->addTo(this->mpPlayMenu);
  this->mpControlWidget->getStepBackwardAction()->addTo(this->mpPlayMenu);
  this->mpPlayMenu->insertSeparator();
  this->mLoopItemId = this->mpPlayMenu->insertItem("loop animation", this, SLOT(slotLoopActivated()));
  this->mpPlayMenu->insertSeparator();
  this->mpLoadDataAction->addTo(this->mpPlayMenu);

  // view menu
  mpViewMenu = new QPopupMenu(this);
  mpViewMenu->insertItem("parameters", 1001);
  mpViewMenu->setItemChecked(1001, TRUE);
  mpViewMenu->insertItem("value table", 1002);
  mpViewMenu->setItemChecked(1002, TRUE);
  mpViewMenu->insertItem("player control", 1003);
  mpViewMenu->setItemChecked(1003, TRUE);
  mpViewMenu->insertItem("toolbar", 1004);
  mpViewMenu->setItemChecked(1004, TRUE);
  connect(this->mpViewMenu, SIGNAL(activated(int)), this, SLOT(slotViewActivated(int)));
  mpViewMenu->insertSeparator();
  mpViewMenu->insertItem("Reset View", this, SLOT(slotResetView()));
  mpZoomMenu = new QPopupMenu(this);
  mpViewMenu->insertItem("Zoom", mpZoomMenu);
  int id;
  id = mpZoomMenu->insertItem("1%", 1);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("2%", 2);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("3%", 3);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("4%", 4);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("5%", 5);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("10%", 10);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("20%", 20);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("30%", 30);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("40%", 40);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("50%", 50);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("100%", 100);
  mpZoomMenu->setItemChecked(id, true);
  id = mpZoomMenu->insertItem("150%", 150);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("200%", 200);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("300%", 300);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("400%", 400);
  mpZoomMenu->setItemChecked(id, false);
  id = mpZoomMenu->insertItem("500%", 500);
  mpZoomMenu->setItemChecked(id, false);
  connect(mpZoomMenu, SIGNAL(activated(int)), this, SLOT(slotZoomItemActivated(int)));
  this->mpViewMenu->insertSeparator();
  mpCreatePicture->addTo(mpViewMenu);

  mpOptionsMenu = new QPopupMenu(this);
  mpOptionsMenu->insertItem("Shape of Label", mpLabelShapeMenu);
  mpMimaNodeSizes->addTo(mpOptionsMenu);
  mpSFontSize->addTo(mpOptionsMenu);

  menuBar()->insertItem("File", mpFileMenu);
  menuBar()->insertItem("Play", this->mpPlayMenu);
  menuBar()->insertItem("View", this->mpViewMenu);
  menuBar()->insertItem("Options", mpOptionsMenu);
}

void CQLayoutMainWindow::loadSBMLFile()
{
  std::cout << "load SBMLfile" << std::endl;
  CListOfLayouts *pLayoutList;
  if (CCopasiDataModel::Global != NULL)
    {
      pLayoutList = CCopasiDataModel::Global->getListOfLayouts();
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
          CLDimensions dim = pLayout->getDimensions();
          CLPoint c1;
          CLPoint c2(dim.getWidth(), dim.getHeight());
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
      int maxVal = mpGLViewport->getPainter()->getNumberOfSteps();
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
  mpValTable->setNumRows(dataSet.getNumberOfElements());
  mpValTable->setNumCols(2);
  while ((key = mpGLViewport->getPainter()->getNodeNameEntry(i)) != "")
    {
      name = this->mpGLViewport->getPainter()->getNameForNodeKey(key);
      val = dataSet.getOrigValueForSpecies(key); // would be (- DBL_MAX) if key not present
      mpValTable->setRowInTable(i, key, name, val);
      i++;
    }
}

void CQLayoutMainWindow::updateValueTable(CDataEntity dataSet)
{
  int i = 0;
  std::string key, name;
  C_FLOAT64 val;
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
}

// adds the item given by s to the list of items to animate (no change, if it is already present)
void CQLayoutMainWindow::addItemInAnimation (std::string key)
{
  mpGLViewport->getPainter()->setItemAnimated(key, true);
}

// removes the item given by s from the list of items to animate (no change, if it is not present in the list)
void CQLayoutMainWindow::removeItemInAnimation (std::string key)
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
      QMessageBox::warning (this, "Missing Data", "No data found: \nYou first have to create a time course.", QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
    }
}

void CQLayoutMainWindow::saveImage()
{
  QImage img = mpGLViewport->getPainter()->getImage();
  QString filename = QFileDialog::getSaveFileName(mCurrentPlace, "PNG Files (*.png);;All Files (*.*);;", this, "Choose a filename to save the image under");
  if (filename)
    {
      img.save(filename, "PNG");
      mCurrentPlace = filename;
    }
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
      this->mpControlWidget->getBackwardAction()->activate();
    }
  else
    {
      this->mpControlWidget->getPauseAction()->activate();
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

void CQLayoutMainWindow::changeStepValue(C_INT32 i)
{
  mpTimeSlider->setValue(i);
}

void CQLayoutMainWindow::setIndividualScaling()
{
  mpVisParameters->mScalingMode = mpVisParameters->INDIVIDUAL_SCALING;
  mpGLViewport->getPainter()->rescaleDataSets(mpVisParameters->INDIVIDUAL_SCALING);
  showStep(this->mpTimeSlider->value());
}

void CQLayoutMainWindow::setGlobalScaling()
{
  mpVisParameters->mScalingMode = mpVisParameters->GLOBAL_SCALING;
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

void CQLayoutMainWindow::closeApplication()
{
  this->close();
}

void CQLayoutMainWindow::closeEvent(QCloseEvent *event)
{
  if (maybeSave())
    {
      this->mpControlWidget->getPauseAction()->activate();
      event->accept();
    }
  else
    {
      event->ignore();
    }
}

QIconSet CQLayoutMainWindow::createStartIcon()
{
  QImage img = QImage();
  C_INT32 w = 19;
  C_INT32 h = 19;
  img.create(w, h, 8, 2);
  img.setColor(0, qRgb(0, 0, 200));
  C_INT16 x, y;

  for (x = 0;x < w;x++)
    {
      for (y = 0;y < h;y++)
        {
          img.setPixel(x, y, 0);
        }
    }

  C_INT32 delta = 0;
  img.setColor(1, qRgb(255, 0, 0));
  for (x = 3;x < w - 3;x++)
    {
      for (y = 3 + delta;y < h - 3 - delta;y++)
        {
          img.setPixel(x, y, 1);
        }
      if (fmod((double) x, 2.0) == 0)
        delta++;
    }

  QPixmap *pixmap = new QPixmap();
  pixmap->convertFromImage(img);
  QIconSet iconset = QIconSet(*pixmap);
  delete pixmap;
  return iconset;
}

QIconSet CQLayoutMainWindow::createStopIcon()
{
  QImage img = QImage();
  C_INT32 w = 20;
  C_INT32 h = 20;
  img.create(w, h, 8, 2);
  img.setColor(0, qRgb(0, 0, 200));
  C_INT16 x, y;

  for (x = 0;x < w;x++)
    {
      for (y = 0;y < h;y++)
        {
          img.setPixel(x, y, 0);
        }
    }

  C_INT32 delta = 4;
  img.setColor(1, qRgb(255, 0, 0));
  for (x = (delta - 1);x <= (w - delta);x++)
    {
      for (y = (delta - 1);y <= (h - delta);y++)
        {
          img.setPixel(x, y, 1);
        }
    }

  QPixmap *pixmap = new QPixmap();
  pixmap->convertFromImage(img);
  QIconSet iconset = QIconSet(*pixmap);
  delete pixmap;
  return iconset;
}

// returns true because window is opened from Copasi and can be easily reopened
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

void CQLayoutMainWindow::slotActivated(int index)
{
  QString item = this->mpZoomComboBox->text(index);
  this->setZoomFactor(item.latin1());
  // update menu items
  int ids[] = {1, 2, 3, 4, 5, 10, 20, 30, 40, 50, 100, 150, 200, 300, 400, 500};
  if (index >= 0 && index < 15)
    {
      unsigned int id = ids[index];
      disconnect(mpZoomMenu, SIGNAL(activated(int)), this, SLOT(slotZoomItemActivated(int)));
      this->mpZoomMenu->setItemChecked(1, false);
      this->mpZoomMenu->setItemChecked(2, false);
      this->mpZoomMenu->setItemChecked(3, false);
      this->mpZoomMenu->setItemChecked(4, false);
      this->mpZoomMenu->setItemChecked(5, false);
      this->mpZoomMenu->setItemChecked(10, false);
      this->mpZoomMenu->setItemChecked(20, false);
      this->mpZoomMenu->setItemChecked(30, false);
      this->mpZoomMenu->setItemChecked(40, false);
      this->mpZoomMenu->setItemChecked(50, false);
      this->mpZoomMenu->setItemChecked(100, false);
      this->mpZoomMenu->setItemChecked(150, false);
      this->mpZoomMenu->setItemChecked(200, false);
      this->mpZoomMenu->setItemChecked(300, false);
      this->mpZoomMenu->setItemChecked(400, false);
      this->mpZoomMenu->setItemChecked(500, false);
      this->mpZoomMenu->setItemChecked(id, true);
      connect(mpZoomMenu, SIGNAL(activated(int)), this, SLOT(slotZoomItemActivated(int)));
    }
}

void CQLayoutMainWindow::setZoomFactor(std::string s)
{
  s.erase(s.size() - 1);
  // create a number from the text
  double n = strtod(s.c_str(), NULL);
  n /= 100.0;
  this->mpGLViewport->setZoomFactor(n);
}

void CQLayoutMainWindow::slotResetView()
{
  // check the 100% zoom entry
  disconnect(mpZoomMenu, SIGNAL(activated(int)), this, SLOT(slotZoomItemActivated(int)));
  this->mpZoomMenu->setItemChecked(1, false);
  this->mpZoomMenu->setItemChecked(2, false);
  this->mpZoomMenu->setItemChecked(3, false);
  this->mpZoomMenu->setItemChecked(4, false);
  this->mpZoomMenu->setItemChecked(5, false);
  this->mpZoomMenu->setItemChecked(10, false);
  this->mpZoomMenu->setItemChecked(20, false);
  this->mpZoomMenu->setItemChecked(30, false);
  this->mpZoomMenu->setItemChecked(40, false);
  this->mpZoomMenu->setItemChecked(50, false);
  this->mpZoomMenu->setItemChecked(100, true);
  this->mpZoomMenu->setItemChecked(150, false);
  this->mpZoomMenu->setItemChecked(200, false);
  this->mpZoomMenu->setItemChecked(300, false);
  this->mpZoomMenu->setItemChecked(400, false);
  this->mpZoomMenu->setItemChecked(500, false);
  connect(mpZoomMenu, SIGNAL(activated(int)), this, SLOT(slotZoomItemActivated(int)));
  // update toolbar
  disconnect(this->mpZoomComboBox, SIGNAL(activated(int)), this, SLOT(slotActivated(int)));
  this->mpZoomComboBox->setCurrentItem(this->mpZoomMenu->indexOf(100));
  connect(this->mpZoomComboBox, SIGNAL(activated(int)), this, SLOT(slotActivated(int)));
  this->mpGLViewport->resetView();
}

void CQLayoutMainWindow::slotZoomItemActivated(int id)
{
  // if the item is not checked, uncheck all other and check this one
  // set the zoom factor
  if (!this->mpZoomMenu->isItemChecked(id))
    {
      disconnect(mpZoomMenu, SIGNAL(activated(int)), this, SLOT(slotZoomItemActivated(int)));
      this->mpZoomMenu->setItemChecked(1, false);
      this->mpZoomMenu->setItemChecked(2, false);
      this->mpZoomMenu->setItemChecked(3, false);
      this->mpZoomMenu->setItemChecked(4, false);
      this->mpZoomMenu->setItemChecked(5, false);
      this->mpZoomMenu->setItemChecked(10, false);
      this->mpZoomMenu->setItemChecked(20, false);
      this->mpZoomMenu->setItemChecked(30, false);
      this->mpZoomMenu->setItemChecked(40, false);
      this->mpZoomMenu->setItemChecked(50, false);
      this->mpZoomMenu->setItemChecked(100, false);
      this->mpZoomMenu->setItemChecked(150, false);
      this->mpZoomMenu->setItemChecked(200, false);
      this->mpZoomMenu->setItemChecked(300, false);
      this->mpZoomMenu->setItemChecked(400, false);
      this->mpZoomMenu->setItemChecked(500, false);
      this->mpZoomMenu->setItemChecked(id, true);
      QString text = this->mpZoomMenu->text(id);
      this->setZoomFactor(text.latin1());
      connect(mpZoomMenu, SIGNAL(activated(int)), this, SLOT(slotZoomItemActivated(int)));
      // update toolbar
      disconnect(this->mpZoomComboBox, SIGNAL(activated(int)), this, SLOT(slotActivated(int)));
      this->mpZoomComboBox->setCurrentItem(this->mpZoomMenu->indexOf(id));
      connect(this->mpZoomComboBox, SIGNAL(activated(int)), this, SLOT(slotActivated(int)));
    }
}

void CQLayoutMainWindow::slotZoomIn()
{
  int ids[] = {1, 2, 3, 4, 5, 10, 20, 30, 40, 50, 100, 150, 200, 300, 400, 500};
  int checkedItem = 0;
  unsigned int i, iMax = 15;
  for (i = 0;i < iMax;++i)
    {
      if (this->mpZoomMenu->isItemChecked(ids[i]))
        {
          checkedItem = i;
          break;
        }
    }
  if (checkedItem != 14)
    {
      slotZoomItemActivated(ids[++checkedItem]);
    }
}

void CQLayoutMainWindow::slotZoomOut()
{
  int ids[] = {1, 2, 3, 4, 5, 10, 20, 30, 40, 50, 100, 150, 200, 300, 400, 500};
  int checkedItem = 0;
  unsigned int i, iMax = 15;
  for (i = 0;i < iMax;++i)
    {
      if (this->mpZoomMenu->isItemChecked(ids[i]))
        {
          checkedItem = i;
          break;
        }
    }
  if (checkedItem != 0)
    {
      slotZoomItemActivated(ids[--checkedItem]);
    }
}

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
  C_INT32 currentStep = this->getCurrentStep();
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
  C_INT32 currentStep = this->getCurrentStep();
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

void CQLayoutMainWindow::slotViewActivated(int id)
{
  switch (id)
    {
    case 1001:
      if (!this->mpViewMenu->isItemChecked(id))
        {
          this->mpParaPanel->show();
        }
      else
        {
          this->mpParaPanel->hide();
        }
      this->mpViewMenu->setItemChecked(id, !this->mpViewMenu->isItemChecked(id));
      break;
    case 1002:
      if (!this->mpViewMenu->isItemChecked(id))
        {
          this->mpValTable->show();
        }
      else
        {
          this->mpValTable->hide();
        }
      this->mpViewMenu->setItemChecked(id, !this->mpViewMenu->isItemChecked(id));
      break;
    case 1003:
      if (!this->mpViewMenu->isItemChecked(id))
        {
          this->mpFrame->show();
        }
      else
        {
          this->mpFrame->hide();
        }
      this->mpViewMenu->setItemChecked(id, !this->mpViewMenu->isItemChecked(id));
      break;
    case 1004:
      if (!this->mpViewMenu->isItemChecked(id))
        {
          this->mpToolbar->show();
        }
      else
        {
          this->mpToolbar->hide();
        }
      this->mpViewMenu->setItemChecked(id, !this->mpViewMenu->isItemChecked(id));
      break;
    default:
      break;
    }
  // if all object in the info box are hidden, we hide the info box
  if (this->mpViewMenu->isItemChecked(1001) == FALSE && this->mpViewMenu->isItemChecked(1002) == FALSE /*&& this->mpViewMenu->isItemChecked(1003) == FALSE*/)
    {
      this->mpInfoBox->hide();
    }
  else
    {
      this->mpInfoBox->show();
    }
}

void CQLayoutMainWindow::slotLoopActivated()
{
  this->mLooping = !this->mpPlayMenu->isItemChecked(this->mLoopItemId);
  this->mpPlayMenu->setItemChecked(this->mLoopItemId, this->mLooping);
}
