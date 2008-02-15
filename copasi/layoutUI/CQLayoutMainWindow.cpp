// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.cpp,v $
//   $Revision: 1.50 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/02/15 11:48:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qwt_slider.h>
#include <qvaluelist.h>
#include <qmessagebox.h>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "layout/CListOfLayouts.h"
#include "layout/CLayout.h"
#include "layout/CLBase.h"
#include "CQLayoutMainWindow.h"
#include "CQGLNetworkPainter.h"
#include "NodeSizePanel.h"

//#include "sbmlDocumentLoader.h"
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

CQLayoutMainWindow::CQLayoutMainWindow(QWidget *parent, const char *name) : QMainWindow(parent, name)
{
  resizeToggle = true;
  dataPresent = false;
  pVisParameters = new CVisParameters();
  setCaption(tr("Reaction network graph"));
  createActions();
  createMenus();

  //mainWidget = new QWidget;
  mainBox = new QVBox(this);

  // create split window with parameter panel and graph panel
  QSplitter *splitter = new QSplitter(Qt::Horizontal, mainBox);
  splitter->setCaption("Test");

  //QLabel *label = new QLabel(splitter, "Test Label", 0);
  //QTextEdit *testEditor = new QTextEdit(splitter);
  paraPanel = new ParaPanel(splitter);

  // create sroll view
  scrollView = new QScrollView(splitter);
  scrollView->setCaption("Network Graph Viewer");
  //scrollView->viewport()->setPaletteBackgroundColor(QColor(255,255,240));
  scrollView->viewport()->setPaletteBackgroundColor(QColor(219, 235, 255));
  //scrollView->viewport()->setMouseTracking(TRUE);
  // Create OpenGL widget
  CListOfLayouts *pLayoutList;
  if (CCopasiDataModel::Global != NULL)
    {
      pLayoutList = CCopasiDataModel::Global->getListOfLayouts();
    }
  else
    pLayoutList = NULL;

  glPainter = new CQGLNetworkPainter(scrollView->viewport(), "Network layout");
  if (pLayoutList != NULL)
    {
      CLayout * pLayout;
      if (pLayoutList->size() > 0)
        {
          pLayout = (*pLayoutList)[0];
          CLDimensions dim = pLayout->getDimensions();
          CLPoint c1;
          CLPoint c2(dim.getWidth(), dim.getHeight());
          glPainter->setGraphSize(c1, c2);
          glPainter->createGraph(pLayout); // create local data structures
          // now zoom graph so that it fits into the panel
          // --> is done in resize method
          //C_FLOAT64 w = 200.0; // initial width of graph panel
          //C_FLOAT64 h = 250.0; // initial height of graph panel
          //C_FLOAT64 z = ((w / dim.getWidth()) < (h / dim.getHeight())) ? w / dim.getWidth() : h / dim.getHeight();
          //std::cout << "zoom by. " << z << std::endl;
          //glPainter->zoomGraph(z);
          //glPainter->drawGraph(); // create display list
        }
    }
  // put OpenGL widget into scrollView
  scrollView->addChild(glPainter);

  QValueList<int> sizeList = splitter->sizes();
  if (sizeList.size() >= 2)
    {
      QValueList<int>::Iterator it = sizeList.begin();
      (*it) = paraPanel->width();
      ++it;
      (*it) = scrollView->width();
    }
  splitter->setSizes(sizeList);
  splitter->setResizeMode(paraPanel, QSplitter::KeepSize);

  frame = new QFrame(mainBox);
  //bottomBox = new QBox(mainBox);
  //bottomBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  startIcon = createStartIcon();
  stopIcon = createStopIcon();

  startStopButton = new QPushButton(frame, "start/stop button");

  connect(startStopButton, SIGNAL(clicked()), this, SLOT(startAnimation()));
  startStopButton->setIconSet(startIcon);
  startStopButton->setEnabled(true);

  timeSlider = new QwtSlider(frame, Qt::Horizontal, QwtSlider::BottomScale, QwtSlider::BgTrough);
  timeSlider->setRange(0, 100, 1, 0);
  timeSlider->setValue(0.0);
  this->timeSlider->setEnabled(false);

  timeSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  frame->setFixedHeight(55);
  //timeSlider->setTickmarks(QSlider::Below);
  //timeSlider->setDisabled(TRUE);
  connect(timeSlider, SIGNAL(valueChanged(double)),
          this, SLOT(showStep(double)));

  QGridLayout* bottomBoxlayout = new QGridLayout(frame, 2, 2, 3, 6);
  bottomBoxlayout->addMultiCellWidget(timeSlider, 0, 1, 1, 1, Qt::AlignTop);
  bottomBoxlayout->addWidget(startStopButton, 0, 0);
  QSpacerItem* theSpacer = new QSpacerItem(20, 20);
  bottomBoxlayout->addItem(theSpacer, 1, 0);

  setCentralWidget(mainBox);
  loadData(); // try to load data (if already present)

  this->show();
  //glPainter->drawGraph();
}

bool CQLayoutMainWindow::getAnimationRunning()
{
  if (pVisParameters != NULL)
    {
      return pVisParameters->animationRunning;
    }
  else
    return false;
}

void CQLayoutMainWindow::setAnimationRunning(bool animationRunningP)
{
  if (pVisParameters != NULL)
    {
      pVisParameters->animationRunning = animationRunningP;
    }
}

C_FLOAT64 CQLayoutMainWindow::getMinNodeSize()
{
  C_FLOAT64 minNodeSize = 10.0;
  if (pVisParameters != NULL)
    {

      //       if ((pVisParameters->mappingMode == CVisParameters::SIZE_DIAMETER_MODE) ||
      //           (pVisParameters->mappingMode == CVisParameters::SIZE_AREA_MODE))
      minNodeSize = pVisParameters->minNodeSize;
      //       else
      //         minNodeSize = 0.0; // color mode means: min h-value = 0;
    }
  return minNodeSize;
}

C_FLOAT64 CQLayoutMainWindow::getMaxNodeSize()
{
  C_FLOAT64 maxNodeSize = 100.0;
  if (pVisParameters != NULL)
    {
      //       if ((pVisParameters->mappingMode == CVisParameters::SIZE_DIAMETER_MODE) ||
      //           (pVisParameters->mappingMode == CVisParameters::SIZE_AREA_MODE))
      maxNodeSize = pVisParameters->maxNodeSize;
      //       else
      //         maxNodeSize = 359.0; // color mode means: max h-value < 360;
    }
  return maxNodeSize;
}

void CQLayoutMainWindow::setMinNodeSize(C_FLOAT64 minNdSize)
{
  if (pVisParameters != NULL)
    pVisParameters->minNodeSize = minNdSize;
}

void CQLayoutMainWindow::setMaxNodeSize(C_FLOAT64 maxNdSize)
{
  if (pVisParameters != NULL)
    pVisParameters->maxNodeSize = maxNdSize;
}

C_INT32 CQLayoutMainWindow::getStepsPerSecond()
{
  if (pVisParameters != NULL)
    {
      return pVisParameters->stepsPerSecond;
    }
  else
    return 2;
}

void CQLayoutMainWindow::setStepsPerSecond(C_INT16 val)
{
  if (pVisParameters != NULL)
    {
      pVisParameters->stepsPerSecond = val;
    }
}

C_INT16 CQLayoutMainWindow::getScalingMode()
{
  if (pVisParameters != NULL)
    {
      return pVisParameters->scalingMode;
    }
  else
    return CVisParameters::INDIVIDUAL_SCALING;
}

C_INT16 CQLayoutMainWindow::getMappingMode()
{
  if (pVisParameters != NULL)
    {
      return pVisParameters->mappingMode;
    }
  else
    return CVisParameters::SIZE_DIAMETER_MODE; // default mode
}

void CQLayoutMainWindow::createActions()
{
  openSBMLFile = new QAction("SBML",
                             "Load SBML file",
                             CTRL + Key_F,
                             this);
  openSBMLFile->setStatusTip("Load SBML file with/without layout");
  connect(openSBMLFile, SIGNAL(activated()) , this, SLOT(loadSBMLFile()));

  //   openDataFile = new QAction("data",
  //                              "Load Simulation Data",
  //                              CTRL + Key_D,
  //                              this);
  //   openDataFile->setStatusTip("Load simulation data");
  //   connect(openDataFile, SIGNAL(activated()), this, SLOT(loadData()));

  closeAction = new QAction ("close",
                             "Close Window",
                             CTRL + Key_Q ,
                             this);
  closeAction->setStatusTip("Close Layout Window");
  connect(closeAction, SIGNAL(activated()), this, SLOT(closeApplication()));

  runAnimation = new QAction("animate",
                             "Run animation",
                             CTRL + Key_A,
                             this);
  runAnimation->setStatusTip("show complete animation sequence of current times series");
  connect(runAnimation, SIGNAL(activated()), this, SLOT(showAnimation()));
  runAnimation->setEnabled(true);
  dataPresent = false;

  rectangularShape = new QAction ("rectangle",
                                  "rectangle",
                                  CTRL + Key_R ,
                                  this);
  rectangularShape->setStatusTip("Show labels as rectangles");
  connect(rectangularShape, SIGNAL(activated()), this, SLOT(mapLabelsToRectangles()));

  circularShape = new QAction ("circle",
                               "circle",
                               CTRL + Key_C ,
                               this);
  connect(circularShape, SIGNAL(activated()), this, SLOT(mapLabelsToCircles()));
  circularShape->setStatusTip("Show labels as circles");

  miMaNodeSizes = new QAction ("minmax",
                               "Set Min/Max Node Sizes",
                               CTRL + Key_M,
                               this);

  connect(miMaNodeSizes, SIGNAL(activated()), this, SLOT(changeMinMaxNodeSizes()));
  miMaNodeSizes->setToolTip("Change Min/Max for node sizes within animation");

  automaticRescaleToggle = new QAction ("autoresize",
                                        "Automatic Rescaling of Graph",
                                        CTRL + Key_R,
                                        this);

  automaticRescaleToggle->setToggleAction(true);
  automaticRescaleToggle->setOn(true);
  //automaticRescaleToggle = new QCheckBox("Automatic Rescaling of Graph", this);
  //automaticRescaleToggle->setChecked(true);

  connect(automaticRescaleToggle, SIGNAL(toggled(bool)), this, SLOT(toggleAutomaticRescaling(bool)));
  automaticRescaleToggle->setToolTip("Enable/disable automatic rescaling of graph when panel is resized");
}

void CQLayoutMainWindow::createMenus()
{
  fileMenu = new QPopupMenu(this);
  openSBMLFile->addTo(fileMenu);
  //openDataFile->addTo(fileMenu);
  fileMenu->insertSeparator();
  closeAction->addTo(fileMenu);

  actionsMenu = new QPopupMenu(this);
  runAnimation->addTo(actionsMenu);

  labelShapeMenu = new QPopupMenu(this);

  rectangularShape->addTo(labelShapeMenu);
  circularShape->addTo(labelShapeMenu);

  optionsMenu = new QPopupMenu(this);
  optionsMenu->insertItem("Shape of Label", labelShapeMenu);
  miMaNodeSizes->addTo(optionsMenu);
  automaticRescaleToggle->addTo(optionsMenu);

  menuBar()->insertItem("File", fileMenu);
  menuBar()->insertItem("Actions", actionsMenu);
  menuBar()->insertItem("Options", optionsMenu);
}

//void CQLayoutMainWindow::contextMenuEvent(QContextMenuEvent *cme){
// QPopupMenu *contextMenu = new QPopupMenu(this);
// exitAction->addTo(contextMenu);
// contextMenu->exec(cme->globalPos());
//}

void CQLayoutMainWindow::loadSBMLFile()
{
  //string filename = "/localhome/ulla/project/data/peroxiShortNew.xml"; // test file
  //string filename = "/home/ulla/project/simulation/data/peroxiShortNew.xml";
  //SBMLDocumentLoader docLoader;
  //network *networkP = docLoader.loadDocument(filename.c_str());

  //glPainter->createGraph(networkP);
  std::cout << "load SBMLfile" << std::endl;
  CListOfLayouts *pLayoutList;
  if (CCopasiDataModel::Global != NULL)
    {
      pLayoutList = CCopasiDataModel::Global->getListOfLayouts();
    }
  else
    pLayoutList = NULL;

  glPainter = new CQGLNetworkPainter(scrollView->viewport());
  if (pLayoutList != NULL)
    {
      CLayout * pLayout;
      if (pLayoutList->size() > 0)
        {
          pLayout = (*pLayoutList)[0];
          CLDimensions dim = pLayout->getDimensions();
          CLPoint c1;
          CLPoint c2(dim.getWidth(), dim.getHeight());
          glPainter->setGraphSize(c1, c2);
          glPainter->createGraph(pLayout); // create local data structures
          //glPainter->drawGraph(); // create display list
        }
    }
}

void CQLayoutMainWindow::mapLabelsToCircles()
{
  if (glPainter != NULL)
    {
      glPainter->mapLabelsToCircles();
      if (glPainter->getNumberOfSteps() > 0)
        showStep(this->timeSlider->value());
    }
}

void CQLayoutMainWindow::mapLabelsToRectangles()
{
  if (glPainter != NULL)
    {
      glPainter->mapLabelsToRectangles();
    }
}

void CQLayoutMainWindow::changeMinMaxNodeSizes()
{
  //std::cout << "change min/max values for node sizes" << std::endl;
  NodeSizePanel *panel = new NodeSizePanel(this);
  panel->exec();
}

void CQLayoutMainWindow::loadData()
{
  bool successfulP = glPainter->createDataSets();
  if (successfulP)
    {
      this->timeSlider->setEnabled(true);
      //this->runAnimation->setEnabled(true);
      //this->startStopButton->setEnabled(true);
      this->dataPresent = true;
      paraPanel->enableStepNumberChoice();
      int maxVal = glPainter->getNumberOfSteps();
      //std::cout << "number of steps: " << maxVal << std::endl;
      this->timeSlider->setRange(0, maxVal - 1);
      //pVisParameters->numberOfSteps = maxVal;
      glPainter->updateGL();
      if (this->glPainter->isCircleMode())
        showStep(this->timeSlider->value());
    }
}

void CQLayoutMainWindow::showAnimation()
{
  startAnimation();
}

void CQLayoutMainWindow::startAnimation()
{
  if (!this->dataPresent)
    this->loadData(); // look for data
  if (this->dataPresent)
    {// only if time series data present
      pVisParameters->animationRunning = true;
      this->timeSlider->setEnabled(false);
      glPainter->runAnimation();

      //exchange icon and callback for start/stop button
      disconnect(startStopButton, SIGNAL(clicked()), this, SLOT(startAnimation()));
      connect(startStopButton, SIGNAL(clicked()), this, SLOT(stopAnimation()));
      startStopButton->setIconSet(stopIcon);
      paraPanel->disableParameterChoice();
      paraPanel->disableStepNumberChoice();
    }
  else
    {
      QMessageBox::warning (this, "Missing Data", "No data found: \nYou first have to create a time course.", QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
    }
}

void CQLayoutMainWindow::stopAnimation()
{
  pVisParameters->animationRunning = false;
  this->timeSlider->setEnabled(true);

  connect(startStopButton, SIGNAL(clicked()), this, SLOT(startAnimation()));
  disconnect(startStopButton, SIGNAL(clicked()), this, SLOT(stopAnimation()));
  startStopButton->setIconSet(startIcon);
  paraPanel->enableParameterChoice();
  paraPanel->enableStepNumberChoice();
}

void CQLayoutMainWindow::endOfAnimationReached()
{
  //this->startStopButton->clicked();
  //emit this->startStopButton->clicked();
  this->stopAnimation();
}

void CQLayoutMainWindow::showStep(double i)
{

  glPainter->showStep(static_cast<int>(i));
  glPainter->updateGL();
  paraPanel->setStepNumber(static_cast<int>(i));
}

void CQLayoutMainWindow::changeStepValue(C_INT32 i)
{
  timeSlider->setValue(i);
  //showStep(i);
}

void CQLayoutMainWindow::setIndividualScaling()
{
  pVisParameters->scalingMode = pVisParameters->INDIVIDUAL_SCALING;
  glPainter->rescaleDataSets(pVisParameters->INDIVIDUAL_SCALING);
  showStep(this->timeSlider->value());
}

void CQLayoutMainWindow::setGlobalScaling()
{
  pVisParameters->scalingMode = pVisParameters->GLOBAL_SCALING;
  glPainter->rescaleDataSets(pVisParameters->GLOBAL_SCALING);
  showStep(this->timeSlider->value());
}

void CQLayoutMainWindow::setSizeMode()
{
  pVisParameters->mappingMode = CVisParameters::SIZE_DIAMETER_MODE;
  //glPainter->changeMinMaxNodeSize(getMinNodeSize(), getMaxNodeSize(),pVisParameters->scalingMode);
  glPainter->rescaleDataSetsWithNewMinMax(0.0, 240.0, getMinNodeSize(), getMaxNodeSize(), pVisParameters->scalingMode); // only [0.240] of possible HSV values (not fill circle in order to get good color range)
  showStep(this->timeSlider->value());
  //std::cout << "show Step: " << this->timeSlider->value() << std::endl;
}

void CQLayoutMainWindow::setColorMode()
{
  pVisParameters->mappingMode = CVisParameters::COLOR_MODE;
  //glPainter->changeMinMaxNodeSize(pVisParameters->scalingMode); // rescaling, because min and max node size changed
  glPainter->rescaleDataSetsWithNewMinMax(getMinNodeSize(), getMaxNodeSize(), 0.0, 240.0, pVisParameters->scalingMode); // rescaling, because min and max node size changed (interpretation as color value takes place elsewhere),only [0.240] of possible HSV values (not fill circle in order to get good color range)
  showStep(this->timeSlider->value());
  //std::cout << "showStep: " << this->timeSlider->value() << std::endl;
}

void CQLayoutMainWindow::setValueOnSlider(C_INT32 val)
{
  timeSlider->setValue(val);
}

// set minimum possible node size for animation
void CQLayoutMainWindow::setMinValue(C_INT32 minNdSize)
{
  glPainter->rescaleDataSetsWithNewMinMax(getMinNodeSize(), getMaxNodeSize(), minNdSize, getMaxNodeSize(), pVisParameters->scalingMode);
  setMinNodeSize(minNdSize);
  showStep(this->timeSlider->value());
}

// set maximum possible node size for animation
void CQLayoutMainWindow::setMaxValue(C_INT32 maxNdSize)
{
  glPainter->rescaleDataSetsWithNewMinMax(getMinNodeSize(), getMaxNodeSize(), getMinNodeSize(), maxNdSize, pVisParameters->scalingMode);
  setMaxNodeSize(maxNdSize);
  showStep(this->timeSlider->value());
}

void CQLayoutMainWindow::setMinAndMaxValue(C_INT32 minNdSize, C_INT32 maxNdSize)
{
  //std::cout << "min old: " << getMinNodeSize() << "  max  old:  " << getMaxNodeSize() << "  min new: " << minNdSize << "  max new: " << maxNdSize << std::endl;
  glPainter->rescaleDataSetsWithNewMinMax(getMinNodeSize(), getMaxNodeSize(), minNdSize, maxNdSize, pVisParameters->scalingMode);
  setMinNodeSize(minNdSize);
  setMaxNodeSize(maxNdSize);
  showStep(this->timeSlider->value());
}

void CQLayoutMainWindow::closeApplication()
{
  close();
}

void CQLayoutMainWindow::closeEvent(QCloseEvent *event)
{
  if (maybeSave())
    {
      //writeSettings();
      event->accept();
    }
  else
    {
      event->ignore();
    }
}

void CQLayoutMainWindow::toggleAutomaticRescaling(bool isChecked)
{
  resizeToggle = isChecked;
}

// when resize of panel occurs, the graph should be resized accordingly
void CQLayoutMainWindow::resizeEvent(QResizeEvent *ev)
{
  //std::cout << "event type: " << ev->type() << std::endl;
  if (resizeToggle)
    {// if automatic rescaling of graph is enabled
      int w = scrollView->width(); // ev->size().width();
      int h = scrollView->height(); // ev->size().height();
      //std::cout << "scroll view "  << w << "  "  << h << std::endl;

      const CLPoint& c1 = glPainter->getGraphMin();
      const CLPoint& c2 = glPainter->getGraphMax();

      // now zoom graph according to new panel size
      C_FLOAT64 z = ((w / c2.getX()) < (h / c2.getY())) ? w / c2.getX() : h / c2.getY();
      //std::cout << "zoom factor in RESIZE: "  << z << std::endl;
      glPainter->zoomGraph(z);
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
          //uint *p = (uint *)img.scanLine(y) + x;
          //*p = qRgb(0,0,255);
        }
    }

  C_INT32 delta = 0;
  img.setColor(1, qRgb(255, 0, 0));
  for (x = 3;x < w - 3;x++)
    {
      for (y = 3 + delta;y < h - 3 - delta;y++)
        {
          img.setPixel(x, y, 1);
          //uint *p = (uint *)img.scanLine(y) + x;
          //*p = qRgb(0,0,255);
        }
      //std::cout << "X: " << x << "  delta: " << delta <<std::endl;
      if (fmod((double) x, 2.0) == 0)
        delta++;
    }

  //QPixmap *pixmap = new QPixmap(20,20);
  QPixmap *pixmap = new QPixmap();
  pixmap->convertFromImage(img);
  //pixmap->fill(QColor(0,255,0));
  QIconSet *iconset = new QIconSet(*pixmap);
  return *iconset;
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
          //uint *p = (uint *)img.scanLine(y) + x;
          //*p = qRgb(0,0,255);
        }
    }

  C_INT32 delta = 4;
  img.setColor(1, qRgb(255, 0, 0));
  for (x = (delta - 1);x <= (w - delta);x++)
    {
      for (y = (delta - 1);y <= (h - delta);y++)
        {
          img.setPixel(x, y, 1);
          //uint *p = (uint *)img.scanLine(y) + x;
          //*p = qRgb(0,0,255);
        }
    }

  QPixmap *pixmap = new QPixmap();
  //pixmap->fill(QColor(255, 0, 0));
  pixmap->convertFromImage(img);
  QIconSet *iconset = new QIconSet(*pixmap);
  return *iconset;
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

//int main(int argc, char *argv[]) {
// //cout << argc << "------" << *argv << endl;
// QApplication app(argc,argv);
// CQLayoutMainWindow win;
// //app.setMainWidget(&gui);
// win.resize(400,230);
// win.show();
// return app.exec();
//}
