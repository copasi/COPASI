// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QKeyEvent>
#include <QFocusEvent>

#include <iostream>

#include "CQTableView.h"

#include "copasi/copasi.h"
#include "qtUtilities.h"

CQTableView::CQTableView(QWidget * pParent):
  QTableView(pParent),
  mNextRow(-1),
  mNextColumn(-1)
{
  // setEditTriggers(QAbstractItemView::AllEditTriggers);
}

// virtual
CQTableView::~CQTableView()
{}

// virtual
void CQTableView::setModel(QAbstractItemModel * pModel)
{
  if (model() != NULL)
    {
      disconnect(model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)), this, SLOT(slotRowInserted(const QModelIndex &, int, int)));
    }

  QTableView::setModel(pModel);

  if (model() != NULL)
    {
      connect(model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)), this, SLOT(slotRowInserted(const QModelIndex &, int, int)));
    }
}

// virtual
void CQTableView::keyPressEvent(QKeyEvent * pKeyEvent)
{
  switch (pKeyEvent->key())
    {
      case Qt::Key_Return:
      case Qt::Key_Enter:
      {
        mNextRow = currentIndex().row() + 1;
        mNextColumn = currentIndex().column();

        QModelIndex Index = model()->index(mNextRow, mNextColumn, currentIndex().parent());

        if (Index.isValid())
          {
            setCurrentIndex(Index);
            pKeyEvent->accept();

            mNextRow = -1;
            mNextColumn = -1;
          }
      }
      break;

      default:
        QTableView::keyPressEvent(pKeyEvent);
        break;
    }

  return;
}

void CQTableView::slotRowInserted(const QModelIndex & parent, int start, int end)
{
  QModelIndex Index = model()->index(mNextRow, mNextColumn);

  if (Index.isValid())
    {
      setCurrentIndex(Index);
      emit activated(Index);
    }

  mNextRow = -1;
  mNextColumn = -1;
}
