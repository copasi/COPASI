// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CQUPDATESWIDGET_H
#define CQUPDATESWIDGET_H

//Added by qt3to4:
#include <QGridLayout>
#include <QLabel>

#include <map>
#include <vector>

#include "copasi/UI/copasiWidget.h"

class QLabel;
class QTabWidget;
class QTableWidget;

class CModel;
class CObjectInterface;
class CMathUpdateSequence;
class CMathContainer;

/**
 * This widget displays tables representing the refresh lists. It will probably only
 * be activated in debug builds
 */
class CQUpdatesWidget : public CopasiWidget
{
  Q_OBJECT

public:
  CQUpdatesWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQUpdatesWidget();

protected slots:

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  void loadWidget();
  void clearArrays();

  void loadOneTable(QTableWidget * pTable, const CMathUpdateSequence & list);
  void loadObjectsTable(CModel* pModel);

  void loadMathContainer(const CMathContainer& MC);

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

  QTabWidget* mpTabMath;
  QTableWidget * mpTableMathState;
};

#endif
