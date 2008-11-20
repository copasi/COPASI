// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTSSATimeScaleWidget.cpp,v $
//   $Revision: 1.2.6.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/11/20 15:38:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQTSSATimeScaleWidget.h"

#include <math.h>
#include <qbitmap.h>
#include <qcolor.h>
#include <qtooltip.h>

/*
 *  Constructs a CScanWidgetRepeat as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQTSSATimeScaleWidget::CQTSSATimeScaleWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CQTSSATimeScaleWidget");

  mpVLayout = new QVBoxLayout(this);
  mpPaintWidget = new PaintWidget(this, "PaintWidget");
  mpSlider = new QSlider(Qt::Horizontal, this);
  mpSlider->setDisabled(true);

  mpVLayout->addWidget(mpPaintWidget);
  mpVLayout->addWidget(mpSlider);

  mpPaintWidget->setBackgroundColor(Qt::white);
  mpPaintWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mpSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  QToolTip::add(mpSlider, "move Slider to set focus on prefered time scale"); // <- helpful
  connect(mpSlider, SIGNAL(valueChanged(int)), this, SLOT(changedInterval()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTSSATimeScaleWidget::~CQTSSATimeScaleWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQTSSATimeScaleWidget::paintTimeScale(CVector< C_FLOAT64> vector)
{
  if (vector.size() > 0)
    {
      mpPaintWidget->mClear = false;
      mpSlider->setDisabled(false);
      if (vector.size() != mpPaintWidget->mVector.size())
        {
          mpSlider->setRange(0, (vector.size() - 1));
          mpSlider->setValue(mpSlider->minValue());
        }
      mpPaintWidget->mVector = vector;
      mpPaintWidget->paintTimeScale(mpSlider->value());
      mpPaintWidget->repaint();
    }
}

void CQTSSATimeScaleWidget::changedInterval()
{
  if (mpPaintWidget->mVector.size() == 0)
    return;
  mpPaintWidget->paintTimeScale(mpSlider->value());
}

void CQTSSATimeScaleWidget::clearWidget()
{
  mpPaintWidget->mClear = true;
  mpPaintWidget->repaint();
  mpSlider->setDisabled(true);
}

//******************************************************************

/*
 *  Constructs a CScanWidgetRepeat as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
PaintWidget::PaintWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl),
    mSelection(0)
{
  if (!name)
    setName("PaintWidget");
}

/*
 *  Destroys the object and frees any allocated resources
 */
PaintWidget::~PaintWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void PaintWidget::paintTimeScale(int select)
{
  mSelection = select;
  repaint();
}

void PaintWidget::paintEvent(QPaintEvent *)
{
  if (mVector.size() == 0) return;

  if (mClear) return;

  int position;
  int space = 35;

  int maxScaleValue = -1000;
  int minScaleValue = 1000;
  unsigned C_INT32 j;
  for (j = 0; j < mVector.size(); ++j)
    {
      if ((int)(log10(fabs(mVector[j])) + 1) > maxScaleValue)
        maxScaleValue = (int)(log10(fabs(mVector[j])) + 1);
      if ((int)(log10(fabs(mVector[j])) - 1) < minScaleValue)
        minScaleValue = (int)(log10(fabs(mVector[j])) - 1);
    }
  int scaleValueRange = maxScaleValue - minScaleValue;

  QPainter paint(this);
  paint.save();

  //paint.setWindow(0, 0, 1000, 1000);
  QRect v = paint.viewport();

  //paint.setFont(QFont("Courier", 15));

  //Legend
  paint.setPen(QPen(QColor(180, 0, 0), 5));
  paint.drawLine(space, space, space, space + 10);
  paint.setPen(QPen(QColor(0, 0, 0), 1));
  paint.drawText (space + 5, space + 10, " - negativ time scale values");

  paint.setPen(QPen(QColor(0, 180, 0), 5));
  paint.drawLine(space, space + 20, space, space + 30);
  paint.setPen(QPen(QColor(0, 0, 0), 1));
  paint.drawText (space + 5, space + 30, " - positiv time scale values");

  //axis
  paint.setPen(QPen(QColor(100, 100, 100), 1));
  int yCentre = v.bottom() - space - 30;
  int scaleBegin = space;
  int scaleEnd = v.right() - space; //(maxScaleValue - minScaleValue) * (1000 - 2 * space) / scaleValueRange + space;
  int axisLength = scaleEnd - scaleBegin;
  paint.drawLine(scaleBegin, yCentre, scaleEnd, yCentre);

  //tics
  C_INT32 i;
  for (i = 0; i <= scaleValueRange; i++)
    {
      position = scaleBegin + (int)(i * axisLength / scaleValueRange);
      paint.drawLine(position, yCentre + 10, position, yCentre);
      paint.drawText(position - 5, yCentre + 30, QString::number(minScaleValue + i));
    }

  paint.setPen(QPen(QColor(0, 180, 0), 1));

  //values
  int yTop = yCentre - 50;
  int xText = v.right() - space - 230;
  int yText = space + 30;
  for (j = 0; j < mVector.size(); j++)
    {
      position = scaleBegin + (int)((log10(fabs(mVector[j])) - minScaleValue) * axisLength / scaleValueRange);
      if ((uint)mSelection == (uint)(mVector.size() - 1 - j))
        {
          if (mVector[j] < 0)
            paint.setPen(QPen(QColor(180, 20, 20), 4));
          else
            paint.setPen(QPen(QColor(20, 180, 20), 4));
          paint.drawLine(position, yCentre - 1, position, yTop);
          paint.setPen(QPen(QColor(200, 200, 200), 1));
          //          paint.setFont(QFont("Courier", 20));
          paint.drawLine(xText, yText, position + 1, yTop - 1);
          paint.drawLine(xText, yText, scaleEnd, yText);
          paint.setPen(QPen(QColor(0, 0, 0), 1));
          if (mVector[j] < 0)
            paint.drawText (xText + 1, yText - 15, " log10 (|" + QString::number(mVector[j]) + "|) = " + QString::number(log10(fabs(mVector[j]))));
          else
            paint.drawText (xText + 1, yText - 15, " log10 (" + QString::number(fabs(mVector[j])) + ") = " + QString::number(log10(fabs(mVector[j]))));
          paint.drawText (scaleBegin + scaleEnd / 2 - 50, yCentre + 50, " log10 (X)");
        }
      else
        {
          if (mVector[j] < 0)
            paint.setPen(QPen(QColor(180, 20, 20), 2));
          else
            paint.setPen(QPen(QColor(20, 180, 20), 2));
          paint.drawLine(position, yCentre - 1, position, yTop);
        }
    }
  paint.restore();
}
