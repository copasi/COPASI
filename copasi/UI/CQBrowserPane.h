// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQBrowserPane
#define COPASI_CQBrowserPane

#include <QTreeView>

class CQBrowserPane: public QTreeView
{
  Q_OBJECT

public:
  CQBrowserPane(QWidget* parent = 0);

  virtual ~CQBrowserPane();

protected slots:
  virtual void currentChanged(const QModelIndex & current, const QModelIndex & previous);
  void slotUpdateScrollBar(const QModelIndex & index);
};

#endif // COPASI_CQBrowserPane
