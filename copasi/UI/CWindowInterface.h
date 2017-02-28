// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CWindowInterface_H
#define CWindowInterface_H

class QMenu;
class QWidget;
class CopasiUI3Window;

#include <QMainWindow>
#include <QtCore/QString>

class CWindowInterface : public QMainWindow
{
  Q_OBJECT
public:
  CWindowInterface(QWidget *parent = NULL, Qt::WindowFlags flags = NULL);
  virtual ~CWindowInterface();

  virtual QMenu *getWindowMenu() const = 0;

  /**
   * Saves the current window to the given filename.
   *
   * This default implementation does nothing
   */
  virtual void saveToFile(const QString& fileName) const;

  void addToMainWindow(CopasiUI3Window *window = NULL);
  void removeFromMainWindow(CopasiUI3Window *window = NULL);
};

#endif // CWindowInterface_H
