// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

  void setFramework(int framework) override;

  CQBaseDataModel* getCqDataModel() override;

private:
  CQCompartmentDM* mpCompartmentDM;
  CQSortFilterProxyModel *mpProxyModel;
  CQComboDelegate* mpTypeDelegate;
  void deleteSelectedCompartments();

signals:
  void initFilter();

protected:
  bool enterProtected() override;
  bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CRegisteredCommonName & cn) override;
  bool leaveProtected() override;

  void keyPressEvent(QKeyEvent* ev) override;

protected slots:
  virtual void slotBtnNewClicked();
  virtual void slotBtnDeleteClicked(bool needFocus=false);
  virtual void slotBtnClearClicked();
  virtual void slotDoubleClicked(const QModelIndex proxyIndex);
  virtual void dataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight);
  virtual void slotFilterChanged();
};

#endif // CQCompartmentsWidget_h
