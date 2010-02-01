// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/StateWidget.h,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2010/02/01 19:43:35 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include "UI/copasiWidget.h"
#include "steadystate/CSteadyStateTask.h"

//Added by qt3to4:
/*
#include <Q3VBoxLayout>
#include <Q3GridLayout>
#include <Q3HBoxLayout>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class StateSubwidget;
class QPushButton;
class Q3HBoxLayout;
class Q3VBoxLayout;
 */

#include <QGridLayout>

class StateSubwidget;
class QPushButton;

class StateWidget : public CopasiWidget
{
  Q_OBJECT

public:
//    QPushButton* buttonSetInitialState;
  QPushButton* setInitialState;

  StateWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~StateWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  bool loadFromBackend();

protected slots:
  //virtual void slotBtnCancelClicked();
  //virtual void slotBtnOKClicked();
  virtual void slotSaveAsInitialClicked();

protected:
  virtual bool enterProtected();
  bool saveToBackend();

  /*
      Q3GridLayout* mWidgetLayout;
      Q3HBoxLayout* stateLayout;
      Q3VBoxLayout* parentLayout;
  */
  QGridLayout* mWidgetLayout;
  StateSubwidget* mCentralWidget;
  bool mUpToDate;
  CSteadyStateTask * pSteadyStateTask;
};

#endif
