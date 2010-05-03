// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CTabWidget.h,v $
//   $Revision: 1.14.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/05/03 19:17:29 $
// End CVS Header

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

#ifndef CTABWIDGET_H
#define CTABWIDGET_H

#include "copasi/UI/listviews.h"

#include "copasi/UI/copasiWidget.h"

class QTabWidget;

/**
 * This class is the container for two or more widgets.
 */
class CTabWidget : public CopasiWidget
{
public:
  CTabWidget(const QString & label, CopasiWidget * pCopasiWidget,
             QWidget* parent = 0, const char* name = 0, Qt::WFlags f = 0);

  ~CTabWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected:
  virtual bool enterProtected();
  QTabWidget *mTabWidget;
  std::vector< CopasiWidget * > mPages;
};

#endif // CTABWIDGET_H
