// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TSSARESULTWIDGET_H
#define TSSARESULTWIDGET_H

#include "UI/copasiWidget.h"
#include <QtGui/QGridLayout>

class CQTSSAResultSubWidget;

class CQTSSAResultWidget : public CopasiWidget
{
  Q_OBJECT

public:
  CQTSSAResultWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CQTSSAResultWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  CQTSSAResultSubWidget* getSubWidget() {return mCentralWidget;};

protected slots:
  //virtual void slotBtnCancelClicked();
  //virtual void slotBtnOKClicked();

public:
  bool loadFromBackend();
  bool saveToBackend();

protected:
  virtual bool enterProtected();
  QGridLayout* mWidgetLayout;
  CQTSSAResultSubWidget* mCentralWidget;
};

#endif
