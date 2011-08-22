// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQUpdatesWidget.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/08/22 21:38:34 $
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

#ifndef CQUPDATESWIDGET_H
#define CQUPDATESWIDGET_H

#include <map>

#include "UI/copasiWidget.h"
#include "mathematics.h"
//Added by qt3to4:
#include <QGridLayout>
#include <QLabel>

class QLabel;
class QTabWidget;
class QTableWidget;

class CModel;

/**
 * This widget displays tables representing the refresh lists. It will probably only
 * be activated in debug builds
 */
class CQUpdatesWidget : public CopasiWidget
{
  Q_OBJECT

public:
  CQUpdatesWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CQUpdatesWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:

protected:
  virtual bool enterProtected();
  void loadWidget();
  void clearArrays();

  void loadOneTable(QTableWidget * pTable, const std::vector< Refresh * > & list);
  void loadObjectsTable(CModel* pModel);

  std::map<const Refresh*, const CCopasiObject*> mRefreshsMap;

  void fillRefreshsMapRecursively(const CCopasiObject* obj);

  QGridLayout* mWidgetLayout;

  QLabel* mLabelTitle;

  QTabWidget* mpMainTab;
  QTabWidget* mpTab;
  QTabWidget* mpTab2;

  QTableWidget * mpTable0;
  QTableWidget * mpTable1;
  QTableWidget * mpTable2;
  QTableWidget * mpTable3;

  QTableWidget * mpTableObj;
  QTableWidget * mpTableState;
};

#endif
