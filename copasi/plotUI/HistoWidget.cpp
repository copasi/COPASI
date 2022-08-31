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

#include <QtCore/QVariant>
#include <QPainter>

#include "HistoWidget.h"
#include "CQPlotEditWidget.h"
#include "CQPlotSubwidget.h"
#include "CQPlotColors.h"

#include "copasi/UI/CCopasiSelectionDialog.h"
#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/copasi.h"

#include "copasi/UI/qtUtilities.h"

#include "copasi/plot/CPlotItem.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"

HistoWidget::HistoWidget(QWidget* parent, Qt::WindowFlags fl):
  CQPlotEditWidget(parent, fl),
  mpObjectX(NULL)
{
  setupUi(this);

  mpBtnVariable->setIcon(CQIconResource::icon(CQIconResource::copasi));

  fillCombobox(mpBoxType, CPlotItem::LineTypeNames);
  fillCombobox(mpBoxLineSubType, CPlotItem::LineStyleNames);
  fillCombobox(mpBoxSymbolSubType, CPlotItem::SymbolNames);
}

HistoWidget::~HistoWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void HistoWidget::buttonPressedX()
{
  if (!mpModel) return;

  //  mpObjectX = CCopasiSelectionDialog::getObjectSingle(this, CQSimpleSelectionTree::NUMERIC, mpObjectX);
  //mpObjectX = CCopasiSelectionDialog::getObjectSingle(this, CQSimpleSelectionTree::PLOT_OBJECT, mpObjectX);

  std::vector< const CDataObject * > oldSelection;

  if (mpObjectX)
    oldSelection.push_back(mpObjectX);

  std::vector< const CDataObject * > objects =
    CCopasiSelectionDialog::getObjectVector(this,
        CQSimpleSelectionTree::NumericValues,
        &oldSelection);

  if (objects.size() && objects[0])
    {
      mpObjectX = objects[0];
      mpEditVariable->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
      mpEditTitle->setText("Histogram: " + FROM_UTF8(mpObjectX->getObjectDisplayName()));
    }
  else
    {
      mpObjectX = NULL;
      mpEditVariable->setText("");
      mpEditTitle->setText("Histogram");
    }

  //check if more than one object was selected...
  if (objects.size() > 1)
    {
      CQPlotSubwidget * pParent;
      QObject* tmp = this;

      while (!(pParent = dynamic_cast< CQPlotSubwidget * >(tmp)) && this)
        tmp = tmp->parent();

      if (pParent) //tell the parent to create the remaining histogram descriptions.
        pParent->createHistograms(objects, mpEditIncrement->text().toDouble());
    }
}

bool HistoWidget::LoadFromCurveSpec(const CPlotItem * curve)
{
  if (!curve)
    {
      // We need to reset the widget to defaults
      mpEditTitle->setText("");

      mpObjectX = NULL;
      mpEditVariable->setText("");

      mpEditIncrement->setText("");

      mpCheckBefore->setChecked(false);
      mpCheckDuring->setChecked(true);
      mpCheckAfter->setChecked(false);

      return true;
    }

  if (curve->getType() != CPlotItem::histoItem1d) return false;

  if (curve->getChannels().size() != 1) return false;

  //title
  mpEditTitle->setText(FROM_UTF8(curve->getTitle()));

  //variable
  mpObjectX = NULL;
  CDataModel* pDataModel = mpModel->getObjectDataModel();
  assert(pDataModel != NULL);

  if (curve->getChannels().size() >= 1)
    mpObjectX = CObjectInterface::DataObject(pDataModel->getObjectFromCN(curve->getChannels()[0]));

  if (mpObjectX == pDataModel)
    {
      mpObjectX = NULL;
    }

  if (mpObjectX != NULL)
    mpEditVariable->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
  else
    mpEditVariable->setText("");

  //other parameters:
  mpEditIncrement->setText(convertToQString(curve->getValue< C_FLOAT64 >("increment")));

  //Type
  unsigned C_INT32 linetype = curve->getValue< unsigned C_INT32 >("Line type");
  mpBoxType->setCurrentIndex(linetype);

  typeChanged(linetype);

  CPlotItem::LineType lineType = (CPlotItem::LineType) linetype;

  //line subtype & width
  if (lineType == CPlotItem::LineType::Lines || lineType == CPlotItem::LineType::LinesAndSymbols)
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
  if (lineType == CPlotItem::LineType::Symbols || lineType == CPlotItem::LineType::LinesAndSymbols)
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

  mpCheckBefore->setChecked(curve->getActivity() & COutputInterface::BEFORE);
  mpCheckDuring->setChecked(curve->getActivity() & COutputInterface::DURING);
  mpCheckAfter->setChecked(curve->getActivity() & COutputInterface::AFTER);

  return true; //TODO
}

bool HistoWidget::SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original /*= NULL*/) const
{

  C_INT32 Activity = 0;

  if (mpCheckBefore->isChecked()) Activity += COutputInterface::BEFORE;

  if (mpCheckDuring->isChecked()) Activity += COutputInterface::DURING;

  if (mpCheckAfter->isChecked()) Activity += COutputInterface::AFTER;

  std::string title = TO_UTF8(mpEditTitle->text());
  CCommonName name = mpObjectX ? mpObjectX->getCN() : CCommonName("");
  C_FLOAT64 increment = mpEditIncrement->text().toDouble();
  unsigned C_INT32 lineType = (unsigned C_INT32) mpBoxType->currentIndex();
  unsigned C_INT32 lineSubType = (unsigned C_INT32) mpBoxLineSubType->currentIndex();
  unsigned C_INT32 symbolSubType = (unsigned C_INT32) mpBoxSymbolSubType->currentIndex();
  C_FLOAT64 lineWidth = (C_FLOAT64) mpSpinBoxWidth->value();
  std::string color = TO_UTF8(mpBoxColor->currentText());

  bool changed = false;

  // compare whether things changed
  if (original == NULL
      || original->getTitle() != title)
    {
      changed = true;
      curve->setTitle(title);
    }

  if (original == NULL
      || original->getType() != CPlotItem::histoItem1d
      || original->getChannels().size() != 1)
    {
      changed = true;
      curve->setType(CPlotItem::histoItem1d);
      curve->getChannels().resize(1);
    }

  if (original == NULL
      || original->getValue< C_FLOAT64 >("increment") != increment)
    {
      changed = true;
      curve->setValue("increment", increment);
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
      || original->getChannels()[0] != name)
    {
      changed = true;
      curve->getChannels()[0] = CPlotDataChannelSpec(name);
    }

  return changed;
}

/**
 * In multiple edit mode, we don't want to edit name & channels
 */
void HistoWidget::setMultipleEditMode(bool mode)
{
  mpEditTitle->setEnabled(!mode);
  mpEditVariable->setEnabled(!mode);
  mpBtnVariable->setEnabled(!mode);
}


void HistoWidget::typeChanged(int type)
{
  CPlotItem::LineType linetype = (CPlotItem::LineType) type;

  if (linetype == CPlotItem::LineType::Lines || linetype == CPlotItem::LineType::LinesAndSymbols || linetype == CPlotItem::LineType::Points)
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
