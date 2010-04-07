/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLyapResultWidget.h,v $
 $Revision: 1.6.2.1 $
 $Name:  $
 $Author: shoops $
 $Date: 2010/04/07 16:51:57 $
 End CVS Header */

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQLYAPRESULT_H
#define CQLYAPRESULT_H

#include "ui_CQLyapResultWidget.h"

#include "lyap/CLyapTask.h"

class CQLyapResultWidget : public CopasiWidget, public Ui::CQLyapResultWidget
{
  Q_OBJECT

public:
  CQLyapResultWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CQLyapResultWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:
  virtual void languageChange();

  void saveToFile();

protected:
  virtual bool enterProtected();
  bool loadFromBackend();

private:
  void init();

  CLyapTask * mpTask;
};

#endif
