// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include "copasi/UI/CQCheckModelWindow.h"
#include <iostream>

CQCheckModelWindow::CQCheckModelWindow(CopasiUI3Window * pMainWindow) :
  CWindowInterface(),
  mpMainWindow(pMainWindow)
{
  setupUi(this);

  // add a place holder menu, to be filled by the main window
  mpWindowMenu = menuBar()->addMenu("Window");

  textEdit->setReadOnly(true);

  addToMainWindow(mpMainWindow);

  setAttribute(Qt::WA_DeleteOnClose);
}

CQCheckModelWindow::~CQCheckModelWindow()
{
  removeFromMainWindow(mpMainWindow);
}

QMenu *CQCheckModelWindow::getWindowMenu() const
{
  return mpWindowMenu;
}

