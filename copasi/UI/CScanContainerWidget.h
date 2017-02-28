// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCONTAINERWIDGET_H
#define CCONTAINERWIDGET_H

#include <QTableWidget>
#include <vector>

/**
 *  This widget is a table that contains other widgets (arranged vertically)
 *  it adds buttons to delete, move up or down the widgets
 */
class CScanContainerWidget : public QTableWidget
{
  Q_OBJECT

public:
  CScanContainerWidget(QWidget * parent = 0, const char * name = 0);
  ~CScanContainerWidget();

  std::vector<QWidget*> getWidgetList() const;
  void clearWidgetList();
  void addWidget(QWidget* widget, bool controls = true);

  //insert before row, if row=-1 insert before the last row
  void insertWidget(QWidget* widget, int row = -1);
  void enableCopy(const bool & enable);

protected slots:
  void slotUp(int index);
  void slotDown(int index);
  void slotDel(int index);
  void slotCopy(int index);

protected:
  void updateIndices();
  void updateTable();
  bool mCopyEnabled;
  void resizeEvent(QResizeEvent *event);

signals:
  void itemDeleted();
  void copyWidget(int);
};

#endif
