// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include <QSlider>
#include <QGridLayout>
#include <QPixmap>
#include <QCloseEvent>

#include <iostream>
#include <cmath>
#include <stdlib.h>

#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/CopasiFileDialog.h"
#include "copasi/layout/CLBase.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "CQNewMainWindow.h"
#include "CQCurrentValueTable.h"
#include "CQGLNetworkPainter.h"
#include "CQGLViewport.h"
#include "FontChooser.h"
#include "NodeSizePanel.h"
#include "ParaPanel.h"
#include "CQPlayerControlWidget.h"
#include "CQScreenshotOptionsDialog.h"

#include "copasi/resourcesUI/CQIconResource.h"

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

using namespace std;

const char *const CQLayoutMainWindow::ZOOM_FACTOR_STRINGS[] = {"1%", "2%", "3%", "4%", "5%", "10%", "20%", "25%", "30%", "40%", "50%", "75%", "100%", "150%", "200%", "300%", "400%", "500%", "1000%"};
const double CQLayoutMainWindow::ZOOM_FACTORS[] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.1, 0.2, 0.25, 0.3, 0.4, 0.5, 0.75, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 10.0};

CQLayoutMainWindow::CQLayoutMainWindow(QWidget *pParent):
  QFrame(pParent)
  , mpVisParameters(new CVisParameters)
  , mpParaPanel(new CQParaPanel)
  , mpValTable(new CQCurrentValueTable)
  , mpMainBox(new QFrame(this))
  , mpSplitter(new QSplitter(Qt::Horizontal, this->mpMainBox))
  , mpGLViewport(NULL)
  , mpTimeSlider(new QSlider(Qt::Horizontal))
  , mpFrame(new QFrame)
  , mpInfoBox(new QFrame)
  , mpControlWidget(new CQPlayerControlWidget)
  , mDataPresent(false)
  , mCurrentPlace()
  , mpZoomActionGroup(new QActionGroup(this))
  , mpLayout(NULL)
{
#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin
  QVBoxLayout *mainLayout = new QVBoxLayout(mpMainBox);
  QVBoxLayout *infoLayout = new QVBoxLayout(mpInfoBox);
  mpSplitter->addWidget(this->mpInfoBox);
  // create split window with parameter panel and graph panel
  mainLayout->addWidget(this->mpSplitter);
  infoLayout->addWidget(this->mpParaPanel);
  infoLayout->addWidget(this->mpValTable);
  this->mpInfoBox->setLayout(infoLayout);
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
  connect(this->mpControlWidget, SIGNAL(play()), this, SLOT(startAnimation()));
  connect(this->mpControlWidget, SIGNAL(pause()), this, SLOT(pauseAnimation()));
  connect(this->mpControlWidget, SIGNAL(stop()), this, SLOT(stopAnimation()));
  connect(this->mpControlWidget, SIGNAL(forward()), this, SLOT(forwardAnimation()));
  connect(this->mpControlWidget, SIGNAL(backward()), this, SLOT(backwardAnimation()));
  connect(this->mpControlWidget, SIGNAL(step_backward()), this, SLOT(stepBackwardAnimation()));
  connect(this->mpControlWidget, SIGNAL(step_forward()), this, SLOT(stepForwardAnimation()));
  this->mpTimeSlider->setRange(0, 100);
  this->mpTimeSlider->setValue(0);
  this->mpTimeSlider->setEnabled(false);
  this->mpTimeSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  connect(this->mpTimeSlider, SIGNAL(valueChanged(int)), this, SLOT(showStep(int)));
  QHBoxLayout *pGridLayout = new QHBoxLayout(mpFrame);
  pGridLayout->addWidget(this->mpControlWidget);
  pGridLayout->addWidget(this->mpTimeSlider);
  this->mpFrame->setLayout(pGridLayout);
  mainLayout->addWidget(this->mpFrame);
  this->mpMainBox->setLayout(mainLayout);
  this->QFrame::setLayout(new QVBoxLayout);
  this->layout()->addWidget(this->mpMainBox);
  connect(this->mpValTable, SIGNAL(valueChanged(int)), this, SLOT(parameterTableValueChanged(int)));
  this->mLooping = false;
  this->setTabOrder(this->mpGLViewport, this->mpToolbar);
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

void CQLayoutMainWindow::loadSBMLFile()
{
  CListOfLayouts *pLayoutList;
  CDataModel *pDataModel = CQNewMainWindow::dataModel(parent());

  if (pDataModel != NULL)
    {
      pLayoutList = pDataModel->getListOfLayouts();
    }
  else
    pLayoutList = NULL;

  mpGLViewport = new CQGLViewport(mpSplitter);

  if (pLayoutList != NULL)
    {
      CLayout *pLayout;

      if (pLayoutList->size() > 0)
        {
          pLayout = &pLayoutList->operator[](0);
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
      CQGLNetworkPainter *pPainter = this->mpGLViewport->getPainter();

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
  disconnect(this->mpValTable, SIGNAL(valueChanged(int)), this, SLOT(parameterTableValueChanged(int)));

  while ((key = mpGLViewport->getPainter()->getNodeNameEntry(i)) != "")
    {
      name = this->mpGLViewport->getPainter()->getNameForNodeKey(key);
      val = dataSet.getOrigValueForSpecies(key); // would be (- std::numeric_limits< C_FLOAT64 >::max()) if key not present
      mpValTable->setRowInTable(i, key, name, val);
      i++;
    }

  connect(this->mpValTable, SIGNAL(valueChanged(int)), this, SLOT(parameterTableValueChanged(int)));
}

void CQLayoutMainWindow::updateValueTable(CDataEntity dataSet)
{
  int i = 0;
  std::string key, name;
  C_FLOAT64 val;
  disconnect(this->mpValTable, SIGNAL(valueChanged(int)), this, SLOT(parameterTableValueChanged(int)));

  while ((key = mpGLViewport->getPainter()->getNodeNameEntry(i)) != "")
    {
      name = mpGLViewport->getPainter()->getNameForNodeKey(key);
      val = dataSet.getOrigValueForSpecies(key); // would be (- std::numeric_limits< C_FLOAT64 >::max()) if key not present

      if (mpValTable->numRows() > i)
        {
          mpValTable->updateRowInTable(i, val);
        }

      i++;
    }

  connect(this->mpValTable, SIGNAL(valueChanged(int)), this, SLOT(parameterTableValueChanged(int)));
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
    {
      // only if time series data present
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
  // get the parameters
  CQGLNetworkPainter *pPainter = this->mpGLViewport->getPainter();
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
      CQScreenshotOptionsDialog *pDialog = new CQScreenshotOptionsDialog(layoutX, layoutY, layoutWidth, layoutHeight,
          x, y, width, height, pPainter->width(), pPainter->height(), lastFrame, this);

      if (pDialog->exec() == QDialog::Accepted)
        {
          // ask for the filename
          // TODO use a nicer default filename
          QString fileName = CopasiFileDialog::getSaveFileName(this, "Save Image Dialog", CopasiFileDialog::getDefaultFileName(".png"), QString("PNG (*.png);;All files (*)"), QString("Choose a filename to save the image(s) under"));

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

void CQLayoutMainWindow::showStep(int i)
{
  this->mpControlWidget->setCurrentStep(static_cast<int>(i));
  mpGLViewport->getPainter()->showStep(static_cast<int>(i));
  mpGLViewport->getPainter()->updateGL();
  mpParaPanel->setStepNumber(static_cast<int>(i));
  CDataEntity *srcData = mpGLViewport->getPainter()->getDataSetAt(static_cast<int>(i));

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

QIcon CQLayoutMainWindow::createStartIcon()
{
  C_INT32 w = 19;
  C_INT32 h = 19;
  QImage img = QImage(w, h, QImage::Format_Indexed8);
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
  img.setNumColors(2);
#endif
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
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
  img.setNumColors(2);
#endif
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
  //  int ret = CQMessageBox::warning(this, "SimWiz",
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
  return zoom;
}

void CQLayoutMainWindow::slotResetView()
{
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

void CQLayoutMainWindow::setLayout(CLayout *pLayout)
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

CQPlayerControlWidget *CQLayoutMainWindow::getControlWidget()
{
  return this->mpControlWidget;
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
