// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLayoutsWidget.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/10/17 12:17:58 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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

class CQLayoutsWidget : public CopasiWidget, public Ui::CQLayoutsWidget
{
  Q_OBJECT

#ifdef USE_CRENDER_EXTENSION
  typedef CQNewMainWindow LayoutWindow;
#else
  typedef CQLayoutMainWindow LayoutWindow;
#endif // USE_CRENDER_EXTENSION

  typedef std::map< std::string, LayoutWindow * > LayoutWindowMap;

public:
  CQLayoutsWidget(QWidget *parent);
  virtual ~CQLayoutsWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

  void deleteLayoutWindows();

private:
  CQLayoutsDM * mpLayoutsDM;
  CQSortFilterProxyModel * mpProxyModel;
  LayoutWindowMap mLayoutWindowMap;
  CQPushButtonDelegate * mpPushButtonDelegate;

  void deleteSelectedLayouts();
  void updateDeleteBtns();
  virtual bool enterProtected();

  void showButtons();

  /**
   * This creates a new layout window.
   */
  LayoutWindow * createLayoutWindow(int row, CLayout* pLayout);

protected slots:
  virtual void slotBtnNewClicked();
  virtual void slotBtnDeleteClicked();
  virtual void slotBtnClearClicked();
  virtual void slotSelectionChanged(const QItemSelection& selected,
                                    const QItemSelection& deselected);
  virtual void slotDoubleClicked(const QModelIndex proxyIndex);
  virtual void dataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight);
  virtual void slotFilterChanged();
  void slotShowLayout(int row);
};

#endif // COPASI_CQLayoutsWidget
