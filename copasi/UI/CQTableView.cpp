// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTableView.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/11/24 18:07:52 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQTableView.h"

#include <QKeyEvent>
#include <QTimer>

#include <iostream>

CQTableView::CQTableView(QWidget * pParent):
    QTableView(pParent),
    mpTimer(NULL),
    mpMouseEvent(NULL)
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
void CQTableView::keyPressEvent(QKeyEvent * pEvent)
{
  QTableView::keyPressEvent(pEvent);

  switch (pEvent->key())
    {
      case Qt::Key_Return:
      case Qt::Key_Enter:
      {
        QModelIndex Next = currentIndex();
        Next = Next.sibling(Next.row() + 1, Next.column());

        if (Next.isValid())
          {
            setCurrentIndex(Next);
            edit(Next);
          }
      }
      break;

      default:
        break;
    }
}


// virtual
void CQTableView::mousePressEvent(QMouseEvent * pEvent)
{
  if (mpTimer->isActive())
    {
      if (mpMouseEvent != NULL)
        {
          delete mpMouseEvent;
          mpMouseEvent = NULL;
        }

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
