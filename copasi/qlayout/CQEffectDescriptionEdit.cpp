// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtGui/QColorDialog>

#include <qlayout/CQEffectDescription.h>
#include <qlayout/CQEffectDescriptionEdit.h>

#if QT_VERSION < 0x040800
#include <QtGui/QPainter>
#endif

CQEffectDescriptionEdit::CQEffectDescriptionEdit(QWidget* parent, Qt::WindowFlags f):
  QWidget(parent, f),
  mpCurrent(NULL)
{
  setupUi(this);
}

CQEffectDescriptionEdit::~CQEffectDescriptionEdit()
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

#if QT_VERSION >= 0x040800
  image.fill(color);
#else
  QPainter painter(&image);
  painter.fillRect(widget->rect(), color);
#endif

  QPixmap pix = QPixmap::fromImage(image);
  widget->setPixmap(pix);
}

void CQEffectDescriptionEdit::initFrom(const CQEffectDescription* other, bool multiple)
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
      case CQEffectDescription::Colorize:
        radColorize->setChecked(true);
        break;

      case CQEffectDescription::DropShadow:
        radShadow->setChecked(true);
        break;

      default:
      case CQEffectDescription::Scale:
        radScale->setChecked(true);
        break;
    }
}

void CQEffectDescriptionEdit::saveTo(CQEffectDescription* other, bool /* multiple*/)
{
  other->setStartColor(txtColorStart->palette().color(QPalette::Background));
  other->setEndColor(txtColorEnd->palette().color(QPalette::Background));
  other->setScaleStart(txtScaleStart->text().toDouble());
  other->setScaleEnd(txtScaleEnd->text().toDouble());

  if (radColorize->isChecked())
    other->setMode(CQEffectDescription::Colorize);
  else if (radShadow->isChecked())
    other->setMode(CQEffectDescription::DropShadow);
  else
    other->setMode(CQEffectDescription::Scale);
}

CQEffectDescription* CQEffectDescriptionEdit::toDescription() const
{
  CQEffectDescription *result = new CQEffectDescription(txtObjectName->text().toStdString());

  result->setStartColor(txtColorStart->palette().color(QPalette::Background));
  result->setEndColor(txtColorEnd->palette().color(QPalette::Background));
  result->setScaleStart(txtScaleStart->text().toDouble());
  result->setScaleEnd(txtScaleEnd->text().toDouble());

  if (radColorize->isChecked())
    result->setMode(CQEffectDescription::Colorize);
  else if (radShadow->isChecked())
    result->setMode(CQEffectDescription::DropShadow);
  else
    result->setMode(CQEffectDescription::Scale);

  return result;
}

void CQEffectDescriptionEdit::slotModeChanged()
{
}

void CQEffectDescriptionEdit::slotScaleEndChanged(QString)
{
}

void CQEffectDescriptionEdit::slotScaleStartChanged(QString)
{
}

void CQEffectDescriptionEdit::slotSelectObject()
{
}

void CQEffectDescriptionEdit::slotSelectColorEnd()
{
  setColor(txtColorEnd, QColorDialog::getColor(txtColorEnd->palette().color(QPalette::Background), this));
}

void CQEffectDescriptionEdit::slotSelectColorStart()
{
  setColor(txtColorStart, QColorDialog::getColor(txtColorStart->palette().color(QPalette::Background), this));
}
