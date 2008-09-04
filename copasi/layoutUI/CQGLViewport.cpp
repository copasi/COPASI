// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQGLViewport.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/04 06:01:52 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQGLViewport.h"
#include "CQGLNetworkPainter.h"
#include <qgl.h>
#include <qscrollbar.h>
#include <qrect.h>

#include <iostream>
#include "copasi/layout/CLBase.h"
#include "copasi/layout/CLayout.h"

/**
 * Constructor.
 */
CQGLViewport::CQGLViewport(QWidget* pParent, const char* name, WFlags f): QFrame(pParent, name, f)
{
  QVBoxLayout* pVBoxLayout = new QVBoxLayout(this);
  QHBox* pHBox = new QHBox(this);
  pVBoxLayout->addWidget(pHBox);
  QGLFormat format;
  format.setDoubleBuffer(TRUE);
  mpNetworkPainter = new CQGLNetworkPainter(format, pHBox, "gl graph");
  mpVerticalScrollbar = new QScrollBar(Qt::Vertical, pHBox, "vertical scrollbar");
  mpVerticalScrollbar->setLineStep(1);
  mpHorizontalScrollbar = new QScrollBar(Qt::Horizontal, this, "horizontal scrollbar");
  mpHorizontalScrollbar->setLineStep(1);
  pVBoxLayout->addWidget(mpHorizontalScrollbar);
  connect(this->mpVerticalScrollbar, SIGNAL(valueChanged(int)), this, SLOT(slotVValueChanged(int)));
  connect(this->mpHorizontalScrollbar, SIGNAL(valueChanged(int)), this, SLOT(slotHValueChanged(int)));
}

/**
 * Destructor.
 */
CQGLViewport::~CQGLViewport()
{}

void CQGLViewport::resizeEvent(QResizeEvent* e)
{
  this->updateScrollbars();
  QFrame::resizeEvent(e);
}

const CQGLNetworkPainter* CQGLViewport::getPainter() const
  {
    return this->mpNetworkPainter;
  }

CQGLNetworkPainter* CQGLViewport::getPainter()
{
  return this->mpNetworkPainter;
}

void CQGLViewport::createGraph(CLayout* IP)
{
  this->mpNetworkPainter->createGraph(IP);
  this->updateScrollbars();
}

void CQGLViewport::setZoomFactor(C_FLOAT64 zoom)
{
  this->mpNetworkPainter->setZoomFactor(zoom);
  this->updateScrollbars();
}

void CQGLViewport::updateScrollbars()
{
  // reset the scollbar range
  double zoom = this->mpNetworkPainter->getZoomFactor();
  CLPoint max = this->mpNetworkPainter->getGraphMax();
  CLPoint min = this->mpNetworkPainter->getGraphMin();
  double graphWidth = (max.getX() - min.getX()) * zoom;
  double graphHeight = (max.getY() - min.getY()) * zoom;
  double rectangleHeight = this->contentsRect().height();
  double rectangleWidth = this->contentsRect().width();
  if (graphHeight < rectangleHeight)
    {
      this->mpVerticalScrollbar->hide();
      this->mpVerticalScrollbar->setValue(0);
    }
  else
    {
      this->mpVerticalScrollbar->setPageStep(rectangleHeight);
      // the value might have to be reset as well
      this->mpVerticalScrollbar->show();
    }
  if (graphWidth < rectangleWidth)
    {
      this->mpHorizontalScrollbar->hide();
      this->mpHorizontalScrollbar->setValue(0);
    }
  else
    {
      this->mpHorizontalScrollbar->setPageStep(rectangleWidth);
      // the value might have to be reset as well
      this->mpHorizontalScrollbar->show();
    }
  this->mpVerticalScrollbar->setRange(0, (unsigned int)(graphHeight - rectangleHeight));
  this->mpHorizontalScrollbar->setRange(0, (unsigned int)(graphWidth - rectangleWidth));
}

void CQGLViewport::slotVValueChanged(int value)
{
  CLPoint p = this->mpNetworkPainter->getGraphMin();
  double zoom = this->mpNetworkPainter->getZoomFactor();
  this->mpNetworkPainter->setCurrentPositionY((double)(p.getY() + value / zoom));
}

void CQGLViewport::slotHValueChanged(int value)
{
  CLPoint p = this->mpNetworkPainter->getGraphMin();
  double zoom = this->mpNetworkPainter->getZoomFactor();
  this->mpNetworkPainter->setCurrentPositionX((double)(p.getX() + value / zoom));
}
