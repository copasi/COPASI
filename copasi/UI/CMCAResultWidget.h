// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CMCAResultWidget.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/16 15:47:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CMCAResultWidget_H__
#define CMCAResultWidget_H__

#include "UI/copasiWidget.h"
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
//class QPushButton;

class CMCAResultSubwidget;

class CMCAResultWidget : public CopasiWidget
{
  Q_OBJECT

public:
  CMCAResultWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CMCAResultWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  bool loadFromBackend();

protected slots:

protected:
  virtual bool enterProtected();
  bool saveToBackend();

  Q3GridLayout* mWidgetLayout;

  CMCAResultSubwidget* mCentralWidget;
};

#endif
