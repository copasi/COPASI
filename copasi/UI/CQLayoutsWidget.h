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

#ifndef COPASI_CQLayoutsWidget
#define COPASI_CQLayoutsWidget

#include <QtCore/QVariant>

#include <map>

#include "copasi/UI/ui_CQLayoutsWidget.h"

class CQNewMainWindow;
class CQLayoutMainWindow;
class CLayout;
class CQLayoutsDM;
class CQSortFilterProxyModel;
class CQPushButtonDelegate;
class CQPushButtonDelegate;

#include "copasi/UI/CWindowInterface.h"

class CQLayoutsWidget : public CopasiWidget, public Ui::CQLayoutsWidget
{
  Q_OBJECT

  typedef CWindowInterface LayoutWindow;

  typedef std::map< std::string, LayoutWindow * > LayoutWindowMap;

public:
  CQLayoutsWidget(QWidget *parent);
  virtual ~CQLayoutsWidget();

  void deleteLayoutWindows();

private:
  CQLayoutsDM * mpLayoutsDM;
  CQSortFilterProxyModel * mpProxyModel;
  LayoutWindowMap mLayoutWindowMap;
  CQPushButtonDelegate * mpPushButtonDelegate;

  void deleteSelectedLayouts();
  void updateDeleteBtns();
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  void showButtons();

  /**
   * This creates a new layout window.
   */
  LayoutWindow * createLayoutWindow(int row, CLayout* pLayout);

signals:
  void initFilter();

protected slots:
  virtual void slotBtnNewClicked();
  virtual void slotBtnDeleteClicked();
  virtual void slotBtnClearClicked();
  virtual void slotSelectionChanged();
  virtual void slotDoubleClicked(const QModelIndex proxyIndex);
  virtual void dataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight);
  virtual void slotFilterChanged();
  void slotShowLayout(const QModelIndex & index);
};

#endif // COPASI_CQLayoutsWidget
