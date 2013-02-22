// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
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

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  virtual void setFramework(int framework);

private:
  CQParameterSetsDM* mpParameterSetsDM;
  CQSortFilterProxyModel *mpProxyModel;
  void deleteSelected();
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
};

#endif // CQParameterSetsWidget_h
