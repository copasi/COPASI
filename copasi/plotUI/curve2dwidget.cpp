// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/curve2dwidget.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2012/05/03 14:25:48 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <qpainter.h>
#include "curve2dwidget.h"

#include "UI/CCopasiSelectionDialog.h"
#include "UI/qtUtilities.h"

#include "copasi.h"

#include "report/CCopasiRootContainer.h"
#include "plot/CPlotItem.h"
#include "CQPlotColors.h"
#include "resourcesUI/CQIconResource.h"

/*
 *  Constructs a Curve2DWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
Curve2DWidget::Curve2DWidget(QWidget* parent, const char* /* name */, Qt::WindowFlags fl)
    : QWidget(parent, fl)
{
  setupUi(this);


  mpBtnX->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnY->setIcon(CQIconResource::icon(CQIconResource::copasi));
}

/*
 *  Destroys the object and frees any allocated resources
 */
Curve2DWidget::~Curve2DWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

bool Curve2DWidget::LoadFromCurveSpec(const CPlotItem * curve)
{
  if (!curve) return false;

  if (curve->getType() != CPlotItem::curve2d) return false;

  //if (curve->getChannels().getSize != 2) return false;

  mpEditTitle->setText(FROM_UTF8(curve->getTitle()));

  //TODO: check if objects exist....
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  mpObjectX = mpObjectY = NULL;

  if (curve->getChannels().size() >= 1)
    mpObjectX = pDataModel->getDataObject(curve->getChannels()[0]);

  if (curve->getChannels().size() >= 2)
    mpObjectY = pDataModel->getDataObject(curve->getChannels()[1]);

  if (mpObjectX)
    mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));

  if (mpObjectY)
    mpEditY->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()));

  const void* tmp;

  //Type
  if (!(tmp = curve->getValue("Line type").pVOID)) return false;

  unsigned C_INT32 linetype = *(unsigned C_INT32*)tmp;
  mpBoxType->setCurrentIndex(linetype);

  typeChanged(linetype);

  //line subtype & width
  if (linetype == 0 || linetype == 3)
    {
      if (!(tmp = curve->getValue("Line subtype").pVOID)) return false;

      mpBoxLineSubType->setCurrentIndex(*(unsigned C_INT32*)tmp);

      //mpBoxWidth
      if (!(tmp = curve->getValue("Line width").pVOID)) return false;

      mpSpinBoxWidth->setValue(*(C_FLOAT64*)tmp);
    }

  //symbol type
  if (linetype == 2 || linetype == 3)
    {
      if (!(tmp = curve->getValue("Symbol subtype").pVOID)) return false;

      mpBoxSymbolSubType->setCurrentIndex(*(unsigned C_INT32*)tmp);
    }

  //color TODO
  mpBoxColor->clear();
  mpBoxColor->addItem("auto");
  size_t i;

  for (i = 0; i < CQPlotColors::getNumCopasiColors(); ++i)
    {
      QColor color = CQPlotColors::getColor("auto", i);
      QPixmap pix(12, 12);
      QPainter painter(&pix);

      if (color.isValid())
        {
          painter.setPen(Qt::gray);
          painter.setBrush(QBrush(color));
          painter.drawRect(0, 0, 12, 12);
        }

      QIcon icon;
      icon.addPixmap(pix);

      mpBoxColor->addItem(icon, CQPlotColors::getCopasiColorStr(i).c_str());
    }

  if (!(tmp = curve->getValue("Color").pVOID)) return false;

  std::string colorstr = *(std::string*)tmp;
  int tmpindex;

  if ((tmpindex = mpBoxColor->findText(colorstr.c_str())) != -1)
    mpBoxColor->setCurrentIndex(tmpindex);
  else
    {
      QColor color = QColor(colorstr.c_str());
      QPixmap pix(12, 12);
      QPainter painter(&pix);

      if (color.isValid())
        {
          painter.setPen(Qt::gray);
          painter.setBrush(QBrush(color));
          painter.drawRect(0, 0, 12, 12);
        }

      QIcon icon;
      icon.addPixmap(pix);

      mpBoxColor->addItem(icon, colorstr.c_str());
      mpBoxColor->setCurrentIndex(mpBoxColor->count() - 1);
    }


  //channel
  mpCheckBefore->setChecked(curve->getActivity() & COutputInterface::BEFORE);
  mpCheckDuring->setChecked(curve->getActivity() & COutputInterface::DURING);
  mpCheckAfter->setChecked(curve->getActivity() & COutputInterface::AFTER);

  return true; //TODO
}

bool Curve2DWidget::SaveToCurveSpec(CPlotItem * curve) const
{
  //if (!(mpObjectX && mpObjectY)) return false;

  //title
  curve->setTitle(TO_UTF8(mpEditTitle->text()));

  //channels
  curve->getChannels().clear();
  curve->getChannels().push_back(CPlotDataChannelSpec(mpObjectX ? mpObjectX->getCN() : CCopasiObjectName("")));
  curve->getChannels().push_back(CPlotDataChannelSpec(mpObjectY ? mpObjectY->getCN() : CCopasiObjectName("")));

  curve->setValue("Line type", (unsigned C_INT32)mpBoxType->currentIndex());
  curve->setValue("Line subtype", (unsigned C_INT32)mpBoxLineSubType->currentIndex());
  curve->setValue("Symbol subtype", (unsigned C_INT32)mpBoxSymbolSubType->currentIndex());
  curve->setValue("Line width", (C_FLOAT64)mpSpinBoxWidth->value());

  //color
  curve->setValue("Color", std::string(TO_UTF8(mpBoxColor->currentText())));

  C_INT32 Activity = 0;

  if (mpCheckBefore->isChecked()) Activity += COutputInterface::BEFORE;

  if (mpCheckDuring->isChecked()) Activity += COutputInterface::DURING;

  if (mpCheckAfter->isChecked()) Activity += COutputInterface::AFTER;

  curve->setActivity((COutputInterface::Activity) Activity);

  return true;
}

void Curve2DWidget::buttonPressedX()
{
  if (!mpModel) return;

  mpObjectX = CCopasiSelectionDialog::getObjectSingle(this,
              CQSimpleSelectionTree::NumericValues,
              mpObjectX);

  if (mpObjectX)
    {
      mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));

      if (mpObjectY)
        mpEditTitle->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()
                                       + "|"
                                       + mpObjectX->getObjectDisplayName()));

      //TODO update tab title
    }
  else
    mpEditX->setText("");
}

void Curve2DWidget::buttonPressedY()
{
  if (!mpModel) return;

  mpObjectY = CCopasiSelectionDialog::getObjectSingle(this,
              CQSimpleSelectionTree::NumericValues,
              mpObjectY);

  if (mpObjectY)
    {
      mpEditY->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()));

      if (mpObjectX)
        mpEditTitle->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()
                                       + "|"
                                       + mpObjectX->getObjectDisplayName()));

      //TODO update tab title
    }
  else
    mpEditY->setText("");
}

void Curve2DWidget::typeChanged(int linetype)
{
  if (linetype == 0 || linetype == 3)
    {
      mpBoxLineSubType->show();
      mpSpinBoxWidth->show();
      mpLblWidth->show();
    }
  else
    {
      mpBoxLineSubType->hide();
      mpSpinBoxWidth->hide();
      mpLblWidth->hide();
    }

  //symbol type
  if (linetype == 2 || linetype == 3)
    {
      mpBoxSymbolSubType->show();
    }
  else
    {
      mpBoxSymbolSubType->hide();
    }

}


void Curve2DWidget::setModel(const CModel * model)
{
  mpModel = model;
}
