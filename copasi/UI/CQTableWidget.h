// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQ_TABLE_WIDGET_H
#define CQ_TABLE_WIDGET_H

#include <QTableWidget>

class QDropEvent;
class QWidget;

class CQTableWidget : public QTableWidget
{
public:
  explicit CQTableWidget(QWidget* pParent = NULL);

protected:
  void dropEvent(QDropEvent* pEvent) override;
};

#endif //CQ_TABLE_WIDGET_H
