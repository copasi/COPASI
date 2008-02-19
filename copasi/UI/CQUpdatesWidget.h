// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQUpdatesWidget.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/02/19 15:00:38 $
// End CVS Header

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

class QGridLayout;
class QLabel;
class QTabWidget;
class QTable;

/**
 * This widget displays tables representing the refresh lists. It will probably only
 * be activated in debug builds
 */
class CQUpdatesWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQUpdatesWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQUpdatesWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:

  protected:

    void loadWidget();
    void clearArrays();

    void loadOneTable(QTable* pTable, const std::vector< Refresh * > & list);

    std::map<const Refresh*, const CCopasiObject*> mRefreshsMap;

    void fillRefreshsMapRecursively(const CCopasiObject* obj);

    QGridLayout* mWidgetLayout;

    QLabel* mLabelTitle;

    QTabWidget* mpTab;

    QTable* mpTable0;
    QTable* mpTable1;
    QTable* mpTable2;
    QTable* mpTable3;
  };

#endif
