// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <copasi/UI/CWindowInterface.h>
#include <copasi/UI/copasiui3window.h>

CWindowInterface::CWindowInterface(QWidget *parent /*= NULL*/, Qt::WindowFlags flags /*= NULL*/)
  : QMainWindow(parent, flags)
{
}

CWindowInterface::~CWindowInterface()
{
}

void CWindowInterface::addToMainWindow(CopasiUI3Window *window)
{
  if (window == NULL)
    window = CopasiUI3Window::getMainWindow();

  if (window != NULL)
    window->addWindow(this);
}

void CWindowInterface::saveToFile(const QString& fileName) const
{
  // by default nothing will be saved, overwrite to implement saving to file
}

void CWindowInterface::removeFromMainWindow(CopasiUI3Window *window)
{
  if (window == NULL)
    window = CopasiUI3Window::getMainWindow();

  if (window != NULL)
    window->removeWindow(this);
}
