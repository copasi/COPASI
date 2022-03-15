// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QPainter>
#include "curve2dwidget.h"
#include "CQPlotEditWidget.h"
#include "CQPlotColors.h"

#include "copasi/UI/CCopasiSelectionDialog.h"
#include "copasi/copasi.h"

#include "copasi/UI/qtUtilities.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/plot/CPlotItem.h"
#include "copasi/resourcesUI/CQIconResource.h"
#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"

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

  fillCombobox(mpBoxType, CPlotItem::LineTypeNames);
  fillCombobox(mpBoxLineSubType, CPlotItem::LineStyleNames);
  fillCombobox(mpBoxSymbolSubType, CPlotItem::SymbolNames);

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
  CDataModel* pDataModel = mpModel->getObjectDataModel();
  assert(pDataModel != NULL);
  mpObjectX = mpObjectY = NULL;

  if (curve->getChannels().size() >= 1)
    mpObjectX = CObjectInterface::DataObject(pDataModel->getObjectFromCN(curve->getChannels()[0]));

  if (curve->getChannels().size() >= 2)
    mpObjectY = CObjectInterface::DataObject(pDataModel->getObjectFromCN(curve->getChannels()[1]));

  if (mpObjectX)
    mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
  else
    mpEditX->clear();

  if (mpObjectY)
    mpEditY->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()));
  else
    mpEditY->clear();

  //Type
  unsigned C_INT32 linetype = curve->getValue< unsigned C_INT32 >("Line type");
  mpBoxType->setCurrentIndex(linetype);

  typeChanged(linetype);

  CPlotItem::LineType lineType = (CPlotItem::LineType) linetype;

  //line subtype & width
  if (lineType == CPlotItem::LineType::Lines ||
      lineType == CPlotItem::LineType::LinesAndSymbols)
    {
      mpBoxLineSubType->setCurrentIndex(curve->getValue< unsigned C_INT32 >("Line subtype"));

      //mpBoxWidth
      mpSpinBoxWidth->setValue(curve->getValue< C_FLOAT64 >("Line width"));
    }

  // points
  if (lineType == CPlotItem::LineType::Points)
    {
      mpSpinBoxWidth->setValue(curve->getValue< C_FLOAT64 >("Line width"));
    }

  //symbol type
  if (lineType == CPlotItem::LineType::Symbols ||
      lineType == CPlotItem::LineType::LinesAndSymbols)
    {
      mpBoxSymbolSubType->setCurrentIndex(curve->getValue< unsigned C_INT32 >("Symbol subtype"));
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

  std::string colorstr = curve->getValue< std::string >("Color");
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

  CCommonName xName = mpObjectX ? mpObjectX->getCN() : CCommonName("");
  CCommonName yName = mpObjectY ? mpObjectY->getCN() : CCommonName("");

  bool changed = false;

  // compare whether things changed
  if (original == NULL
      || original->getTitle() != title)
    {
      changed = true;
      curve->setTitle(title);
    }

  if (original == NULL
      || original->getType() != CPlotItem::curve2d
      || original->getChannels().size() != 2)
    {
      changed = true;
      curve->setType(CPlotItem::curve2d);
      curve->getChannels().resize(2);
    }

  if (original == NULL
      || original->getValue< unsigned C_INT32 >("Line type") != lineType)
    {
      changed = true;
      curve->setValue("Line type", lineType);
    }

  if (original == NULL
      || original->getValue< unsigned C_INT32 >("Line subtype") != lineSubType)
    {
      changed = true;
      curve->setValue("Line subtype", lineSubType);
    }

  if (original == NULL
      || original->getValue< unsigned C_INT32 >("Symbol subtype") != symbolSubType)
    {
      changed = true;
      curve->setValue("Symbol subtype", symbolSubType);
    }

  if (original == NULL
      || original->getValue< C_FLOAT64 >("Line width") != lineWidth)
    {
      changed = true;
      curve->setValue("Line width", lineWidth);
    }

  if (original == NULL
      || original->getValue< std::string >("Color") != color)
    {
      changed = true;
      curve->setValue("Color", color);
    }

  if (original == NULL
      || original->getActivity() != Activity)
    {
      changed = true;
      curve->setActivity((COutputInterface::Activity) Activity);
    }

  if (original == NULL
      || original->getChannels()[0] != xName)
    {
      changed = true;
      curve->getChannels()[0] = CPlotDataChannelSpec(xName);
    }

  if (original == NULL
      || original->getChannels()[1] != yName)
    {
      changed = true;
      curve->getChannels()[1] = CPlotDataChannelSpec(yName);
    }

  return changed;
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

void Curve2DWidget::typeChanged(int type)
{
  CPlotItem::LineType linetype = (CPlotItem::LineType) type;

  if (linetype == CPlotItem::LineType::Lines ||
      linetype == CPlotItem::LineType::LinesAndSymbols ||
      linetype == CPlotItem::LineType::Points)
    {
      mpBoxLineSubType->setEnabled(linetype != CPlotItem::LineType::Points);
      mpSpinBoxWidth->setEnabled(true);
    }
  else
    {
      mpBoxLineSubType->setEnabled(linetype == CPlotItem::LineType::Points);
      mpSpinBoxWidth->setEnabled(false);
    }

  //symbol type
  if (linetype == CPlotItem::LineType::Symbols || linetype == CPlotItem::LineType::LinesAndSymbols)
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
