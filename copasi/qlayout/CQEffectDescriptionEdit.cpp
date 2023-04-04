// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QColorDialog>

#include <copasi/qlayout/CQEffectDescription.h>
#include <copasi/qlayout/CQEffectDescriptionEdit.h>

#include <copasi/UI/CCopasiSelectionDialog.h>
#include <copasi/UI/CQCopasiApplication.h>
#include <copasi/UI/copasiui3window.h>
#include <copasi/UI/listviews.h>
#include <copasi/core/CRootContainer.h>
#include <copasi/core/CDataVector.h>
#include <copasi/CopasiDataModel/CDataModel.h>

#include "copasi/UI/qtUtilities.h"

#if QT_VERSION < QT_VERSION_CHECK(4,8,0)
#include <QPainter>
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
  palette.setColor(QPalette::Window, color);
  palette.setColor(QPalette::WindowText, color);
  widget->setPalette(palette);
  QImage image(widget->rect().size(), QImage::Format_ARGB32);

#if QT_VERSION >= QT_VERSION_CHECK(4,8,0)
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
  if (other == NULL)
    return;

  setColor(txtColorEnd, other->getEndColor());
  setColor(txtColorStart, other->getStartColor());

  if (multiple)
    txtObjectName->setText("");
  else
    txtObjectName->setText(other->getCN().c_str());

  if (multiple)
    txtDataObject->setText("");
  else
    txtDataObject->setText(other->getDataCN().c_str());

  txtScaleStart->setText(convertToQString(other->getScaleStart()));
  txtScaleEnd->setText(convertToQString(other->getScaleEnd()));

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

void CQEffectDescriptionEdit::saveTo(CQEffectDescription* other, bool multiple)
{
  if (other == NULL)
    return;

  other->setStartColor(txtColorStart->palette().color(QPalette::Window));
  other->setEndColor(txtColorEnd->palette().color(QPalette::Window));
  other->setScaleStart(txtScaleStart->text().toDouble());
  other->setScaleEnd(txtScaleEnd->text().toDouble());

  if (radColorize->isChecked())
    other->setMode(CQEffectDescription::Colorize);
  else if (radShadow->isChecked())
    other->setMode(CQEffectDescription::DropShadow);
  else
    other->setMode(CQEffectDescription::Scale);

  if (!multiple)
    {
      other->setDataCN(txtDataObject->text().toStdString());
      other->setCN(txtObjectName->text().toStdString());
    }
}

CQEffectDescription* CQEffectDescriptionEdit::toDescription() const
{
  CQEffectDescription *result = new CQEffectDescription(txtObjectName->text().toStdString());

  result->setStartColor(txtColorStart->palette().color(QPalette::Window));
  result->setEndColor(txtColorEnd->palette().color(QPalette::Window));
  result->setScaleStart(txtScaleStart->text().toDouble());
  result->setScaleEnd(txtScaleEnd->text().toDouble());

  if (radColorize->isChecked())
    result->setMode(CQEffectDescription::Colorize);
  else if (radShadow->isChecked())
    result->setMode(CQEffectDescription::DropShadow);
  else
    result->setMode(CQEffectDescription::Scale);

  result->setDataCN(txtDataObject->text().toStdString());

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
  auto * pModelList = CRootContainer::getDatamodelList();

  if (!pModelList || pModelList->empty())
    return;

  const CDataObject * pObject = dynamic_cast< const CDataObject * >((*pModelList)[0].getObjectFromCN(txtObjectName->text().toStdString()));

  pObject =
    CCopasiSelectionDialog::getObjectSingle(
      (dynamic_cast< CQCopasiApplication * >(qApp))
      ->getMainWindow()
      ->getMainWidget(),
      CQSimpleSelectionTree::Variables | CQSimpleSelectionTree::ObservedConstants | CQSimpleSelectionTree::ObservedValues, pObject);

  if (pObject)
    txtObjectName->setText(FROM_UTF8(pObject->getCN()));
}

void CQEffectDescriptionEdit::slotSelectDataObject()
{
  auto * pModelList = CRootContainer::getDatamodelList();

  if (!pModelList || pModelList->empty())
    return;

  const CDataObject * pObject = dynamic_cast< const CDataObject * >((*pModelList)[0].getObjectFromCN(txtDataObject->text().toStdString()));

  pObject =
    CCopasiSelectionDialog::getObjectSingle(
      (dynamic_cast< CQCopasiApplication * >(qApp))
      ->getMainWindow()
      ->getMainWidget(),
      CQSimpleSelectionTree::NumericValues, pObject);

  if (pObject)
    txtDataObject->setText(FROM_UTF8(pObject->getCN()));
}

void CQEffectDescriptionEdit::slotSelectColorEnd()
{
  setColor(txtColorEnd, QColorDialog::getColor(txtColorEnd->palette().color(QPalette::Window), this));
}

void CQEffectDescriptionEdit::slotSelectColorStart()
{
  setColor(txtColorStart, QColorDialog::getColor(txtColorStart->palette().color(QPalette::Window), this));
}
