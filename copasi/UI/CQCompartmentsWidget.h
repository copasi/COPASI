// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartmentsWidget.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/16 15:47:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQCompartmentsWidget_h
#define CQCompartmentsWidget_h

#include "CQComboDelegate.h"
#include "CQSortFilterProxyModel.h"
#include "ui_CQCompartmentsWidget.h"
#include "CQCompartmentDM.h"

class CQCompartmentsWidget : public CopasiWidget, public Ui::CQCompartmentsWidget
{
  Q_OBJECT

public:
  CQCompartmentsWidget(QWidget* parent = 0, const char* name = 0);
  ~CQCompartmentsWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

private:
  CQCompartmentDM* mpCompartmentDM;
  CQSortFilterProxyModel *mpProxyModel;
  CQIndexComboDelegate* mpTypeDelegate;
  void deleteSelectedCompartments();
  virtual bool enterProtected();

protected:
  virtual void keyPressEvent(QKeyEvent* ev);

protected slots:
  virtual void languageChange();
  virtual void slotBtnDeleteClicked();
  virtual void slotBtnClearClicked();
  virtual void slotDoubleClicked(const QModelIndex proxyIndex);
  virtual void dataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight);
  virtual void slotFilterChanged();
};

#endif // CQCompartmentsWidget_h
