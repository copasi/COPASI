// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef OBJECTDEBUG_H
#define OBJECTDEBUG_H

#include <QVariant>
#include <iostream>
#include "copasi/UI/ui_objectdebug.h"

class ObjectDebug : public QDialog, public Ui_ObjectDebug
{
  Q_OBJECT

public:
  ObjectDebug(QWidget* parent = NULL, Qt::WindowFlags fl = 0);
  ~ObjectDebug();

public slots:
  void update();
  virtual void writeDot();
  virtual void checkModel();

protected slots:


private:
  void addObjectRecursive(QTreeWidgetItem * parent, const void * ptr);
  void init();

};

#endif // OBJECTDEBUG_H
