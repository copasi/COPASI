// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQTSSATimeScaleWidget.h"

#include <cmath>
#include <QBitmap>
#include <QColor>
#include <QToolTip>
#include <QVBoxLayout>
#include <QPaintEvent>

#include "copasi/UI/qtUtilities.h"

/*
 *  Constructs a CScanWidgetRepeat as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQTSSATimeScaleWidget::CQTSSATimeScaleWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
  : QWidget(parent, fl)
{
  setObjectName(QString::fromUtf8(name));

  if (!name)
    setObjectName("CQTSSATimeScaleWidget");

  mpVLayout = new QVBoxLayout(this);
  mpPaintWidget = new PaintWidget(this, "PaintWidget");
  mpPaintWidget->setMinimumHeight(200);
  mpSlider = new QSlider(Qt::Horizontal, this);
  mpSlider->setDisabled(true);

  mpVLayout->addWidget(mpPaintWidget);
  mpVLayout->addWidget(mpSlider);

  mpPaintWidget->setStyleSheet(QString(mpPaintWidget->metaObject()->className()) + " {background-color:" + QColor(Qt::white).name() + ";}");
  mpPaintWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  mpSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  mpSlider->setToolTip("move slider to set focus on preferred time scale");  // <- helpful

  mpVLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Fixed));

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
          mpSlider->setRange(0, (int)(vector.size() - 1));
          mpSlider->setValue(mpSlider->minimum());
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
PaintWidget::PaintWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
  : QWidget(parent, fl),
    mSelection(0)
{
  setObjectName(QString::fromUtf8(name));

  if (!name)
    setObjectName("PaintWidget");
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
      if (fabs(mVector[j]) == std::numeric_limits<C_FLOAT64>::infinity())
        continue;

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
  paint.drawText(space + 5, space + 10, " - negative time scale values");

  paint.setPen(QPen(QColor(0, 180, 0), 5));
  paint.drawLine(space, space + 20, space, space + 30);
  paint.setPen(QPen(QColor(0, 0, 0), 1));
  paint.drawText(space + 5, space + 30, " - positive time scale values");

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
            paint.drawText(xText + 1, yText - 15, " log10 (|" + convertToQString(mVector[j]) + "|) = " + convertToQString(log10(fabs(mVector[j]))));
          else
            paint.drawText(xText + 1, yText - 15, " log10 (" + convertToQString(fabs(mVector[j])) + ") = " + convertToQString(log10(fabs(mVector[j]))));

          paint.drawText(scaleBegin + scaleEnd / 2 - 50, yCentre + 50, " log timescale");
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
