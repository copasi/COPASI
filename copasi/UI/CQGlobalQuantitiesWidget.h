// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected:
  virtual bool enterProtected();

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

#ifdef COPASI_UNDO
  virtual void slotChangeWidget(const size_t & id);
#endif
};

#endif // CQGlobalQuantitiesWidget_h
