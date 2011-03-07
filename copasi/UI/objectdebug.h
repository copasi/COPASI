// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/Attic/objectdebug.h,v $
//   $Revision: 1.13.2.3 $
//   $Name: Build-33 $
//   $Author: shoops $
//   $Date: 2011/01/26 13:30:09 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef OBJECTDEBUG_H
#define OBJECTDEBUG_H

#include <QVariant>
#include <iostream>
#include "ui_objectdebug.h"

class ObjectDebug : public QDialog, public Ui::ObjectDebug
{
  Q_OBJECT

public:
  ObjectDebug(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~ObjectDebug();

public slots:
  void update();
  virtual void writeDot();
  virtual void checkModel();

protected slots:
  virtual void languageChange();

private:
  void addObjectRecursive(QWidget * parent, const void * ptr);
  void init();

};

#endif // OBJECTDEBUG_H
