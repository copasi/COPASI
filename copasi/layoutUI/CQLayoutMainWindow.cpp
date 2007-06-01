// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/06/01 10:40:16 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CopasiDataModel/CCopasiDataModel.h"
#include "layout/CListOfLayouts.h"
#include "layout/CLayout.h"
#include "layout/CLBase.h"
#include"CQLayoutMainWindow.h"
//#include "sbmlDocumentLoader.h"
#include <string>
#include <iostream>

using namespace std;

CQLayoutMainWindow::CQLayoutMainWindow(QWidget *parent, const char *name) : QMainWindow(parent, name)
{
  setCaption(tr("Reaction network graph"));
  createActions();
  createMenus();

  // create split window
  QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
  splitter->setCaption("Test");

  //QLabel *label = new QLabel(splitter, "Test Label", 0);
  //QTextEdit *testEditor = new QTextEdit(splitter);
  ParaPanel *paraPanel = new ParaPanel;

  timeSlider = new QSlider(Qt::Horizontal, splitter);
  timeSlider->setRange(0, 100);
  timeSlider->setValue(0);
  //timeSlider->setTickmarks(QSlider::Below);
  timeSlider->setDisabled(TRUE);
  connect(timeSlider, SIGNAL(valueChanged(int)),
          this, SLOT(showStep(int)));

  // create sroll view
  scrollView = new QScrollView(splitter);
  //scrollView = new QScrollView(this);
  scrollView->setCaption("Network Graph Viewer");
  //scrollView->viewport()->setPaletteBackgroundColor(QColor(255,255,240));
  scrollView->viewport()->setPaletteBackgroundColor(QColor(219, 235, 255));
  //scrollView->viewport()->setMouseTracking(TRUE);
  // Create OpenGL widget
  //cout << "viewport: " << scrollView.viewport() << endl;
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
  // put OpenGL widget into scrollView
  scrollView->addChild(glPainter);
  //setCentralWidget(scrollView);
  //scrollView->show();

  setCentralWidget(splitter);
  splitter->show();
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
      int maxVal = glPainter->getNumberOfSteps();
      //std::cout << "number of steps: " << maxVal << std::endl;
      this->timeSlider->setRange(0, maxVal);
      glPainter->updateGL();
    }
}

void CQLayoutMainWindow::showAnimation()
{
  glPainter->runAnimation();
}

void CQLayoutMainWindow::showStep(int i)
{
  glPainter->showStep(i);
  glPainter->updateGL();
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
