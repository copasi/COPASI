// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#ifndef CQCHECKMODELWINDOW_H
#define CQCHECKMODELWINDOW_H

#include "copasi/UI/CWindowInterface.h"
#include "copasi/UI/ui_CQCheckModelWindow.h"

class QMenu;

class CQCheckModelWindow : public CWindowInterface, public Ui::CQCheckModelWindow
{
  Q_OBJECT
  
public:
  explicit CQCheckModelWindow(CopasiUI3Window * pMainWindow);

  virtual ~CQCheckModelWindow();

  //return a pointer to this plot windows 'window' menu.
  virtual QMenu *getWindowMenu() const;

private:
  CopasiUI3Window * mpMainWindow;
};

#endif // CQCHECKMODELWINDOW_H
