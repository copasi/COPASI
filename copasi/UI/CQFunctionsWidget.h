// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFunctionsWidget.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/01/11 15:30:51 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQFunctionsWidget_h
#define CQFunctionsWidget_h

#include "CQSortFilterProxyModel.h"
#include "ui_CQFunctionsWidget.h"
#include "CQFunctionDM.h"

class CQFunctionsWidget : public CopasiWidget, public Ui::CQFunctionsWidget
{
  Q_OBJECT

public:
  CQFunctionsWidget(QWidget* parent = 0, const char* name = 0);
  ~CQFunctionsWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected:
  virtual bool enterProtected();

private:
  CQFunctionDM* mpFunctionDM;
  CQSortFilterProxyModel *mpProxyModel;
  void deleteSelectedFunctions();

protected:
  virtual void keyPressEvent(QKeyEvent* ev);

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

#endif // CQFunctionsWidget_h
