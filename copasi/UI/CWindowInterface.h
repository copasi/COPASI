// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CWindowInterface_H
#define CWindowInterface_H

class QMenu;
class QWidget;
class CopasiUI3Window;

#include <QMainWindow>

class CWindowInterface : public QMainWindow
{
  Q_OBJECT
public:
  CWindowInterface(QWidget *parent = NULL, Qt::WindowFlags flags = NULL);
  virtual ~CWindowInterface();

  virtual QMenu *getWindowMenu() const = 0;

  void addToMainWindow(CopasiUI3Window *window = NULL);
  void removeFromMainWindow(CopasiUI3Window *window = NULL);
};

#endif CWindowInterface_H
