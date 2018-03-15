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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef STATESUBWIDGET_H
#define STATESUBWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_StateSubwidget.h"

#include "copasi/UI/listviews.h"

class CModel;
class CSteadyStateTask;

class StateSubwidget : public CopasiWidget, public Ui::StateSubwidget
{
  Q_OBJECT

public:
  StateSubwidget(QWidget* parent = 0, const char* name = 0);
  ~StateSubwidget();

  virtual bool loadAll(const CSteadyStateTask * pTask);
  void clear();
  virtual void setFramework(int framework);

protected:
  const CSteadyStateTask * mpTask;
  CModel * mpModel;

  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  void loadMetabolites();
  void loadCompartments();
  void loadReactions();
  void loadModelValues();
  void loadJacobian();
  void showUnits();

protected slots:
};

#endif // STATESUBWIDGET_H
