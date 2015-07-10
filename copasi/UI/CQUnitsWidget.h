// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQUnitsWidget_h
#define CQUnitsWidget_h

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQUnitsWidget.h"

#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQUnitDM.h"

class CQUnitsWidget : public CopasiWidget, public Ui::CQUnitsWidget
{
  Q_OBJECT

public:
  CQUnitsWidget(QWidget* parent = 0, const char* name = 0);
  ~CQUnitsWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  virtual void setFramework(int framework);

private:
  CQUnitDM* mpUnitDM;
  CQSortFilterProxyModel *mpProxyModel;
  void deleteSelectedUnits();
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

#endif // CQUnitsWidget_h
