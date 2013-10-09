// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtGui/QPainter>
#include "curve2dwidget.h"
#include "CQPlotEditWidget.h"

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
Curve2DWidget::Curve2DWidget(QWidget* parent, const char* /* name */, Qt::WindowFlags fl):
  CQPlotEditWidget(parent, fl),
  mpObjectY(NULL),
  mpObjectX(NULL)
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
  if (!curve)
    {
      // We need to reset the widget to defaults
      mpEditTitle->setText("");

      mpObjectX = NULL;
      mpEditX->setText("");

      mpObjectY = NULL;
      mpEditY->setText("");

      mpBoxType->setCurrentIndex(0);
      mpBoxLineSubType->setCurrentIndex(0);
      mpBoxColor->clear();

      mpCheckBefore->setChecked(false);
      mpCheckDuring->setChecked(true);
      mpCheckAfter->setChecked(false);

      return true;
    }

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

  // points
  if (linetype == 1)
    {
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

bool Curve2DWidget::SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original /*= NULL*/) const
{
  //if (!(mpObjectX && mpObjectY)) return false;

  //curve->setType(CPlotItem::curve2d);

  std::string title = TO_UTF8(mpEditTitle->text());
  unsigned C_INT32 lineType = (unsigned C_INT32)mpBoxType->currentIndex();
  unsigned C_INT32 lineSubType = (unsigned C_INT32)mpBoxLineSubType->currentIndex();
  unsigned C_INT32 symbolSubType = (unsigned C_INT32)mpBoxSymbolSubType->currentIndex();
  C_FLOAT64 lineWidth = (C_FLOAT64)mpSpinBoxWidth->value();
  std::string color = TO_UTF8(mpBoxColor->currentText());

  C_INT32 Activity = 0;

  if (mpCheckBefore->isChecked()) Activity += COutputInterface::BEFORE;

  if (mpCheckDuring->isChecked()) Activity += COutputInterface::DURING;

  if (mpCheckAfter->isChecked()) Activity += COutputInterface::AFTER;

  CCopasiObjectName xName = mpObjectX ? mpObjectX->getCN() : CCopasiObjectName("");
  CCopasiObjectName yName = mpObjectY ? mpObjectY->getCN() : CCopasiObjectName("");

  bool thingsChanged = false;

  if (original != NULL)
    {
      // compare whether things changed
      if (original->getTitle() != title)
        thingsChanged = true;

      if (thingsChanged || original->getType() != CPlotItem::curve2d)
        thingsChanged = true;

      if (thingsChanged || *original->getValue("Line type").pUINT != lineType)
        thingsChanged = true;

      if (thingsChanged || *original->getValue("Line subtype").pUINT != lineSubType)
        thingsChanged = true;

      if (thingsChanged || *original->getValue("Symbol subtype").pUINT != symbolSubType)
        thingsChanged = true;

      if (thingsChanged || *original->getValue("Line width").pDOUBLE != lineWidth)
        thingsChanged = true;

      if (thingsChanged || *original->getValue("Color").pSTRING != color)
        thingsChanged = true;

      if (thingsChanged || original->getActivity() != Activity)
        thingsChanged = true;

      if (thingsChanged || original->getChannels().size() != 2)
        thingsChanged = true;

      if (thingsChanged || original->getChannels()[0] != xName)
        thingsChanged = true;

      if (thingsChanged || original->getChannels()[1] != yName)
        thingsChanged = true;
    }
  else thingsChanged = true;

  if (!thingsChanged)
    return false;

  //title
  curve->setTitle(title);

  //channels
  curve->getChannels().clear();
  curve->getChannels().push_back(CPlotDataChannelSpec(xName));
  curve->getChannels().push_back(CPlotDataChannelSpec(yName));

  curve->setValue("Line type", lineType);
  curve->setValue("Line subtype", lineSubType);
  curve->setValue("Symbol subtype", symbolSubType);
  curve->setValue("Line width", lineWidth);

  //color
  curve->setValue("Color", color);

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
  if (linetype == 0 || linetype == 3 || linetype == 1)
    {
      mpBoxLineSubType->setEnabled(linetype != 1);
      mpSpinBoxWidth->setEnabled(true);
    }
  else
    {
      mpBoxLineSubType->setEnabled(linetype == 1);
      mpSpinBoxWidth->setEnabled(false);
    }

  //symbol type
  if (linetype == 2 || linetype == 3)
    {
      mpBoxSymbolSubType->setEnabled(true);
    }
  else
    {
      mpBoxSymbolSubType->setEnabled(false);
    }
}

/**
 * In multiple edit mode, we don't want to edit name & channels
 */
void Curve2DWidget::setMultipleEditMode(bool mode)
{
  mpEditTitle->setEnabled(!mode);
  mpEditX->setEnabled(!mode);
  mpEditY->setEnabled(!mode);
  mpBtnX->setEnabled(!mode);
  mpBtnY->setEnabled(!mode);
}
