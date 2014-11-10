// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQBrowserPane.h"

#include "listviews.h"

CQBrowserPane::CQBrowserPane(QWidget* parent) :
  QTreeView(parent)
{
  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
  setSizePolicy(sizePolicy);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  setAutoScroll(true);
  setEditTriggers(QAbstractItemView::NoEditTriggers);
  setTextElideMode(Qt::ElideNone);
  setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
  setUniformRowHeights(true);
  setSortingEnabled(true);
  setHeaderHidden(true);

  connect(this, SIGNAL(expanded(const QModelIndex &)), this, SLOT(slotUpdateScrollBar(const QModelIndex &)));
  connect(this, SIGNAL(collapsed(const QModelIndex &)), this, SLOT(slotUpdateScrollBar(const QModelIndex &)));
}

// virtual
CQBrowserPane::~CQBrowserPane()
{}

// virtual
void CQBrowserPane::currentChanged(const QModelIndex & current, const QModelIndex & /* previous */)
{
  static_cast< ListViews * >(parent())->slotFolderChanged(current);
}

void CQBrowserPane::slotUpdateScrollBar(const QModelIndex & index)
{
  resizeColumnToContents(index.column());
}
