// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEventsWidget.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/14 16:17:46 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEventsWidget_h
#define CQEventsWidget_h

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQEventsWidget.h"

#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQSpinBoxDelegate.h"
#include "copasi/UI/CQEventDM.h"

class CQEventsWidget : public CopasiWidget, public Ui::CQEventsWidget
{
  Q_OBJECT

public:
  CQEventsWidget(QWidget* parent = 0, const char* name = 0);
  ~CQEventsWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

private:
  CQEventDM* mpEventDM;
  CQSortFilterProxyModel *mpProxyModel;
  void deleteSelectedEvents();
  void updateDeleteBtns();

protected:
  virtual void keyPressEvent(QKeyEvent* ev);
  virtual bool enterProtected();

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

#ifdef COPASI_UNDO
  virtual void slotChangeWidget(const size_t & id);
#endif
};

#endif // CQEventsWidget_h
