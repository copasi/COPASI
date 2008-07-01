// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTSSATimeScaleWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/07/01 11:09:50 $
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
      mpSlider->setRange(0, (vector.size() - 1));
      mpSlider->setValue(mpSlider->minValue());
      mpPaintWidget->paintTimeScale(0);
      mpPaintWidget->mVector = vector;
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

/*
 *  Constructs a CScanWidgetRepeat as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
PaintWidget::PaintWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
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

  uint i;
  int position;
  int space = 50;
  C_FLOAT64 scaleEnd;
  C_FLOAT64 scaleBegin;
  C_FLOAT64 maxScaleValue = (int)(log10(fabs(mVector[0])) + 1);
  C_FLOAT64 minScaleValue = (int)(log10(fabs(mVector[mVector.size() - 1])) - 1);
  C_FLOAT64 scaleValueRange = maxScaleValue - minScaleValue;

  QPainter paint(this);
  paint.save();

  paint.setWindow(0, 0, 1000, 1000);

  paint.setFont(QFont("Courier", 15));

  paint.setPen(QPen(QColor(180, 0, 0), 5));
  paint.drawLine(space, 100, space, 110);
  paint.setPen(QPen(QColor(0, 0, 0), 1));
  paint.drawText (space + 5, 110, " - negativ time scale values");

  paint.setPen(QPen(QColor(0, 180, 0), 5));
  paint.drawLine(space, 130, space, 140);
  paint.setPen(QPen(QColor(0, 0, 0), 1));
  paint.drawText (space + 5, 140, " - positiv time scale values");

  paint.setPen(QPen(QColor(100, 100, 100), 1));
  scaleBegin = space;
  scaleEnd = (maxScaleValue - minScaleValue) * (1000 - 2 * space) / scaleValueRange + space;
  paint.drawLine((int)scaleBegin, 700, (int)scaleEnd, 700);

  for (i = 0; i <= scaleValueRange; i++)
    {
      position = (int)((i) * (1000 - 2 * space) / scaleValueRange + space);
      paint.drawLine(position, 720, position, 680);
      paint.drawText ((position - 4), 750, QString::number(minScaleValue + i));
    }

  paint.setPen(QPen(QColor(0, 180, 0), 1));

  for (i = 0; i < mVector.size(); i++)
    {
      position = (int)(((log10(fabs(mVector[i]))) - minScaleValue) * (1000 - 2 * space) / scaleValueRange + space);
      if ((uint)mSelection == (uint)(mVector.size() - 1 - i))
        {
          if (mVector[i] < 0)
            paint.setPen(QPen(QColor(180, 20, 20), 4));
          else
            paint.setPen(QPen(QColor(20, 180, 20), 4));
          paint.drawLine(position, 697, position, 600);
          paint.setPen(QPen(QColor(200, 200, 200), 1));
          paint.setFont(QFont("Courier", 20));
          paint.drawLine(500, 400, position + 1, 599);
          paint.drawLine(500, 400, 930, 400);
          paint.setPen(QPen(QColor(0, 0, 0), 1));
          if (mVector[i] < 0)
            paint.drawText (510, 380, " log10 (|" + QString::number(mVector[i]) + "|) = " + QString::number(log10(fabs(mVector[i]))));
          else
            paint.drawText (510, 380, " log10 (" + QString::number(fabs(mVector[i])) + ") = " + QString::number(log10(fabs(mVector[i]))));
          paint.drawText (450, 800, " log10 (X)");
        }
      else
        {
          if (mVector[i] < 0)
            paint.setPen(QPen(QColor(180, 20, 20), 2));
          else
            paint.setPen(QPen(QColor(20, 180, 20), 2));
          paint.drawLine(position, 699, position, 600);
        }
    }
  paint.restore();
}
