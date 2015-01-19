// Copyright (C) 2011 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQTableView.h"

#include <QtGui/QKeyEvent>
#include <QtCore/QTimer>

#include <iostream>

CQTableView::CQTableView(QWidget * pParent):
  QTableView(pParent),
  mpTimer(NULL),
  mpMouseEvent(NULL),
  mMoveDown(false),
  mpModel(NULL)
{
  mpTimer = new QTimer(this);
  mpTimer->setSingleShot(true);
  mpTimer->setInterval(250);

  connect(mpTimer, SIGNAL(timeout()), this, SLOT(slotSingleClick()));
}

// virtual
CQTableView::~CQTableView()
{}

// virtual
void CQTableView::setModel(QAbstractItemModel * model)
{
  if (mpModel != NULL)
    disconnect(mpModel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex)),
               this, SLOT(slotMoveDown()));

  mpModel = model;

  if (mpModel != NULL)
    connect(mpModel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex)),
            this, SLOT(slotMoveDown()));

  QTableView::setModel(model);
}

// virtual
void CQTableView::keyPressEvent(QKeyEvent * pEvent)
{
  QTableView::keyPressEvent(pEvent);

  switch (pEvent->key())
    {
      case Qt::Key_Return:
      case Qt::Key_Enter:
        mMoveDown = true;
        break;

      default:
        mMoveDown = false;
        break;
    }
}

// virtual
void CQTableView::mousePressEvent(QMouseEvent * pEvent)
{
  if (mpMouseEvent != NULL)
    {
      delete mpMouseEvent;
      mpMouseEvent = NULL;
    }

  if (mpTimer->isActive())
    {
      QTableView::mousePressEvent(pEvent);
      emit doubleClicked(currentIndex());

      return;
    }

  mpMouseEvent = new QMouseEvent(*pEvent);
  pEvent->accept();
  mpTimer->start();
}

void CQTableView::slotSingleClick()
{
  if (mpMouseEvent != NULL)
    {
      QTableView::mousePressEvent(mpMouseEvent);
      mpMouseEvent = NULL;
    }
}

void CQTableView::slotMoveDown()
{
  if (mMoveDown)
    {
      QKeyEvent Down(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
      QTableView::keyPressEvent(&Down);
    }
}
