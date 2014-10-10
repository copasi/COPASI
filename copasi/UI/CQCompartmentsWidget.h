// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQCompartmentsWidget_h
#define CQCompartmentsWidget_h

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQCompartmentsWidget.h"

#include "copasi/UI/CQCompartmentDM.h"
#include "copasi/UI/CQComboDelegate.h"
#include "copasi/UI/CQSortFilterProxyModel.h"

class CQCompartmentsWidget : public CopasiWidget, public Ui::CQCompartmentsWidget
{
  Q_OBJECT

public:
  CQCompartmentsWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQCompartmentsWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

private:
  CQCompartmentDM* mpCompartmentDM;
  CQSortFilterProxyModel *mpProxyModel;
  CQIndexComboDelegate* mpTypeDelegate;
  void deleteSelectedCompartments();
  void updateDeleteBtns();
  virtual bool enterProtected();

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

#endif // CQCompartmentsWidget_h
