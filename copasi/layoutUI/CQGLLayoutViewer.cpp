// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQGLLayoutViewer.h"

#include <QHBoxLayout>
#include <QLayout>
#include <QScrollBar>
#include <QFrame>
#include <QtOpenGL/QGLFormat>
#include "CQGLLayoutPainter.h"

/**
 * Constructor.
 */
CQGLLayoutViewer::CQGLLayoutViewer(QWidget* pParent, Qt::WindowFlags f): QFrame(pParent, f)
{
  QVBoxLayout *pVBoxLayout = new QVBoxLayout(this);
  this->setLayout(pVBoxLayout);
  pVBoxLayout->setContentsMargins(0, 0, 0, 0);
  QFrame *pHBox = new QFrame(this);
  QHBoxLayout *pHBoxLayout = new QHBoxLayout(pHBox);
  pHBox->setLayout(pHBoxLayout);
  pHBoxLayout->setContentsMargins(0, 0, 0, 0);
  // the QGLformat needs to enable sample buffers, otherwise
  // there is no anti aliasing
  QGLFormat format(QGL::SampleBuffers);
  format.setDoubleBuffer(true);
  this->mpLayoutPainter = new CQGLLayoutPainter(format, pHBox);
  pHBoxLayout->addWidget(this->mpLayoutPainter);
  this->mpVerticalScrollbar = new QScrollBar(Qt::Vertical, pHBox);
  this->mpVerticalScrollbar->setSingleStep(1);
  pHBoxLayout->addWidget(this->mpVerticalScrollbar);
  pVBoxLayout->addWidget(pHBox);
  this->mpHorizontalScrollbar = new QScrollBar(Qt::Horizontal, this);
  this->mpHorizontalScrollbar->setSingleStep(1);
  pVBoxLayout->addWidget(this->mpHorizontalScrollbar);
  connect(this->mpVerticalScrollbar, SIGNAL(valueChanged(int)), this, SLOT(slotVValueChanged(int)));
  connect(this->mpHorizontalScrollbar, SIGNAL(valueChanged(int)), this, SLOT(slotHValueChanged(int)));
  connect(this->mpLayoutPainter, SIGNAL(documentChanged()), this, SLOT(slotDocumentChanged()));
  connect(this->mpLayoutPainter, SIGNAL(singleCurveSelected(bool)), this, SLOT(slotSingleCurveSelected(bool)));
}

/**
 * Destructor.
 */
CQGLLayoutViewer::~CQGLLayoutViewer()
{}

void CQGLLayoutViewer::resizeEvent(QResizeEvent *e)
{
  this->updateScrollbars();
  QFrame::resizeEvent(e);
}

void CQGLLayoutViewer::setZoomFactor(double zoom)
{
  this->mpLayoutPainter->setZoomFactor(zoom);
  this->updateScrollbars();
  this->mpLayoutPainter->update();
}

void CQGLLayoutViewer::updateScrollbars()
{
  // reset the scollbar range
  // disconnect the scrollbar listeners and handle the update so that the GL
  // window is only redrawn once
  double zoom = this->mpLayoutPainter->getZoomFactor();
  double maxX = this->mpLayoutPainter->maxX();
  double maxY = this->mpLayoutPainter->maxY();
  double minX = this->mpLayoutPainter->minX();
  double minY = this->mpLayoutPainter->minY();
  double graphWidth = (maxX - minX) * zoom;
  double graphHeight = (maxY - minY) * zoom;
  double rectangleHeight = this->mpLayoutPainter->contentsRect().height();
  double rectangleWidth = this->mpLayoutPainter->contentsRect().width();
  disconnect(this->mpVerticalScrollbar, SIGNAL(valueChanged(int)), this, SLOT(slotVValueChanged(int)));
  disconnect(this->mpHorizontalScrollbar, SIGNAL(valueChanged(int)), this, SLOT(slotHValueChanged(int)));

  if (graphHeight < rectangleHeight)
    {
      this->mpVerticalScrollbar->hide();
      this->mpVerticalScrollbar->setValue(0);
      this->mpLayoutPainter->setCurrentPositionY(minY);
    }
  else
    {
      this->mpVerticalScrollbar->setPageStep(rectangleHeight);
      int oldMaximum = this->mpVerticalScrollbar->maximum();
      int newMaximum = (int)(graphHeight - rectangleHeight);
      int oldValue = this->mpVerticalScrollbar->value();
      int newValue = 0;

      if (oldValue != 0 && oldMaximum != 0)
        {
          newValue = (int)((double) oldValue * (double) newMaximum / (double) oldMaximum);
        }

      this->mpVerticalScrollbar->setRange(0, newMaximum);
      this->mpVerticalScrollbar->setValue(newValue);
      this->mpLayoutPainter->setCurrentPositionY((double)(minY + newValue / zoom));
      this->mpVerticalScrollbar->show();
    }

  if (graphWidth < rectangleWidth)
    {
      this->mpHorizontalScrollbar->hide();
      this->mpHorizontalScrollbar->setValue(0);
      this->mpLayoutPainter->setCurrentPositionX(minX);
    }
  else
    {
      this->mpHorizontalScrollbar->setPageStep(rectangleWidth);
      int oldMaximum = this->mpHorizontalScrollbar->maximum();
      int newMaximum = (int)(graphWidth - rectangleWidth);
      int oldValue = this->mpHorizontalScrollbar->value();
      int newValue = 0;

      if (oldValue != 0 && oldMaximum != 0)
        {
          newValue = (int)((double) oldValue * (double) newMaximum / (double) oldMaximum);
        }

      this->mpHorizontalScrollbar->setRange(0, newMaximum);
      this->mpHorizontalScrollbar->setValue(newValue);
      this->mpLayoutPainter->setCurrentPositionX((double)(minX + newValue / zoom));
      this->mpHorizontalScrollbar->show();
    }

  connect(this->mpVerticalScrollbar, SIGNAL(valueChanged(int)), this, SLOT(slotVValueChanged(int)));
  connect(this->mpHorizontalScrollbar, SIGNAL(valueChanged(int)), this, SLOT(slotHValueChanged(int)));
}

void CQGLLayoutViewer::slotVValueChanged(int value)
{
  double minY = this->mpLayoutPainter->minY();
  double zoom = this->mpLayoutPainter->getZoomFactor();
  this->mpLayoutPainter->setCurrentPositionY((double)(minY + value / zoom));
}

void CQGLLayoutViewer::slotHValueChanged(int value)
{
  double minX = this->mpLayoutPainter->minX();
  double zoom = this->mpLayoutPainter->getZoomFactor();
  this->mpLayoutPainter->setCurrentPositionX((double)(minX + value / zoom));
}

void CQGLLayoutViewer::resetView()
{
  // TODO disconnect the scrollbar listeners
  // so that the display is only redrawn once
  this->mpLayoutPainter->resetView();
  this->updateScrollbars();
}

/**
 * Calculates the ratio that is needed to fit the diagram on the current viewport
 * and sets this as the zoom factor.
 * The methods return the newly calculated zoom factor.
 */
double CQGLLayoutViewer::fitToScreen()
{
  double zoom = this->mpLayoutPainter->fitToScreen();
  this->updateScrollbars();
  return zoom;
}

void CQGLLayoutViewer::updateWidget()
{
  this->mpLayoutPainter->update();
}

void CQGLLayoutViewer::update(const CDataModel *pDatamodel, CLayout *pLayout, const CLRenderInformationBase *pRenderInfo, const QString &baseDir)
{
  // pass the options on to the layout painter
  if (pRenderInfo)
    {
      this->mpLayoutPainter->update(pDatamodel, pLayout, pRenderInfo, baseDir);
      this->updateScrollbars();
    }
}

void CQGLLayoutViewer::change_style(const CLRenderInformationBase *pRenderInfo, bool defaultStyle)
{
  this->mpLayoutPainter->change_style(pRenderInfo, defaultStyle);
}

/**
 * This slot is called when the layout painter changes
 * the document (layout).
 */
void CQGLLayoutViewer::slotDocumentChanged()
{
  emit documentChanged();
}

/**
 * This slot is called when the selection changes.
 * The value determines whether a single curve is selected or not.
 */
void CQGLLayoutViewer::slotSingleCurveSelected(bool selected)
{
  emit singleCurveSelected(selected);
}

/**
 * This slot is called when the user initiates the action to revert the
 * currently selected curve.
 */
void CQGLLayoutViewer::slotRevertCurve()
{
  this->mpLayoutPainter->revertCurve();
}

/**
 * Returns a pointer to the OpenGL painter.
 */
CQGLLayoutPainter *CQGLLayoutViewer::getPainter()
{
  return this->mpLayoutPainter;
}

/**
 * Returns a const pointer to the OpenGL painter.
 */
const CQGLLayoutPainter *CQGLLayoutViewer::getPainter() const
{
  return this->mpLayoutPainter;
}
