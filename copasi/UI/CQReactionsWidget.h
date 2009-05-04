// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReactionsWidget.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/05/04 15:24:00 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQReactionsWidget_h
#define CQReactionsWidget_h

#include "CQSortFilterProxyModel.h"
#include "ui_CQReactionsWidget.h"
#include "CQReactionDM.h"

class CQReactionsWidget : public CopasiWidget, public Ui::CQReactionsWidget
{
  Q_OBJECT

public:
  CQReactionsWidget(QWidget* parent = 0, const char* name = 0);
  ~CQReactionsWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  virtual bool enter(const std::string & key = "");

private:
  CQReactionDM* mpReactionDM;
  CQSortFilterProxyModel *mpProxyModel;
  void deleteSelectedReaction();

protected:
  virtual void keyPressEvent(QKeyEvent* ev);
  virtual void setFramework(int framework);

protected slots:
  virtual void languageChange();
  virtual void slotBtnDeleteClicked();
  virtual void slotBtnClearClicked();
  virtual void slotDoubleClicked(const QModelIndex proxyIndex);
  virtual void dataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight);
  virtual void slotNotifyGUI(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");
  virtual void slotFilterChanged();
};

#endif // CQReactionsWidget_h
