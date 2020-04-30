// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQSpectogramWidget.h"

#include "copasi/UI/CCopasiSelectionDialog.h"
#include "CQPlotEditWidget.h"

#include "copasi/copasi.h"

#include "copasi/UI/qtUtilities.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/plot/CPlotItem.h"
#include "copasi/resourcesUI/CQIconResource.h"
#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"

/**
 * In multiple edit mode, we don't want to edit name & channels
 */
void CQSpectogramWidget::setMultipleEditMode(bool mode)
{
  mpEditTitle->setEnabled(!mode);
  mpEditX->setEnabled(!mode);
  mpEditY->setEnabled(!mode);
  mpEditZ->setEnabled(!mode);
  mpBtnX->setEnabled(!mode);
  mpBtnY->setEnabled(!mode);
  mpBtnZ->setEnabled(!mode);
}

/*
 *  Constructs a CQSpectogramWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQSpectogramWidget::CQSpectogramWidget(QWidget* parent, const char* /* name */, Qt::WindowFlags fl):
  CQPlotEditWidget(parent, fl),
  mpObjectX(NULL),
  mpObjectY(NULL),
  mpObjectZ(NULL)
{
  setupUi(this);

  mpBtnX->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnY->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnZ->setIcon(CQIconResource::icon(CQIconResource::copasi));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQSpectogramWidget::~CQSpectogramWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

bool
CQSpectogramWidget::LoadFromCurveSpec(const CPlotItem * pCurve)
{
  if (!pCurve)
    {
      // We need to reset the widget to defaults
      mpEditTitle->setText("");

      mpObjectX = mpObjectY = mpObjectZ = NULL;

      mpEditX->setText("");
      mpEditY->setText("");
      mpEditZ->setText("");

      mpCheckBefore->setChecked(false);
      mpCheckDuring->setChecked(true);
      mpCheckAfter->setChecked(false);

      return true;
    }

  if (pCurve->getType() != CPlotItem::spectogram) return false;

  //if (pCurve->getChannels().getSize != 3) return false;

  mpEditTitle->setText(FROM_UTF8(pCurve->getTitle()));

  //TODO: check if objects exist....
  CDataModel* pDataModel = mpModel->getObjectDataModel();
  assert(pDataModel != NULL);
  mpObjectX = mpObjectY = mpObjectZ = NULL;

  if (pCurve->getChannels().size() >= 1)
    mpObjectX = dynamic_cast<const CDataObject*>(pDataModel->getObject(pCurve->getChannels()[0]));

  if (pCurve->getChannels().size() >= 2)
    mpObjectY = dynamic_cast<const CDataObject*>(pDataModel->getObject(pCurve->getChannels()[1]));

  if (pCurve->getChannels().size() >= 3)
    {
      mpObjectZ = dynamic_cast<const CDataObject*>(pDataModel->getObject(pCurve->getChannels()[2]));

      if ((mpObjectZ == NULL || mpObjectZ->getObjectDisplayName() == "(CN)Root") && mpObjectY)
        mpObjectZ = mpObjectY;  // as long as we haven't a second Y-axis chooser, this has to suffice.
    }

  if (mpObjectX)
    mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
  else
    mpEditX->clear();

  if (mpObjectY)
    mpEditY->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()));
  else
    mpEditY->clear();

  if (mpObjectZ)
    mpEditZ->setText(FROM_UTF8(mpObjectZ->getObjectDisplayName()));
  else
    mpEditZ->clear();

  CPlotItem* pItem = const_cast<CPlotItem*>(pCurve);

  mpLogZ->setChecked(*pItem->assertParameter("logZ", CCopasiParameter::Type::BOOL, false));
  mpBilinear->setChecked(*pItem->assertParameter("bilinear", CCopasiParameter::Type::BOOL, true));
  std::string *contours = pItem->assertParameter("contours", CCopasiParameter::Type::STRING, std::string(""));
  mpContours->setText(FROM_UTF8(*contours));
  std::string *maxZ = pItem->assertParameter("maxZ", CCopasiParameter::Type::STRING, std::string(""));
  mpMaxZ->setText(FROM_UTF8(*maxZ));
  std::string *colorMap = pItem->assertParameter("colorMap", CCopasiParameter::Type::STRING, std::string("Default"));
  mpColorMap->setCurrentIndex(mpColorMap->findText(FROM_UTF8(*colorMap)));

  mpCheckBefore->setChecked(pCurve->getActivity() & COutputInterface::BEFORE);
  mpCheckDuring->setChecked(pCurve->getActivity() & COutputInterface::DURING);
  mpCheckAfter->setChecked(pCurve->getActivity() & COutputInterface::AFTER);

  return true;
}

bool
CQSpectogramWidget::SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original /*= NULL*/) const
{
  curve->setType(CPlotItem::spectogram);

  std::string title = TO_UTF8(mpEditTitle->text());

  CCommonName xName = mpObjectX ? mpObjectX->getCN() : CCommonName("");
  CCommonName yName = mpObjectY ? mpObjectY->getCN() : CCommonName("");
  CCommonName zName = mpObjectZ ? mpObjectZ->getCN() : CCommonName("");

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
      || original->getType() != CPlotItem::spectogram
      || original->getChannels().size() != 3)
    {
      changed = true;
      curve->setType(CPlotItem::spectogram);
      curve->getChannels().resize(3);
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

  if (original == NULL
      || original->getChannels()[2] != zName)
    {
      changed = true;
      curve->getChannels()[2] = CPlotDataChannelSpec(zName);
    }

  if (original == NULL
      || *curve->assertParameter("contours", CCopasiParameter::Type::STRING, std::string("")) != TO_UTF8(mpContours->text()))
    {
      changed = true;
      std::string * pContours = curve->assertParameter("contours", CCopasiParameter::Type::STRING, std::string(""));
      *pContours = TO_UTF8(mpContours->text());
    }

  if (original == NULL
      || *curve->assertParameter("maxZ", CCopasiParameter::Type::STRING, std::string("")) != TO_UTF8(mpMaxZ->text()))
    {
      changed = true;
      std::string * pMaxZ = curve->assertParameter("maxZ", CCopasiParameter::Type::STRING, std::string(""));
      *pMaxZ = TO_UTF8(mpMaxZ->text());
    }

  if (original == NULL
      || *curve->assertParameter("colorMap", CCopasiParameter::Type::STRING, std::string("")) != TO_UTF8(mpColorMap->currentText()))
    {
      changed = true;
      std::string * pColorMap = curve->assertParameter("colorMap", CCopasiParameter::Type::STRING, std::string("Default"));
      *pColorMap = TO_UTF8(mpColorMap->currentText());
    }

  if (original == NULL
      || *curve->assertParameter("logZ", CCopasiParameter::Type::BOOL, false) != mpLogZ->isChecked())
    {
      changed = true;
      bool * pLogZ = curve->assertParameter("logZ", CCopasiParameter::Type::BOOL, false);
      *pLogZ = mpLogZ->isChecked();
    }

  if (original == NULL
      || *curve->assertParameter("bilinear", CCopasiParameter::Type::BOOL, true) != mpBilinear->isChecked())
    {
      changed = true;
      bool * pBilinear = curve->assertParameter("bilinear", CCopasiParameter::Type::BOOL, true);
      *pBilinear = mpBilinear->isChecked();
    }

  return changed;
}

void
CQSpectogramWidget::buttonPressedX()
{
  if (!mpModel) return;

  mpObjectX = CCopasiSelectionDialog::getObjectSingle(this,
              CQSimpleSelectionTree::NumericValues,
              mpObjectX);

  if (mpObjectX)
    {
      mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));

      if (mpObjectY)
        {
          if (mpObjectZ && (mpObjectZ != mpObjectY))
            mpEditTitle->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()
                                           + "/"
                                           + mpObjectZ->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
          else
            mpEditTitle->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
        }

      //TODO update tab title
    }
  else
    mpEditX->setText("");
}

void
CQSpectogramWidget::buttonPressedY()
{
  if (!mpModel) return;

  mpObjectY = CCopasiSelectionDialog::getObjectSingle(this,
              CQSimpleSelectionTree::NumericValues,
              mpObjectY);

  if (mpObjectY)
    {
      mpEditY->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()));

      if (mpObjectX)
        {
          if (mpObjectZ && (mpObjectZ != mpObjectY))
            mpEditTitle->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()
                                           + "/"
                                           + mpObjectZ->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
          else
            mpEditTitle->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
        }

      //TODO update tab title
    }
  else
    mpEditY->setText("");
}

void
CQSpectogramWidget::buttonPressedZ()
{
  if (!mpModel) return;

  mpObjectZ = CCopasiSelectionDialog::getObjectSingle(this,
              CQSimpleSelectionTree::NumericValues,
              mpObjectZ);

  if (mpObjectZ)
    {
      mpEditZ->setText(FROM_UTF8(mpObjectZ->getObjectDisplayName()));

      if (mpObjectX)
        {
          if (mpObjectY && (mpObjectY != mpObjectZ))
            mpEditTitle->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()
                                           + "/"
                                           + mpObjectZ->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
          else
            mpEditTitle->setText(FROM_UTF8(mpObjectZ->getObjectDisplayName()
                                           + "|"
                                           + mpObjectX->getObjectDisplayName()));
        }

      //TODO update tab title
    }
  else
    mpEditZ->setText("");
}
