// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QColorDialog>

#include <qlayout/qeffectdescription.h>
#include <qlayout/qeffectdescriptionedit.h>

#if QT_VERSION < 40800
#include <QPainter>
#endif

QEffectDescriptionEdit::QEffectDescriptionEdit(QWidget* parent, Qt::WindowFlags f)
  : QWidget(parent, f)
{
  setupUi(this);
}

QEffectDescriptionEdit::~QEffectDescriptionEdit()
{
}

void setColor(QLabel *widget, const QColor& color)
{
  QPalette palette(color);
  palette.setColor(QPalette::Base, color);
  palette.setColor(QPalette::Background, color);
  palette.setColor(QPalette::Window, color);
  palette.setColor(QPalette::Foreground, color);
  widget->setPalette(palette);
  QImage image(widget->rect().size(), QImage::Format_ARGB32);

#if QT_VERSION >= 40800
  image.fill(color);
#else
  QPainter painter(&image);
  painter.fillRect(widget->rect(), color);
#endif

  QPixmap pix = QPixmap::fromImage(image);
  widget->setPixmap(pix);
}

void QEffectDescriptionEdit::initFrom(const QEffectDescription* other, bool multiple)
{
  setColor(txtColorEnd, other->getEndColor());
  setColor(txtColorStart, other->getStartColor());

  if (multiple)
    txtObjectName->setText("");
  else
    txtObjectName->setText(other->getCN().c_str());

  txtScaleStart->setText(QString::number(other->getScaleStart()));
  txtScaleEnd->setText(QString::number(other->getScaleEnd()));

  switch (other->getMode())
    {
      case QEffectDescription::Colorize:
        radColorize->setChecked(true);
        break;

      case QEffectDescription::DropShadow:
        radShadow->setChecked(true);
        break;

      default:
      case QEffectDescription::Scale:
        radScale->setChecked(true);
        break;
    }
}

void QEffectDescriptionEdit::saveTo(QEffectDescription* other, bool /* multiple*/)
{
  other->setStartColor(txtColorStart->palette().color(QPalette::Background));
  other->setEndColor(txtColorEnd->palette().color(QPalette::Background));
  other->setScaleStart(txtScaleStart->text().toDouble());
  other->setScaleEnd(txtScaleEnd->text().toDouble());

  if (radColorize->isChecked())
    other->setMode(QEffectDescription::Colorize);
  else if (radShadow->isChecked())
    other->setMode(QEffectDescription::DropShadow);
  else
    other->setMode(QEffectDescription::Scale);
}

QEffectDescription* QEffectDescriptionEdit::toDescription() const
{
  QEffectDescription *result = new QEffectDescription(txtObjectName->text().toStdString());

  result->setStartColor(txtColorStart->palette().color(QPalette::Background));
  result->setEndColor(txtColorEnd->palette().color(QPalette::Background));
  result->setScaleStart(txtScaleStart->text().toDouble());
  result->setScaleEnd(txtScaleEnd->text().toDouble());

  if (radColorize->isChecked())
    result->setMode(QEffectDescription::Colorize);
  else if (radShadow->isChecked())
    result->setMode(QEffectDescription::DropShadow);
  else
    result->setMode(QEffectDescription::Scale);

  return result;
}

void QEffectDescriptionEdit::slotModeChanged()
{
}

void QEffectDescriptionEdit::slotScaleEndChanged(QString)
{
}

void QEffectDescriptionEdit::slotScaleStartChanged(QString)
{
}

void QEffectDescriptionEdit::slotSelectObject()
{
}

void QEffectDescriptionEdit::slotSelectColorEnd()
{
  setColor(txtColorEnd, QColorDialog::getColor(txtColorEnd->palette().color(QPalette::Background), this));
}

void QEffectDescriptionEdit::slotSelectColorStart()
{
  setColor(txtColorStart, QColorDialog::getColor(txtColorStart->palette().color(QPalette::Background), this));
}
