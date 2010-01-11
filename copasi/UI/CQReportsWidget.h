// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportsWidget.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/01/11 15:30:51 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQReportsWidget_h
#define CQReportsWidget_h

#include "CQSortFilterProxyModel.h"
#include "ui_CQReportsWidget.h"
#include "CQReportDM.h"

class CQReportsWidget : public CopasiWidget, public Ui::CQReportsWidget
{
  Q_OBJECT

public:
  CQReportsWidget(QWidget* parent = 0, const char* name = 0);
  ~CQReportsWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  virtual void setFramework(int framework);

private:
  CQReportDM* mpReportDM;
  CQSortFilterProxyModel *mpProxyModel;
  void deleteSelectedReports();

protected:
  virtual void keyPressEvent(QKeyEvent* ev);
  virtual bool enterProtected();

protected slots:
  virtual void languageChange();
  virtual void slotBtnNewClicked();
  virtual void slotBtnDeleteClicked();
  virtual void slotBtnClearClicked();
  virtual void slotDoubleClicked(const QModelIndex proxyIndex);
  virtual void dataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight);
  virtual void slotFilterChanged();
};

#endif // CQReportsWidget_h
