// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "BandedGraphWidget.h"

#include <QPainter>

#include "copasi/UI/CCopasiSelectionDialog.h"
#include "copasi/UI/qtUtilities.h"
#include "CQPlotEditWidget.h"
#include "CQPlotColors.h"

#include "copasi/copasi.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/plot/CPlotItem.h"
#include "copasi/resourcesUI/CQIconResource.h"

/**
 * In multiple edit mode, we don't want to edit name & channels
 */
void BandedGraphWidget::setMultipleEditMode(bool mode)
{
  mpEditTitle->setEnabled(!mode);
  mpEditX->setEnabled(!mode);
  mpEditYone->setEnabled(!mode);
  mpEditYtwo->setEnabled(!mode);
  mpBtnX->setEnabled(!mode);
  mpBtnYone->setEnabled(!mode);
  mpBtnYtwo->setEnabled(!mode);
}

/*
 *  Constructs a BandedGraphWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
BandedGraphWidget::BandedGraphWidget(QWidget* parent, const char* /* name */, Qt::WindowFlags fl):
  CQPlotEditWidget(parent, fl),
  mpObjectYone(NULL),
  mpObjectYtwo(NULL),
  mpObjectX(NULL)
{
  setupUi(this);

  fillCombobox(mpBoxType, CPlotItem::LineTypeNames);
  fillCombobox(mpBoxLineSubType, CPlotItem::LineStyleNames);
  fillCombobox(mpBoxSymbolSubType, CPlotItem::SymbolNames);

  mpBtnX->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnYone->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnYtwo->setIcon(CQIconResource::icon(CQIconResource::copasi));
}

/*
 *  Destroys the object and frees any allocated resources
 */
BandedGraphWidget::~BandedGraphWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

bool
BandedGraphWidget::LoadFromCurveSpec(const CPlotItem * pCurve)
{
  if (!pCurve)
    {
      // We need to reset the widget to defaults
      mpEditTitle->setText("");

      mpObjectX = mpObjectYone = mpObjectYtwo = NULL;

      mpEditX->setText("");
      mpEditYone->setText("");
      mpEditYtwo->setText("");

      mpCheckBefore->setChecked(false);
      mpCheckDuring->setChecked(true);
      mpCheckAfter->setChecked(false);

      mpBoxType->setCurrentIndex(0);
      mpBoxLineSubType->setCurrentIndex(0);
      mpBoxColor->clear();

      return true;
    }

  if (pCurve->getType() != CPlotItem::bandedGraph) return false;

  //if (pCurve->getChannels().getSize != 3) return false;

  mpEditTitle->setText(FROM_UTF8(pCurve->getTitle()));

  const CDataModel* pDataModel = mpModel->getObjectDataModel();
  assert(pDataModel != NULL);

  mpObjectX = mpObjectYone = mpObjectYtwo = NULL;

  if (pCurve->getChannels().size() >= 1)
    mpObjectX = dynamic_cast<const CDataObject*>(pDataModel->getObject(pCurve->getChannels()[0]));

  if (pCurve->getChannels().size() >= 2)
    mpObjectYone = dynamic_cast<const CDataObject*>(pDataModel->getObject(pCurve->getChannels()[1]));

  if (pCurve->getChannels().size() >= 3)
    {
      mpObjectYtwo = dynamic_cast<const CDataObject*>(pDataModel->getObject(pCurve->getChannels()[2]));

      if ((mpObjectYtwo->getObjectDisplayName() == "(CN)Root") && mpObjectYone)
        mpObjectYtwo = mpObjectYone;  // as long as we haven't a second Y-axis chooser, this has to suffice.
    }

  if (mpObjectX)
    mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
  else
    mpEditX->clear();

  if (mpObjectYone)
    mpEditYone->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()));
  else
    mpEditYone->clear();

  if (mpObjectYtwo)
    mpEditYtwo->setText(FROM_UTF8(mpObjectYtwo->getObjectDisplayName()));
  else
    mpEditYtwo->clear();

  //Type
  unsigned C_INT32 linetype = pCurve->getValue< unsigned C_INT32 >("Line type");
  mpBoxType->setCurrentIndex(linetype);

  typeChanged(linetype);

  CPlotItem::LineType lineType = (CPlotItem::LineType) linetype;

  //line subtype & width
  if (lineType == CPlotItem::LineType::Lines || lineType == CPlotItem::LineType::LinesAndSymbols)
    {
      mpBoxLineSubType->setCurrentIndex(pCurve->getValue< unsigned C_INT32 >("Line subtype"));

      //mpBoxWidth
      mpSpinBoxWidth->setValue(pCurve->getValue< C_FLOAT64 >("Line width"));
    }

  // points
  if (lineType == CPlotItem::LineType::Points)
    {
      mpSpinBoxWidth->setValue(pCurve->getValue< C_FLOAT64 >("Line width"));
    }

  //symbol type
  if (lineType == CPlotItem::LineType::Symbols || lineType == CPlotItem::LineType::LinesAndSymbols)
    {
      mpBoxSymbolSubType->setCurrentIndex(pCurve->getValue< unsigned C_INT32 >("Symbol subtype"));
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

  std::string colorstr = pCurve->getValue< std::string >("Color");
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

  mpCheckBefore->setChecked(pCurve->getActivity() & COutputInterface::BEFORE);
  mpCheckDuring->setChecked(pCurve->getActivity() & COutputInterface::DURING);
  mpCheckAfter->setChecked(pCurve->getActivity() & COutputInterface::AFTER);

  return true;
}

void BandedGraphWidget::typeChanged(int type)
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
  if (linetype == CPlotItem::LineType::Symbols ||
      linetype == CPlotItem::LineType::LinesAndSymbols)
    {
      mpBoxSymbolSubType->setEnabled(true);
    }
  else
    {
      mpBoxSymbolSubType->setEnabled(false);
    }
}

bool
BandedGraphWidget::SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original /*= NULL*/) const
{
  //curve->setType(CPlotItem::bandedGraph);

  std::string title = TO_UTF8(mpEditTitle->text());
  unsigned C_INT32 lineType = (unsigned C_INT32) mpBoxType->currentIndex();
  unsigned C_INT32 lineSubType = (unsigned C_INT32) mpBoxLineSubType->currentIndex();
  unsigned C_INT32 symbolSubType = (unsigned C_INT32) mpBoxSymbolSubType->currentIndex();
  C_FLOAT64 lineWidth = (C_FLOAT64) mpSpinBoxWidth->value();
  std::string color = TO_UTF8(mpBoxColor->currentText());

  CCommonName xName = mpObjectX ? mpObjectX->getCN() : CCommonName("");
  CCommonName yName1 = mpObjectYone ? mpObjectYone->getCN() : CCommonName("");
  CCommonName yName2 = mpObjectYtwo ? mpObjectYtwo->getCN() : (mpObjectYone ? mpObjectYone->getCN() : CCommonName(""));

  C_INT32 Activity = 0;

  if (mpCheckBefore->isChecked()) Activity += COutputInterface::BEFORE;

  if (mpCheckDuring->isChecked()) Activity += COutputInterface::DURING;

  if (mpCheckAfter->isChecked()) Activity += COutputInterface::AFTER;

  bool changed = false;

  // compare whether things changed
  if (original == NULL
      || original->getTitle() != title)
    {
      changed = true;
      curve->setTitle(title);
    }

  if (original == NULL
      || original->getType() != CPlotItem::bandedGraph
      || original->getChannels().size() != 3)
    {
      changed = true;
      curve->setType(CPlotItem::bandedGraph);
      curve->getChannels().resize(3);
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
      || original->getChannels()[1] != yName1)
    {
      changed = true;
      curve->getChannels()[1] = CPlotDataChannelSpec(yName1);
    }

  if (original == NULL
      || original->getChannels()[2] != yName2)
    {
      changed = true;
      curve->getChannels()[2] = CPlotDataChannelSpec(yName2);
    }

  return changed;
}

void
BandedGraphWidget::buttonPressedX()
{
  if (!mpModel) return;

  mpObjectX = CCopasiSelectionDialog::getObjectSingle(this,
              CQSimpleSelectionTree::NumericValues,
              mpObjectX);

  if (mpObjectX)
    {
      mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));

      if (mpObjectYone)
        {
          if (mpObjectYtwo && (mpObjectYtwo != mpObjectYone))
            mpEditTitle->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()
                                           + "/"
                                           + mpObjectYtwo->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
          else
            mpEditTitle->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
        }

      //TODO update tab title
    }
  else
    mpEditX->setText("");
}

void
BandedGraphWidget::buttonPressedYone()
{
  if (!mpModel) return;

  mpObjectYone = CCopasiSelectionDialog::getObjectSingle(this,
                 CQSimpleSelectionTree::NumericValues,
                 mpObjectYone);

  if (mpObjectYone)
    {
      mpEditYone->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()));

      if (mpObjectX)
        {
          if (mpObjectYtwo && (mpObjectYtwo != mpObjectYone))
            mpEditTitle->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()
                                           + "/"
                                           + mpObjectYtwo->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
          else
            mpEditTitle->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
        }

      //TODO update tab title
    }
  else
    mpEditYone->setText("");
}

void
BandedGraphWidget::buttonPressedYtwo()
{
  if (!mpModel) return;

  mpObjectYtwo = CCopasiSelectionDialog::getObjectSingle(this,
                 CQSimpleSelectionTree::NumericValues,
                 mpObjectYtwo);

  if (mpObjectYtwo)
    {
      mpEditYtwo->setText(FROM_UTF8(mpObjectYtwo->getObjectDisplayName()));

      if (mpObjectX)
        {
          if (mpObjectYone && (mpObjectYone != mpObjectYtwo))
            mpEditTitle->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()
                                           + "/"
                                           + mpObjectYtwo->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
          else
            mpEditTitle->setText(FROM_UTF8(mpObjectYtwo->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
        }

      //TODO update tab title
    }
  else
    mpEditYtwo->setText("");
}
