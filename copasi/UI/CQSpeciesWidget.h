// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSpeciesWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/05/15 19:35:32 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQSpeciesWidget_h
#define CQSpeciesWidget_h

#include "CQSortFilterProxyModel.h"
#include "CQComboDelegate.h"
#include "ui_CQSpeciesWidget.h"
#include "CQSpecieDM.h"

class CQSpeciesWidget : public CopasiWidget, public Ui::CQSpeciesWidget
{
  Q_OBJECT

public:
  CQSpeciesWidget(QWidget* parent = 0, const char* name = 0);
  ~CQSpeciesWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  virtual bool enter(const std::string & key = "");

private:
  CQSpecieDM* mpSpecieDM;
  CQSortFilterProxyModel *mpProxyModel;
  QStringList mCompartments;
  CQComboDelegate* mpCompartmentDelegate;
  CQIndexComboDelegate* mpTypeDelegate;
  void deleteSelectedSpecie();

protected:
  virtual void keyPressEvent(QKeyEvent* ev);
  virtual void setFramework(int framework);
  void refreshCompartments();

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

#endif // CQSpeciesWidget_h
