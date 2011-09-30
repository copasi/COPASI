// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/StateSubwidget.h,v $
//   $Revision: 1.27 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:41 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef STATESUBWIDGET_H
#define STATESUBWIDGET_H

#include "ui_StateSubwidget.h"

#include <QtCore/QVariant>
#include <QPixmap>
#include <QLabel>

class CModel;
class CSteadyStateTask;

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "CQArrayAnnotationsWidget.h"
#include "copasiWidget.h"

#include "UI/listviews.h"

class StateSubwidget : public CopasiWidget, public Ui::StateSubwidget
{
  Q_OBJECT

public:
  StateSubwidget(QWidget* parent = 0, const char* name = 0);
  ~StateSubwidget();

  void displayOptimizationTab(bool displayOptTab);
  virtual bool loadAll(const CSteadyStateTask * pTask);
  void clear();
  virtual void setFramework(int framework);
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  const CSteadyStateTask * mpTask;
  CModel * mpModel;

  virtual void init();
  void loadMetabolites();
  void loadCompartments();
  void loadReactions();
  void loadModelValues();
  void loadJacobian();
  void showUnits();

protected slots:
};

#endif // STATESUBWIDGET_H
