// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQGlobalQuantitiesWidget_h
#define CQGlobalQuantitiesWidget_h

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQGlobalQuantitiesWidget.h"

#include "copasi/UI/CQComboDelegate.h"
#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQGlobalQuantityDM.h"

class CQGlobalQuantitiesWidget : public CopasiWidget, public Ui::CQGlobalQuantitiesWidget
{
  Q_OBJECT

public:
  CQGlobalQuantitiesWidget(QWidget* parent = 0, const char* name = 0);
  ~CQGlobalQuantitiesWidget();

  virtual bool leave();
  virtual CQBaseDataModel* getCqDataModel();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);

private:
  CQGlobalQuantityDM* mpGlobalQuantityDM;
  CQSortFilterProxyModel *mpProxyModel;
  CQIndexComboDelegate* mpTypeDelegate;
  void deleteSelectedGlobalQuantities();
  void updateDeleteBtns();

protected:
  virtual void keyPressEvent(QKeyEvent* ev);

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

#endif // CQGlobalQuantitiesWidget_h
