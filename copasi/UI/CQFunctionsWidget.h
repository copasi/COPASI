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

#ifndef CQFunctionsWidget_h
#define CQFunctionsWidget_h

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQFunctionsWidget.h"

#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQFunctionDM.h"

class CQFunctionsWidget : public CopasiWidget, public Ui::CQFunctionsWidget
{
  Q_OBJECT

public:
  CQFunctionsWidget(QWidget* parent = 0, const char* name = 0);
  ~CQFunctionsWidget();

  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leave();

protected:
  virtual bool enterProtected();

private:
  CQFunctionDM* mpFunctionDM;
  CQSortFilterProxyModel *mpProxyModel;
  void deleteSelectedFunctions();
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

#endif // CQFunctionsWidget_h
