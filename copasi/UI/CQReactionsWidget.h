// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReactionsWidget.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/06/22 17:19:07 $
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
  virtual void setFramework(int framework);

private:
  CQReactionDM* mpReactionDM;
  CQSortFilterProxyModel *mpProxyModel;
  void deleteSelectedReactions();

protected:
  virtual void keyPressEvent(QKeyEvent* ev);

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
