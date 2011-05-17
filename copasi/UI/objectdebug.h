// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/objectdebug.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:49 $
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

private:
  void addObjectRecursive(QWidget * parent, const void * ptr);
  void init();

};

#endif // OBJECTDEBUG_H
