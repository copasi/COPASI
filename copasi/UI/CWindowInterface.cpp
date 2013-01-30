// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <UI/CWindowInterface.h>
#include <UI/copasiui3window.h>

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

void CWindowInterface::removeFromMainWindow(CopasiUI3Window *window)
{
  if (window == NULL)
    window = CopasiUI3Window::getMainWindow();

  if (window != NULL)
    window->removeWindow(this);
}
