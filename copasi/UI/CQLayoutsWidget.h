// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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
#ifdef USE_CRENDER_EXTENSION
# include "copasi/UI/CWindowInterface.h"
#endif // USE_CRENDER_EXTENSION

class CQLayoutsWidget : public CopasiWidget, public Ui::CQLayoutsWidget
{
  Q_OBJECT

#ifdef USE_CRENDER_EXTENSION
  typedef CWindowInterface LayoutWindow;
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
  void slotShowLayout(const QModelIndex & index);
};

#endif // COPASI_CQLayoutsWidget
