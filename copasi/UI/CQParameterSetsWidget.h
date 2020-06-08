// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQParameterSetsWidget_h
#define CQParameterSetsWidget_h

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQParameterSetsWidget.h"

#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQParameterSetsDM.h"

class CQParameterSetsWidget : public CopasiWidget, public Ui::CQParameterSetsWidget
{
  Q_OBJECT

public:
  CQParameterSetsWidget(QWidget* parent = 0, const char* name = 0);
  ~CQParameterSetsWidget();

  virtual void setFramework(int framework);

private:
  CQParameterSetsDM* mpParameterSetsDM;
  CQSortFilterProxyModel *mpProxyModel;
  void deleteSelected();
  void updateDeleteBtns();

signals:
  void initFilter();

protected:
  virtual void keyPressEvent(QKeyEvent* ev);
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

protected slots:
  virtual void slotBtnNewClicked();
  virtual void slotBtnDeleteClicked();
  virtual void slotBtnClearClicked();
  virtual void slotSelectionChanged();
  virtual void slotDoubleClicked(const QModelIndex proxyIndex);
  virtual void dataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight);
  virtual void slotFilterChanged();
};

#endif // CQParameterSetsWidget_h
