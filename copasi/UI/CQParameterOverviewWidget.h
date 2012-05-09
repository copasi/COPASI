// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQParameterOverviewWidget.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/09 21:32:17 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQParameterOverviewWidget
#define COPASI_CQParameterOverviewWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQParameterOverviewWidget.h"

class CModelParameterSet;
class CQParameterOverviewDM;
class QSortFilterProxyModel;

class CQParameterOverviewWidget : public CopasiWidget, public Ui::CQParameterOverviewWidget
{
  Q_OBJECT

public:
  CQParameterOverviewWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQParameterOverviewWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

private:
  virtual bool enterProtected();

protected:

protected slots:
  virtual void slotBtnNew();
  virtual void slotBtnDelete();
  virtual void slotBtnSave();
  virtual void dataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight);

private:
  CModelParameterSet * mpParameterSet;

  CQParameterOverviewDM * mpParameterSetDM;

  QSortFilterProxyModel * mpParameterSetSortDM;

};

#endif // COPASI_CQParameterOverviewWidget
