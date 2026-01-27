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

#ifndef CQReportsWidget_h
#define CQReportsWidget_h

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQReportsWidget.h"

#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQReportDM.h"

class CQReportsWidget : public CopasiWidget, public Ui::CQReportsWidget
{
  Q_OBJECT

public:
  CQReportsWidget(QWidget* parent = 0, const char* name = 0);
  ~CQReportsWidget();

  void setFramework(int framework) override;

private:
  CQReportDM* mpReportDM;
  CQSortFilterProxyModel *mpProxyModel;
  void deleteSelectedReports();

signals:
  void initFilter();

protected:
  void keyPressEvent(QKeyEvent* ev) override;
  bool enterProtected() override;
  bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CRegisteredCommonName & cn) override;
  bool leaveProtected() override;

protected slots:
  virtual void slotBtnNewClicked();
  virtual void slotBtnDeleteClicked(bool needFocus=false);
  virtual void slotBtnClearClicked();
  virtual void slotDoubleClicked(const QModelIndex proxyIndex);
  virtual void dataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight);
  virtual void slotFilterChanged();
};

#endif // CQReportsWidget_h
