// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/03/02 10:56:33 $
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

  // create sroll view
  scrollView = new QScrollView(this);
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
  setCentralWidget(scrollView);
  scrollView->show();
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
                             "Load Simulation Data File",
                             CTRL + Key_D,
                             this);
  openDataFile->setStatusTip("Load simulation data file");
  connect(openDataFile, SIGNAL(activated()), this, SLOT(loadDataFile()));

  exitAction = new QAction ("exit",
                            "Exit SimWiz",
                            CTRL + Key_Q ,
                            this);
  exitAction->setStatusTip("Exit SimWiz");
  connect(exitAction, SIGNAL(activated()), this, SLOT(exitApplication()));
}

void CQLayoutMainWindow::createMenus()
{
  fileMenu = new QPopupMenu(this);
  openSBMLFile->addTo(fileMenu);
  openDataFile->addTo(fileMenu);
  fileMenu->insertSeparator();
  exitAction->addTo(fileMenu);

  menuBar()->insertItem("File", fileMenu);
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

void CQLayoutMainWindow::loadDataFile()
{}

void CQLayoutMainWindow::exitApplication()
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

bool CQLayoutMainWindow::maybeSave()
{
  //   if (modified) {
  int ret = QMessageBox::warning(this, "SimWiz",
                                 "Do you really want to quit?",
                                 //                   tr("Do you really want to quit?\n"
                                 //                      "XXXXXXXX"),
                                 QMessageBox::Yes | QMessageBox::Default,
                                 QMessageBox::No,
                                 QMessageBox::Cancel | QMessageBox::Escape);
  if (ret == QMessageBox::Yes)
    return true;
  else if (ret == QMessageBox::Cancel)
    return false;

  //   return true;
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
