// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QApplication>
#include <QWheelEvent>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QtCore/QFileInfo>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>

#include <copasi/qlayout/CQZoomableView.h>

#include <copasi/copasi.h>
#include <copasi/resourcesUI/CQIconResource.h>

CQZoomableView::~CQZoomableView()
{
}

CQZoomableView::CQZoomableView(QWidget*parent)
  : QGraphicsView(parent)
  , mScaleFactor(1.15)
  , mIgnoreEvents(false)
{
  setDragMode(QGraphicsView::ScrollHandDrag);
  createActions();
}

CQZoomableView::CQZoomableView(QGraphicsView *scene)
  : QGraphicsView(scene)
  , mScaleFactor(1.15)
  , mIgnoreEvents(false)

{
  setDragMode(QGraphicsView::ScrollHandDrag);
  createActions();
}

void CQZoomableView::fillZoomMenu(QMenu* menu)
{
  if (menu == NULL) return;

  menu->addAction(mpActFitOnScreen);
  menu->addAction(mpActZoomIn);
  menu->addAction(mpActZoomOut);
  menu->addAction(mpActResetZoom);
}

void CQZoomableView::fillZoomTooBar(QToolBar* toolBar)
{
  if (toolBar == NULL) return;

  toolBar->addAction(mpActFitOnScreen);
  toolBar->addAction(mpActZoomIn);
  toolBar->addAction(mpActZoomOut);
  toolBar->addAction(mpActResetZoom);
}

void CQZoomableView::createActions()
{
  mpActFitOnScreen = new QAction(tr("Fit On Screen"), this);
  mpActFitOnScreen->setShortcut(QKeySequence::fromString("F5"));
  mpActFitOnScreen->setIcon(CQIconResource::icon(CQIconResource::viewmagfit));
  connect(mpActFitOnScreen, SIGNAL(triggered()), this, SLOT(slotFitOnScreen()));
  addAction(mpActFitOnScreen);

  mpActResetZoom = new QAction(tr("Reset Zoom"), this);
  mpActResetZoom->setIcon(CQIconResource::icon(CQIconResource::viewmag1));
  connect(mpActResetZoom, SIGNAL(triggered()), this, SLOT(slotResetZoom()));
  addAction(mpActResetZoom);

  mpActZoomIn = new QAction(tr("Zoom In"), this);
  mpActZoomIn->setIcon(CQIconResource::icon(CQIconResource::viewmagPlus));
  mpActZoomIn->setShortcut(QKeySequence::ZoomIn);
  connect(mpActZoomIn, SIGNAL(triggered()), this, SLOT(slotZoomIn()));
  addAction(mpActZoomIn);

  mpActZoomOut = new QAction(tr("Zoom Out"), this);
  mpActZoomOut->setIcon(CQIconResource::icon(CQIconResource::viewmagMinus));
  mpActZoomOut->setShortcut(QKeySequence::ZoomOut);
  connect(mpActZoomOut, SIGNAL(triggered()), this, SLOT(slotZoomOut()));
  addAction(mpActZoomOut);

  setInteractive(true);
  setRenderHints(QPainter::Antialiasing);
}

void CQZoomableView::slotFitOnScreen()
{
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  fitInView(scene()->itemsBoundingRect().adjusted(-0.05, -0.05, 0.05, 0.05), Qt::KeepAspectRatio);
  update();
}
void CQZoomableView::slotResetZoom()
{
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
#if QT_VERSION < QT_VERSION_CHECK(5,15,0)
  resetMatrix();
#else
  resetTransform();
#endif
  ensureVisible(scene()->itemsBoundingRect());
  update();
}
void CQZoomableView::slotZoomIn()
{
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  scale(mScaleFactor, mScaleFactor);
}
void CQZoomableView::slotZoomOut()
{
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  scale(1.0 / mScaleFactor, 1.0 / mScaleFactor);
}

void CQZoomableView::wheelEvent(QWheelEvent* event)
{
  if (QApplication::keyboardModifiers() == Qt::ControlModifier ||
      QApplication::keyboardModifiers() == Qt::MetaModifier ||
      QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
#if QT_VERSION < QT_VERSION_CHECK(5,15,0)
      int delta = event->delta();
# else
      int delta = event->angleDelta().y();
#endif

      if (delta > 0)
        {
          // Zoom in
          slotZoomIn();
        }
      else
        {
          // Zooming out
          slotZoomOut();
        }
    }
  else
    {
      QGraphicsView::wheelEvent(event);
    }
}
