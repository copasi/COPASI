// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
class CQComboDelegate;

class CQParameterOverviewWidget : public CopasiWidget, public Ui::CQParameterOverviewWidget
{
  Q_OBJECT

public:
  CQParameterOverviewWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQParameterOverviewWidget();

  virtual void setFramework(int framework);

  /**
   * Allows showing / hiding the button group at the bottom of the overview
   * widget
   *
   * @param isVisible boolean, indicating whether the button group should
   *                   be visible (true), or not.
   */
  void setBtnGroupVisible(bool isVisible);

private:
  void buildSelectionList();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

signals:
  void initFilter();

protected slots:
  virtual void slotBtnRevert();
  virtual void slotBtnCommit();
  virtual void slotBtnNew();
  virtual void slotBtnCopy();
  virtual void slotBtnDelete();
  virtual void slotBtnSaveToFile();
  virtual void slotBtnSaveAs();

  void saveParameterSet(CModelParameterSet * pParameterSet);

  void slotOpenEditor(const QModelIndex & index);
  void slotCloseEditor(const QModelIndex & index);
  void slotResolve(const QModelIndex & index);
  virtual void slotFilterChanged();

private:
  CModelParameterSet * mpParameterSet;

  CModelParameterSet * mpParameterSetCopy;
  bool mOwnCopy;

  CQParameterOverviewDM * mpParameterSetDM;

  QSortFilterProxyModel * mpParameterSetSortDM;

  CQComboDelegate * mpComboDelegate;

  QStringList mGlobalQuantities;
};

#endif // COPASI_CQParameterOverviewWidget
