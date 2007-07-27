// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.cpp,v $
//   $Revision: 1.26 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/07/27 10:05:23 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qwt_slider.h>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "layout/CListOfLayouts.h"
#include "layout/CLayout.h"
#include "layout/CLBase.h"
#include "CQLayoutMainWindow.h"

//#include "sbmlDocumentLoader.h"
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

CQLayoutMainWindow::CQLayoutMainWindow(QWidget *parent, const char *name) : QMainWindow(parent, name)
{
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
          //glPainter->drawGraph(); // create display list
        }
    }
  // put OpenGL widget into scrollView
  scrollView->addChild(glPainter);

  bottomBox = new QHBox(mainBox);
  //bottomBox->setMinimumHeight(15);
  //bottomBox->setMinimumWidth(100);

  startIcon = createStartIcon();
  stopIcon = createStopIcon();
  startStopButton = new QPushButton(bottomBox, "start/stop button");
  connect(startStopButton, SIGNAL(clicked()), this, SLOT(startAnimation()));
  startStopButton->setIconSet(startIcon);
  startStopButton->setEnabled(false);

  timeSlider = new QwtSlider(bottomBox, Qt::Horizontal, QwtSlider::BottomScale, QwtSlider::BgTrough);
  timeSlider->setRange(0, 100, 1, 0);
  timeSlider->setValue(0.0);
  this->timeSlider->setEnabled(false);

  timeSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  //timeSlider->setTickmarks(QSlider::Below);
  //timeSlider->setDisabled(TRUE);
  connect(timeSlider, SIGNAL(valueChanged(double)),
          this, SLOT(showStep(double)));

  setCentralWidget(mainBox);
  this->show();
  //glPainter->drawGraph();
}

void CQLayoutMainWindow::createActions()
{
  openSBMLFile = new QAction("SBML",
                             "Load SBML file",
                             CTRL + Key_F,
                             this);
  openSBMLFile->setStatusTip("Load SBML file with/without layout");
  connect(openSBMLFile, SIGNAL(activated()) , this, SLOT(loadSBMLFile()));

  openDataFile = new QAction("data",
                             "Load Simulation Data",
                             CTRL + Key_D,
                             this);
  openDataFile->setStatusTip("Load simulation data");
  connect(openDataFile, SIGNAL(activated()), this, SLOT(loadData()));

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
}

void CQLayoutMainWindow::createMenus()
{
  fileMenu = new QPopupMenu(this);
  openSBMLFile->addTo(fileMenu);
  openDataFile->addTo(fileMenu);
  fileMenu->insertSeparator();
  closeAction->addTo(fileMenu);

  actionsMenu = new QPopupMenu(this);
  runAnimation->addTo(actionsMenu);

  labelShapeMenu = new QPopupMenu(this);

  rectangularShape->addTo(labelShapeMenu);
  circularShape->addTo(labelShapeMenu);

  optionsMenu = new QPopupMenu(this);
  optionsMenu->insertItem("Shape of Label", labelShapeMenu);

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
    }
}

void CQLayoutMainWindow::mapLabelsToRectangles()
{
  if (glPainter != NULL)
    {
      glPainter->mapLabelsToRectangles();
    }
}

void CQLayoutMainWindow::loadData()
{
  bool successfulP = glPainter->createDataSets();
  if (successfulP)
    {
      this->timeSlider->setEnabled(true);
      this->startStopButton->setEnabled(true);
      int maxVal = glPainter->getNumberOfSteps();
      //std::cout << "number of steps: " << maxVal << std::endl;
      this->timeSlider->setRange(0, maxVal);
      CVisParameters::numberOfSteps = maxVal;
      glPainter->updateGL();
    }
}

void CQLayoutMainWindow::showAnimation()
{
  startAnimation();
}

void CQLayoutMainWindow::startAnimation()
{
  CVisParameters::animationRunning = true;
  this->timeSlider->setEnabled(false);
  glPainter->runAnimation();

  //exchange icon and callback for start/stop button
  disconnect(startStopButton, SIGNAL(clicked()), this, SLOT(startAnimation()));
  connect(startStopButton, SIGNAL(clicked()), this, SLOT(stopAnimation()));
  startStopButton->setIconSet(stopIcon);
  paraPanel->disableParameterChoice();
}

void CQLayoutMainWindow::stopAnimation()
{
  CVisParameters::animationRunning = false;
  this->timeSlider->setEnabled(true);

  connect(startStopButton, SIGNAL(clicked()), this, SLOT(startAnimation()));
  disconnect(startStopButton, SIGNAL(clicked()), this, SLOT(stopAnimation()));
  startStopButton->setIconSet(startIcon);
  paraPanel->enableParameterChoice();
}

void CQLayoutMainWindow::endOfAnimationReached()
{
  //this->startStopButton->clicked();
  //emit this->startStopButton->clicked();
  this->stopAnimation();
}

void CQLayoutMainWindow::showStep(double i)
{

  glPainter->showStep((int) i);
  glPainter->updateGL();
}

void CQLayoutMainWindow::changeStepValue(C_INT32 i)
{
  timeSlider->setValue(i);
  //showStep(i);
}

void CQLayoutMainWindow::setIndividualScaling()
{
  CVisParameters::scalingMode == CVisParameters::INDIVIDUAL_SCALING;
  glPainter->rescaleDataSets(CVisParameters::INDIVIDUAL_SCALING);
}

void CQLayoutMainWindow::setGlobalScaling()
{
  CVisParameters::scalingMode == CVisParameters::GLOBAL_SCALING;
  glPainter->rescaleDataSets(CVisParameters::GLOBAL_SCALING);
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
