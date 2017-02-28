// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQTableView.h
 *
 *  Created on: Nov 23, 2010
 *      Author: shoops
 */

#ifndef COPASI_QTableView
#define COPASI_QTableView

#include <QTableView>
#include <QModelIndex>

class CQTableView : public QTableView
{
  Q_OBJECT

public:
  CQTableView(QWidget * pParent = NULL);
  virtual ~CQTableView();
  virtual void setModel(QAbstractItemModel * model);

protected:
  virtual void keyPressEvent(QKeyEvent * pKeyEvent);

protected slots:
  void slotRowInserted(const QModelIndex & parent, int start, int end);

private:
  int mNextRow;
  int mNextColumn;
};

#endif // COPASI_QTableView
