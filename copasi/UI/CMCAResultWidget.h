// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CMCAResultWidget.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/20 16:07:07 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CMCAResultWidget_H__
#define CMCAResultWidget_H__

#include "UI/copasiWidget.h"

#include <QGridLayout>


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

  QGridLayout* mWidgetLayout;

  CMCAResultSubwidget* mCentralWidget;
};

#endif
